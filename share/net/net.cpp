#include "net.h"
#include "epoll_handler_mgr.h"

int net::send(const int sock_id, bytebuff *buff)
{
	epoll_handler *handler = epoll_handler_mgr::instance()->find(sock_id);
	if (handler == NULL)
		return -1;
	return handler->send(buff);
}
