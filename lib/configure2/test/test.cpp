/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: test.cpp
 * date: 2012-11-19
 * desc: test of configure
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "configure.h"

int main() {
	configure::Configure conf(std::string("./conf/configure.conf"));
	//conf.save("a");
	fprintf(stdout, "int: %lf\n", conf["trunk"]["branch"]["int"].to_double());
	fprintf(stdout, "array1: %d\n", conf["trunk"]["branch"]["array1"][1][0].to_int());
	fprintf(stdout, "array1 size: %d\n", conf["trunk"]["branch"]["array1"].size());
	fprintf(stdout, "array1[0] size: %d\n", conf["trunk"]["branch"]["array1"][0].size());
	fprintf(stdout, "array1[1] size: %d\n", conf["trunk"]["branch"]["array1"][1].size());
	return 0;
}

