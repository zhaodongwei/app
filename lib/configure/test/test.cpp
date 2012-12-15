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
	int i = 2;
	while (i--) {
		fprintf(stdout, "[test]input: %s\n", conf["trunck"]["branch"]["another_branch"]["input"].to_cstr());
		fprintf(stdout, "[test]input: %s\n", conf["trunck"]["branch"][0]["another_branch"]["input"].to_cstr());
		fprintf(stdout, "[test]output: %s\n", conf["trunck"]["branch"][0]["another_branch"]["output"].to_cstr());
		fprintf(stdout, "[test]output: %s\n", conf["trunck"]["branch"][1]["another_branch"]["output"].to_cstr());
		fprintf(stdout, "[test]array: %s\n", conf["trunck"]["branch"][1]["another_branch"]["array"][1][3].to_cstr());
		fprintf(stdout, "[test]branch count: %d\n", conf["trunck"]["branch"].size());
		fprintf(stdout, "[test]array cnount: %d\n", conf["trunck"]["branch"][1]["another_branch"]["array"].size());
		fprintf(stdout, "[test]has key array3: %s\n", conf["trunck"]["branch"][1]["another_branch"]["array"][1].has_key(3)?"t":"f");
		fprintf(stdout, "[test]has key array4: %s\n", conf["trunck"]["branch"][1]["another_branch"]["array"][1].has_key(4)?"t":"f");
		fprintf(stdout, "[test]has key input: %d\n", conf["trunck"]["branch"][0]["another_branch"].has_key("input"));
		fprintf(stdout, "[test]has key inputx: %d\n", conf["trunck"]["branch"][0]["another_branch"].has_key("inputx"));
		sleep(15);
		conf.reload();
	}
	return 0;
}

