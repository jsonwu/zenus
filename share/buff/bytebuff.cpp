#include <string.h>
#include "digital.h"
#include "bytebuff.h"

bytebuff::bytebuff(int size)
		:buff_(new char[size]),
		buff_size_(size),
		read_index_(0),
		write_index_(0)
{
	bzero(this->buff_, size);
}

bytebuff::~bytebuff()
{
	delete this->buff_;
	this->buff_size_ = 0;
	this->write_index_ = this->read_index_ = 0;
}

#define LOOK_TYPE(type, num)  \
	if (this->data_len() < sizeof(type)) \
		return -1;  \
	num = *((type *)(this->buff_ + this->read_index_)); \
	return 0;

int bytebuff::look_short(short &num)
{
	LOOK_TYPE(short, num); 
}

int bytebuff::look_int(int &num)
{
	LOOK_TYPE(int, num);
}

int bytebuff::read_short(short &num)
{
	if (this->look_short(num) < 0)
		return -1;
	this->read_index_ += 2;
	return 0;
}

int bytebuff::read_int(int &num)
{
	if (this->look_int(num) < 0)
		return -1;
	this->read_index_ += 4;
	return 0;
}

int bytebuff::read_bytebuff(bytebuff *bf, const int size)
{
	if (this->read(bf->buff_, size) < 0)
		return -1;
	bf->write_index_ += size;
	return 0;
}

int bytebuff::write_short(const short num)
{
	char s[128] = {0};
	*(short *)s = num;
	return this->write(s, 2);
}

int bytebuff::write_int(const int num)
{
	char s[128] = {0};
	*(int *)s = num;
	return this->write(s, 4);
}

int bytebuff::read(char *buff, int size)
{
	if(this->data_len() < size
	   || buff == NULL)
		return -1;

	memcpy(buff, this->buff_, size);
	this->read_index_ += size;
	return 0;
}

int bytebuff::write(char *buff, int size)
{
	if (buff == NULL || size <= 0)
		return -1;

	if (this->space_len() < size)
	{
		if (this->buff_size_ < size)
		{
			//扩张buff的大小
			int need_size = this->buff_size_ +  size;
			int expand_size = num_2n(need_size);
			if (expand_size < 0)
				return -1;
			this->expand_buff(expand_size);
		}else
		{
			//将整个数据前移动
			this->discard_readbyte();
		}
	}
	this->put(buff, size);
	return 0;
}

int bytebuff::write(bytebuff *buff)
{
	this->write(buff->buff_ + buff->read_index_, buff->data_len());
}

int bytebuff::data_len() {
	return this->write_index_ - this->read_index_;
}

void bytebuff::clear()
{
	this->read_index_ = this->write_index_ = 0;
}

int bytebuff::size()
{
	return this->buff_size_;
}

char *bytebuff::readable_buff()
{
	return this->buff_ + this->read_index_;
}

int bytebuff::read_index(const int size)
{
	if (this->read_index_ + size > this->write_index_)
		return -1;
	this->read_index_ += size;
	return 0;
}
//==================================private===================
int bytebuff::space_len()
{
	return this->buff_size_ - this->write_index_;
}

int bytebuff::expand_buff(int expand_size)
{
	if (this->buff_size_ >= expand_size)
		return 0;

	char *tmp = new char[expand_size];
	int date_len = this->data_len();
	memcpy(tmp,
		   this->buff_ + this->read_index_,
		   this->data_len());
	delete this->buff_;
	this->buff_ = tmp;
	this->buff_size_ = expand_size;
	this->read_index_ = 0;
	this->write_index_ = date_len;
	return 0;
}

int bytebuff::discard_readbyte()
{
	if (this->read_index_ == 0)
		return 0;

	if (this->read_index_ != this->write_index_)
	{
		int date_len = this->data_len();
		memmove(this->buff_, this->buff_ + this->read_index_, date_len);
		this->read_index_ = 0;
		this->write_index_ = date_len;
	}else
	{
		this->read_index_ = this->write_index_ = 0;
	}
	return 0;
}

int bytebuff::put(char *buff, int size)
{
	memcpy(this->buff_ + this->write_index_, buff, size);
	this->write_index_ += size;
	return 0;
}
