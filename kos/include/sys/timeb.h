/* HASH CRC-32:0xfcc4a312 */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/timeb.h) */
/* (#) Portability: DJGPP         (/include/sys/timeb.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/timeb.h) */
/* (#) Portability: FreeBSD       (/sys/sys/timeb.h) */
/* (#) Portability: GNU C Library (/time/sys/timeb.h) */
/* (#) Portability: MSVC          (/include/sys/timeb.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/timeb.h) */
/* (#) Portability: NetBSD        (/sys/sys/timeb.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/timeb.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/timeb.h) */
/* (#) Portability: Windows Kits  (/ucrt/sys/timeb.h) */
/* (#) Portability: diet libc     (/include/sys/timeb.h) */
/* (#) Portability: libc4/5       (/include/sys/timeb.h) */
/* (#) Portability: mintlib       (/include/sys/timeb.h) */
/* (#) Portability: musl libc     (/include/sys/timeb.h) */
/* (#) Portability: uClibc        (/include/sys/timeb.h) */
#ifndef _SYS_TIMEB_H
#define _SYS_TIMEB_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/os/timeb.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#ifdef __USE_DOS
#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#ifdef __CRT_HAVE__ftime32
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID(__ATTR_OUT(1),__NOTHROW_NCX,_ftime32,(struct __timeb32 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT_VOID(__ATTR_OUT(1),__NOTHROW_NCX,_ftime32,(struct __timeb32 *__timebuf),_ftime,(__timebuf))
#elif defined(__CRT_HAVE__ftime64) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT_VOID(__ATTR_OUT(1),__NOTHROW_NCX,_ftime32,(struct __timeb32 *__timebuf),_ftime64,(__timebuf))
#elif defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime64)
#include <libc/local/sys.timeb/_ftime32.h>
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL _ftime32)(struct __timeb32 *__timebuf) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime32))(__timebuf); })
#endif /* ... */
#if defined(__CRT_HAVE__ftime32) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT_VOID(__ATTR_OUT(1),__NOTHROW_NCX,_ftime64,(struct __timeb64 *__timebuf),_ftime32,(__timebuf))
#elif defined(__CRT_HAVE__ftime64)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE_VOID(__ATTR_OUT(1),__NOTHROW_NCX,_ftime64,(struct __timeb64 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE_ftime)
#include <libc/local/sys.timeb/_ftime64.h>
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL _ftime64)(struct __timeb64 *__timebuf) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime64))(__timebuf); })
#endif /* ... */
#ifdef __CRT_HAVE__ftime32_s
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT(1),errno_t,__NOTHROW_NCX,_ftime32_s,(struct __timeb32 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime64_s) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT(1),errno_t,__NOTHROW_NCX,_ftime32_s,(struct __timeb32 *__timebuf),_ftime64_s,(__timebuf))
#elif defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime) || defined(__CRT_HAVE__ftime64)
#include <libc/local/sys.timeb/_ftime32_s.h>
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) errno_t __NOTHROW_NCX(__LIBCCALL _ftime32_s)(struct __timeb32 *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime32_s))(__timebuf); })
#endif /* ... */
#if defined(__CRT_HAVE__ftime32_s) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT(1),errno_t,__NOTHROW_NCX,_ftime64_s,(struct __timeb64 *__timebuf),_ftime32_s,(__timebuf))
#elif defined(__CRT_HAVE__ftime64_s)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT(1),errno_t,__NOTHROW_NCX,_ftime64_s,(struct __timeb64 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime)
#include <libc/local/sys.timeb/_ftime64_s.h>
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(_ftime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) errno_t __NOTHROW_NCX(__LIBCCALL _ftime64_s)(struct __timeb64 *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ftime64_s))(__timebuf); })
#endif /* ... */
#endif /* __USE_DOS */


#if defined(__CRT_HAVE_ftime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,ftime,(struct timeb *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE_ftime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,ftime,(struct timeb *__timebuf),ftime64,(__timebuf))
#elif defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64)
#include <libc/local/sys.timeb/ftime.h>
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL ftime)(struct timeb *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftime))(__timebuf); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_ftime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,ftime64,(struct timeb64 *__timebuf),ftime,(__timebuf))
#elif defined(__CRT_HAVE_ftime64)
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(__ATTR_OUT(1),int,__NOTHROW_NCX,ftime64,(struct timeb64 *__timebuf),(__timebuf))
#elif defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime)
#include <libc/local/sys.timeb/ftime64.h>
/* >> ftime(3), ftime64(3)
 * Write information about the current time to `*timebuf'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
__NAMESPACE_LOCAL_USING_OR_IMPL(ftime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) int __NOTHROW_NCX(__LIBCCALL ftime64)(struct timeb64 *__timebuf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ftime64))(__timebuf); })
#endif /* ... */
#endif /* __USE_TIME64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_TIMEB_H */
