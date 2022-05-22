/* HASH CRC-32:0x83b9135a */
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
#ifndef _PARTS_UCHAR_TIME_H
#define _PARTS_UCHAR_TIME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _TIME_H
#include <time.h>
#endif /* !_TIME_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__CRT_HAVE_wcsftime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsftime(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),size_t,__NOTHROW_NCX,c16ftime,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif defined(__CRT_HAVE_DOS$wcsftime)
/* >> wcsftime(3) */
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),size_t,__NOTHROW_NCX,c16ftime,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsftime.h>
/* >> wcsftime(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0) size_t __NOTHROW_NCX(__LIBDCALL c16ftime)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __tp); }
#else /* ... */
#include <libc/local/parts.uchar.time/c16ftime.h>
/* >> wcsftime(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0) size_t __NOTHROW_NCX(__LIBDCALL c16ftime)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsftime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsftime(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),size_t,__NOTHROW_NCX,c32ftime,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif defined(__CRT_HAVE_KOS$wcsftime)
/* >> wcsftime(3) */
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),size_t,__NOTHROW_NCX,c32ftime,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsftime.h>
/* >> wcsftime(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0) size_t __NOTHROW_NCX(__LIBKCALL c32ftime)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __tp); }
#else /* ... */
#include <libc/local/parts.uchar.time/c32ftime.h>
/* >> wcsftime(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ftime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0) size_t __NOTHROW_NCX(__LIBKCALL c32ftime)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_wcsftime_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_DOS$wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/wchar/wcsftime_l.h>
/* >> wcsftime_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16ftime_l)(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))((__WCHAR_TYPE__ *)__buf, __maxsize, (__WCHAR_TYPE__ const *)__format, __tp, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.time/c16ftime_l.h>
/* >> wcsftime_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ftime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C16FTIME(3, 0) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16ftime_l)(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsftime_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_KOS$wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
/* >> wcsftime_l(3) */
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_KOS$__wcsftime_l)
/* >> wcsftime_l(3) */
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/wchar/wcsftime_l.h>
/* >> wcsftime_l(3) */
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32ftime_l)(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))((__WCHAR_TYPE__ *)__buf, __maxsize, (__WCHAR_TYPE__ const *)__format, __tp, __locale); }
#else /* ... */
#include <libc/local/parts.uchar.time/c32ftime_l.h>
/* >> wcsftime_l(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ftime_l, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_WRS(1, 2) __ATTR_LIBC_C32FTIME(3, 0) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32ftime_l)(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_GNU */

#ifdef __USE_DOS
#if defined(__CRT_HAVE__wasctime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16asctime,(struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime,(__tp))
#elif defined(__CRT_HAVE_DOS$_wasctime)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16asctime,(struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime,(__tp))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wasctime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16asctime)(struct __NAMESPACE_STD_SYM tm const *__tp) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wasctime))(__tp); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c16asctime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16asctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16asctime)(struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16asctime))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE__wasctime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32asctime,(struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime,(__tp))
#elif defined(__CRT_HAVE_KOS$_wasctime)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32asctime,(struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime,(__tp))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wasctime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32asctime)(struct __NAMESPACE_STD_SYM tm const *__tp) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wasctime))(__tp); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c32asctime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32asctime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32asctime)(struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32asctime))(__tp); })
#endif /* !... */
#if defined(__CRT_HAVE__wasctime_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16asctime_s,(char16_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#elif defined(__CRT_HAVE_DOS$_wasctime_s)
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16asctime_s,(char16_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wasctime_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16asctime_s)(char16_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wasctime_s))((__WCHAR_TYPE__ *)__buf, __buflen, __tp); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c16asctime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16asctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16asctime_s)(char16_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16asctime_s))(__buf, __buflen, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE__wasctime_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32asctime_s,(char32_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#elif defined(__CRT_HAVE_KOS$_wasctime_s)
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32asctime_s,(char32_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp),_wasctime_s,(__buf,__buflen,__tp))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wasctime_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32asctime_s)(char32_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wasctime_s))((__WCHAR_TYPE__ *)__buf, __buflen, __tp); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c32asctime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32asctime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32asctime_s)(char32_t *__buf, size_t __buflen, struct __NAMESPACE_STD_SYM tm const *__tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32asctime_s))(__buf, __buflen, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16ctime32,(__time32_t const *__timer),_wctime32,(__timer))
#elif defined(__CRT_HAVE_DOS$_wctime32)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16ctime32,(__time32_t const *__timer),_wctime32,(__timer))
#elif defined(__CRT_HAVE__wctime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16ctime32,(__time32_t const *__timer),_wctime,(__timer))
#elif defined(__CRT_HAVE_DOS$_wctime)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16ctime32,(__time32_t const *__timer),_wctime,(__timer))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wctime32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16ctime32)(__time32_t const *__timer) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime32))(__timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c16ctime32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16ctime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16ctime32)(__time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16ctime32))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32ctime32,(__time32_t const *__timer),_wctime32,(__timer))
#elif defined(__CRT_HAVE_KOS$_wctime32)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32ctime32,(__time32_t const *__timer),_wctime32,(__timer))
#elif defined(__CRT_HAVE__wctime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32ctime32,(__time32_t const *__timer),_wctime,(__timer))
#elif defined(__CRT_HAVE_KOS$_wctime)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32ctime32,(__time32_t const *__timer),_wctime,(__timer))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wctime32.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32ctime32)(__time32_t const *__timer) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime32))(__timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c32ctime32.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32ctime32, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32ctime32)(__time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32ctime32))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16ctime64,(__time64_t const *__timer),_wctime64,(__timer))
#elif defined(__CRT_HAVE_DOS$_wctime64)
__CREDIRECT_DOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char16_t *,__NOTHROW_NCX,_c16ctime64,(__time64_t const *__timer),_wctime64,(__timer))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wctime64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16ctime64)(__time64_t const *__timer) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime64))(__timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c16ctime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16ctime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16ctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16ctime64))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32ctime64,(__time64_t const *__timer),_wctime64,(__timer))
#elif defined(__CRT_HAVE_KOS$_wctime64)
__CREDIRECT_KOS(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),char32_t *,__NOTHROW_NCX,_c32ctime64,(__time64_t const *__timer),_wctime64,(__timer))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wctime64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32ctime64)(__time64_t const *__timer) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime64))(__timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c32ctime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32ctime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ACCESS_RO(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32ctime64)(__time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32ctime64))(__timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime32_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16ctime32_s,(char16_t *__buf, size_t __buflen, __time32_t const *__timer),_wctime32_s,(__buf,__buflen,__timer))
#elif defined(__CRT_HAVE_DOS$_wctime32_s)
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16ctime32_s,(char16_t *__buf, size_t __buflen, __time32_t const *__timer),_wctime32_s,(__buf,__buflen,__timer))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wctime32_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16ctime32_s)(char16_t *__buf, size_t __buflen, __time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime32_s))((__WCHAR_TYPE__ *)__buf, __buflen, __timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c16ctime32_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16ctime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16ctime32_s)(char16_t *__buf, size_t __buflen, __time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16ctime32_s))(__buf, __buflen, __timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime32_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32ctime32_s,(char32_t *__buf, size_t __buflen, __time32_t const *__timer),_wctime32_s,(__buf,__buflen,__timer))
#elif defined(__CRT_HAVE_KOS$_wctime32_s)
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32ctime32_s,(char32_t *__buf, size_t __buflen, __time32_t const *__timer),_wctime32_s,(__buf,__buflen,__timer))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wctime32_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32ctime32_s)(char32_t *__buf, size_t __buflen, __time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime32_s))((__WCHAR_TYPE__ *)__buf, __buflen, __timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c32ctime32_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32ctime32_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32ctime32_s)(char32_t *__buf, size_t __buflen, __time32_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32ctime32_s))(__buf, __buflen, __timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime64_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16ctime64_s,(char16_t *__buf, size_t __buflen, __time64_t const *__timer),_wctime64_s,(__buf,__buflen,__timer))
#elif defined(__CRT_HAVE_DOS$_wctime64_s)
__CREDIRECT_DOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16ctime64_s,(char16_t *__buf, size_t __buflen, __time64_t const *__timer),_wctime64_s,(__buf,__buflen,__timer))
#elif __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wctime64_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16ctime64_s)(char16_t *__buf, size_t __buflen, __time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime64_s))((__WCHAR_TYPE__ *)__buf, __buflen, __timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c16ctime64_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16ctime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16ctime64_s)(char16_t *__buf, size_t __buflen, __time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16ctime64_s))(__buf, __buflen, __timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wctime64_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32ctime64_s,(char32_t *__buf, size_t __buflen, __time64_t const *__timer),_wctime64_s,(__buf,__buflen,__timer))
#elif defined(__CRT_HAVE_KOS$_wctime64_s)
__CREDIRECT_KOS(__ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32ctime64_s,(char32_t *__buf, size_t __buflen, __time64_t const *__timer),_wctime64_s,(__buf,__buflen,__timer))
#elif __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wctime64_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32ctime64_s)(char32_t *__buf, size_t __buflen, __time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wctime64_s))((__WCHAR_TYPE__ *)__buf, __buflen, __timer); }
#else /* ... */
#include <libc/local/parts.uchar.time/_c32ctime64_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32ctime64_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_RO(3) __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32ctime64_s)(char32_t *__buf, size_t __buflen, __time64_t const *__timer) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32ctime64_s))(__buf, __buflen, __timer); })
#endif /* !... */
#if defined(__CRT_HAVE__wstrtime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_WR(1),char16_t *,__NOTHROW_NCX,_c16strtime,(char16_t __buf[9]),_wstrtime,(__buf))
#elif defined(__CRT_HAVE_DOS$_wstrtime)
__CREDIRECT_DOS(__ATTR_ACCESS_WR(1),char16_t *,__NOTHROW_NCX,_c16strtime,(char16_t __buf[9]),_wstrtime,(__buf))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wstrtime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16strtime)(char16_t __buf[9]) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrtime))((__WCHAR_TYPE__ *)__buf); }
#elif defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c16strtime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16strtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16strtime)(char16_t __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16strtime))(__buf); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrtime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_WR(1),char32_t *,__NOTHROW_NCX,_c32strtime,(char32_t __buf[9]),_wstrtime,(__buf))
#elif defined(__CRT_HAVE_KOS$_wstrtime)
__CREDIRECT_KOS(__ATTR_ACCESS_WR(1),char32_t *,__NOTHROW_NCX,_c32strtime,(char32_t __buf[9]),_wstrtime,(__buf))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wstrtime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32strtime)(char32_t __buf[9]) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrtime))((__WCHAR_TYPE__ *)__buf); }
#elif defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c32strtime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32strtime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32strtime)(char32_t __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32strtime))(__buf); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrtime_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16strtime_s,(char16_t *__buf, size_t __buflen),_wstrtime_s,(__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$_wstrtime_s)
__CREDIRECT_DOS(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16strtime_s,(char16_t *__buf, size_t __buflen),_wstrtime_s,(__buf,__buflen))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__wstrtime) || defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wstrtime_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16strtime_s)(char16_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrtime_s))((__WCHAR_TYPE__ *)__buf, __buflen); }
#elif (defined(__CRT_HAVE__wstrtime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wstrtime) || defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c16strtime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16strtime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16strtime_s)(char16_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16strtime_s))(__buf, __buflen); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrtime_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32strtime_s,(char32_t *__buf, size_t __buflen),_wstrtime_s,(__buf,__buflen))
#elif defined(__CRT_HAVE_KOS$_wstrtime_s)
__CREDIRECT_KOS(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32strtime_s,(char32_t *__buf, size_t __buflen),_wstrtime_s,(__buf,__buflen))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__wstrtime) || defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wstrtime_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32strtime_s)(char32_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrtime_s))((__WCHAR_TYPE__ *)__buf, __buflen); }
#elif (defined(__CRT_HAVE__wstrtime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wstrtime) || defined(__CRT_HAVE__strtime) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c32strtime_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32strtime_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32strtime_s)(char32_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32strtime_s))(__buf, __buflen); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrdate) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_WR(1),char16_t *,__NOTHROW_NCX,_c16strdate,(char16_t __buf[9]),_wstrdate,(__buf))
#elif defined(__CRT_HAVE_DOS$_wstrdate)
__CREDIRECT_DOS(__ATTR_ACCESS_WR(1),char16_t *,__NOTHROW_NCX,_c16strdate,(char16_t __buf[9]),_wstrdate,(__buf))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wstrdate.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16strdate)(char16_t __buf[9]) { return (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrdate))((__WCHAR_TYPE__ *)__buf); }
#elif defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c16strdate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16strdate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char16_t *__NOTHROW_NCX(__LIBDCALL _c16strdate)(char16_t __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16strdate))(__buf); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrdate) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_WR(1),char32_t *,__NOTHROW_NCX,_c32strdate,(char32_t __buf[9]),_wstrdate,(__buf))
#elif defined(__CRT_HAVE_KOS$_wstrdate)
__CREDIRECT_KOS(__ATTR_ACCESS_WR(1),char32_t *,__NOTHROW_NCX,_c32strdate,(char32_t __buf[9]),_wstrdate,(__buf))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wstrdate.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32strdate)(char32_t __buf[9]) { return (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrdate))((__WCHAR_TYPE__ *)__buf); }
#elif defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c32strdate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32strdate, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WR(1) char32_t *__NOTHROW_NCX(__LIBKCALL _c32strdate)(char32_t __buf[9]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32strdate))(__buf); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrdate_s) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16strdate_s,(char16_t *__buf, size_t __buflen),_wstrdate_s,(__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$_wstrdate_s)
__CREDIRECT_DOS(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c16strdate_s,(char16_t *__buf, size_t __buflen),_wstrdate_s,(__buf,__buflen))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__wstrdate) || defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 2
#include <libc/local/corecrt_wtime/_wstrdate_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16strdate_s)(char16_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrdate_s))((__WCHAR_TYPE__ *)__buf, __buflen); }
#elif (defined(__CRT_HAVE__wstrdate) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wstrdate) || defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c16strdate_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c16strdate_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBDCALL _c16strdate_s)(char16_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c16strdate_s))(__buf, __buflen); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE__wstrdate_s) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32strdate_s,(char32_t *__buf, size_t __buflen),_wstrdate_s,(__buf,__buflen))
#elif defined(__CRT_HAVE_KOS$_wstrdate_s)
__CREDIRECT_KOS(__ATTR_ACCESS_WRS(1, 2),errno_t,__NOTHROW_NCX,_c32strdate_s,(char32_t *__buf, size_t __buflen),_wstrdate_s,(__buf,__buflen))
#else /* ... */
#include <bits/types.h>
#if (defined(__CRT_HAVE__wstrdate) || defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)) && __SIZEOF_WCHAR_T__ == 4
#include <libc/local/corecrt_wtime/_wstrdate_s.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32strdate_s)(char32_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_wstrdate_s))((__WCHAR_TYPE__ *)__buf, __buflen); }
#elif (defined(__CRT_HAVE__wstrdate) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wstrdate) || defined(__CRT_HAVE__strdate) || defined(__CRT_HAVE_time64) || defined(__CRT_HAVE__time64) || defined(__CRT_HAVE_time) || defined(__CRT_HAVE___time) || defined(__CRT_HAVE___libc_time) || defined(__CRT_HAVE__time32)
#include <libc/local/parts.uchar.time/_c32strdate_s.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_c32strdate_s, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_ACCESS_WRS(1, 2) errno_t __NOTHROW_NCX(__LIBKCALL _c32strdate_s)(char32_t *__buf, size_t __buflen) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_c32strdate_s))(__buf, __buflen); })
#endif /* ... */
#endif /* !... */


#ifdef __USE_TIME_BITS64
#define _c16ctime   _c16ctime64
#define _c32ctime   _c32ctime64
#define _c16ctime_s _c16ctime64_s
#define _c32ctime_s _c32ctime64_s
#else /* __USE_TIME_BITS64 */
#define _c16ctime   _c16ctime32
#define _c32ctime   _c32ctime32
#define _c16ctime_s _c16ctime32_s
#define _c32ctime_s _c32ctime32_s
#endif /* !__USE_TIME_BITS64 */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_TIME_H */
