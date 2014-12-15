#ifndef EPOLL_CONNECTOR_H_
#define EPOLL_CONNECTOR_H_

#include "epoll_handler.h"
#include "epoll_worker.h"
#include "singleton.h"

class epoll_connector : public singleton<epoll_connector>
{
public:
	int start();
	int add(epoll_handler *handler);
	int del(const int scok);
private:
	epoll_worker *epoll_worker_;
};

#endif
