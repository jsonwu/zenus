#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "nolockpipe.h"

nolockpipe::nolockpipe():
	buff_(NULL),
	head_(NULL),
	tail_(NULL),
	size_(0)
{ }

nolockpipe::~nolockpipe()
{
	delete []this->buff_;
}

int nolockpipe::init(const int size)
{
	if (size <= 0)
		goto error;

	this->buff_ = new char[size];
	if (this->buff_ == NULL)
		goto error;

	this->size_ = size;
	this->head_ = this->buff_;
	this->tail_ = this->buff_;

	return 0;

error:
	return -1;
}

int nolockpipe::read(char *buff, const int len)
{
	int distance = this->head_ - this->tail_ + this->size_;
	int data_num = distance >= this->size_ ? distance - this->size_ : distance;

	//std::cout << "read len" << data_num << std::endl;

	if (len > data_num)
	{
		//std::cout << "read data less" << data_num << std::endl;
		goto error;
	}
	if (this->tail_ + len >= this->buff_ + this->size_)
	{
		int len_1 = this->buff_ + this->size_ - this->tail_;
		int len_2 = len - len_1;
		memcpy(buff, this->tail_, len_1);
		memcpy(buff + len_1, this->buff_, len_2);
		char *p_temp = this->buff_ + len_2;
		__sync_lock_test_and_set(&this->tail_, p_temp);
	}else
	{
		memcpy(buff, this->tail_, len);
		__sync_fetch_and_add(&this->tail_, len);
	}
	//printf("%p,  %p begin %p  end %p \n", this->tail_, this->head_, this->buff_, this->buff_ + this->size_);
	return 0;

error:
	return -1;
}

int nolockpipe::write(const char *buff, const int len)
{
	int distance = this->head_ - this->tail_ + this->size_;
	int data_num = distance >= this->size_ ?  distance - this->size_ : distance;

	//std::cout << "data_num" << data_num << std::endl; 
	//std::cout << "write len" << data_num << std::endl;
    // 因为head 所指的地方一直为空不写入数据
	if (data_num + len + 1 >= this->size_)
	{
		//std::cout << "data_num" << data_num << std::endl; 
		goto error;
	}

	if (this->head_  + len >= this->buff_ + this->size_)
	{
		//printf("send %p  %p %p\n", this->head_, this->tail_, this->buff_+this->size_);
		int head2end_len = this->buff_ + this->size_ - this->head_; // +1   -1
		int last_len = len - head2end_len; 
		memcpy(this->head_, buff, head2end_len);
		memcpy(this->buff_, buff + head2end_len, last_len);
		char *temp_buf = this->buff_ + last_len;
		__sync_lock_test_and_set(&this->head_, temp_buf);
	}else
	{
		memcpy(this->head_, buff, len);
		__sync_fetch_and_add(&this->head_, len);
	}

	return 0;
error:
	return -1;
}

