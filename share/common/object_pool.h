#ifndef FAST_OBJECT_POOL_H_
#define FAST_OBJECT_POOL_H_

#include <list>
#include <stdlib.h>
#include <iostream>
#include "singleton.h"

//pay attention !!!!
//the Type must had init() and uinit
//beacuse use malloc not support class with  virtural function  or stl: vector list and so on 
//beacuse use malloc a long memory to be faster 

template<typename Type>
class object_pool : public singleton <object_pool<Type> >
{
public:
	object_pool();
	~object_pool();
	bool init(const int every_size);

	Type* alloc();
	void  release(Type *data);

private:
	bool expand(const int size);

private:
	int init_size_;
	int every_expand_size_;
	std::list<Type *>  data_list_;
};

template<typename Type>
object_pool<Type>::object_pool()
{
	this->init(100);
}

template<typename Type>
object_pool<Type>::~object_pool()
{
	/*
	std::list<Type *>::iterator it = this->data_list_.begin();
	for(; it != this->data_list_.end(); ++it)
		delete it;
		*/
}

template<typename Type>
bool object_pool<Type>::init(const int every_size)
{
	if (every_size <= 0)
		return false;

	this->every_expand_size_ =  every_size;
	return this->expand(this->every_expand_size_);
}

template<typename Type>
Type *object_pool<Type>::alloc()
{
	Type *data = NULL;
	if (this->data_list_.empty())
	{
		if (!this->expand(this->every_expand_size_))
			goto error;
	}

	data = this->data_list_.front();
	this->data_list_.pop_front();
	return data;

error:
	return NULL;
}

template<typename Type>
void object_pool<Type>::release(Type *data)
{
	data->uinit();
	this->data_list_.push_back(data);
}

template<typename Type>
bool object_pool<Type>::expand(const int size)
{
	int type_len = sizeof(Type);

	//because of  here so not  class with 
	Type *p = (Type *)malloc(type_len*size);   
	if (p == NULL)
		return false;
	for (int i = 0; i < this->every_expand_size_; ++i)
	{
		Type *p_data = p+i;
		new(p_data) Type;

		p_data->init();
		this->data_list_.push_back(p_data);
	}
	return true;
}

#endif 
