#include "channel_pip_line.h"
#include "epoll_handler.h"

int channel_pip_line::hand_send_msg(epoll_handler *hd, bytebuff *buff)
{
	handler_list_iter iter = this->send_handler_list_.begin();
	for (; iter != this->send_handler_list_.end(); ++iter)
	{
		int res = (*iter)->hand_message(hd, buff);
		if (res < 0)
			break;
	}
	return 0;
}

int channel_pip_line::hand_recv_msg(epoll_handler *hd, bytebuff *buff)
{
	handler_list_iter iter = this->recv_handler_list_.begin();
	for (; iter != this->recv_handler_list_.end(); ++iter)
	{
		if ((*iter)->hand_message(hd, buff) < 0)
			break;
	}
	return 0;
}


int channel_pip_line::push_back_send_handler(channel_handler_adapter *hd)
{
	this->send_handler_list_.push_back(hd);
}

int channel_pip_line::push_back_recv_handler(channel_handler_adapter *hd)
{
	this->recv_handler_list_.push_back(hd);
}

