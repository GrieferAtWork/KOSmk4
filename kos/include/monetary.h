/* HASH CRC-32:0x2aaf0d36 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/monetary.h) */
/* (#) Portability: DragonFly BSD (/include/monetary.h) */
/* (#) Portability: FreeBSD       (/include/monetary.h) */
/* (#) Portability: GNU C Library (/stdlib/monetary.h) */
/* (#) Portability: GNU Hurd      (/usr/include/monetary.h) */
/* (#) Portability: NetBSD        (/include/monetary.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/monetary.h) */
/* (#) Portability: libc6         (/include/monetary.h) */
/* (#) Portability: musl libc     (/include/monetary.h) */
#ifndef _MONETARY_H
#define _MONETARY_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifdef __CRT_HAVE_strfmon
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
extern "C++" {
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
__LIBC __ATTR_IN(3) __ATTR_LIBC_STRFMON(3, 4) __ATTR_OUTS(1, 2) ssize_t __NOTHROW_NCX(__VLIBCCALL strfmon)(char *__restrict __s, size_t __maxsize, char const *__restrict __format, ...) __CASMNAME_SAME_GCCNCX("strfmon");
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
} /* extern "C++" */
#endif /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#endif /* __CRT_HAVE_strfmon */
#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_strfmon_l
__LIBC __ATTR_IN(4) __ATTR_LIBC_STRFMON(4, 5) __ATTR_OUTS(1, 2) ssize_t __NOTHROW_NCX(__VLIBCCALL strfmon_l)(char *__restrict __s, size_t __maxsize, __locale_t __loc, const char *__restrict __format, ...) __CASMNAME_SAME("strfmon_l");
#elif defined(__CRT_HAVE___strfmon_l)
__LIBC __ATTR_IN(4) __ATTR_LIBC_STRFMON(4, 5) __ATTR_OUTS(1, 2) ssize_t __NOTHROW_NCX(__VLIBCCALL strfmon_l)(char *__restrict __s, size_t __maxsize, __locale_t __loc, const char *__restrict __format, ...) __CASMNAME("__strfmon_l");
#endif /* ... */
#endif /* __USE_XOPEN2K8 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_MONETARY_H */
