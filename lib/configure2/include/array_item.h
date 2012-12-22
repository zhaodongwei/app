/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: array_item.h
 * date: 2012-12-22
 * desc: array item node type
 ***********************************************************/

#ifndef _ARRAY_ITEM_H_
#define _ARRAY_ITEM_H_

#include <stdio.h>
#include <string>

#include "conf_struct.h"

namespace configure {

class ConfNode;

class ArrayItem : public ConfStruct {

public:
	ArrayItem() : ConfStruct(ARRAY_ITEM) {};
	~ArrayItem();
	
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

#endif //_ARRAY_ITEM_H_


