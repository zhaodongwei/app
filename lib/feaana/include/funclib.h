/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: funclib.h
 * date: 2012-12-27
 * desc: funclib file for feaana
 ***********************************************************/

#ifndef _FUNCLIB_H_
#define _FUNCLIB_H_

template<class T>
bool F_GREATER_THAN(T lhs, T rhs) {
	if (rhs < lhs) {
		return true;
	}
	return false;
};

template<class T>
bool F_GREATER_EQUAL(T lhs, T rhs) {
	if (rhs < lhs || rhs == lhs) {
		return true;
	}
	return false;
};

template<class T>
bool F_LESS_THAN(T lhs, T rhs) {
	if (lhs < rhs) {
		return true;
	}
	return false;
};

template<class T>
bool F_LESS_EQUAL(T lhs, T rhs) {
	if (lhs < rhs || rhs == lhs) {
		return true;
	}
	return false;
};

template<class T>
bool F_EQUAL(T lhs, T rhs) {
	if (rhs == lhs) {
		return true;
	}
	return false;
};

#endif //_FUNCLIB_H_


