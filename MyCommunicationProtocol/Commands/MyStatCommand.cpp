#pragma once

#include "stdio.h"
#include "Command.h"
#include <string>
#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "../File/FileMetadata.h"

using namespace std;

class MyStatCommand : public Command {
    private:
    FILE* fileUnderStat;

    float GetFileSize(const char* file) {
        fseek(fileUnderStat,0,SEEK_END);
        auto size = ftell(fileUnderStat);

        return size;
    }

    char* GetCreatedAt(const char* file) {
        struct stat t_stat;
        stat(file, &t_stat);
        struct tm * timeinfo = localtime(&t_stat.st_ctime);

        return asctime(timeinfo);
    }

    char* GetModifiedAt(const char* file) {
        struct stat t_stat;
        stat(file, &t_stat);
        struct tm * timeinfo = localtime(&t_stat.st_atime);

        return asctime(timeinfo);
    }

    public:
    
    void Execute(const char* args) {
        fileUnderStat = fopen(args,"rb");

        if(fileUnderStat == NULL) {
            cout<<"Invalid file!\n";
            return;
        }

        auto metadata = new FileMetadata();

        metadata->title = (char*)args;
        metadata->size = this->GetFileSize(args);
        metadata->createdAt = this->GetCreatedAt(args);
        metadata->modifiedAt = this->GetModifiedAt(args);

        fclose(fileUnderStat);

        cout<<metadata->ToInline();
    }
};