#ifndef CLIENT_H_
#define CLIENT_H_

#include "client_handler.h"

class client : public client_handler
{
public:
	virtual int handle_message(const int msg_id,
							   const char *msg,
							   int message_len);
	int send_errno(const int msg_id, const int err_id);

	int send_client_msg(const int msg_id,
						const char *msg, const int len);

private:
	int send_msg_impl(const int msg_id,
					  const char *pdata,
					  const int len,
					  const int ernno);
};

#endif
