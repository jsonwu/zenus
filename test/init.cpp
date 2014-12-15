#include "init.h"

#include "kcrontab_timer_mgr.h"

int init()
{
	if(kcrontab_timer_mgr::instance()->init(10000) < 0)
		goto error;


error:
	return -1;

}
