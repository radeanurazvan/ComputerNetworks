#pragma once

#include "stdio.h"
#include <cstring>

#include "Command.h"
#include "../Communication/CommunicationChannel.h"

class MyFindCommand : public Command {
    public:
        void Execute(const char* args, CommunicationChannel* channel) {
            char helloMessage[] = "Hello myfind";

            channel->Write(helloMessage, strlen(helloMessage));
        }
};