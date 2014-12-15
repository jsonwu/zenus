#ifndef  CLIENT_CONNECTOR_H_
#define CLIENT_CONNECTOR_H_

#include <string>
#include <iostream>

#include "client_handler.h"
#include "connector.h"
#include "my_timer.h"


class client_connector : public client_handler
{
public:
	client_connector(const char *ip, const int port);
	int connect_server();

	virtual int timer_time_out();

	virtual int timeout();
protected:
	virtual int handle_message(const int msg_id,
							   const char* msg,
							   const int len);
private:
	connector  connector_;
	my_timer<client_connector>

};

#endif
