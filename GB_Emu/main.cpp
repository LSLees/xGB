#include <iostream>
#include "cpu.h"
#include "memory.h"

#include <thread>
#include <chrono>


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "no rom entered";
        return 1;
    }

    initMemory();
    if (!loadROM(argv[1])) return 1;

    bootSetup();
    postBootSetup();
    std::system("cls");
    printCPUState();


    for (int i = 0; i < 3; ++i) {
        emulateCycle();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


    return 0;
}