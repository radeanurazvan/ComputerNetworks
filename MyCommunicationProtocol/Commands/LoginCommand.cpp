#pragma once

#include "stdio.h"
#include <fstream>
#include <cstring>

#include "Command.h"
#include "../Settings/Settings.h"
#include "../Communication/CommunicationChannel.h"
#include "../Protocol/ProtocolMessage.h"

using namespace std;

class LoginCommand : public Command {
    private:
    
    void OpenSession() {
        ofstream sessionFile(Settings::sessionPath);
        sessionFile.close();
    }

    public:

    void Execute(const char* commandArguments, CommunicationChannel* channel) {
        FILE * credentialsFile;
        char credentials [100];

        credentialsFile  = fopen (Settings::credentialsStore, "r");
        if (credentialsFile == NULL) {
            auto protocolMessage = new ProtocolMessage("Could not open credentials store!\n");
            channel->Write(protocolMessage->GetMessage().c_str(), protocolMessage->GetMessage().length());
            return;
        }
        
        fgets(credentials , 100 , credentialsFile);
        fclose (credentialsFile);

        if(strcmp(credentials, commandArguments) != 0) {
            auto protocolMessage = new ProtocolMessage("Fail");

            channel->Write(protocolMessage->GetMessage().c_str(), protocolMessage->GetMessage().length());
            return;
        }

        this->OpenSession();
        auto protocolMessage = new ProtocolMessage("Success");
        channel->Write(protocolMessage->GetMessage().c_str(), protocolMessage->GetMessage().length());

    }
};