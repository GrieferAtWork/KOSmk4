/* HASH CRC-32:0xa23e949b */
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
/* (>) Standard: ISO C95 (ISO/IEC 9899:1990/AMD1:1995) */
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/newlib/libc/include/wctype.h) */
/* (#) Portability: DJGPP         (/include/wctype.h) */
/* (#) Portability: DragonFly BSD (/include/wctype.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/wctype.h) */
/* (#) Portability: FreeBSD       (/include/wctype.h) */
/* (#) Portability: GNU C Library (/wctype/wctype.h) */
/* (#) Portability: GNU Hurd      (/usr/include/wctype.h) */
/* (#) Portability: MSVC          (/include/wctype.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/wctype.h) */
/* (#) Portability: NetBSD        (/include/wctype.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/wctype.h) */
/* (#) Portability: OpenBSD       (/include/wctype.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/wctype.h) */
/* (#) Portability: PDCLib        (/include/wctype.h) */
/* (#) Portability: Windows Kits  (/ucrt/wctype.h) */
/* (#) Portability: diet libc     (/include/wctype.h) */
/* (#) Portability: libc6         (/include/wctype.h) */
/* (#) Portability: mintlib       (/include/wctype.h) */
/* (#) Portability: musl libc     (/include/wctype.h) */
/* (#) Portability: uClibc        (/include/wctype.h) */
#ifndef _WCTYPE_H
#define _WCTYPE_H 1

#ifdef _CXX_STDONLY_CWCTYPE
#ifdef __CXX_SYSTEM_HEADER
#undef _WCTYPE_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "wctype.h" after "cwctype" */
#ifndef __wint_t_defined
#define __wint_t_defined
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
#if defined(__USE_ISOC99) || defined(__USE_XOPEN2K8)
#ifndef __wctrans_t_defined
#define __wctrans_t_defined
__NAMESPACE_STD_USING(wctrans_t)
#endif /* !__wctrans_t_defined */
#endif /* __USE_ISOC99 || __USE_XOPEN2K8 */
__NAMESPACE_STD_USING(iswcntrl)
__NAMESPACE_STD_USING(iswspace)
__NAMESPACE_STD_USING(iswupper)
__NAMESPACE_STD_USING(iswlower)
__NAMESPACE_STD_USING(iswalpha)
__NAMESPACE_STD_USING(iswdigit)
__NAMESPACE_STD_USING(iswxdigit)
__NAMESPACE_STD_USING(iswalnum)
__NAMESPACE_STD_USING(iswpunct)
__NAMESPACE_STD_USING(iswgraph)
__NAMESPACE_STD_USING(iswprint)
__NAMESPACE_STD_USING(towlower)
__NAMESPACE_STD_USING(towupper)
__NAMESPACE_STD_USING(iswblank)
#if !defined(__wctrans_defined) && defined(__std_wctrans_defined)
#define __wctrans_defined
__NAMESPACE_STD_USING(wctrans)
#endif /* !__wctrans_defined && __std_wctrans_defined */
#if !defined(__towctrans_defined) && defined(__std_towctrans_defined)
#define __towctrans_defined
__NAMESPACE_STD_USING(towctrans)
#endif /* !__towctrans_defined && __std_towctrans_defined */
#if defined(__CRT_HAVE_wctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
__NAMESPACE_STD_USING(wctype)
#endif /* __CRT_HAVE_wctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#if defined(__CRT_HAVE_iswctype) || defined(__CRT_HAVE_is_wctype) || defined(__CRT_HAVE___iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
__NAMESPACE_STD_USING(iswctype)
#endif /* __CRT_HAVE_iswctype || __CRT_HAVE_is_wctype || __CRT_HAVE___iswctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#undef _CXX_STDONLY_CWCTYPE
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CWCTYPE */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/byteorder.h>
#include <hybrid/typecore.h>
#include <asm/crt/stdio.h>
#include <bits/crt/wctype.h>
#include <bits/types.h>

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_GLIBC_BLOAT
#include <endian.h>
#endif /* __USE_GLIBC_BLOAT */


#if !defined(WEOF) && defined(__WEOF)
#define WEOF __WEOF
#endif /* !WEOF && __WEOF */

#ifdef __CC__
__SYSDECL_BEGIN

__NAMESPACE_STD_BEGIN
#ifndef __std_wint_t_defined
#define __std_wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
#ifndef __std_wctype_t_defined
#define __std_wctype_t_defined
typedef __wctype_t wctype_t;
#endif /* !__std_wctype_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __wint_t_defined
#define __wint_t_defined
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#ifndef __wctype_t_defined
#define __wctype_t_defined
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#if defined(__USE_ISOC99) || defined(__USE_XOPEN2K8)
#ifndef __std_wctrans_t_defined
#define __std_wctrans_t_defined
__NAMESPACE_STD_BEGIN
typedef __wctrans_t wctrans_t;
__NAMESPACE_STD_END
#endif /* !__std_wctrans_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __wctrans_t_defined
#define __wctrans_t_defined
__NAMESPACE_STD_USING(wctrans_t)
#endif /* !__wctrans_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 || __USE_XOPEN2K8 */


__NAMESPACE_STD_BEGIN
#if defined(__crt_iswcntrl) && defined(__CRT_HAVE_iswcntrl)
/* >> iswcntrl(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswcntrl,(wint_t __wc),{ return __crt_iswcntrl(__wc); })
#elif defined(__crt_iswcntrl)
/* >> iswcntrl(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswcntrl)(wint_t __wc) { return __crt_iswcntrl(__wc); }
#elif __has_builtin(__builtin_iswcntrl) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswcntrl)
/* >> iswcntrl(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswcntrl,(wint_t __wc),{ return __builtin_iswcntrl(__wc); })
#elif defined(__CRT_HAVE_iswcntrl)
/* >> iswcntrl(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswcntrl,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswcntrl.h>
__NAMESPACE_STD_BEGIN
/* >> iswcntrl(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswcntrl, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswcntrl)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl))(__wc); })
#endif /* !... */
#if defined(__crt_iswspace) && defined(__CRT_HAVE_iswspace)
/* >> iswspace(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswspace,(wint_t __wc),{ return __crt_iswspace(__wc); })
#elif defined(__crt_iswspace)
/* >> iswspace(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswspace)(wint_t __wc) { return __crt_iswspace(__wc); }
#elif __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace)
/* >> iswspace(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswspace,(wint_t __wc),{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace)
/* >> iswspace(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswspace,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswspace.h>
__NAMESPACE_STD_BEGIN
/* >> iswspace(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswspace, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswspace)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace))(__wc); })
#endif /* !... */
#if defined(__crt_iswupper) && defined(__CRT_HAVE_iswupper)
/* >> iswupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswupper,(wint_t __wc),{ return __crt_iswupper(__wc); })
#elif defined(__crt_iswupper)
/* >> iswupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswupper)(wint_t __wc) { return __crt_iswupper(__wc); }
#elif __has_builtin(__builtin_iswupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswupper)
/* >> iswupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswupper,(wint_t __wc),{ return __builtin_iswupper(__wc); })
#elif defined(__CRT_HAVE_iswupper)
/* >> iswupper(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswupper,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswupper.h>
__NAMESPACE_STD_BEGIN
/* >> iswupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswupper)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper))(__wc); })
#endif /* !... */
#if defined(__crt_iswlower) && defined(__CRT_HAVE_iswlower)
/* >> iswlower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswlower,(wint_t __wc),{ return __crt_iswlower(__wc); })
#elif defined(__crt_iswlower)
/* >> iswlower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswlower)(wint_t __wc) { return __crt_iswlower(__wc); }
#elif __has_builtin(__builtin_iswlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswlower)
/* >> iswlower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswlower,(wint_t __wc),{ return __builtin_iswlower(__wc); })
#elif defined(__CRT_HAVE_iswlower)
/* >> iswlower(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswlower,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswlower.h>
__NAMESPACE_STD_BEGIN
/* >> iswlower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswlower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswlower)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower))(__wc); })
#endif /* !... */
#if defined(__crt_iswalpha) && defined(__CRT_HAVE_iswalpha)
/* >> iswalpha(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalpha,(wint_t __wc),{ return __crt_iswalpha(__wc); })
#elif defined(__crt_iswalpha)
/* >> iswalpha(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswalpha)(wint_t __wc) { return __crt_iswalpha(__wc); }
#elif __has_builtin(__builtin_iswalpha) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalpha)
/* >> iswalpha(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalpha,(wint_t __wc),{ return __builtin_iswalpha(__wc); })
#elif defined(__CRT_HAVE_iswalpha)
/* >> iswalpha(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalpha,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswalpha.h>
__NAMESPACE_STD_BEGIN
/* >> iswalpha(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalpha, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswalpha)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha))(__wc); })
#endif /* !... */
#if defined(__crt_iswdigit) && defined(__CRT_HAVE_iswdigit)
/* >> iswdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswdigit,(wint_t __wc),{ return __crt_iswdigit(__wc); })
#elif defined(__crt_iswdigit)
/* >> iswdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswdigit)(wint_t __wc) { return __crt_iswdigit(__wc); }
#elif __has_builtin(__builtin_iswdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswdigit)
/* >> iswdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswdigit,(wint_t __wc),{ return __builtin_iswdigit(__wc); })
#elif defined(__CRT_HAVE_iswdigit)
/* >> iswdigit(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswdigit,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswdigit.h>
__NAMESPACE_STD_BEGIN
/* >> iswdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswdigit)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit))(__wc); })
#endif /* !... */
#if defined(__crt_iswxdigit) && defined(__CRT_HAVE_iswxdigit)
/* >> iswxdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswxdigit,(wint_t __wc),{ return __crt_iswxdigit(__wc); })
#elif defined(__crt_iswxdigit)
/* >> iswxdigit(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswxdigit)(wint_t __wc) { return __crt_iswxdigit(__wc); }
#elif __has_builtin(__builtin_iswxdigit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswxdigit)
/* >> iswxdigit(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswxdigit,(wint_t __wc),{ return __builtin_iswxdigit(__wc); })
#elif defined(__CRT_HAVE_iswxdigit)
/* >> iswxdigit(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswxdigit,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswxdigit.h>
__NAMESPACE_STD_BEGIN
/* >> iswxdigit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswxdigit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswxdigit)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit))(__wc); })
#endif /* !... */
#if defined(__crt_iswalnum) && defined(__CRT_HAVE_iswalnum)
/* >> iswalnum(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalnum,(wint_t __wc),{ return __crt_iswalnum(__wc); })
#elif defined(__crt_iswalnum)
/* >> iswalnum(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswalnum)(wint_t __wc) { return __crt_iswalnum(__wc); }
#elif __has_builtin(__builtin_iswalnum) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswalnum)
/* >> iswalnum(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalnum,(wint_t __wc),{ return __builtin_iswalnum(__wc); })
#elif defined(__CRT_HAVE_iswalnum)
/* >> iswalnum(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswalnum,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswalnum.h>
__NAMESPACE_STD_BEGIN
/* >> iswalnum(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalnum, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswalnum)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum))(__wc); })
#endif /* !... */
#if defined(__crt_iswpunct) && defined(__CRT_HAVE_iswpunct)
/* >> iswpunct(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswpunct,(wint_t __wc),{ return __crt_iswpunct(__wc); })
#elif defined(__crt_iswpunct)
/* >> iswpunct(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswpunct)(wint_t __wc) { return __crt_iswpunct(__wc); }
#elif __has_builtin(__builtin_iswpunct) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswpunct)
/* >> iswpunct(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswpunct,(wint_t __wc),{ return __builtin_iswpunct(__wc); })
#elif defined(__CRT_HAVE_iswpunct)
/* >> iswpunct(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswpunct,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswpunct.h>
__NAMESPACE_STD_BEGIN
/* >> iswpunct(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswpunct, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswpunct)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct))(__wc); })
#endif /* !... */
#if defined(__crt_iswgraph) && defined(__CRT_HAVE_iswgraph)
/* >> iswgraph(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswgraph,(wint_t __wc),{ return __crt_iswgraph(__wc); })
#elif defined(__crt_iswgraph)
/* >> iswgraph(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswgraph)(wint_t __wc) { return __crt_iswgraph(__wc); }
#elif __has_builtin(__builtin_iswgraph) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswgraph)
/* >> iswgraph(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswgraph,(wint_t __wc),{ return __builtin_iswgraph(__wc); })
#elif defined(__CRT_HAVE_iswgraph)
/* >> iswgraph(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswgraph,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswgraph.h>
__NAMESPACE_STD_BEGIN
/* >> iswgraph(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswgraph, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswgraph)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph))(__wc); })
#endif /* !... */
#if defined(__crt_iswprint) && defined(__CRT_HAVE_iswprint)
/* >> iswprint(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswprint,(wint_t __wc),{ return __crt_iswprint(__wc); })
#elif defined(__crt_iswprint)
/* >> iswprint(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswprint)(wint_t __wc) { return __crt_iswprint(__wc); }
#elif __has_builtin(__builtin_iswprint) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswprint)
/* >> iswprint(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswprint,(wint_t __wc),{ return __builtin_iswprint(__wc); })
#elif defined(__CRT_HAVE_iswprint)
/* >> iswprint(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswprint,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswprint.h>
__NAMESPACE_STD_BEGIN
/* >> iswprint(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswprint, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswprint)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint))(__wc); })
#endif /* !... */
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower)
/* >> towlower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towlower,(wint_t __wc),{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower)
/* >> towlower(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towlower)(wint_t __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower)
/* >> towlower(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towlower,(wint_t __wc),{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower)
/* >> towlower(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towlower,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/towlower.h>
__NAMESPACE_STD_BEGIN
/* >> towlower(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(towlower, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towlower)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower))(__wc); })
#endif /* !... */
#if defined(__crt_towupper) && defined(__CRT_HAVE_towupper)
/* >> towupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towupper,(wint_t __wc),{ return __crt_towupper(__wc); })
#elif defined(__crt_towupper)
/* >> towupper(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towupper)(wint_t __wc) { return __crt_towupper(__wc); }
#elif __has_builtin(__builtin_towupper) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towupper)
/* >> towupper(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towupper,(wint_t __wc),{ return __builtin_towupper(__wc); })
#elif defined(__CRT_HAVE_towupper)
/* >> towupper(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towupper,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/towupper.h>
__NAMESPACE_STD_BEGIN
/* >> towupper(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(towupper, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towupper)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper))(__wc); })
#endif /* !... */
#ifdef __USE_ISOC99
#if defined(__crt_iswblank) && defined(__CRT_HAVE_iswblank)
/* >> iswblank(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswblank,(wint_t __wc),{ return __crt_iswblank(__wc); })
#elif defined(__crt_iswblank)
/* >> iswblank(3) */
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswblank)(wint_t __wc) { return __crt_iswblank(__wc); }
#elif __has_builtin(__builtin_iswblank) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswblank)
/* >> iswblank(3) */
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswblank,(wint_t __wc),{ return __builtin_iswblank(__wc); })
#elif defined(__CRT_HAVE_iswblank)
/* >> iswblank(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswblank,(wint_t __wc),(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wctype/iswblank.h>
__NAMESPACE_STD_BEGIN
/* >> iswblank(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswblank, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswblank)(wint_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank))(__wc); })
#endif /* !... */
#endif /* __USE_ISOC99 */
#ifdef __USE_ISOC99
#ifndef __std_wctrans_defined
#define __std_wctrans_defined
#ifdef __wctrans_defined
__NAMESPACE_GLB_USING_OR_IMPL(wctrans, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wctrans_t __NOTHROW_NCX(__LIBCCALL wctrans)(char const *__prop) { return :: wctrans(__prop); })
#elif defined(__CRT_HAVE_wctrans)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wctrans_t,__NOTHROW_NCX,wctrans,(char const *__prop),(__prop))
#elif defined(__CRT_KOS)
__NAMESPACE_STD_END
#include <libc/local/wctype/wctrans.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctrans, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wctrans_t __NOTHROW_NCX(__LIBCCALL wctrans)(char const *__prop) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctrans))(__prop); })
#else /* ... */
#undef __std_wctrans_defined
#endif /* !... */
#endif /* !__std_wctrans_defined */
#ifndef __std_towctrans_defined
#define __std_towctrans_defined
#ifdef __towctrans_defined
__NAMESPACE_GLB_USING_OR_IMPL(towctrans, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towctrans)(wint_t __wc, wctrans_t __desc) { return :: towctrans(__wc, __desc); })
#elif defined(__CRT_HAVE_towctrans)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towctrans,(wint_t __wc, wctrans_t __desc),(__wc,__desc))
#elif defined(__CRT_HAVE___towctrans)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW,towctrans,(wint_t __wc, wctrans_t __desc),__towctrans,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_STD_END
#include <libc/local/wctype/towctrans.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(towctrans, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW(__LIBCCALL towctrans)(wint_t __wc, wctrans_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans))(__wc, __desc); })
#else /* ... */
#undef __std_towctrans_defined
#endif /* !... */
#endif /* !__std_towctrans_defined */
#endif /* __USE_ISOC99 */
#ifdef __CRT_HAVE_wctype
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wctype_t,__NOTHROW_NCX,wctype,(char const *__prop),(__prop))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_STD_END
#include <libc/local/wctype/wctype.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctype, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wctype_t __NOTHROW_NCX(__LIBCCALL wctype)(char const *__prop) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctype))(__prop); })
#endif /* ... */
#ifdef __CRT_HAVE_iswctype
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswctype,(__WINT_TYPE__ __wc, __wctype_t __desc),(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswctype,(__WINT_TYPE__ __wc, __wctype_t __desc),is_wctype,(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswctype,(__WINT_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
__NAMESPACE_STD_END
#include <libc/local/wctype/iswctype.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(iswctype, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswctype)(__WINT_TYPE__ __wc, __wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))(__wc, __desc); })
#endif /* ... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(iswcntrl)
__NAMESPACE_STD_USING(iswspace)
__NAMESPACE_STD_USING(iswupper)
__NAMESPACE_STD_USING(iswlower)
__NAMESPACE_STD_USING(iswalpha)
__NAMESPACE_STD_USING(iswdigit)
__NAMESPACE_STD_USING(iswxdigit)
__NAMESPACE_STD_USING(iswalnum)
__NAMESPACE_STD_USING(iswpunct)
__NAMESPACE_STD_USING(iswgraph)
__NAMESPACE_STD_USING(iswprint)
__NAMESPACE_STD_USING(towlower)
__NAMESPACE_STD_USING(towupper)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(iswblank)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifdef __USE_ISOC99
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wctrans_defined) && defined(__std_wctrans_defined)
#define __wctrans_defined
__NAMESPACE_STD_USING(wctrans)
#endif /* !__wctrans_defined && __std_wctrans_defined */
#if !defined(__towctrans_defined) && defined(__std_towctrans_defined)
#define __towctrans_defined
__NAMESPACE_STD_USING(towctrans)
#endif /* !__towctrans_defined && __std_towctrans_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_wctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
__NAMESPACE_STD_USING(wctype)
#endif /* __CRT_HAVE_wctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#if defined(__CRT_HAVE_iswctype) || defined(__CRT_HAVE_is_wctype) || defined(__CRT_HAVE___iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
__NAMESPACE_STD_USING(iswctype)
#endif /* __CRT_HAVE_iswctype || __CRT_HAVE_is_wctype || __CRT_HAVE___iswctype || (__CRT_KOS && __CRT_HAVE___unicode_descriptor) */
#endif /* !__CXX_SYSTEM_HEADER */

#if defined(__USE_KOS) || defined(__USE_DOS)
#ifdef __CRT_HAVE_iswascii
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswascii,(__WINT_TYPE__ __wc),(__wc))
#else /* __CRT_HAVE_iswascii */
#include <libc/local/wctype/iswascii.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswascii, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswascii)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswascii))(__wc); })
#endif /* !__CRT_HAVE_iswascii */
#endif /* __USE_KOS || __USE_DOS */

#ifdef __USE_XOPEN2K8
#if defined(__crt_iswcntrl_l) && defined(__CRT_HAVE_iswcntrl_l)
/* >> iswcntrl_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE__iswcntrl_l)
/* >> iswcntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE___iswcntrl_l)
/* >> iswcntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l)
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswcntrl_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswcntrl_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswcntrl_l)
/* >> iswcntrl_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,(__ch,__locale))
#elif defined(__crt_iswcntrl)
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswcntrl_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswcntrl(__ch); }
#else /* ... */
#include <libc/local/wctype/iswcntrl_l.h>
/* >> iswcntrl_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswcntrl_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswcntrl_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswspace_l) && defined(__CRT_HAVE_iswspace_l)
/* >> iswspace_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE__iswspace_l)
/* >> iswspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE___iswspace_l)
/* >> iswspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l)
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswspace_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswspace_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswspace_l)
/* >> iswspace_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswspace_l,(__ch,__locale))
#elif defined(__crt_iswspace)
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswspace_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswspace(__ch); }
#else /* ... */
#include <libc/local/wctype/iswspace_l.h>
/* >> iswspace_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswspace_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswspace_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswupper_l) && defined(__CRT_HAVE_iswupper_l)
/* >> iswupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE__iswupper_l)
/* >> iswupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE___iswupper_l)
/* >> iswupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l)
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswupper_l)
/* >> iswupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswupper_l,(__ch,__locale))
#elif defined(__crt_iswupper)
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswupper(__ch); }
#else /* ... */
#include <libc/local/wctype/iswupper_l.h>
/* >> iswupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswlower_l) && defined(__CRT_HAVE_iswlower_l)
/* >> iswlower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE__iswlower_l)
/* >> iswlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE___iswlower_l)
/* >> iswlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l)
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswlower_l)
/* >> iswlower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswlower_l,(__ch,__locale))
#elif defined(__crt_iswlower)
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswlower(__ch); }
#else /* ... */
#include <libc/local/wctype/iswlower_l.h>
/* >> iswlower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswlower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswalpha_l) && defined(__CRT_HAVE_iswalpha_l)
/* >> iswalpha_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE__iswalpha_l)
/* >> iswalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE___iswalpha_l)
/* >> iswalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l)
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalpha_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalpha_l)
/* >> iswalpha_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__crt_iswalpha)
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalpha_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalpha(__ch); }
#else /* ... */
#include <libc/local/wctype/iswalpha_l.h>
/* >> iswalpha_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalpha_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalpha_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswdigit_l) && defined(__CRT_HAVE_iswdigit_l)
/* >> iswdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE__iswdigit_l)
/* >> iswdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE___iswdigit_l)
/* >> iswdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l)
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswdigit_l)
/* >> iswdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswdigit_l,(__ch,__locale))
#elif defined(__crt_iswdigit)
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswdigit(__ch); }
#else /* ... */
#include <libc/local/wctype/iswdigit_l.h>
/* >> iswdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswxdigit_l) && defined(__CRT_HAVE_iswxdigit_l)
/* >> iswxdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE__iswxdigit_l)
/* >> iswxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE___iswxdigit_l)
/* >> iswxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l)
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswxdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswxdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswxdigit_l)
/* >> iswxdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,(__ch,__locale))
#elif defined(__crt_iswxdigit)
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswxdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswxdigit(__ch); }
#else /* ... */
#include <libc/local/wctype/iswxdigit_l.h>
/* >> iswxdigit_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswxdigit_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswxdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswalnum_l) && defined(__CRT_HAVE_iswalnum_l)
/* >> iswalnum_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE__iswalnum_l)
/* >> iswalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE___iswalnum_l)
/* >> iswalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l)
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalnum_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalnum_l)
/* >> iswalnum_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__crt_iswalnum)
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalnum_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalnum(__ch); }
#else /* ... */
#include <libc/local/wctype/iswalnum_l.h>
/* >> iswalnum_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswalnum_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswalnum_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswpunct_l) && defined(__CRT_HAVE_iswpunct_l)
/* >> iswpunct_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE__iswpunct_l)
/* >> iswpunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE___iswpunct_l)
/* >> iswpunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l)
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswpunct_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswpunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswpunct_l)
/* >> iswpunct_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswpunct_l,(__ch,__locale))
#elif defined(__crt_iswpunct)
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswpunct_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswpunct(__ch); }
#else /* ... */
#include <libc/local/wctype/iswpunct_l.h>
/* >> iswpunct_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswpunct_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswpunct_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswgraph_l) && defined(__CRT_HAVE_iswgraph_l)
/* >> iswgraph_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE__iswgraph_l)
/* >> iswgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE___iswgraph_l)
/* >> iswgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l)
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswgraph_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswgraph_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswgraph_l)
/* >> iswgraph_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswgraph_l,(__ch,__locale))
#elif defined(__crt_iswgraph)
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswgraph_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswgraph(__ch); }
#else /* ... */
#include <libc/local/wctype/iswgraph_l.h>
/* >> iswgraph_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswgraph_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswgraph_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswprint_l) && defined(__CRT_HAVE_iswprint_l)
/* >> iswprint_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE__iswprint_l)
/* >> iswprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE___iswprint_l)
/* >> iswprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l)
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswprint_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswprint_l)
/* >> iswprint_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswprint_l,(__ch,__locale))
#elif defined(__crt_iswprint)
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswprint_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswprint(__ch); }
#else /* ... */
#include <libc/local/wctype/iswprint_l.h>
/* >> iswprint_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswprint_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswprint_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_iswblank_l) && defined(__CRT_HAVE_iswblank_l)
/* >> iswblank_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE__iswblank_l)
/* >> iswblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE___iswblank_l)
/* >> iswblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l)
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswblank_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswblank_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswblank_l)
/* >> iswblank_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),_iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE___iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswblank_l,(__ch,__locale))
#elif defined(__crt_iswblank)
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswblank_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswblank(__ch); }
#else /* ... */
#include <libc/local/wctype/iswblank_l.h>
/* >> iswblank_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswblank_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswblank_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_towlower_l) && defined(__CRT_HAVE_towlower_l)
/* >> towlower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE__towlower_l)
/* >> towlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE___towlower_l)
/* >> towlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l)
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_towlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towlower_l)
/* >> towlower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__towlower_l)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towlower_l)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__crt_towlower)
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towlower(__ch); }
#else /* ... */
#include <libc/local/wctype/towlower_l.h>
/* >> towlower_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(towlower_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))(__ch, __locale); })
#endif /* !... */
#if defined(__crt_towupper_l) && defined(__CRT_HAVE_towupper_l)
/* >> towupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE__towupper_l)
/* >> towupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE___towupper_l)
/* >> towupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l)
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_towupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towupper_l)
/* >> towupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE__towupper_l)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),_towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE___towupper_l)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__crt_towupper)
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towupper(__ch); }
#else /* ... */
#include <libc/local/wctype/towupper_l.h>
/* >> towupper_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(towupper_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))(__ch, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_iswctype_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype_l,(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale),(__wc,__type,__locale))
#elif defined(__CRT_HAVE__iswctype_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype_l,(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale),_iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE___iswctype_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswctype_l,(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_iswctype) || defined(__CRT_HAVE_is_wctype) || defined(__CRT_HAVE___iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/wctype/iswctype_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(iswctype_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswctype_l)(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype_l))(__wc, __type, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE_wctype_l
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__wctype_t,__NOTHROW_NCX,wctype_l,(char const *__prop, __locale_t __locale),(__prop,__locale))
#elif defined(__CRT_HAVE___wctype_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__wctype_t,__NOTHROW_NCX,wctype_l,(char const *__prop, __locale_t __locale),__wctype_l,(__prop,__locale))
#elif defined(__CRT_HAVE_wctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/wctype/wctype_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctype_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __wctype_t __NOTHROW_NCX(__LIBCCALL wctype_l)(char const *__prop, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctype_l))(__prop, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE_towctrans_l
__CDECLARE(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towctrans_l,(__WINT_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),(__wc,__desc,__locale))
#elif defined(__CRT_HAVE___towctrans_l)
__CREDIRECT(__ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,towctrans_l,(__WINT_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale),__towctrans_l,(__wc,__desc,__locale))
#elif defined(__CRT_HAVE_towctrans) || defined(__CRT_HAVE___towctrans) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/wctype/towctrans_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(towctrans_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL towctrans_l)(__WINT_TYPE__ __wc, __wctrans_t __desc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towctrans_l))(__wc, __desc, __locale); })
#endif /* ... */
#ifdef __CRT_HAVE_wctrans_l
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1),__wctrans_t,__NOTHROW_NCX,wctrans_l,(char const *__prop, __locale_t __locale),(__prop,__locale))
#elif defined(__CRT_HAVE___wctrans_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__wctrans_t,__NOTHROW_NCX,wctrans_l,(char const *__prop, __locale_t __locale),__wctrans_l,(__prop,__locale))
#elif defined(__CRT_HAVE_wctrans) || defined(__CRT_KOS)
#include <libc/local/wctype/wctrans_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wctrans_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __wctrans_t __NOTHROW_NCX(__LIBCCALL wctrans_l)(char const *__prop, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctrans_l))(__prop, __locale); })
#endif /* ... */
#endif /* __USE_XOPEN2K8 */
#ifdef __USE_KOS
#ifdef __CRT_HAVE___iswcsymf
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswsymstrt,(__WINT_TYPE__ __wc),__iswcsymf,(__wc))
#else /* __CRT_HAVE___iswcsymf */
#include <libc/local/wctype/iswsymstrt.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswsymstrt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswsymstrt)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt))(__wc); })
#endif /* !__CRT_HAVE___iswcsymf */
#ifdef __CRT_HAVE___iswcsym
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,iswsymcont,(__WINT_TYPE__ __wc),__iswcsym,(__wc))
#else /* __CRT_HAVE___iswcsym */
#include <libc/local/wctype/iswsymcont.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswsymcont, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL iswsymcont)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont))(__wc); })
#endif /* !__CRT_HAVE___iswcsym */
#ifdef __CRT_HAVE__iswcsymf_l
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswsymstrt_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswcsymf_l,(__wc,__locale))
#else /* __CRT_HAVE__iswcsymf_l */
#include <libc/local/wctype/iswsymstrt_l.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswsymstrt_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswsymstrt_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt_l))(__wc, __locale); })
#endif /* !__CRT_HAVE__iswcsymf_l */
#ifdef __CRT_HAVE__iswcsym_l
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,iswsymcont_l,(__WINT_TYPE__ __wc, __locale_t __locale),_iswcsym_l,(__wc,__locale))
#else /* __CRT_HAVE__iswcsym_l */
#include <libc/local/wctype/iswsymcont_l.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__NAMESPACE_LOCAL_USING_OR_IMPL(iswsymcont_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL iswsymcont_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont_l))(__wc, __locale); })
#endif /* !__CRT_HAVE__iswcsym_l */
#endif /* __USE_KOS */

#ifdef __USE_DOS
#ifndef __wctype_t_defined
#define __wctype_t_defined
__NAMESPACE_STD_USING(wctype_t)
#endif /* !__wctype_t_defined */
#ifndef _WCTYPE_DEFINED
#define _WCTYPE_DEFINED 1
#if defined(__crt_iswalnum_l) && defined(__CRT_HAVE_iswalnum_l)
/* >> iswalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE__iswalnum_l)
/* >> iswalnum_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l) && defined(__CRT_HAVE___iswalnum_l)
/* >> iswalnum_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalnum_l,{ return __crt_iswalnum_l(__ch, __locale); })
#elif defined(__crt_iswalnum_l)
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalnum_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswalnum_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswalnum_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalnum_l)
/* >> iswalnum_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswalnum_l)
/* >> iswalnum_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalnum_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalnum_l,(__ch,__locale))
#elif defined(__crt_iswalnum)
/* >> iswalnum_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalnum_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalnum(__ch); }
#else /* ... */
#include <libc/local/wctype/iswalnum_l.h>
/* >> iswalnum_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalnum_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalnum_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswalpha_l) && defined(__CRT_HAVE_iswalpha_l)
/* >> iswalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE__iswalpha_l)
/* >> iswalpha_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l) && defined(__CRT_HAVE___iswalpha_l)
/* >> iswalpha_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalpha_l,{ return __crt_iswalpha_l(__ch, __locale); })
#elif defined(__crt_iswalpha_l)
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalpha_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswalpha_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswalpha_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswalpha_l)
/* >> iswalpha_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswalpha_l)
/* >> iswalpha_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswalpha_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswalpha_l,(__ch,__locale))
#elif defined(__crt_iswalpha)
/* >> iswalpha_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalpha_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswalpha(__ch); }
#else /* ... */
#include <libc/local/wctype/iswalpha_l.h>
/* >> iswalpha_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswalpha_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswalpha_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswcntrl_l) && defined(__CRT_HAVE_iswcntrl_l)
/* >> iswcntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE__iswcntrl_l)
/* >> iswcntrl_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l) && defined(__CRT_HAVE___iswcntrl_l)
/* >> iswcntrl_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,{ return __crt_iswcntrl_l(__ch, __locale); })
#elif defined(__crt_iswcntrl_l)
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcntrl_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswcntrl_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswcntrl_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswcntrl_l)
/* >> iswcntrl_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswcntrl_l)
/* >> iswcntrl_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcntrl_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswcntrl_l,(__ch,__locale))
#elif defined(__crt_iswcntrl)
/* >> iswcntrl_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcntrl_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswcntrl(__ch); }
#else /* ... */
#include <libc/local/wctype/iswcntrl_l.h>
/* >> iswcntrl_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcntrl_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswcntrl_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswdigit_l) && defined(__CRT_HAVE_iswdigit_l)
/* >> iswdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE__iswdigit_l)
/* >> iswdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l) && defined(__CRT_HAVE___iswdigit_l)
/* >> iswdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswdigit_l,{ return __crt_iswdigit_l(__ch, __locale); })
#elif defined(__crt_iswdigit_l)
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswdigit_l)
/* >> iswdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswdigit_l)
/* >> iswdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswdigit_l,(__ch,__locale))
#elif defined(__crt_iswdigit)
/* >> iswdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswdigit(__ch); }
#else /* ... */
#include <libc/local/wctype/iswdigit_l.h>
/* >> iswdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswdigit_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswgraph_l) && defined(__CRT_HAVE_iswgraph_l)
/* >> iswgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE__iswgraph_l)
/* >> iswgraph_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l) && defined(__CRT_HAVE___iswgraph_l)
/* >> iswgraph_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswgraph_l,{ return __crt_iswgraph_l(__ch, __locale); })
#elif defined(__crt_iswgraph_l)
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswgraph_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswgraph_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswgraph_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswgraph_l)
/* >> iswgraph_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswgraph_l)
/* >> iswgraph_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswgraph_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswgraph_l,(__ch,__locale))
#elif defined(__crt_iswgraph)
/* >> iswgraph_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswgraph_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswgraph(__ch); }
#else /* ... */
#include <libc/local/wctype/iswgraph_l.h>
/* >> iswgraph_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswgraph_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswgraph_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswlower_l) && defined(__CRT_HAVE_iswlower_l)
/* >> iswlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE__iswlower_l)
/* >> iswlower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l) && defined(__CRT_HAVE___iswlower_l)
/* >> iswlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswlower_l,{ return __crt_iswlower_l(__ch, __locale); })
#elif defined(__crt_iswlower_l)
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswlower_l)
/* >> iswlower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswlower_l)
/* >> iswlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswlower_l,(__ch,__locale))
#elif defined(__crt_iswlower)
/* >> iswlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswlower(__ch); }
#else /* ... */
#include <libc/local/wctype/iswlower_l.h>
/* >> iswlower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswlower_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswprint_l) && defined(__CRT_HAVE_iswprint_l)
/* >> iswprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE__iswprint_l)
/* >> iswprint_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l) && defined(__CRT_HAVE___iswprint_l)
/* >> iswprint_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswprint_l,{ return __crt_iswprint_l(__ch, __locale); })
#elif defined(__crt_iswprint_l)
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswprint_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswprint_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswprint_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswprint_l)
/* >> iswprint_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswprint_l)
/* >> iswprint_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswprint_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswprint_l,(__ch,__locale))
#elif defined(__crt_iswprint)
/* >> iswprint_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswprint_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswprint(__ch); }
#else /* ... */
#include <libc/local/wctype/iswprint_l.h>
/* >> iswprint_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswprint_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswprint_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswpunct_l) && defined(__CRT_HAVE_iswpunct_l)
/* >> iswpunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE__iswpunct_l)
/* >> iswpunct_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l) && defined(__CRT_HAVE___iswpunct_l)
/* >> iswpunct_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswpunct_l,{ return __crt_iswpunct_l(__ch, __locale); })
#elif defined(__crt_iswpunct_l)
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswpunct_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswpunct_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswpunct_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswpunct_l)
/* >> iswpunct_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswpunct_l)
/* >> iswpunct_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswpunct_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswpunct_l,(__ch,__locale))
#elif defined(__crt_iswpunct)
/* >> iswpunct_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswpunct_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswpunct(__ch); }
#else /* ... */
#include <libc/local/wctype/iswpunct_l.h>
/* >> iswpunct_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswpunct_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswpunct_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswspace_l) && defined(__CRT_HAVE_iswspace_l)
/* >> iswspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE__iswspace_l)
/* >> iswspace_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l) && defined(__CRT_HAVE___iswspace_l)
/* >> iswspace_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswspace_l,{ return __crt_iswspace_l(__ch, __locale); })
#elif defined(__crt_iswspace_l)
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswspace_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswspace_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswspace_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswspace_l)
/* >> iswspace_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswspace_l)
/* >> iswspace_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswspace_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswspace_l,(__ch,__locale))
#elif defined(__crt_iswspace)
/* >> iswspace_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswspace_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswspace(__ch); }
#else /* ... */
#include <libc/local/wctype/iswspace_l.h>
/* >> iswspace_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswspace_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswspace_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswupper_l) && defined(__CRT_HAVE_iswupper_l)
/* >> iswupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE__iswupper_l)
/* >> iswupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l) && defined(__CRT_HAVE___iswupper_l)
/* >> iswupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswupper_l,{ return __crt_iswupper_l(__ch, __locale); })
#elif defined(__crt_iswupper_l)
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswupper_l)
/* >> iswupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswupper_l)
/* >> iswupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswupper_l,(__ch,__locale))
#elif defined(__crt_iswupper)
/* >> iswupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswupper(__ch); }
#else /* ... */
#include <libc/local/wctype/iswupper_l.h>
/* >> iswupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswupper_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswxdigit_l) && defined(__CRT_HAVE_iswxdigit_l)
/* >> iswxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE__iswxdigit_l)
/* >> iswxdigit_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l) && defined(__CRT_HAVE___iswxdigit_l)
/* >> iswxdigit_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,{ return __crt_iswxdigit_l(__ch, __locale); })
#elif defined(__crt_iswxdigit_l)
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswxdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswxdigit_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswxdigit_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswxdigit_l)
/* >> iswxdigit_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswxdigit_l)
/* >> iswxdigit_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswxdigit_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswxdigit_l,(__ch,__locale))
#elif defined(__crt_iswxdigit)
/* >> iswxdigit_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswxdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswxdigit(__ch); }
#else /* ... */
#include <libc/local/wctype/iswxdigit_l.h>
/* >> iswxdigit_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswxdigit_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswxdigit_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_iswblank_l) && defined(__CRT_HAVE_iswblank_l)
/* >> iswblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE__iswblank_l)
/* >> iswblank_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l) && defined(__CRT_HAVE___iswblank_l)
/* >> iswblank_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswblank_l,{ return __crt_iswblank_l(__ch, __locale); })
#elif defined(__crt_iswblank_l)
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswblank_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_iswblank_l(__ch, __locale); }
#elif defined(__CRT_HAVE_iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),iswblank_l,(__ch,__locale))
#elif defined(__CRT_HAVE__iswblank_l)
/* >> iswblank_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___iswblank_l)
/* >> iswblank_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswblank_l,(__WINT_TYPE__ __ch, __locale_t __locale),__iswblank_l,(__ch,__locale))
#elif defined(__crt_iswblank)
/* >> iswblank_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswblank_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_iswblank(__ch); }
#else /* ... */
#include <libc/local/wctype/iswblank_l.h>
/* >> iswblank_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswblank_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswblank_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_towupper_l) && defined(__CRT_HAVE_towupper_l)
/* >> towupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE__towupper_l)
/* >> towupper_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l) && defined(__CRT_HAVE___towupper_l)
/* >> towupper_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towupper_l,{ return __crt_towupper_l(__ch, __locale); })
#elif defined(__crt_towupper_l)
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_towupper_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towupper_l)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),towupper_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towupper_l)
/* >> towupper_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___towupper_l)
/* >> towupper_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towupper_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towupper_l,(__ch,__locale))
#elif defined(__crt_towupper)
/* >> towupper_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towupper(__ch); }
#else /* ... */
#include <libc/local/wctype/towupper_l.h>
/* >> towupper_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towupper_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towupper_l))(__ch, __locale); }
#endif /* !... */
#if defined(__crt_towlower_l) && defined(__CRT_HAVE_towlower_l)
/* >> towlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE__towlower_l)
/* >> towlower_l(3) */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l) && defined(__CRT_HAVE___towlower_l)
/* >> towlower_l(3) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towlower_l,{ return __crt_towlower_l(__ch, __locale); })
#elif defined(__crt_towlower_l)
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return __crt_towlower_l(__ch, __locale); }
#elif defined(__CRT_HAVE_towlower_l)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),towlower_l,(__ch,__locale))
#elif defined(__CRT_HAVE__towlower_l)
/* >> towlower_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),(__ch,__locale))
#elif defined(__CRT_HAVE___towlower_l)
/* >> towlower_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,_towlower_l,(__WINT_TYPE__ __ch, __locale_t __locale),__towlower_l,(__ch,__locale))
#elif defined(__crt_towlower)
/* >> towlower_l(3) */
__LOCAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { __COMPILER_IMPURE(); (void)__locale; return __crt_towlower(__ch); }
#else /* ... */
#include <libc/local/wctype/towlower_l.h>
/* >> towlower_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __WINT_TYPE__ __NOTHROW_NCX(__LIBCCALL _towlower_l)(__WINT_TYPE__ __ch, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))(__ch, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_iswctype_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswctype_l,(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale),iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE__iswctype_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswctype_l,(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale),(__wc,__type,__locale))
#elif defined(__CRT_HAVE___iswctype_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswctype_l,(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale),__iswctype_l,(__wc,__type,__locale))
#elif defined(__CRT_HAVE_iswctype) || defined(__CRT_HAVE_is_wctype) || defined(__CRT_HAVE___iswctype) || (defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor))
#include <libc/local/wctype/iswctype_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswctype_l)(__WINT_TYPE__ __wc, __wctype_t __type, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype_l))(__wc, __type, __locale); }
#endif /* ... */
#ifdef __CRT_HAVE_iswctype
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,is_wctype,(__WINT_TYPE__ __wc, __wctype_t __desc),iswctype,(__wc,__desc))
#elif defined(__CRT_HAVE_is_wctype)
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,is_wctype,(__WINT_TYPE__ __wc, __wctype_t __desc),(__wc,__desc))
#elif defined(__CRT_HAVE___iswctype)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,is_wctype,(__WINT_TYPE__ __wc, __wctype_t __desc),__iswctype,(__wc,__desc))
#elif defined(__CRT_KOS) && defined(__CRT_HAVE___unicode_descriptor)
#include <libc/local/wctype/iswctype.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL is_wctype)(__WINT_TYPE__ __wc, __wctype_t __desc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswctype))(__wc, __desc); }
#endif /* ... */

#ifdef __CRT_HAVE_isleadbyte
/* >> isleadbyte(3) */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,isleadbyte,(int __wc),(__wc))
#else /* __CRT_HAVE_isleadbyte */
#include <libc/local/wctype/isleadbyte.h>
/* >> isleadbyte(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(isleadbyte, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL isleadbyte)(int __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isleadbyte))(__wc); })
#endif /* !__CRT_HAVE_isleadbyte */
#ifdef __CRT_HAVE__isleadbyte_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_isleadbyte_l,(int __wc, __locale_t __locale),(__wc,__locale))
#else /* __CRT_HAVE__isleadbyte_l */
#include <libc/local/wctype/_isleadbyte_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_isleadbyte_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _isleadbyte_l)(int __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_isleadbyte_l))(__wc, __locale); })
#endif /* !__CRT_HAVE__isleadbyte_l */
#ifdef __CRT_HAVE___iswcsymf
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__iswcsymf,(__WINT_TYPE__ __wc),(__wc))
#else /* __CRT_HAVE___iswcsymf */
#include <libc/local/wctype/iswsymstrt.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __iswcsymf)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt))(__wc); }
#endif /* !__CRT_HAVE___iswcsymf */
#ifdef __CRT_HAVE___iswcsym
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__iswcsym,(__WINT_TYPE__ __wc),(__wc))
#else /* __CRT_HAVE___iswcsym */
#include <libc/local/wctype/iswsymcont.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __iswcsym)(__WINT_TYPE__ __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont))(__wc); }
#endif /* !__CRT_HAVE___iswcsym */
#ifdef __CRT_HAVE__iswcsymf_l
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcsymf_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#else /* __CRT_HAVE__iswcsymf_l */
#include <libc/local/wctype/iswsymstrt_l.h>
/* >> iswsymstrt(3), iswsymstrt_l(3)
 * Check if `wc' may appear at the start of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcsymf_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymstrt_l))(__wc, __locale); }
#endif /* !__CRT_HAVE__iswcsymf_l */
#ifdef __CRT_HAVE__iswcsym_l
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,_iswcsym_l,(__WINT_TYPE__ __wc, __locale_t __locale),(__wc,__locale))
#else /* __CRT_HAVE__iswcsym_l */
#include <libc/local/wctype/iswsymcont_l.h>
/* >> iswsymcont(3), iswsymcont_l(3)
 * Check if `wc' may appear in the middle of a symbol/keyword/identifier */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL _iswcsym_l)(__WINT_TYPE__ __wc, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(iswsymcont_l))(__wc, __locale); }
#endif /* !__CRT_HAVE__iswcsym_l */
#endif /* !_WCTYPE_DEFINED */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_WCTYPE_H)
#include <parts/uchar/wctype.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_WCTYPE_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CWCTYPE
#undef _WCTYPE_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CWCTYPE */
#endif /* !_WCTYPE_H */
