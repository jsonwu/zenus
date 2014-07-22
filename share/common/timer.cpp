#include "timer.h"

#include <timerfd.h>
#include <unistd.h>

timer::timer(const int first_time, const int time_interval)
	: repeat_(true)
	first_timeout_time_(first_time),
	interval_(time_interval)
{
	this->timer_id_ = timerfd_create(CLOCK_REALTIME, 0);
	if (this->interval_ == 0)
		this->repeat_ = false;
}

int timer::get_timer_id()
{
	return this->timer_id_;
}

int timer::start()
{
	if (this->timer_id_ < 0)
		return -1;

	int first_time_sec = this->first_timeout_time_/1000;
	int first_time_nsec = (this->first_time_sec%1000)*1000000;

	int time_interval_sec = this->interval_/1000;
	int time_interval_nsec = (this->interval_%1000)*1000000;

	struct itimerspec ptimer = {0};
	ptimer.it_valude.tv_sec = first_time_sec;
	ptimer.it_valude.tv_nsec = first_time_nsec;

	if (this->repeat_)
	{
		ptimer.it_interval.tv_sec = time_interval_sec;
		ptimer.it_interval.tv_nsec = time_interval_nsec;
	}
	int ret = timerfd_settime(this->timer_id_, 0, &ptimer, NULL);
	return ret;
}

int timer::stop()
{
	return close(this->timer_id_);
}
