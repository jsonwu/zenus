#include <iostream>
#include <sys/timerfd.h>
#include <unistd.h>
#include "timer.h"
#include "sock.h"

using namespace std;

s_timer::s_timer(int first_time,
				 int time_interval,
				 bool delete_self)
	: delete_self_(true),
	first_timeout_time_(first_time),
	interval_(time_interval)
{
}

s_timer::~s_timer()
{ }

int s_timer::get_timer_id()
{
	return this->timer_id_;
}

int s_timer::start()
{
	this->timer_id_ = timerfd_create(CLOCK_REALTIME, 0);
	if (this->timer_id_ < 0)
		return -1;

	if (sock::set_noblock(this->timer_id_))
		return -1;

	if (this->timer_id_ < 0)
		return -1; 

	int first_time_sec = this->first_timeout_time_/1000;
	int first_time_nsec = (this->first_timeout_time_%1000)*1000000;

	struct itimerspec ptimer = {0};
	ptimer.it_value.tv_sec = first_time_sec;
	ptimer.it_value.tv_nsec = first_time_nsec;


	int time_interval_sec = this->interval_/1000;
	int time_interval_nsec = (this->interval_%1000)*1000000;
	ptimer.it_interval.tv_sec = time_interval_sec;
	ptimer.it_interval.tv_nsec = time_interval_nsec;
	//cout << time_interval_sec << "    " << time_interval_nsec << endl;

	int ret = timerfd_settime(this->timer_id_, 0, &ptimer, NULL);
	return ret;
}

int s_timer::stop()
{
	return close(this->timer_id_);
}

bool s_timer::delete_self()
{ return this->delete_self_; }
