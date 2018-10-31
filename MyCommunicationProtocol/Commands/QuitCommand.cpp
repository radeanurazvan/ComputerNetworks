#pragma once

#include "stdio.h"

#include "../Settings/Settings.h"
#include "Command.h"
#include "../Communication/CommunicationChannel.h"
class QuitCommand : public Command {
    public:

    void Execute(const char* args, CommunicationChannel* channel) {
        remove(Settings::sessionFile);
    }
};