#include "stdio.h"
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <vector>

#include "Protocol.h"
#include "ProtocolInput.h"
#include "ProtocolOutput.h"
#include "ProtocolMessage.h"
#include "../Fork/Fork.h"
#include "../Adapters/CommandAdapter.h"

#include "../Communication/Pipe.cpp"
#include "../Communication/Fifo.cpp"
#include "../Communication/SocketPair.cpp"

#include "../Guards/AuthGuard.h"

using namespace std;

bool Protocol::isOpen;

void Protocol::Run() {
    Protocol::Open();

    char input[100];

    while(Protocol::isOpen) {
        cin.getline(input, 255);

        auto protocolInput = new ProtocolInput(input);

        CommunicationChannel* channels[3] =  { new Pipe(), new Fifo(), new SocketPair() };
        for(auto channel : channels) {
            Protocol::ForkAndPlay(protocolInput, channel);
        }
    }

}

void Protocol::HandleInputCommand(const char* inputCommand, const char* args, CommunicationChannel* channel) {
    auto command = CommandAdapter::GetInternalCommand(inputCommand);

    if (command == nullptr) {
        auto protocolMessage = new ProtocolMessage("Invalid command!");
        channel->Write(protocolMessage->GetMessage().c_str(), protocolMessage->GetMessage().length());
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

void Protocol::ForkAndPlay(ProtocolInput* protocolInput, CommunicationChannel* channel) {
    auto fork = new Fork();
        fork
            ->BeforeBoth([protocolInput](pid_t childId) {
                if(Protocol::ReceivedQuitCommand(protocolInput->GetCommand())) {
                    Protocol::Close();
                }
            })
            ->OnParent([channel](pid_t childId) {
                channel->InitRead();
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

                cout<<"Parent received from "<<channel->GetName()<<": "<<output->Decode()<<endl;
            })
            ->OnChild([channel, protocolInput](pid_t childId) {

                channel->InitWrite();

                auto canExecute = Protocol::CanExecuteCommand(protocolInput->GetCommand());
                
                if(!canExecute) {
                    char errorMessage[] = "Cannot execute. Check your login status\n"; 
                    channel->Write(errorMessage, strlen(errorMessage));

                    exit(0);
                    return;
                } 

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

bool Protocol::CanExecuteCommand(const char*  command){
    if(strcmp(command, "quit") == 0) {
        return true;
    }

    auto isAuthenticated = AuthGuard().IsAuthenticated();

    if(strcmp(command, "login") == 0) {
        if(isAuthenticated) {
            return false;
        }

        return true;
    }

    return isAuthenticated;
}