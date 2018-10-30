#pragma once

#include "stdio.h"
#include <fstream>
#include <cstring>

#include "Command.h"
#include "../Settings/Settings.h"

using namespace std;

class LoginCommand : public Command {
    private:
    
    void OpenSession() {
        ofstream sessionFile(Settings::sessionPath);
        sessionFile.close();
    }

    public:

    void Execute(const char* commandArguments) {
        FILE * credentialsFile;
        char credentials [100];

        credentialsFile  = fopen (Settings::credentialsStore, "r");
        if (credentialsFile == NULL) {
            printf("Could not open credentials store!\n");
            return;
        }
        
        fgets(credentials , 100 , credentialsFile);
        fclose (credentialsFile);

        if(strcmp(credentials, commandArguments) == 0) {
            this->OpenSession();
        }

    }
};