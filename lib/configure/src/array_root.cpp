/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: array_root.cpp
 * date: 2012-12-22
 * desc: array root node type
 ***********************************************************/

#include "array_root.h" 

namespace configure {

ArrayRoot::~ArrayRoot() {
	if (NULL != _child) {
		delete _child;
		_child = NULL;
	};

	if (NULL != _brother) {
		delete _brother;
		_brother = NULL;
	}
};

int ArrayRoot::size() {
	int ret = 0;
	ConfStruct* child = _child;
	while (NULL != child) {
		ret++;
		child = child->get_child();
	}
	return ret;
};

int ArrayRoot::save(FILE* fs, int depth) {
	if (NULL == fs || depth < 0) {
		throw exception(UNEXPECTED, "NULL fs ptr");
	}
	fprintf(fs, "%s : [ ", _key.c_str());
	if (_child != NULL) {
		_child->save(fs, depth + 1);
	}
	if (_brother != NULL) {
		_brother->save(fs, depth);
	}
	return 0;
};

bool ArrayRoot::has_key(const char* key) {
	return false;
};

bool ArrayRoot::has_key(const std::string& key) {
	return has_key(key.c_str());
};

bool ArrayRoot::has_key(int key) {
	if (key < 0 || key >= size() - 1) {
		return false;
	}
	return true;
};

ConfStruct* ArrayRoot::operator[](const char* key) {
	throw exception(UNEXPECTED, "no such key %d\n", key);
};

ConfStruct* ArrayRoot::operator[](int key) {
	int iter = 0;
	ConfStruct* child = _child;
	while (NULL != child && iter < key) {
		iter++;
		child = child->get_child();
	}
	if (NULL == child) {
		throw exception(UNEXPECTED, "no such key %d\n", key);
	}
	return child;
};

int ArrayRoot::to_int() {
	throw exception(UNEXPECTED, "try to convert array root");
};

double ArrayRoot::to_double() {
	throw exception(UNEXPECTED, "try to convert array root");
};

const char* ArrayRoot::to_cstr() {
	throw exception(UNEXPECTED, "try to convert array root");
};

std::string ArrayRoot::to_string() {
	throw exception(UNEXPECTED, "try to convert array root");
};

};

