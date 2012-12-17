/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: zdict.h
 * date: 2012-12-13
 * desc: head file of zdict
 ***********************************************************/

#ifndef _ZDICT_H_
#define _ZDICT_H_

#include <string>
#include <map>

typedef unsigned int zint32;
typedef unsigned long long zint64;
#define ZDICT_SUCC 0
#define ZDICT_ERROR -1
#define ZDICT_EXIST 0
#define ZDICT_NOTEXIST -1

namespace zdict {

struct key {
	zint64 a;
	zint64 b;
	key():a(0),b(0) {};
	key(zint64 sign1, zint64 sign2):a(sign1),b(sign2) {};
	friend bool operator<(const struct key& lh, const struct key& rh);
};
typedef struct key KEY;

inline bool operator<(const KEY& lh, const KEY & rh) {
	if (lh.a < rh.a) {
		return true;
	}
	if (lh.a > rh.a) {
		return false;
	}
	return lh.b < rh.b;
};

class ZDict {

public:
	ZDict();
	ZDict(zint64 sign1, zint64 sign2, int value);
	~ZDict();

	int add(zint64 sign1, zint64 sign2, int value);
	int remove(zint64 sign1, zint64 sign2);
	int has(zint64 sign1, zint64 sign2);
	int has(zint64 sign1, zint64 sign2, int& value);

private:
	std::map<KEY, int> _dict;
};

};

#endif//_ZDICT_H_

