#ifndef ACCOUNT_MGR_H
#define ACCOUNT_MGR_H

#include <map>

#include "singleton.h"
#include "account.h"

class account_mgr : public singleton<account_mgr>
{
public:
	int insert(const int session_id, account_info *info);
	int del(int session_id);
	account_info *get(int session_id);

private:
	typedef std::map<int, account_info *>::iterator account_map_iter;
	std::map<int /*session_id*/, account_info *> account_map_;
};

#endif
