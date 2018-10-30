#pragma once

class ProtocolInput {
    private:
        char* command;
        char* args;

    public:
        ProtocolInput(char* input);
        char* GetCommand();
        char* GetArgs();
};