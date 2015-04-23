#include <iostream>

#include "thread_pool.h"

using namespace std;

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

  for (int i = 0; i < 13; ++i) {
    Worker *worker = new Worker(i);
    if (!thread_pool->AddWork(worker)) {
      std::cout << "Failed to add a new worker!" << std::endl;
    }
  }

  std::this_thread::sleep_for (std::chrono::seconds(1));

  return 0;
}
