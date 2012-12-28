/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: wordseg.h
 * date: 2012-12-17
 * desc: head file of wordseg class
 ***********************************************************/

#ifndef _WORDSEG_H_
#define _WORDSEG_H_

#include <stdio.h>
#include <string>
#include <vector>

#include "zdict.h"
#include "sign.h"

#define WORDSEG_SUCC 0
#define WORDSEG_ERROR -1

const unsigned int BUFF_LENGTH = 1024;

namespace wordseg {

class WordSeg {

public:
	WordSeg(const char* pdict);
	WordSeg(const std::string& pdict);
	WordSeg();
	int load_dict(const char* pdict);
	int load_dict(const std::string& pdict);
	~WordSeg();
	
	int seg(const char* pstr);
	int seg(const std::string& pstr);
	int get(unsigned int idx, char* des);
	int get(unsigned int idx, char* des, unsigned int len);
	unsigned int size();

private:

	zdict::ZDict _dict;
	std::vector<int> _seg;
	unsigned int _len;
	char* _line;
	
};

};

#endif //_WORDSEG_H_
