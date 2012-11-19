/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_struct.cpp
 * date: 2012-11-19
 * desc: conf struct implement
 ***********************************************************/

#include "conf_struct.h"

namespace configure {

ConfStruct::ConfStruct() {
	_child = NULL;
	_brother = NULL;
	_father = NULL;
}

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

};
