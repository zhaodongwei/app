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
int zlog_load(const char* path);
int zlog_close();

void* _write_log_thread(void* pfile);

class ZLog {

public:
	static ZLog* get_instance();
	static ZLog* get_instance(const char* path);
	int write_log(zlogtype type, const char* info);
	int write_log(const char* info);
	~ZLog();

private:
	ZLog(const char* path);
	ZLog();
	int _write_type(zlogtype type, char* line);
	bool _show(zlogtype type);
	int _create_pool();
	FILE* _fs;
	int _log_level;
	static ZLog* _pzlog;
};

#endif //_ZLOG_H_



