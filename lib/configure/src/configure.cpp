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

nodetype Configure::_check_type(char* src) {
	nodetype ret = INVALID;
	if (NULL == src) {
		return INVALID;
	}
	if (*src == '[') {
		src++;
		while (*src == '.') {
			src++;
		}
		if (CONF_SUCC == expect(src, "@")) {
			ret = BRANCH;
		}
		else if (is_alpha_number(src)) {
			ret = TRUNK;
		}
		else {
			return INVALID;
		}
		while (is_alpha_number(src)) {
			src++;
		}
		if (CONF_SUCC == expect(src, "]")) {
			return ret;
		}
		else {
			return INVALID;
		}
	}
	else if (is_alpha_number(src)) {
		while (is_alpha_number(src)) {
			src++;
		}
		if (CONF_SUCC != expect(src, ":")) {
			return INVALID;
		}
		if (CONF_SUCC == expect(src, "[")) {
			return ARRAY_ITEM;
		}
		else {
			return ITEM;
		}
	}
	else {
		return INVALID;
	}
};

int Configure::_parse() {
	_root = new conf_item;
	_root->set_key("root");
	_root->set_nodetype(ROOT);
	conf_item* pre_trunk_or_branch = _root;
	_layers.push_back(_root);

	char line[CONF_LINE_NUM];
	char* iter = line;
	while(get_next_line(line, CONF_LINE_NUM)) {
		iter = line;
		nodetype line_type = _check_type(iter);
		switch(line_type) {
			case INVALID:
				fprintf(stderr, "[parse] INVALID CONF LINE: %s\n", line);
				break;
			case TRUNK:
				fprintf(stderr, "[parse] TRUNK: %s\n", line);
				_parse_trunk(iter, pre_trunk_or_branch);
				break;
			case BRANCH:
				fprintf(stderr, "[parse] BRANCH: %s\n", line);
				_parse_branch(iter, pre_trunk_or_branch);
				break;
			case ITEM:
				fprintf(stderr, "[parse] ITEM: %s\n", line);
				_parse_item(iter, pre_trunk_or_branch);
				break;
			case ARRAY_ITEM:
				fprintf(stderr, "[parse] ARRAY_ITEM: %s\n", line);
				_parse_array_item(iter, pre_trunk_or_branch);
				break;
			default:
				fprintf(stderr, "[parse] fatal error occurs: %s\n", line);
				break;
		}
/*
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
*/
	}
};

int Configure::_get_layer(char*& src) {
	int ret = 0;
	while (*src == '.') {
		src++;
		ret++;
	}
};

conf_item* Configure::_get_father_node(int layer) {
	if (_layers.size() - 1 < layer) {
		return NULL;
	} 
	return _layers[layer];
};

int Configure::_set_father_node(int layer, conf_item* node) {
	if (NULL == node) {
		return CONF_ERROR;
	}
	if (_layers.size() - 1 < layer) {
		return CONF_ERROR;
	}
	_layers[layer + 1] = node;
}

int Configure::_parse_branch(char*& src, conf_item*& item) {
	expect(src, "[");
	int layer = _get_layer(src);	
	expect(src, "@");
	char token[CONF_LINE_NUM];
	get_token(src, token, CONF_LINE_NUM);
	conf_item* node = new conf_item(BRANCH);
	node->set_key(token);
	expect(src, "]");
	node->set_father(_get_father_node(layer));
	node->add_to_tree();
	_set_father_node(layer, node);
	item = node;
	if (*src == 0) {
		fprintf(stdout, "[build]key: %s, value: %s, father key: %s\n", 
			node->get_key().c_str(), node->get_value().c_str(), node->get_father()->get_key().c_str());
		return CONF_SUCC;
	}	
	return CONF_ERROR;
};

int Configure::_parse_trunk(char*& src, conf_item*& item) {
	expect(src, "[");
	int layer = _get_layer(src);	
	char token[CONF_LINE_NUM];
	get_token(src, token, CONF_LINE_NUM);
	conf_item* node = new conf_item(TRUNK);
	node->set_key(token);
	expect(src, "]");
	node->set_father(_get_father_node(layer));
	node->add_to_tree();
	_set_father_node(layer, node);
	item = node;
	if (*src == 0) {
		fprintf(stdout, "[build]key: %s, value: %s, father key: %s\n", 
			node->get_key().c_str(), node->get_value().c_str(), node->get_father()->get_key().c_str());
		return CONF_SUCC;
	}	
	return CONF_ERROR;
};

int Configure::_parse_item(char*& src, conf_item* item) {
	conf_item* node = new conf_item(ITEM);
	_parse_key(src, node);
	expect(src, ":");
	node->set_father(item);
	node->add_to_tree();
	_parse_value(src, node);
	if (*src == 0) {
		fprintf(stdout, "[build]key: %s, value: %s, father key: %s\n", 
			node->get_key().c_str(), node->get_value().c_str(), node->get_father()->get_key().c_str());
		return CONF_SUCC;
	}	
	return CONF_ERROR;
};

int Configure::_parse_array_item(char*& src, conf_item* item) {
	conf_item* node = new conf_item(ARRAY_ITEM);
	_parse_key(src, node);
	expect(src, ":");
	expect(src, "[");
	node->set_father(item);
	node->add_to_tree();
	_parse_array(src, node);
	if (*src == 0) {
		fprintf(stdout, "[build]key: %s, value: %s, father key: %s\n", 
			node->get_key().c_str(), node->get_value().c_str(), node->get_father()->get_key().c_str());
		return CONF_SUCC;
	}	
	return CONF_ERROR;
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
	char* next = src;
	if (*next == ' ' || *next == '\t') {
		next++;
	}
	int i = 0;
	int len = strlen(des);
	while (i < len && next[i] == des[i]) {
		i++;
		next++;
	}
	if (i != len) {
		return CONF_ERROR;
	}
	src = next;
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

