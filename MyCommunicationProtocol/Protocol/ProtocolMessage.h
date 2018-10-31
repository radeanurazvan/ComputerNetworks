#pragma once

#include <string>

class ProtocolMessage {
    private:
        std::string message;
    public:
        ProtocolMessage(const char* message);
        std::string GetMessage();
};