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

#include "conf_struct.h"

namespace configure {

const int CONF_LINE_NUM = 1024;
const int CONF_ERROR = -1;
const int CONF_SUCC = 0;

class Configure {
public:
	Configure(const char* conf_file);
	Configure(const std::string& conf_file);
	conf_item& operator[](const char* item);
	conf_item& operator[](const std::string item);
	conf_item& operator[](int item);
	~Configure();

private:
	FILE* _fs;
	conf_item* _root;
	std::vector<conf_item*> _layers;
	nodetype _check_type(char* src);
	int _parse_branch(char*& src, conf_item*& item);
	int _parse_trunk(char*& src, conf_item*& item);
	int _parse_item(char*& src, conf_item* item);
	int _parse_array_item(char*& src, conf_item* item);
	int _get_layer(char*& src);
	conf_item* _get_father_node(int layer);
	int _set_father_node(int layer, conf_item* node);
	int _show_layers() {
		int i = 0;
		for (; i < _layers.size(); i++) {
			fprintf(stdout, "[layers]layer: %d,key: %s\n", i, _layers[i]->get_key().c_str());
		}
	};

	int _parse_key(char*& src, conf_item* item);
	int _parse_value(char*& src, conf_item* item);
	int _parse_array(char*& src, conf_item* item);

	int _parse();
	int _release(conf_item* conf_tree);
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
		if (item == '_') {
			return true;
		}
		return false;
	};
	bool get_next_line(char* line, int length);
	int _regulate_value(char* token, char* src);
};

};

#endif //#ifndef _CONFIGURE_H_
