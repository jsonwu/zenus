#ifndef LTHREAD_H_
#define LTHREAD_H_

#include <pthread.h>
#include "lrunnable.h"

class lthread
{
public:
	int start(lrunnable *object);
private:

	static void* thread_func(void *arg);
private:
	pthread_t thread_id_;
	lrunnable *object_;
};

#endif
