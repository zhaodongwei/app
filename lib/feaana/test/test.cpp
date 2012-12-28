/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: test.cpp
 * date: 2012-12-27
 * desc: test file for feaana
 ***********************************************************/

#include <stdio.h>

#include "feaana.h"
#include "spliter.h"

int main() {

	feaana::Feaana f;
	f.reg("./data/fea");
	f.filter(2, F_GREATER_THAN<int>, 200);
	f.filter(2, F_LESS_THAN<int>, 20000);

	char line[1024];
	feaana::spliter_split("	hello	world		I'm	here	", "\t");
	fprintf(stdout, "can be split to %d\n", feaana::spliter_size());
	for (int i = 0; i <= feaana::spliter_size(); i++) {
		feaana::spliter_at(i, line);
		fprintf(stdout, "[%d]: [%s]\n", i, line);
	}
	return 0;
};

