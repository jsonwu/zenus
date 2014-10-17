#include "lthread.h"
#include <iostream>


using namespace std;
int lthread::start(lrunnable *object)
{
	if (object == NULL)
		return -1;
	this->object_ = object;
   return pthread_create(&(this->thread_id_), NULL, lthread::thread_func, object_);
}

void* lthread::thread_func(void *arg)
{
	cout << "come to thread" << endl;
	int res = ((lrunnable*)arg)->run();
	cout << "out to thread" << endl;
	pthread_exit((void *)res);
}
