/* hos v4a の kcre_mpf.c を元に改変 */

#include "core/core.h"
#include "object/mplobj.h"


/* %jp{メモリ不足エラーチェックサポートの判定} */
#if (_KERNEL_SPT_CRE_MPL && _KERNEL_SPT_CRE_MPL_E_NOMEM) || (_KERNEL_SPT_ACRE_MPL && _KERNEL_SPT_ACRE_MPL_E_NOMEM)
#define _KERNEL_SPT_KCRE_MPL_E_NOMEM	TRUE
#else
#define _KERNEL_SPT_KCRE_MPL_E_NOMEM	FALSE
#endif


void _kernel_set_mpl(_KERNEL_T_MPLCB_PTR mplcb, _KERNEL_MPL_T_BLKCNT blkcnt, _KERNEL_MPL_T_BLKSZ blksz, VP mpl);


/** %jp{可変長メモリプールの生成}
 * @param  mplid	%jp{生成対象の可変長メモリプールのID番号}
 * @param  pk_ctsk	%jp{可変長メモリプール生成情報を入れたパケットへのポインタ}
 * @retval E_OK     %jp{正常終了}%en{Normal completion}
 * @retval E_NOMEM  %jp{メモリ不足}%en{Insufficient memory}
 */
ER _kernel_cre_mpl(ID mplid, const T_CMPL *pk_cmpl)
{
	_KERNEL_T_MPLCB    *mplcb;
	_KERNEL_T_MPLCB_RO *mplcb_ro;
	VP                 mpl;
	
	/* %jp{メモリ確保}%en{get memory} */
#if _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_BLKARRAY
	{	/*  %jp{MPLCB領域がブロック管理の場合} */

		/* メモリ確保 */
		if ( pk_cmpl->mpl == NULL )
		{
			mpl = _KERNEL_SYS_ALC_HEP(TSZ_MPL(pk_cmpl->blkcnt, pk_cmpl->blksz));
		/* %jp{メモリ不足チェック} */
#if _KERNEL_SPT_KCRE_MPL_E_NOMEM
			if ( mpl == NULL )
			{
				return E_NOMEM;
			}
#endif
		}
		else
		{
			mpl = pk_cmpl->mpl;
		}
		mplcb    = _KERNEL_MPL_ID2MPLCB(mplid);
		mplcb_ro = mplcb;
	}
#elif _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_PTRARRAY
#if _KERNEL_MPLCB_SPLIT_RO
	{	/* %jp{MPLCB領域がポインタ管理で、ROM/RAM分離の場合} */
		VP   mem;
		SIZE memsz;

		/* %jp{メモリサイズ決定} */
		memsz  = _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB));
		memsz += _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB_ROM));
		if ( pk_cmpl->mpl == NULL )
		{
			memsz += TSZ_MPL(pk_cmpl->blkcnt, pk_cmpl->blksz);
		}

		/* %jp{メモリ確保} */
		mem = _KERNEL_SYS_ALC_HEP(memsz);

		/* %jp{メモリ不足チェック} */
#if _KERNEL_SPT_KCRE_MPL_E_NOMEM
		if ( mem == NULL )
		{
			return E_NOMEM;
		}
#endif
		
		/* %jp{メモリ割り当て} */
		mplcb    = (_KERNEL_T_MPLCB *)mem;
		mplcb_ro = (_KERNEL_T_MPLCB_ROM *)((B *)mem + _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB)));
		mplcb->mplcb_ro = mplcb_ro;
		_KERNEL_TSK_ID2MPLCB(mplid) = mplcb;
		if ( pk_cmpl->mpl == NULL )
		{
			mpl = (_KERNEL_T_MPLCB_ROM *)((B *)mem + _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB)) + _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB_ROM)));
		}
		else
		{
			mpl = pk_cmpl->mpl;
		}
	}
#else
	{	/* %jp{MPLCB領域がポインタ管理で、ROM/RAM統合の場合} */
		VP   mem;
		SIZE memsz;

		/* %jp{メモリサイズ決定} */
		memsz = _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB));
		if ( pk_cmpl->mpl == NULL )
		{
			memsz += TSZ_MPL(pk_cmpl->blkcnt, pk_cmpl->blksz)
		}

		/* %jp{メモリ確保} */
		mem = _KERNEL_SYS_ALC_HEP(memsz);

		/* %jp{メモリ不足チェック} */
#if _KERNEL_SPT_KCRE_MPL_E_NOMEM
		if ( mem == NULL )
		{
			return E_NOMEM;
		}
#endif

		/* %jp{メモリ割り当て} */
		mplcb    = (_KERNEL_T_MPLCB *)mem;
		mplcb_ro = mplcb;
		_KERNEL_MPL_ID2MPLCB(mplid) = mplcb;
		if ( pk_cmpl->mpl == NULL )
		{
			mpl = (_KERNEL_T_MPLCB_ROM *)((B *)mem + _KERNEL_SYS_ALG_HEP(sizeof(_KERNEL_T_MPLCB)));
		}
		else
		{
			mpl = pk_cmpl->mpl;
		}
	}
#endif
#endif
		
	/* %jp{メンバ初期化} */
	_KERNEL_MPL_SET_MPLATR(mplcb_ro, pk_cmpl->mplatr);
	_KERNEL_MPL_SET_BLKCNT(mplcb_ro, pk_cmpl->blkcnt);
	_KERNEL_MPL_SET_BLKSZ(mplcb_ro, _KERNEL_TSZ_ALIGNED(pk_cmpl->blksz));
	_KERNEL_MPL_SET_MPL(mplcb_ro, mpl);
	_KERNEL_CRE_QUE(_KERNEL_MPL_GET_QUE(mplcb));
	_kernel_set_mpl(mplcb, pk_cmpl->blkcnt, pk_cmpl->blksz, mpl);

	return E_OK;
}


void _kernel_set_mpl(_KERNEL_T_MPLCB_PTR mplcb, _KERNEL_MPL_T_BLKCNT blkcnt, _KERNEL_MPL_T_BLKSZ blksz, VP mpl)
{
	UINT i;

#if _KERNEL_MPL_ALGORITHM == _KERNEL_MPL_ALG_CHAIN_PTR		/* %jp{ポインタ管理} */
	{
		VB *ptr, *next;

		ptr = (VB *)mpl;
		_KERNEL_MPL_SET_FREBLK(mplcb, ptr);
		for ( i = 0; i < blkcnt - 1; i++ )
		{
			next = ptr + blksz;
			*(_KERNEL_MPLCB_T_BLKHDL *)ptr = next;
			ptr = next;
		}
		*(_KERNEL_MPLCB_T_BLKHDL *)ptr = NULL;
	}
#elif  _KERNEL_MPL_ALGORITHM == _KERNEL_MPL_ALG_CHAIN_NUM	/* %jp{ブロック番号管理} */
	{
		VB *ptr;

		ptr = (VB *)mpl;
		_KERNEL_MPL_SET_FREBLK(mplcb, 1);
		for ( i = 1; i < blkcnt - 1; i++ )
		{
			*(_KERNEL_MPLCB_T_BLKHDL *)ptr = (i + 1);
			ptr += blksz;
		}
		*(_KERNEL_MPLCB_T_BLKHDL *)ptr = 0;
	}
#endif
}




/* end of file */
