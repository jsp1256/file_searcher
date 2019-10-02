#ifndef DEFINE_COMMON_H
#define DEFINE_COMMON_H

typedef unsigned char node_status;
typedef unsigned char func_status;

const node_status SCAN_UNFINISHED = 0;	//此节点尚未扫描
const node_status SCAN_FINISHED = 1;	//此节点扫描完毕
const node_status NEED_UPDATE = 2;		//此节点需要更新

const func_status FAIL = 255;
const func_status SUCCESS = 0;
const func_status PARAM_IS_NULL = 1;	//参数为空;
const func_status PARAM_NOT_DIR = 2;	//参数不为目录
const func_status OPEN_DIR_FAIL = 3;
const func_status HANDLE_IS_NULL = 4;
const func_status NODE_IS_EXSIT = 5;
const func_status NODE_NOT_EXSIT = 6;

#endif //DEFINE_COMMON_H
