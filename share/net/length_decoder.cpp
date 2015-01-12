#include <iostream>
#include"length_decoder.h"
#include "bytebuff_pool.h"

int length_decoder::hand_message(epoll_handler *hd, bytebuff *buff)
{
	int data_len = buff->data_len();
	if (data_len < 2)
		return -1;
	short message_len = 0;

	if (buff->look_short(message_len) < 0)
		return -1;

	if (message_len + 2 > data_len)
		return -1;

	buff->read_short(message_len);
	bytebuff  *msg_buff = bytebuff_pool::instance()->acquire(data_len);
	if (buff->read_bytebuff(msg_buff, data_len) < 0)
	{
		std::cout << "read bytebuff error" << data_len << buff->data_len() << std::endl;
		bytebuff_pool::instance()->release(msg_buff);
		return -1;
	}

	//接下来的逻辑线程是需要把buff释放掉
	buff = msg_buff;

	return 0;
}
