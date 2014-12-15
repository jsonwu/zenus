#include <algorithm>
#include <iostream>
#include "delete_con_functor.h"
#include "db_msg_handler_mgr.h"
#include "mysql_mgr.h"
#include "message_handler_runnable.h"

using namespace std;

db_msg_handler_mgr::~db_msg_handler_mgr()
{
	for_each(this->runnable_vect_.begin(), this->runnable_vect_.end(), delete_con_functor());

	for_each(this->thread_vect_.begin(), this->thread_vect_.end(), delete_con_functor());
}

int db_msg_handler_mgr::start(const int thread_num)
{
	if (thread_num < 0)
		return -1;

	this->thread_num_  = thread_num;
	this->thread_vect_.reserve(thread_num);
	this->runnable_vect_.reserve(thread_num);

	for (int i = 0; i < thread_num; ++i)
	{
		lthread *handler_thread = new lthread;
		mysqldb *db = mysql_mgr::instance()->get_sqldb(i);
		if (db == NULL)
			goto error;
		message_handler_runnable *runnable = new message_handler_runnable(100, db);
		if (handler_thread->start(runnable) < 0)
			goto error;
		this->runnable_vect_.push_back(runnable);
		this->thread_vect_.push_back(handler_thread); 
	}
	std::cout << this->runnable_vect_.size() << std::endl;
	return 0;
error:
	this->~db_msg_handler_mgr();
	return -1;
}

int db_msg_handler_mgr::add(const int session_id, db_date *date)
{
	int id = session_id%this->thread_num_;
	std::cout <<  id << std::endl; 
	message_handler_runnable *handler = this->runnable_vect_[id];
	handler->push_date(date);
	return 0;
}
