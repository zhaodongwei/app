/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: wordseg.h
 * date: 2012-12-17
 * desc: word seg program
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "wordseg.h"

namespace wordseg {

WordSeg::WordSeg(const char* pdict) {
	load_dict(pdict);
	_len = BUFF_LENGTH;
	_line = (char*)malloc(_len + 1);
	if (NULL == _line) {
		throw exception(OUT_OF_MEMORY, "out of resource");
	}
};

WordSeg::WordSeg(const std::string& pdict) {
	load_dict(pdict);
	_len = BUFF_LENGTH;
	_line = (char*)malloc(_len + 1);
	if (NULL == _line) {
		throw exception(OUT_OF_MEMORY, "out of resource");
	}
};

WordSeg::WordSeg() {
	_len = BUFF_LENGTH;
	_line = (char*)malloc(_len + 1);
	if (NULL == _line) {
		throw exception(OUT_OF_MEMORY, "out of resource");
	}
};

WordSeg::~WordSeg() {
	if (NULL != _line) {
		delete _line;
		_line = NULL;
	}
};

int WordSeg::load_dict(const char* pdict) {
	FILE* fs = fopen(pdict, "r");
	if (NULL == fs) {
		throw exception(NOT_EXIST, "dict %s not exist", pdict);
		return WORDSEG_ERROR;
	}
	zint64 sign1;
	zint64 sign2;
	char line[BUFF_LENGTH];
	while (NULL != fgets(line, BUFF_LENGTH, fs)) {
		for(int i = 0; i < strlen(line); i++) {
			if (*(line + i) == '\n' || *(line + i) == '\r') {
				*(line + i) = 0;
			}
		}
		create_sign(sign1, sign2, line);
		_dict.add(sign1, sign2, 1);
	}
	return WORDSEG_SUCC;
};

int WordSeg::load_dict(const std::string& pdict) {
	return load_dict(pdict.c_str());
};

int WordSeg::seg(const char* pstr) {
	unsigned int len = strlen(pstr);
	_seg.clear();
	if (0 == len) {
		return 0;
	}
	_seg.push_back(0);
	if (_len < len) {
		char* tmp = (char*)malloc(len + 1);
		if (NULL == tmp) {
			return WORDSEG_ERROR;
		}
		_len = len;
		delete _line;
		_line = tmp;
	}
	memcpy(_line, pstr, len);
	for(int i = 0; i < len; i++) {
		if (*(_line + i) == '\n' || *(_line + i) == '\r') {
			*(_line + i) = ' ';
		}
	}
	zint64 sign1, sign2;
	for (int i = 0; i < len; ) {
		int j = i + 2;
		for ( ; j < len; j += 1) {
			create_sign(sign1, sign2, j - i, _line + i);
			char tmp[1024] = {0};
			memcpy(tmp, _line + i, j - i);
			if (ZDICT_EXIST == _dict.has(sign1, sign2))  {
				_seg.push_back(j);
				break;
			}
		}
		i = j;
	}
	return _seg.size();
};

int WordSeg::seg(const std::string& pstr) {
	return seg(pstr.c_str());
};

int WordSeg::get(unsigned int idx, char* des) {
	if (idx > _seg.size() || 0 == _seg.size()) {
		return WORDSEG_ERROR;
	}
	if (0 == idx) {
		memcpy(des, _line, strlen(_line));
		memset(des + strlen(_line), 0, 1);
		return WORDSEG_SUCC;
	}
	int start = _seg[idx - 1];
	int end;
	if (idx == _seg.size()) {
		end = strlen(_line);
	}
	else {
		end = _seg[idx];
	}
	memcpy(des, _line + start, end - start);
	memset(des + end - start, 0, 1);
	return WORDSEG_SUCC;
};
 
int WordSeg::get(unsigned int idx, char* des, unsigned int len) {
	if (idx > _seg.size() || 0 == _seg.size() || len <= 0) {
		return WORDSEG_ERROR;
	}
	if (0 == idx) {
		int len_min = strlen(_line);
		if (len_min > len) {
			len_min = len;
		}
		memcpy(des, _line, len_min);
		memset(des + len_min, 0, 1);
		return WORDSEG_SUCC;
	}
	int start = _seg[idx - 1];
	int end;
	if (idx == _seg.size()) {
		end = strlen(_line);
	}
	else {
		end = _seg[idx];
	}
	int len_min = end - start;
	if (len_min > len) {
		len_min = len;
	}
	memcpy(des, _line + start, len_min);
	memset(des + len_min, 0, 1);
	return WORDSEG_SUCC;
};

unsigned int WordSeg::size() {
	return _seg.size();
};

};
