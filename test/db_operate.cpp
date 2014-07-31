#include "db_operate.h"

int db_operate::init(const char* server,
					 const char* user,
					 const char* password,
					 const char* database,
					 unsigned int port)
{
	this->mysqldb_ = new mysqldb(server,
								 user,
								 password,
								 database,
								 port);
	return 0;
}

MYSQL_RES* db_operate::query(const char *msg, const int len)
{
	return this->mysqldb_->query(msg, len);
}

bool db_operate::store(const char *msg, const int len)
{
	return this->mysqldb_->store(msg, len);
}

unsigned int db_operate::row_number(MYSQL_RES *res)
{
	return this->mysqldb_->row_number(res);
}

