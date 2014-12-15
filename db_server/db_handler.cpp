#include "db_handler.h"
#include "db_date.h"
#include "object_pool.h"
#include "db_msg_handler_mgr.h"

db_handler::db_handler(int sock, struct sockaddr_in* remote_addr)
	:client_handler(sock, remote_addr)
{ }

int db_handler::handle_message(const int msg_id,
				   const char *message,
				   const int message_len)
{
	int session_id = *(int *)message;
	db_date *date = object_pool<db_date>::instance()->alloc();
	date->message_id_ = msg_id;
	date->handler_ = this;
	date->msg_.append(message, message_len);

	db_msg_handler_mgr::instance()->add(session_id, date);

	return 0;
}
