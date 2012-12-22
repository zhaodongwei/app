/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_node.h
 * date: 2012-12-22
 * desc: conf node wrapper
 ***********************************************************/

#ifndef _CONF_NODE_H_
#define _CONF_NODE_H_

#include <stdio.h>
#include <string>
#include <vector>

#include "conf_struct.h"
#include "conf_nodetype.h"
#include "root.h"
#include "trunk.h"
#include "branch.h"
#include "array_root.h"
#include "array_item.h"
#include "item.h"

namespace configure {

class ConfNode {

public:
	ConfNode(nodetype node);
	~ConfNode();

	int set_value(const char* value);
	int set_key(const char* key);
	std::string get_key();
	std::string get_value();
	int set_father(ConfNode* father);
	int add_to_tree();
	int save(FILE* fs, int depth);

	ConfStruct* get_ins();
	ConfNode* get_child();

	bool has_key(const char* key);
	bool has_key(const std::string& key);
	bool has_key(int key);
	int size();
	ConfNode& operator[](const char* key);
	ConfNode& operator[](const std::string& key);
	ConfNode& operator[](int key);
	int to_int();
	double to_double();
	const char* to_cstr();
	std::string to_string();
	static std::vector<ConfNode*> gc;

private:
	ConfStruct* _conf_factory(nodetype node);
	ConfStruct* _conf_ins;

};

};

#endif //_CONF_NODE_H_
