#include <iostream>

#include "db_handler.h"
#include "db_date.h"
#include "object_pool.h"
#include "db_msg_handler_mgr.h"
#include "message_id_def.h"

db_handler::db_handler(int sock, struct sockaddr_in* remote_addr)
	:client_handler(sock, remote_addr)
{ }

int db_handler::handle_message(const int msg_id,
				   const char *message,
				   const int message_len)
{
	std::cout <<  "msg id " << msg_id << std::endl;
	if (msg_id == HEART_BEAT)
	{
		std::cout << "recv herat beat " << std::endl;
		return 0;
	}

	int session_id = *(int *)message;
	db_date *date = object_pool<db_date>::instance()->alloc();
	date->message_id_ = msg_id;
	date->handler_ = this;
	date->msg_.append(message, message_len);

	db_msg_handler_mgr::instance()->add(session_id, date);

	return 0;
}
