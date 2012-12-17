/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: test.cpp
 * date: 2012-12-17
 * desc: test file of wordseg class
 ***********************************************************/

#include <stdio.h>

#include "wordseg.h"

int main() {
	wordseg::WordSeg wseg("./data/dict");
	wseg.seg("我还需要加倍努力向前辈学习");
	unsigned int num = wseg.size();
	fprintf(stdout, "size of seg: %d\n", num);
	char tmp[1024];
	for (int i = 0; i <= num; i++) {
		wseg.get(i, tmp, 1024);
		fprintf(stdout, "[%d]: %s\n", i, tmp);
	}
	return 0;
};
