#include "lib_str.h"

int pattern_match(const char *str, const char *pattern)
{
    size_t str_num, pattern_num;
    size_t str_size = strlen(str);
    size_t pattern_size = strlen(pattern);

	//特殊处理，模板串或字符串为空。
	if(!pattern_size || !str_size)
        return -1;

	//特殊处理*在最后的情况
    if(pattern[pattern_size - 1] == '*') {
        pattern_size--;
    }

	for (str_num = pattern_num = 0;
		str_num < str_size && pattern_num < pattern_size ;str_num++) {
		if (pattern[pattern_num] == '?') {
			pattern_num++;
			continue;
		}
		if (pattern[pattern_num] == '*') {
            pattern_num++;
            str_num--;
            continue;
		}
		if (str[str_num] != pattern[pattern_num]) {
            if(pattern_num && pattern[pattern_num - 1] == '*') {
                continue;
            }
            if (str_num && pattern_num) str_num--;
			pattern_num = 0;
		} else {
			pattern_num++;
		}
	}

	if (pattern_num == pattern_size) {
        return 0;
	}
    return -1;
}
