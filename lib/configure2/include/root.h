/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: root.h
 * date: 2012-12-21
 * desc: root conf type
 ***********************************************************/

#ifndef _ROOT_H_
#define _ROOT_H_

#include <string>

#include "conf_struct.h"
#include "exception.h"

namespace configure {

class ConfNode;

class Root : public ConfStruct {

public:
	Root() : ConfStruct(ROOT) {};
	~Root();
	
	int size();	
	int save(FILE* fs, int depth);
	bool has_key(const char* key);
	bool has_key(const std::string& key);
	bool has_key(int key);

	ConfStruct* operator[](const char* key);
	ConfStruct* operator[](int key);
	int to_int();
	double to_double();
	const char* to_cstr();
	std::string to_string();

};

};

#endif //_ROOT_H_
