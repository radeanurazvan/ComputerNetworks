#pragma once

#include "stdio.h"
#include "Command.h"

#define CREDENTIALS_STORE "credentials.txt"

class LoginCommand : public Command {
    public:

    void Execute(const char* commandArguments) {
        FILE * credentialsFile;
        char credentials [100];

        credentialsFile  = fopen (CREDENTIALS_STORE, "r");
        if (credentialsFile == NULL) {
            printf("Could not open credentials store!\n");
            return;
        }
        
        fgets(credentials , 100 , credentialsFile);
        fclose (credentialsFile);

        printf("My credentials are %s, I entered %s", credentials, commandArguments);
    }
};