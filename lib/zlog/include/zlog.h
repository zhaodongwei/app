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
#include <vector>
#include <deque>
#include <pthread.h>
#include <unistd.h>

#define ZLOG_SUCC 0
#define ZLOG_ERROR -1

enum LOG_TYPE {
	ZDEBUG = 1,
	ZNOTICE,
	ZWARNNING,
	ZFATAL
};
typedef enum LOG_TYPE zlogtype;

static std::vector<char*> _pool;
static std::deque<char*> _task;
static char* pmem;
static pthread_t tid;
static int _max_task_num;
static int _max_task_length;
static pthread_cond_t qready;
static pthread_mutex_t qlock;
static pthread_mutex_t task_lock;

int zlog(zlogtype type, const char* format, ...);
int zlog_load(const char* path);
int zlog_close();

void* _write_log_thread(void* pfile);
void close_log(void* pfile);

class ZLog {

public:
	static ZLog* get_instance();
	static ZLog* get_instance(const char* path);
	int write_log(zlogtype type, const char* info);
	int write_log(const char* info);
	bool show(zlogtype type);
	~ZLog();

private:
	ZLog(const char* path);
	ZLog();
	int _write_type(zlogtype type, char* line);
	int _create_pool();
	FILE* _fs;
	int _log_level;
	static ZLog* _pzlog;
	class ZGarbage {
	public:
		~ZGarbage() {
			if (NULL != ZLog::_pzlog) {
				delete _pzlog;
				_pzlog = NULL;
			}
            int cnt = 10;
            while (_task.size() != 0 && cnt--) {
                usleep(10);
            }
		}
	};
	static ZGarbage _z_garbage;
};

#endif //_ZLOG_H_



