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
/* (#) Portability: Linux (/usr/include/linux/swab.h) */
#ifndef _LINUX_SWAB_H
#define _LINUX_SWAB_H 1

#include <__stdinc.h>

#include <hybrid/byteswap.h>
#include <hybrid/typecore.h>

#include <asm/bitsperlong.h>
#include <linux/types.h>
#ifndef _ASM_SWAB_H
#include <asm/swab.h>
#endif /* !_ASM_SWAB_H */

#define ___constant_swab16 __hybrid_bswap16_c
#define ___constant_swab32 __hybrid_bswap32_c
#define ___constant_swab64 __hybrid_bswap64_c
#define ___constant_swahw32(x)                                             \
	(__CCAST(__u32)(((__CCAST(__u32)(x) & __UINT32_C(0x0000ffff)) << 16) | \
	                ((__CCAST(__u32)(x) & __UINT32_C(0xffff0000)) >> 16)))
#define ___constant_swahb32(x)                                            \
	(__CCAST(__u32)(((__CCAST(__u32)(x) & __UINT32_C(0x00ff00ff)) << 8) | \
	                ((__CCAST(__u32)(x) & __UINT32_C(0xff00ff00)) >> 8)))

#define __fswab16  __hybrid_bswap16
#define __fswab32  __hybrid_bswap32
#define __fswab64  __hybrid_bswap64
#define __fswahw32 ___constant_swahw32
#define __fswahb32 ___constant_swahb32
#define __swab16   __hybrid_bswap16
#define __swab32   __hybrid_bswap32
#define __swab64   __hybrid_bswap64

#if __SIZEOF_LONG__ == 8
#define __swab __swab64
#elif __SIZEOF_LONG__ == 4
#define __swab __swab32
#elif __SIZEOF_LONG__ == 2
#define __swab __swab16
#elif __SIZEOF_LONG__ == 1
#define __swab __swab8
#endif /* __SIZEOF_LONG__ == ... */

#define __swahw32     __fswahw32
#define __swahb32     __fswahb32
#define __swab16p(p)  __swab16(*(p))
#define __swab32p(p)  __swab32(*(p))
#define __swab64p(p)  __swab64(*(p))
#define __swahw32p(p) __swahw32(*(p))
#define __swahb32p(p) __swahb32(*(p))
#define __swab16s(p)  (void)(*(p) = __swab16p(p))
#define __swab32s(p)  (void)(*(p) = __swab32p(p))
#define __swab64s(p)  (void)(*(p) = __swab64p(p))
#define __swahw32s(p) (void)(*(p) = __swahw32p(p))
#define __swahb32s(p) (void)(*(p) = __swahb32p(p))

#endif /* !_LINUX_SWAB_H */
