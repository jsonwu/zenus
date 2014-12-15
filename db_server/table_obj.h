#ifndef TABLE_OBJ_H_
#define TABLE_OBJ_H_

#include "db_date.h"

class table_obj
{
public:
	virtual int get_all_info(db_date *date)
	{ return -1; }

	virtual int insert(db_date *date)
	{ return -1; }

	virtual int get_info(db_date *date)
	{ return -1; }

	virtual int update(db_date *date)
	{ return -1; }
};

#endif
