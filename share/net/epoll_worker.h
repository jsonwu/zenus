#ifndef EPOLL_WORKER_H_
#define EPOLL_WORKER_H_

#include <map>
#include <pthread.h>
#include <sys/epoll.h>
#include "epoll_handler.h"

class epoll_worker
{
public:
  epoll_worker(bool edge_trigger = true);
  virtual ~epoll_worker(void);
  int start(void);
  int stop(void);
  int dispatch(const int sock, epoll_handler *hd);
  int remove(const int sock);

private:
  int get_max_events();
  void run_handlers();
  static void* work_thread(void *arg);

private:
  bool edge_trigger_;
  bool work_stop_;
  int epoll_fd_;
  int max_events_;

  pthread_rwlock_t rwlock_;

  pthread_t thread_worker_id_;

  struct epoll_event *events_;
  std::map<int, epoll_handler*>  handlers_;
};

#endif
