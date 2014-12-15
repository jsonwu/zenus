#include <unistd.h>
#include <iostream>
#include <stdlib.h>

#include "message_handler_runnable.h"
#include "mysqldb.h"
#include "tb_map_mgr.h"
#include "object_pool.h"


message_handler_runnable::message_handler_runnable(const int queue_size, mysqldb *db)
	: db_(db)
{
	this->queue_.init(queue_size);
}


int message_handler_runnable::push_date(db_date *date)
{
	if(!this->queue_.push(date))
		return -1;
	return 0;
}

int message_handler_runnable::run()
{
	while(1)
	{
		db_date *date = this->queue_.pop();
		if (date == NULL)
		{
			usleep(3000);
		}	
		else
		{
			date->db_ =  this->db_;
			tb_map_mgr::instance()->call(date->message_id_,
										 date);
			object_pool<db_date>::instance()->release(date);
		}
	}
	return 0;
}


