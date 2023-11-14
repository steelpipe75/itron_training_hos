#if 1
/**
 * hos-v4a の aplfw\driver\serial\winsock\winsockdrv_constructor.c
 * をもとに改変
 */
#endif
/** 
 *  Hyper Operating System  Application Framework
 *
 * @file  winsockdrv.h
 * @brief %jp{WinSockでシリアルを擬似するドライバ}
 *
 * Copyright (C) 2006-2007 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */

#if 1
#include <process.h>
#endif


#include "winsockdrv_local.h"


/** 仮想関数テーブル */
const T_DRVOBJ_METHODS  WinSockDrv_Methods = 
	{
		{ WinSockDrv_Delete },
		WinSockDrv_Open,
		WinSockDrv_Close,
		WinSockDrv_IoControl,
		WinSockDrv_Seek,
		WinSockDrv_Read,
		WinSockDrv_Write,
		WinSockDrv_Flush,
	};


/** コンストラクタ */
FILE_ERR WinSockDrv_Constructor(C_WINSOCKDRV *self, const T_DRVOBJ_METHODS *pMethods, int iPortNum, int iIntNum, int iBufSize)
{
#if 1
	unsigned	dwThreadId;
#else
	DWORD		dwThreadId;
#endif
	FILE_ERR	ErrCode;
	void		*pRecvMem;
	void		*pSendMem;
	
	/* 仮想関数テーブル */
	if ( pMethods == NULL )
	{
		pMethods = &WinSockDrv_Methods;
	}

	/* バッファ用メモリ確保 */
	if ( (pRecvMem = SysMem_Alloc(iBufSize)) == NULL )
	{
		return FILE_ERR_NG;
	}
	if ( (pSendMem = SysMem_Alloc(iBufSize)) == NULL )
	{
		SysMem_Free(pRecvMem);
		return FILE_ERR_NG;
	}


	/* 親クラスコンストラクタ呼び出し */
	if ( (ErrCode = SyncDrv_Constructor(&self->SyncDrv, pMethods, SYNCDRV_FACTOR_NUM)) != FILE_ERR_OK )
	{
		SysMem_Free(pRecvMem);
		SysMem_Free(pSendMem);
		return ErrCode;
	}
	
	/* メンバ変数初期化 */
	self->iOpenCount  = 0;
	self->iPortNum    = iPortNum;
	self->iIntNum     = iIntNum;
	self->iConnection = FALSE;

	/* バッファ生成 */
	StreamBuf_Create(&self->StmBufRecv, iBufSize, pRecvMem);
	StreamBuf_Create(&self->StmBufSend, iBufSize, pSendMem);

	/* 割込み処理登録 */
	self->hIsr = SysIsr_Create(self->iIntNum, WinSockDrv_Isr, (VPARAM)self);
	
	/* イベント生成 */
	self->hConnectEvent    = CreateEvent(NULL, FALSE, FALSE, NULL);
	self->hDisconnectEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	self->hSendEvent       = CreateEvent(NULL, FALSE, FALSE, NULL);

	/* %jp{スレッド生成} */
#if 1
	self->hRecvThread = (HANDLE)_beginthreadex(NULL, 0, WinSockDrv_Recv, (void *)self, 0, &dwThreadId);
	self->hSendThread = (HANDLE)_beginthreadex(NULL, 0, WinSockDrv_Send, (void *)self, 0, &dwThreadId);
#else
	self->hRecvThread = CreateThread(NULL, 0, WinSockDrv_Recv, (LPVOID)self, 0, &dwThreadId);
	self->hSendThread = CreateThread(NULL, 0, WinSockDrv_Send, (LPVOID)self, 0, &dwThreadId);
#endif

	return FILE_ERR_OK;
}



/* end of file */
