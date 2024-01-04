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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: DJGPP         (/include/stdarg.h) */
/* (#) Portability: DragonFly BSD (/include/stdarg.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/stdarg.h) */
/* (#) Portability: FreeBSD       (/sys/[...]/include/stdarg.h) */
/* (#) Portability: MSVC          (/include/stdarg.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/stdarg.h) */
/* (#) Portability: NetBSD        (/sys/arch/[...]/include/stdarg.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/stdarg.h) */
/* (#) Portability: PDCLib        (/include/stdarg.h) */
/* (#) Portability: diet libc     (/include/stdarg.h) */
/* (#) Portability: libcmini      (/include/stdarg.h) */
/* (#) Portability: musl libc     (/include/stdarg.h) */
#ifndef _STDARG_H
#define _STDARG_H 1

#ifdef _CXX_STDONLY_CSTDARG
#ifdef __CXX_SYSTEM_HEADER
#undef _STDARG_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "ctype.h" after "cctype" */
#ifndef __va_list_defined
#define __va_list_defined
__NAMESPACE_STD_USING(va_list)
#endif /* !__va_list_defined */
#undef _CXX_STDONLY_CSTDARG
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSTDARG */

#include "__stdinc.h"
#include <features.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __std_va_list_defined
#define __std_va_list_defined
__NAMESPACE_STD_BEGIN
typedef __builtin_va_list va_list;
__NAMESPACE_STD_END
#endif /* !__std_va_list_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __va_list_defined
#define __va_list_defined
__NAMESPACE_STD_USING(va_list)
#endif /* !__va_list_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* void va_start(va_list &ap, T &last_named_argument); */
#define va_start __builtin_va_start

/* void va_start(va_list &dest, va_list &src); */
#define __va_copy __builtin_va_copy

/* void va_end(va_list &ap); */
#define va_end __builtin_va_end

/* T va_arg(va_list &ap, typename T); */
#define va_arg __builtin_va_arg

#if (defined(__USE_ISOC99) || defined(__USE_SOLARIS) ||                  \
     defined(__USE_XOPEN2K) || defined(__USE_NETBSD) ||                  \
     (defined(__STDC_VERSION__) && (__STDC_VERSION__ + 0 >= 199900L)) || \
     (defined(__cplusplus) && (__cplusplus + 0 >= 201103L)))
#define va_copy __builtin_va_copy
#endif /* ... */
#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSTDARG
#undef _STDARG_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSTDARG */
#endif /* !_STDARG_H */
