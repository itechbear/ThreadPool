//
// Created by hudong on 4/23/15.
//

#ifndef THREADPOOL_WORK_H_
#define THREADPOOL_WORK_H_

class Work {
 public:
  virtual ~Work() {};

  virtual void Run() = 0;
};

#endif //THREADPOOL_WORK_H_
