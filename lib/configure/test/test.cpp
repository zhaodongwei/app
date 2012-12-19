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

#include "configure.h"

int main() {
	configure::Configure conf("./conf/configure.conf");
	//conf.save("a");
	fprintf(stdout, "array1: %s\n", conf["trunk"]["branch"]["array1"][1][0].get_key().c_str());
	fprintf(stdout, "array2: %d\n", conf["trunk"]["branch"]["array2"].get_elder_brother()->to_int());
	return 0;
}

