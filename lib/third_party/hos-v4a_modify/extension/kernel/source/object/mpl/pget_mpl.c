/* hos v4a の pget_mpf.c を元に改変 */

#include "core/core.h"
#include "object/mplobj.h"



#if _KERNEL_SPT_PGET_MPL


#if _KERNEL_SPT_TGET_MPL && (_KERNEL_OPT_CODE_SIZE <= _KERNEL_OPT_SPEED)	/* %jp{tget_mplありで、サイズ優先なら} */

/** %jp{可変長メモリプールの獲得(ポーリング)}
 * @param  mplid	%jp{メモリブロック獲得対象の可変長メモリプールのID番号}
 * @param  p_blkf	%jp{可変長メモリプール生成情報を入れたパケットへのポインタ}
 * @retval E_OK     %jp{正常終了}%en{Normal completion}
 * @retval E_ID     %jp{不正ID番号(mplidが不正あるいは使用できない)}
 * @retval E_NOEXS  %jp{オブジェクト未生成(対象可変長メモリプールが未登録)}
 * @retval E_PAR    %jp{パラメータエラー(p_blk, tmoutが不正)}
 * @retval E_RLWAI  %jp{待ち状態の強制解除(待ち状態の間にrel_waiを受付)}
 * @retval E_DLT    %jp{待ちオブジェクトの削除(待ち状態の間に可変長メモリプールが削除)}
 */
ER pget_mpl(ID mplid, VP *p_blk)
{
	/* %jp{tget_mplで代替する} */
	return tget_mpl(mplid, p_blk, TMO_POL);
}

#else


/** %jp{可変長メモリプールの獲得(ポーリング)}
 * @param  mplid	%jp{メモリブロック獲得対象の可変長メモリプールのID番号}
 * @param  p_blkf	%jp{可変長メモリプール生成情報を入れたパケットへのポインタ}
 * @retval E_OK     %jp{正常終了}
 * @retval E_ID     %jp{不正ID番号(mplidが不正あるいは使用できない)}
 * @retval E_NOEXS  %jp{オブジェクト未生成(対象可変長メモリプールが未登録)}
 * @retval E_PAR    %jp{パラメータエラー(p_blk, tmoutが不正)}
 * @retval E_RLWAI  %jp{待ち状態の強制解除(待ち状態の間にrel_waiを受付)}
 * @retval E_DLT    %jp{待ちオブジェクトの削除(待ち状態の間に可変長メモリプールが削除)}
 */
ER pget_mpl(ID mplid, VP *p_blk)
{
	_KERNEL_T_MPLCB_PTR  mplcb;
	_KERNEL_MPL_T_BLKHDL blkhdl;
	VP                   blkptr;
	ER                   ercd;
	
	
	/* %jp{ID のチェック} */
#if _KERNEL_SPT_PGET_MPL_E_ID
	if ( !_KERNEL_MPL_CHECK_MPLID(mplid) )
	{
		return E_ID;	/* %jp{不正ID番号}%en{Invalid ID number} */
	}
#endif
	
	_KERNEL_ENTER_SVC();		/* %jp{サービスコールに入る}%en{enter service-call} */
	
	/* %jp{オブジェクト存在チェック} */
#if _KERNEL_SPT_PGET_MPL_E_NOEXS
	if ( !_KERNEL_MPL_CHECK_EXS(mplid) )
	{
		_KERNEL_LEAVE_SVC();	/* %jp{サービスコールから出る}%en{leave service-call} */
		return E_NOEXS;			/* %jp{オブジェクト未生成}%en{Non-existant object} */
	}
#endif

	/* %jp{コントロールブロック取得} */
	mplcb = _KERNEL_MPL_ID2MPLCB(mplid);
	
	/* %jp{可変長メモリプールカウンタ取得} */
	blkhdl = _KERNEL_MPL_GET_FREBLK(mplcb);
	
	if ( blkhdl != _KERNEL_MPL_BLKHDL_NULL )
	{
		/* %jp{可変長メモリプール資源が獲得できれば成功} */
		blkptr = _KERNEL_MPL_BLKHDL2PTR(mplcb, blkhdl);
		*p_blk = blkptr;
		_KERNEL_MPL_SET_FREBLK(mplcb, *(_KERNEL_MPL_T_BLKHDL *)blkptr);
		_KERNEL_MPL_SET_FBLKCNT(mplcb, _KERNEL_MPL_GET_FBLKCNT(mplhdl) - 1);
		ercd = E_OK;
	}
	else
	{
		ercd = E_TMOUT;
	}
	
	_KERNEL_LEAVE_SVC();	/* %jp{オブジェクト未生成}%en{Non-existant object} */
	
	return ercd;
}

#endif


#else	/* _KERNEL_SPT_PGET_MPL */


#if _KERNEL_SPT_PGET_MPL_E_NOSPT

/** %jp{可変長メモリプールの獲得(ポーリング)}
 * @param  mplid	%jp{メモリブロック獲得対象の可変長メモリプールのID番号}
 * @param  p_blkf	%jp{可変長メモリプール生成情報を入れたパケットへのポインタ}
 * @retval E_NOSPT  %jp{未サポート機能}%en{Unsupported function}
 */
ER pget_mpl(ID mplid)
{
	return E_NOSPT;
}

#endif


#endif	/* _KERNEL_SPT_PGET_MPL */



/* end of file */
