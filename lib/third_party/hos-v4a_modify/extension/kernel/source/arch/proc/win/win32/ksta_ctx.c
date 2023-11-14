#if 1
/**
 * hos-v4a の kernel/source/arch/proc/win/win32/ksta_ctx.c
 * をもとに改変
 */
#endif
/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  ksta_ctx.c
 * @brief %jp{コンテキスト制御}%en{context control}
 *
 * Copyright (C) 1998-2008 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#include "core/core.h"
#if 1
#include <stdio.h>
#endif

/** %jp{コンテキストの開始} */
void _kernel_sta_ctx(_KERNEL_T_CTXCB *ctxcb)
{
	/* %jp{実行中コンテキストの登録} */
	_kernel_ictxcb.runctxcb = ctxcb;

	/* %jp{スレッドの実行開始} */
	SetEvent(ctxcb->hEvent);
	
	if ( GetCurrentThreadId() == _kernel_ictxcb.dwPrimaryThreadId )
	{
#if 1
		printf("#### Hit Space Key to Exit ####\n");
		while(1) {
			if(GetAsyncKeyState(VK_SPACE) & 0x01 ) {
				break;
			}
			DWORD result = WaitForSingleObject(_kernel_ictxcb.hTerCtxEvent, 10);
			if(result == WAIT_OBJECT_0) {
				break;
			}else if(result == WAIT_TIMEOUT) {
				/* タイムアウト */
			}else {
				printf("Error : WaitForSingleObject() returned WAIT_FAILED");
				ExitProcess(1);
			}
		}
#else
		/* %jp{ダイアログを表示} */
		MessageBox(NULL, _T("Press OK, Exit a process"), _T("Hyper Operationg System V4 Advance for Win32"), MB_OK);
		
		/* %jp{終了} */
		ExitProcess(0);
#endif
	}
}


/* end of file */
