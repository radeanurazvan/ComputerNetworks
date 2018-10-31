#pragma once

#include <string>

#include "ProtocolMessage.h"

class ProtocolOutput {
    private:
        char* message;
    public:
        ProtocolOutput(char* message);
        std::string Decode();
};