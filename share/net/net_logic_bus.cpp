#include "net_logic_bus.h"

net_logic_bus::net_logic_bus()
{
	this->net_2_logic_.init(1024);
	this->logic_2_net_.init(1024);
}

int net_logic_bus::net_write(void *p)
{
	return this->net_2_logic_.write((char *)&p, 4);
}

int net_logic_bus::net_read(void *&p)
{
	int point;
	if (!this->logic_2_net_.read((char *)&point, 4))
		return -1;
	p = (void *)point;
	return 0;
}

int net_logic_bus::logic_write(void *p)
{
	return this->logic_2_net_.write((char *)&p, 4);
}

int net_logic_bus::logic_read(void *&p)
{
	int point;
	if (!this->net_2_logic_.read((char *)&point, 4))
		return -1;
	p = (void *)point;
	return 0;
}
