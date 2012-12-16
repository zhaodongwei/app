/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: tools.h
 * date: 2012-11-16
 * desc: some useful tools
 ***********************************************************/

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>

namespace tools{

class ScopeFile{

public:
	ScopeFile(const char* arg, const char* mode);
	~ScopeFile();
	FILE* get_ptr();

private:
	FILE* _file;
};

const char* seg_sentence(const char* line, const char* sep, char* des, int idx);
int count_sep(const char* line, const char* sep);

};

#endif //#ifndef _TOOLS_H_


