//
// Created by hudong on 4/23/15.
//

#ifndef THREADPOOL_DELEGATE_H_
#define THREADPOOL_DELEGATE_H_

#include "work.h"

class Delegate {
 public:
  explicit Delegate(Work *work);
  explicit Delegate(const Delegate &other);

  virtual ~Delegate();

  void operator()();
 private:
  Work *work_;
};

#endif //THREADPOOL_DELEGATE_H_
