#ifndef REACTO_H_
#define REACTO_H_

#include <vector>

#include "singleton.h"
#include "epoll_worker.h"
#include "epoll_handler.h"

class reactor : public singleton<reactor>
{
public:
	int init(const int worker_thread_num);
	int add(epoll_handler *handler);
	int remove(const int sock);
private:
	std::vector<epoll_worker *> workers_;
};

#endif
