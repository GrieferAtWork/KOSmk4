/* HASH CRC-32:0xcc99a17 */
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
/* (#) Portability: libbsd (/include/bsd/libutil.h) */
#ifndef _BSD_LIBUTIL_H
#define _BSD_LIBUTIL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <asm/crt/humanize_number.h>
#include <features.h>
#include <libutil.h>
#include <bits/types.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>

/* Flags for `humanize_number(3)::flags' */
#if !defined(HN_DECIMAL) && defined(__HN_DECIMAL)
#define HN_DECIMAL      __HN_DECIMAL
#endif /* !HN_DECIMAL && __HN_DECIMAL */
#if !defined(HN_NOSPACE) && defined(__HN_NOSPACE)
#define HN_NOSPACE      __HN_NOSPACE
#endif /* !HN_NOSPACE && __HN_NOSPACE */
#if !defined(HN_B) && defined(__HN_B)
#define HN_B            __HN_B
#endif /* !HN_B && __HN_B */
#if !defined(HN_DIVISOR_1000) && defined(__HN_DIVISOR_1000)
#define HN_DIVISOR_1000 __HN_DIVISOR_1000
#endif /* !HN_DIVISOR_1000 && __HN_DIVISOR_1000 */
#if !defined(HN_IEC_PREFIXES) && defined(__HN_IEC_PREFIXES)
#define HN_IEC_PREFIXES __HN_IEC_PREFIXES
#endif /* !HN_IEC_PREFIXES && __HN_IEC_PREFIXES */

/* Flags for `humanize_number(3)::scale' */
#if !defined(HN_GETSCALE) && defined(__HN_GETSCALE)
#define HN_GETSCALE     __HN_GETSCALE
#endif /* !HN_GETSCALE && __HN_GETSCALE */
#if !defined(HN_AUTOSCALE) && defined(__HN_AUTOSCALE)
#define HN_AUTOSCALE    __HN_AUTOSCALE
#endif /* !HN_AUTOSCALE && __HN_AUTOSCALE */

#ifdef __CC__
__SYSDECL_BEGIN

#if !defined(__humanize_number_defined) && defined(__CRT_HAVE_humanize_number)
#define __humanize_number_defined
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
__CDECLARE(,int,__NOTHROW_NCX,humanize_number,(char *__buf, __SIZE_TYPE__ __len, __INT64_TYPE__ __bytes, char const *__suffix, int __scale, int __flags),(__buf,__len,__bytes,__suffix,__scale,__flags))
#endif /* !__humanize_number_defined && __CRT_HAVE_humanize_number */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_LIBUTIL_H */
