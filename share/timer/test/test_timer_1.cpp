#include <iostream>
#include <unistd.h>

#include "timer.h"
#include "kcrontab_timer_thread.h"

#include "my_timer.h"
#include "kcrontab_timer_mgr.h"

using namespace std;

class test
{
public:
	int init()
	{
		te_timer_.init(this, &test::timeout);
		return kcrontab_timer_mgr::instance()->add_timer(&this->te_timer_, 1000, 5000, false);
	}
	int timeout()
	{
		cout << "out" << endl;
		return 0;
	}
private:
	my_timer<test> te_timer_;
};


int main()
{

	int rest = kcrontab_timer_mgr::instance()->init(500);
	if (rest < 0)
	{
		cout << "kcrontable init error" << endl;
		return -1;
	}
	test a;
	if(a.init() < 0)
	{
		cout << "timer init error" << endl;
		return -1;
	}

	while(1)
	{
		kcrontab_timer_mgr::instance()->update();
		cout << "sleep" << endl;
		sleep(1);
	}
}


//for test kcrontab_timer_mgr



//for test kcrontab_timer_thread
/*
class mail : public s_timer
{
public:
	mail(int first_time, int interval_time);
	virtual ~mail();

	int init(int k )
	{
		this->last_time_ = k;
		return 0;
	}
	virtual int time_out();
private:
	int  last_time_;
	int run_times_;
};

mail::mail(int first_time, int interval_time)
	: s_timer(first_time, interval_time, true),
	last_time_(0),
	run_times_(0)
{ }

mail::~mail()
{
	cout << "delete ok" << endl;
}


int mail::time_out()
{
	cout << "time out " << this->last_time_ << endl;
	this->run_times_ ++;
	if (this->run_times_ > 20)
		return -1;
	return 0;
}


int main()
{
	if (kcrontab_timer_thread::instance()->init() < 0)
	{
		cout << "krontable init error" << endl;
		return -1;
	}
	if (kcrontab_timer_thread::instance()->start() < 0)
	{
		cout <<  "krontable start error" << endl;
		return -1;
	}
	for (int i = 1; i < 5; ++i)
	{
		int ti = 0*i;
		mail *t = new mail(3000, ti);
		t->init(i);
		cout << "main mail timer start " << endl;
		if (t->start() < 0)
		{
			cout << "mail timer start error" << endl;	
			return -1;
		}
		cout << "main mail timer start " << endl;

		if (kcrontab_timer_thread::instance()->add_timer(t) < 0)
		{
			cout << "kcrontab_timer_fd add mail timer error " << endl;
			return -1;
		}
	}
	while(1)
	{
		sleep(60);
	}
	return 0;
}
*/
