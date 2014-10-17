#include"nolockqueue.h"

#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;
class test
{
public:
	test(int a_num, int b_num):
		a(a_num),
		b(b_num)
	{  }
	int a;
	int b;
};

nolockqueue<test> queue;

static  void *thread_pop(void *arg)
{
	test *p;
	int num = 0;
	int a = 1;
	int b = 2;
	while(true)
	{
		//cout << "come in pop" << endl;
		p = queue.pop();
		if (p == NULL)
		{
			usleep(10);
			continue;
		}
		//cout << "pop one" << endl;
		//cout << p->a << " " << p->b  << a << "  " << b  << endl;
		if (p->a != a || p->b != b)
		{
			cout << "error: " << a << b
			   << p->a << p->b << endl;
			break;
		}
		a++;
		b++;
		delete  p;
		p = NULL;

		num += 1;
		if (num >= 100000000)
		{
			cout << "receive once " << endl;
			num = 0;
		}

	}
	cout << "receive over" << endl;
	return NULL;

}

static  void *thread_push(void *arg)
{
	int num = 0;
	int a = 1;
	int b = 2;
	bool result = false;
	test *p = new test(a, b);
	while(true)
	{
		result = queue.push(p);
		if (!result)
		{
			usleep(10);
			continue;
		}
		//cout << "push one" << endl;
		a++;
		b++;
		p = new test(a, b);
		if (p == NULL)
		{
			cout << "malloc test error " << endl;
			break;
		}

		num += 1;
		if (num >= 100000000)
		{
			cout <<  "send once" << endl;
			num = 0;
		}

	}
	cout << "send over" << endl;
	return NULL;

}

int main()
{
	bool re = queue.init(10000);
	if (!re)
	{
		cout << "init queue error" << endl;
	}
	pthread_t tid_1;
	if (pthread_create(&tid_1, NULL, thread_push, NULL) != 0)
		cout << "create push error" << endl;

	pthread_t tid_2;
	if (pthread_create(&tid_2, NULL, thread_pop, NULL) != 0)
		cout << "create pop error" << endl;

	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
}
