#ifndef TIMER_H_
#define TIMER_H_

class timer
{
public:
	timer();
	~timer();
	virtual int time_out();
	int get_timer_id();

private:
	bool repeat_;
	int timer_id_;
	int first_timeout_time_; //毫秒
	int interval_;           //毫秒
};

#endif
