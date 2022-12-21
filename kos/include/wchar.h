/* HASH CRC-32:0xfc964dd4 */
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
/* (>) Standard: ISO C95 (ISO/IEC 9899:1990/AMD1:1995) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/wchar.h) */
/* (#) Portability: DJGPP         (/include/wchar.h) */
/* (#) Portability: DragonFly BSD (/include/wchar.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/wchar.h) */
/* (#) Portability: FreeBSD       (/include/wchar.h) */
/* (#) Portability: GNU C Library (/wcsmbs/wchar.h) */
/* (#) Portability: MSVC          (/include/wchar.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/wchar.h) */
/* (#) Portability: NetBSD        (/include/wchar.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/wchar.h) */
/* (#) Portability: OpenBSD       (/include/wchar.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/wchar.h) */
/* (#) Portability: Windows Kits  (/ucrt/wchar.h) */
/* (#) Portability: diet libc     (/include/wchar.h) */
/* (#) Portability: libbsd        (/include/bsd/wchar.h) */
/* (#) Portability: libc6         (/include/wchar.h) */
/* (#) Portability: mintlib       (/include/wchar.h) */
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
#define __mbstate_t_defined
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */
#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined
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
#define __wcstol_defined
__NAMESPACE_STD_USING(wcstol)
#endif /* !__wcstol_defined && __std_wcstol_defined */
#if !defined(__wcstoul_defined) && defined(__std_wcstoul_defined)
#define __wcstoul_defined
__NAMESPACE_STD_USING(wcstoul)
#endif /* !__wcstoul_defined && __std_wcstoul_defined */
__NAMESPACE_STD_USING(mbsinit)
__NAMESPACE_STD_USING(wmemcmp)
__NAMESPACE_STD_USING(wmemcpy)
__NAMESPACE_STD_USING(wmemmove)
__NAMESPACE_STD_USING(wmemset)
#if !defined(__wcscpy_defined) && defined(__std_wcscpy_defined)
#define __wcscpy_defined
__NAMESPACE_STD_USING(wcscpy)
#endif /* !__wcscpy_defined && __std_wcscpy_defined */
#if !defined(__wcscat_defined) && defined(__std_wcscat_defined)
#define __wcscat_defined
__NAMESPACE_STD_USING(wcscat)
#endif /* !__wcscat_defined && __std_wcscat_defined */
#if !defined(__wcsncat_defined) && defined(__std_wcsncat_defined)
#define __wcsncat_defined
__NAMESPACE_STD_USING(wcsncat)
#endif /* !__wcsncat_defined && __std_wcsncat_defined */
#if !defined(__wcsncpy_defined) && defined(__std_wcsncpy_defined)
#define __wcsncpy_defined
__NAMESPACE_STD_USING(wcsncpy)
#endif /* !__wcsncpy_defined && __std_wcsncpy_defined */
#if !defined(__wcscmp_defined) && defined(__std_wcscmp_defined)
#define __wcscmp_defined
__NAMESPACE_STD_USING(wcscmp)
#endif /* !__wcscmp_defined && __std_wcscmp_defined */
#if !defined(__wcsncmp_defined) && defined(__std_wcsncmp_defined)
#define __wcsncmp_defined
__NAMESPACE_STD_USING(wcsncmp)
#endif /* !__wcsncmp_defined && __std_wcsncmp_defined */
#if !defined(__wcscoll_defined) && defined(__std_wcscoll_defined)
#define __wcscoll_defined
__NAMESPACE_STD_USING(wcscoll)
#endif /* !__wcscoll_defined && __std_wcscoll_defined */
#if !defined(__wcsxfrm_defined) && defined(__std_wcsxfrm_defined)
#define __wcsxfrm_defined
__NAMESPACE_STD_USING(wcsxfrm)
#endif /* !__wcsxfrm_defined && __std_wcsxfrm_defined */
#if !defined(__getwchar_defined) && defined(__std_getwchar_defined)
#define __getwchar_defined
__NAMESPACE_STD_USING(getwchar)
#endif /* !__getwchar_defined && __std_getwchar_defined */
#if !defined(__putwchar_defined) && defined(__std_putwchar_defined)
#define __putwchar_defined
__NAMESPACE_STD_USING(putwchar)
#endif /* !__putwchar_defined && __std_putwchar_defined */
#if !defined(__fgetwc_defined) && defined(__std_fgetwc_defined)
#define __fgetwc_defined
__NAMESPACE_STD_USING(fgetwc)
#endif /* !__fgetwc_defined && __std_fgetwc_defined */
#if !defined(__fputwc_defined) && defined(__std_fputwc_defined)
#define __fputwc_defined
__NAMESPACE_STD_USING(fputwc)
#endif /* !__fputwc_defined && __std_fputwc_defined */
#if !defined(__getwc_defined) && defined(__std_getwc_defined)
#define __getwc_defined
__NAMESPACE_STD_USING(getwc)
#endif /* !__getwc_defined && __std_getwc_defined */
#if !defined(__putwc_defined) && defined(__std_putwc_defined)
#define __putwc_defined
__NAMESPACE_STD_USING(putwc)
#endif /* !__putwc_defined && __std_putwc_defined */
#if !defined(__fgetws_defined) && defined(__std_fgetws_defined)
#define __fgetws_defined
__NAMESPACE_STD_USING(fgetws)
#endif /* !__fgetws_defined && __std_fgetws_defined */
#if !defined(__fputws_defined) && defined(__std_fputws_defined)
#define __fputws_defined
__NAMESPACE_STD_USING(fputws)
#endif /* !__fputws_defined && __std_fputws_defined */
#if !defined(__ungetwc_defined) && defined(__std_ungetwc_defined)
#define __ungetwc_defined
__NAMESPACE_STD_USING(ungetwc)
#endif /* !__ungetwc_defined && __std_ungetwc_defined */
#if !defined(__wcsftime_defined) && defined(__std_wcsftime_defined)
#define __wcsftime_defined
__NAMESPACE_STD_USING(wcsftime)
#endif /* !__wcsftime_defined && __std_wcsftime_defined */
#if !defined(__USE_DOS) || defined(__USE_ISOC95)
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
#endif /* !__USE_DOS || __USE_ISOC95 */
#if !defined(__wcslen_defined) && defined(__std_wcslen_defined)
#define __wcslen_defined
__NAMESPACE_STD_USING(wcslen)
#endif /* !__wcslen_defined && __std_wcslen_defined */
#if !defined(__wcsspn_defined) && defined(__std_wcsspn_defined)
#define __wcsspn_defined
__NAMESPACE_STD_USING(wcsspn)
#endif /* !__wcsspn_defined && __std_wcsspn_defined */
#if !defined(__wcscspn_defined) && defined(__std_wcscspn_defined)
#define __wcscspn_defined
__NAMESPACE_STD_USING(wcscspn)
#endif /* !__wcscspn_defined && __std_wcscspn_defined */
#if !defined(__wcschr_defined) && defined(__std_wcschr_defined)
#define __wcschr_defined
__NAMESPACE_STD_USING(wcschr)
#endif /* !__wcschr_defined && __std_wcschr_defined */
#if !defined(__wcsrchr_defined) && defined(__std_wcsrchr_defined)
#define __wcsrchr_defined
__NAMESPACE_STD_USING(wcsrchr)
#endif /* !__wcsrchr_defined && __std_wcsrchr_defined */
#if !defined(__wcspbrk_defined) && defined(__std_wcspbrk_defined)
#define __wcspbrk_defined
__NAMESPACE_STD_USING(wcspbrk)
#endif /* !__wcspbrk_defined && __std_wcspbrk_defined */
#if !defined(__wcsstr_defined) && defined(__std_wcsstr_defined)
#define __wcsstr_defined
__NAMESPACE_STD_USING(wcsstr)
#endif /* !__wcsstr_defined && __std_wcsstr_defined */
__NAMESPACE_STD_USING(wmemchr)
#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
#if !defined(__fwide_defined) && defined(__std_fwide_defined)
#define __fwide_defined
__NAMESPACE_STD_USING(fwide)
#endif /* !__fwide_defined && __std_fwide_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 */
#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#if !defined(__fwprintf_defined) && defined(__std_fwprintf_defined)
#define __fwprintf_defined
#ifdef __PRIVATE_fwprintf_rt
__NAMESPACE_STD_USING(__PRIVATE_fwprintf_rt)
#else /* __PRIVATE_fwprintf_rt */
__NAMESPACE_STD_USING(fwprintf)
#endif /* !__PRIVATE_fwprintf_rt */
#endif /* !__fwprintf_defined && __std_fwprintf_defined */
#if !defined(__vfwprintf_defined) && defined(__std_vfwprintf_defined)
#define __vfwprintf_defined
__NAMESPACE_STD_USING(vfwprintf)
#endif /* !__vfwprintf_defined && __std_vfwprintf_defined */
#if !defined(__wprintf_defined) && defined(__std_wprintf_defined)
#define __wprintf_defined
#ifdef __PRIVATE_wprintf_rt
__NAMESPACE_STD_USING(__PRIVATE_wprintf_rt)
#else /* __PRIVATE_wprintf_rt */
__NAMESPACE_STD_USING(wprintf)
#endif /* !__PRIVATE_wprintf_rt */
#endif /* !__wprintf_defined && __std_wprintf_defined */
#if !defined(__vwprintf_defined) && defined(__std_vwprintf_defined)
#define __vwprintf_defined
__NAMESPACE_STD_USING(vwprintf)
#endif /* !__vwprintf_defined && __std_vwprintf_defined */
#if !defined(__fwscanf_defined) && defined(__std_fwscanf_defined)
#define __fwscanf_defined
#ifdef __PRIVATE_fwscanf_rt
__NAMESPACE_STD_USING(__PRIVATE_fwscanf_rt)
#else /* __PRIVATE_fwscanf_rt */
__NAMESPACE_STD_USING(fwscanf)
#endif /* !__PRIVATE_fwscanf_rt */
#endif /* !__fwscanf_defined && __std_fwscanf_defined */
#if !defined(__wscanf_defined) && defined(__std_wscanf_defined)
#define __wscanf_defined
#ifdef __PRIVATE_wscanf_rt
__NAMESPACE_STD_USING(__PRIVATE_wscanf_rt)
#else /* __PRIVATE_wscanf_rt */
__NAMESPACE_STD_USING(wscanf)
#endif /* !__PRIVATE_wscanf_rt */
#endif /* !__wscanf_defined && __std_wscanf_defined */
#if !defined(__swscanf_defined) && defined(__std_swscanf_defined)
#define __swscanf_defined
#ifdef __PRIVATE_swscanf_rt
__NAMESPACE_STD_USING(__PRIVATE_swscanf_rt)
#else /* __PRIVATE_swscanf_rt */
__NAMESPACE_STD_USING(swscanf)
#endif /* !__PRIVATE_swscanf_rt */
#endif /* !__swscanf_defined && __std_swscanf_defined */
#if !defined(__vswprintf_defined) && defined(__std_vswprintf_defined)
#define __vswprintf_defined
__NAMESPACE_STD_USING(vswprintf)
#endif /* !__vswprintf_defined && __std_vswprintf_defined */
#if !defined(__swprintf_defined) && defined(__std_swprintf_defined)
#define __swprintf_defined
#ifdef __PRIVATE_swprintf_rt
__NAMESPACE_STD_USING(__PRIVATE_swprintf_rt)
#else /* __PRIVATE_swprintf_rt */
__NAMESPACE_STD_USING(swprintf)
#endif /* !__PRIVATE_swprintf_rt */
#endif /* !__swprintf_defined && __std_swprintf_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */
#ifndef __NO_FPU
#if !defined(__wcstod_defined) && defined(__std_wcstod_defined)
#define __wcstod_defined
__NAMESPACE_STD_USING(wcstod)
#endif /* !__wcstod_defined && __std_wcstod_defined */
#endif /* !__NO_FPU */
#ifdef __USE_ISOC99
#ifndef __NO_FPU
#if !defined(__wcstof_defined) && defined(__std_wcstof_defined)
#define __wcstof_defined
__NAMESPACE_STD_USING(wcstof)
#endif /* !__wcstof_defined && __std_wcstof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#if !defined(__wcstold_defined) && defined(__std_wcstold_defined)
#define __wcstold_defined
__NAMESPACE_STD_USING(wcstold)
#endif /* !__wcstold_defined && __std_wcstold_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#if !defined(__wcstoll_defined) && defined(__std_wcstoll_defined)
#define __wcstoll_defined
__NAMESPACE_STD_USING(wcstoll)
#endif /* !__wcstoll_defined && __std_wcstoll_defined */
#if !defined(__wcstoull_defined) && defined(__std_wcstoull_defined)
#define __wcstoull_defined
__NAMESPACE_STD_USING(wcstoull)
#endif /* !__wcstoull_defined && __std_wcstoull_defined */
#if !defined(__vfwscanf_defined) && defined(__std_vfwscanf_defined)
#define __vfwscanf_defined
__NAMESPACE_STD_USING(vfwscanf)
#endif /* !__vfwscanf_defined && __std_vfwscanf_defined */
#if !defined(__vwscanf_defined) && defined(__std_vwscanf_defined)
#define __vwscanf_defined
__NAMESPACE_STD_USING(vwscanf)
#endif /* !__vwscanf_defined && __std_vwscanf_defined */
#if !defined(__vswscanf_defined) && defined(__std_vswscanf_defined)
#define __vswscanf_defined
__NAMESPACE_STD_USING(vswscanf)
#endif /* !__vswscanf_defined && __std_vswscanf_defined */
#endif /* __USE_ISOC99 */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined
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
#define __std_mbstate_t_defined
__NAMESPACE_STD_BEGIN
typedef struct __mbstate mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __mbstate_t_defined
#define __mbstate_t_defined
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

/* Define 'FILE' */
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_btowc
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btowc,(int __ch),(__ch))
#else /* __CRT_HAVE_btowc */
__NAMESPACE_STD_END
#include <libc/local/wchar/btowc.h>
__NAMESPACE_STD_BEGIN
/* >> btowc(3)
 * Convert a single-byte into a wide character. If the given
 * character `ch' isn't valid, or  is `EOF', then `WEOF'  is
 * returned instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(btowc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL btowc)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); })
#endif /* !__CRT_HAVE_btowc */
#ifdef __CRT_HAVE_wctob
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,wctob,(wint_t __ch),(__ch))
#else /* __CRT_HAVE_wctob */
__NAMESPACE_STD_END
#include <libc/local/wchar/wctob.h>
__NAMESPACE_STD_BEGIN
/* >> wctob(3)
 * Convert a wide-character into a single-byte character. If
 * doing so isn't possible, then `EOF' is returned  instead. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wctob, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL wctob)(wint_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctob))(__ch); })
#endif /* !__CRT_HAVE_wctob */
#ifdef __CRT_HAVE_mbrtowc
/* >> mbrtowc(3) */
__CDECLARE(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrtowc)
/* >> mbrtowc(3) */
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),__mbrtowc,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc16) && __SIZEOF_WCHAR_T__ == 2
/* >> mbrtowc(3) */
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtoc16,(__pwc,__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE_mbrtoc32) && __SIZEOF_WCHAR_T__ == 4
/* >> mbrtowc(3) */
__CREDIRECT(__ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs),mbrtoc32,(__pwc,__str,__maxlen,__mbs))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
/* >> mbrtowc(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrtowc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(4) __ATTR_IN_OPT(2) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBCCALL mbrtowc)(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))(__pwc, __str, __maxlen, __mbs); })
#endif /* !... */
#ifdef __CRT_HAVE_wcrtomb
/* >> wcrtomb(3) */
__CDECLARE(__ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs),(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c16rtomb) && __SIZEOF_WCHAR_T__ == 2
/* >> wcrtomb(3) */
__CREDIRECT(__ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs),c16rtomb,(__str,__wc,__mbs))
#elif defined(__CRT_HAVE_c32rtomb) && __SIZEOF_WCHAR_T__ == 4
/* >> wcrtomb(3) */
__CREDIRECT(__ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs),c32rtomb,(__str,__wc,__mbs))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
/* >> wcrtomb(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcrtomb, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBCCALL wcrtomb)(char *__restrict __str, wchar_t __wc, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, __wc, __mbs); })
#endif /* !... */
#ifdef __CRT_HAVE_mbrlen
/* >> mbrlen(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen)
/* >> mbrlen(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),__mbrlen,(__str,__maxlen,__mbs))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbrlen.h>
__NAMESPACE_STD_BEGIN
/* >> mbrlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL mbrlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); })
#endif /* !... */
#ifdef __CRT_HAVE_mbsrtowcs
/* >> mbsrtowcs(3) */
__CDECLARE(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,mbsrtowcs,(wchar_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),(__dst,__psrc,__dstlen,__mbs))
#else /* __CRT_HAVE_mbsrtowcs */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbsrtowcs.h>
__NAMESPACE_STD_BEGIN
/* >> mbsrtowcs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtowcs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBCCALL mbsrtowcs)(wchar_t *__restrict __dst, char const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !__CRT_HAVE_mbsrtowcs */
#ifdef __CRT_HAVE_wcsrtombs
/* >> wcsrtombs(3) */
__CDECLARE(__ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1),size_t,__NOTHROW_NCX,wcsrtombs,(char *__dst, wchar_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs),(__dst,__psrc,__dstlen,__mbs))
#else /* __CRT_HAVE_wcsrtombs */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsrtombs.h>
__NAMESPACE_STD_BEGIN
/* >> wcsrtombs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(4) __ATTR_OUT_OPT(1) size_t __NOTHROW_NCX(__LIBCCALL wcsrtombs)(char *__dst, wchar_t const **__restrict __psrc, size_t __dstlen, mbstate_t *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, __psrc, __dstlen, __mbs); })
#endif /* !__CRT_HAVE_wcsrtombs */
#ifndef __std_wcstol_defined
#define __std_wcstol_defined
#ifdef __wcstol_defined
/* >> wcstol(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return :: wcstol(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstol)
/* >> wcstol(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG__ == 4
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG__ == 8
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG__ == 8
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstol(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstol.h>
__NAMESPACE_STD_BEGIN
/* >> wcstol(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstol_defined */
#ifndef __std_wcstoul_defined
#define __std_wcstoul_defined
#ifdef __wcstoul_defined
/* >> wcstoul(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return :: wcstoul(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstoul)
/* >> wcstoul(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG__ == 4
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG__ == 8
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG__ == 8
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoul(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstoul.h>
__NAMESPACE_STD_BEGIN
/* >> wcstoul(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstoul_defined */
#ifdef __CRT_HAVE_mbsinit
/* >> mbsinit(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN_OPT(1),int,__NOTHROW_NCX,mbsinit,(mbstate_t const *__mbs),(__mbs))
#else /* __CRT_HAVE_mbsinit */
__NAMESPACE_STD_END
#include <libc/local/wchar/mbsinit.h>
__NAMESPACE_STD_BEGIN
/* >> mbsinit(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsinit, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN_OPT(1) int __NOTHROW_NCX(__LIBCCALL mbsinit)(mbstate_t const *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsinit))(__mbs); })
#endif /* !__CRT_HAVE_mbsinit */
#ifdef __CRT_HAVE_wmemcmp
/* >> wmemcmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars),(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memcmpw) && __SIZEOF_WCHAR_T__ == 2
/* >> wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars),memcmpw,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memcmpl) && __SIZEOF_WCHAR_T__ == 4
/* >> wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars),memcmpl,(__s1,__s2,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memcmpw.h>
__NAMESPACE_STD_BEGIN
/* >> wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpw))((void const *)__s1, (void const *)__s2, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memcmpl.h>
__NAMESPACE_STD_BEGIN
/* >> wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmpl))((void const *)__s1, (void const *)__s2, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemcmp.h>
__NAMESPACE_STD_BEGIN
/* >> wmemcmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcmp))(__s1, __s2, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wmemcpy
/* >> wmemcpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && __SIZEOF_WCHAR_T__ == 2
/* >> wmemcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && __SIZEOF_WCHAR_T__ == 4
/* >> wmemcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memcpyw.h>
__NAMESPACE_STD_BEGIN
/* >> wmemcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memcpyl.h>
__NAMESPACE_STD_BEGIN
/* >> wmemcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemcpy.h>
__NAMESPACE_STD_BEGIN
/* >> wmemcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wmemmove
/* >> wmemmove(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew) && __SIZEOF_WCHAR_T__ == 2
/* >> wmemmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel) && __SIZEOF_WCHAR_T__ == 4
/* >> wmemmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memmovew.h>
__NAMESPACE_STD_BEGIN
/* >> wmemmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovew))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memmovel.h>
__NAMESPACE_STD_BEGIN
/* >> wmemmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memmovel))((void *)__dst, (void const *)__src, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemmove.h>
__NAMESPACE_STD_BEGIN
/* >> wmemmove(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemmove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))(__dst, __src, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wmemset
/* >> wmemset(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && __SIZEOF_WCHAR_T__ == 2
/* >> wmemset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && __SIZEOF_WCHAR_T__ == 4
/* >> wmemset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memsetw.h>
__NAMESPACE_STD_BEGIN
/* >> wmemset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetw))((void *)__dst, (__UINT16_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memsetl.h>
__NAMESPACE_STD_BEGIN
/* >> wmemset(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memsetl))((void *)__dst, (__UINT32_TYPE__)__filler, (__SIZE_TYPE__)__num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemset.h>
__NAMESPACE_STD_BEGIN
/* >> wmemset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))(__dst, __filler, __num_chars); })
#endif /* !... */
#ifndef __std_wcscpy_defined
#define __std_wcscpy_defined
#ifdef __wcscpy_defined
/* >> wcscpy(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return :: wcscpy(__buf, __src); })
#elif defined(__CRT_HAVE_wcscpy)
/* >> wcscpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),wchar_t *,__NOTHROW_NCX,wcscpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscpy.h>
__NAMESPACE_STD_BEGIN
/* >> wcscpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))(__buf, __src); })
#endif /* !... */
#endif /* !__std_wcscpy_defined */
#ifndef __std_wcscat_defined
#define __std_wcscat_defined
#ifdef __wcscat_defined
/* >> wcscat(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return :: wcscat(__buf, __src); })
#elif defined(__CRT_HAVE_wcscat)
/* >> wcscat(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcscat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscat.h>
__NAMESPACE_STD_BEGIN
/* >> wcscat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))(__buf, __src); })
#endif /* !... */
#endif /* !__std_wcscat_defined */
#ifndef __std_wcsncat_defined
#define __std_wcsncat_defined
#ifdef __wcsncat_defined
/* >> wcsncat(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return :: wcsncat(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_wcsncat)
/* >> wcsncat(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3),wchar_t *,__NOTHROW_NCX,wcsncat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsncat.h>
__NAMESPACE_STD_BEGIN
/* >> wcsncat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_INS(2, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__std_wcsncat_defined */
#ifndef __std_wcsncpy_defined
#define __std_wcsncpy_defined
#ifdef __wcsncpy_defined
/* >> wcsncpy(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return :: wcsncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_wcsncpy)
/* >> wcsncpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wcsncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsncpy.h>
__NAMESPACE_STD_BEGIN
/* >> wcsncpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))(__buf, __src, __buflen); })
#endif /* !... */
#endif /* !__std_wcsncpy_defined */
#ifndef __std_wcscmp_defined
#define __std_wcscmp_defined
#ifdef __wcscmp_defined
/* >> wcscmp(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return :: wcscmp(__s1, __s2); })
#elif defined(__CRT_HAVE_wcscmp)
/* >> wcscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscmp.h>
__NAMESPACE_STD_BEGIN
/* >> wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))(__s1, __s2); })
#endif /* !... */
#endif /* !__std_wcscmp_defined */
#ifndef __std_wcsncmp_defined
#define __std_wcsncmp_defined
#ifdef __wcsncmp_defined
/* >> wcsncmp(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return :: wcsncmp(__s1, __s2, __maxlen); })
#elif defined(__CRT_HAVE_wcsncmp)
/* >> wcsncmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen),(__s1,__s2,__maxlen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsncmp.h>
__NAMESPACE_STD_BEGIN
/* >> wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#endif /* !__std_wcsncmp_defined */
#ifndef __std_wcscoll_defined
#define __std_wcscoll_defined
#ifdef __wcscoll_defined
/* >> wcscoll(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return :: wcscoll(__s1, __s2); })
#elif defined(__CRT_HAVE_wcscoll)
/* >> wcscoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscoll.h>
__NAMESPACE_STD_BEGIN
/* >> wcscoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))(__s1, __s2); })
#endif /* !... */
#endif /* !__std_wcscoll_defined */
#ifndef __std_wcsxfrm_defined
#define __std_wcsxfrm_defined
#ifdef __wcsxfrm_defined
/* >> wcsxfrm(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __buflen) { return :: wcsxfrm(__dst, __src, __buflen); })
#elif defined(__CRT_HAVE_wcsxfrm)
/* >> wcsxfrm(3) */
__CDECLARE(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),size_t,__NOTHROW_NCX,wcsxfrm,(wchar_t *__dst, wchar_t const *__restrict __src, size_t __buflen),(__dst,__src,__buflen))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsxfrm.h>
__NAMESPACE_STD_BEGIN
/* >> wcsxfrm(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) size_t __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))(__dst, __src, __buflen); })
#endif /* !... */
#endif /* !__std_wcsxfrm_defined */
#ifndef __std_getwchar_defined
#define __std_getwchar_defined
#ifdef __getwchar_defined
/* >> getwchar(3), getwchar_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(getwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL getwchar)(void) __THROWS(...) { return :: getwchar(); })
#elif defined(__CRT_HAVE_getwchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> getwchar(3), getwchar_unlocked(3) */
__CREDIRECT(,wint_t,__THROWING,getwchar,(void),getwchar_unlocked,())
#elif defined(__CRT_HAVE_getwchar)
/* >> getwchar(3), getwchar_unlocked(3) */
__CDECLARE(,wint_t,__THROWING,getwchar,(void),())
#elif defined(__CRT_HAVE__fgetwchar)
/* >> getwchar(3), getwchar_unlocked(3) */
__CREDIRECT(,wint_t,__THROWING,getwchar,(void),_fgetwchar,())
#elif defined(__CRT_HAVE_getwchar_unlocked)
/* >> getwchar(3), getwchar_unlocked(3) */
__CREDIRECT(,wint_t,__THROWING,getwchar,(void),getwchar_unlocked,())
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked))
__NAMESPACE_STD_END
#include <libc/local/wchar/getwchar.h>
__NAMESPACE_STD_BEGIN
/* >> getwchar(3), getwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL getwchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); })
#else /* __LOCAL_stdin && (__CRT_HAVE_fgetwc || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked) */
#undef __std_getwchar_defined
#endif /* !__LOCAL_stdin || (!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked) */
#endif /* !... */
#endif /* !__std_getwchar_defined */
#ifndef __std_putwchar_defined
#define __std_putwchar_defined
#ifdef __putwchar_defined
/* >> putwchar(3), putwchar_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(putwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL putwchar)(wchar_t __wc) __THROWS(...) { return :: putwchar(__wc); })
#elif defined(__CRT_HAVE_putwchar_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> putwchar(3), putwchar_unlocked(3) */
__CREDIRECT(,wint_t,__THROWING,putwchar,(wchar_t __wc),putwchar_unlocked,(__wc))
#elif defined(__CRT_HAVE_putwchar)
/* >> putwchar(3), putwchar_unlocked(3) */
__CDECLARE(,wint_t,__THROWING,putwchar,(wchar_t __wc),(__wc))
#elif defined(__CRT_HAVE__fputwchar)
/* >> putwchar(3), putwchar_unlocked(3) */
__CREDIRECT(,wint_t,__THROWING,putwchar,(wchar_t __wc),_fputwchar,(__wc))
#elif defined(__CRT_HAVE_putwchar_unlocked)
/* >> putwchar(3), putwchar_unlocked(3) */
__CREDIRECT(,wint_t,__THROWING,putwchar,(wchar_t __wc),putwchar_unlocked,(__wc))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
__NAMESPACE_STD_END
#include <libc/local/wchar/putwchar.h>
__NAMESPACE_STD_BEGIN
/* >> putwchar(3), putwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar, __FORCELOCAL __ATTR_ARTIFICIAL wint_t (__LIBCCALL putwchar)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); })
#else /* __LOCAL_stdout && (__CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) */
#undef __std_putwchar_defined
#endif /* !__LOCAL_stdout || (!__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) */
#endif /* !... */
#endif /* !__std_putwchar_defined */
#ifndef __std_fgetwc_defined
#define __std_fgetwc_defined
#ifdef __fgetwc_defined
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(fgetwc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) wint_t (__LIBCCALL fgetwc)(FILE *__restrict __stream) __THROWS(...) { return :: fgetwc(__stream); })
#elif defined(__CRT_HAVE_fgetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(1),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,fgetwc,(FILE *__restrict __stream),getwc_unlocked,(__stream))
#else /* ... */
#undef __std_fgetwc_defined
#endif /* !... */
#endif /* !__std_fgetwc_defined */
#ifndef __std_fputwc_defined
#define __std_fputwc_defined
#ifdef __fputwc_defined
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(fputwc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) wint_t (__LIBCCALL fputwc)(wchar_t __wc, FILE *__stream) __THROWS(...) { return :: fputwc(__wc, __stream); })
#elif defined(__CRT_HAVE_fputwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(2),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,fputwc,(wchar_t __wc, FILE *__stream),putwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __std_fputwc_defined
#endif /* !... */
#endif /* !__std_fputwc_defined */
#ifndef __std_getwc_defined
#define __std_getwc_defined
#if defined(__CRT_HAVE_fgetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,getwc,(FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,getwc,(FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,getwc,(FILE *__restrict __stream),fgetwc,(__stream))
#elif defined(__CRT_HAVE_getwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(1),wint_t,__THROWING,getwc,(FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,getwc,(FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),wint_t,__THROWING,getwc,(FILE *__restrict __stream),getwc_unlocked,(__stream))
#else /* ... */
#undef __std_getwc_defined
#endif /* !... */
#endif /* !__std_getwc_defined */
#ifndef __std_putwc_defined
#define __std_putwc_defined
#if defined(__CRT_HAVE_fputwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),fputwc,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(2),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__THROWING,putwc,(wchar_t __wc, FILE *__stream),putwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __std_putwc_defined
#endif /* !... */
#endif /* !__std_putwc_defined */
#ifndef __std_fgetws_defined
#define __std_fgetws_defined
#ifdef __fgetws_defined
/* >> fgetws(3), fgetws_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(fgetws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2) wchar_t *(__LIBCCALL fgetws)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return :: fgetws(__buf, __bufsize, __stream); })
#elif defined(__CRT_HAVE_fgetws_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetws(3), fgetws_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fgetws(3), fgetws_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws)
/* >> fgetws(3), fgetws_unlocked(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws_unlocked)
/* >> fgetws(3), fgetws_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock)
/* >> fgetws(3), fgetws_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_STD_END
#include <libc/local/wchar/fgetws.h>
__NAMESPACE_STD_BEGIN
/* >> fgetws(3), fgetws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2) wchar_t *(__LIBCCALL fgetws)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))(__buf, __bufsize, __stream); })
#else /* ... */
#undef __std_fgetws_defined
#endif /* !... */
#endif /* !__std_fgetws_defined */
#ifndef __std_fputws_defined
#define __std_fputws_defined
#ifdef __fputws_defined
/* >> fputws(3), fputws_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(fputws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(2) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws)(wchar_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return :: fputws(__str, __stream); })
#elif defined(__CRT_HAVE_fputws_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fputws(3), fputws_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock) && defined(__USE_STDIO_UNLOCKED)
/* >> fputws(3), fputws_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_fputws)
/* >> fputws(3), fputws_unlocked(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),(__str,__stream))
#elif defined(__CRT_HAVE_fputws_unlocked)
/* >> fputws(3), fputws_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),fputws_unlocked,(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock)
/* >> fputws(3), fputws_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws,(wchar_t const *__restrict __str, FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)
__NAMESPACE_STD_END
#include <libc/local/wchar/fputws.h>
__NAMESPACE_STD_BEGIN
/* >> fputws(3), fputws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(2) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws)(wchar_t const *__restrict __str, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))(__str, __stream); })
#else /* ... */
#undef __std_fputws_defined
#endif /* !... */
#endif /* !__std_fputws_defined */
#ifndef __std_ungetwc_defined
#define __std_ungetwc_defined
#ifdef __ungetwc_defined
/* >> ungetwc(3), ungetwc_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(ungetwc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) wint_t __NOTHROW_NCX(__LIBCCALL ungetwc)(wint_t __wc, FILE *__stream) { return :: ungetwc(__wc, __stream); })
#elif defined(__CRT_HAVE_ungetwc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> ungetwc(3), ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc)
/* >> ungetwc(3), ungetwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(2),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked)
/* >> ungetwc(3), ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#else /* ... */
#undef __std_ungetwc_defined
#endif /* !... */
#endif /* !__std_ungetwc_defined */
#ifndef __std_wcsftime_defined
#define __std_wcsftime_defined
#ifdef __wcsftime_defined
/* >> wcsftime(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcsftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2) size_t __NOTHROW_NCX(__LIBCCALL wcsftime)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) { return :: wcsftime(__buf, __buflen, __format, __tp); })
#elif defined(__CRT_HAVE_wcsftime)
/* >> wcsftime(3) */
__CDECLARE(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2),size_t,__NOTHROW_NCX,wcsftime,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),(__buf,__buflen,__format,__tp))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsftime.h>
__NAMESPACE_STD_BEGIN
/* >> wcsftime(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2) size_t __NOTHROW_NCX(__LIBCCALL wcsftime)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */
#endif /* !__std_wcsftime_defined */

#if !defined(__USE_DOS) || defined(__USE_ISOC95)
#ifndef __std_wcstok_defined
#define __std_wcstok_defined
#ifdef __wcstok_defined
/* >> wcstok(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return :: wcstok(__str, __delim, __save_ptr); })
#elif defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_STD_BEGIN
/* >> wcstok(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__str, __delim, __save_ptr); })
#endif /* !... */
#endif /* !__std_wcstok_defined */
#endif /* !__USE_DOS || __USE_ISOC95 */
#ifndef __std_wcslen_defined
#define __std_wcslen_defined
#ifdef __wcslen_defined
/* >> wcslen(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __str) { return :: wcslen(__str); })
#elif defined(__CRT_HAVE_wcslen)
/* >> wcslen(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),size_t,__NOTHROW_NCX,wcslen,(wchar_t const *__restrict __str),(__str))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_STD_BEGIN
/* >> wcslen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) size_t __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))(__str); })
#endif /* !... */
#endif /* !__std_wcslen_defined */
#ifndef __std_wcsspn_defined
#define __std_wcsspn_defined
#ifdef __wcsspn_defined
/* >> wcsspn(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return :: wcsspn(__haystack, __accept); })
#elif defined(__CRT_HAVE_wcsspn)
/* >> wcsspn(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,wcsspn,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsspn.h>
__NAMESPACE_STD_BEGIN
/* >> wcsspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))(__haystack, __accept); })
#endif /* !... */
#endif /* !__std_wcsspn_defined */
#ifndef __std_wcscspn_defined
#define __std_wcscspn_defined
#ifdef __wcscspn_defined
/* >> wcscspn(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return :: wcscspn(__haystack, __reject); })
#elif defined(__CRT_HAVE_wcscspn)
/* >> wcscspn(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),size_t,__NOTHROW_NCX,wcscspn,(wchar_t const *__haystack, wchar_t const *__reject),(__haystack,__reject))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcscspn.h>
__NAMESPACE_STD_BEGIN
/* >> wcscspn(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) size_t __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))(__haystack, __reject); })
#endif /* !... */
#endif /* !__std_wcscspn_defined */
#ifndef __std_wcschr_defined
#define __std_wcschr_defined
#ifdef __wcschr_defined
/* >> wcschr(3) */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcschr)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return :: wcschr(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return :: wcschr(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return :: wcschr(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcschr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
/* >> wcschr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t const *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcschr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
/* >> wcschr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcschr_defined */
#ifndef __std_wcsrchr_defined
#define __std_wcsrchr_defined
#ifdef __wcsrchr_defined
/* >> wcsrchr(3) */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcsrchr)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return :: wcsrchr(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return :: wcsrchr(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return :: wcsrchr(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcsrchr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
/* >> wcsrchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t const *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsrchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
/* >> wcsrchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcsrchr_defined */
#ifndef __std_wcspbrk_defined
#define __std_wcspbrk_defined
#ifdef __wcspbrk_defined
/* >> wcspbrk(3) */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcspbrk)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return :: wcspbrk(__haystack, __accept); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return :: wcspbrk(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return :: wcspbrk(__haystack, __accept); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcspbrk)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
/* >> wcspbrk(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t const *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),wcspbrk,(__haystack,__accept))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcspbrk.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
/* >> wcspbrk(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcspbrk(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspbrk, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcspbrk_defined */
#ifndef __std_wcsstr_defined
#define __std_wcsstr_defined
#ifdef __wcsstr_defined
/* >> wcsstr(3) */
#if !defined(__COMPILER_HAVE_BUG_BLOATY_CXX_USING) || defined(__NO_NAMESPACE_STD)
__NAMESPACE_GLB_USING(wcsstr)
#else /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING || __NO_NAMESPACE_STD */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return :: wcsstr(__haystack, __needle); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return :: wcsstr(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return :: wcsstr(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING && !__NO_NAMESPACE_STD */
#elif defined(__CRT_HAVE_wcsstr)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcsstr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__std_wcsstr_defined */
#ifdef __CRT_HAVE_wmemchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),wmemchr,(__haystack,__needle,__num_chars))
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),wmemchr,(__haystack,__needle,__num_chars))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wmemchr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),(__haystack,__needle,__num_chars))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_memchrw) && __SIZEOF_WCHAR_T__ == 2
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_memchrl) && __SIZEOF_WCHAR_T__ == 4
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wmemchr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/memchrw.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))((void const *)__haystack, (__UINT16_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))((void const *)__haystack, (__UINT16_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrw))((void const *)__haystack, (__UINT16_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/memchrl.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))((void const *)__haystack, (__UINT32_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ const *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))((void const *)__haystack, (__UINT32_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchrl))((void const *)__haystack, (__UINT32_TYPE__)__needle, (__SIZE_TYPE__)__num_chars); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmemchr.h>
__NAMESPACE_STD_BEGIN
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); }
/* >> wmemchr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wmemchr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
#ifndef __std_fwide_defined
#define __std_fwide_defined
#ifdef __fwide_defined
/* >> fwide(3) */
__NAMESPACE_GLB_USING_OR_IMPL(fwide, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL fwide)(FILE *__fp, int __mode) { return :: fwide(__fp, __mode); })
#elif defined(__CRT_HAVE_fwide)
/* >> fwide(3) */
__CDECLARE(__ATTR_INOUT(1),int,__NOTHROW_NCX,fwide,(FILE *__fp, int __mode),(__fp,__mode))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/fwide.h>
__NAMESPACE_STD_BEGIN
/* >> fwide(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fwide, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL fwide)(FILE *__fp, int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwide))(__fp, __mode); })
#endif /* !... */
#endif /* !__std_fwide_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 */

#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#ifndef __std_fwprintf_defined
#define __std_fwprintf_defined
#ifdef __fwprintf_defined
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
#ifdef __PRIVATE_fwprintf_rt
__NAMESPACE_GLB_USING(__PRIVATE_fwprintf_rt)
#elif __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(fwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return :: fwprintf(__stream, __format, __builtin_va_arg_pack()); })
#else /* ... */
__NAMESPACE_GLB_USING(fwprintf)
#endif /* !... */
#elif defined(__CRT_HAVE_fwprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_fwprintf)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf");
#elif defined(__CRT_HAVE_fwprintf_unlocked)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)
__NAMESPACE_STD_END
#include <libc/local/wchar/fwprintf.h>
__NAMESPACE_STD_BEGIN
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
typedef __STDC_INT_AS_SIZE_T __PRIVATE_fwprintf_rt;
#define __PRIVATE_fwprintf_rt __PRIVATE_fwprintf_rt
#define fwprintf(...) __PRIVATE_fwprintf_rt((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))(__VA_ARGS__))
#else /* ... */
#define fwprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))(__VA_ARGS__)
#endif /* !... */
#else /* ... */
#undef __std_fwprintf_defined
#endif /* !... */
#endif /* !__std_fwprintf_defined */
#ifndef __std_vfwprintf_defined
#define __std_vfwprintf_defined
#ifdef __vfwprintf_defined
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(vfwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return :: vfwprintf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfwprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwprintf)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwprintf_unlocked)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwprintf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)
__NAMESPACE_STD_END
#include <libc/local/wchar/vfwprintf.h>
__NAMESPACE_STD_BEGIN
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, __format, __args); })
#else /* ... */
#undef __std_vfwprintf_defined
#endif /* !... */
#endif /* !__std_vfwprintf_defined */
#ifndef __std_wprintf_defined
#define __std_wprintf_defined
#ifdef __wprintf_defined
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
#ifdef __PRIVATE_wprintf_rt
__NAMESPACE_GLB_USING(__PRIVATE_wprintf_rt)
#elif __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(wprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return :: wprintf(__format, __builtin_va_arg_pack()); })
#else /* ... */
__NAMESPACE_GLB_USING(wprintf)
#endif /* !... */
#elif defined(__CRT_HAVE_wprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf_unlocked");
#elif defined(__CRT_HAVE_wprintf)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf");
#elif defined(__CRT_HAVE_wprintf_unlocked)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf_unlocked");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vwprintf) || defined(__CRT_HAVE_vwprintf_unlocked) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)))
__NAMESPACE_STD_END
#include <libc/local/wchar/wprintf.h>
__NAMESPACE_STD_BEGIN
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(wprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))(__format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
typedef __STDC_INT_AS_SIZE_T __PRIVATE_wprintf_rt;
#define __PRIVATE_wprintf_rt __PRIVATE_wprintf_rt
#define wprintf(...) __PRIVATE_wprintf_rt((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))(__VA_ARGS__))
#else /* ... */
#define wprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))(__VA_ARGS__)
#endif /* !... */
#else /* __CRT_HAVE_vwprintf || __CRT_HAVE_vwprintf_unlocked || (__LOCAL_stdout && (__CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked)) */
#undef __std_wprintf_defined
#endif /* !__CRT_HAVE_vwprintf && !__CRT_HAVE_vwprintf_unlocked && (!__LOCAL_stdout || (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked)) */
#endif /* !... */
#endif /* !__std_wprintf_defined */
#ifndef __std_vwprintf_defined
#define __std_vwprintf_defined
#ifdef __vwprintf_defined
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(vwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return :: vwprintf(__format, __args); })
#elif defined(__CRT_HAVE_vwprintf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf,(wchar_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#elif defined(__CRT_HAVE_vwprintf)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vwprintf_unlocked)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf,(wchar_t const *__restrict __format, __builtin_va_list __args),vwprintf_unlocked,(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked))
__NAMESPACE_STD_END
#include <libc/local/wchar/vwprintf.h>
__NAMESPACE_STD_BEGIN
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))(__format, __args); })
#else /* __LOCAL_stdout && (__CRT_HAVE_vfwprintf || __CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_fputwc || __CRT_HAVE_putwc || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked) */
#undef __std_vwprintf_defined
#endif /* !__LOCAL_stdout || (!__CRT_HAVE_vfwprintf && !__CRT_HAVE_vfwprintf_unlocked && !__CRT_HAVE_file_wprinter && !__CRT_HAVE_file_wprinter_unlocked && !__CRT_HAVE_fputwc && !__CRT_HAVE_putwc && !__CRT_HAVE_fputwc_unlocked && !__CRT_HAVE_putwc_unlocked) */
#endif /* !... */
#endif /* !__std_vwprintf_defined */
#ifndef __std_fwscanf_defined
#define __std_fwscanf_defined
#ifdef __fwscanf_defined
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
#ifdef __PRIVATE_fwscanf_rt
__NAMESPACE_GLB_USING(__PRIVATE_fwscanf_rt)
#elif __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(fwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return :: fwscanf(__stream, __format, __builtin_va_arg_pack()); })
#else /* ... */
__NAMESPACE_GLB_USING(fwscanf)
#endif /* !... */
#elif defined(__CRT_HAVE_fwscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_fwscanf)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf");
#elif defined(__CRT_HAVE_fwscanf_unlocked)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))
__NAMESPACE_STD_END
#include <libc/local/wchar/fwscanf.h>
__NAMESPACE_STD_BEGIN
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))(__stream, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
typedef __STDC_INT_AS_SIZE_T __PRIVATE_fwscanf_rt;
#define __PRIVATE_fwscanf_rt __PRIVATE_fwscanf_rt
#define fwscanf(...) __PRIVATE_fwscanf_rt((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))(__VA_ARGS__))
#else /* ... */
#define fwscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))(__VA_ARGS__)
#endif /* !... */
#else /* ... */
#undef __std_fwscanf_defined
#endif /* !... */
#endif /* !__std_fwscanf_defined */
#ifndef __std_wscanf_defined
#define __std_wscanf_defined
#ifdef __wscanf_defined
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
#ifdef __PRIVATE_wscanf_rt
__NAMESPACE_GLB_USING(__PRIVATE_wscanf_rt)
#elif __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(wscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return :: wscanf(__format, __builtin_va_arg_pack()); })
#else /* ... */
__NAMESPACE_GLB_USING(wscanf)
#endif /* !... */
#elif defined(__CRT_HAVE_wscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf_unlocked");
#elif defined(__CRT_HAVE_wscanf)
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf");
#elif defined(__CRT_HAVE_wscanf_unlocked)
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf_unlocked");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__CRT_HAVE_vwscanf) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)))))
__NAMESPACE_STD_END
#include <libc/local/wchar/wscanf.h>
__NAMESPACE_STD_BEGIN
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(wscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))(__format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
typedef __STDC_INT_AS_SIZE_T __PRIVATE_wscanf_rt;
#define __PRIVATE_wscanf_rt __PRIVATE_wscanf_rt
#define wscanf(...) __PRIVATE_wscanf_rt((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))(__VA_ARGS__))
#else /* ... */
#define wscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))(__VA_ARGS__)
#endif /* !... */
#else /* __CRT_HAVE_vwscanf || (__LOCAL_stdin && (__CRT_HAVE_vfwscanf || __CRT_HAVE_vfwscanf_unlocked || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked)))) */
#undef __std_wscanf_defined
#endif /* !__CRT_HAVE_vwscanf && (!__LOCAL_stdin || (!__CRT_HAVE_vfwscanf && !__CRT_HAVE_vfwscanf_unlocked && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked)))) */
#endif /* !... */
#endif /* !__std_wscanf_defined */
#ifndef __std_swscanf_defined
#define __std_swscanf_defined
#ifdef __swscanf_defined
/* >> swscanf(3), vswscanf(3) */
#ifdef __PRIVATE_swscanf_rt
__NAMESPACE_GLB_USING(__PRIVATE_swscanf_rt)
#elif __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(swscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) { return :: swscanf(__src, __format, __builtin_va_arg_pack()); })
#else /* ... */
__NAMESPACE_GLB_USING(swscanf)
#endif /* !... */
#elif defined(__CRT_HAVE_swscanf)
/* >> swscanf(3), vswscanf(3) */
__LIBC __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swscanf");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/swscanf.h>
__NAMESPACE_STD_BEGIN
/* >> swscanf(3), vswscanf(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(swscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))(__src, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
typedef __STDC_INT_AS_SIZE_T __PRIVATE_swscanf_rt;
#define __PRIVATE_swscanf_rt __PRIVATE_swscanf_rt
#define swscanf(...) __PRIVATE_swscanf_rt((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))(__VA_ARGS__))
#else /* ... */
#define swscanf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))(__VA_ARGS__)
#endif /* !... */
#endif /* !... */
#endif /* !__std_swscanf_defined */
#ifndef __std_vswprintf_defined
#define __std_vswprintf_defined
#ifdef __vswprintf_defined
/* >> vswprintf(3) */
__NAMESPACE_GLB_USING_OR_IMPL(vswprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return :: vswprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vswprintf)
/* >> vswprintf(3) */
__CDECLARE(__ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswprintf,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/vswprintf.h>
__NAMESPACE_STD_BEGIN
/* >> vswprintf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vswprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); })
#endif /* !... */
#endif /* !__std_vswprintf_defined */
#ifndef __std_swprintf_defined
#define __std_swprintf_defined
#ifdef __swprintf_defined
/* >> swprintf(3) */
#ifdef __PRIVATE_swprintf_rt
__NAMESPACE_GLB_USING(__PRIVATE_swprintf_rt)
#elif __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_GLB_USING_OR_IMPL(swprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 4) __ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) { return :: swprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#else /* ... */
__NAMESPACE_GLB_USING(swprintf)
#endif /* !... */
#elif defined(__CRT_HAVE_swprintf)
/* >> swprintf(3) */
__LIBC __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 4) __ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swprintf");
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/swprintf.h>
__NAMESPACE_STD_BEGIN
/* >> swprintf(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(swprintf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 4) __ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__cplusplus)
typedef __STDC_INT_AS_SIZE_T __PRIVATE_swprintf_rt;
#define __PRIVATE_swprintf_rt __PRIVATE_swprintf_rt
#define swprintf(...) __PRIVATE_swprintf_rt((__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))(__VA_ARGS__))
#else /* ... */
#define swprintf(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))(__VA_ARGS__)
#endif /* !... */
#endif /* !... */
#endif /* !__std_swprintf_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

#ifndef __NO_FPU
#ifndef __std_wcstod_defined
#define __std_wcstod_defined
#ifdef __wcstod_defined
/* >> wcstod(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return :: wcstod(__nptr, __endptr); })
#elif defined(__CRT_HAVE_wcstod)
/* >> wcstod(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,wcstod,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstod.h>
__NAMESPACE_STD_BEGIN
/* >> wcstod(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_wcstod_defined */
#endif /* !__NO_FPU */
#ifdef __USE_ISOC99
#ifndef __NO_FPU
#ifndef __std_wcstof_defined
#define __std_wcstof_defined
#ifdef __wcstof_defined
/* >> wcstof(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return :: wcstof(__nptr, __endptr); })
#elif defined(__CRT_HAVE_wcstof)
/* >> wcstof(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,wcstof,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstof.h>
__NAMESPACE_STD_BEGIN
/* >> wcstof(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_wcstof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_wcstold_defined
#define __std_wcstold_defined
#ifdef __wcstold_defined
/* >> wcstold(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return :: wcstold(__nptr, __endptr); })
#elif defined(__CRT_HAVE_wcstold)
/* >> wcstold(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,wcstold,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstold.h>
__NAMESPACE_STD_BEGIN
/* >> wcstold(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__std_wcstold_defined */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifndef __std_wcstoll_defined
#define __std_wcstoll_defined
#ifdef __wcstoll_defined
/* >> wcstoll(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return :: wcstoll(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll)
/* >> wcstoll(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstoll.h>
__NAMESPACE_STD_BEGIN
/* >> wcstoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstoll_defined */
#ifndef __std_wcstoull_defined
#define __std_wcstoull_defined
#ifdef __wcstoull_defined
/* >> wcstoull(3) */
__NAMESPACE_GLB_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return :: wcstoull(__nptr, __endptr, __base); })
#elif defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull)
/* >> wcstoull(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wcstoull.h>
__NAMESPACE_STD_BEGIN
/* >> wcstoull(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__std_wcstoull_defined */
#ifndef __std_vfwscanf_defined
#define __std_vfwscanf_defined
#ifdef __vfwscanf_defined
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__NAMESPACE_GLB_USING_OR_IMPL(vfwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return :: vfwscanf(__stream, __format, __args); })
#elif defined(__CRT_HAVE_vfwscanf_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf_unlocked)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf_unlocked,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))
__NAMESPACE_STD_END
#include <libc/local/wchar/vfwscanf.h>
__NAMESPACE_STD_BEGIN
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwscanf))(__stream, __format, __args); })
#else /* ... */
#undef __std_vfwscanf_defined
#endif /* !... */
#endif /* !__std_vfwscanf_defined */
#ifndef __std_vwscanf_defined
#define __std_vwscanf_defined
#ifdef __vwscanf_defined
/* >> vwscanf(3) */
__NAMESPACE_GLB_USING_OR_IMPL(vwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return :: vwscanf(__format, __args); })
#elif defined(__CRT_HAVE_vwscanf)
/* >> vwscanf(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/template/stdstreams.h>
__NAMESPACE_STD_BEGIN
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE_vfwscanf_unlocked) || ((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked))))
__NAMESPACE_STD_END
#include <libc/local/wchar/vwscanf.h>
__NAMESPACE_STD_BEGIN
/* >> vwscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))(__format, __args); })
#else /* __LOCAL_stdin && (__CRT_HAVE_vfwscanf || __CRT_HAVE_vfwscanf_unlocked || ((__CRT_HAVE_fgetwc || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked) && (__CRT_HAVE_ungetwc || __CRT_HAVE_ungetwc_unlocked))) */
#undef __std_vwscanf_defined
#endif /* !__LOCAL_stdin || (!__CRT_HAVE_vfwscanf && !__CRT_HAVE_vfwscanf_unlocked && ((!__CRT_HAVE_fgetwc && !__CRT_HAVE_getwc && !__CRT_HAVE_fgetwc_unlocked && !__CRT_HAVE_getwc_unlocked) || (!__CRT_HAVE_ungetwc && !__CRT_HAVE_ungetwc_unlocked))) */
#endif /* !... */
#endif /* !__std_vwscanf_defined */
#ifndef __std_vswscanf_defined
#define __std_vswscanf_defined
#ifdef __vswscanf_defined
/* >> swscanf(3), vswscanf(3) */
__NAMESPACE_GLB_USING_OR_IMPL(vswscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf)(wchar_t const *__restrict __input, wchar_t const *__restrict __format, __builtin_va_list __args) { return :: vswscanf(__input, __format, __args); })
#elif defined(__CRT_HAVE_vswscanf)
/* >> swscanf(3), vswscanf(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswscanf,(wchar_t const *__restrict __input, wchar_t const *__restrict __format, __builtin_va_list __args),(__input,__format,__args))
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/vswscanf.h>
__NAMESPACE_STD_BEGIN
/* >> swscanf(3), vswscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vswscanf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf)(wchar_t const *__restrict __input, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))(__input, __format, __args); })
#endif /* !... */
#endif /* !__std_vswscanf_defined */
#endif /* __USE_ISOC99 */
#ifndef __std_wcstok_defined
#define __std_wcstok_defined
#ifdef __wcstok_defined
/* >> wcstok(3)
 * Define wcstok() incorrectly, the same way DOS does */
__NAMESPACE_GLB_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT_OPT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim) { return :: wcstok(__str, __delim); })
#elif defined(__CRT_HAVE_wcstok) && defined(__CRT_DOS_PRIMARY)
__NAMESPACE_STD_END
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined
#ifdef __CRT_HAVE_wcstok_s
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* __CRT_HAVE_wcstok_s */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_LOCAL_BEGIN
/* >> wcstok(3) */
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !__CRT_HAVE_wcstok_s */
#endif /* !__local___localdep_wcstok_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_STD_BEGIN
/* >> wcstok(3)
 * Define wcstok() incorrectly, the same way DOS does */
__CEIDECLARE(__ATTR_IN(2) __ATTR_INOUT_OPT(1),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__str, wchar_t const *__restrict __delim),{ static wchar_t *__save_ptr = __NULLPTR; return (__NAMESPACE_LOCAL_SYM __localdep_wcstok)(__str, __delim, &__save_ptr); })
#else /* ... */
__NAMESPACE_STD_END
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined
#if defined(__CRT_HAVE_wcstok) && !defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__str,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s) && defined(__CRT_DOS_PRIMARY)
/* >> wcstok(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1),wchar_t *,__NOTHROW_NCX,__localdep_wcstok,(wchar_t *__str, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__str,__delim,__save_ptr))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcstok.h>
__NAMESPACE_LOCAL_BEGIN
/* >> wcstok(3) */
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !... */
#endif /* !__local___localdep_wcstok_defined */
__NAMESPACE_LOCAL_END
__NAMESPACE_STD_BEGIN
/* >> wcstok(3)
 * Define wcstok() incorrectly, the same way DOS does */
__LOCAL __ATTR_IN(2) __ATTR_INOUT_OPT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__str, wchar_t const *__restrict __delim) { static wchar_t *__save_ptr = __NULLPTR; return (__NAMESPACE_LOCAL_SYM __localdep_wcstok)(__str, __delim, &__save_ptr); }
#endif /* !... */
#endif /* !__std_wcstok_defined */
#ifdef __CRT_HAVE_wmempmove
/* >> wmempmove(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovew) && __SIZEOF_WCHAR_T__ == 2
/* >> wmempmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovel) && __SIZEOF_WCHAR_T__ == 4
/* >> wmempmove(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_STD_END
#include <libc/local/string/mempmovew.h>
__NAMESPACE_STD_BEGIN
/* >> wmempmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovew))((void *)__dst, (void const *)__src, __num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_STD_END
#include <libc/local/string/mempmovel.h>
__NAMESPACE_STD_BEGIN
/* >> wmempmove(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempmovel))((void *)__dst, (void const *)__src, __num_chars); }
#else /* ... */
__NAMESPACE_STD_END
#include <libc/local/wchar/wmempmove.h>
__NAMESPACE_STD_BEGIN
/* >> wmempmove(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempmove, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))(__dst, __src, __num_chars); })
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
#define __wcstol_defined
__NAMESPACE_STD_USING(wcstol)
#endif /* !__wcstol_defined && __std_wcstol_defined */
#if !defined(__wcstoul_defined) && defined(__std_wcstoul_defined)
#define __wcstoul_defined
__NAMESPACE_STD_USING(wcstoul)
#endif /* !__wcstoul_defined && __std_wcstoul_defined */
__NAMESPACE_STD_USING(mbsinit)
__NAMESPACE_STD_USING(wmemcmp)
__NAMESPACE_STD_USING(wmemcpy)
__NAMESPACE_STD_USING(wmemmove)
__NAMESPACE_STD_USING(wmemset)
#if !defined(__wcscpy_defined) && defined(__std_wcscpy_defined)
#define __wcscpy_defined
__NAMESPACE_STD_USING(wcscpy)
#endif /* !__wcscpy_defined && __std_wcscpy_defined */
#if !defined(__wcscat_defined) && defined(__std_wcscat_defined)
#define __wcscat_defined
__NAMESPACE_STD_USING(wcscat)
#endif /* !__wcscat_defined && __std_wcscat_defined */
#if !defined(__wcsncat_defined) && defined(__std_wcsncat_defined)
#define __wcsncat_defined
__NAMESPACE_STD_USING(wcsncat)
#endif /* !__wcsncat_defined && __std_wcsncat_defined */
#if !defined(__wcsncpy_defined) && defined(__std_wcsncpy_defined)
#define __wcsncpy_defined
__NAMESPACE_STD_USING(wcsncpy)
#endif /* !__wcsncpy_defined && __std_wcsncpy_defined */
#if !defined(__wcscmp_defined) && defined(__std_wcscmp_defined)
#define __wcscmp_defined
__NAMESPACE_STD_USING(wcscmp)
#endif /* !__wcscmp_defined && __std_wcscmp_defined */
#if !defined(__wcsncmp_defined) && defined(__std_wcsncmp_defined)
#define __wcsncmp_defined
__NAMESPACE_STD_USING(wcsncmp)
#endif /* !__wcsncmp_defined && __std_wcsncmp_defined */
#if !defined(__wcscoll_defined) && defined(__std_wcscoll_defined)
#define __wcscoll_defined
__NAMESPACE_STD_USING(wcscoll)
#endif /* !__wcscoll_defined && __std_wcscoll_defined */
#if !defined(__wcsxfrm_defined) && defined(__std_wcsxfrm_defined)
#define __wcsxfrm_defined
__NAMESPACE_STD_USING(wcsxfrm)
#endif /* !__wcsxfrm_defined && __std_wcsxfrm_defined */
#if !defined(__getwchar_defined) && defined(__std_getwchar_defined)
#define __getwchar_defined
__NAMESPACE_STD_USING(getwchar)
#endif /* !__getwchar_defined && __std_getwchar_defined */
#if !defined(__putwchar_defined) && defined(__std_putwchar_defined)
#define __putwchar_defined
__NAMESPACE_STD_USING(putwchar)
#endif /* !__putwchar_defined && __std_putwchar_defined */
#if !defined(__fgetwc_defined) && defined(__std_fgetwc_defined)
#define __fgetwc_defined
__NAMESPACE_STD_USING(fgetwc)
#endif /* !__fgetwc_defined && __std_fgetwc_defined */
#if !defined(__fputwc_defined) && defined(__std_fputwc_defined)
#define __fputwc_defined
__NAMESPACE_STD_USING(fputwc)
#endif /* !__fputwc_defined && __std_fputwc_defined */
#if !defined(__getwc_defined) && defined(__std_getwc_defined)
#define __getwc_defined
__NAMESPACE_STD_USING(getwc)
#endif /* !__getwc_defined && __std_getwc_defined */
#if !defined(__putwc_defined) && defined(__std_putwc_defined)
#define __putwc_defined
__NAMESPACE_STD_USING(putwc)
#endif /* !__putwc_defined && __std_putwc_defined */
#if !defined(__fgetws_defined) && defined(__std_fgetws_defined)
#define __fgetws_defined
__NAMESPACE_STD_USING(fgetws)
#endif /* !__fgetws_defined && __std_fgetws_defined */
#if !defined(__fputws_defined) && defined(__std_fputws_defined)
#define __fputws_defined
__NAMESPACE_STD_USING(fputws)
#endif /* !__fputws_defined && __std_fputws_defined */
#if !defined(__ungetwc_defined) && defined(__std_ungetwc_defined)
#define __ungetwc_defined
__NAMESPACE_STD_USING(ungetwc)
#endif /* !__ungetwc_defined && __std_ungetwc_defined */
#if !defined(__wcsftime_defined) && defined(__std_wcsftime_defined)
#define __wcsftime_defined
__NAMESPACE_STD_USING(wcsftime)
#endif /* !__wcsftime_defined && __std_wcsftime_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#if !defined(__USE_DOS) || defined(__USE_ISOC95)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__USE_DOS || __USE_ISOC95 */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcslen_defined) && defined(__std_wcslen_defined)
#define __wcslen_defined
__NAMESPACE_STD_USING(wcslen)
#endif /* !__wcslen_defined && __std_wcslen_defined */
#if !defined(__wcsspn_defined) && defined(__std_wcsspn_defined)
#define __wcsspn_defined
__NAMESPACE_STD_USING(wcsspn)
#endif /* !__wcsspn_defined && __std_wcsspn_defined */
#if !defined(__wcscspn_defined) && defined(__std_wcscspn_defined)
#define __wcscspn_defined
__NAMESPACE_STD_USING(wcscspn)
#endif /* !__wcscspn_defined && __std_wcscspn_defined */
#if !defined(__wcschr_defined) && defined(__std_wcschr_defined)
#define __wcschr_defined
__NAMESPACE_STD_USING(wcschr)
#endif /* !__wcschr_defined && __std_wcschr_defined */
#if !defined(__wcsrchr_defined) && defined(__std_wcsrchr_defined)
#define __wcsrchr_defined
__NAMESPACE_STD_USING(wcsrchr)
#endif /* !__wcsrchr_defined && __std_wcsrchr_defined */
#if !defined(__wcspbrk_defined) && defined(__std_wcspbrk_defined)
#define __wcspbrk_defined
__NAMESPACE_STD_USING(wcspbrk)
#endif /* !__wcspbrk_defined && __std_wcspbrk_defined */
#if !defined(__wcsstr_defined) && defined(__std_wcsstr_defined)
#define __wcsstr_defined
__NAMESPACE_STD_USING(wcsstr)
#endif /* !__wcsstr_defined && __std_wcsstr_defined */
__NAMESPACE_STD_USING(wmemchr)
#endif /* !__CXX_SYSTEM_HEADER */
#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__fwide_defined) && defined(__std_fwide_defined)
#define __fwide_defined
__NAMESPACE_STD_USING(fwide)
#endif /* !__fwide_defined && __std_fwide_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC95 || __USE_UNIX98 */
#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__fwprintf_defined) && defined(__std_fwprintf_defined)
#define __fwprintf_defined
#ifdef __PRIVATE_fwprintf_rt
__NAMESPACE_STD_USING(__PRIVATE_fwprintf_rt)
#else /* __PRIVATE_fwprintf_rt */
__NAMESPACE_STD_USING(fwprintf)
#endif /* !__PRIVATE_fwprintf_rt */
#endif /* !__fwprintf_defined && __std_fwprintf_defined */
#if !defined(__vfwprintf_defined) && defined(__std_vfwprintf_defined)
#define __vfwprintf_defined
__NAMESPACE_STD_USING(vfwprintf)
#endif /* !__vfwprintf_defined && __std_vfwprintf_defined */
#if !defined(__wprintf_defined) && defined(__std_wprintf_defined)
#define __wprintf_defined
#ifdef __PRIVATE_wprintf_rt
__NAMESPACE_STD_USING(__PRIVATE_wprintf_rt)
#else /* __PRIVATE_wprintf_rt */
__NAMESPACE_STD_USING(wprintf)
#endif /* !__PRIVATE_wprintf_rt */
#endif /* !__wprintf_defined && __std_wprintf_defined */
#if !defined(__vwprintf_defined) && defined(__std_vwprintf_defined)
#define __vwprintf_defined
__NAMESPACE_STD_USING(vwprintf)
#endif /* !__vwprintf_defined && __std_vwprintf_defined */
#if !defined(__fwscanf_defined) && defined(__std_fwscanf_defined)
#define __fwscanf_defined
#ifdef __PRIVATE_fwscanf_rt
__NAMESPACE_STD_USING(__PRIVATE_fwscanf_rt)
#else /* __PRIVATE_fwscanf_rt */
__NAMESPACE_STD_USING(fwscanf)
#endif /* !__PRIVATE_fwscanf_rt */
#endif /* !__fwscanf_defined && __std_fwscanf_defined */
#if !defined(__wscanf_defined) && defined(__std_wscanf_defined)
#define __wscanf_defined
#ifdef __PRIVATE_wscanf_rt
__NAMESPACE_STD_USING(__PRIVATE_wscanf_rt)
#else /* __PRIVATE_wscanf_rt */
__NAMESPACE_STD_USING(wscanf)
#endif /* !__PRIVATE_wscanf_rt */
#endif /* !__wscanf_defined && __std_wscanf_defined */
#if !defined(__swscanf_defined) && defined(__std_swscanf_defined)
#define __swscanf_defined
#ifdef __PRIVATE_swscanf_rt
__NAMESPACE_STD_USING(__PRIVATE_swscanf_rt)
#else /* __PRIVATE_swscanf_rt */
__NAMESPACE_STD_USING(swscanf)
#endif /* !__PRIVATE_swscanf_rt */
#endif /* !__swscanf_defined && __std_swscanf_defined */
#if !defined(__vswprintf_defined) && defined(__std_vswprintf_defined)
#define __vswprintf_defined
__NAMESPACE_STD_USING(vswprintf)
#endif /* !__vswprintf_defined && __std_vswprintf_defined */
#if !defined(__swprintf_defined) && defined(__std_swprintf_defined)
#define __swprintf_defined
#ifdef __PRIVATE_swprintf_rt
__NAMESPACE_STD_USING(__PRIVATE_swprintf_rt)
#else /* __PRIVATE_swprintf_rt */
__NAMESPACE_STD_USING(swprintf)
#endif /* !__PRIVATE_swprintf_rt */
#endif /* !__swprintf_defined && __std_swprintf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstod_defined) && defined(__std_wcstod_defined)
#define __wcstod_defined
__NAMESPACE_STD_USING(wcstod)
#endif /* !__wcstod_defined && __std_wcstod_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */
#ifdef __USE_ISOC99
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstof_defined) && defined(__std_wcstof_defined)
#define __wcstof_defined
__NAMESPACE_STD_USING(wcstof)
#endif /* !__wcstof_defined && __std_wcstof_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstold_defined) && defined(__std_wcstold_defined)
#define __wcstold_defined
__NAMESPACE_STD_USING(wcstold)
#endif /* !__wcstold_defined && __std_wcstold_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstoll_defined) && defined(__std_wcstoll_defined)
#define __wcstoll_defined
__NAMESPACE_STD_USING(wcstoll)
#endif /* !__wcstoll_defined && __std_wcstoll_defined */
#if !defined(__wcstoull_defined) && defined(__std_wcstoull_defined)
#define __wcstoull_defined
__NAMESPACE_STD_USING(wcstoull)
#endif /* !__wcstoull_defined && __std_wcstoull_defined */
#if !defined(__vfwscanf_defined) && defined(__std_vfwscanf_defined)
#define __vfwscanf_defined
__NAMESPACE_STD_USING(vfwscanf)
#endif /* !__vfwscanf_defined && __std_vfwscanf_defined */
#if !defined(__vwscanf_defined) && defined(__std_vwscanf_defined)
#define __vwscanf_defined
__NAMESPACE_STD_USING(vwscanf)
#endif /* !__vwscanf_defined && __std_vwscanf_defined */
#if !defined(__vswscanf_defined) && defined(__std_vswscanf_defined)
#define __vswscanf_defined
__NAMESPACE_STD_USING(vswscanf)
#endif /* !__vswscanf_defined && __std_vswscanf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_ISOC99 */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && __std_wcstok_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_mbrlen
/* >> mbrlen(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),mbrlen,(__str,__maxlen,__mbs))
#elif defined(__CRT_HAVE___mbrlen)
/* >> mbrlen(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,__mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs),(__str,__maxlen,__mbs))
#else /* ... */
#include <libc/local/wchar/mbrlen.h>
/* >> mbrlen(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT_OPT(3) __ATTR_IN_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __mbrlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __mbs); }
#endif /* !... */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wcscasecmp
/* >> wcscasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
/* >> wcscasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecmp.h>
/* >> wcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscasecmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp
/* >> wcsncasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
/* >> wcsncasecmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp.h>
/* >> wcsncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecmp_l
/* >> wcscasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
/* >> wcscasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecmp_l.h>
/* >> wcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecmp_l
/* >> wcsncasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l)
/* >> wcsncasecmp_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecmp_l.h>
/* >> wcsncasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcsncasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscoll_l
/* >> wcscoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
/* >> wcscoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscoll_l.h>
/* >> wcscoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsxfrm_l
/* >> wcsxfrm_l(3) */
__CDECLARE(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__buflen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
/* >> wcsxfrm_l(3) */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__buflen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsxfrm_l.h>
/* >> wcsxfrm_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __buflen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcpcpy
/* >> wcpcpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),wchar_t *,__NOTHROW_NCX,wcpcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src),(__dst,__src))
#else /* __CRT_HAVE_wcpcpy */
#include <libc/local/wchar/wcpcpy.h>
/* >> wcpcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcpcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcpcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcpcpy))(__dst, __src); })
#endif /* !__CRT_HAVE_wcpcpy */
#ifdef __CRT_HAVE_wcpncpy
/* >> wcpncpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wcpncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* __CRT_HAVE_wcpncpy */
#include <libc/local/wchar/wcpncpy.h>
/* >> wcpncpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcpncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wcpncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcpncpy))(__buf, __src, __buflen); })
#endif /* !__CRT_HAVE_wcpncpy */
#ifdef __CRT_HAVE_mbsnrtowcs
/* >> mbsnrtowcs(3) */
__CDECLARE(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtowcs,(wchar_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs),(__dst,__psrc,__nmc,__dstlen,__mbs))
#else /* __CRT_HAVE_mbsnrtowcs */
#include <libc/local/wchar/mbsnrtowcs.h>
/* >> mbsnrtowcs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsnrtowcs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL mbsnrtowcs)(wchar_t *__restrict __dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsnrtowcs))(__dst, __psrc, __nmc, __dstlen, __mbs); })
#endif /* !__CRT_HAVE_mbsnrtowcs */
#ifdef __CRT_HAVE_wcsnrtombs
/* >> wcsnrtombs(3) */
__CDECLARE(__ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_NCX,wcsnrtombs,(char *__dst, wchar_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs),(__dst,__psrc,__nwc,__dstlen,__mbs))
#else /* __CRT_HAVE_wcsnrtombs */
#include <libc/local/wchar/wcsnrtombs.h>
/* >> wcsnrtombs(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrtombs, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(2) __ATTR_INOUT_OPT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnrtombs)(char *__dst, wchar_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, size_t __dstlen, struct __mbstate *__mbs) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrtombs))(__dst, __psrc, __nwc, __dstlen, __mbs); })
#endif /* !__CRT_HAVE_wcsnrtombs */
/* >> open_wmemstream(3) */
__CDECLARE_OPT(,__FILE *,__NOTHROW_NCX,open_wmemstream,(wchar_t **__bufloc, __SIZE_TYPE__ *__sizeloc),(__bufloc,__sizeloc))
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#ifndef __wcsnlen_defined
#define __wcsnlen_defined
#ifdef __CRT_HAVE_wcsnlen
/* >> wcsnlen(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#elif defined(__CRT_HAVE___wcsncnt)
/* >> wcsnlen(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),__wcsncnt,(__str,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnlen.h>
/* >> wcsnlen(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlen, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))(__str, __maxlen); })
#endif /* !... */
#endif /* !__wcsnlen_defined */
#ifndef __wcsdup_defined
#define __wcsdup_defined
#ifdef __CRT_HAVE_wcsdup
/* >> wcsdup(3) */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__wcsdup)
/* >> wcsdup(3) */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsdup.h>
/* >> wcsdup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); })
#else /* ... */
#undef __wcsdup_defined
#endif /* !... */
#endif /* !__wcsdup_defined */
#endif /* __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_wcwidth
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,wcwidth,(wchar_t __ch),(__ch))
#else /* __CRT_HAVE_wcwidth */
#include <libc/local/wchar/wcwidth.h>
/* >> wcwidth(3)
 * Returns the number of columns needed to display `ch' in a system terminal
 * When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
 * never modified by this function). Zero-width characters return `0'. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcwidth, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL wcwidth)(wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))(__ch); })
#endif /* !__CRT_HAVE_wcwidth */
#ifdef __CRT_HAVE_wcswidth
/* >> wcswidth(3)
 * Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
 * in a system terminal. If any of the contained characters cannot be printed, then
 * `-1' is returned. (s.a. `wcwidth(3)') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__STDC_INT32_AS_SSIZE_T,__NOTHROW_NCX,wcswidth,(wchar_t const *__restrict __str, __SIZE_TYPE__ __num_chars),(__str,__num_chars))
#else /* __CRT_HAVE_wcswidth */
#include <libc/local/wchar/wcswidth.h>
/* >> wcswidth(3)
 * Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
 * in a system terminal. If any of the contained characters cannot be printed, then
 * `-1' is returned. (s.a. `wcwidth(3)') */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcswidth, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) __STDC_INT32_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL wcswidth)(wchar_t const *__restrict __str, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcswidth))(__str, __num_chars); })
#endif /* !__CRT_HAVE_wcswidth */
#endif /* __USE_XOPEN */

#ifdef __USE_XOPEN
#ifndef __wcswcs_defined
#define __wcswcs_defined
#ifdef __CRT_HAVE_wcsstr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#elif defined(__CRT_HAVE_wcswcs)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack,__needle))
/* >> wcsstr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* ... */
#include <libc/local/wchar/wcsstr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsstr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !... */
#endif /* !__wcswcs_defined */
#endif /* __USE_XOPEN */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_wcschrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcschrnul,(wchar_t *__restrict __haystack, wchar_t __needle),wcschrnul,(__haystack,__needle))
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t const *,__NOTHROW_NCX,wcschrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcschrnul,(wchar_t const *__haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcschrnul */
#include <libc/local/wchar/wcschrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); }
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcschrnul(3)
 * Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t const *__haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcschrnul */
#ifdef __CRT_HAVE_wmempcpy
/* >> wmempcpy(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw) && __SIZEOF_WCHAR_T__ == 2
/* >> wmempcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl) && __SIZEOF_WCHAR_T__ == 4
/* >> wmempcpy(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/string/mempcpyw.h>
/* >> wmempcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyw))((void *)__dst, (void const *)__src, __num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/string/mempcpyl.h>
/* >> wmempcpy(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpyl))((void *)__dst, (void const *)__src, __num_chars); }
#else /* ... */
#include <libc/local/wchar/wmempcpy.h>
/* >> wmempcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))(__dst, __src, __num_chars); })
#endif /* !... */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(wmempmove)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_wcstol_l
/* >> wcstol_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstol_l.h>
/* >> wcstol_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBCCALL wcstol_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoul_l
/* >> wcstoul_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoul_l.h>
/* >> wcstoul_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll)
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq)
/* >> wcstoll(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstoll.h>
/* >> wcstoll(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoq)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull)
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq)
/* >> wcstoull(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstoull.h>
/* >> wcstoull(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstouq)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); }
#endif /* !... */

#ifdef __LONGLONG
#ifdef __CRT_HAVE_wcstoll_l
/* >> wcstoll_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoll_l.h>
/* >> wcstoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstoull_l
/* >> wcstoull_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoull_l.h>
/* >> wcstoull_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __LONGLONG */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_wcstof_l
/* >> wcstof_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstof_l.h>
/* >> wcstof_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBCCALL wcstof_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcstod_l
/* >> wcstod_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstod_l.h>
/* >> wcstod_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBCCALL wcstod_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_wcstold_l
/* >> wcstold_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstold_l.h>
/* >> wcstold_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))(__nptr, __endptr, __locale); })
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_getwchar_unlocked
/* >> getwchar(3), getwchar_unlocked(3) */
__CDECLARE(,__WINT_TYPE__,__THROWING,getwchar_unlocked,(void),())
#elif defined(__CRT_HAVE_getwchar)
/* >> getwchar(3), getwchar_unlocked(3) */
__CREDIRECT(,__WINT_TYPE__,__THROWING,getwchar_unlocked,(void),getwchar,())
#else /* ... */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc))
#include <libc/local/wchar/getwchar_unlocked.h>
/* >> getwchar(3), getwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT_TYPE__ (__LIBCCALL getwchar_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); })
#endif /* __LOCAL_stdin && (__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) */
#endif /* !... */
#ifdef __CRT_HAVE_putwchar_unlocked
/* >> putwchar(3), putwchar_unlocked(3) */
__CDECLARE(,__WINT_TYPE__,__THROWING,putwchar_unlocked,(wchar_t __wc),(__wc))
#elif defined(__CRT_HAVE_putwchar)
/* >> putwchar(3), putwchar_unlocked(3) */
__CREDIRECT(,__WINT_TYPE__,__THROWING,putwchar_unlocked,(wchar_t __wc),putwchar,(__wc))
#else /* ... */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc))
#include <libc/local/wchar/putwchar_unlocked.h>
/* >> putwchar(3), putwchar_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __WINT_TYPE__ (__LIBCCALL putwchar_unlocked)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))(__wc); })
#endif /* __LOCAL_stdout && (__CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_putwc || __CRT_HAVE_fputwc) */
#endif /* !... */
#ifdef __CRT_HAVE_fgetwc_unlocked
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__getwc_nolock)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_getwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,getwc_unlocked,(__FILE *__restrict __stream),fgetwc,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fputwc_unlocked
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#elif defined(__CRT_HAVE__putwc_nolock)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),fputwc,(__wc,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fgetwc_unlocked
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_getwc_unlocked)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),getwc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getwc_nolock)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),_getwc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_getwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),getwc,(__stream))
#elif defined(__CRT_HAVE_fgetwc)
/* >> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(1),__WINT_TYPE__,__THROWING,fgetwc_unlocked,(__FILE *__restrict __stream),fgetwc,(__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fputwc_unlocked
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#elif defined(__CRT_HAVE_putwc_unlocked)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),putwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE__putwc_nolock)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_putwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_putwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),putwc,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc)
/* >> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__THROWING,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),fputwc,(__wc,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_fgetws_unlocked
/* >> fgetws(3), fgetws_unlocked(3) */
__CDECLARE(__ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE__fgetws_nolock)
/* >> fgetws(3), fgetws_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream))
#elif defined(__CRT_HAVE_fgetws)
/* >> fgetws(3), fgetws_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(3) __ATTR_OUTS(1, 2),wchar_t *,__THROWING,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <libc/local/wchar/fgetws_unlocked.h>
/* >> fgetws(3), fgetws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(3) __ATTR_OUTS(1, 2) wchar_t *(__LIBCCALL fgetws_unlocked)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))(__buf, __bufsize, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_fputws_unlocked
/* >> fputws(3), fputws_unlocked(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws_unlocked,(wchar_t const *__restrict __str, __FILE *__restrict __stream),(__str,__stream))
#elif defined(__CRT_HAVE__fputws_nolock)
/* >> fputws(3), fputws_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws_unlocked,(wchar_t const *__restrict __str, __FILE *__restrict __stream),_fputws_nolock,(__str,__stream))
#elif defined(__CRT_HAVE_fputws)
/* >> fputws(3), fputws_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT(2),__STDC_INT_AS_SIZE_T,__THROWING,fputws_unlocked,(wchar_t const *__restrict __str, __FILE *__restrict __stream),fputws,(__str,__stream))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)
#include <libc/local/wchar/fputws_unlocked.h>
/* >> fputws(3), fputws_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT(2) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws_unlocked)(wchar_t const *__restrict __str, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))(__str, __stream); })
#endif /* ... */
#ifdef __CRT_HAVE_wcsftime_l
/* >> wcsftime_l(3) */
__CDECLARE(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#else /* ... */
#include <libc/local/wchar/wcsftime_l.h>
/* >> wcsftime_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_IN(4) __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_OUTS(1, 2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsftime_l)(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_GNU */




#ifdef __USE_KOS
/* Static initializer for `mbstate_t':
 * >> mbstate_t mbs = MBSTATE_INIT; */
#if !defined(MBSTATE_INIT) && defined(__MBSTATE_INIT)
#define MBSTATE_INIT __MBSTATE_INIT
#endif /* !MBSTATE_INIT && __MBSTATE_INIT */

/* Dynamic initializer for `mbstate_t':
 * >> mbstate_t mbs;
 * >> mbstate_init(&mbs); */
#if !defined(mbstate_init) && defined(__mbstate_init)
#define mbstate_init __mbstate_init
#endif /* !mbstate_init && __mbstate_init */

/* Check if the given mbstate_t is in its zero-shift state:
 * >> if (mbstate_isempty(&mbs)) { ... } */
#if !defined(mbstate_isempty) && defined(__mbstate_isempty)
#define mbstate_isempty __mbstate_isempty
#endif /* !mbstate_isempty && __mbstate_isempty */

/* KOS FILE extension functions. */

#if defined(__CRT_HAVE_file_wprinter_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CDECLARE(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter_unlocked)
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked)
#include <libc/local/wchar/file_wprinter.h>
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_wprinter, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ (__LIBCCALL file_wprinter)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, __data, __datalen); })
#endif /* ... */
#ifdef __CRT_HAVE_file_wprinter_unlocked
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CDECLARE(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,file_wprinter_unlocked,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_file_wprinter)
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,file_wprinter_unlocked,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)
#include <libc/local/wchar/file_wprinter_unlocked.h>
/* >> file_wprinter(3), file_wprinter_unlocked(3)
 * For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_wprinter_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__ (__LIBCCALL file_wprinter_unlocked)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, __data, __datalen); })
#endif /* ... */
#ifdef __CRT_HAVE_ungetwc_unlocked
/* >> ungetwc(3), ungetwc_unlocked(3) */
__CDECLARE(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
/* >> ungetwc(3), ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
/* >> ungetwc(3), ungetwc_unlocked(3) */
__CREDIRECT(__ATTR_INOUT(2),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#endif /* ... */
#ifdef __CRT_HAVE_vfwprintf_unlocked
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__CDECLARE(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwprintf)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwprintf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args))
#elif defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)
#include <libc/local/wchar/vfwprintf_unlocked.h>
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_fwprintf_unlocked
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_fwprintf)
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
__LIBC __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwprintf");
#elif defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)
#include <libc/local/wchar/fwprintf_unlocked.h>
/* >> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fwprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define fwprintf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_wprintf_unlocked
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf_unlocked");
#elif defined(__CRT_HAVE_wprintf)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__LIBC __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wprintf");
#else /* ... */
#include <libc/template/stdstreams.h>
#if defined(__CRT_HAVE_vwprintf_unlocked) || defined(__CRT_HAVE_vwprintf) || (defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc)))
#include <libc/local/wchar/wprintf_unlocked.h>
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(wprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define wprintf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_vwprintf_unlocked || __CRT_HAVE_vwprintf || (__LOCAL_stdout && (__CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_putwc || __CRT_HAVE_fputwc)) */
#endif /* !... */
#ifdef __CRT_HAVE_vwprintf_unlocked
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vwprintf)
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwprintf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),vwprintf,(__format,__args))
#else /* ... */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdout) && (defined(__CRT_HAVE_vfwprintf_unlocked) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE_putwc_unlocked) || defined(__CRT_HAVE__putwc_nolock) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_fputwc))
#include <libc/local/wchar/vwprintf_unlocked.h>
/* >> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf_unlocked)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))(__format, __args); })
#endif /* __LOCAL_stdout && (__CRT_HAVE_vfwprintf_unlocked || __CRT_HAVE_vfwprintf || __CRT_HAVE_file_wprinter_unlocked || __CRT_HAVE_file_wprinter || __CRT_HAVE_fputwc_unlocked || __CRT_HAVE_putwc_unlocked || __CRT_HAVE__putwc_nolock || __CRT_HAVE__fputwc_nolock || __CRT_HAVE_putwc || __CRT_HAVE_fputwc) */
#endif /* !... */
#ifdef __CRT_HAVE_vfwscanf_unlocked
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args))
#elif defined(__CRT_HAVE_vfwscanf)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__THROWING,vfwscanf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args))
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))
#include <libc/local/wchar/vfwscanf_unlocked.h>
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwscanf_unlocked))(__stream, __format, __args); })
#endif /* ... */
#ifdef __CRT_HAVE_vwscanf_unlocked
/* >> vwscanf(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args))
#elif defined(__CRT_HAVE_vwscanf)
/* >> vwscanf(3) */
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SIZE_T,__THROWING,vwscanf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),vwscanf,(__format,__args))
#else /* ... */
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc))))
#include <libc/local/wchar/vwscanf_unlocked.h>
/* >> vwscanf(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf_unlocked)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))(__format, __args); })
#endif /* __LOCAL_stdin && (__CRT_HAVE_vfwscanf_unlocked || __CRT_HAVE_vfwscanf || ((__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc))) */
#endif /* !... */
#ifdef __CRT_HAVE_fwscanf_unlocked
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_fwscanf)
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)))
#include <libc/local/wchar/fwscanf_unlocked.h>
/* >> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(fwscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))(__stream, __format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define fwscanf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* ... */
#ifdef __CRT_HAVE_wscanf_unlocked
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf_unlocked");
#elif defined(__CRT_HAVE_wscanf)
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
__LIBC __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME("wscanf");
#else /* ... */
#include <libc/template/stdstreams.h>
#if defined(__CRT_HAVE_vwscanf_unlocked) || defined(__CRT_HAVE_vwscanf) || (defined(__LOCAL_stdin) && (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf) || ((defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE_getwc_unlocked) || defined(__CRT_HAVE__getwc_nolock) || defined(__CRT_HAVE__fgetwc_nolock) || defined(__CRT_HAVE_getwc) || defined(__CRT_HAVE_fgetwc)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE__ungetwc_nolock) || defined(__CRT_HAVE_ungetwc)))))
#include <libc/local/wchar/wscanf_unlocked.h>
/* >> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3) */
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(wscanf_unlocked, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))(__format, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define wscanf_unlocked(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __CRT_HAVE_vwscanf_unlocked || __CRT_HAVE_vwscanf || (__LOCAL_stdin && (__CRT_HAVE_vfwscanf_unlocked || __CRT_HAVE_vfwscanf || ((__CRT_HAVE_fgetwc_unlocked || __CRT_HAVE_getwc_unlocked || __CRT_HAVE__getwc_nolock || __CRT_HAVE__fgetwc_nolock || __CRT_HAVE_getwc || __CRT_HAVE_fgetwc) && (__CRT_HAVE_ungetwc_unlocked || __CRT_HAVE__ungetwc_nolock || __CRT_HAVE_ungetwc)))) */
#endif /* !... */




#ifdef __CRT_HAVE_wcsend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsend,(wchar_t *__restrict __str),wcsend,(__str))
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t const *,__NOTHROW_NCX,wcsend,(wchar_t const *__restrict __str),wcsend,(__str))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsend,(wchar_t const *__restrict __str),(__str))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsend */
#include <libc/local/wchar/wcsend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__str); }
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__str); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsend(3)
 * Same as `str + wcslen(str)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t const *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__str); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsend */
#ifdef __CRT_HAVE_wcsnend
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnend,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnend,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),wcsnend,(__str,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnend,(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnend */
#include <libc/local/wchar/wcsnend.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__str, __maxlen); }
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__str, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnend(3)
 * Same as `str + wcsnlen(str, max_chars)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t const *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__str, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnend */
#ifdef __CRT_HAVE_wcsto32_r
/* >> wcsto32_r(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcsto32_r */
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcsto32_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcsto32_r */
#ifdef __CRT_HAVE_wcstou32_r
/* >> wcstou32_r(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcstou32_r */
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstou32_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcstou32_r */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32)
/* >> wcsto32(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcsto32.h>
/* >> wcsto32(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32)
/* >> wcstou32(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstou32.h>
/* >> wcstou32(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))(__nptr, __endptr, __base); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_wcsto64_r
/* >> wcsto64_r(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcsto64_r */
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcsto64_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcsto64_r */
#ifdef __CRT_HAVE_wcstou64_r
/* >> wcstou64_r(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),(__nptr,__endptr,__base,__error))
#else /* __CRT_HAVE_wcstou64_r */
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstou64_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))(__nptr, __endptr, __base, __error); })
#endif /* !__CRT_HAVE_wcstou64_r */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64)
/* >> wcsto64(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcsto64.h>
/* >> wcsto64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))(__nptr, __endptr, __base); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64)
/* >> wcstou64(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstou64.h>
/* >> wcstou64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#if defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG__ == 4
/* >> wcstol_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,wcstol_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG__ == 8
/* >> wcstol_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),long,__NOTHROW_NCX,wcstol_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBCCALL wcstol_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcstol_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBCCALL wcstol_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstol_r.h>
/* >> wcstol_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) long __NOTHROW_NCX(__LIBCCALL wcstol_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG__ == 4
/* >> wcstoul_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,wcstoul_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG__ == 8
/* >> wcstoul_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),unsigned long,__NOTHROW_NCX,wcstoul_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG__ == 4
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG__ == 8
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstoul_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (unsigned long)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstoul_r.h>
/* >> wcstoul_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#ifdef __LONGLONG
#if defined(__CRT_HAVE_wcsto64_r) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,wcstoll_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcsto32_r) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoll_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__LONGLONG,__NOTHROW_NCX,wcstoll_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcsto32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/wchar/wcsto64_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/wchar/wcsto32_r.h>
/* >> wcstoll_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__LONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstoll_r.h>
/* >> wcstoll_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstou64_r) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,wcstoull_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou64_r,(__nptr,__endptr,__base,__error))
#elif defined(__CRT_HAVE_wcstou32_r) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstoull_r(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4),__ULONGLONG,__NOTHROW_NCX,wcstoull_r,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error),wcstou32_r,(__nptr,__endptr,__base,__error))
#elif __SIZEOF_LONG_LONG__ == 8
#include <libc/local/wchar/wcstou64_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_r))(__nptr, __endptr, __base, __error); }
#elif __SIZEOF_LONG_LONG__ == 4
#include <libc/local/wchar/wcstou32_r.h>
/* >> wcstoull_r(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__ULONGLONG)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_r))(__nptr, __endptr, __base, __error); }
#else /* ... */
#include <libc/local/wchar/wcstoull_r.h>
/* >> wcstoull_r(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_r)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_r))(__nptr, __endptr, __base, __error); })
#endif /* !... */
#endif /* __LONGLONG */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto32_l)
/* >> wcsto32_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcsto32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT32_TYPE__,__NOTHROW_NCX,wcsto32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcsto32_l.h>
/* >> wcsto32_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou32_l)
/* >> wcstou32_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 4
/* >> wcstou32_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstou32_l.h>
/* >> wcstou32_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */

#ifdef __UINT64_TYPE__
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l)
/* >> wcsto64_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,wcsto64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcsto64_l.h>
/* >> wcsto64_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l)
/* >> wcstou64_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstou64_l.h>
/* >> wcstou64_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))(__nptr, __endptr, __base, __locale); })
#endif /* !... */
#endif /* __UINT64_TYPE__ */
#endif /* __USE_XOPEN2K8 */

#ifdef __CRT_HAVE_wcsncoll
/* >> wcsncoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll)
/* >> wcsncoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncoll.h>
/* >> wcsncoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll
/* >> wcscasecoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicoll)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicoll,(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
/* >> wcscasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* ... */
#include <libc/local/wchar/wcscasecoll.h>
/* >> wcscasecoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscasecoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll
/* >> wcsncasecoll(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicoll)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
/* >> wcsncasecoll(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll.h>
/* >> wcsncasecoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsnrev
/* >> wcsnrev(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrev,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnrev */
#include <libc/local/wchar/wcsnrev.h>
/* >> wcsnrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrev)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnrev */
#ifdef __CRT_HAVE_wcsnlwr
/* >> wcsnlwr(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnlwr,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnlwr */
#include <libc/local/wchar/wcsnlwr.h>
/* >> wcsnlwr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnlwr)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlwr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnlwr */
#ifdef __CRT_HAVE_wcsnupr
/* >> wcsnupr(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnupr,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* __CRT_HAVE_wcsnupr */
#include <libc/local/wchar/wcsnupr.h>
/* >> wcsnupr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnupr)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnupr))(__str, __maxlen); })
#endif /* !__CRT_HAVE_wcsnupr */
#ifdef __CRT_HAVE_wcscasestr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t *__haystack, wchar_t *__needle),wcscasestr,(__haystack,__needle))
/* >> wcscasestr(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t const *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),wcscasestr,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcscasestr */
#include <libc/local/wchar/wcscasestr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); }
/* >> wcscasestr(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcscasestr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasestr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcscasestr */
#ifdef __CRT_HAVE_wcspcpy
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1),wchar_t *,__NOTHROW_NCX,wcspcpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* __CRT_HAVE_wcspcpy */
#include <libc/local/wchar/wcspcpy.h>
/* >> wcspcpy(3)
 * Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_IN(2) __ATTR_OUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspcpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))(__buf, __src); })
#endif /* !__CRT_HAVE_wcspcpy */
#ifdef __CRT_HAVE_wcspncpy
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* __CRT_HAVE_wcspncpy */
#include <libc/local/wchar/wcspncpy.h>
/* >> wcspncpy(3)
 * Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspncpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))(__buf, __src, __buflen); })
#endif /* !__CRT_HAVE_wcspncpy */
#ifdef __CRT_HAVE_wmempset
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw) && __SIZEOF_WCHAR_T__ == 2
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && __SIZEOF_WCHAR_T__ == 4
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/string/mempsetw.h>
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetw))((void *)__dst, (__UINT16_TYPE__)__filler, __num_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/string/mempsetl.h>
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__WCHAR_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempsetl))((void *)__dst, (__UINT32_TYPE__)__filler, __num_chars); }
#else /* ... */
#include <libc/local/wchar/wmempset.h>
/* >> wmempset(3)
 * Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))(__dst, __filler, __num_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsnchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchr,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnchr */
#include <libc/local/wchar/wcsnchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); }
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchr(3)
 * Same as `wcschr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnchr */
#ifdef __CRT_HAVE_wcsnrchr
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchr,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnrchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnrchr */
#include <libc/local/wchar/wcsnrchr.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); }
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchr(3)
 * Same as `wcsrchr', but don't exceed `max_chars' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrchr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnrchr */
#ifdef __CRT_HAVE_wcssep
/* >> wcssep(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcssep,(wchar_t **__restrict __stringp, wchar_t const *__restrict __delim),(__stringp,__delim))
#else /* __CRT_HAVE_wcssep */
#include <libc/local/wchar/wcssep.h>
/* >> wcssep(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcssep, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcssep)(wchar_t **__restrict __stringp, wchar_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))(__stringp, __delim); })
#endif /* !__CRT_HAVE_wcssep */
#ifdef __CRT_HAVE_wcsfry
/* >> wcsfry(3) */
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsfry,(wchar_t *__restrict __str),(__str))
#else /* __CRT_HAVE_wcsfry */
#include <libc/local/wchar/wcsfry.h>
/* >> wcsfry(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsfry, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsfry)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))(__str); })
#endif /* !__CRT_HAVE_wcsfry */
#ifdef __CRT_HAVE_wcsndup
/* >> wcsndup(3) */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2),wchar_t *,__NOTHROW_NCX,wcsndup,(wchar_t const *__restrict __str, __SIZE_TYPE__ __max_chars),(__str,__max_chars))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/wchar/wcsndup.h>
/* >> wcsndup(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsndup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_INS(1, 2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsndup)(wchar_t const *__restrict __str, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))(__str, __max_chars); })
#endif /* ... */
#ifdef __CRT_HAVE_wcsrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsrchrnul,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchrnul,(__haystack,__needle))
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t const *,__NOTHROW_NCX,wcsrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchrnul,(__haystack,__needle))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsrchrnul */
#include <libc/local/wchar/wcsrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); }
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsrchrnul(3)
 * Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsrchrnul */
#ifdef __CRT_HAVE_wcsnchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchrnul,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnchrnul */
#include <libc/local/wchar/wcsnchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); }
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnchrnul(3)
 * Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnchrnul */
#ifdef __CRT_HAVE_wcsnrchrnul
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#else /* __CRT_HAVE_wcsnrchrnul */
#include <libc/local/wchar/wcsnrchrnul.h>
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
extern "C++" {
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); }
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); }
} /* extern "C++" */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
/* >> wcsnrchrnul(3)
 * Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrchrnul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); })
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__CRT_HAVE_wcsnrchrnul */
#ifdef __CRT_HAVE_wcsoff
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,wcsoff,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* __CRT_HAVE_wcsoff */
#include <libc/local/wchar/wcsoff.h>
/* >> wcsoff(3)
 * Same as `wcschrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsoff)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_wcsoff */
#ifdef __CRT_HAVE_wcsroff
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,wcsroff,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* __CRT_HAVE_wcsroff */
#include <libc/local/wchar/wcsroff.h>
/* >> wcsroff(3)
 * Same as `wcsrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsroff)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))(__haystack, __needle); })
#endif /* !__CRT_HAVE_wcsroff */
#ifdef __CRT_HAVE_wcsnoff
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,wcsnoff,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_wcsnoff */
#include <libc/local/wchar/wcsnoff.h>
/* >> wcsnoff(3)
 * Same as `wcsnchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnoff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnoff)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_wcsnoff */
#ifdef __CRT_HAVE_wcsnroff
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,wcsnroff,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* __CRT_HAVE_wcsnroff */
#include <libc/local/wchar/wcsnroff.h>
/* >> wcsnroff(3)
 * Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnroff, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnroff)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))(__haystack, __needle, __maxlen); })
#endif /* !__CRT_HAVE_wcsnroff */
#ifdef __CRT_HAVE_fuzzy_wmemcmp
/* >> fuzzy_wmemcmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpw) && __SIZEOF_WCHAR_T__ == 2
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpw,(__s1,__s1_chars,__s2,__s2_chars))
#elif defined(__CRT_HAVE_fuzzy_memcmpl) && __SIZEOF_WCHAR_T__ == 4
/* >> fuzzy_wmemcmp(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),fuzzy_memcmpl,(__s1,__s1_chars,__s2,__s2_chars))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/string/fuzzy_memcmpw.h>
/* >> fuzzy_wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpw))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/string/fuzzy_memcmpl.h>
/* >> fuzzy_wmemcmp(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_memcmpl))((void const *)__s1, __s1_chars, (void const *)__s2, __s2_chars); }
#else /* ... */
#include <libc/local/wchar/fuzzy_wmemcmp.h>
/* >> fuzzy_wmemcmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* !... */
#ifdef __CRT_HAVE_fuzzy_wcscmp
/* >> fuzzy_wcscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_fuzzy_wcscmp */
#include <libc/local/wchar/fuzzy_wcscmp.h>
/* >> fuzzy_wcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))(__s1, __s2); })
#endif /* !__CRT_HAVE_fuzzy_wcscmp */
#ifdef __CRT_HAVE_fuzzy_wcsncmp
/* >> fuzzy_wcsncmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* __CRT_HAVE_fuzzy_wcsncmp */
#include <libc/local/wchar/fuzzy_wcsncmp.h>
/* >> fuzzy_wcsncmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* !__CRT_HAVE_fuzzy_wcsncmp */
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp
/* >> fuzzy_wmemcasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcasecmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#else /* __CRT_HAVE_fuzzy_wmemcasecmp */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/wchar/fuzzy_wmemcasecmp.h>
/* >> fuzzy_wmemcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcasecmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wmemcasecmp */
#ifdef __CRT_HAVE_fuzzy_wcscasecmp
/* >> fuzzy_wcscasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_fuzzy_wcscasecmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcscasecmp.h>
/* >> fuzzy_wcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscasecmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))(__s1, __s2); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcscasecmp */
#ifdef __CRT_HAVE_fuzzy_wcsncasecmp
/* >> fuzzy_wcsncasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncasecmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#else /* __CRT_HAVE_fuzzy_wcsncasecmp */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcsncasecmp.h>
/* >> fuzzy_wcsncasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncasecmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcsncasecmp */
#ifdef __CRT_HAVE_wildwcscmp
/* >> wildwcscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildwcscmp,(wchar_t const *__pattern, wchar_t const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildwcscmp */
#include <libc/local/wchar/wildwcscmp.h>
/* >> wildwcscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wildwcscmp)(wchar_t const *__pattern, wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildwcscmp */
#ifdef __CRT_HAVE_wildwcscasecmp
/* >> wildwcscasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildwcscasecmp,(wchar_t const *__pattern, wchar_t const *__string),(__pattern,__string))
#else /* __CRT_HAVE_wildwcscasecmp */
#include <libc/local/wchar/wildwcscasecmp.h>
/* >> wildwcscasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wildwcscasecmp)(wchar_t const *__pattern, wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))(__pattern, __string); })
#endif /* !__CRT_HAVE_wildwcscasecmp */
#ifdef __CRT_HAVE_wcsverscmp
/* >> wcsverscmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcsverscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* __CRT_HAVE_wcsverscmp */
#include <libc/local/wchar/wcsverscmp.h>
/* >> wcsverscmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsverscmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcsverscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))(__s1, __s2); })
#endif /* !__CRT_HAVE_wcsverscmp */
#ifdef __CRT_HAVE_wcslstrip
/* >> wcslstrip(3) */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcslstrip,(wchar_t const *__str),(__str))
#else /* __CRT_HAVE_wcslstrip */
#include <libc/local/wchar/wcslstrip.h>
/* >> wcslstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslstrip)(wchar_t const *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslstrip))(__str); })
#endif /* !__CRT_HAVE_wcslstrip */
#ifdef __CRT_HAVE_wcsrstrip
/* >> wcsrstrip(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsrstrip,(wchar_t *__str),(__str))
#else /* __CRT_HAVE_wcsrstrip */
#include <libc/local/wchar/wcsrstrip.h>
/* >> wcsrstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrstrip)(wchar_t *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrstrip))(__str); })
#endif /* !__CRT_HAVE_wcsrstrip */
#ifdef __CRT_HAVE_wcsstrip
/* >> wcsstrip(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,wcsstrip,(wchar_t *__str),(__str))
#else /* __CRT_HAVE_wcsstrip */
#include <libc/local/wchar/wcsstrip.h>
/* >> wcsstrip(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstrip, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstrip)(wchar_t *__str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstrip))(__str); })
#endif /* !__CRT_HAVE_wcsstrip */
#ifdef __CRT_HAVE_wmemcasecmp
/* >> wmemcasecmp(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),(__s1,__s2,__num_chars))
#else /* __CRT_HAVE_wmemcasecmp */
#include <libc/local/wchar/wmemcasecmp.h>
/* >> wmemcasecmp(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcasecmp, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcasecmp)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcasecmp))(__s1, __s2, __num_chars); })
#endif /* !__CRT_HAVE_wmemcasecmp */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wmemcasecmp_l
/* >> wmemcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcasecmp_l,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale),(__s1,__s2,__num_chars,__locale))
#else /* __CRT_HAVE_wmemcasecmp_l */
#include <libc/local/wchar/wmemcasecmp_l.h>
/* >> wmemcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcasecmp_l)(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcasecmp_l))(__s1, __s2, __num_chars, __locale); })
#endif /* !__CRT_HAVE_wmemcasecmp_l */
#ifdef __CRT_HAVE_wcsncoll_l
/* >> wcsncoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
/* >> wcsncoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncoll_l.h>
/* >> wcsncoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcscasecoll_l
/* >> wcscasecoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
/* >> wcscasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* ... */
#include <libc/local/wchar/wcscasecoll_l.h>
/* >> wcscasecoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wcscasecoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsncasecoll_l
/* >> wcsncasecoll_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
/* >> wcsncasecoll_l(3) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* ... */
#include <libc/local/wchar/wcsncasecoll_l.h>
/* >> wcsncasecoll_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcslwr_l
/* >> wcslwr_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
/* >> wcslwr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcslwr_l.h>
/* >> wcslwr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsupr_l
/* >> wcsupr_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
/* >> wcsupr_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#else /* ... */
#include <libc/local/wchar/wcsupr_l.h>
/* >> wcsupr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE_wcsnlwr_l
/* >> wcsnlwr_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnlwr_l,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_wcsnlwr_l */
#include <libc/local/wchar/wcsnlwr_l.h>
/* >> wcsnlwr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlwr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnlwr_l)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlwr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_wcsnlwr_l */
#ifdef __CRT_HAVE_wcsnupr_l
/* >> wcsnupr_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnupr_l,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* __CRT_HAVE_wcsnupr_l */
#include <libc/local/wchar/wcsnupr_l.h>
/* >> wcsnupr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnupr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 2) __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnupr_l)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnupr_l))(__str, __maxlen, __locale); })
#endif /* !__CRT_HAVE_wcsnupr_l */
#ifdef __CRT_HAVE_wcscasestr_l
/* >> wcscasestr_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),wchar_t *,__NOTHROW_NCX,wcscasestr_l,(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale),(__haystack,__needle,__locale))
#else /* __CRT_HAVE_wcscasestr_l */
#include <libc/local/wchar/wcscasestr_l.h>
/* >> wcscasestr_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasestr_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr_l)(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))(__haystack, __needle, __locale); })
#endif /* !__CRT_HAVE_wcscasestr_l */
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp_l
/* >> fuzzy_wmemcasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcasecmp_l,(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#else /* __CRT_HAVE_fuzzy_wmemcasecmp_l */
#include <parts/malloca.h>
#ifndef __NO_MALLOCA
#include <libc/local/wchar/fuzzy_wmemcasecmp_l.h>
/* >> fuzzy_wmemcasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcasecmp_l)(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wmemcasecmp_l */
#ifdef __CRT_HAVE_fuzzy_wcscasecmp_l
/* >> fuzzy_wcscasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#else /* __CRT_HAVE_fuzzy_wcscasecmp_l */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcscasecmp_l.h>
/* >> fuzzy_wcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))(__s1, __s2, __locale); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp_l || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcscasecmp_l */
#ifdef __CRT_HAVE_fuzzy_wcsncasecmp_l
/* >> fuzzy_wcsncasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncasecmp_l,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#else /* __CRT_HAVE_fuzzy_wcsncasecmp_l */
#include <parts/malloca.h>
#if defined(__CRT_HAVE_fuzzy_wmemcasecmp_l) || !defined(__NO_MALLOCA)
#include <libc/local/wchar/fuzzy_wcsncasecmp_l.h>
/* >> fuzzy_wcsncasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncasecmp_l)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* __CRT_HAVE_fuzzy_wmemcasecmp_l || !__NO_MALLOCA */
#endif /* !__CRT_HAVE_fuzzy_wcsncasecmp_l */
#ifdef __CRT_HAVE_wildwcscasecmp_l
/* >> wildwcscasecmp_l(3) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,wildwcscasecmp_l,(wchar_t const *__pattern, wchar_t const *__string, __locale_t __locale),(__pattern,__string,__locale))
#else /* __CRT_HAVE_wildwcscasecmp_l */
#include <libc/local/wchar/wildwcscasecmp_l.h>
/* >> wildwcscasecmp_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscasecmp_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL wildwcscasecmp_l)(wchar_t const *__pattern, wchar_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))(__pattern, __string, __locale); })
#endif /* !__CRT_HAVE_wildwcscasecmp_l */
#endif /* __USE_XOPEN2K8 */
#endif /* __USE_KOS */

#ifdef __USE_BSD
#if !defined(__fgetwln_defined) && defined(__CRT_HAVE_fgetwln)
#define __fgetwln_defined
/* >> fgetwln(3) */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT_OPT(2),wchar_t *,__NOTHROW_NCX,fgetwln,(FILE *__restrict __fp, __SIZE_TYPE__ *__restrict __lenp),(__fp,__lenp))
#endif /* !__fgetwln_defined && __CRT_HAVE_fgetwln */
#ifndef __wcslcat_defined
#define __wcslcat_defined
#ifdef __CRT_HAVE_wcslcat
/* >> wcslcat(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcslcat,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_wcslcat */
#include <libc/local/wchar/wcslcat.h>
/* >> wcslcat(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslcat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslcat)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcat))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_wcslcat */
#endif /* !__wcslcat_defined */
#ifndef __wcslcpy_defined
#define __wcslcpy_defined
#ifdef __CRT_HAVE_wcslcpy
/* >> wcslcpy(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcslcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize),(__dst,__src,__bufsize))
#else /* __CRT_HAVE_wcslcpy */
#include <libc/local/wchar/wcslcpy.h>
/* >> wcslcpy(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslcpy, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(2) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __bufsize) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslcpy))(__dst, __src, __bufsize); })
#endif /* !__CRT_HAVE_wcslcpy */
#endif /* !__wcslcpy_defined */
#endif /* __USE_BSD */




#if defined(__USE_DOS) || defined(__USE_KOS)
#ifndef __wcsnset_defined
#define __wcsnset_defined
#ifdef __CRT_HAVE_wcsnset
/* >> wcsnset(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
/* >> wcsnset(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUTS(1, 3),wchar_t *,__NOTHROW_NCX,wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),_wcsnset,(__str,__ch,__maxlen))
#else /* ... */
#include <libc/local/wchar/wcsnset.h>
/* >> wcsnset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); })
#endif /* !... */
#endif /* !__wcsnset_defined */
#ifndef __wcsrev_defined
#define __wcsrev_defined
#ifdef __CRT_HAVE_wcsrev
/* >> wcsrev(3) */
__CDECLARE(__ATTR_RETNONNULL __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsrev)
/* >> wcsrev(3) */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),_wcsrev,(__str))
#else /* ... */
#include <libc/local/wchar/wcsrev.h>
/* >> wcsrev(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); })
#endif /* !... */
#endif /* !__wcsrev_defined */
#ifndef __wcsset_defined
#define __wcsset_defined
#ifdef __CRT_HAVE_wcsset
/* >> wcsset(3) */
__CDECLARE(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
/* >> wcsset(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, int __ch),_wcsset,(__str,__ch))
#else /* ... */
#include <libc/local/wchar/wcsset.h>
/* >> wcsset(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsset, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsset)(wchar_t *__restrict __str, int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); })
#endif /* !... */
#endif /* !__wcsset_defined */
#ifndef __wcslwr_defined
#define __wcslwr_defined
#ifdef __CRT_HAVE_wcslwr
/* >> wcslwr(3) */
__CDECLARE(__ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcslwr)
/* >> wcslwr(3) */
__CREDIRECT(__ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),_wcslwr,(__str))
#else /* ... */
#include <libc/local/wchar/wcslwr.h>
/* >> wcslwr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); })
#endif /* !... */
#endif /* !__wcslwr_defined */
#ifndef __wcsupr_defined
#define __wcsupr_defined
#ifdef __CRT_HAVE_wcsupr
/* >> wcsupr(3) */
__CDECLARE(__ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsupr)
/* >> wcsupr(3) */
__CREDIRECT(__ATTR_INOUT(1),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),_wcsupr,(__str))
#else /* ... */
#include <libc/local/wchar/wcsupr.h>
/* >> wcsupr(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT(1) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); })
#endif /* !... */
#endif /* !__wcsupr_defined */
#endif /* __USE_DOS || __USE_KOS */

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

#ifdef __USE_DOS
#include <corecrt_wconio.h>
#include <corecrt_wdirect.h>
#include <corecrt_wio.h>
#include <corecrt_wprocess.h>
#include <corecrt_wstdio.h>
#include <corecrt_wstdlib.h>
#include <corecrt_wstring.h>
#include <corecrt_wtime.h>
#ifndef __USE_DOS_CLEAN
#include <corecrt_memcpy_s.h> /* Include <string.h> instead */
#include <corecrt_wctype.h>   /* Include <wctype.h> instead */
#endif /* !__USE_DOS_CLEAN */
#endif /* __USE_DOS */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CWCHAR
#undef _WCHAR_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CWCHAR */
#endif /* !_WCHAR_H */
