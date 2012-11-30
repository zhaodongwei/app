/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: zlog.h
 * date: 2012-11-30
 * desc: header of zlog
 ***********************************************************/

#ifndef _ZLOG_H_
#define _ZLOG_H_

#include <stdio.h>

#define ZLOG_SUCC 0
#define ZLOG_ERROR -1

enum LOG_TYPE {
	ZDEBUG = 1,
	ZNOTICE,
	ZWARNNING,
	ZFATAL
};
typedef enum LOG_TYPE zlogtype;

int zlog(zlogtype type, const char* format, ...);

#endif //_ZLOG_H_



