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
		if (singleton<type>::instance_ == NULL)
		{
			thread_mutex_guard<thread_mutex_lock> lock(singleton<type>::singleton_lock_);
			if (singleton<type>::instance_ == NULL)
			{
				singleton<type>::instance_ = new type;
			}
		}
		return singleton<type>::instance_;
	}
protected:
	static type *instance_;
	static thread_mutex_lock singleton_lock_;
};

template<typename type> type *singleton<type>::instance_ = NULL;
template<typename type> thread_mutex_lock  singleton<type>::singleton_lock_;

#endif
