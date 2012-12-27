/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: array_item.cpp
 * date: 2012-12-22
 * desc: array item node type
 ***********************************************************/

#include "array_item.h" 

namespace configure {

ArrayItem::~ArrayItem() {
};

int ArrayItem::size() {
	int ret = 0;
	ConfStruct* brother = this;
	while (NULL != brother) {
		ret++;
		brother = brother->get_brother();
	}
	return ret;
};

int ArrayItem::save(FILE* fs, int depth) {
	if (NULL == fs || depth < 0) {
		throw exception(UNEXPECTED, "NULL fs ptr");
	}
	fprintf(fs, " %s ", _value.c_str());
	if (NULL == _brother) {
		ConfStruct* grandson = _father->get_child();
		grandson = grandson->get_child();
		if (NULL == grandson) {
			fprintf(fs, " ]\n");
		}
		else {
			fprintf(fs, "\n");
		}
	}
	else {
		_brother->save(fs, depth);
	}

	if (_child != NULL) {
		_child->save(fs, depth + 1);
	}
	return 0;
};

bool ArrayItem::has_key(const char* key) {
	return false;
};

bool ArrayItem::has_key(const std::string& key) {
	return has_key(key.c_str());
};

bool ArrayItem::has_key(int key) {
	if (key < 0 || key >= size()) {
		return false;
	}
	return true;
};

ConfStruct* ArrayItem::operator[](const char* key) {
	throw exception(UNEXPECTED, "no such key %d\n", key);
};

ConfStruct* ArrayItem::operator[](int key) {
	int iter = 0;
	ConfStruct* brother = this;
	while (NULL != brother && iter < key) {
		iter++;
		brother = brother->get_brother();
	}
	if (NULL == brother) {
		throw exception(UNEXPECTED, "no such key %d\n", key);
	}
	return brother;
};

int ArrayItem::to_int() {
	return (int)(_parse_number());
};

double ArrayItem::to_double() {
	return _parse_number();
};

const char* ArrayItem::to_cstr() {
	return _value.c_str();
};

std::string ArrayItem::to_string() {
	return _value;
};

};

