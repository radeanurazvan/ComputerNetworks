#pragma once

#include <functional>

using namespace std;

class Fork {
    private:
        pid_t childId;
        function<void(pid_t)> parentCallback;
        function<void(pid_t)> childCallback;
    public:
        Fork* OnParent(function<void(pid_t)> callback);
        Fork* OnChild(function<void(pid_t)> callback);
        void Run();
};