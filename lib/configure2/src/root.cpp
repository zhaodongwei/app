/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: root.cpp
 * date: 2012-12-21
 * desc: root node type
 ***********************************************************/

#include "root.h"

namespace configure {

Root::~Root() {
	if (_child != NULL) {
		delete _child;
		_child = NULL;
	}
};

int Root::size() {
	return 1;
};

int Root::save(FILE* fs, int depth) {
	if (NULL == fs || depth != 0) {
		throw exception(NEXPECTED, "NULL fs ptr");
	}
	if (NULL == _child) {
		return 0;
	}
	return _child->save(fs, depth + 1);
};

bool has_key(const char* key) {
	return ConfStruct::has_key(key);
};

bool has_key(int key) {
	return false;
};

ConfStruct* operator[](const char* key) {
	return ConfStruct::operator[](key);	
};

ConfStruct* operator[int key] {
	throw exception(UNEXCEPTED, "no such key: %d", key);
};

int to_int() {
	throw exception(UNEXPECTED, "try to convert root");
};

double to_double() {
	throw exception(UNEXPECTED, "try to convert root");
};

const char* to_cstr() {
	throw exception(UNEXPECTED, "try to convert root");
};

std::string to_string() {
	throw exception(UNEXPECTED, "try to convert root");
};

};
