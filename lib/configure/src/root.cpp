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
};

int Root::size() {
	return 1;
};

int Root::save(FILE* fs, int depth) {
	if (NULL == fs || depth != 0) {
		throw exception(UNEXPECTED, "NULL fs ptr");
	}
	if (NULL == _child) {
		return 0;
	}
	return _child->save(fs, depth + 1);
};

bool Root::has_key(const char* key) {
	return ConfStruct::has_key(key);
};

bool Root::has_key(const std::string& key) {
	return has_key(key.c_str());
};

bool Root::has_key(int key) {
	return false;
};

ConfStruct* Root::operator[](const char* key) {
	return ConfStruct::operator[](key);	
};

ConfStruct* Root::operator[](int key) {
	throw exception(UNEXPECTED, "no such key: %d", key);
};

int Root::to_int() {
	throw exception(UNEXPECTED, "try to convert root");
};

double Root::to_double() {
	throw exception(UNEXPECTED, "try to convert root");
};

const char* Root::to_cstr() {
	throw exception(UNEXPECTED, "try to convert root");
};

std::string Root::to_string() {
	throw exception(UNEXPECTED, "try to convert root");
};

};
