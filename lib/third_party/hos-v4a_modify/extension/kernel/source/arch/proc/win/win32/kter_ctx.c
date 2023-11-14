#include "core/core.h"

/** %jp{コンテキストの強制終了} */
void _kernel_ter_ctx()
{
	SetEvent(_kernel_ictxcb.hTerCtxEvent);
}


/* end of file */
