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
/* (#) Portability: Cygwin        (/newlib/libc/include/alloca.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/alloca.h) */
/* (#) Portability: GNU C Library (/stdlib/alloca.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/alloca.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/alloca.h) */
/* (#) Portability: avr-libc      (/include/alloca.h) */
/* (#) Portability: diet libc     (/include/alloca.h) */
/* (#) Portability: libc4/5       (/include/alloca.h) */
/* (#) Portability: libc6         (/include/alloca.h) */
/* (#) Portability: mintlib       (/include/alloca.h) */
/* (#) Portability: musl libc     (/include/alloca.h) */
/* (#) Portability: uClibc        (/include/alloca.h) */
#ifndef _ALLOCA_H
#define _ALLOCA_H 1

#include "__stdinc.h"
/**/

#include <features.h>

#include <hybrid/__alloca.h>

#ifdef __CC__
#ifndef __hybrid_alloca
#error "alloca() isn't support on this platform"
#endif /* !__hybrid_alloca */
#define alloca(num_bytes) __hybrid_alloca(num_bytes)

#ifdef __USE_KOS
#if __has_builtin(__builtin_alloca_with_align) || defined(__INTELLISENSE_GCC__)
/* Allocate on the stack with the given minimum alignment.
 *
 * Note that GCC's `__builtin_alloca_with_align()' uses  BIT-based
 * alignment values (for whatever nonsensical reason), though this
 * function is sane and takes BYTE-based alignments. */
#define aligned_alloca(num_bytes, min_alignment) \
	__builtin_alloca_with_align(num_bytes, (min_alignment) * 8)
#endif /* __has_builtin(__builtin_alloca_with_align) || __INTELLISENSE_GCC__ */
#endif /* __USE_KOS */

#endif /* __CC__ */

#endif /* !_ALLOCA_H */
