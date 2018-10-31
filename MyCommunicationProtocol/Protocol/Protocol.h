#pragma once

#include "ProtocolInput.h"
#include "../Communication/CommunicationChannel.h"

class Protocol {
    private:
        static bool isOpen;

        Protocol();
        static void Open();
        static void Close();
        static bool ReceivedQuitCommand(const char* command);
        static void HandleInputCommand(const char* command, const char* args, CommunicationChannel* channel);
        static void ForkAndPlay(ProtocolInput* input, CommunicationChannel* channel);
        static bool CanExecuteCommand(const char* command);

    public:
        static void Run();
};