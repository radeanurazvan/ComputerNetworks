class CommunicationChannel {
    public:
        virtual char* Read() = 0;
        virtual void Write(char* subject, int bitsLength) = 0;
};