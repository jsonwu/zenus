#include "epoll_connector.h"

int epoll_connector::start()
{
	this->epoll_worker_ = new epoll_worker();
	if (this->epoll_worker_->start() < 0)
	{
		delete this->epoll_worker_;
		this->epoll_worker_ = NULL;
		return -1;
	}
	return 0;
}

int epoll_connector::add(epoll_handler *handler)
{
	return this->epoll_worker_->dispatch(handler->sock(), handler);
}

int epoll_connector::del(const int sock)
{
	return this->epoll_worker_->remove(sock);
}
