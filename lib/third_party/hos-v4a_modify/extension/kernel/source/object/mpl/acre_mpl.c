/* hos v4a の acre_mpf.c を元に改変 */

#include "core/core.h"
#include "object/mplobj.h"



#if _KERNEL_SPT_ACRE_MPL

/** %jp{可変長メモリプールの生成(ID番号自動割付け)}
 * @param  pk_cmpl	      %jp{可変長メモリプール生成情報を入れたパケットへのポインタ}
 * @retval %jp{正の値}%en{positiv-value} %jp{生成した可変長メモリプールのID番号}
 * @retval E_NOID  %jp{ID番号不足(割付可能な可変長メモリプールIDが無い)}
 * @retval E_RSATR %jp{予約属性(mplatrが不正あるいは使用できない)}
 */
ER_ID acre_mpl(const T_CMPL *pk_cmpl)
{
	ID    mplid;
	ER_ID erid;

	/* %jp{属性チェック}%en{check attribute} */
#if _KERNEL_SPT_ACRE_MPL_E_RSATR
	if ( ((pk_cmpl->mplatr & TA_TPRI) == 0 && !_KERNEL_SPT_MPL_TA_TFIFO)
		|| ((pk_cmpl->mplatr & TA_TPRI) != 0 && !_KERNEL_SPT_MPL_TA_TPRI) )
	{
		return E_RSATR;	/* %jp{予約属性}%en{Reserved attribute} */
	}
#endif

	_KERNEL_ENTER_SVC();		/* %jp{サービスコールに入る}%en{enter service-call} */
	
	/* %jp{空きID探索} */
	for ( mplid = _KERNEL_MPL_TMAX_ID; mplid >= _KERNEL_MPL_TMIN_ID; mplid-- )
	{
		if ( !_KERNEL_MPL_CHECK_EXS(mplid) )
		{
			break;
		}
	}

	/* %jp{空きID探索チェック} */
#if _KERNEL_SPT_ACRE_MPL_E_NOID
	if ( mplid < _KERNEL_MPL_TMIN_ID )
	{
		_KERNEL_LEAVE_SVC();	/* %jp{サービスコールから出る}%en{leave service-call} */
		return E_NOID;			/* %jp{ID番号不足} */
	}
#endif
	
	/* %jp{オブジェクト生成} */
#if (_KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_PTRARRAY) && _KERNEL_SPT_ACRE_MPL_E_NOMEM
	erid = (ER_ID)_kernel_cre_mpl(mplid, pk_cmpl);
	if ( erid == E_OK )
	{
		erid = (ER_ID)mplid;	/* %jp{エラーでなければ可変長メモリプールIDを格納} */
	}
#else
	_kernel_cre_mpl(mplid, pk_cmpl);
	erid = (ER_ID)mplid;		/* %jp{可変長メモリプールIDを格納} */
#endif

	_KERNEL_LEAVE_SVC();		/* %jp{サービスコールから出る}%en{leave service-call} */
	
	return erid;
}


#else	/* _KERNEL_SPT_ACRE_MPL */


#if _KERNEL_SPT_ACRE_MPL_E_NOSPT


/** %jp{可変長メモリプールの生成(ID番号自動割付け)}
 * @param  pk_cmpl  %jp{可変長メモリプール生成情報を入れたパケットへのポインタ}
 * @retval E_NOSPT  %jp{未サポート機能}%en{Unsupported function}
 */
ER_ID acre_mpl(const T_CMPL *pk_cmpl)
{
	return E_NOSPT;
}

#endif


#endif	/* _KERNEL_SPT_ACRE_MPL */



/* end of file */
