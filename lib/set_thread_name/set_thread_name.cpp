extern "C" {
    #include "set_thread_name.h"
}
//
// Usage: SetThreadName ((DWORD)-1, "MainThread");
//
#include <windows.h>
#if defined(_MSC_VER)
const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)
#endif /* #if defined(_MSC_VER) */
extern "C" void SetThreadName(DWORD dwThreadID, const char* threadName) {
#if defined(_MSC_VER)
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = threadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable: 6320 6322)
    __try{
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
    }
    __except (EXCEPTION_EXECUTE_HANDLER){
    }
#pragma warning(pop)
#else /* #if defined(_MSC_VER) */
    /* 何もしない */
    (void)dwThreadID; /* 使用しない引数警告対策 */
    (void)threadName; /* 使用しない引数警告対策 */
#endif /* #if defined(_MSC_VER) */
}

