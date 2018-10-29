#include <string>
#include <cstring>
#include "InputHelper.h"

using namespace std;

const char* InputHelper::InputToCommand(char* input) {
    return strtok(input, " ");
}

const char* InputHelper::InputToArgs(char* input) {
    std::string stringInput = input;
    return stringInput.substr(stringInput.find(" ") + 1).c_str(); 
}