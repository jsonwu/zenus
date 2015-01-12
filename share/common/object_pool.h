#ifndef FAST_OBJECT_POOL_H_
#define FAST_OBJECT_POOL_H_

#include <list>
#include <stdlib.h>
#include <iostream>
#include "singleton.h"

//pay attention !!!!
//object must have  unint to in use in release

template<typename Type>
class object_pool : public singleton <object_pool<Type> >
{
public:
	object_pool();
	~object_pool();
	int init(const int every_size);

	Type* alloc();
	void  release(Type *data);

private:
	int expand(const int size);

private:
	int every_expand_size_;
	std::list<Type *>  data_list_;
};

template<typename Type>
object_pool<Type>::object_pool():
	every_expand_size_(128)
{
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
int object_pool<Type>::init(const int every_size)
{
	if (every_size <= 0)
		return -1;

	this->every_expand_size_ =  every_size;
	return this->expand(this->every_expand_size_);
}

template<typename Type>
Type *object_pool<Type>::alloc()
{
	Type *data = NULL;
	if (this->data_list_.empty())
	{
		if (this->expand(this->every_expand_size_) < 0)
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
	//data->~Type();  //析构了导致类问题
	data->unint();
	this->data_list_.push_back(data);
}

template<typename Type>
int object_pool<Type>::expand(const int size)
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

		//p_data->init();
		this->data_list_.push_back(p_data);
	}

	/*
	for (int i = 0; i < this->every_expand_size_; ++i)
	{
		Type *p_data = new Type;

		//p_data->init();
		this->data_list_.push_back(p_data);
	}
	*/

	return true;
}

#endif 
