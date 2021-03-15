/* HASH CRC-32:0x9ba4ed45 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: ISO C95 (ISO/IEC 9899:1990/AMD1:1995) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/wchar.h) */
/* (#) Portability: DJGPP         (/include/wchar.h) */
/* (#) Portability: FreeBSD       (/include/wchar.h) */
/* (#) Portability: GNU C Library (/wcsmbs/wchar.h) */
/* (#) Portability: MSVC          (/include/wchar.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/wchar.h) */
/* (#) Portability: NetBSD        (/include/wchar.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/wchar.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/wchar.h) */
/* (#) Portability: diet libc     (/include/wchar.h) */
/* (#) Portability: musl libc     (/include/wchar.h) */
/* (#) Portability: uClibc        (/include/wchar.h) */
#ifndef _WCHAR_H
#define _WCHAR_H 1

#ifdef _CXX_STDONLY_CWCHAR
#ifdef __CXX_SYSTEM_HEADER
#undef _WCHAR_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "wchar.h" after "cwchar" */
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */
#ifndef __tm_defined
#define __tm_defined 1
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
__NAMESPACE_STD_USING(btowc)
__NAMESPACE_STD_USING(wctob)
__NAMESPACE_STD_USING(mbrtowc)
__NAMESPACE_STD_USING(wcrtomb)
__NAMESPACE_STD_USING(mbrlen)
__NAMESPACE_STD_USING(mbsrtowcs)
__NAMESPACE_STD_USING(wcsrtombs)
#if !defined(__wcstol_defined) && defined(__std_wcstol_defined)
#define __wcstol_defined 1
__NAMESPACE_STD_USING(wcstol)
#endif /* !__wcstol_defined && __std_wcstol_defined */
#if !defined(__wcstoul_defined) && defined(__std_wcstoul_defined)
#define __wcstoul_defined 1
__NAMESPACE_STD_USING(wcstoul)
#endif /* !__wcstoul_defined && __std_wcstoul_defined */
__NAMESPACE_STD_USING(mbsinit)
__NAMESPACE_STD_USING(wmemcmp)
__NAMESPACE_STD_USING(wmemcpy)
__NAMESPACE_STD_USING(wmemmove)
__NAMESPACE_STD_USING(wmemset)
#if !defined(__wcscpy_defined) && defined(__std_wcscpy_defined)
#define __wcscpy_defined 1
__NAMESPACE_STD_USING(wcscpy)
#endif /* !__wcscpy_defined && __std_wcscpy_defined */
#if !defined(__wcscat_defined) && defined(__std_wcscat_defined)
#define __wcscat_defined 1
__NAMESPACE_STD_USING(wcscat)
#endif /* !__wcscat_defined && __std_wcscat_defined */
#if !defined(__wcsncat_defined) && defined(__std_wcsncat_defined)
#define __wcsncat_defined 1
__NAMESPACE_STD_USING(wcsncat)
#endif /* !__wcsncat_defined && __std_wcsncat_defined */
#if !defined(__wcsncpy_defined) && defined(__std_wcsncpy_defined)
#define __wcsncpy_defined 1
__NAMESPACE_STD_USING(wcsncpy)
#endif /* !__wcsncpy_defined && __std_wcsncpy_defined */
#if !defined(__wcscmp_defined) && defined(__std_wcscmp_defined)
#define __wcscmp_defined 1
__NAMESPACE_STD_USING(wcscmp)
#endif /* !__wcscmp_defined && __std_wcscmp_defined */
#if !defined(__wcsncmp_defined) && defined(__std_wcsncmp_defined)
#define __wcsncmp_defined 1
__NAMESPACE_STD_USING(wcsncmp)
#endif /* !__wcsncmp_defined && __std_wcsncmp_defined */
#if !defined(__wcscoll_defined) && defined(__std_wcscoll_defined)
#define __wcscoll_defined 1
__NAMESPACE_STD_USING(wcscoll)
#endif /* !__wcscoll_defined && __std_wcscoll_defined */
#if !defined(__wcsxfrm_defined) && defined(__std_wcsxfrm_defined)
#define __wcsxfrm_defined 1
__NAMESPACE_STD_USING(wcsxfrm)
#endif /* !__wcsxfrm_defined && __std_wcsxfrm_defined */
#if !defined(__getwchar_defined) && defined(__std_getwchar_defined)
#define __getwchar_defined 1
__NAMESPACE_STD_USING(getwchar)
#endif /* !__getwchar_defined && __std_getwchar_defined */
#if !defined(__fgetwc_defined) && defined(__std_fgetwc_defined)
#define __fgetwc_defined 1
__NAMESPACE_STD_USING(fgetwc)
#endif /* !__fgetwc_defined && __std_fgetwc_defined */
#if !defined(__getwc_defined) && defined(__std_getwc_defined)
#define __getwc_defined 1
__NAMESPACE_STD_USING(getwc)
#endif /* !__getwc_defined && __std_getwc_defined */
#if !defined(__putwchar_defined) && defined(__std_putwchar_defined)
#define __putwchar_defined 1
__NAMESPACE_STD_USING(putwchar)
#endif /* !__putwchar_defined && __std_putwchar_defined */
#if !defined(__fputwc_defined) && defined(__std_fputwc_defined)
#define __fputwc_defined 1
__NAMESPACE_STD_USING(fputwc)
#endif /* !__fputwc_defined && __std_fputwc_defined */
#if !defined(__putwc_defined) && defined(__std_putwc_defined)
#define __putwc_defined 1
__NAMESPACE_STD_USING(putwc)
#endif /* !__putwc_defined && __std_putwc_defined */
#if !defined(__fgetws_defined) && defined(__std_fgetws_defined)
#define __fgetws_defined 1
__NAMESPACE_STD_USING(fgetws)
#endif /* !__fgetws_defined && __std_fgetws_defined */
#if !defined(__fputws_defined) && defined(__std_fputws_defined)
#define __fputws_defined 1
__NAMESPACE_STD_USING(fputws)
#endif /* !__fputws_defined && __std_fputws_defined */
#if !defined(__ungetwc_defined) && defined(__std_ungetwc_defined)
#define __ungetwc_defined 1
__NAMESPACE_STD_USING(ungetwc)
#endif /* !__ungetwc_defined && __std_ungetwc_defined */
#if !defined(__wcsftime_defined) && defined(__std_wcsftime_defined)
#define __wcsftime_defined 1
__NAMESPACE_STD_USING(wcsftime)
#endif /* !__wcsftime_defined && __std_wcsftime_defined */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
#if !defined(__wcslen_defined) && defined(__std_wcslen_defined)
#define __wcslen_defined 1
__NAMESPACE_STD_USING(wcslen)
#endif /* !__wcslen_defined && __std_wcslen_defined */
#if !defined(__wcsspn_defined) && defined(__std_wcsspn_defined)
#define __wcsspn_defined 1
__NAMESPACE_STD_USING(wcsspn)
#endif /* !__wcsspn_defined && __std_wcsspn_defined */
#if !defined(__wcscspn_defined) && defined(__std_wcscspn_defined)
#define __wcscspn_defined 1
__NAMESPACE_STD_USING(wcscspn)
#endif /* !__wcscspn_defined && __std_wcscspn_defined */
#if !defined(__wcschr_defined) && defined(__std_wcschr_defined)
#define __wcschr_defined 1
__NAMESPACE_STD_USING(wcschr)
#endif /* !__wcschr_defined && __std_wcschr_defined */
#if !defined(__wcsrchr_defined) && defined(__std_wcsrchr_defined)
#define __wcsrchr_defined 1
__NAMESPACE_STD_USING(wcsrchr)
#endif /* !__wcsrchr_defined && __std_wcsrchr_defined */
#if !defined(__wcspbrk_defined) && defined(__std_wcspbrk_defined)
#define __wcspbrk_defined 1
__NAMESPACE_STD_USING(wcspbrk)
#endif /* !__wcspbrk_defined && __std_wcspbrk_defined */
#if !defined(__wcsstr_defined) && defined(__std_wcsstr_defined)
#define __wcsstr_defined 1
__NAMESPACE_STD_USING(wcsstr)
#endif /* !__wcsstr_defined && __std_wcsstr_defined */
__NAMESPACE_STD_USING(wmemchr)
#if !defined(__fwide_defined) && defined(__std_fwide_defined)
#define __fwide_defined 1
__NAMESPACE_STD_USING(fwide)
#endif /* !__fwide_defined && __std_fwide_defined */
#if !defined(__fwprintf_defined) && defined(__std_fwprintf_defined)
#define __fwprintf_defined 1
__NAMESPACE_STD_USING(fwprintf)
#endif /* !__fwprintf_defined && __std_fwprintf_defined */
#if !defined(__vfwprintf_defined) && defined(__std_vfwprintf_defined)
#define __vfwprintf_defined 1
__NAMESPACE_STD_USING(vfwprintf)
#endif /* !__vfwprintf_defined && __std_vfwprintf_defined */
#if !defined(__wprintf_defined) && defined(__std_wprintf_defined)
#define __wprintf_defined 1
__NAMESPACE_STD_USING(wprintf)
#endif /* !__wprintf_defined && __std_wprintf_defined */
#if !defined(__vwprintf_defined) && defined(__std_vwprintf_defined)
#define __vwprintf_defined 1
__NAMESPACE_STD_USING(vwprintf)
#endif /* !__vwprintf_defined && __std_vwprintf_defined */
#if !defined(__fwscanf_defined) && defined(__std_fwscanf_defined)
#define __fwscanf_defined 1
__NAMESPACE_STD_USING(fwscanf)
#endif /* !__fwscanf_defined && __std_fwscanf_defined */
#if !defined(__wscanf_defined) && defined(__std_wscanf_defined)
#define __wscanf_defined 1
__NAMESPACE_STD_USING(wscanf)
#endif /* !__wscanf_defined && __std_wscanf_defined */
#if !defined(__swscanf_defined) && defined(__std_swscanf_defined)
#define __swscanf_defined 1
__NAMESPACE_STD_USING(swscanf)
#endif /* !__swscanf_defined && __std_swscanf_defined */
#if !defined(__vswprintf_defined) && defined(__std_vswprintf_defined)
#define __vswprintf_defined 1
__NAMESPACE_STD_USING(vswprintf)
#endif /* !__vswprintf_defined && __std_vswprintf_defined */
#if !defined(__swprintf_defined) && defined(__std_swprintf_defined)
#define __swprintf_defined 1
__NAMESPACE_STD_USING(swprintf)
#endif /* !__swprintf_defined && __std_swprintf_defined */
#ifndef __NO_FPU
#if !defined(__wcstod_defined) && defined(__std_wcstod_defined)
#define __wcstod_defined 1
__NAMESPACE_STD_USING(wcstod)
#endif /* !__wcstod_defined && __std_wcstod_defined */
#endif /* !__NO_FPU */
#ifndef __NO_FPU
#if !defined(__wcstof_defined) && defined(__std_wcstof_defined)
#define __wcstof_defined 1
__NAMESPACE_STD_USING(wcstof)
#endif /* !__wcstof_defined && __std_wcstof_defined */
#if !defined(__wcstold_defined) && defined(__std_wcstold_defined)
#define __wcstold_defined 1
__NAMESPACE_STD_USING(wcstold)
#endif /* !__wcstold_defined && __std_wcstold_defined */
#endif /* !__NO_FPU */
#if !defined(__wcstoll_defined) && defined(__std_wcstoll_defined)
#define __wcstoll_defined 1
__NAMESPACE_STD_USING(wcstoll)
#endif /* !__wcstoll_defined && __std_wcstoll_defined */
#if !defined(__wcstoull_defined) && defined(__std_wcstoull_defined)
#define __wcstoull_defined 1
__NAMESPACE_STD_USING(wcstoull)
#endif /* !__wcstoull_defined && __std_wcstoull_defined */
#if !defined(__vfwscanf_defined) && defined(__std_vfwscanf_defined)
#define __vfwscanf_defined 1
__NAMESPACE_STD_USING(vfwscanf)
#endif /* !__vfwscanf_defined && __std_vfwscanf_defined */
#if !defined(__vwscanf_defined) && defined(__std_vwscanf_defined)
#define __vwscanf_defined 1
__NAMESPACE_STD_USING(vwscanf)
#endif /* !__vwscanf_defined && __std_vwscanf_defined */
#if !defined(__vswscanf_defined) && defined(__std_vswscanf_defined)
#define __vswscanf_defined 1
__NAMESPACE_STD_USING(vswscanf)
#endif /* !__vswscanf_defined && __std_vswscanf_defined */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
__NAMESPACE_STD_USING(wmempmove)
#undef _CXX_STDONLY_CWCHAR
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CWCHAR */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/limitcore.h> /* __WCHAR_MIN__, __WCHAR_MAX__ */
#include <hybrid/typecore.h>

#include <asm/crt/stdio.h> /* __WEOF */
#include <bits/crt/tm.h>   /* struct tm */
#include <bits/crt/mbstate.h>
#include <kos/anno.h>

#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/types.h>
#include <libc/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */


/* Define `NULL' */
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN__
#define WCHAR_MAX __WCHAR_MAX__
#endif /* !WCHAR_MIN */

#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef struct __mbstate mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* Define 'FILE' */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __tm_defined
#define __tm_defined 1
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_btowc
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btowc,(int __ch),(__ch))
#else /* __CRT_HAVE_btowc */
__NAMESPACE_STD_END
#include <libc/local/wchar/btowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(btowc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL btowc)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); })
#endif /* !__CRT_HAVE_btowc */
#ifdef __CRT_HAVE_wctob
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,wctob,(wint_t __ch),(__ch))
#else /* __CRT_HAVE_wctob */
__NAMESPACE_STD_END
#include <libc/local/wchar/wctob.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctob, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL wctob)(wint_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctob))(__ch); })
#endif /* !__CRT_HAVE_wctob */
#ifdef __CRT_HAVE_mbrtowc
__CDECLARE(,size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc)
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc16) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtoc16,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc32) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(,size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrtowc, __FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL mbrtowc)(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))(__pwc, __str, __maxlen, __mbs); })
#endif /* !... */
#ifdef __CRT_HAVE_wcrtomb
__CDECLARE(,size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs),(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c16rtomb) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(,size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs),c16rtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c32rtomb) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(,size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs),c32rtomb,(__str,__wc,__mbs))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcrtomb, __FORCELOCAL __ATTR_ARTIFICIAL size_t __NOTHROW_NCX(__LIBCCALL wcrtomb)(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, __wc, __mbs); })
#endif /* !... */
#ifdef __CRT_HAVE_mbrlen
__CDECLARE(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen)
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbrlen.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL mbrlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); })
#endif /* !... */
#ifdef __CRT_HAVE_mbsrtowcs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbsrtowcs,(wchar_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),(__dst,__psrc,__dstlen,__mbs))
#else /* __CRT_HAVE_mbsrtowcs */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbsrtowcs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtowcs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL mbsrtowcs)(wchar_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !__CRT_HAVE_mbsrtowcs */
#ifdef __CRT_HAVE_wcsrtombs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsrtombs,(char *__dst, wchar_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),(__dst,__psrc,__dstlen,__mbs))
#else /* __CRT_HAVE_wcsrtombs */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsrtombs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsrtombs)(char *__dst, wchar_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !__CRT_HAVE_wcsrtombs */
#ifndef __std_wcstol_defined
#define __std_wcstol_defined 1
#ifdef __wcstol_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (:: wcstol)(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstol)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstol_defined */
#ifndef __std_wcstoul_defined
#define __std_wcstoul_defined 1
#ifdef __wcstoul_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (:: wcstoul)(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstoul)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstoul.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstoul_defined */
#ifdef __CRT_HAVE_mbsinit
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,mbsinit,(mbstate_t const *__mbs),(__mbs))
#else /* __CRT_HAVE_mbsinit */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbsinit.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsinit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL mbsinit)(mbstate_t const *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsinit))(__mbs); })
#endif /* !__CRT_HAVE_mbsinit */
#ifdef __CRT_HAVE_wmemcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars),(__s1,__s2,__num_chars))
#else /* __CRT_HAVE_wmemcmp */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemcmp.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcmp))(__s1, __s2, __num_chars); })
#endif /* !__CRT_HAVE_wmemcmp */
#ifdef __CRT_HAVE_wmemcpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memcpyw.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memcpyl.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemcpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wmemmove
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memmovew.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memmovel.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemmove.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemmove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))(__dst, __src, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wmemset
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memsetw.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))((void *)__dst, (__UINT16_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memsetl.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))((void *)__dst, (__UINT32_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemset.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))(__dst, __filler, __num_chars); })
#endif /* !... */
#ifndef __std_wcscpy_defined
#define __std_wcscpy_defined 1
#ifdef __wcscpy_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (:: wcscpy)(__buf, __src); })
#elif defined(__CRT_HAVE_wcscpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))(__buf, __src); })
#endif /* !... */
#endif /* !__std_wcscpy_defined */
#ifndef __std_wcscat_defined
#define __std_wcscat_defined 1
#ifdef __wcscat_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (:: wcscat)(__buf, __src); })
#elif defined(__CRT_HAVE_wcscat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))(__buf, __src); })
#endif /* !... */
#endif /* !__std_wcscat_defined */
#ifndef __std_wcsncat_defined
#define __std_wcsncat_defined 1
#ifdef __wcsncat_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (:: wcsncat)(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_wcsncat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsncat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__std_wcsncat_defined */
#ifndef __std_wcsncpy_defined
#define __std_wcsncpy_defined 1
#ifdef __wcsncpy_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (:: wcsncpy)(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_wcsncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsncpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__std_wcsncpy_defined */
#ifndef __std_wcscmp_defined
#define __std_wcscmp_defined 1
#ifdef __wcscmp_defined
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_GLB_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (:: wcscmp)(__s1, __s2); })
#elif defined(__CRT_HAVE_wcscmp)
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscmp.h>
__NAMESPACE_STD_BEGIN
/* >> strcmp(3)
 * Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__std_wcscmp_defined */
#ifndef __std_wcsncmp_defined
#define __std_wcsncmp_defined 1
#ifdef __wcsncmp_defined
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__NAMESPACE_GLB_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return (:: wcsncmp)(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_wcsncmp)
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsncmp.h>
__NAMESPACE_STD_BEGIN
/* >> strncmp(3)
 * Same as `strcmp', but compare at most `maxlen' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__std_wcsncmp_defined */
#ifndef __std_wcscoll_defined
#define __std_wcscoll_defined 1
#ifdef __wcscoll_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (:: wcscoll)(__s1, __s2); })
#elif defined(__CRT_HAVE_wcscoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))(__s1, __s2); })
#endif /* !... */
#endif /* !__std_wcscoll_defined */
#ifndef __std_wcsxfrm_defined
#define __std_wcsxfrm_defined 1
#ifdef __wcsxfrm_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen) { return (:: wcsxfrm)(__dst, __src, __maxlen); })
#elif defined(__CRT_HAVE_wcsxfrm)
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,wcsxfrm,(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen),(__dst,__src,__maxlen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsxfrm.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))(__dst, __src, __maxlen); })
#endif /* !... */
#endif /* !__std_wcsxfrm_defined */
#ifndef __std_getwchar_defined
#define __std_getwchar_defined 1
#ifdef __getwchar_defined
__NAMESPACE_GLB_USING_OR_IMPL(getwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL getwchar)(void) __THROWS(...) { return (:: getwchar)(); })
#elif defined(__CRT_HAVE_getwchar)
__CDECLARE(,wint_t,__THROWING,getwchar,(void),())
#elif defined(__CRT_HAVE__fgetwchar)
__CREDIRECT(,wint_t,__THROWING,getwchar,(void),_fgetwchar,())
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
__NAMESPACE_STD_END
#include <libc/local/wchar/getwchar.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL getwchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); })
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) */
#undef __std_getwchar_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc) */
#endif /* !... */
#endif /* !__std_getwchar_defined */
#ifndef __std_fgetwc_defined
#define __std_fgetwc_defined 1
#ifdef __fgetwc_defined
__NAMESPACE_GLB_USING_OR_IMPL(fgetwc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) wint_t (__LIBCCALL fgetwc)(FILE *__restrict __stream) __THROWS(...) { return (:: fgetwc)(__stream); })
#elif defined(__CRT_HAVE_fgetwc)
__CDECLARE(__ATTR_NONNULL((1)),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getwc)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),getwc,(__stream))
#else /* ... */
#undef __std_fgetwc_defined
#endif /* !... */
#endif /* !__std_fgetwc_defined */
#ifndef __std_getwc_defined
#define __std_getwc_defined 1
#ifdef __CRT_HAVE_fgetwc
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,__THROWING,getwc,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc)
__CDECLARE(__ATTR_NONNULL((1)),wint_t,__THROWING,getwc,(FILE *__restrict __stream),(__stream))
#else /* ... */
#undef __std_getwc_defined
#endif /* !... */
#endif /* !__std_getwc_defined */
#ifndef __std_putwchar_defined
#define __std_putwchar_defined 1
#ifdef __putwchar_defined
__NAMESPACE_GLB_USING_OR_IMPL(putwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL putwchar)(wchar_t __wc) __THROWS(...) { return (:: putwchar)(__wc); })
#elif defined(__CRT_HAVE_putwchar)
__CDECLARE(,wint_t,__THROWING,putwchar,(wchar_t __wc),(__wc))
#elif defined(__CRT_HAVE__fputwchar)
__CREDIRECT(,wint_t,__THROWING,putwchar,(wchar_t __wc),_fputwchar,(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
__NAMESPACE_STD_END
#include <libc/local/wchar/putwchar.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL putwchar)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); })
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fputwc || __CRT_HAVE_putwc) */
#undef __std_putwchar_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) */
#endif /* !... */
#endif /* !__std_putwchar_defined */
#ifndef __std_fputwc_defined
#define __std_fputwc_defined 1
#ifdef __fputwc_defined
__NAMESPACE_GLB_USING_OR_IMPL(fputwc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wint_t (__LIBCCALL fputwc)(wchar_t __wc, FILE *__stream) __THROWS(...) { return (:: fputwc)(__wc, __stream); })
#elif defined(__CRT_HAVE_fputwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),putwc,(__wc,__stream))
#else /* ... */
#undef __std_fputwc_defined
#endif /* !... */
#endif /* !__std_fputwc_defined */
#ifndef __std_putwc_defined
#define __std_putwc_defined 1
#ifdef __CRT_HAVE_fputwc
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),(__wc,__stream))
#else /* ... */
#undef __std_putwc_defined
#endif /* !... */
#endif /* !__std_putwc_defined */
#ifndef __std_fgetws_defined
#define __std_fgetws_defined 1
#ifdef __fgetws_defined
__NAMESPACE_GLB_USING_OR_IMPL(fgetws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) wchar_t *(__LIBCCALL fgetws)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (:: fgetws)(__buf, __bufsize, __stream); })
#elif defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_STD_END
#include <libc/local/wchar/fgetws.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) wchar_t *(__LIBCCALL fgetws)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))(__buf, __bufsize, __stream); })
#else /* ... */
#undef __std_fgetws_defined
#endif /* !... */
#endif /* !__std_fgetws_defined */
#ifndef __std_fputws_defined
#define __std_fputws_defined 1
#ifdef __fputws_defined
__NAMESPACE_GLB_USING_OR_IMPL(fputws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws)(wchar_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (:: fputws)(__str, __stream); })
#elif defined(__CRT_HAVE_fputws_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_fputws)
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),(__str,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
__NAMESPACE_STD_END
#include <libc/local/wchar/fputws.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws)(wchar_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))(__str, __stream); })
#else /* ... */
#undef __std_fputws_defined
#endif /* !... */
#endif /* !__std_fputws_defined */
#ifndef __std_ungetwc_defined
#define __std_ungetwc_defined 1
#ifdef __ungetwc_defined
__NAMESPACE_GLB_USING_OR_IMPL(ungetwc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wint_t __NOTHROW_NCX(__LIBCCALL ungetwc)(wint_t __wc, FILE *__stream) { return (:: ungetwc)(__wc, __stream); })
#elif defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __std_ungetwc_defined
#endif /* !... */
#endif /* !__std_ungetwc_defined */
#ifndef __std_wcsftime_defined
#define __std_wcsftime_defined 1
#ifdef __wcsftime_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcsftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBCCALL wcsftime)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp) { return (:: wcsftime)(__buf, __buflen, __format, __tp); })
#elif defined(__CRT_HAVE_wcsftime)
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,wcsftime,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp),(__buf,__buflen,__format,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsftime.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBCCALL wcsftime)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */
#endif /* !__std_wcsftime_defined */

#if !defined(__USE_DOS) || defined(__USE_ISOC95)
#ifndef __std_wcstok_defined
#define __std_wcstok_defined 1
#ifdef __wcstok_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (:: wcstok)(__str, __delim, __save_ptr); })
#elif defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__str, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__std_wcstok_defined */
#endif /* !__USE_DOS || __USE_ISOC95 */
#ifndef __std_wcslen_defined
#define __std_wcslen_defined 1
#ifdef __wcslen_defined
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__NAMESPACE_GLB_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __str) { return (:: wcslen)(__str); })
#elif defined(__CRT_HAVE_wcslen)
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,wcslen,(wchar_t const *__restrict __str),(__str))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_STD_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](str, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))(__str); })
#endif /* !... */
#endif /* !__std_wcslen_defined */
#ifndef __std_wcsspn_defined
#define __std_wcsspn_defined 1
#ifdef __wcsspn_defined
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_GLB_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (:: wcsspn)(__haystack, __accept); })
#elif defined(__CRT_HAVE_wcsspn)
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsspn,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsspn.h>
__NAMESPACE_STD_BEGIN
/* >> strspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) == NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))(__haystack, __accept); })
#endif /* !... */
#endif /* !__std_wcsspn_defined */
#ifndef __std_wcscspn_defined
#define __std_wcscspn_defined 1
#ifdef __wcscspn_defined
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_GLB_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (:: wcscspn)(__haystack, __reject); })
#elif defined(__CRT_HAVE_wcscspn)
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcscspn,(wchar_t const *__haystack, wchar_t const *__reject),(__haystack,__reject))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscspn.h>
__NAMESPACE_STD_BEGIN
/* >> strcspn(3)
 * Return the offset from `haystack' to the first
 * character for which `strchr(reject, ch) != NULL'.
 * If no such character exists, return `strlen(haystack)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))(__haystack, __reject); })
#endif /* !... */
#endif /* !__std_wcscspn_defined */
#ifndef __std_wcschr_defined
#define __std_wcschr_defined 1
#ifdef __wcschr_defined
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcschr)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (:: wcschr)(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (:: wcschr)(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (:: wcschr)(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcschr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcschr_defined */
#ifndef __std_wcsrchr_defined
#define __std_wcsrchr_defined 1
#ifdef __wcsrchr_defined
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcsrchr)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (:: wcsrchr)(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (:: wcsrchr)(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (:: wcsrchr)(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsrchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strrchr(3)
 * Return the pointer of the last instance of `needle', or `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcsrchr_defined */
#ifndef __std_wcspbrk_defined
#define __std_wcspbrk_defined 1
#ifdef __wcspbrk_defined
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcspbrk)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (:: wcspbrk)(__haystack, __accept); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (:: wcspbrk)(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (:: wcspbrk)(__haystack, __accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcspbrk.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strpbrk(3)
 * Return a pointer to the first character from `haystack' with `strchr(*return, accept) != NULL'
 * If no such character exists, return `NULL' instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcspbrk_defined */
#ifndef __std_wcsstr_defined
#define __std_wcsstr_defined 1
#ifdef __wcsstr_defined
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcsstr)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (:: wcsstr)(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (:: wcsstr)(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (:: wcsstr)(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsstr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcsstr_defined */
#ifdef __CRT_HAVE_wmemchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),wmemchr,(__haystack,__needle,__num_chars))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),wmemchr,(__haystack,__needle,__num_chars))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),(__haystack,__needle,__num_chars))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_memchrw) && __SIZEOF_WCHAR_T__ == 2
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_memchrl) && __SIZEOF_WCHAR_T__ == 4
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memchrw.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))((void const *)__haystack, (__UINT16_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))((void const *)__haystack, (__UINT16_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))((void const *)__haystack, (__UINT16_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memchrl.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))((void const *)__haystack, (__UINT32_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))((void const *)__haystack, (__UINT32_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))((void const *)__haystack, (__UINT32_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
#ifndef __std_fwide_defined
#define __std_fwide_defined 1
#ifdef __fwide_defined
__NAMESPACE_GLB_USING_OR_IMPL(fwide, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fwide)(FILE *__fp, int __mode) { return (:: fwide)(__fp, __mode); })
#elif defined(__CRT_HAVE_fwide)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fwide,(FILE *__fp, int __mode),(__fp,__mode))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/fwide.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fwide, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fwide)(FILE *__fp, int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwide))(__fp, __mode); })
#endif /* !... */
#endif /* !__std_fwide_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 */

#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#ifndef __std_fwprintf_defined
#define __std_fwprintf_defined 1
#ifdef __fwprintf_defined
__NAMESPACE_GLB_USING_OR_IMPL(fwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (:: fwprintf)(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fwprintf)
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf");
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
__NAMESPACE_STD_END
#include <libc/local/wchar/fwprintf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#endif /* !__cplusplus */
#else /* ... */
#undef __std_fwprintf_defined
#endif /* !... */
#endif /* !__std_fwprintf_defined */
#ifndef __std_vfwprintf_defined
#define __std_vfwprintf_defined 1
#ifdef __vfwprintf_defined
__NAMESPACE_GLB_USING_OR_IMPL(vfwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (:: vfwprintf)(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfwprintf)
__CDECLARE(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
__NAMESPACE_STD_END
#include <libc/local/wchar/vfwprintf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, __format, __args); })
#else /* ... */
#undef __std_vfwprintf_defined
#endif /* !... */
#endif /* !__std_vfwprintf_defined */
#ifndef __std_wprintf_defined
#define __std_wprintf_defined 1
#ifdef __wprintf_defined
__NAMESPACE_GLB_USING_OR_IMPL(wprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (:: wprintf)(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_wprintf)
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf");
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
__NAMESPACE_STD_END
#include <libc/local/wchar/wprintf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(wprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define wprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef __std_wprintf_defined
#endif /* !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !... */
#endif /* !__std_wprintf_defined */
#ifndef __std_vwprintf_defined
#define __std_vwprintf_defined 1
#ifdef __vwprintf_defined
__NAMESPACE_GLB_USING_OR_IMPL(vwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (:: vwprintf)(__format, __args); })
#elif defined(__CRT_HAVE_vwprintf)
__CDECLARE(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
__NAMESPACE_STD_END
#include <libc/local/wchar/vwprintf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))(__format, __args); })
#else /* (__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS */
#undef __std_vwprintf_defined
#endif /* (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS */
#endif /* !... */
#endif /* !__std_vwprintf_defined */
#ifndef __std_fwscanf_defined
#define __std_fwscanf_defined 1
#ifdef __fwscanf_defined
__NAMESPACE_GLB_USING_OR_IMPL(fwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (:: fwscanf)(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_fwscanf)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
__NAMESPACE_STD_END
#include <libc/local/wchar/fwscanf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#endif /* !__cplusplus */
#else /* ... */
#undef __std_fwscanf_defined
#endif /* !... */
#endif /* !__std_fwscanf_defined */
#ifndef __std_wscanf_defined
#define __std_wscanf_defined 1
#ifdef __wscanf_defined
__NAMESPACE_GLB_USING_OR_IMPL(wscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (:: wscanf)(__format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_wscanf)
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf");
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
__NAMESPACE_STD_END
#include <libc/local/wchar/wscanf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(wscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define wscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#endif /* !__cplusplus */
#else /* __CRT_HAVE_vwscanf || (__CRT_HAVE_vfwscanf && !__NO_STDSTREAMS) */
#undef __std_wscanf_defined
#endif /* !__CRT_HAVE_vwscanf && (!__CRT_HAVE_vfwscanf || __NO_STDSTREAMS) */
#endif /* !... */
#endif /* !__std_wscanf_defined */
#ifndef __std_swscanf_defined
#define __std_swscanf_defined 1
#ifdef __swscanf_defined
__NAMESPACE_GLB_USING_OR_IMPL(swscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) { return (:: swscanf)(__src, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_swscanf)
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swscanf");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/swscanf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(swscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))(__src, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define swscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#endif /* !__cplusplus */
#endif /* !... */
#endif /* !__std_swscanf_defined */
#ifndef __std_vswprintf_defined
#define __std_vswprintf_defined 1
#ifdef __vswprintf_defined
__NAMESPACE_GLB_USING_OR_IMPL(vswprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (:: vswprintf)(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vswprintf)
__CDECLARE(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswprintf,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/vswprintf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vswprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#endif /* !__std_vswprintf_defined */
#ifndef __std_swprintf_defined
#define __std_swprintf_defined 1
#ifdef __swprintf_defined
__NAMESPACE_GLB_USING_OR_IMPL(swprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) { return (:: swprintf)(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_swprintf)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swprintf");
#elif defined(__CRT_HAVE__swprintf)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/swprintf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(swprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define swprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* !__cplusplus */
#endif /* !... */
#endif /* !__std_swprintf_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

#ifndef __NO_FPU
#ifndef __std_wcstod_defined
#define __std_wcstod_defined 1
#ifdef __wcstod_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (:: wcstod)(__nptr, __endptr); })
#elif defined(__CRT_HAVE_wcstod)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstod.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_wcstod_defined */
#endif /* !__NO_FPU */
#ifdef __USE_ISOC99
#ifndef __NO_FPU
#ifndef __std_wcstof_defined
#define __std_wcstof_defined 1
#ifdef __wcstof_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (:: wcstof)(__nptr, __endptr); })
#elif defined(__CRT_HAVE_wcstof)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_wcstof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_wcstold_defined
#define __std_wcstold_defined 1
#ifdef __wcstold_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (:: wcstold)(__nptr, __endptr); })
#elif defined(__CRT_HAVE_wcstold)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,wcstold,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstold.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_wcstold_defined */
#endif /* !__NO_FPU */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifndef __std_wcstoll_defined
#define __std_wcstoll_defined 1
#ifdef __wcstoll_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (:: wcstoll)(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstoll)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstoll_defined */
#ifndef __std_wcstoull_defined
#define __std_wcstoull_defined 1
#ifdef __wcstoull_defined
__NAMESPACE_GLB_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (:: wcstoull)(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstoull)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstoull.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstoull_defined */
#ifndef __std_vfwscanf_defined
#define __std_vfwscanf_defined 1
#ifdef __vfwscanf_defined
__NAMESPACE_GLB_USING_OR_IMPL(vfwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (:: vfwscanf)(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfwscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#else /* ... */
#undef __std_vfwscanf_defined
#endif /* !... */
#endif /* !__std_vfwscanf_defined */
#ifndef __std_vwscanf_defined
#define __std_vwscanf_defined 1
#ifdef __vwscanf_defined
__NAMESPACE_GLB_USING_OR_IMPL(vwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (:: vwscanf)(__format, __args); })
#elif defined(__CRT_HAVE_vwscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <__crt.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
__NAMESPACE_STD_END
#include <libc/local/wchar/vwscanf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))(__format, __args); })
#else /* __CRT_HAVE_vfwscanf && !__NO_STDSTREAMS */
#undef __std_vwscanf_defined
#endif /* !__CRT_HAVE_vfwscanf || __NO_STDSTREAMS */
#endif /* !... */
#endif /* !__std_vwscanf_defined */
#ifndef __std_vswscanf_defined
#define __std_vswscanf_defined 1
#ifdef __vswscanf_defined
__NAMESPACE_GLB_USING_OR_IMPL(vswscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args) { return (:: vswscanf)(__src, __format, __args); })
#elif defined(__CRT_HAVE_vswscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswscanf,(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args),(__src,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/vswscanf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vswscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))(__src, __format, __args); })
#endif /* !... */
#endif /* !__std_vswscanf_defined */
#endif /* __USE_ISOC99 */
#ifndef __std_wcstok_defined
#define __std_wcstok_defined 1
#ifdef __wcstok_defined
/* Define wcstok() incorrectly, the same way DOS does */
__NAMESPACE_GLB_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim) { return (:: wcstok)(__str, __delim); })
#elif defined(__CRT_HAVE_wcstok) && defined(__CRT_DOS_PRIMARY)
__NAMESPACE_STD_END
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined 1
#ifdef __CRT_HAVE_wcstok_s
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* __CRT_HAVE_wcstok_s */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !__CRT_HAVE_wcstok_s */
#endif /* !__local___localdep_wcstok_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_STD_BEGIN
/* Define wcstok() incorrectly, the same way DOS does */
__CEIDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim),{ static wchar_t *__save_ptr = __NULLPTR; return (__NAMESPACE_LOCAL_SYM __localdep_wcstok)(__str, __delim, &__save_ptr); })
#else /* ... */
__NAMESPACE_STD_END
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !... */
#endif /* !__local___localdep_wcstok_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_STD_BEGIN
/* Define wcstok() incorrectly, the same way DOS does */
__LOCAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim) { static wchar_t *__save_ptr = __NULLPTR; return (__NAMESPACE_LOCAL_SYM __localdep_wcstok)(__str, __delim, &__save_ptr); }
#endif /* !... */
#endif /* !__std_wcstok_defined */
#ifdef __CRT_HAVE_wmempmove
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovew) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovel) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/mempmovew.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))((void *)__dst, (void const *)__src, __num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/mempmovel.h>
__NAMESPACE_STD_BEGIN
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))((void *)__dst, (void const *)__src, __num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmempmove.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempmove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))(__dst, __src, __num_chars); })
#endif /* !... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(btowc)
__NAMESPACE_STD_USING(wctob)
__NAMESPACE_STD_USING(mbrtowc)
__NAMESPACE_STD_USING(wcrtomb)
__NAMESPACE_STD_USING(mbrlen)
__NAMESPACE_STD_USING(mbsrtowcs)
__NAMESPACE_STD_USING(wcsrtombs)
#if !defined(__wcstol_defined) && defined(__std_wcstol_defined)
#define __wcstol_defined 1
__NAMESPACE_STD_USING(wcstol)
#endif /* !__wcstol_defined && __std_wcstol_defined */
#if !defined(__wcstoul_defined) && defined(__std_wcstoul_defined)
#define __wcstoul_defined 1
__NAMESPACE_STD_USING(wcstoul)
#endif /* !__wcstoul_defined && __std_wcstoul_defined */
__NAMESPACE_STD_USING(mbsinit)
__NAMESPACE_STD_USING(wmemcmp)
__NAMESPACE_STD_USING(wmemcpy)
__NAMESPACE_STD_USING(wmemmove)
__NAMESPACE_STD_USING(wmemset)
#if !defined(__wcscpy_defined) && defined(__std_wcscpy_defined)
#define __wcscpy_defined 1
__NAMESPACE_STD_USING(wcscpy)
#endif /* !__wcscpy_defined && __std_wcscpy_defined */
#if !defined(__wcscat_defined) && defined(__std_wcscat_defined)
#define __wcscat_defined 1
__NAMESPACE_STD_USING(wcscat)
#endif /* !__wcscat_defined && __std_wcscat_defined */
#if !defined(__wcsncat_defined) && defined(__std_wcsncat_defined)
#define __wcsncat_defined 1
__NAMESPACE_STD_USING(wcsncat)
#endif /* !__wcsncat_defined && __std_wcsncat_defined */
#if !defined(__wcsncpy_defined) && defined(__std_wcsncpy_defined)
#define __wcsncpy_defined 1
__NAMESPACE_STD_USING(wcsncpy)
#endif /* !__wcsncpy_defined && __std_wcsncpy_defined */
#if !defined(__wcscmp_defined) && defined(__std_wcscmp_defined)
#define __wcscmp_defined 1
__NAMESPACE_STD_USING(wcscmp)
#endif /* !__wcscmp_defined && __std_wcscmp_defined */
#if !defined(__wcsncmp_defined) && defined(__std_wcsncmp_defined)
#define __wcsncmp_defined 1
__NAMESPACE_STD_USING(wcsncmp)
#endif /* !__wcsncmp_defined && __std_wcsncmp_defined */
#if !defined(__wcscoll_defined) && defined(__std_wcscoll_defined)
#define __wcscoll_defined 1
__NAMESPACE_STD_USING(wcscoll)
#endif /* !__wcscoll_defined && __std_wcscoll_defined */
#if !defined(__wcsxfrm_defined) && defined(__std_wcsxfrm_defined)
#define __wcsxfrm_defined 1
__NAMESPACE_STD_USING(wcsxfrm)
#endif /* !__wcsxfrm_defined && __std_wcsxfrm_defined */
#if !defined(__getwchar_defined) && defined(__std_getwchar_defined)
#define __getwchar_defined 1
__NAMESPACE_STD_USING(getwchar)
#endif /* !__getwchar_defined && __std_getwchar_defined */
#if !defined(__fgetwc_defined) && defined(__std_fgetwc_defined)
#define __fgetwc_defined 1
__NAMESPACE_STD_USING(fgetwc)
#endif /* !__fgetwc_defined && __std_fgetwc_defined */
#if !defined(__getwc_defined) && defined(__std_getwc_defined)
#define __getwc_defined 1
__NAMESPACE_STD_USING(getwc)
#endif /* !__getwc_defined && __std_getwc_defined */
#if !defined(__putwchar_defined) && defined(__std_putwchar_defined)
#define __putwchar_defined 1
__NAMESPACE_STD_USING(putwchar)
#endif /* !__putwchar_defined && __std_putwchar_defined */
#if !defined(__fputwc_defined) && defined(__std_fputwc_defined)
#define __fputwc_defined 1
__NAMESPACE_STD_USING(fputwc)
#endif /* !__fputwc_defined && __std_fputwc_defined */
#if !defined(__putwc_defined) && defined(__std_putwc_defined)
#define __putwc_defined 1
__NAMESPACE_STD_USING(putwc)
#endif /* !__putwc_defined && __std_putwc_defined */
#if !defined(__fgetws_defined) && defined(__std_fgetws_defined)
#define __fgetws_defined 1
__NAMESPACE_STD_USING(fgetws)
#endif /* !__fgetws_defined && __std_fgetws_defined */
#if !defined(__fputws_defined) && defined(__std_fputws_defined)
#define __fputws_defined 1
__NAMESPACE_STD_USING(fputws)
#endif /* !__fputws_defined && __std_fputws_defined */
#if !defined(__ungetwc_defined) && defined(__std_ungetwc_defined)
#define __ungetwc_defined 1
__NAMESPACE_STD_USING(ungetwc)
#endif /* !__ungetwc_defined && __std_ungetwc_defined */
#if !defined(__wcsftime_defined) && defined(__std_wcsftime_defined)
#define __wcsftime_defined 1
__NAMESPACE_STD_USING(wcsftime)
#endif /* !__wcsftime_defined && __std_wcsftime_defined */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
#if !defined(__wcslen_defined) && defined(__std_wcslen_defined)
#define __wcslen_defined 1
__NAMESPACE_STD_USING(wcslen)
#endif /* !__wcslen_defined && __std_wcslen_defined */
#if !defined(__wcsspn_defined) && defined(__std_wcsspn_defined)
#define __wcsspn_defined 1
__NAMESPACE_STD_USING(wcsspn)
#endif /* !__wcsspn_defined && __std_wcsspn_defined */
#if !defined(__wcscspn_defined) && defined(__std_wcscspn_defined)
#define __wcscspn_defined 1
__NAMESPACE_STD_USING(wcscspn)
#endif /* !__wcscspn_defined && __std_wcscspn_defined */
#if !defined(__wcschr_defined) && defined(__std_wcschr_defined)
#define __wcschr_defined 1
__NAMESPACE_STD_USING(wcschr)
#endif /* !__wcschr_defined && __std_wcschr_defined */
#if !defined(__wcsrchr_defined) && defined(__std_wcsrchr_defined)
#define __wcsrchr_defined 1
__NAMESPACE_STD_USING(wcsrchr)
#endif /* !__wcsrchr_defined && __std_wcsrchr_defined */
#if !defined(__wcspbrk_defined) && defined(__std_wcspbrk_defined)
#define __wcspbrk_defined 1
__NAMESPACE_STD_USING(wcspbrk)
#endif /* !__wcspbrk_defined && __std_wcspbrk_defined */
#if !defined(__wcsstr_defined) && defined(__std_wcsstr_defined)
#define __wcsstr_defined 1
__NAMESPACE_STD_USING(wcsstr)
#endif /* !__wcsstr_defined && __std_wcsstr_defined */
__NAMESPACE_STD_USING(wmemchr)
#if !defined(__fwide_defined) && defined(__std_fwide_defined)
#define __fwide_defined 1
__NAMESPACE_STD_USING(fwide)
#endif /* !__fwide_defined && __std_fwide_defined */
#if !defined(__fwprintf_defined) && defined(__std_fwprintf_defined)
#define __fwprintf_defined 1
__NAMESPACE_STD_USING(fwprintf)
#endif /* !__fwprintf_defined && __std_fwprintf_defined */
#if !defined(__vfwprintf_defined) && defined(__std_vfwprintf_defined)
#define __vfwprintf_defined 1
__NAMESPACE_STD_USING(vfwprintf)
#endif /* !__vfwprintf_defined && __std_vfwprintf_defined */
#if !defined(__wprintf_defined) && defined(__std_wprintf_defined)
#define __wprintf_defined 1
__NAMESPACE_STD_USING(wprintf)
#endif /* !__wprintf_defined && __std_wprintf_defined */
#if !defined(__vwprintf_defined) && defined(__std_vwprintf_defined)
#define __vwprintf_defined 1
__NAMESPACE_STD_USING(vwprintf)
#endif /* !__vwprintf_defined && __std_vwprintf_defined */
#if !defined(__fwscanf_defined) && defined(__std_fwscanf_defined)
#define __fwscanf_defined 1
__NAMESPACE_STD_USING(fwscanf)
#endif /* !__fwscanf_defined && __std_fwscanf_defined */
#if !defined(__wscanf_defined) && defined(__std_wscanf_defined)
#define __wscanf_defined 1
__NAMESPACE_STD_USING(wscanf)
#endif /* !__wscanf_defined && __std_wscanf_defined */
#if !defined(__swscanf_defined) && defined(__std_swscanf_defined)
#define __swscanf_defined 1
__NAMESPACE_STD_USING(swscanf)
#endif /* !__swscanf_defined && __std_swscanf_defined */
#if !defined(__vswprintf_defined) && defined(__std_vswprintf_defined)
#define __vswprintf_defined 1
__NAMESPACE_STD_USING(vswprintf)
#endif /* !__vswprintf_defined && __std_vswprintf_defined */
#if !defined(__swprintf_defined) && defined(__std_swprintf_defined)
#define __swprintf_defined 1
__NAMESPACE_STD_USING(swprintf)
#endif /* !__swprintf_defined && __std_swprintf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstod_defined) && defined(__std_wcstod_defined)
#define __wcstod_defined 1
__NAMESPACE_STD_USING(wcstod)
#endif /* !__wcstod_defined && __std_wcstod_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstof_defined) && defined(__std_wcstof_defined)
#define __wcstof_defined 1
__NAMESPACE_STD_USING(wcstof)
#endif /* !__wcstof_defined && __std_wcstof_defined */
#if !defined(__wcstold_defined) && defined(__std_wcstold_defined)
#define __wcstold_defined 1
__NAMESPACE_STD_USING(wcstold)
#endif /* !__wcstold_defined && __std_wcstold_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstoll_defined) && defined(__std_wcstoll_defined)
#define __wcstoll_defined 1
__NAMESPACE_STD_USING(wcstoll)
#endif /* !__wcstoll_defined && __std_wcstoll_defined */
#if !defined(__wcstoull_defined) && defined(__std_wcstoull_defined)
#define __wcstoull_defined 1
__NAMESPACE_STD_USING(wcstoull)
#endif /* !__wcstoull_defined && __std_wcstoull_defined */
#if !defined(__vfwscanf_defined) && defined(__std_vfwscanf_defined)
#define __vfwscanf_defined 1
__NAMESPACE_STD_USING(vfwscanf)
#endif /* !__vfwscanf_defined && __std_vfwscanf_defined */
#if !defined(__vwscanf_defined) && defined(__std_vwscanf_defined)
#define __vwscanf_defined 1
__NAMESPACE_STD_USING(vwscanf)
#endif /* !__vwscanf_defined && __std_vwscanf_defined */
#if !defined(__vswscanf_defined) && defined(__std_vswscanf_defined)
#define __vswscanf_defined 1
__NAMESPACE_STD_USING(vswscanf)
#endif /* !__vswscanf_defined && __std_vswscanf_defined */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_mbrlen
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen)
__CDECLARE(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),(__str,__maxlen,__mbs))
#else /* ... */
#include <libc/local/wchar/mbrlen.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __mbrlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); }
#endif /* !... */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wcscasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsxfrm_l
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcpcpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcpcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src),(__dst,__src))
#else /* __CRT_HAVE_wcpcpy */
#include <libc/local/wchar/wcpcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcpcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcpcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcpcpy))(__dst, __src); })
#endif /* !__CRT_HAVE_wcpcpy */
#ifdef __CRT_HAVE_wcpncpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcpncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* __CRT_HAVE_wcpncpy */
#include <libc/local/wchar/wcpncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcpncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcpncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcpncpy))(__buf, __src, __buflen); })
#endif /* !__CRT_HAVE_wcpncpy */
__CDECLARE_OPT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtowcs,(wchar_t *__dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __len, struct __mbstate *__mbs),(__dst,__psrc,__nmc,__len,__mbs))
__CDECLARE_OPT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnrtombs,(char *__dst, wchar_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __len, struct __mbstate *__mbs),(__dst,__psrc,__nwc,__len,__mbs))
__CDECLARE_OPT(,__FILE *,__NOTHROW_NCX,open_wmemstream,(wchar_t **__bufloc, __SIZE_TYPE__ *__sizeloc),(__bufloc,__sizeloc))
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#ifndef __wcsnlen_defined
#define __wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
#include <libc/local/wchar/wcsnlen.h>
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnlen */
#endif /* !__wcsnlen_defined */
#ifndef __wcsdup_defined
#define __wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); })
#else /* ... */
#undef __wcsdup_defined
#endif /* !... */
#endif /* !__wcsdup_defined */
#endif /* __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_wcwidth
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,wcwidth,(wchar_t __ch),(__ch))
#else /* __CRT_HAVE_wcwidth */
#include <libc/local/wchar/wcwidth.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcwidth, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL wcwidth)(wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))(__ch); })
#endif /* !__CRT_HAVE_wcwidth */
#ifdef __CRT_HAVE_wcswidth
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wcswidth,(wchar_t const *__restrict __str, __SIZE_TYPE__ __num_chars),(__str,__num_chars))
#else /* __CRT_HAVE_wcswidth */
#include <libc/local/wchar/wcswidth.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcswidth, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wcswidth)(wchar_t const *__restrict __str, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcswidth))(__str, __num_chars); })
#endif /* !__CRT_HAVE_wcswidth */
#endif /* __USE_XOPEN */

#if defined(__USE_XOPEN) || defined(__USE_DOS)
#ifndef __wcswcs_defined
#define __wcswcs_defined 1
#ifdef __CRT_HAVE_wcsstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strstr(3)
 * Search for a given `needle' appearing as a sub-string within `haystack'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcswcs_defined */
#endif /* __USE_XOPEN || __USE_DOS */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_wcschrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschrnul,(wchar_t *__restrict __haystack, wchar_t __needle),wcschrnul,(__haystack,__needle))
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschrnul,(wchar_t const *__haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcschrnul */
#include <libc/local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); }
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t const *__haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcschrnul */
#ifdef __CRT_HAVE_wmempcpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/string/mempcpyw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))((void *)__dst, (void const *)__src, __num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/string/mempcpyl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))((void *)__dst, (void const *)__src, __num_chars); }
#else /* ... */
#include <libc/local/wchar/wmempcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(wmempmove)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_wcstol_l
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoul_l
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoul_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoll
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoq)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstoull
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstoull.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstouq)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstoll_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoull_l
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoull_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_wcstof_l
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL wcstof_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstod_l
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL wcstod_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_wcstold_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_getwchar_unlocked
__CDECLARE(,__WINT_TYPE__,__THROWING,getwchar_unlocked,(void),())
#else /* __CRT_HAVE_getwchar_unlocked */
#include <__crt.h>
#if (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/getwchar_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT_TYPE__ (__LIBCCALL getwchar_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); })
#endif /* (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE__fgetwc_nolock) && !__NO_STDSTREAMS */
#endif /* !__CRT_HAVE_getwchar_unlocked */
#ifdef __CRT_HAVE_putwchar_unlocked
__CDECLARE(,__WINT_TYPE__,__THROWING,putwchar_unlocked,(wchar_t __wc),(__wc))
#else /* __CRT_HAVE_putwchar_unlocked */
#include <__crt.h>
#if (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/putwchar_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT_TYPE__ (__LIBCCALL putwchar_unlocked)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))(__wc); })
#endif /* (__CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && !__NO_STDSTREAMS */
#endif /* !__CRT_HAVE_putwchar_unlocked */
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fgetwc_unlocked
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fputwc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fgetws_unlocked
__CDECLARE(__ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws)
__CREDIRECT(__ATTR_NONNULL((1, 3)),wchar_t *,__THROWING,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/wchar/fgetws_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) wchar_t *(__LIBCCALL fgetws_unlocked)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))(__buf, __bufsize, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fputws_unlocked
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws_unlocked,(wchar_t const *__restrict __str, __FILE *__restrict __stream),(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,fputws_unlocked,(wchar_t const *__restrict __str, __FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#include <libc/local/wchar/fputws_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws_unlocked)(wchar_t const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))(__str, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_wcsftime_l
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#else /* ... */
#include <libc/local/wchar/wcsftime_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsftime_l)(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_GNU */




#ifdef __USE_KOS

/* KOS FILE extension functions. */

#if defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked)
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/file_wprinter.h>
/* >> file_wprinter(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_wprinter, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBCCALL file_wprinter)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, __data, __datalen); })
#endif /* ... */
#ifdef __CRT_HAVE_file_wprinter_unlocked
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_wprinter_unlocked,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__THROWING,file_wprinter_unlocked,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#include <libc/local/wchar/file_wprinter_unlocked.h>
/* >> file_wprinter_unlocked(3)
 * Same as `file_wprinter()', but performs I/O without acquiring a lock to `(FILE *)arg' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_wprinter_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBCCALL file_wprinter_unlocked)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, __data, __datalen); })
#endif /* ... */
#ifdef __CRT_HAVE_ungetwc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_vfwprintf_unlocked
__CDECLARE(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#include <libc/local/wchar/vfwprintf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_fwprintf_unlocked
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#include <libc/local/wchar/fwprintf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fwprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fwprintf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_wprintf_unlocked
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf_unlocked");
#else /* __CRT_HAVE_wprintf_unlocked */
#include <__crt.h>
#if defined(__CRT_HAVE_vwprintf_unlocked) || ((defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/wprintf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(wprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define wprintf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))
#endif /* !__cplusplus */
#endif /* __CRT_HAVE_vwprintf_unlocked || ((__CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && !__NO_STDSTREAMS) */
#endif /* !__CRT_HAVE_wprintf_unlocked */
#ifdef __CRT_HAVE_vwprintf_unlocked
__CDECLARE(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE_vwprintf_unlocked */
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/vwprintf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf_unlocked)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))(__format, __args); })
#endif /* (__CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE__fputwc_nolock) && !__NO_STDSTREAMS */
#endif /* !__CRT_HAVE_vwprintf_unlocked */
#ifdef __CRT_HAVE_vfwscanf_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* ... */
#ifdef __CRT_HAVE_vwscanf_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/vwscanf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf_unlocked)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))(__format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_fwscanf_unlocked
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)
#include <libc/local/wchar/fwscanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(fwscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define fwscanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */
#ifdef __CRT_HAVE_wscanf_unlocked
__LIBC __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf_unlocked");
#elif defined(__CRT_HAVE_vwscanf_unlocked) || ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/wscanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(wscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_SCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define wscanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))
#endif /* !__cplusplus */
#endif /* ... */




#ifdef __CRT_HAVE_wcsend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `str+wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsend,(wchar_t *__restrict __str),wcsend,(__str))
/* Same as `str+wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsend,(wchar_t const *__restrict __str),wcsend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `str+wcslen(str)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsend,(wchar_t const *__restrict __str),(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsend */
#include <libc/local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `str+wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__str); }
/* Same as `str+wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `str+wcslen(str)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__str); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsend */
#ifdef __CRT_HAVE_wcsnend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `str+wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnend,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
/* Same as `str+wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnend,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `str+wcsnlen(str, max_chars)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnend,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnend */
#include <libc/local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `str+wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__str, __maxlen); }
/* Same as `str+wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `str+wcsnlen(str, max_chars)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__str, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnend */
#ifdef __CRT_HAVE_wcsto32_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcsto32_r */
#include <libc/local/wchar/wcsto32_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcsto32_r */
#ifdef __CRT_HAVE_wcstou32_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcstou32_r */
#include <libc/local/wchar/wcstou32_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcstou32_r */
#ifdef __CRT_HAVE_wcsto32
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcsto32.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstou32
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstou32.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))(__nptr, __endptr, __base); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_wcsto64_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcsto64_r */
#include <libc/local/wchar/wcsto64_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcsto64_r */
#ifdef __CRT_HAVE_wcstou64_r
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcstou64_r */
#include <libc/local/wchar/wcstou64_r.h>
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcstou64_r */
#ifdef __CRT_HAVE_wcstou64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstou64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))(__nptr, __endptr, __base); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsto64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcsto64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/wchar/wcsto32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/wchar/wcsto64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstol_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/wchar/wcstou32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/wchar/wcstou64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstoul_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#ifdef __LONGLONG
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/wchar/wcsto64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/wchar/wcsto32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstoll_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/wchar/wcstou64_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/wchar/wcstou32_r.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstoull_r.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#endif /* __LONGLONG */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wcsto32_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcsto32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstou32_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstou32_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_wcsto64_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcsto64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstou64_l
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l)
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstou64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_XOPEN2K8 */

#ifdef __CRT_HAVE_wcsncoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsnrev
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrev,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnrev */
#include <libc/local/wchar/wcsnrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrev)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnrev */
#ifdef __CRT_HAVE_wcsnlwr
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnlwr,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnlwr */
#include <libc/local/wchar/wcsnlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnlwr)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlwr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnlwr */
#ifdef __CRT_HAVE_wcsnupr
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnupr,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnupr */
#include <libc/local/wchar/wcsnupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnupr)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnupr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnupr */
#ifdef __CRT_HAVE_wcscasestr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t *__haystack, wchar_t *__needle),wcscasestr,(__haystack,__needle))
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcscasestr */
#include <libc/local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); }
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> strcasestr(3)
 * Same as `strstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcscasestr */
#ifdef __CRT_HAVE_wcspcpy
/* Same as wcscpy, but return a pointer after the last written character */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspcpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* __CRT_HAVE_wcspcpy */
#include <libc/local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspcpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))(__buf, __src); })
#endif /* !__CRT_HAVE_wcspcpy */
#ifdef __CRT_HAVE_wcspncpy
/* Same as wcsncpy, but return a pointer after the last written character */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* __CRT_HAVE_wcspncpy */
#include <libc/local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))(__buf, __src, __buflen); })
#endif /* !__CRT_HAVE_wcspncpy */
#ifdef __CRT_HAVE_wmempset
/* Same as wmemset, but return a pointer after the last written character */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw) && __SIZEOF_WCHAR_T__ == 2
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && __SIZEOF_WCHAR_T__ == 4
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/string/mempsetw.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))((void *)__dst, (__UINT16_TYPE__)__filler, __num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/string/mempsetl.h>
/* Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))((void *)__dst, (__UINT32_TYPE__)__filler, __num_chars); }
#else /* ... */
#include <libc/local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))(__dst, __filler, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsnchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchr,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `max_chars' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnchr */
#include <libc/local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); }
/* Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcschr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnchr */
#ifdef __CRT_HAVE_wcsnrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchr,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnrchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnrchr */
#include <libc/local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnrchr */
#ifdef __CRT_HAVE_wcssep
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcssep,(wchar_t **__restrict __stringp, wchar_t const *__restrict __delim),(__stringp,__delim))
#else /* __CRT_HAVE_wcssep */
#include <libc/local/wchar/wcssep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcssep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcssep)(wchar_t **__restrict __stringp, wchar_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))(__stringp, __delim); })
#endif /* !__CRT_HAVE_wcssep */
#ifdef __CRT_HAVE_wcsfry
/* >> strfry(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsfry,(wchar_t *__restrict __str),(__str))
#else /* __CRT_HAVE_wcsfry */
#include <libc/local/wchar/wcsfry.h>
/* >> strfry(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsfry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsfry)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))(__str); })
#endif /* !__CRT_HAVE_wcsfry */
#ifdef __CRT_HAVE_wcsndup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsndup,(wchar_t const *__restrict __str, __SIZE_TYPE__ __max_chars),(__str,__max_chars))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsndup)(wchar_t const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))(__str, __max_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_wcsrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchrnul,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchrnul,(__haystack,__needle))
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsrchrnul */
#include <libc/local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); }
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsrchrnul */
#ifdef __CRT_HAVE_wcsnchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchrnul,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnchrnul */
#include <libc/local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnchrnul */
#ifdef __CRT_HAVE_wcsnrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnrchrnul */
#include <libc/local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnrchrnul */
#ifdef __CRT_HAVE_wcsoff
/* Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsoff,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* __CRT_HAVE_wcsoff */
#include <libc/local/wchar/wcsoff.h>
/* Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsoff)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_wcsoff */
#ifdef __CRT_HAVE_wcsroff
/* Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsroff,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* __CRT_HAVE_wcsroff */
#include <libc/local/wchar/wcsroff.h>
/* Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsroff)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_wcsroff */
#ifdef __CRT_HAVE_wcsnoff
/* Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnoff,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_wcsnoff */
#include <libc/local/wchar/wcsnoff.h>
/* Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnoff)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_wcsnoff */
#ifdef __CRT_HAVE_wcsnroff
/* Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnroff,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_wcsnroff */
#include <libc/local/wchar/wcsnroff.h>
/* Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnroff)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_wcsnroff */
#ifdef __CRT_HAVE_fuzzy_wmemcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpw) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpl) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/string/fuzzy_memcmpw.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/string/fuzzy_memcmpl.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#else /* ... */
#include <libc/local/wchar/fuzzy_wmemcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_fuzzy_wcscmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_fuzzy_wcscmp */
#include <libc/local/wchar/fuzzy_wcscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))(__s1, __s2); })
#endif /* !__CRT_HAVE_fuzzy_wcscmp */
#ifdef __CRT_HAVE_fuzzy_wcsncmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* __CRT_HAVE_fuzzy_wcsncmp */
#include <libc/local/wchar/fuzzy_wcsncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* !__CRT_HAVE_fuzzy_wcsncmp */
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcasecmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_wmemcasecmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcasecmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wmemcasecmp */
#ifdef __CRT_HAVE_fuzzy_wcscasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_fuzzy_wcscasecmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcscasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscasecmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcscasecmp */
#ifdef __CRT_HAVE_fuzzy_wcsncasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncasecmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* __CRT_HAVE_fuzzy_wcsncasecmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcsncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncasecmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcsncasecmp */
#ifdef __CRT_HAVE_wildwcscmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildwcscmp,(wchar_t const *__pattern, wchar_t const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildwcscmp */
#include <libc/local/wchar/wildwcscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildwcscmp)(wchar_t const *__pattern, wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildwcscmp */
#ifdef __CRT_HAVE_wildwcscasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildwcscasecmp,(wchar_t const *__pattern, wchar_t const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildwcscasecmp */
#include <libc/local/wchar/wildwcscasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildwcscasecmp)(wchar_t const *__pattern, wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildwcscasecmp */
#ifdef __CRT_HAVE_wcsverscmp
/* >> strverscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsverscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_wcsverscmp */
#include <libc/local/wchar/wcsverscmp.h>
/* >> strverscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsverscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsverscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))(__s1, __s2); })
#endif /* !__CRT_HAVE_wcsverscmp */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wcsncoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcslwr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcslwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsupr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcsupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsnlwr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnlwr_l,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_wcsnlwr_l */
#include <libc/local/wchar/wcsnlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnlwr_l)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlwr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_wcsnlwr_l */
#ifdef __CRT_HAVE_wcsnupr_l
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnupr_l,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_wcsnupr_l */
#include <libc/local/wchar/wcsnupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnupr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnupr_l)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnupr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_wcsnupr_l */
#ifdef __CRT_HAVE_wcscasestr_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr_l,(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale),(__haystack,__needle,__locale))
#else /* __CRT_HAVE_wcscasestr_l */
#include <libc/local/wchar/wcscasestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr_l)(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))(__haystack, __needle, __locale); })
#endif /* !__CRT_HAVE_wcscasestr_l */
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcasecmp_l,(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* __CRT_HAVE_fuzzy_wmemcasecmp_l */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcasecmp_l)(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wmemcasecmp_l */
#ifdef __CRT_HAVE_fuzzy_wcscasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* __CRT_HAVE_fuzzy_wcscasecmp_l */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcscasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))(__s1, __s2, __locale); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp_l || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcscasecmp_l */
#ifdef __CRT_HAVE_fuzzy_wcsncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncasecmp_l,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#else /* __CRT_HAVE_fuzzy_wcsncasecmp_l */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcsncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncasecmp_l)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp_l || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcsncasecmp_l */
#ifdef __CRT_HAVE_wildwcscasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildwcscasecmp_l,(wchar_t const *__pattern, wchar_t const *__string, __locale_t __locale),(__pattern,__string,__locale))
#else /* __CRT_HAVE_wildwcscasecmp_l */
#include <libc/local/wchar/wildwcscasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildwcscasecmp_l)(wchar_t const *__pattern, wchar_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))(__pattern, __string, __locale); })
#endif /* !__CRT_HAVE_wildwcscasecmp_l */
#endif /* __USE_XOPEN2K8 */
#endif /* __USE_KOS */

#ifdef __USE_BSD
#if !defined(__fgetwln_defined) && defined(__CRT_HAVE_fgetwln)
#define __fgetwln_defined 1
/* >> fgetwln(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,fgetwln,(FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),(__fp,__lenp))
#endif /* !__fgetwln_defined && __CRT_HAVE_fgetwln */
#ifndef __wcslcat_defined
#define __wcslcat_defined 1
#ifdef __CRT_HAVE_wcslcat
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,wcslcat,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_wcslcat */
#include <libc/local/wchar/wcslcat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslcat)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcat))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_wcslcat */
#endif /* !__wcslcat_defined */
#ifndef __wcslcpy_defined
#define __wcslcpy_defined 1
#ifdef __CRT_HAVE_wcslcpy
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,wcslcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_wcslcpy */
#include <libc/local/wchar/wcslcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcpy))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_wcslcpy */
#endif /* !__wcslcpy_defined */
#endif /* __USE_BSD */





#ifdef __USE_DOS
#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED 1
#ifndef ___wcsdup_defined
#define ___wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); }
#else /* ... */
#undef ___wcsdup_defined
#endif /* !... */
#endif /* !___wcsdup_defined */

#ifdef __USE_DOS_SLIB
#ifndef __wcscat_s_defined
#define __wcscat_s_defined 1
#ifdef __CRT_HAVE_wcscat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscat_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_wcscat_s */
#include <libc/local/wchar/wcscat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscat_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_wcscat_s */
#endif /* !__wcscat_s_defined */
#ifndef __wcscpy_s_defined
#define __wcscpy_s_defined 1
#ifdef __CRT_HAVE_wcscpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* __CRT_HAVE_wcscpy_s */
#include <libc/local/wchar/wcscpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy_s))(__dst, __dstsize, __src); })
#endif /* !__CRT_HAVE_wcscpy_s */
#endif /* !__wcscpy_s_defined */
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcsnlen_defined
#define __local___localdep_wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnlen,(__str,__maxlen))
#else /* __CRT_HAVE_wcsnlen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `max_chars' characters (Same as `memlen[...](str, '\0', max_chars)´) */
#define __localdep_wcsnlen __LIBC_LOCAL_NAME(wcsnlen)
#endif /* !__CRT_HAVE_wcsnlen */
#endif /* !__local___localdep_wcsnlen_defined */
__NAMESPACE_LOCAL_END
__LOCAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen) { return __str ? (__NAMESPACE_LOCAL_SYM __localdep_wcsnlen)(__str, __maxlen) : 0; }
#endif /* !__wcsnlen_s_defined */
#ifndef __wcsncat_s_defined
#define __wcsncat_s_defined 1
#ifdef __CRT_HAVE_wcsncat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncat_s,(wchar_t *__dst, rsize_t __dstsize, const wchar_t *__src, rsize_t __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_wcsncat_s */
#include <libc/local/wchar/wcsncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncat_s)(wchar_t *__dst, rsize_t __dstsize, const wchar_t *__src, rsize_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcsncat_s */
#endif /* !__wcsncat_s_defined */
#ifndef __wcsncpy_s_defined
#define __wcsncpy_s_defined 1
#ifdef __CRT_HAVE_wcsncpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* __CRT_HAVE_wcsncpy_s */
#include <libc/local/wchar/wcsncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* !__CRT_HAVE_wcsncpy_s */
#endif /* !__wcsncpy_s_defined */
#ifndef __wcstok_s_defined
#define __wcstok_s_defined 1
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__str,__delim,__save_ptr))
#else /* ... */
#include <libc/local/wchar/wcstok.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok_s)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__str, __delim, __save_ptr); }
#endif /* !... */
#endif /* !__wcstok_s_defined */
#endif  /* __USE_DOS_SLIB */
#if !defined(___wcserror_defined) && defined(__CRT_HAVE__wcserror)
#define ___wcserror_defined 1
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_wcserror,(int __errno_value),(__errno_value))
#endif /* !___wcserror_defined && __CRT_HAVE__wcserror */
#if !defined(___wcserror_s_defined) && defined(__CRT_HAVE__wcserror_s)
#define ___wcserror_s_defined 1
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, int __errno_value),(__buf,__bufsize,__errno_value))
#endif /* !___wcserror_s_defined && __CRT_HAVE__wcserror_s */
#if !defined(____wcserror_defined) && defined(__CRT_HAVE___wcserror)
#define ____wcserror_defined 1
__CDECLARE(,wchar_t *,__NOTHROW_NCX,__wcserror,(wchar_t const *__message),(__message))
#endif /* !____wcserror_defined && __CRT_HAVE___wcserror */
#if !defined(____wcserror_s_defined) && defined(__CRT_HAVE___wcserror_s)
#define ____wcserror_s_defined 1
__CDECLARE(,__errno_t,__NOTHROW_NCX,__wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__message),(__buf,__bufsize,__message))
#endif /* !____wcserror_s_defined && __CRT_HAVE___wcserror_s */
#ifndef ___wcsicmp_defined
#define ___wcsicmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* !... */
#endif /* !___wcsicmp_defined */
#ifndef ___wcsnicmp_defined
#define ___wcsnicmp_defined 1
#ifdef __CRT_HAVE_wcsncasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* !___wcsnicmp_defined */
#ifndef ___wcsicmp_l_defined
#define ___wcsicmp_l_defined 1
#ifdef __CRT_HAVE_wcscasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); }
#endif /* !... */
#endif /* !___wcsicmp_l_defined */
#ifndef ___wcsnicmp_l_defined
#define ___wcsnicmp_l_defined 1
#ifdef __CRT_HAVE_wcsncasecmp_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsnicmp_l_defined */
#ifndef ___wcsnset_s_defined
#define ___wcsnset_s_defined 1
#ifdef __CRT_HAVE__wcsnset_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsnset_s,(wchar_t *__restrict __buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* __CRT_HAVE__wcsnset_s */
#include <libc/local/wchar/_wcsnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsnset_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsnset_s)(wchar_t *__restrict __buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* !__CRT_HAVE__wcsnset_s */
#endif /* !___wcsnset_s_defined */
#ifndef ___wcsset_s_defined
#define ___wcsset_s_defined 1
#ifdef __CRT_HAVE__wcsset_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wcsset_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch),(__dst,__dstsize,__ch))
#else /* __CRT_HAVE__wcsset_s */
#include <libc/local/wchar/_wcsset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsset_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _wcsset_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsset_s))(__dst, __dstsize, __ch); })
#endif /* !__CRT_HAVE__wcsset_s */
#endif /* !___wcsset_s_defined */
#ifndef ___wcslwr_s_defined
#define ___wcslwr_s_defined 1
#ifdef __CRT_HAVE__wcslwr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__wcslwr_s */
#include <libc/local/wchar/_wcslwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__wcslwr_s */
#endif /* !___wcslwr_s_defined */
#ifndef ___wcsupr_s_defined
#define ___wcsupr_s_defined 1
#ifdef __CRT_HAVE__wcsupr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__wcsupr_s */
#include <libc/local/wchar/_wcsupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s))(__buf, __buflen); })
#endif /* !__CRT_HAVE__wcsupr_s */
#endif /* !___wcsupr_s_defined */
#ifndef ___wcslwr_s_l_defined
#define ___wcslwr_s_l_defined 1
#ifdef __CRT_HAVE__wcslwr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__wcslwr_s_l */
#include <libc/local/wchar/_wcslwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__wcslwr_s_l */
#endif /* !___wcslwr_s_l_defined */
#ifndef ___wcsupr_s_l_defined
#define ___wcsupr_s_l_defined 1
#ifdef __CRT_HAVE__wcsupr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* __CRT_HAVE__wcsupr_s_l */
#include <libc/local/wchar/_wcsupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s_l))(__buf, __buflen, __locale); })
#endif /* !__CRT_HAVE__wcsupr_s_l */
#endif /* !___wcsupr_s_l_defined */
#ifndef __wmemcpy_s_defined
#define __wmemcpy_s_defined 1
#ifdef __CRT_HAVE_wmemcpy_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wmemcpy_s,(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_wmemcpy_s */
#include <libc/local/wchar/wmemcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcpy_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wmemcpy_s)(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_wmemcpy_s */
#endif /* !__wmemcpy_s_defined */
#ifndef __wmemmove_s_defined
#define __wmemmove_s_defined 1
#ifdef __CRT_HAVE_wmemmove_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wmemmove_s,(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* __CRT_HAVE_wmemmove_s */
#include <libc/local/wchar/wmemmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemmove_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wmemmove_s)(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* !__CRT_HAVE_wmemmove_s */
#endif /* !__wmemmove_s_defined */



#ifndef ___wcsnset_defined
#define ___wcsnset_defined 1
#ifdef __CRT_HAVE_wcsnset
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); }
#endif /* !... */
#endif /* !___wcsnset_defined */
#ifndef ___wcsrev_defined
#define ___wcsrev_defined 1
#ifdef __CRT_HAVE_wcsrev
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); }
#endif /* !... */
#endif /* !___wcsrev_defined */
#ifndef ___wcsset_defined
#define ___wcsset_defined 1
#ifdef __CRT_HAVE_wcsset
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, int __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, int __ch),(__str,__ch))
#else /* ... */
#include <libc/local/wchar/wcsset.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); }
#endif /* !... */
#endif /* !___wcsset_defined */
#ifndef ___wcslwr_defined
#define ___wcslwr_defined 1
#ifdef __CRT_HAVE_wcslwr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); }
#endif /* !... */
#endif /* !___wcslwr_defined */
#ifndef ___wcsupr_defined
#define ___wcsupr_defined 1
#ifdef __CRT_HAVE_wcsupr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),(__str))
#else /* ... */
#include <libc/local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); }
#endif /* !... */
#endif /* !___wcsupr_defined */
#ifndef ___wcslwr_l_defined
#define ___wcslwr_l_defined 1
#ifdef __CRT_HAVE_wcslwr_l
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); }
#endif /* !... */
#endif /* !___wcslwr_l_defined */
#ifndef ___wcsupr_l_defined
#define ___wcsupr_l_defined 1
#ifdef __CRT_HAVE_wcsupr_l
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); }
#endif /* !... */
#endif /* !___wcsupr_l_defined */
#ifndef ___wcsxfrm_l_defined
#define ___wcsxfrm_l_defined 1
#ifdef __CRT_HAVE_wcsxfrm_l
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsxfrm_l_defined */
#ifndef ___wcscoll_l_defined
#define ___wcscoll_l_defined 1
#ifdef __CRT_HAVE_wcscoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#endif /* !___wcscoll_l_defined */
#ifndef ___wcsicoll_defined
#define ___wcsicoll_defined 1
#ifdef __CRT_HAVE_wcscasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* !... */
#endif /* !___wcsicoll_defined */
#ifndef ___wcsicoll_l_defined
#define ___wcsicoll_l_defined 1
#ifdef __CRT_HAVE_wcscasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); }
#endif /* !... */
#endif /* !___wcsicoll_l_defined */
#ifndef ___wcsncoll_defined
#define ___wcsncoll_defined 1
#ifdef __CRT_HAVE_wcsncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* !___wcsncoll_defined */
#ifndef ___wcsncoll_l_defined
#define ___wcsncoll_l_defined 1
#ifdef __CRT_HAVE_wcsncoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsncoll_l_defined */
#ifndef ___wcsnicoll_defined
#define ___wcsnicoll_defined 1
#ifdef __CRT_HAVE_wcsncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* !___wcsnicoll_defined */
#ifndef ___wcsnicoll_l_defined
#define ___wcsnicoll_l_defined 1
#ifdef __CRT_HAVE_wcsncasecoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* !... */
#endif /* !___wcsnicoll_l_defined */



#ifndef __wcsicmp_defined
#define __wcsicmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* !... */
#endif /* !__wcsicmp_defined */
#ifndef __wcsnicmp_defined
#define __wcsnicmp_defined 1
#ifdef __CRT_HAVE_wcsncasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* !... */
#endif /* !__wcsnicmp_defined */
#ifndef __wcsicoll_defined
#define __wcsicoll_defined 1
#ifdef __CRT_HAVE_wcscasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecoll,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* !... */
#endif /* !__wcsicoll_defined */
#endif /* !_WSTRING_DEFINED */
#endif /* __USE_DOS */
#if defined(__USE_DOS) || defined(__USE_KOS)
#ifndef __wcsnset_defined
#define __wcsnset_defined 1
#ifdef __CRT_HAVE_wcsnset
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); })
#endif /* !... */
#endif /* !__wcsnset_defined */
#ifndef __wcsrev_defined
#define __wcsrev_defined 1
#ifdef __CRT_HAVE_wcsrev
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),_wcsrev,(__str))
#else /* ... */
#include <libc/local/wchar/wcsrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); })
#endif /* !... */
#endif /* !__wcsrev_defined */
#ifndef __wcsset_defined
#define __wcsset_defined 1
#ifdef __CRT_HAVE_wcsset
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#else /* ... */
#include <libc/local/wchar/wcsset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); })
#endif /* !... */
#endif /* !__wcsset_defined */
#ifndef __wcslwr_defined
#define __wcslwr_defined 1
#ifdef __CRT_HAVE_wcslwr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcslwr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),_wcslwr,(__str))
#else /* ... */
#include <libc/local/wchar/wcslwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); })
#endif /* !... */
#endif /* !__wcslwr_defined */
#ifndef __wcsupr_defined
#define __wcsupr_defined 1
#ifdef __CRT_HAVE_wcsupr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsupr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),_wcsupr,(__str))
#else /* ... */
#include <libc/local/wchar/wcsupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); })
#endif /* !... */
#endif /* !__wcsupr_defined */
#endif /* __USE_DOS || __USE_KOS */
#ifdef __USE_DOS
#ifndef _WSTDIO_DEFINED
#define _WSTDIO_DEFINED 1
#ifdef __USE_DOS_SLIB
#ifndef __vswprintf_s_defined
#define __vswprintf_s_defined 1
#ifdef __CRT_HAVE_vswprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswprintf_s,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#else /* __CRT_HAVE_vswprintf */
#include <libc/local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf_s)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); }
#endif /* !__CRT_HAVE_vswprintf */
#endif /* !__vswprintf_s_defined */
#ifndef __swprintf_s_defined
#define __swprintf_s_defined 1
#ifdef __CRT_HAVE_swprintf
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf_s)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE__swprintf)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf_s)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#else /* ... */
#include <libc/local/wchar/swprintf.h>
#define swprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* !... */
#endif /* !__swprintf_s_defined */
#ifndef __vfwprintf_s_defined
#define __vfwprintf_s_defined 1
#ifdef __CRT_HAVE_vfwprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf_s,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/vfwprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf_s)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, __format, __args); }
#else /* ... */
#undef __vfwprintf_s_defined
#endif /* !... */
#endif /* !__vfwprintf_s_defined */
#ifndef __fwprintf_s_defined
#define __fwprintf_s_defined 1
#ifdef __CRT_HAVE_fwprintf
__LIBC __ATTR_LIBC_WPRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_s)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf");
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/fwprintf.h>
#define fwprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#else /* ... */
#undef __fwprintf_s_defined
#endif /* !... */
#endif /* !__fwprintf_s_defined */
#ifndef __vwprintf_s_defined
#define __vwprintf_s_defined 1
#ifdef __CRT_HAVE_vwprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf_s,(wchar_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#else /* __CRT_HAVE_vwprintf */
#include <__crt.h>
#if (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/vwprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf_s)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))(__format, __args); }
#else /* (__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS */
#undef __vwprintf_s_defined
#endif /* (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS */
#endif /* !__CRT_HAVE_vwprintf */
#endif /* !__vwprintf_s_defined */
#ifndef __wprintf_s_defined
#define __wprintf_s_defined 1
#ifdef __CRT_HAVE_wprintf
__LIBC __ATTR_LIBC_WPRINTF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_s)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf");
#else /* __CRT_HAVE_wprintf */
#include <__crt.h>
#if defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/wprintf.h>
#define wprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#else /* __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef __wprintf_s_defined
#endif /* !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE_wprintf */
#endif /* !__wprintf_s_defined */
#ifndef __vswscanf_s_defined
#define __vswscanf_s_defined 1
#ifdef __CRT_HAVE_vswscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswscanf_s,(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#else /* __CRT_HAVE_vswscanf */
#include <libc/local/wchar/vswscanf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf_s)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))(__src, __format, __args); }
#endif /* !__CRT_HAVE_vswscanf */
#endif /* !__vswscanf_s_defined */
#ifndef __swscanf_s_defined
#define __swscanf_s_defined 1
#ifdef __CRT_HAVE_swscanf
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf_s)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) __CASMNAME("swscanf");
#else /* __CRT_HAVE_swscanf */
#include <libc/local/wchar/swscanf.h>
#define swscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#endif /* !__CRT_HAVE_swscanf */
#endif /* !__swscanf_s_defined */
#if !defined(__vfwscanf_s_defined) && defined(__CRT_HAVE_vfwscanf)
#define __vfwscanf_s_defined 1
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(2, 0) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf_s,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#endif /* !__vfwscanf_s_defined && __CRT_HAVE_vfwscanf */
#ifndef __fwscanf_s_defined
#define __fwscanf_s_defined 1
#ifdef __CRT_HAVE_fwscanf
__LIBC __ATTR_LIBC_WSCANF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_s)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
#include <libc/local/wchar/fwscanf.h>
#define fwscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#else /* ... */
#undef __fwscanf_s_defined
#endif /* !... */
#endif /* !__fwscanf_s_defined */
#ifndef __vwscanf_s_defined
#define __vwscanf_s_defined 1
#ifdef __CRT_HAVE_vwscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf_s,(wchar_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#else /* __CRT_HAVE_vwscanf */
#include <__crt.h>
#if defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/vwscanf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_LIBC_WSCANF(1, 0) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf_s)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))(__format, __args); }
#else /* __CRT_HAVE_vfwscanf && !__NO_STDSTREAMS */
#undef __vwscanf_s_defined
#endif /* !__CRT_HAVE_vfwscanf || __NO_STDSTREAMS */
#endif /* !__CRT_HAVE_vwscanf */
#endif /* !__vwscanf_s_defined */
#ifndef __wscanf_s_defined
#define __wscanf_s_defined 1
#ifdef __CRT_HAVE_wscanf
__LIBC __ATTR_LIBC_WSCANF(1, 2) __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_s)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf");
#else /* __CRT_HAVE_wscanf */
#include <__crt.h>
#if defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/wscanf.h>
#define wscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#else /* __CRT_HAVE_vwscanf || (__CRT_HAVE_vfwscanf && !__NO_STDSTREAMS) */
#undef __wscanf_s_defined
#endif /* !__CRT_HAVE_vwscanf && (!__CRT_HAVE_vfwscanf || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE_wscanf */
#endif /* !__wscanf_s_defined */
#endif /* __USE_DOS_SLIB */
#ifndef ___vscwprintf_defined
#define ___vscwprintf_defined 1
#ifdef __CRT_HAVE__vscwprintf
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscwprintf */
#include <libc/local/wchar/_vscwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf))(__format, __args); })
#endif /* !__CRT_HAVE__vscwprintf */
#endif /* !___vscwprintf_defined */
#ifndef ___scwprintf_defined
#define ___scwprintf_defined 1
#ifdef __CRT_HAVE__scwprintf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf)(wchar_t const *__format, ...) __CASMNAME_SAME("_scwprintf");
#else /* __CRT_HAVE__scwprintf */
#include <libc/local/wchar/_scwprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf */
#endif /* !___scwprintf_defined */
#ifndef ___vscwprintf_p_defined
#define ___vscwprintf_p_defined 1
#ifdef __CRT_HAVE__vscwprintf_p
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_p,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* __CRT_HAVE__vscwprintf_p */
#include <libc/local/wchar/_vscwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_p)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_p))(__format, __args); })
#endif /* !__CRT_HAVE__vscwprintf_p */
#endif /* !___vscwprintf_p_defined */
#ifndef ___scwprintf_p_defined
#define ___scwprintf_p_defined 1
#ifdef __CRT_HAVE__scwprintf_p
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p)(wchar_t const *__format, ...) __CASMNAME_SAME("_scwprintf_p");
#else /* __CRT_HAVE__scwprintf_p */
#include <libc/local/wchar/_scwprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p)(wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf_p */
#endif /* !___scwprintf_p_defined */
#ifndef ___vscwprintf_l_defined
#define ___vscwprintf_l_defined 1
#ifdef __CRT_HAVE__vscwprintf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscwprintf_l */
#include <libc/local/wchar/_vscwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscwprintf_l */
#endif /* !___vscwprintf_l_defined */
#ifndef ___scwprintf_l_defined
#define ___scwprintf_l_defined 1
#ifdef __CRT_HAVE__scwprintf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scwprintf_l");
#else /* __CRT_HAVE__scwprintf_l */
#include <libc/local/wchar/_scwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf_l */
#endif /* !___scwprintf_l_defined */
#ifndef ___vscwprintf_p_l_defined
#define ___vscwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vscwprintf_p_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vscwprintf_p_l */
#include <libc/local/wchar/_vscwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_p_l))(__format, __locale, __args); })
#endif /* !__CRT_HAVE__vscwprintf_p_l */
#endif /* !___vscwprintf_p_l_defined */
#ifndef ___scwprintf_p_l_defined
#define ___scwprintf_p_l_defined 1
#ifdef __CRT_HAVE__scwprintf_p_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scwprintf_p_l");
#else /* __CRT_HAVE__scwprintf_p_l */
#include <libc/local/wchar/_scwprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_scwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _scwprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__scwprintf_p_l */
#endif /* !___scwprintf_p_l_defined */
#ifndef ___vswprintf_c_defined
#define ___vswprintf_c_defined 1
#ifdef __CRT_HAVE_vswprintf
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_vswprintf_c,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),vswprintf,(__buf,__buflen,__format,__args))
#else /* __CRT_HAVE_vswprintf */
#include <libc/local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_c)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); }
#endif /* !__CRT_HAVE_vswprintf */
#endif /* !___vswprintf_c_defined */
#ifndef ___swprintf_c_defined
#define ___swprintf_c_defined 1
#ifdef __CRT_HAVE_swprintf
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("swprintf");
#elif defined(__CRT_HAVE__swprintf)
__LIBC __ATTR_LIBC_WPRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#else /* ... */
#include <libc/local/wchar/swprintf.h>
#define _swprintf_c (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* !... */
#endif /* !___swprintf_c_defined */
#ifndef ___vsnwprintf_s_defined
#define ___vsnwprintf_s_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s
__CDECLARE(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__buflen,__format,__args))
#else /* __CRT_HAVE__vsnwprintf_s */
#include <libc/local/wchar/_vsnwprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_s))(__buf, __bufsize, __buflen, __format, __args); })
#endif /* !__CRT_HAVE__vsnwprintf_s */
#endif /* !___vsnwprintf_s_defined */
#ifndef ___snwprintf_s_defined
#define ___snwprintf_s_defined 1
#ifdef __CRT_HAVE__snwprintf_s
__LIBC __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, ...) __CASMNAME_SAME("_snwprintf_s");
#else /* __CRT_HAVE__snwprintf_s */
#include <libc/local/wchar/_snwprintf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwprintf_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s))(__buf, __bufsize, __buflen, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwprintf_s */
#endif /* !___snwprintf_s_defined */
#ifndef ___vfwprintf_p_defined
#define ___vfwprintf_p_defined 1
#ifdef __CRT_HAVE__vfwprintf_p
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_p,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),(__stream,__format,__args))
#else /* __CRT_HAVE__vfwprintf_p */
#include <libc/local/wchar/_vfwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_p)(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_p))(__stream, __format, __args); })
#endif /* !__CRT_HAVE__vfwprintf_p */
#endif /* !___vfwprintf_p_defined */
#ifndef ___fwprintf_p_defined
#define ___fwprintf_p_defined 1
#ifdef __CRT_HAVE__fwprintf_p
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_p");
#else /* __CRT_HAVE__fwprintf_p */
#include <libc/local/wchar/_fwprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__fwprintf_p */
#endif /* !___fwprintf_p_defined */
#ifndef ___vwprintf_p_defined
#define ___vwprintf_p_defined 1
#ifdef __CRT_HAVE__vwprintf_p
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_p,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#elif !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/_vwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_p)(wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p))(__format, __args); })
#else /* ... */
#undef ___vwprintf_p_defined
#endif /* !... */
#endif /* !___vwprintf_p_defined */
#ifndef ___wprintf_p_defined
#define ___wprintf_p_defined 1
#ifdef __CRT_HAVE__wprintf_p
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_p");
#elif defined(__CRT_HAVE__vwprintf_p) || !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/_wprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p)(wchar_t const *__format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wprintf_p_defined
#endif /* !... */
#endif /* !___wprintf_p_defined */
#ifndef ___vswprintf_p_defined
#define ___vswprintf_p_defined 1
#ifdef __CRT_HAVE__vswprintf_p
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_p,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* __CRT_HAVE__vswprintf_p */
#include <libc/local/wchar/_vswprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_p)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p))(__buf, __bufsize, __format, __args); })
#endif /* !__CRT_HAVE__vswprintf_p */
#endif /* !___vswprintf_p_defined */
#ifndef ___swprintf_p_defined
#define ___swprintf_p_defined 1
#ifdef __CRT_HAVE__swprintf_p
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_swprintf_p");
#else /* __CRT_HAVE__swprintf_p */
#include <libc/local/wchar/_swprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_p, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p))(__dst, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_p */
#endif /* !___swprintf_p_defined */
#ifndef ___vwprintf_l_defined
#define ___vwprintf_l_defined 1
#ifdef __CRT_HAVE__vwprintf_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vwprintf_l */
#include <__crt.h>
#if defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/_vwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_l))(__format, __locale, __args); })
#else /* __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef ___vwprintf_l_defined
#endif /* !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE__vwprintf_l */
#endif /* !___vwprintf_l_defined */
#ifndef ___wprintf_l_defined
#define ___wprintf_l_defined 1
#ifdef __CRT_HAVE__wprintf_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_l");
#else /* __CRT_HAVE__wprintf_l */
#include <__crt.h>
#if defined(__CRT_HAVE__vwprintf_l) || defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/_wprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_l))
#endif /* !__cplusplus */
#else /* __CRT_HAVE__vwprintf_l || __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef ___wprintf_l_defined
#endif /* !__CRT_HAVE__vwprintf_l && !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE__wprintf_l */
#endif /* !___wprintf_l_defined */
#ifndef ___vwprintf_p_l_defined
#define ___vwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vwprintf_p_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#elif defined(__CRT_HAVE__vwprintf_p) || !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/_vwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p_l))(__format, __locale, __args); })
#else /* ... */
#undef ___vwprintf_p_l_defined
#endif /* !... */
#endif /* !___vwprintf_p_l_defined */
#ifndef ___wprintf_p_l_defined
#define ___wprintf_p_l_defined 1
#ifdef __CRT_HAVE__wprintf_p_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_p_l");
#elif defined(__CRT_HAVE__vwprintf_p_l) || defined(__CRT_HAVE__vwprintf_p) || !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/_wprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___wprintf_p_l_defined
#endif /* !... */
#endif /* !___wprintf_p_l_defined */
#ifndef ___vwprintf_s_l_defined
#define ___vwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__THROWING,_vwprintf_s_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* __CRT_HAVE__vwprintf_s_l */
#include <__crt.h>
#if defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/_vwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_s_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_s_l))(__format, __locale, __args); })
#else /* __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef ___vwprintf_s_l_defined
#endif /* !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE__vwprintf_s_l */
#endif /* !___vwprintf_s_l_defined */
#ifndef ___wprintf_s_l_defined
#define ___wprintf_s_l_defined 1
#ifdef __CRT_HAVE__wprintf_s_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_s_l");
#else /* __CRT_HAVE__wprintf_s_l */
#include <__crt.h>
#if defined(__CRT_HAVE__vwprintf_s_l) || defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/_wprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_s_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_s_l))
#endif /* !__cplusplus */
#else /* __CRT_HAVE__vwprintf_s_l || __CRT_HAVE_vwprintf || ((__CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS) */
#undef ___wprintf_s_l_defined
#endif /* !__CRT_HAVE__vwprintf_s_l && !__CRT_HAVE_vwprintf && ((!__CRT_HAVE_vfwprintf && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE__wprintf_s_l */
#endif /* !___wprintf_s_l_defined */
#ifndef ___vfwprintf_l_defined
#define ___vfwprintf_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/_vfwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_l))(__stream, __format, __locale, __args); })
#else /* ... */
#undef ___vfwprintf_l_defined
#endif /* !... */
#endif /* !___vfwprintf_l_defined */
#ifndef ___fwprintf_l_defined
#define ___fwprintf_l_defined 1
#ifdef __CRT_HAVE__fwprintf_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_l");
#elif defined(__CRT_HAVE__vfwprintf_l) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/_fwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___fwprintf_l_defined
#endif /* !... */
#endif /* !___fwprintf_l_defined */
#ifndef ___vfwprintf_p_l_defined
#define ___vfwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_p_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_p_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#else /* __CRT_HAVE__vfwprintf_p_l */
#include <libc/local/wchar/_vfwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_p_l))(__stream, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vfwprintf_p_l */
#endif /* !___vfwprintf_p_l_defined */
#ifndef ___fwprintf_p_l_defined
#define ___fwprintf_p_l_defined 1
#ifdef __CRT_HAVE__fwprintf_p_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_p_l");
#else /* __CRT_HAVE__fwprintf_p_l */
#include <libc/local/wchar/_fwprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__fwprintf_p_l */
#endif /* !___fwprintf_p_l_defined */
#ifndef ___vfwprintf_s_l_defined
#define ___vfwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__THROWING,_vfwprintf_s_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args))
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/_vfwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_s_l))(__stream, __format, __locale, __args); })
#else /* ... */
#undef ___vfwprintf_s_l_defined
#endif /* !... */
#endif /* !___vfwprintf_s_l_defined */
#ifndef ___fwprintf_s_l_defined
#define ___fwprintf_s_l_defined 1
#ifdef __CRT_HAVE__fwprintf_s_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_s_l");
#elif defined(__CRT_HAVE__vfwprintf_s_l) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <libc/local/wchar/_fwprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_s_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_s_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___fwprintf_s_l_defined
#endif /* !... */
#endif /* !___fwprintf_s_l_defined */
#ifndef ___vswprintf_c_l_defined
#define ___vswprintf_c_l_defined 1
#ifdef __CRT_HAVE__vswprintf_c_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_c_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vswprintf_c_l */
#include <libc/local/wchar/_vswprintf_c_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_c_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vswprintf_c_l */
#endif /* !___vswprintf_c_l_defined */
#ifndef ___swprintf_c_l_defined
#define ___swprintf_c_l_defined 1
#ifdef __CRT_HAVE__swprintf_c_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_c_l");
#else /* __CRT_HAVE__swprintf_c_l */
#include <libc/local/wchar/_swprintf_c_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_c_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_c_l))(__dst, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_c_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_c_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_c_l */
#endif /* !___swprintf_c_l_defined */
#ifndef ___vswprintf_p_l_defined
#define ___vswprintf_p_l_defined 1
#ifdef __CRT_HAVE__vswprintf_p_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_p_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vswprintf_p_l */
#include <libc/local/wchar/_vswprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vswprintf_p_l */
#endif /* !___vswprintf_p_l_defined */
#ifndef ___swprintf_p_l_defined
#define ___swprintf_p_l_defined 1
#ifdef __CRT_HAVE__swprintf_p_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_p_l");
#else /* __CRT_HAVE__swprintf_p_l */
#include <libc/local/wchar/_swprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_p_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p_l))(__dst, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_p_l */
#endif /* !___swprintf_p_l_defined */
#ifndef ___vswprintf_s_l_defined
#define ___vswprintf_s_l_defined 1
#ifdef __CRT_HAVE__vswprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_s_l,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__wchar_count,__format,__locale,__args))
#else /* __CRT_HAVE__vswprintf_s_l */
#include <libc/local/wchar/_vswprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_s_l))(__dst, __wchar_count, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vswprintf_s_l */
#endif /* !___vswprintf_s_l_defined */
#ifndef ___swprintf_s_l_defined
#define ___swprintf_s_l_defined 1
#ifdef __CRT_HAVE__swprintf_s_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_s_l");
#else /* __CRT_HAVE__swprintf_s_l */
#include <libc/local/wchar/_swprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_s_l))(__dst, __wchar_count, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swprintf_s_l */
#endif /* !___swprintf_s_l_defined */
#ifndef ___vsnwprintf_l_defined
#define ___vsnwprintf_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnwprintf_l */
#include <libc/local/wchar/_vsnwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnwprintf_l */
#endif /* !___vsnwprintf_l_defined */
#ifndef ___snwprintf_l_defined
#define ___snwprintf_l_defined 1
#ifdef __CRT_HAVE__snwprintf_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwprintf_l");
#else /* __CRT_HAVE__snwprintf_l */
#include <libc/local/wchar/_snwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwprintf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_l))(__dst, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwprintf_l */
#endif /* !___snwprintf_l_defined */
#ifndef ___vsnwprintf_s_l_defined
#define ___vsnwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_s_l,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__wchar_count,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsnwprintf_s_l */
#include <libc/local/wchar/_vsnwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_s_l))(__dst, __wchar_count, __bufsize, __format, __locale, __args); })
#endif /* !__CRT_HAVE__vsnwprintf_s_l */
#endif /* !___vsnwprintf_s_l_defined */
#ifndef ___snwprintf_s_l_defined
#define ___snwprintf_s_l_defined 1
#ifdef __CRT_HAVE__snwprintf_s_l
__LIBC __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwprintf_s_l");
#else /* __CRT_HAVE__snwprintf_s_l */
#include <libc/local/wchar/_snwprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwprintf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s_l))(__dst, __wchar_count, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwprintf_s_l */
#endif /* !___snwprintf_s_l_defined */
#ifndef ___fwscanf_l_defined
#define ___fwscanf_l_defined 1
#ifdef __CRT_HAVE__fwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwscanf_l");
#elif defined(__CRT_HAVE__vfwscanf_l) || defined(__CRT_HAVE_vfwscanf)
#include <libc/local/wchar/_fwscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_fwscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))(__stream, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _fwscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))
#endif /* !__cplusplus */
#else /* ... */
#undef ___fwscanf_l_defined
#endif /* !... */
#endif /* !___fwscanf_l_defined */
#ifndef ___fwscanf_s_l_defined
#define ___fwscanf_s_l_defined 1
#ifdef __CRT_HAVE__fwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_fwscanf_l");
#elif defined(__CRT_HAVE__vfwscanf_l) || defined(__CRT_HAVE_vfwscanf)
#include <libc/local/wchar/_fwscanf_l.h>
#define _fwscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))
#else /* ... */
#undef ___fwscanf_s_l_defined
#endif /* !... */
#endif /* !___fwscanf_s_l_defined */
#ifndef ___swscanf_l_defined
#define ___swscanf_l_defined 1
#ifdef __CRT_HAVE__swscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swscanf_l");
#else /* __CRT_HAVE__swscanf_l */
#include <libc/local/wchar/_swscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_swscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))(__src, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _swscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__swscanf_l */
#endif /* !___swscanf_l_defined */
#ifndef ___swscanf_s_l_defined
#define ___swscanf_s_l_defined 1
#ifdef __CRT_HAVE__swscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_s_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME("_swscanf_l");
#else /* __CRT_HAVE__swscanf_l */
#include <libc/local/wchar/_swscanf_l.h>
#define _swscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))
#endif /* !__CRT_HAVE__swscanf_l */
#endif /* !___swscanf_s_l_defined */
#ifndef ___snwscanf_defined
#define ___snwscanf_defined 1
#ifdef __CRT_HAVE__snwscanf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_snwscanf");
#else /* __CRT_HAVE__snwscanf */
#include <libc/local/wchar/_snwscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))(__src, __bufsize, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwscanf */
#endif /* !___snwscanf_defined */
#ifndef ___snwscanf_l_defined
#define ___snwscanf_l_defined 1
#ifdef __CRT_HAVE__snwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwscanf_l");
#else /* __CRT_HAVE__snwscanf_l */
#include <libc/local/wchar/_snwscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_l))(__src, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwscanf_l */
#endif /* !___snwscanf_l_defined */
#ifndef ___snwscanf_s_defined
#define ___snwscanf_s_defined 1
#ifdef __CRT_HAVE__snwscanf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME("_snwscanf");
#else /* __CRT_HAVE__snwscanf */
#include <libc/local/wchar/_snwscanf.h>
#define _snwscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))
#endif /* !__CRT_HAVE__snwscanf */
#endif /* !___snwscanf_s_defined */
#ifndef ___snwscanf_s_l_defined
#define ___snwscanf_s_l_defined 1
#ifdef __CRT_HAVE__snwscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwscanf_s_l");
#else /* __CRT_HAVE__snwscanf_s_l */
#include <libc/local/wchar/_snwscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_snwscanf_s_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_s_l))(__src, __bufsize, __format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _snwscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_s_l))
#endif /* !__cplusplus */
#endif /* !__CRT_HAVE__snwscanf_s_l */
#endif /* !___snwscanf_s_l_defined */
#ifndef ___wscanf_l_defined
#define ___wscanf_l_defined 1
#ifdef __CRT_HAVE__wscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wscanf_l");
#else /* __CRT_HAVE__wscanf_l */
#include <__crt.h>
#if defined(__CRT_HAVE__vwscanf_l) || defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/_wscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING_OR_IMPL(_wscanf_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))(__format, __locale, __builtin_va_arg_pack()); })
#else /* __cplusplus */
#define _wscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))
#endif /* !__cplusplus */
#else /* __CRT_HAVE__vwscanf_l || __CRT_HAVE_vwscanf || (__CRT_HAVE_vfwscanf && !__NO_STDSTREAMS) */
#undef ___wscanf_l_defined
#endif /* !__CRT_HAVE__vwscanf_l && !__CRT_HAVE_vwscanf && (!__CRT_HAVE_vfwscanf || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE__wscanf_l */
#endif /* !___wscanf_l_defined */
#ifndef ___wscanf_s_l_defined
#define ___wscanf_s_l_defined 1
#ifdef __CRT_HAVE__wscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_wscanf_l");
#else /* __CRT_HAVE__wscanf_l */
#include <__crt.h>
#if defined(__CRT_HAVE__vwscanf_l) || defined(__CRT_HAVE_vwscanf) || (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS))
#include <libc/local/wchar/_wscanf_l.h>
#define _wscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))
#else /* __CRT_HAVE__vwscanf_l || __CRT_HAVE_vwscanf || (__CRT_HAVE_vfwscanf && !__NO_STDSTREAMS) */
#undef ___wscanf_s_l_defined
#endif /* !__CRT_HAVE__vwscanf_l && !__CRT_HAVE_vwscanf && (!__CRT_HAVE_vfwscanf || __NO_STDSTREAMS) */
#endif /* !__CRT_HAVE__wscanf_l */
#endif /* !___wscanf_s_l_defined */
#if !defined(___wfsopen_defined) && defined(__CRT_HAVE__wfsopen)
#define ___wfsopen_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfsopen,(wchar_t const *__filename, wchar_t const *__mode, __STDC_INT_AS_UINT_T __sh_flag),(__filename,__mode,__sh_flag))
#endif /* !___wfsopen_defined && __CRT_HAVE__wfsopen */
#if !defined(___wfdopen_defined) && defined(__CRT_HAVE__wfdopen)
#define ___wfdopen_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_wfdopen,(__fd_t __fd, wchar_t const *__mode),(__fd,__mode))
#endif /* !___wfdopen_defined && __CRT_HAVE__wfdopen */
#if !defined(___wfopen_s_defined) && defined(__CRT_HAVE__wfopen_s)
#define ___wfopen_s_defined 1
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,_wfopen_s,(__FILE **__pstream, wchar_t const *__filename, wchar_t const *__mode),(__pstream,__filename,__mode))
#endif /* !___wfopen_s_defined && __CRT_HAVE__wfopen_s */
#if !defined(___wfreopen_s_defined) && defined(__CRT_HAVE__wfreopen_s)
#define ___wfreopen_s_defined 1
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,_wfreopen_s,(__FILE **__pstream, wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__pstream,__filename,__mode,__stream))
#endif /* !___wfreopen_s_defined && __CRT_HAVE__wfreopen_s */
#ifndef ___wfopen_defined
#define ___wfopen_defined 1
#ifdef __CRT_HAVE_wfopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfopen,(wchar_t const *__filename, wchar_t const *__mode),wfopen,(__filename,__mode))
#elif defined(__CRT_HAVE__wfopen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfopen,(wchar_t const *__filename, wchar_t const *__mode),(__filename,__mode))
#else /* ... */
#undef ___wfopen_defined
#endif /* !... */
#endif /* !___wfopen_defined */
#ifndef ___wfreopen_defined
#define ___wfreopen_defined 1
#ifdef __CRT_HAVE_wfreopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#elif defined(__CRT_HAVE__wfreopen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__filename,__mode,__stream))
#else /* ... */
#undef ___wfreopen_defined
#endif /* !... */
#endif /* !___wfreopen_defined */
#ifndef ___fgetwchar_defined
#define ___fgetwchar_defined 1
#ifdef __CRT_HAVE_getwchar
__CREDIRECT(,wint_t,__THROWING,_fgetwchar,(void),getwchar,())
#elif defined(__CRT_HAVE__fgetwchar)
__CDECLARE(,wint_t,__THROWING,_fgetwchar,(void),())
#else /* ... */
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#include <libc/local/wchar/getwchar.h>
__FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL _fgetwchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) */
#undef ___fgetwchar_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc) */
#endif /* !... */
#endif /* !___fgetwchar_defined */
#ifndef ___fputwchar_defined
#define ___fputwchar_defined 1
#ifdef __CRT_HAVE_putwchar
__CREDIRECT(,wint_t,__THROWING,_fputwchar,(wchar_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE__fputwchar)
__CDECLARE(,wint_t,__THROWING,_fputwchar,(wchar_t __wc),(__wc))
#else /* ... */
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#include <libc/local/wchar/putwchar.h>
__FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL _fputwchar)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); }
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fputwc || __CRT_HAVE_putwc) */
#undef ___fputwchar_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) */
#endif /* !... */
#endif /* !___fputwchar_defined */
#ifndef ___getws_s_defined
#define ___getws_s_defined 1
#ifdef __CRT_HAVE__getws_s
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_getws_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* __CRT_HAVE__getws_s */
#include <__crt.h>
#if (defined(__CRT_HAVE_fgetws) || defined(__CRT_HAVE_fgetws_unlocked) || defined(__CRT_HAVE__fgetws_nolock) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked)))) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/_getws_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getws_s, __FORCELOCAL __ATTR_ARTIFICIAL wchar_t *__NOTHROW_NCX(__LIBCCALL _getws_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getws_s))(__buf, __buflen); })
#else /* (__CRT_HAVE_fgetws || __CRT_HAVE_fgetws_unlocked || __CRT_HAVE__fgetws_nolock || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked))) && !__NO_STDSTREAMS */
#undef ___getws_s_defined
#endif /* (!__CRT_HAVE_fgetws && !__CRT_HAVE_fgetws_unlocked && !__CRT_HAVE__fgetws_nolock && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked))) || __NO_STDSTREAMS */
#endif /* !__CRT_HAVE__getws_s */
#endif /* !___getws_s_defined */
#ifndef ___putws_defined
#define ___putws_defined 1
#ifdef __CRT_HAVE__putws
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_putws,(wchar_t const *__str),(__str))
#else /* __CRT_HAVE__putws */
#include <__crt.h>
#if (defined(__CRT_HAVE_fputws) || defined(__CRT_HAVE_fputws_unlocked) || defined(__CRT_HAVE__fputws_nolock) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)) && !defined(__NO_STDSTREAMS)
#include <libc/local/wchar/_putws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _putws)(wchar_t const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putws))(__str); })
#else /* (__CRT_HAVE_fputws || __CRT_HAVE_fputws_unlocked || __CRT_HAVE__fputws_nolock || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc) && !__NO_STDSTREAMS */
#undef ___putws_defined
#endif /* (!__CRT_HAVE_fputws && !__CRT_HAVE_fputws_unlocked && !__CRT_HAVE__fputws_nolock && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc) || __NO_STDSTREAMS */
#endif /* !__CRT_HAVE__putws */
#endif /* !___putws_defined */
#if !defined(___wtempnam_defined) && defined(__CRT_HAVE__wtempnam)
#define ___wtempnam_defined 1
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,_wtempnam,(wchar_t const *__directory, wchar_t const *__file_prefix),(__directory,__file_prefix))
#endif /* !___wtempnam_defined && __CRT_HAVE__wtempnam */
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__THROWING,_wperror,(__WCHAR_TYPE__ const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <__crt.h>
#include <libc/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD void (__LIBCCALL _wperror)(__WCHAR_TYPE__ const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef _CRT_WPERROR_DEFINED
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE__wperror */
#endif /* !_CRT_WPERROR_DEFINED */
#ifndef ___wpopen_defined
#define ___wpopen_defined 1
#ifdef __CRT_HAVE_wpopen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wpopen,(wchar_t const *__command, wchar_t const *__mode),wpopen,(__command,__mode))
#elif defined(__CRT_HAVE__wpopen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wpopen,(wchar_t const *__command, wchar_t const *__mode),(__command,__mode))
#else /* ... */
#undef ___wpopen_defined
#endif /* !... */
#endif /* !___wpopen_defined */
#ifndef ___wremove_defined
#define ___wremove_defined 1
#ifdef __CRT_HAVE_wremove
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wremove,(wchar_t const *__filename),wremove,(__filename))
#elif defined(__CRT_HAVE__wremove)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wremove,(wchar_t const *__filename),(__filename))
#else /* ... */
#undef ___wremove_defined
#endif /* !... */
#endif /* !___wremove_defined */
#if !defined(___wtmpnam_s_defined) && defined(__CRT_HAVE__wtmpnam_s)
#define ___wtmpnam_s_defined 1
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wtmpnam_s,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count),(__dst,__wchar_count))
#endif /* !___wtmpnam_s_defined && __CRT_HAVE__wtmpnam_s */
#ifndef ___fgetwc_nolock_defined
#define ___fgetwc_nolock_defined 1
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_fgetwc_nolock,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_fgetwc_nolock,(__FILE *__restrict __stream),(__stream))
#else /* ... */
#undef ___fgetwc_nolock_defined
#endif /* !... */
#endif /* !___fgetwc_nolock_defined */
#ifndef ___fputwc_nolock_defined
#define ___fputwc_nolock_defined 1
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_fputwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_fputwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#else /* ... */
#undef ___fputwc_nolock_defined
#endif /* !... */
#endif /* !___fputwc_nolock_defined */
#ifndef ___ungetwc_nolock_defined
#define ___ungetwc_nolock_defined 1
#ifdef __CRT_HAVE_ungetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#else /* ... */
#undef ___ungetwc_nolock_defined
#endif /* !... */
#endif /* !___ungetwc_nolock_defined */
#ifndef ___getwc_nolock_defined
#define ___getwc_nolock_defined 1
#ifdef __CRT_HAVE_fgetwc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_getwc_nolock,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__THROWING,_getwc_nolock,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#else /* ... */
#undef ___getwc_nolock_defined
#endif /* !... */
#endif /* !___getwc_nolock_defined */
#ifndef ___putwc_nolock_defined
#define ___putwc_nolock_defined 1
#ifdef __CRT_HAVE_fputwc_unlocked
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__THROWING,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#else /* ... */
#undef ___putwc_nolock_defined
#endif /* !... */
#endif /* !___putwc_nolock_defined */
#endif /* !_WSTDIO_DEFINED */
#ifndef _WSTDLIB_DEFINED
#define _WSTDLIB_DEFINED
#ifndef ___wcstol_l_defined
#define ___wcstol_l_defined 1
#ifdef __CRT_HAVE_wcstol_l
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l)
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstol_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _wcstol_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstol_l_defined */
#ifndef ___wcstoul_l_defined
#define ___wcstoul_l_defined 1
#ifdef __CRT_HAVE_wcstoul_l
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l)
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoul_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL _wcstoul_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoul_l_defined */
#ifndef __NO_FPU
#ifndef ___wcstof_l_defined
#define ___wcstof_l_defined 1
#ifdef __CRT_HAVE_wcstof_l
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l)
__CDECLARE(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l)
__CREDIRECT(__ATTR_NONNULL((1)),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstof_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL _wcstof_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* !___wcstof_l_defined */
#ifndef ___wcstod_l_defined
#define ___wcstod_l_defined 1
#ifdef __CRT_HAVE_wcstod_l
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
__CREDIRECT(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstod_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _wcstod_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* !___wcstod_l_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef ___wcstold_l_defined
#define ___wcstold_l_defined 1
#ifdef __CRT_HAVE_wcstold_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l)
__CDECLARE(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstold_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL _wcstold_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* !___wcstold_l_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifndef ___wtof_defined
#define ___wtof_defined 1
#ifdef __CRT_HAVE__wtof
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wtof,(wchar_t const *__nptr),(__nptr))
#else /* __CRT_HAVE__wtof */
#include <libc/local/stdlib/_wtof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _wtof)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtof))(__nptr); })
#endif /* !__CRT_HAVE__wtof */
#endif /* !___wtof_defined */
#ifndef ___wtof_l_defined
#define ___wtof_l_defined 1
#ifdef __CRT_HAVE__wtof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,_wtof_l,(wchar_t const *__nptr, __locale_t __locale),(__nptr,__locale))
#else /* __CRT_HAVE__wtof_l */
#include <libc/local/stdlib/_wtof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL _wtof_l)(wchar_t const *__nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtof_l))(__nptr, __locale); })
#endif /* !__CRT_HAVE__wtof_l */
#endif /* !___wtof_l_defined */
#endif /* !__NO_FPU */
#ifndef ___itow_defined
#define ___itow_defined 1
#ifdef __CRT_HAVE__itow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_itow,(int __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__itow */
#include <libc/local/stdlib/_itow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _itow)(int __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__itow */
#endif /* !___itow_defined */
#ifndef ___ltow_defined
#define ___ltow_defined 1
#ifdef __CRT_HAVE__ltow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_ltow,(long __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ltow */
#include <libc/local/stdlib/_ltow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _ltow)(long __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ltow */
#endif /* !___ltow_defined */
#ifndef ___ultow_defined
#define ___ultow_defined 1
#ifdef __CRT_HAVE__ultow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_ultow,(unsigned long __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ultow */
#include <libc/local/stdlib/_ultow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _ultow)(unsigned long __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ultow */
#endif /* !___ultow_defined */
#ifndef ___i64tow_defined
#define ___i64tow_defined 1
#ifdef __CRT_HAVE__i64tow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_i64tow,(__INT64_TYPE__ __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__i64tow */
#include <libc/local/stdlib/_i64tow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64tow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _i64tow)(__INT64_TYPE__ __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64tow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__i64tow */
#endif /* !___i64tow_defined */
#ifndef ___ui64tow_defined
#define ___ui64tow_defined 1
#ifdef __CRT_HAVE__ui64tow
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,_ui64tow,(__UINT64_TYPE__ __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ui64tow */
#include <libc/local/stdlib/_ui64tow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64tow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) wchar_t *__NOTHROW_NCX(__LIBCCALL _ui64tow)(__UINT64_TYPE__ __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64tow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ui64tow */
#endif /* !___ui64tow_defined */
#ifndef ___itow_s_defined
#define ___itow_s_defined 1
#ifdef __CRT_HAVE__itow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_itow_s,(int __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__itow_s */
#include <libc/local/stdlib/_itow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _itow_s)(int __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__itow_s */
#endif /* !___itow_s_defined */
#ifndef ___ltow_s_defined
#define ___ltow_s_defined 1
#ifdef __CRT_HAVE__ltow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ltow_s,(long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ltow_s */
#include <libc/local/stdlib/_ltow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ltow_s)(long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ltow_s */
#endif /* !___ltow_s_defined */
#ifndef ___ultow_s_defined
#define ___ultow_s_defined 1
#ifdef __CRT_HAVE__ultow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ultow_s,(unsigned long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ultow_s */
#include <libc/local/stdlib/_ultow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ultow_s)(unsigned long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ultow_s */
#endif /* !___ultow_s_defined */
#ifndef ___i64tow_s_defined
#define ___i64tow_s_defined 1
#ifdef __CRT_HAVE__i64tow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_i64tow_s,(__INT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__i64tow_s */
#include <libc/local/stdlib/_i64tow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64tow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _i64tow_s)(__INT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64tow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__i64tow_s */
#endif /* !___i64tow_s_defined */
#ifndef ___ui64tow_s_defined
#define ___ui64tow_s_defined 1
#ifdef __CRT_HAVE__ui64tow_s
__CDECLARE(__ATTR_NONNULL((2)),errno_t,__NOTHROW_NCX,_ui64tow_s,(__UINT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ui64tow_s */
#include <libc/local/stdlib/_ui64tow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64tow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) errno_t __NOTHROW_NCX(__LIBCCALL _ui64tow_s)(__UINT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64tow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ui64tow_s */
#endif /* !___ui64tow_s_defined */
#if !defined(___wgetenv_defined) && defined(__CRT_HAVE__wgetenv)
#define ___wgetenv_defined 1
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wgetenv,(wchar_t const *__varname),(__varname))
#endif /* !___wgetenv_defined && __CRT_HAVE__wgetenv */
#if !defined(___wgetenv_s_defined) && defined(__CRT_HAVE__wgetenv_s)
#define ___wgetenv_s_defined 1
__CDECLARE(__ATTR_NONNULL((1, 4)),errno_t,__NOTHROW_NCX,_wgetenv_s,(__SIZE_TYPE__ *__return_size, wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__varname),(__return_size,__buf,__buflen,__varname))
#endif /* !___wgetenv_s_defined && __CRT_HAVE__wgetenv_s */
#if !defined(___wdupenv_s_defined) && defined(__CRT_HAVE__wdupenv_s)
#define ___wdupenv_s_defined 1
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_NCX,_wdupenv_s,(wchar_t **__pbuf, __SIZE_TYPE__ *__pbuflen, wchar_t const *__varname),(__pbuf,__pbuflen,__varname))
#endif /* !___wdupenv_s_defined && __CRT_HAVE__wdupenv_s */
#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED 1
#ifdef __CRT_HAVE_wsystem
__CREDIRECT(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CDECLARE(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),(__cmd))
#else /* ... */
#undef _CRT_WSYSTEM_DEFINED
#endif /* !... */
#endif /* !_CRT_WSYSTEM_DEFINED */
#ifndef ___wtoi_defined
#define ___wtoi_defined 1
#ifdef __CRT_HAVE_wtoi
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _wtoi)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))(__nptr); }
#endif /* !... */
#endif /* !___wtoi_defined */
#ifndef ___wtol_defined
#define ___wtol_defined 1
#ifdef __CRT_HAVE_wtol
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL _wtol)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))(__nptr); }
#endif /* !... */
#endif /* !___wtol_defined */
#ifndef ___wtoi64_defined
#define ___wtoi64_defined 1
#ifdef __CRT_HAVE__wtoi64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtoll,(__nptr))
#else /* ... */
#include <libc/local/stdlib/_wtoi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wtoi64)(wchar_t const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi64))(__nptr); })
#endif /* !... */
#endif /* !___wtoi64_defined */
#ifndef ___wcstoi64_defined
#define ___wcstoi64_defined 1
#ifdef __CRT_HAVE_wcsto64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcsto64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoi64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))(__nptr, __endptr, __base); }
#endif /* !... */
#endif /* !___wcstoi64_defined */
#ifndef ___wcstoui64_defined
#define ___wcstoui64_defined 1
#ifdef __CRT_HAVE_wcstou64
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstou64.h>
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoui64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))(__nptr, __endptr, __base); }
#endif /* !... */
#endif /* !___wcstoui64_defined */
#ifndef ___wtoi_l_defined
#define ___wtoi_l_defined 1
#ifdef __CRT_HAVE__wtoi_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_wtoi_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL _wtoi_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtoi_l_defined */
#ifndef ___wtol_l_defined
#define ___wtol_l_defined 1
#ifdef __CRT_HAVE__wtol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_wtol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long int __NOTHROW_NCX(__LIBCCALL _wtol_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtol_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtol_l_defined */
#ifndef ___wtoi64_l_defined
#define ___wtoi64_l_defined 1
#ifdef __CRT_HAVE__wtoi64_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_wtoi64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wtoi64_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi64_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtoi64_l_defined */
#ifndef ___wcstoi64_l_defined
#define ___wcstoi64_l_defined 1
#ifdef __CRT_HAVE_wcsto64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcsto64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoi64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoi64_l_defined */
#ifndef ___wcstoui64_l_defined
#define ___wcstoui64_l_defined 1
#ifdef __CRT_HAVE_wcstou64_l
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l)
__CDECLARE(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
__CREDIRECT(__ATTR_LEAF __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstou64_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoui64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoui64_l_defined */
#ifdef __LONGLONG
#ifndef ___wcstoll_l_defined
#define ___wcstoll_l_defined 1
#ifdef __CRT_HAVE_wcstoll_l
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l)
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoll_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wcstoll_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoll_l_defined */
#ifndef ___wcstoull_l_defined
#define ___wcstoull_l_defined 1
#ifdef __CRT_HAVE_wcstoull_l
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l)
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoull_l.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _wcstoull_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#endif /* !___wcstoull_l_defined */
#ifndef ___wtoll_defined
#define ___wtoll_defined 1
#ifdef __CRT_HAVE_wtoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wtoll)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))(__nptr); }
#endif /* !... */
#endif /* !___wtoll_defined */
#ifndef ___wtoll_l_defined
#define ___wtoll_l_defined 1
#ifdef __CRT_HAVE__wtoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/stdlib/_wtoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wtoll_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoll_l))(__nptr, __locale); })
#endif /* !... */
#endif /* !___wtoll_l_defined */
#endif /* __LONGLONG */
#endif /* !_WSTDLIB_DEFINED */
#ifndef _WSTDLIBP_DEFINED
#define _WSTDLIBP_DEFINED 1
#if !defined(___wfullpath_defined) && defined(__CRT_HAVE__wfullpath)
#define ___wfullpath_defined 1
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_wfullpath,(wchar_t *__buf, wchar_t const *__path, __SIZE_TYPE__ __buflen),(__buf,__path,__buflen))
#endif /* !___wfullpath_defined && __CRT_HAVE__wfullpath */
#ifndef ___wmakepath_s_defined
#define ___wmakepath_s_defined 1
#ifdef __CRT_HAVE__wmakepath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_wmakepath_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext),(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wmakepath_s */
#include <libc/local/stdlib/_wmakepath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmakepath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _wmakepath_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmakepath_s))(__buf, __buflen, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wmakepath_s */
#endif /* !___wmakepath_s_defined */
#ifndef ___wmakepath_defined
#define ___wmakepath_defined 1
#ifdef __CRT_HAVE__wmakepath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_wmakepath,(wchar_t *__restrict __buf, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext),(__buf,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wmakepath */
#include <libc/local/stdlib/_wmakepath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmakepath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _wmakepath)(wchar_t *__restrict __buf, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmakepath))(__buf, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wmakepath */
#endif /* !___wmakepath_defined */
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD,__THROWING,_wperror,(__WCHAR_TYPE__ const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <__crt.h>
#include <libc/errno.h>
#if !defined(__NO_STDSTREAMS) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/stdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD void (__LIBCCALL _wperror)(__WCHAR_TYPE__ const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* !__NO_STDSTREAMS && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked || (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef _CRT_WPERROR_DEFINED
#endif /* __NO_STDSTREAMS || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_fputc && !__CRT_HAVE_putc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE_putc_unlocked && (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE__wperror */
#endif /* !_CRT_WPERROR_DEFINED */
#if !defined(___wputenv_defined) && defined(__CRT_HAVE__wputenv)
#define ___wputenv_defined 1
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wputenv,(wchar_t *__string),(__string))
#endif /* !___wputenv_defined && __CRT_HAVE__wputenv */
#if !defined(___wputenv_s_defined) && defined(__CRT_HAVE__wputenv_s)
#define ___wputenv_s_defined 1
__CDECLARE(,errno_t,__NOTHROW_NCX,_wputenv_s,(wchar_t const *__varname, wchar_t const *__val),(__varname,__val))
#endif /* !___wputenv_s_defined && __CRT_HAVE__wputenv_s */
#if !defined(___wsearchenv_s_defined) && defined(__CRT_HAVE__wsearchenv_s)
#define ___wsearchenv_s_defined 1
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),errno_t,__NOTHROW_RPC,_wsearchenv_s,(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath, __SIZE_TYPE__ __buflen),(__file,__envvar,__resultpath,__buflen))
#endif /* !___wsearchenv_s_defined && __CRT_HAVE__wsearchenv_s */
#ifndef ___wsearchenv_defined
#define ___wsearchenv_defined 1
#ifdef __CRT_HAVE__wsearchenv
__CDECLARE_VOID(__ATTR_NONNULL((1, 2, 3)),__NOTHROW_RPC,_wsearchenv,(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath),(__file,__envvar,__resultpath))
#elif defined(__CRT_HAVE__wsearchenv_s)
#include <libc/local/stdlib/_wsearchenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsearchenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) void __NOTHROW_RPC(__LIBCCALL _wsearchenv)(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsearchenv))(__file, __envvar, __resultpath); })
#else /* ... */
#undef ___wsearchenv_defined
#endif /* !... */
#endif /* !___wsearchenv_defined */
#ifndef ___wsplitpath_defined
#define ___wsplitpath_defined 1
#ifdef __CRT_HAVE__wsplitpath
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,_wsplitpath,(wchar_t const *__restrict __abspath, wchar_t *__drive, wchar_t *__dir, wchar_t *__file, wchar_t *__ext),(__abspath,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wsplitpath */
#include <libc/local/stdlib/_wsplitpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsplitpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL _wsplitpath)(wchar_t const *__restrict __abspath, wchar_t *__drive, wchar_t *__dir, wchar_t *__file, wchar_t *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsplitpath))(__abspath, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wsplitpath */
#endif /* !___wsplitpath_defined */
#ifndef ___wsplitpath_s_defined
#define ___wsplitpath_s_defined 1
#ifdef __CRT_HAVE__wsplitpath_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_wsplitpath_s,(wchar_t const *__restrict __abspath, wchar_t *__drive, __SIZE_TYPE__ __drivelen, wchar_t *__dir, __SIZE_TYPE__ __dirlen, wchar_t *__file, __SIZE_TYPE__ __filelen, wchar_t *__ext, __SIZE_TYPE__ __extlen),(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__wsplitpath_s */
#include <libc/local/stdlib/_wsplitpath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsplitpath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _wsplitpath_s)(wchar_t const *__restrict __abspath, wchar_t *__drive, __SIZE_TYPE__ __drivelen, wchar_t *__dir, __SIZE_TYPE__ __dirlen, wchar_t *__file, __SIZE_TYPE__ __filelen, wchar_t *__ext, __SIZE_TYPE__ __extlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsplitpath_s))(__abspath, __drive, __drivelen, __dir, __dirlen, __file, __filelen, __ext, __extlen); })
#endif /* !__CRT_HAVE__wsplitpath_s */
#endif /* !___wsplitpath_s_defined */
#endif /* !_WSTDLIBP_DEFINED */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */


#ifdef __USE_KOS
#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_WCHAR_FORMAT_PRINTER_H)
#include <parts/wchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_WCHAR_FORMAT_PRINTER_H */

#if defined(_PROCESS_H) && !defined(_PARTS_WCHAR_PROCESS_H)
#include <parts/wchar/process.h>
#endif /* _PROCESS_H && !_PARTS_WCHAR_PROCESS_H */

#if defined(_UTIME_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif /* _UTIME_H && !_PARTS_WCHAR_UTIME_H */

#if defined(_UNISTD_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_WCHAR_UNISTD_H */

#if defined(_STDLIB_H) && !defined(_PARTS_WCHAR_STDLIB_H)
#include <parts/wchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_WCHAR_STDLIB_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_WCHAR_H */
#endif /* __USE_UTF */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CWCHAR 1
#undef _WCHAR_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CWCHAR */
#endif /* !_WCHAR_H */
