#include <iostream>
#include "client.h"
#include "login.h"
#include "message_id_def.h"


static const int MAX_ONE_MESSAGE_lEN = 1024;
static const int MESSAGE_HEAD_LEN =  12;
static const int MESSAGE_DATA_LEN = 1000;

int client::handle_message(const int msg_id,
						   const char *msg,
						   const int len)
{
	int ret = 0;
	int msg_type = msg_id/1000;
	switch(msg_type)	
	{
	case LOGIN:
		ret = login::instance()->process_msg(this, msg_id, msg, len);
		break;
	default:
		std::cout << "unknow msg in client" << std::endl;
		break;
	}
	return  ret;
}

int client::send_errno(const int msg_id, const int err_id)
{
	return this->send_msg_impl(msg_id, NULL, 0, 0);
}

int client::send_client_msg(const int msg_id, const char *msg, const int len)
{
	return this->send_msg_impl(msg_id, msg, len, 0);
}


int client::send_msg_impl(const int msg_id, const char *msg, const int len, const int ernno)
{
	char  send_buf[MAX_ONE_MESSAGE_lEN]  = {0};
	int cur = 0;

	*(int *)(msg+cur) = msg_id;
	cur += 4;
	*(int *)(msg+cur) = errno;
	cur += 4;
	*(int *)(msg+cur) = len;

	if (msg != NULL)
		memcpy(send_buf+MESSAGE_HEAD_LEN, msg, len);
	this->send_message(send_buf, MESSAGE_HEAD_LEN+len);
	return 0;
}
