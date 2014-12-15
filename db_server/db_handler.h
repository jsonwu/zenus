#ifndef DB_HANDLER_H_
#define DB_HANDLER_H_

#include "client_handler.h"


class db_handler : public client_handler
{
public:
	db_handler(int sock, struct sockaddr_in* remote_addr);
	virtual ~db_handler()
	{ }
private:
	virtual int handle_message(const int msg_id,
						   const char *message,
						   const int message_len);

};


#endif
