/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: tools.cpp
 * date: 2012-11-16
 * desc: some useful tools
 ***********************************************************/

#include <stdio.h>
#include <string.h>

#include "zlib.h"

namespace zlib {

ScopeFile::ScopeFile(const char* file, const char* mode) {
	if (NULL == file || NULL == mode) {
		fprintf(stderr, "invalid file or open mode\n");
	}
	else {
		_file = fopen(file, mode);
		if (NULL == _file) {
			fprintf(stderr, "open file %s error\n", file);
		}
	}
};

ScopeFile::~ScopeFile() {
	if (NULL != _file) {
		fclose(_file);
		_file = NULL;
	}
};

FILE* ScopeFile::get_ptr() {
	return _file;
};

const char* seg_sentence(const char* line, const char* sep, char* des, int idx) {
	if (NULL == line || NULL == des || NULL == sep) {
		return NULL;
	}
	if (idx <= 0 || idx > strlen(line)) {
		return NULL;
	}

	const char* begin = line;
	int i = 1;
	while (i < idx) {
		begin = strstr(begin, sep);
		if (NULL == begin) {
			return NULL;
		}
		begin += strlen(sep);
		++i;
	}
	const char* end = strstr(begin, sep);
	if (NULL == end) {
		end = line + strlen(line);
	}
	i = 0;
	while (i < (end - begin)) {
		des[i] = begin[i];
		++i;
	}
	des[i] = 0;

	return begin;
};

int count_sep(const char* line, const char* sep) {
	if (NULL ==  line || NULL == sep) {
		return 0;
	}
	const char* iter = line;
	int ret = 0;
	while (iter < line + strlen(line)) {
		iter = strstr(iter, sep);
		if (NULL != iter) {
			++ret;
			iter += strlen(sep);
		}
		else {
			break;
		}
	}
	return ret;
};

};


