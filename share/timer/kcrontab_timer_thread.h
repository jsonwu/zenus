#ifndef KCRONTAB_TIMER_THREAD_H_
#define KCRONTAB_TIMER_THREAD_H_

#include <map>
#include "singleton.h"
#include "lrunnable.h"
#include "timer.h"
#include "lthread.h"

class kcrontab_timer_thread : public singleton<kcrontab_timer_thread>,
   lrunnable
{
public:
	kcrontab_timer_thread(int max_fd = 1024);
	~kcrontab_timer_thread();

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
