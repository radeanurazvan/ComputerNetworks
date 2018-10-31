#pragma once

class CommunicationChannel {
    public:
        virtual void CloseReadDescriptors() = 0;
        virtual void CloseWriteDescriptors() = 0;

        virtual void Read(char* readTarget, int readLimit = 255) = 0;
        virtual void Write(const char* subject, int bitsLength) = 0;
};