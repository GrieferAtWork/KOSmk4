/* HASH CRC-32:0x9ba0e271 */
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
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/utime.h) */
/* (#) Portability: DJGPP         (/include/utime.h) */
/* (#) Portability: DragonFly BSD (/include/utime.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/utime.h) */
/* (#) Portability: FreeBSD       (/include/utime.h) */
/* (#) Portability: GNU C Library (/io/utime.h) */
/* (#) Portability: GNU Hurd      (/usr/include/utime.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/utime.h) */
/* (#) Portability: NetBSD        (/include/utime.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/utime.h) */
/* (#) Portability: OpenBSD       (/include/utime.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/utime.h) */
/* (#) Portability: diet libc     (/include/utime.h) */
/* (#) Portability: libc4/5       (/include/utime.h) */
/* (#) Portability: libc6         (/include/utime.h) */
/* (#) Portability: mintlib       (/include/utime.h) */
/* (#) Portability: musl libc     (/include/utime.h) */
/* (#) Portability: uClibc        (/include/utime.h) */
#ifndef _UTIME_H
#define _UTIME_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/types.h>
#include <bits/os/utimbuf.h>


#ifdef __CC__
__SYSDECL_BEGIN

#if (defined(__USE_XOPEN) || defined(__USE_XOPEN2K) || defined(__USE_DOS))
#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K || __USE_DOS */

#ifdef __USE_DOS
#ifndef _UTIMBUF_DEFINED
#define _UTIMBUF_DEFINED 1
#define _utimbuf utimbuf
#endif /* !_UTIMBUF_DEFINED */
#endif /* __USE_DOS */

/* Used assembly names (Required for binary compatibility):
 * FMT       TIME  KOS         DOS(HOSTED)      DOS        GLC
 * char      32    utime       DOS$_utime32    _utime32   utime
 * char      64    utime64     DOS$_utime64    _utime64   ---
 * fd_t fd   32    futime      _futime32       _futime32  ---
 * fd_t fd   64    futime64    _futime64       _futime64  ---
 */

#if defined(__CRT_HAVE_utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE___utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),_utime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),_utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime,(char const *__filename, struct utimbuf const *__file_times),__utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE___utime64)
#include <libc/local/utime/utime.h>
/* >> utime(2), utime64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(utime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL utime)(char const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utime))(__filename, __file_times); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime32) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),_utime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime64)
/* >> utime(2), utime64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE___utime64)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),__utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime64)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,utime64,(char const *__filename, struct utimbuf64 const *__file_times),_utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)
#include <libc/local/utime/utime64.h>
/* >> utime(2), utime64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(utime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL utime64)(char const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utime64))(__filename, __file_times); })
#endif /* ... */
#endif /* __USE_TIME64 */


#ifdef __USE_KOS
#if defined(__CRT_HAVE_futime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime,(__fd_t __fd, struct utimbuf const *__file_times),(__fd,__file_times))
#elif defined(__CRT_HAVE__futime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime,(__fd_t __fd, struct utimbuf const *__file_times),_futime,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime,(__fd_t __fd, struct utimbuf const *__file_times),_futime32,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime,(__fd_t __fd, struct utimbuf const *__file_times),futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime,(__fd_t __fd, struct utimbuf const *__file_times),_futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime) || defined(__CRT_HAVE__futime32) || defined(__CRT_HAVE_futime64) || defined(__CRT_HAVE__futime64)
#include <libc/local/utime/futime.h>
/* >> futime(3), futime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL futime)(__fd_t __fd, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futime))(__fd, __file_times); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_futime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime64,(__fd_t __fd, struct utimbuf64 const *__file_times),futime,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime64)
/* >> futime(3), futime64(3) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime64,(__fd_t __fd, struct utimbuf64 const *__file_times),(__fd,__file_times))
#elif defined(__CRT_HAVE__futime64)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futime64,(__fd_t __fd, struct utimbuf64 const *__file_times),_futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime) || defined(__CRT_HAVE__futime32)
#include <libc/local/utime/futime64.h>
/* >> futime(3), futime64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL futime64)(__fd_t __fd, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futime64))(__fd, __file_times); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_KOS */



#ifdef __USE_DOS
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */
#if defined(__CRT_HAVE_utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE__utime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),_utime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),_utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime,(char const *__filename, struct utimbuf const *__file_times),__utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE___utime64)
#include <libc/local/utime/utime.h>
/* >> utime(2), utime64(2) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _utime)(char const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utime))(__filename, __file_times); }
#endif /* ... */
#if defined(__CRT_HAVE_futime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime,(__fd_t __fd, struct utimbuf const *__file_times),futime,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime,(__fd_t __fd, struct utimbuf const *__file_times),(__fd,__file_times))
#elif defined(__CRT_HAVE__futime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime,(__fd_t __fd, struct utimbuf const *__file_times),_futime32,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime,(__fd_t __fd, struct utimbuf const *__file_times),futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime,(__fd_t __fd, struct utimbuf const *__file_times),_futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime) || defined(__CRT_HAVE__futime32) || defined(__CRT_HAVE_futime64) || defined(__CRT_HAVE__futime64)
#include <libc/local/utime/futime.h>
/* >> futime(3), futime64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _futime)(__fd_t __fd, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futime))(__fd, __file_times); }
#endif /* ... */
#ifdef __CRT_HAVE__utime32
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime32,(char const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE_utime)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime32,(char const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime32,(char const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime32,(char const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime32,(char const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE___utime64)
#include <libc/local/utime/_utime32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_utime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _utime32)(char const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_utime32))(__filename, __file_times); })
#endif /* ... */
#if defined(__CRT_HAVE_utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime32) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),_utime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_utime64)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime64)
/* >> utime(2), utime64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),__utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime64)
/* >> utime(2), utime64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_utime64,(char const *__filename, struct utimbuf64 const *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)
#include <libc/local/utime/utime64.h>
/* >> utime(2), utime64(2) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _utime64)(char const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utime64))(__filename, __file_times); }
#endif /* ... */
#ifdef __CRT_HAVE__futime32
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime32,(__fd_t __fd, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),(__fd,__file_times))
#elif defined(__CRT_HAVE_futime)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime32,(__fd_t __fd, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),futime,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime32,(__fd_t __fd, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),_futime,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime64) || defined(__CRT_HAVE__futime64)
#include <libc/local/utime/_futime32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_futime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _futime32)(__fd_t __fd, struct __utimbuf32 __KOS_FIXED_CONST *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_futime32))(__fd, __file_times); })
#endif /* ... */
#if defined(__CRT_HAVE_futime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime64,(__fd_t __fd, struct utimbuf64 const *__file_times),futime,(__fd,__file_times))
#elif defined(__CRT_HAVE_futime64)
/* >> futime(3), futime64(3) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime64,(__fd_t __fd, struct utimbuf64 const *__file_times),futime64,(__fd,__file_times))
#elif defined(__CRT_HAVE__futime64)
/* >> futime(3), futime64(3) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_futime64,(__fd_t __fd, struct utimbuf64 const *__file_times),(__fd,__file_times))
#elif defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime) || defined(__CRT_HAVE__futime32)
#include <libc/local/utime/futime64.h>
/* >> futime(3), futime64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _futime64)(__fd_t __fd, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futime64))(__fd, __file_times); }
#endif /* ... */
#ifdef __CRT_HAVE__wutime
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime,(wchar_t const *__file, struct utimbuf const *__file_times),(__file,__file_times))
#elif defined(__CRT_HAVE__wutime32)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime,(wchar_t const *__file, struct utimbuf const *__file_times),_wutime32,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime,(wchar_t const *__file, struct utimbuf const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime,(wchar_t const *__file, struct utimbuf const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime,(wchar_t const *__file, struct utimbuf const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64) || ((defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE___utime64)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.wchar.utime/wutime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _wutime)(wchar_t const *__file, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime))(__file, __file_times); }
#endif /* ... */
#ifdef __CRT_HAVE_wutime
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime32,(wchar_t const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime32,(wchar_t const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times),_wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)
#include <libc/local/utime/_wutime32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wutime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _wutime32)(wchar_t const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wutime32))(__filename, __file_times); })
#endif /* ... */
#if defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime64,(__WCHAR_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime64,(__WCHAR_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64)
__CDECLARE(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,_wutime64,(__WCHAR_TYPE__ const *__file, struct utimbuf64 const *__file_times),(__file,__file_times))
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE___utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime) || defined(__CRT_HAVE__wutime32)
#include <libc/local/parts.wchar.utime/wutime64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL _wutime64)(__WCHAR_TYPE__ const *__file, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))(__file, __file_times); }
#endif /* ... */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */


#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_UTIME_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_UTIME_H */
#endif /* __USE_UTF */

#endif /* !_UTIME_H */
