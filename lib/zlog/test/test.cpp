/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: test.cpp
 * date: 2012-11-30
 * desc: test file of zlog
 ***********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "zlog.h"

int main() {
	zlog_load("./conf/zlog.conf");
	int i = 1;
	while (i--) {
		zlog(ZDEBUG, "debug log");
		zlog(ZNOTICE, "notice log");
		zlog(ZWARNNING, "warnning log");
		zlog(ZFATAL, "fatal log");
	}
    //sleep(1);
	zlog_close();
	return 0;
}
