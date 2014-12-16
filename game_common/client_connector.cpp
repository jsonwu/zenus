#include <iostream>
#include "client_connector.h"
#include "reactor.h"
#include "kcrontab_timer_mgr.h"
#include "message_id_def.h"

client_connector::client_connector(char *ip, unsigned int port)
: connector_(ip, port)
{ }


client_connector::~client_connector()
{ }

int client_connector::handle_close()
{
	return 0;
}

int client_connector::connect_server()
{
	this->reconnect();
	this->s_timer_.init(this, &client_connector::timer_time_out);
	if (kcrontab_timer_mgr::instance()->add_timer(&this->s_timer_,
												  2000, 2000, false) < 0)
		return -1;

	this->heart_beat_timer_.init(this, &client_connector::timeout);
	if (kcrontab_timer_mgr::instance()->add_timer(&this->heart_beat_timer_,
												  1000, 1000, false) < 0)
		return -1;

	return 0;
}

int client_connector::reconnect()
{
	int sock_fd = this->connector_.connect();
	if (sock_fd < 0)
		return -1;
	this->sock(sock_fd);
	this->sock_status(SOCK_ACTIVE_);
	return reactor::instance()->add(this);
}

int client_connector::handle_message(const int msg_id,
									 const char* msg,
									 const int len)
{
	std::cout << "msg_id : "
		<< msg_id << "msg_len" << len << std::endl;
	return 0;
}

int client_connector::timer_time_out()
{
	if (this->sock_status() != SOCK_ACTIVE_)
		this->reconnect();
	std::cout << "in timeout " << std::endl;
	return 0;
}

int client_connector::timeout()
{
	if (this->send(HEART_BEAT, "aaaaa"))
	{
		std::cout << "send heart_beat error" << std::endl;
		return -0;
	}
	std::cout << "send heart_beat ok" << std::endl;
	return 0;
}
