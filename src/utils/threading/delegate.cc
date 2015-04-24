//
// Created by hudong on 4/23/15.
//

#include "utils/threading/delegate.h"

namespace utils {
namespace threading {

Delegate::Delegate(Work* work)
    : work_(work) {
}

Delegate::~Delegate() {
  // Don't destroy work_ here, because we don't and shouldn't
  // have the ownership of *work_.
}

void Delegate::operator()() {
  work_->Run();
}

Delegate::Delegate(const Delegate &other)
    : work_(other.work_) {
}

}  // namespace threading
}  // namespace utils
