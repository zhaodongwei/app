/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: sign.cpp
 * date: 2012-12-16
 * desc: implement md5 sign calc
 ***********************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sign.h"

int lrotate(int src, int n) {
	return ((src << n) | (src >> (32 - n)));
};

int create_sign(int64 & sign1, int64& sign2, const char* pchar) {
	if (NULL == pchar) {
		sign1 = sign2 = 0;
		return -1;
	}
	
	int r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
				 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 
				 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21  
		};

	int k[64];
	for (int i = 0; i < 64; i++) {
		k[i] = floor(abs(sin(i + 1)) * pow(2, 32));
	}
	int h0 = 0x67452301;
	int h1 = 0xEFCDAB89;
	int h2 = 0x98BADCFE;
	int h3 = 0x10325476;

	int len = strlen(pchar);
	int slen = 448 - (len % 512);
	unsigned char* pmem = (unsigned char*)malloc(len + slen);
	if (NULL == pmem) {
		fprintf(stderr, "out of memmory\n");
	}
	if (slen > 0) {
		memcpy(pmem, pchar, len);
		memset((void*)(pmem + len), 0x80, 1);
		int i = slen - 1;
		while (i > 0) {
			memset((void*)(pmem + len + slen - i), 0x0, 1);
			i--;
		}
		memset((void*)(pmem + len + slen), len, 1);
	}
	int w[16];
	for(int chunck = 0; chunck < len + slen; chunck += 512) {
		for (int i = 0; i < 16; i++) {
			memcpy(w + i, pmem + chunck, 4);
		}
		int a = h0;
		int b = h1;
		int c = h2;
		int d = h3;
		int f;
		int g;
		for (int i = 0; i < 64; i++) {
			if (i < 16) {
				f = (b & c) | ((~b) & d);
				g = i;	
			}
			else if (i < 32) {
				f = (d & b) | ((~d) & c);
				g = (5 * i + 1) % 16;  
			}
			else if (i < 48) {
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else {
				f = c ^ (b | (~d));
				g = (7 * i) % 16;
			}
			int tmp = d;
			d = c;
			c = b;
			b = lrotate((a + f + k[i] + w[g]), r[i]) + b; 
			a = tmp;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
	}
	sign1 = h0;
	sign1 = sign1 << 32 + h1;
	sign2 = h2;
	sign2 = sign2 << 32 + h3;
	return 0;
};

int create_sign(int64 & sign1, int64& sign2, const std::string& pchar) {
	return create_sign(sign1, sign2, pchar.c_str());
};

