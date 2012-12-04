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
#include <stdlib.h>
#include <vector>
#include <deque>

#include "exception.h"
#include "configure.h"
#include "zlog.h"

ZLog* ZLog::_pzlog;
std::vector<char*> _pool;
std::deque<char*> _task;
char* pmem;
int _max_task_num;
int _max_task_length;
pthread_cond_t qready;
pthread_mutex_t qlock;
pthread_mutex_t task_lock;

int zlog(zlogtype type, const char* format, ...) {
	va_list va;
	va_start(va, format);
	vsnprintf(pmem, _max_task_length, format, va);
	ZLog* ins = ZLog::get_instance();
	ins->write_log(type, pmem);
	return ZLOG_SUCC;
};

int zlog_load(const char* path) {
	ZLog::get_instance(path);
	zlog(ZNOTICE, "-------------open log--------------");
	return ZLOG_SUCC;
};

int zlog_close() {
	usleep(10);
	pthread_mutex_lock(&qlock);
	pthread_mutex_lock(&task_lock);
	pthread_cond_destroy(&qready);
	pthread_mutex_destroy(&qlock);
	pthread_mutex_destroy(&task_lock);

	ZLog* ins = ZLog::get_instance();
	if (NULL != ins) {
		delete ins;
	}
	if (NULL != pmem) {
		delete pmem;
	}
	return ZLOG_SUCC;
};

void* _write_log_thread(void* pfile) {
	FILE* _fs_thread = (FILE*)pfile;
	for(;;) {
		pthread_mutex_lock(&qlock);
		while (_task.size() == 0) {
			pthread_cond_wait(&qready, &qlock);
		}
		pthread_mutex_lock(&task_lock);
		char* tmp;
		tmp = _task.front();
		_task.pop_front();
		pthread_mutex_unlock(&task_lock);
		fprintf(_fs_thread, "%s\n", tmp);
		_pool.push_back(tmp);
		pthread_mutex_unlock(&qlock);
	}
	pthread_exit(ZLOG_SUCC);
};

ZLog::ZLog() {
	_log_level = 0;
	_fs = stdout;
	_max_task_length = 1024;
	_max_task_num = 100;
	_create_pool();
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
		_log_level = 7;
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

	if (conf.has_key("buffer_log_length")) {
		_max_task_length = conf["buffer_log_length"].to_int();
	}
	else {
		_max_task_length = 1024;
	}

	if (conf.has_key("buffer_log_num")) {
		_max_task_num = conf["buffer_log_num"].to_int(); 
	}
	else {
		_max_task_num = 100;
	}
	
	_create_pool();
	
};

int ZLog::_create_pool() {
	pmem = (char*)malloc((_max_task_num + 1) * _max_task_length);
	if (NULL == pmem) {
		throw exception(UNEXPECTED, "allocate mem for log fail");
	}
	_pool.reserve(_max_task_num + 1);

	int i = 0;
	while (i++ < _max_task_num) {
		_pool.push_back(pmem + i * _max_task_length);
	}
	pthread_cond_init(&qready, NULL);
	pthread_mutex_init(&qlock, NULL);
	pthread_mutex_init(&task_lock, NULL);

	pthread_t pid;
	int ret = pthread_create(&pid, NULL, _write_log_thread, (void*)_fs);
	if (0 != ret) {
		throw exception(UNEXPECTED, "init log thread fail");
	}
	
	return ZLOG_SUCC;
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
	sprintf(line + strlen(line), " * %d-%02d-%02d",  tmp->tm_year+1900, tmp->tm_mon + 1, tmp->tm_mday);
	sprintf(line + strlen(line), " %02d:%02d:%02d * ", tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
	return ZLOG_SUCC;
};

int ZLog::write_log(zlogtype type, const char* info) {
	if (!_show(type)) {
		return ZLOG_SUCC;
	}
	char* tmp;
	pthread_mutex_lock(&qlock);
	if (0 == _pool.size()) {
		tmp = NULL;
	}
	else {
		tmp = _pool.back();
		_pool.pop_back();
		if (NULL == tmp) {
			fprintf(stdout, "WARNNING ** NULL ptr\n");
		}
		else {
			_write_type(type, tmp);
			snprintf(tmp + strlen(tmp), _max_task_length - strlen(tmp), "%s", info);
			pthread_mutex_lock(&task_lock);
			_task.push_back(tmp);
		}
		pthread_mutex_unlock(&task_lock);
	}
	pthread_mutex_unlock(&qlock);
	if (NULL == tmp) {
		fprintf(stdout, "WARNNING ** no buffer for log\n");
		return ZLOG_ERROR;
	}
	pthread_cond_signal(&qready);

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
