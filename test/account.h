#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
#include <vector>
#include <algorithm>

#include "delete_con_functor.h"

class char_base_info
{
public:
	int char_id_;
	int char_type_;
	int lvl_;
};

class account_info
{
public:
	account_info()
		:current_char_id_(-1)
	{ }
	~account_info()
	{
		for_each(this->char_vect_.begin(),
				 this->char_vect_.end(),
				 delete_con_functor());
	}
	std::string account_;
	std::string key_;
	std::vector<account_info *> char_vect_;
	int current_char_id_;
};


#endif
