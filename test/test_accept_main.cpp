#include <iostream>
#include <unistd.h>
#include "epoll_accepter.h"
#include "client_handler.h"

int main()
{
	epoll_accepter<client_handler>  accepter;
	int ret = accepter.start(8088, 5);
	if (ret < 0)
		std::cout << "accept start error" << std::endl;
	while(1)
		sleep(1000);
	return 1;
}
