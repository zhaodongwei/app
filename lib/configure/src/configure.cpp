/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: configure.cpp
 * date: 2012-11-19
 * desc: main implementation of configure
 ***********************************************************/

#include <stdio.h>

#include "configure.h"

namespace configure {

Configure::Configure(const char* conf_file) {
	_fs = fopen(conf_file, "r");
	if (NULL == _fs) {
		fprintf(stderr, "conf file open error\n");
	}
	_root = NULL;
	_parse();
};

Configure::Configure(const std::string& conf_file) {
	_fs = fopen(conf_file.c_str(), "r");
	if (NULL == _fs) {
		fprintf(stderr, "conf file open error\n");
	}
	_root = NULL;
	_parse();
};

Configure::~Configure() {
	if (NULL != _fs) {
		fclose(_fs);
	}
	_fs = NULL;
	_release(_root);
};

int Configure::_parse() {
	_root = new conf_item;
	char line[1024];
	char token[1024];
	const char* iter = line;
	while(NULL != fgets(line, 1024, _fs)) {
		iter = line;
		fprintf(stdout, "%s", line);
		conf_item* item = new conf_item;
		_parse_key(iter, token);
		item->key.append(token);
		fprintf(stdout, "key: -->%s<--\n", item->key.c_str());
		_parse_split(iter, token);
		fprintf(stdout, "split: -->%s<--\n", token);
		_parse_value(iter, token);
		item->value.append(token);
		fprintf(stdout, "value: -->%s<--\n", item->value.c_str());
	}
};

int Configure::_parse_key(const char*& src, char* token) {
	if (NULL == src || NULL == token) {
		return -1;
	}
	while (*src == ' ' || *src == '\t') {
		src++;
	}
	int ret = 0;
	while (is_alpha_number(src) && *src != '\n' 
			&& *src != ' ' && *src != '\t') {
		token[ret] = *src;
		src++;
		ret++;
	}
	token[ret] = 0;
	return ret;
};

int Configure::_parse_split(const char*& src, char* token) {
	if (NULL == src || NULL == token) {
		return -1;
	}
	while (*src == ' ' || *src == '\t') {
		src++;
	}
	int ret = 0;
	while (*src == ':') {
		token[ret] = *src;
		src++;
		ret++;
	}
	token[ret] = 0;
	return ret;
};

int Configure::_parse_value(const char*& src, char* token) {
	if (NULL == src || NULL == token) {
		return -1;
	}
	while (*src == ' ' || *src == '\t') {
		src++;
	}
	int ret = 0;
	while (*src != '\n') {
		token[ret] = *src;
		src++;
		ret++;
	}
	token[ret] = 0;
	return ret;
};

int Configure::_release(conf_item* conf_tree) {
	if (NULL == conf_tree) {
		return 0;
	}
	if (NULL != conf_tree->child) {
		_release(conf_tree->child);
	}
	if (NULL != conf_tree->brother) {
		_release(conf_tree->brother);
	}
	delete conf_tree;
	conf_tree = NULL;
};

};

