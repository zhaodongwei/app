/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: test.cpp
 * date: 2012-12-13
 * desc: test file of zdict
 ***********************************************************/

#include <stdio.h>

#include "zdict.h"

int main() {
	zdict::ZDict dict;
	dict.add(1, 2, 8);
	if (ZDICT_EXIST == dict.has(1, 2)) {
		fprintf(stdout, "have key (%d,%d)\n", 1, 2);
	}
	dict.remove(1, 2);
	if (ZDICT_EXIST != dict.has(1, 2)) {
		fprintf(stdout, "don't have key (%d,%d)\n", 1, 2);
	}
	if (ZDICT_EXIST != dict.has(2, 2)) {
		fprintf(stdout, "don't have key (%d,%d)\n", 2, 2);
	}
	return 0;
};


