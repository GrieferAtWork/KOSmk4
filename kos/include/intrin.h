/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: MSVC  (/include/intrin.h) */
/* (#) Portability: MinGW (/mingw-w64-headers/crt/intrin.h) */
#ifndef _INTRIN_H
#define _INTRIN_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__atomic.h>
#include <hybrid/__byteswap.h>
#include <hybrid/__rotate.h>
#include <hybrid/host.h>

#include <asm/intrin.h>

#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin-arith.h>
#include <asm/intrin-lock.h>
#include <asm/intrin-segarith.h>
#endif /* __i386__ || __x86_64__ */

#ifdef __CC__
__DECL_BEGIN

#ifdef _MSC_VER
#ifndef _BitScanForward
#define _BitScanForward _BitScanForward
__BYTE_TYPE__ __NOTHROW_NCX(_BitScanForward)(__ULONG32_TYPE__ *__index, __ULONG32_TYPE__ __mask);
#pragma intrinsic(_BitScanForward)
#endif /* !_BitScanForward */
#ifndef _BitScanForward64
#define _BitScanForward64 _BitScanForward64
__BYTE_TYPE__ __NOTHROW_NCX(_BitScanForward64)(__ULONG32_TYPE__ *__index, __ULONG64_TYPE__ __mask);
#pragma intrinsic(_BitScanForward64)
#endif /* !_BitScanForward64 */
#ifndef _BitScanReverse
#define _BitScanReverse _BitScanReverse
__BYTE_TYPE__ __NOTHROW_NCX(_BitScanReverse)(__ULONG32_TYPE__ *__index, __ULONG32_TYPE__ __mask);
#pragma intrinsic(_BitScanReverse)
#endif /* !_BitScanReverse */
#ifndef _BitScanReverse64
#define _BitScanReverse64 _BitScanReverse64
__BYTE_TYPE__ __NOTHROW_NCX(_BitScanReverse64)(__ULONG32_TYPE__ *__index, __ULONG64_TYPE__ __mask);
#pragma intrinsic(_BitScanReverse64)
#endif /* !_BitScanReverse64 */

#ifndef _bittest
#define _bittest _bittest
__BYTE_TYPE__ __NOTHROW_NCX(_bittest)(__LONG32_TYPE__ const *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittest)
#endif /* !_bittest */
#ifndef _bittest64
#define _bittest64 _bittest64
__BYTE_TYPE__ __NOTHROW_NCX(_bittest64)(__LONG64_TYPE__ const *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittest64)
#endif /* !_bittest64 */
#ifndef _bittestandset
#define _bittestandset _bittestandset
__BYTE_TYPE__ __NOTHROW_NCX(_bittestandset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittestandset)
#endif /* !_bittestandset */
#ifndef _bittestandset64
#define _bittestandset64 _bittestandset64
__BYTE_TYPE__ __NOTHROW_NCX(_bittestandset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittestandset64)
#endif /* !_bittestandset64 */
#ifndef _bittestandreset
#define _bittestandreset _bittestandreset
__BYTE_TYPE__ __NOTHROW_NCX(_bittestandreset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittestandreset)
#endif /* !_bittestandreset */
#ifndef _bittestandreset64
#define _bittestandreset64 _bittestandreset64
__BYTE_TYPE__ __NOTHROW_NCX(_bittestandreset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittestandreset64)
#endif /* !_bittestandreset64 */
#ifndef _bittestandcomplement
#define _bittestandcomplement _bittestandcomplement
__BYTE_TYPE__ __NOTHROW_NCX(_bittestandcomplement)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittestandcomplement)
#endif /* !_bittestandcomplement */
#ifndef _bittestandcomplement64
#define _bittestandcomplement64 _bittestandcomplement64
__BYTE_TYPE__ __NOTHROW_NCX(_bittestandcomplement64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittestandcomplement64)
#endif /* !_bittestandcomplement64 */
#ifndef _interlockedbittestandset
#define _interlockedbittestandset _interlockedbittestandset
__BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandset)(__LONG32_TYPE__ volatile *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandset)
#endif /* !_interlockedbittestandset */
#ifndef _interlockedbittestandreset
#define _interlockedbittestandreset _interlockedbittestandreset
__BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandreset)(__LONG32_TYPE__ volatile *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandset64)
#endif /* !_interlockedbittestandreset */
#ifndef _interlockedbittestandset64
#define _interlockedbittestandset64 _interlockedbittestandset64
__BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandset64)(__LONG64_TYPE__ volatile *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandreset)
#endif /* !_interlockedbittestandset64 */
#ifndef _interlockedbittestandreset64
#define _interlockedbittestandreset64 _interlockedbittestandreset64
__BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandreset64)(__LONG64_TYPE__ volatile *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandreset64)
#endif /* !_interlockedbittestandreset64 */
#endif /* _MSC_VER */


#ifndef _BitScanForward
/* TODO */
#endif /* !_BitScanForward */
#ifndef _BitScanForward64
/* TODO */
#endif /* !_BitScanForward64 */
#ifndef _BitScanReverse
/* TODO */
#endif /* !_BitScanReverse */
#ifndef _BitScanReverse64
/* TODO */
#endif /* !_BitScanReverse64 */

#ifndef _bittest
#define _bittest(pBase, offset) \
	((*__COMPILER_REQTYPE(__LONG32_TYPE__ const *, pBase) >> ((offset)&31)) & 1)
#endif /* !_bittest */
#ifndef _bittest64
#define _bittest64(pBase, offset) \
	((*__COMPILER_REQTYPE(__LONG64_TYPE__ const *, pBase) >> ((offset)&63)) & 1)
#endif /* !_bittest64 */
#ifndef _bittestandcomplement
#define _bittestandcomplement _bittestandcomplement
#if !__has_builtin(_bittestandcomplement)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_bittestandcomplement)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { return !(((*__base ^= (__LONG32_TYPE__)1 << __offset) >> __offset) & 1); }
#endif /* !__has_builtin(_bittestandcomplement) */
#endif /* !_bittestandcomplement */
#ifndef _bittestandcomplement64
#define _bittestandcomplement64 _bittestandcomplement64
#if !__has_builtin(_bittestandcomplement64)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_bittestandcomplement64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { return !(((*__base ^= (__LONG64_TYPE__)1 << __offset) >> __offset) & 1); }
#endif /* !__has_builtin(_bittestandcomplement64) */
#endif /* !_bittestandcomplement64 */
#ifndef _bittestandset
#define _bittestandset _bittestandset
#if !__has_builtin(_bittestandset)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_bittestandset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base |= __mask; return __result; }
#endif /* !__has_builtin(_bittestandset) */
#endif /* !_bittestandset */
#ifndef _bittestandset64
#define _bittestandset64 _bittestandset64
#if !__has_builtin(_bittestandset64)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_bittestandset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base |= __mask; return __result; }
#endif /* !__has_builtin(_bittestandset64) */
#endif /* !_bittestandset64 */
#ifndef _bittestandreset
#define _bittestandreset _bittestandreset
#if !__has_builtin(_bittestandreset)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_bittestandreset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base &= ~__mask; return __result; }
#endif /* !__has_builtin(_bittestandreset) */
#endif /* !_bittestandreset */
#ifndef _bittestandreset64
#define _bittestandreset64 _bittestandreset64
#if !__has_builtin(_bittestandreset64)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_bittestandreset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base &= ~__mask; return __result; }
#endif /* !__has_builtin(_bittestandreset64) */
#endif /* !_bittestandreset64 */
#ifndef _interlockedbittestandcomplement
#define _interlockedbittestandcomplement _interlockedbittestandcomplement
#if !__has_builtin(_interlockedbittestandcomplement)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandcomplement)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { return !((__hybrid_atomic_fetchxor(__base, (__LONG32_TYPE__)1 << __offset, __ATOMIC_SEQ_CST) >> __offset) & 1); }
#endif /* !__has_builtin(_interlockedbittestandcomplement) */
#endif /* !_interlockedbittestandcomplement */
#ifndef _interlockedbittestandcomplement64
#define _interlockedbittestandcomplement64 _interlockedbittestandcomplement64
#if !__has_builtin(_interlockedbittestandcomplement64)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandcomplement64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { return !((__hybrid_atomic_fetchxor(__base, (__LONG64_TYPE__)1 << __offset, __ATOMIC_SEQ_CST) >> __offset) & 1); }
#endif /* !__has_builtin(_interlockedbittestandcomplement64) */
#endif /* !_interlockedbittestandcomplement64 */
#ifndef _interlockedbittestandset
#define _interlockedbittestandset _interlockedbittestandset
#if !__has_builtin(_interlockedbittestandset)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; return (__hybrid_atomic_fetchor(__base, __mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !__has_builtin(_interlockedbittestandset) */
#endif /* !_interlockedbittestandset */
#ifndef _interlockedbittestandset64
#define _interlockedbittestandset64 _interlockedbittestandset64
#if !__has_builtin(_interlockedbittestandset64)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; return (__hybrid_atomic_fetchor(__base, __mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !__has_builtin(_interlockedbittestandset64) */
#endif /* !_interlockedbittestandset64 */
#ifndef _interlockedbittestandreset
#define _interlockedbittestandreset _interlockedbittestandreset
#if !__has_builtin(_interlockedbittestandreset)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandreset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; return (__hybrid_atomic_fetchand(__base, ~__mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !__has_builtin(_interlockedbittestandreset) */
#endif /* !_interlockedbittestandreset */
#ifndef _interlockedbittestandreset64
#define _interlockedbittestandreset64 _interlockedbittestandreset64
#if !__has_builtin(_interlockedbittestandreset64)
__LOCAL __BYTE_TYPE__ __NOTHROW_NCX(_interlockedbittestandreset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; return (__hybrid_atomic_fetchand(__base, ~__mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !__has_builtin(_interlockedbittestandreset64) */
#endif /* !_interlockedbittestandreset64 */


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
	__hybrid_atomic_fetchand(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd8 */
#ifndef _InterlockedAnd16
#define _InterlockedAnd16(ptr, mask) \
	__hybrid_atomic_fetchand(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd16 */
#ifndef _InterlockedAnd
#define _InterlockedAnd(ptr, mask) \
	__hybrid_atomic_fetchand(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd */
#ifndef _InterlockedAnd64
#define _InterlockedAnd64(ptr, mask) \
	__hybrid_atomic_fetchand(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAnd64 */
//#ifndef _InterlockedAndPointer
//#define _InterlockedAndPointer(ptr, mask) \
//	__hybrid_atomic_fetchand(__COMPILER_REQTYPE(void **, ptr), mask, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedAndPointer */


/* _InterlockedOr */
#ifndef _InterlockedOr8
#define _InterlockedOr8(ptr, mask) \
	__hybrid_atomic_fetchor(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr8 */
#ifndef _InterlockedOr16
#define _InterlockedOr16(ptr, mask) \
	__hybrid_atomic_fetchor(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr16 */
#ifndef _InterlockedOr
#define _InterlockedOr(ptr, mask) \
	__hybrid_atomic_fetchor(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr */
#ifndef _InterlockedOr64
#define _InterlockedOr64(ptr, mask) \
	__hybrid_atomic_fetchor(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedOr64 */
//#ifndef _InterlockedOrPointer
//#define _InterlockedOrPointer(ptr, mask) \
//	__hybrid_atomic_fetchor(__COMPILER_REQTYPE(void **, ptr), mask, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedOrPointer */


/* _InterlockedXor */
#ifndef _InterlockedXor8
#define _InterlockedXor8(ptr, mask) \
	__hybrid_atomic_fetchxor(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor8 */
#ifndef _InterlockedXor16
#define _InterlockedXor16(ptr, mask) \
	__hybrid_atomic_fetchxor(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor16 */
#ifndef _InterlockedXor
#define _InterlockedXor(ptr, mask) \
	__hybrid_atomic_fetchxor(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor */
#ifndef _InterlockedXor64
#define _InterlockedXor64(ptr, mask) \
	__hybrid_atomic_fetchxor(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), mask, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedXor64 */
//#ifndef _InterlockedXorPointer
//#define _InterlockedXorPointer(ptr, mask) \
//	__hybrid_atomic_fetchxor(__COMPILER_REQTYPE(void **, ptr), mask, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedXorPointer */


/* _InterlockedCompareExchange */
#ifndef _InterlockedCompareExchange8
#define _InterlockedCompareExchange8(ptr, newval, oldval)                \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__INT8_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange8 */
#ifndef _InterlockedCompareExchange16
#define _InterlockedCompareExchange16(ptr, newval, oldval)                \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__INT16_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange16 */
#ifndef _InterlockedCompareExchange
#define _InterlockedCompareExchange(ptr, newval, oldval)                   \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__LONG32_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange */
#ifndef _InterlockedCompareExchange64
#define _InterlockedCompareExchange64(ptr, newval, oldval)                 \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__LONG64_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchange64 */
#ifndef _InterlockedCompareExchangePointer
#define _InterlockedCompareExchangePointer(ptr, newval, oldval)  \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(void **, val), \
	                           newval, oldval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedCompareExchangePointer */


/* _InterlockedCompareExchangeAcquire */
#ifndef _InterlockedCompareExchangeAcquire8
#define _InterlockedCompareExchangeAcquire8(ptr, newval, oldval)         \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__INT8_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire8 */
#ifndef _InterlockedCompareExchangeAcquire16
#define _InterlockedCompareExchangeAcquire16(ptr, newval, oldval)         \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__INT16_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire16 */
#ifndef _InterlockedCompareExchangeAcquire
#define _InterlockedCompareExchangeAcquire(ptr, newval, oldval)            \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__LONG32_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire */
#ifndef _InterlockedCompareExchangeAcquire64
#define _InterlockedCompareExchangeAcquire64(ptr, newval, oldval)          \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__LONG64_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquire64 */
#ifndef _InterlockedCompareExchangeAcquirePointer
#define _InterlockedCompareExchangeAcquirePointer(ptr, newval, oldval) \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(void **, val),       \
	                           newval, oldval, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedCompareExchangeAcquirePointer */


/* _InterlockedCompareExchangeRelease */
#ifndef _InterlockedCompareExchangeRelease8
#define _InterlockedCompareExchangeRelease8(ptr, newval, oldval)         \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__INT8_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease8 */
#ifndef _InterlockedCompareExchangeRelease16
#define _InterlockedCompareExchangeRelease16(ptr, newval, oldval)         \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__INT16_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease16 */
#ifndef _InterlockedCompareExchangeRelease
#define _InterlockedCompareExchangeRelease(ptr, newval, oldval)            \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__LONG32_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease */
#ifndef _InterlockedCompareExchangeRelease64
#define _InterlockedCompareExchangeRelease64(ptr, newval, oldval)          \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(__LONG64_TYPE__ *, val), \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeRelease64 */
#ifndef _InterlockedCompareExchangeReleasePointer
#define _InterlockedCompareExchangeReleasePointer(ptr, newval, oldval) \
	__hybrid_atomic_cmpxch_val(__COMPILER_REQTYPE(void **, val),       \
	                           newval, oldval, __ATOMIC_RELEASE, __ATOMIC_RELEASE)
#endif /* !_InterlockedCompareExchangeReleasePointer */


/* _InterlockedDecrement */
//#ifndef _InterlockedDecrement8
//#define _InterlockedDecrement8(ptr) \
//	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedDecrement8 */
#ifndef _InterlockedDecrement16
#define _InterlockedDecrement16(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedDecrement16 */
#ifndef _InterlockedDecrement
#define _InterlockedDecrement(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedDecrement */
#ifndef _InterlockedDecrement64
#define _InterlockedDecrement64(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedDecrement64 */
//#ifndef        _InterlockedDecrementPointer
//#define _InterlockedDecrementPointer(ptr) \
//	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(void **, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedDecrementPointer */


/* _InterlockedDecrementAcquire */
//#ifndef        _InterlockedDecrementAcquire8
//#define _InterlockedDecrementAcquire8(ptr) \
//	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedDecrementAcquire8 */
#ifndef _InterlockedDecrementAcquire16
#define _InterlockedDecrementAcquire16(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedDecrementAcquire16 */
#ifndef _InterlockedDecrementAcquire
#define _InterlockedDecrementAcquire(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedDecrementAcquire */
#ifndef _InterlockedDecrementAcquire64
#define _InterlockedDecrementAcquire64(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedDecrementAcquire64 */
//#ifndef        _InterlockedDecrementAcquirePointer
//#define _InterlockedDecrementAcquirePointer(ptr) \
//	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(void **, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedDecrementAcquirePointer */


/* _InterlockedDecrementRelease */
//#ifndef        _InterlockedDecrementRelease8
//#define _InterlockedDecrementRelease8(ptr) \
//	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedDecrementRelease8 */
#ifndef _InterlockedDecrementRelease16
#define _InterlockedDecrementRelease16(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedDecrementRelease16 */
#ifndef _InterlockedDecrementRelease
#define _InterlockedDecrementRelease(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedDecrementRelease */
#ifndef _InterlockedDecrementRelease64
#define _InterlockedDecrementRelease64(ptr) \
	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedDecrementRelease64 */
//#ifndef        _InterlockedDecrementReleasePointer
//#define _InterlockedDecrementReleasePointer(ptr) \
//	__hybrid_atomic_decfetch(__COMPILER_REQTYPE(void **, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedDecrementReleasePointer */


/* _InterlockedIncrement */
//#ifndef _InterlockedIncrement8
//#define _InterlockedIncrement8(ptr) \
//	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedIncrement8 */
#ifndef _InterlockedIncrement16
#define _InterlockedIncrement16(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedIncrement16 */
#ifndef _InterlockedIncrement
#define _InterlockedIncrement(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedIncrement */
#ifndef _InterlockedIncrement64
#define _InterlockedIncrement64(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_SEQ_CST)
#endif /* !_InterlockedIncrement64 */
//#ifndef        _InterlockedIncrementPointer
//#define _InterlockedIncrementPointer(ptr) \
//	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(void **, ptr), __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedIncrementPointer */


/* _InterlockedIncrementAcquire */
//#ifndef        _InterlockedIncrementAcquire8
//#define _InterlockedIncrementAcquire8(ptr) \
//	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedIncrementAcquire8 */
#ifndef _InterlockedIncrementAcquire16
#define _InterlockedIncrementAcquire16(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedIncrementAcquire16 */
#ifndef _InterlockedIncrementAcquire
#define _InterlockedIncrementAcquire(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedIncrementAcquire */
#ifndef _InterlockedIncrementAcquire64
#define _InterlockedIncrementAcquire64(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_ACQUIRE)
#endif /* !_InterlockedIncrementAcquire64 */
//#ifndef        _InterlockedIncrementAcquirePointer
//#define _InterlockedIncrementAcquirePointer(ptr) \
//	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(void **, ptr), __ATOMIC_ACQUIRE)
//#endif /* !_InterlockedIncrementAcquirePointer */


/* _InterlockedIncrementRelease */
//#ifndef        _InterlockedIncrementRelease8
//#define _InterlockedIncrementRelease8(ptr) \
//	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedIncrementRelease8 */
#ifndef _InterlockedIncrementRelease16
#define _InterlockedIncrementRelease16(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedIncrementRelease16 */
#ifndef _InterlockedIncrementRelease
#define _InterlockedIncrementRelease(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedIncrementRelease */
#ifndef _InterlockedIncrementRelease64
#define _InterlockedIncrementRelease64(ptr) \
	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), __ATOMIC_RELEASE)
#endif /* !_InterlockedIncrementRelease64 */
//#ifndef        _InterlockedIncrementReleasePointer
//#define _InterlockedIncrementReleasePointer(ptr) \
//	__hybrid_atomic_incfetch(__COMPILER_REQTYPE(void **, ptr), __ATOMIC_RELEASE)
//#endif /* !_InterlockedIncrementReleasePointer */


/* _InterlockedExchange */
#ifndef _InterlockedExchange8
#define _InterlockedExchange8(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange8 */
#ifndef _InterlockedExchange16
#define _InterlockedExchange16(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange16 */
#ifndef _InterlockedExchange
#define _InterlockedExchange(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange */
#ifndef _InterlockedExchange64
#define _InterlockedExchange64(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchange64 */
#ifndef _InterlockedExchangePointer
#define _InterlockedExchangePointer(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangePointer */


/* _InterlockedExchangeAcquire */
#ifndef _InterlockedExchangeAcquire8
#define _InterlockedExchangeAcquire8(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire8 */
#ifndef _InterlockedExchangeAcquire16
#define _InterlockedExchangeAcquire16(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire16 */
#ifndef _InterlockedExchangeAcquire
#define _InterlockedExchangeAcquire(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire */
#ifndef _InterlockedExchangeAcquire64
#define _InterlockedExchangeAcquire64(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquire64 */
#ifndef _InterlockedExchangeAcquirePointer
#define _InterlockedExchangeAcquirePointer(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_ACQUIRE)
#endif /* !_InterlockedExchangeAcquirePointer */


/* _InterlockedExchangeRelease */
#ifndef _InterlockedExchangeRelease8
#define _InterlockedExchangeRelease8(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease8 */
#ifndef _InterlockedExchangeRelease16
#define _InterlockedExchangeRelease16(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease16 */
#ifndef _InterlockedExchangeRelease
#define _InterlockedExchangeRelease(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease */
#ifndef _InterlockedExchangeRelease64
#define _InterlockedExchangeRelease64(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeRelease64 */
#ifndef _InterlockedExchangeReleasePointer
#define _InterlockedExchangeReleasePointer(ptr, val) \
	__hybrid_atomic_xch(__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_RELEASE)
#endif /* !_InterlockedExchangeReleasePointer */


/* _InterlockedExchangeAdd */
#ifndef _InterlockedExchangeAdd8
#define _InterlockedExchangeAdd8(ptr, val) \
	__hybrid_atomic_fetchadd(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd8 */
#ifndef _InterlockedExchangeAdd16
#define _InterlockedExchangeAdd16(ptr, val) \
	__hybrid_atomic_fetchadd(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd16 */
#ifndef _InterlockedExchangeAdd
#define _InterlockedExchangeAdd(ptr, val) \
	__hybrid_atomic_fetchadd(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd */
#ifndef _InterlockedExchangeAdd64
#define _InterlockedExchangeAdd64(ptr, val) \
	__hybrid_atomic_fetchadd(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedExchangeAdd64 */
//#ifndef _InterlockedExchangeAddPointer
//#define _InterlockedExchangeAddPointer(ptr, val) \
//	__hybrid_atomic_fetchadd(__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedExchangeAddPointer */

/* _InterlockedAdd */
#ifndef _InterlockedAdd8
#define _InterlockedAdd8(ptr, val) \
	__hybrid_atomic_addfetch(__COMPILER_REQTYPE(__INT8_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd8 */
#ifndef _InterlockedAdd16
#define _InterlockedAdd16(ptr, val) \
	__hybrid_atomic_addfetch(__COMPILER_REQTYPE(__INT16_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd16 */
#ifndef _InterlockedAdd
#define _InterlockedAdd(ptr, val) \
	__hybrid_atomic_addfetch(__COMPILER_REQTYPE(__LONG32_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd */
#ifndef _InterlockedAdd64
#define _InterlockedAdd64(ptr, val) \
	__hybrid_atomic_addfetch(__COMPILER_REQTYPE(__LONG64_TYPE__ *, ptr), val, __ATOMIC_SEQ_CST)
#endif /* !_InterlockedAdd64 */
//#ifndef _InterlockedAddPointer
//#define _InterlockedAddPointer(ptr, val) \
//	__hybrid_atomic_addfetch(__COMPILER_REQTYPE(void **, ptr), val, __ATOMIC_SEQ_CST)
//#endif /* !_InterlockedAddPointer */


#if __has_builtin(__builtin_return_address)
#define _ReturnAddress() __builtin_return_address(0)
#endif /* __has_builtin(__builtin_return_address) */
#ifndef _byteswap_ushort
#define _byteswap_ushort(x)   __hybrid_bswap16(x)
#endif /* !_byteswap_ushort */
#ifndef _byteswap_ulong
#define _byteswap_ulong(x)    __hybrid_bswap32(x)
#endif /* !_byteswap_ulong */
#ifdef __UINT64_TYPE__
#ifndef _byteswap_uint64
#define _byteswap_uint64(x)   __hybrid_bswap64(x)
#endif /* !_byteswap_uint64 */
#endif /* __UINT64_TYPE__ */

#define _lrotl(val, shift)  __hybrid_rol32(val, shift)
#define _rotl(val, shift)   __hybrid_rol32(val, shift)
#define _rotl16(val, shift) __hybrid_rol16(val, shift)
#define _rotl8(val, shift)  __hybrid_rol8(val, shift)
#define _lrotr(val, shift)  __hybrid_rol32(val, shift)
#define _rotr(val, shift)   __hybrid_ror32(val, shift)
#define _rotr16(val, shift) __hybrid_ror16(val, shift)
#define _rotr8(val, shift)  __hybrid_ror8(val, shift)
#ifdef __hybrid_rol64
#define _rotl64(val, shift) __hybrid_rol64(val, shift)
#define _rotr64(val, shift) __hybrid_ror64(val, shift)
#endif /* __hybrid_rol64 */


/* __MACHINE: void *_AddressOfReturnAddress(void) */
/* __MACHINE: void __code_seg(const char *) */
/* __MACHINE: int __cdecl _setjmp(jmp_buf) */



/************************************************************************/
/* X86                                                                  */
/************************************************************************/
#if defined(__i386__) || defined(__x86_64__)
#define __debugbreak() __int3()
#ifdef __COMPILER_HAVE_GCC_ASM
#if __has_builtin(__fastfail)
#define __fastfail(code) __x86_fastfail(code)
__FORCELOCAL __ATTR_NORETURN void (__x86_fastfail)(unsigned int __code) {
	__asm__ __volatile__("int {$}0x29"
	                     :
	                     : "c"(__code)
	                     : "memory");
	__builtin_unreachable();
}
#else /* __has_builtin(__fastfail) */
#define __fastfail(code) __fastfail(code)
__FORCELOCAL __ATTR_NORETURN void (__fastfail)(unsigned int __code) {
	__asm__ __volatile__("int {$}0x29"
	                     :
	                     : "c"(__code)
	                     : "memory");
	__builtin_unreachable();
}
#endif /* !__has_builtin(__fastfail) */
#endif /* __COMPILER_HAVE_GCC_ASM */
#define __nop() __nop()
#define _disable()            __cli()
#define _enable()             __sti()
#ifndef __readfsbyte
#define __readfsbyte(offset)   __rdfsb(offset)
#endif /* !__readfsbyte */
#ifndef __readfsword
#define __readfsword(offset)   __rdfsw(offset)
#endif /* !__readfsword */
#ifndef __readfsdword
#define __readfsdword(offset)  __rdfsl(offset)
#endif /* !__readfsdword */
#ifndef __writefsbyte
#define __writefsbyte(offset)  __wrfsb(offset)
#endif /* !__writefsbyte */
#ifndef __writefsword
#define __writefsword(offset)  __wrfsw(offset)
#endif /* !__writefsword */
#ifndef __writefsdword
#define __writefsdword(offset) __wrfsl(offset)
#endif /* !__writefsdword */
#ifndef __readgsbyte
#define __readgsbyte(offset)   __rdgsb(offset)
#endif /* !__readgsbyte */
#ifndef __readgsword
#define __readgsword(offset)   __rdgsw(offset)
#endif /* !__readgsword */
#ifndef __readgsdword
#define __readgsdword(offset)  __rdgsl(offset)
#endif /* !__readgsdword */
#ifndef __writegsbyte
#define __writegsbyte(offset)  __wrgsb(offset)
#endif /* !__writegsbyte */
#ifndef __writegsword
#define __writegsword(offset)  __wrgsw(offset)
#endif /* !__writegsword */
#ifndef __writegsdword
#define __writegsdword(offset) __wrgsl(offset)
#endif /* !__writegsdword */
#ifdef __x86_64__
#ifndef __readfsqword
#define __readfsqword(offset)  __rdfsq(offset)
#endif /* !__readfsqword */
#ifndef __writefsqword
#define __writefsqword(offset) __wrfsq(offset)
#endif /* !__writefsqword */
#ifndef __readgsqword
#define __readgsqword(offset)  __rdgsq(offset)
#endif /* !__readgsqword */
#ifndef __writegsqword
#define __writegsqword(offset) __wrgsq(offset)
#endif /* !__writegsqword */
#endif /* __x86_64__ */
#define __readcr0()     __rdcr0()
#define __readcr2()     __rdcr2()
#define __readcr3()     __rdcr3()
#define __readcr4()     __rdcr4()
#define __writecr0(val) __wrcr0(val)
#define __writecr3(val) __wrcr3(val)
#define __writecr4(val) __wrcr4(val)
#ifdef __x86_64__
#define __readcr8()     __rdcr8()
#define __writecr8(val) __wrcr8(val)
#endif /* __x86_64__ */
#define __readeflags()     __rdflags()
#define __writeeflags(val) __wrflags(val)
__FORCELOCAL __ATTR_WUNUSED __REGISTER_TYPE__ (__readdr)(unsigned int __n) {
	switch (__n) {
	case 0: return (__REGISTER_TYPE__)__rddr0();
	case 1: return (__REGISTER_TYPE__)__rddr1();
	case 2: return (__REGISTER_TYPE__)__rddr2();
	case 3: return (__REGISTER_TYPE__)__rddr3();
	case 6: return __rddr6();
	case 7: return __rddr7();
	default: __builtin_unreachable();
	}
}
__FORCELOCAL void (__writedr)(unsigned int __n, __REGISTER_TYPE__ __val) {
	switch (__n) {
	case 0: __wrdr0((void *)__val); break;
	case 1: __wrdr1((void *)__val); break;
	case 2: __wrdr2((void *)__val); break;
	case 3: __wrdr3((void *)__val); break;
	case 6: __wrdr6(__val); break;
	case 7: __wrdr7(__val); break;
	default: __builtin_unreachable();
	}
}

#if defined(__i386__) && !defined(__x86_64__)
#define __addfsbyte(off, val)  __addfsb(off, val)
#define __addfsdword(off, val) __addfsl(off, val)
#define __addfsword(off, val)  __addfsw(off, val)
#define __incfsbyte(off)       __incfsb(off)
#define __incfsdword(off)      __incfsl(off)
#define __incfsword(off)       __incfsw(off)
#ifndef __readfsqword
#define __readfsqword __readfsqword
#if !__has_builtin(__readfsqword)
__FORCELOCAL __ATTR_WUNUSED __UINT64_TYPE__ (__readfsqword)(__ULONGPTR_TYPE__ __off) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
	} __res;
	__res.__v32[0] = __rdfsl(__off + 0);
	__res.__v32[1] = __rdfsl(__off + 4);
	return __res.__v64;
}
#endif /* !__has_builtin(__readfsqword) */
#endif /* !__readfsqword */
#ifndef __writefsqword
#define __writefsqword __writefsqword
#if !__has_builtin(__writefsqword)
__FORCELOCAL void (__writefsqword)(__ULONGPTR_TYPE__ __off, __UINT64_TYPE__ __val) {
	union {
		__UINT64_TYPE__ __v64;
		__UINT32_TYPE__ __v32[2];
	} __data;
	__data.__v64 = __val;
	__wrfsl(__off + 0, __data.__v32[0]);
	__wrfsl(__off + 4, __data.__v32[1]);
}
#endif /* !__has_builtin(__writefsqword) */
#endif /* !__writefsqword */
/* __MACHINEX86: void _m_empty(void) */
/* __MACHINEX86: void _m_femms(void) */
/* __MACHINEX86: __m64 _m_from_float(float) */
/* __MACHINEX86: __m64 _m_from_int(int) */
/* __MACHINEX86: void _m_maskmovq(__m64, __m64, char *) */
/* __MACHINEX86: __m64 _m_packssdw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_packsswb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_packuswb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddsb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddusb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddusw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_paddw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pand(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pandn(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pavgb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pavgusb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pavgw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpeqb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpeqd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpeqw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpgtb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpgtd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pcmpgtw(__m64, __m64) */
/* __MACHINEX86: int _m_pextrw(__m64, int) */
/* __MACHINEX86: __m64 _m_pf2id(__m64) */
/* __MACHINEX86: __m64 _m_pf2iw(__m64) */
/* __MACHINEX86: __m64 _m_pfacc(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfadd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfcmpeq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfcmpge(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfcmpgt(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfmax(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfmin(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfmul(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfnacc(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfpnacc(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrcp(__m64) */
/* __MACHINEX86: __m64 _m_pfrcpit1(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrcpit2(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrsqit1(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfrsqrt(__m64) */
/* __MACHINEX86: __m64 _m_pfsub(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pfsubr(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pi2fd(__m64) */
/* __MACHINEX86: __m64 _m_pi2fw(__m64) */
/* __MACHINEX86: __m64 _m_pinsrw(__m64, int, int) */
/* __MACHINEX86: __m64 _m_pmaddwd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmaxsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmaxub(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pminsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pminub(__m64, __m64) */
/* __MACHINEX86: int _m_pmovmskb(__m64) */
/* __MACHINEX86: __m64 _m_pmulhrw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmulhuw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmulhw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pmullw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_por(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psadbw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pshufw(__m64, int) */
/* __MACHINEX86: __m64 _m_pslld(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pslldi(__m64, int) */
/* __MACHINEX86: __m64 _m_psllq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psllqi(__m64, int) */
/* __MACHINEX86: __m64 _m_psllw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psllwi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrad(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psradi(__m64, int) */
/* __MACHINEX86: __m64 _m_psraw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrawi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrld(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrldi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrlq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrlqi(__m64, int) */
/* __MACHINEX86: __m64 _m_psrlw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psrlwi(__m64, int) */
/* __MACHINEX86: __m64 _m_psubb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubsb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubsw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubusb(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubusw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_psubw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pswapd(__m64) */
/* __MACHINEX86: __m64 _m_punpckhbw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpckhdq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpckhwd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpcklbw(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpckldq(__m64, __m64) */
/* __MACHINEX86: __m64 _m_punpcklwd(__m64, __m64) */
/* __MACHINEX86: __m64 _m_pxor(__m64, __m64) */
/* __MACHINEX86: float _m_to_float(__m64) */
/* __MACHINEX86: int _m_to_int(__m64) */
/* __MACHINEX86: __m64 _mm_add_si64(__m64, __m64) */
/* __MACHINEX86: __m128 _mm_cvt_pi2ps(__m128, __m64) */
/* __MACHINEX86: __m64 _mm_cvt_ps2pi(__m128) */
/* __MACHINEX86: __m64 _mm_cvtpd_pi32(__m128d) */
/* __MACHINEX86: __m128d _mm_cvtpi32_pd(__m64) */
/* __MACHINEX86: __m64 _mm_cvtt_ps2pi(__m128) */
/* __MACHINEX86: __m64 _mm_cvttpd_pi32(__m128d) */
/* __MACHINEX86: __m64 _mm_movepi64_pi64(__m128i) */
/* __MACHINEX86: __m128i _mm_movpi64_epi64(__m64) */
/* __MACHINEX86: __m64 _mm_mul_su32(__m64, __m64) */
/* __MACHINEX86: __m128i _mm_set1_epi64(__m64) */
/* __MACHINEX86: __m64 _mm_set1_pi16(short) */
/* __MACHINEX86: __m64 _mm_set1_pi32(int) */
/* __MACHINEX86: __m64 _mm_set1_pi8(char) */
/* __MACHINEX86: __m128i _mm_set_epi64(__m64, __m64) */
/* __MACHINEX86: __m64 _mm_set_pi16(short, short, short, short) */
/* __MACHINEX86: __m64 _mm_set_pi32(int, int) */
/* __MACHINEX86: __m64 _mm_set_pi8(char, char, char, char, char, char, char, char) */
/* __MACHINEX86: __m128i _mm_setr_epi64(__m64, __m64) */
/* __MACHINEX86: __m64 _mm_setr_pi16(short, short, short, short) */
/* __MACHINEX86: __m64 _mm_setr_pi32(int, int) */
/* __MACHINEX86: __m64 _mm_setr_pi8(char, char, char, char, char, char, char, char) */
/* __MACHINEX86: __m64 _mm_setzero_si64(void) */
/* __MACHINEX86: void _mm_stream_pi(__m64 *, __m64) */
/* __MACHINEX86: __m64 _mm_sub_si64(__m64, __m64) */
#endif /* __i386__ && !__x86_64__ */


/* __MACHINEX64 */
#ifdef __x86_64__
#define __addgsbyte(off, val)    __addgsb(off, val)
#define __addgsdword(off, val)   __addgsl(off, val)
#define __addgsword(off, val)    __addgsw(off, val)
#define __addgsqword(off, val)   __addgsq(off, val)
#define __incgsbyte(off)         __incgsb(off)
#define __incgsdword(off)        __incgsl(off)
#define __incgsword(off)         __incgsw(off)
#define __incgsqword(off)        __incgsq(off)
/* __MACHINEX64: short _InterlockedAnd16_np(short volatile *val, short mask) */
/* __MACHINEX64: __int64 _InterlockedAnd64_np(__int64 volatile *val, __int64 mask) */
/* __MACHINEX64: char _InterlockedAnd8_np(char volatile *val, char mask) */
/* __MACHINEX64: long _InterlockedAnd_np(long volatile *val, long mask) */
/* __MACHINEX64: unsigned char _InterlockedCompareExchange128(__int64 volatile *ptr, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 *_ComparandResult) */
/* __MACHINEX64: unsigned char _InterlockedCompareExchange128_np(__int64 volatile *ptr, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 *_ComparandResult) */
/* __MACHINEX64: __int64 _InterlockedCompareExchange64_np(__int64 volatile *ptr, __int64 newval, __int64 oldval) */
/* __MACHINEX64: void *_InterlockedCompareExchangePointer_np(void *volatile *ptr, void *newval, void *oldval) */
/* __MACHINEX64: long _InterlockedCompareExchange_np(long volatile *ptr, long newval, long oldval) */
/* __MACHINEX64: short _InterlockedOr16_np(short volatile *val, short mask) */
/* __MACHINEX64: __int64 _InterlockedOr64_np(__int64 volatile *val, __int64 mask) */
/* __MACHINEX64: char _InterlockedOr8_np(char volatile *val, char mask) */
/* __MACHINEX64: long _InterlockedOr_np(long volatile *val, long mask) */
/* __MACHINEX64: short _InterlockedXor16_np(short volatile *val, short mask) */
/* __MACHINEX64: __int64 _InterlockedXor64_np(__int64 volatile *val, __int64 mask) */
/* __MACHINEX64: char _InterlockedXor8_np(char volatile *val, char mask) */
/* __MACHINEX64: long _InterlockedXor_np(long volatile *val, long mask) */
/* __MACHINEX64: void __faststorefence(void) */
#define __lzcnt64(val)                  __lzcntq(val)
#define __movsq(dst, src, NumQuadwords) __movsq(dst, src, NumQuadwords)
/* __MACHINEX64: __int64 __mulh(__int64, __int64) */
#define __popcnt64(val) __popcntq(val)
/* __MACHINEX64: unsigned __int64 __shiftleft128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _shift) */
/* __MACHINEX64: unsigned __int64 __shiftright128(unsigned __int64 _LowPart, unsigned __int64 _HighPart, unsigned char _shift) */
#define __stosq(dst, Quadword, NumQuadwords) __stosq(dst, Quadword, NumQuadwords)
/* __MACHINEX64: unsigned __int64 __umulh(unsigned __int64, unsigned __int64) */
/* __MACHINEX64: unsigned char __vmx_on(unsigned __int64 *) */
/* __MACHINEX64: unsigned char __vmx_vmclear(unsigned __int64 *) */
/* __MACHINEX64: unsigned char __vmx_vmlaunch(void) */
/* __MACHINEX64: unsigned char __vmx_vmptrld(unsigned __int64 *) */
/* __MACHINEX64: unsigned char __vmx_vmread(size_t, size_t *) */
/* __MACHINEX64: unsigned char __vmx_vmresume(void) */
/* __MACHINEX64: unsigned char __vmx_vmwrite(size_t, size_t) */
/* __MACHINEX64: unsigned char _bittest64(__int64 const *, __int64) */
/* __MACHINEX64: unsigned char _bittestandcomplement64(__int64 *, __int64) */
/* __MACHINEX64: unsigned char _bittestandreset64(__int64 *, __int64) */
/* __MACHINEX64: unsigned char _bittestandset64(__int64 *, __int64) */
/* __MACHINEX64: unsigned char _interlockedbittestandreset64(__int64 volatile *, __int64) */
/* __MACHINEX64: unsigned char _interlockedbittestandset64(__int64 volatile *, __int64) */
/* __MACHINEX64: unsigned __int64 _mm_crc32_u64(unsigned __int64, unsigned __int64) */
/* __MACHINEX64: __int64 _mm_cvtsd_si64(__m128d) */
/* __MACHINEX64: __int64 _mm_cvtsd_si64x(__m128d) */
/* __MACHINEX64: __int64 _mm_cvtsi128_si64(__m128i) */
/* __MACHINEX64: __int64 _mm_cvtsi128_si64x(__m128i) */
/* __MACHINEX64: __m128d _mm_cvtsi64_sd(__m128d, __int64) */
/* __MACHINEX64: __m128i _mm_cvtsi64_si128(__int64) */
/* __MACHINEX64: __m128 _mm_cvtsi64_ss(__m128, __int64) */
/* __MACHINEX64: __m128d _mm_cvtsi64x_sd(__m128d, __int64) */
/* __MACHINEX64: __m128i _mm_cvtsi64x_si128(__int64) */
/* __MACHINEX64: __m128 _mm_cvtsi64x_ss(__m128, __int64) */
/* __MACHINEX64: __int64 _mm_cvtss_si64(__m128) */
/* __MACHINEX64: __int64 _mm_cvtss_si64x(__m128) */
/* __MACHINEX64: __int64 _mm_cvttsd_si64(__m128d) */
/* __MACHINEX64: __int64 _mm_cvttsd_si64x(__m128d) */
/* __MACHINEX64: __int64 _mm_cvttss_si64(__m128) */
/* __MACHINEX64: __int64 _mm_cvttss_si64x(__m128) */
/* __MACHINEX64: __int64 _mm_extract_epi64(__m128i, int) */
/* __MACHINEX64: __m128i _mm_insert_epi64(__m128i, __int64, int) */
/* __MACHINEX64: __int64 _mm_popcnt_u64(unsigned __int64) */
/* __MACHINEX64: __m128i _mm_set1_epi64x(__int64) */
/* __MACHINEX64: __m128i _mm_set_epi64x(__int64, __int64) */
/* __MACHINEX64: void _mm_stream_si64x(__int64 *, __int64) */
/* __MACHINEX64: __int64 _mul128(__int64 _Multiplier, __int64 _Multiplicand, __int64 *_HighProduct) */
/* __MACHINEX64: unsigned __int64 _umul128(unsigned __int64 _Multiplier, unsigned __int64 _Multiplicand, unsigned __int64 *_HighProduct) */
/* __MACHINEX64: unsigned char __cdecl _addcarry_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *) */
/* __MACHINEX64: unsigned char __cdecl _subborrow_u64(unsigned char, unsigned __int64, unsigned __int64, unsigned __int64 *) */
/* __MACHINEX64: int __cdecl _setjmpex(jmp_buf) */
#endif /* __x86_64__ */




/* __MACHINEX86_X64 */
/* __MACHINEX86_X64: void __cpuid(int[4], int) */
/* __MACHINEX86_X64: void __cpuidex(int[4], int, int) */
/* __MACHINEX86_X64: __int64 __emul(int, int) */
/* __MACHINEX86_X64: unsigned __int64 __emulu(unsigned int, unsigned int) */
/* __MACHINEX86_X64: unsigned int __getcallerseflags(void) */
#define __halt()                               __hlt()
#define __inbyte(port)                         __inb(port)
#define __inbytestring(port, dst, num_bytes)   __insb(port, dst, num_bytes)
#define __indword(port)                        __inl(port)
#define __indwordstring(port, dst, num_dwords) __insl(port, dst, num_dwords)
#define __int2c()                              __int(0x2c)
#define __invlpg()                             __invlpg()
#define __inword(port)                         __inw(port)
#define __inwordstring(port, dst, num_words)   __insw(port, dst, num_words)
#define __lidt(data)                           __lidt_p(data)
#define __ll_lshift(x, shift)                  ((__UINT64_TYPE__)(x) << (__SHIFT_TYPE__)(shift))
#define __ll_rshift(x, shift)                  ((__INT64_TYPE__)(x) >> (__SHIFT_TYPE__)(shift))
#define __lzcnt(x)                             __lzcntl(x)
#define __lzcnt16(x)                           __lzcntw(x)
#define __movsb(dst, src, num_bytes)           __movsb(dst, src, num_bytes)
#define __movsd(dst, src, num_dwords)          __movsl(dst, src, num_dwords)
#define __movsw(dst, src, num_words)           __movsw(dst, src, num_words)
/* __MACHINEX86_X64: void __nvreg_restore_fence(void) */
/* __MACHINEX86_X64: void __nvreg_save_fence(void) */
#define __outbyte(port, byte)                    __outb(port, byte)
#define __outbytestring(port, data, num_bytes)   __outsb(port, data, num_bytes)
#define __outdword(port, dwords)                 __outl(port, dwords)
#define __outdwordstring(port, data, num_dwords) __outsl(port, data, num_dwords)
#define __outword(port, word)                    __outw(port, word)
#define __outwordstring(port, data, num_words)   __outsw(port, data, num_words)
#define __popcnt(val)                            __popcntl(val)
#define __popcnt16(val)                          __popcntw(val)
#define __rdtsc()                                __rdtsc()
#define __rdtscp(pid)                            __rdtscp(pid)
#define __readmsr(Id)                            __rdmsr(Id)
#define __readpmc(Id)                            __rdpmc(Id)
/* __MACHINEX86_X64: unsigned long __segmentlimit(unsigned long) */
#define __sidt(p)                       __sidt(p)
#define __stosb(dst, byte, num_bytes)   __stosb(dst, byte, num_bytes)
#define __stosd(dst, dword, num_dwords) __stosl(dst, dword, num_dwords)
#define __stosw(dst, word, num_words)   __stosw(dst, word, num_words)
/* __MACHINEX86_X64: void __svm_clgi(void) */
/* __MACHINEX86_X64: void __svm_invlpga(void *, int) */
/* __MACHINEX86_X64: void __svm_skinit(int) */
/* __MACHINEX86_X64: void __svm_stgi(void) */
/* __MACHINEX86_X64: void __svm_vmload(size_t) */
/* __MACHINEX86_X64: void __svm_vmrun(size_t) */
/* __MACHINEX86_X64: void __svm_vmsave(size_t) */
#define __ud2()                  __ud2()
#define __ull_rshift(val, shift) ((__UINT64_TYPE__)(val) >> (shift))
/* __MACHINEX86_X64: void __vmx_off(void) */
/* __MACHINEX86_X64: void __vmx_vmptrst(unsigned __int64 *) */
#define __wbinvd()          __wbinvd()
#define __writemsr(id, val) __wrmsr(id, val)
/* __MACHINEX86_X64: void _m_prefetch(void *) */
/* __MACHINEX86_X64: void _m_prefetchw(const volatile void *) */
/* __MACHINEX86_X64: __m128i _mm_abs_epi16(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_abs_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_abs_epi8(__m128i) */
/* __MACHINEX86_X64: __m64 _mm_abs_pi16(__m64) */
/* __MACHINEX86_X64: __m64 _mm_abs_pi32(__m64) */
/* __MACHINEX86_X64: __m64 _mm_abs_pi8(__m64) */
/* __MACHINEX86_X64: __m128i _mm_add_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_add_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_add_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_add_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_add_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_add_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_add_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_add_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_adds_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_adds_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_adds_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_adds_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_addsub_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_addsub_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_alignr_epi8(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m64 _mm_alignr_pi8(__m64, __m64, int) */
/* __MACHINEX86_X64: __m128d _mm_and_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_and_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_and_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_andnot_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_andnot_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_andnot_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_avg_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_avg_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_blend_epi16(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128d _mm_blend_pd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_blend_ps(__m128, __m128, int) */
/* __MACHINEX86_X64: __m128i _mm_blendv_epi8(__m128i, __m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_blendv_pd(__m128d, __m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_blendv_ps(__m128, __m128, __m128) */
/* __MACHINEX86_X64: void _mm_clflush(void const *) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpeq_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_cmpeq_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpeq_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpeq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpeq_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_cmpestra(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestrc(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestri(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_cmpestrm(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestro(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestrs(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: int _mm_cmpestrz(__m128i, int, __m128i, int, int) */
/* __MACHINEX86_X64: __m128d _mm_cmpge_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpge_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpge_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpge_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmpgt_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_cmpgt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpgt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpgt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpgt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_cmpistra(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistrc(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistri(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_cmpistrm(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistro(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistrs(__m128i, __m128i, int) */
/* __MACHINEX86_X64: int _mm_cmpistrz(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128d _mm_cmple_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmple_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmple_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmple_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_cmplt_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmplt_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_cmplt_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_cmplt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmplt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmplt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmplt_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpneq_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpneq_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpneq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpneq_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnge_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnge_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnge_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnge_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpngt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpngt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpngt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpngt_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnle_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnle_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnle_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnle_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnlt_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnlt_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpnlt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpnlt_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpord_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpord_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpord_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpord_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpunord_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpunord_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_cmpunord_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_cmpunord_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comieq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comieq_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comige_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comige_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comigt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comigt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comile_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comile_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comilt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comilt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_comineq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_comineq_ss(__m128, __m128) */
/* __MACHINEX86_X64: unsigned int _mm_crc32_u16(unsigned int, unsigned short) */
/* __MACHINEX86_X64: unsigned int _mm_crc32_u32(unsigned int, unsigned int) */
/* __MACHINEX86_X64: unsigned int _mm_crc32_u8(unsigned int, unsigned char) */
/* __MACHINEX86_X64: __m128 _mm_cvt_si2ss(__m128, int) */
/* __MACHINEX86_X64: int _mm_cvt_ss2si(__m128) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi16_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi16_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi32_epi64(__m128i) */
/* __MACHINEX86_X64: __m128d _mm_cvtepi32_pd(__m128i) */
/* __MACHINEX86_X64: __m128 _mm_cvtepi32_ps(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi8_epi16(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi8_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepi8_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu16_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu16_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu32_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu8_epi16(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu8_epi32(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtepu8_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_cvtpd_epi32(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_cvtpd_ps(__m128d) */
/* __MACHINEX86_X64: __m128i _mm_cvtps_epi32(__m128) */
/* __MACHINEX86_X64: __m128d _mm_cvtps_pd(__m128) */
/* __MACHINEX86_X64: int _mm_cvtsd_si32(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_cvtsd_ss(__m128, __m128d) */
/* __MACHINEX86_X64: int _mm_cvtsi128_si32(__m128i) */
/* __MACHINEX86_X64: __m128d _mm_cvtsi32_sd(__m128d, int) */
/* __MACHINEX86_X64: __m128i _mm_cvtsi32_si128(int) */
/* __MACHINEX86_X64: __m128d _mm_cvtss_sd(__m128d, __m128) */
/* __MACHINEX86_X64: int _mm_cvtt_ss2si(__m128) */
/* __MACHINEX86_X64: __m128i _mm_cvttpd_epi32(__m128d) */
/* __MACHINEX86_X64: __m128i _mm_cvttps_epi32(__m128) */
/* __MACHINEX86_X64: int _mm_cvttsd_si32(__m128d) */
/* __MACHINEX86_X64: __m128d _mm_div_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_div_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_div_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_div_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_dp_pd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_dp_ps(__m128, __m128, int) */
/* __MACHINEX86_X64: int _mm_extract_epi16(__m128i, int) */
/* __MACHINEX86_X64: int _mm_extract_epi32(__m128i, int) */
/* __MACHINEX86_X64: int _mm_extract_epi8(__m128i, int) */
/* __MACHINEX86_X64: int _mm_extract_ps(__m128, int) */
/* __MACHINEX86_X64: __m128i _mm_extract_si64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_extracti_si64(__m128i, int, int) */
/* __MACHINEX86_X64: unsigned int _mm_getcsr(void) */
/* __MACHINEX86_X64: __m128i _mm_hadd_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_hadd_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_hadd_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m64 _mm_hadd_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_hadd_pi32(__m64, __m64) */
/* __MACHINEX86_X64: __m128 _mm_hadd_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_hadds_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_hadds_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_hsub_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_hsub_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_hsub_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m64 _mm_hsub_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_hsub_pi32(__m64, __m64) */
/* __MACHINEX86_X64: __m128 _mm_hsub_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_hsubs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_hsubs_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_insert_epi16(__m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_insert_epi32(__m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_insert_epi8(__m128i, int, int) */
/* __MACHINEX86_X64: __m128 _mm_insert_ps(__m128, __m128, int) */
/* __MACHINEX86_X64: __m128i _mm_insert_si64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_inserti_si64(__m128i, __m128i, int, int) */
/* __MACHINEX86_X64: __m128i _mm_lddqu_si128(__m128i const *) */
/* __MACHINEX86_X64: void _mm_lfence(void) */
/* __MACHINEX86_X64: __m128d _mm_load1_pd(double const *) */
/* __MACHINEX86_X64: __m128d _mm_load_pd(double const *) */
/* __MACHINEX86_X64: __m128 _mm_load_ps(float const *) */
/* __MACHINEX86_X64: __m128 _mm_load_ps1(float const *) */
/* __MACHINEX86_X64: __m128d _mm_load_sd(double const *) */
/* __MACHINEX86_X64: __m128i _mm_load_si128(__m128i const *) */
/* __MACHINEX86_X64: __m128 _mm_load_ss(float const *) */
/* __MACHINEX86_X64: __m128d _mm_loaddup_pd(double const *) */
/* __MACHINEX86_X64: __m128d _mm_loadh_pd(__m128d, double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadh_pi(__m128, __m64 const *) */
/* __MACHINEX86_X64: __m128i _mm_loadl_epi64(__m128i const *) */
/* __MACHINEX86_X64: __m128d _mm_loadl_pd(__m128d, double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadl_pi(__m128, __m64 const *) */
/* __MACHINEX86_X64: __m128d _mm_loadr_pd(double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadr_ps(float const *) */
/* __MACHINEX86_X64: __m128d _mm_loadu_pd(double const *) */
/* __MACHINEX86_X64: __m128 _mm_loadu_ps(float const *) */
/* __MACHINEX86_X64: __m128i _mm_loadu_si128(__m128i const *) */
/* __MACHINEX86_X64: __m128i _mm_madd_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_maddubs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_maddubs_pi16(__m64, __m64) */
/* __MACHINEX86_X64: void _mm_maskmoveu_si128(__m128i, __m128i, char *) */
/* __MACHINEX86_X64: __m128i _mm_max_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epu32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_max_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_max_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_max_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_max_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_max_ss(__m128, __m128) */
/* __MACHINEX86_X64: void _mm_mfence(void) */
/* __MACHINEX86_X64: __m128i _mm_min_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epu32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_min_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_min_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_min_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_min_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_min_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_minpos_epu16(__m128i) */
/* __MACHINEX86_X64: void _mm_monitor(void const *, unsigned int, unsigned int) */
/* __MACHINEX86_X64: __m128i _mm_move_epi64(__m128i) */
/* __MACHINEX86_X64: __m128d _mm_move_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_move_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_movedup_pd(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_movehdup_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_movehl_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128 _mm_moveldup_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_movelh_ps(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_movemask_epi8(__m128i) */
/* __MACHINEX86_X64: int _mm_movemask_pd(__m128d) */
/* __MACHINEX86_X64: int _mm_movemask_ps(__m128) */
/* __MACHINEX86_X64: __m128i _mm_mpsadbw_epu8(__m128i, __m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_mul_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mul_epu32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_mul_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_mul_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_mul_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_mul_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_mulhi_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mulhi_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mulhrs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_mulhrs_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_mullo_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_mullo_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: void _mm_mwait(unsigned int, unsigned int) */
/* __MACHINEX86_X64: __m128d _mm_or_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_or_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_or_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packs_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packus_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_packus_epi32(__m128i, __m128i) */
#ifndef _mm_pause
#define _mm_pause() __pause()
#endif /* !_mm_pause */
/* __MACHINEX86_X64: int _mm_popcnt_u32(unsigned int) */
/* __MACHINEX86_X64: void _mm_prefetch(char const *, int) */
/* __MACHINEX86_X64: __m128 _mm_rcp_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_rcp_ss(__m128) */
/* __MACHINEX86_X64: __m128d _mm_round_pd(__m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_round_ps(__m128, int) */
/* __MACHINEX86_X64: __m128d _mm_round_sd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m128 _mm_round_ss(__m128, __m128, int) */
/* __MACHINEX86_X64: __m128 _mm_rsqrt_ps(__m128) */
/* __MACHINEX86_X64: __m128 _mm_rsqrt_ss(__m128) */
/* __MACHINEX86_X64: __m128i _mm_sad_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_set1_epi16(short) */
/* __MACHINEX86_X64: __m128i _mm_set1_epi32(int) */
/* __MACHINEX86_X64: __m128i _mm_set1_epi8(char) */
/* __MACHINEX86_X64: __m128d _mm_set1_pd(double) */
/* __MACHINEX86_X64: __m128i _mm_set_epi16(short, short, short, short, short, short, short, short) */
/* __MACHINEX86_X64: __m128i _mm_set_epi32(int, int, int, int) */
/* __MACHINEX86_X64: __m128i _mm_set_epi8(char, char, char, char, char, char, char, char, char, char, char, char, char, char, char, char) */
/* __MACHINEX86_X64: __m128d _mm_set_pd(double, double) */
/* __MACHINEX86_X64: __m128 _mm_set_ps(float, float, float, float) */
/* __MACHINEX86_X64: __m128 _mm_set_ps1(float) */
/* __MACHINEX86_X64: __m128d _mm_set_sd(double) */
/* __MACHINEX86_X64: __m128 _mm_set_ss(float) */
/* __MACHINEX86_X64: void _mm_setcsr(unsigned int) */
/* __MACHINEX86_X64: __m128i _mm_setl_epi64(__m128i) */
/* __MACHINEX86_X64: __m128i _mm_setr_epi16(short, short, short, short, short, short, short, short) */
/* __MACHINEX86_X64: __m128i _mm_setr_epi32(int, int, int, int) */
/* __MACHINEX86_X64: __m128i _mm_setr_epi8(char, char, char, char, char, char, char, char, char, char, char, char, char, char, char, char) */
/* __MACHINEX86_X64: __m128d _mm_setr_pd(double, double) */
/* __MACHINEX86_X64: __m128 _mm_setr_ps(float, float, float, float) */
/* __MACHINEX86_X64: __m128d _mm_setzero_pd(void) */
/* __MACHINEX86_X64: __m128 _mm_setzero_ps(void) */
/* __MACHINEX86_X64: __m128i _mm_setzero_si128(void) */
/* __MACHINEX86_X64: void _mm_sfence(void) */
/* __MACHINEX86_X64: __m128i _mm_shuffle_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_shuffle_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_shuffle_pd(__m128d, __m128d, int) */
/* __MACHINEX86_X64: __m64 _mm_shuffle_pi8(__m64, __m64) */
/* __MACHINEX86_X64: __m128 _mm_shuffle_ps(__m128, __m128, unsigned int) */
/* __MACHINEX86_X64: __m128i _mm_shufflehi_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_shufflelo_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_sign_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sign_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sign_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m64 _mm_sign_pi16(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_sign_pi32(__m64, __m64) */
/* __MACHINEX86_X64: __m64 _mm_sign_pi8(__m64, __m64) */
/* __MACHINEX86_X64: __m128i _mm_sll_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sll_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sll_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_slli_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_slli_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_slli_epi64(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_slli_si128(__m128i, int) */
/* __MACHINEX86_X64: __m128d _mm_sqrt_pd(__m128d) */
/* __MACHINEX86_X64: __m128 _mm_sqrt_ps(__m128) */
/* __MACHINEX86_X64: __m128d _mm_sqrt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_sqrt_ss(__m128) */
/* __MACHINEX86_X64: __m128i _mm_sra_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sra_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srai_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srai_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srl_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srl_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srl_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_srli_epi16(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srli_epi32(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srli_epi64(__m128i, int) */
/* __MACHINEX86_X64: __m128i _mm_srli_si128(__m128i, int) */
/* __MACHINEX86_X64: void _mm_store1_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_store_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_store_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_store_ps1(float *, __m128) */
/* __MACHINEX86_X64: void _mm_store_sd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_store_si128(__m128i *, __m128i) */
/* __MACHINEX86_X64: void _mm_store_ss(float *, __m128) */
/* __MACHINEX86_X64: void _mm_storeh_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storeh_pi(__m64 *, __m128) */
/* __MACHINEX86_X64: void _mm_storel_epi64(__m128i *, __m128i) */
/* __MACHINEX86_X64: void _mm_storel_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storel_pi(__m64 *, __m128) */
/* __MACHINEX86_X64: void _mm_storer_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storer_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_storeu_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_storeu_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_storeu_si128(__m128i *, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_stream_load_si128(__m128i *) */
/* __MACHINEX86_X64: void _mm_stream_pd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_stream_ps(float *, __m128) */
/* __MACHINEX86_X64: void _mm_stream_sd(double *, __m128d) */
/* __MACHINEX86_X64: void _mm_stream_si128(__m128i *, __m128i) */
/* __MACHINEX86_X64: void _mm_stream_si32(int *, int) */
/* __MACHINEX86_X64: void _mm_stream_ss(float *, __m128) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_sub_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_sub_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_sub_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_sub_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_sub_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_subs_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_subs_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_subs_epu16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_subs_epu8(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_testc_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_testnzc_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_testz_si128(__m128i, __m128i) */
/* __MACHINEX86_X64: int _mm_ucomieq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomieq_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomige_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomige_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomigt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomigt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomile_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomile_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomilt_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomilt_ss(__m128, __m128) */
/* __MACHINEX86_X64: int _mm_ucomineq_sd(__m128d, __m128d) */
/* __MACHINEX86_X64: int _mm_ucomineq_ss(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpackhi_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_unpackhi_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_unpackhi_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi16(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi32(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi64(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128i _mm_unpacklo_epi8(__m128i, __m128i) */
/* __MACHINEX86_X64: __m128d _mm_unpacklo_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_unpacklo_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128d _mm_xor_pd(__m128d, __m128d) */
/* __MACHINEX86_X64: __m128 _mm_xor_ps(__m128, __m128) */
/* __MACHINEX86_X64: __m128i _mm_xor_si128(__m128i, __m128i) */
#define _rsm()      __rsm()
#define _lgdt(data) __lgdt_p(data)
#define _sgdt(p)    __sgdt(p)
#define _clac()     __clac()
#define _stac()     __stac()
/* __MACHINEX86_X64: unsigned char __cdecl _addcarry_u8(unsigned char, unsigned char, unsigned char, unsigned char *) */
/* __MACHINEX86_X64: unsigned char __cdecl _subborrow_u8(unsigned char, unsigned char, unsigned char, unsigned char *) */
/* __MACHINEX86_X64: unsigned char __cdecl _addcarry_u16(unsigned char, unsigned short, unsigned short, unsigned short *) */
/* __MACHINEX86_X64: unsigned char __cdecl _subborrow_u16(unsigned char, unsigned short, unsigned short, unsigned short *) */
/* __MACHINEX86_X64: unsigned char __cdecl _addcarry_u32(unsigned char, unsigned int, unsigned int, unsigned int *) */
/* __MACHINEX86_X64: unsigned char __cdecl _subborrow_u32(unsigned char, unsigned int, unsigned int, unsigned int *) */
#elif defined(__arm__)
#define __debugbreak() __bkpt(0)
#define _mm_pause()    __yield()
#endif /* ... */
/************************************************************************/




#ifdef __USE_DOS
#include <crtdefs.h>
#include <setjmp.h>
#include <stddef.h>
#endif /* __USE_DOS */

//TODO:#if !defined (_M_CEE_PURE)
//TODO:
//TODO:#if defined (_M_IX86) || defined (_M_X64)
//TODO:#include <immintrin.h>
//TODO:#include <ammintrin.h>
//TODO:#endif  /* defined (_M_IX86) || defined (_M_X64) */
//TODO:
//TODO:#if defined (_M_IX86)
//TODO:#include <mm3dnow.h>
//TODO:#endif  /* defined (_M_IX86) */
//TODO:
//TODO:#if defined (_M_ARM)
//TODO:#include <armintr.h>
//TODO:#endif  /* defined (_M_ARM) */
//TODO:
//TODO:#endif  /* !defined (_M_CEE_PURE) */

__DECL_END
#endif /* __CC__ */

#endif /* !_INTRIN_H */
