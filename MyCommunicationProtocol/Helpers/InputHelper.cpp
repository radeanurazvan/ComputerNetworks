#include <string>
#include <cstring>
#include "InputHelper.h"

using namespace std;

const char* InputHelper::InputToCommand(char* input) {
    return strtok(input, " ");
}

const char* InputHelper::InputToArgs(char* input) {
    auto p = strtok(input, " ");
    auto args = strtok(NULL, " ");

    if(args == NULL) {
        return "";
    }

    return args;
}