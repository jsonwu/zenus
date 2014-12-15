#include <string>
#include <stdio.h>

#include "account_tb.h"
#include "message_id_def.h"
#include "db_server.pb.h"
#include "common_def.h"
#include "errno_def.h"

using namespace std;

std::string  account_tb::table_name_ = "account_info";

int account_tb::insert(db_date *date)
{

	//printf("come in account_tb ::insert \n");
	return 0;
	db_server::regist_account prot;
	db_server::resp_regist_account resp;
	string resp_string; 

	int errno_num = 0;
	int size = 0;

	string account  = prot.account();
	string password = prot.password();

	if(!prot.ParseFromString(date->msg_))
	{
		errno_num = ERR_PROTOC_PARSE;
		goto error;
	}
	if(account.empty())
	{
		errno_num = ERR_ACCOUNT_ILLEGAL;
		goto error;
	}
	if(password.empty())
	{
		errno_num = ERR_PASSWORD_ILLEGAL;
		goto error;
	}

	char buff[MAX_SQL_LEN];
	size = snprintf(buff, MAX_SQL_LEN - 1 , "insert into %s (  \
		account,  \
		password)  \
		values(%s, %s)", 
		account_tb::table_name_.c_str(),
		account.c_str(),  
		password.c_str());
	if (size < 0)
	{
		errno_num = ERR_PROGRAME;
		goto error;
	}
	if (date->db_->store(buff, size))
	{
		errno_num = ERR_PROGRAME;
		goto error;
	}
resp.set_errno_num(errno);
	resp.set_account(account);
	if (!resp.SerializeToString(&resp_string))
	{
		errno_num = ERR_PROGRAME;
		goto error;
	}
	date->handler_->send(RES_REGIST, resp_string);
	return 0;

error:
	resp.set_errno_num(errno);
	if (!resp.SerializeToString(&resp_string))
	{
		//log
		return 0;
	}
	date->handler_->send(RES_REGIST, resp_string);
	return 0;
}

int account_tb::get_info(db_date *date)
{
	return 0;
}
