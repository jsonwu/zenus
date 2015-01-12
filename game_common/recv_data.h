#ifndef RECV_DATA_H_
#define RECV_DATA_H_

#include "bytebuff.h"
#include "client_handler.h"

class recv_data
{
public:
	int message_id;
	bytebuff *msg_buff;
	client_handler
};

#endif
