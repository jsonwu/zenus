#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include "db_operate.h"
#include "client.h"
#include "login.h"
#include "message_id_def.h"
#include "errno_def.h"
#include "client_server.pb.h"

const int MAX_SQL_DATA_LEN = 1024;

int login::process_msg(client *pclient, const int msg_id, const char *msg, const int len)
{
#define HANDLE_LOGIN_MESSAGE(id, handle)  case id: \
	ret = this->handle(pclient, msg, len);  \
	break

#define DEFAULE  default: \
	std::cout << "unknow msg_id in login" << msg_id << std::endl; \
	break

	int ret = 0;
	switch(msg_id)
	{
		HANDLE_LOGIN_MESSAGE(REQ_REGIST, regist_accout);
		HANDLE_LOGIN_MESSAGE(REQ_LOGIN, login_app);
		DEFAULE;
	}
	return ret;
}

int login::regist_accout(client *pclient, const char *msg, const int len)
{ 
	int ret = 0;
	client_server::regist_account  regist_message;

	regist_message.ParseFromArray(msg, len);
	std::string account = regist_message.account();
	std::string password = regist_message.password();

	char buf[MAX_SQL_DATA_LEN] = {0};
	int sql_len =::snprintf(buf, MAX_SQL_DATA_LEN, "select * from  account_info where acccount = %s", account.c_str());

	time_t now = time(NULL);
	MYSQL_RES  *res = db_operate::instance()->query(buf, sql_len);
	if (res == NULL)
	{
		ret = ERR_COMMUNICATE;
		goto error;
	}

	if (db_operate::instance()->row_number(res) != 0)
	{
		ret = ERR_ACCOUNT_EXIST;
		goto error;
	}

	bzero((void *)buf, MAX_SQL_DATA_LEN);

	sql_len = snprintf(buf, MAX_SQL_DATA_LEN, "insert into account_info("
									"account,"
									"password,"
									"regist_time)"
									"VALUES(%s, %s, %ld)",
									account.c_str(),
									password.c_str(),
									now);
	if (!db_operate::instance()->store(buf, sql_len))
	{
		ret = ERR_COMMUNICATE;
		goto error;
	}

	// need base info;
error:
	pclient->send_errno(RES_REGIST, ret);
	return 0;
}

int login::login_app(client *pclietn, const char *msg, const int len)
{
	//int ret = 0;
	/*
	client_server::login_app  regist_message;
	regist_message.ParseFromArray(msg, len); 

	std::string account = regist_message.account();
	std::string password = regist_message.password();

	player_manager::instance()->find(account);
	*/
	return 0;
}
