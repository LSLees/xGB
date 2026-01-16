#include <iostream>
#include "xSystem.h"
#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "no rom found";
        return 1;
    }

    xgb* sys = new xgb();

    if (!sys->load(argv[1]))
    {
        std::cerr << "error loading rom";
        delete sys;
        return 1;
    }

    std::cout << "rom loaded\n";

    while (true)
    {
        sys->tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    delete sys;
    return 0;
}