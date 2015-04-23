//
// Created by hudong on 4/23/15.
//

#include "thread_pool.h"

ThreadPool::~ThreadPool() {
  for (int i = 0; i < core_size_; ++i) {
    delete threads[i];
  }
}

void ThreadPool::Start() {
  threads.resize(core_size_);

  for (int i = 0; i < core_size_; ++i) {
    // Caution: please check null pointers.
    Delegate *delegate = new Delegate(this);
    std::thread *work_thread = new std::thread(*delegate);
    threads.push_back(work_thread);
  }
}

void ThreadPool::Run() {
  while (true) {
    std::unique_lock<std::mutex> lock(mutex_);

    while (work_queue_.size() == 0) {
      cond_var_.wait(lock);
    }
    std::unique_ptr<Work> work(work_queue_.front());
    work_queue_.pop();
    lock.unlock();

    work->Run();
  }
}

ThreadPool::ThreadPool(const int core_size, const int queue_size)
    : work_queue_(), mutex_(), cond_var_(), core_size_(core_size), queue_size_(queue_size) {
}

bool ThreadPool::AddWork(Work *work) {
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
