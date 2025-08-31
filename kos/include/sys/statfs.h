/* HASH CRC-32:0xa3da6171 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/statfs.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/statfs.h) */
/* (#) Portability: GNU C Library (/io/sys/statfs.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/statfs.h) */
/* (#) Portability: diet libc     (/include/sys/statfs.h) */
/* (#) Portability: mintlib       (/include/sys/statfs.h) */
/* (#) Portability: musl libc     (/include/sys/statfs.h) */
/* (#) Portability: uClibc        (/include/sys/statfs.h) */
#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/os/statfs.h>
#include <bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__CRT_HAVE_statfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),(__file,__buf))
#elif defined(__CRT_HAVE___statfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),__statfs,(__file,__buf))
#elif defined(__CRT_HAVE___libc_statfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),__libc_statfs,(__file,__buf))
#elif defined(__CRT_HAVE_statfs64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs,(char const *__file, struct statfs *__buf),statfs64,(__file,__buf))
#endif /* ... */
#if defined(__CRT_HAVE_fstatfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs,(__fd_t __filedes, struct statfs *__buf),(__filedes,__buf))
#elif defined(__CRT_HAVE___fstatfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs,(__fd_t __filedes, struct statfs *__buf),__fstatfs,(__filedes,__buf))
#elif defined(__CRT_HAVE___libc_fstatfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs,(__fd_t __filedes, struct statfs *__buf),__libc_fstatfs,(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatfs64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs,(__fd_t __filedes, struct statfs *__buf),fstatfs64,(__filedes,__buf))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifndef statfs64
#if defined(__CRT_HAVE_statfs) && defined(_STATFS_MATCHES_STATFS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs64,(char const *__file, struct statfs64 *__buf),statfs,(__file,__buf))
#elif defined(__CRT_HAVE_statfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs64,(char const *__file, struct statfs64 *__buf),statfs,(__file,__buf))
#elif defined(__CRT_HAVE___statfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs64,(char const *__file, struct statfs64 *__buf),__statfs,(__file,__buf))
#elif defined(__CRT_HAVE___libc_statfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs64,(char const *__file, struct statfs64 *__buf),__libc_statfs,(__file,__buf))
#elif defined(__CRT_HAVE_statfs64)
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,statfs64,(char const *__file, struct statfs64 *__buf),(__file,__buf))
#endif /* ... */
#endif /* !statfs64 */
#if defined(__CRT_HAVE_fstatfs) && defined(_STATFS_MATCHES_STATFS64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),fstatfs,(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),fstatfs,(__filedes,__buf))
#elif defined(__CRT_HAVE___fstatfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),__fstatfs,(__filedes,__buf))
#elif defined(__CRT_HAVE___libc_fstatfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),__libc_fstatfs,(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatfs64)
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstatfs64,(__fd_t __filedes, struct statfs64 *__buf),(__filedes,__buf))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_STATFS_H */
