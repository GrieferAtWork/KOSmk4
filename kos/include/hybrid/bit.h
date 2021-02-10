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
#ifndef __GUARD_HYBRID_BIT_H
#define __GUARD_HYBRID_BIT_H 1

#include "__bit.h"

/* Bit-scanning / bit-manipulation functions. */

#ifdef __CC__

/* unsigned int FFS(unsigned Integer i):
 *     FindFirstSet
 *     Returns the index (starting at 1 for 0x01) of the first
 *     1-bit in given value, or ZERO(0) if the given value is ZERO(0).
 *     >> assert(!x ||  (x &  (1 << (ffs(x)-1))));    // FFS-bit is set
 *     >> assert(!x || !(x & ((1 << (ffs(x)-1))-1))); // Less significant bits are clear */
#define FFS(i) __hybrid_ffs(i)

/* unsigned int CLZ(unsigned Integer i):
 *     CountLeadingZeroes
 *     Return  the number of  leading ZEROes in `i',  starting at the most
 *     significant bit. When `i' is ZERO(0), then the result is undefined. */
#define CLZ(i) __hybrid_clz(i)

/* unsigned int CTZ(unsigned Integer i):
 *     CounTrailingZeroes
 *     Return the number of trailing ZEROes in `i', starting at the  least
 *     significant bit. When `i' is ZERO(0), then the result is undefined. */
#define CTZ(i) __hybrid_ctz(i)

/* unsigned int POPCOUNT(unsigned Integer i):
 *     POPulationCOUNT
 *     Return the number of 1-bits in `i' */
#define POPCOUNT(i) __hybrid_popcount(i)

/* unsigned int PARITY(unsigned Integer i):
 *     Return the parity of `i', that is `POPCOUNT(i) % 2' */
#define PARITY(i) __hybrid_parity(i)

/* unsigned int CLRSB(signed Integer i):
 *     CoultLeadingRedundantSignBits
 *     Return the number of leading, redundant sign-bits,
 *     that is:  The number  of bits  following the  most
 *     significant bit that are identical to it. */
#define CLRSB(i) __hybrid_clrsb(i)

/* UNSIGNED PEXT(UNSIGNED value, UNSIGNED mask):
 *     Parallel bit EXTract
 *     Return a compressed stream of bits from `value', selected by `mask'. */
#define PEXT(value, mask) __hybrid_pext(value, mask)

/* UNSIGNED PDEP(UNSIGNED value, UNSIGNED mask):
 *     Parallel bit DEPosit
 *     Decompress compressed bitset `value' by depositing as data selected by `mask'. */
#define PDEP(value, mask) __hybrid_pdep(value, mask)

#endif /* __CC__ */

#endif /* !__GUARD_HYBRID_BIT_H */
