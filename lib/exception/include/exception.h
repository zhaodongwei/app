/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: exception.h
 * date: 2012-11-27
 * desc: head file for exception class
 ***********************************************************/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#define EXCEPTION_SUCC 0
#define EXCEPTION_ERROR -1

enum FATAL_TYPE {
	NOT_EXIST,
	UNEXPECTED,
	MISSING,
	DIVIDE,
	OUT_OF_MEMORY,
	OUT_OF_RANGE
};

typedef enum FATAL_TYPE fatal_type;

class exception {

public:
	exception();
	exception(const char* info, ...);
	exception(fatal_type type, const char* info, ...);
	~exception(){};

private:
	void _print_type(fatal_type type);
};

#endif// _EXCEPTION_H_



