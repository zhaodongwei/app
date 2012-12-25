/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: item.h
 * date: 2012-12-22
 * desc: item node type
 ***********************************************************/

#ifndef _ITEM_H_
#define _iTEM_H_

#include <stdio.h>
#include <string>

#include "conf_struct.h"

namespace configure {

class ConfNode;

class Item : public ConfStruct {

public:
	Item() : ConfStruct(ITEM) {};
	~Item();
	
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

#endif //_ITEM_H_


