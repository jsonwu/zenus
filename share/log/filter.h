#ifndef	FILTER_H_
#define FILTER_H_

#include "logitem.h"

class filter
{
public:
	virtual bool pass(logitem &itme) = 0; 
};

#endif
