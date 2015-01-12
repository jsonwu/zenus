#ifndef NET_LOGIC_BUS_H_
#define NET_LOGIC_BUS_H_

#include "singleton.h"
#include "nolockpipe.h"

class net_logic_bus : public singleton<net_logic_bus>
{
public:
	net_logic_bus();
	int net_write(void *p);
	int net_read(void *&p);
	int logic_write(void *p);
	int logic_read(void *&p);
private:
	nolockpipe net_2_logic_;
	nolockpipe logic_2_net_;
};

#endif
