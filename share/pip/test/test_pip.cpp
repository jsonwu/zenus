#include"nolockqueue.h"
#include "nolockpipe.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

nolockpipe queue;

static  void *thread_pop(void *arg)
{
	int b = 1;
	while(true)
	{
		//cout << "come in pop" << endl;
		int a = 0;
		if (queue.read((char *)&a, 4) < 0)
		{
			//cout << "read sleep" << endl;
			//sleep(1);
			continue;
		}
		if (a != b)
		{
			cout << "read error" << a  << endl;
			exit(0);
		}
		else
			b++;
		cout << "read ok" << a << endl;
		//sleep(1);
	}
	cout << "receive over" << endl;
	return NULL;

}

static  void *thread_push(void *arg)
{
	int a = 1;
	int b = 0;
	while(true)
	{
		if (queue.write((char *)&a, 4) < 0)
		{
			//cout << "write sleep" << endl;	
			//usleep(1000);
			continue;
		}
		cout << "push one" << a << endl;
		//
		a++;
		b++;
		if (b >100)
		{
			//cout << "push 100 data" << endl;
			b = 0;
		}
		//sleep(1);
	}
	cout << "send over" << endl;
	return NULL;

}

int main()
{ int re = queue.init(1024);
	if (re < 0)
	{
		cout << "init queue error" << endl;
		return -1;
	}

	pthread_t tid_1;
	if (pthread_create(&tid_1, NULL, thread_push, NULL) != 0)
		cout << "create push error" << endl;

	pthread_t tid_2;
	if (pthread_create(&tid_2, NULL, thread_pop, NULL) != 0)
		cout << "create pop error" << endl;

	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
	return 0;
}
