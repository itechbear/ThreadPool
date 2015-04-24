//
// Created by hudong on 4/23/15.
//

#ifndef UTILS_THREADING_THREADPOOL_DELEGATE_H_
#define UTILS_THREADING_THREADPOOL_DELEGATE_H_

#include <memory>

#include "utils/threading/work.h"

namespace utils {
namespace threading {

class Delegate {
 public:
  explicit Delegate(Work *work);
  explicit Delegate(const Delegate &other);

  virtual ~Delegate();

  void operator()();
 private:
  Work *work_;
};

}  // namespace threading
}  // namespace utils

#endif //UTILS_THREADING_THREADPOOL_DELEGATE_H_
