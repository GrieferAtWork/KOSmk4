/* HASH CRC-32:0xf9acb297 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
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
#undef __STRUCT_TM
#define __STRUCT_TM struct tm
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
#ifndef __NO_FPU
__NAMESPACE_STD_USING(wcstod)
#endif /* !__NO_FPU */
__NAMESPACE_STD_USING(wcstol)
__NAMESPACE_STD_USING(wcstoul)
__NAMESPACE_STD_USING(mbsinit)
__NAMESPACE_STD_USING(wmemcmp)
__NAMESPACE_STD_USING(wmemcpy)
__NAMESPACE_STD_USING(wmemmove)
__NAMESPACE_STD_USING(wmemset)
#if !defined(__wcscpy_defined) && defined(__std_wcscpy_defined)
#define __wcscpy_defined 1
__NAMESPACE_STD_USING(wcscpy)
#endif /* !__wcscpy_defined && !__std_wcscpy_defined */
#if !defined(__wcscat_defined) && defined(__std_wcscat_defined)
#define __wcscat_defined 1
__NAMESPACE_STD_USING(wcscat)
#endif /* !__wcscat_defined && !__std_wcscat_defined */
#if !defined(__wcsncat_defined) && defined(__std_wcsncat_defined)
#define __wcsncat_defined 1
__NAMESPACE_STD_USING(wcsncat)
#endif /* !__wcsncat_defined && !__std_wcsncat_defined */
#if !defined(__wcsncpy_defined) && defined(__std_wcsncpy_defined)
#define __wcsncpy_defined 1
__NAMESPACE_STD_USING(wcsncpy)
#endif /* !__wcsncpy_defined && !__std_wcsncpy_defined */
#if !defined(__wcscmp_defined) && defined(__std_wcscmp_defined)
#define __wcscmp_defined 1
__NAMESPACE_STD_USING(wcscmp)
#endif /* !__wcscmp_defined && !__std_wcscmp_defined */
#if !defined(__wcsncmp_defined) && defined(__std_wcsncmp_defined)
#define __wcsncmp_defined 1
__NAMESPACE_STD_USING(wcsncmp)
#endif /* !__wcsncmp_defined && !__std_wcsncmp_defined */
#if !defined(__wcscoll_defined) && defined(__std_wcscoll_defined)
#define __wcscoll_defined 1
__NAMESPACE_STD_USING(wcscoll)
#endif /* !__wcscoll_defined && !__std_wcscoll_defined */
#if !defined(__wcsxfrm_defined) && defined(__std_wcsxfrm_defined)
#define __wcsxfrm_defined 1
__NAMESPACE_STD_USING(wcsxfrm)
#endif /* !__wcsxfrm_defined && !__std_wcsxfrm_defined */
#if !defined(__getwchar_defined) && defined(__std_getwchar_defined)
#define __getwchar_defined 1
__NAMESPACE_STD_USING(getwchar)
#endif /* !__getwchar_defined && !__std_getwchar_defined */
#if !defined(__fgetwc_defined) && defined(__std_fgetwc_defined)
#define __fgetwc_defined 1
__NAMESPACE_STD_USING(fgetwc)
#endif /* !__fgetwc_defined && !__std_fgetwc_defined */
#if !defined(__getwc_defined) && defined(__std_getwc_defined)
#define __getwc_defined 1
__NAMESPACE_STD_USING(getwc)
#endif /* !__getwc_defined && !__std_getwc_defined */
#if !defined(__putwchar_defined) && defined(__std_putwchar_defined)
#define __putwchar_defined 1
__NAMESPACE_STD_USING(putwchar)
#endif /* !__putwchar_defined && !__std_putwchar_defined */
#if !defined(__fputwc_defined) && defined(__std_fputwc_defined)
#define __fputwc_defined 1
__NAMESPACE_STD_USING(fputwc)
#endif /* !__fputwc_defined && !__std_fputwc_defined */
#if !defined(__putwc_defined) && defined(__std_putwc_defined)
#define __putwc_defined 1
__NAMESPACE_STD_USING(putwc)
#endif /* !__putwc_defined && !__std_putwc_defined */
#if !defined(__fgetws_defined) && defined(__std_fgetws_defined)
#define __fgetws_defined 1
__NAMESPACE_STD_USING(fgetws)
#endif /* !__fgetws_defined && !__std_fgetws_defined */
#if !defined(__fputws_defined) && defined(__std_fputws_defined)
#define __fputws_defined 1
__NAMESPACE_STD_USING(fputws)
#endif /* !__fputws_defined && !__std_fputws_defined */
#if !defined(__ungetwc_defined) && defined(__std_ungetwc_defined)
#define __ungetwc_defined 1
__NAMESPACE_STD_USING(ungetwc)
#endif /* !__ungetwc_defined && !__std_ungetwc_defined */
#if !defined(__wcsftime_defined) && defined(__std_wcsftime_defined)
#define __wcsftime_defined 1
__NAMESPACE_STD_USING(wcsftime)
#endif /* !__wcsftime_defined && !__std_wcsftime_defined */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && !__std_wcstok_defined */
#if !defined(__wcslen_defined) && defined(__std_wcslen_defined)
#define __wcslen_defined 1
__NAMESPACE_STD_USING(wcslen)
#endif /* !__wcslen_defined && !__std_wcslen_defined */
#if !defined(__wcsspn_defined) && defined(__std_wcsspn_defined)
#define __wcsspn_defined 1
__NAMESPACE_STD_USING(wcsspn)
#endif /* !__wcsspn_defined && !__std_wcsspn_defined */
#if !defined(__wcscspn_defined) && defined(__std_wcscspn_defined)
#define __wcscspn_defined 1
__NAMESPACE_STD_USING(wcscspn)
#endif /* !__wcscspn_defined && !__std_wcscspn_defined */
#if !defined(__wcschr_defined) && defined(__std_wcschr_defined)
#define __wcschr_defined 1
__NAMESPACE_STD_USING(wcschr)
#endif /* !__wcschr_defined && !__std_wcschr_defined */
#if !defined(__wcsrchr_defined) && defined(__std_wcsrchr_defined)
#define __wcsrchr_defined 1
__NAMESPACE_STD_USING(wcsrchr)
#endif /* !__wcsrchr_defined && !__std_wcsrchr_defined */
#if !defined(__wcspbrk_defined) && defined(__std_wcspbrk_defined)
#define __wcspbrk_defined 1
__NAMESPACE_STD_USING(wcspbrk)
#endif /* !__wcspbrk_defined && !__std_wcspbrk_defined */
#if !defined(__wcsstr_defined) && defined(__std_wcsstr_defined)
#define __wcsstr_defined 1
__NAMESPACE_STD_USING(wcsstr)
#endif /* !__wcsstr_defined && !__std_wcsstr_defined */
__NAMESPACE_STD_USING(wmemchr)
#if !defined(__fwide_defined) && defined(__std_fwide_defined)
#define __fwide_defined 1
__NAMESPACE_STD_USING(fwide)
#endif /* !__fwide_defined && !__std_fwide_defined */
#if !defined(__fwprintf_defined) && defined(__std_fwprintf_defined)
#define __fwprintf_defined 1
__NAMESPACE_STD_USING(fwprintf)
#endif /* !__fwprintf_defined && !__std_fwprintf_defined */
#if !defined(__vfwprintf_defined) && defined(__std_vfwprintf_defined)
#define __vfwprintf_defined 1
__NAMESPACE_STD_USING(vfwprintf)
#endif /* !__vfwprintf_defined && !__std_vfwprintf_defined */
#if !defined(__wprintf_defined) && defined(__std_wprintf_defined)
#define __wprintf_defined 1
__NAMESPACE_STD_USING(wprintf)
#endif /* !__wprintf_defined && !__std_wprintf_defined */
#if !defined(__vwprintf_defined) && defined(__std_vwprintf_defined)
#define __vwprintf_defined 1
__NAMESPACE_STD_USING(vwprintf)
#endif /* !__vwprintf_defined && !__std_vwprintf_defined */
#if !defined(__fwscanf_defined) && defined(__std_fwscanf_defined)
#define __fwscanf_defined 1
__NAMESPACE_STD_USING(fwscanf)
#endif /* !__fwscanf_defined && !__std_fwscanf_defined */
#if !defined(__wscanf_defined) && defined(__std_wscanf_defined)
#define __wscanf_defined 1
__NAMESPACE_STD_USING(wscanf)
#endif /* !__wscanf_defined && !__std_wscanf_defined */
#if !defined(__swscanf_defined) && defined(__std_swscanf_defined)
#define __swscanf_defined 1
__NAMESPACE_STD_USING(swscanf)
#endif /* !__swscanf_defined && !__std_swscanf_defined */
#if !defined(__vswprintf_defined) && defined(__std_vswprintf_defined)
#define __vswprintf_defined 1
__NAMESPACE_STD_USING(vswprintf)
#endif /* !__vswprintf_defined && !__std_vswprintf_defined */
#if !defined(__swprintf_defined) && defined(__std_swprintf_defined)
#define __swprintf_defined 1
__NAMESPACE_STD_USING(swprintf)
#endif /* !__swprintf_defined && !__std_swprintf_defined */
#if !defined(__wcstof_defined) && defined(__std_wcstof_defined)
#define __wcstof_defined 1
__NAMESPACE_STD_USING(wcstof)
#endif /* !__wcstof_defined && !__std_wcstof_defined */
#if !defined(__wcstold_defined) && defined(__std_wcstold_defined)
#define __wcstold_defined 1
__NAMESPACE_STD_USING(wcstold)
#endif /* !__wcstold_defined && !__std_wcstold_defined */
#if !defined(__wcstoll_defined) && defined(__std_wcstoll_defined)
#define __wcstoll_defined 1
__NAMESPACE_STD_USING(wcstoll)
#endif /* !__wcstoll_defined && !__std_wcstoll_defined */
#if !defined(__wcstoull_defined) && defined(__std_wcstoull_defined)
#define __wcstoull_defined 1
__NAMESPACE_STD_USING(wcstoull)
#endif /* !__wcstoull_defined && !__std_wcstoull_defined */
#if !defined(__vfwscanf_defined) && defined(__std_vfwscanf_defined)
#define __vfwscanf_defined 1
__NAMESPACE_STD_USING(vfwscanf)
#endif /* !__vfwscanf_defined && !__std_vfwscanf_defined */
#if !defined(__vwscanf_defined) && defined(__std_vwscanf_defined)
#define __vwscanf_defined 1
__NAMESPACE_STD_USING(vwscanf)
#endif /* !__vwscanf_defined && !__std_vwscanf_defined */
#if !defined(__vswscanf_defined) && defined(__std_vswscanf_defined)
#define __vswscanf_defined 1
__NAMESPACE_STD_USING(vswscanf)
#endif /* !__vswscanf_defined && !__std_vswscanf_defined */
#ifndef __wcstok_defined
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined */
__NAMESPACE_STD_USING(wmempmove)
#undef _CXX_STDONLY_CWCHAR
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CWCHAR */
#include "__stdinc.h"
#include "__crt.h"
#include <kos/anno.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/mbstate.h>
#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */
#ifdef __USE_DOS
#include <crtdefs.h>
#include <parts/errno.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

/* Define `NULL' */
#ifndef NULL
#define NULL __NULLPTR
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN__
#define WCHAR_MAX __WCHAR_MAX__
#endif

#ifndef WEOF
#if __SIZEOF_WCHAR_T__ == 4
#define WEOF 0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define WEOF (__CCAST(__WINT_TYPE__)0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !WEOF */

#ifdef __CC__

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __mbstate_t mbstate_t;
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

/* Define `size_t' */
__NAMESPACE_STD_BEGIN
#ifndef __std_tm_defined
#define __std_tm_defined 1
#ifdef __tm_defined
__NAMESPACE_GLB_USING(tm)
#else /* __tm_defined */
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#ifdef __CRT_GLC
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* __CRT_GLC */
};
#endif /* !__tm_defined */
#endif /* !__std_tm_defined */
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __STRUCT_TM
#define __STRUCT_TM struct __NAMESPACE_STD_SYM tm
#endif /* !__STRUCT_TM */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __tm_defined
#define __tm_defined 1
#undef __STRUCT_TM
#define __STRUCT_TM struct tm
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
__CDECLARE(__ATTR_WUNUSED,wint_t,__NOTHROW_NCX,btowc,(int __ch),(__ch))
#else /* LIBC: btowc */
__NAMESPACE_STD_END
#include <local/wchar/btowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(btowc, __FORCELOCAL __ATTR_WUNUSED wint_t __NOTHROW_NCX(__LIBCCALL btowc)(int __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(btowc))(__ch); })
#endif /* btowc... */
#ifdef __CRT_HAVE_wctob
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,wctob,(wint_t __ch),(__ch))
#else /* LIBC: wctob */
__NAMESPACE_STD_END
#include <local/wchar/wctob.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wctob, __FORCELOCAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL wctob)(wint_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wctob))(__ch); })
#endif /* wctob... */
#ifdef __CRT_HAVE_mbrtowc
__CDECLARE(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__ps),(__pwc,__str,__maxlen,__ps))
#elif defined(__CRT_HAVE___mbrtowc)
__CREDIRECT(__ATTR_NONNULL((2)),size_t,__NOTHROW_NCX,mbrtowc,(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__ps),__mbrtowc,(__pwc,__str,__maxlen,__ps))
#else /* LIBC: mbrtowc */
__NAMESPACE_STD_END
#include <local/wchar/mbrtowc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrtowc, __FORCELOCAL __ATTR_NONNULL((2)) size_t __NOTHROW_NCX(__LIBCCALL mbrtowc)(wchar_t *__pwc, char const *__restrict __str, size_t __maxlen, mbstate_t *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrtowc))(__pwc, __str, __maxlen, __ps); })
#endif /* mbrtowc... */
#ifdef __CRT_HAVE_wcrtomb
__CDECLARE(__ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,wcrtomb,(char *__restrict __str, wchar_t __wc, mbstate_t *__ps),(__str,__wc,__ps))
#else /* LIBC: wcrtomb */
__NAMESPACE_STD_END
#include <local/wchar/wcrtomb.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcrtomb, __FORCELOCAL __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL wcrtomb)(char *__restrict __str, wchar_t __wc, mbstate_t *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcrtomb))(__str, __wc, __ps); })
#endif /* wcrtomb... */
#ifdef __CRT_HAVE_mbrlen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,mbrlen,(char const *__restrict __str, size_t __maxlen, mbstate_t *__ps),(__str,__maxlen,__ps))
#elif defined(__CRT_HAVE___mbrlen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),size_t,__NOTHROW_NCX,mbrlen,(char const *__restrict __str, size_t __maxlen, mbstate_t *__ps),__mbrlen,(__str,__maxlen,__ps))
#else /* LIBC: mbrlen */
__NAMESPACE_STD_END
#include <local/wchar/mbrlen.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbrlen, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) size_t __NOTHROW_NCX(__LIBCCALL mbrlen)(char const *__restrict __str, size_t __maxlen, mbstate_t *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __ps); })
#endif /* mbrlen... */
#ifdef __CRT_HAVE_mbsrtowcs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,mbsrtowcs,(wchar_t *__dst, char const **__restrict __psrc, size_t __len, mbstate_t *__ps),(__dst,__psrc,__len,__ps))
#else /* LIBC: mbsrtowcs */
__NAMESPACE_STD_END
#include <local/wchar/mbsrtowcs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsrtowcs, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL mbsrtowcs)(wchar_t *__dst, char const **__restrict __psrc, size_t __len, mbstate_t *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsrtowcs))(__dst, __psrc, __len, __ps); })
#endif /* mbsrtowcs... */
#ifdef __CRT_HAVE_wcsrtombs
__CDECLARE(__ATTR_NONNULL((1, 2)),size_t,__NOTHROW_NCX,wcsrtombs,(char *__dst, wchar_t const **__restrict __psrc, size_t __len, mbstate_t *__ps),(__dst,__psrc,__len,__ps))
#else /* LIBC: wcsrtombs */
__NAMESPACE_STD_END
#include <local/wchar/wcsrtombs.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrtombs, __FORCELOCAL __ATTR_NONNULL((1, 2)) size_t __NOTHROW_NCX(__LIBCCALL wcsrtombs)(char *__dst, wchar_t const **__restrict __psrc, size_t __len, mbstate_t *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrtombs))(__dst, __psrc, __len, __ps); })
#endif /* wcsrtombs... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_wcstod
__CDECLARE(__ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* LIBC: wcstod */
__NAMESPACE_STD_END
#include <local/wchar/wcstod.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))(__nptr, __endptr); })
#endif /* wcstod... */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_wcstol
__CDECLARE(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#else /* LIBC: wcstol */
__NAMESPACE_STD_END
#include <local/wchar/wcstol.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))(__nptr, __endptr, __base); })
#endif /* wcstol... */
#ifdef __CRT_HAVE_wcstoul
__CDECLARE(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && (__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstoul */
__NAMESPACE_STD_END
#include <local/wchar/wcstoul.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))(__nptr, __endptr, __base); })
#endif /* wcstoul... */
#ifdef __CRT_HAVE_mbsinit
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,mbsinit,(mbstate_t const *__ps),(__ps))
#else /* LIBC: mbsinit */
__NAMESPACE_STD_END
#include <local/wchar/mbsinit.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(mbsinit, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL mbsinit)(mbstate_t const *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbsinit))(__ps); })
#endif /* mbsinit... */
#ifdef __CRT_HAVE_wmemcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wmemcmp,(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars),(__s1,__s2,__num_chars))
#else /* LIBC: wmemcmp */
__NAMESPACE_STD_END
#include <local/wchar/wmemcmp.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wmemcmp)(wchar_t const *__s1, wchar_t const *__s2, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcmp))(__s1, __s2, __num_chars); })
#endif /* wmemcmp... */
#ifdef __CRT_HAVE_wmemcpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars),memcpyl,(__dst,__src,__num_chars))
#else /* LIBC: wmemcpy */
__NAMESPACE_STD_END
#include <local/wchar/wmemcpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))(__dst, __src, __num_chars); })
#endif /* wmemcpy... */
#ifdef __CRT_HAVE_wmemmove
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovew) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),memmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memmovel) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmemmove,(wchar_t *__dst, wchar_t const *__src, size_t __num_chars),memmovel,(__dst,__src,__num_chars))
#else /* LIBC: wmemmove */
__NAMESPACE_STD_END
#include <local/wchar/wmemmove.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemmove)(wchar_t *__dst, wchar_t const *__src, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove))(__dst, __src, __num_chars); })
#endif /* wmemmove... */
#ifdef __CRT_HAVE_wmemset
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),memsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_memsetl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemset,(wchar_t *__dst, wchar_t __filler, size_t __num_chars),memsetl,(__dst,__filler,__num_chars))
#else /* LIBC: wmemset */
__NAMESPACE_STD_END
#include <local/wchar/wmemset.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemset)(wchar_t *__dst, wchar_t __filler, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemset))(__dst, __filler, __num_chars); })
#endif /* wmemset... */
#ifndef __std_wcscpy_defined
#define __std_wcscpy_defined 1
#ifdef __wcscpy_defined
__NAMESPACE_GLB_USING(wcscpy)
#elif defined(__CRT_HAVE_wcscpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* LIBC: wcscpy */
__NAMESPACE_STD_END
#include <local/wchar/wcscpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy))(__buf, __src); })
#endif /* wcscpy... */
#endif /* !__std_wcscpy_defined */
#ifndef __std_wcscat_defined
#define __std_wcscat_defined 1
#ifdef __wcscat_defined
__NAMESPACE_GLB_USING(wcscat)
#elif defined(__CRT_HAVE_wcscat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* LIBC: wcscat */
__NAMESPACE_STD_END
#include <local/wchar/wcscat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat))(__buf, __src); })
#endif /* wcscat... */
#endif /* !__std_wcscat_defined */
#ifndef __std_wcsncat_defined
#define __std_wcsncat_defined 1
#ifdef __wcsncat_defined
__NAMESPACE_GLB_USING(wcsncat)
#elif defined(__CRT_HAVE_wcsncat)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncat,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* LIBC: wcsncat */
__NAMESPACE_STD_END
#include <local/wchar/wcsncat.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncat)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat))(__buf, __src, __buflen); })
#endif /* wcsncat... */
#endif /* !__std_wcsncat_defined */
#ifndef __std_wcsncpy_defined
#define __std_wcsncpy_defined 1
#ifdef __wcsncpy_defined
__NAMESPACE_GLB_USING(wcsncpy)
#elif defined(__CRT_HAVE_wcsncpy)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* LIBC: wcsncpy */
__NAMESPACE_STD_END
#include <local/wchar/wcsncpy.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy))(__buf, __src, __buflen); })
#endif /* wcsncpy... */
#endif /* !__std_wcsncpy_defined */
#ifndef __std_wcscmp_defined
#define __std_wcscmp_defined 1
#ifdef __wcscmp_defined
__NAMESPACE_GLB_USING(wcscmp)
#elif defined(__CRT_HAVE_wcscmp)
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcscmp */
__NAMESPACE_STD_END
#include <local/wchar/wcscmp.h>
__NAMESPACE_STD_BEGIN
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscmp))(__s1, __s2); })
#endif /* wcscmp... */
#endif /* !__std_wcscmp_defined */
#ifndef __std_wcsncmp_defined
#define __std_wcsncmp_defined 1
#ifdef __wcsncmp_defined
__NAMESPACE_GLB_USING(wcsncmp)
#elif defined(__CRT_HAVE_wcsncmp)
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: wcsncmp */
__NAMESPACE_STD_END
#include <local/wchar/wcsncmp.h>
__NAMESPACE_STD_BEGIN
/* Same as `wcscmp', but compare at most `MAXLEN' characters from either string */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncmp))(__s1, __s2, __maxlen); })
#endif /* wcsncmp... */
#endif /* !__std_wcsncmp_defined */
#ifndef __std_wcscoll_defined
#define __std_wcscoll_defined 1
#ifdef __wcscoll_defined
__NAMESPACE_GLB_USING(wcscoll)
#elif defined(__CRT_HAVE_wcscoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcscoll */
__NAMESPACE_STD_END
#include <local/wchar/wcscoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll))(__s1, __s2); })
#endif /* wcscoll... */
#endif /* !__std_wcscoll_defined */
#ifndef __std_wcsxfrm_defined
#define __std_wcsxfrm_defined 1
#ifdef __wcsxfrm_defined
__NAMESPACE_GLB_USING(wcsxfrm)
#elif defined(__CRT_HAVE_wcsxfrm)
__CDECLARE(__ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen),(__dst,__src,__maxlen))
#else /* LIBC: wcsxfrm */
__NAMESPACE_STD_END
#include <local/wchar/wcsxfrm.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsxfrm)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm))(__dst, __src, __maxlen); })
#endif /* wcsxfrm... */
#endif /* !__std_wcsxfrm_defined */
#ifndef __std_getwchar_defined
#define __std_getwchar_defined 1
#ifdef __getwchar_defined
__NAMESPACE_GLB_USING(getwchar)
#elif defined(__CRT_HAVE_getwchar)
__CDECLARE(,wint_t,,getwchar,(void),()) __THROWS(...)
#elif defined(__CRT_HAVE__fgetwchar)
__CREDIRECT(,wint_t,,getwchar,(void),_fgetwchar,()) __THROWS(...)
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
__NAMESPACE_STD_END
#include <local/wchar/getwchar.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar, __FORCELOCAL wint_t (__LIBCCALL getwchar)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); })
#else /* CUSTOM: getwchar */
#undef __std_getwchar_defined
#endif /* getwchar... */
#endif /* !__std_getwchar_defined */
#ifndef __std_fgetwc_defined
#define __std_fgetwc_defined 1
#ifdef __fgetwc_defined
__NAMESPACE_GLB_USING(fgetwc)
#elif defined(__CRT_HAVE_fgetwc)
__CDECLARE(__ATTR_NONNULL((1)),wint_t,,fgetwc,(FILE *__restrict __stream),(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getwc)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,,fgetwc,(FILE *__restrict __stream),getwc,(__stream)) __THROWS(...)
#else /* LIBC: fgetwc */
#undef __std_fgetwc_defined
#endif /* fgetwc... */
#endif /* !__std_fgetwc_defined */
#ifndef __std_getwc_defined
#define __std_getwc_defined 1
#ifdef __getwc_defined
__NAMESPACE_GLB_USING(getwc)
#elif defined(__CRT_HAVE_getwc)
__CDECLARE(__ATTR_NONNULL((1)),wint_t,,getwc,(FILE *__restrict __stream),(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetwc)
__CREDIRECT(__ATTR_NONNULL((1)),wint_t,,getwc,(FILE *__restrict __stream),fgetwc,(__stream)) __THROWS(...)
#else /* LIBC: getwc */
#undef __std_getwc_defined
#endif /* getwc... */
#endif /* !__std_getwc_defined */
#ifndef __std_putwchar_defined
#define __std_putwchar_defined 1
#ifdef __putwchar_defined
__NAMESPACE_GLB_USING(putwchar)
#elif defined(__CRT_HAVE_putwchar)
__CDECLARE(,wint_t,,putwchar,(wchar_t __wc),(__wc)) __THROWS(...)
#elif defined(__CRT_HAVE__fputwchar)
__CREDIRECT(,wint_t,,putwchar,(wchar_t __wc),_fputwchar,(__wc)) __THROWS(...)
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
__NAMESPACE_STD_END
#include <local/wchar/putwchar.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar, __FORCELOCAL wint_t (__LIBCCALL putwchar)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); })
#else /* CUSTOM: putwchar */
#undef __std_putwchar_defined
#endif /* putwchar... */
#endif /* !__std_putwchar_defined */
#ifndef __std_fputwc_defined
#define __std_fputwc_defined 1
#ifdef __fputwc_defined
__NAMESPACE_GLB_USING(fputwc)
#elif defined(__CRT_HAVE_fputwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,,fputwc,(wchar_t __wc, FILE *__stream),(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putwc)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,,fputwc,(wchar_t __wc, FILE *__stream),putwc,(__wc,__stream)) __THROWS(...)
#else /* LIBC: fputwc */
#undef __std_fputwc_defined
#endif /* fputwc... */
#endif /* !__std_fputwc_defined */
#ifndef __std_putwc_defined
#define __std_putwc_defined 1
#ifdef __putwc_defined
__NAMESPACE_GLB_USING(putwc)
#elif defined(__CRT_HAVE_putwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,,putwc,(wchar_t __wc, FILE *__stream),(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,,putwc,(wchar_t __wc, FILE *__stream),fputwc,(__wc,__stream)) __THROWS(...)
#else /* LIBC: putwc */
#undef __std_putwc_defined
#endif /* putwc... */
#endif /* !__std_putwc_defined */
#ifndef __std_fgetws_defined
#define __std_fgetws_defined 1
#ifdef __fgetws_defined
__NAMESPACE_GLB_USING(fgetws)
#elif defined(__CRT_HAVE_fgetws_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetws_nolock) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetws)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetws_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),fgetws_unlocked,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetws_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 3)),wchar_t *,,fgetws,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream)) __THROWS(...)
#elif (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE_ferror_unlocked))
__NAMESPACE_STD_END
#include <local/wchar/fgetws.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) wchar_t *(__LIBCCALL fgetws)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws))(__buf, __bufsize, __stream); })
#else /* CUSTOM: fgetws */
#undef __std_fgetws_defined
#endif /* fgetws... */
#endif /* !__std_fgetws_defined */
#ifndef __std_fputws_defined
#define __std_fputws_defined 1
#ifdef __fputws_defined
__NAMESPACE_GLB_USING(fputws)
#elif defined(__CRT_HAVE_fputws_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputws_nolock) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputws)
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputws_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),fputws_unlocked,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws,(wchar_t const *__restrict __string, FILE *__restrict __stream),_fputws_nolock,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
__NAMESPACE_STD_END
#include <local/wchar/fputws.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws)(wchar_t const *__restrict __string, FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws))(__string, __stream); })
#else /* CUSTOM: fputws */
#undef __std_fputws_defined
#endif /* fputws... */
#endif /* !__std_fputws_defined */
#ifndef __std_ungetwc_defined
#define __std_ungetwc_defined 1
#ifdef __ungetwc_defined
__NAMESPACE_GLB_USING(ungetwc)
#elif defined(__CRT_HAVE_ungetwc_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CDECLARE(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),(__wc,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),wint_t,__NOTHROW_NCX,ungetwc,(wint_t __wc, FILE *__stream),ungetwc_unlocked,(__wc,__stream))
#else /* LIBC: ungetwc */
#undef __std_ungetwc_defined
#endif /* ungetwc... */
#endif /* !__std_ungetwc_defined */
#ifndef __std_wcsftime_defined
#define __std_wcsftime_defined 1
#ifdef __wcsftime_defined
__NAMESPACE_GLB_USING(wcsftime)
#elif defined(__CRT_HAVE_wcsftime)
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,wcsftime,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp),(__buf,__buflen,__format,__tp))
#else /* LIBC: wcsftime */
__NAMESPACE_STD_END
#include <local/wchar/wcsftime.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBCCALL wcsftime)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))(__buf, __buflen, __format, __tp); })
#endif /* wcsftime... */
#endif /* !__std_wcsftime_defined */

#if !defined(__USE_DOS) || defined(__USE_ISOC95)
#ifndef __std_wcstok_defined
#define __std_wcstok_defined 1
#ifdef __wcstok_defined
__NAMESPACE_GLB_USING(wcstok)
#elif defined(__CRT_HAVE_wcstok) && (!defined(__CRT_DOS_PRIMARY))
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok_s)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#else /* LIBC: wcstok */
__NAMESPACE_STD_END
#include <local/wchar/wcstok.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstok, __FORCELOCAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__string, __delim, __save_ptr); })
#endif /* wcstok... */
#endif /* !__std_wcstok_defined */
#endif
#ifndef __std_wcslen_defined
#define __std_wcslen_defined 1
#ifdef __wcslen_defined
__NAMESPACE_GLB_USING(wcslen)
#elif defined(__CRT_HAVE_wcslen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcslen,(wchar_t const *__restrict __string),(__string))
#else /* LIBC: wcslen */
__NAMESPACE_STD_END
#include <local/wchar/wcslen.h>
__NAMESPACE_STD_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcslen)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslen))(__string); })
#endif /* wcslen... */
#endif /* !__std_wcslen_defined */
#ifndef __std_wcsspn_defined
#define __std_wcsspn_defined 1
#ifdef __wcsspn_defined
__NAMESPACE_GLB_USING(wcsspn)
#elif defined(__CRT_HAVE_wcsspn)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsspn,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* LIBC: wcsspn */
__NAMESPACE_STD_END
#include <local/wchar/wcsspn.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsspn)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))(__haystack, __accept); })
#endif /* wcsspn... */
#endif /* !__std_wcsspn_defined */
#ifndef __std_wcscspn_defined
#define __std_wcscspn_defined 1
#ifdef __wcscspn_defined
__NAMESPACE_GLB_USING(wcscspn)
#elif defined(__CRT_HAVE_wcscspn)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,wcscspn,(wchar_t const *__haystack, wchar_t const *__reject),(__haystack,__reject))
#else /* LIBC: wcscspn */
__NAMESPACE_STD_END
#include <local/wchar/wcscspn.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscspn, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcscspn)(wchar_t const *__haystack, wchar_t const *__reject) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))(__haystack, __reject); })
#endif /* wcscspn... */
#endif /* !__std_wcscspn_defined */
#ifndef __std_wcschr_defined
#define __std_wcschr_defined 1
#ifdef __wcschr_defined
__NAMESPACE_GLB_USING(wcschr)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcschr
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t *__restrict __haystack, wchar_t __needle),wcschr,(__haystack, __needle))
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschr,(__haystack, __needle))
}
#else /* LIBC: wcschr */
__NAMESPACE_STD_END
#include <local/wchar/wcschr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); }
}
#endif /* wcschr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcschr
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcschr */
__NAMESPACE_STD_END
#include <local/wchar/wcschr.h>
__NAMESPACE_STD_BEGIN
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr))(__haystack, __needle); })
#endif /* wcschr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__std_wcschr_defined */
#ifndef __std_wcsrchr_defined
#define __std_wcsrchr_defined 1
#ifdef __wcsrchr_defined
__NAMESPACE_GLB_USING(wcsrchr)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsrchr
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack, __needle))
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchr,(__haystack, __needle))
}
#else /* LIBC: wcsrchr */
__NAMESPACE_STD_END
#include <local/wchar/wcsrchr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); }
}
#endif /* wcsrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsrchr
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchr,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcsrchr */
__NAMESPACE_STD_END
#include <local/wchar/wcsrchr.h>
__NAMESPACE_STD_BEGIN
/* Return the pointer of the last instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchr)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchr))(__haystack, __needle); })
#endif /* wcsrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__std_wcsrchr_defined */
#ifndef __std_wcspbrk_defined
#define __std_wcspbrk_defined 1
#ifdef __wcspbrk_defined
__NAMESPACE_GLB_USING(wcspbrk)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcspbrk
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t *__haystack, wchar_t const *__accept),wcspbrk,(__haystack, __accept))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),wcspbrk,(__haystack, __accept))
}
#else /* LIBC: wcspbrk */
__NAMESPACE_STD_END
#include <local/wchar/wcspbrk.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); }
}
#endif /* wcspbrk... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcspbrk
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspbrk,(wchar_t const *__haystack, wchar_t const *__accept),(__haystack,__accept))
#else /* LIBC: wcspbrk */
__NAMESPACE_STD_END
#include <local/wchar/wcspbrk.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspbrk, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspbrk)(wchar_t const *__haystack, wchar_t const *__accept) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspbrk))(__haystack, __accept); })
#endif /* wcspbrk... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__std_wcspbrk_defined */
#ifndef __std_wcsstr_defined
#define __std_wcsstr_defined 1
#ifdef __wcsstr_defined
__NAMESPACE_GLB_USING(wcsstr)
#elif defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsstr
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcswcs)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack, __needle))
}
#else /* LIBC: wcsstr */
__NAMESPACE_STD_END
#include <local/wchar/wcsstr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
}
#endif /* wcsstr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsstr
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_wcswcs)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcsstr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#else /* LIBC: wcsstr */
__NAMESPACE_STD_END
#include <local/wchar/wcsstr.h>
__NAMESPACE_STD_BEGIN
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsstr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsstr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); })
#endif /* wcsstr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__std_wcsstr_defined */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wmemchr
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),wmemchr,(__haystack, __needle, __num_chars))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),wmemchr,(__haystack, __needle, __num_chars))
}
#elif defined(__CRT_HAVE_memchrw) && (__SIZEOF_WCHAR_T__ == 2)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack, __needle, __num_chars))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack, __needle, __num_chars))
}
#elif defined(__CRT_HAVE_memchrl) && (__SIZEOF_WCHAR_T__ == 4)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack, __needle, __num_chars))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack, __needle, __num_chars))
}
#else /* LIBC: wmemchr */
__NAMESPACE_STD_END
#include <local/wchar/wmemchr.h>
__NAMESPACE_STD_BEGIN
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); }
}
#endif /* wmemchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wmemchr
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),(__haystack,__needle,__num_chars))
#elif defined(__CRT_HAVE_memchrw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrw,(__haystack,__needle,__num_chars))
#elif defined(__CRT_HAVE_memchrl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmemchr,(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars),memchrl,(__haystack,__needle,__num_chars))
#else /* LIBC: wmemchr */
__NAMESPACE_STD_END
#include <local/wchar/wmemchr.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmemchr)(wchar_t const *__restrict __haystack, wchar_t __needle, size_t __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemchr))(__haystack, __needle, __num_chars); })
#endif /* wmemchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
#ifndef __std_fwide_defined
#define __std_fwide_defined 1
#ifdef __fwide_defined
__NAMESPACE_GLB_USING(fwide)
#elif defined(__CRT_HAVE_fwide)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,fwide,(FILE *__fp, int __mode),(__fp,__mode))
#else /* LIBC: fwide */
__NAMESPACE_STD_END
#include <local/wchar/fwide.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(fwide, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL fwide)(FILE *__fp, int __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwide))(__fp, __mode); })
#endif /* fwide... */
#endif /* !__std_fwide_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 */

#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
#ifndef __std_fwprintf_defined
#define __std_fwprintf_defined 1
#ifdef __fwprintf_defined
__NAMESPACE_GLB_USING(fwprintf)
#elif defined(__CRT_HAVE_fwprintf)
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf");
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)
__NAMESPACE_STD_END
#include <local/wchar/fwprintf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fwprintf)
#else /* __cplusplus */
#define fwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#endif /* !__cplusplus */
#else /* CUSTOM: fwprintf */
#undef __std_fwprintf_defined
#endif /* fwprintf... */
#endif /* !__std_fwprintf_defined */
#ifndef __std_vfwprintf_defined
#define __std_vfwprintf_defined 1
#ifdef __vfwprintf_defined
__NAMESPACE_GLB_USING(vfwprintf)
#elif defined(__CRT_HAVE_vfwprintf)
__CDECLARE(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,,vfwprintf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
__NAMESPACE_STD_END
#include <local/wchar/vfwprintf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf, __FORCELOCAL __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf)(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))(__stream, __format, __args); })
#else /* CUSTOM: vfwprintf */
#undef __std_vfwprintf_defined
#endif /* vfwprintf... */
#endif /* !__std_vfwprintf_defined */
#ifndef __std_wprintf_defined
#define __std_wprintf_defined 1
#ifdef __wprintf_defined
__NAMESPACE_GLB_USING(wprintf)
#elif defined(__CRT_HAVE_wprintf)
__LIBC __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf");
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf)
__NAMESPACE_STD_END
#include <local/wchar/wprintf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wprintf)
#else /* __cplusplus */
#define wprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#endif /* !__cplusplus */
#else /* CUSTOM: wprintf */
#undef __std_wprintf_defined
#endif /* wprintf... */
#endif /* !__std_wprintf_defined */
#ifndef __std_vwprintf_defined
#define __std_vwprintf_defined 1
#ifdef __vwprintf_defined
__NAMESPACE_GLB_USING(vwprintf)
#elif defined(__CRT_HAVE_vwprintf)
__CDECLARE(__ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,,vwprintf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
__NAMESPACE_STD_END
#include <local/wchar/vwprintf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf, __FORCELOCAL __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))(__format, __args); })
#else /* CUSTOM: vwprintf */
#undef __std_vwprintf_defined
#endif /* vwprintf... */
#endif /* !__std_vwprintf_defined */
#ifndef __std_fwscanf_defined
#define __std_fwscanf_defined 1
#ifdef __fwscanf_defined
__NAMESPACE_GLB_USING(fwscanf)
#elif defined(__CRT_HAVE_fwscanf)
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf)(FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
__NAMESPACE_STD_END
#include <local/wchar/fwscanf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fwscanf)
#else /* __cplusplus */
#define fwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#endif /* !__cplusplus */
#else /* CUSTOM: fwscanf */
#undef __std_fwscanf_defined
#endif /* fwscanf... */
#endif /* !__std_fwscanf_defined */
#ifndef __std_wscanf_defined
#define __std_wscanf_defined 1
#ifdef __wscanf_defined
__NAMESPACE_GLB_USING(wscanf)
#elif defined(__CRT_HAVE_wscanf)
__LIBC __ATTR_NONNULL((1)) __ATTR_LIBC_WSCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf)
__NAMESPACE_STD_END
#include <local/wchar/wscanf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wscanf)
#else /* __cplusplus */
#define wscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#endif /* !__cplusplus */
#else /* CUSTOM: wscanf */
#undef __std_wscanf_defined
#endif /* wscanf... */
#endif /* !__std_wscanf_defined */
#ifndef __std_swscanf_defined
#define __std_swscanf_defined 1
#ifdef __swscanf_defined
__NAMESPACE_GLB_USING(swscanf)
#elif defined(__CRT_HAVE_swscanf)
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 3) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swscanf");
#else /* LIBC: swscanf */
__NAMESPACE_STD_END
#include <local/wchar/swscanf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(swscanf)
#else /* __cplusplus */
#define swscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#endif /* !__cplusplus */
#endif /* swscanf... */
#endif /* !__std_swscanf_defined */
#ifndef __std_vswprintf_defined
#define __std_vswprintf_defined 1
#ifdef __vswprintf_defined
__NAMESPACE_GLB_USING(vswprintf)
#elif defined(__CRT_HAVE_vswprintf)
__CDECLARE(__ATTR_NONNULL((3)) __ATTR_LIBC_WPRINTF(3, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswprintf,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args),(__buf,__buflen,__format,__args))
#else /* LIBC: vswprintf */
__NAMESPACE_STD_END
#include <local/wchar/vswprintf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vswprintf, __FORCELOCAL __ATTR_NONNULL((3)) __ATTR_LIBC_WPRINTF(3, 0) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))(__buf, __buflen, __format, __args); })
#endif /* vswprintf... */
#endif /* !__std_vswprintf_defined */
#ifndef __std_swprintf_defined
#define __std_swprintf_defined 1
#ifdef __swprintf_defined
__NAMESPACE_GLB_USING(swprintf)
#elif defined(__CRT_HAVE_swprintf)
__LIBC __ATTR_NONNULL((3)) __ATTR_LIBC_WPRINTF(3, 4) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME_SAME("swprintf");
#elif defined(__CRT_HAVE__swprintf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_NONNULL((3)) __ATTR_LIBC_WPRINTF(3, 4) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, ...) __CASMNAME("_swprintf");
#else /* LIBC: swprintf */
__NAMESPACE_STD_END
#include <local/wchar/swprintf.h>
__NAMESPACE_STD_BEGIN
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(swprintf)
#else /* __cplusplus */
#define swprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* !__cplusplus */
#endif /* swprintf... */
#endif /* !__std_swprintf_defined */
#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

#ifdef __USE_ISOC99
#ifndef __NO_FPU
#ifndef __std_wcstof_defined
#define __std_wcstof_defined 1
#ifdef __wcstof_defined
__NAMESPACE_GLB_USING(wcstof)
#elif defined(__CRT_HAVE_wcstof)
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* LIBC: wcstof */
__NAMESPACE_STD_END
#include <local/wchar/wcstof.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))(__nptr, __endptr); })
#endif /* wcstof... */
#endif /* !__std_wcstof_defined */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __std_wcstold_defined
#define __std_wcstold_defined 1
#ifdef __wcstold_defined
__NAMESPACE_GLB_USING(wcstold)
#elif defined(__CRT_HAVE_wcstold)
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,wcstold,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* LIBC: wcstold */
__NAMESPACE_STD_END
#include <local/wchar/wcstold.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) long double __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))(__nptr, __endptr); })
#endif /* wcstold... */
#endif /* !__std_wcstold_defined */
#endif /* !__NO_FPU */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifndef __std_wcstoll_defined
#define __std_wcstoll_defined 1
#ifdef __wcstoll_defined
__NAMESPACE_GLB_USING(wcstoll)
#elif defined(__CRT_HAVE_wcstoll)
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#else /* LIBC: wcstoll */
__NAMESPACE_STD_END
#include <local/wchar/wcstoll.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); })
#endif /* wcstoll... */
#endif /* !__std_wcstoll_defined */
#ifndef __std_wcstoull_defined
#define __std_wcstoull_defined 1
#ifdef __wcstoull_defined
__NAMESPACE_GLB_USING(wcstoull)
#elif defined(__CRT_HAVE_wcstoull)
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstoull */
__NAMESPACE_STD_END
#include <local/wchar/wcstoull.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); })
#endif /* wcstoull... */
#endif /* !__std_wcstoull_defined */
#ifndef __std_vfwscanf_defined
#define __std_vfwscanf_defined 1
#ifdef __vfwscanf_defined
__NAMESPACE_GLB_USING(vfwscanf)
#elif defined(__CRT_HAVE_vfwscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,,vfwscanf,(FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#else /* LIBC: vfwscanf */
#undef __std_vfwscanf_defined
#endif /* vfwscanf... */
#endif /* !__std_vfwscanf_defined */
#ifndef __std_vwscanf_defined
#define __std_vwscanf_defined 1
#ifdef __vwscanf_defined
__NAMESPACE_GLB_USING(vwscanf)
#elif defined(__CRT_HAVE_vwscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_WSCANF(1, 0),__STDC_INT_AS_SIZE_T,,vwscanf,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
__NAMESPACE_STD_END
#include <local/wchar/vwscanf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_WSCANF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))(__format, __args); })
#else /* CUSTOM: vwscanf */
#undef __std_vwscanf_defined
#endif /* vwscanf... */
#endif /* !__std_vwscanf_defined */
#ifndef __std_vswscanf_defined
#define __std_vswscanf_defined 1
#ifdef __vswscanf_defined
__NAMESPACE_GLB_USING(vswscanf)
#elif defined(__CRT_HAVE_vswscanf)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,vswscanf,(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args),(__src,__format,__args))
#else /* LIBC: vswscanf */
__NAMESPACE_STD_END
#include <local/wchar/vswscanf.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(vswscanf, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 0) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf)(wchar_t const *__restrict __src, wchar_t const *__restrict __format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))(__src, __format, __args); })
#endif /* vswscanf... */
#endif /* !__std_vswscanf_defined */
#endif /* __USE_ISOC99 */
#ifdef __CRT_HAVE_wmempmove
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovew) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),mempmovew,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempmovel) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempmove,(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars),mempmovel,(__dst,__src,__num_chars))
#else /* LIBC: wmempmove */
__NAMESPACE_STD_END
#include <local/wchar/wmempmove.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempmove, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempmove)(wchar_t *__dst, wchar_t const *__src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempmove))(__dst, __src, __num_chars); })
#endif /* wmempmove... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(btowc)
__NAMESPACE_STD_USING(wctob)
__NAMESPACE_STD_USING(mbrtowc)
__NAMESPACE_STD_USING(wcrtomb)
__NAMESPACE_STD_USING(mbrlen)
__NAMESPACE_STD_USING(mbsrtowcs)
__NAMESPACE_STD_USING(wcsrtombs)
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(wcstod)
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(wcstol)
__NAMESPACE_STD_USING(wcstoul)
__NAMESPACE_STD_USING(mbsinit)
__NAMESPACE_STD_USING(wmemcmp)
__NAMESPACE_STD_USING(wmemcpy)
__NAMESPACE_STD_USING(wmemmove)
__NAMESPACE_STD_USING(wmemset)
#if !defined(__wcscpy_defined) && defined(__std_wcscpy_defined)
#define __wcscpy_defined 1
__NAMESPACE_STD_USING(wcscpy)
#endif /* !__wcscpy_defined && !__std_wcscpy_defined */
#if !defined(__wcscat_defined) && defined(__std_wcscat_defined)
#define __wcscat_defined 1
__NAMESPACE_STD_USING(wcscat)
#endif /* !__wcscat_defined && !__std_wcscat_defined */
#if !defined(__wcsncat_defined) && defined(__std_wcsncat_defined)
#define __wcsncat_defined 1
__NAMESPACE_STD_USING(wcsncat)
#endif /* !__wcsncat_defined && !__std_wcsncat_defined */
#if !defined(__wcsncpy_defined) && defined(__std_wcsncpy_defined)
#define __wcsncpy_defined 1
__NAMESPACE_STD_USING(wcsncpy)
#endif /* !__wcsncpy_defined && !__std_wcsncpy_defined */
#if !defined(__wcscmp_defined) && defined(__std_wcscmp_defined)
#define __wcscmp_defined 1
__NAMESPACE_STD_USING(wcscmp)
#endif /* !__wcscmp_defined && !__std_wcscmp_defined */
#if !defined(__wcsncmp_defined) && defined(__std_wcsncmp_defined)
#define __wcsncmp_defined 1
__NAMESPACE_STD_USING(wcsncmp)
#endif /* !__wcsncmp_defined && !__std_wcsncmp_defined */
#if !defined(__wcscoll_defined) && defined(__std_wcscoll_defined)
#define __wcscoll_defined 1
__NAMESPACE_STD_USING(wcscoll)
#endif /* !__wcscoll_defined && !__std_wcscoll_defined */
#if !defined(__wcsxfrm_defined) && defined(__std_wcsxfrm_defined)
#define __wcsxfrm_defined 1
__NAMESPACE_STD_USING(wcsxfrm)
#endif /* !__wcsxfrm_defined && !__std_wcsxfrm_defined */
#if !defined(__getwchar_defined) && defined(__std_getwchar_defined)
#define __getwchar_defined 1
__NAMESPACE_STD_USING(getwchar)
#endif /* !__getwchar_defined && !__std_getwchar_defined */
#if !defined(__fgetwc_defined) && defined(__std_fgetwc_defined)
#define __fgetwc_defined 1
__NAMESPACE_STD_USING(fgetwc)
#endif /* !__fgetwc_defined && !__std_fgetwc_defined */
#if !defined(__getwc_defined) && defined(__std_getwc_defined)
#define __getwc_defined 1
__NAMESPACE_STD_USING(getwc)
#endif /* !__getwc_defined && !__std_getwc_defined */
#if !defined(__putwchar_defined) && defined(__std_putwchar_defined)
#define __putwchar_defined 1
__NAMESPACE_STD_USING(putwchar)
#endif /* !__putwchar_defined && !__std_putwchar_defined */
#if !defined(__fputwc_defined) && defined(__std_fputwc_defined)
#define __fputwc_defined 1
__NAMESPACE_STD_USING(fputwc)
#endif /* !__fputwc_defined && !__std_fputwc_defined */
#if !defined(__putwc_defined) && defined(__std_putwc_defined)
#define __putwc_defined 1
__NAMESPACE_STD_USING(putwc)
#endif /* !__putwc_defined && !__std_putwc_defined */
#if !defined(__fgetws_defined) && defined(__std_fgetws_defined)
#define __fgetws_defined 1
__NAMESPACE_STD_USING(fgetws)
#endif /* !__fgetws_defined && !__std_fgetws_defined */
#if !defined(__fputws_defined) && defined(__std_fputws_defined)
#define __fputws_defined 1
__NAMESPACE_STD_USING(fputws)
#endif /* !__fputws_defined && !__std_fputws_defined */
#if !defined(__ungetwc_defined) && defined(__std_ungetwc_defined)
#define __ungetwc_defined 1
__NAMESPACE_STD_USING(ungetwc)
#endif /* !__ungetwc_defined && !__std_ungetwc_defined */
#if !defined(__wcsftime_defined) && defined(__std_wcsftime_defined)
#define __wcsftime_defined 1
__NAMESPACE_STD_USING(wcsftime)
#endif /* !__wcsftime_defined && !__std_wcsftime_defined */
#if !defined(__wcstok_defined) && defined(__std_wcstok_defined)
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined && !__std_wcstok_defined */
#if !defined(__wcslen_defined) && defined(__std_wcslen_defined)
#define __wcslen_defined 1
__NAMESPACE_STD_USING(wcslen)
#endif /* !__wcslen_defined && !__std_wcslen_defined */
#if !defined(__wcsspn_defined) && defined(__std_wcsspn_defined)
#define __wcsspn_defined 1
__NAMESPACE_STD_USING(wcsspn)
#endif /* !__wcsspn_defined && !__std_wcsspn_defined */
#if !defined(__wcscspn_defined) && defined(__std_wcscspn_defined)
#define __wcscspn_defined 1
__NAMESPACE_STD_USING(wcscspn)
#endif /* !__wcscspn_defined && !__std_wcscspn_defined */
#if !defined(__wcschr_defined) && defined(__std_wcschr_defined)
#define __wcschr_defined 1
__NAMESPACE_STD_USING(wcschr)
#endif /* !__wcschr_defined && !__std_wcschr_defined */
#if !defined(__wcsrchr_defined) && defined(__std_wcsrchr_defined)
#define __wcsrchr_defined 1
__NAMESPACE_STD_USING(wcsrchr)
#endif /* !__wcsrchr_defined && !__std_wcsrchr_defined */
#if !defined(__wcspbrk_defined) && defined(__std_wcspbrk_defined)
#define __wcspbrk_defined 1
__NAMESPACE_STD_USING(wcspbrk)
#endif /* !__wcspbrk_defined && !__std_wcspbrk_defined */
#if !defined(__wcsstr_defined) && defined(__std_wcsstr_defined)
#define __wcsstr_defined 1
__NAMESPACE_STD_USING(wcsstr)
#endif /* !__wcsstr_defined && !__std_wcsstr_defined */
__NAMESPACE_STD_USING(wmemchr)
#if !defined(__fwide_defined) && defined(__std_fwide_defined)
#define __fwide_defined 1
__NAMESPACE_STD_USING(fwide)
#endif /* !__fwide_defined && !__std_fwide_defined */
#if !defined(__fwprintf_defined) && defined(__std_fwprintf_defined)
#define __fwprintf_defined 1
__NAMESPACE_STD_USING(fwprintf)
#endif /* !__fwprintf_defined && !__std_fwprintf_defined */
#if !defined(__vfwprintf_defined) && defined(__std_vfwprintf_defined)
#define __vfwprintf_defined 1
__NAMESPACE_STD_USING(vfwprintf)
#endif /* !__vfwprintf_defined && !__std_vfwprintf_defined */
#if !defined(__wprintf_defined) && defined(__std_wprintf_defined)
#define __wprintf_defined 1
__NAMESPACE_STD_USING(wprintf)
#endif /* !__wprintf_defined && !__std_wprintf_defined */
#if !defined(__vwprintf_defined) && defined(__std_vwprintf_defined)
#define __vwprintf_defined 1
__NAMESPACE_STD_USING(vwprintf)
#endif /* !__vwprintf_defined && !__std_vwprintf_defined */
#if !defined(__fwscanf_defined) && defined(__std_fwscanf_defined)
#define __fwscanf_defined 1
__NAMESPACE_STD_USING(fwscanf)
#endif /* !__fwscanf_defined && !__std_fwscanf_defined */
#if !defined(__wscanf_defined) && defined(__std_wscanf_defined)
#define __wscanf_defined 1
__NAMESPACE_STD_USING(wscanf)
#endif /* !__wscanf_defined && !__std_wscanf_defined */
#if !defined(__swscanf_defined) && defined(__std_swscanf_defined)
#define __swscanf_defined 1
__NAMESPACE_STD_USING(swscanf)
#endif /* !__swscanf_defined && !__std_swscanf_defined */
#if !defined(__vswprintf_defined) && defined(__std_vswprintf_defined)
#define __vswprintf_defined 1
__NAMESPACE_STD_USING(vswprintf)
#endif /* !__vswprintf_defined && !__std_vswprintf_defined */
#if !defined(__swprintf_defined) && defined(__std_swprintf_defined)
#define __swprintf_defined 1
__NAMESPACE_STD_USING(swprintf)
#endif /* !__swprintf_defined && !__std_swprintf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __NO_FPU
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstof_defined) && defined(__std_wcstof_defined)
#define __wcstof_defined 1
__NAMESPACE_STD_USING(wcstof)
#endif /* !__wcstof_defined && !__std_wcstof_defined */
#if !defined(__wcstold_defined) && defined(__std_wcstold_defined)
#define __wcstold_defined 1
__NAMESPACE_STD_USING(wcstold)
#endif /* !__wcstold_defined && !__std_wcstold_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* !__NO_FPU */
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__wcstoll_defined) && defined(__std_wcstoll_defined)
#define __wcstoll_defined 1
__NAMESPACE_STD_USING(wcstoll)
#endif /* !__wcstoll_defined && !__std_wcstoll_defined */
#if !defined(__wcstoull_defined) && defined(__std_wcstoull_defined)
#define __wcstoull_defined 1
__NAMESPACE_STD_USING(wcstoull)
#endif /* !__wcstoull_defined && !__std_wcstoull_defined */
#if !defined(__vfwscanf_defined) && defined(__std_vfwscanf_defined)
#define __vfwscanf_defined 1
__NAMESPACE_STD_USING(vfwscanf)
#endif /* !__vfwscanf_defined && !__std_vfwscanf_defined */
#if !defined(__vwscanf_defined) && defined(__std_vwscanf_defined)
#define __vwscanf_defined 1
__NAMESPACE_STD_USING(vwscanf)
#endif /* !__vwscanf_defined && !__std_vwscanf_defined */
#if !defined(__vswscanf_defined) && defined(__std_vswscanf_defined)
#define __vswscanf_defined 1
__NAMESPACE_STD_USING(vswscanf)
#endif /* !__vswscanf_defined && !__std_vswscanf_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifndef __std_wcstok_defined
#define __std_wcstok_defined 1
/* Define wcstok() incorrectly, the same way DOS does. */
#if defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE_wcstok)
__NAMESPACE_STD_BEGIN
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string,wchar_t const *__restrict __delim),(__string,__delim))
__NAMESPACE_STD_END
#else /* __CRT_DOS_PRIMARY && __CRT_HAVE_wcstok */
#ifdef __CRT_HAVE_wcstok_s
__CREDIRECT(__ATTR_NONNULL((2,3)),wchar_t *,__NOTHROW_NCX,__crt_wcstok,(wchar_t *__string,wchar_t const *__restrict __delim,wchar_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok)
__CREDIRECT(__ATTR_NONNULL((2,3)),wchar_t *,__NOTHROW_NCX,__crt_wcstok,(wchar_t *__string,wchar_t const *__restrict __delim,wchar_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#else
#include <local/wchar/wcstok.h>
#define __crt_wcstok(string, delim, save_ptr) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(string, delim, save_ptr)
#endif
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK wchar_t *__wcstok_save_ptr = __NULLPTR;
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY wchar_t *__wcstok_save_ptr = __NULLPTR;
#else
__PRIVATE __ATTR_UNUSED wchar_t *__wcstok_save_ptr = __NULLPTR;
#endif
__NAMESPACE_STD_BEGIN
__LOCAL_LIBC(wcstok) __ATTR_NONNULL((2)) wchar_t *
__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__string, wchar_t const *__restrict __delim) {
	return __crt_wcstok(__string, __delim, &__wcstok_save_ptr);
}
__NAMESPACE_STD_END
#endif /* !__CRT_DOS_PRIMARY || !__CRT_HAVE_wcstok */
#endif /* !__std_wcstok_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __wcstok_defined
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_mbrlen
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__ps),mbrlen,(__str,__maxlen,__ps))
#elif defined(__CRT_HAVE___mbrlen)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__mbrlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__ps),(__str,__maxlen,__ps))
#else /* LIBC: mbrlen */
#include <local/wchar/mbrlen.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL __mbrlen)(char const *__restrict __str, __SIZE_TYPE__ __maxlen, __mbstate_t *__ps) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mbrlen))(__str, __maxlen, __ps); }
#endif /* __mbrlen... */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wcscasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* LIBC: wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); })
#endif /* wcscasecmp... */
#ifdef __CRT_HAVE_wcsncasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); })
#endif /* wcsncasecmp... */
#ifdef __CRT_HAVE_wcscasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* LIBC: wcscasecmp_l */
#include <local/wchar/wcscasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); })
#endif /* wcscasecmp_l... */
#ifdef __CRT_HAVE_wcsncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncasecmp_l */
#include <local/wchar/wcsncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); })
#endif /* wcsncasecmp_l... */
#ifdef __CRT_HAVE_wcscoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* LIBC: wcscoll_l */
#include <local/wchar/wcscoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); })
#endif /* wcscoll_l... */
#ifdef __CRT_HAVE_wcsxfrm_l
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* LIBC: wcsxfrm_l */
#include <local/wchar/wcsxfrm_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsxfrm_l, __FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); })
#endif /* wcsxfrm_l... */
#ifdef __CRT_HAVE_wcpcpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcpcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src),(__dst,__src))
#else /* LIBC: wcpcpy */
#include <local/wchar/wcpcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcpcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcpcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcpcpy))(__dst, __src); })
#endif /* wcpcpy... */
#ifdef __CRT_HAVE_wcpncpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcpncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* LIBC: wcpncpy */
#include <local/wchar/wcpncpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcpncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcpncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcpncpy))(__buf, __src, __buflen); })
#endif /* wcpncpy... */
#ifdef __CRT_HAVE_mbsnrtowcs
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,mbsnrtowcs,(wchar_t *__dst, char const **__restrict __psrc, __SIZE_TYPE__ __nmc, __SIZE_TYPE__ __len, __mbstate_t *__ps),(__dst,__psrc,__nmc,__len,__ps))
#endif /* mbsnrtowcs... */
#ifdef __CRT_HAVE_wcsnrtombs
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnrtombs,(char *__dst, wchar_t const **__restrict __psrc, __SIZE_TYPE__ __nwc, __SIZE_TYPE__ __len, __mbstate_t *__ps),(__dst,__psrc,__nwc,__len,__ps))
#endif /* wcsnrtombs... */
#ifdef __CRT_HAVE_open_wmemstream
__CDECLARE(,__FILE *,__NOTHROW_NCX,open_wmemstream,(wchar_t **__bufloc, __SIZE_TYPE__ *__sizeloc),(__bufloc,__sizeloc))
#endif /* open_wmemstream... */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)
#ifndef __wcsnlen_defined
#define __wcsnlen_defined 1
#ifdef __CRT_HAVE_wcsnlen
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnlen,(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen),(__string,__maxlen))
#else /* LIBC: wcsnlen */
#include <local/wchar/wcsnlen.h>
/* Same as `wcslen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlen, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen)(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlen))(__string, __maxlen); })
#endif /* wcsnlen... */
#endif /* !__wcsnlen_defined */
#ifndef __wcsdup_defined
#define __wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsdup,(wchar_t const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); })
#else /* CUSTOM: wcsdup */
#undef __wcsdup_defined
#endif /* wcsdup... */
#endif /* !__wcsdup_defined */
#endif /* __USE_XOPEN2K8 || __USE_DOS */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_wcwidth
__CDECLARE(__ATTR_WUNUSED,int,__NOTHROW_NCX,wcwidth,(wchar_t __ch),(__ch))
#else /* LIBC: wcwidth */
#include <local/wchar/wcwidth.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcwidth, __FORCELOCAL __ATTR_WUNUSED int __NOTHROW_NCX(__LIBCCALL wcwidth)(wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcwidth))(__ch); })
#endif /* wcwidth... */
#ifdef __CRT_HAVE_wcswidth
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,wcswidth,(wchar_t const *__restrict __string, __SIZE_TYPE__ __num_chars),(__string,__num_chars))
#else /* LIBC: wcswidth */
#include <local/wchar/wcswidth.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcswidth, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL wcswidth)(wchar_t const *__restrict __string, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcswidth))(__string, __num_chars); })
#endif /* wcswidth... */
#endif /* __USE_XOPEN */

#if defined(__USE_XOPEN) || defined(__USE_DOS)
#ifndef __wcswcs_defined
#define __wcswcs_defined 1
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcswcs
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcsstr)
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t *__haystack, wchar_t *__needle),wcsstr,(__haystack, __needle))
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack, __needle))
}
#else /* LIBC: wcsstr */
#include <local/wchar/wcsstr.h>
extern "C++" {
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
}
#endif /* wcswcs... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcswcs
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_wcsstr)
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcswcs,(wchar_t const *__haystack, wchar_t const *__needle),wcsstr,(__haystack,__needle))
#else /* LIBC: wcsstr */
#include <local/wchar/wcsstr.h>
/* Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
 * If no such needle exists, return `NULL' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcswcs)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsstr))(__haystack, __needle); }
#endif /* wcswcs... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#endif /* !__wcswcs_defined */
#endif /* __USE_XOPEN || __USE_DOS */

#ifdef __USE_GNU
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcschrnul
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschrnul,(wchar_t *__restrict __haystack, wchar_t __needle),wcschrnul,(__haystack, __needle))
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcschrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),wcschrnul,(__haystack, __needle))
}
#else /* LIBC: wcschrnul */
#include <local/wchar/wcschrnul.h>
extern "C++" {
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, __needle); }
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)__haystack, __needle); }
}
#endif /* wcschrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcschrnul
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcschrnul,(wchar_t const *__haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcschrnul */
#include <local/wchar/wcschrnul.h>
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcschrnul, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcschrnul)(wchar_t const *__haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))(__haystack, __needle); })
#endif /* wcschrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wmempcpy
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wmempcpy,(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#else /* LIBC: wmempcpy */
#include <local/wchar/wmempcpy.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempcpy)(wchar_t *__restrict __dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy))(__dst, __src, __num_chars); })
#endif /* wmempcpy... */
#ifndef __CXX_SYSTEM_HEADER
__NAMESPACE_STD_USING(wmempmove)
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_wcstol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__restrict __endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long,__NOTHROW_NCX,wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__restrict __endptr, int __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstol_l */
#include <local/wchar/wcstol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long __NOTHROW_NCX(__LIBCCALL wcstol_l)(wchar_t const *__restrict __nptr, wchar_t **__restrict __endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))(__nptr, __endptr, __base, __locale); })
#endif /* wcstol_l... */
#ifdef __CRT_HAVE_wcstoul_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__restrict __endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),unsigned long,__NOTHROW_NCX,wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__restrict __endptr, int __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoul_l */
#include <local/wchar/wcstoul_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul_l)(wchar_t const *__restrict __nptr, wchar_t **__restrict __endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))(__nptr, __endptr, __base, __locale); })
#endif /* wcstoul_l... */
#ifdef __CRT_HAVE_wcstoq
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcsto32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#else /* LIBC: wcstoll */
#include <local/wchar/wcstoll.h>
__FORCELOCAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoq)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); }
#endif /* wcstoq... */
#ifdef __CRT_HAVE_wcstouq
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou32) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstou32,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstouq,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstoull */
#include <local/wchar/wcstoull.h>
__FORCELOCAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstouq)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); }
#endif /* wcstouq... */
#ifdef __CRT_HAVE_wcstoll_l
__CDECLARE(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__LONGLONG,__NOTHROW_NCX,wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoll_l */
#include <local/wchar/wcstoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll_l, __FORCELOCAL __ATTR_NONNULL((1)) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))(__nptr, __endptr, __base, __locale); })
#endif /* wcstoll_l... */
#ifdef __CRT_HAVE_wcstoull_l
__CDECLARE(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && (__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__)
__CREDIRECT(__ATTR_NONNULL((1)),__ULONGLONG,__NOTHROW_NCX,wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* LIBC: wcstoull_l */
#include <local/wchar/wcstoull_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull_l, __FORCELOCAL __ATTR_NONNULL((1)) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))(__nptr, __endptr, __base, __locale); })
#endif /* wcstoull_l... */
#ifndef __NO_FPU
#ifdef __CRT_HAVE_wcstof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),float,__NOTHROW_NCX,wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#else /* LIBC: wcstof_l */
#include <local/wchar/wcstof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) float __NOTHROW_NCX(__LIBCCALL wcstof_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))(__nptr, __endptr, __locale); })
#endif /* wcstof_l... */
#ifdef __CRT_HAVE_wcstod_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),double,__NOTHROW_NCX,wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* LIBC: wcstod_l */
#include <local/wchar/wcstod_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) double __NOTHROW_NCX(__LIBCCALL wcstod_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))(__nptr, __endptr, __locale); })
#endif /* wcstod_l... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __CRT_HAVE_wcstold_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),_wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),long double,__NOTHROW_NCX,wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#else /* LIBC: wcstold_l */
#include <local/wchar/wcstold_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) long double __NOTHROW_NCX(__LIBCCALL wcstold_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))(__nptr, __endptr, __locale); })
#endif /* wcstold_l... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE_getwchar_unlocked
__CDECLARE(,__WINT_TYPE__,,getwchar_unlocked,(void),()) __THROWS(...)
#elif defined(__CRT_HAVE__getwchar_nolock)
__CREDIRECT(,__WINT_TYPE__,,getwchar_unlocked,(void),_getwchar_nolock,()) __THROWS(...)
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/getwchar_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(getwchar_unlocked, __FORCELOCAL __WINT_TYPE__ (__LIBCCALL getwchar_unlocked)(void) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar_unlocked))(); })
#endif /* getwchar_unlocked... */
#ifdef __CRT_HAVE_putwchar_unlocked
__CDECLARE(,__WINT_TYPE__,,putwchar_unlocked,(wchar_t __wc),(__wc)) __THROWS(...)
#elif defined(__CRT_HAVE__putwchar_nolock)
__CREDIRECT(,__WINT_TYPE__,,putwchar_unlocked,(wchar_t __wc),_putwchar_nolock,(__wc)) __THROWS(...)
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/putwchar_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(putwchar_unlocked, __FORCELOCAL __WINT_TYPE__ (__LIBCCALL putwchar_unlocked)(wchar_t __wc) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar_unlocked))(__wc); })
#endif /* putwchar_unlocked... */
#ifdef __CRT_HAVE_getwc_unlocked
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,,getwc_unlocked,(__FILE *__restrict __stream),(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,,getwc_unlocked,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,,getwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream)) __THROWS(...)
#endif /* getwc_unlocked... */
#ifdef __CRT_HAVE_putwc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,putwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream)) __THROWS(...)
#endif /* putwc_unlocked... */
#ifdef __CRT_HAVE_fgetwc_unlocked
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,,fgetwc_unlocked,(__FILE *__restrict __stream),(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,,fgetwc_unlocked,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream)) __THROWS(...)
#endif /* fgetwc_unlocked... */
#ifdef __CRT_HAVE_fputwc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,,fputwc_unlocked,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream)) __THROWS(...)
#endif /* fputwc_unlocked... */
#ifdef __CRT_HAVE_fgetws_unlocked
__CDECLARE(__ATTR_NONNULL((1, 3)),wchar_t *,,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetws)
__CREDIRECT(__ATTR_NONNULL((1, 3)),wchar_t *,,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),fgetws,(__buf,__bufsize,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fgetws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 3)),wchar_t *,,fgetws_unlocked,(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream),_fgetws_nolock,(__buf,__bufsize,__stream)) __THROWS(...)
#elif (defined(__CRT_HAVE_fgetwc_unlocked) || defined(__CRT_HAVE__fgetwc_nolock)) && (defined(__CRT_HAVE_ungetwc_unlocked) || defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE__ungetwc_nolock)) && (defined(__CRT_HAVE_ferror_unlocked) || defined(__CRT_HAVE_ferror))
#include <local/wchar/fgetws_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fgetws_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 3)) wchar_t *(__LIBCCALL fgetws_unlocked)(wchar_t *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetws_unlocked))(__buf, __bufsize, __stream); })
#endif /* fgetws_unlocked... */
#ifdef __CRT_HAVE_fputws_unlocked
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws_unlocked,(wchar_t const *__restrict __string, __FILE *__restrict __stream),(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fputws_nolock)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,,fputws_unlocked,(wchar_t const *__restrict __string, __FILE *__restrict __stream),_fputws_nolock,(__string,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#include <local/wchar/fputws_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fputws_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T (__LIBCCALL fputws_unlocked)(wchar_t const *__restrict __string, __FILE *__restrict __stream) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputws_unlocked))(__string, __stream); })
#endif /* fputws_unlocked... */
#ifdef __CRT_HAVE_wcsftime_l
__CDECLARE(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#else /* LIBC: wcsftime_l */
#include <local/wchar/wcsftime_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime_l, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsftime_l)(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* wcsftime_l... */
#endif /* __USE_GNU */




#ifdef __USE_KOS

/* KOS FILE extension functions. */

#if defined(__CRT_HAVE_file_wprinter_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_file_wprinter)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_file_wprinter_unlocked)
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,file_wprinter,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter_unlocked,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc)
#include <local/wchar/file_wprinter.h>
/* For use with `format_printf()' and friends: Prints to a `FILE *' closure argument */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_wprinter, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBCCALL file_wprinter)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter))(__arg, __data, __datalen); })
#endif /* file_wprinter... */
#ifdef __CRT_HAVE_file_wprinter_unlocked
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CDECLARE(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,file_wprinter_unlocked,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_file_wprinter)
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,,file_wprinter_unlocked,(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen),file_wprinter,(__arg,__data,__datalen)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock)
#include <local/wchar/file_wprinter_unlocked.h>
/* Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG' */
__NAMESPACE_LOCAL_USING_OR_IMPL(file_wprinter_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__ (__LIBCCALL file_wprinter_unlocked)(void *__arg, wchar_t const *__restrict __data, __SIZE_TYPE__ __datalen) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(file_wprinter_unlocked))(__arg, __data, __datalen); })
#endif /* file_wprinter_unlocked... */
#ifdef __CRT_HAVE_ungetwc_unlocked
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,ungetwc_unlocked,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),_ungetwc_nolock,(__ch,__stream))
#endif /* ungetwc_unlocked... */
#ifdef __CRT_HAVE_vfwprintf_unlocked
__CDECLARE(__ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0),__STDC_INT_AS_SIZE_T,,vfwprintf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter)
#include <local/wchar/vfwprintf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vfwprintf_unlocked, __FORCELOCAL __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vfwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf_unlocked))(__stream, __format, __args); })
#endif /* vfwprintf_unlocked... */
#ifdef __CRT_HAVE_fwprintf_unlocked
__LIBC __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WPRINTF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwprintf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf_unlocked");
#elif defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)
#include <local/wchar/fwprintf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fwprintf_unlocked)
#else /* __cplusplus */
#define fwprintf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf_unlocked))
#endif /* !__cplusplus */
#endif /* fwprintf_unlocked... */
#ifdef __CRT_HAVE_wprintf_unlocked
__LIBC __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wprintf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wprintf_unlocked");
#elif ((defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf_unlocked)
#include <local/wchar/wprintf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wprintf_unlocked)
#else /* __cplusplus */
#define wprintf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf_unlocked))
#endif /* !__cplusplus */
#endif /* wprintf_unlocked... */
#ifdef __CRT_HAVE_vwprintf_unlocked
__CDECLARE(__ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0),__STDC_INT_AS_SIZE_T,,vwprintf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif (defined(__CRT_HAVE_fputwc_unlocked) || defined(__CRT_HAVE__fputwc_nolock) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_vfwprintf_unlocked)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwprintf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vwprintf_unlocked, __FORCELOCAL __ATTR_NONNULL((1)) __ATTR_LIBC_WPRINTF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwprintf_unlocked)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf_unlocked))(__format, __args); })
#endif /* vwprintf_unlocked... */
#ifdef __CRT_HAVE_vfwscanf_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,,vfwscanf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_WSCANF(2, 0),__STDC_INT_AS_SIZE_T,,vfwscanf_unlocked,(__FILE *__restrict __stream, wchar_t const *__restrict __format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args)) __THROWS(...)
#endif /* vfwscanf_unlocked... */
#ifdef __CRT_HAVE_vwscanf_unlocked
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0),__STDC_INT_AS_SIZE_T,,vwscanf_unlocked,(wchar_t const *__restrict __format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif (defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwscanf_unlocked.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(vwscanf_unlocked, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 0) __STDC_INT_AS_SIZE_T (__LIBCCALL vwscanf_unlocked)(wchar_t const *__restrict __format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf_unlocked))(__format, __args); })
#endif /* vwscanf_unlocked... */
#ifdef __CRT_HAVE_fwscanf_unlocked
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __ATTR_LIBC_SCANF(2, 3) __STDC_INT_AS_SIZE_T (__VLIBCCALL fwscanf_unlocked)(__FILE *__restrict __stream, wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf_unlocked");
#elif defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)
#include <local/wchar/fwscanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(fwscanf_unlocked)
#else /* __cplusplus */
#define fwscanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf_unlocked))
#endif /* !__cplusplus */
#endif /* fwscanf_unlocked... */
#ifdef __CRT_HAVE_wscanf_unlocked
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_LIBC_SCANF(1, 2) __STDC_INT_AS_SIZE_T (__VLIBCCALL wscanf_unlocked)(wchar_t const *__restrict __format, ...) __THROWS(...) __CASMNAME_SAME("wscanf_unlocked");
#elif ((defined(__CRT_HAVE_vfwscanf_unlocked) || defined(__CRT_HAVE_vfwscanf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf_unlocked)
#include <local/wchar/wscanf_unlocked.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wscanf_unlocked)
#else /* __cplusplus */
#define wscanf_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf_unlocked))
#endif /* !__cplusplus */
#endif /* wscanf_unlocked... */




#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsend
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsend,(wchar_t *__restrict __string),wcsend,(__string))
/* Same as `STR+wcslen(STR)' */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsend,(wchar_t const *__restrict __string),wcsend,(__string))
}
#else /* LIBC: wcsend */
#include <local/wchar/wcsend.h>
extern "C++" {
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__string); }
/* Same as `STR+wcslen(STR)' */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__string); }
}
#endif /* wcsend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsend
/* Same as `STR+wcslen(STR)' */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsend,(wchar_t const *__restrict __string),(__string))
#else /* LIBC: wcsend */
#include <local/wchar/wcsend.h>
/* Same as `STR+wcslen(STR)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsend, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsend)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsend))(__string); })
#endif /* wcsend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsnend
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnend,(wchar_t *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnend,(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen),wcsnend,(__string, __maxlen))
}
#else /* LIBC: wcsnend */
#include <local/wchar/wcsnend.h>
extern "C++" {
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__string, __maxlen); }
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__string, __maxlen); }
}
#endif /* wcsnend... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsnend
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnend,(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen),(__string,__maxlen))
#else /* LIBC: wcsnend */
#include <local/wchar/wcsnend.h>
/* Same as `STR+wcsnlen(STR, MAX_CHARS)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnend, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnend)(wchar_t const *__restrict __string, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnend))(__string, __maxlen); })
#endif /* wcsnend... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcstou32
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,wcstou32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstou32 */
#include <local/wchar/wcstou32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou32, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou32)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou32))(__nptr, __endptr, __base); })
#endif /* wcstou32... */
#ifdef __CRT_HAVE_wcsto32
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_LONG_LONG__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_INTMAX_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT32_TYPE__,__NOTHROW_NCX,wcsto32,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#else /* LIBC: wcsto32 */
#include <local/wchar/wcsto32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto32, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT32_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto32)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto32))(__nptr, __endptr, __base); })
#endif /* wcsto32... */
#ifdef __UINT64_TYPE__
#ifdef __CRT_HAVE_wcstou64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoui64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoul) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__UINT64_TYPE__,__NOTHROW_NCX,wcstou64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoumax,(__nptr,__endptr,__base))
#else /* LIBC: wcstou64 */
#include <local/wchar/wcstou64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstou64, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcstou64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))(__nptr, __endptr, __base); })
#endif /* wcstou64... */
#ifdef __CRT_HAVE_wcsto64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),_wcstoi64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstol) && (__SIZEOF_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && (__SIZEOF_LONG_LONG__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && (__SIZEOF_INTMAX_T__ == 8)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__INT64_TYPE__,__NOTHROW_NCX,wcsto64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base),wcstoimax,(__nptr,__endptr,__base))
#else /* LIBC: wcsto64 */
#include <local/wchar/wcsto64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsto64, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsto64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, int __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))(__nptr, __endptr, __base); })
#endif /* wcsto64... */
#endif /* __UINT64_TYPE__ */

#ifdef _PROCESS_H
#ifndef __TWARGV
#ifdef __USE_DOS
#   define __TWARGV wchar_t const *const *__restrict ___argv
#   define __TWENVP wchar_t const *const *__restrict ___envp
#else
#   define __TWARGV wchar_t *const ___argv[__restrict_arr]
#   define __TWENVP wchar_t *const ___envp[__restrict_arr]
#endif
#endif /* !__TWARGV */
#ifndef __wexecv_defined
#define __wexecv_defined 1
#ifdef __CRT_HAVE_wexecv
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),(__path,____TWARGV))
#elif defined(__CRT_HAVE__wexecv)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecv,(wchar_t const *__restrict __path, __TWARGV),_wexecv,(__path,____TWARGV))
#else /* LIBC: wexecv */
#undef __wexecv_defined
#endif /* wexecv... */
#endif /* !__wexecv_defined */
#ifndef __wexecve_defined
#define __wexecve_defined 1
#ifdef __CRT_HAVE_wexecve
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__path,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wexecve)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecve,(wchar_t const *__restrict __path, __TWARGV, __TWENVP),_wexecve,(__path,____TWARGV,____TWENVP))
#else /* LIBC: wexecve */
#undef __wexecve_defined
#endif /* wexecve... */
#endif /* !__wexecve_defined */
#ifndef __wexecvp_defined
#define __wexecvp_defined 1
#ifdef __CRT_HAVE_wexecvp
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),(__file,____TWARGV))
#elif defined(__CRT_HAVE__wexecvp)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,wexecvp,(wchar_t const *__restrict __file, __TWARGV),_wexecvp,(__file,____TWARGV))
#else /* LIBC: wexecvp */
#undef __wexecvp_defined
#endif /* wexecvp... */
#endif /* !__wexecvp_defined */
#ifndef __wexecvpe_defined
#define __wexecvpe_defined 1
#ifdef __CRT_HAVE_wexecvpe
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__file,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wexecvpe)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,wexecvpe,(wchar_t const *__restrict __file, __TWARGV, __TWENVP),_wexecvpe,(__file,____TWARGV,____TWENVP))
#else /* LIBC: wexecvpe */
#undef __wexecvpe_defined
#endif /* wexecvpe... */
#endif /* !__wexecvpe_defined */
#ifndef __wexecl_defined
#define __wexecl_defined 1
#ifdef __CRT_HAVE_wexecl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wexecl");
#elif defined(__CRT_HAVE__wexecl) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecl)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wexecl");
#elif defined(__CRT_HAVE_wexecv) || defined(__CRT_HAVE__wexecv)
#include <local/parts.wchar.process/wexecl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexecl)
#else /* __cplusplus */
#define wexecl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecl))
#endif /* !__cplusplus */
#else /* CUSTOM: wexecl */
#undef __wexecl_defined
#endif /* wexecl... */
#endif /* !__wexecl_defined */
#ifndef __wexecle_defined
#define __wexecle_defined 1
#ifdef __CRT_HAVE_wexecle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wexecle");
#elif defined(__CRT_HAVE__wexecle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexecle)(wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wexecle");
#elif defined(__CRT_HAVE_wexecve) || defined(__CRT_HAVE__wexecve)
#include <local/parts.wchar.process/wexecle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexecle)
#else /* __cplusplus */
#define wexecle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexecle))
#endif /* !__cplusplus */
#else /* CUSTOM: wexecle */
#undef __wexecle_defined
#endif /* wexecle... */
#endif /* !__wexecle_defined */
#ifndef __wexeclp_defined
#define __wexeclp_defined 1
#ifdef __CRT_HAVE_wexeclp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wexeclp");
#elif defined(__CRT_HAVE__wexeclp) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclp)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wexeclp");
#elif defined(__CRT_HAVE_wexecvp) || defined(__CRT_HAVE__wexecvp)
#include <local/parts.wchar.process/wexeclp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexeclp)
#else /* __cplusplus */
#define wexeclp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclp))
#endif /* !__cplusplus */
#else /* CUSTOM: wexeclp */
#undef __wexeclp_defined
#endif /* wexeclp... */
#endif /* !__wexeclp_defined */
#ifndef __wexeclpe_defined
#define __wexeclpe_defined 1
#ifdef __CRT_HAVE_wexeclpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wexeclpe");
#elif defined(__CRT_HAVE__wexecle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((1)) int __NOTHROW_RPC(__VLIBCCALL wexeclpe)(wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wexecle");
#elif defined(__CRT_HAVE_wexecvpe) || defined(__CRT_HAVE__wexecvpe)
#include <local/parts.wchar.process/wexeclpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wexeclpe)
#else /* __cplusplus */
#define wexeclpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wexeclpe))
#endif /* !__cplusplus */
#else /* CUSTOM: wexeclpe */
#undef __wexeclpe_defined
#endif /* wexeclpe... */
#endif /* !__wexeclpe_defined */
#ifndef __wspawnv_defined
#define __wspawnv_defined 1
#ifdef __CRT_HAVE_wspawnv
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),(__mode,__path,____TWARGV))
#elif defined(__CRT_HAVE__wspawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnv,(int __mode, wchar_t const *__restrict __path, __TWARGV),_wspawnv,(__mode,__path,____TWARGV))
#else /* LIBC: wspawnv */
#undef __wspawnv_defined
#endif /* wspawnv... */
#endif /* !__wspawnv_defined */
#ifndef __wspawnve_defined
#define __wspawnve_defined 1
#ifdef __CRT_HAVE_wspawnve
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),(__mode,__path,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wspawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnve,(int __mode, wchar_t const *__restrict __path, __TWARGV, __TWENVP),_wspawnve,(__mode,__path,____TWARGV,____TWENVP))
#else /* LIBC: wspawnve */
#undef __wspawnve_defined
#endif /* wspawnve... */
#endif /* !__wspawnve_defined */
#ifndef __wspawnvp_defined
#define __wspawnvp_defined 1
#ifdef __CRT_HAVE_wspawnvp
__CDECLARE(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),(__mode,__file,____TWARGV))
#elif defined(__CRT_HAVE__wspawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,wspawnvp,(int __mode, wchar_t const *__restrict __file, __TWARGV),_wspawnvp,(__mode,__file,____TWARGV))
#else /* LIBC: wspawnvp */
#undef __wspawnvp_defined
#endif /* wspawnvp... */
#endif /* !__wspawnvp_defined */
#ifndef __wspawnvpe_defined
#define __wspawnvpe_defined 1
#ifdef __CRT_HAVE_wspawnvpe
__CDECLARE(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),(__mode,__file,____TWARGV,____TWENVP))
#elif defined(__CRT_HAVE__wspawnvpe)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,wspawnvpe,(int __mode, wchar_t const *__restrict __file, __TWARGV, __TWENVP),_wspawnvpe,(__mode,__file,____TWARGV,____TWENVP))
#else /* LIBC: wspawnvpe */
#undef __wspawnvpe_defined
#endif /* wspawnvpe... */
#endif /* !__wspawnvpe_defined */
#ifndef __wspawnl_defined
#define __wspawnl_defined 1
#ifdef __CRT_HAVE_wspawnl
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wspawnl");
#elif defined(__CRT_HAVE__wspawnl) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnl)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wspawnl");
#elif defined(__CRT_HAVE_wspawnv) || defined(__CRT_HAVE__wspawnv)
#include <local/parts.wchar.process/wspawnl.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnl)
#else /* __cplusplus */
#define wspawnl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnl))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnl */
#undef __wspawnl_defined
#endif /* wspawnl... */
#endif /* !__wspawnl_defined */
#ifndef __wspawnle_defined
#define __wspawnle_defined 1
#ifdef __CRT_HAVE_wspawnle
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wspawnle");
#elif defined(__CRT_HAVE__wspawnle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnle)(int __mode, wchar_t const *__restrict __path, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wspawnle");
#elif defined(__CRT_HAVE_wspawnve) || defined(__CRT_HAVE__wspawnve)
#include <local/parts.wchar.process/wspawnle.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnle)
#else /* __cplusplus */
#define wspawnle (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnle))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnle */
#undef __wspawnle_defined
#endif /* wspawnle... */
#endif /* !__wspawnle_defined */
#ifndef __wspawnlp_defined
#define __wspawnlp_defined 1
#ifdef __CRT_HAVE_wspawnlp
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME_SAME("wspawnlp");
#elif defined(__CRT_HAVE__wspawnlp) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlp)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL*/) __CASMNAME("_wspawnlp");
#elif defined(__CRT_HAVE_wspawnvp) || defined(__CRT_HAVE__wspawnvp)
#include <local/parts.wchar.process/wspawnlp.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnlp)
#else /* __cplusplus */
#define wspawnlp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlp))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnlp */
#undef __wspawnlp_defined
#endif /* wspawnlp... */
#endif /* !__wspawnlp_defined */
#ifndef __wspawnlpe_defined
#define __wspawnlpe_defined 1
#ifdef __CRT_HAVE_wspawnlpe
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME_SAME("wspawnlpe");
#elif defined(__CRT_HAVE__wspawnle) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t __NOTHROW_RPC(__VLIBCCALL wspawnlpe)(int __mode, wchar_t const *__restrict __file, wchar_t const *__args, ... /*, (wchar_t *)NULL, wchar_t **environ*/) __CASMNAME("_wspawnle");
#elif defined(__CRT_HAVE_wspawnvpe) || defined(__CRT_HAVE__wspawnvpe)
#include <local/parts.wchar.process/wspawnlpe.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(wspawnlpe)
#else /* __cplusplus */
#define wspawnlpe (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wspawnlpe))
#endif /* !__cplusplus */
#else /* CUSTOM: wspawnlpe */
#undef __wspawnlpe_defined
#endif /* wspawnlpe... */
#endif /* !__wspawnlpe_defined */
#ifndef __wsystem_defined
#define __wsystem_defined 1
#ifdef __CRT_HAVE_wsystem
__CDECLARE(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CREDIRECT(,int,__NOTHROW_RPC,wsystem,(wchar_t const *__cmd),_wsystem,(__cmd))
#else /* LIBC: wsystem */
#undef __wsystem_defined
#endif /* wsystem... */
#endif /* !__wsystem_defined */
#endif /* _PROCESS_H */

#ifdef __CRT_HAVE_wcsncoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsncoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsncoll,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncoll */
#include <local/wchar/wcsncoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll))(__s1, __s2, __maxlen); })
#endif /* wcsncoll... */
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
#else /* LIBC: wcscasecoll */
#include <local/wchar/wcscasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); })
#endif /* wcscasecoll... */
#ifdef __CRT_HAVE_wcsncasecoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecoll */
#include <local/wchar/wcsncasecoll.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecoll, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); })
#endif /* wcsncasecoll... */
#ifdef __CRT_HAVE_wcsnrev
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrev,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* LIBC: wcsnrev */
#include <local/wchar/wcsnrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrev)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrev))(__str, __maxlen); })
#endif /* wcsnrev... */
#ifdef __CRT_HAVE_wcsnlwr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnlwr,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* LIBC: wcsnlwr */
#include <local/wchar/wcsnlwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnlwr)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlwr))(__str, __maxlen); })
#endif /* wcsnlwr... */
#ifdef __CRT_HAVE_wcsnupr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnupr,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen),(__str,__maxlen))
#else /* LIBC: wcsnupr */
#include <local/wchar/wcsnupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnupr)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnupr))(__str, __maxlen); })
#endif /* wcsnupr... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcscasestr
extern "C++" {
/* Same as `wcsstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t *__haystack, wchar_t *__needle),wcscasestr,(__haystack, __needle))
/* Same as `wcsstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),wcscasestr,(__haystack, __needle))
}
#elif defined(__CRT_HAVE_wcswcs)
extern "C++" {
/* Same as `wcsstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t *__haystack, wchar_t *__needle),wcswcs,(__haystack, __needle))
/* Same as `wcsstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack, __needle))
}
#else /* LIBC: wcscasestr */
#include <local/wchar/wcscasestr.h>
extern "C++" {
/* Same as `wcsstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t *__haystack, wchar_t *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); }
/* Same as `wcsstr', but ignore casing */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); }
}
#endif /* wcscasestr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcscasestr
/* Same as `wcsstr', but ignore casing */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),(__haystack,__needle))
#elif defined(__CRT_HAVE_wcswcs)
/* Same as `wcsstr', but ignore casing */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr,(wchar_t const *__haystack, wchar_t const *__needle),wcswcs,(__haystack,__needle))
#else /* LIBC: wcscasestr */
#include <local/wchar/wcscasestr.h>
/* Same as `wcsstr', but ignore casing */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasestr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr)(wchar_t const *__haystack, wchar_t const *__needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr))(__haystack, __needle); })
#endif /* wcscasestr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcspcpy
/* Same as wcscpy, but return a pointer after the last written character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspcpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src),(__buf,__src))
#else /* LIBC: wcspcpy */
#include <local/wchar/wcspcpy.h>
/* Same as wcscpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspcpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspcpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspcpy))(__buf, __src); })
#endif /* wcspcpy... */
#ifdef __CRT_HAVE_wcspncpy
/* Same as wcsncpy, but return a pointer after the last written character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcspncpy,(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen),(__buf,__src,__buflen))
#else /* LIBC: wcspncpy */
#include <local/wchar/wcspncpy.h>
/* Same as wcsncpy, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcspncpy, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcspncpy)(wchar_t *__restrict __buf, wchar_t const *__restrict __src, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcspncpy))(__buf, __src, __buflen); })
#endif /* wcspncpy... */
#ifdef __CRT_HAVE_wmempset
/* Same as wmemset, but return a pointer after the last written character */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetw) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),mempsetw,(__dst,__filler,__num_chars))
#elif defined(__CRT_HAVE_mempsetl) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as wmemset, but return a pointer after the last written character */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wmempset,(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars),mempsetl,(__dst,__filler,__num_chars))
#else /* LIBC: wmempset */
#include <local/wchar/wmempset.h>
/* Same as wmemset, but return a pointer after the last written character */
__NAMESPACE_LOCAL_USING_OR_IMPL(wmempset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wmempset)(wchar_t *__dst, wchar_t __filler, __SIZE_TYPE__ __num_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempset))(__dst, __filler, __num_chars); })
#endif /* wmempset... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsnchr
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchr,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchr,(__haystack, __needle, __maxlen))
}
#else /* LIBC: wcsnchr */
#include <local/wchar/wcsnchr.h>
extern "C++" {
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); }
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); }
}
#endif /* wcsnchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsnchr
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnchr */
#include <local/wchar/wcsnchr.h>
/* Same as `wcschr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchr))(__haystack, __needle, __maxlen); })
#endif /* wcsnchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsnrchr
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchr,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnrchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchr,(__haystack, __needle, __maxlen))
}
#else /* LIBC: wcsnrchr */
#include <local/wchar/wcsnrchr.h>
extern "C++" {
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); }
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); }
}
#endif /* wcsnrchr... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsnrchr
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchr,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnrchr */
#include <local/wchar/wcsnrchr.h>
/* Same as `wcsrchr', but don't exceed `MAX_CHARS' characters. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrchr, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchr)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchr))(__haystack, __needle, __maxlen); })
#endif /* wcsnrchr... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcssep
__CDECLARE(__ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcssep,(wchar_t **__restrict __stringp, wchar_t const *__restrict __delim),(__stringp,__delim))
#else /* LIBC: wcssep */
#include <local/wchar/wcssep.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcssep, __FORCELOCAL __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcssep)(wchar_t **__restrict __stringp, wchar_t const *__restrict __delim) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcssep))(__stringp, __delim); })
#endif /* wcssep... */
#ifdef __CRT_HAVE_wcsfry
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsfry,(wchar_t *__restrict __string),(__string))
#else /* LIBC: wcsfry */
#include <local/wchar/wcsfry.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsfry, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsfry)(wchar_t *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsfry))(__string); })
#endif /* wcsfry... */
#ifdef __CRT_HAVE_wcsndup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsndup,(wchar_t const *__restrict __string, __SIZE_TYPE__ __max_chars),(__string,__max_chars))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/wchar/wcsndup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsndup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsndup)(wchar_t const *__restrict __string, __SIZE_TYPE__ __max_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsndup))(__string, __max_chars); })
#endif /* wcsndup... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsrchrnul
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchrnul,(wchar_t *__restrict __haystack, wchar_t __needle),wcsrchrnul,(__haystack, __needle))
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),wcsrchrnul,(__haystack, __needle))
}
#else /* LIBC: wcsrchrnul */
#include <local/wchar/wcsrchrnul.h>
extern "C++" {
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); }
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); }
}
#endif /* wcsrchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsrchrnul
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcsrchrnul */
#include <local/wchar/wcsrchrnul.h>
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul))(__haystack, __needle); })
#endif /* wcsrchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsnchrnul
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchrnul,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack, __needle, __maxlen))
}
#else /* LIBC: wcsnchrnul */
#include <local/wchar/wcsnchrnul.h>
extern "C++" {
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* wcsnchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsnchrnul
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnchrnul */
#include <local/wchar/wcsnchrnul.h>
/* Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))(__haystack, __needle, __maxlen); })
#endif /* wcsnchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcsnrchrnul
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t const *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack, __needle, __maxlen))
}
#else /* LIBC: wcsnrchrnul */
#include <local/wchar/wcsnrchrnul.h>
extern "C++" {
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); }
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); }
}
#endif /* wcsnrchrnul... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsnrchrnul
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CDECLARE(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnrchrnul,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnrchrnul */
#include <local/wchar/wcsnrchrnul.h>
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnrchrnul, __FORCELOCAL __ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnrchrnul)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))(__haystack, __needle, __maxlen); })
#endif /* wcsnrchrnul... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcsoff
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsoff,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcsoff */
#include <local/wchar/wcsoff.h>
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsoff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsoff)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsoff))(__haystack, __needle); })
#endif /* wcsoff... */
#ifdef __CRT_HAVE_wcsroff
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsroff,(wchar_t const *__restrict __haystack, wchar_t __needle),(__haystack,__needle))
#else /* LIBC: wcsroff */
#include <local/wchar/wcsroff.h>
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsroff)(wchar_t const *__restrict __haystack, wchar_t __needle) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsroff))(__haystack, __needle); })
#endif /* wcsroff... */
#ifdef __CRT_HAVE_wcsnoff
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnoff,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnoff */
#include <local/wchar/wcsnoff.h>
/* Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnoff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnoff)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnoff))(__haystack, __needle, __maxlen); })
#endif /* wcsnoff... */
#ifdef __CRT_HAVE_wcsnroff
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,wcsnroff,(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen),(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnroff */
#include <local/wchar/wcsnroff.h>
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnroff, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnroff)(wchar_t const *__restrict __haystack, wchar_t __needle, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnroff))(__haystack, __needle, __maxlen); })
#endif /* wcsnroff... */
#ifdef __CRT_HAVE_fuzzy_wmemcmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars),(__s1,__s1_chars,__s2,__s2_chars))
#elif !defined(__NO_MALLOCA)
#include <local/wchar/fuzzy_wmemcmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_chars, wchar_t const *__s2, __SIZE_TYPE__ __s2_chars) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcmp))(__s1, __s1_chars, __s2, __s2_chars); })
#endif /* fuzzy_wmemcmp... */
#ifdef __CRT_HAVE_fuzzy_wcscmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#include <local/wchar/fuzzy_wcscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscmp))(__s1, __s2); })
#endif /* fuzzy_wcscmp... */
#ifdef __CRT_HAVE_fuzzy_wcsncmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcmp)
#include <local/wchar/fuzzy_wcsncmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* fuzzy_wcsncmp... */
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcasecmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes),(__s1,__s1_bytes,__s2,__s2_bytes))
#elif !defined(__NO_MALLOCA)
#include <local/wchar/fuzzy_wmemcasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcasecmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp))(__s1, __s1_bytes, __s2, __s2_bytes); })
#endif /* fuzzy_wmemcasecmp... */
#ifdef __CRT_HAVE_fuzzy_wcscasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscasecmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#include <local/wchar/fuzzy_wcscasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscasecmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp))(__s1, __s2); })
#endif /* fuzzy_wcscasecmp... */
#ifdef __CRT_HAVE_fuzzy_wcsncasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncasecmp,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen),(__s1,__s1_maxlen,__s2,__s2_maxlen))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp)
#include <local/wchar/fuzzy_wcsncasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncasecmp)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp))(__s1, __s1_maxlen, __s2, __s2_maxlen); })
#endif /* fuzzy_wcsncasecmp... */
#ifdef __CRT_HAVE_wildwcscmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildwcscmp,(wchar_t const *__pattern, wchar_t const *__string),(__pattern,__string))
#else /* LIBC: wildwcscmp */
#include <local/wchar/wildwcscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildwcscmp)(wchar_t const *__pattern, wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))(__pattern, __string); })
#endif /* wildwcscmp... */
#ifdef __CRT_HAVE_wildwcscasecmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildwcscasecmp,(wchar_t const *__pattern, wchar_t const *__string),(__pattern,__string))
#else /* LIBC: wildwcscasecmp */
#include <local/wchar/wildwcscasecmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscasecmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildwcscasecmp)(wchar_t const *__pattern, wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp))(__pattern, __string); })
#endif /* wildwcscasecmp... */
#ifdef __CRT_HAVE_wcsverscmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsverscmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcsverscmp */
#include <local/wchar/wcsverscmp.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsverscmp, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsverscmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsverscmp))(__s1, __s2); })
#endif /* wcsverscmp... */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_wcsncoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncoll_l */
#include <local/wchar/wcsncoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* wcsncoll_l... */
#ifdef __CRT_HAVE_wcscasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcscasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#else /* LIBC: wcscasecoll_l */
#include <local/wchar/wcscasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcscasecoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); })
#endif /* wcscasecoll_l... */
#ifdef __CRT_HAVE_wcsncasecoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsncasecoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),_wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncasecoll_l */
#include <local/wchar/wcsncasecoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncasecoll_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsncasecoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); })
#endif /* wcsncasecoll_l... */
#ifdef __CRT_HAVE_wcslwr_l
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),_wcslwr_l,(__str,__locale))
#else /* LIBC: wcslwr_l */
#include <local/wchar/wcslwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); })
#endif /* wcslwr_l... */
#ifdef __CRT_HAVE_wcsupr_l
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),_wcsupr_l,(__str,__locale))
#else /* LIBC: wcsupr_l */
#include <local/wchar/wcsupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); })
#endif /* wcsupr_l... */
#ifdef __CRT_HAVE_wcsnlwr_l
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnlwr_l,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* LIBC: wcsnlwr_l */
#include <local/wchar/wcsnlwr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnlwr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnlwr_l)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnlwr_l))(__str, __maxlen, __locale); })
#endif /* wcsnlwr_l... */
#ifdef __CRT_HAVE_wcsnupr_l
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsnupr_l,(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__str,__maxlen,__locale))
#else /* LIBC: wcsnupr_l */
#include <local/wchar/wcsnupr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnupr_l, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnupr_l)(wchar_t *__restrict __str, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnupr_l))(__str, __maxlen, __locale); })
#endif /* wcsnupr_l... */
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_WCHAR_H_PROTO)
#ifdef __CRT_HAVE_wcscasestr_l
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr_l,(wchar_t *__haystack, wchar_t *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcscasestr_l,(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale),wcscasestr_l,(__haystack, __needle, __locale))
}
#elif defined(__CRT_HAVE_wcswcs)
extern "C++" {
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr_l,(wchar_t *__haystack, wchar_t *__needle, __locale_t __locale),wcswcs,(__haystack, __needle, __locale))
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t const *,__NOTHROW_NCX,wcscasestr_l,(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale),wcswcs,(__haystack, __needle, __locale))
}
#else /* LIBC: wcscasestr_l */
#include <local/wchar/wcscasestr_l.h>
extern "C++" {
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr_l)(wchar_t *__haystack, wchar_t *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))(__haystack, __needle, __locale); }
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t const *__NOTHROW_NCX(__LIBCCALL wcscasestr_l)(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))(__haystack, __needle, __locale); }
}
#endif /* wcscasestr_l... */
#else /* __cplusplus && __CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_wcscasestr_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr_l,(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale),(__haystack,__needle,__locale))
#elif defined(__CRT_HAVE_wcswcs)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),wchar_t *,__NOTHROW_NCX,wcscasestr_l,(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale),wcswcs,(__haystack,__needle,__locale))
#else /* LIBC: wcscasestr_l */
#include <local/wchar/wcscasestr_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscasestr_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcscasestr_l)(wchar_t const *__haystack, wchar_t const *__needle, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasestr_l))(__haystack, __needle, __locale); })
#endif /* wcscasestr_l... */
#endif /* !__cplusplus || !__CORRECT_ISO_CPP_WCHAR_H_PROTO */
#ifdef __CRT_HAVE_fuzzy_wmemcasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wmemcasecmp_l,(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale),(__s1,__s1_bytes,__s2,__s2_bytes,__locale))
#elif !defined(__NO_MALLOCA)
#include <local/wchar/fuzzy_wmemcasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wmemcasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wmemcasecmp_l)(wchar_t const *__s1, __SIZE_TYPE__ __s1_bytes, wchar_t const *__s2, __SIZE_TYPE__ __s2_bytes, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wmemcasecmp_l))(__s1, __s1_bytes, __s2, __s2_bytes, __locale); })
#endif /* fuzzy_wmemcasecmp_l... */
#ifdef __CRT_HAVE_fuzzy_wcscasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcscasecmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#include <local/wchar/fuzzy_wcscasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcscasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcscasecmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcscasecmp_l))(__s1, __s2, __locale); })
#endif /* fuzzy_wcscasecmp_l... */
#ifdef __CRT_HAVE_fuzzy_wcsncasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)),__SIZE_TYPE__,__NOTHROW_NCX,fuzzy_wcsncasecmp_l,(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale),(__s1,__s1_maxlen,__s2,__s2_maxlen,__locale))
#elif !defined(__NO_MALLOCA) || defined(__CRT_HAVE_fuzzy_wmemcasecmp_l)
#include <local/wchar/fuzzy_wcsncasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fuzzy_wcsncasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL fuzzy_wcsncasecmp_l)(wchar_t const *__s1, __SIZE_TYPE__ __s1_maxlen, wchar_t const *__s2, __SIZE_TYPE__ __s2_maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fuzzy_wcsncasecmp_l))(__s1, __s1_maxlen, __s2, __s2_maxlen, __locale); })
#endif /* fuzzy_wcsncasecmp_l... */
#ifdef __CRT_HAVE_wildwcscasecmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wildwcscasecmp_l,(wchar_t const *__pattern, wchar_t const *__string, __locale_t __locale),(__pattern,__string,__locale))
#else /* LIBC: wildwcscasecmp_l */
#include <local/wchar/wildwcscasecmp_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wildwcscasecmp_l, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wildwcscasecmp_l)(wchar_t const *__pattern, wchar_t const *__string, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscasecmp_l))(__pattern, __string, __locale); })
#endif /* wildwcscasecmp_l... */
#endif /* __USE_XOPEN2K8 */
#endif /* __USE_KOS */





#ifdef __USE_DOS
#ifndef _WSTRING_DEFINED
#define _WSTRING_DEFINED 1
#ifndef ___wcsdup_defined
#define ___wcsdup_defined 1
#ifdef __CRT_HAVE_wcsdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsdup,(wchar_t const *__restrict __string),(__string))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/wchar/wcsdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsdup)(wchar_t const *__restrict __string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsdup))(__string); }
#else /* CUSTOM: wcsdup */
#undef ___wcsdup_defined
#endif /* _wcsdup... */
#endif /* !___wcsdup_defined */

#ifdef __USE_DOS_SLIB
#ifndef __wcscat_s_defined
#define __wcscat_s_defined 1
#ifdef __CRT_HAVE_wcscat_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wcscat_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* LIBC: wcscat_s */
#include <local/wchar/wcscat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscat_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wcscat_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscat_s))(__dst, __dstsize, __src); })
#endif /* wcscat_s... */
#endif /* !__wcscat_s_defined */
#ifndef __wcscpy_s_defined
#define __wcscpy_s_defined 1
#ifdef __CRT_HAVE_wcscpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcscpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src),(__dst,__dstsize,__src))
#else /* LIBC: wcscpy_s */
#include <local/wchar/wcscpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcscpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcscpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscpy_s))(__dst, __dstsize, __src); })
#endif /* wcscpy_s... */
#endif /* !__wcscpy_s_defined */
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__LOCAL __ATTR_WUNUSED __ATTR_PURE
__SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen) {
	return __str ? wcsnlen(__str, __maxlen) : 0;
}
#endif /* !__wcsnlen_s_defined */
#ifndef __wcsncat_s_defined
#define __wcsncat_s_defined 1
#ifdef __CRT_HAVE_wcsncat_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncat_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* LIBC: wcsncat_s */
#include <local/wchar/wcsncat_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncat_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncat_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncat_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* wcsncat_s... */
#endif /* !__wcsncat_s_defined */
#ifndef __wcsncpy_s_defined
#define __wcsncpy_s_defined 1
#ifdef __CRT_HAVE_wcsncpy_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,wcsncpy_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen),(__dst,__dstsize,__src,__maxlen))
#else /* LIBC: wcsncpy_s */
#include <local/wchar/wcsncpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsncpy_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL wcsncpy_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t const *__src, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncpy_s))(__dst, __dstsize, __src, __maxlen); })
#endif /* wcsncpy_s... */
#endif /* !__wcsncpy_s_defined */
#ifndef __wcstok_s_defined
#define __wcstok_s_defined 1
#ifdef __CRT_HAVE_wcstok_s
__CDECLARE(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok)
__CREDIRECT(__ATTR_NONNULL((2, 3)),wchar_t *,__NOTHROW_NCX,wcstok_s,(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#else /* LIBC: wcstok */
#include <local/wchar/wcstok.h>
__FORCELOCAL __ATTR_NONNULL((2, 3)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcstok_s)(wchar_t *__string, wchar_t const *__restrict __delim, wchar_t **__restrict __save_ptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(__string, __delim, __save_ptr); }
#endif /* wcstok_s... */
#endif /* !__wcstok_s_defined */
#endif  /* __USE_DOS_SLIB */
#ifndef ___wcserror_defined
#define ___wcserror_defined 1
#ifdef __CRT_HAVE__wcserror
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_wcserror,(int __errno_value),(__errno_value))
#else /* LIBC: _wcserror */
#undef ___wcserror_defined
#endif /* _wcserror... */
#endif /* !___wcserror_defined */
#ifndef ___wcserror_s_defined
#define ___wcserror_s_defined 1
#ifdef __CRT_HAVE__wcserror_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, int __errno_value),(__buf,__bufsize,__errno_value))
#else /* LIBC: _wcserror_s */
#undef ___wcserror_s_defined
#endif /* _wcserror_s... */
#endif /* !___wcserror_s_defined */
#ifndef ____wcserror_defined
#define ____wcserror_defined 1
#ifdef __CRT_HAVE___wcserror
__CDECLARE(,wchar_t *,__NOTHROW_NCX,__wcserror,(wchar_t const *__message),(__message))
#else /* LIBC: __wcserror */
#undef ____wcserror_defined
#endif /* __wcserror... */
#endif /* !____wcserror_defined */
#ifndef ____wcserror_s_defined
#define ____wcserror_s_defined 1
#ifdef __CRT_HAVE___wcserror_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,__wcserror_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__message),(__buf,__bufsize,__message))
#else /* LIBC: __wcserror_s */
#undef ____wcserror_s_defined
#endif /* __wcserror_s... */
#endif /* !____wcserror_s_defined */
#ifndef ___wcsicmp_defined
#define ___wcsicmp_defined 1
#ifdef __CRT_HAVE__wcsicmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#elif defined(__CRT_HAVE_wcscasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcsicmp,(__s1,__s2))
#else /* LIBC: wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* _wcsicmp... */
#endif /* !___wcsicmp_defined */
#ifndef ___wcsnicmp_defined
#define ___wcsnicmp_defined 1
#ifdef __CRT_HAVE__wcsnicmp
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* _wcsnicmp... */
#endif /* !___wcsnicmp_defined */
#ifndef ___wcsicmp_l_defined
#define ___wcsicmp_l_defined 1
#ifdef __CRT_HAVE__wcsicmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#else /* LIBC: wcscasecmp_l */
#include <local/wchar/wcscasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))(__s1, __s2, __locale); }
#endif /* _wcsicmp_l... */
#endif /* !___wcsicmp_l_defined */
#ifndef ___wcsnicmp_l_defined
#define ___wcsnicmp_l_defined 1
#ifdef __CRT_HAVE__wcsnicmp_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsncasecmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncasecmp_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE_wcsnicmp_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicmp_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsnicmp_l,(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncasecmp_l */
#include <local/wchar/wcsncasecmp_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicmp_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _wcsnicmp_l... */
#endif /* !___wcsnicmp_l_defined */
#ifndef ___wcsnset_s_defined
#define ___wcsnset_s_defined 1
#ifdef __CRT_HAVE__wcsnset_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsnset_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__buf,__buflen,__ch,__maxlen))
#else /* LIBC: _wcsnset_s */
#include <local/wchar/_wcsnset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsnset_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsnset_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsnset_s))(__buf, __buflen, __ch, __maxlen); })
#endif /* _wcsnset_s... */
#endif /* !___wcsnset_s_defined */
#ifndef ___wcsset_s_defined
#define ___wcsset_s_defined 1
#ifdef __CRT_HAVE__wcsset_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wcsset_s,(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch),(__dst,__dstsize,__ch))
#else /* LIBC: _wcsset_s */
#include <local/wchar/_wcsset_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsset_s, __FORCELOCAL __ATTR_NONNULL((1)) __errno_t __NOTHROW_NCX(__LIBCCALL _wcsset_s)(wchar_t *__dst, __SIZE_TYPE__ __dstsize, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsset_s))(__dst, __dstsize, __ch); })
#endif /* _wcsset_s... */
#endif /* !___wcsset_s_defined */
#ifndef ___wcslwr_s_defined
#define ___wcslwr_s_defined 1
#ifdef __CRT_HAVE__wcslwr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* LIBC: _wcslwr_s */
#include <local/wchar/_wcslwr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s))(__buf, __buflen); })
#endif /* _wcslwr_s... */
#endif /* !___wcslwr_s_defined */
#ifndef ___wcsupr_s_defined
#define ___wcsupr_s_defined 1
#ifdef __CRT_HAVE__wcsupr_s
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#else /* LIBC: _wcsupr_s */
#include <local/wchar/_wcsupr_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s))(__buf, __buflen); })
#endif /* _wcsupr_s... */
#endif /* !___wcsupr_s_defined */
#ifndef ___wcslwr_s_l_defined
#define ___wcslwr_s_l_defined 1
#ifdef __CRT_HAVE__wcslwr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcslwr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* LIBC: _wcslwr_s_l */
#include <local/wchar/_wcslwr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcslwr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcslwr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcslwr_s_l))(__buf, __buflen, __locale); })
#endif /* _wcslwr_s_l... */
#endif /* !___wcslwr_s_l_defined */
#ifndef ___wcsupr_s_l_defined
#define ___wcsupr_s_l_defined 1
#ifdef __CRT_HAVE__wcsupr_s_l
__CDECLARE(,__errno_t,__NOTHROW_NCX,_wcsupr_s_l,(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale),(__buf,__buflen,__locale))
#else /* LIBC: _wcsupr_s_l */
#include <local/wchar/_wcsupr_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wcsupr_s_l, __FORCELOCAL __errno_t __NOTHROW_NCX(__LIBCCALL _wcsupr_s_l)(wchar_t *__buf, __SIZE_TYPE__ __buflen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wcsupr_s_l))(__buf, __buflen, __locale); })
#endif /* _wcsupr_s_l... */
#endif /* !___wcsupr_s_l_defined */
#ifndef __wmemcpy_s_defined
#define __wmemcpy_s_defined 1
#ifdef __CRT_HAVE_wmemcpy_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wmemcpy_s,(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* LIBC: wmemcpy_s */
#include <local/wchar/wmemcpy_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemcpy_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wmemcpy_s)(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy_s))(__dst, __dstlength, __src, __srclength); })
#endif /* wmemcpy_s... */
#endif /* !__wmemcpy_s_defined */
#ifndef __wmemmove_s_defined
#define __wmemmove_s_defined 1
#ifdef __CRT_HAVE_wmemmove_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,wmemmove_s,(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength),(__dst,__dstlength,__src,__srclength))
#else /* LIBC: wmemmove_s */
#include <local/wchar/wmemmove_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wmemmove_s, __FORCELOCAL __ATTR_NONNULL((1, 3)) __errno_t __NOTHROW_NCX(__LIBCCALL wmemmove_s)(wchar_t *__dst, rsize_t __dstlength, wchar_t const *__src, rsize_t __srclength) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemmove_s))(__dst, __dstlength, __src, __srclength); })
#endif /* wmemmove_s... */
#endif /* !__wmemmove_s_defined */



#ifndef ___wcsnset_defined
#define ___wcsnset_defined 1
#ifdef __CRT_HAVE_wcsnset
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),wcsnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__wcsnset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsnset,(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen),(__str,__ch,__maxlen))
#else /* LIBC: wcsnset */
#include <local/wchar/wcsnset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); }
#endif /* _wcsnset... */
#endif /* !___wcsnset_defined */
#ifndef ___wcsrev_defined
#define ___wcsrev_defined 1
#ifdef __CRT_HAVE_wcsrev
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),wcsrev,(__str))
#elif defined(__CRT_HAVE__wcsrev)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsrev,(wchar_t *__restrict __str),(__str))
#else /* LIBC: wcsrev */
#include <local/wchar/wcsrev.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); }
#endif /* _wcsrev... */
#endif /* !___wcsrev_defined */
#ifndef ___wcsset_defined
#define ___wcsset_defined 1
#ifdef __CRT_HAVE_wcsset
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, wchar_t __ch),wcsset,(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsset,(wchar_t *__restrict __str, wchar_t __ch),(__str,__ch))
#else /* LIBC: wcsset */
#include <local/wchar/wcsset.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsset)(wchar_t *__restrict __str, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); }
#endif /* _wcsset... */
#endif /* !___wcsset_defined */
#ifndef ___wcslwr_defined
#define ___wcslwr_defined 1
#ifdef __CRT_HAVE_wcslwr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),wcslwr,(__str))
#elif defined(__CRT_HAVE__wcslwr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr,(wchar_t *__restrict __str),(__str))
#else /* LIBC: wcslwr */
#include <local/wchar/wcslwr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); }
#endif /* _wcslwr... */
#endif /* !___wcslwr_defined */
#ifndef ___wcsupr_defined
#define ___wcsupr_defined 1
#ifdef __CRT_HAVE_wcsupr
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),wcsupr,(__str))
#elif defined(__CRT_HAVE__wcsupr)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr,(wchar_t *__restrict __str),(__str))
#else /* LIBC: wcsupr */
#include <local/wchar/wcsupr.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); }
#endif /* _wcsupr... */
#endif /* !___wcsupr_defined */
#ifndef ___wcslwr_l_defined
#define ___wcslwr_l_defined 1
#ifdef __CRT_HAVE_wcslwr_l
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),wcslwr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcslwr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcslwr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* LIBC: wcslwr_l */
#include <local/wchar/wcslwr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcslwr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr_l))(__str, __locale); }
#endif /* _wcslwr_l... */
#endif /* !___wcslwr_l_defined */
#ifndef ___wcsupr_l_defined
#define ___wcsupr_l_defined 1
#ifdef __CRT_HAVE_wcsupr_l
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),wcsupr_l,(__str,__locale))
#elif defined(__CRT_HAVE__wcsupr_l)
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wcsupr_l,(wchar_t *__restrict __str, __locale_t __locale),(__str,__locale))
#else /* LIBC: wcsupr_l */
#include <local/wchar/wcsupr_l.h>
__FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wcsupr_l)(wchar_t *__restrict __str, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr_l))(__str, __locale); }
#endif /* _wcsupr_l... */
#endif /* !___wcsupr_l_defined */
#ifndef ___wcsxfrm_l_defined
#define ___wcsxfrm_l_defined 1
#ifdef __CRT_HAVE_wcsxfrm_l
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsxfrm_l)
__CDECLARE(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__dst,__src,__maxlen,__locale))
#elif defined(__CRT_HAVE___wcsxfrm_l)
__CREDIRECT(__ATTR_NONNULL((2)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsxfrm_l,(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale),__wcsxfrm_l,(__dst,__src,__maxlen,__locale))
#else /* LIBC: wcsxfrm_l */
#include <local/wchar/wcsxfrm_l.h>
__FORCELOCAL __ATTR_NONNULL((2)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcsxfrm_l)(wchar_t *__dst, wchar_t const *__restrict __src, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsxfrm_l))(__dst, __src, __maxlen, __locale); }
#endif /* _wcsxfrm_l... */
#endif /* !___wcsxfrm_l_defined */
#ifndef ___wcscoll_l_defined
#define ___wcscoll_l_defined 1
#ifdef __CRT_HAVE_wcscoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),wcscoll_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcscoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscoll_l)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcscoll_l,(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale),__wcscoll_l,(__s1,__s2,__locale))
#else /* LIBC: wcscoll_l */
#include <local/wchar/wcscoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcscoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscoll_l))(__s1, __s2, __locale); }
#endif /* _wcscoll_l... */
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
#else /* LIBC: wcscasecoll */
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* _wcsicoll... */
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
#else /* LIBC: wcscasecoll_l */
#include <local/wchar/wcscasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll_l))(__s1, __s2, __locale); }
#endif /* _wcsicoll_l... */
#endif /* !___wcsicoll_l_defined */
#ifndef ___wcsncoll_defined
#define ___wcsncoll_defined 1
#ifdef __CRT_HAVE__wcsncoll
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecoll */
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* _wcsncoll... */
#endif /* !___wcsncoll_defined */
#ifndef ___wcsncoll_l_defined
#define ___wcsncoll_l_defined 1
#ifdef __CRT_HAVE_wcsncoll_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),wcsncoll_l,(__s1,__s2,__maxlen,__locale))
#elif defined(__CRT_HAVE__wcsncoll_l)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsncoll_l,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale),(__s1,__s2,__maxlen,__locale))
#else /* LIBC: wcsncoll_l */
#include <local/wchar/wcsncoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsncoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _wcsncoll_l... */
#endif /* !___wcsncoll_l_defined */
#ifndef ___wcsnicoll_defined
#define ___wcsnicoll_defined 1
#ifdef __CRT_HAVE_wcsncasecoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecoll,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsncasecmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wcsnicoll,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsnicmp,(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecoll */
#include <local/wchar/wcsncasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll))(__s1, __s2, __maxlen); }
#endif /* _wcsnicoll... */
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
#else /* LIBC: wcsncasecoll_l */
#include <local/wchar/wcsncasecoll_l.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL _wcsnicoll_l)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecoll_l))(__s1, __s2, __maxlen, __locale); }
#endif /* _wcsnicoll_l... */
#endif /* !___wcsnicoll_l_defined */



#ifndef __wcsicmp_defined
#define __wcsicmp_defined 1
#ifdef __CRT_HAVE_wcscasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),wcscasecmp,(__s1,__s2))
#elif defined(__CRT_HAVE__wcsicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),_wcsicmp,(__s1,__s2))
#elif defined(__CRT_HAVE_wcsicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsicmp,(wchar_t const *__s1, wchar_t const *__s2),(__s1,__s2))
#else /* LIBC: wcscasecmp */
#include <local/wchar/wcscasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicmp)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp))(__s1, __s2); }
#endif /* wcsicmp... */
#endif /* !__wcsicmp_defined */
#ifndef __wcsnicmp_defined
#define __wcsnicmp_defined 1
#ifdef __CRT_HAVE_wcsncasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),wcsncasecmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE__wcsnicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),_wcsnicmp,(__s1,__s2,__maxlen))
#elif defined(__CRT_HAVE_wcsnicmp)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wcsnicmp,(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen),(__s1,__s2,__maxlen))
#else /* LIBC: wcsncasecmp */
#include <local/wchar/wcsncasecmp.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsnicmp)(wchar_t const *__s1, wchar_t const *__s2, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsncasecmp))(__s1, __s2, __maxlen); }
#endif /* wcsnicmp... */
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
#else /* LIBC: wcscasecoll */
#include <local/wchar/wcscasecoll.h>
__FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL wcsicoll)(wchar_t const *__s1, wchar_t const *__s2) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecoll))(__s1, __s2); }
#endif /* wcsicoll... */
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
#else /* LIBC: wcsnset */
#include <local/wchar/wcsnset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsnset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsnset)(wchar_t *__restrict __str, wchar_t __ch, __SIZE_TYPE__ __maxlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnset))(__str, __ch, __maxlen); })
#endif /* wcsnset... */
#endif /* !__wcsnset_defined */
#ifndef __wcsrev_defined
#define __wcsrev_defined 1
#ifdef __CRT_HAVE_wcsrev
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsrev)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsrev,(wchar_t *__restrict __str),_wcsrev,(__str))
#else /* LIBC: wcsrev */
#include <local/wchar/wcsrev.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsrev, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsrev)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrev))(__str); })
#endif /* wcsrev... */
#endif /* !__wcsrev_defined */
#ifndef __wcsset_defined
#define __wcsset_defined 1
#ifdef __CRT_HAVE_wcsset
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, wchar_t __ch),(__str,__ch))
#elif defined(__CRT_HAVE__wcsset)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsset,(wchar_t *__restrict __str, wchar_t __ch),_wcsset,(__str,__ch))
#else /* LIBC: wcsset */
#include <local/wchar/wcsset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsset, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsset)(wchar_t *__restrict __str, wchar_t __ch) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsset))(__str, __ch); })
#endif /* wcsset... */
#endif /* !__wcsset_defined */
#ifndef __wcslwr_defined
#define __wcslwr_defined 1
#ifdef __CRT_HAVE_wcslwr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcslwr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcslwr,(wchar_t *__restrict __str),_wcslwr,(__str))
#else /* LIBC: wcslwr */
#include <local/wchar/wcslwr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcslwr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcslwr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcslwr))(__str); })
#endif /* wcslwr... */
#endif /* !__wcslwr_defined */
#ifndef __wcsupr_defined
#define __wcsupr_defined 1
#ifdef __CRT_HAVE_wcsupr
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),(__str))
#elif defined(__CRT_HAVE__wcsupr)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,wcsupr,(wchar_t *__restrict __str),_wcsupr,(__str))
#else /* LIBC: wcsupr */
#include <local/wchar/wcsupr.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsupr, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL wcsupr)(wchar_t *__restrict __str) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsupr))(__str); })
#endif /* wcsupr... */
#endif /* !__wcsupr_defined */
#endif /* __USE_DOS || __USE_KOS */
#ifdef __USE_DOS
#ifndef _WSTDIO_DEFINED
#define _WSTDIO_DEFINED 1
#ifdef __USE_DOS_SLIB
#ifndef __vswprintf_s_defined
#define __vswprintf_s_defined 1
#ifdef __CRT_HAVE_vswprintf_s
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vswprintf_s,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __builtin_va_list __args),(__dst,__wchar_count,__format,__args))
#elif defined(__CRT_HAVE_vswprintf)
__CREDIRECT(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vswprintf_s,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __builtin_va_list __args),vswprintf,(__dst,__wchar_count,__format,__args))
#else /* LIBC: vswprintf */
#include <local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vswprintf_s)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __builtin_va_list __args) { return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)__dst, __wchar_count, (__WCHAR_TYPE__ const *)__format, __args); }
#endif /* vswprintf_s... */
#endif /* !__vswprintf_s_defined */
#ifndef __swprintf_s_defined
#define __swprintf_s_defined 1
#ifdef __CRT_HAVE_swprintf_s
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf_s)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, ...) __CASMNAME_SAME("swprintf_s");
#elif defined(__CRT_HAVE_swprintf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL swprintf_s)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, ...) __CASMNAME("swprintf");
#else /* LIBC: swprintf */
#include <local/wchar/swprintf.h>
#define swprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* swprintf_s... */
#endif /* !__swprintf_s_defined */
#ifndef __vfwprintf_s_defined
#define __vfwprintf_s_defined 1
#ifdef __CRT_HAVE_vfwprintf_s
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,vfwprintf_s,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwprintf)
__CREDIRECT(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,vfwprintf_s,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),vfwprintf,(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#include <local/wchar/vfwprintf.h>
__FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vfwprintf_s)(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vfwprintf))((__FILE *)__stream, (__WCHAR_TYPE__ const *)__format, __args); }
#else /* CUSTOM: vfwprintf */
#undef __vfwprintf_s_defined
#endif /* vfwprintf_s... */
#endif /* !__vfwprintf_s_defined */
#ifndef __fwprintf_s_defined
#define __fwprintf_s_defined 1
#ifdef __CRT_HAVE_fwprintf_s
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fwprintf_s)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("fwprintf_s");
#elif defined(__CRT_HAVE_fwprintf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fwprintf_s)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME("fwprintf");
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)
#include <local/wchar/fwprintf.h>
#define fwprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwprintf))
#else /* CUSTOM: fwprintf */
#undef __fwprintf_s_defined
#endif /* fwprintf_s... */
#endif /* !__fwprintf_s_defined */
#ifndef __vwprintf_s_defined
#define __vwprintf_s_defined 1
#ifdef __CRT_HAVE_vwprintf_s
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,vwprintf_s,(wchar_t const *__format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vwprintf)
__CREDIRECT(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,vwprintf_s,(wchar_t const *__format, __builtin_va_list __args),vwprintf,(__format,__args)) __THROWS(...)
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwprintf.h>
__FORCELOCAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vwprintf_s)(wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwprintf))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* CUSTOM: vwprintf */
#undef __vwprintf_s_defined
#endif /* vwprintf_s... */
#endif /* !__vwprintf_s_defined */
#ifndef __wprintf_s_defined
#define __wprintf_s_defined 1
#ifdef __CRT_HAVE_wprintf_s
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL wprintf_s)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("wprintf_s");
#elif defined(__CRT_HAVE_wprintf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL wprintf_s)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME("wprintf");
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf)
#include <local/wchar/wprintf.h>
#define wprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wprintf))
#else /* CUSTOM: wprintf */
#undef __wprintf_s_defined
#endif /* wprintf_s... */
#endif /* !__wprintf_s_defined */
#ifndef __vswscanf_s_defined
#define __vswscanf_s_defined 1
#ifdef __CRT_HAVE_vswscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vswscanf_s,(wchar_t const *__src, wchar_t const *__format, __builtin_va_list __args),(__src,__format,__args))
#elif defined(__CRT_HAVE_vswscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,vswscanf_s,(wchar_t const *__src, wchar_t const *__format, __builtin_va_list __args),vswscanf,(__src,__format,__args))
#else /* LIBC: vswscanf */
#include <local/wchar/vswscanf.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL vswscanf_s)(wchar_t const *__src, wchar_t const *__format, __builtin_va_list __args) { return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswscanf))((__WCHAR_TYPE__ const *)__src, (__WCHAR_TYPE__ const *)__format, __args); }
#endif /* vswscanf_s... */
#endif /* !__vswscanf_s_defined */
#ifndef __swscanf_s_defined
#define __swscanf_s_defined 1
#ifdef __CRT_HAVE_swscanf_s
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf_s)(wchar_t const *__src, wchar_t const *__format, ...) __CASMNAME_SAME("swscanf_s");
#elif defined(__CRT_HAVE_swscanf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL swscanf_s)(wchar_t const *__src, wchar_t const *__format, ...) __CASMNAME("swscanf");
#else /* LIBC: swscanf */
#include <local/wchar/swscanf.h>
#define swscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swscanf))
#endif /* swscanf_s... */
#endif /* !__swscanf_s_defined */
#ifndef __vfwscanf_s_defined
#define __vfwscanf_s_defined 1
#ifdef __CRT_HAVE_vfwscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,vfwscanf_s,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,vfwscanf_s,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),vfwscanf,(__stream,__format,__args)) __THROWS(...)
#else /* LIBC: vfwscanf_s */
#undef __vfwscanf_s_defined
#endif /* vfwscanf_s... */
#endif /* !__vfwscanf_s_defined */
#ifndef __fwscanf_s_defined
#define __fwscanf_s_defined 1
#ifdef __CRT_HAVE_fwscanf_s
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fwscanf_s)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("fwscanf_s");
#elif defined(__CRT_HAVE_fwscanf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL fwscanf_s)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME("fwscanf");
#elif defined(__CRT_HAVE_vfwscanf)
#include <local/wchar/fwscanf.h>
#define fwscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fwscanf))
#else /* CUSTOM: fwscanf */
#undef __fwscanf_s_defined
#endif /* fwscanf_s... */
#endif /* !__fwscanf_s_defined */
#ifndef __vwscanf_s_defined
#define __vwscanf_s_defined 1
#ifdef __CRT_HAVE_vwscanf_s
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,vwscanf_s,(wchar_t const *__format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vwscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,vwscanf_s,(wchar_t const *__format, __builtin_va_list __args),vwscanf,(__format,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)
#include <local/wchar/vwscanf.h>
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL vwscanf_s)(wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vwscanf))((__WCHAR_TYPE__ const *)__format, __args); }
#else /* CUSTOM: vwscanf */
#undef __vwscanf_s_defined
#endif /* vwscanf_s... */
#endif /* !__vwscanf_s_defined */
#ifndef __wscanf_s_defined
#define __wscanf_s_defined 1
#ifdef __CRT_HAVE_wscanf_s
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL wscanf_s)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("wscanf_s");
#elif defined(__CRT_HAVE_wscanf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL wscanf_s)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME("wscanf");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf)
#include <local/wchar/wscanf.h>
#define wscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wscanf))
#else /* CUSTOM: wscanf */
#undef __wscanf_s_defined
#endif /* wscanf_s... */
#endif /* !__wscanf_s_defined */
#endif /* __USE_DOS_SLIB */
#ifndef ___vscwprintf_defined
#define ___vscwprintf_defined 1
#ifdef __CRT_HAVE__vscwprintf
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* LIBC: _vscwprintf */
#include <local/wchar/_vscwprintf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf))(__format, __args); })
#endif /* _vscwprintf... */
#endif /* !___vscwprintf_defined */
#ifndef ___scwprintf_defined
#define ___scwprintf_defined 1
#ifdef __CRT_HAVE__scwprintf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__VLIBCCALL _scwprintf)(wchar_t const *__format, ...) __CASMNAME_SAME("_scwprintf");
#else /* LIBC: _scwprintf */
#include <local/wchar/_scwprintf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_scwprintf)
#else /* __cplusplus */
#define _scwprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf))
#endif /* !__cplusplus */
#endif /* _scwprintf... */
#endif /* !___scwprintf_defined */
#ifndef ___vscwprintf_p_defined
#define ___vscwprintf_p_defined 1
#ifdef __CRT_HAVE__vscwprintf_p
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_p,(wchar_t const *__format, __builtin_va_list __args),(__format,__args))
#else /* LIBC: _vscwprintf_p */
#include <local/wchar/_vscwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_p, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_p)(wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_p))(__format, __args); })
#endif /* _vscwprintf_p... */
#endif /* !___vscwprintf_p_defined */
#ifndef ___scwprintf_p_defined
#define ___scwprintf_p_defined 1
#ifdef __CRT_HAVE__scwprintf_p
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p)(wchar_t const *__format, ...) __CASMNAME_SAME("_scwprintf_p");
#else /* LIBC: _scwprintf_p */
#include <local/wchar/_scwprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_scwprintf_p)
#else /* __cplusplus */
#define _scwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p))
#endif /* !__cplusplus */
#endif /* _scwprintf_p... */
#endif /* !___scwprintf_p_defined */
#ifndef ___vscwprintf_l_defined
#define ___vscwprintf_l_defined 1
#ifdef __CRT_HAVE__vscwprintf_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* LIBC: _vscwprintf_l */
#include <local/wchar/_vscwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_l))(__format, __locale, __args); })
#endif /* _vscwprintf_l... */
#endif /* !___vscwprintf_l_defined */
#ifndef ___scwprintf_l_defined
#define ___scwprintf_l_defined 1
#ifdef __CRT_HAVE__scwprintf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scwprintf_l");
#else /* LIBC: _scwprintf_l */
#include <local/wchar/_scwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_scwprintf_l)
#else /* __cplusplus */
#define _scwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_l))
#endif /* !__cplusplus */
#endif /* _scwprintf_l... */
#endif /* !___scwprintf_l_defined */
#ifndef ___vscwprintf_p_l_defined
#define ___vscwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vscwprintf_p_l
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vscwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args))
#else /* LIBC: _vscwprintf_p_l */
#include <local/wchar/_vscwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vscwprintf_p_l, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vscwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vscwprintf_p_l))(__format, __locale, __args); })
#endif /* _vscwprintf_p_l... */
#endif /* !___vscwprintf_p_l_defined */
#ifndef ___scwprintf_p_l_defined
#define ___scwprintf_p_l_defined 1
#ifdef __CRT_HAVE__scwprintf_p_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _scwprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_scwprintf_p_l");
#else /* LIBC: _scwprintf_p_l */
#include <local/wchar/_scwprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_scwprintf_p_l)
#else /* __cplusplus */
#define _scwprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_scwprintf_p_l))
#endif /* !__cplusplus */
#endif /* _scwprintf_p_l... */
#endif /* !___scwprintf_p_l_defined */
#ifndef ___vswprintf_c_defined
#define ___vswprintf_c_defined 1
#ifdef __CRT_HAVE__vswprintf_c
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_c,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#elif defined(__CRT_HAVE_vswprintf)
__CREDIRECT(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_c,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args),vswprintf,(__buf,__bufsize,__format,__args))
#else /* LIBC: vswprintf */
#include <local/wchar/vswprintf.h>
__FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_c)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args) { return (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(vswprintf))((__WCHAR_TYPE__ *)__buf, __bufsize, (__WCHAR_TYPE__ const *)__format, __args); }
#endif /* _vswprintf_c... */
#endif /* !___vswprintf_c_defined */
#ifndef ___swprintf_c_defined
#define ___swprintf_c_defined 1
#ifdef __CRT_HAVE__swprintf_c
__LIBC __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__VLIBCCALL _swprintf_c)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_swprintf_c");
#elif defined(__CRT_HAVE_swprintf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_NONNULL((1, 3)) void __NOTHROW_NCX(__VLIBCCALL _swprintf_c)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME("swprintf");
#else /* LIBC: swprintf */
#include <local/wchar/swprintf.h>
#define _swprintf_c (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(swprintf))
#endif /* _swprintf_c... */
#endif /* !___swprintf_c_defined */
#ifndef ___vsnwprintf_s_defined
#define ___vsnwprintf_s_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s
__CDECLARE(__ATTR_NONNULL((4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_s,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__buflen,__format,__args))
#else /* LIBC: _vsnwprintf_s */
#include <local/wchar/_vsnwprintf_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_s, __FORCELOCAL __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_s))(__buf, __bufsize, __buflen, __format, __args); })
#endif /* _vsnwprintf_s... */
#endif /* !___vsnwprintf_s_defined */
#ifndef ___snwprintf_s_defined
#define ___snwprintf_s_defined 1
#ifdef __CRT_HAVE__snwprintf_s
__LIBC __ATTR_NONNULL((4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __buflen, wchar_t const *__format, ...) __CASMNAME_SAME("_snwprintf_s");
#else /* LIBC: _snwprintf_s */
#include <local/wchar/_snwprintf_s.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_snwprintf_s)
#else /* __cplusplus */
#define _snwprintf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s))
#endif /* !__cplusplus */
#endif /* _snwprintf_s... */
#endif /* !___snwprintf_s_defined */
#ifndef ___vfwprintf_p_defined
#define ___vfwprintf_p_defined 1
#ifdef __CRT_HAVE__vfwprintf_p
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,_vfwprintf_p,(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args),(__stream,__format,__args)) __THROWS(...)
#else /* LIBC: _vfwprintf_p */
#include <local/wchar/_vfwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_p, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_p)(__FILE *__stream, wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_p))(__stream, __format, __args); })
#endif /* _vfwprintf_p... */
#endif /* !___vfwprintf_p_defined */
#ifndef ___fwprintf_p_defined
#define ___fwprintf_p_defined 1
#ifdef __CRT_HAVE__fwprintf_p
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p)(__FILE *__stream, wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_p");
#else /* LIBC: _fwprintf_p */
#include <local/wchar/_fwprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_fwprintf_p)
#else /* __cplusplus */
#define _fwprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p))
#endif /* !__cplusplus */
#endif /* _fwprintf_p... */
#endif /* !___fwprintf_p_defined */
#ifndef ___vwprintf_p_defined
#define ___vwprintf_p_defined 1
#ifdef __CRT_HAVE__vwprintf_p
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,_vwprintf_p,(wchar_t const *__format, __builtin_va_list __args),(__format,__args)) __THROWS(...)
#elif !defined(__NO_STDSTREAMS)
#include <local/wchar/_vwprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_p, __FORCELOCAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_p)(wchar_t const *__format, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p))(__format, __args); })
#else /* CUSTOM: _vwprintf_p */
#undef ___vwprintf_p_defined
#endif /* _vwprintf_p... */
#endif /* !___vwprintf_p_defined */
#ifndef ___wprintf_p_defined
#define ___wprintf_p_defined 1
#ifdef __CRT_HAVE__wprintf_p
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p)(wchar_t const *__format, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_p");
#elif !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE__vwprintf_p)
#include <local/wchar/_wprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_wprintf_p)
#else /* __cplusplus */
#define _wprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p))
#endif /* !__cplusplus */
#else /* CUSTOM: _wprintf_p */
#undef ___wprintf_p_defined
#endif /* _wprintf_p... */
#endif /* !___wprintf_p_defined */
#ifndef ___vswprintf_p_defined
#define ___vswprintf_p_defined 1
#ifdef __CRT_HAVE__vswprintf_p
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_p,(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args),(__buf,__bufsize,__format,__args))
#else /* LIBC: _vswprintf_p */
#include <local/wchar/_vswprintf_p.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_p, __FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_p)(wchar_t *__buf, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p))(__buf, __bufsize, __format, __args); })
#endif /* _vswprintf_p... */
#endif /* !___vswprintf_p_defined */
#ifndef ___swprintf_p_defined
#define ___swprintf_p_defined 1
#ifdef __CRT_HAVE__swprintf_p
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_swprintf_p");
#else /* LIBC: _swprintf_p */
#include <local/wchar/_swprintf_p.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_swprintf_p)
#else /* __cplusplus */
#define _swprintf_p (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p))
#endif /* !__cplusplus */
#endif /* _swprintf_p... */
#endif /* !___swprintf_p_defined */
#ifndef ___vwprintf_l_defined
#define ___vwprintf_l_defined 1
#ifdef __CRT_HAVE__vwprintf_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,_vwprintf_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args)) __THROWS(...)
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf)
#include <local/wchar/_vwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_l, __FORCELOCAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_l))(__format, __locale, __args); })
#else /* CUSTOM: _vwprintf_l */
#undef ___vwprintf_l_defined
#endif /* _vwprintf_l... */
#endif /* !___vwprintf_l_defined */
#ifndef ___wprintf_l_defined
#define ___wprintf_l_defined 1
#ifdef __CRT_HAVE__wprintf_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_l");
#elif ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwprintf) || defined(__CRT_HAVE__vwprintf_l)
#include <local/wchar/_wprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_wprintf_l)
#else /* __cplusplus */
#define _wprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _wprintf_l */
#undef ___wprintf_l_defined
#endif /* _wprintf_l... */
#endif /* !___wprintf_l_defined */
#ifndef ___vwprintf_p_l_defined
#define ___vwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vwprintf_p_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,_vwprintf_p_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args)) __THROWS(...)
#elif !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE__vwprintf_p)
#include <local/wchar/_vwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_p_l, __FORCELOCAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_p_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_p_l))(__format, __locale, __args); })
#else /* CUSTOM: _vwprintf_p_l */
#undef ___vwprintf_p_l_defined
#endif /* _vwprintf_p_l... */
#endif /* !___vwprintf_p_l_defined */
#ifndef ___wprintf_p_l_defined
#define ___wprintf_p_l_defined 1
#ifdef __CRT_HAVE__wprintf_p_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_p_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_p_l");
#elif !defined(__NO_STDSTREAMS) || defined(__CRT_HAVE__vwprintf_p) || defined(__CRT_HAVE__vwprintf_p_l)
#include <local/wchar/_wprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_wprintf_p_l)
#else /* __cplusplus */
#define _wprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_p_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _wprintf_p_l */
#undef ___wprintf_p_l_defined
#endif /* _wprintf_p_l... */
#endif /* !___wprintf_p_l_defined */
#ifndef ___vwprintf_s_l_defined
#define ___vwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SSIZE_T,,_vwprintf_s_l,(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vwprintf_s) || defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS))
#include <local/wchar/_vwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vwprintf_s_l, __FORCELOCAL __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vwprintf_s_l)(wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vwprintf_s_l))(__format, __locale, __args); })
#else /* CUSTOM: _vwprintf_s_l */
#undef ___vwprintf_s_l_defined
#endif /* _vwprintf_s_l... */
#endif /* !___vwprintf_s_l_defined */
#ifndef ___wprintf_s_l_defined
#define ___wprintf_s_l_defined 1
#ifdef __CRT_HAVE__wprintf_s_l
__LIBC __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wprintf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wprintf_s_l");
#elif defined(__CRT_HAVE_vwprintf_s) || defined(__CRT_HAVE_vwprintf) || ((defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE__vwprintf_s_l)
#include <local/wchar/_wprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_wprintf_s_l)
#else /* __cplusplus */
#define _wprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wprintf_s_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _wprintf_s_l */
#undef ___wprintf_s_l_defined
#endif /* _wprintf_s_l... */
#endif /* !___wprintf_s_l_defined */
#ifndef ___vfwprintf_l_defined
#define ___vfwprintf_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,_vfwprintf_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf)
#include <local/wchar/_vfwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_l))(__stream, __format, __locale, __args); })
#else /* CUSTOM: _vfwprintf_l */
#undef ___vfwprintf_l_defined
#endif /* _vfwprintf_l... */
#endif /* !___vfwprintf_l_defined */
#ifndef ___fwprintf_l_defined
#define ___fwprintf_l_defined 1
#ifdef __CRT_HAVE__fwprintf_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_l");
#elif defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE__vfwprintf_l)
#include <local/wchar/_fwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_fwprintf_l)
#else /* __cplusplus */
#define _fwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _fwprintf_l */
#undef ___fwprintf_l_defined
#endif /* _fwprintf_l... */
#endif /* !___fwprintf_l_defined */
#ifndef ___vfwprintf_p_l_defined
#define ___vfwprintf_p_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_p_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,_vfwprintf_p_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args)) __THROWS(...)
#else /* LIBC: _vfwprintf_p_l */
#include <local/wchar/_vfwprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_p_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_p_l))(__stream, __format, __locale, __args); })
#endif /* _vfwprintf_p_l... */
#endif /* !___vfwprintf_p_l_defined */
#ifndef ___fwprintf_p_l_defined
#define ___fwprintf_p_l_defined 1
#ifdef __CRT_HAVE__fwprintf_p_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_p_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_p_l");
#else /* LIBC: _fwprintf_p_l */
#include <local/wchar/_fwprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_fwprintf_p_l)
#else /* __cplusplus */
#define _fwprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_p_l))
#endif /* !__cplusplus */
#endif /* _fwprintf_p_l... */
#endif /* !___fwprintf_p_l_defined */
#ifndef ___vfwprintf_s_l_defined
#define ___vfwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vfwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,,_vfwprintf_s_l,(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__stream,__format,__locale,__args)) __THROWS(...)
#elif defined(__CRT_HAVE_vfwprintf_s) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked)
#include <local/wchar/_vfwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vfwprintf_s_l, __FORCELOCAL __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__LIBCCALL _vfwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) __THROWS(...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vfwprintf_s_l))(__stream, __format, __locale, __args); })
#else /* CUSTOM: _vfwprintf_s_l */
#undef ___vfwprintf_s_l_defined
#endif /* _vfwprintf_s_l... */
#endif /* !___vfwprintf_s_l_defined */
#ifndef ___fwprintf_s_l_defined
#define ___fwprintf_s_l_defined 1
#ifdef __CRT_HAVE__fwprintf_s_l
__LIBC __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwprintf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwprintf_s_l");
#elif defined(__CRT_HAVE_vfwprintf_s) || defined(__CRT_HAVE_vfwprintf) || defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE__vfwprintf_s_l)
#include <local/wchar/_fwprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_fwprintf_s_l)
#else /* __cplusplus */
#define _fwprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwprintf_s_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _fwprintf_s_l */
#undef ___fwprintf_s_l_defined
#endif /* _fwprintf_s_l... */
#endif /* !___fwprintf_s_l_defined */
#ifndef ___vswprintf_c_l_defined
#define ___vswprintf_c_l_defined 1
#ifdef __CRT_HAVE__vswprintf_c_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_c_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* LIBC: _vswprintf_c_l */
#include <local/wchar/_vswprintf_c_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_c_l, __FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_c_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* _vswprintf_c_l... */
#endif /* !___vswprintf_c_l_defined */
#ifndef ___swprintf_c_l_defined
#define ___swprintf_c_l_defined 1
#ifdef __CRT_HAVE__swprintf_c_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_c_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_c_l");
#else /* LIBC: _swprintf_c_l */
#include <local/wchar/_swprintf_c_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_swprintf_c_l)
#else /* __cplusplus */
#define _swprintf_c_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_c_l))
#endif /* !__cplusplus */
#endif /* _swprintf_c_l... */
#endif /* !___swprintf_c_l_defined */
#ifndef ___vswprintf_p_l_defined
#define ___vswprintf_p_l_defined 1
#ifdef __CRT_HAVE__vswprintf_p_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_p_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* LIBC: _vswprintf_p_l */
#include <local/wchar/_vswprintf_p_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_p_l, __FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_p_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* _vswprintf_p_l... */
#endif /* !___vswprintf_p_l_defined */
#ifndef ___swprintf_p_l_defined
#define ___swprintf_p_l_defined 1
#ifdef __CRT_HAVE__swprintf_p_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_p_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_p_l");
#else /* LIBC: _swprintf_p_l */
#include <local/wchar/_swprintf_p_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_swprintf_p_l)
#else /* __cplusplus */
#define _swprintf_p_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_p_l))
#endif /* !__cplusplus */
#endif /* _swprintf_p_l... */
#endif /* !___swprintf_p_l_defined */
#ifndef ___vswprintf_s_l_defined
#define ___vswprintf_s_l_defined 1
#ifdef __CRT_HAVE__vswprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vswprintf_s_l,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__wchar_count,__format,__locale,__args))
#else /* LIBC: _vswprintf_s_l */
#include <local/wchar/_vswprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vswprintf_s_l, __FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vswprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vswprintf_s_l))(__dst, __wchar_count, __format, __locale, __args); })
#endif /* _vswprintf_s_l... */
#endif /* !___vswprintf_s_l_defined */
#ifndef ___swprintf_s_l_defined
#define ___swprintf_s_l_defined 1
#ifdef __CRT_HAVE__swprintf_s_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swprintf_s_l");
#else /* LIBC: _swprintf_s_l */
#include <local/wchar/_swprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_swprintf_s_l)
#else /* __cplusplus */
#define _swprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swprintf_s_l))
#endif /* !__cplusplus */
#endif /* _swprintf_s_l... */
#endif /* !___swprintf_s_l_defined */
#ifndef ___vsnwprintf_l_defined
#define ___vsnwprintf_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_l
__CDECLARE(__ATTR_NONNULL((1, 3)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_l,(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__bufsize,__format,__locale,__args))
#else /* LIBC: _vsnwprintf_l */
#include <local/wchar/_vsnwprintf_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_l, __FORCELOCAL __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_l))(__dst, __bufsize, __format, __locale, __args); })
#endif /* _vsnwprintf_l... */
#endif /* !___vsnwprintf_l_defined */
#ifndef ___snwprintf_l_defined
#define ___snwprintf_l_defined 1
#ifdef __CRT_HAVE__snwprintf_l
__LIBC __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_l)(wchar_t *__dst, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwprintf_l");
#else /* LIBC: _snwprintf_l */
#include <local/wchar/_snwprintf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_snwprintf_l)
#else /* __cplusplus */
#define _snwprintf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_l))
#endif /* !__cplusplus */
#endif /* _snwprintf_l... */
#endif /* !___snwprintf_l_defined */
#ifndef ___vsnwprintf_s_l_defined
#define ___vsnwprintf_s_l_defined 1
#ifdef __CRT_HAVE__vsnwprintf_s_l
__CDECLARE(__ATTR_NONNULL((1, 4)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,_vsnwprintf_s_l,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args),(__dst,__wchar_count,__bufsize,__format,__locale,__args))
#else /* LIBC: _vsnwprintf_s_l */
#include <local/wchar/_vsnwprintf_s_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_vsnwprintf_s_l, __FORCELOCAL __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__LIBCCALL _vsnwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, __builtin_va_list __args) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnwprintf_s_l))(__dst, __wchar_count, __bufsize, __format, __locale, __args); })
#endif /* _vsnwprintf_s_l... */
#endif /* !___vsnwprintf_s_l_defined */
#ifndef ___snwprintf_s_l_defined
#define ___snwprintf_s_l_defined 1
#ifdef __CRT_HAVE__snwprintf_s_l
__LIBC __ATTR_NONNULL((1, 4)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwprintf_s_l)(wchar_t *__dst, __SIZE_TYPE__ __wchar_count, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwprintf_s_l");
#else /* LIBC: _snwprintf_s_l */
#include <local/wchar/_snwprintf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_snwprintf_s_l)
#else /* __cplusplus */
#define _snwprintf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwprintf_s_l))
#endif /* !__cplusplus */
#endif /* _snwprintf_s_l... */
#endif /* !___snwprintf_s_l_defined */
#ifndef ___fwscanf_l_defined
#define ___fwscanf_l_defined 1
#ifdef __CRT_HAVE__fwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwscanf_l");
#elif defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE__vfwscanf_l)
#include <local/wchar/_fwscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_fwscanf_l)
#else /* __cplusplus */
#define _fwscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _fwscanf_l */
#undef ___fwscanf_l_defined
#endif /* _fwscanf_l... */
#endif /* !___fwscanf_l_defined */
#ifndef ___fwscanf_s_l_defined
#define ___fwscanf_s_l_defined 1
#ifdef __CRT_HAVE__fwscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_fwscanf_s_l");
#elif defined(__CRT_HAVE__fwscanf_l) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _fwscanf_s_l)(__FILE *__stream, wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_fwscanf_l");
#elif defined(__CRT_HAVE_vfwscanf) || defined(__CRT_HAVE__vfwscanf_l)
#include <local/wchar/_fwscanf_l.h>
#define _fwscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_fwscanf_l))
#else /* CUSTOM: _fwscanf_l */
#undef ___fwscanf_s_l_defined
#endif /* _fwscanf_s_l... */
#endif /* !___fwscanf_s_l_defined */
#ifndef ___swscanf_l_defined
#define ___swscanf_l_defined 1
#ifdef __CRT_HAVE__swscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swscanf_l");
#else /* LIBC: _swscanf_l */
#include <local/wchar/_swscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_swscanf_l)
#else /* __cplusplus */
#define _swscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))
#endif /* !__cplusplus */
#endif /* _swscanf_l... */
#endif /* !___swscanf_l_defined */
#ifndef ___swscanf_s_l_defined
#define ___swscanf_s_l_defined 1
#ifdef __CRT_HAVE__swscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_s_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_swscanf_s_l");
#elif defined(__CRT_HAVE__swscanf_l) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _swscanf_s_l)(wchar_t const *__src, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME("_swscanf_l");
#else /* LIBC: _swscanf_l */
#include <local/wchar/_swscanf_l.h>
#define _swscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_swscanf_l))
#endif /* _swscanf_s_l... */
#endif /* !___swscanf_s_l_defined */
#ifndef ___snwscanf_defined
#define ___snwscanf_defined 1
#ifdef __CRT_HAVE__snwscanf
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_snwscanf");
#else /* LIBC: _snwscanf */
#include <local/wchar/_snwscanf.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_snwscanf)
#else /* __cplusplus */
#define _snwscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))
#endif /* !__cplusplus */
#endif /* _snwscanf... */
#endif /* !___snwscanf_defined */
#ifndef ___snwscanf_l_defined
#define ___snwscanf_l_defined 1
#ifdef __CRT_HAVE__snwscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwscanf_l");
#else /* LIBC: _snwscanf_l */
#include <local/wchar/_snwscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_snwscanf_l)
#else /* __cplusplus */
#define _snwscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_l))
#endif /* !__cplusplus */
#endif /* _snwscanf_l... */
#endif /* !___snwscanf_l_defined */
#ifndef ___snwscanf_s_defined
#define ___snwscanf_s_defined 1
#ifdef __CRT_HAVE__snwscanf_s
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME_SAME("_snwscanf_s");
#elif defined(__CRT_HAVE__snwscanf) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, ...) __CASMNAME("_snwscanf");
#else /* LIBC: _snwscanf */
#include <local/wchar/_snwscanf.h>
#define _snwscanf_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf))
#endif /* _snwscanf_s... */
#endif /* !___snwscanf_s_defined */
#ifndef ___snwscanf_s_l_defined
#define ___snwscanf_s_l_defined 1
#ifdef __CRT_HAVE__snwscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL _snwscanf_s_l)(wchar_t const *__src, __SIZE_TYPE__ __bufsize, wchar_t const *__format, __locale_t __locale, ...) __CASMNAME_SAME("_snwscanf_s_l");
#else /* LIBC: _snwscanf_s_l */
#include <local/wchar/_snwscanf_s_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_snwscanf_s_l)
#else /* __cplusplus */
#define _snwscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_snwscanf_s_l))
#endif /* !__cplusplus */
#endif /* _snwscanf_s_l... */
#endif /* !___snwscanf_s_l_defined */
#ifndef ___wscanf_l_defined
#define ___wscanf_l_defined 1
#ifdef __CRT_HAVE__wscanf_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wscanf_l");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf) || defined(__CRT_HAVE__vwscanf_l)
#include <local/wchar/_wscanf_l.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(_wscanf_l)
#else /* __cplusplus */
#define _wscanf_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))
#endif /* !__cplusplus */
#else /* CUSTOM: _wscanf_l */
#undef ___wscanf_l_defined
#endif /* _wscanf_l... */
#endif /* !___wscanf_l_defined */
#ifndef ___wscanf_s_l_defined
#define ___wscanf_s_l_defined 1
#ifdef __CRT_HAVE__wscanf_s_l
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME_SAME("_wscanf_s_l");
#elif defined(__CRT_HAVE__wscanf_l) && (!defined(__NO_ASMNAME))
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T (__VLIBCCALL _wscanf_s_l)(wchar_t const *__format, __locale_t __locale, ...) __THROWS(...) __CASMNAME("_wscanf_l");
#elif (defined(__CRT_HAVE_vfwscanf) && !defined(__NO_STDSTREAMS)) || defined(__CRT_HAVE_vwscanf) || defined(__CRT_HAVE__vwscanf_l)
#include <local/wchar/_wscanf_l.h>
#define _wscanf_s_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wscanf_l))
#else /* CUSTOM: _wscanf_l */
#undef ___wscanf_s_l_defined
#endif /* _wscanf_s_l... */
#endif /* !___wscanf_s_l_defined */
#ifndef ___wfsopen_defined
#define ___wfsopen_defined 1
#ifdef __CRT_HAVE__wfsopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfsopen,(wchar_t const *__filename, wchar_t const *__mode, int __sh_flag),(__filename,__mode,__sh_flag))
#else /* LIBC: _wfsopen */
#undef ___wfsopen_defined
#endif /* _wfsopen... */
#endif /* !___wfsopen_defined */
#ifndef ___wfdopen_defined
#define ___wfdopen_defined 1
#ifdef __CRT_HAVE__wfdopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),__FILE *,__NOTHROW_NCX,_wfdopen,(__fd_t __fd, wchar_t const *__mode),(__fd,__mode))
#else /* LIBC: _wfdopen */
#undef ___wfdopen_defined
#endif /* _wfdopen... */
#endif /* !___wfdopen_defined */
#ifndef ___wfopen_s_defined
#define ___wfopen_s_defined 1
#ifdef __CRT_HAVE__wfopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,_wfopen_s,(__FILE **__pstream, wchar_t const *__filename, wchar_t const *__mode),(__pstream,__filename,__mode))
#else /* LIBC: _wfopen_s */
#undef ___wfopen_s_defined
#endif /* _wfopen_s... */
#endif /* !___wfopen_s_defined */
#ifndef ___wfreopen_s_defined
#define ___wfreopen_s_defined 1
#ifdef __CRT_HAVE__wfreopen_s
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,_wfreopen_s,(__FILE **__pstream, wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__pstream,__filename,__mode,__stream))
#else /* LIBC: _wfreopen_s */
#undef ___wfreopen_s_defined
#endif /* _wfreopen_s... */
#endif /* !___wfreopen_s_defined */
#ifndef ___wfopen_defined
#define ___wfopen_defined 1
#ifdef __CRT_HAVE__wfopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfopen,(wchar_t const *__filename, wchar_t const *__mode),(__filename,__mode))
#elif defined(__CRT_HAVE_wfopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfopen,(wchar_t const *__filename, wchar_t const *__mode),wfopen,(__filename,__mode))
#else /* LIBC: _wfopen */
#undef ___wfopen_defined
#endif /* _wfopen... */
#endif /* !___wfopen_defined */
#ifndef ___wfreopen_defined
#define ___wfreopen_defined 1
#ifdef __CRT_HAVE__wfreopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),(__filename,__mode,__stream))
#elif defined(__CRT_HAVE_wfreopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wfreopen,(wchar_t const *__filename, wchar_t const *__mode, __FILE *__stream),wfreopen,(__filename,__mode,__stream))
#else /* LIBC: _wfreopen */
#undef ___wfreopen_defined
#endif /* _wfreopen... */
#endif /* !___wfreopen_defined */
#ifndef ___fgetwchar_defined
#define ___fgetwchar_defined 1
#ifdef __CRT_HAVE_getwchar
__CREDIRECT(,wint_t,__NOTHROW_NCX,_fgetwchar,(void),getwchar,())
#elif defined(__CRT_HAVE__fgetwchar)
__CDECLARE(,wint_t,__NOTHROW_NCX,_fgetwchar,(void),())
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc))
#include <local/wchar/getwchar.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL _fgetwchar)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getwchar))(); }
#else /* CUSTOM: getwchar */
#undef ___fgetwchar_defined
#endif /* _fgetwchar... */
#endif /* !___fgetwchar_defined */
#ifndef ___fputwchar_defined
#define ___fputwchar_defined 1
#ifdef __CRT_HAVE_putwchar
__CREDIRECT(,wint_t,__NOTHROW_NCX,_fputwchar,(wchar_t __wc),putwchar,(__wc))
#elif defined(__CRT_HAVE__fputwchar)
__CDECLARE(,wint_t,__NOTHROW_NCX,_fputwchar,(wchar_t __wc),(__wc))
#elif !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc))
#include <local/wchar/putwchar.h>
__FORCELOCAL wint_t __NOTHROW_NCX(__LIBCCALL _fputwchar)(wchar_t __wc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(putwchar))(__wc); }
#else /* CUSTOM: putwchar */
#undef ___fputwchar_defined
#endif /* _fputwchar... */
#endif /* !___fputwchar_defined */
#ifndef ___getws_s_defined
#define ___getws_s_defined 1
#ifdef __CRT_HAVE__getws_s
__CDECLARE(,wchar_t *,__NOTHROW_NCX,_getws_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen),(__buf,__buflen))
#elif (((defined(__CRT_HAVE_fgetwc) || defined(__CRT_HAVE_getwc)) && (defined(__CRT_HAVE_ungetwc) || defined(__CRT_HAVE_ungetwc_unlocked)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE_ferror_unlocked))) || defined(__CRT_HAVE_fgetws) || defined(__CRT_HAVE_fgetws_unlocked) || defined(__CRT_HAVE__fgetws_nolock)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/_getws_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_getws_s, __FORCELOCAL wchar_t *__NOTHROW_NCX(__LIBCCALL _getws_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_getws_s))(__buf, __buflen); })
#else /* CUSTOM: _getws_s */
#undef ___getws_s_defined
#endif /* _getws_s... */
#endif /* !___getws_s_defined */
#ifndef ___putws_defined
#define ___putws_defined 1
#ifdef __CRT_HAVE__putws
__CDECLARE(__ATTR_NONNULL((1)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,_putws,(wchar_t const *__string),(__string))
#elif (defined(__CRT_HAVE_fputwc) || defined(__CRT_HAVE_putwc) || defined(__CRT_HAVE_file_wprinter) || defined(__CRT_HAVE_file_wprinter_unlocked) || defined(__CRT_HAVE_fputws) || defined(__CRT_HAVE_fputws_unlocked) || defined(__CRT_HAVE__fputws_nolock)) && !defined(__NO_STDSTREAMS)
#include <local/wchar/_putws.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_putws, __FORCELOCAL __ATTR_NONNULL((1)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__LIBCCALL _putws)(wchar_t const *__string) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_putws))(__string); })
#else /* CUSTOM: _putws */
#undef ___putws_defined
#endif /* _putws... */
#endif /* !___putws_defined */
#ifndef ___wtempnam_defined
#define ___wtempnam_defined 1
#ifdef __CRT_HAVE__wtempnam
__CDECLARE(__ATTR_WUNUSED,wchar_t *,__NOTHROW_NCX,_wtempnam,(wchar_t const *__directory, wchar_t const *__file_prefix),(__directory,__file_prefix))
#else /* LIBC: _wtempnam */
#undef ___wtempnam_defined
#endif /* _wtempnam... */
#endif /* !___wtempnam_defined */
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
#ifndef ___wperror_defined
#define ___wperror_defined 1
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(,__NOTHROW_NCX,_wperror,(wchar_t const *__errmsg),(__errmsg))
#else /* LIBC: _wperror */
#undef ___wperror_defined
#endif /* _wperror... */
#endif /* !___wperror_defined */
#endif  /* _CRT_WPERROR_DEFINED */
#ifndef ___wpopen_defined
#define ___wpopen_defined 1
#ifdef __CRT_HAVE__wpopen
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wpopen,(wchar_t const *__command, wchar_t const *__mode),(__command,__mode))
#elif defined(__CRT_HAVE_wpopen)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_NCX,_wpopen,(wchar_t const *__command, wchar_t const *__mode),wpopen,(__command,__mode))
#else /* LIBC: _wpopen */
#undef ___wpopen_defined
#endif /* _wpopen... */
#endif /* !___wpopen_defined */
#ifndef ___wremove_defined
#define ___wremove_defined 1
#ifdef __CRT_HAVE__wremove
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wremove,(wchar_t const *__filename),(__filename))
#elif defined(__CRT_HAVE_wremove)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,_wremove,(wchar_t const *__filename),wremove,(__filename))
#else /* LIBC: _wremove */
#undef ___wremove_defined
#endif /* _wremove... */
#endif /* !___wremove_defined */
#ifndef ___wtmpnam_s_defined
#define ___wtmpnam_s_defined 1
#ifdef __CRT_HAVE__wtmpnam_s
__CDECLARE(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,_wtmpnam_s,(wchar_t *__dst, __SIZE_TYPE__ __wchar_count),(__dst,__wchar_count))
#else /* LIBC: _wtmpnam_s */
#undef ___wtmpnam_s_defined
#endif /* _wtmpnam_s... */
#endif /* !___wtmpnam_s_defined */
#ifndef ___fgetwc_nolock_defined
#define ___fgetwc_nolock_defined 1
#ifdef __CRT_HAVE__fgetwc_nolock
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,_fgetwc_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,_fgetwc_nolock,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#else /* LIBC: _fgetwc_nolock */
#undef ___fgetwc_nolock_defined
#endif /* _fgetwc_nolock... */
#endif /* !___fgetwc_nolock_defined */
#ifndef ___fputwc_nolock_defined
#define ___fputwc_nolock_defined 1
#ifdef __CRT_HAVE__fputwc_nolock
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_fputwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_fputwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#else /* LIBC: _fputwc_nolock */
#undef ___fputwc_nolock_defined
#endif /* _fputwc_nolock... */
#endif /* !___fputwc_nolock_defined */
#ifndef ___ungetwc_nolock_defined
#define ___ungetwc_nolock_defined 1
#ifdef __CRT_HAVE_ungetwc
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetwc_nolock)
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),(__ch,__stream))
#elif defined(__CRT_HAVE_ungetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_ungetwc_nolock,(__WINT_TYPE__ __ch, __FILE *__restrict __stream),ungetwc_unlocked,(__ch,__stream))
#else /* LIBC: _ungetwc_nolock */
#undef ___ungetwc_nolock_defined
#endif /* _ungetwc_nolock... */
#endif /* !___ungetwc_nolock_defined */
#ifndef ___getwc_nolock_defined
#define ___getwc_nolock_defined 1
#ifdef __CRT_HAVE__getwc_nolock
__CDECLARE(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,_getwc_nolock,(__FILE *__restrict __stream),(__stream))
#elif defined(__CRT_HAVE__fgetwc_nolock)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,_getwc_nolock,(__FILE *__restrict __stream),_fgetwc_nolock,(__stream))
#elif defined(__CRT_HAVE_fgetwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__WINT_TYPE__,__NOTHROW_NCX,_getwc_nolock,(__FILE *__restrict __stream),fgetwc_unlocked,(__stream))
#else /* LIBC: _getwc_nolock */
#undef ___getwc_nolock_defined
#endif /* _getwc_nolock... */
#endif /* !___getwc_nolock_defined */
#ifndef ___putwc_nolock_defined
#define ___putwc_nolock_defined 1
#ifdef __CRT_HAVE__putwc_nolock
__CDECLARE(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),(__wc,__stream))
#elif defined(__CRT_HAVE__fputwc_nolock)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),_fputwc_nolock,(__wc,__stream))
#elif defined(__CRT_HAVE_fputwc_unlocked)
__CREDIRECT(__ATTR_NONNULL((2)),__WINT_TYPE__,__NOTHROW_NCX,_putwc_nolock,(wchar_t __wc, __FILE *__restrict __stream),fputwc_unlocked,(__wc,__stream))
#else /* LIBC: _putwc_nolock */
#undef ___putwc_nolock_defined
#endif /* _putwc_nolock... */
#endif /* !___putwc_nolock_defined */
#endif /* !_WSTDIO_DEFINED */
#endif /* __USE_DOS */

#endif /* __CC__ */

__SYSDECL_END

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

#endif /* __USE_KOS */

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CWCHAR 1
#undef _WCHAR_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CWCHAR */
#endif /* !_WCHAR_H */
