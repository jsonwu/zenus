#include <iostream>
#include <signal.h>

#include "init.h"
#include "reactor.h"
#include "accepter.h"
#include "client_handler.h"
#include "client_connector.h"
#include "kcrontab_timer_mgr.h"
#include "length_decoder.h"

using namespace std;

int main()
{

	signal(SIGPIPE, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	if (init() < 0)
		return -1;
	if (reactor::instance()->init(1) < 0)
	{
		cout <<  "reactor init error" << endl;
		return -1;
	}
	accepter<client_handler> accept;
	accept.channel()->push_back_recv_handler(new length_decoder);
	if (accept.start(9098) < 0)
	{
		cout << "accepter start error" <<  endl;
		return -1;
	}
	char *ip = "0.0.0.0";
	client_connector  db_connect(ip, 8089);
	if (db_connect.connect_server() < 0)
	{
		cout << "connect db_server error" << endl;
		return -1;
	}

	while(1)
	{
		process_message(1000);
		kcrontab_timer_mgr::instance()->update();
	}
}


