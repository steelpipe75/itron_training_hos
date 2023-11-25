#ifndef MPF_LOG_H
#define MPF_LOG_H

#include "kernel.h"

void mpf_log_write(const char* event,ID mpfid, VP blk, const char* file, unsigned int line);

#endif /* #ifndef MPF_LOG_H */
