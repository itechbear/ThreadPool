#include <iostream>

#include <google/heap-profiler.h>

#include "utils/threading/thread_pool.h"

using namespace std;
using namespace utils::threading;

class Worker : public Work {
 public:
  Worker(int index) : index_(index) {};

  void Run() {
    // std::cout << "index: " << index_ << std::endl;
  }

  ~Worker() {
    std::cout << "destructed!" << std::endl;
  }

 private:
  int index_;
};

int main() {
  std::unique_ptr<ThreadPool> thread_pool(new ThreadPool(5, 10));

  HeapProfilerStart("thread_pool");

  thread_pool->Start();

  for (int i = 0; i < 20; ++i) {
    std::shared_ptr<Worker> worker(new Worker(i));
    if (!thread_pool->AddWork(worker, true)) {
      // std::cout << i << " : Failed to add a new worker!" << std::endl;
    }
    std::cout << "finished!" << std::endl;
    // worker->Wait(); // wait until this worker finishes, synchronously.
  }

  thread_pool->WaitUntilAllThreadsFinish();

  std::cout << "all are finished!" << std::endl;

  HeapProfilerStop();

  // Don't worray about pending threads. They will be cancelled
  // and destroyed once thread_pool goes out of scope.

  return 0;
}
