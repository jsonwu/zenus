#ifndef LOGITEM_H_
#define LOGITEM_H_

#include <string>
#include <time.h>
#include "level.h"

using namespace std;

class logitem
{
public:
	logitem(level lvl, char *msg)
		:lvl_(lvl),
		msg_(msg)
	{ this->time_ = ::time(NULL); }

	~logitem()
	{ }
 
	string& msg()
	{ return this->msg_; }

	time_t time()
	{ return this->time_; }

	string strtime()
	{
		struct tm *tm = localtime(&(this->time_));
		char buff[128] = {0};
		strftime(buff, 127, "%F:%T",  tm);
		return string(buff);
	}

	level_value lvl_value()
	{ return this->lvl_.get_value(); }

	string& lvl_name()
	{ return this->lvl_.get_name(); }

private:
	time_t time_;
	level  lvl_;
	string msg_;
};
#endif 
