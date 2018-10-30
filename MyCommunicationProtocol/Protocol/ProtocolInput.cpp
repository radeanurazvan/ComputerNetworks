#include <cstring>

#include "ProtocolInput.h"


ProtocolInput::ProtocolInput(char* input) {
    this->command = strtok(input, " ");

    this->args = strtok(NULL, " ");

    if(this->args == NULL) {
        this->args = "";
    }
}

char* ProtocolInput::GetCommand() {
    return this->command;
}

char* ProtocolInput::GetArgs() {
    return this->args;
}