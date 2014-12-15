#include "reactor.h"
#include "epoll_handler.h"

int reactor::init(const int worker_thread_num)
{
  for (int i = 0; i < worker_thread_num; ++i)
  {
    epoll_worker *worker = new epoll_worker(true);
    if (worker->start() != 0)
      return -1;
   	this->workers_.push_back(worker);
  }
  return 0;
}

int reactor::add(epoll_handler *handler)
{
	int num =  handler->sock()%this->workers_.size();
	return this->workers_[num]->dispatch(handler->sock(), handler);
}

int reactor::remove(const int sock)
{
	int num =  sock%this->workers_.size();
	return this->workers_[num]->remove(sock);
}
