#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "thread_mutex_lock.h"
#include "thread_mutex_guard.h"

template<typename type>
class singleton
{
public:
	static type* instance()
	{ 
		if (instance_ == NULL)
		{
			thread_mutex_guard<thread_mutex_lock> lock(singleton_lock_);
			if (instance_ == NULL)
			{
				instance_ = new type;
			}
		}
		return instance_;
	}
private:
	static type *instance_;
	static thread_mutex_lock singleton_lock_;
};

#endif
