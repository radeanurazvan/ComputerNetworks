#include <cstring>

#include "ProtocolMessage.h"

ProtocolMessage::ProtocolMessage(const char* message) {
    auto lengthAsString = std::to_string(strlen(message));
    
    this->message = lengthAsString;
    this->message += ":" + std::string(message);
}

std::string ProtocolMessage::GetMessage() {
    return this->message;
}