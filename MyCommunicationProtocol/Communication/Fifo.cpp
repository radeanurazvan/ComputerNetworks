#include <cstring>
#include <string>
#include <sys/stat.h>
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"
#include "stdio.h"

#include "CommunicationChannel.h"

class Fifo : public CommunicationChannel {
    private:
        char fifoName[20] = "fifos/fifo";
        int channel;

    public:
        Fifo() {
            auto random = rand() % 11;
            strcat(fifoName, std::to_string(random).c_str());

            mkfifo(fifoName, 0666);
        }

        void Read(char* readSubject, int readLimit = 255) {
            channel = open(fifoName, O_RDONLY); 
            read(channel, readSubject, readLimit); 

            printf("Read subj %s \n", readSubject);

            close(channel); 
        }

        void Write(const char* subject, int bitsLength) {
            channel = open(fifoName, O_WRONLY); 

            printf("Writing %s \n", subject);

            write(channel, subject, bitsLength); 
            close(channel); 
        }

        void CloseReadDescriptors() {}

        void CloseWriteDescriptors() {}
};