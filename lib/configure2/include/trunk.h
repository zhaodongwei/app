/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: trunk.h
 * date: 2012-12-21
 * desc: trunk node type
 ***********************************************************/

#ifndef _TRUNK_H_
#define _TRUNK_H_

#include <stdio.h>
#include <string>

#include "conf_struct.h"

namespace configure {

class ConfNode;

class Trunk : public ConfStruct {

public:
	Trunk() : ConfStruct(TRUNK) {};
	~Trunk();
	
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

#endif //_TRUNK_H_


