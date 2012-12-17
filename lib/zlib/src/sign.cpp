/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: sign.cpp
 * date: 2012-12-16
 * desc: implement md5 sign calc
 ***********************************************************/

#include <stdio.h>
#include <string.h>

#include "sign.h"
#include "md5.h"

int create_sign(zint64 & sign1, zint64& sign2, const char* pchar) {
	if (NULL == pchar)
	{
		sign1 = sign2 = 0;
		return -1;
	}

	struct MD5Context context;
	unsigned char checksum[16];
	int i;
	
	MD5Init(&context);
	MD5Update(&context, (unsigned char*)pchar, strlen(pchar));
	MD5Final(checksum, &context);
	sign1 = getu32(checksum + 4);
	sign1 = (sign1 << 32) | getu32(checksum);
	sign2 = getu32(checksum + 12);
	sign2 = (sign2 << 32) | getu32(checksum + 8);
	return 0;
};

int create_sign(zint64& sign1, zint64& sign2, const std::string& pchar) {
	return create_sign(sign1, sign2, pchar.c_str());
};

int create_sign(zint64 & sign1, zint64& sign2, const char* pchar, int file) {
	if (NULL == pchar)
	{
		sign1 = sign2 = 0;
		return -1;
	}
	FILE* fs = fopen(pchar, "r");
	if (NULL == fs) {
		sign1 = sign2 = 0;
		return -1;
	};

	struct MD5Context context;
	unsigned char checksum[16];
	int i;
	
	MD5Init(&context);
	unsigned char file_buff[65];
	char* fbuff = (char*)file_buff;
	memset(fbuff, 0, 65);
	char* ret = fgets(fbuff, 64, fs);
	while (1) {
		int len = strlen(fbuff);
		while (NULL != ret && 64 > len)	{
			ret = fgets(fbuff + len, 65 - len, fs);
			len = strlen(fbuff);
		}
		if (64 == len) {
			MD5Update(&context, (unsigned char*)fbuff, 64);
		}
		if (NULL == ret) {
			MD5Final(checksum, &context);
			break;
		}
		
		memset(fbuff, 0, 65);
	}
	fclose(fs);
	sign1 = getu32(checksum + 4);
	sign1 = (sign1 << 32) | getu32(checksum);
	sign2 = getu32(checksum + 12);
	sign2 = (sign2 << 32) | getu32(checksum + 8);
	return 0;
};

int create_sign(zint64 & sign1, zint64& sign2, const std::string& pchar, int file) {
	create_sign(sign1, sign2, pchar.c_str(), 0);
};

int create_sign(zint64 & sign1, zint64& sign2, unsigned int len, const char* pchar) {
	if (NULL == pchar)
	{
		sign1 = sign2 = 0;
		return -1;
	}

	struct MD5Context context;
	unsigned char checksum[16];
	int i;
	unsigned int length = strlen(pchar);
	if (len < length) {
		length = len;
	}
	MD5Init(&context);
	MD5Update(&context, (unsigned char*)pchar, length);
	MD5Final(checksum, &context);
	sign1 = getu32(checksum + 4);
	sign1 = (sign1 << 32) | getu32(checksum);
	sign2 = getu32(checksum + 12);
	sign2 = (sign2 << 32) | getu32(checksum + 8);
	return 0;
};

int create_sign(zint64 & sign1, zint64& sign2, unsigned int len, const std::string& pchar) {
	return create_sign(sign1, sign2, len, pchar.c_str());
};
