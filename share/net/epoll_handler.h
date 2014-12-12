#ifndef  EPOLL_HANDLER_H_
#define  EPOLL_HANDLER_H_

#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>


class epoll_handler
{
public:
	epoll_handler():
		sock_(-1),
		ip_(0),
		port_(0),
		timer_tm_((time_t)0),
		userarg_(NULL)
	{ }

	epoll_handler(int sock, struct sockaddr_in* remote_addr)
		:timer_tm_(0),
		userarg_(NULL)
	{
		this->sock_ = sock;
		this->ip_ = remote_addr->sin_addr.s_addr;
		this->port_ = remote_addr->sin_port;
	}
	virtual ~epoll_handler()
	{
		if (this->sock_ != -1)
			close(this->sock_);
		this->sock_ = -1;
	}
	virtual int handle_open()
	{ return 0; }

	virtual int handle_input()
	{ return -1; }
	virtual int handle_output()
	{ return -1; }
	virtual int handle_err()
	{ return -1; }
	virtual int handle_close()
	{ return -1; }
	virtual int handle_shutdown()
	{ return -1; }
	virtual int handle_run()
	{ return 0; }
	virtual int handle_timeout()
	{ return 0; }

public:
	inline void sock(int sk)
	{ this->sock_ = sk; }

	inline int sock()
	{ return this->sock_; } 
	inline  void ip(unsigned int ip)
	{ this->ip_ = ip; }

	inline unsigned int ip()
	{ return this->ip_; }

	inline unsigned int port()
	{ return this->port_; }

	inline  void port(unsigned short port)
	{ this->port_ = port; }

private:
	int sock_;
	unsigned int ip_;
	unsigned short port_;
	time_t timer_tm_;
	void *userarg_;
};

#endif
