#ifndef PLAYER_MGR_H_
#define PLAYER_MGR_H_

#include <string>
#include <map>
#include "player.h"
#include "singleton.h"

class player_mgr : public singleton<player_mgr>
{
public:
	player* find(std::string &account);

private:
	std::map<std::string, player*> player_map_;
};

#endif
