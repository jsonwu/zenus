#include "player_mgr.h"

player* player_mgr::find(const int player_id)
{
	std::map<int, player *>::iterator it = this->player_map_.find(player_id);
	if (it == this->player_map_.end())
		return NULL;
	return it->second;
}

int player_mgr::insert(const int player_id, player *pl)
{
	std::pair<player_map_iterator, bool> res = this->player_map_.insert(std::pair<int, player *>(player_id, pl));
	if (!res.second)
		return -1;
	return 0;
}

int player_mgr::del(const int player_id)
{
	player_map_iterator it = this->player_map_.find(player_id);
	if (it == this->player_map_.end())
		return -1;
	delete  it->second;
	return 0;
}
