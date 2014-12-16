#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "connector.h"
#include "sock.h"

connector::connector()
	:ip_(0),
	port_(0)
{  }

connector::connector(char *ip, unsigned int port)
	:ip_(ip),
	port_(port)
{ }

int connector::connect(const char *ip, const unsigned int port)
{
	this->sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock_fd_ < 0)
		return -1;

	struct sockaddr_in s_add,c_add;
	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(ip);
	s_add.sin_port=htons(port);
	if(::connect(this->sock_fd_,
			   (struct sockaddr *)(&s_add),
			   (socklen_t)sizeof(struct sockaddr)) < 0)
		return -1;

	this->ip_ = ip;
	this->port_ = port;
	return this->sock_fd_;
}

int connector::connect()
{
	return this->connect(this->ip_.c_str(), this->port_);
}

int connector::sock_fd()
{
	return this->sock_fd_;
}
