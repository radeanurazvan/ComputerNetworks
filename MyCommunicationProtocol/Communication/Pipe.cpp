#include "unistd.h"
#include "stdio.h"

#include "CommunicationChannel.h"

class Pipe : public CommunicationChannel {
    private:
    int channel[2];

    void CloseReadDescriptors() {
        close(channel[0]);
    }

    void CloseWriteDescriptors() {
        close(channel[1]);
    }

    public:
        Pipe() {
            if(pipe(channel) == -1){
                printf("Pipe failed!\n");
            }
        }
        char* Read() {
            CloseWriteDescriptors();

            char tmpString[255];
            read(channel[0], tmpString, 255);

            return tmpString;
        }

        void Write(char* subject, int bitsLength) {
            CloseReadDescriptors();

            write(channel[1], subject, bitsLength);
        }
};