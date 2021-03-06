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
	conf.save(stdout);
	fprintf(stdout, "extract values\n");
	fprintf(stdout, "number: %lf\n", conf["trunk"]["branch"]["number"].to_double());
	fprintf(stdout, "name: %s\n", conf["trunk"]["branch"]["name"].to_cstr());
	fprintf(stdout, "array1: %d\n", conf["trunk"]["branch"]["array1"][1][0].to_int());
	fprintf(stdout, "array1 size: %d\n", conf["trunk"]["branch"]["array1"].size());
	fprintf(stdout, "array1[0] size: %d\n", conf["trunk"]["branch"]["array1"][0].size());
	fprintf(stdout, "array1[1] size: %d\n", conf["trunk"]["branch"]["array1"][1].size());
	fprintf(stdout, "array3 size: %d\n", conf["trunk"]["branch"]["array3"].size());
	fprintf(stdout, "array3[0] size: %d\n", conf["trunk"]["branch"]["array3"][0].size());
	fprintf(stdout, "array3[0] value: %d\n", conf["trunk"]["branch"]["array3"][0].to_int());
	fprintf(stdout, "array3[1] value: %d\n", conf["trunk"]["branch"]["array3"][1].to_int());
	fprintf(stdout, "array3[2] value: %d\n", conf["trunk"]["branch"]["array3"][2].to_int());

	return 0;
}

