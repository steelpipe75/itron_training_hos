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
	#ifndef HOSV4A_KERNEL_EX_NOUSE_MESSAGEBOX
#include <process.h>
#include "set_thread_name.h"
static unsigned dwThreadId;
static HANDLE hThread = NULL;
static HANDLE hTable[2] = {NULL, NULL};
static unsigned __stdcall MessageBox_Thread(void* pArg);
static unsigned __stdcall MessageBox_Thread(void* pArg)
{
	(void)pArg;
	/* %jp{ダイアログを表示} */
	MessageBox(NULL, _T("Press OK, Exit a process"), _T("Hyper Operationg System V4 Advance for Win32"), MB_OK);
	return 0;
}
	#endif
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
	#ifndef HOSV4A_KERNEL_EX_NOUSE_MESSAGEBOX
		hThread = (HANDLE)_beginthreadex(
			NULL,				/* void *security, */
			0,					/* unsigned stack_size, */
			MessageBox_Thread,	/* unsigned ( __stdcall *start_address )( void * ), */
			NULL,				/* void *arglist, */
			0,					/* unsigned initflag, */
			&dwThreadId			/* unsigned *thrdaddr */
		);
		if(hThread == NULL){
			printf("Error : _beginthreadex() returned NULL\n");
			ExitProcess(1);
		}
		SetThreadName(dwThreadId, "MessageBox_Thread");
		hTable[0] = hThread;
		hTable[1] = _kernel_ictxcb.hTerCtxEvent;
		WaitForMultipleObjects(sizeof(hTable)/sizeof(hTable[0]), hTable, FALSE, INFINITE);
	#else
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
				printf("Error : WaitForSingleObject() returned WAIT_FAILED\n");
				ExitProcess(1);
			}
		}
	#endif
#else
		/* %jp{ダイアログを表示} */
		MessageBox(NULL, _T("Press OK, Exit a process"), _T("Hyper Operationg System V4 Advance for Win32"), MB_OK);
#endif
		
		/* %jp{終了} */
		ExitProcess(0);
	}
}


/* end of file */
