#include "epoll_handler_mgr.h"

epoll_handler_mgr::epoll_handler_mgr()
{
}

epoll_handler* epoll_handler_mgr::find(const int sock_id)
{
	handler_map_iter it = this->handler_map_.find(sock_id);
	if (it == this->handler_map_.end())
		return NULL;
	return (it->second);
}

int epoll_handler_mgr::insert(epoll_handler *handler)
{
	int sock_id = handler->sock();
	std::pair<handler_map_iter, bool> res = this->handler_map_.insert(std::pair<int, epoll_handler *>(sock_id, handler));
	if (res.second == false)
		return -1;
	return 0;
}

void epoll_handler_mgr::del(const int sock_id)
{
	this->handler_map_.erase(sock_id);
	return; 
}
