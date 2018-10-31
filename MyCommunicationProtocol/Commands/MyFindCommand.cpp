#pragma once

#include "stdio.h"
#include "Command.h"
#include "../Communication/CommunicationChannel.h"

class MyFindCommand : public Command {
    public:
        void Execute(const char* args, CommunicationChannel* channel) {
            printf("%s\n", "Hello myfind");
        }
};