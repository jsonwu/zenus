#include "account_mgr.h"


int account_mgr::insert(const int session_id, account_info *info)
{
	std::pair<account_map_iter, bool> res = this->account_map_.insert(std::pair<int, account_info *>(session_id, info));
	if (!res.second)
		return -1;
	return 0;
}

int account_mgr::del(const int session_id)
{
	account_map_iter it = this->account_map_.find(session_id);
	if (it == this->account_map_.end())
		return -1;
	delete it->second;
	this->account_map_.erase(it);
	return 0;
}

account_info* account_mgr::get(const int session_id)
{
	account_map_iter it = this->account_map_.find(session_id);
	if (it == this->account_map_.end())
		return NULL;
	return it->second;
}
