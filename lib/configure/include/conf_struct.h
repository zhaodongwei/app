/***********************************************************
 * Copyright: zhaodongwei@nanjing university
 * author: zhaodongwei(joodaw@gmail.com)
 * 
 * file: conf_struct.h
 * date: 2012-11-18
 * desc: conf struct declare
 ***********************************************************/

#ifndef _CONF_STRUCT_H_
#define _CONF_STRUCT_H_

#include <stdio.h>
#include <list>
#include <string>

namespace configure {

class ConfStruct {
public:
	ConfStruct();
	ConfStruct(const char* key, const char* value);
	ConfStruct(const std::string& key, const std::string& value);
	~ConfStruct();
	//ConfStruct* operater[](int iter);
	//ConfStruct* operater[](const char* iter);

	std::string get_key() const {
		return _key;
	};
	void set_key(const char* key_in) {
		_key.clear();
		_key.append(key_in);
	}

	std::string get_value() const {
		return _value;
	};
	void set_value(const char* value_in) {
		_value.clear();
		_value.append(value_in);
	}
	
	ConfStruct* get_child() const {
		return _child;
	};
	void set_child(ConfStruct* p_child) {
		_child = p_child;
	};

	ConfStruct* get_brother() const {
		return _brother;
	};
	void set_brother(ConfStruct* p_brother) {
		_brother = p_brother;
	};

	ConfStruct* get_father() const {
		return _father;
	};
	void set_father(ConfStruct* p_father) {
		_father = p_father;
	};

	bool add_to_tree();
	ConfStruct* get_last_child() const;
	
	int to_int();
	double to_double();
	std::string to_string();
	const char* to_cstr();

	ConfStruct& operator[](const char*);

private:
	std::string _key;
	std::string _value;
	int _value_num;
	int _value_icnt;
	ConfStruct* _child;
	ConfStruct* _brother;
	ConfStruct* _father;
	
	bool _is_number(char letter) {
		if (letter >= '0' && letter <= '9') {
			return true;
		}
		return false;
	};
	double _get_number(std::string& str, int& iter);
	double _parse_number();
};

typedef ConfStruct conf_item;

};

#endif //#ifndef _CONF_STRUCT_H_

