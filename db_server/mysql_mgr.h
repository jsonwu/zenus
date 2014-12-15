#ifndef MYSQL_MGR_H_
#define MYSQL_MGR_H_

#include <vector>

#include "singleton.h"
#include "mysqldb.h"

class mysql_mgr : public singleton<mysql_mgr>
{
public:
	int init(const int num,
			 const char *server,
			 const char *user,
			 const char *password,
			 const char *database,
			 const int port = 0);

	mysqldb* get_sqldb(const int num);

	int close_all();
private:
	std::vector<mysqldb *>  dbsql_vect_;
};

#endif
