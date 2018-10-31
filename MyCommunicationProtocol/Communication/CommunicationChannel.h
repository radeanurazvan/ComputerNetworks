#pragma once

class CommunicationChannel {
    public:
        virtual void InitRead() = 0;
        virtual void InitWrite() = 0;

        virtual void CloseReadDescriptors() = 0;
        virtual void CloseWriteDescriptors() = 0;

        virtual void Read(char* readTarget, int readLimit = 255) = 0;
        virtual void Write(const char* subject, int bitsLength) = 0;

        virtual const char* GetName() = 0; 
};