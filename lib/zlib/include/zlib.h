/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: zlib.h
 * date: 2012-11-16
 * desc: some useful tools
 ***********************************************************/

#ifndef _ZLIB_H_
#define _ZLIB_H_

#include <stdio.h>

namespace zlib{

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

#endif //#ifndef _ZLIB_H_


