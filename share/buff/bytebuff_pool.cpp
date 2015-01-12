#include <iostream>

#include "bytebuff_pool.h"
#include "digital.h"

bytebuff*  bytebuff_pool::acquire(const int size)
{
	if (size <= 0)
		return NULL;
	int byte_size = num_2n(size);
	if (byte_size <= 0)
		return NULL;

	std::list<bytebuff *> *list = this->find_list(byte_size);

	bytebuff *res = NULL;

	if (list->empty())
	{
		res = new bytebuff(byte_size);
	}else
	{
		res = list->front();
		list->pop_front();
	}
	return res;
}

void bytebuff_pool::release(bytebuff *by)
{
	std::list<bytebuff *> * list = this->find_list(by->size());
	if (list == NULL)
		return;
	list->push_front(by);
}


void bytebuff_pool::print()
{
	pool_map_iter iter = this->bytebuff_pool_.begin();
	for(; iter != this->bytebuff_pool_.end(); ++iter)
	{
		std::cout << "size: " << iter->first << "num: "<< iter->second->size() << std::endl;
	}
}
//===============================private=====================

std::list<bytebuff *>* bytebuff_pool::find_list(const int size)
{
	std::list<bytebuff *> *by_list = NULL;
	pool_map_iter iter = this->bytebuff_pool_.find(size);
	if (iter == this->bytebuff_pool_.end())
	{
		std::list<bytebuff *> *new_list = new std::list<bytebuff *>;
		this->bytebuff_pool_.insert(std::make_pair<int,
									std::list<bytebuff *> *>(size,
															 new_list));
		by_list = new_list;
	}else
	{
		by_list = iter->second;
	}
	return by_list;
}
