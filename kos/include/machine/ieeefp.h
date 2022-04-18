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
/* (#) Portability: Cygwin    (/newlib/libc/include/machine/ieeefp.h) */
/* (#) Portability: EMX kLIBC (/libc/include/machine/ieeefp.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/machine/ieeefp.h) */
#ifndef _MACHINE_IEEEFP_H
#define _MACHINE_IEEEFP_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

#if 0
#define _FLT_LARGEST_EXPONENT_IS_NORMAL 1
#endif

#if 0
#define _FLT_NO_DENORMALS 1
#endif

#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __IEEE_LITTLE_ENDIAN 1
#elif __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
#define __IEEE_BIG_ENDIAN 1
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define __IEEE_BYTES_LITTLE_ENDIAN 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#else /* __FLOAT_WORD_ORDER__ == ... */
#error "Unsupported endian"
#endif /* __FLOAT_WORD_ORDER__ != ... */

#if __SIZEOF_DOUBLE__ == 4
#define _DOUBLE_IS_32BITS 1
#endif /* __SIZEOF_DOUBLE__ == 4 */

/* #define _FLOAT_ARG float */
/* #define __OBSOLETE_MATH_DEFAULT 0/1 */
/* #define __OBSOLETE_MATH 0/1 */

#endif /* !_MACHINE_IEEEFP_H */
