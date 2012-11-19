/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: configure.cpp
 * date: 2012-11-19
 * desc: main function of configure
 ***********************************************************/

#include <stdio.h>

#include "tools.h"
#include "configure.h"

namespace configure {

Configure::Configure(const char* conf_file) {
	tools::ScopeFile sf(conf_file, "r");
	_fs = sf.get_ptr();
	if (NULL == _fs) {
		fprintf(stderr, "conf file open error\n");
	}
	root = NULL;
};

Configure::Configure(const std::string& conf_file) {
	tools::ScopeFile sf(conf_file.c_str(), "r");
	_fs = sf.get_ptr();
	if (NULL == _fs) {
		fprintf(stderr, "conf file open error\n");
	}
	root = NULL;
};

Configure::~Configure() {
	if (NULL != _fs) {
		fclose(_fs);
	}
	_fs = NULL;
	release(root);
};

int Configure::parse() {
	root = new conf_item;
	char line[1024];
	char token[1024];
	char* iter = line;
	while(NULL != fgets(line, 1024, _fs)) {
		iter = line;
		int ret = get_token(iter, token);
	}
};

int Configure::get_token(char* src, char* token) {
	while (*src == " " || *src == "\t") {
		src++;
	}
	if (*src == "\n") {
		return 0;
	}
};

int Configure::release(conf_item* conf_tree) {
	if (NULL == conf_tree) {
		return 0;
	}
	if (NULL != conf_tree->child) {
		release(conf_tree->child);
	}
	if (NULL != conf_tree->brother) {
		release(conf_tree->brother);
	}
	delete conf_tree;
	conf_tree = NULL;
};

};

