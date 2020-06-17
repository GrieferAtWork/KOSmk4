/* HASH CRC-32:0xd4c06032 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_wcsftime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,c16ftime,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif defined(__CRT_HAVE_DOS$wcsftime)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,c16ftime,(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsftime.h>
__FORCELOCAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBDCALL c16ftime)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __tp); }
#else /* ... */
#include <local/parts.uchar.time/c16ftime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ftime, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBDCALL c16ftime)(char16_t *__restrict __buf, size_t __buflen, char16_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsftime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,c32ftime,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif defined(__CRT_HAVE_KOS$wcsftime)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3, 4)),size_t,__NOTHROW_NCX,c32ftime,(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp),wcsftime,(__buf,__buflen,__format,__tp))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsftime.h>
__FORCELOCAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBKCALL c32ftime)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime))((__WCHAR_TYPE__ *)__buf, __buflen, (__WCHAR_TYPE__ const *)__format, __tp); }
#else /* ... */
#include <local/parts.uchar.time/c32ftime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ftime, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) size_t __NOTHROW_NCX(__LIBKCALL c32ftime)(char32_t *__restrict __buf, size_t __buflen, char32_t const *__restrict __format, struct tm const *__restrict __tp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ftime))(__buf, __buflen, __format, __tp); })
#endif /* !... */

#ifdef __USE_GNU
#if defined(__CRT_HAVE_wcsftime_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_DOS$wcsftime_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsftime_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_DOS$__wcsftime_l)
__CREDIRECT_DOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c16ftime_l,(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsftime_l.h>
__FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16ftime_l)(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))((__WCHAR_TYPE__ *)__buf, __maxsize, (__WCHAR_TYPE__ const *)__format, __tp, __locale); }
#else /* ... */
#include <local/parts.uchar.time/c16ftime_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16ftime_l, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBDCALL c16ftime_l)(char16_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char16_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16ftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* !... */
#if defined(__CRT_HAVE_wcsftime_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_KOS$wcsftime_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__wcsftime_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_KOS$_wcsftime_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),_wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___wcsftime_l) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE_KOS$__wcsftime_l)
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,c32ftime_l,(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale),__wcsftime_l,(__buf,__maxsize,__format,__tp,__locale))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsftime_l.h>
__FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32ftime_l)(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsftime_l))((__WCHAR_TYPE__ *)__buf, __maxsize, (__WCHAR_TYPE__ const *)__format, __tp, __locale); }
#else /* ... */
#include <local/parts.uchar.time/c32ftime_l.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32ftime_l, __FORCELOCAL __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__ __NOTHROW_NCX(__LIBKCALL c32ftime_l)(char32_t *__restrict __buf, __SIZE_TYPE__ __maxsize, char32_t const *__restrict __format, __STRUCT_TM const *__restrict __tp, __locale_t __locale) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32ftime_l))(__buf, __maxsize, __format, __tp, __locale); })
#endif /* !... */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_TIME_H */
