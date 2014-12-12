#ifndef CLIETN_HANDLER_H_
#define CLIETN_HANDLER_H_

#include <string.h>
#include <iostream>
#include <errno.h>
#include <list>
#include "epoll_handler.h"

#define MAX_BUFF_SIZE 1024*1024
#define MSG_HEAD_LEN  8
#define MAX_ONE_MESSAGE_LEN 1024*50;

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

	virtual ~client_handler()
	{ }

	virtual int handle_input();

	virtual int handle_output();

	virtual void add_protoc_head(const char *buff_dest, const char *msg, const int len);

	int send(const int message_id, const char *message, const int len);
	int send(const int message_id, const std::string &message);

	int send_message(const char *msg, const int len);
protected:
	virtual int handle_buff_msg(); 

	virtual int handle_message(const int msg_id,
							   const char *message,
							   const int message_len);
private:

	int buff_messg_len();

	void move_buff_head();

	int check_one_message_ok();

	int buff_left();
private:
	int msg_id_;  //用于测试验证消息号
	char *head_;
	char *tail_;
	char buff_[MAX_BUFF_SIZE];
	std::list<std::string> sock_busy_message_list_;
};

#endif
