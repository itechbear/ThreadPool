//
// Created by hudong on 4/23/15.
//

#ifndef UTILS_THREADING_THREADPOOL_THREAD_POOL_H_
#define UTILS_THREADING_THREADPOOL_THREAD_POOL_H_

#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <memory>

#include "utils/threading/delegate.h"

namespace utils {
namespace threading {

class ThreadPool : public Work {
 public:
  ThreadPool(const size_t core_size, const size_t queue_size);

  ~ThreadPool();

  void Start();

  void WaitUntilAllThreadsFinish();

  void Run() override;

  bool AddWork(std::shared_ptr<Work> work,
               bool check_queue = true);

 private:
  std::vector<std::shared_ptr<Delegate>> delegates_;
  std::vector<std::shared_ptr<std::thread>> threads_;
  std::mutex mutex_;
  std::condition_variable cond_var_;
  std::queue<std::shared_ptr<Work>> work_queue_;
  const size_t core_size_;
  const size_t queue_size_;
};

}  // namespace threading
}  // namespace utils

#endif // UTILS_THREADING_THREADPOOL_THREAD_POOL_H_
