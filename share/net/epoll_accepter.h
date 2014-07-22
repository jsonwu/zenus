#ifndef EPOLL_ACCEPTER_H_
#define EPOLL_ACCEPTER_H_

#include <vector>
#include <unistd.h>

#include "sock.h"
#include "epoll_worker.h"
using namespace std;

template<typename handler>
class epoll_accepter
{
public:
  epoll_accepter();
  ~epoll_accepter();

  int start(unsigned short port, int worker_num, void *arg = NULL);
  int start(unsigned int ip, unsigned short port, int worker_num, void *arg = NULL);
  int stop();

  static void *accept_thread(void *arg);

  int dispatch(int socket, handler *hd);
private:
  bool acceptor_stop_;
  unsigned short listen_port_;
  int listen_sock_;
  int worker_num_;
  int hd_num_;
  unsigned int local_ip_;
  pthread_t accept_thread_id_;
  vector<epoll_worker *> workers_;
};

#include "epoll_accepter.cpp"

#endif
