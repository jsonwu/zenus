#include <string.h>
#include <string>
#include <iostream>
#include "client_handler.h"
#include "sock.h"
#include "bytebuff_pool.h"

using namespace std;

client_handler::client_handler(int sock,
							   struct sockaddr_in* remote_addr)

:epoll_handler(sock, remote_addr)
{
	this->init();
}

client_handler::client_handler()
{
	this->init();
}

void client_handler::init()
{
	this->sock_status(SOCK_ACTIVE_);
	this->buff_ = bytebuff_pool::instance()->acquire(MAX_ONE_MESSAGE_LEN);
}

int client_handler::handle_input()
{
	char recv_buff[MAX_ONE_MESSAGE_LEN] = {0};
	int ret = 0;
	while (true) {
		int len = sock::recv_n_msg(this->sock(),
								   recv_buff, MAX_ONE_MESSAGE_LEN);
		if (len < 0)
		{
			this->sock_status(SOCK_ERROR_);
			std::cout << "recv error" << std::endl;
			ret = -1;
			break;
		}
		else if (len == 0)
		{
			break;
		}
		else
			this->buff_->write(recv_buff, len);

		this->channel()->hand_recv_msg(this, this->buff_);

		if (len == MAX_ONE_MESSAGE_LEN)
			continue;
		break;
	}
	return ret;
}

int client_handler::handle_output()
{
	int ret = 0;
	while (true)
	{
		if (this->sock_busy_message_list_.empty()) break;

		std::list<bytebuff *>::iterator iter =
			this->sock_busy_message_list_.begin();

		bytebuff *buff = *iter;
		ret = sock::send_n_msg(this->sock(),
							   buff->readable_buff(),
							   buff->data_len());

		if (ret > 0)
		{
			if (ret < buff->data_len())
			{
				buff->read_index(ret);
			}
			else
			{
				this->sock_busy_message_list_.pop_front();
				bytebuff_pool::instance()->release(buff);
			}
		}
		else if (ret < 0)
		{
			this->sock_status(SOCK_ERROR_);
			break;
		}
		else if (ret == 0)
			break;
	}
	return 0;
}

int client_handler::handle_close()
{
	delete this;
}

int client_handler::send(bytebuff *buff)
{
	this->channel()->hand_send_msg(this, buff);
	if (this->sock_busy_message_list_.empty())
	{
		std::cout << "int send" << std::endl;
		int ret = sock::send_n_msg(this->sock(), buff->readable_buff(), buff->data_len());
		if (ret >= 0)
		{
			if (ret == buff->data_len())
				bytebuff_pool::instance()->release(buff);
			else
			{
				buff->read_index(ret);
				this->sock_busy_message_list_.push_back(buff);
			}
		}else if (ret < 0)
		{
			std::cout << "send error" << std::endl;
			return -1;
		}
		std::cout << "int send ok" << std::endl;
		
	}else
	{
		this->sock_busy_message_list_.push_back(buff);
	}

	return 0;
}

/*
int client_handler::send(const int message_id, const char *message, const int len)
{
	char buff[MAX_ONE_MESSAGE_LEN] = {0};


	std::cout << "msg len " <<  len << *(int *)buff << std::endl;
	return this->send_message(buff, MSG_HEAD_LEN + len);
}

int client_handler::send(const int message_id, const string &message)
{
	std::cout << message <<  message.size() << std::endl;
	return this->send(message_id, message.c_str(), message.size());
}
*/
