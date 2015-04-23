//
// Created by hudong on 4/23/15.
//

#ifndef THREADPOOL_THREAD_POOL_H_
#define THREADPOOL_THREAD_POOL_H_

#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>

#include "delegate.h"

class ThreadPool : public Work {
 public:
  ThreadPool(const int core_size, const int queue_size);

  ~ThreadPool();

  void Start();

  void Run() override;

  bool AddWork(Work *);

 private:
  std::mutex mutex_;
  std::condition_variable cond_var_;
  std::queue<Work *> work_queue_;
  const int core_size_;
  const int queue_size_;
  std::vector<std::thread *>threads;
};

#endif //THREADPOOL_THREAD_POOL_H_
