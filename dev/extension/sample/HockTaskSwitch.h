#ifndef HOCK_TASK_SWITCH_H
#define HOCK_TASK_SWITCH_H

#include <iostream>
#include <string>
#include <fstream>

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
};

#endif /* #ifndef HOCK_TASK_SWITCH_H */
