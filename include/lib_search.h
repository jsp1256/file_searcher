#include <cstdio>
#include <string>
#include <list>

/*
 * @brief 获取目录下所有的文件名，不获取目录名
 * @details 实现时如果使用了系统依赖的函数需要使用相关的宏来区分
 * @param dir_path 目录路径
 * @param file_name_list 传入用于存放文件名的链表
 * @return 成功返回列表中文件数量个数，失败返回-1
 */
int get_dir_filename(const std::string dir_path, std::list<std::string> &file_name_list);

/*
 * @brief 获取目录下所有的目录名，不获取文件名
 * @details 实现时如果使用了系统依赖的函数需要使用相关的宏来区分
 * @param dir_path 目录路径
 * @param file_name_list 传入用于存放目录名的链表
 * @return 成功返回列表中数量个数，失败返回-1
 */
int get_dir_dirname(const std::string dir_path, std::list<std::string> &dir_name_list);

/*
 * @brief 依次打印列表中的文件名,不递归子目录
 * @param file_name_list 传入用于存放文件名的链表
 */
void print_local_file_once(const std::list<std::string> &file_name_list);

/*
 * @brief 依次打印列表中的目录名,不递归子目录
 * @param dir_name_list 传入用于存放目录名的链表
 */
void print_local_dir_once(const std::list<std::string> &dir_name_list);
