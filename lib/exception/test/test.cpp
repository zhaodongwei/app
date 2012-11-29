/***********************************************************
 * copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: test.h
 * date: 2012-11-27
 * desc: test file for exception class
 ***********************************************************/

#include <stdio.h>
#include "exception.h"

int main() {
	fprintf(stdout, "before throwing an exception\n");
	throw exception(NOT_EXIST, "This is an exception");
	fprintf(stdout, "after throwing an exception\n");
	return 0;
}

