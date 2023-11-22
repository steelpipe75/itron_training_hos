#ifndef HOCK_TASK_SWITCH_H
#define HOCK_TASK_SWITCH_H

extern "C" {
    #include "kernel.h"
}

class CHockTaskSwitch
{
public:
    CHockTaskSwitch();
    ~CHockTaskSwitch();

    void HockTaskSwitch(ID tskid_old, ID tskid_new);
};

#endif /* #ifndef HOCK_TASK_SWITCH_H */
