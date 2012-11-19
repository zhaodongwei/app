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
#include "tools.h"
#include "conf_struct.h"

namespace configure {

class Configure {
public:
	Configure(const char* conf_file);
	Configure(const std::string& conf_file);
	const char* operator[](const char* item);
	~Configure();

private:
	FILE* _fs;
	conf_item* root;
	int get_token(char* src, char* token);
	int parse();
	int release(conf_item* conf_tree);
};

};

#endif //#ifndef _CONFIGURE_H_
