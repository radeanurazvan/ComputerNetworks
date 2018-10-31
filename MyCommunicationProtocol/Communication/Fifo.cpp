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

        int readEnd;
        int writeEnd;

    public:
        Fifo() {
            auto random = rand() % 11;
            strcat(fifoName, std::to_string(random).c_str());

            mkfifo(fifoName, 0777);
        }

        void Read(char* readSubject, int readLimit = 255) {
            auto charsRead = read(readEnd, readSubject, readLimit); 
            readSubject[charsRead] = NULL;
        }

        void Write(const char* subject, int bitsLength) {
            write(writeEnd, subject, bitsLength); 
        }

        void InitRead() {
            readEnd = open(fifoName, O_RDONLY);
        }

        void InitWrite() {
            writeEnd = open(fifoName, O_WRONLY);
        }

        void CloseReadDescriptors() {
            //close(readEnd);
        }

        void CloseWriteDescriptors() {
            //close(writeEnd);
        }

        const char* GetName() {
            return "Fifo";
        }
};