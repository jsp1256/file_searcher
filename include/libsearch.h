#ifndef LIB_SEARCH_H
#define LIB_SEARCH_H
#include <cstdio>
#include <string>
#include <list>

#include "define_common.h"

/*
 * @brief 扫描开始执行的函数
 * @param  dir_node 存储节点
 * @return 成功返回SUCCESS，失败返回对应的错误代码
 */
int start_scan(std::string dir_path);

/*
 * @brief 扫描结果清理函数，将清理扫描的一切结果
 * @return 成功返回SUCCESS，失败返回对应的错误代码
 */
int clear_scan_result();
/*
 * @brief 获取目录下所有的文件名，不获取目录名
 * @param dir_path 目录路径
 * @param file_name_list 传入用于存放文件名的链表
 * @return 成功返回列表中文件数量个数，失败返回FAIL
 */
size_t get_dir_filename(const std::string dir_path, std::list<std::string> &file_name_list);

/*
 * @brief 获取目录下所有的目录名，不获取文件名
 * @param dir_path 目录路径
 * @param file_name_list 传入用于存放目录名的链表
 * @return 成功返回列表中数量个数，失败返回FAIL
 */
size_t get_dir_dirname(const std::string dir_path, std::list<std::string> &dir_name_list);

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

/*
 * @brief 将数据写入txt文件中保存
 * @param txt_file_path txt文件保存路径
 * @param data 数据
 * @param data_type 数据类型
 * @return 返回SUCCESS表示成功，FAIL表示失败
 */
int write_to_txt_file(const std::string txt_file_path, const void *data, const std::string data_type);

/*
 * @brief 将数据写入xlsx文件中保存
 * @param xlsx_file_path xlsx文件保存路径
 * @param data 数据
 * @param data_type 数据类型
 * @return 返回SUCCESS表示成功，FAIL表示失败
 */
int write_to_xlsx_file(const std::string xlsx_file_path, const void *data, const std::string data_type);

/*
 * @brief 根据后缀名查找文件，例如：exe查早后缀为.exe的文件
 * @param file_name_list 待查找的文件列表
 * @param extension 后缀名，例如："exe"
 * @param file_name_list_find 查找到的文件存储列表
 * @return 成功返回查找到的文件个数，失败返回-1
 */
size_t scan_files_by_extension(const std::list<std::string> &file_name_list, const std::string extension, std::list<std::string> &file_name_list_find);

/*
 * @brief 根据文件名查找文件，支持使用?或*正则匹配，?匹配一个，*匹配0到多个
 * @param file_name_list 待查找的文件列表
 * @param name 文件名
 * @param file_name_list_find 查找到的文件存储列表
 * @return 成功返回查找到的文件个数，失败返回-1
 */
size_t search_file_by_name(const std::list<std::string> &file_name_list, const std::string name, std::list<std::string> &file_name_list_find);
#endif //LIB_SEARCH_H
