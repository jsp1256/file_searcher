#include "platform.h"


#ifdef USE_LINUX
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#elif USE_WINDOWS_COMMON
#include <io.h>
#endif

#include <ctime>

#include "lib_search.h"
#include "lib_str.h"

using namespace std;

static inline string get_local_name_from_absolute_path(string absolute_path)
{
    return absolute_path.substr(absolute_path.find_last_of("/\\") + 1);
}

typedef struct file_store_st{
    file_store_st(string absolute_path){
        this->dir_name = get_local_name_from_absolute_path(absolute_path);
        this->absolute_path = absolute_path;
        this->status = SCAN_UNFINISHED;
        this->last_scan_time = 0;
        this->pre = nullptr;
    }
    string dir_name;						//记录的目录名
    string absolute_path;					//此目录所在的绝对目录路径
    node_status status;						//节点扫描状态,上次扫描时间，如果节点状态是SCAN_UNFINISHED，则表示未成功扫描过
    time_t last_scan_time;					//末次扫描时间
    struct file_store_st *pre;				//父目录节点索引
    list<struct file_store_st> subdir_list;	//子目录节点索引
    list<string> file_name_list;			//此目录下存储的文件名列表

}file_store_st;

static file_store_st *g_node = nullptr;

static func_status init_node(string start_path)
{
    if(nullptr == g_node) {
        g_node = new file_store_st(start_path);
        return SUCCESS;
    }
    return NODE_IS_EXSIT;
}

static void clear_node_list(file_store_st &dir_node)
{
    dir_node.file_name_list.clear();
    if(dir_node.subdir_list.empty())
        return;
    list<struct file_store_st>::iterator dir_it;
    for(dir_it = dir_node.subdir_list.begin(); dir_it != dir_node.subdir_list.end(); dir_it++){
        clear_node_list(*dir_it);
    }
    dir_node.subdir_list.clear();
}

static func_status dinit_node()
{
    if(nullptr != g_node) {
        clear_node_list(*g_node);
        delete g_node;
        return SUCCESS;
    }
    return NODE_NOT_EXSIT;
}

#ifdef USE_LINUX
/*
 * @brief 根据给定的dir_node，列出一个目录下所有的文件
 * @detail Linux系统依赖
 * @param  dir_node 存储节点
 * @return 成功返回SUCCESS，错误返回对应的错误代码
 */
static func_status scan_one_dir(file_store_st &dir_node)
{  
    if(dir_node.dir_name.empty() || !dir_node.dir_name.size()) return PARAM_IS_NULL;

    struct stat dir_stat;
    lstat(dir_node.absolute_path.data() , &dir_stat);
    if(!S_ISDIR(dir_stat.st_mode)) return PARAM_NOT_DIR;

    struct dirent *entry;
    DIR *dir;
    dir = opendir(dir_node.absolute_path.data());
    if(nullptr == dir) return OPEN_DIR_FAIL;
    chdir(dir_node.absolute_path.data());
    printf("%s scan start", dir_node.absolute_path.data());
    while((entry = readdir(dir)) != nullptr)
    {
        if( strcmp(entry->d_name ,".") == 0 ||
                strcmp(entry->d_name ,"..") == 0)
            continue;
        lstat(entry->d_name, &dir_stat);    // 获取下一级成员属性
        if(S_ISDIR(dir_stat.st_mode)) {    // 判断下一级成员是否是目录
            file_store_st new_node(string(dir_node.absolute_path).append("/").append(entry->d_name));
            new_node.pre = &dir_node;
            dir_node.subdir_list.push_back(new_node);
        } else {
            dir_node.file_name_list.push_back(string(entry->d_name));
        }
    }
    time(&dir_node.last_scan_time);
    return SUCCESS;
}
#elif USE_WINDOWS_COMMON
/*
 * @brief 根据给定的dir_node，列出一个目录下所有的文件
 * @detail Windows系统依赖,未验证
 * @param  dir_node 存储节点
 * @return 成功返回SUCCESS，错误返回对应的错误代码
 */
static func_status scan_one_dir(file_store_st &dir_node)
{
    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(string(dir_node.absolute_path).append("\\*.*").data(), &findData);
    if (handle == -1)        // 检查是否成功
        return HANDLE_IS_NULL;
    do{
        if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
            continue;
        if (findData.attrib & _A_SUBDIR){
            file_store_st new_node(string(dir_node.absolute_path).append("\\").append(findData.name));
            new_node.pre = &dir_node;
            dir_node.subdir_list.push_back(new_node);
        }
        else
            dir_node.file_name_list.push_back(string(findData.name));
    }
    while (_findnext(handle, &findData) == 0);

    _findclose(handle);    // 关闭搜索句柄
    time(&dir_node.last_scan_time);
    return SUCCESS;
}
#endif

/*
 * @brief 根据给定的dir_node，递归列出一个目录下所有的文件
 * @param  dir_node 存储节点
 * @return 成功返回SUCCESS，错误返回对应的错误代码
 */
static func_status recursion_scan_dir_file(file_store_st &dir_node)
{
    func_status ret = scan_one_dir(dir_node);
    if(SUCCESS != ret) return ret;
    if(!dir_node.subdir_list.size())
        return SUCCESS;
    list<struct file_store_st>::iterator dir_it;
    for(dir_it = dir_node.subdir_list.begin(); dir_it != dir_node.subdir_list.end(); dir_it++){
        ret = recursion_scan_dir_file(*dir_it);
        if(SUCCESS != ret) return ret;
    }
    return SUCCESS;
}

int start_scan(string dir_path)
{
    init_node(dir_path);
    return recursion_scan_dir_file(*g_node);
}

int clear_scan_result(){
    return dinit_node();
}

/*
 * @breif 节点查找函数
 * @detail 深度优先搜索-递归实现
 * @param dir_absollute_path 目录绝对路径
 * @param pre 父节点暂存指针，首次搜索置nullptr
 * @return 找到返回对应存储结构指针，失败返回nullptr
 */
file_store_st* find_node_by_path(string dir_absolute_path, file_store_st *pre)
{
    if(nullptr == pre)
        pre = g_node;
    if(0 == dir_absolute_path.compare(pre->absolute_path)) return pre;
    file_store_st *tmp;
    list<struct file_store_st>::iterator dir_it;
    for(dir_it = pre->subdir_list.begin(); dir_it != pre->subdir_list.end(); dir_it++){
        if(string::npos != dir_absolute_path.find(dir_it->absolute_path)) { //存在匹配的子串
            tmp = find_node_by_path(dir_absolute_path, &(*dir_it));
            if(nullptr != tmp) return tmp;
        }
    }
    return nullptr;
}

size_t get_dir_filename(const string dir_path, list<string> &file_name_list)
{
    file_store_st *dir_node = find_node_by_path(dir_path, nullptr);
    if(nullptr == dir_node) return FAIL;
    file_name_list.assign(dir_node->file_name_list.begin(), dir_node->file_name_list.end());
    return file_name_list.size();
}

size_t get_dir_dirname(const string dir_path, list<string> &dir_name_list)
{
    file_store_st *dir_node = find_node_by_path(dir_path, nullptr);
    if(nullptr == dir_node) return FAIL;
    dir_name_list.clear();
    list<struct file_store_st>::iterator dir_it;
    for(dir_it = dir_node->subdir_list.begin(); dir_it != dir_node->subdir_list.end(); dir_it++){
        dir_name_list.push_back(dir_it->dir_name);
    }
    return dir_name_list.size();
}

void print_local_file_once(const list<string> &file_name_list)
{
    //TODO need to finish
    return;
}

void print_local_dir_once(const list<string> &dir_name_list)
{
    //TODO need to finish
    return;
}

int write_to_txt_file(const string txt_file_path, const void *data, const string data_type)
{
    //TODO need to finish
    return SUCCESS;
}

int write_to_xlsx_file(const string xlsx_file_path, const void *data, const string data_type)
{
    //TODO need to finish
    int size = FAIL;
    return size;
}

int scan_files_by_extension(const string &file_name_list, const string extension, string &file_name_list_find)
{
    //TODO need to finish
    int size = FAIL;
    return size;
}

int search_file_by_name(const string &file_name_list, const string name, string &file_name_list_find)
{
    //TODO need to finish
    int size = FAIL;
    return size;
}
