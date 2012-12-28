/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: feaana.h
 * date: 2012-12-27
 * desc: implementation of feaana
 ***********************************************************/

#include "exception.h"
#include "feaana.h"
#include "spliter.h"

namespace feaana {

Feaana::Feaana() {
	_fs = NULL;
};

Feaana::~Feaana() {
	if (NULL != _fs) {
		fclose(_fs);
		_fs = NULL;
	}
};

int Feaana::reg(const char* pfile) {
	if (NULL == pfile) {
		throw exception(NOT_EXIST, "invalid file ptr");
	}
	
	if (NULL != _fs) {
		fclose(_fs);
		_fs = NULL;
	}

	_fname.clear();
	_fname.append(pfile);
	_fs = fopen(pfile, "r");
	if (NULL == _fs) {
		throw exception(NOT_EXIST, "open file %s fail", pfile);
	}
	
	return 0;
};

int Feaana::filter(int pos, bool (*func)(int, int), int arg) {
	freopen(_fname.c_str(), "r", _fs);
	const int LINE_LENGTH = 1024;
	char line[LINE_LENGTH];
	while (NULL != fgets(line, LINE_LENGTH, _fs)) {
		spliter_erase_newline(line);
		spliter_split(line, "\t");
		char tmp[LINE_LENGTH];
		spliter_at(3, tmp);
		fprintf(stdout, "[%s]\n", tmp);
	}
	int tmp = 10000;
	if (func(tmp, arg)) {
		fprintf(stdout, "%d\t%d\t%d\n", pos, tmp, arg);
	}
	
	return 0;
}


};
