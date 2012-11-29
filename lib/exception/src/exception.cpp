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

exception::exception(fatal_type type, const char* info) {
	_print_type(type);
	fprintf(stdout, "%s\n", info);
};

void exception::_print_type(fatal_type type) {
	switch(type) {
		case NOT_EXIST:
			fprintf(stdout, "[FILE NOT EXIST]");
			break;
		case LOGIC:
			fprintf(stdout, "[LOGIC]");
			break;
		case UNEXPECTED:
			fprintf(stdout, "[UNEXPECTED]");
			break;
		case EXPECTED:
			fprintf(stdout, "[EXPECTED]");
			break;
		case NUMBERIC:
			fprintf(stdout, "[NUMBERIC]");
			break;
		case RUNTIME:
			fprintf(stdout, "[RUN TIME]");
			break;
		case RANGE:
			fprintf(stdout, "[OUT OF RANGE]");
			break;
	}
};





