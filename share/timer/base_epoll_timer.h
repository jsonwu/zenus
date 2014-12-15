#ifndef BASE_EPOLL_TIMER_H_
#define BASE_EPOLL_TIMER_H_

class base_epoll_timer
{
public:
	int start(const int first_timeout,
			  const int time_interval,
			  const bool delete_self);
	int close();
	virtual int run() = 0;
	int get_timer_id();
	bool delete_self();
private:
	bool delete_self_;       // 是否在循环结束后由kcrontabel 删除
	int timer_id_;
};


#endif
