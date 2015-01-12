#ifndef ACCEPTER_H_
#define ACCEPTER_H_

#include <string.h>
#include <iostream>

#include "epoll_handler.h"
#include "reactor.h"
#include "sock.h"
#include "channel_pip_line.h"

template<typename HANDLER>
class accepter : public epoll_handler
{
public:
	int start(unsigned port);
	int start(unsigned int ip, unsigned int port);
	int handle_input();

private:
	unsigned int local_ip_;
	unsigned int listen_port_;
	channel_pip_line channel_;
};

template<typename HANDLER>
int accepter<HANDLER>::start(unsigned int port)
{
	return this->start(INADDR_ANY, port);
}

template<typename HANDLER>
int accepter<HANDLER>::start(unsigned int ip, unsigned int port)
{
	this->local_ip_ = ip;
	this->listen_port_ = port;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		return -1;
	this->sock(sock);
	if (sock::set_sockfd_reuseable(this->sock()) < 0)
		return -1;

	std::cout << "ok" << std::endl;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->listen_port_);
	addr.sin_addr.s_addr = htonl(this->local_ip_);

	if (::bind(this->sock(), (struct sockaddr*)&addr, sizeof(addr))  < 0)
		return -1;

	std::cout << "ok" << std::endl;
	if (listen(this->sock(), SOMAXCONN) < 0)
		return -1;
	std::cout << "ok" << std::endl;
	this->channel(new channel_pip_line);
	return reactor::instance()->add(this);
}

template<typename HANDLER>
int accepter<HANDLER>::handle_input()
{
    struct sockaddr_in remote_addr;
    socklen_t addr_len = sizeof(remote_addr);
    memset(&remote_addr, 0, addr_len);
    int sock = ::accept(this->sock(), 
                      (struct sockaddr*)&remote_addr, 
                      &addr_len);
    if (sock < 0)
		return -1;
	if(sock::set_noblock(sock) < 0)
	{
		close(sock);
		return -1;
	}
    HANDLER *hd = new HANDLER(sock, &remote_addr);
	hd->channel(this->channel());
	reactor::instance()->add(hd);
	return 0;
}


#endif
