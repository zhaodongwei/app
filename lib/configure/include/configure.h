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

class Configure {
public:
	Configure(const char* conf_file);
	Configure(const std::string& conf_file);
	conf_item** operator[](const char* item);
	~Configure();

private:
	FILE* _fs;
	conf_item* _root;
	int _parse_key(const char*& src, char* token);
	int _parse_split(const char*& src, char* token);
	int _parse_value(const char*& src, char* token);
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
};

};

#endif //#ifndef _CONFIGURE_H_
