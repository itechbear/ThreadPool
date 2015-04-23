//
// Created by hudong on 4/23/15.
//

#include "delegate.h"

Delegate::Delegate(Work *work)
    : work_(work) {
}

Delegate::~Delegate() {
  // Don't destroy work_ here.
}

void Delegate::operator()() {
  work_->Run();
}

Delegate::Delegate(const Delegate &other)
    : work_(other.work_) {
}
