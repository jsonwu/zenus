#include <string.h>
#include <string>
#include <iostream>
#include "client_handler.h"
#include "sock.h"

using namespace std;

client_handler::client_handler(int sock,
							   struct sockaddr_in* remote_addr)

:epoll_handler(sock, remote_addr),
	sock_status_(SOCK_INIT_)
{
	this->init();
}

client_handler::client_handler()
{
	this->init();
}

void client_handler::init()
{
	this->msg_id_ = 1;
	this->head_ = this->buff_;
	this->tail_ = this->buff_;
	this->sock_status_ = SOCK_ACTIVE_;
}

int client_handler::handle_input()
{
	int ret = 0;
	while (true)
	{
		int len = sock::recv_n_msg(this->sock(),
								   this->head_,
								   MAX_ONE_MESSAGE_LEN);
		if (len < 0)
		{
			this->sock_status_ = SOCK_ERROR_;
			std::cout << "recv error" << std::endl;
			ret = -1;
			break;
		}
		else if (len == 0)
		{
			break;
		}
		else
			this->head_ += len;

		this->handle_buff_msg();
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
		if (this->sock_busy_message_list_.empty())
			break;

		std::list<std::string>::iterator iter =
			this->sock_busy_message_list_.begin();

		ret = sock::send_n_msg(this->sock(),
							   (*iter).c_str(),
							   (*iter).size());
		if (ret < 0)
		{
			this->sock_status_ = SOCK_ERROR_;
			break;
		}
		else if (ret == 0)
			break;
		else if (ret > 0 && (unsigned int)ret < (*iter).size())
		{
			std::string left_msg((*iter).begin() + ret,
								 (*iter).end());
			this->sock_busy_message_list_.pop_front();
			this->sock_busy_message_list_.push_front(left_msg);
			break;
		}else // ret == (*iter).size()
		{
			this->sock_busy_message_list_.pop_front();
		}
	}
	return 0;
}

int client_handler::handle_close()
{
	delete this;
}

void client_handler::add_protoc_head(int message_id,
									 char *buff_dest,
									 const char *msg,
									 const int len)
{
	int step = 0;
	*(int *)(buff_dest + step) = len;
	step += 4;
	*(int *)(buff_dest + step) = message_id;
	step += 4;
	strncpy((buff_dest + step), msg, len);
}

int client_handler::send(const int message_id, const char *message, const int len)
{
	char buff[MAX_ONE_MESSAGE_LEN] = {0};


	this->add_protoc_head(message_id, buff, message, len);
	std::cout << "msg len " <<  len << *(int *)buff << std::endl;
	return this->send_message(buff, MSG_HEAD_LEN + len);
}

int client_handler::send(const int message_id, const string &message)
{
	std::cout << message <<  message.size() << std::endl;
	return this->send(message_id, message.c_str(), message.size());
}


int client_handler::handle_buff_msg()
{
	while(true)
	{
		int one_message_len = this->check_one_message_ok();
		if (one_message_len < 0)
		{
			break;
		}
		int msg_id = *(int *)(this->tail_ + 4);
		this->handle_message(msg_id,
							 this->tail_ + MSG_HEAD_LEN,
							 one_message_len-MSG_HEAD_LEN);

		this->tail_ += one_message_len;
	}
	if ( this->buff_left()  < MAX_ONE_MESSAGE_LEN)
		this->move_buff_head();
	return 0;
}

int client_handler::handle_message(const int msg_id,
				   const char *message, 
				   const int message_len)
{

	if (msg_id != this->msg_id_)
		std::cout << "msg_id is eorror"
			<< this->msg_id_ << " " << msg_id << std::endl;
	this->msg_id_++;
	if (this->msg_id_ == 1024)
		this->msg_id_ = 1;
	return 0;
}


int client_handler::send_message(const char *msg,
								 const int len)
{
	if (this->sock_busy_message_list_.empty())
	{
		std::cout << "int send" << std::endl;
		int ret = sock::send_n_msg(this->sock(), msg, len);
		if (ret < 0)
		{
			std::cout << "send error" << std::endl;
			return -1;
		}
		else if (ret == 0)
			this->sock_busy_message_list_.push_back(std::string(msg, len));
		else if (ret > 0 && ret < len)
		{
			this->sock_busy_message_list_.push_back(std::string(msg+ret, len-ret));
		}
		std::cout << "int send ok" << std::endl;
		
	}else
	{
		this->sock_busy_message_list_.push_back(std::string(msg, len));
	}

	return 0;
}

int client_handler::buff_messg_len()
{
	return this->head_ - this->tail_;
}

void client_handler::move_buff_head()
{
	int len = this->buff_messg_len();
	memmove(this->buff_, this->tail_, len);
	this->tail_ = this->buff_;
	this->head_ = this->buff_ + len;
}

int client_handler::check_one_message_ok()
{
	int len = this->buff_messg_len();
	if (len < MSG_HEAD_LEN)
		return -1;
	int message_data_len = *(int *)this->tail_;
	if (len < message_data_len + MSG_HEAD_LEN)
		return -1;
	return message_data_len + MSG_HEAD_LEN;
}

int client_handler::buff_left()
{
	return this->buff_ + MAX_BUFF_SIZE - this->head_;
}

int client_handler::sock_status()
{
	return this->sock_status_;
}

void client_handler::sock_status(int sock_status)
{
	this->sock_status_ =  sock_status;
}
								 
