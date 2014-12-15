#include <iostream>
#include <unistd.h>

#include "init.h"
#include "epoll_accepter.h"
#include "db_handler.h"
#include "tb_map_mgr.h"
#include "mysql_mgr.h"
#include "db_msg_handler_mgr.h"


using namespace std;

int main()
{
	if (init() < 0)
	{
		cout << "base init error" << endl;
		return -1;
	}
	tb_map_mgr::instance()->init();

	if (mysql_mgr::instance()->init(10,
									"localhost",
									"root",
									"123456",
									"test") < 0)
	{
		cout << "mysql_mgr start error" << endl;
		return -1;
	}

	if (db_msg_handler_mgr::instance()->start(10) < 0)
	{
		cout << "db_msg_handler_mgr start error" << endl;
		return -1;
	}

	epoll_accepter<db_handler>  accepter;
	int ret = accepter.start(8089, 5);
	if (ret < 0)
		std::cout << "accept start error" << std::endl;
	while(1)
		sleep(1000);
	return 1;
}
