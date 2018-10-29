#include "CommandAdapter.h"
#include "../Commands/Command.h"
#include "../Commands/LoginCommand.cpp"


Command* CommandAdapter::GetInternalCommand(const char* command) {
    return new LoginCommand();
}