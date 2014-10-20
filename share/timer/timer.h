#ifndef TIMER_H_
#define TIMER_H_

class s_timer
{
public:
	s_timer(int first_time, int time_interval, bool delete_self);
	virtual ~s_timer();
	virtual int time_out() = 0;
	int get_timer_id();
	int start();
	int stop();
	bool delete_self();
private:
	bool delete_self_;  // 是否在循环结束后由kcrontabel 删除
	int timer_id_;
	int first_timeout_time_; //毫秒
	int interval_;           //毫秒
};

#endif
