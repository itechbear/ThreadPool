#include <iostream>

#include "utils/threading/thread_pool.h"

using namespace std;
using namespace utils::threading;

class Worker : public Work {
 public:
  Worker(int index) : index_(index) {};

  void Run() {
    std::cout << "index: " << index_ << std::endl;
  }

 private:
  int index_;
};

int main() {
  std::unique_ptr<ThreadPool> thread_pool(new ThreadPool(5, 10));
  thread_pool->Start();
  std::vector<std::shared_ptr<Worker>> workers;

  for (int i = 0; i < 200; ++i) {
    std::shared_ptr<Worker> worker(new Worker(i));
    if (!thread_pool->AddWork(worker)) {
      // std::cout << i << " : Failed to add a new worker!" << std::endl;
    } else {
      workers.push_back(worker);
    }
  }

  for (auto worker : workers) {
    worker.get()->Wait();
  }

  // Don't worray about pending threads. They will be cancelled
  // and destroyed once thread_pool goes out of scope.

  return 0;
}
