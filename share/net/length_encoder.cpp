#include "length_encoder.h"
#include "bytebuff_pool.h"

int length_encoder::hand_message(epoll_handler *hd, bytebuff *buff)
{
	int data_len = buff->data_len();
	bytebuff *bf = bytebuff_pool::instance()->acquire(data_len + 2);
	bf->write_short(buff->data_len());
	bf->write(buff);
	bytebuff_pool::instance()->release(buff);
	buff = bf;
	return 0;
}
