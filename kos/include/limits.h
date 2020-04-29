/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIMITS_H
#define _LIMITS_H 1

#include <__crt.h> /* Must be here because some programs need <limits.h> to `#define __stub_XXX' macros. */
#include <__stdinc.h>
#include <features.h>

#include <hybrid/limitcore.h>

/* You should really just always using 'MB_CUR_MAX'... */
#ifdef __CRT_DOS_PRIMARY
#define MB_LEN_MAX 5
#elif defined(__CRT_CYG_PRIMARY)
#include <newlib.h>
#define MB_LEN_MAX _MB_LEN_MAX
#else /* ... */
#define MB_LEN_MAX 16
#endif /* !... */

__SYSDECL_BEGIN

#define CHAR_BIT    __CHAR_BIT__
#define SCHAR_MIN   __SCHAR_MIN__
#define SCHAR_MAX   __SCHAR_MAX__
#define UCHAR_MAX   __UCHAR_MAX__
#define CHAR_MIN    __CHAR_MIN__
#define CHAR_MAX    __CHAR_MAX__
#define SHRT_MIN    __SHRT_MIN__
#define SHRT_MAX    __SHRT_MAX__
#define USHRT_MAX   __USHRT_MAX__
#define INT_MIN     __INT_MIN__
#define INT_MAX     __INT_MAX__
#define UINT_MAX    __UINT_MAX__
#define LONG_MIN    __LONG_MIN__
#define LONG_MAX    __LONG_MAX__
#define ULONG_MAX   __ULONG_MAX__
#ifdef __USE_ISOC99
#define LLONG_MIN   __LONG_LONG_MIN__
#define LLONG_MAX   __LONG_LONG_MAX__
#define ULLONG_MAX  __ULONG_LONG_MAX__
#endif /* __USE_ISOC99 */

#ifdef __USE_DOS
#define _I8_MIN     __PRIVATE_MIN_S1
#define _I8_MAX     __PRIVATE_MAX_S1
#define _UI8_MAX    __PRIVATE_MIN_U1
#define _I16_MIN    __PRIVATE_MIN_S2
#define _I16_MAX    __PRIVATE_MAX_S2
#define _UI16_MAX   __PRIVATE_MIN_U2
#define _I32_MIN    __PRIVATE_MIN_S4
#define _I32_MAX    __PRIVATE_MAX_S4
#define _UI32_MAX   __PRIVATE_MIN_U4
#define _I64_MIN    __PRIVATE_MIN_S8
#define _I64_MAX    __PRIVATE_MAX_S8
#define _UI64_MAX   __PRIVATE_MIN_U8
#ifdef __PRIVATE_MIN_S16
#define _I128_MIN   __PRIVATE_MIN_S16
#define _I128_MAX   __PRIVATE_MAX_S16
#define _UI128_MAX  __PRIVATE_MAX_U16
#endif /* __PRIVATE_MIN_S16 */

/* """Extension""" Define something that belongs in <stdint.h> */
#ifndef SIZE_MAX
#define SIZE_MAX    __SIZE_MAX__
#endif  /* SIZE_MAX */

#ifdef __USE_DOS_SLIB
#ifndef RSIZE_MAX
#define RSIZE_MAX  (__SIZE_MAX__ >> 1)
#endif /* RSIZE_MAX */
#endif /* __USE_DOS_SLIB */

#endif /* __USE_DOS */

__SYSDECL_END

#ifdef __USE_POSIX
#include <bits/posix1_lim.h>
#endif /* __USE_POSIX */

#ifdef __USE_POSIX2
#include <bits/posix2_lim.h>
#endif /* __USE_POSIX2 */

#ifdef __USE_XOPEN
#include <bits/xopen_lim.h>
#endif /* __USE_XOPEN */

#endif /* !_LIMITS_H */
