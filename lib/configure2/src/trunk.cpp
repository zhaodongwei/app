/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: trunk.cpp
 * date: 2012-12-21
 * desc: trunk node type
 ***********************************************************/

#include "trunk.h" 

namespace configure {

Trunk::~Trunk() {
	if (NULL != _brother) {
		delete _brother;
		_brother = NULL;
	}

	if (NULL != _child) {
		delete _child;
		_child = NULL;
	};
};

int Trunk::size() {
	return 1;
};

int Trunk::save(FILE* fs, int depth) {
	if (NULL == fs || depth < 0) {
		throw exception(UNEXPECTED, "NULL fs ptr");
	}
	fprintf(fs, "[");
	int i = depth - 1;
	while (i > 0) {
		fprintf(fs, ".");
		i--;
	}
	fprintf(fs, "%s]\n", _key.c_str());
	if (_child != NULL) {
		_child->save(fs, depth + 1);
	}
	if (_brother != NULL) {
		_brother->save(fs, depth);
	}
	return 0;
};

bool has_key(const char* key) {
	return ConfStruct::has_key(key);
};

bool has_key(int key) {
	return false;
};

Confstruct* operator[](const char* key) {
	return ConfStruct::operator(key);
};

ConfStruct* operator[](int key) {
	throw exception(UNEXPECTED, "no such key %d\n", key);
};

int to_int() {
	throw exception(UNEXPECTED, "try to convert trunk");
};

double to_double() {
	throw exception(UNEXPECTED, "try to convert trunk");
};

const char* to_cstr() {
	throw exception(UNEXPECTED, "try to convert trunk");
};

std::string to_string() {
	throw exception(UNEXPECTED, "try to convert trunk");
};

};

