#ifndef DB_MSG_HANDLER_MGR_H_
#define DB_MSG_HANDLER_MGR_H_

#include <vector>

#include "singleton.h"
#include "db_date.h"
#include "message_handler_runnable.h"
#include "lthread.h"

class db_msg_handler_mgr : public singleton<db_msg_handler_mgr>
{
public:
	~db_msg_handler_mgr();
	int start(const int thread_num);
	int add(const int session_id, db_date *date);
private:
	int thread_num_;
	std::vector<message_handler_runnable *> runnable_vect_;
	std::vector<lthread *> thread_vect_;
};


#endif
