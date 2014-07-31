#ifndef MYSQLDB_H_
#define MYSQLDB_H_

#include <mysql.h>
#include <string.h>

const int MAX_SERVER_LEN = 64;
const int MAX_USER_LEN  = 64;
const int MAX_PASSWORD_LEN = 64;
const int MAX_DATABASE_LEN = 64;

class mysqldb
{
public:
	mysqldb(const char* server,
			const char* user,
			const char* password,
			const char* database,
			unsigned int port = 0);
	mysqldb();
	~mysqldb();

	int init(const char* server,
			 const char* user,
			 const char* password,
			 const char* database,
			 unsigned int port = 0);

	int connect();
	void close();

	MYSQL_RES*  query(const char *sql, const int len);
	bool  store(const char *sql, const int len);

	unsigned int row_number(MYSQL_RES *res);
private:
	int errnu();
private:
	bool is_connect_;;
	char server_[MAX_SERVER_LEN];
	char user_[MAX_USER_LEN];
	char password_[MAX_PASSWORD_LEN];
	char database_[MAX_DATABASE_LEN];
	unsigned int port_;

	MYSQL  mysql_;
};

#endif
