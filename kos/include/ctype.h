/* HASH CRC-32:0xf2a9b1ed */
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
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/ctype.h) */
/* (#) Portability: DJGPP         (/include/ctype.h) */
/* (#) Portability: FreeBSD       (/include/ctype.h) */
/* (#) Portability: GNU C Library (/ctype/ctype.h) */
/* (#) Portability: MSVC          (/include/ctype.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/ctype.h) */
/* (#) Portability: NetBSD        (/include/ctype.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/ctype.h) */
/* (#) Portability: OpenBSD       (/include/ctype.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/ctype.h) */
/* (#) Portability: Windows Kits  (/ucrt/ctype.h) */
/* (#) Portability: diet libc     (/include/ctype.h) */
/* (#) Portability: libc4/5       (/include/ctype.h) */
/* (#) Portability: libc6         (/include/ctype.h) */
/* (#) Portability: musl libc     (/include/ctype.h) */
/* (#) Portability: uClibc        (/include/ctype.h) */
#ifndef _CTYPE_H
#define _CTYPE_H 1

#ifdef _CXX_STDONLY_CCTYPE
#ifdef __CXX_SYSTEM_HEADER
#undef _CTYPE_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "ctype.h" after "cctype" */
__NAMESPACE_STD_USING(iscntrl)
__NAMESPACE_STD_USING(isspace)
__NAMESPACE_STD_USING(isupper)
__NAMESPACE_STD_USING(islower)
__NAMESPACE_STD_USING(isalpha)
__NAMESPACE_STD_USING(isdigit)
__NAMESPACE_STD_USING(isxdigit)
__NAMESPACE_STD_USING(isalnum)
__NAMESPACE_STD_USING(ispunct)
__NAMESPACE_STD_USING(isgraph)
__NAMESPACE_STD_USING(isprint)
__NAMESPACE_STD_USING(tolower)
__NAMESPACE_STD_USING(toupper)
__NAMESPACE_STD_USING(isblank)
#undef _CXX_STDONLY_CCTYPE
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CCTYPE */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/crt/ctype.h>
#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_GLIBC
#include <endian.h>
#endif /* __USE_GLIBC */

#ifdef __USE_DOS
#include <corecrt.h>
#include <corecrt_wctype.h>
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#if defined(__crt_iscntrl) && defined(__CRT_HAVE_iscntrl)
/* >> iscntrl(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl,(int __ch),{ return __crt_iscntrl(__ch); })
#elif defined(__crt_iscntrl)
/* >> iscntrl(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iscntrl)(int __ch) { return __crt_iscntrl(__ch); }
#elif __has_builtin(__builtin_iscntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iscntrl)
/* >> iscntrl(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl,(int __ch),{ return __builtin_iscntrl(__ch); })
#elif defined(__CRT_HAVE_iscntrl)
/* >> iscntrl(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iscntrl,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/iscntrl.h>
__NAMESPACE_STD_BEGIN
/* >> iscntrl(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iscntrl)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl))(__ch); })
#endif /* !... */
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
/* >> isspace(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace,(int __ch),{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
/* >> isspace(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
/* >> isspace(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace,(int __ch),{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
/* >> isspace(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isspace,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_STD_BEGIN
/* >> isspace(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isspace)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace))(__ch); })
#endif /* !... */
#if defined(__crt_isupper) && defined(__CRT_HAVE_isupper)
/* >> isupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper,(int __ch),{ return __crt_isupper(__ch); })
#elif defined(__crt_isupper)
/* >> isupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isupper)(int __ch) { return __crt_isupper(__ch); }
#elif __has_builtin(__builtin_isupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isupper)
/* >> isupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper,(int __ch),{ return __builtin_isupper(__ch); })
#elif defined(__CRT_HAVE_isupper)
/* >> isupper(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isupper,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isupper.h>
__NAMESPACE_STD_BEGIN
/* >> isupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isupper)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper))(__ch); })
#endif /* !... */
#if defined(__crt_islower) && defined(__CRT_HAVE_islower)
/* >> islower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower,(int __ch),{ return __crt_islower(__ch); })
#elif defined(__crt_islower)
/* >> islower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL islower)(int __ch) { return __crt_islower(__ch); }
#elif __has_builtin(__builtin_islower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_islower)
/* >> islower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower,(int __ch),{ return __builtin_islower(__ch); })
#elif defined(__CRT_HAVE_islower)
/* >> islower(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,islower,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/islower.h>
__NAMESPACE_STD_BEGIN
/* >> islower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(islower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL islower)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower))(__ch); })
#endif /* !... */
#if defined(__crt_isalpha) && defined(__CRT_HAVE_isalpha)
/* >> isalpha(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha,(int __ch),{ return __crt_isalpha(__ch); })
#elif defined(__crt_isalpha)
/* >> isalpha(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isalpha)(int __ch) { return __crt_isalpha(__ch); }
#elif __has_builtin(__builtin_isalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalpha)
/* >> isalpha(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha,(int __ch),{ return __builtin_isalpha(__ch); })
#elif defined(__CRT_HAVE_isalpha)
/* >> isalpha(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalpha,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isalpha.h>
__NAMESPACE_STD_BEGIN
/* >> isalpha(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isalpha)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha))(__ch); })
#endif /* !... */
#if defined(__crt_isdigit) && defined(__CRT_HAVE_isdigit)
/* >> isdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit,(int __ch),{ return __crt_isdigit(__ch); })
#elif defined(__crt_isdigit)
/* >> isdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isdigit)(int __ch) { return __crt_isdigit(__ch); }
#elif __has_builtin(__builtin_isdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isdigit)
/* >> isdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit,(int __ch),{ return __builtin_isdigit(__ch); })
#elif defined(__CRT_HAVE_isdigit)
/* >> isdigit(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isdigit,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isdigit.h>
__NAMESPACE_STD_BEGIN
/* >> isdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isdigit)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit))(__ch); })
#endif /* !... */
#if defined(__crt_isxdigit) && defined(__CRT_HAVE_isxdigit)
/* >> isxdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit,(int __ch),{ return __crt_isxdigit(__ch); })
#elif defined(__crt_isxdigit)
/* >> isxdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isxdigit)(int __ch) { return __crt_isxdigit(__ch); }
#elif __has_builtin(__builtin_isxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isxdigit)
/* >> isxdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit,(int __ch),{ return __builtin_isxdigit(__ch); })
#elif defined(__CRT_HAVE_isxdigit)
/* >> isxdigit(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isxdigit,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isxdigit.h>
__NAMESPACE_STD_BEGIN
/* >> isxdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isxdigit)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit))(__ch); })
#endif /* !... */
#if defined(__crt_isalnum) && defined(__CRT_HAVE_isalnum)
/* >> isalnum(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum,(int __ch),{ return __crt_isalnum(__ch); })
#elif defined(__crt_isalnum)
/* >> isalnum(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isalnum)(int __ch) { return __crt_isalnum(__ch); }
#elif __has_builtin(__builtin_isalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isalnum)
/* >> isalnum(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum,(int __ch),{ return __builtin_isalnum(__ch); })
#elif defined(__CRT_HAVE_isalnum)
/* >> isalnum(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isalnum,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isalnum.h>
__NAMESPACE_STD_BEGIN
/* >> isalnum(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isalnum)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum))(__ch); })
#endif /* !... */
#if defined(__crt_ispunct) && defined(__CRT_HAVE_ispunct)
/* >> ispunct(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct,(int __ch),{ return __crt_ispunct(__ch); })
#elif defined(__crt_ispunct)
/* >> ispunct(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ispunct)(int __ch) { return __crt_ispunct(__ch); }
#elif __has_builtin(__builtin_ispunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_ispunct)
/* >> ispunct(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct,(int __ch),{ return __builtin_ispunct(__ch); })
#elif defined(__CRT_HAVE_ispunct)
/* >> ispunct(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,ispunct,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/ispunct.h>
__NAMESPACE_STD_BEGIN
/* >> ispunct(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL ispunct)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct))(__ch); })
#endif /* !... */
#if defined(__crt_isgraph) && defined(__CRT_HAVE_isgraph)
/* >> isgraph(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph,(int __ch),{ return __crt_isgraph(__ch); })
#elif defined(__crt_isgraph)
/* >> isgraph(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isgraph)(int __ch) { return __crt_isgraph(__ch); }
#elif __has_builtin(__builtin_isgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isgraph)
/* >> isgraph(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph,(int __ch),{ return __builtin_isgraph(__ch); })
#elif defined(__CRT_HAVE_isgraph)
/* >> isgraph(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isgraph,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isgraph.h>
__NAMESPACE_STD_BEGIN
/* >> isgraph(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isgraph)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph))(__ch); })
#endif /* !... */
#if defined(__crt_isprint) && defined(__CRT_HAVE_isprint)
/* >> isprint(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint,(int __ch),{ return __crt_isprint(__ch); })
#elif defined(__crt_isprint)
/* >> isprint(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isprint)(int __ch) { return __crt_isprint(__ch); }
#elif __has_builtin(__builtin_isprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isprint)
/* >> isprint(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint,(int __ch),{ return __builtin_isprint(__ch); })
#elif defined(__CRT_HAVE_isprint)
/* >> isprint(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isprint,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isprint.h>
__NAMESPACE_STD_BEGIN
/* >> isprint(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isprint)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint))(__ch); })
#endif /* !... */
#if defined(__crt_tolower) && defined(__CRT_HAVE_tolower)
/* >> tolower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,tolower,(int __ch),{ return __crt_tolower(__ch); })
#elif defined(__crt_tolower)
/* >> tolower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL tolower)(int __ch) { return __crt_tolower(__ch); }
#elif __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
/* >> tolower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,tolower,(int __ch),{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
/* >> tolower(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,tolower,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/tolower.h>
__NAMESPACE_STD_BEGIN
/* >> tolower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL tolower)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower))(__ch); })
#endif /* !... */
#if defined(__crt_toupper) && defined(__CRT_HAVE_toupper)
/* >> toupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,toupper,(int __ch),{ return __crt_toupper(__ch); })
#elif defined(__crt_toupper)
/* >> toupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL toupper)(int __ch) { return __crt_toupper(__ch); }
#elif __has_builtin(__builtin_toupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_toupper)
/* >> toupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,toupper,(int __ch),{ return __builtin_toupper(__ch); })
#elif defined(__CRT_HAVE_toupper)
/* >> toupper(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,toupper,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/toupper.h>
__NAMESPACE_STD_BEGIN
/* >> toupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL toupper)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper))(__ch); })
#endif /* !... */
#ifdef __USE_ISOC99
#if defined(__crt_isblank) && defined(__CRT_HAVE_isblank)
/* >> isblank(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank,(int __ch),{ return __crt_isblank(__ch); })
#elif defined(__crt_isblank)
/* >> isblank(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isblank)(int __ch) { return __crt_isblank(__ch); }
#elif __has_builtin(__builtin_isblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isblank)
/* >> isblank(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank,(int __ch),{ return __builtin_isblank(__ch); })
#elif defined(__CRT_HAVE_isblank)
/* >> isblank(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isblank,(int __ch),(__ch))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/ctype/isblank.h>
__NAMESPACE_STD_BEGIN
/* >> isblank(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isblank)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank))(__ch); })
#endif /* !... */
#endif /* __USE_ISOC99 */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(iscntrl)
__NAMESPACE_STD_USING(isspace)
__NAMESPACE_STD_USING(isupper)
__NAMESPACE_STD_USING(islower)
__NAMESPACE_STD_USING(isalpha)
__NAMESPACE_STD_USING(isdigit)
__NAMESPACE_STD_USING(isxdigit)
__NAMESPACE_STD_USING(isalnum)
__NAMESPACE_STD_USING(ispunct)
__NAMESPACE_STD_USING(isgraph)
__NAMESPACE_STD_USING(isprint)
__NAMESPACE_STD_USING(tolower)
__NAMESPACE_STD_USING(toupper)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(isblank)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */

#ifdef __USE_XOPEN2K8
#if defined(__crt_iscntrl_l) && defined(__CRT_HAVE_iscntrl_l)
/* >> iscntrl_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),{ return __crt_iscntrl_l(__ch, __locale); })
#elif defined(__crt_iscntrl_l) && defined(__CRT_HAVE__iscntrl_l)
/* >> iscntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),_iscntrl_l,{ return __crt_iscntrl_l(__ch, __locale); })
#elif defined(__crt_iscntrl_l) && defined(__CRT_HAVE___iscntrl_l)
/* >> iscntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),__iscntrl_l,{ return __crt_iscntrl_l(__ch, __locale); })
#elif defined(__crt_iscntrl_l)
/* >> iscntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iscntrl_l)(int __ch, __locale_t __locale) { return __crt_iscntrl_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iscntrl_l)
/* >> iscntrl_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iscntrl_l)
/* >> iscntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),_iscntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iscntrl_l)
/* >> iscntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iscntrl_l,(int __ch, __locale_t __locale),__iscntrl_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/iscntrl_l.h>
/* >> iscntrl_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iscntrl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iscntrl_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isspace_l) && defined(__CRT_HAVE_isspace_l)
/* >> isspace_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),{ return __crt_isspace_l(__ch, __locale); })
#elif defined(__crt_isspace_l) && defined(__CRT_HAVE__isspace_l)
/* >> isspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),_isspace_l,{ return __crt_isspace_l(__ch, __locale); })
#elif defined(__crt_isspace_l) && defined(__CRT_HAVE___isspace_l)
/* >> isspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),__isspace_l,{ return __crt_isspace_l(__ch, __locale); })
#elif defined(__crt_isspace_l)
/* >> isspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isspace_l)(int __ch, __locale_t __locale) { return __crt_isspace_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isspace_l)
/* >> isspace_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isspace_l)
/* >> isspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),_isspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isspace_l)
/* >> isspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isspace_l,(int __ch, __locale_t __locale),__isspace_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isspace_l.h>
/* >> isspace_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isspace_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isspace_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isupper_l) && defined(__CRT_HAVE_isupper_l)
/* >> isupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),{ return __crt_isupper_l(__ch, __locale); })
#elif defined(__crt_isupper_l) && defined(__CRT_HAVE__isupper_l)
/* >> isupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),_isupper_l,{ return __crt_isupper_l(__ch, __locale); })
#elif defined(__crt_isupper_l) && defined(__CRT_HAVE___isupper_l)
/* >> isupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),__isupper_l,{ return __crt_isupper_l(__ch, __locale); })
#elif defined(__crt_isupper_l)
/* >> isupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isupper_l)(int __ch, __locale_t __locale) { return __crt_isupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isupper_l)
/* >> isupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isupper_l)
/* >> isupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),_isupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isupper_l)
/* >> isupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isupper_l,(int __ch, __locale_t __locale),__isupper_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isupper_l.h>
/* >> isupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isupper_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_islower_l) && defined(__CRT_HAVE_islower_l)
/* >> islower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),{ return __crt_islower_l(__ch, __locale); })
#elif defined(__crt_islower_l) && defined(__CRT_HAVE__islower_l)
/* >> islower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),_islower_l,{ return __crt_islower_l(__ch, __locale); })
#elif defined(__crt_islower_l) && defined(__CRT_HAVE___islower_l)
/* >> islower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),__islower_l,{ return __crt_islower_l(__ch, __locale); })
#elif defined(__crt_islower_l)
/* >> islower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL islower_l)(int __ch, __locale_t __locale) { return __crt_islower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_islower_l)
/* >> islower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__islower_l)
/* >> islower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),_islower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___islower_l)
/* >> islower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,islower_l,(int __ch, __locale_t __locale),__islower_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/islower_l.h>
/* >> islower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(islower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL islower_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isalpha_l) && defined(__CRT_HAVE_isalpha_l)
/* >> isalpha_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),{ return __crt_isalpha_l(__ch, __locale); })
#elif defined(__crt_isalpha_l) && defined(__CRT_HAVE__isalpha_l)
/* >> isalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),_isalpha_l,{ return __crt_isalpha_l(__ch, __locale); })
#elif defined(__crt_isalpha_l) && defined(__CRT_HAVE___isalpha_l)
/* >> isalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),__isalpha_l,{ return __crt_isalpha_l(__ch, __locale); })
#elif defined(__crt_isalpha_l)
/* >> isalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isalpha_l)(int __ch, __locale_t __locale) { return __crt_isalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isalpha_l)
/* >> isalpha_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isalpha_l)
/* >> isalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),_isalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isalpha_l)
/* >> isalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalpha_l,(int __ch, __locale_t __locale),__isalpha_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isalpha_l.h>
/* >> isalpha_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalpha_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isalpha_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isdigit_l) && defined(__CRT_HAVE_isdigit_l)
/* >> isdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l) && defined(__CRT_HAVE__isdigit_l)
/* >> isdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),_isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l) && defined(__CRT_HAVE___isdigit_l)
/* >> isdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l)
/* >> isdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isdigit_l)(int __ch, __locale_t __locale) { return __crt_isdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isdigit_l)
/* >> isdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isdigit_l)
/* >> isdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),_isdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isdigit_l)
/* >> isdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isdigit_l.h>
/* >> isdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isdigit_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isxdigit_l) && defined(__CRT_HAVE_isxdigit_l)
/* >> isxdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),{ return __crt_isxdigit_l(__ch, __locale); })
#elif defined(__crt_isxdigit_l) && defined(__CRT_HAVE__isxdigit_l)
/* >> isxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),_isxdigit_l,{ return __crt_isxdigit_l(__ch, __locale); })
#elif defined(__crt_isxdigit_l) && defined(__CRT_HAVE___isxdigit_l)
/* >> isxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),__isxdigit_l,{ return __crt_isxdigit_l(__ch, __locale); })
#elif defined(__crt_isxdigit_l)
/* >> isxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isxdigit_l)(int __ch, __locale_t __locale) { return __crt_isxdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isxdigit_l)
/* >> isxdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isxdigit_l)
/* >> isxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),_isxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isxdigit_l)
/* >> isxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isxdigit_l,(int __ch, __locale_t __locale),__isxdigit_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isxdigit_l.h>
/* >> isxdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isxdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isxdigit_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isalnum_l) && defined(__CRT_HAVE_isalnum_l)
/* >> isalnum_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l) && defined(__CRT_HAVE__isalnum_l)
/* >> isalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),_isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l) && defined(__CRT_HAVE___isalnum_l)
/* >> isalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l)
/* >> isalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isalnum_l)(int __ch, __locale_t __locale) { return __crt_isalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isalnum_l)
/* >> isalnum_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isalnum_l)
/* >> isalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),_isalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isalnum_l)
/* >> isalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isalnum_l.h>
/* >> isalnum_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isalnum_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isalnum_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_ispunct_l) && defined(__CRT_HAVE_ispunct_l)
/* >> ispunct_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l) && defined(__CRT_HAVE__ispunct_l)
/* >> ispunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),_ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l) && defined(__CRT_HAVE___ispunct_l)
/* >> ispunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l)
/* >> ispunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL ispunct_l)(int __ch, __locale_t __locale) { return __crt_ispunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_ispunct_l)
/* >> ispunct_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__ispunct_l)
/* >> ispunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),_ispunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE___ispunct_l)
/* >> ispunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/ispunct_l.h>
/* >> ispunct_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(ispunct_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL ispunct_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isgraph_l) && defined(__CRT_HAVE_isgraph_l)
/* >> isgraph_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),{ return __crt_isgraph_l(__ch, __locale); })
#elif defined(__crt_isgraph_l) && defined(__CRT_HAVE__isgraph_l)
/* >> isgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),_isgraph_l,{ return __crt_isgraph_l(__ch, __locale); })
#elif defined(__crt_isgraph_l) && defined(__CRT_HAVE___isgraph_l)
/* >> isgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),__isgraph_l,{ return __crt_isgraph_l(__ch, __locale); })
#elif defined(__crt_isgraph_l)
/* >> isgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isgraph_l)(int __ch, __locale_t __locale) { return __crt_isgraph_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isgraph_l)
/* >> isgraph_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isgraph_l)
/* >> isgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),_isgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isgraph_l)
/* >> isgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isgraph_l,(int __ch, __locale_t __locale),__isgraph_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isgraph_l.h>
/* >> isgraph_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isgraph_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isgraph_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isprint_l) && defined(__CRT_HAVE_isprint_l)
/* >> isprint_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l) && defined(__CRT_HAVE__isprint_l)
/* >> isprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),_isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l) && defined(__CRT_HAVE___isprint_l)
/* >> isprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),__isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l)
/* >> isprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isprint_l)(int __ch, __locale_t __locale) { return __crt_isprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isprint_l)
/* >> isprint_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isprint_l)
/* >> isprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),_isprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isprint_l)
/* >> isprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isprint_l,(int __ch, __locale_t __locale),__isprint_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isprint_l.h>
/* >> isprint_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isprint_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isprint_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_isblank_l) && defined(__CRT_HAVE_isblank_l)
/* >> isblank_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),{ return __crt_isblank_l(__ch, __locale); })
#elif defined(__crt_isblank_l) && defined(__CRT_HAVE__isblank_l)
/* >> isblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),_isblank_l,{ return __crt_isblank_l(__ch, __locale); })
#elif defined(__crt_isblank_l) && defined(__CRT_HAVE___isblank_l)
/* >> isblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),__isblank_l,{ return __crt_isblank_l(__ch, __locale); })
#elif defined(__crt_isblank_l)
/* >> isblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isblank_l)(int __ch, __locale_t __locale) { return __crt_isblank_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isblank_l)
/* >> isblank_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__isblank_l)
/* >> isblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),_isblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE___isblank_l)
/* >> isblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,isblank_l,(int __ch, __locale_t __locale),__isblank_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isblank_l.h>
/* >> isblank_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isblank_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL isblank_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_tolower_l) && defined(__CRT_HAVE_tolower_l)
/* >> tolower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l) && defined(__CRT_HAVE__tolower_l)
/* >> tolower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),_tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l) && defined(__CRT_HAVE___tolower_l)
/* >> tolower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),__tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l)
/* >> tolower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL tolower_l)(int __ch, __locale_t __locale) { return __crt_tolower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_tolower_l)
/* >> tolower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__tolower_l)
/* >> tolower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),_tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___tolower_l)
/* >> tolower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,tolower_l,(int __ch, __locale_t __locale),__tolower_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/tolower_l.h>
/* >> tolower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(tolower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL tolower_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_toupper_l) && defined(__CRT_HAVE_toupper_l)
/* >> toupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l) && defined(__CRT_HAVE__toupper_l)
/* >> toupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),_toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l) && defined(__CRT_HAVE___toupper_l)
/* >> toupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),__toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l)
/* >> toupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL toupper_l)(int __ch, __locale_t __locale) { return __crt_toupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_toupper_l)
/* >> toupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__toupper_l)
/* >> toupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),_toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___toupper_l)
/* >> toupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,toupper_l,(int __ch, __locale_t __locale),__toupper_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/toupper_l.h>
/* >> toupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(toupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL toupper_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper_l))(__ch, __locale); })
#endif /* !... */
#endif /* __USE_XOPEN2K8 */

#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)

#ifdef __USE_XOPEN2K8
#ifdef __crt_isalnum_l
#define isalnum_l(ch, locale) __crt_isalnum_l(ch, locale)
#endif /* __crt_isalnum_l */
#ifdef __crt_isalpha_l
#define isalpha_l(ch, locale) __crt_isalpha_l(ch, locale)
#endif /* __crt_isalpha_l */
#ifdef __crt_isupper_l
#define isupper_l(ch, locale) __crt_isupper_l(ch, locale)
#endif /* __crt_isupper_l */
#ifdef __crt_islower_l
#define islower_l(ch, locale) __crt_islower_l(ch, locale)
#endif /* __crt_islower_l */
#ifdef __crt_isdigit_l
#define isdigit_l(ch, locale) __crt_isdigit_l(ch, locale)
#endif /* __crt_isdigit_l */
#ifdef __crt_isxdigit_l
#define isxdigit_l(ch, locale) __crt_isxdigit_l(ch, locale)
#endif /* __crt_isxdigit_l */
#ifdef __crt_isspace_l
#define isspace_l(ch, locale) __crt_isspace_l(ch, locale)
#endif /* __crt_isspace_l */
#ifdef __crt_ispunct_l
#define ispunct_l(ch, locale) __crt_ispunct_l(ch, locale)
#endif /* __crt_ispunct_l */
#ifdef __crt_isprint_l
#define isprint_l(ch, locale) __crt_isprint_l(ch, locale)
#endif /* __crt_isprint_l */
#ifdef __crt_isgraph_l
#define isgraph_l(ch, locale) __crt_isgraph_l(ch, locale)
#endif /* __crt_isgraph_l */
#ifdef __crt_iscntrl_l
#define iscntrl_l(ch, locale) __crt_iscntrl_l(ch, locale)
#endif /* __crt_iscntrl_l */
#ifdef __crt_isblank_l
#define isblank_l(ch, locale) __crt_isblank_l(ch, locale)
#endif /* __crt_isblank_l */
#ifdef __crt_tolower_l
#define tolower_l(ch, locale) __crt_tolower_l(ch, locale)
#endif /* __crt_tolower_l */
#ifdef __crt_toupper_l
#define toupper_l(ch, locale) __crt_toupper_l(ch, locale)
#endif /* __crt_toupper_l */
#endif /* __USE_XOPEN2K8 */

#ifndef __NO_builtin_constant_p
#ifndef __NO_builtin_choose_expr
#ifdef __crt_isalnum
#define isalnum(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalnum(ch), __crt_isalnum(ch))
#endif /* __crt_isalnum */
#ifdef __crt_isalpha
#define isalpha(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isalpha(ch), __crt_isalpha(ch))
#endif /* __crt_isalpha */
#ifdef __crt_isupper
#define isupper(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isupper(ch), __crt_isupper(ch))
#endif /* __crt_isupper */
#ifdef __crt_islower
#define islower(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_islower(ch), __crt_islower(ch))
#endif /* __crt_islower */
#ifdef __crt_isdigit
#define isdigit(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isdigit(ch), __crt_isdigit(ch))
#endif /* __crt_isdigit */
#ifdef __crt_isxdigit
#define isxdigit(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isxdigit(ch), __crt_isxdigit(ch))
#endif /* __crt_isxdigit */
#ifdef __crt_isspace
#define isspace(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isspace(ch), __crt_isspace(ch))
#endif /* __crt_isspace */
#ifdef __crt_ispunct
#define ispunct(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_ispunct(ch), __crt_ispunct(ch))
#endif /* __crt_ispunct */
#ifdef __crt_isprint
#define isprint(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isprint(ch), __crt_isprint(ch))
#endif /* __crt_isprint */
#ifdef __crt_isgraph
#define isgraph(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isgraph(ch), __crt_isgraph(ch))
#endif /* __crt_isgraph */
#ifdef __crt_iscntrl
#define iscntrl(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_iscntrl(ch), __crt_iscntrl(ch))
#endif /* __crt_iscntrl */
#if defined(__USE_ISOC99) && defined(__crt_isblank)
#define isblank(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_isblank(ch), __crt_isblank(ch))
#endif /* __USE_ISOC99 && __crt_isblank */
#ifdef __crt_tolower
#define tolower(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_tolower(ch), __crt_tolower(ch))
#endif /* __crt_tolower */
#ifdef __crt_toupper
#define toupper(ch) __builtin_choose_expr(__builtin_constant_p(ch), __ascii_toupper(ch), __crt_toupper(ch))
#endif /* __crt_toupper */
#else /* !__NO_builtin_choose_expr */
#ifdef __crt_isalnum
#define isalnum(ch) (__builtin_constant_p(ch) ? __ascii_isalnum(ch) : __crt_isalnum(ch))
#endif /* __crt_isalnum */
#ifdef __crt_isalpha
#define isalpha(ch) (__builtin_constant_p(ch) ? __ascii_isalpha(ch) : __crt_isalpha(ch))
#endif /* __crt_isalpha */
#ifdef __crt_isupper
#define isupper(ch) (__builtin_constant_p(ch) ? __ascii_isupper(ch) : __crt_isupper(ch))
#endif /* __crt_isupper */
#ifdef __crt_islower
#define islower(ch) (__builtin_constant_p(ch) ? __ascii_islower(ch) : __crt_islower(ch))
#endif /* __crt_islower */
#ifdef __crt_isdigit
#define isdigit(ch) (__builtin_constant_p(ch) ? __ascii_isdigit(ch) : __crt_isdigit(ch))
#endif /* __crt_isdigit */
#ifdef __crt_isxdigit
#define isxdigit(ch) (__builtin_constant_p(ch) ? __ascii_isxdigit(ch) : __crt_isxdigit(ch))
#endif /* __crt_isxdigit */
#ifdef __crt_isspace
#define isspace(ch) (__builtin_constant_p(ch) ? __ascii_isspace(ch) : __crt_isspace(ch))
#endif /* __crt_isspace */
#ifdef __crt_ispunct
#define ispunct(ch) (__builtin_constant_p(ch) ? __ascii_ispunct(ch) : __crt_ispunct(ch))
#endif /* __crt_ispunct */
#ifdef __crt_isprint
#define isprint(ch) (__builtin_constant_p(ch) ? __ascii_isprint(ch) : __crt_isprint(ch))
#endif /* __crt_isprint */
#ifdef __crt_isgraph
#define isgraph(ch) (__builtin_constant_p(ch) ? __ascii_isgraph(ch) : __crt_isgraph(ch))
#endif /* __crt_isgraph */
#ifdef __crt_iscntrl
#define iscntrl(ch) (__builtin_constant_p(ch) ? __ascii_iscntrl(ch) : __crt_iscntrl(ch))
#endif /* __crt_iscntrl */
#if defined(__USE_ISOC99) && defined(__crt_isblank)
#define isblank(ch) (__builtin_constant_p(ch) ? __ascii_isblank(ch) : __crt_isblank(ch))
#endif /* __USE_ISOC99 && __crt_isblank */
#ifdef __crt_tolower
#define tolower(ch) (__builtin_constant_p(ch) ? __ascii_tolower(ch) : __crt_tolower(ch))
#endif /* __crt_tolower */
#ifdef __crt_toupper
#define toupper(ch) (__builtin_constant_p(ch) ? __ascii_toupper(ch) : __crt_toupper(ch))
#endif /* __crt_toupper */
#endif /* __NO_builtin_choose_expr */
#else /* !__NO_builtin_constant_p */
#ifdef __crt_isalnum
#define isalnum(ch) __crt_isalnum(ch)
#endif /* __crt_isalnum */
#ifdef __crt_isalpha
#define isalpha(ch) __crt_isalpha(ch)
#endif /* __crt_isalpha */
#ifdef __crt_isupper
#define isupper(ch) __crt_isupper(ch)
#endif /* __crt_isupper */
#ifdef __crt_islower
#define islower(ch) __crt_islower(ch)
#endif /* __crt_islower */
#ifdef __crt_isdigit
#define isdigit(ch) __crt_isdigit(ch)
#endif /* __crt_isdigit */
#ifdef __crt_isxdigit
#define isxdigit(ch) __crt_isxdigit(ch)
#endif /* __crt_isxdigit */
#ifdef __crt_isspace
#define isspace(ch) __crt_isspace(ch)
#endif /* __crt_isspace */
#ifdef __crt_ispunct
#define ispunct(ch) __crt_ispunct(ch)
#endif /* __crt_ispunct */
#ifdef __crt_isprint
#define isprint(ch) __crt_isprint(ch)
#endif /* __crt_isprint */
#ifdef __crt_isgraph
#define isgraph(ch) __crt_isgraph(ch)
#endif /* __crt_isgraph */
#ifdef __crt_iscntrl
#define iscntrl(ch) __crt_iscntrl(ch)
#endif /* __crt_iscntrl */
#if defined(__USE_ISOC99) && defined(__crt_isblank)
#define isblank(ch) __crt_isblank(ch)
#endif /* __USE_ISOC99 && __crt_isblank */
#ifdef __crt_tolower
#define tolower(ch) __crt_tolower(ch)
#endif /* __crt_tolower */
#ifdef __crt_toupper
#define toupper(ch) __crt_toupper(ch)
#endif /* __crt_toupper */
#endif /* __NO_builtin_constant_p */

#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */

#ifdef __USE_KOS
#ifdef __CRT_HAVE___iscsymf
/* >> issymstrt(3)
 * Test if `ch' can appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymstrt,(int __ch),__iscsymf,(__ch))
#else /* __CRT_HAVE___iscsymf */
#include <libc/local/ctype/issymstrt.h>
/* >> issymstrt(3)
 * Test if `ch' can appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymstrt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL issymstrt)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymstrt))(__ch); })
#endif /* !__CRT_HAVE___iscsymf */
#ifdef __CRT_HAVE___iscsym
/* >> issymcont(3)
 * Test if `ch' can appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,issymcont,(int __ch),__iscsym,(__ch))
#else /* __CRT_HAVE___iscsym */
#include <libc/local/ctype/issymcont.h>
/* >> issymcont(3)
 * Test if `ch' can appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(issymcont, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL issymcont)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymcont))(__ch); })
#endif /* !__CRT_HAVE___iscsym */
#endif /* __USE_KOS */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifdef __CRT_HAVE_isascii
/* Returns non-zero if `(C & ~0x7f) == 0' */
__CEIDECLARE(__ATTR_CONST,int,__NOTHROW,isascii,(int __c),{ return (__c & ~0x7f) == 0; })
#elif defined(__CRT_HAVE___isascii)
/* Returns non-zero if `(C & ~0x7f) == 0' */
__CEIREDIRECT(__ATTR_CONST,int,__NOTHROW,isascii,(int __c),__isascii,{ return (__c & ~0x7f) == 0; })
#else /* ... */
/* Returns non-zero if `(C & ~0x7f) == 0' */
__LOCAL __ATTR_CONST int __NOTHROW(__LIBCCALL isascii)(int __c) { return (__c & ~0x7f) == 0; }
#endif /* !... */
#ifdef __CRT_HAVE_toascii
/* Re-returns `C & 0x7f' */
__CEIDECLARE(__ATTR_CONST,int,__NOTHROW,toascii,(int __c),{ return __c & 0x7f; })
#elif defined(__CRT_HAVE___toascii)
/* Re-returns `C & 0x7f' */
__CEIREDIRECT(__ATTR_CONST,int,__NOTHROW,toascii,(int __c),__toascii,{ return __c & 0x7f; })
#else /* ... */
/* Re-returns `C & 0x7f' */
__LOCAL __ATTR_CONST int __NOTHROW(__LIBCCALL toascii)(int __c) { return __c & 0x7f; }
#endif /* !... */
#if (!defined(__cplusplus) || defined(__USE_CTYPE_MACROS)) && !defined(__CXX_SYSTEM_HEADER)
#define isascii(c) (((c) & ~0x7f) == 0)
#define toascii(c) ((c) & 0x7f)
#endif /* (!__cplusplus || __USE_CTYPE_MACROS) && !__CXX_SYSTEM_HEADER */
#endif /* __USE_MISC || __USE_XOPEN */

#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(__USE_DOS)
#ifdef __CRT_HAVE__tolower
/* >> _tolower(3)
 * Same as `tolower(3)', but the caller must ensure that `isupper(ch)' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_tolower,(int __ch),{ return __ch + 0x20; })
#else /* __CRT_HAVE__tolower */
/* >> _tolower(3)
 * Same as `tolower(3)', but the caller must ensure that `isupper(ch)' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL _tolower)(int __ch) { return __ch + 0x20; }
#endif /* !__CRT_HAVE__tolower */
#ifdef __CRT_HAVE__toupper
/* >> _toupper(3)
 * Same as `toupper(3)', but the caller must ensure that `islower(ch)' */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_toupper,(int __ch),{ return __ch - 0x20; })
#else /* __CRT_HAVE__toupper */
/* >> _toupper(3)
 * Same as `toupper(3)', but the caller must ensure that `islower(ch)' */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL _toupper)(int __ch) { return __ch - 0x20; }
#endif /* !__CRT_HAVE__toupper */
#endif /* __USE_MISC || __USE_XOPEN || __USE_DOS */

#ifdef __USE_DOS
/* Possible values for `mask' argument of `_isctype(3)' */
#ifndef _UPPER
#define _UPPER    0x0001 /* isupper() */
#define _LOWER    0x0002 /* islower() */
#define _DIGIT    0x0004 /* isdigit() */
#define _SPACE    0x0008 /* isspace() */
#define _PUNCT    0x0010 /* ispunct() */
#define _CONTROL  0x0020 /* iscntrl() */
#define _BLANK    0x0040 /* isblank() */
#define _HEX      0x0080 /* isxdigit() - isdigit() */
#define _LEADBYTE 0x8000 /* Leading byte of multi-byte sequence */
#define _ALPHA    0x0103 /* isalpha() -- (0x0100 | _UPPER | _LOWER) */
#endif /* !_UPPER */


#ifndef MB_CUR_MAX
#ifdef __LOCAL_MB_CUR_MAX
#define MB_CUR_MAX __LOCAL_MB_CUR_MAX
#elif defined(__mb_cur_max)
#define MB_CUR_MAX ((__SIZE_TYPE__)__mb_cur_max)
#elif defined(__ctype_get_mb_cur_max) || defined(____ctype_get_mb_cur_max_defined)
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(___mb_cur_max_func) || defined(_____mb_cur_max_func_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__p___mb_cur_max) || defined(____p___mb_cur_max_defined)
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___ctype_get_mb_cur_max)
#define ____ctype_get_mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW,__ctype_get_mb_cur_max,(void),())
#define MB_CUR_MAX __ctype_get_mb_cur_max()
#elif defined(__CRT_HAVE____mb_cur_max_func)
#define _____mb_cur_max_func_defined
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,___mb_cur_max_func,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)___mb_cur_max_func())
#elif defined(__CRT_HAVE___p___mb_cur_max)
#define ____p___mb_cur_max_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW,__p___mb_cur_max,(void),())
#define MB_CUR_MAX ((__SIZE_TYPE__)*__p___mb_cur_max())
#elif defined(__CRT_HAVE___mb_cur_max)
__LIBC int __mb_cur_max __CASMNAME_SAME("__mb_cur_max");
#define __mb_cur_max __mb_cur_max
#define MB_CUR_MAX   ((__SIZE_TYPE__)__mb_cur_max)
#else /* __CRT_HAVE___ctype_get_mb_cur_max */
#define MB_CUR_MAX 7 /* == UNICODE_UTF8_CURLEN */
#endif /* !__CRT_HAVE___ctype_get_mb_cur_max */
#endif /* !MB_CUR_MAX */
#ifndef _____mb_cur_max_func_defined
#define _____mb_cur_max_func_defined
#ifdef __CRT_HAVE___ctype_get_mb_cur_max
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,___mb_cur_max_func,(void),__ctype_get_mb_cur_max,())
#elif defined(__CRT_HAVE____mb_cur_max_func)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,___mb_cur_max_func,(void),())
#else /* ... */
#include <libc/local/ctype/__ctype_get_mb_cur_max.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL ___mb_cur_max_func)(void) { return (int)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(__ctype_get_mb_cur_max))(); }
#endif /* !... */
#endif /* !_____mb_cur_max_func_defined */
#ifdef __CRT_HAVE____mb_cur_max_l_func
__CDECLARE(,int,__NOTHROW_NCX,___mb_cur_max_l_func,(__locale_t __locale),(__locale))
#else /* __CRT_HAVE____mb_cur_max_l_func */
#include <libc/local/ctype/___mb_cur_max_l_func.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(___mb_cur_max_l_func, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL ___mb_cur_max_l_func)(__locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(___mb_cur_max_l_func))(__locale); })
#endif /* !__CRT_HAVE____mb_cur_max_l_func */
#ifdef __CRT_HAVE__chvalidator
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_chvalidator,(int __ch, int __mask),(__ch,__mask))
#elif defined(__CRT_HAVE__isctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_chvalidator,(int __ch, int __mask),_isctype,(__ch,__mask))
#endif /* ... */
#ifdef __CRT_HAVE__chvalidator_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_chvalidator_l,(__locale_t __locale, int __ch, int __mask),(__locale,__ch,__mask))
#else /* __CRT_HAVE__chvalidator_l */
#include <libc/local/ctype/_chvalidator_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_chvalidator_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _chvalidator_l)(__locale_t __locale, int __ch, int __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_chvalidator_l))(__locale, __ch, __mask); })
#endif /* !__CRT_HAVE__chvalidator_l */
#if !defined(NDEBUG) && (defined(__CRT_HAVE__chvalidator) || defined(__CRT_HAVE__isctype))
#define __chvalidchk(ch, mask) _chvalidator(ch, mask)
#else /* !NDEBUG && (__CRT_HAVE__chvalidator || __CRT_HAVE__isctype) */
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __acrt_locale_get_ctype_array_value)(__UINT16_TYPE__ const *__ct_array,
                                                              int __ch, int __mask) {
	if __likely(__ch >= -1 && __ch <= 255)
		return __ct_array[__ch] & __mask;
	return 0;
}
#define __chvalidchk(ch, mask) __acrt_locale_get_ctype_array_value(__PCTYPE_FUNC, ch, mask)
#endif /* NDEBUG || (!__CRT_HAVE__chvalidator && !__CRT_HAVE__isctype) */
#define _chvalidchk_l(ch, mask, locale) _isctype_l(ch, mask, locale)
#define _ischartype_l(ch, mask, locale) _isctype_l(ch, mask, locale)
#ifndef ___isctype_defined
#define ___isctype_defined
#ifdef __CRT_HAVE__isctype
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isctype,(int __ch, int __mask),(__ch,__mask))
#elif defined(__CRT_HAVE__chvalidator)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,_isctype,(int __ch, int __mask),_chvalidator,(__ch,__mask))
#else /* ... */
#include <libc/local/ctype/_isctype.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_isctype, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL _isctype)(int __ch, int __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_isctype))(__ch, __mask); })
#endif /* !... */
#endif /* !___isctype_defined */
#ifndef ___isctype_l_defined
#define ___isctype_l_defined
#ifdef __CRT_HAVE__isctype_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isctype_l,(int __ch, int __mask, __locale_t __locale),(__ch,__mask,__locale))
#else /* __CRT_HAVE__isctype_l */
#include <libc/local/ctype/_isctype_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_isctype_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isctype_l)(int __ch, int __mask, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_isctype_l))(__ch, __mask, __locale); })
#endif /* !__CRT_HAVE__isctype_l */
#endif /* !___isctype_l_defined */
#if defined(__crt_isalpha_l) && defined(__CRT_HAVE_isalpha_l)
/* >> isalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalpha_l,(int __ch, __locale_t __locale),isalpha_l,{ return __crt_isalpha_l(__ch, __locale); })
#elif defined(__crt_isalpha_l) && defined(__CRT_HAVE__isalpha_l)
/* >> isalpha_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalpha_l,(int __ch, __locale_t __locale),{ return __crt_isalpha_l(__ch, __locale); })
#elif defined(__crt_isalpha_l) && defined(__CRT_HAVE___isalpha_l)
/* >> isalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalpha_l,(int __ch, __locale_t __locale),__isalpha_l,{ return __crt_isalpha_l(__ch, __locale); })
#elif defined(__crt_isalpha_l)
/* >> isalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isalpha_l)(int __ch, __locale_t __locale) { return __crt_isalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isalpha_l)
/* >> isalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalpha_l,(int __ch, __locale_t __locale),isalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isalpha_l)
/* >> isalpha_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalpha_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isalpha_l)
/* >> isalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalpha_l,(int __ch, __locale_t __locale),__isalpha_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isalpha_l.h>
/* >> isalpha_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isalpha_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalpha_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isupper_l) && defined(__CRT_HAVE_isupper_l)
/* >> isupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isupper_l,(int __ch, __locale_t __locale),isupper_l,{ return __crt_isupper_l(__ch, __locale); })
#elif defined(__crt_isupper_l) && defined(__CRT_HAVE__isupper_l)
/* >> isupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isupper_l,(int __ch, __locale_t __locale),{ return __crt_isupper_l(__ch, __locale); })
#elif defined(__crt_isupper_l) && defined(__CRT_HAVE___isupper_l)
/* >> isupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isupper_l,(int __ch, __locale_t __locale),__isupper_l,{ return __crt_isupper_l(__ch, __locale); })
#elif defined(__crt_isupper_l)
/* >> isupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isupper_l)(int __ch, __locale_t __locale) { return __crt_isupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isupper_l)
/* >> isupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isupper_l,(int __ch, __locale_t __locale),isupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isupper_l)
/* >> isupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isupper_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isupper_l)
/* >> isupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isupper_l,(int __ch, __locale_t __locale),__isupper_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isupper_l.h>
/* >> isupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isupper_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isupper_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_islower_l) && defined(__CRT_HAVE_islower_l)
/* >> islower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_islower_l,(int __ch, __locale_t __locale),islower_l,{ return __crt_islower_l(__ch, __locale); })
#elif defined(__crt_islower_l) && defined(__CRT_HAVE__islower_l)
/* >> islower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_islower_l,(int __ch, __locale_t __locale),{ return __crt_islower_l(__ch, __locale); })
#elif defined(__crt_islower_l) && defined(__CRT_HAVE___islower_l)
/* >> islower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_islower_l,(int __ch, __locale_t __locale),__islower_l,{ return __crt_islower_l(__ch, __locale); })
#elif defined(__crt_islower_l)
/* >> islower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _islower_l)(int __ch, __locale_t __locale) { return __crt_islower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_islower_l)
/* >> islower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_islower_l,(int __ch, __locale_t __locale),islower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__islower_l)
/* >> islower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_islower_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___islower_l)
/* >> islower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_islower_l,(int __ch, __locale_t __locale),__islower_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/islower_l.h>
/* >> islower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _islower_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(islower_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isdigit_l) && defined(__CRT_HAVE_isdigit_l)
/* >> isdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isdigit_l,(int __ch, __locale_t __locale),isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l) && defined(__CRT_HAVE__isdigit_l)
/* >> isdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isdigit_l,(int __ch, __locale_t __locale),{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l) && defined(__CRT_HAVE___isdigit_l)
/* >> isdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,{ return __crt_isdigit_l(__ch, __locale); })
#elif defined(__crt_isdigit_l)
/* >> isdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isdigit_l)(int __ch, __locale_t __locale) { return __crt_isdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isdigit_l)
/* >> isdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isdigit_l,(int __ch, __locale_t __locale),isdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isdigit_l)
/* >> isdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isdigit_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isdigit_l)
/* >> isdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isdigit_l,(int __ch, __locale_t __locale),__isdigit_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isdigit_l.h>
/* >> isdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isdigit_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isdigit_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isxdigit_l) && defined(__CRT_HAVE_isxdigit_l)
/* >> isxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isxdigit_l,(int __ch, __locale_t __locale),isxdigit_l,{ return __crt_isxdigit_l(__ch, __locale); })
#elif defined(__crt_isxdigit_l) && defined(__CRT_HAVE__isxdigit_l)
/* >> isxdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isxdigit_l,(int __ch, __locale_t __locale),{ return __crt_isxdigit_l(__ch, __locale); })
#elif defined(__crt_isxdigit_l) && defined(__CRT_HAVE___isxdigit_l)
/* >> isxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isxdigit_l,(int __ch, __locale_t __locale),__isxdigit_l,{ return __crt_isxdigit_l(__ch, __locale); })
#elif defined(__crt_isxdigit_l)
/* >> isxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isxdigit_l)(int __ch, __locale_t __locale) { return __crt_isxdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isxdigit_l)
/* >> isxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isxdigit_l,(int __ch, __locale_t __locale),isxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isxdigit_l)
/* >> isxdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isxdigit_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isxdigit_l)
/* >> isxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isxdigit_l,(int __ch, __locale_t __locale),__isxdigit_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isxdigit_l.h>
/* >> isxdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isxdigit_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isxdigit_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isspace_l) && defined(__CRT_HAVE_isspace_l)
/* >> isspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isspace_l,(int __ch, __locale_t __locale),isspace_l,{ return __crt_isspace_l(__ch, __locale); })
#elif defined(__crt_isspace_l) && defined(__CRT_HAVE__isspace_l)
/* >> isspace_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isspace_l,(int __ch, __locale_t __locale),{ return __crt_isspace_l(__ch, __locale); })
#elif defined(__crt_isspace_l) && defined(__CRT_HAVE___isspace_l)
/* >> isspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isspace_l,(int __ch, __locale_t __locale),__isspace_l,{ return __crt_isspace_l(__ch, __locale); })
#elif defined(__crt_isspace_l)
/* >> isspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isspace_l)(int __ch, __locale_t __locale) { return __crt_isspace_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isspace_l)
/* >> isspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isspace_l,(int __ch, __locale_t __locale),isspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isspace_l)
/* >> isspace_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isspace_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isspace_l)
/* >> isspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isspace_l,(int __ch, __locale_t __locale),__isspace_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isspace_l.h>
/* >> isspace_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isspace_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_ispunct_l) && defined(__CRT_HAVE_ispunct_l)
/* >> ispunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ispunct_l,(int __ch, __locale_t __locale),ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l) && defined(__CRT_HAVE__ispunct_l)
/* >> ispunct_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ispunct_l,(int __ch, __locale_t __locale),{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l) && defined(__CRT_HAVE___ispunct_l)
/* >> ispunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,{ return __crt_ispunct_l(__ch, __locale); })
#elif defined(__crt_ispunct_l)
/* >> ispunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ispunct_l)(int __ch, __locale_t __locale) { return __crt_ispunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_ispunct_l)
/* >> ispunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ispunct_l,(int __ch, __locale_t __locale),ispunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE__ispunct_l)
/* >> ispunct_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ispunct_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___ispunct_l)
/* >> ispunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_ispunct_l,(int __ch, __locale_t __locale),__ispunct_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/ispunct_l.h>
/* >> ispunct_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _ispunct_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ispunct_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isblank_l) && defined(__CRT_HAVE_isblank_l)
/* >> isblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isblank_l,(int __ch, __locale_t __locale),isblank_l,{ return __crt_isblank_l(__ch, __locale); })
#elif defined(__crt_isblank_l) && defined(__CRT_HAVE__isblank_l)
/* >> isblank_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isblank_l,(int __ch, __locale_t __locale),{ return __crt_isblank_l(__ch, __locale); })
#elif defined(__crt_isblank_l) && defined(__CRT_HAVE___isblank_l)
/* >> isblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isblank_l,(int __ch, __locale_t __locale),__isblank_l,{ return __crt_isblank_l(__ch, __locale); })
#elif defined(__crt_isblank_l)
/* >> isblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isblank_l)(int __ch, __locale_t __locale) { return __crt_isblank_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isblank_l)
/* >> isblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isblank_l,(int __ch, __locale_t __locale),isblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isblank_l)
/* >> isblank_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isblank_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isblank_l)
/* >> isblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isblank_l,(int __ch, __locale_t __locale),__isblank_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isblank_l.h>
/* >> isblank_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isblank_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isblank_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isalnum_l) && defined(__CRT_HAVE_isalnum_l)
/* >> isalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalnum_l,(int __ch, __locale_t __locale),isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l) && defined(__CRT_HAVE__isalnum_l)
/* >> isalnum_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalnum_l,(int __ch, __locale_t __locale),{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l) && defined(__CRT_HAVE___isalnum_l)
/* >> isalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,{ return __crt_isalnum_l(__ch, __locale); })
#elif defined(__crt_isalnum_l)
/* >> isalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isalnum_l)(int __ch, __locale_t __locale) { return __crt_isalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isalnum_l)
/* >> isalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalnum_l,(int __ch, __locale_t __locale),isalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isalnum_l)
/* >> isalnum_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalnum_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isalnum_l)
/* >> isalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isalnum_l,(int __ch, __locale_t __locale),__isalnum_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isalnum_l.h>
/* >> isalnum_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isalnum_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isalnum_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isprint_l) && defined(__CRT_HAVE_isprint_l)
/* >> isprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isprint_l,(int __ch, __locale_t __locale),isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l) && defined(__CRT_HAVE__isprint_l)
/* >> isprint_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isprint_l,(int __ch, __locale_t __locale),{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l) && defined(__CRT_HAVE___isprint_l)
/* >> isprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isprint_l,(int __ch, __locale_t __locale),__isprint_l,{ return __crt_isprint_l(__ch, __locale); })
#elif defined(__crt_isprint_l)
/* >> isprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isprint_l)(int __ch, __locale_t __locale) { return __crt_isprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isprint_l)
/* >> isprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isprint_l,(int __ch, __locale_t __locale),isprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isprint_l)
/* >> isprint_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isprint_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isprint_l)
/* >> isprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isprint_l,(int __ch, __locale_t __locale),__isprint_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isprint_l.h>
/* >> isprint_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isprint_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isprint_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_isgraph_l) && defined(__CRT_HAVE_isgraph_l)
/* >> isgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isgraph_l,(int __ch, __locale_t __locale),isgraph_l,{ return __crt_isgraph_l(__ch, __locale); })
#elif defined(__crt_isgraph_l) && defined(__CRT_HAVE__isgraph_l)
/* >> isgraph_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isgraph_l,(int __ch, __locale_t __locale),{ return __crt_isgraph_l(__ch, __locale); })
#elif defined(__crt_isgraph_l) && defined(__CRT_HAVE___isgraph_l)
/* >> isgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isgraph_l,(int __ch, __locale_t __locale),__isgraph_l,{ return __crt_isgraph_l(__ch, __locale); })
#elif defined(__crt_isgraph_l)
/* >> isgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isgraph_l)(int __ch, __locale_t __locale) { return __crt_isgraph_l(__ch, __locale); }
#elif defined(__CRT_HAVE_isgraph_l)
/* >> isgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isgraph_l,(int __ch, __locale_t __locale),isgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE__isgraph_l)
/* >> isgraph_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isgraph_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___isgraph_l)
/* >> isgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isgraph_l,(int __ch, __locale_t __locale),__isgraph_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/isgraph_l.h>
/* >> isgraph_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isgraph_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isgraph_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iscntrl_l) && defined(__CRT_HAVE_iscntrl_l)
/* >> iscntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iscntrl_l,(int __ch, __locale_t __locale),iscntrl_l,{ return __crt_iscntrl_l(__ch, __locale); })
#elif defined(__crt_iscntrl_l) && defined(__CRT_HAVE__iscntrl_l)
/* >> iscntrl_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iscntrl_l,(int __ch, __locale_t __locale),{ return __crt_iscntrl_l(__ch, __locale); })
#elif defined(__crt_iscntrl_l) && defined(__CRT_HAVE___iscntrl_l)
/* >> iscntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iscntrl_l,(int __ch, __locale_t __locale),__iscntrl_l,{ return __crt_iscntrl_l(__ch, __locale); })
#elif defined(__crt_iscntrl_l)
/* >> iscntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iscntrl_l)(int __ch, __locale_t __locale) { return __crt_iscntrl_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iscntrl_l)
/* >> iscntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iscntrl_l,(int __ch, __locale_t __locale),iscntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iscntrl_l)
/* >> iscntrl_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iscntrl_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iscntrl_l)
/* >> iscntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iscntrl_l,(int __ch, __locale_t __locale),__iscntrl_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/iscntrl_l.h>
/* >> iscntrl_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iscntrl_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iscntrl_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_tolower_l) && defined(__CRT_HAVE_tolower_l)
/* >> tolower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_tolower_l,(int __ch, __locale_t __locale),tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l) && defined(__CRT_HAVE__tolower_l)
/* >> tolower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_tolower_l,(int __ch, __locale_t __locale),{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l) && defined(__CRT_HAVE___tolower_l)
/* >> tolower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_tolower_l,(int __ch, __locale_t __locale),__tolower_l,{ return __crt_tolower_l(__ch, __locale); })
#elif defined(__crt_tolower_l)
/* >> tolower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _tolower_l)(int __ch, __locale_t __locale) { return __crt_tolower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_tolower_l)
/* >> tolower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_tolower_l,(int __ch, __locale_t __locale),tolower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__tolower_l)
/* >> tolower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_tolower_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___tolower_l)
/* >> tolower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_tolower_l,(int __ch, __locale_t __locale),__tolower_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/tolower_l.h>
/* >> tolower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _tolower_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_toupper_l) && defined(__CRT_HAVE_toupper_l)
/* >> toupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_toupper_l,(int __ch, __locale_t __locale),toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l) && defined(__CRT_HAVE__toupper_l)
/* >> toupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_toupper_l,(int __ch, __locale_t __locale),{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l) && defined(__CRT_HAVE___toupper_l)
/* >> toupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_toupper_l,(int __ch, __locale_t __locale),__toupper_l,{ return __crt_toupper_l(__ch, __locale); })
#elif defined(__crt_toupper_l)
/* >> toupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _toupper_l)(int __ch, __locale_t __locale) { return __crt_toupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_toupper_l)
/* >> toupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_toupper_l,(int __ch, __locale_t __locale),toupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__toupper_l)
/* >> toupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_toupper_l,(int __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___toupper_l)
/* >> toupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_toupper_l,(int __ch, __locale_t __locale),__toupper_l,(__ch,__locale))
#else /* ... */
#include <libc/local/ctype/toupper_l.h>
/* >> toupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _toupper_l)(int __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(toupper_l))(__ch, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_isascii
/* Returns non-zero if `(C & ~0x7f) == 0' */
__CEIREDIRECT(__ATTR_CONST,int,__NOTHROW,__isascii,(int __c),isascii,{ return (__c & ~0x7f) == 0; })
#elif defined(__CRT_HAVE___isascii)
/* Returns non-zero if `(C & ~0x7f) == 0' */
__CEIDECLARE(__ATTR_CONST,int,__NOTHROW,__isascii,(int __c),{ return (__c & ~0x7f) == 0; })
#else /* ... */
/* Returns non-zero if `(C & ~0x7f) == 0' */
__LOCAL __ATTR_CONST int __NOTHROW(__LIBCCALL __isascii)(int __c) { return (__c & ~0x7f) == 0; }
#endif /* !... */
#ifdef __CRT_HAVE_toascii
/* Re-returns `C & 0x7f' */
__CEIREDIRECT(__ATTR_CONST,int,__NOTHROW,__toascii,(int __c),toascii,{ return __c & 0x7f; })
#elif defined(__CRT_HAVE___toascii)
/* Re-returns `C & 0x7f' */
__CEIDECLARE(__ATTR_CONST,int,__NOTHROW,__toascii,(int __c),{ return __c & 0x7f; })
#else /* ... */
/* Re-returns `C & 0x7f' */
__LOCAL __ATTR_CONST int __NOTHROW(__LIBCCALL __toascii)(int __c) { return __c & 0x7f; }
#endif /* !... */
#ifdef __CRT_HAVE___iscsymf
/* >> issymstrt(3)
 * Test if `ch' can appear at the start of a symbol/keyword/identifier */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__iscsymf,(int __ch),(__ch))
#else /* __CRT_HAVE___iscsymf */
#include <libc/local/ctype/issymstrt.h>
/* >> issymstrt(3)
 * Test if `ch' can appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __iscsymf)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymstrt))(__ch); }
#endif /* !__CRT_HAVE___iscsymf */
#ifdef __CRT_HAVE___iscsym
/* >> issymcont(3)
 * Test if `ch' can appear in the middle of a symbol/keyword/identifier */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__iscsym,(int __ch),(__ch))
#else /* __CRT_HAVE___iscsym */
#include <libc/local/ctype/issymcont.h>
/* >> issymcont(3)
 * Test if `ch' can appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL __iscsym)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(issymcont))(__ch); }
#endif /* !__CRT_HAVE___iscsym */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CCTYPE
#undef _CTYPE_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CCTYPE */
#endif /* !_CTYPE_H */
