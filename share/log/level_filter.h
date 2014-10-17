#ifndef LEVLE_FILTER_H_
#define LEVLE_FILTER_H_

#include "level.h"
#include "filter.h"

class level_filter : public filter
{
public:
	level_filter(level_value lvl)
		:pass_value_(lvl)
	{  }
	~level_filter();

	virtual bool pass(logitem &item)
	{
		return item.lvl_value() >= this->pass_value_;
	}
private:
	level_value  pass_value_;
};

#endif
