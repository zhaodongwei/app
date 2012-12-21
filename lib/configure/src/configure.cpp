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
#include "exception.h"

namespace configure {

Configure::Configure(const char* conf_file) {
	_init(conf_file);
};

Configure::Configure(const std::string& conf_file) {
	_init(conf_file.c_str());
};

Configure::~Configure() {
	_release(_root);
};

int Configure::_init(const char* conf_file) {
	_file.append(conf_file);
	_fs = fopen(conf_file, "r");
	if (NULL == _fs) {
		fprintf(stderr, "conf file open error\n");
		throw exception(NOT_EXIST, "%s", conf_file);
	}
	_root = NULL;
	_parse();
	if (NULL != _fs) {
		fclose(_fs);
	}
	_fs = NULL;
};

int Configure::reload() {
	_fs = fopen(_file.c_str(), "r");
	_release(_root);
	_root = NULL;
	if (NULL == _fs) {
		fprintf(stderr, "conf file open error\n");
		throw exception(NOT_EXIST, "%s", _file.c_str());
	}
	_layers.clear();
	_parse();
	if (NULL != _fs) {
		fclose(_fs);
	}
	_fs = NULL;
	return CONF_SUCC;
};

int Configure::save(const char* conf_file) {
/*
	FILE* new_fs = fopen(conf_file, "w");
	if (NULL == new_fs) {
		throw exception("save conf file %s fail", conf_file);
	}
*/
	FILE* new_fs = stdout;
	fprintf(new_fs, "#This is conf file generated by conf saver\n");
	fprintf(new_fs, "#You're free to rewrite it\n\n");
	_root->save(new_fs, 0);
	fclose(new_fs);
	return CONF_SUCC;
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
		int ret = CONF_SUCC;
		switch(line_type) {
			case INVALID:
				throw exception(UNEXPECTED, "invalid conf line: %s", line);
				break;
			case TRUNK:
				ret = _parse_trunk(iter, pre_trunk_or_branch);
				break;
			case BRANCH:
				ret = _parse_branch(iter, pre_trunk_or_branch);
				break;
			case ITEM:
				ret = _parse_item(iter, pre_trunk_or_branch);
				break;
			case ARRAY_ITEM:
				ret = _parse_array_item(iter, pre_trunk_or_branch);
				break;
			default:
				fprintf(stdout, "[parse] fatal error occurs: %s\n", line);
				break;
		}
		if (CONF_ERROR == ret) {
			//throw exception(UNEXPECTED, "unexpected conf contents: %s", line);
		}
	}
};

int Configure::_get_layer(char*& src) {
	int ret = 0;
	while (*src == '.') {
		src++;
		ret++;
	}
	return ret;
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
	if (_layers.size() - 1 == layer) {
		_layers.push_back(node);
	} 
	else {
		_layers[layer + 1] = node;
	}
	return CONF_SUCC;
};

int Configure::_parse_branch(char*& src, conf_item*& item) {
	expect(src, "[");
	int layer = _get_layer(src);	
	expect(src, "@");
	char token[CONF_LINE_NUM];
	get_token(src, token, CONF_LINE_NUM);
	conf_item* node = new conf_item(BRANCH);
	node->set_key(token);
	expect(src, "]");
	if (NULL == node->set_father(_get_father_node(layer))) {
		throw exception(UNEXPECTED, "unexpected layer of line: %s", src);
	}
	node->add_to_tree();
	_set_father_node(layer, node);
	item = node;
	if (*src == 0) {
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
	if (NULL == node->set_father(_get_father_node(layer))) {
		throw exception(UNEXPECTED, "unexpected layer of line: %s", src);
	}
	node->add_to_tree();
	_set_father_node(layer, node);
	item = node;
	if (*src == 0) {
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
	if (CONF_ERROR == _parse_array(src, node)) {
		throw exception(MISSING, "parse array error");
	}
	if (*src == 0) {
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
	char* tmp = src + strlen(src) - 1;
	while (*tmp == ' ' || *tmp == '\t') {
		tmp--;
	}
	if (*src == '\"' && *tmp == '\"') {
		*(tmp + 1) = 0;
		_regulate_value(token, src);
	}
	else {
		while (*src != 0 && *src != ' ' && *src != '\t' && *src != '\n') {
			token[ret++] = *src;
			src++;
		}
		token[ret] = 0;
	}
	item->set_value(token);
	item->set_nodetype(ITEM);
	return ret;
};

int Configure::_regulate_value(char* token, char* src) {
	if (NULL == token || NULL == src) {
		return CONF_ERROR;
	}
	expect(src, "\"");
	while (*src != 0 && *src != '\"') {
		if (*src == '\\') {
			expect(src, "\\");
			switch(*src) {
				case 't':
					*token = '\t';
					break;
				case 'n':
					*token = '\n';
					break;
				case 'r':
					*token = '\r';
					break;
				case '\\':
					*token = '\\';
					break;
				case '\"':
					*token = '\"';
					break;
				default:
					throw exception(UNEXPECTED, "unknown meaning of \"\\%c\"", *src);
			};
			token++;
			src++;
		}
		else {
			*token = *src;
			token++;
			src++;	
		}
	}
	*token = 0;
};

int Configure::_parse_array(char*& src, conf_item* item) {
	if (NULL == src || NULL == item) {
		return CONF_ERROR;
	}
	char token[CONF_LINE_NUM];
	int element_cnt = 0;
	while (get_token(src, token, CONF_LINE_NUM) > 0) {
		conf_item* tmp;
		if (0 == element_cnt) {
			tmp = item;
			tmp->set_value(token);
		}
		else {
			tmp = new conf_item(item->get_key().c_str(), token);
			tmp->set_father(item->get_father());
		}
		tmp->add_to_tree();
		tmp->set_nodetype(ARRAY_ITEM);
		expect(src, ",");
		element_cnt++;
	}
	if (element_cnt == 0 && CONF_SUCC == expect(src, "]")) {
		delete item;
		return CONF_SUCC;
	}
	if (element_cnt == 0 && CONF_SUCC != expect(src, "]")) {
		delete item;
		throw exception(UNEXPECTED, "invalid empty line of array");
	}
	if (*src == 0) {
		char tmp[CONF_LINE_NUM];
		if (true != get_next_line(tmp, CONF_LINE_NUM)) {
			throw exception(UNEXPECTED, "unexpected end of array");
		}
		char* iter = tmp;
		conf_item* next_item = new conf_item;
		next_item->set_key(item->get_key());
		next_item->set_father(item);
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
	while (ret && *line == '#') {
		if (NULL != fgets(line, length, _fs)) {
			ret = true;
		}
		else {
			ret = false;
		}
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
	if (false == ret || 0 == len) {
		return false;
	}

	if (line[len - 1] == '\n' || line[len -1] == '\r') {
		line[len - 1] = 0;
	}
	return true;
};

int Configure::_release(conf_item* conf_tree) {
	if (NULL == conf_tree) {
		return CONF_SUCC;
	}
	delete conf_tree;
	conf_tree = NULL;
	return CONF_SUCC;
};

conf_item& Configure::operator[](const char* item) {
	return (*_root)[item];
}
conf_item& Configure::operator[](int item) {
	return (*_root)[item];
};

conf_item& Configure::operator[](const std::string item) {
	return operator[](item.c_str());
};

int Configure::size() {
	return _root->size();
};

bool Configure::has_key(const char* key) {
	return _root->has_key(key);
};

bool Configure::has_key(const std::string& key) {
	return _root->has_key(key);
};

bool Configure::has_key(int key) {
	return _root->has_key(key);
};

};

