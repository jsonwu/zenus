#include <sys/epoll.h>
#include <iostream>
#include <stdio.h>

#include "kcrontab_timer_fd.h"

using namespace std;

kcrontab_timer_fd::kcrontab_timer_fd(int max_fd_num):
	active_(true),
	ep_fd_(-1),
	max_fd_num_(max_fd_num)
{ }

kcrontab_timer_fd::~kcrontab_timer_fd()
{
}

int kcrontab_timer_fd::init()
{
	this->ep_fd_ = epoll_create(this->max_fd_num_);
	if (this->ep_fd_ < 0)
		return -1;
	return 0;
}

int kcrontab_timer_fd::start()
{
	return this->timer_thread_.start(this);
}

int kcrontab_timer_fd::add_timer(s_timer *ptimer)
{
	int timer_id = ptimer->get_timer_id(); 
	struct epoll_event ev;
	ev.data.fd = timer_id;
	ev.data.ptr = (void *)ptimer;
	ev.events = EPOLLIN | EPOLLET;

	int ret = epoll_ctl(this->ep_fd_, EPOLL_CTL_ADD, timer_id, &ev);
	if (ret == -1)
		return -1;
	return 0;
}

int kcrontab_timer_fd::delete_timer(int timer_id)
{
	struct epoll_event ev;
	ev.data.fd = timer_id;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(this->ep_fd_, EPOLL_CTL_DEL, timer_id, &ev);
	if (ret < -1)
		return -1;
	return 0;
}

int kcrontab_timer_fd::delete_timer(s_timer *ptimer)
{
	int timer_fd = ptimer->get_timer_id();
	if (this->delete_timer(timer_fd))
		return -1;
	if (ptimer->delete_self())
		delete ptimer;
	return 0;
}

int kcrontab_timer_fd::run()
{
	struct epoll_event  events[this->max_fd_num_];
	char buff[128];
	while(this->active_)
	{
		int num = epoll_wait(this->ep_fd_, events, this->max_fd_num_, -1);
		for (int i = 0; i < num; ++i)
		{
			s_timer *ptimer = (s_timer *)events[i].data.ptr;
			while(::read(ptimer->get_timer_id(), buff, 128)>0);
			cout << buff << endl;
			int err = ptimer->time_out();
			if (err < 0) {
				ptimer->stop();
				this->delete_timer(ptimer);
			}
		}
	}
	return 0;
}

void kcrontab_timer_fd::stop_kcrontab()
{
	this->active_ = false;
}
