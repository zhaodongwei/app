/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: exception.cpp
 * date: 2012-11-27
 * desc: src file for exception class
 ***********************************************************/

#include <stdio.h>
#include "exception.h"

exception::exception(const char* info) {
	fprintf(stdout, "%s\n", info);
};





