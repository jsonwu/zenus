#ifndef KCRONTAB_TIMER_FD_H_
#define KCRONTAB_TIMER_FD_H_

#include <map>
#include "singleton.h"
#include "lrunnable.h"
#include "timer.h"
#include "lthread.h"

class kcrontab_timer_fd : public singleton<kcrontab_timer_fd>,
   lrunnable
{
public:
	kcrontab_timer_fd(int max_fd = 1024);
	~kcrontab_timer_fd();

	int init();

	int start();

	int add_timer(s_timer *ptimer);

	int delete_timer(int timer_fd);
	int delete_timer(s_timer *ptimer);
	virtual int run();

	void stop_kcrontab();


private:
	bool active_;
	int ep_fd_;
	int max_fd_num_;
	lthread  timer_thread_;
	std::map<int, s_timer *> timer_map_;
};

#endif
