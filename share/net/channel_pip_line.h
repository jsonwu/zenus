#ifndef CHANNEL_PIP_LINE_H_
#define CHANNEL_PIP_LINE_H_

#include <list>
#include "bytebuff.h"
#include "channel_handler_adapter.h"

class epoll_handler;
class channel_pip_line
{
public:
	int hand_send_msg(epoll_handler *hd, bytebuff* buff);
	int hand_recv_msg(epoll_handler *hd, bytebuff* buff);
	int push_back_send_handler(channel_handler_adapter *hd);
	int push_back_recv_handler(channel_handler_adapter *hd);
private:
	typedef std::list<channel_handler_adapter *> handler_list;
	typedef std::list<channel_handler_adapter *>::iterator handler_list_iter;
	std::list<channel_handler_adapter *>  recv_handler_list_;
	std::list<channel_handler_adapter *>  send_handler_list_;
};

#endif
