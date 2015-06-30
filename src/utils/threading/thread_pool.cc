//
// Created by hudong on 4/23/15.
//

#include "utils/threading/thread_pool.h"

#include <glog/logging.h>

namespace utils {
namespace threading {

ThreadPool::~ThreadPool() {
  for (int i = 0; i < core_size_; ++i) {
    AddWork(nullptr);
  }
  cond_var_.notify_all();
  for (size_t i = 0; i < threads_.size(); ++i) {
    threads_.at(i).join();
  }
  threads_.clear();
}

void ThreadPool::Start() {
  for (int i = 0; i < core_size_; ++i) {
    Delegate delegate(this);
    threads_.push_back(std::thread(&Delegate::Run, delegate));
  }
}

void ThreadPool::Run() {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex_);

    while (work_queue_.size() == 0) {
      cond_var_.wait(lock);
    }
    std::shared_ptr<Work> work = work_queue_.front();
    work_queue_.pop();
    lock.unlock();

    if (work.get() == nullptr) {
      break;
    }

    work->RunAll();
  }
}

ThreadPool::ThreadPool(const size_t core_size, const size_t queue_size)
    : threads_(), work_queue_(), mutex_(), cond_var_(),
      core_size_(core_size), queue_size_(queue_size) {
  threads_.reserve(core_size_);
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
