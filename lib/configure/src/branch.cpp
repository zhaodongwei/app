/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: branch.cpp
 * date: 2012-12-22
 * desc: branch node type
 ***********************************************************/

#include "branch.h" 

namespace configure {

Branch::~Branch() {
};

int Branch::size() {
	ConfStruct* bro = get_brother();
	int ret = 1;
	while (bro != NULL) {
		if ((!bro->get_key().compare(_key)) && BRANCH == bro->get_nodetype()) {
			ret++;
		}
		bro = bro->get_brother();
	}
	return ret;
};

int Branch::save(FILE* fs, int depth) {
	if (NULL == fs || depth < 0) {
		throw exception(UNEXPECTED, "NULL fs ptr");
	}
	fprintf(fs, "[");
	int i = depth - 1;
	while (i > 0) {
		fprintf(fs, ".");
		i--;
	}
	fprintf(fs, "@%s]\n", _key.c_str());
	if (_child != NULL) {
		_child->save(fs, depth + 1);
	}
	if (_brother != NULL) {
		_brother->save(fs, depth);
	}
	return 0;
};

bool Branch::has_key(const char* key) {
	return ConfStruct::has_key(key);
};

bool Branch::has_key(const std::string& key) {
	return has_key(key.c_str());
};

bool Branch::has_key(int key) {
	if (key < 0 || key >= size()) {
		return false;
	}
	return true;
};

ConfStruct* Branch::operator[](const char* key) {
	return ConfStruct::operator[](key);
};

ConfStruct* Branch::operator[](int key) {
	ConfStruct* bro = this;
	int iter = 0;
	while (bro != NULL && iter < key) {
		if ((!bro->get_key().compare(_key)) && BRANCH == bro->get_nodetype()) {
			iter++;
		}
		bro = bro->get_brother();
	}
	if (NULL == bro) {
		throw exception(UNEXPECTED, "try to convert branch");
	}
	return bro;
};

int Branch::to_int() {
	throw exception(UNEXPECTED, "try to convert branch");
};

double Branch::to_double() {
	throw exception(UNEXPECTED, "try to convert branch");
};

const char* Branch::to_cstr() {
	throw exception(UNEXPECTED, "try to convert branch");
};

std::string Branch::to_string() {
	throw exception(UNEXPECTED, "try to convert branch");
};

};

