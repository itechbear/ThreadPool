//
// Created by hudong on 4/23/15.
//

#ifndef UTILS_THREADING_THREADPOOL_WORK_H_
#define UTILS_THREADING_THREADPOOL_WORK_H_

namespace utils {
namespace threading {

class Work {
 public:
  virtual ~Work() {};

  virtual void Run() = 0;
};

}  // namespace threading
}  // namespace utils

#endif //UTILS_THREADING_THREADPOOL_WORK_H_
