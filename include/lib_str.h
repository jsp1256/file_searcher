#ifndef LIB_STR_H
#define LIB_STR_H
//内部私有头文件
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "define_common.h"

/*
 * @brief 模板匹配，支持使用?或*正则匹配，?匹配一个，*匹配0到多个
 * @param str 待匹配的字符串
 * @param pattern 模板串
 * @return 成功返回SUCCESS，失败返回FAIL
 */
int pattern_match(const char *str, const char *pattern);

#ifdef __cplusplus
}
#endif
#endif //LIB_STR_H
