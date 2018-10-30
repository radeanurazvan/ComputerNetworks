#pragma once

#include "stdio.h"
#include "Command.h"

class LoginCommand : public Command {
    public:
        void Execute(const char* commandArguments) {
            printf("%s\n", "Just sayin hello from login");
        }
};