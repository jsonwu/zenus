#include "mysql_mgr.h"

int mysql_mgr::init(const int num,
					const char *server,
					const char *user,
					const char *password,
					const char *database,
					const int port /*= 0*/)
{
	if (num < 0)
		return -1;
	for(int i = 0; i < num; ++i)
	{
		mysqldb *db = new  mysqldb(server,
								   user,
								   password,
								   database,
								   port);
		if (db->connect() < 0)
			goto error;
		this->dbsql_vect_.push_back(db);
	}

	return 0;

error:
	mysql_mgr::instance()->close_all();
	return -1;
}

mysqldb*  mysql_mgr::get_sqldb(const int num)
{
	if (num < 0 || (unsigned int)num > this->dbsql_vect_.size())
		return NULL;
	return this->dbsql_vect_[num];
}

int mysql_mgr::close_all()
{
	std::vector<mysqldb *>::iterator it = this->dbsql_vect_.begin();
	for (; it != this->dbsql_vect_.end(); ++it)
	{
		(*it)->close();
		delete *it;
	}
	return 0;
}
