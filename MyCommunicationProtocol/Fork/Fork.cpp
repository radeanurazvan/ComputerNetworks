#include "unistd.h"
#include "Fork.h"

Fork::Fork() {
    prebothCallback = postbothCallback = parentCallback = childCallback = [](pid_t x) {};
}

Fork* Fork::OnParent(function<void(pid_t)> parentCallback) {
    this->parentCallback = parentCallback;

    return this;
}

Fork* Fork::OnChild(function<void(pid_t)> childCallback) {
    this->childCallback = childCallback;

    return this;
}

Fork* Fork::BeforeBoth(function<void(pid_t)> bothCallback) {
    this->prebothCallback = bothCallback;

    return this;
}

Fork* Fork::AfterBoth(function<void(pid_t)> bothCallback) {
    this->postbothCallback = bothCallback;

    return this;
}

void Fork::Run() {
    this->childId = fork();

    this->prebothCallback(this->childId);

    if(this->childId > 0) {
        this->parentCallback(this->childId);
    } else {
        this->childCallback(this->childId);
    }

    this->postbothCallback(this->childId);
}