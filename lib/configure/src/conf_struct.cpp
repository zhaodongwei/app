/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_struct.cpp
 * date: 2012-11-19
 * desc: conf struct implement
 ***********************************************************/

#include <math.h>

#include "conf_struct.h"

namespace configure {

ConfStruct::ConfStruct() {
	_child = NULL;
	_brother = NULL;
	_father = NULL;
};

ConfStruct::ConfStruct(const char* key, const char* value) {
	_key.append(key);
	_value.append(value);
};

ConfStruct::ConfStruct(const std::string& key, const std::string& value) {
	_key.append(key);
	_value.append(value);
};

ConfStruct::~ConfStruct() {
	fprintf(stdout, "[delete]key: %s\n", _key.c_str());
	if (NULL != _child) {
		delete _child;
		_child = NULL;
	}
	if (NULL != _brother) {
		delete _brother;
		_brother = NULL;
	}
};

bool ConfStruct::add_to_tree() {
	if (NULL == _father) {
		return false;
	}
	ConfStruct* bro = _father->get_last_child();
	if (NULL == bro) {
		_father->set_child(this);
	}
	else {
		bro->set_brother(this);
	}
	return true;
};

ConfStruct* ConfStruct::get_last_child() const {
	ConfStruct* ret = _child;
	if (NULL == ret) {
		return NULL;
	}

	while (ret->get_brother() != NULL) {
		ret = ret->get_brother();
	}
	return ret;
};

double ConfStruct::_get_number(std::string& str, int& iter) {
	if (iter >= str.size() || iter < 0) {
		return 0.0;
	}
	int label = 1;
	if (str[iter] == '-') {
		label = -1;
		iter++;
	}
	else if(str[iter] == '+') {
		iter++;
	}

	double ret = 0;
	while (iter < str.size() && _is_number(str[iter])) {
		ret = ret * 10 + (int)(str[iter] - '0');
		iter++;
	}
	if (iter < str.size() && str[iter] == '.') {
		iter++;
	}
	else {
		return ret * label;
	}

	double decimal = 0.1;
	while (iter < str.size() && _is_number(str[iter])) {
		ret += (double)(str[iter] - '0') * decimal;
		decimal *= 0.1;
		iter++;
	}
	return ret * label;
};

double ConfStruct::_parse_number() {
	if (_value.size() == 0) {
		fprintf(stderr, "try to extract null value\n");
		return 0;
	}
	int iter = 0;
	double ret = _get_number(_value, iter);
	if (iter < _value.size() 
		&& (_value[iter] == 'E' || _value[iter] == 'e')) {
		double base = ret;
		double exp = _get_number(_value, ++iter);
		if (iter == _value.size()) {
			ret = base * pow(10, exp);
		}
		else {
			ret = 0.0;
		}
	}
	else if (iter < _value.size()) {
		ret = 0.0;
	}
	
	return ret;
};

int ConfStruct::to_int() {
	return (int)_parse_number();
};

double ConfStruct::to_double() {
	return (double)_parse_number();
};

std::string ConfStruct::to_string() {
	return _value;
};

const char* ConfStruct::to_cstr() {
	return _value.c_str();
};

ConfStruct& ConfStruct::operator[](const char* key) {
	ConfStruct* child = _child;
	if (NULL == child) {
		fprintf(stderr, "[no such key] %s\n", key);
	}
	ConfStruct* ret = NULL;
	while (NULL != child) {
		if (!child->get_key().compare(key)) {
			ret = child;
			break;
		}
		child = child->get_brother();
	}
	if (NULL == child) {
		fprintf(stderr, "[no such key] %s\n", key);
	}
	return *ret;
};

ConfStruct& ConfStruct::operator[](int key) {
	if (key < 0) {
		fprintf(stderr, "[conf]invalid key");
		return *this;
	}
	if (key == 0) {
		return *this;
	}
	ConfStruct* next = this;
	int iter = 0;
	while (next != NULL && iter < key ) {
		if (_child != NULL) {
			next = next->get_child();
		}
		else {
			next = next->get_brother();
		}
		iter++;
	}
	if (iter == key) {
		return *next;
	}
	else {
		fprintf(stderr, "[conf]invalid key");
		return *this;
	}
};

}
