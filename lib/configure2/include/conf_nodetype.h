/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_nodetype.h
 * date: 2012-11-21
 * desc: conf node type
 ***********************************************************/

#ifndef _CONF_NODETYPE_H_
#define _CONF_NODETYPE_H_
namespace configure {

enum all_types{
	INVALID = 0,
	ROOT,
	TRUNK,
	BRANCH,
	ITEM,
	ARRAY_ROOT,
	ARRAY_ITEM,
	SHADOW
};

typedef enum all_types nodetype; 

};

#endif //#ifndef _CONF_NODETYPE_H_



