#include "stdio.h"
#include <iostream>
#include <cstring>

#include "Protocol.h"
#include "ProtocolInput.h"
#include "../Adapters/CommandAdapter.h"
using namespace std;

bool Protocol::isOpen;

void Protocol::Run() {
    Protocol::Open();

    char input[100];

    while(Protocol::isOpen) {
        cin.getline(input, 255);
        char copy[255];

        auto protocolInput = new ProtocolInput(input);

        if(Protocol::ReceivedQuitCommand(protocolInput->GetCommand())) {
            Protocol::Close();
            break;
        }

        Protocol::HandleInputCommand(
            protocolInput->GetCommand(), 
            protocolInput->GetArgs()
        );

    }

}

void Protocol::HandleInputCommand(const char* inputCommand, const char* args) {
    auto command = CommandAdapter::GetInternalCommand(inputCommand);

    if (command == nullptr) {
        printf("Invalid command! %s\n", inputCommand);
        return;
    }

    command->Execute(args);
}

bool Protocol::ReceivedQuitCommand(const char* command) {
    return strcmp(command, "quit") == 0;
}

void Protocol::Open() {
    Protocol::isOpen = true;
}

void Protocol::Close(){
    Protocol::isOpen = false;
}