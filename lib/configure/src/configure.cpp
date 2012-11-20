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
	_root->set_key("root");
	char line[CONF_LINE_NUM];
	char token[CONF_LINE_NUM];
	char* iter = line;
	while(get_next_line(line, CONF_LINE_NUM)) {
		iter = line;
		fprintf(stdout, "%s", line);
		conf_item* item = new conf_item;
		item->set_father(_root);
		item->add_to_tree();
		_parse_key(iter, token);
		item->set_key(token);
		fprintf(stdout, "key: -->%s<--\n", item->get_key().c_str());
		_parse_split(iter, token);
		fprintf(stdout, "split: -->%s<--\n", token);
		_parse_value(iter, token);
		item->set_value(token);
		fprintf(stdout, "value: -->%s<--\n", item->get_value().c_str());
		fprintf(stdout, "I'm double: %lf\n", item->to_double());
		fprintf(stdout, "The _value of _key %s is %s\n", "input", (*_root)["input"].to_cstr());
	}
};

int Configure::_parse_key(char*& src, char* token) {
	if (NULL == src || NULL == token) {
		return CONF_ERROR;
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

int Configure::_parse_split(char*& src, char* token) {
	if (NULL == src || NULL == token) {
		return CONF_ERROR;
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

int Configure::_parse_value(char*& src, char* token) {
	if (NULL == src || NULL == token) {
		return CONF_ERROR;
	}
	int src_len = strlen(src);
	if (src_len == 0) {
		return CONF_ERROR;
	}
	
	if (src[src_len - 2] == '\\') {
		get_next_line(src + src_len - 2, CONF_LINE_NUM - src_len);
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

bool Configure::get_next_line(char* line, int length) {
	bool ret = false;
	if (NULL != fgets(line, length, _fs)) {
		ret = true;
	}
	return ret;
};

int Configure::_release(conf_item* conf_tree) {
	if (NULL == conf_tree) {
		return 0;
	}
	delete conf_tree;
	conf_tree = NULL;
};

};

