#ifndef KCRONTAB_TIMER_FD_H_
#define KCRONTAB_TIMER_FD_H_

#include <map>
#include "singleton.h"

class kcrontab_timer_fd : public singleton
{
public:
	kcrontab_timer_fd(int max_fd = 1024);
	~kcrontab_timer_fd();

	int init();

	int add_timer(timer &ptimer);

	int add_timer(timer &ptimer);

	int run();

	void stop_kcrontab()
	{ this->active_ = false; }

private:
	bool active_;
	int ep_fd_;
	int max_fd_;
	std::map<int, timer *> timer_map_;
};

#endif
