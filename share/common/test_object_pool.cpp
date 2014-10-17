#include "object_pool.h"
#include <iostream>
#include <list>

using namespace std;

class test
{
public:
	test()
	{
		a = 12345;
		b = 23456;
	}
	void init()
	{
		a = 12345;
		b = 23456;
	}
	void uinit()
	{
		a = 0;
		b = 0;
	}
	void foo()
	{
		cout << "ok" << endl;
	}
	~test()
	{ }
	int a;
	int b;
};

int main()
{
	object_pool<test> pool;
	pool.init(10);
	list<test *> list_;
	int k = 0;
	while(true)
	{
		for (int j = 0; j < 100; ++j)
		{
			test *data = pool.alloc();
			//cout << data->a << " " << data->b << endl;
			list_.push_back(data);
		}
		list<test *>::iterator it =  list_.begin();
		for(; it != list_.end(); ++it)
		{
			pool.release(*it);
		}
		list_.clear();
		cout << k << endl;
		k++;
	}
	return 0;
}
