#ifndef MESSAGE_ID_DECODER_H_
#define MESSAGE_ID_DECODER_H_

#include "channel_handler_adapter.h"

class message_id_decoder : public channel_handler_adapter
{
public:
	virtual int hand_message(epoll_handler *hd, bytebuff *buff);
};

#endif
