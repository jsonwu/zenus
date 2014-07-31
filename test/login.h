#ifndef LOGIN_H_
#define LOGIN_H_

#include "singleton.h"
#include "client_server.pb.h"

class client;

class login : public singleton<login>
{
	friend class singleton<login>;
public:
	int process_msg(client *pclient, const int msg_id, const char *msg, const int len);

private:
	int regist_accout(client *pclient, const char *msg, const int len);
	int login_app(client *pclient, const char *msg, const int len);
};

#endif
