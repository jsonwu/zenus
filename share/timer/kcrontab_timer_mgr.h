#ifndef KCRONTAB_TIMER_MGR_H_
#define KCRONTAB_TIMER_MGR_H_

#include <sys/epoll.h>
#include "singleton.h"
#include "base_epoll_timer.h"

class kcrontab_timer_mgr : public singleton<kcrontab_timer_mgr>
{
public:
	kcrontab_timer_mgr();
	~kcrontab_timer_mgr();

	int init(const int max_timer_num = 10000);

	int start();

	int add_timer(base_epoll_timer *ptimer,
				  const int first_time,
				  const int time_interval,
				  bool delete_sel);

	int delete_timer(int timer_fd);
	int delete_timer(base_epoll_timer *ptimer);

	int update();
private:
	int ep_fd_;
	int max_fd_num_;
	struct epoll_event *epoll_event_;   
};

#endif
