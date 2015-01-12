#ifndef LENGTH_DECODER_H_
#define LENGTH_DECODER_H_

#include "channel_handler_adapter.h"
#include "epoll_handler.h"

class length_decoder : public channel_handler_adapter
{
public:
	virtual int hand_message(epoll_handler *hd, bytebuff *buff);
};

#endif
