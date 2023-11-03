#if 1
/**
 * hos-v4a の sample\win\win32\wintimer.c
 * をもとに改変
 */
#endif
/** 
 *  Sample program for Hyper Operating System V4 Advance
 *
 * @file  wintimer.c
 * @brief %jp{Windows用のタイマ}%en{Windows timer object}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


/** %jp{Windows ヘッダファイルの読みこみ} */
#define SIZE  WIN_SIZE
#include <windows.h>
#undef  SIZE

#if 1
#include <process.h>
#endif
#include "kernel.h"
#include "wintimer.h"
#include "arch/proc/win/win32/proc.h"

#if 1
static unsigned __stdcall WinTimer_Thread(void* param);	/**< %jp{タイマ割込み用スレッド関数} */
#else
static DWORD WINAPI WinTimer_Thread(LPVOID param);		/**< %jp{タイマ割込み用スレッド関数} */
#endif
static HANDLE hEventTimer;								/**< %jp{タイマハンドル} */


/** %jp{OS用タイマの初期化} */
void WinTimer_Start(INHNO inhno, int iInterval)
{
	DWORD dwThreadId;
		
	/* %jp{タイマ用イベントの作成} */
	hEventTimer = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	/* %jp{マルチメディアタイマの開始} */
	timeSetEvent(iInterval, 1, (LPTIMECALLBACK)hEventTimer, 0, TIME_PERIODIC | TIME_CALLBACK_EVENT_PULSE);
	
	/* %jp{スレッド生成} */
#if 1
	_beginthreadex(
		NULL,				/* void *security, */
		0,					/* unsigned stack_size, */
		WinTimer_Thread,	/* unsigned ( __stdcall *start_address )( void * ), */
		(void*)inhno,		/* void *arglist, */
		0,					/* unsigned initflag, */
		&dwThreadId			/* unsigned *thrdaddr */
	);
#else
	CreateThread(NULL, 0, WinTimer_Thread, (LPVOID)inhno, 0, &dwThreadId);
#endif
}


/** %jp{タイマ割込み用スレッド関数} */
#if 1
unsigned __stdcall WinTimer_Thread(void* param)
#else
DWORD WINAPI WinTimer_Thread(LPVOID param)
#endif
{
	INHNO inhno;
	
	inhno = (INHNO)param;

	for ( ; ; )
	{
		/* %jp{タイマイベントを待つ} */
		WaitForSingleObject(hEventTimer, INFINITE);

		/* %jp{割込みシグナルを入れる} */
		vsig_int(inhno);
	}
}


/* end of file */
