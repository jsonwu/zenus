#ifndef THREAD_MUTEX_LOCK_H_
#define THREAD_MUTEX_LOCK_H_

#include <pthread.h>

#include "lock.h"

class thread_mutex_lock : public lock
{
public:
	thread_mutex_lock()
	{
		pthread_mutex_init(&this->mutex_, NULL);
	}
	virtual int acquire()
	{	
		return pthread_mutex_lock(&this->mutex_);
	}
	virtual int release()
	{
		return pthread_mutex_unlock(&this->mutex_);
	}
private:
	pthread_mutex_t  mutex_;
};

#endif
