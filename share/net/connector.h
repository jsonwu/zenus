#ifdef  CONNECTOR_H_
#define CONNECTOR_H_

#include <string>
#include <iostream>

#include "epoll_handler.h"

class connector : public epoll_handler
{
public:
	connector(const char *ip, const int port)
		: str_ip_(ip)
	{
		this->ip(inet_addr(this->str_ip_.c_str()));
		this->port(port);
	}
	int connect_server()
	{
		int connect_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (connect_fd == -1)
		{
			std::cout << "connector:: socket error" << std::endl;
			return -1;
		}
		this->sock(connect_fd);


		struct sockaddr_in server_addr;
		bzero(&server_addr, sizeof(struct sockaddr_in));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = this->ip();
		server_addr.sin_port = htons(this->port());
		if (connect(connect_fd,
					(struct sockaddr *)(&server_addr),
					sizeof(struct sockaddr)) == -1)
		{
			std::cout << "connector:: connect error " 
				<< " ip : "<< this->str_ip_
				<< " port : " << this->port() << std::endl;
			return -1;
		}
		return this->connect_fd_;
	}
private:
	std::string str_ip_;
};

#endif
