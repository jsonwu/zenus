#ifndef MY_TIMER_H_
#define MY_TIMER_H_

#include <sys/timerfd.h>
#include <unistd.h>

#include "base_epoll_timer.h"
#include "sock.h"

template<typename T>
class my_timer :  public base_epoll_timer
{
public:
	typedef int (T::*fun)();
	my_timer()
	{  }
	~my_timer()
	{  }
	int init(T *type, fun mem_fun)
	{
		this->t_mem_ = type;
		this->t_mem_func_ =  mem_fun;
		return 0;
	}
	int run()
	{
		if (this->t_mem_ != NULL && this->t_mem_func_ != NULL)
			return (this->t_mem_->*this->t_mem_func_)();
		return 0;
	}
private:
	T *t_mem_;
	fun t_mem_func_; 
};

#endif
