#ifndef CLIETN_HANDLER_H_
#define CLIETN_HANDLER_H_

#include <string.h>
#include <iostream>
#include <errno.h>
#include <list>
#include "epoll_handler.h"
#include "bytebuff.h"

#define MAX_BUFF_SIZE 1024*1024
#define MSG_HEAD_LEN  8
#define MAX_ONE_MESSAGE_LEN 1024*50

enum
{
	SOCK_INIT_ = 0,
	SOCK_ACTIVE_,
	SOCK_RESET_BY_PEER_,
	SOCK_ERROR_
};

class client_handler : public epoll_handler
{
public:
	client_handler(int sock, struct sockaddr_in* remote_addr);
client_handler();

	virtual ~client_handler()
	{ }

	void init();
	virtual int handle_input(); 
	virtual int handle_output();

	virtual int handle_close();

	virtual int send(bytebuff *buff);
	/*
	int send(const int message_id, const char *message, const int len);
	int send(const int message_id, const std::string &message);
	*/

private:
	bytebuff *buff_;
	std::list<bytebuff *> sock_busy_message_list_;
};

#endif
