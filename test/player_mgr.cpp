#include "player_mgr.h"

player* player_mgr::find(std::string &account)
{
	std::<std::string, player*>::iterator it = this->player_map_.find(account);
	if (it != this->player_map_.end())
		return it->second();
	return NULL;
}
