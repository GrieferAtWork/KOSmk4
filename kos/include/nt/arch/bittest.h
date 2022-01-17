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
#ifndef GUARD_NT_ARCH_BITTEST_H
#define GUARD_NT_ARCH_BITTEST_H 1

#include <__stdinc.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef _MSC_VER
#ifndef _BitScanForward
#define _BitScanForward _BitScanForward
__BYTE_TYPE__ _BitScanForward(__ULONG32_TYPE__ *__index, __ULONG32_TYPE__ __mask);
#pragma intrinsic(_BitScanForward)
#endif /* !_BitScanForward */
#ifndef _BitScanForward64
#define _BitScanForward64 _BitScanForward64
__BYTE_TYPE__ _BitScanForward64(__ULONG32_TYPE__ *__index, __ULONG64_TYPE__ __mask);
#pragma intrinsic(_BitScanForward64)
#endif /* !_BitScanForward64 */
#ifndef _BitScanReverse
#define _BitScanReverse _BitScanReverse
__BYTE_TYPE__ _BitScanReverse(__ULONG32_TYPE__ *__index, __ULONG32_TYPE__ __mask);
#pragma intrinsic(_BitScanReverse)
#endif /* !_BitScanReverse */
#ifndef _BitScanReverse64
#define _BitScanReverse64 _BitScanReverse64
__BYTE_TYPE__ _BitScanReverse64(__ULONG32_TYPE__ *__index, __ULONG64_TYPE__ __mask);
#pragma intrinsic(_BitScanReverse64)
#endif /* !_BitScanReverse64 */

#ifndef _bittest
#define _bittest _bittest
__BYTE_TYPE__ _bittest(__LONG32_TYPE__ const *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittest)
#endif /* !_bittest */
#ifndef _bittest64
#define _bittest64 _bittest64
__BYTE_TYPE__ _bittest64(__LONG64_TYPE__ const *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittest64)
#endif /* !_bittest64 */
#ifndef _bittestandset
#define _bittestandset _bittestandset
__BYTE_TYPE__ _bittestandset(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittestandset)
#endif /* !_bittestandset */
#ifndef _bittestandset64
#define _bittestandset64 _bittestandset64
__BYTE_TYPE__ _bittestandset64(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittestandset64)
#endif /* !_bittestandset64 */
#ifndef _bittestandreset
#define _bittestandreset _bittestandreset
__BYTE_TYPE__ _bittestandreset(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittestandreset)
#endif /* !_bittestandreset */
#ifndef _bittestandreset64
#define _bittestandreset64 _bittestandreset64
__BYTE_TYPE__ _bittestandreset64(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittestandreset64)
#endif /* !_bittestandreset64 */
#ifndef _bittestandcomplement
#define _bittestandcomplement _bittestandcomplement
__BYTE_TYPE__ _bittestandcomplement(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_bittestandcomplement)
#endif /* !_bittestandcomplement */
#ifndef _bittestandcomplement64
#define _bittestandcomplement64 _bittestandcomplement64
__BYTE_TYPE__ _bittestandcomplement64(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_bittestandcomplement64)
#endif /* !_bittestandcomplement64 */
#ifndef _interlockedbittestandset
#define _interlockedbittestandset _interlockedbittestandset
__BYTE_TYPE__ _interlockedbittestandset(__LONG32_TYPE__ volatile *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandset)
#endif /* !_interlockedbittestandset */
#ifndef _interlockedbittestandreset
#define _interlockedbittestandreset _interlockedbittestandreset
__BYTE_TYPE__ _interlockedbittestandreset(__LONG32_TYPE__ volatile *__base, __LONG32_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandset64)
#endif /* !_interlockedbittestandreset */
#ifndef _interlockedbittestandset64
#define _interlockedbittestandset64 _interlockedbittestandset64
__BYTE_TYPE__ _interlockedbittestandset64(__LONG64_TYPE__ volatile *__base, __LONG64_TYPE__ __offset);
#pragma intrinsic(_interlockedbittestandreset)
#endif /* !_interlockedbittestandset64 */
#ifndef _interlockedbittestandreset64
#define _interlockedbittestandreset64 _interlockedbittestandreset64
__BYTE_TYPE__ _interlockedbittestandreset64(__LONG64_TYPE__ volatile *__base, __LONG64_TYPE__ __offset);
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
__LOCAL __BYTE_TYPE__ (_bittestandcomplement)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { return !(((*__base ^= (__LONG32_TYPE__)1 << __offset) >> __offset) & 1); }
#endif /* !_bittestandcomplement */
#ifndef _bittestandcomplement64
#define _bittestandcomplement64 _bittestandcomplement64
__LOCAL __BYTE_TYPE__ (_bittestandcomplement64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { return !(((*__base ^= (__LONG64_TYPE__)1 << __offset) >> __offset) & 1); }
#endif /* !_bittestandcomplement64 */
#ifndef _bittestandset
#define _bittestandset _bittestandset
__LOCAL __BYTE_TYPE__ (_bittestandset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base |= __mask; return __result; }
#endif /* !_bittestandset */
#ifndef _bittestandset64
#define _bittestandset64 _bittestandset64
__LOCAL __BYTE_TYPE__ (_bittestandset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base |= __mask; return __result; }
#endif /* !_bittestandset64 */
#ifndef _bittestandreset
#define _bittestandreset _bittestandreset
__LOCAL __BYTE_TYPE__ (_bittestandreset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base &= ~__mask; return __result; }
#endif /* !_bittestandreset */
#ifndef _bittestandreset64
#define _bittestandreset64 _bittestandreset64
__LOCAL __BYTE_TYPE__ (_bittestandreset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; __BYTE_TYPE__ __result = (*__base & __mask) != 0; *__base &= ~__mask; return __result; }
#endif /* !_bittestandreset64 */
#ifndef _interlockedbittestandcomplement
#define _interlockedbittestandcomplement _interlockedbittestandcomplement
__LOCAL __BYTE_TYPE__ (_interlockedbittestandcomplement)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { return !((__hybrid_atomic_fetchxor(*__base, (__LONG32_TYPE__)1 << __offset, __ATOMIC_SEQ_CST) >> __offset) & 1); }
#endif /* !_interlockedbittestandcomplement */
#ifndef _interlockedbittestandcomplement64
#define _interlockedbittestandcomplement64 _interlockedbittestandcomplement64
__LOCAL __BYTE_TYPE__ (_interlockedbittestandcomplement64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { return !((__hybrid_atomic_fetchxor(*__base, (__LONG64_TYPE__)1 << __offset, __ATOMIC_SEQ_CST) >> __offset) & 1); }
#endif /* !_interlockedbittestandcomplement64 */
#ifndef _interlockedbittestandset
#define _interlockedbittestandset _interlockedbittestandset
__LOCAL __BYTE_TYPE__ (_interlockedbittestandset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; return (__hybrid_atomic_fetchor(*__base, __mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !_interlockedbittestandset */
#ifndef _interlockedbittestandset64
#define _interlockedbittestandset64 _interlockedbittestandset64
__LOCAL __BYTE_TYPE__ (_interlockedbittestandset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; return (__hybrid_atomic_fetchor(*__base, __mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !_interlockedbittestandset64 */
#ifndef _interlockedbittestandreset
#define _interlockedbittestandreset _interlockedbittestandreset
__LOCAL __BYTE_TYPE__ (_interlockedbittestandreset)(__LONG32_TYPE__ *__base, __LONG32_TYPE__ __offset) { __LONG32_TYPE__ __mask = (__LONG32_TYPE__)1 << __offset; return (__hybrid_atomic_fetchand(*__base, ~__mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !_interlockedbittestandreset */
#ifndef _interlockedbittestandreset64
#define _interlockedbittestandreset64 _interlockedbittestandreset64
__LOCAL __BYTE_TYPE__ (_interlockedbittestandreset64)(__LONG64_TYPE__ *__base, __LONG64_TYPE__ __offset) { __LONG64_TYPE__ __mask = (__LONG64_TYPE__)1 << __offset; return (__hybrid_atomic_fetchand(*__base, ~__mask, __ATOMIC_SEQ_CST) & __mask) != 0; }
#endif /* !_interlockedbittestandreset64 */


__DECL_END
#endif /* __CC__ */

#endif /* GUARD_NT_ARCH_BITTEST_H */
