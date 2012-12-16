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

typedef unsigned int zint32;
typedef unsigned long long zint64;

int create_sign(zint64 & sign1, zint64& sign2, const char* pchar);
int create_sign(zint64 & sign1, zint64& sign2, const std::string& pchar);

int create_sign(zint64 & sign1, zint64& sign2, const char* pchar, int file);
int create_sign(zint64 & sign1, zint64& sign2, const std::string& pchar, int file);

#endif //#ifndef _SIGN_H_

