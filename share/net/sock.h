#ifndef SOCK_H_
#define SOCK_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

class sock
{
public:
	static int set_sockfd_reuseable(const int sockfd)
	{
		int on = 1;
		int ret = setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		if (ret != 0)
			return -1;
		return 0;
	}

	static int set_noblock(const int sockfd)
	{
		int opts = fcntl(sockfd, F_GETFL);
		if(opts < 0) 
			return -1;
		opts = opts | O_NONBLOCK;
		if(fcntl(sockfd, F_SETFL, opts) < 0)
			return -1;
		return 0;
	}

	static int send_n_msg(const int sock_fd, const char *msg, const int len)
	{
		int ret = 0;
		while(true)
		{
			ret = sock::send(sock_fd, msg, len, 0);
			if (ret < 0)
			{
				if (errno == EINTR) 
					continue;
				else if (errno == EAGAIN)
				{
					ret = 0;
					break;
				}
				else
					break;
			}else
				break;
		}
		return ret;
	}

	static int recv_n_msg(const int sock_fd, char *buff, const int len)
	{
		int ret = 0;
		while(true)
		{
			ret = sock::recv(sock_fd, buff, len, 0);
			if (ret < 0)
			{
				if(errno == EINTR)
				{
					continue;
				} else if(errno == EAGAIN)
				{
					ret = 0;
					break;
				} else
				{
					ret = -1;
					break;
				}
			}else if (ret == 0)
			{
				ret = -1;
				break;
			}else // ret > 0
				break;
		}
		return ret;
	}

	static ssize_t send(const int sock_fd,
						const void *buf,
						const size_t length,
						const int flags)
	{
		return ::send(sock_fd, buf, length, flags);
	}

	static ssize_t recv(const int sock_fd,
						char *buf,
						const size_t length,
						const int flags)
	{
		return ::recv(sock_fd, buf, length, flags);
	}
};

#endif
