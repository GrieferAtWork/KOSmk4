/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___ATOMIC_MSVC_H
#define __GUARD_HYBRID___ATOMIC_MSVC_H 1

#include "../__stdinc.h"
#include "typecore.h"
#include "host.h"

#ifndef __GUARD_HYBRID___ATOMIC_H
#error "Never include this file directly. - Always include `<hybrid/__atomic.h>' instead"
#endif /* !__GUARD_HYBRID___ATOMIC_H */

#ifdef __x86_64__
#define __CDECL_OR_DEFAULT /* Nothing */
#else /* __x86_64__ */
#define __CDECL_OR_DEFAULT __cdecl
#endif /* !__x86_64__ */

__DECL_BEGIN

#define __HYBRID_ATOMIC_LOCKFREE_MAX 8

#ifndef _InterlockedCompareExchange8
#define _InterlockedCompareExchange8 _InterlockedCompareExchange8
extern char (_InterlockedCompareExchange8)(char volatile *__px, char __newv, char __oldv);
#pragma intrinsic(_InterlockedCompareExchange8)
#endif /* !_InterlockedCompareExchange8 */
#ifndef _InterlockedCompareExchange16
#define _InterlockedCompareExchange16 _InterlockedCompareExchange16
extern short (_InterlockedCompareExchange16)(short volatile *__px, short __newv, short __oldv);
#pragma intrinsic(_InterlockedCompareExchange16)
#endif /* !_InterlockedCompareExchange16 */
#ifndef _InterlockedCompareExchange
#define _InterlockedCompareExchange _InterlockedCompareExchange
extern long (__CDECL_OR_DEFAULT _InterlockedCompareExchange)(long volatile *__px, long __newv, long __oldv);
#pragma intrinsic(_InterlockedCompareExchange)
#endif /* !_InterlockedCompareExchange */
#ifndef _InterlockedCompareExchange64
#define _InterlockedCompareExchange64 _InterlockedCompareExchange64
extern __int64 (_InterlockedCompareExchange64)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
#pragma intrinsic(_InterlockedCompareExchange64)
#endif /* !_InterlockedCompareExchange64 */

#define __hybrid_atomic_cmpxch_val8_seq_cst(p, oldval, newval) \
	((__UINT8_TYPE__)_InterlockedCompareExchange8((char volatile *)(p), (char)(newval), (char)(oldval)))
#define __hybrid_atomic_cmpxch_val16_seq_cst(p, oldval, newval) \
	((__UINT16_TYPE__)_InterlockedCompareExchange16((short volatile *)(p), (short)(newval), (short)(oldval)))
#define __hybrid_atomic_cmpxch_val32_seq_cst(p, oldval, newval) \
	((__UINT32_TYPE__)_InterlockedCompareExchange((long volatile *)(p), (long)(newval), (long)(oldval)))
#define __hybrid_atomic_cmpxch_val64_seq_cst(p, oldval, newval) \
	((__UINT64_TYPE__)_InterlockedCompareExchange64((__int64 volatile *)(p), (__int64)(newval), (__int64)(oldval)))

#ifdef __arm__
#ifndef _InterlockedCompareExchange8_acq
#define _InterlockedCompareExchange8_acq _InterlockedCompareExchange8_acq
extern char (_InterlockedCompareExchange8_acq)(char volatile *__px, char __newv, char __oldv);
#pragma intrinsic(_InterlockedCompareExchange8_acq)
#endif /* !_InterlockedCompareExchange8_acq */
#ifndef _InterlockedCompareExchange8_nf
#define _InterlockedCompareExchange8_nf _InterlockedCompareExchange8_nf
extern char (_InterlockedCompareExchange8_nf)(char volatile *__px, char __newv, char __oldv);
#pragma intrinsic(_InterlockedCompareExchange8_nf)
#endif /* !_InterlockedCompareExchange8_nf */
#ifndef _InterlockedCompareExchange8_rel
#define _InterlockedCompareExchange8_rel _InterlockedCompareExchange8_rel
extern char (_InterlockedCompareExchange8_rel)(char volatile *__px, char __newv, char __oldv);
#pragma intrinsic(_InterlockedCompareExchange8_rel)
#endif /* !_InterlockedCompareExchange8_rel */
#ifndef _InterlockedCompareExchange16_acq
#define _InterlockedCompareExchange16_acq _InterlockedCompareExchange16_acq
extern short (_InterlockedCompareExchange16_acq)(short volatile *__px, short __newv, short __oldv);
#pragma intrinsic(_InterlockedCompareExchange16_acq)
#endif /* !_InterlockedCompareExchange16_acq */
#ifndef _InterlockedCompareExchange16_nf
#define _InterlockedCompareExchange16_nf _InterlockedCompareExchange16_nf
extern short (_InterlockedCompareExchange16_nf)(short volatile *__px, short __newv, short __oldv);
#pragma intrinsic(_InterlockedCompareExchange16_nf)
#endif /* !_InterlockedCompareExchange16_nf */
#ifndef _InterlockedCompareExchange16_rel
#define _InterlockedCompareExchange16_rel _InterlockedCompareExchange16_rel
extern short (_InterlockedCompareExchange16_rel)(short volatile *__px, short __newv, short __oldv);
#pragma intrinsic(_InterlockedCompareExchange16_rel)
#endif /* !_InterlockedCompareExchange16_rel */
#ifndef _InterlockedCompareExchange_acq
#define _InterlockedCompareExchange_acq _InterlockedCompareExchange_acq
extern long (_InterlockedCompareExchange_acq)(long volatile *__px, long __newv, long __oldv);
#pragma intrinsic(_InterlockedCompareExchange_acq)
#endif /* !_InterlockedCompareExchange_acq */
#ifndef _InterlockedCompareExchange_nf
#define _InterlockedCompareExchange_nf _InterlockedCompareExchange_nf
extern long (_InterlockedCompareExchange_nf)(long volatile *__px, long __newv, long __oldv);
#pragma intrinsic(_InterlockedCompareExchange_nf)
#endif /* !_InterlockedCompareExchange_nf */
#ifndef _InterlockedCompareExchange_rel
#define _InterlockedCompareExchange_rel _InterlockedCompareExchange_rel
extern long (_InterlockedCompareExchange_rel)(long volatile *__px, long __newv, long __oldv);
#pragma intrinsic(_InterlockedCompareExchange_rel)
#endif /* !_InterlockedCompareExchange_rel */
#ifndef _InterlockedCompareExchange64_acq
#define _InterlockedCompareExchange64_acq _InterlockedCompareExchange64_acq
extern __int64 (_InterlockedCompareExchange64_acq)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
#pragma intrinsic(_InterlockedCompareExchange64_acq) /* __ATOMIC_ACQUIRE */
#endif /* !_InterlockedCompareExchange64_acq */
#ifndef _InterlockedCompareExchange64_nf
#define _InterlockedCompareExchange64_nf _InterlockedCompareExchange64_nf
extern __int64 (_InterlockedCompareExchange64_nf)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
#pragma intrinsic(_InterlockedCompareExchange64_nf)  /* __ATOMIC_RELAXED */
#endif /* !_InterlockedCompareExchange64_nf */
#ifndef _InterlockedCompareExchange64_rel
#define _InterlockedCompareExchange64_rel _InterlockedCompareExchange64_rel
extern __int64 (_InterlockedCompareExchange64_rel)(__int64 volatile *__px, __int64 __newv, __int64 __oldv);
#pragma intrinsic(_InterlockedCompareExchange64_rel) /* __ATOMIC_RELEASE */
#endif /* !_InterlockedCompareExchange64_rel */

#define __hybrid_atomic_cmpxch_val8_relaxed(p, oldval, newval) \
	((__UINT8_TYPE__)_InterlockedCompareExchange8_nf((char volatile *)(p), (char)(newval), (char)(oldval)))
#define __hybrid_atomic_cmpxch_val16_relaxed(p, oldval, newval) \
	((__UINT16_TYPE__)_InterlockedCompareExchange16_nf((short volatile *)(p), (short)(newval), (short)(oldval)))
#define __hybrid_atomic_cmpxch_val32_relaxed(p, oldval, newval) \
	((__UINT32_TYPE__)_InterlockedCompareExchange_nf((long volatile *)(p), (long)(newval), (long)(oldval)))
#define __hybrid_atomic_cmpxch_val64_relaxed(p, oldval, newval) \
	((__UINT64_TYPE__)_InterlockedCompareExchange64_nf((__int64 volatile *)(p), (__int64)(newval), (__int64)(oldval)))
#define __hybrid_atomic_cmpxch_val8_acquire(p, oldval, newval) \
	((__UINT8_TYPE__)_InterlockedCompareExchange8_acq((char volatile *)(p), (char)(newval), (char)(oldval)))
#define __hybrid_atomic_cmpxch_val16_acquire(p, oldval, newval) \
	((__UINT16_TYPE__)_InterlockedCompareExchange16_acq((short volatile *)(p), (short)(newval), (short)(oldval)))
#define __hybrid_atomic_cmpxch_val32_acquire(p, oldval, newval) \
	((__UINT32_TYPE__)_InterlockedCompareExchange_acq((long volatile *)(p), (long)(newval), (long)(oldval)))
#define __hybrid_atomic_cmpxch_val64_acquire(p, oldval, newval) \
	((__UINT64_TYPE__)_InterlockedCompareExchange64_acq((__int64 volatile *)(p), (__int64)(newval), (__int64)(oldval)))
#define __hybrid_atomic_cmpxch_val8_release(p, oldval, newval) \
	((__UINT8_TYPE__)_InterlockedCompareExchange8_rel((char volatile *)(p), (char)(newval), (char)(oldval)))
#define __hybrid_atomic_cmpxch_val16_release(p, oldval, newval) \
	((__UINT16_TYPE__)_InterlockedCompareExchange16_rel((short volatile *)(p), (short)(newval), (short)(oldval)))
#define __hybrid_atomic_cmpxch_val32_release(p, oldval, newval) \
	((__UINT32_TYPE__)_InterlockedCompareExchange_rel((long volatile *)(p), (long)(newval), (long)(oldval)))
#define __hybrid_atomic_cmpxch_val64_release(p, oldval, newval) \
	((__UINT64_TYPE__)_InterlockedCompareExchange64_rel((__int64 volatile *)(p), (__int64)(newval), (__int64)(oldval)))

#define __HYBRID_PRIVATE_ARM_ATOMIC(order, func, args)   \
	((order) >= __ATOMIC_ACQ_REL ? func##_seq_cst args : \
	 (order) >= __ATOMIC_RELEASE ? func##_release args : \
	 (order) >= __ATOMIC_CONSUME ? func##_acquire args : \
	                               func##_relaxed args)
#define __hybrid_atomic_cmpxch_val8_p(p, oldval, newval, order)     __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_cmpxch_val8, (p, oldval, newval, order))
#define __hybrid_atomic_cmpxch_val16_p(p, oldval, newval, order)    __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_cmpxch_val16, (p, oldval, newval, order))
#define __hybrid_atomic_cmpxch_val32_p(p, oldval, newval, order)    __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_cmpxch_val32, (p, oldval, newval, order))
#define __hybrid_atomic_cmpxch_val64_p(p, oldval, newval, order)    __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_cmpxch_val64, (p, oldval, newval, order))
#define __hybrid_atomic_cmpxch_val8(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val8_p(p, oldval, newval, (succ) > (fail) ? (succ) : (fail))
#define __hybrid_atomic_cmpxch_val16(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val16_p(p, oldval, newval, (succ) > (fail) ? (succ) : (fail))
#define __hybrid_atomic_cmpxch_val32(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val32_p(p, oldval, newval, (succ) > (fail) ? (succ) : (fail))
#define __hybrid_atomic_cmpxch_val64(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val64_p(p, oldval, newval, (succ) > (fail) ? (succ) : (fail))
#else /* __arm__ */
#define __hybrid_atomic_cmpxch_val8(p, oldval, newval, succ, fail)  __hybrid_atomic_cmpxch_val8_seq_cst(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val16(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val16_seq_cst(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val32(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val32_seq_cst(p, oldval, newval)
#define __hybrid_atomic_cmpxch_val64(p, oldval, newval, succ, fail) __hybrid_atomic_cmpxch_val64_seq_cst(p, oldval, newval)
#endif /* !__arm__ */

/* Implement these for much faster atomic operations. */
#ifndef _InterlockedIncrement8
#define _InterlockedIncrement8(px) (_InterlockedExchangeAdd8(px, 1) + 1)
#endif /* !_InterlockedIncrement8 */
#ifndef _InterlockedDecrement8
#define _InterlockedDecrement8(px) (_InterlockedExchangeAdd8(px, -1) - 1)
#endif /* !_InterlockedDecrement8 */
#ifndef _InterlockedIncrement16
#define _InterlockedIncrement16 _InterlockedIncrement16
extern short (_InterlockedIncrement16)(short volatile *__px);
#pragma intrinsic(_InterlockedIncrement16)
#endif /* !_InterlockedIncrement16 */
#ifndef _InterlockedIncrement
#define _InterlockedIncrement _InterlockedIncrement
extern long (__CDECL_OR_DEFAULT _InterlockedIncrement)(long volatile *__px);
#pragma intrinsic(_InterlockedIncrement)
#endif /* !_InterlockedIncrement */
#ifndef _InterlockedDecrement16
#define _InterlockedDecrement16 _InterlockedDecrement16
extern short (_InterlockedDecrement16)(short volatile *__px);
#pragma intrinsic(_InterlockedDecrement16)
#endif /* !_InterlockedDecrement16 */
#ifndef _InterlockedDecrement
#define _InterlockedDecrement _InterlockedDecrement
extern long (__CDECL_OR_DEFAULT _InterlockedDecrement)(long volatile *__px);
#pragma intrinsic(_InterlockedDecrement)
#endif /* !_InterlockedDecrement */
#ifndef _InterlockedExchange8
#define _InterlockedExchange8 _InterlockedExchange8
extern char (_InterlockedExchange8)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchange8)
#endif /* !_InterlockedExchange8 */
#ifndef _InterlockedExchange16
#define _InterlockedExchange16 _InterlockedExchange16
extern short (_InterlockedExchange16)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchange16)
#endif /* !_InterlockedExchange16 */
#ifndef _InterlockedExchange
#define _InterlockedExchange _InterlockedExchange
extern long (__CDECL_OR_DEFAULT _InterlockedExchange)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchange)
#endif /* !_InterlockedExchange */
#ifndef _InterlockedExchangeAdd8
#define _InterlockedExchangeAdd8 _InterlockedExchangeAdd8
extern char (_InterlockedExchangeAdd8)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchangeAdd8)
#endif /* !_InterlockedExchangeAdd8 */
#ifndef _InterlockedExchangeAdd16
#define _InterlockedExchangeAdd16 _InterlockedExchangeAdd16
extern short (_InterlockedExchangeAdd16)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchangeAdd16)
#endif /* !_InterlockedExchangeAdd16 */
#ifndef _InterlockedExchangeAdd
#define _InterlockedExchangeAdd _InterlockedExchangeAdd
extern long (__CDECL_OR_DEFAULT _InterlockedExchangeAdd)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchangeAdd)
#endif /* !_InterlockedExchangeAdd */
#ifndef _InterlockedAnd8
#define _InterlockedAnd8 _InterlockedAnd8
extern char (_InterlockedAnd8)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedAnd8)
#endif /* !_InterlockedAnd8 */
#ifndef _InterlockedAnd16
#define _InterlockedAnd16 _InterlockedAnd16
extern short (_InterlockedAnd16)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedAnd16)
#endif /* !_InterlockedAnd16 */
#ifndef _InterlockedAnd
#define _InterlockedAnd _InterlockedAnd
extern long (_InterlockedAnd)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedAnd)
#endif /* !_InterlockedAnd */
#ifndef _InterlockedOr8
#define _InterlockedOr8 _InterlockedOr8
extern char (_InterlockedOr8)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedOr8)
#endif /* !_InterlockedOr8 */
#ifndef _InterlockedOr16
#define _InterlockedOr16 _InterlockedOr16
extern short (_InterlockedOr16)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedOr16)
#endif /* !_InterlockedOr16 */
#ifndef _InterlockedOr
#define _InterlockedOr _InterlockedOr
extern long (_InterlockedOr)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedOr)
#endif /* !_InterlockedOr */
#ifndef _InterlockedXor8
#define _InterlockedXor8 _InterlockedXor8
extern char (_InterlockedXor8)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedXor8)
#endif /* !_InterlockedXor8 */
#ifndef _InterlockedXor16
#define _InterlockedXor16 _InterlockedXor16
extern short (_InterlockedXor16)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedXor16)
#endif /* !_InterlockedXor16 */
#ifndef _InterlockedXor
#define _InterlockedXor _InterlockedXor
extern long (_InterlockedXor)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedXor)
#endif /* !_InterlockedXor */


/* 64-bit arithmetic atomic operations. */
#if defined(__arm__) || defined(__x86_64__)
#ifndef _InterlockedAnd64
#define _InterlockedAnd64 _InterlockedAnd64
extern __int64 (_InterlockedAnd64)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedAnd64)
#endif /* !_InterlockedAnd64 */
#ifndef _InterlockedExchange64
#define _InterlockedExchange64 _InterlockedExchange64
extern __int64 (_InterlockedExchange64)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchange64)
#endif /* !_InterlockedExchange64 */
#ifndef _InterlockedExchangeAdd64
#define _InterlockedExchangeAdd64 _InterlockedExchangeAdd64
extern __int64 (_InterlockedExchangeAdd64)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchangeAdd64)
#endif /* !_InterlockedExchangeAdd64 */
#ifndef _InterlockedOr64
#define _InterlockedOr64 _InterlockedOr64
extern __int64 (_InterlockedOr64)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedOr64)
#endif /* !_InterlockedOr64 */
#ifndef _InterlockedXor64
#define _InterlockedXor64 _InterlockedXor64
extern __int64 (_InterlockedXor64)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedXor64)
#endif /* !_InterlockedXor64 */
#ifndef _InterlockedIncrement64
#define _InterlockedIncrement64 _InterlockedIncrement64
extern __int64 (_InterlockedIncrement64)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedIncrement64)
#endif /* !_InterlockedIncrement64 */
#ifndef _InterlockedDecrement64
#define _InterlockedDecrement64 _InterlockedDecrement64
extern __int64 (_InterlockedDecrement64)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedDecrement64)
#endif /* !_InterlockedDecrement64 */
#endif /* __arm__ || __x86_64__ */


#ifndef _InterlockedExchange64
#define _InterlockedExchange64 _InterlockedExchange64
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedExchange64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __v, __res) != __res);
	return __res;
}
#endif /* !_InterlockedExchange64 */

#ifndef _InterlockedExchangeAdd64
#define _InterlockedExchangeAdd64 _InterlockedExchangeAdd64
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedExchangeAdd64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res + __v, __res) != __res);
	return __res;
}
#endif /* !_InterlockedExchangeAdd64 */

#ifndef _InterlockedAnd64
#define _InterlockedAnd64 _InterlockedAnd64
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedAnd64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res & __v, __res) != __res);
	return __res;
}
#endif /* !_InterlockedAnd64 */

#ifndef _InterlockedOr64
#define _InterlockedOr64 _InterlockedOr64
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedOr64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res | __v, __res) != __res);
	return __res;
}
#endif /* !_InterlockedOr64 */

#ifndef _InterlockedXor64
#define _InterlockedXor64 _InterlockedXor64
__FORCELOCAL __ATTR_ARTIFICIAL __int64
__NOTHROW_NCX(_InterlockedXor64)(__int64 volatile *__px, __int64 __v) {
	__int64 __res;
	do {
		__COMPILER_READ_BARRIER();
		__res = *__px;
	} while (_InterlockedCompareExchange64(__px, __res ^ __v, __res) != __res);
	return __res;
}
#endif /* !_InterlockedXor64 */

#ifndef _InterlockedIncrement64
#define _InterlockedIncrement64(px) _InterlockedExchangeAdd64(px, 1)
#endif /* !_InterlockedIncrement64 */
#ifndef _InterlockedDecrement64
#define _InterlockedDecrement64(px) _InterlockedExchangeAdd64(px, -1)
#endif /* !_InterlockedDecrement64 */

#define __hybrid_atomic_xch8_seq_cst(p, val)       ((__UINT8_TYPE__)_InterlockedExchange8((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_xch16_seq_cst(p, val)      ((__UINT16_TYPE__)_InterlockedExchange16((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_xch32_seq_cst(p, val)      ((__UINT32_TYPE__)_InterlockedExchange((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_xch64_seq_cst(p, val)      ((__UINT64_TYPE__)_InterlockedExchange64((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchadd8_seq_cst(p, val)  ((__UINT8_TYPE__)_InterlockedExchangeAdd8((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchadd16_seq_cst(p, val) ((__UINT16_TYPE__)_InterlockedExchangeAdd16((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchadd32_seq_cst(p, val) ((__UINT32_TYPE__)_InterlockedExchangeAdd((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchadd64_seq_cst(p, val) ((__UINT64_TYPE__)_InterlockedExchangeAdd64((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchand8_seq_cst(p, val)  ((__UINT8_TYPE__)_InterlockedAnd8((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchand16_seq_cst(p, val) ((__UINT16_TYPE__)_InterlockedAnd16((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchand32_seq_cst(p, val) ((__UINT32_TYPE__)_InterlockedAnd((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchand64_seq_cst(p, val) ((__UINT64_TYPE__)_InterlockedAnd64((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchor8_seq_cst(p, val)   ((__UINT8_TYPE__)_InterlockedOr8((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchor16_seq_cst(p, val)  ((__UINT16_TYPE__)_InterlockedOr16((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchor32_seq_cst(p, val)  ((__UINT32_TYPE__)_InterlockedOr((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchor64_seq_cst(p, val)  ((__UINT64_TYPE__)_InterlockedOr64((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchxor8_seq_cst(p, val)  ((__UINT8_TYPE__)_InterlockedXor8((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchxor16_seq_cst(p, val) ((__UINT16_TYPE__)_InterlockedXor16((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchxor32_seq_cst(p, val) ((__UINT32_TYPE__)_InterlockedXor((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchxor64_seq_cst(p, val) ((__UINT64_TYPE__)_InterlockedXor64((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_incfetch8_seq_cst(p)       ((__UINT8_TYPE__)_InterlockedIncrement8((char volatile *)(p)))
#define __hybrid_atomic_incfetch16_seq_cst(p)      ((__UINT16_TYPE__)_InterlockedIncrement16((short volatile *)(p)))
#define __hybrid_atomic_incfetch32_seq_cst(p)      ((__UINT32_TYPE__)_InterlockedIncrement((long volatile *)(p)))
#define __hybrid_atomic_incfetch64_seq_cst(p)      ((__UINT64_TYPE__)_InterlockedIncrement64((__int64 volatile *)(p)))
#define __hybrid_atomic_decfetch8_seq_cst(p)       ((__UINT8_TYPE__)_InterlockedDecrement8((char volatile *)(p)))
#define __hybrid_atomic_decfetch16_seq_cst(p)      ((__UINT16_TYPE__)_InterlockedDecrement16((short volatile *)(p)))
#define __hybrid_atomic_decfetch32_seq_cst(p)      ((__UINT32_TYPE__)_InterlockedDecrement((long volatile *)(p)))
#define __hybrid_atomic_decfetch64_seq_cst(p)      ((__UINT64_TYPE__)_InterlockedDecrement64((__int64 volatile *)(p)))


/* Fix ARM atomics. */
#ifdef __arm__
#ifndef _InterlockedExchange8_acq
#define _InterlockedExchange8_acq _InterlockedExchange8_acq
extern char (_InterlockedExchange8_acq)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchange8_acq)
#endif /* !_InterlockedExchange8_acq */
#ifndef _InterlockedExchange8_nf
#define _InterlockedExchange8_nf _InterlockedExchange8_nf
extern char (_InterlockedExchange8_nf)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchange8_nf)
#endif /* !_InterlockedExchange8_nf */
#ifndef _InterlockedExchange8_rel
#define _InterlockedExchange8_rel _InterlockedExchange8_rel
extern char (_InterlockedExchange8_rel)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchange8_rel)
#endif /* !_InterlockedExchange8_rel */
#ifndef _InterlockedExchange16_acq
#define _InterlockedExchange16_acq _InterlockedExchange16_acq
extern short (_InterlockedExchange16_acq)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchange16_acq)
#endif /* !_InterlockedExchange16_acq */
#ifndef _InterlockedExchange16_nf
#define _InterlockedExchange16_nf _InterlockedExchange16_nf
extern short (_InterlockedExchange16_nf)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchange16_nf)
#endif /* !_InterlockedExchange16_nf */
#ifndef _InterlockedExchange16_rel
#define _InterlockedExchange16_rel _InterlockedExchange16_rel
extern short (_InterlockedExchange16_rel)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchange16_rel)
#endif /* !_InterlockedExchange16_rel */
#ifndef _InterlockedExchange_acq
#define _InterlockedExchange_acq _InterlockedExchange_acq
extern long (_InterlockedExchange_acq)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchange_acq)
#endif /* !_InterlockedExchange_acq */
#ifndef _InterlockedExchange_nf
#define _InterlockedExchange_nf _InterlockedExchange_nf
extern long (_InterlockedExchange_nf)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchange_nf)
#endif /* !_InterlockedExchange_nf */
#ifndef _InterlockedExchange_rel
#define _InterlockedExchange_rel _InterlockedExchange_rel
extern long (_InterlockedExchange_rel)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchange_rel)
#endif /* !_InterlockedExchange_rel */
#ifndef _InterlockedExchange64_acq
#define _InterlockedExchange64_acq _InterlockedExchange64_acq
extern __int64 (_InterlockedExchange64_acq)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchange64_acq)
#endif /* !_InterlockedExchange64_acq */
#ifndef _InterlockedExchange64_nf
#define _InterlockedExchange64_nf _InterlockedExchange64_nf
extern __int64 (_InterlockedExchange64_nf)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchange64_nf)
#endif /* !_InterlockedExchange64_nf */
#ifndef _InterlockedExchange64_rel
#define _InterlockedExchange64_rel _InterlockedExchange64_rel
extern __int64 (_InterlockedExchange64_rel)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchange64_rel)
#endif /* !_InterlockedExchange64_rel */

#ifndef _InterlockedExchangeAdd8_acq
#define _InterlockedExchangeAdd8_acq _InterlockedExchangeAdd8_acq
extern char (_InterlockedExchangeAdd8_acq)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchangeAdd8_acq)
#endif /* !_InterlockedExchangeAdd8_acq */
#ifndef _InterlockedExchangeAdd8_nf
#define _InterlockedExchangeAdd8_nf _InterlockedExchangeAdd8_nf
extern char (_InterlockedExchangeAdd8_nf)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchangeAdd8_nf)
#endif /* !_InterlockedExchangeAdd8_nf */
#ifndef _InterlockedExchangeAdd8_rel
#define _InterlockedExchangeAdd8_rel _InterlockedExchangeAdd8_rel
extern char (_InterlockedExchangeAdd8_rel)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedExchangeAdd8_rel)
#endif /* !_InterlockedExchangeAdd8_rel */
#ifndef _InterlockedExchangeAdd16_acq
#define _InterlockedExchangeAdd16_acq _InterlockedExchangeAdd16_acq
extern short (_InterlockedExchangeAdd16_acq)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchangeAdd16_acq)
#endif /* !_InterlockedExchangeAdd16_acq */
#ifndef _InterlockedExchangeAdd16_nf
#define _InterlockedExchangeAdd16_nf _InterlockedExchangeAdd16_nf
extern short (_InterlockedExchangeAdd16_nf)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchangeAdd16_nf)
#endif /* !_InterlockedExchangeAdd16_nf */
#ifndef _InterlockedExchangeAdd16_rel
#define _InterlockedExchangeAdd16_rel _InterlockedExchangeAdd16_rel
extern short (_InterlockedExchangeAdd16_rel)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedExchangeAdd16_rel)
#endif /* !_InterlockedExchangeAdd16_rel */
#ifndef _InterlockedExchangeAdd_acq
#define _InterlockedExchangeAdd_acq _InterlockedExchangeAdd_acq
extern long (_InterlockedExchangeAdd_acq)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchangeAdd_acq)
#endif /* !_InterlockedExchangeAdd_acq */
#ifndef _InterlockedExchangeAdd_nf
#define _InterlockedExchangeAdd_nf _InterlockedExchangeAdd_nf
extern long (_InterlockedExchangeAdd_nf)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchangeAdd_nf)
#endif /* !_InterlockedExchangeAdd_nf */
#ifndef _InterlockedExchangeAdd_rel
#define _InterlockedExchangeAdd_rel _InterlockedExchangeAdd_rel
extern long (_InterlockedExchangeAdd_rel)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedExchangeAdd_rel)
#endif /* !_InterlockedExchangeAdd_rel */
#ifndef _InterlockedExchangeAdd64_acq
#define _InterlockedExchangeAdd64_acq _InterlockedExchangeAdd64_acq
extern __int64 (_InterlockedExchangeAdd64_acq)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchangeAdd64_acq)
#endif /* !_InterlockedExchangeAdd64_acq */
#ifndef _InterlockedExchangeAdd64_nf
#define _InterlockedExchangeAdd64_nf _InterlockedExchangeAdd64_nf
extern __int64 (_InterlockedExchangeAdd64_nf)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchangeAdd64_nf)
#endif /* !_InterlockedExchangeAdd64_nf */
#ifndef _InterlockedExchangeAdd64_rel
#define _InterlockedExchangeAdd64_rel _InterlockedExchangeAdd64_rel
extern __int64 (_InterlockedExchangeAdd64_rel)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedExchangeAdd64_rel)
#endif /* !_InterlockedExchangeAdd64_rel */

#ifndef _InterlockedIncrement8_acq
#define _InterlockedIncrement8_acq(px) _InterlockedExchangeAdd8_acq(px, 1)
#endif /* !_InterlockedIncrement8_acq */
#ifndef _InterlockedIncrement8_nf
#define _InterlockedIncrement8_nf(px) _InterlockedExchangeAdd8_nf(px, 1)
#endif /* !_InterlockedIncrement8_nf */
#ifndef _InterlockedIncrement8_rel
#define _InterlockedIncrement8_rel(px) _InterlockedExchangeAdd8_rel(px, 1)
#endif /* !_InterlockedIncrement8_rel */
#ifndef _InterlockedIncrement16_acq
#define _InterlockedIncrement16_acq _InterlockedIncrement16_acq
extern short (_InterlockedIncrement16_acq)(short volatile *__px);
#pragma intrinsic(_InterlockedIncrement16_acq)
#endif /* !_InterlockedIncrement16_acq */
#ifndef _InterlockedIncrement16_nf
#define _InterlockedIncrement16_nf _InterlockedIncrement16_nf
extern short (_InterlockedIncrement16_nf)(short volatile *__px);
#pragma intrinsic(_InterlockedIncrement16_nf)
#endif /* !_InterlockedIncrement16_nf */
#ifndef _InterlockedIncrement16_rel
#define _InterlockedIncrement16_rel _InterlockedIncrement16_rel
extern short (_InterlockedIncrement16_rel)(short volatile *__px);
#pragma intrinsic(_InterlockedIncrement16_rel)
#endif /* !_InterlockedIncrement16_rel */
#ifndef _InterlockedIncrement_acq
#define _InterlockedIncrement_acq _InterlockedIncrement_acq
extern long (_InterlockedIncrement_acq)(long volatile *__px);
#pragma intrinsic(_InterlockedIncrement_acq)
#endif /* !_InterlockedIncrement_acq */
#ifndef _InterlockedIncrement_nf
#define _InterlockedIncrement_nf _InterlockedIncrement_nf
extern long (_InterlockedIncrement_nf)(long volatile *__px);
#pragma intrinsic(_InterlockedIncrement_nf)
#endif /* !_InterlockedIncrement_nf */
#ifndef _InterlockedIncrement_rel
#define _InterlockedIncrement_rel _InterlockedIncrement_rel
extern long (_InterlockedIncrement_rel)(long volatile *__px);
#pragma intrinsic(_InterlockedIncrement_rel)
#endif /* !_InterlockedIncrement_rel */
#ifndef _InterlockedIncrement64_acq
#define _InterlockedIncrement64_acq _InterlockedIncrement64_acq
extern __int64 (_InterlockedIncrement64_acq)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedIncrement64_acq)
#endif /* !_InterlockedIncrement64_acq */
#ifndef _InterlockedIncrement64_nf
#define _InterlockedIncrement64_nf _InterlockedIncrement64_nf
extern __int64 (_InterlockedIncrement64_nf)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedIncrement64_nf)
#endif /* !_InterlockedIncrement64_nf */
#ifndef _InterlockedIncrement64_rel
#define _InterlockedIncrement64_rel _InterlockedIncrement64_rel
extern __int64 (_InterlockedIncrement64_rel)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedIncrement64_rel)
#endif /* !_InterlockedIncrement64_rel */

#ifndef _InterlockedDecrement8_acq
#define _InterlockedDecrement8_acq(px) _InterlockedExchangeAdd8_acq(px, -1)
#endif /* !_InterlockedDecrement8_acq */
#ifndef _InterlockedDecrement8_nf
#define _InterlockedDecrement8_nf(px) _InterlockedExchangeAdd8_nf(px, -1)
#endif /* !_InterlockedDecrement8_nf */
#ifndef _InterlockedDecrement8_rel
#define _InterlockedDecrement8_rel(px) _InterlockedExchangeAdd8_rel(px, -1)
#endif /* !_InterlockedDecrement8_rel */
#ifndef _InterlockedDecrement16_acq
#define _InterlockedDecrement16_acq _InterlockedDecrement16_acq
extern short (_InterlockedDecrement16_acq)(short volatile *__px);
#pragma intrinsic(_InterlockedDecrement16_acq)
#endif /* !_InterlockedDecrement16_acq */
#ifndef _InterlockedDecrement16_nf
#define _InterlockedDecrement16_nf _InterlockedDecrement16_nf
extern short (_InterlockedDecrement16_nf)(short volatile *__px);
#pragma intrinsic(_InterlockedDecrement16_nf)
#endif /* !_InterlockedDecrement16_nf */
#ifndef _InterlockedDecrement16_rel
#define _InterlockedDecrement16_rel _InterlockedDecrement16_rel
extern short (_InterlockedDecrement16_rel)(short volatile *__px);
#pragma intrinsic(_InterlockedDecrement16_rel)
#endif /* !_InterlockedDecrement16_rel */
#ifndef _InterlockedDecrement_acq
#define _InterlockedDecrement_acq _InterlockedDecrement_acq
extern long (_InterlockedDecrement_acq)(long volatile *__px);
#pragma intrinsic(_InterlockedDecrement_acq)
#endif /* !_InterlockedDecrement_acq */
#ifndef _InterlockedDecrement_nf
#define _InterlockedDecrement_nf _InterlockedDecrement_nf
extern long (_InterlockedDecrement_nf)(long volatile *__px);
#pragma intrinsic(_InterlockedDecrement_nf)
#endif /* !_InterlockedDecrement_nf */
#ifndef _InterlockedDecrement_rel
#define _InterlockedDecrement_rel _InterlockedDecrement_rel
extern long (_InterlockedDecrement_rel)(long volatile *__px);
#pragma intrinsic(_InterlockedDecrement_rel)
#endif /* !_InterlockedDecrement_rel */
#ifndef _InterlockedDecrement64_acq
#define _InterlockedDecrement64_acq _InterlockedDecrement64_acq
extern __int64 (_InterlockedDecrement64_acq)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedDecrement64_acq)
#endif /* !_InterlockedDecrement64_acq */
#ifndef _InterlockedDecrement64_nf
#define _InterlockedDecrement64_nf _InterlockedDecrement64_nf
extern __int64 (_InterlockedDecrement64_nf)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedDecrement64_nf)
#endif /* !_InterlockedDecrement64_nf */
#ifndef _InterlockedDecrement64_rel
#define _InterlockedDecrement64_rel _InterlockedDecrement64_rel
extern __int64 (_InterlockedDecrement64_rel)(__int64 volatile *__px);
#pragma intrinsic(_InterlockedDecrement64_rel)
#endif /* !_InterlockedDecrement64_rel */

#ifndef _InterlockedAnd8_acq
#define _InterlockedAnd8_acq _InterlockedAnd8_acq
extern char (_InterlockedAnd8_acq)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedAnd8_acq)
#endif /* !_InterlockedAnd8_acq */
#ifndef _InterlockedAnd8_nf
#define _InterlockedAnd8_nf _InterlockedAnd8_nf
extern char (_InterlockedAnd8_nf)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedAnd8_nf)
#endif /* !_InterlockedAnd8_nf */
#ifndef _InterlockedAnd8_rel
#define _InterlockedAnd8_rel _InterlockedAnd8_rel
extern char (_InterlockedAnd8_rel)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedAnd8_rel)
#endif /* !_InterlockedAnd8_rel */
#ifndef _InterlockedAnd16_acq
#define _InterlockedAnd16_acq _InterlockedAnd16_acq
extern short (_InterlockedAnd16_acq)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedAnd16_acq)
#endif /* !_InterlockedAnd16_acq */
#ifndef _InterlockedAnd16_nf
#define _InterlockedAnd16_nf _InterlockedAnd16_nf
extern short (_InterlockedAnd16_nf)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedAnd16_nf)
#endif /* !_InterlockedAnd16_nf */
#ifndef _InterlockedAnd16_rel
#define _InterlockedAnd16_rel _InterlockedAnd16_rel
extern short (_InterlockedAnd16_rel)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedAnd16_rel)
#endif /* !_InterlockedAnd16_rel */
#ifndef _InterlockedAnd_acq
#define _InterlockedAnd_acq _InterlockedAnd_acq
extern long (_InterlockedAnd_acq)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedAnd_acq)
#endif /* !_InterlockedAnd_acq */
#ifndef _InterlockedAnd_nf
#define _InterlockedAnd_nf _InterlockedAnd_nf
extern long (_InterlockedAnd_nf)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedAnd_nf)
#endif /* !_InterlockedAnd_nf */
#ifndef _InterlockedAnd_rel
#define _InterlockedAnd_rel _InterlockedAnd_rel
extern long (_InterlockedAnd_rel)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedAnd_rel)
#endif /* !_InterlockedAnd_rel */
#ifndef _InterlockedAnd64_acq
#define _InterlockedAnd64_acq _InterlockedAnd64_acq
extern __int64 (_InterlockedAnd64_acq)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedAnd64_acq)
#endif /* !_InterlockedAnd64_acq */
#ifndef _InterlockedAnd64_nf
#define _InterlockedAnd64_nf _InterlockedAnd64_nf
extern __int64 (_InterlockedAnd64_nf)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedAnd64_nf)
#endif /* !_InterlockedAnd64_nf */
#ifndef _InterlockedAnd64_rel
#define _InterlockedAnd64_rel _InterlockedAnd64_rel
extern __int64 (_InterlockedAnd64_rel)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedAnd64_rel)
#endif /* !_InterlockedAnd64_rel */

#ifndef _InterlockedOr8_acq
#define _InterlockedOr8_acq _InterlockedOr8_acq
extern char (_InterlockedOr8_acq)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedOr8_acq)
#endif /* !_InterlockedOr8_acq */
#ifndef _InterlockedOr8_nf
#define _InterlockedOr8_nf _InterlockedOr8_nf
extern char (_InterlockedOr8_nf)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedOr8_nf)
#endif /* !_InterlockedOr8_nf */
#ifndef _InterlockedOr8_rel
#define _InterlockedOr8_rel _InterlockedOr8_rel
extern char (_InterlockedOr8_rel)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedOr8_rel)
#endif /* !_InterlockedOr8_rel */
#ifndef _InterlockedOr16_acq
#define _InterlockedOr16_acq _InterlockedOr16_acq
extern short (_InterlockedOr16_acq)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedOr16_acq)
#endif /* !_InterlockedOr16_acq */
#ifndef _InterlockedOr16_nf
#define _InterlockedOr16_nf _InterlockedOr16_nf
extern short (_InterlockedOr16_nf)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedOr16_nf)
#endif /* !_InterlockedOr16_nf */
#ifndef _InterlockedOr16_rel
#define _InterlockedOr16_rel _InterlockedOr16_rel
extern short (_InterlockedOr16_rel)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedOr16_rel)
#endif /* !_InterlockedOr16_rel */
#ifndef _InterlockedOr_acq
#define _InterlockedOr_acq _InterlockedOr_acq
extern long (_InterlockedOr_acq)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedOr_acq)
#endif /* !_InterlockedOr_acq */
#ifndef _InterlockedOr_nf
#define _InterlockedOr_nf _InterlockedOr_nf
extern long (_InterlockedOr_nf)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedOr_nf)
#endif /* !_InterlockedOr_nf */
#ifndef _InterlockedOr_rel
#define _InterlockedOr_rel _InterlockedOr_rel
extern long (_InterlockedOr_rel)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedOr_rel)
#endif /* !_InterlockedOr_rel */
#ifndef _InterlockedOr64_acq
#define _InterlockedOr64_acq _InterlockedOr64_acq
extern __int64 (_InterlockedOr64_acq)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedOr64_acq)
#endif /* !_InterlockedOr64_acq */
#ifndef _InterlockedOr64_nf
#define _InterlockedOr64_nf _InterlockedOr64_nf
extern __int64 (_InterlockedOr64_nf)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedOr64_nf)
#endif /* !_InterlockedOr64_nf */
#ifndef _InterlockedOr64_rel
#define _InterlockedOr64_rel _InterlockedOr64_rel
extern __int64 (_InterlockedOr64_rel)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedOr64_rel)
#endif /* !_InterlockedOr64_rel */

#ifndef _InterlockedXor8_acq
#define _InterlockedXor8_acq _InterlockedXor8_acq
extern char (_InterlockedXor8_acq)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedXor8_acq)
#endif /* !_InterlockedXor8_acq */
#ifndef _InterlockedXor8_nf
#define _InterlockedXor8_nf _InterlockedXor8_nf
extern char (_InterlockedXor8_nf)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedXor8_nf)
#endif /* !_InterlockedXor8_nf */
#ifndef _InterlockedXor8_rel
#define _InterlockedXor8_rel _InterlockedXor8_rel
extern char (_InterlockedXor8_rel)(char volatile *__px, char __v);
#pragma intrinsic(_InterlockedXor8_rel)
#endif /* !_InterlockedXor8_rel */
#ifndef _InterlockedXor16_acq
#define _InterlockedXor16_acq _InterlockedXor16_acq
extern short (_InterlockedXor16_acq)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedXor16_acq)
#endif /* !_InterlockedXor16_acq */
#ifndef _InterlockedXor16_nf
#define _InterlockedXor16_nf _InterlockedXor16_nf
extern short (_InterlockedXor16_nf)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedXor16_nf)
#endif /* !_InterlockedXor16_nf */
#ifndef _InterlockedXor16_rel
#define _InterlockedXor16_rel _InterlockedXor16_rel
extern short (_InterlockedXor16_rel)(short volatile *__px, short __v);
#pragma intrinsic(_InterlockedXor16_rel)
#endif /* !_InterlockedXor16_rel */
#ifndef _InterlockedXor_acq
#define _InterlockedXor_acq _InterlockedXor_acq
extern long (_InterlockedXor_acq)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedXor_acq)
#endif /* !_InterlockedXor_acq */
#ifndef _InterlockedXor_nf
#define _InterlockedXor_nf _InterlockedXor_nf
extern long (_InterlockedXor_nf)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedXor_nf)
#endif /* !_InterlockedXor_nf */
#ifndef _InterlockedXor_rel
#define _InterlockedXor_rel _InterlockedXor_rel
extern long (_InterlockedXor_rel)(long volatile *__px, long __v);
#pragma intrinsic(_InterlockedXor_rel)
#endif /* !_InterlockedXor_rel */
#ifndef _InterlockedXor64_acq
#define _InterlockedXor64_acq _InterlockedXor64_acq
extern __int64 (_InterlockedXor64_acq)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedXor64_acq)
#endif /* !_InterlockedXor64_acq */
#ifndef _InterlockedXor64_nf
#define _InterlockedXor64_nf _InterlockedXor64_nf
extern __int64 (_InterlockedXor64_nf)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedXor64_nf)
#endif /* !_InterlockedXor64_nf */
#ifndef _InterlockedXor64_rel
#define _InterlockedXor64_rel _InterlockedXor64_rel
extern __int64 (_InterlockedXor64_rel)(__int64 volatile *__px, __int64 __v);
#pragma intrinsic(_InterlockedXor64_rel)
#endif /* !_InterlockedXor64_rel */

#define __hybrid_atomic_xch8_release(p, val)       ((__UINT8_TYPE__)_InterlockedExchange8_rel((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_xch16_release(p, val)      ((__UINT16_TYPE__)_InterlockedExchange16_rel((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_xch32_release(p, val)      ((__UINT32_TYPE__)_InterlockedExchange_rel((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_xch64_release(p, val)      ((__UINT64_TYPE__)_InterlockedExchange64_rel((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchadd8_release(p, val)  ((__UINT8_TYPE__)_InterlockedExchangeAdd8_rel((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchadd16_release(p, val) ((__UINT16_TYPE__)_InterlockedExchangeAdd16_rel((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchadd32_release(p, val) ((__UINT32_TYPE__)_InterlockedExchangeAdd_rel((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchadd64_release(p, val) ((__UINT64_TYPE__)_InterlockedExchangeAdd64_rel((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchand8_release(p, val)  ((__UINT8_TYPE__)_InterlockedAnd8_rel((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchand16_release(p, val) ((__UINT16_TYPE__)_InterlockedAnd16_rel((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchand32_release(p, val) ((__UINT32_TYPE__)_InterlockedAnd_rel((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchand64_release(p, val) ((__UINT64_TYPE__)_InterlockedAnd64_rel((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchor8_release(p, val)   ((__UINT8_TYPE__)_InterlockedOr8_rel((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchor16_release(p, val)  ((__UINT16_TYPE__)_InterlockedOr16_rel((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchor32_release(p, val)  ((__UINT32_TYPE__)_InterlockedOr_rel((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchor64_release(p, val)  ((__UINT64_TYPE__)_InterlockedOr64_rel((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchxor8_release(p, val)  ((__UINT8_TYPE__)_InterlockedXor8_rel((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchxor16_release(p, val) ((__UINT16_TYPE__)_InterlockedXor16_rel((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchxor32_release(p, val) ((__UINT32_TYPE__)_InterlockedXor_rel((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchxor64_release(p, val) ((__UINT64_TYPE__)_InterlockedXor64_rel((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_incfetch8_release(p)       ((__UINT8_TYPE__)_InterlockedIncrement8_rel((char volatile *)(p)))
#define __hybrid_atomic_incfetch16_release(p)      ((__UINT16_TYPE__)_InterlockedIncrement16_rel((short volatile *)(p)))
#define __hybrid_atomic_incfetch32_release(p)      ((__UINT32_TYPE__)_InterlockedIncrement_rel((long volatile *)(p)))
#define __hybrid_atomic_incfetch64_release(p)      ((__UINT64_TYPE__)_InterlockedIncrement64_rel((__int64 volatile *)(p)))
#define __hybrid_atomic_decfetch8_release(p)       ((__UINT8_TYPE__)_InterlockedDecrement8_rel((char volatile *)(p)))
#define __hybrid_atomic_decfetch16_release(p)      ((__UINT16_TYPE__)_InterlockedDecrement16_rel((short volatile *)(p)))
#define __hybrid_atomic_decfetch32_release(p)      ((__UINT32_TYPE__)_InterlockedDecrement_rel((long volatile *)(p)))
#define __hybrid_atomic_decfetch64_release(p)      ((__UINT64_TYPE__)_InterlockedDecrement64_rel((__int64 volatile *)(p)))

#define __hybrid_atomic_xch8_acquire(p, val)       ((__UINT8_TYPE__)_InterlockedExchange8_acq((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_xch16_acquire(p, val)      ((__UINT16_TYPE__)_InterlockedExchange16_acq((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_xch32_acquire(p, val)      ((__UINT32_TYPE__)_InterlockedExchange_acq((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_xch64_acquire(p, val)      ((__UINT64_TYPE__)_InterlockedExchange64_acq((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchadd8_acquire(p, val)  ((__UINT8_TYPE__)_InterlockedExchangeAdd8_acq((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchadd16_acquire(p, val) ((__UINT16_TYPE__)_InterlockedExchangeAdd16_acq((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchadd32_acquire(p, val) ((__UINT32_TYPE__)_InterlockedExchangeAdd_acq((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchadd64_acquire(p, val) ((__UINT64_TYPE__)_InterlockedExchangeAdd64_acq((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchand8_acquire(p, val)  ((__UINT8_TYPE__)_InterlockedAnd8_acq((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchand16_acquire(p, val) ((__UINT16_TYPE__)_InterlockedAnd16_acq((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchand32_acquire(p, val) ((__UINT32_TYPE__)_InterlockedAnd_acq((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchand64_acquire(p, val) ((__UINT64_TYPE__)_InterlockedAnd64_acq((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchor8_acquire(p, val)   ((__UINT8_TYPE__)_InterlockedOr8_acq((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchor16_acquire(p, val)  ((__UINT16_TYPE__)_InterlockedOr16_acq((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchor32_acquire(p, val)  ((__UINT32_TYPE__)_InterlockedOr_acq((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchor64_acquire(p, val)  ((__UINT64_TYPE__)_InterlockedOr64_acq((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchxor8_acquire(p, val)  ((__UINT8_TYPE__)_InterlockedXor8_acq((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchxor16_acquire(p, val) ((__UINT16_TYPE__)_InterlockedXor16_acq((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchxor32_acquire(p, val) ((__UINT32_TYPE__)_InterlockedXor_acq((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchxor64_acquire(p, val) ((__UINT64_TYPE__)_InterlockedXor64_acq((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_incfetch8_acquire(p)       ((__UINT8_TYPE__)_InterlockedIncrement8_acq((char volatile *)(p)))
#define __hybrid_atomic_incfetch16_acquire(p)      ((__UINT16_TYPE__)_InterlockedIncrement16_acq((short volatile *)(p)))
#define __hybrid_atomic_incfetch32_acquire(p)      ((__UINT32_TYPE__)_InterlockedIncrement_acq((long volatile *)(p)))
#define __hybrid_atomic_incfetch64_acquire(p)      ((__UINT64_TYPE__)_InterlockedIncrement64_acq((__int64 volatile *)(p)))
#define __hybrid_atomic_decfetch8_acquire(p)       ((__UINT8_TYPE__)_InterlockedDecrement8_acq((char volatile *)(p)))
#define __hybrid_atomic_decfetch16_acquire(p)      ((__UINT16_TYPE__)_InterlockedDecrement16_acq((short volatile *)(p)))
#define __hybrid_atomic_decfetch32_acquire(p)      ((__UINT32_TYPE__)_InterlockedDecrement_acq((long volatile *)(p)))
#define __hybrid_atomic_decfetch64_acquire(p)      ((__UINT64_TYPE__)_InterlockedDecrement64_acq((__int64 volatile *)(p)))

#define __hybrid_atomic_xch8_relaxed(p, val)       ((__UINT8_TYPE__)_InterlockedExchange8_nf((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_xch16_relaxed(p, val)      ((__UINT16_TYPE__)_InterlockedExchange16_nf((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_xch32_relaxed(p, val)      ((__UINT32_TYPE__)_InterlockedExchange_nf((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_xch64_relaxed(p, val)      ((__UINT64_TYPE__)_InterlockedExchange64_nf((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchadd8_relaxed(p, val)  ((__UINT8_TYPE__)_InterlockedExchangeAdd8_nf((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchadd16_relaxed(p, val) ((__UINT16_TYPE__)_InterlockedExchangeAdd16_nf((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchadd32_relaxed(p, val) ((__UINT32_TYPE__)_InterlockedExchangeAdd_nf((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchadd64_relaxed(p, val) ((__UINT64_TYPE__)_InterlockedExchangeAdd64_nf((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchand8_relaxed(p, val)  ((__UINT8_TYPE__)_InterlockedAnd8_nf((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchand16_relaxed(p, val) ((__UINT16_TYPE__)_InterlockedAnd16_nf((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchand32_relaxed(p, val) ((__UINT32_TYPE__)_InterlockedAnd_nf((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchand64_relaxed(p, val) ((__UINT64_TYPE__)_InterlockedAnd64_nf((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchor8_relaxed(p, val)   ((__UINT8_TYPE__)_InterlockedOr8_nf((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchor16_relaxed(p, val)  ((__UINT16_TYPE__)_InterlockedOr16_nf((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchor32_relaxed(p, val)  ((__UINT32_TYPE__)_InterlockedOr_nf((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchor64_relaxed(p, val)  ((__UINT64_TYPE__)_InterlockedOr64_nf((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_fetchxor8_relaxed(p, val)  ((__UINT8_TYPE__)_InterlockedXor8_nf((char volatile *)(p), (char)(val)))
#define __hybrid_atomic_fetchxor16_relaxed(p, val) ((__UINT16_TYPE__)_InterlockedXor16_nf((short volatile *)(p), (short)(val)))
#define __hybrid_atomic_fetchxor32_relaxed(p, val) ((__UINT32_TYPE__)_InterlockedXor_nf((long volatile *)(p), (long)(val)))
#define __hybrid_atomic_fetchxor64_relaxed(p, val) ((__UINT64_TYPE__)_InterlockedXor64_nf((__int64 volatile *)(p), (__int64)(val)))
#define __hybrid_atomic_incfetch8_relaxed(p)       ((__UINT8_TYPE__)_InterlockedIncrement8_nf((char volatile *)(p)))
#define __hybrid_atomic_incfetch16_relaxed(p)      ((__UINT16_TYPE__)_InterlockedIncrement16_nf((short volatile *)(p)))
#define __hybrid_atomic_incfetch32_relaxed(p)      ((__UINT32_TYPE__)_InterlockedIncrement_nf((long volatile *)(p)))
#define __hybrid_atomic_incfetch64_relaxed(p)      ((__UINT64_TYPE__)_InterlockedIncrement64_nf((__int64 volatile *)(p)))
#define __hybrid_atomic_decfetch8_relaxed(p)       ((__UINT8_TYPE__)_InterlockedDecrement8_nf((char volatile *)(p)))
#define __hybrid_atomic_decfetch16_relaxed(p)      ((__UINT16_TYPE__)_InterlockedDecrement16_nf((short volatile *)(p)))
#define __hybrid_atomic_decfetch32_relaxed(p)      ((__UINT32_TYPE__)_InterlockedDecrement_nf((long volatile *)(p)))
#define __hybrid_atomic_decfetch64_relaxed(p)      ((__UINT64_TYPE__)_InterlockedDecrement64_nf((__int64 volatile *)(p)))

#define __hybrid_atomic_xch8(p, val, order)       __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_xch8, (p, val))
#define __hybrid_atomic_xch16(p, val, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_xch16, (p, val))
#define __hybrid_atomic_xch32(p, val, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_xch32, (p, val))
#define __hybrid_atomic_xch64(p, val, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_xch64, (p, val))
#define __hybrid_atomic_fetchadd8(p, val, order)  __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchadd8, (p, val))
#define __hybrid_atomic_fetchadd16(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchadd16, (p, val))
#define __hybrid_atomic_fetchadd32(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchadd32, (p, val))
#define __hybrid_atomic_fetchadd64(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchadd64, (p, val))
#define __hybrid_atomic_fetchand8(p, val, order)  __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchand8, (p, val))
#define __hybrid_atomic_fetchand16(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchand16, (p, val))
#define __hybrid_atomic_fetchand32(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchand32, (p, val))
#define __hybrid_atomic_fetchand64(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchand64, (p, val))
#define __hybrid_atomic_fetchor8(p, val, order)   __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchor8, (p, val))
#define __hybrid_atomic_fetchor16(p, val, order)  __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchor16, (p, val))
#define __hybrid_atomic_fetchor32(p, val, order)  __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchor32, (p, val))
#define __hybrid_atomic_fetchor64(p, val, order)  __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchor64, (p, val))
#define __hybrid_atomic_fetchxor8(p, val, order)  __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchxor8, (p, val))
#define __hybrid_atomic_fetchxor16(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchxor16, (p, val))
#define __hybrid_atomic_fetchxor32(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchxor32, (p, val))
#define __hybrid_atomic_fetchxor64(p, val, order) __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_fetchxor64, (p, val))
#define __hybrid_atomic_incfetch8(p, order)       __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_incfetch8, (p))
#define __hybrid_atomic_incfetch16(p, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_incfetch16, (p))
#define __hybrid_atomic_incfetch32(p, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_incfetch32, (p))
#define __hybrid_atomic_incfetch64(p, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_incfetch64, (p))
#define __hybrid_atomic_decfetch8(p, order)       __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_decfetch8, (p))
#define __hybrid_atomic_decfetch16(p, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_decfetch16, (p))
#define __hybrid_atomic_decfetch32(p, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_decfetch32, (p))
#define __hybrid_atomic_decfetch64(p, order)      __HYBRID_PRIVATE_ARM_ATOMIC(order, __hybrid_atomic_decfetch64, (p))
#define __hybrid_atomic_thread_fence(order) \
	((order != __ATOMIC_RELAXED) ? __dmb(_ARM_BARRIER_ISH) : (void)0)
#else /* __arm__ */

#define __hybrid_atomic_xch8(p, val, order)       __hybrid_atomic_xch8_seq_cst(p, val)
#define __hybrid_atomic_xch16(p, val, order)      __hybrid_atomic_xch16_seq_cst(p, val)
#define __hybrid_atomic_xch32(p, val, order)      __hybrid_atomic_xch32_seq_cst(p, val)
#define __hybrid_atomic_xch64(p, val, order)      __hybrid_atomic_xch64_seq_cst(p, val)
#define __hybrid_atomic_fetchadd8(p, val, order)  __hybrid_atomic_fetchadd8_seq_cst(p, val)
#define __hybrid_atomic_fetchadd16(p, val, order) __hybrid_atomic_fetchadd16_seq_cst(p, val)
#define __hybrid_atomic_fetchadd32(p, val, order) __hybrid_atomic_fetchadd32_seq_cst(p, val)
#define __hybrid_atomic_fetchadd64(p, val, order) __hybrid_atomic_fetchadd64_seq_cst(p, val)
#define __hybrid_atomic_fetchand8(p, val, order)  __hybrid_atomic_fetchand8_seq_cst(p, val)
#define __hybrid_atomic_fetchand16(p, val, order) __hybrid_atomic_fetchand16_seq_cst(p, val)
#define __hybrid_atomic_fetchand32(p, val, order) __hybrid_atomic_fetchand32_seq_cst(p, val)
#define __hybrid_atomic_fetchand64(p, val, order) __hybrid_atomic_fetchand64_seq_cst(p, val)
#define __hybrid_atomic_fetchor8(p, val, order)   __hybrid_atomic_fetchor8_seq_cst(p, val)
#define __hybrid_atomic_fetchor16(p, val, order)  __hybrid_atomic_fetchor16_seq_cst(p, val)
#define __hybrid_atomic_fetchor32(p, val, order)  __hybrid_atomic_fetchor32_seq_cst(p, val)
#define __hybrid_atomic_fetchor64(p, val, order)  __hybrid_atomic_fetchor64_seq_cst(p, val)
#define __hybrid_atomic_fetchxor8(p, val, order)  __hybrid_atomic_fetchxor8_seq_cst(p, val)
#define __hybrid_atomic_fetchxor16(p, val, order) __hybrid_atomic_fetchxor16_seq_cst(p, val)
#define __hybrid_atomic_fetchxor32(p, val, order) __hybrid_atomic_fetchxor32_seq_cst(p, val)
#define __hybrid_atomic_fetchxor64(p, val, order) __hybrid_atomic_fetchxor64_seq_cst(p, val)
#define __hybrid_atomic_incfetch8(p, order)       __hybrid_atomic_incfetch8_seq_cst(p)
#define __hybrid_atomic_incfetch16(p, order)      __hybrid_atomic_incfetch16_seq_cst(p)
#define __hybrid_atomic_incfetch32(p, order)      __hybrid_atomic_incfetch32_seq_cst(p)
#define __hybrid_atomic_incfetch64(p, order)      __hybrid_atomic_incfetch64_seq_cst(p)
#define __hybrid_atomic_decfetch8(p, order)       __hybrid_atomic_decfetch8_seq_cst(p)
#define __hybrid_atomic_decfetch16(p, order)      __hybrid_atomic_decfetch16_seq_cst(p)
#define __hybrid_atomic_decfetch32(p, order)      __hybrid_atomic_decfetch32_seq_cst(p)
#define __hybrid_atomic_decfetch64(p, order)      __hybrid_atomic_decfetch64_seq_cst(p)

#define __hybrid_atomic_thread_fence(order) \
	((__NAMESPACE_INT_SYM __impl_hybrid_atomic_thread_fence)(order))
__NAMESPACE_INT_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL void
__NOTHROW_NCX(__impl_hybrid_atomic_thread_fence)(int __order) {
	if (__order >= __ATOMIC_SEQ_CST) {
		volatile __UINT32_TYPE__ __guard;
		__COMPILER_BARRIER();
		__hybrid_atomic_xch32_seq_cst(&__guard, 0);
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
