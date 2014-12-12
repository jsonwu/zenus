#ifndef EPOLL_SOCK_H_
#define EPOLL_SOCK_H_

#include <time.h>

class epoll_sock
{
public:
	int handle_input();

	int handle_output();

	virtual int handle_open()
	{ return 0; }

	virtual int handle_err()
	{ return -1; }
	virtual int handle_close()
	{ return -1; }
	virtual int handle_shutdown()
	{ }
	int handle_run()
	{
		return 0;
	}
	virtual int handle_timeout()
	{
	}

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
