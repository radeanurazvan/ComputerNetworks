#include "stdio.h"
#include <sys/wait.h>
#include <iostream>
#include <cstring>

#include "Protocol.h"
#include "ProtocolInput.h"
#include "ProtocolOutput.h"
#include "../Fork/Fork.h"
#include "../Adapters/CommandAdapter.h"

#include "../Communication/Pipe.cpp"

using namespace std;

bool Protocol::isOpen;

void Protocol::Run() {
    Protocol::Open();

    char input[100];

    while(Protocol::isOpen) {
        cin.getline(input, 255);

        auto protocolInput = new ProtocolInput(input);

        auto channel = new Pipe();
        auto fork = new Fork();
        fork
            ->BeforeBoth([protocolInput](pid_t childId) {
                if(Protocol::ReceivedQuitCommand(protocolInput->GetCommand())) {
                    Protocol::Close();
                }
            })
            ->OnParent([channel](pid_t childId) {
                channel->CloseWriteDescriptors();                

                int status;
                waitpid(childId, &status, 0);

                if(!Protocol::isOpen) {
                    return;
                }
                
                char result[255];
                channel->Read(result);
                channel->CloseReadDescriptors();

                auto output = new ProtocolOutput(result);

                cout<<"Parent received "<<output->Decode()<<endl;
            })
            ->OnChild([channel, protocolInput](pid_t childId) {
                channel->CloseReadDescriptors();

                Protocol::HandleInputCommand(
                    protocolInput->GetCommand(), 
                    protocolInput->GetArgs(),
                    channel
                );

                channel->CloseWriteDescriptors();

                exit(0);
            })
            ->Run();

    }

}

void Protocol::HandleInputCommand(const char* inputCommand, const char* args, CommunicationChannel* channel) {
    auto command = CommandAdapter::GetInternalCommand(inputCommand);

    if (command == nullptr) {
        printf("Invalid command! %s\n", inputCommand);
        return;
    }

    command->Execute(args, channel);
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