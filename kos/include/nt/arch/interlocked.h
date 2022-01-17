/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_NT_ARCH_INTERLOCKED_H
#define GUARD_NT_ARCH_INTERLOCKED_H 1

#include <__stdinc.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

/* _ReadWriteBarrier */
#ifndef _ReadBarrier
#define _ReadBarrier() __COMPILER_READ_BARRIER()
#endif /* !_ReadBarrier */
#ifndef _WriteBarrier
#define _WriteBarrier() __COMPILER_WRITE_BARRIER()
#endif /* !_WriteBarrier */
#ifndef _ReadWriteBarrier
#define _ReadWriteBarrier() __COMPILER_BARRIER()
#endif /* !_ReadWriteBarrier */


/* _InterlockedAnd */
#ifndef _InterlockedAnd8
#define _InterlockedAnd8(ptr, mask) \
	__hybrid_atomic_fetchand(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd8 */
#ifndef _InterlockedAnd16
#define _InterlockedAnd16(ptr, mask) \
	__hybrid_atomic_fetchand(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd16 */
#ifndef _InterlockedAnd
#define _InterlockedAnd(ptr, mask) \
	__hybrid_atomic_fetchand(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd */
#ifndef _InterlockedAnd64
#define _InterlockedAnd64(ptr, mask) \
	__hybrid_atomic_fetchand(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd64 */
//#ifndef _InterlockedAndPointer
//#define _InterlockedAndPointer(ptr, mask) \
//	__hybrid_atomic_fetchand(*__COMPILER_REQTYPE(void **, ptr), mask, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedAndPointer */


/* _InterlockedOr */
#ifndef _InterlockedOr8
#define _InterlockedOr8(ptr, mask) \
	__hybrid_atomic_fetchor(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr8 */
#ifndef _InterlockedOr16
#define _InterlockedOr16(ptr, mask) \
	__hybrid_atomic_fetchor(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr16 */
#ifndef _InterlockedOr
#define _InterlockedOr(ptr, mask) \
	__hybrid_atomic_fetchor(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr */
#ifndef _InterlockedOr64
#define _InterlockedOr64(ptr, mask) \
	__hybrid_atomic_fetchor(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr64 */
//#ifndef _InterlockedOrPointer
//#define _InterlockedOrPointer(ptr, mask) \
//	__hybrid_atomic_fetchor(*__COMPILER_REQTYPE(void **, ptr), mask, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedOrPointer */


/* _InterlockedXor */
#ifndef _InterlockedXor8
#define _InterlockedXor8(ptr, mask) \
	__hybrid_atomic_fetchxor(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor8 */
#ifndef _InterlockedXor16
#define _InterlockedXor16(ptr, mask) \
	__hybrid_atomic_fetchxor(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor16 */
#ifndef _InterlockedXor
#define _InterlockedXor(ptr, mask) \
	__hybrid_atomic_fetchxor(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor */
#ifndef _InterlockedXor64
#define _InterlockedXor64(ptr, mask) \
	__hybrid_atomic_fetchxor(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor64 */
//#ifndef _InterlockedXorPointer
//#define _InterlockedXorPointer(ptr, mask) \
//	__hybrid_atomic_fetchxor(*__COMPILER_REQTYPE(void **, ptr), mask, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedXorPointer */


/* _InterlockedCompareExchange */
#ifndef _InterlockedCompareExchange8
#define _InterlockedCompareExchange8(ptr, newval, oldval)                 \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__INT8_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange8 */
#ifndef _InterlockedCompareExchange16
#define _InterlockedCompareExchange16(ptr, newval, oldval)                 \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__INT16_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange16 */
#ifndef _InterlockedCompareExchange
#define _InterlockedCompareExchange(ptr, newval, oldval)                    \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange */
#ifndef _InterlockedCompareExchange64
#define _InterlockedCompareExchange64(ptr, newval, oldval)                  \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange64 */
#ifndef _InterlockedCompareExchangePointer
#define _InterlockedCompareExchangePointer(ptr, newval, oldval)   \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(void **, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchangePointer */


/* _InterlockedCompareExchangeAcquire */
#ifndef _InterlockedCompareExchangeAcquire8
#define _InterlockedCompareExchangeAcquire8(ptr, newval, oldval)          \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__INT8_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire8 */
#ifndef _InterlockedCompareExchangeAcquire16
#define _InterlockedCompareExchangeAcquire16(ptr, newval, oldval)          \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__INT16_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire16 */
#ifndef _InterlockedCompareExchangeAcquire
#define _InterlockedCompareExchangeAcquire(ptr, newval, oldval)             \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire */
#ifndef _InterlockedCompareExchangeAcquire64
#define _InterlockedCompareExchangeAcquire64(ptr, newval, oldval)           \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire64 */
#ifndef _InterlockedCompareExchangeAcquirePointer
#define _InterlockedCompareExchangeAcquirePointer(ptr, newval, oldval) \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(void **, val),      \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquirePointer */


/* _InterlockedCompareExchangeRelease */
#ifndef _InterlockedCompareExchangeRelease8
#define _InterlockedCompareExchangeRelease8(ptr, newval, oldval)          \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__INT8_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease8 */
#ifndef _InterlockedCompareExchangeRelease16
#define _InterlockedCompareExchangeRelease16(ptr, newval, oldval)          \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__INT16_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease16 */
#ifndef _InterlockedCompareExchangeRelease
#define _InterlockedCompareExchangeRelease(ptr, newval, oldval)             \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease */
#ifndef _InterlockedCompareExchangeRelease64
#define _InterlockedCompareExchangeRelease64(ptr, newval, oldval)           \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease64 */
#ifndef _InterlockedCompareExchangeReleasePointer
#define _InterlockedCompareExchangeReleasePointer(ptr, newval, oldval) \
	__hybrid_atomic_cmpxch_val(*__COMPILER_REQTYPE(void **, val),      \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeReleasePointer */


/* _InterlockedDecrement */
//#ifndef _InterlockedDecrement8
//#define _InterlockedDecrement8(ptr) \
//	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedDecrement8 */
#ifndef _InterlockedDecrement16
#define _InterlockedDecrement16(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedDecrement16 */
#ifndef _InterlockedDecrement
#define _InterlockedDecrement(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedDecrement */
#ifndef _InterlockedDecrement64
#define _InterlockedDecrement64(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedDecrement64 */
//#ifndef _InterlockedDecrementPointer
//#define _InterlockedDecrementPointer(ptr) \
//	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(void **, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedDecrementPointer */


/* _InterlockedDecrementAcquire */
//#ifndef _InterlockedDecrementAcquire8
//#define _InterlockedDecrementAcquire8(ptr) \
//	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedDecrementAcquire8 */
#ifndef _InterlockedDecrementAcquire16
#define _InterlockedDecrementAcquire16(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedDecrementAcquire16 */
#ifndef _InterlockedDecrementAcquire
#define _InterlockedDecrementAcquire(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedDecrementAcquire */
#ifndef _InterlockedDecrementAcquire64
#define _InterlockedDecrementAcquire64(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedDecrementAcquire64 */
//#ifndef _InterlockedDecrementAcquirePointer
//#define _InterlockedDecrementAcquirePointer(ptr) \
//	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(void **, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedDecrementAcquirePointer */


/* _InterlockedDecrementRelease */
//#ifndef _InterlockedDecrementRelease8
//#define _InterlockedDecrementRelease8(ptr) \
//	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedDecrementRelease8 */
#ifndef _InterlockedDecrementRelease16
#define _InterlockedDecrementRelease16(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedDecrementRelease16 */
#ifndef _InterlockedDecrementRelease
#define _InterlockedDecrementRelease(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedDecrementRelease */
#ifndef _InterlockedDecrementRelease64
#define _InterlockedDecrementRelease64(ptr) \
	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedDecrementRelease64 */
//#ifndef _InterlockedDecrementReleasePointer
//#define _InterlockedDecrementReleasePointer(ptr) \
//	__hybrid_atomic_decfetch(*__COMPILER_REQTYPE(void **, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedDecrementReleasePointer */


/* _InterlockedIncrement */
//#ifndef _InterlockedIncrement8
//#define _InterlockedIncrement8(ptr) \
//	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedIncrement8 */
#ifndef _InterlockedIncrement16
#define _InterlockedIncrement16(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedIncrement16 */
#ifndef _InterlockedIncrement
#define _InterlockedIncrement(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedIncrement */
#ifndef _InterlockedIncrement64
#define _InterlockedIncrement64(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedIncrement64 */
//#ifndef _InterlockedIncrementPointer
//#define _InterlockedIncrementPointer(ptr) \
//	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(void **, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedIncrementPointer */


/* _InterlockedIncrementAcquire */
//#ifndef _InterlockedIncrementAcquire8
//#define _InterlockedIncrementAcquire8(ptr) \
//	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedIncrementAcquire8 */
#ifndef _InterlockedIncrementAcquire16
#define _InterlockedIncrementAcquire16(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedIncrementAcquire16 */
#ifndef _InterlockedIncrementAcquire
#define _InterlockedIncrementAcquire(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedIncrementAcquire */
#ifndef _InterlockedIncrementAcquire64
#define _InterlockedIncrementAcquire64(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedIncrementAcquire64 */
//#ifndef _InterlockedIncrementAcquirePointer
//#define _InterlockedIncrementAcquirePointer(ptr) \
//	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(void **, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedIncrementAcquirePointer */


/* _InterlockedIncrementRelease */
//#ifndef _InterlockedIncrementRelease8
//#define _InterlockedIncrementRelease8(ptr) \
//	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedIncrementRelease8 */
#ifndef _InterlockedIncrementRelease16
#define _InterlockedIncrementRelease16(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedIncrementRelease16 */
#ifndef _InterlockedIncrementRelease
#define _InterlockedIncrementRelease(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedIncrementRelease */
#ifndef _InterlockedIncrementRelease64
#define _InterlockedIncrementRelease64(ptr) \
	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedIncrementRelease64 */
//#ifndef _InterlockedIncrementReleasePointer
//#define _InterlockedIncrementReleasePointer(ptr) \
//	__hybrid_atomic_incfetch(*__COMPILER_REQTYPE(void **, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedIncrementReleasePointer */


/* _InterlockedExchange */
#ifndef _InterlockedExchange8
#define _InterlockedExchange8(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange8 */
#ifndef _InterlockedExchange16
#define _InterlockedExchange16(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange16 */
#ifndef _InterlockedExchange
#define _InterlockedExchange(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange */
#ifndef _InterlockedExchange64
#define _InterlockedExchange64(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange64 */
#ifndef _InterlockedExchangePointer
#define _InterlockedExchangePointer(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangePointer */


/* _InterlockedExchangeAcquire */
#ifndef _InterlockedExchangeAcquire8
#define _InterlockedExchangeAcquire8(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire8 */
#ifndef _InterlockedExchangeAcquire16
#define _InterlockedExchangeAcquire16(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire16 */
#ifndef _InterlockedExchangeAcquire
#define _InterlockedExchangeAcquire(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire */
#ifndef _InterlockedExchangeAcquire64
#define _InterlockedExchangeAcquire64(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire64 */
#ifndef _InterlockedExchangeAcquirePointer
#define _InterlockedExchangeAcquirePointer(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquirePointer */


/* _InterlockedExchangeRelease */
#ifndef _InterlockedExchangeRelease8
#define _InterlockedExchangeRelease8(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease8 */
#ifndef _InterlockedExchangeRelease16
#define _InterlockedExchangeRelease16(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease16 */
#ifndef _InterlockedExchangeRelease
#define _InterlockedExchangeRelease(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease */
#ifndef _InterlockedExchangeRelease64
#define _InterlockedExchangeRelease64(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease64 */
#ifndef _InterlockedExchangeReleasePointer
#define _InterlockedExchangeReleasePointer(ptr, val) \
	__hybrid_atomic_xch(*__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeReleasePointer */


/* _InterlockedExchangeAdd */
#ifndef _InterlockedExchangeAdd8
#define _InterlockedExchangeAdd8(ptr, val) \
	__hybrid_atomic_fetchadd(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd8 */
#ifndef _InterlockedExchangeAdd16
#define _InterlockedExchangeAdd16(ptr, val) \
	__hybrid_atomic_fetchadd(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd16 */
#ifndef _InterlockedExchangeAdd
#define _InterlockedExchangeAdd(ptr, val) \
	__hybrid_atomic_fetchadd(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd */
#ifndef _InterlockedExchangeAdd64
#define _InterlockedExchangeAdd64(ptr, val) \
	__hybrid_atomic_fetchadd(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd64 */
//#ifndef _InterlockedExchangeAddPointer
//#define _InterlockedExchangeAddPointer(ptr, val) \
//	__hybrid_atomic_fetchadd(*__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedExchangeAddPointer */

/* _InterlockedAdd */
#ifndef _InterlockedAdd8
#define _InterlockedAdd8(ptr, val) \
	__hybrid_atomic_addfetch(*__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd8 */
#ifndef _InterlockedAdd16
#define _InterlockedAdd16(ptr, val) \
	__hybrid_atomic_addfetch(*__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd16 */
#ifndef _InterlockedAdd
#define _InterlockedAdd(ptr, val) \
	__hybrid_atomic_addfetch(*__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd */
#ifndef _InterlockedAdd64
#define _InterlockedAdd64(ptr, val) \
	__hybrid_atomic_addfetch(*__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd64 */
//#ifndef _InterlockedAddPointer
//#define _InterlockedAddPointer(ptr, val) \
//	__hybrid_atomic_addfetch(*__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedAddPointer */

__DECL_END
#endif /* __CC__ */

#endif /* GUARD_NT_ARCH_INTERLOCKED_H */
