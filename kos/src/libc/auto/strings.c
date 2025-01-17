/* HASH CRC-32:0x58a190d8 */
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
#ifndef GUARD_LIBC_AUTO_STRINGS_C
#define GUARD_LIBC_AUTO_STRINGS_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "strings.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/typecore.h>
#if __SIZEOF_INT__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)
DEFINE_INTERN_ALIAS_P(libc_popcount,libc_popcount32,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int i),(i));
#elif __SIZEOF_INT__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)
DEFINE_INTERN_ALIAS_P(libc_popcount,libc_popcount64,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int i),(i));
#elif !defined(LIBC_ARCH_HAVE_POPCOUNT)
#include <hybrid/__bit.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_popcount)(unsigned int i) {
	return __hybrid_popcount(i);
}
#endif /* ... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)
DEFINE_INTERN_ALIAS_P(libc_popcountl,libc_popcount32,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long i),(i));
#elif __SIZEOF_LONG__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)
DEFINE_INTERN_ALIAS_P(libc_popcountl,libc_popcount64,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long i),(i));
#elif !defined(LIBC_ARCH_HAVE_POPCOUNTL)
#include <hybrid/__bit.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_popcountl)(unsigned long i) {
	return __hybrid_popcount(i);
}
#endif /* ... */
#include <hybrid/typecore.h>
#if __SIZEOF_LONG_LONG__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)
DEFINE_INTERN_ALIAS_P(libc_popcountll,libc_popcount32,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG i),(i));
#elif __SIZEOF_LONG_LONG__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)
DEFINE_INTERN_ALIAS_P(libc_popcountll,libc_popcount64,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG i),(i));
#elif !defined(LIBC_ARCH_HAVE_POPCOUNTLL)
#include <hybrid/__bit.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_popcountll)(__ULONGLONG i) {
	return __hybrid_popcount(i);
}
#endif /* ... */
#ifndef LIBC_ARCH_HAVE_POPCOUNT32
#include <hybrid/__bit.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_popcount32)(uint32_t i) {
	return __hybrid_popcount(i);
}
#endif /* !LIBC_ARCH_HAVE_POPCOUNT32 */
#ifndef LIBC_ARCH_HAVE_POPCOUNT64
#include <hybrid/__bit.h>
/* >> popcount(3), popcountl(3), popcountll(3), popcount32(3), popcount64(3)
 * POPulationCOUNT. Return the number of 1-bits in `i' */
INTERN ATTR_SECTION(".text.crt.string.memory") ATTR_CONST WUNUSED unsigned int
NOTHROW(LIBCCALL libc_popcount64)(uint64_t i) {
	return __hybrid_popcount(i);
}
#endif /* !LIBC_ARCH_HAVE_POPCOUNT64 */
#endif /* !__KERNEL__ */

DECL_END

#include <hybrid/typecore.h>
#if !defined(__KERNEL__) && ((__SIZEOF_INT__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)) || (__SIZEOF_INT__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)) || !defined(LIBC_ARCH_HAVE_POPCOUNT))
DEFINE_PUBLIC_ALIAS_P(popcount,libc_popcount,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned int i),(i));
#endif /* !__KERNEL__ && ((__SIZEOF_INT__ == 4 && !LIBC_ARCH_HAVE_POPCOUNT32) || (__SIZEOF_INT__ == 8 && !LIBC_ARCH_HAVE_POPCOUNT64) || !LIBC_ARCH_HAVE_POPCOUNT) */
#if !defined(__KERNEL__) && ((__SIZEOF_LONG__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)) || (__SIZEOF_LONG__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)) || !defined(LIBC_ARCH_HAVE_POPCOUNTL))
DEFINE_PUBLIC_ALIAS_P(popcountl,libc_popcountl,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(unsigned long i),(i));
#endif /* !__KERNEL__ && ((__SIZEOF_LONG__ == 4 && !LIBC_ARCH_HAVE_POPCOUNT32) || (__SIZEOF_LONG__ == 8 && !LIBC_ARCH_HAVE_POPCOUNT64) || !LIBC_ARCH_HAVE_POPCOUNTL) */
#if !defined(__KERNEL__) && ((__SIZEOF_LONG_LONG__ == 4 && !defined(LIBC_ARCH_HAVE_POPCOUNT32)) || (__SIZEOF_LONG_LONG__ == 8 && !defined(LIBC_ARCH_HAVE_POPCOUNT64)) || !defined(LIBC_ARCH_HAVE_POPCOUNTLL))
DEFINE_PUBLIC_ALIAS_P(popcountll,libc_popcountll,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(__ULONGLONG i),(i));
#endif /* !__KERNEL__ && ((__SIZEOF_LONG_LONG__ == 4 && !LIBC_ARCH_HAVE_POPCOUNT32) || (__SIZEOF_LONG_LONG__ == 8 && !LIBC_ARCH_HAVE_POPCOUNT64) || !LIBC_ARCH_HAVE_POPCOUNTLL) */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_POPCOUNT32)
DEFINE_PUBLIC_ALIAS_P(popcount32,libc_popcount32,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(uint32_t i),(i));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_POPCOUNT32 */
#if !defined(__KERNEL__) && !defined(LIBC_ARCH_HAVE_POPCOUNT64)
DEFINE_PUBLIC_ALIAS_P(popcount64,libc_popcount64,ATTR_CONST WUNUSED,unsigned int,NOTHROW,LIBCCALL,(uint64_t i),(i));
#endif /* !__KERNEL__ && !LIBC_ARCH_HAVE_POPCOUNT64 */

#endif /* !GUARD_LIBC_AUTO_STRINGS_C */
