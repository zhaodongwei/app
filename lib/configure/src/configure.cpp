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
	char* iter = line;
	while(get_next_line(line, CONF_LINE_NUM)) {
		iter = line;
		fprintf(stdout, "%s", line);
		conf_item* item = new conf_item;
		item->set_father(_root);
		item->add_to_tree();
		_parse_key(iter, item);
		fprintf(stdout, "key: -->%s<--\n", item->get_key().c_str());
		expect(iter, ":");
		_parse_value(iter, item);
		fprintf(stdout, "value: -->%s<--\n", item->get_value().c_str());
		fprintf(stdout, "I'm double: %lf\n", item->to_double());
		fprintf(stdout, "The _value of _key %s is %s\n", "input", (*_root)["input"].to_cstr());
	}
};

int Configure::_parse_key(char*& src, conf_item* item) {
	if (NULL == src || NULL == item) {
		return CONF_ERROR;
	}
	while (*src == ' ' || *src == '\t') {
		src++;
	}
	int ret = 0;
	char token[CONF_LINE_NUM];
	while (is_alpha_number(src) && *src != '\n' 
			&& *src != ' ' && *src != '\t') {
		token[ret] = *src;
		src++;
		ret++;
	}
	token[ret] = 0;
	item->set_key(token);
	return ret;
};

int Configure::_parse_value(char*& src, conf_item* item) {
	if (NULL == src || NULL == item) {
		return CONF_ERROR;
	}
	int src_len = strlen(src);
	if (src_len == 0) {
		return CONF_ERROR;
	}
	
	while (*src == ' ' || *src == '\t') {
		src++;
	}
	if (*src == '[') {
		return _parse_array(src, item);
	}

	int ret = 0;
	char token[CONF_LINE_NUM];
	while (*src != '\n') {
		token[ret] = *src;
		src++;
		ret++;
	}
	token[ret] = 0;
	item->set_value(token);
	return ret;
};

int Configure::_parse_array(char*& src, conf_item* item) {
	if (NULL == src || NULL == item) {
		return CONF_ERROR;
	}
	expect(src, "\\");	
};

int Configure::expect(char*& src, const char*des) {
	if (NULL == src || des == NULL) {
		return CONF_ERROR;
	}
	if (*src == ' ' || *src == '\t') {
		src++;
	}
	int i = 0;
	int len = strlen(des);
	while (i < len && src[i] == des[i]) {
		i++;
		src++;
	}
	if (i != len) {
		return CONF_ERROR;
	}
	return CONF_SUCC;
};

bool Configure::get_next_line(char* line, int length) {
	bool ret = false;

	if (NULL != fgets(line, length, _fs)) {
		ret = true;
	}
	int len = strlen(line);
	while (ret && line[len - 2] == '\\') {
		if (NULL != fgets(line + len - 2, CONF_LINE_NUM - len, _fs)) {
			ret = true;
			len = strlen(line);
		}
		else {
			ret = false;
		}
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

