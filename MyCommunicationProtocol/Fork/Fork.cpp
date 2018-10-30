#include "unistd.h"
#include "Fork.h"

Fork* Fork::OnParent(function<void(pid_t)> parentCallback) {
    this->parentCallback = parentCallback;

    return this;
}

Fork* Fork::OnChild(function<void(pid_t)> childCallback) {
    this->childCallback = childCallback;

    return this;
}

void Fork::Run() {
    this->childId = fork();
    if(this->childId > 0) {
        this->parentCallback(this->childId);
    } else {
        this->childCallback(this->childId);
    }
}