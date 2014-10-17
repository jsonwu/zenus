#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "logitem.h"

class layout
{
public:
	virtual  void render(logitem &item, std::string &out) = 0;
};

#endif 
