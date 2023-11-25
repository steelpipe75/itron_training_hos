#ifndef MPF_LOG_HPPP
#define MPF_LOG_HPPP

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

extern "C" {
    #include "kernel.h"
}

class MpfLog
{
public:
    MpfLog();
    ~MpfLog();

    void Write(const char* event,ID mpfid, VP blk, const char* file, unsigned int line);
private:
    std::ofstream *ofs;
    std::chrono::steady_clock::time_point start_time;
};

#endif /* #ifndef MPF_LOG_HPPP */
