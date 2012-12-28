/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: feaana.cpp
 * date: 2012-12-27
 * desc: head file for feaana
 ***********************************************************/

#ifndef _FEAANA_H_
#define _FEAANA_H_

#include <stdio.h>
#include <string.h>
#include <string>

#include "funclib.h"

namespace feaana {

class Feaana {

public:
	Feaana();
	~Feaana();
	int reg(const char* pfile);
	int filter(int pos, bool (*func)(int, int), int arg);

private:
	FILE* _fs;
	std::string _fname;

};

};

#endif //_FEAANA_H_
