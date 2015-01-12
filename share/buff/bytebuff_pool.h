#ifndef BYTEBUFF_POOL_H_
#define BYTEBUFF_POOL_H_

#include <map>
#include <list> 
#include "bytebuff.h"
#include "singleton.h"

class bytebuff_pool : public singleton<bytebuff_pool>
{
public:
	bytebuff* acquire(const int size);
	void release(bytebuff *by);

//for test
	void print();
private:
	std::list<bytebuff *>* find_list(const int size);
private:
	typedef std::map<int/*buff_size*/,
			std::list<bytebuff *>* > pool_map;
	typedef  std::map<int/*buff_size*/,
			std::list<bytebuff *>* >::iterator pool_map_iter;

	pool_map  bytebuff_pool_;
};

#endif
