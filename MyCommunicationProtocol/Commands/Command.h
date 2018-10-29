#pragma once

class Command {
    public:
        virtual void Execute(const char* commandArguments) = 0;
};