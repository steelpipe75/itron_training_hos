/* hos v4a の kcre_mpf.c を元に改変 */

#ifndef _KERNEL__object__mplobj_h__
#define _KERNEL__object__mplobj_h__



/* ------------------------------------------ */
/*  type definition                           */
/* ------------------------------------------ */

/* %jp{可変長メモリプールブロック数の型} */
#if _KERNEL_MPLCB_BITFIELD		/* %jp{MPLCBにビットフィールドを利用する場合} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{符号付優先の場合1bit増やして符号付を使う} */
typedef signed int						_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef signed int						_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#define _KERNEL_MPLCB_TBITDEF_BLKCNT	: _KERNEL_MPL_TBIT_BLKCNT + 1	/**< %jp{可変長メモリプールブロック数のビットフィールド宣言時の幅} */
#else
typedef unsigned int					_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef unsigned int					_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#define _KERNEL_MPLCB_TBITDEF_BLKCNT	: _KERNEL_MPL_TBIT_BLKCNT		/**< %jp{可変長メモリプールブロック数のビットフィールド宣言時の幅} */
#endif

#else							/* %jp{MPLCBにビットフィールドを利用しない場合} */

#if (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_B) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_B				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_UB) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_H) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_H				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_UH) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_W) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_W				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_UW) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKCNT <= _KERNEL_TMAX_D) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_D				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_MPL_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数を演算操作するときの型} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_MPLCB_T_BLKCNT;			/**< %jp{可変長メモリプールブロック数をMPLCBに格納するときの型} */
#endif

#define _KERNEL_MPLCB_TBITDEF_BLKCNT									/**< %jp{可変長メモリプールブロック数のビットフィールド宣言時の幅} */

#endif


/* %jp{可変長メモリプールブロックサイズの型} */
#if _KERNEL_MPLCB_BITFIELD		/* %jp{MPLCBにビットフィールドを利用する場合} */

#if _KERNEL_PROCATR_SIGNED_INT && !_KERNEL_LEAST_CB_SIZE	/* %jp{符号付優先の場合1bit増やして符号付を使う} */
typedef signed int						_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef signed int						_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#define _KERNEL_MPLCB_TBITDEF_BLKSZ	: _KERNEL_MPL_TBIT_BLKSZ + 1		/**< %jp{可変長メモリプールブロックサイズのビットフィールド宣言時の幅} */
#else
typedef unsigned int					_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef unsigned int					_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#define _KERNEL_MPLCB_TBITDEF_BLKSZ	: _KERNEL_MPL_TBIT_BLKSZ			/**< %jp{可変長メモリプールブロックサイズのビットフィールド宣言時の幅} */
#endif

#else							/* %jp{MPLCBにビットフィールドを利用しない場合} */

#if (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_B) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_B				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_B				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_UB) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UB				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_UB				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_H) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_H				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_H				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_UH) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UH				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_UH				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_W) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_W				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_W				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_UW) && !(_KERNEL_PROCATR_SIGNED_INT && !_KERNEL_OPT_CB_SIZE)
typedef _KERNEL_T_FAST_UW				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_UW				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#elif (_KERNEL_MPL_TMAX_BLKSZ <= _KERNEL_TMAX_D) && _KERNEL_PROCATR_SIGNED_INT
typedef _KERNEL_T_FAST_D				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_D				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#else
typedef _KERNEL_T_FAST_UD				_KERNEL_MPL_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズを演算操作するときの型} */
typedef _KERNEL_T_LEAST_UD				_KERNEL_MPLCB_T_BLKSZ;			/**< %jp{可変長メモリプールブロックサイズをMPLCBに格納するときの型} */
#endif

#define _KERNEL_MPLCB_TBITDEF_BLKSZ										/**< %jp{可変長メモリプールブロックサイズのビットフィールド宣言時の幅} */

#endif


/* %jp{可変長メモリプール属性用の型} */
#if _KERNEL_MPLCB_BITFIELD		/* %jp{MPLCBにビットフィールドを利用する場合} */

/* %jp{TA_TFIFO と TA_TPRI の判定に 1bit 必要} */
typedef unsigned int					_KERNEL_MPL_T_MPLATR;
typedef unsigned int					_KERNEL_MPLCB_T_MPLATR;
#define _KERNEL_MPLCB_TBITDEF_MPLATR	: 1

#else							/* %jp{MPLCBにビットフィールドを利用しない場合} */

typedef _KERNEL_T_FAST_UB				_KERNEL_MPL_T_MPLATR;
typedef _KERNEL_T_LEAST_UB				_KERNEL_MPLCB_T_MPLATR;
#define _KERNEL_MPLCB_TBITDEF_MPLATR

#endif

typedef VP								_KERNEL_MPL_T_MPL;
typedef VP								_KERNEL_MPLCB_T_MPL;
#define _KERNEL_MPLCB_TBITDEF_MPL		


/* %jp{メモリブロックのハンドル} */
#if _KERNEL_MPL_ALGORITHM == _KERNEL_MPL_ALG_CHAIN_PTR		/* %jp{ポインタ管理} */

typedef VP								_KERNEL_MPL_T_BLKHDL;
typedef VP								_KERNEL_MPLCB_T_BLKHDL;
#define _KERNEL_MPLCB_TBITDEF_BLKHDL
#define _KERNEL_MPL_BLKHDL_NULL			NULL
#define _KERNEL_MPL_BLKHDL2PTR(mplhdl, blkhdl)		(blkhdl)
#define _KERNEL_MPL_PTR2BLKHDL(mplhdl, blkptr)		(blkptr)

#elif _KERNEL_MPL_ALGORITHM == _KERNEL_MPL_ALG_CHAIN_NUM	/* %jp{ブロック番号管理} */

typedef _KERNEL_MPL_T_BLKCNT			_KERNEL_MPL_T_BLKHDL;
typedef _KERNEL_MPLCB_T_BLKCNT			_KERNEL_MPLCB_T_BLKHDL;
#define _KERNEL_MPLCB_TBITDEF_BLKHDL	_KERNEL_MPLCB_TBITDEF_BLKCNT
#define _KERNEL_MPL_BLKHDL_NULL			0
#define _KERNEL_MPL_BLKHDL2PTR(mplhdl, blkhdl)		((VP)((VB *)_KERNEL_MPL_GET_MPL(mplhdl) + ((SIZE)((blkhdl) - 1) * (SIZE)_KERNEL_MPL_GET_BLKSZ(mplhdl))))
#define _KERNEL_MPL_PTR2BLKHDL(mplhdl, blkptr)		(((VB *)(blkptr) - (VB *)_KERNEL_MPL_GET_MPL(mplhdl)) / _KERNEL_MPL_GET_BLKSZ(mplhdl) + 1)

#endif



/* ------------------------------------------ */
/*  Control block                             */
/* ------------------------------------------ */

#if _KERNEL_MPLCB_SPLIT_RO

/** %jp{可変長メモリプールコントロールブロック(ROM部)} */
typedef struct _kernel_t_mplcb_ro
{
#if _KERNEL_MPLCB_MPLATR
	_KERNEL_MPLCB_T_MPLATR	mplatr		_KERNEL_MPLCB_TBITDEF_MPLATR;		/**< %jp{可変長メモリプール属性} */
#endif

#if _KERNEL_MPLCB_BLKCNT
	_KERNEL_MPLCB_T_BLKCNT	blkcnt		_KERNEL_MPLCB_TBITDEF_BLKCNT;		/**< %jp{獲得できるメモリブロック数(個数)} */
#endif

#if _KERNEL_MPLCB_BLKSZ
	_KERNEL_MPLCB_T_BLKCNT	blksz		_KERNEL_MPLCB_TBITDEF_BLKSZ;		/**< %jp{メモリブロックのサイズ(バイト数)} */
#endif

#if _KERNEL_MPLCB_MPL
	_KERNEL_MPLCB_T_MPL		mpl			_KERNEL_MPLCB_TBITDEF_MPL;			/**< %jp{可変長メモリプール領域の先頭番地} */
#endif
} _KERNEL_T_MPLCB_RO;

typedef const _KERNEL_T_MPLCB_RO	*_KERNEL_T_MPLCB_RO_PTR;


/** %jp{可変長メモリプールコントロールブロック(RAM部)} */
typedef struct _kernel_t_mplcb
{
#if _KERNEL_MPLCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{可変長メモリプール待ちタスクキュー} */
#endif

#if _KERNEL_MPLCB_FREBLK
	_KERNEL_MPLCB_T_BLKHDL	freblk		_KERNEL_MPLCB_TBITDEF_BLKHDL;		/**< %jp{最初のメモリプールの空きメモリブロック位置} */
#endif

#if _KERNEL_MPLCB_FBLKCNT
	_KERNEL_MPLCB_T_BLKCNT	fblkcnt		_KERNEL_MPLCB_TBITDEF_BLKCNT;		/**< %jp{可変長メモリプールの空きメモリブロック数(個数)} */
#endif

#if _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_PTRARRAY
	_KERNEL_MPLCB_T_ROM		*mplcb_rom;										/**< %jp{可変長メモリプールコントロールブロックROM部へのポインタ} */
#endif
} _KERNEL_T_MPLCB;

typedef _KERNEL_T_MPLCB				*_KERNEL_T_MPLCB_PTR;


#else


/** %jp{可変長メモリプールコントロールブロック} */
typedef struct _kernel_t_mplcb
{
#if _KERNEL_MPLCB_QUE
	_KERNEL_T_QUE			que;											/**< %jp{可変長メモリプール待ちタスクキュー} */
#endif

#if _KERNEL_MPLCB_FREBLK
	_KERNEL_MPLCB_T_BLKHDL	freblk		_KERNEL_MPLCB_TBITDEF_BLKHDL;		/**< %jp{最初のメモリプールの空きメモリブロック位置} */
#endif

#if _KERNEL_MPLCB_FBLKCNT
	_KERNEL_MPLCB_T_BLKCNT	fblkcnt		_KERNEL_MPLCB_TBITDEF_BLKCNT;		/**< %jp{可変長メモリプールの空きメモリブロック数(個数)} */
#endif

#if _KERNEL_MPLCB_MPLATR
	_KERNEL_MPLCB_T_MPLATR	mplatr		_KERNEL_MPLCB_TBITDEF_MPLATR;		/**< %jp{可変長メモリプール属性} */
#endif

#if _KERNEL_MPLCB_BLKCNT
	_KERNEL_MPLCB_T_BLKCNT	blkcnt		_KERNEL_MPLCB_TBITDEF_BLKCNT;		/**< %jp{獲得できるメモリブロック数(個数)} */
#endif

#if _KERNEL_MPLCB_BLKSZ
	_KERNEL_MPLCB_T_BLKSZ	blksz		_KERNEL_MPLCB_TBITDEF_BLKSZ;		/**< %jp{メモリブロックのサイズ(バイト数)} */
#endif

#if _KERNEL_MPLCB_MPL
	_KERNEL_MPLCB_T_MPL		mpl			_KERNEL_MPLCB_TBITDEF_MPL;			/**< %jp{可変長メモリプール領域の先頭番地} */
#endif
} _KERNEL_T_MPLCB;

typedef _KERNEL_T_MPLCB				_KERNEL_T_MPLCB_RO;
typedef const _KERNEL_T_MPLCB_RO	*_KERNEL_T_MPLCB_RO_PTR;
typedef _KERNEL_T_MPLCB				*_KERNEL_T_MPLCB_PTR;


#endif



/* ------------------------------------------ */
/*  ID range                                  */
/* ------------------------------------------ */

extern const ID							_kernel_max_mplid;										/**< %jp{可変長メモリプールIDの最大値} */

#define _KERNEL_MPL_TMIN_ID				1														/**< %jp{可変長メモリプールIDの最小値} */
#define _KERNEL_MPL_TMAX_ID				(_kernel_max_mplid)										/**< %jp{可変長メモリプールIDの最大値} */

#define _KERNEL_MPL_CHECK_MPLID(mplid)	((mplid) >= _KERNEL_MPL_TMIN_ID && (mplid) <= _KERNEL_MPL_TMAX_ID)
																								/**< %jp{ID範囲チェック} */


/* ------------------------------------------ */
/*  Control block tables                      */
/* ------------------------------------------ */

#if _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_BLKARRAY
#if _KERNEL_MPLCB_SPLIT_RO

/* %jp{ブロック配列管理でRO分離の場合}%en{block array} */
extern  _KERNEL_T_MPLCB					_kernel_mplcb_tbl[];									/**< %jp{可変長メモリプールコントロールブロックテーブル} */
extern const _KERNEL_T_MPLCB_RO			_kernel_mplcb_ro_tbl[];									/**< %jp{可変長メモリプールコントロールブロック(リードオンリー部)テーブル} */
#define _KERNEL_MPL_ID2MPLCB(mplid)		(&_kernel_mplcb_tbl[(mplid) - _KERNEL_MPL_TMIN_ID])		/**< %jp{コントロールブロックの取得} */
#define _KERNEL_MPL_CHECK_EXS(mplid)	(_kernel_mplcb_ro_tbl[(mplid) - _KERNEL_MPL_TMIN_ID].mpl != NULL)				
																								/**< %jp{オブジェクトの存在チェック} */

#else

/* %jp{ブロック配列管理の場合}%en{block array} */
extern  _KERNEL_T_MPLCB					_kernel_mplcb_tbl[];									/**< %jp{可変長メモリプールコントロールブロックテーブル} */
#define _KERNEL_MPL_ID2MPLCB(mplid)		(&_kernel_mplcb_tbl[(mplid) - _KERNEL_MPL_TMIN_ID])		/**< %jp{コントロールブロックの取得} */
#define _KERNEL_MPL_CHECK_EXS(mplid)	(_kernel_mplcb_tbl[(mplid) - _KERNEL_MPL_TMIN_ID].mpl != NULL)				
																								/**< %jp{オブジェクトの存在チェック} */

#endif

#elif _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_PTRARRAY

/* %jp{ポインタ配列管理の場合}%en{pointer array} */
extern  _KERNEL_T_MPLCB					*_kernel_mplcb_tbl[];									/**< %jp{可変長メモリプールコントロールブロックテーブル} */
#define _KERNEL_MPL_ID2MPLCB(mplid)		(_kernel_mplcb_tbl[(mplid) - _KERNEL_TMIN_MPLID])		/**< %jp{可変長メモリプールIDからMPLCB アドレスを取得} */
#define _KERNEL_MPL_CHECK_EXS(mplid)	(_KERNEL_MPL_ID2MPLCB(mplid) != NULL)					/**< %jp{オブジェクトの存在チェック} */

#endif



/* ------------------------------------------ */
/*   Accessor for MPLCB                       */
/* ------------------------------------------ */

/* mplcb_ro */
#if !_KERNEL_MPLCB_SPLIT_RO								
#define _KERNEL_MPL_GET_MPLCB_RO(mplid, mplcb)	(mplcb)
#else
#if _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_BLKARRAY		/* %jp{MPLCBを単純配列で管理}%en{array of block} */
#define _KERNEL_MPL_GET_MPLCB_RO(mplid, mplcb)	(&_kernel_mplcb_ro_tbl[(mplid)])
#elif _KERNEL_MPLCB_ALGORITHM == _KERNEL_MPLCB_ALG_PTRARRAY		/* %jp{MPLCBをポインタ配列で管理}%en{array of pointer} */
#define _KERNEL_MPL_GET_MPLCB_RO(mplid, mplcb)	((mplcb)->mplcb_ro)
#endif
#endif


/* que */
#define _KERNEL_MPL_GET_QUE(mplcb)			(&(mplcb)->que)

/* freblk */
#if _KERNEL_MPLCB_FREBLK
#define _KERNEL_MPL_SET_FREBLK(mplcb, x)		do { (mplcb)->freblk = (_KERNEL_MPLCB_T_BLKHDL)(x); } while (0)
#define _KERNEL_MPL_GET_FREBLK(mplcb)			((_KERNEL_MPL_T_BLKHDL)(mplcb)->freblk)
#else
#define _KERNEL_MPL_SET_FREBLK(mplcb, x)		do { } while (0)
#define _KERNEL_MPL_GET_FREBLK(mplcb)			(0)
#endif

/* fblkcnt */
#if _KERNEL_MPLCB_FBLKCNT
#define _KERNEL_MPL_SET_FBLKCNT(mplcb, x)		do { (mplcb)->fblkcnt = (_KERNEL_MPLCB_T_BLKCNT)(x); } while (0)
#define _KERNEL_MPL_GET_FBLKCNT(mplcb)			((_KERNEL_MPL_T_BLKCNT)(mplcb)->fblkcnt)
#else
#define _KERNEL_MPL_SET_FBLKCNT(mplcb, x)		do { } while (0)
#define _KERNEL_MPL_GET_FBLKCNT(mplcb)			(0)
#endif


/* mplatr */
#if _KERNEL_MPLCB_MPLATR
#define _KERNEL_MPL_SET_MPLATR(mplcb_ro, x)		do { (mplcb_ro)->mplatr = (_KERNEL_MPLCB_T_MPLATR)(x); } while (0)
#define _KERNEL_MPL_GET_MPLATR(mplcb_ro)		((_KERNEL_MPL_T_MPLATR)(mplcb_ro)->mplatr)
#else
#define _KERNEL_MPL_SET_MPLATR(mplcb_ro, x)		do { } while (0)
#if _KERNEL_SPT_MPL_TA_TFIFO
#define _KERNEL_MPL_GET_MPLATR(mplcb_ro)		(TA_TFIFO)
#else
#define _KERNEL_MPL_GET_MPLATR(mplcb_ro)		(TA_TPRI)
#endif
#endif

/* blkcnt */
#if _KERNEL_MPLCB_BLKCNT
#define _KERNEL_MPL_SET_BLKCNT(mplcb_ro, x)		do { (mplcb_ro)->blkcnt = (_KERNEL_MPLCB_T_BLKCNT)(x); } while (0)
#define _KERNEL_MPL_GET_BLKCNT(mplcb_ro)		((_KERNEL_MPL_T_BLKCNT)(mplcb_ro)->blkcnt)
#else
#define _KERNEL_MPL_SET_BLKCNT(mplcb_ro, x)		do { } while (0)
#define _KERNEL_MPL_GET_BLKCNT(mplcb_ro)		(1)
#endif

/* blksz */
#if _KERNEL_MPLCB_BLKSZ
#define _KERNEL_MPL_SET_BLKSZ(mplcb_ro, x)		do { (mplcb_ro)->blksz = (_KERNEL_MPLCB_T_BLKCNT)(x); } while (0)
#define _KERNEL_MPL_GET_BLKSZ(mplcb_ro)			((_KERNEL_MPL_T_BLKCNT)(mplcb_ro)->blksz)
#else
#define _KERNEL_MPL_SET_BLKSZ(mplcb_ro, x)		do { } while (0)
#define _KERNEL_MPL_GET_BLKSZ(mplcb_ro)			(_KERNEL_TMAX_BLKCNT)
#endif

/* mpl */
#if _KERNEL_MPLCB_MPL
#define _KERNEL_MPL_SET_MPL(mplcb_ro, x)		do { (mplcb_ro)->mpl = (_KERNEL_MPLCB_T_MPL)(x); } while (0)
#define _KERNEL_MPL_GET_MPL(mplcb_ro)			((_KERNEL_MPL_T_MPL)(mplcb_ro)->mpl)
#else
#define _KERNEL_MPL_SET_MPL(mplcb_ro, x)		do { } while (0)
#define _KERNEL_MPL_GET_MPL(mplcb_ro)			(NULL)
#endif



/* ------------------------------------------ */
/*   Macro functions                          */
/* ------------------------------------------ */

/* %jp{キュー接続} */
#if _KERNEL_SPT_MPL_TA_TFIFO && _KERNEL_SPT_MPL_TA_TPRI		/* %jp{TA_TFIFO と TA_TPRI の混在 } */
#define _KERNEL_MPL_ADD_QUE(mplcb, mplcb_ro, tskhdl)	_KERNEL_ADD_QUE(_KERNEL_MPL_GET_QUE(mplcb), tskhdl, _KERNEL_MPL_GET_MPLATR(mplcb_ro))
#elif _KERNEL_SPT_MPL_TA_TFIFO && !_KERNEL_SPT_SE_TA_TPRI	/* %jp{TA_TFIFO のみ利用 } */
#define _KERNEL_MPL_ADD_QUE(mplcb, mplcb_ro, tskhdl)	_KERNEL_ADF_QUE(_KERNEL_MPL_GET_QUE(mplcb), tskhdl)
#elif !_KERNEL_SPT_MPL_TA_TFIFO && _KERNEL_SPT_MPL_TA_TPRI	/* %jp{TA_TPRI のみ利用 } */
#define _KERNEL_MPL_ADD_QUE(mplcb, mplcb_ro, tskhdl)	_KERNEL_ADP_QUE(_KERNEL_MPL_GET_QUE(mplcb), tskhdl)
#else
#error error:_KERNEL_SPT_MPL_TA_TPRI and _KERNEL_SPT_MPL_TA_TFIFO
#endif

/* %jp{キュー取り外し} */
#define _KERNEL_MPL_RMV_QUE(mplcb, tskhdl)	_KERNEL_RMV_QUE(_KERNEL_MPL_GET_QUE(mplcb), tskhdl)

/* %jp{キュー先頭取り出し} */
#define _KERNEL_MPL_RMH_QUE(mplcb)			_KERNEL_RMH_QUE(_KERNEL_MPL_GET_QUE(mplcb))


/* %jp{タイムアウトキュー操作} */
#if _KERNEL_SPT_TGET_MPL	/* %jp{tget_mplサポート時はタイムアウトキューも考慮する} */
#define _KERNEL_MPL_ADD_TOQ(tskhdl, tmout)	_KERNEL_SYS_ADD_TOQ(tskhdl, tmout)
#define _KERNEL_MPL_RMV_TOQ(tskhdl)			_KERNEL_SYS_RMV_TOQ(tskhdl)
#else
#define _KERNEL_MPL_ADD_TOQ(tskhdl)			do { } while (0)
#define _KERNEL_MPL_RMV_TOQ(tskhdl)			do { } while (0)
#endif


/* ------------------------------------------ */
/*   Functions                                */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

ER _kernel_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);		/**< %jp{可変長メモリプール生成} */

#ifdef __cplusplus
}
#endif



#endif	/* _KERNEL__object__mplobj_h__ */


/* end of file */
