#ifndef TEST_HANDLER_H_
#define TEST_HANDLER_H_

#include <iostream>
#include <errno.h>
#include <list>
#include "epoll_handler.h"

class base_client : public epoll_handler
{
public:
	test_handler(int sock_fd, struct sockaddr_in *remote_addr)
		: epoll_handler(sock_fd, remote_addr)
	{ }

	virtual int handle_input()
	{
		std::cout << "handle input " << endl;
		char data[1024];
		int ret = this->recv(data, sizeof(data), 0);
		if (ret <= 0)
		{
			if (errno == EINTR || errno == EAGAIN)
				return 0;
			else
			{
				std::cout << "handle input : read error" << std::endl;
				return -1;
			}
		}
		if (ret >= 0)
			std::cout << data << ret << std::endl;
		return 0;
	}
	virtual int handle_output()
	{
		std::cout << "handle output" << std::endl;
		char data[] = "sssss";
		int ret = this->send(data, strlen(data), 0);
		return 0;
	}
	virtual int handle_err()
	{
		std::cout << "handle error" << std::endl;
		char data[] = "sssss";
		return -1;
	}
	virtual int handle_close()
	{
		std::cout << "handle close" << endl;
		return -1;
	}
private:
	list<>
};

#endif
