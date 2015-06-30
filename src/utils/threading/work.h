//
// Created by hudong on 4/23/15.
//

#ifndef UTILS_THREADING_THREADPOOL_WORK_H_
#define UTILS_THREADING_THREADPOOL_WORK_H_

#include <mutex>
#include <condition_variable>

namespace utils {
namespace threading {

class Work {
 private:
  std::mutex mutex_;
  std::condition_variable cv_;
  bool finished_;

 public:
  Work();

  virtual ~Work() {};

  virtual void Run() = 0;

  void RunAll();

  void Before();

  void After();

  void Wait();
};

}  // namespace threading
}  // namespace utils

#endif //UTILS_THREADING_THREADPOOL_WORK_H_
