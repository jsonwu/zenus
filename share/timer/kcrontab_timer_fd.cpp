#include "kcrontab_timer_fd.h"

#include <sys/epoll.h>

kcrontab_timer_fd::kcrontab_timer_fd(int max_fd):
	active_(true),
	ep_fd_(-1),
	max_fd_(max_fd)
{ }

kcrontab_timer_fd::kcrontab_timer_fd()
{
}

int kcrontab_timer_fd::init()
{
	this->ep_fd_ = epoll_create(this->max_fd_);
	if (this->ep_fd_ < 0)
		return -1;
	return 0;
}

int kcrontab_timer_fd::add_timer(timer &ptimer)
{
	int timer_id = ptimer.get_timer_id(); 
	struct epoll_event ev;
	ev.data.fd = timer_id;
	ev.events = EPOLLIN | EPOLLOUT;
	int ret = epoll_ctl(this->ep_fd_, EPOLL_CTL_ADD, timer_id, &ev);
	if (ret == -1)
		return -1;
	return 0;
}

int kcrontab_timer_fd::delete_timer(timer_id)
{
	struct epoll_event ev;
	ev.data.fd = timer_id;
	ev.events = EPOLLIN | EPOLLOUT;
	int ret = epoll_ctl(this->ep_fd_, EPOLL_CTL_DEL, timer_id, &ev);
	if (ret == -1)
		return -1;
	return 0;
}

int kcrontab_timer_fd::run()
{
	struct epoll_event  events[this->max_fd_];
	while(this->active_)
	{
		int num = epoll_wait(this->ep_fd_, events, this->max_events_, -1);
		for (int i = 0; i < num; ++i)
		{
			timer *ptimer = (timer *)events[i].data.ptr;
			int err = ptimer->timeout();
			if (err < 0)
				this->delete_timer(timer->timer_id());
		}
	}
	return 0;
}

int kcrontab_timer_fd::stop_kcrontab()
{
	this->active_ = false;
}
