#include "process_message.h"

int process_message(const int num)
{
	void *p = NULL;
	int a = 0;
	while (a++ < num)
	{
		if (net_logic_bus::instance()->logic_read(p) < 0)
			break;

	}
}
