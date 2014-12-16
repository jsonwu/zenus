#include <iostream>

#include "init.h"
#include "kcrontab_timer_mgr.h"


int init()
{

	if (kcrontab_timer_mgr::instance()->init(1000) < 0)
	{
		std::cout <<  "kcrontabale init error" << std::endl;
		return -1;
	}
	return 0;
}
