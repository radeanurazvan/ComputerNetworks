#include "stdio.h"
#include <iostream>

#include "Protocol.h"
#include "../Adapters/CommandAdapter.h"
#include "../Helpers/InputHelper.h"

using namespace std;

bool Protocol::isOpen;

void Protocol::Run() {
    Protocol::Open();

    auto inputHelper = new InputHelper();
    char input[10];


    while(true) {
        cin>>input;

        auto inputCommand = inputHelper->InputToCommand(input);
        auto inputArgs = inputHelper->InputToArgs(input);

        if(Protocol::ReceivedQuitCommand(inputCommand)) {
            Protocol::Close();
            break;
        }

        Protocol::HandleInputCommand(inputCommand, inputArgs);

    }

}

void Protocol::HandleInputCommand(const char* inputCommand, const char* args) {
    auto command = CommandAdapter::GetInternalCommand(inputCommand);

    if (command == nullptr) {
        printf("%s", "Invalid command!");
        return;
    }

    command->Execute(args);
}

bool Protocol::ReceivedQuitCommand(const char* command) {
    return command == "quit";
}

void Protocol::Open() {
    Protocol::isOpen = true;
}

void Protocol::Close(){
    Protocol::isOpen = false;
}