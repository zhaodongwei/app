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
#include "conf_struct.h"

namespace configure {

const int CONF_LINE_NUM = 1024;
const int CONF_ERROR = -1;

class Configure {
public:
	Configure(const char* conf_file);
	Configure(const std::string& conf_file);
	conf_item** operator[](const char* item);
	~Configure();

private:
	FILE* _fs;
	conf_item* _root;
	int _parse_key(char*& src, char* token);
	int _parse_split(char*& src, char* token);
	int _parse_value(char*& src, char* token);
	int _parse();
	int _release(conf_item* conf_tree);
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
};

};

#endif //#ifndef _CONFIGURE_H_
