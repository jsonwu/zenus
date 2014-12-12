#ifndef PLAYER_MGR_H_
#define PLAYER_MGR_H_

#include <string>
#include <map>
#include "player.h"
#include "singleton.h"

class player_mgr : public singleton<player_mgr>
{
public:
	player* find(const int char_id);
	int insert(const int player_id, player *pl);
	int del(const int player_id);
private:
	typedef std::map<int, player*>::iterator player_map_iterator;
	std::map<int/*player_id*/, player*> player_map_;
};

#endif
