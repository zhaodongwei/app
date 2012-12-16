/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: md5app.cpp
 * date: 2012-12-16
 * desc: md5app for os
 ***********************************************************/

#include <stdio.h>

#include "sign.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stdout, "usage: md5 <file or string>\n");
		return -1;
	}
	
	zint64 sign1, sign2;
	if (0 != create_sign(sign1, sign2, argv[1], 0)) {
		create_sign(sign1, sign2, argv[1]);
	}

	unsigned char *p = (unsigned char*)(&sign1);
	for (int i = 0; i < 8; i++) {
		fprintf(stdout, "%02x", *(p + i));
	}
	p = (unsigned char*)(&sign2);
	for (int i = 0; i < 8; i++) {
		fprintf(stdout, "%02x", *(p + i));
	}
	fprintf(stdout, "\n");
	return 0;
}
