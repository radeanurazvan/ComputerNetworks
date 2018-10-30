#include "stdio.h"
#include <iostream>
#include <cstring>

#include "Protocol.h"
#include "ProtocolInput.h"
#include "../Fork/Fork.h"
#include "../Adapters/CommandAdapter.h"

using namespace std;

bool Protocol::isOpen;

void Protocol::Run() {
    Protocol::Open();

    char input[100];

    while(Protocol::isOpen) {
        cin.getline(input, 255);

        auto protocolInput = new ProtocolInput(input);

        auto fork = new Fork();
        fork
            ->BeforeBoth([protocolInput](pid_t childId) {
                if(Protocol::ReceivedQuitCommand(protocolInput->GetCommand())) {
                    Protocol::Close();
                }
            })
            ->OnParent([](pid_t childId) {
                printf("I am parent\n");
            })
            ->OnChild([protocolInput](pid_t childId) {
                Protocol::HandleInputCommand(
                    protocolInput->GetCommand(), 
                    protocolInput->GetArgs()
                );
            })
            ->Run();
        
        if(!Protocol::isOpen) {
            break;
        }

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
    printf("Clsing, bye");
    Protocol::isOpen = false;
}