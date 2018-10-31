#include <iostream>
#include <cstring>
#include <string>

#include "ProtocolOutput.h"

ProtocolOutput::ProtocolOutput(char* message) {
    this->message = message;
}

std::string ProtocolOutput::Decode() {
    auto stringMessage = std::string(this->message);
    auto delimiterPosition = stringMessage.find(":");

    return stringMessage.substr(delimiterPosition + 1);
}