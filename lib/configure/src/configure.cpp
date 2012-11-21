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
#include "conf_nodetype.h"

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
	_root->set_nodetype(ROOT);

	char line[CONF_LINE_NUM];
	char* iter = line;
	while(get_next_line(line, CONF_LINE_NUM)) {
		iter = line;
		fprintf(stdout, "%s\n", line);
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
	int ret = 0;
	char token[CONF_LINE_NUM];
	get_token(src, token, CONF_LINE_NUM);
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
		expect(src, "[");
		return _parse_array(src, item);
	}

	int ret = 0;
	char token[CONF_LINE_NUM];
	while (*src != 0) {
		token[ret++] = *src;
		src++;
	}
	token[ret] = 0;
	item->set_value(token);
	item->set_nodetype(ITEM);
	fprintf(stdout, "[parse value] value: %s\n", item->get_value().c_str());
	return ret;
};

int Configure::_parse_array(char*& src, conf_item* item) {
	if (NULL == src || NULL == item) {
		return CONF_ERROR;
	}
	char token[CONF_LINE_NUM];
	fprintf(stdout, "[array]%s\n", src);
	int element_cnt = 0;
	while (get_token(src, token, CONF_LINE_NUM) > 0) {
		fprintf(stdout, "[array]try to build an element %s\n", token);
		conf_item* tmp;
		if (0 == element_cnt) {
			tmp = item;
			tmp->set_value(token);
		}
		else {
			tmp = new conf_item(item->get_key().c_str(), token);
			tmp->set_father(item->get_father());
			tmp->add_to_tree();
		}
		tmp->set_nodetype(ARRAY_ITEM);
		expect(src, ",");
		element_cnt++;
	}
	if (*src == 0) {
		char tmp[CONF_LINE_NUM];
		get_next_line(tmp, CONF_LINE_NUM);
		char* iter = tmp;
		conf_item* next_item = new conf_item;
		next_item->set_key(item->get_key());
		next_item->set_father(item);
		next_item->add_to_tree();
		return _parse_array(iter, next_item);
	}	
	if (*src == ']') {
		expect(src, "]");
		return CONF_SUCC;
	}
	return CONF_ERROR;
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
	fprintf(stdout, "[expect]%s,from: %s\n", des, src);
	while (i < len && src[i] == des[i]) {
		i++;
		src++;
	}
	if (i != len) {
		return CONF_ERROR;
	}
	return CONF_SUCC;
};

int Configure::get_token(char*& src, char* token, int length) {
	if (NULL == src || NULL == token || length <= 0) {
		return CONF_ERROR;
	}
	int len = std::min((int)strlen(src), length);
	int iter = 0;
	while (iter < len && (*src == ' ' || *src == '\t')) {
		src++;
		iter++;
	}
	int token_len = 0; 
	while (iter++ < len && is_alpha_number(src)) {
		*token++ = *src++;
		token_len++;
	}
	*token = 0;
	return token_len;
}

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
	if (line[len - 1] == '\n' || line[len -1] == '\r') {
		line[len - 1] = 0;
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
conf_item& Configure::operator[](const char* item) {
	return (*_root)[item];
}
conf_item& Configure::operator[](int item) {
	return (*_root)[item];
};

};

