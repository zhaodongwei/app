/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_struct.h
 * date: 2012-11-18
 * desc: conf struct declare
 ***********************************************************/

#ifndef _CONF_STRUCT_H_
#define _CONF_STRUCT_H_

#include <stdio.h>
#include <list>

namespace configure {

struct conf_struct {
	std::string key;
	int value_num;
	std::string value;
	std::list<std::string> value_list;
	struct conf_struct* child;
	struct conf_struct* brother;
	conf_struct() {
		child = NULL;
		brother = NULL;
	}
};

typedef struct conf_struct conf_item;

};

#endif //#ifndef _CONF_STRUCT_H_

