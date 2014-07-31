#include <iostream>
#include <errmsg.h>
#include "mysqldb.h"


mysqldb::mysqldb(const char* server,
				 const char* user,
				 const char* password,
				 const char* database,
				 unsigned int port /* = 0 */)
{
	::strncpy(this->server_, server, MAX_SERVER_LEN-1);
	::strncpy(this->user_, user, MAX_USER_LEN-1);
	::strncpy(this->password_, password, MAX_PASSWORD_LEN-1);
	::strncpy(this->database_, database, MAX_DATABASE_LEN-1);
	this->port_ = port;
	this->is_connect_ = false;
}

int mysqldb::init(const char* server,
				  const char* user,
				  const char* password,
				  const char* database,
				  unsigned int port /* = 0 */)
{
	::strncpy(this->server_, server, MAX_SERVER_LEN-1);
	::strncpy(this->user_, user, MAX_USER_LEN-1);
	::strncpy(this->password_, password, MAX_PASSWORD_LEN-1);
	::strncpy(this->database_, database, MAX_DATABASE_LEN-1);
	this->port_ = port;
	this->is_connect_ = false;
	return 0;
}

mysqldb::mysqldb()
{
	bzero(this->server_, MAX_SERVER_LEN);
	bzero(this->user_, MAX_USER_LEN);
	bzero(this->password_, MAX_PASSWORD_LEN);
	bzero(this->database_, MAX_DATABASE_LEN);
	this->port_ = -1;
}
mysqldb::~mysqldb()
{
	this->close();
}

int mysqldb::connect()
{
	this->close();
	mysql_init(&this->mysql_);
	int timeout = 2;
	mysql_options(&this->mysql_, MYSQL_OPT_READ_TIMEOUT, (char *)&timeout);
	mysql_options(&this->mysql_, MYSQL_OPT_CONNECT_TIMEOUT, (char *)&timeout);

	if (mysql_real_connect(&this->mysql_,
						   this->server_,
						   this->user_,
						   this->password_,
						   this->database_,
						   this->port_,
							NULL,
							0) == NULL)
	{
		std::cout << "connect error" << std::endl;
		this->close();
		return -1;
	}
	this->is_connect_ = true;
	return 0;
}

void mysqldb::close() 
{
	mysql_close(&this->mysql_);
	this->is_connect_ = false;
}

int mysqldb::errnu()
{
	return mysql_errno(&this->mysql_);
}

MYSQL_RES* mysqldb::query(const char *sql, const int len)
{
	int retry_time = 1;
	MYSQL_RES *res = NULL;
	do
	{
		if (mysql_real_query(&this->mysql_, sql, len) != 0)
		{
			int ret = this->errnu();
			if (ret == CR_SERVER_GONE_ERROR || ret == CR_SERVER_LOST)
				this->is_connect_ = false;
		}else
		{
			res = mysql_store_result(&this->mysql_);
			if (res == NULL)
			{
				int errno = this->errnu();
				if (errno == CR_SERVER_GONE_ERROR || errno == CR_SERVER_LOST)
					this->is_connect_ = false;
			}
		}
	}while(!this->is_connect_ && retry_time-- > 0);

	return res;
}

bool mysqldb::store(const char *sql, const int len)
{
	int retry_time = 1;
	int ret = 0;
	do
	{
	   	ret = mysql_real_query(&this->mysql_, sql, len);
		if ( ret != 0)
		{
			int ret = this->errnu();
			if (ret == CR_SERVER_GONE_ERROR || ret == CR_SERVER_LOST)
				this->is_connect_ = false;
		}
	}while(!this->is_connect_ && retry_time-- > 0);

	return ret == 0 ? true : false;
}


unsigned int mysqldb::row_number(MYSQL_RES *res)
{
	return mysql_num_rows(res);
}
