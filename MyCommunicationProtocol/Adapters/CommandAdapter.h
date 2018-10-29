#pragma once

#include "../Commands/Command.h"

class CommandAdapter {
    private:
     CommandAdapter();
     
    public:
     static Command* GetInternalCommand(const char* command);
};