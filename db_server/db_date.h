#ifndef DB_DATE_H_
#define DB_DATE_H_

#include <string>
#include "db_handler.h"
#include "mysqldb.h"

class db_date
{
public:
	void init()
	{
		this->handler_ = NULL;
		this->db_ = NULL;
		this->msg_.clear();
		this->message_id_ = 0;
	}
	void uinit()
	{
		this->handler_ = NULL;
		this->db_ = NULL;
		this->msg_.clear();
		this->message_id_ = 0;
	}
public:
	std::string msg_; 
	db_handler *handler_; 
	mysqldb *db_;
	int message_id_;
};

#endif
