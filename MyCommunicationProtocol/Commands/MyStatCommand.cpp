#pragma once

#include "stdio.h"
#include "Command.h"

class MyStatCommand : public Command {
    public:
        void Execute(const char* args) {
            printf("%s\n", "Hello mystat");
        }
};