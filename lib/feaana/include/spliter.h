/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: spliter.h
 * date: 2012-12-28
 * desc: the split lib
 ***********************************************************/

#ifndef _SPLITER_H_
#define _SPLITER_H_

#include <vector>

namespace feaana {

#define SPLIT_SUCC 0
#define SPLIT_ERROR -1

const int SPLITER_LINE_LENGTH = 1025;
const int SPLITER_SEG_LENGTH = 513;

int spliter_setseg(const char* seg);
int spliter_split(const char* line, const char* seg);
int spliter_split(const char* line);

int spliter_at(int pos, char* des);
unsigned int spliter_size();

int spliter_erase_newline(char* line);

class Spliter {

public:
	Spliter();
	~Spliter();

	int set_seg(const char* seg);
	int split(const char* line, const char* seg);
	int split(const char* line);

	int at(int pos, char* des);
	unsigned int size();

	static Spliter* get_spliter_instance();

private:
	char* _seg;
	char* _line;
	int _line_length;
	std::vector<int> _idx;
	static Spliter* _spliter; 

	class SplitGarbage {
	public:
		SplitGarbage() {};
		~SplitGarbage() {
			if (NULL != Spliter::_spliter) {
				delete _spliter;
			}
		};
	};
	static SplitGarbage _sg;
};

};

#endif //_SPLITER_H_



