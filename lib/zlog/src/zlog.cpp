/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: zlog.cpp
 * date: 2012-11-30
 * desc: src file of zlog
 ***********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "exception.h"
#include "configure.h"
#include "zlog.h"

ZLog* ZLog::_pzlog;

int zlog(zlogtype type, const char* format, ...) {
	char line[1024];
	va_list va;
	va_start(va, format);
	vsprintf(line, format, va);
	ZLog* ins = ZLog::get_instance();
	ins->write_log(type, line);
	return ZLOG_SUCC;
};

int zlog_load(const char* path) {
	ZLog::get_instance(path);
	return ZLOG_SUCC;
};

int zlog_close() {
	ZLog* ins = ZLog::get_instance();
	if (NULL != ins) {
		delete ins;
	}
	return ZLOG_SUCC;
};

void* ZLog::_write_log_thread(void* pchar) {
	FILE* _fs_thread = (FILE*)(((void**)pchar)[0]);
	char* info = (char*)(((void**)pchar)[1]);
	//fprintf(stdout, "[thread]%s\n", info);
	fprintf(_fs_thread, "[thread]%s\n", info);
	pthread_exit(ZLOG_SUCC);
};

ZLog::ZLog() {
	_log_level = 0;
	_fs = stdout;
};

ZLog::ZLog(const char* path) {
	if (NULL == path) {
		throw exception(UNEXPECTED, "invalid conf file");
	}
	configure::Configure conf(path);
	if (conf.has_key("log_level")) {
		_log_level = conf["log_level"].to_int();	
	}
	else {
		_log_level = 0;
	}
	
	if (conf.has_key("output") && !strcmp(conf["output"].to_cstr(), "stdout")) {
		_fs = stdout;
	}
	else if (conf.has_key("output") && !strcmp(conf["output"].to_cstr(), "stderr")){
		_fs = stderr;
	}
	else if (conf.has_key("output")) {
		_fs = fopen(conf["output"].to_cstr(), "a+");
		if (NULL == _fs) {
			throw exception(NOT_EXIST, "open %s fail", conf["output"].to_cstr());
		}
	}
	else {
		_fs = stdout;
	}
};

ZLog* ZLog::get_instance(const char* path) {
	if (NULL == _pzlog) {
		_pzlog = new ZLog(path);
	}
	return _pzlog;
};

ZLog::~ZLog() {
	if (NULL != _fs && stdout != _fs && stderr != _fs) {
		fclose(_fs);
	}
	_fs = NULL;
	_pzlog = NULL;
}

ZLog* ZLog::get_instance() {
	if (NULL == _pzlog) {
		_pzlog = new ZLog();
	}
	return _pzlog;
};

int ZLog::_write_type(zlogtype type, char* line) {
	switch(type) {
		case ZDEBUG:
			strcpy(line, "[DEBUG]");
			break;
		case ZNOTICE:
			strcpy(line, "[NOTICE]");
			break;
		case ZWARNNING:
			strcpy(line, "[WARNNING]");
			break;
		case ZFATAL:
			strcpy(line, "[FATAL]");
			break;
	};
	time_t now;
	tm* tmp;
	time(&now);
	tmp = localtime(&now);	
	char today[1024];
	sprintf(today, "%d-%02d-%02d",  tmp->tm_year+1900, tmp->tm_mon + 1, tmp->tm_mday);
	sprintf(today + strlen(today), " %02d:%02d:%02d", tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
	sprintf(line + strlen(line), " * %s * ", today);
	return ZLOG_SUCC;
};

char gline[1024];
int ZLog::write_log(zlogtype type, const char* info) {
	if (!_show(type)) {
		return ZLOG_SUCC;
	}
	_write_type(type, gline);
	sprintf(gline + strlen(gline), "%s", info);
	fprintf(_fs, "%s\n", gline);
	
	void* pchar[2];
	pchar[0] = (void*)_fs;
	pchar[1] = (void*)gline;
	pthread_t pid;
	pthread_create(&pid, NULL, _write_log_thread, (void*)pchar);
	usleep(1);
	return ZLOG_SUCC;
};

int ZLog::write_log(const char* info) {
	return write_log(ZNOTICE, info); 
};

bool ZLog::_show(zlogtype type) {
	bool ret = false;
	int i = (int)ZFATAL - (int)type;
	if (_log_level & (1 << i)) {
		ret = true;
	}
	return ret;
};
