#ifndef TB_MAP_MANAGER_H_
#define TB_MAP_MANAGER_H_

#include <map>

#include "singleton.h"
#include "table_obj.h"
#include "db_date.h"

class tb_map_mgr : public singleton<tb_map_mgr>
{
public:
	class table
	{
	public:
		table_obj *to_;
		int (table_obj::*func_)(db_date *);
	};

	int init();
	int regist(int message_id,
			   table_obj *to,
			   int (table_obj::*fun)(db_date *));

	int call(const int message_id, db_date *date);
private:
	std::map<int, table>  handler_table_map_;
};

#endif
