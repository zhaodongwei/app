/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: configure.h
 * date: 2012-11-18
 * desc: main declaration of configure
 ***********************************************************/

#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>

#include "conf_nodetype.h"
#include "conf_node.h"

namespace configure {

const int CONF_LINE_NUM = 1024;
const int CONF_ERROR = -1;
const int CONF_SUCC = 0;

class Configure {
public:
	Configure(const char* conf_file);
	Configure(const std::string& conf_file);
	ConfNode& operator[](const char* item);
	ConfNode& operator[](const std::string item);
	ConfNode& operator[](int item);
	int reload();
	int save(const char* conf_file);
	int save(FILE* conf_file);
	int size();
	bool has_key(const char* key);
	bool has_key(const std::string& key);
	bool has_key(int key);
	~Configure();

private:
	FILE* _fs;
	std::string _file;
	ConfNode* _root;
	std::vector<ConfNode*> _layers;
	int _init(const char* conf_file);
	nodetype _check_type(char* src);
	int _parse_branch(char*& src, ConfNode*& item);
	int _parse_trunk(char*& src, ConfNode*& item);
	int _parse_item(char*& src, ConfNode* item);
	int _parse_array_root(char*& src, ConfNode* item);
	int _get_layer(char*& src);
	ConfNode* _get_father_node(int layer);
	int _set_father_node(int layer, ConfNode* node);

	int _parse_key(char*& src, char* token);
	int _parse_value(char*& src, char* token);
	int _parse_array(char*& src, ConfNode* item);

	int _parse();
	int _release(ConfNode* conf_tree);
	int expect(char*& src, const char* des);
	int get_token(char*& src, char* token, int length);
	bool is_alpha_number(const char* letter) {
		char item = *letter;
		if (item >= 'a' && item <= 'z') {
			return true;
		}
		if (item >= 'A' && item <= 'Z') {
			return true;
		}
		if (item >= '0' && item <= '9') {
			return true;
		}
		if (item == '-' || item == '.' || item == '+') {
			return true;
		}
		return false;
	};
	bool get_next_line(char* line, int length);
	int _regulate_value(char* token, char* src);
};

};

#endif //#ifndef _CONFIGURE_H_
