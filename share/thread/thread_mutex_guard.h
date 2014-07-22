#ifndef THREAD_MUTEX_GUARD_H_
#define THREAD_MUTEX_GUARD_H_

template<typename thread_mutex>
class thread_mutex_guard
{
public:
	thread_mutex_guard(thread_mutex &lock)
		:lock_(lock),
		owner_(false)
	{
		this->acquire();
	}

	void acquire()
	{
		this->lock_->acquire();
		this->owner_ = true;
	}

	void release()
	{
		if (this->owner_)
		{
			this->lock_->release();
			this->owner_ = false;
		}
	}
	~thread_mutex()
	{
		this->release();
	}

private:

	thread_mutex_guard(const thread_mutex_guard &);
	void operator=(const thread_mutex &)

private:
	thread_mutex *lock_;
	bool owner_;
};
#endif
