/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_node.h
 * date: 2012-12-22
 * desc: conf node wrapper
 ***********************************************************/

#include "conf_node.h"

namespace configure {

ConfNode::ConfNode(nodetype node) {
	_conf_ins = _conf_factory(node);
	_conf_ins->set_wrapper(this);
};

ConfNode::~ConfNode() {
	if (NULL != _conf_ins && ROOT == _conf_ins->get_nodetype()) {
		delete _conf_ins;
		_conf_ins = NULL;
	}
};

ConfStruct* ConfNode::_conf_factory(nodetype node) {
	ConfStruct* ret = NULL;
	switch (node) {
		case ROOT:
			ret = new Root();
			break;
		case TRUNK:
			ret = new Trunk();
			break;
		case BRANCH:
			ret = new Branch();
			break;
		case ITEM:
			ret = new Item();
			break;
		case ARRAY_ROOT:
			ret = new ArrayRoot();
			break;
		case ARRAY_ITEM:
			ret = new ArrayItem();
			break;
		default:
			ret = new Item();
	};
	return ret;
};

ConfStruct* ConfNode::get_ins() {
	return _conf_ins;
};

ConfNode* ConfNode::get_child() {
	ConfStruct* ret = _conf_ins->get_child();
	return ret->get_wrapper();
};

int ConfNode::set_value(const char* value) {
	_conf_ins->set_value(value);
	return 0;
};

int ConfNode::set_key(const char* key) {
	_conf_ins->set_key(key);
	return 0;
};

std::string ConfNode::get_key() {
	return _conf_ins->get_key();
};

std::string ConfNode::get_value() {
	return _conf_ins->get_value();
};

int ConfNode::set_father(ConfNode* father) {
	_conf_ins->set_father(father->get_ins());
	return 0;
};

int ConfNode::add_to_tree() {
	return _conf_ins->add_to_tree();
};

ConfNode& ConfNode::operator[](const char* key) {
	ConfStruct* ret = (*_conf_ins)[key];
	return *(ret->get_wrapper());
};

ConfNode& ConfNode::operator[](const std::string& key) {
	return operator[](key.c_str());
};

ConfNode& ConfNode::operator[](int key) {
	ConfStruct* ret = (*_conf_ins)[key];
	return *(ret->get_wrapper());
};

bool ConfNode::has_key(const char* key) {
	return _conf_ins->has_key(key);
};

bool ConfNode::has_key(const std::string& key) {
	return _conf_ins->has_key(key.c_str());
};

bool ConfNode::has_key(int key) {
	return _conf_ins->has_key(key);
};

int ConfNode::size() {
	return _conf_ins->size();
};

int ConfNode::save(FILE* fs, int depth) {
	if (ROOT == _conf_ins->get_nodetype()) {
		_conf_ins->save(fs, depth);
	}
	return 0;
};

int ConfNode::to_int() {
	return _conf_ins->to_int();
};

double ConfNode::to_double() {
	return _conf_ins->to_double();
};

const char* ConfNode::to_cstr() {
	return _conf_ins->to_cstr();
};

std::string ConfNode::to_string() {
	return _conf_ins->to_string();
};

};
