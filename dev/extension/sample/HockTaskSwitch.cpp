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
    const char *fileName = "HockTaskSwitch.txt";
    this->ofs = new std::ofstream(fileName);
}

CHockTaskSwitch::~CHockTaskSwitch()
{
    this->ofs->close();
}

void CHockTaskSwitch::HockTaskSwitch(ID tskid_old, ID tskid_new)
{
    *(this->ofs) << tskid_old << ", " << tskid_new << std::endl;
}

