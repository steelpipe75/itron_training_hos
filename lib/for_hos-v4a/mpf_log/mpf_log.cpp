extern "C" {
    #include "mpf_log.h"
}
#include "mpf_log.hpp"

MpfLog g_MpfLog;

extern "C" void mpf_log_write(const char* event,ID mpfid, VP blk, const char* file, unsigned int line)
{
    g_MpfLog.Write(event, mpfid, blk, file, line);
}

MpfLog::MpfLog()
{
    this->start_time = std::chrono::steady_clock::now();
    const char *fileName = "MpfLog.csv";
    this->ofs = new std::ofstream(fileName);
    *(this->ofs)    << "event"          << "," 
                    << "mpfid"          << ","
                    << "blk"            << ","
                    << "file"           << ","
                    << "line"           << ","
                    << "diff_time_ms"
                    << std::endl;
}

MpfLog::~MpfLog()
{
    this->ofs->close();
}

void MpfLog::Write(const char* event,ID mpfid, VP blk, const char* file, unsigned int line)
{
    auto crrent_time = std::chrono::steady_clock::now();
    auto diff_time_ms = std::chrono::duration_cast<std::chrono::microseconds>(crrent_time - start_time).count();
    *(this->ofs)    << event        << "," 
                    << mpfid        << ","
                    << blk          << ","
                    << file         << ","
                    << line         << ","
                    << diff_time_ms << ","
                    << std::endl;
}

