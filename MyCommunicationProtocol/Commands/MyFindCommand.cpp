#pragma once

#include "stdio.h"
#include "Command.h"

class MyFindCommand : public Command {
    public:
        void Execute(const char* args) {
            printf("%s\n", "Hello myfind");
        }
};