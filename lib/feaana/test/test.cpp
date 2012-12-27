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

int main() {

	feaana::Feaana f;
	f.reg("./data/fea");
	f.filter(2, F_GREATER_THAN, 200);
	f.filter(2, F_GREATER_THAN, 20000);

	return 0;
};

