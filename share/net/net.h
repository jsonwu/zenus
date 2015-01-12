#ifndef _NET_H_
#define _NET_H_

#include "bytebuff.h"

class net
{
	static int send(const int sock_id, bytebuff *buff);
};

#endif
