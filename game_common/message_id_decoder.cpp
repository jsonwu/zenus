#include "message_id_decoder.h"

int message_id_decoder::hand_message(epoll_handler *hd, bytebuff *buff)
{
	int message_id = 0;
	if (buff->read_int(message_id) < 0)
		return -1;

}
