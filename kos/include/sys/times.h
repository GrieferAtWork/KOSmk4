/* HASH CRC-32:0xefb80ac5 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/times.h) */
/* (#) Portability: DJGPP         (/include/sys/times.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/times.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/times.h) */
/* (#) Portability: FreeBSD       (/sys/sys/times.h) */
/* (#) Portability: GNU C Library (/posix/sys/times.h) */
/* (#) Portability: NetBSD        (/sys/sys/times.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/times.h) */
/* (#) Portability: OpenBSD       (/sys/sys/times.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/times.h) */
/* (#) Portability: diet libc     (/include/sys/times.h) */
/* (#) Portability: libc4/5       (/include/sys/times.h) */
/* (#) Portability: mintlib       (/include/sys/times.h) */
/* (#) Portability: musl libc     (/include/sys/times.h) */
/* (#) Portability: uClibc        (/include/sys/times.h) */
#ifndef _SYS_TIMES_H
#define _SYS_TIMES_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <bits/os/tms.h> /* struct tms */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __clock_t_defined
#define __clock_t_defined
typedef __clock_t clock_t;
#endif /* !__clock_t_defined */

#ifdef __CRT_HAVE_times
/* >> times(2) */
__CDECLARE(__ATTR_OUT_OPT(1),clock_t,__NOTHROW_NCX,times,(struct tms *__buffer),(__buffer))
#elif defined(__CRT_HAVE___times)
/* >> times(2) */
__CREDIRECT(__ATTR_OUT_OPT(1),clock_t,__NOTHROW_NCX,times,(struct tms *__buffer),__times,(__buffer))
#elif defined(__CRT_HAVE___libc_times)
/* >> times(2) */
__CREDIRECT(__ATTR_OUT_OPT(1),clock_t,__NOTHROW_NCX,times,(struct tms *__buffer),__libc_times,(__buffer))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_TIMES_H */
