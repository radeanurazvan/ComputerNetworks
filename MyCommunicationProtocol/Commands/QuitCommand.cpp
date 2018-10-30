#pragma once

#include "stdio.h"

#include "../Settings/Settings.h"
#include "Command.h"

class QuitCommand : public Command {
    public:

    void Execute(const char* args) {
        printf("removing %d", remove(Settings::sessionFile));
        remove(Settings::sessionFile);
    }
};