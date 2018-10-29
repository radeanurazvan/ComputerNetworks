#pragma once

class Protocol {
    private:
        static bool isOpen;

        Protocol();
        static void Open();
        static void Close();
        static bool ReceivedQuitCommand(const char* command);
        static void HandleInputCommand(const char* command, const char* args);

    public:
        static void Run();
};