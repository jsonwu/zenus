#ifndef CONNECTOR_H_
#define CONNECTOR_H_

#include <string>

class connector
{
public:
	connector();
	connector(const char *ip, unsigned int port);
	int connect(const char *ip, const unsigned int  port);
	int connect();
	int sock_fd();
private:
	int sock_fd_;
	unsigned int port_;
	std::string ip_;
};


#endif
