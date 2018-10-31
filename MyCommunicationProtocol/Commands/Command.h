#pragma once

#include "../Communication/CommunicationChannel.h"

class Command {
    public:
        virtual void Execute(const char* commandArguments, CommunicationChannel* channel) = 0;
};