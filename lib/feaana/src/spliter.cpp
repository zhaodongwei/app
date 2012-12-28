/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: spliter.cpp
 * date: 2012-12-28
 * desc: the split lib
 ***********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "exception.h"
#include "spliter.h"

namespace feaana {

int spliter_setseg(const char* seg) {
	Spliter* ins = Spliter::get_spliter_instance();
	return ins->set_seg(seg);
};

int spliter_split(const char* line, const char* seg) {
	Spliter* ins = Spliter::get_spliter_instance();
	return ins->split(line, seg);
};

int spliter_split(const char* line) {
	Spliter* ins = Spliter::get_spliter_instance();
	return ins->split(line);	
};

int spliter_at(int pos, char* des) {
	Spliter* ins = Spliter::get_spliter_instance();
	return ins->at(pos, des);
};

unsigned int spliter_size() {
	Spliter* ins = Spliter::get_spliter_instance();
	return ins->size();
};

Spliter* Spliter::_spliter;
Spliter::SplitGarbage Spliter::_sg;

Spliter::Spliter() {
	int try_time = 0;
	while (NULL == _line) {
		_line = (char*)malloc(SPLITER_LINE_LENGTH);
		if (10 < try_time) {
			break;
		}
		try_time++;
	}
	try_time = 0;
	while (NULL == _seg) {
		_seg  = (char*)malloc(SPLITER_SEG_LENGTH);
		if (10 < try_time) {
			break;
		}
		try_time++;
	}
	if (NULL == _line || NULL == _seg) {
		throw exception(OUT_OF_MEMORY, "alloc space for spliter fail");
	}

	_line_length = SPLITER_LINE_LENGTH;
	*_seg = '\t';
}

Spliter::~Spliter() {
	if (NULL != _line) {
		delete _line;
	}
	if (NULL != _seg) {
		delete _seg;
	}
};

Spliter* Spliter::get_spliter_instance() {
	if (NULL != _spliter) {
		return _spliter;
	}
	_spliter = new Spliter();
	return _spliter;
};

int Spliter::set_seg(const char* seg) {
	if (NULL == seg) {
		return SPLIT_ERROR;
	}
	if (strlen(seg) >= SPLITER_SEG_LENGTH - 1) {
		return SPLIT_ERROR;
	}
	strncpy(_seg, seg, SPLITER_SEG_LENGTH);
	return SPLIT_SUCC;
};

int Spliter::split(const char* line, const char* seg) {
	if (NULL == line || NULL == seg) {
		return SPLIT_ERROR;
	}
	if (SPLIT_SUCC != set_seg(seg)) {
		return SPLIT_ERROR;
	}
	int ret = split(line);
	return ret;
};

int Spliter::split(const char* line) {
	if (NULL == line) {
		return SPLIT_ERROR;
	}
	if (strlen(line) > _line_length - 1) {
		char* tmp = (char*)malloc(strlen(line) + 1);
		if (NULL == tmp) {
			return SPLIT_ERROR;
		}
		delete _line;
		_line = tmp;
		_line_length = strlen(line) + 1;
	}
	strncpy(_line, line, strlen(line) + 1);
	fprintf(stdout, "split now, seg[%s], line[%s]\n", _seg, line);
	_idx.clear();
	_idx.push_back(0);
	char* tmp = _line;
	char* idx;
	while(NULL != (idx = strstr(tmp, _seg))) {
		_idx.push_back(idx - _line + strlen(_seg));
		tmp = idx + strlen(_seg);
		if (tmp - _line >= strlen(_line)) {
			break;
		}
	}
	return SPLIT_SUCC;
};

unsigned int Spliter::size() {
	return _idx.size();
};

int Spliter::at(int pos, char* des) {
	if (pos < 0 || pos > size() || des == NULL) {
		return SPLIT_ERROR;
	}
	if (0 == pos) {
		strncpy(des, _line, _line_length);
		return SPLIT_SUCC;
	}
	int begin, length;
	begin = _idx.at(pos - 1);
	if (size() == pos) {
		length = strlen(_line) - begin;
	}
	else {
		length = _idx.at(pos) - begin - strlen(_seg);
	}
	strncpy(des, _line + begin, length);
	*(des + length) = '\0';

	return SPLIT_SUCC;
};

};
