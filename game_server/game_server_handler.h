#ifndef GAME_SERVER_HANDLER_H_
#define GAME_SERVER_HANDLER_H_


#include "client_handler.h" 

class  game_server_handler : public client_handler
{
public:
	virtual int handle_message(const int msg_id,
							   const char* msg,
							   const int message_len);

};


#endif
