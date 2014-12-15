#include "client_connector.h"

client_connector::client_connector(const char *ip, const int port)
: connector_(ip, port)
{
}

int client_connector::connect_server()
{
	int sock_fd = this->connector_.connect();
	if (sock_fd < 0)
		return -1;
	this->sock(sock_fd);
	return 0;
} 

int client_connector::handle_message(const int msg_id,
									 const char* msg,
									 const int len)
{
	std::cout << "msg_id : "
		<< msg_id << "msg_len" << len << std::endl;
	return 0;
}


