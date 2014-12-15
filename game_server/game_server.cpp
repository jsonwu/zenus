#include <iostream>

#include "reactor.h"
#include "accepter.h"
#include "client_handler.h"

using namespace std;

int main()
{
	if (reactor::instance()->init(1) < 0)
	{
		cout <<  "reactor init error" << endl;
		return -1;
	}
	accepter<client_handler> accept;
	if (accept.start(9098) < 0)
	{
		cout << "accepter start error" <<  endl;
		return -1;
	}

	while(1)
		sleep(-1);
}
