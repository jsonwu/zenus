#ifndef CLIENT_CONNECTOR_H_
#define CLIENT_CONNECTOR_H_

#include <string>
#include <iostream>

#include "client_handler.h"
#include "connector.h"
#include "my_timer.h"


class client_connector : public client_handler
{
public:
	client_connector(char *ip, unsigned int port);
	virtual  ~client_connector();

	virtual int handle_close();

	int connect_server();

	virtual int timer_time_out();

	virtual int timeout();

protected:
	virtual int handle_message(const int msg_id,
							   const char* msg,
							   const int len);
	int reconnect();
private:
	connector  connector_;
	my_timer<client_connector> s_timer_;
	my_timer<client_connector> heart_beat_timer_;
};

#endif
