#include <cstring>

#include "CommandAdapter.h"
#include "../Commands/Command.h"
#include "../Commands/LoginCommand.cpp"
#include "../Commands/MyStatCommand.cpp"
#include "../Commands/MyFindCommand.cpp"

#define LOGIN "login"
#define MYSTAT "mystat"
#define MYFIND "myfind"

Command* CommandAdapter::GetInternalCommand(const char* command) {
    if(strcmp(command, LOGIN) == 0) {
        return new LoginCommand();
    }    

    if(strcmp(command, MYSTAT) == 0) {
        return new MyStatCommand();
    }

    if(strcmp(command, MYFIND) == 0) {
        return new MyFindCommand();
    }
    
    return nullptr;
}