/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: exception.cpp
 * date: 2012-11-27
 * desc: src file for exception class
 ***********************************************************/

#include <stdio.h>
#include <string>
#include <stdarg.h>

#include "exception.h"

exception::exception() {
	fprintf(stdout, "[FATAL] fatal occurs");
};

exception::exception(const char* info, ...) {
	char buffer[1024];
	va_list args;
	va_start(args, info);
	vsprintf(buffer, info, args);
	va_end(args);
	fprintf(stdout, "%s\n", buffer);
};

exception::exception(fatal_type type, const char* info, ...) {
	_print_type(type);
	char buffer[1024];
	va_list args;
	va_start(args, info);
	vsprintf(buffer, info, args);
	fprintf(stdout, "%s\n", buffer);
};

void exception::_print_type(fatal_type type) {
	switch(type) {
		case NOT_EXIST:
			fprintf(stdout, "[FILE NOT EXIST]");
			break;
		case UNEXPECTED:
			fprintf(stdout, "[UNEXPECTED]");
			break;
		case MISSING:
			fprintf(stdout, "[MISSING]");
			break;
		case DIVIDE:
			fprintf(stdout, "[DIVIDE]");
			break;
		case OUT_OF_MEMORY:
			fprintf(stdout, "[OUT OF MEMORY]");
			break;
		case OUT_OF_RANGE:
			fprintf(stdout, "[OUT OF RANGE]");
			break;
	}
};





