//
// Created by hudong on 4/23/15.
//

#include "utils/threading/thread_pool.h"

namespace utils {
namespace threading {

ThreadPool::~ThreadPool() {
}

void ThreadPool::Start() {
  for (int i = 0; i < core_size_; ++i) {
    Delegate delegate(this);
    std::shared_ptr<std::thread> work_thread(new std::thread(delegate));
    threads.push_back(work_thread);
    // Detach each thread. Or the destructor of std::thread would
    // call std::terminate().
    work_thread->detach();
  }
}

void ThreadPool::Run() {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex_);

    while (work_queue_.size() == 0) {
      cond_var_.wait(lock);
    }
    std::shared_ptr<Work> work(work_queue_.front());
    work_queue_.pop();
    lock.unlock();

    work->Run();
  }
}

ThreadPool::ThreadPool(const int core_size, const int queue_size)
    : work_queue_(), mutex_(), cond_var_(), core_size_(core_size), queue_size_(queue_size) {
  threads.resize(core_size_);
}

bool ThreadPool::AddWork(std::shared_ptr<Work> work) {
  bool result = true;

  mutex_.lock();
  if (work_queue_.size() >= queue_size_) {
    result = false;
  } else {
    work_queue_.push(work);
    cond_var_.notify_one();
  }
  mutex_.unlock();

  return result;
}

}  // namespace threading
}  // namespace utils
