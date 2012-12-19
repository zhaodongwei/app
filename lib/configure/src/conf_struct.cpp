/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_struct.cpp
 * date: 2012-11-19
 * desc: conf struct implement
 ***********************************************************/

#include <math.h>

#include "exception.h"
#include "conf_struct.h"

namespace configure {

ConfStruct::ConfStruct() {
	init();
};

ConfStruct::ConfStruct(const char* key, const char* value) {
	init();
	_key.append(key);
	_value.append(value);
};

ConfStruct::ConfStruct(const std::string& key, const std::string& value) {
	init();
	_key.append(key);
	_value.append(value);
};

ConfStruct::ConfStruct(nodetype node) {
	init();
	_node = node;
};

int ConfStruct::init() {
	_child = NULL;
	_brother = NULL;
	_father = NULL;
	_node = INVALID;
	_shadow = NULL;
};

ConfStruct::~ConfStruct() {
	if (NULL != _child && SHADOW != _node) {
		delete _child;
		_child = NULL;
	}
	if (NULL != _brother && SHADOW != _node) {
		delete _brother;
		_brother = NULL;
	}
	if (NULL != _shadow) {
		delete _shadow;
		_shadow = NULL;
	}
};

bool ConfStruct::add_to_tree() {
	if (NULL == _father) {
		return false;
	}
	ConfStruct* bro = _father->get_last_child();
	if (NULL == bro) {
		_father->set_child(this);
		_elder_brother = NULL;
	}
	else {
		bro->set_brother(this);
		_elder_brother = bro;
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
		throw exception(UNEXPECTED, "no such key: %s", key);
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
		throw exception(UNEXPECTED, "no such key: %s", key);
	}
	return *ret;
};

ConfStruct& ConfStruct::operator[](int key) {
	if (key < 0) {
		throw exception(UNEXPECTED, "no such key: %d", key);
		return *this;
	}
	if (BRANCH == _node) {
		ConfStruct* next = this;
		int iter = 0;
		while (next != NULL && iter < key) {
			if (!_key.compare(next->get_key())) {
				iter++;
			}
			next = next->get_brother();
		}
		if (next != NULL && key == iter) {
			return *next;
		}
		else {
			throw exception(UNEXPECTED, "no such key: %d", key);
			return *this;
		}
	}
	ConfStruct* next = this;
	int iter = 0;
	while (next != NULL && iter < key ) {
		if (SHADOW != _node) {
			next = next->get_child();
		}
		else {
			next = next->get_brother();
		}
		iter++;
	}
	if (iter == key && NULL != next) {
		if (SHADOW != _node) {
			ConfStruct* tmp = next->get_shadow();
			if (NULL != tmp) {
				return *tmp;
			}
			tmp = new ConfStruct(SHADOW);
			next->set_shadow(tmp);
			tmp->set_key(next->get_key());
			tmp->set_value(next->get_value());
			tmp->set_brother(next->get_brother());
			return *tmp;
		}
		else {
			return *next;
		}
	}
	else {
		throw exception(UNEXPECTED, "no such key: %d", key);
		return *this;
	}
};

int ConfStruct::size() {
	int ret = 1;
	if (BRANCH == _node) {
		ConfStruct* bro = _brother;
		while (bro != NULL) {
			if (BRANCH == bro->get_nodetype() && (!_key.compare(bro->get_key()))) {
				ret++;
			}
			bro = bro->get_brother();
		}
	}
	if (ARRAY_ITEM == _node || SHADOW == _node) {
		if (_child != NULL) {
			ConfStruct* tmp = _child;
			while (NULL != tmp) {
				ret++;
				tmp = tmp->get_child();
			}
		}
		else if (_brother != NULL) {
			ConfStruct* tmp = _brother;
			while (NULL != tmp) {
				ret++;
				tmp = tmp->get_brother();
			}
		}
	}
	return ret;
};

bool ConfStruct::has_key(const char* key) {
	ConfStruct* child = _child;
	while (NULL != child) {
		if (!child->get_key().compare(key)) {
			break;
		}
		child = child->get_brother();
	}
	if (NULL == child) {
		return false;
	}
	return true;
};

bool ConfStruct::has_key(const std::string& key) {
	return has_key(key.c_str());
};

bool ConfStruct::has_key(int key) {
	if (key < 0) {
		return false;
	}
	int ret = size();
	if (key < ret) {
		return true;
	}
	return false;
};

int ConfStruct::save(FILE* new_fs, int depth) {
	//need a reconstruction
	return 0;
};

}
