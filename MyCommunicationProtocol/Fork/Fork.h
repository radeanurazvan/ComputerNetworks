#pragma once

#include <functional>

using namespace std;

class Fork {
    private:
        pid_t childId;
        function<void(pid_t)> parentCallback;
        function<void(pid_t)> childCallback;
        function<void(pid_t)> prebothCallback;
        function<void(pid_t)> postbothCallback;
    public:
        Fork();
        Fork* OnParent(function<void(pid_t)> callback);
        Fork* OnChild(function<void(pid_t)> callback);
        Fork* BeforeBoth(function<void(pid_t)> callback);
        Fork* AfterBoth(function<void(pid_t)> callback);
        void Run();
};