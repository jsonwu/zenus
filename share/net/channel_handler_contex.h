#ifndef CHANNEL_HANDLER_CONTEX_H_
#define CHANNEL_HANDLER_CONTEX_H_

#include "epoll_handler.h"

class channel_handler_contex
{
public:
	epoll_handler *handler_;
};

#endif
