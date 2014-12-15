#ifndef MESSAGE_HANDLER_RUNNABLE_H_
#define MESSAGE_HANDLER_RUNNABLE_H_

#include "lrunnable.h"
#include "nolockqueue.h"
#include "db_date.h"
#include "mysqldb.h"

class message_handler_runnable : public lrunnable
{
public:
	message_handler_runnable(const int queue_size, mysqldb *db);
	int push_date(db_date *date);
	virtual int run();
private:
	nolockqueue<db_date> queue_;
	mysqldb *db_;
};

#endif
