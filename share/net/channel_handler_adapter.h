#ifndef CHANNEL_HANDLER_ADAPTER_H_
#define CHANNEL_HANDLER_ADAPTER_H_

#include "bytebuff.h"

class epoll_handler;
class channel_handler_adapter
{
public:
	virtual int hand_message(epoll_handler *hd, bytebuff *buff) = 0;
};

#endif
