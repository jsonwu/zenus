#include <pthread.h>
#include <string.h>
#include "sock.h"

template<typename handler>
epoll_accepter<handler>::epoll_accepter():
  acceptor_stop_(false),
  listen_port_(0),
  listen_sock_(0),
  worker_num_(0),
  hd_num_(0),
  local_ip_(0)
{ }

template<typename handler>
epoll_accepter<handler>::~epoll_accepter()
{ }

template<typename handler>
int epoll_accepter<handler>::start(unsigned short port,
								   int worker_num,
								   void *arg /*NULL*/)
{
	return this->start(INADDR_ANY, port, worker_num, arg);
}

template<typename handler>
int epoll_accepter<handler>::start(unsigned int ip,
								   unsigned short port,
								   int worker_num,
								   void *arg /*NULL*/)
{
  if (worker_num <= 0)
    return -1;

  this->worker_num_ = worker_num;
  this->local_ip_ = ip;
  this->listen_port_ = port;

  this->listen_sock_ = socket(AF_INET, SOCK_STREAM, 0);
  if (this->listen_sock_ == -1)
    return -1;

  if (sock::set_sockfd_reuseable(this->listen_sock_) == -1)
    return -1;

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->listen_port_);
  addr.sin_addr.s_addr = htonl(this->local_ip_);

  if (::bind(this->listen_sock_, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return -1;

  if (listen(this->listen_sock_, SOMAXCONN) == -1)
    return -1;

  if (pthread_create(&this->accept_thread_id_, NULL, &accept_thread, (void *)this) < 0)
	  return -1;

  for (int i = 0; i < this->worker_num_; ++i)
  {
    epoll_worker *worker = new epoll_worker(true);
    if (worker->start() != 0)
      return -1;
    this->workers_.push_back(worker);
  }
  return 0;
}

template<typename handler>
int epoll_accepter<handler>::stop()
{
	if (this->acceptor_stop_ == true)
		return -1;
	this->acceptor_stop_ = true;
	return 0;
}

template<typename handler>
void* epoll_accepter<handler>::accept_thread(void *arg)
{
  epoll_accepter<handler> *accepter = (epoll_accepter<handler> *)arg; 
  while(!accepter->acceptor_stop_)
  {
    struct sockaddr_in remote_addr;
    socklen_t addr_len = sizeof(remote_addr);
    memset(&remote_addr, 0, addr_len);
    int sock = accept(accepter->listen_sock_, 
                      (struct sockaddr*)&remote_addr, 
                      &addr_len);
    if (sock > 0)
    {
      if(sock::set_noblock(sock) < 0)
      {
        close(sock);
        continue;
      }
      handler *hd = new handler(sock, &remote_addr);
      if (accepter->dispatch(sock, hd) != 0)
      {
        hd->handle_close();
        delete hd;
      }
    }
  }
  return NULL;
}

template<typename handler>
int epoll_accepter<handler>::dispatch(int sock, handler *hd)
{
  int i = this->hd_num_%this->worker_num_;
  int ret = this->workers_[i]->dispatch(sock, hd);
  ++this->hd_num_;
  return ret;
}

