#ifndef LENGTH_ENCODER_H_
#define LENGTH_ENCODER_H_

#include "channel_handler_adapter.h"


class length_encoder
{
public:
	virtual int hand_message(epoll_handler *hd, bytebuff *buff);
};

#endif
