#include <iostream>
#include <unistd.h>

#include "time_cycle_log.h"

time_cycle_log::time_cycle_log(const char *file_name, int time_splite_type)
	:logger(file_name),
	 splite_type_(time_splite_type),
	 last_splite_value_(0)
{  }

bool time_cycle_log::if_log_new_file()
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	int value = 0;
	if (this->splite_type_ == LOG_NOT_NEW)
		return false;
	switch(this->splite_type_)
	{
	case LOG_MIN:
		value = t->tm_min;
		break;
	case LOG_HONOUR:
		value = t->tm_hour;
		break;
	case LOG_DAY:
		value = t->tm_mday;
		break;
	case LOG_MONTH:
		value = t->tm_mon;
		break;
	case LOG_YEAR:
		value = t->tm_year;
		break;
	default:
		break;
	}

	if (value == this->last_splite_value_)
		return false;
	this->last_splite_value_ = value;
	return true;
}

int time_cycle_log::start()
{
	if (this->open() < 0)
		return -1;

	//就是说如果不产生新文件 是不需要线程的
	if (this->splite_type_ == LOG_NOT_NEW) 
		return 0;

	if(this->lthread_.start(this))
		return -1;
	this->if_log_new_file();  //for set this->last_splite_value_;
	return 0;
}

int time_cycle_log::run()
{
	while(true)
	{
		if(this->if_log_new_file())
		{	
			this->close();
			this->open();
		}
		sleep(30);
	}
	return 0;
}

