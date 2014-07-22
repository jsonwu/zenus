#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <iostream>

#include "epoll_worker.h"

epoll_worker::epoll_worker(bool edge_trigger):
	edge_trigger_(edge_trigger),
	work_stop_(true),
	epoll_fd_(-1),
	max_events_(0),
	events_(NULL)
{ }

epoll_worker::~epoll_worker()
{ }

int epoll_worker::start()
{
	if(pthread_rwlock_init(&this->rwlock_, NULL) != 0)
		return -1;

	this->epoll_fd_ = epoll_create(1024);
	if (this->epoll_fd_ == -1)
		return -1;
	work_stop_ = false;
	this->max_events_ = this->get_max_events();
	if (this->max_events_ <= 0)
		return -1;

	if(pthread_create(&this->thread_worker_id_,
					  NULL,
					  this->work_thread,
					  this) != 0)
	{
		this->work_stop_ = true;
		return -1;
	}
	return 0;
}

int epoll_worker::stop(void)
{
	if (this->work_stop_)
		return -1;
	this->work_stop_ = true;
	return 0;
}

int epoll_worker::dispatch(const int sock, epoll_handler *hd)
{
	if (hd->handle_open() != 0)
		return -1;

	pthread_rwlock_wrlock(&this->rwlock_);
	int ret = 0;
	if (this->handlers_.find(sock) == this->handlers_.end()) 
	{
		struct epoll_event evt;
		evt.events = EPOLLIN | EPOLLOUT | EPOLLERR;
		if (this->edge_trigger_)
			evt.events |= EPOLLET;
		evt.data.ptr = (void *)hd;

		if(epoll_ctl (this->epoll_fd_, EPOLL_CTL_ADD, sock, &evt) == -1)
			ret = -1;
		else
			this->handlers_.insert(std::make_pair<int, epoll_handler*>(sock, hd));
	}
	else
	{
		ret = -1;
	}
	pthread_rwlock_unlock(&this->rwlock_);

	return ret;
}

void* epoll_worker::work_thread(void *arg)
{
	epoll_worker *worker = (epoll_worker *)arg;
	worker->events_ = new epoll_event[worker->max_events_];

	while(!worker->work_stop_)
	{
		int num = epoll_wait(worker->epoll_fd_, worker->events_, worker->max_events_, -1);
		for (int i = 0; i < num; ++i)
		{
			int err = 0;
			epoll_handler *hd = (epoll_handler*)worker->events_[i].data.ptr;
			int event_flag = worker->events_[i].events;
			if (event_flag & EPOLLIN)
				err |= hd->handle_input();

			if (event_flag & EPOLLOUT)
				err |= hd->handle_output();

			if (event_flag & EPOLLERR)
				err |= hd->handle_err(); 

			if (err != 0)
				worker->remove(hd->sock());
		}
		//worker->run_handlers();
	}
	delete []worker->events_;
	return 0;
}

void epoll_worker::remove(const int sock)
{
	pthread_rwlock_wrlock(&this->rwlock_);
	std::map<int, epoll_handler*>::iterator itor = this->handlers_.find(sock);
	if (itor != this->handlers_.end())
	{
		itor->second->handle_close();
		delete itor->second;
		this->handlers_.erase(sock);
	}

	struct epoll_event ev_del;
	ev_del.data.fd = sock;
	epoll_ctl(this->epoll_fd_, EPOLL_CTL_DEL, sock, &ev_del);
	pthread_rwlock_unlock(&this->rwlock_);
	return ;
}

void epoll_worker::run_handlers()
{
	return ;
}

int epoll_worker::get_max_events()
{
	struct rlimit rl;
	memset((void *)&rl, 0, sizeof(rl));
	int r = ::getrlimit(RLIMIT_NOFILE, &rl);
	if (r != 0
		|| rl.rlim_cur == RLIM_INFINITY
		|| rl.rlim_cur <= 0)
		return -1;
	return rl.rlim_cur;
}
