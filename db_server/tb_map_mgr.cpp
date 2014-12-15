#include "tb_map_mgr.h"

#include "message_id_def.h"
#include "account_tb.h"


using namespace std;

int tb_map_mgr::init()
{
	table_obj *account = new account_tb;
	tb_map_mgr::instance()->regist(REQ_REGIST, account, &table_obj::insert);
	return 0;
}

int tb_map_mgr::regist(int message_id, table_obj *to, int (table_obj::*fun)(db_date *))
{
	table tb;
	tb.to_ = to;
	tb.func_ = fun;
	pair<map<int, table>::iterator, bool > ret;
	ret = this->handler_table_map_.insert(pair<int, table>(message_id, tb));
	if (ret.second == false)
		return -1;
	return 0;
}

int tb_map_mgr::call(const int message_id, db_date* date)
{
	map<int, table>::iterator it = this->handler_table_map_.find(message_id);
	if (it == this->handler_table_map_.end())
	{
		//log
		return -1;
	}

	return (it->second.to_->*(it->second.func_))(date);
}
