/* HASH CRC-32:0xbbedf4a5 */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wtime.h) */
#ifndef _CORECRT_WTIME_H
#define _CORECRT_WTIME_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/tm.h>
#include <hybrid/typecore.h>

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifdef __CRT_HAVE__wasctime
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wasctime,(struct tm const *__tp),(__tp))
#else /* __CRT_HAVE__wasctime */
#include <libc/local/corecrt_wtime/_wasctime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wasctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wasctime)(struct tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wasctime))(__tp); })
#endif /* !__CRT_HAVE__wasctime */
#ifdef __CRT_HAVE__wasctime_s
__CDECLARE(__ATTR_NONNULL((1, 3)),errno_t,__NOTHROW_NCX,_wasctime_s,(wchar_t *__buf, size_t __buflen, struct tm const *__tp),(__buf,__buflen,__tp))
#else /* __CRT_HAVE__wasctime_s */
#include <libc/local/corecrt_wtime/_wasctime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wasctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) errno_t __NOTHROW_NCX(__LIBCCALL _wasctime_s)(wchar_t *__buf, size_t __buflen, struct tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wasctime_s))(__buf, __buflen, __tp); })
#endif /* !__CRT_HAVE__wasctime_s */
#ifndef __wcsftime_defined
#define __wcsftime_defined
#ifdef __std_wcsftime_defined
/* >> wcsftime(3) */
__NAMESPACE_STD_USING(wcsftime)
#elif defined(__CRT_HAVE_wcsftime)
/* >> wcsftime(3) */
__CDECLARE(__ATTR_LIBC_WCSFTIME(3, 0) __ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,wcsftime,(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp),(__buf,__buflen,__format,__tp))
#else /* ... */
#include <libc/local/wchar/wcsftime.h>
/* >> wcsftime(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(wcsftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBCCALL wcsftime)(wchar_t *__restrict __buf, size_t __buflen, wchar_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */
#endif /* !__wcsftime_defined */
#ifdef __CRT_HAVE_wcsftime_l
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_LIBC_WCSFTIME(3, 0) __ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l)
/* >> wcsftime_l(3) */
__CDECLARE(__ATTR_LIBC_WCSFTIME(3, 0) __ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_LIBC_WCSFTIME(3, 0) __ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,_wcsftime_l,(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#else /* ... */
#include <libc/local/wchar/wcsftime_l.h>
/* >> wcsftime_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LIBC_WCSFTIME(3, 0) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _wcsftime_l)(wchar_t *__restrict __buf, __SIZE_TYPE__ __maxsize, wchar_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))(__buf, __maxsize, __format, __tp, __locale); }
#endif /* !... */
#ifdef __CRT_HAVE__wctime32
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wctime32,(__time32_t const *__timer),(__timer))
#elif defined(__CRT_HAVE__wctime)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wctime32,(__time32_t const *__timer),_wctime,(__timer))
#else /* ... */
#include <libc/local/corecrt_wtime/_wctime32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wctime32)(__time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime32))(__timer); })
#endif /* !... */
#ifdef __CRT_HAVE__wctime64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wctime64,(__time64_t const *__timer),(__timer))
#else /* __CRT_HAVE__wctime64 */
#include <libc/local/corecrt_wtime/_wctime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime64))(__timer); })
#endif /* !__CRT_HAVE__wctime64 */
#ifdef __CRT_HAVE__wctime32_s
__CDECLARE(__ATTR_NONNULL((1, 3)),errno_t,__NOTHROW_NCX,_wctime32_s,(wchar_t *__buf, size_t __buflen, __time32_t const *__timer),(__buf,__buflen,__timer))
#else /* __CRT_HAVE__wctime32_s */
#include <libc/local/corecrt_wtime/_wctime32_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) errno_t __NOTHROW_NCX(__LIBCCALL _wctime32_s)(wchar_t *__buf, size_t __buflen, __time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime32_s))(__buf, __buflen, __timer); })
#endif /* !__CRT_HAVE__wctime32_s */
#ifdef __CRT_HAVE__wctime64_s
__CDECLARE(__ATTR_NONNULL((1, 3)),errno_t,__NOTHROW_NCX,_wctime64_s,(wchar_t *__buf, size_t __buflen, __time64_t const *__timer),(__buf,__buflen,__timer))
#else /* __CRT_HAVE__wctime64_s */
#include <libc/local/corecrt_wtime/_wctime64_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wctime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 3)) errno_t __NOTHROW_NCX(__LIBCCALL _wctime64_s)(wchar_t *__buf, size_t __buflen, __time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime64_s))(__buf, __buflen, __timer); })
#endif /* !__CRT_HAVE__wctime64_s */
#ifdef __CRT_HAVE__wstrtime
__CDECLARE(__ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wstrtime,(wchar_t __buf[9]),(__buf))
#elif defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/corecrt_wtime/_wstrtime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wstrtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wstrtime)(wchar_t __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrtime))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE__wstrdate
__CDECLARE(__ATTR_NONNULL((1)),wchar_t *,__NOTHROW_NCX,_wstrdate,(wchar_t __buf[9]),(__buf))
#elif defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/corecrt_wtime/_wstrdate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wstrdate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) wchar_t *__NOTHROW_NCX(__LIBCCALL _wstrdate)(wchar_t __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrdate))(__buf); })
#endif /* ... */
#ifdef __CRT_HAVE__wstrtime_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_wstrtime_s,(wchar_t *__buf, size_t __buflen),(__buf,__buflen))
#elif defined(__CRT_HAVE__wstrtime) || defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/corecrt_wtime/_wstrtime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wstrtime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _wstrtime_s)(wchar_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrtime_s))(__buf, __buflen); })
#endif /* ... */
#ifdef __CRT_HAVE__wstrdate_s
__CDECLARE(__ATTR_NONNULL((1)),errno_t,__NOTHROW_NCX,_wstrdate_s,(wchar_t *__buf, size_t __buflen),(__buf,__buflen))
#elif defined(__CRT_HAVE__wstrdate) || defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/corecrt_wtime/_wstrdate_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_wstrdate_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) errno_t __NOTHROW_NCX(__LIBCCALL _wstrdate_s)(wchar_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrdate_s))(__buf, __buflen); })
#endif /* ... */


#ifdef __USE_TIME_BITS64
#define _wctime   _wctime64
#define _wctime_s _wctime64_s
#else /* __USE_TIME_BITS64 */
#define _wctime   _wctime32
#define _wctime_s _wctime32_s
#endif /* !__USE_TIME_BITS64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_WTIME_H */
