/* hos v4a の rel_mpf.c を元に改変 */

#include "core/core.h"
#include "object/mplobj.h"



#if _KERNEL_SPT_GET_MPL


#if _KERNEL_SPT_TGET_MPL && (_KERNEL_OPT_CODE_SIZE <= _KERNEL_OPT_SPEED)	/* %jp{tget_mplありで、サイズ優先なら} */


ER get_mpl(ID mplid, VP *p_blk)
{
	/* %jp{tget_mplで代替する} */
	return tget_mpl(mplid, p_blk, TMO_FEVR);
}

#else


ER rel_mpl(ID mplid, VP blk)
{
	_KERNEL_T_MPLCB_PTR mplcb;
	_KERNEL_T_TSKHDL    tskhdl;
	_KERNEL_T_TCB       *tcb;

	/* %jp{コンテキストチェック} */
#if _KERNEL_SPT_GET_MPL_E_CTX
	if ( _KERNEL_SYS_SNS_DPN() )
	{
		_KERNEL_LEAVE_SVC();	/* %jp{サービスコールから出る}%en{leave service-call} */
		return E_CTX;			/* %jp{コンテキストエラー}%en{Context error} */
	}
#endif
	
	/* %jp{ID のチェック} */
#if _KERNEL_SPT_GET_MPL_E_ID
	if ( !_KERNEL_MPL_CHECK_MPLID(mplid) )
	{
		return E_ID;	/* %jp{不正ID番号}%en{Invalid ID number} */
	}
#endif
	
	_KERNEL_ENTER_SVC();		/* %jp{サービスコールに入る}%en{enter service-call} */
	
	/* %jp{オブジェクト存在チェック} */
#if _KERNEL_SPT_GET_MPL_E_NOEXS
	if ( !_KERNEL_MPL_CHECK_EXS(mplid) )
	{
		_KERNEL_LEAVE_SVC();	/* %jp{サービスコールから出る}%en{leave service-call} */
		return E_NOEXS;			/* %jp{オブジェクト未生成}%en{Non-existant object} */
	}
#endif

	/* %jp{コントロールブロック取得} */
	mplcb = _KERNEL_MPL_ID2MPLCB(mplid);

	/* %jp{待ち行列先頭からタスク取り出し} */
	tskhdl = _KERNEL_MPL_RMH_QUE(mplcb);
	if ( tskhdl != _KERNEL_TSKHDL_NULL )
	{
		VP *p_blk;

		/* %jp{待ちタスクがあれば待ち解除} */
		tcb = _KERNEL_TSK_TSKHDL2TCB(tskhdl);		/* %jp{TCB取得} */
		p_blk = (VP *)_KERNEL_TSK_GET_DATA(tcb);
		*p_blk = blk;
		_KERNEL_TSK_SET_ERCD(tcb, E_OK);			/* %jp{エラーコード設定} */
		_KERNEL_DSP_WUP_TSK(tskhdl);				/* %jp{タスクの待ち解除} */
		_KERNEL_MPL_RMV_TOQ(tskhdl);
		
		/* %jp{タスクディスパッチの実行} */
		_KERNEL_DSP_TSK();
	}
	else
	{
		/* %jp{プールに返却} */
		*(_KERNEL_MPL_T_BLKHDL *)blk = _KERNEL_MPL_GET_FREBLK(mplcb);
		_KERNEL_MPL_SET_FREBLK(mplcb, _KERNEL_MPL_PTR2BLKHDL(mplcb, blk));
	}
	
	_KERNEL_LEAVE_SVC();	/* %jp{サービスコールから出る}%en{leave service-call} */
	
	return E_OK;
}

#endif


#else	/* _KERNEL_SPT_GET_MPL */


#if _KERNEL_SPT_GET_MPL_E_NOSPT


ER get_mpl(ID mplid)
{
	return E_NOSPT;
}

#endif


#endif	/* _KERNEL_SPT_GET_MPL */



/* end of file */
