#include <sys/timerfd.h>
#include <unistd.h>

#include "sock.h"
#include "base_epoll_timer.h"

int base_epoll_timer::start(const int first_timeout,
						   const int time_interval,
						   bool delete_self)
{
	if (first_timeout < 0 || time_interval < 0)
		return -1;
	this->timer_id_ = timerfd_create(CLOCK_REALTIME, 0);
	if (this->timer_id_ < 0)
		return -1;

	if (sock::set_noblock(this->timer_id_) < 0)
		return -1;

	int first_time_sec = first_timeout/1000;
	int first_time_nsec = (first_timeout%1000)*1000000;

	struct itimerspec ptimer = {0};
	ptimer.it_value.tv_sec = first_time_sec;
	ptimer.it_value.tv_nsec = first_time_nsec;

	int time_interval_sec = time_interval/1000;
	int time_interval_nsec = (time_interval%1000)*1000000;
	ptimer.it_interval.tv_sec = time_interval_sec;
	ptimer.it_interval.tv_nsec = time_interval_nsec;
	//cout << time_interval_sec << "    " << time_interval_nsec << endl;

	int ret = timerfd_settime(this->timer_id_, 0, &ptimer, NULL);
	return ret;
}

int base_epoll_timer::get_timer_id()
{
	return this->timer_id_;
}

bool base_epoll_timer::delete_self()
{
	return this->delete_self_;
}

int base_epoll_timer::close()
{
	return ::close(this->timer_id_);
}
