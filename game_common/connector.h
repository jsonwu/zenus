#ifdef  CONNECTOR_H_
#define CONNECTOR_H_

#include <string>
#include <iostream>

#include "client_handler.h"

class client_connector : public client_handler
{
public:
	connector(const char *ip, const int port);
	int connect_server();
protected:
	virtual int handle_message(const int msg_id,
							   const char* msg,
							   const int len)
	{
		std::cout << "msg_id : "
			msg_id << "msg_len" << len << std::endl;
		return 0;
	}
private:
	std::string str_ip_;
};

#endif
