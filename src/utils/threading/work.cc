//
// Created by hudong on 4/23/15.
//

#include "work.h"

namespace utils {
namespace threading {

Work::Work() : mutex_(), cv_(), finished_(false) {

}

void Work::RunAll() {
  Before();
  Run();
  After();
}

void Work::Before() {
}

void Work::After() {
  finished_ = true;
  cv_.notify_one();
}

void Work::Wait() {
  std::unique_lock<std::mutex> unique_lock(mutex_);
  while (!finished_) {
    cv_.wait(unique_lock);
  }
}

}  // namespace threading
}  // namespace utils

