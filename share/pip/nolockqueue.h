#ifndef NOLOCKQUEUE_H_
#define NOLOCKQUEUE_H_

#include <stdlib.h>

//  pay attention !!!!!!
//  only support one thread read  one thread write
//  write in 2014-9-5 in prefect world
//  only support keep pointer int queue; 
//  for example:
//       class test {int a; int b};
//       nolockqueue<test> queue;
//       test *m = new test;
//       queue.push(m);           // push into queue;
//       test *n = queue.pop();   // pop pointer out of queue
//
//


template<typename Type>
class nolockqueue
{
public:
	nolockqueue();
	~nolockqueue();

	bool init(const int size);
	bool push(Type *data);
	Type* pop();

private:
	Type **p_queue_;
	unsigned int  push_position_;
	unsigned int  pop_position_; 
	int size_;
};

template<typename Type>
nolockqueue<Type>::nolockqueue()
{
}

template<typename Type>
nolockqueue<Type>::~nolockqueue()
{
	if (this->p_queue_ != NULL)
	{
		for (int i = 0; i < this->size_; ++i)
		{
			if (this->p_queue_[i] != NULL)
				delete this->p_queue_[i];
		}
	}
}

template<typename Type>
bool nolockqueue<Type>::init(const int size)
{
	if (size <= 0)
		goto error;
	this->p_queue_ = new Type *[size];
	if (this->p_queue_ == NULL)
		goto error;
	for (int i = 0; i < size; ++i) this->p_queue_[i] = NULL;

	this->push_position_ = 0;
	this->pop_position_ = 0;
	this->size_ = size;

	return true;
error:
	return false;
}

template<typename Type>
bool nolockqueue<Type>::push(Type *data)
{
	int pos = (this->push_position_)%this->size_;
	if (this->p_queue_[pos] != NULL)
		return false;
	this->p_queue_[pos] = data;
	__sync_fetch_and_add(&this->push_position_, 1);
	return true;
}

template<typename Type>
Type* nolockqueue<Type>::pop()
{
	int postion = this->pop_position_%this->size_;

	if (this->p_queue_[postion] == NULL)
		return NULL;
Type* tmp = this->p_queue_[postion];
	this->p_queue_[postion] = NULL;
	__sync_fetch_and_add(&this->pop_position_, 1);
	return tmp;
}
#endif
