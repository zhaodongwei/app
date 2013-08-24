/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: zdict.cpp
 * date: 2012-12-13
 * desc: src file of zdict
 ***********************************************************/

#include <map>

#include "zdict.h"

namespace zdict {

ZDict::ZDict() {

};

ZDict::ZDict(zint64 sign1, zint64 sign2, int value) {
	_dict.insert(std::make_pair(KEY(sign1, sign2), value));
};
ZDict::~ZDict() {
	_dict.clear();
};

int ZDict::add(zint64 sign1, zint64 sign2, int value) {
	_dict.insert(std::make_pair(KEY(sign1, sign2), value));
	return ZDICT_SUCC;
};

int ZDict::remove(zint64 sign1, zint64 sign2) {
	_dict.erase(KEY(sign1, sign2));
	return ZDICT_SUCC;
};

int ZDict::has(zint64 sign1, zint64 sign2) {
	if (_dict.end() == _dict.find(KEY(sign1, sign2))) {
		return ZDICT_NOTEXIST;
	}
	return ZDICT_EXIST;
};

int ZDict::has(zint64 sign1, zint64 sign2, int& value) {
	std::map<KEY, int>::iterator iter = _dict.find(KEY(sign1, sign2));
	if (_dict.end() == iter) {
		return ZDICT_NOTEXIST;
	}
	value = iter->second;
	return ZDICT_EXIST;
};

};
