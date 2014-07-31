#ifndef DB_OPERATE_H_
#define DB_OPERATE_H_

#include "singleton.h"
#include "mysqldb.h"

class db_operate : public singleton<db_operate>
{
public:
	int init(const char* server,
			 const char* user,
			 const char* password,
			 const char* database,
			 unsigned int port = 0);
	MYSQL_RES* query(const char *sql, const int len);
	bool store(const char *sql, const int len);
	unsigned int row_number(MYSQL_RES *res);
private:
	mysqldb* mysqldb_;
};

#endif 
