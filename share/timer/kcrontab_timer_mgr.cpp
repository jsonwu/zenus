#include <sys/epoll.h>
#include <iostream>
#include <stdio.h>

#include "kcrontab_timer_mgr.h"

using namespace std;

kcrontab_timer_mgr::kcrontab_timer_mgr():
	ep_fd_(-1),
	epoll_event_(NULL)
{ }

kcrontab_timer_mgr::~kcrontab_timer_mgr()
{
	if (this->epoll_event_)
	{
		delete this->epoll_event_;
		this->epoll_event_ = NULL;
	}

}

int kcrontab_timer_mgr::init(const int max_timer_num)
{
	this->epoll_event_ = new epoll_event[this->max_fd_num_];
	this->ep_fd_ = epoll_create(max_timer_num);
	if (this->ep_fd_ < 0)
		return -1;
	this->max_fd_num_ = max_timer_num;
	return 0;
}

int kcrontab_timer_mgr::add_timer(base_epoll_timer *ptimer, const int first_timeout, const int time_interval, bool delete_self)
{
	if (ptimer->start(first_timeout, time_interval, delete_self) < 0)
		return -1;

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

int kcrontab_timer_mgr::delete_timer(int timer_id)
{
	struct epoll_event ev;
	ev.data.fd = timer_id;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(this->ep_fd_, EPOLL_CTL_DEL, timer_id, &ev);
	if (ret < -1)
		return -1;
	return 0;
}

int kcrontab_timer_mgr::delete_timer(base_epoll_timer *ptimer)
{
	int timer_fd = ptimer->get_timer_id(); if (this->delete_timer(timer_fd))
		return -1;
	if (ptimer->delete_self())
		delete ptimer;
	return 0;
}

int kcrontab_timer_mgr::update()
{
	char buff[128];
	int num = epoll_wait(this->ep_fd_, (this->epoll_event_), this->max_fd_num_, 0);
	for (int i = 0; i < num; ++i)
	{
		base_epoll_timer *ptimer = (base_epoll_timer *)this->epoll_event_[i].data.ptr;
		while(::read(ptimer->get_timer_id(), buff, 128)>0);
		int err = ptimer->run();
		if (err < 0) {
			ptimer->close();
			this->delete_timer(ptimer);
		}
	}
	return 0;
}

