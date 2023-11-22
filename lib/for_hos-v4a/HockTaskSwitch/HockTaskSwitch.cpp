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
    this->start_time = std::chrono::steady_clock::now();
    const char *fileName = "HockTaskSwitch.csv";
    this->ofs = new std::ofstream(fileName);
    *(this->ofs)    << "tskid_old"      << "," 
                    << "tskid_new"      << ","
                    << "diff_time_ms"
                    << std::endl;
}

CHockTaskSwitch::~CHockTaskSwitch()
{
    this->ofs->close();
}

void CHockTaskSwitch::HockTaskSwitch(ID tskid_old, ID tskid_new)
{
    auto crrent_time = std::chrono::steady_clock::now();
    auto diff_time_ms = std::chrono::duration_cast<std::chrono::microseconds>(crrent_time - start_time).count();
    *(this->ofs)    << tskid_old    << "," 
                    << tskid_new    << ","
                    << diff_time_ms
                    << std::endl;
}

