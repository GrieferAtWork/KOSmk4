/* HASH CRC-32:0x8612d779 */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wstdlib.h) */
#ifndef _CORECRT_WSTDLIB_H
#define _CORECRT_WSTDLIB_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

#define _MAX_I64TOSTR_BASE16_COUNT (16 + 1)
#define _MAX_I64TOSTR_BASE10_COUNT (1 + 19 + 1)
#define _MAX_I64TOSTR_BASE8_COUNT  (22 + 1)
#define _MAX_I64TOSTR_BASE2_COUNT  (64 + 1)
#define _MAX_U64TOSTR_BASE16_COUNT (16 + 1)
#define _MAX_U64TOSTR_BASE10_COUNT (20 + 1)
#define _MAX_U64TOSTR_BASE8_COUNT  (22 + 1)
#define _MAX_U64TOSTR_BASE2_COUNT  (64 + 1)

#if __SIZEOF_INT__ == 4
#define _MAX_ITOSTR_BASE16_COUNT (8 + 1)
#define _MAX_ITOSTR_BASE10_COUNT (1 + 10 + 1)
#define _MAX_ITOSTR_BASE8_COUNT  (11 + 1)
#define _MAX_ITOSTR_BASE2_COUNT  (32 + 1)
#endif /* __SIZEOF_INT__ == 4 */

#if __SIZEOF_LONG__ == 4
#define _MAX_LTOSTR_BASE16_COUNT  (8 + 1)
#define _MAX_LTOSTR_BASE10_COUNT  (1 + 10 + 1)
#define _MAX_LTOSTR_BASE8_COUNT   (11 + 1)
#define _MAX_LTOSTR_BASE2_COUNT   (32 + 1)
#define _MAX_ULTOSTR_BASE16_COUNT (8 + 1)
#define _MAX_ULTOSTR_BASE10_COUNT (10 + 1)
#define _MAX_ULTOSTR_BASE8_COUNT  (11 + 1)
#define _MAX_ULTOSTR_BASE2_COUNT  (32 + 1)
#elif __SIZEOF_LONG__ == 8
#define _MAX_LTOSTR_BASE16_COUNT  (16 + 1)
#define _MAX_LTOSTR_BASE10_COUNT  (1 + 19 + 1)
#define _MAX_LTOSTR_BASE8_COUNT   (22 + 1)
#define _MAX_LTOSTR_BASE2_COUNT   (64 + 1)
#define _MAX_ULTOSTR_BASE16_COUNT (16 + 1)
#define _MAX_ULTOSTR_BASE10_COUNT (20 + 1)
#define _MAX_ULTOSTR_BASE8_COUNT  (22 + 1)
#define _MAX_ULTOSTR_BASE2_COUNT  (64 + 1)
#endif /* ... */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

#ifndef _WSTDLIB_DEFINED
#define _WSTDLIB_DEFINED
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_IN(1),wchar_t *,__NOTHROW_NCX,_wgetenv,(wchar_t const *__varname),(__varname))
#ifdef __CRT_HAVE__wgetenv_s
__CDECLARE(__ATTR_IN(4) __ATTR_OUT(1) __ATTR_OUTS(2, 3),errno_t,__NOTHROW_NCX,_wgetenv_s,(__SIZE_TYPE__ *__preqsize, wchar_t *__buf, rsize_t __bufsize, wchar_t const *__varname),(__preqsize,__buf,__bufsize,__varname))
#elif defined(__CRT_HAVE__wgetenv)
#include <libc/local/stdlib/_wgetenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wgetenv_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(4) __ATTR_OUT(1) __ATTR_OUTS(2, 3) errno_t __NOTHROW_NCX(__LIBCCALL _wgetenv_s)(__SIZE_TYPE__ *__preqsize, wchar_t *__buf, rsize_t __bufsize, wchar_t const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wgetenv_s))(__preqsize, __buf, __bufsize, __varname); })
#endif /* ... */
#ifdef __CRT_HAVE__wdupenv_s
__CDECLARE(__ATTR_IN(3) __ATTR_OUT(1) __ATTR_OUT(2),errno_t,__NOTHROW_NCX,_wdupenv_s,(wchar_t **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, wchar_t const *__varname),(__pbuf,__pbuflen,__varname))
#elif defined(__CRT_HAVE__wgetenv) && (defined(__CRT_HAVE_wcsdup) || defined(__CRT_HAVE__wcsdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
#include <libc/local/stdlib/_wdupenv_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wdupenv_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(3) __ATTR_OUT(1) __ATTR_OUT(2) errno_t __NOTHROW_NCX(__LIBCCALL _wdupenv_s)(wchar_t **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, wchar_t const *__varname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wdupenv_s))(__pbuf, __pbuflen, __varname); })
#endif /* ... */
#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED
#ifdef __CRT_HAVE_wsystem
__CREDIRECT(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),wsystem,(__cmd))
#elif defined(__CRT_HAVE__wsystem)
__CDECLARE(,int,__NOTHROW_RPC,_wsystem,(wchar_t const *__cmd),(__cmd))
#else /* ... */
#include <libc/template/environ.h>
#if (defined(__CRT_HAVE_system) || defined(__CRT_HAVE___libc_system) || ((defined(__CRT_HAVE_shexec) || defined(__CRT_HAVE_execl) || defined(__CRT_HAVE__execl) || defined(__CRT_HAVE_execv) || defined(__CRT_HAVE__execv) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve) || defined(__CRT_HAVE___execve) || defined(__CRT_HAVE___libc_execve)) && defined(__LOCAL_environ))) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_waitpid) || defined(__CRT_HAVE___waitpid)) && (defined(__CRT_HAVE_vfork) || defined(__CRT_HAVE___vfork) || defined(__CRT_HAVE___libc_vfork) || defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)))) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/parts.wchar.stdlib/wsystem.h>
__FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_RPC(__LIBCCALL _wsystem)(wchar_t const *__cmd) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wsystem))(__cmd); }
#else /* (__CRT_HAVE_system || __CRT_HAVE___libc_system || ((__CRT_HAVE_shexec || __CRT_HAVE_execl || __CRT_HAVE__execl || __CRT_HAVE_execv || __CRT_HAVE__execv || ((__CRT_HAVE_execve || __CRT_HAVE__execve || __CRT_HAVE___execve || __CRT_HAVE___libc_execve) && __LOCAL_environ)) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_waitpid || __CRT_HAVE___waitpid) && (__CRT_HAVE_vfork || __CRT_HAVE___vfork || __CRT_HAVE___libc_vfork || __CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork))) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef _CRT_WSYSTEM_DEFINED
#endif /* (!__CRT_HAVE_system && !__CRT_HAVE___libc_system && ((!__CRT_HAVE_shexec && !__CRT_HAVE_execl && !__CRT_HAVE__execl && !__CRT_HAVE_execv && !__CRT_HAVE__execv && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve && !__CRT_HAVE___execve && !__CRT_HAVE___libc_execve) || !__LOCAL_environ)) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_waitpid && !__CRT_HAVE___waitpid) || (!__CRT_HAVE_vfork && !__CRT_HAVE___vfork && !__CRT_HAVE___libc_vfork && !__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork))) || (!__CRT_HAVE_convert_wcstombs && !__CRT_HAVE_convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !... */
#endif /* !_CRT_WSYSTEM_DEFINED */
#ifndef __wcstol_defined
#define __wcstol_defined
#ifdef __std_wcstol_defined
/* >> wcstol(3) */
__NAMESPACE_STD_USING(wcstol)
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
#include <libc/local/wchar/wcstol.h>
/* >> wcstol(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstol, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBCCALL wcstol)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstol_defined */
#ifndef __wcstoll_defined
#define __wcstoll_defined
#ifdef __std_wcstoll_defined
/* >> wcstoll(3) */
__NAMESPACE_STD_USING(wcstoll)
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
#include <libc/local/wchar/wcstoll.h>
/* >> wcstoll(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoll, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBCCALL wcstoll)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstoll_defined */
#ifndef __wcstoul_defined
#define __wcstoul_defined
#ifdef __std_wcstoul_defined
/* >> wcstoul(3) */
__NAMESPACE_STD_USING(wcstoul)
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
#include <libc/local/wchar/wcstoul.h>
/* >> wcstoul(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoul, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBCCALL wcstoul)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstoul_defined */
#ifndef __wcstoull_defined
#define __wcstoull_defined
#ifdef __std_wcstoull_defined
/* >> wcstoull(3) */
__NAMESPACE_STD_USING(wcstoull)
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
#include <libc/local/wchar/wcstoull.h>
/* >> wcstoull(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstoull, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBCCALL wcstoull)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull))(__nptr, __endptr, __base); })
#endif /* !... */
#endif /* !__wcstoull_defined */
#ifdef __CRT_HAVE_wcstol_l
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l)
/* >> wcstol_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l)
/* >> wcstol_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),long,__NOTHROW_NCX,_wcstol_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstol_l.h>
/* >> wcstol_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) long __NOTHROW_NCX(__LIBCCALL _wcstol_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstol_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstoul_l
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l)
/* >> wcstoul_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l)
/* >> wcstoul_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),unsigned long,__NOTHROW_NCX,_wcstoul_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoul_l.h>
/* >> wcstoul_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) unsigned long __NOTHROW_NCX(__LIBCCALL _wcstoul_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoul_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifndef __NO_FPU
#ifndef __wcstof_defined
#define __wcstof_defined
#ifdef __std_wcstof_defined
/* >> wcstof(3) */
__NAMESPACE_STD_USING(wcstof)
#elif defined(__CRT_HAVE_wcstof)
/* >> wcstof(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,wcstof,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
#include <libc/local/wchar/wcstof.h>
/* >> wcstof(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBCCALL wcstof)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__wcstof_defined */
#ifndef __wcstod_defined
#define __wcstod_defined
#ifdef __std_wcstod_defined
/* >> wcstod(3) */
__NAMESPACE_STD_USING(wcstod)
#elif defined(__CRT_HAVE_wcstod)
/* >> wcstod(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,wcstod,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
#include <libc/local/wchar/wcstod.h>
/* >> wcstod(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBCCALL wcstod)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__wcstod_defined */
#ifdef __CRT_HAVE_wcstof_l
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstof_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstof_l)
/* >> wcstof_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstof_l)
/* >> wcstof_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),float,__NOTHROW_NCX,_wcstof_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstof_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstof_l.h>
/* >> wcstof_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) float __NOTHROW_NCX(__LIBCCALL _wcstof_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstof_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstod_l
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstod_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstod_l)
/* >> wcstod_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstod_l)
/* >> wcstod_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),double,__NOTHROW_NCX,_wcstod_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstod_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstod_l.h>
/* >> wcstod_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) double __NOTHROW_NCX(__LIBCCALL _wcstod_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstod_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifndef __wcstold_defined
#define __wcstold_defined
#ifdef __std_wcstold_defined
/* >> wcstold(3) */
__NAMESPACE_STD_USING(wcstold)
#elif defined(__CRT_HAVE_wcstold)
/* >> wcstold(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,wcstold,(wchar_t const *__restrict __nptr, wchar_t **__endptr),(__nptr,__endptr))
#else /* ... */
#include <libc/local/wchar/wcstold.h>
/* >> wcstold(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcstold, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL wcstold)(wchar_t const *__restrict __nptr, wchar_t **__endptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold))(__nptr, __endptr); })
#endif /* !... */
#endif /* !__wcstold_defined */
#ifdef __CRT_HAVE_wcstold_l
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),wcstold_l,(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE__wcstold_l)
/* >> wcstold_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),(__nptr,__endptr,__locale))
#elif defined(__CRT_HAVE___wcstold_l)
/* >> wcstold_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGDOUBLE,__NOTHROW_NCX,_wcstold_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale),__wcstold_l,(__nptr,__endptr,__locale))
#else /* ... */
#include <libc/local/wchar/wcstold_l.h>
/* >> wcstold_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGDOUBLE __NOTHROW_NCX(__LIBCCALL _wcstold_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstold_l))(__nptr, __endptr, __locale); }
#endif /* !... */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#ifdef __CRT_HAVE__wtof
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),double,__NOTHROW_NCX,_wtof,(wchar_t const *__nptr),(__nptr))
#else /* __CRT_HAVE__wtof */
#include <libc/local/corecrt_wstdlib/_wtof.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) double __NOTHROW_NCX(__LIBCCALL _wtof)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtof))(__nptr); })
#endif /* !__CRT_HAVE__wtof */
#ifdef __CRT_HAVE__wtof_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),double,__NOTHROW_NCX,_wtof_l,(wchar_t const *__nptr, __locale_t __locale),(__nptr,__locale))
#else /* __CRT_HAVE__wtof_l */
#include <libc/local/corecrt_wstdlib/_wtof_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtof_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) double __NOTHROW_NCX(__LIBCCALL _wtof_l)(wchar_t const *__nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtof_l))(__nptr, __locale); })
#endif /* !__CRT_HAVE__wtof_l */
#endif /* !__NO_FPU */
#ifdef __CRT_HAVE__itow
__CDECLARE(__ATTR_OUT(2),wchar_t *,__NOTHROW_NCX,_itow,(int __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__itow */
#include <libc/local/corecrt_wstdlib/_itow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) wchar_t *__NOTHROW_NCX(__LIBCCALL _itow)(int __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__itow */
#ifdef __CRT_HAVE__ltow
__CDECLARE(__ATTR_OUT(2),wchar_t *,__NOTHROW_NCX,_ltow,(long __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ltow */
#include <libc/local/corecrt_wstdlib/_ltow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) wchar_t *__NOTHROW_NCX(__LIBCCALL _ltow)(long __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ltow */
#ifdef __CRT_HAVE__ultow
__CDECLARE(__ATTR_OUT(2),wchar_t *,__NOTHROW_NCX,_ultow,(unsigned long __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ultow */
#include <libc/local/corecrt_wstdlib/_ultow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) wchar_t *__NOTHROW_NCX(__LIBCCALL _ultow)(unsigned long __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ultow */
#ifdef __CRT_HAVE__i64tow
__CDECLARE(__ATTR_OUT(2),wchar_t *,__NOTHROW_NCX,_i64tow,(__INT64_TYPE__ __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__i64tow */
#include <libc/local/corecrt_wstdlib/_i64tow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64tow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) wchar_t *__NOTHROW_NCX(__LIBCCALL _i64tow)(__INT64_TYPE__ __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64tow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__i64tow */
#ifdef __CRT_HAVE__ui64tow
__CDECLARE(__ATTR_OUT(2),wchar_t *,__NOTHROW_NCX,_ui64tow,(__UINT64_TYPE__ __val, wchar_t *__buf, int __radix),(__val,__buf,__radix))
#else /* __CRT_HAVE__ui64tow */
#include <libc/local/corecrt_wstdlib/_ui64tow.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64tow, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) wchar_t *__NOTHROW_NCX(__LIBCCALL _ui64tow)(__UINT64_TYPE__ __val, wchar_t *__buf, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64tow))(__val, __buf, __radix); })
#endif /* !__CRT_HAVE__ui64tow */
#ifdef __CRT_HAVE__itow_s
__CDECLARE(__ATTR_OUTS(2, 3),errno_t,__NOTHROW_NCX,_itow_s,(int __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__itow_s */
#include <libc/local/corecrt_wstdlib/_itow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_itow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) errno_t __NOTHROW_NCX(__LIBCCALL _itow_s)(int __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_itow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__itow_s */
#ifdef __CRT_HAVE__ltow_s
__CDECLARE(__ATTR_OUTS(2, 3),errno_t,__NOTHROW_NCX,_ltow_s,(long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ltow_s */
#include <libc/local/corecrt_wstdlib/_ltow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ltow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) errno_t __NOTHROW_NCX(__LIBCCALL _ltow_s)(long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ltow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ltow_s */
#ifdef __CRT_HAVE__ultow_s
__CDECLARE(__ATTR_OUTS(2, 3),errno_t,__NOTHROW_NCX,_ultow_s,(unsigned long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ultow_s */
#include <libc/local/corecrt_wstdlib/_ultow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ultow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) errno_t __NOTHROW_NCX(__LIBCCALL _ultow_s)(unsigned long __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ultow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ultow_s */
#ifdef __CRT_HAVE__i64tow_s
__CDECLARE(__ATTR_OUTS(2, 3),errno_t,__NOTHROW_NCX,_i64tow_s,(__INT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__i64tow_s */
#include <libc/local/corecrt_wstdlib/_i64tow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_i64tow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) errno_t __NOTHROW_NCX(__LIBCCALL _i64tow_s)(__INT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_i64tow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__i64tow_s */
#ifdef __CRT_HAVE__ui64tow_s
__CDECLARE(__ATTR_OUTS(2, 3),errno_t,__NOTHROW_NCX,_ui64tow_s,(__UINT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix),(__val,__buf,__buflen,__radix))
#else /* __CRT_HAVE__ui64tow_s */
#include <libc/local/corecrt_wstdlib/_ui64tow_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_ui64tow_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) errno_t __NOTHROW_NCX(__LIBCCALL _ui64tow_s)(__UINT64_TYPE__ __val, wchar_t *__buf, __SIZE_TYPE__ __buflen, int __radix) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_ui64tow_s))(__val, __buf, __buflen, __radix); })
#endif /* !__CRT_HAVE__ui64tow_s */
#ifdef __CRT_HAVE_wtoi
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoi.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL _wtoi)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoi))(__nptr); }
#endif /* !... */
#ifdef __CRT_HAVE_wtol
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long,__NOTHROW_NCX,_wtol,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtol.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long __NOTHROW_NCX(__LIBCCALL _wtol)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtol))(__nptr); }
#endif /* !... */
#ifdef __CRT_HAVE__wtoi64
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoll) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64,(wchar_t const *__restrict __nptr),_wtoll,(__nptr))
#else /* ... */
#include <libc/local/corecrt_wstdlib/_wtoi64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wtoi64)(wchar_t const *__restrict __nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi64))(__nptr); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol) && __SIZEOF_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstol,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoll) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoll,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcsto64)
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcsto64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoi64)
/* >> wcsto64(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoimax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoimax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcsto64.h>
/* >> wcsto64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoi64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64))(__nptr, __endptr, __base); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul) && __SIZEOF_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoul,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoull) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoull,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstouq) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstouq,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstou64)
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstou64,(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE__wcstoui64)
/* >> wcstou64(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),(__nptr,__endptr,__base))
#elif defined(__CRT_HAVE_wcstoumax) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base),wcstoumax,(__nptr,__endptr,__base))
#else /* ... */
#include <libc/local/wchar/wcstou64.h>
/* >> wcstou64(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoui64)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64))(__nptr, __endptr, __base); }
#endif /* !... */
#ifdef __CRT_HAVE__wtoi_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_INT__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,_wtoi_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/corecrt_wstdlib/_wtoi_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL _wtoi_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi_l))(__nptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE__wtol_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_LONG__ == __SIZEOF_LONG_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),long int,__NOTHROW_NCX,_wtol_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/corecrt_wstdlib/_wtol_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtol_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) long int __NOTHROW_NCX(__LIBCCALL _wtol_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtol_l))(__nptr, __locale); })
#endif /* !... */
#ifdef __CRT_HAVE__wtoi64_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_INT__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoll_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__INT64_TYPE__,__NOTHROW_NCX,_wtoi64_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoll_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/corecrt_wstdlib/_wtoi64_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoi64_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wtoi64_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoi64_l))(__nptr, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l)
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l)
/* >> wcsto64_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcsto64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__INT64_TYPE__,__NOTHROW_NCX,_wcstoi64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcsto64_l.h>
/* >> wcsto64_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __INT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoi64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsto64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#if defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l)
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l)
/* >> wcstou64_l(3) */
__CDECLARE(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_INTMAX_T__ == 8
/* >> wcstou64_l(3) */
__CREDIRECT(__ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2),__UINT64_TYPE__,__NOTHROW_NCX,_wcstoui64_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstou64_l.h>
/* >> wcstou64_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __UINT64_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcstoui64_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstou64_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __LONGLONG
#ifdef __CRT_HAVE_wcstoll_l
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoll_l)
/* >> wcstoll_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoll_l)
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoll_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstol_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcsto64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcsto64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoi64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoi64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoimax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoimax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoll_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__LONGLONG,__NOTHROW_NCX,_wcstoll_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoimax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoll_l.h>
/* >> wcstoll_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wcstoll_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoll_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wcstoull_l
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoull_l)
/* >> wcstoull_l(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoull_l)
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoull_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoul_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoul_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstou64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstou64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoui64_l) && __SIZEOF_LONG_LONG__ == 8
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoui64_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE_wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE__wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),_wcstoumax_l,(__nptr,__endptr,__base,__locale))
#elif defined(__CRT_HAVE___wcstoumax_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__
/* >> wcstoull_l(3) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT_OPT(2),__ULONGLONG,__NOTHROW_NCX,_wcstoull_l,(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale),__wcstoumax_l,(__nptr,__endptr,__base,__locale))
#else /* ... */
#include <libc/local/wchar/wcstoull_l.h>
/* >> wcstoull_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ULONGLONG __NOTHROW_NCX(__LIBCCALL _wcstoull_l)(wchar_t const *__restrict __nptr, wchar_t **__endptr, __STDC_INT_AS_UINT_T __base, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstoull_l))(__nptr, __endptr, __base, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE_wtoll
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtoll,(__nptr))
#elif defined(__CRT_HAVE__wtoll)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),(__nptr))
#elif defined(__CRT_HAVE_wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtoi,(__nptr))
#elif defined(__CRT_HAVE__wtoi) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtoi,(__nptr))
#elif defined(__CRT_HAVE_wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),wtol,(__nptr))
#elif defined(__CRT_HAVE__wtol) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtol,(__nptr))
#elif defined(__CRT_HAVE__wtoi64) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll,(wchar_t const *__nptr),_wtoi64,(__nptr))
#else /* ... */
#include <libc/local/parts.wchar.stdlib/wtoll.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wtoll)(wchar_t const *__nptr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wtoll))(__nptr); }
#endif /* !... */
#ifdef __CRT_HAVE__wtoll_l
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_INT__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtol_l) && __SIZEOF_LONG_LONG__ == __SIZEOF_LONG__
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtol_l,(__nptr,__locale))
#elif defined(__CRT_HAVE__wtoi64_l) && __SIZEOF_LONG_LONG__ == 8
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__LONGLONG,__NOTHROW_NCX,_wtoll_l,(wchar_t const *__restrict __nptr, __locale_t __locale),_wtoi64_l,(__nptr,__locale))
#else /* ... */
#include <libc/local/corecrt_wstdlib/_wtoll_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wtoll_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __LONGLONG __NOTHROW_NCX(__LIBCCALL _wtoll_l)(wchar_t const *__restrict __nptr, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wtoll_l))(__nptr, __locale); })
#endif /* !... */
#endif /* __LONGLONG */
#endif /* !_WSTDLIB_DEFINED */
#ifndef _WSTDLIBP_DEFINED
#define _WSTDLIBP_DEFINED 1
#ifdef __CRT_HAVE__wfullpath
__CDECLARE(__ATTR_IN(2) __ATTR_OUTS(1, 3),wchar_t *,__NOTHROW_NCX,_wfullpath,(wchar_t *__buf, wchar_t const *__path, __SIZE_TYPE__ __buflen),(__buf,__path,__buflen))
#else /* __CRT_HAVE__wfullpath */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE__fullpath) || defined(__CRT_HAVE_frealpathat)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_convert_mbstowcs) || defined(__CRT_HAVE_convert_mbstowcsn) || ((defined(__CRT_HAVE_format_waprintf_printer) || defined(__CRT_HAVE_format_waprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_format_waprintf_pack) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/corecrt_wstdlib/_wfullpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wfullpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUTS(1, 3) wchar_t *__NOTHROW_NCX(__LIBCCALL _wfullpath)(wchar_t *__buf, wchar_t const *__path, __SIZE_TYPE__ __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wfullpath))(__buf, __path, __buflen); })
#endif /* __AT_FDCWD && (__CRT_HAVE__fullpath || __CRT_HAVE_frealpathat) && (__CRT_HAVE_convert_wcstombs || __CRT_HAVE_convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_convert_mbstowcs || __CRT_HAVE_convert_mbstowcsn || ((__CRT_HAVE_format_waprintf_printer || __CRT_HAVE_format_waprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_format_waprintf_pack || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#endif /* !__CRT_HAVE__wfullpath */
#ifdef __CRT_HAVE__wmakepath_s
__CDECLARE(__ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6) __ATTR_OUTS(1, 2),errno_t,__NOTHROW_NCX,_wmakepath_s,(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext),(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wmakepath_s */
#include <libc/local/corecrt_wstdlib/_wmakepath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmakepath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6) __ATTR_OUTS(1, 2) errno_t __NOTHROW_NCX(__LIBCCALL _wmakepath_s)(wchar_t *__buf, __SIZE_TYPE__ __buflen, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmakepath_s))(__buf, __buflen, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wmakepath_s */
#ifdef __CRT_HAVE__wmakepath
__CDECLARE_VOID(__ATTR_IN_OPT(2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_OUT(1),__NOTHROW_NCX,_wmakepath,(wchar_t *__restrict __buf, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext),(__buf,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wmakepath */
#include <libc/local/corecrt_wstdlib/_wmakepath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wmakepath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN_OPT(2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_OUT(1) void __NOTHROW_NCX(__LIBCCALL _wmakepath)(wchar_t *__restrict __buf, wchar_t const *__drive, wchar_t const *__dir, wchar_t const *__file, wchar_t const *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wmakepath))(__buf, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wmakepath */
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
#ifdef __CRT_HAVE__wperror
__CDECLARE_VOID(__ATTR_COLD __ATTR_IN_OPT(1),__THROWING,_wperror,(wchar_t const *__restrict __message),(__message))
#else /* __CRT_HAVE__wperror */
#include <libc/template/stdstreams.h>
#include <libc/errno.h>
#if defined(__LOCAL_stderr) && defined(__libc_geterrno) && (defined(__CRT_HAVE_fprintf) || defined(__CRT_HAVE__IO_fprintf) || defined(__CRT_HAVE_fprintf_s) || defined(__CRT_HAVE_fprintf_unlocked) || defined(__CRT_HAVE_vfprintf) || defined(__CRT_HAVE__IO_vfprintf) || defined(__CRT_HAVE_vfprintf_s) || defined(__CRT_HAVE_vfprintf_unlocked) || defined(__CRT_HAVE_file_printer) || defined(__CRT_HAVE_file_printer_unlocked) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock))
#include <libc/local/corecrt_wstdio/_wperror.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wperror, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_COLD __ATTR_IN_OPT(1) void (__LIBCCALL _wperror)(wchar_t const *__restrict __message) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wperror))(__message); })
#else /* __LOCAL_stderr && __libc_geterrno && (__CRT_HAVE_fprintf || __CRT_HAVE__IO_fprintf || __CRT_HAVE_fprintf_s || __CRT_HAVE_fprintf_unlocked || __CRT_HAVE_vfprintf || __CRT_HAVE__IO_vfprintf || __CRT_HAVE_vfprintf_s || __CRT_HAVE_vfprintf_unlocked || __CRT_HAVE_file_printer || __CRT_HAVE_file_printer_unlocked || __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock) */
#undef _CRT_WPERROR_DEFINED
#endif /* !__LOCAL_stderr || !__libc_geterrno || (!__CRT_HAVE_fprintf && !__CRT_HAVE__IO_fprintf && !__CRT_HAVE_fprintf_s && !__CRT_HAVE_fprintf_unlocked && !__CRT_HAVE_vfprintf && !__CRT_HAVE__IO_vfprintf && !__CRT_HAVE_vfprintf_s && !__CRT_HAVE_vfprintf_unlocked && !__CRT_HAVE_file_printer && !__CRT_HAVE_file_printer_unlocked && !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock) */
#endif /* !__CRT_HAVE__wperror */
#endif /* !_CRT_WPERROR_DEFINED */
__CDECLARE_OPT(__ATTR_INOUT(1),int,__NOTHROW_NCX,_wputenv,(wchar_t *__string),(__string))
__CDECLARE_OPT(,errno_t,__NOTHROW_NCX,_wputenv_s,(wchar_t const *__varname, wchar_t const *__val),(__varname,__val))
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUTS(3, 4),errno_t,__NOTHROW_RPC,_wsearchenv_s,(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath, __SIZE_TYPE__ __resultpath_len),(__file,__envvar,__resultpath,__resultpath_len))
#ifdef __CRT_HAVE__wsearchenv
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3),__NOTHROW_RPC,_wsearchenv,(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath),(__file,__envvar,__resultpath))
#elif defined(__CRT_HAVE__wsearchenv_s)
#include <libc/local/corecrt_wstdlib/_wsearchenv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsearchenv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_OUT(3) void __NOTHROW_RPC(__LIBCCALL _wsearchenv)(wchar_t const *__file, wchar_t const *__envvar, wchar_t *__restrict __resultpath) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsearchenv))(__file, __envvar, __resultpath); })
#endif /* ... */
#ifdef __CRT_HAVE__wsplitpath
__CDECLARE_VOID(__ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) __ATTR_OUT_OPT(5),__NOTHROW_NCX,_wsplitpath,(wchar_t const *__restrict __abspath, wchar_t *__drive, wchar_t *__dir, wchar_t *__file, wchar_t *__ext),(__abspath,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__wsplitpath */
#include <libc/local/corecrt_wstdlib/_wsplitpath.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsplitpath, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) __ATTR_OUT_OPT(5) void __NOTHROW_NCX(__LIBCCALL _wsplitpath)(wchar_t const *__restrict __abspath, wchar_t *__drive, wchar_t *__dir, wchar_t *__file, wchar_t *__ext) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsplitpath))(__abspath, __drive, __dir, __file, __ext); })
#endif /* !__CRT_HAVE__wsplitpath */
#ifdef __CRT_HAVE__wsplitpath_s
__CDECLARE(__ATTR_IN(1) __ATTR_OUTS(2, 3) __ATTR_OUTS(4, 5) __ATTR_OUTS(6, 7) __ATTR_OUTS(8, 9),errno_t,__NOTHROW_NCX,_wsplitpath_s,(wchar_t const *__restrict __abspath, wchar_t *__drive, __SIZE_TYPE__ __drivelen, wchar_t *__dir, __SIZE_TYPE__ __dirlen, wchar_t *__file, __SIZE_TYPE__ __filelen, wchar_t *__ext, __SIZE_TYPE__ __extlen),(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__wsplitpath_s */
#include <libc/local/corecrt_wstdlib/_wsplitpath_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wsplitpath_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUTS(2, 3) __ATTR_OUTS(4, 5) __ATTR_OUTS(6, 7) __ATTR_OUTS(8, 9) errno_t __NOTHROW_NCX(__LIBCCALL _wsplitpath_s)(wchar_t const *__restrict __abspath, wchar_t *__drive, __SIZE_TYPE__ __drivelen, wchar_t *__dir, __SIZE_TYPE__ __dirlen, wchar_t *__file, __SIZE_TYPE__ __filelen, wchar_t *__ext, __SIZE_TYPE__ __extlen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wsplitpath_s))(__abspath, __drive, __drivelen, __dir, __dirlen, __file, __filelen, __ext, __extlen); })
#endif /* !__CRT_HAVE__wsplitpath_s */
#endif /* !_WSTDLIBP_DEFINED */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDLIB_H */
#endif /* __USE_UTF */

#endif /* !_CORECRT_WSTDLIB_H */
