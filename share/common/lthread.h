#ifndef LTHREAD_H_
#define LTHREAD_H_

#include <pthread.h>
#include "lrunnable.h"

class lthread
{
public:
	int start(lrunnable *object)
	{
		if (object == NULL)
			return -1;
		this->object_ = object;
		return pthread_create(&(this->thread_id_), NULL, lthread::thread_func, (void *)object_);
	}
private:

	static void* thread_func(void *arg)
	{
		int res = ((lrunnable*)arg)->run();
		pthread_exit((void *)res);
	}
private:
	pthread_t thread_id_;
	lrunnable *object_;
};

#endif
