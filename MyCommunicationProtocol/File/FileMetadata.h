#pragma once

#include <cstring>
#include <string>

using namespace std;

class FileMetadata {
    public:
        string title;

        string createdAt;
        string modifiedAt;
        float size;

        string ToInline() {
            return "Title: " + title + " has size: " + std::to_string(size) + ". Exists since: " + createdAt + ". Last modified at: " + modifiedAt;
        }
};