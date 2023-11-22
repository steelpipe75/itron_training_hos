#ifndef HOCK_TASK_SWITCH_H
#define HOCK_TASK_SWITCH_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

extern "C" {
    #include "kernel.h"
}

class CHockTaskSwitch
{
public:
    CHockTaskSwitch();
    ~CHockTaskSwitch();

    void HockTaskSwitch(ID tskid_old, ID tskid_new);
private:
    std::ofstream *ofs;
    std::chrono::steady_clock::time_point start_time;
};

#endif /* #ifndef HOCK_TASK_SWITCH_H */
