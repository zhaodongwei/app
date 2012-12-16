/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: sign.h
 * date: 2012-12-16
 * desc: md5 sign calc
 ***********************************************************/

#ifndef _SIGN_H_
#define _SIGN_H_

#include <stdio.h>
#include <string>

typedef int int32;
typedef long long int64;

int create_sign(int64 & sign1, int64& sign2, const char* pchar);
int create_sign(int64 & sign1, int64& sign2, const std::string& pchar);

#endif //#ifndef _SIGN_H_

