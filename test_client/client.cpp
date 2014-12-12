#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>


using namespace std;
int main(int argc, char *argv[])
{
	int cfd;
	int recbytes;
	int sin_size;
	char buffer[1024]={0};   
	struct sockaddr_in s_add,c_add;
	unsigned short portnum=atoi(argv[2]); 

	printf("Hello,welcome to client !\r\n");

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == cfd)
	{
		printf("socket fail ! \r\n");
		return -1;
	}
	printf("socket ok !\r\n");

	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(argv[1]);
	s_add.sin_port=htons(portnum);
	printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);


	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
		printf("connect fail !\r\n");
		return -1;
	}
	printf("connect ok !\r\n");

	std::string message_data(2048, 's');
	for (int i = 1 ; i < 10000; ++i)
	{
	    char data[1024*1024] = {0};
		*(int *)data =  i;
		*(int *)(data + 4) = i;
		memcpy(data+8, message_data.c_str(), i);
		int n = send(cfd, data, i+8, 0);
		cout << "send n char " << n << endl;
		std::string send_message(data+8, i);
		if (i%200 == 0)
			sleep(1);
		if (i == 1023)
			i = 0; 
		sleep(5);
		break;
		//std::cout << send_message.c_str() << std::endl;
	}
	close(cfd);
		sleep(5);
		sleep(5);
		sleep(5);

	/*
	if(-1 == (recbytes = recv(cfd,buffer,1024, 0)))
	{
		printf("read data fail !\r\n");
		return -1;
	}
	printf("read ok\r\nREC:\r\n");
k
	buffer[recbytes]='\0';
	printf("%s\r\n",buffer);

	getchar();
	*/
	sleep(10);
	close(cfd);
	return 0;
}
