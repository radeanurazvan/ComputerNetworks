#include "unistd.h"
#include "stdio.h"

#include "CommunicationChannel.h"

class Pipe : public CommunicationChannel {
    private:
    int channel[2];

    public:
        Pipe() {
            if(pipe(channel) == -1){
                printf("Pipe failed!\n");
            }
        }
        void Read(char* readTarget, int readLimit = 255) {
            read(channel[0], readTarget, readLimit);
        }

        void Write(const char* subject, int bitsLength) {
            write(channel[1], subject, bitsLength);
        }

        void CloseReadDescriptors() {
            close(channel[0]);
        }

        void CloseWriteDescriptors() {
            close(channel[1]);
        }
};