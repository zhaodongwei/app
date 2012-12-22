/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: item.cpp
 * date: 2012-12-22
 * desc: item node type
 ***********************************************************/

#include "item.h" 

namespace configure {

Item::~Item() {
	if (NULL != _brother) {
		delete _brother;
		_brother = NULL;
	}
};

int Item::size() {
	return 1;
};

int Item::save(FILE* fs, int depth) {
	if (NULL == fs || depth < 0) {
		throw exception(UNEXPECTED, "NULL fs ptr");
	}
	fprintf(fs, "%s : %s\n", _key.c_str(), _value.c_str());
	if (NULL != _brother) {
		_brother->save(fs, depth);
	}
	return 0;
};

bool Item::has_key(const char* key) {
	return false;
};

bool Item::has_key(const std::string& key) {
	return false;
};

bool Item::has_key(int key) {
	return false;
};

ConfStruct* Item::operator[](const char* key) {
	throw exception(UNEXPECTED, "no such key %d\n", key);
};

ConfStruct* Item::operator[](int key) {
	throw exception(UNEXPECTED, "no such key %d\n", key);
};

int Item::to_int() {
	return (int)_parse_number();
};

double Item::to_double() {
	return _parse_number();
};

const char* Item::to_cstr() {
	return _value.c_str();	
};

std::string Item::to_string() {
	return _value;
};

};

