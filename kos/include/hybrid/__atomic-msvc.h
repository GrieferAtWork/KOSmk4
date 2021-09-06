/* Copyright (c) 2019-2021 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___ATOMIC_MSVC_H
#define __GUARD_HYBRID___ATOMIC_MSVC_H 1

#include "../__stdinc.h"
#include "host.h"

#ifndef __GUARD_HYBRID___ATOMIC_H
#error "Never include this file directly. - Always include `<hybrid/__atomic.h>' instead"
#endif /* !__GUARD_HYBRID___ATOMIC_H */


#define __GCC_ATOMIC_BOOL_LOCK_FREE     1
#define __GCC_ATOMIC_CHAR_LOCK_FREE     1
#define __GCC_ATOMIC_CHAR16_T_LOCK_FREE 1
#define __GCC_ATOMIC_CHAR32_T_LOCK_FREE 1
#define __GCC_ATOMIC_WCHAR_T_LOCK_FREE  1
#define __GCC_ATOMIC_SHORT_LOCK_FREE    1
#define __GCC_ATOMIC_INT_LOCK_FREE      1
#define __GCC_ATOMIC_LONG_LOCK_FREE     1
#define __GCC_ATOMIC_LLONG_LOCK_FREE    1
#define __GCC_ATOMIC_POINTER_LOCK_FREE  1

__DECL_BEGIN

#ifdef __x86_64__
#define __CDECL_OR_DEFAULT /* Nothing */
#else /* __x86_64__ */
#define __CDECL_OR_DEFAULT __cdecl
#endif /* !__x86_64__ */

__NAMESPACE_INT_BEGIN
extern char (_InterlockedCompareExchange8)(char volatile *__px, char __newv, char __oldv);
extern short (_InterlockedCompareExchange16)(short volatile *__px, short __newv, short __oldv);
extern long (__CDECL_OR_DEFAULT _InterlockedCompareExchange)(long volatile *__px, long __newv, long __oldv);
extern __int64 (_InterlockedCompareExchange64)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
#pragma intrinsic(_InterlockedCompareExchange8)
#pragma intrinsic(_InterlockedCompareExchange16)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedCompareExchange64)
__NAMESPACE_INT_END

#ifdef __cplusplus
extern "C++" {

template<class __T, class __OV, class __NV>
#define __impl_hybrid_atomic_cmpxch_val_seqcst __impl_hybrid_atomic_cmpxch_val_seqcst
__T __FORCELOCAL __ATTR_ARTIFICIAL __NOTHROW_NCX(__impl_hybrid_atomic_cmpxch_val_seqcst)(__T &__x, __OV __oldv, __NV __newv) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM _InterlockedCompareExchange8((char volatile *)&__x, (char)__newv, (char)__oldv);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM _InterlockedCompareExchange16((short volatile *)&__x, (short)__newv, (short)__oldv);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedCompareExchange((long volatile *)&__x, (long)__newv, (long)__oldv);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedCompareExchange64((__int64 volatile *)&__x, (__int64)__newv, (__int64)__oldv);
			}
		}
	}
}

}
#else /* __cplusplus */
#define __impl_hybrid_atomic_cmpxch_val_seqcst(x, oldv, newv)                                                                                                     \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange8((char volatile *)&(x), (char)(newv), (char)(oldv)) :     \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange16((short volatile *)&(x), (short)(newv), (short)(oldv)) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange((long volatile *)&(x), (long)(newv), (long)(oldv)) :      \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange64((__int64 volatile *)&(x), (__int64)(newv), (__int64)(oldv)))
#endif /* !__cplusplus */

#ifdef __arm__
__NAMESPACE_INT_BEGIN
extern char (_InterlockedCompareExchange8_acq)(char volatile *__px, char __newv, char __oldv);
extern char (_InterlockedCompareExchange8_nf)(char volatile *__px, char __newv, char __oldv);
extern char (_InterlockedCompareExchange8_rel)(char volatile *__px, char __newv, char __oldv);
extern short (_InterlockedCompareExchange16_acq)(short volatile *__px, short __newv, short __oldv);
extern short (_InterlockedCompareExchange16_nf)(short volatile *__px, short __newv, short __oldv);
extern short (_InterlockedCompareExchange16_rel)(short volatile *__px, short __newv, short __oldv);
extern long (_InterlockedCompareExchange_acq)(long volatile *__px, long __newv, long __oldv);
extern long (_InterlockedCompareExchange_nf)(long volatile *__px, long __newv, long __oldv);
extern long (_InterlockedCompareExchange_rel)(long volatile *__px, long __newv, long __oldv);
extern __int64 (_InterlockedCompareExchange64_acq)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
extern __int64 (_InterlockedCompareExchange64_nf)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
extern __int64 (_InterlockedCompareExchange64_rel)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
#pragma intrinsic(_InterlockedCompareExchange8_acq)
#pragma intrinsic(_InterlockedCompareExchange8_nf)
#pragma intrinsic(_InterlockedCompareExchange8_rel)
#pragma intrinsic(_InterlockedCompareExchange16_acq)
#pragma intrinsic(_InterlockedCompareExchange16_nf)
#pragma intrinsic(_InterlockedCompareExchange16_rel)
#pragma intrinsic(_InterlockedCompareExchange_acq)
#pragma intrinsic(_InterlockedCompareExchange_nf)
#pragma intrinsic(_InterlockedCompareExchange_rel)
#pragma intrinsic(_InterlockedCompareExchange64_acq) /* __ATOMIC_ACQUIRE */
#pragma intrinsic(_InterlockedCompareExchange64_nf)  /* __ATOMIC_RELAXED */
#pragma intrinsic(_InterlockedCompareExchange64_rel) /* __ATOMIC_RELEASE */

#define __DEFINE_WRAPPER(n, y, T)                                                                                                         \
	__FORCELOCAL __ATTR_ARTIFICIAL __UINT##n##_TYPE__                                                                                     \
	__NOTHROW_NCX(__impl_hybrid_atomic_cmpxch_val##n)(void *__x, __UINT##n##_TYPE__ __oldv,                                               \
	                                                  __UINT##n##_TYPE__ __newv, int __succ, int __fail) {                                \
		int const __order = __MAX(__succ, __fail);                                                                                        \
		if (__order >= __ATOMIC_ACQ_REL)                                                                                                  \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange##y((T volatile *)__x, (T)__newv, (T)__oldv);       \
		if (__order >= __ATOMIC_RELEASE)                                                                                                  \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange##y##_rel((T volatile *)__x, (T)__newv, (T)__oldv); \
		if (__order >= __ATOMIC_CONSUME)                                                                                                  \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange##y##_acq((T volatile *)__x, (T)__newv, (T)__oldv); \
		return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedCompareExchange##y##_nf((T volatile *)__x, (T)__newv, (T)__oldv);      \
	}
__DEFINE_WRAPPER(8, 8, char)
__DEFINE_WRAPPER(16, 16, short)
__DEFINE_WRAPPER(32, , long)
__DEFINE_WRAPPER(64, 64, __int64)
__NAMESPACE_INT_END
#undef __DEFINE_WRAPPER

#ifdef __cplusplus
extern "C++" {
template<class __T, class __OV, class __NV>
#define __hybrid_atomic_cmpxch_val __hybrid_atomic_cmpxch_val
__T __FORCELOCAL __ATTR_ARTIFICIAL __NOTHROW_NCX(__hybrid_atomic_cmpxch_val)(__T &__x, __OV __oldv, __NV __newv, int __fail, int __succ) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val8(&__x, (__UINT8_TYPE__)__newv, (__UINT8_TYPE__)__oldv, __fail, __succ);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val16(&__x, (__UINT16_TYPE__)__newv, (__UINT16_TYPE__)__oldv, __fail, __succ);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val32(&__x, (__UINT32_TYPE__)__newv, (__UINT32_TYPE__)__oldv, __fail, __succ);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val64(&__x, (__UINT64_TYPE__)__newv, (__UINT64_TYPE__)__oldv, __fail, __succ);
			}
		}
	}
}
}
#else /* __cplusplus */
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, fail, succ)                                                                                                                        \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val8(&(x), (__UINT8_TYPE__)(newv), (__UINT8_TYPE__)(oldv), fail, succ) :     \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val16(&(x), (__UINT16_TYPE__)(newv), (__UINT16_TYPE__)(oldv), fail, succ) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val32(&(x), (__UINT32_TYPE__)(newv), (__UINT32_TYPE__)(oldv), fail, succ) : \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_cmpxch_val64(&(x), (__UINT64_TYPE__)(newv), (__UINT64_TYPE__)(oldv), fail, succ))
#endif /* !__cplusplus */

#endif /* __arm__ */


/* Implement these for much faster atomic operations. */
__NAMESPACE_INT_BEGIN
#define _InterlockedIncrement8(px) _InterlockedExchangeAdd8(px, 1)
extern short (_InterlockedIncrement16)(short volatile *__px);
extern long (__CDECL_OR_DEFAULT _InterlockedIncrement)(long volatile *__px);
#define _InterlockedDecrement8(px) _InterlockedExchangeAdd8(px, -1)
extern short (_InterlockedDecrement16)(short volatile *__px);
extern long (__CDECL_OR_DEFAULT _InterlockedDecrement)(long volatile *__px);
extern char (_InterlockedExchange8)(char volatile *__px, char __v);
extern short (_InterlockedExchange16)(short volatile *__px, short __v);
extern long (__CDECL_OR_DEFAULT _InterlockedExchange)(long volatile *__px, long __v);
extern char (_InterlockedExchangeAdd8)(char volatile *__px, char __v);
extern short (_InterlockedExchangeAdd16)(short volatile *__px, short __v);
extern long (__CDECL_OR_DEFAULT _InterlockedExchangeAdd)(long volatile *__px, long __v);
extern char (_InterlockedAnd8)(char volatile *__px, char __v);
extern short (_InterlockedAnd16)(short volatile *__px, short __v);
extern long (_InterlockedAnd)(long volatile *__px, long __v);
extern char (_InterlockedOr8)(char volatile *__px, char __v);
extern short (_InterlockedOr16)(short volatile *__px, short __v);
extern long (_InterlockedOr)(long volatile *__px, long __v);
extern char (_InterlockedXor8)(char volatile *__px, char __v);
extern short (_InterlockedXor16)(short volatile *__px, short __v);
extern long (_InterlockedXor)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedAnd8)
#pragma intrinsic(_InterlockedAnd)
#pragma intrinsic(_InterlockedAnd16)
#pragma intrinsic(_InterlockedDecrement16)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedIncrement16)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedExchange8)
#pragma intrinsic(_InterlockedExchange16)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd8)
#pragma intrinsic(_InterlockedExchangeAdd16)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedOr8)
#pragma intrinsic(_InterlockedOr16)
#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedXor8)
#pragma intrinsic(_InterlockedXor16)
#pragma intrinsic(_InterlockedXor)


/* 64-bit arithmetic atomic operations. */
#if defined(__arm__) || defined(__x86_64__)
extern __int64 (_InterlockedAnd64)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedExchange64)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedExchangeAdd64)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedOr64)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedXor64)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedIncrement64)(__int64 volatile *__px);
extern __int64 (_InterlockedDecrement64)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedAnd64)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedOr64)
#pragma intrinsic(_InterlockedXor64)
#pragma intrinsic(_InterlockedIncrement64)
#pragma intrinsic(_InterlockedDecrement64)
#else /* Native... */

__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedExchange64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __v, __res) != __res);
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedExchangeAdd64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res + __v, __res) != __res);
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedAnd64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res & __v, __res) != __res);
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedOr64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res | __v, __res) != __res);
	return __res;
}

__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedXor64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res ^ __v, __res) != __res);
	return __res;
}

#if 1
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedIncrement64)(__int64 volatile *__px) {
	return _InterlockedExchangeAdd64(__px, 1);
}
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedDecrement64)(__int64 volatile *__px) {
	return _InterlockedExchangeAdd64(__px, -1);
}
//#define _InterlockedIncrement64(__px) _InterlockedExchangeAdd64(__px,  1)
//#define _InterlockedDecrement64(__px) _InterlockedExchangeAdd64(__px, -1)
#endif
#endif /* Emulated... */

__NAMESPACE_INT_END

/* Wrap extended intrinsic atomic arithmetic */
#ifdef __cplusplus
extern "C++" {

template<class __T, class __V>
#define __impl_hybrid_atomic_xch_seqcst __impl_hybrid_atomic_xch_seqcst
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__impl_hybrid_atomic_xch_seqcst)(__T &__x, __V __v) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM _InterlockedExchange8((char volatile *)&__x, (char)__v);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM _InterlockedExchange16((short volatile *)&__x, (short)__v);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedExchange((long volatile *)&__x, (long)__v);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedExchange64((__int64 volatile *)&__x, (__int64)__v);
			}
		}
	}
}

template<class __T, class __V>
#define __impl_hybrid_atomic_fetchadd_seqcst __impl_hybrid_atomic_fetchadd_seqcst
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__impl_hybrid_atomic_fetchadd_seqcst)(__T &__x, __V __v) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM _InterlockedExchangeAdd8((char volatile *)&__x, (char)__v);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM _InterlockedExchangeAdd16((short volatile *)&__x, (short)__v);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedExchangeAdd((long volatile *)&__x, (long)__v);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedExchangeAdd64((__int64 volatile *)&__x, (__int64)__v);
			}
		}
	}
}

template<class __T, class __V>
#define __impl_hybrid_atomic_fetchand_seqcst __impl_hybrid_atomic_fetchand_seqcst
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__impl_hybrid_atomic_fetchand_seqcst)(__T &__x, __V __v) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM _InterlockedAnd8((char volatile *)&__x, (char)__v);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM _InterlockedAnd16((short volatile *)&__x, (short)__v);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedAnd((long volatile *)&__x, (long)__v);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedAnd64((__int64 volatile *)&__x, (__int64)__v);
			}
		}
	}
}

template<class __T, class __V>
#define __impl_hybrid_atomic_fetchor_seqcst __impl_hybrid_atomic_fetchor_seqcst
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__impl_hybrid_atomic_fetchor_seqcst)(__T &__x, __V __v) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM _InterlockedOr8((char volatile *)&__x, (char)__v);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM _InterlockedOr16((short volatile *)&__x, (short)__v);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedOr((long volatile *)&__x, (long)__v);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedOr64((__int64 volatile *)&__x, (__int64)__v);
			}
		}
	}
}

template<class __T, class __V>
#define __impl_hybrid_atomic_fetchxor_seqcst __impl_hybrid_atomic_fetchxor_seqcst
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__impl_hybrid_atomic_fetchxor_seqcst)(__T &__x, __V __v) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM _InterlockedXor8((char volatile *)&__x, (char)__v);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM _InterlockedXor16((short volatile *)&__x, (short)__v);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedXor((long volatile *)&__x, (long)__v);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM _InterlockedXor64((__int64 volatile *)&__x, (__int64)__v);
			}
		}
	}
}
}
#else /* __cplusplus */
#define __impl_hybrid_atomic_xch_seqcst(x, v)                                                                                             \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__ )__NAMESPACE_INT_SYM _InterlockedExchange8((char volatile *)&(x), (char)(v)) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange16((short volatile *)&(x), (short)(v)) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange((long volatile *)&(x), (long)(v)) :     \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange64((__int64 volatile *)&(x), (__int64)(v)))
#define __impl_hybrid_atomic_fetchadd_seqcst(x, v)                                                                                           \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__ )__NAMESPACE_INT_SYM _InterlockedExchangeAdd8((char volatile *)&(x), (char)(v)) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd16((short volatile *)&(x), (short)(v)) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd((long volatile *)&(x), (long)(v)) :     \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd64((__int64 volatile *)&(x), (__int64)(v)))
#define __impl_hybrid_atomic_fetchand_seqcst(x, v)                                                                                   \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__ )__NAMESPACE_INT_SYM _InterlockedAnd8((char volatile *)&(x), (char)(v)) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd16((short volatile *)&(x), (short)(v)) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd((long volatile *)&(x), (long)(v)) :     \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd64((__int64 volatile *)&(x), (__int64)(v)))
#define __impl_hybrid_atomic_fetchor_seqcst(x, v)                                                                                   \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__ )__NAMESPACE_INT_SYM _InterlockedOr8((char volatile *)&(x), (char)(v)) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr16((short volatile *)&(x), (short)(v)) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr((long volatile *)&(x), (long)(v)) :     \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr64((__int64 volatile *)&(x), (__int64)(v)))
#define __impl_hybrid_atomic_fetchxor_seqcst(x, v)                                                                                   \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__ )__NAMESPACE_INT_SYM _InterlockedXor8((char volatile *)&(x), (char)(v)) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor16((short volatile *)&(x), (short)(v)) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor((long volatile *)&(x), (long)(v)) :     \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor64((__int64 volatile *)&(x), (__int64)(v)))
#endif /* !__cplusplus */


/* Fix ARM atomics. */
#ifdef __arm__
__NAMESPACE_INT_BEGIN

extern char (_InterlockedExchange8_acq)(char volatile *__px, char __v);
extern char (_InterlockedExchange8_nf)(char volatile *__px, char __v);
extern char (_InterlockedExchange8_rel)(char volatile *__px, char __v);
extern short (_InterlockedExchange16_acq)(short volatile *__px, short __v);
extern short (_InterlockedExchange16_nf)(short volatile *__px, short __v);
extern short (_InterlockedExchange16_rel)(short volatile *__px, short __v);
extern long (_InterlockedExchange_acq)(long volatile *__px, long __v);
extern long (_InterlockedExchange_nf)(long volatile *__px, long __v);
extern long (_InterlockedExchange_rel)(long volatile *__px, long __v);
extern __int64 (_InterlockedExchange64_acq)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedExchange64_nf)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedExchange64_rel)(__int64 volatile *__px, __int64 __v);

extern char (_InterlockedExchangeAdd8_acq)(char volatile *__px, char __v);
extern char (_InterlockedExchangeAdd8_nf)(char volatile *__px, char __v);
extern char (_InterlockedExchangeAdd8_rel)(char volatile *__px, char __v);
extern short (_InterlockedExchangeAdd16_acq)(short volatile *__px, short __v);
extern short (_InterlockedExchangeAdd16_nf)(short volatile *__px, short __v);
extern short (_InterlockedExchangeAdd16_rel)(short volatile *__px, short __v);
extern long (_InterlockedExchangeAdd_acq)(long volatile *__px, long __v);
extern long (_InterlockedExchangeAdd_nf)(long volatile *__px, long __v);
extern long (_InterlockedExchangeAdd_rel)(long volatile *__px, long __v);
extern __int64 (_InterlockedExchangeAdd64_acq)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedExchangeAdd64_nf)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedExchangeAdd64_rel)(__int64 volatile *__px, __int64 __v);

#define _InterlockedIncrement8_acq(px) _InterlockedExchangeAdd8_acq(px, 1)
#define _InterlockedIncrement8_nf(px) _InterlockedExchangeAdd8_nf(px, 1)
#define _InterlockedIncrement8_rel(px) _InterlockedExchangeAdd8_rel(px, 1)
extern short (_InterlockedIncrement16_acq)(short volatile *__px);
extern short (_InterlockedIncrement16_nf)(short volatile *__px);
extern short (_InterlockedIncrement16_rel)(short volatile *__px);
extern long (_InterlockedIncrement_acq)(long volatile *__px);
extern long (_InterlockedIncrement_nf)(long volatile *__px);
extern long (_InterlockedIncrement_rel)(long volatile *__px);
extern __int64 (_InterlockedIncrement64_acq)(__int64 volatile *__px);
extern __int64 (_InterlockedIncrement64_nf)(__int64 volatile *__px);
extern __int64 (_InterlockedIncrement64_rel)(__int64 volatile *__px);

#define _InterlockedDecrement8_acq(px) _InterlockedExchangeAdd8_acq(px, -1)
#define _InterlockedDecrement8_nf(px) _InterlockedExchangeAdd8_nf(px, -1)
#define _InterlockedDecrement8_rel(px) _InterlockedExchangeAdd8_rel(px, -1)
extern short (_InterlockedDecrement16_acq)(short volatile *__px);
extern short (_InterlockedDecrement16_nf)(short volatile *__px);
extern short (_InterlockedDecrement16_rel)(short volatile *__px);
extern long (_InterlockedDecrement_acq)(long volatile *__px);
extern long (_InterlockedDecrement_nf)(long volatile *__px);
extern long (_InterlockedDecrement_rel)(long volatile *__px);
extern __int64 (_InterlockedDecrement64_acq)(__int64 volatile *__px);
extern __int64 (_InterlockedDecrement64_nf)(__int64 volatile *__px);
extern __int64 (_InterlockedDecrement64_rel)(__int64 volatile *__px);

extern char (_InterlockedAnd8_acq)(char volatile *__px, char __v);
extern char (_InterlockedAnd8_nf)(char volatile *__px, char __v);
extern char (_InterlockedAnd8_rel)(char volatile *__px, char __v);
extern short (_InterlockedAnd16_acq)(short volatile *__px, short __v);
extern short (_InterlockedAnd16_nf)(short volatile *__px, short __v);
extern short (_InterlockedAnd16_rel)(short volatile *__px, short __v);
extern long (_InterlockedAnd_acq)(long volatile *__px, long __v);
extern long (_InterlockedAnd_nf)(long volatile *__px, long __v);
extern long (_InterlockedAnd_rel)(long volatile *__px, long __v);
extern __int64 (_InterlockedAnd64_acq)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedAnd64_nf)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedAnd64_rel)(__int64 volatile *__px, __int64 __v);

extern char (_InterlockedOr8_acq)(char volatile *__px, char __v);
extern char (_InterlockedOr8_nf)(char volatile *__px, char __v);
extern char (_InterlockedOr8_rel)(char volatile *__px, char __v);
extern short (_InterlockedOr16_acq)(short volatile *__px, short __v);
extern short (_InterlockedOr16_nf)(short volatile *__px, short __v);
extern short (_InterlockedOr16_rel)(short volatile *__px, short __v);
extern long (_InterlockedOr_acq)(long volatile *__px, long __v);
extern long (_InterlockedOr_nf)(long volatile *__px, long __v);
extern long (_InterlockedOr_rel)(long volatile *__px, long __v);
extern __int64 (_InterlockedOr64_acq)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedOr64_nf)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedOr64_rel)(__int64 volatile *__px, __int64 __v);

extern char (_InterlockedXor8_acq)(char volatile *__px, char __v);
extern char (_InterlockedXor8_nf)(char volatile *__px, char __v);
extern char (_InterlockedXor8_rel)(char volatile *__px, char __v);
extern short (_InterlockedXor16_acq)(short volatile *__px, short __v);
extern short (_InterlockedXor16_nf)(short volatile *__px, short __v);
extern short (_InterlockedXor16_rel)(short volatile *__px, short __v);
extern long (_InterlockedXor_acq)(long volatile *__px, long __v);
extern long (_InterlockedXor_nf)(long volatile *__px, long __v);
extern long (_InterlockedXor_rel)(long volatile *__px, long __v);
extern __int64 (_InterlockedXor64_acq)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedXor64_nf)(__int64 volatile *__px, __int64 __v);
extern __int64 (_InterlockedXor64_rel)(__int64 volatile *__px, __int64 __v);

#pragma intrinsic(_InterlockedExchange8_acq)
#pragma intrinsic(_InterlockedExchange8_nf)
#pragma intrinsic(_InterlockedExchange8_rel)
#pragma intrinsic(_InterlockedExchange16_acq)
#pragma intrinsic(_InterlockedExchange16_nf)
#pragma intrinsic(_InterlockedExchange16_rel)
#pragma intrinsic(_InterlockedExchange_acq)
#pragma intrinsic(_InterlockedExchange_nf)
#pragma intrinsic(_InterlockedExchange_rel)
#pragma intrinsic(_InterlockedExchange64_acq)
#pragma intrinsic(_InterlockedExchange64_nf)
#pragma intrinsic(_InterlockedExchange64_rel)
#pragma intrinsic(_InterlockedExchangeAdd8_acq)
#pragma intrinsic(_InterlockedExchangeAdd8_nf)
#pragma intrinsic(_InterlockedExchangeAdd8_rel)
#pragma intrinsic(_InterlockedExchangeAdd16_acq)
#pragma intrinsic(_InterlockedExchangeAdd16_nf)
#pragma intrinsic(_InterlockedExchangeAdd16_rel)
#pragma intrinsic(_InterlockedExchangeAdd_acq)
#pragma intrinsic(_InterlockedExchangeAdd_nf)
#pragma intrinsic(_InterlockedExchangeAdd_rel)
#pragma intrinsic(_InterlockedExchangeAdd64_acq)
#pragma intrinsic(_InterlockedExchangeAdd64_nf)
#pragma intrinsic(_InterlockedExchangeAdd64_rel)
#pragma intrinsic(_InterlockedIncrement16_acq)
#pragma intrinsic(_InterlockedIncrement16_nf)
#pragma intrinsic(_InterlockedIncrement16_rel)
#pragma intrinsic(_InterlockedIncrement_acq)
#pragma intrinsic(_InterlockedIncrement_nf)
#pragma intrinsic(_InterlockedIncrement_rel)
#pragma intrinsic(_InterlockedIncrement64_acq)
#pragma intrinsic(_InterlockedIncrement64_nf)
#pragma intrinsic(_InterlockedIncrement64_rel)
#pragma intrinsic(_InterlockedDecrement16_acq)
#pragma intrinsic(_InterlockedDecrement16_nf)
#pragma intrinsic(_InterlockedDecrement16_rel)
#pragma intrinsic(_InterlockedDecrement_acq)
#pragma intrinsic(_InterlockedDecrement_nf)
#pragma intrinsic(_InterlockedDecrement_rel)
#pragma intrinsic(_InterlockedDecrement64_acq)
#pragma intrinsic(_InterlockedDecrement64_nf)
#pragma intrinsic(_InterlockedDecrement64_rel)
#pragma intrinsic(_InterlockedAnd8_acq)
#pragma intrinsic(_InterlockedAnd8_nf)
#pragma intrinsic(_InterlockedAnd8_rel)
#pragma intrinsic(_InterlockedAnd16_acq)
#pragma intrinsic(_InterlockedAnd16_nf)
#pragma intrinsic(_InterlockedAnd16_rel)
#pragma intrinsic(_InterlockedAnd_acq)
#pragma intrinsic(_InterlockedAnd_nf)
#pragma intrinsic(_InterlockedAnd_rel)
#pragma intrinsic(_InterlockedAnd64_acq)
#pragma intrinsic(_InterlockedAnd64_nf)
#pragma intrinsic(_InterlockedAnd64_rel)
#pragma intrinsic(_InterlockedOr8_acq)
#pragma intrinsic(_InterlockedOr8_nf)
#pragma intrinsic(_InterlockedOr8_rel)
#pragma intrinsic(_InterlockedOr16_acq)
#pragma intrinsic(_InterlockedOr16_nf)
#pragma intrinsic(_InterlockedOr16_rel)
#pragma intrinsic(_InterlockedOr_acq)
#pragma intrinsic(_InterlockedOr_nf)
#pragma intrinsic(_InterlockedOr_rel)
#pragma intrinsic(_InterlockedOr64_acq)
#pragma intrinsic(_InterlockedOr64_nf)
#pragma intrinsic(_InterlockedOr64_rel)
#pragma intrinsic(_InterlockedXor8_acq)
#pragma intrinsic(_InterlockedXor8_nf)
#pragma intrinsic(_InterlockedXor8_rel)
#pragma intrinsic(_InterlockedXor16_acq)
#pragma intrinsic(_InterlockedXor16_nf)
#pragma intrinsic(_InterlockedXor16_rel)
#pragma intrinsic(_InterlockedXor_acq)
#pragma intrinsic(_InterlockedXor_nf)
#pragma intrinsic(_InterlockedXor_rel)
#pragma intrinsic(_InterlockedXor64_acq)
#pragma intrinsic(_InterlockedXor64_nf)
#pragma intrinsic(_InterlockedXor64_rel)

#define __DEFINE_WRAPPER(n, y, T)                                                                                       \
	__FORCELOCAL __ATTR_ARTIFICIAL __UINT##n##_TYPE__                                                                   \
	__NOTHROW_NCX(__impl_hybrid_atomic_xch##n)(void *__x, __UINT##n##_TYPE__ __v, int __order) {                        \
		if (__order >= __ATOMIC_ACQ_REL)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange##y((T volatile *)__x, (T)__v);          \
		if (__order >= __ATOMIC_RELEASE)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange##y##_rel((T volatile *)__x, (T)__v);    \
		if (__order >= __ATOMIC_CONSUME)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange##y##_acq((T volatile *)__x, (T)__v);    \
		return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchange##y##_nf((T volatile *)__x, (T)__v);         \
	}                                                                                                                   \
	__FORCELOCAL __ATTR_ARTIFICIAL __UINT##n##_TYPE__                                                                   \
	__NOTHROW_NCX(__impl_hybrid_atomic_fetchadd##n)(void *__x, __UINT##n##_TYPE__ __v, int __order) {                   \
		if (__order >= __ATOMIC_ACQ_REL)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd##y((T volatile *)__x, (T)__v);       \
		if (__order >= __ATOMIC_RELEASE)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd##y##_rel((T volatile *)__x, (T)__v); \
		if (__order >= __ATOMIC_CONSUME)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd##y##_acq((T volatile *)__x, (T)__v); \
		return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedExchangeAdd##y##_nf((T volatile *)__x, (T)__v);      \
	}                                                                                                                   \
	__FORCELOCAL __ATTR_ARTIFICIAL __UINT##n##_TYPE__                                                                   \
	__NOTHROW_NCX(__impl_hybrid_atomic_fetchand##n)(void *__x, __UINT##n##_TYPE__ __v, int __order) {                   \
		if (__order >= __ATOMIC_ACQ_REL)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd##y((T volatile *)__x, (T)__v);               \
		if (__order >= __ATOMIC_RELEASE)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd##y##_rel((T volatile *)__x, (T)__v);         \
		if (__order >= __ATOMIC_CONSUME)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd##y##_acq((T volatile *)__x, (T)__v);         \
		return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedAnd##y##_nf((T volatile *)__x, (T)__v);              \
	}                                                                                                                   \
	__FORCELOCAL __ATTR_ARTIFICIAL __UINT##n##_TYPE__                                                                   \
	__NOTHROW_NCX(__impl_hybrid_atomic_fetchor##n)(void *__x, __UINT##n##_TYPE__ __v, int __order) {                    \
		if (__order >= __ATOMIC_ACQ_REL)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr##y((T volatile *)__x, (T)__v);                \
		if (__order >= __ATOMIC_RELEASE)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr##y##_rel((T volatile *)__x, (T)__v);          \
		if (__order >= __ATOMIC_CONSUME)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr##y##_acq((T volatile *)__x, (T)__v);          \
		return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedOr##y##_nf((T volatile *)__x, (T)__v);               \
	}                                                                                                                   \
	__FORCELOCAL __ATTR_ARTIFICIAL __UINT##n##_TYPE__                                                                   \
	__NOTHROW_NCX(__impl_hybrid_atomic_fetchxor##n)(void *__x, __UINT##n##_TYPE__ __v, int __order) {                   \
		if (__order >= __ATOMIC_ACQ_REL)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor##y((T volatile *)__x, (T)__v);               \
		if (__order >= __ATOMIC_RELEASE)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor##y##_rel((T volatile *)__x, (T)__v);         \
		if (__order >= __ATOMIC_CONSUME)                                                                                \
			return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor##y##_acq((T volatile *)__x, (T)__v);         \
		return (__UINT##n##_TYPE__)__NAMESPACE_INT_SYM _InterlockedXor##y##_nf((T volatile *)__x, (T)__v);              \
	}
__DEFINE_WRAPPER(8, 8, char)
__DEFINE_WRAPPER(16, 16, short)
__DEFINE_WRAPPER(32, , long)
__DEFINE_WRAPPER(64, 64, __int64)
__NAMESPACE_INT_END
#undef __DEFINE_WRAPPER

#ifdef __cplusplus
extern "C++" {

template<class __T, class __V>
#define __hybrid_atomic_xch __hybrid_atomic_xch
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__hybrid_atomic_xch)(__T &__x, __V __v, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch8(&__x, (__UINT8_TYPE__)__v, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch16(&__x, (__UINT16_TYPE__)__v, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch32(&__x, (__UINT32_TYPE__)__v, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch64(&__x, (__UINT64_TYPE__)__v, __order);
			}
		}
	}
}

template<class __T, class __V>
#define __hybrid_atomic_fetchadd __hybrid_atomic_fetchadd
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__hybrid_atomic_fetchadd)(__T &__x, __V __v, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd8(&__x, (__UINT8_TYPE__)__v, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd16(&__x, (__UINT16_TYPE__)__v, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd32(&__x, (__UINT32_TYPE__)__v, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd64(&__x, (__UINT64_TYPE__)__v, __order);
			}
		}
	}
}

template<class __T, class __V>
#define __hybrid_atomic_fetchand __hybrid_atomic_fetchand
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__hybrid_atomic_fetchand)(__T &__x, __V __v, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand8(&__x, (__UINT8_TYPE__)__v, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand16(&__x, (__UINT16_TYPE__)__v, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand32(&__x, (__UINT32_TYPE__)__v, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand64(&__x, (__UINT64_TYPE__)__v, __order);
			}
		}
	}
}

template<class __T, class __V>
#define __hybrid_atomic_fetchor __hybrid_atomic_fetchor
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__hybrid_atomic_fetchor)(__T &__x, __V __v, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor8(&__x, (__UINT8_TYPE__)__v, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor16(&__x, (__UINT16_TYPE__)__v, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor32(&__x, (__UINT32_TYPE__)__v, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor64(&__x, (__UINT64_TYPE__)__v, __order);
			}
		}
	}
}

template<class __T, class __V>
#define __hybrid_atomic_fetchxor __hybrid_atomic_fetchxor
__FORCELOCAL __ATTR_ARTIFICIAL __T __NOTHROW_NCX(__hybrid_atomic_fetchxor)(__T &__x, __V __v, int __order) {
	__STATIC_IF(sizeof(__T) == 1) {
		return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor8(&__x, (__UINT8_TYPE__)__v, __order);
	}
	__STATIC_ELSE(sizeof(__T) == 1) {
		__STATIC_IF(sizeof(__T) == 2) {
			return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor16(&__x, (__UINT16_TYPE__)__v, __order);
		}
		__STATIC_ELSE(sizeof(__T) == 2) {
			__STATIC_IF(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor32(&__x, (__UINT32_TYPE__)__v, __order);
			}
			__STATIC_ELSE(sizeof(__T) == 4) {
				return (__T)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor64(&__x, (__UINT64_TYPE__)__v, __order);
			}
		}
	}
}

}
#else /* __cplusplus */
#define __hybrid_atomic_xch(x, v, order)                                                                                                     \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch8(&(x), (__UINT8_TYPE__)(v), order) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch16(&(x), (__UINT16_TYPE__)(v), order) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch32(&(x), (__UINT32_TYPE__)(v), order) : \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_xch64(&(x), (__UINT64_TYPE__)(v), order))
#define __hybrid_atomic_fetchadd(x, v, order)                                                                                                     \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd8(&(x), (__UINT8_TYPE__)(v), order) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd16(&(x), (__UINT16_TYPE__)(v), order) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd32(&(x), (__UINT32_TYPE__)(v), order) : \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchadd64(&(x), (__UINT64_TYPE__)(v), order))
#define __hybrid_atomic_fetchand(x, v, order)                                                                                                     \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand8(&(x), (__UINT8_TYPE__)(v), order) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand16(&(x), (__UINT16_TYPE__)(v), order) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand32(&(x), (__UINT32_TYPE__)(v), order) : \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchand64(&(x), (__UINT64_TYPE__)(v), order))
#define __hybrid_atomic_fetchor(x, v, order)                                                                                                     \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor8(&(x), (__UINT8_TYPE__)(v), order) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor16(&(x), (__UINT16_TYPE__)(v), order) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor32(&(x), (__UINT32_TYPE__)(v), order) : \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchor64(&(x), (__UINT64_TYPE__)(v), order))
#define __hybrid_atomic_fetchxor(x, v, order)                                                                                                     \
	__ATOMIC_RECAST(x, sizeof(x) == 1 ? (__UINT8_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor8(&(x), (__UINT8_TYPE__)(v), order) :    \
	                   sizeof(x) == 2 ? (__UINT16_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor16(&(x), (__UINT16_TYPE__)(v), order) : \
	                   sizeof(x) == 4 ? (__UINT32_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor32(&(x), (__UINT32_TYPE__)(v), order) : \
	                                    (__UINT64_TYPE__)__NAMESPACE_INT_SYM __impl_hybrid_atomic_fetchxor64(&(x), (__UINT64_TYPE__)(v), order))
#endif /* !__cplusplus */

#define __hybrid_atomic_thread_fence(order) \
	(__NAMESPACE_INT_SYM __impl_hybrid_atomic_thread_fence(order))
__NAMESPACE_INT_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(__impl_hybrid_atomic_thread_fence)(int __order) {
	if (__order != __ATOMIC_RELAXED)
		__dmb(_ARM_BARRIER_ISH);
}
__NAMESPACE_INT_END

#else /* __arm__ */
#define __hybrid_atomic_thread_fence(order) \
	(__NAMESPACE_INT_SYM __impl_hybrid_atomic_thread_fence(order))
__NAMESPACE_INT_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(__impl_hybrid_atomic_thread_fence)(int __order) {
	if (__order >= __ATOMIC_SEQ_CST) {
		volatile __UINT32_TYPE__ __guard;
		__COMPILER_BARRIER();
		__impl_hybrid_atomic_xch_seqcst(__guard,0);
		__COMPILER_BARRIER();
	} else if (__order >= __ATOMIC_ACQ_REL) {
		__COMPILER_BARRIER();
	} else if (__order >= __ATOMIC_RELEASE) {
		__COMPILER_WRITE_BARRIER();
	} else if (__order >= __ATOMIC_CONSUME) {
		__COMPILER_READ_BARRIER();
	}
}
__NAMESPACE_INT_END

#endif /* __arm__ */

__DECL_END

#endif /* !__GUARD_HYBRID___ATOMIC_MSVC_H */
