extern "C" {
    #include "kernel.h"
}
#include "HockTaskSwitch.h"

CHockTaskSwitch g_HockTaskSwitch;

extern "C" void _kernel_tsk_swi(ID tskid_old, ID tskid_new)
{
    g_HockTaskSwitch.HockTaskSwitch(tskid_old, tskid_new);
}

CHockTaskSwitch::CHockTaskSwitch()
{

}

CHockTaskSwitch::~CHockTaskSwitch()
{

}

void CHockTaskSwitch::HockTaskSwitch(ID tskid_old, ID tskid_new)
{
    (void)tskid_old;
    (void)tskid_new;
}

