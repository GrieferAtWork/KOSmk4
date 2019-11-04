/* HASH CRC-32:0x647b2dc2 */
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
#ifndef _PARTS_UCHAR_UTIME_H
#define _PARTS_UCHAR_UTIME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _UTIME_H
#include <utime.h>
#endif /* !_UTIME_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_wutime) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime64) && defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && !defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && !defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime64) && (defined(__USE_TIME_BITS64))
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime64) && (defined(__USE_TIME_BITS64))
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime) && (!defined(__USE_TIME_BITS64))
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime32) && (!defined(__USE_TIME_BITS64))
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime32)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__filename, struct utimbuf const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.utime/wutime.h>
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16utime)(char16_t const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime))((__WCHAR_TYPE__ const *)__filename, __file_times); }
#else /* LIBC: c16utime */
#include <local/parts.wchar.utime/c16utime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16utime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16utime)(char16_t const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16utime))(__filename, __file_times); })
#endif /* LIBC: c16utime */
#endif /* c16utime... */
#if defined(__CRT_HAVE_wutime) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__filename, struct utimbuf const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime64) && defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__filename, struct utimbuf const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__filename, struct utimbuf const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && !defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__filename, struct utimbuf const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && !defined(__USE_TIME_BITS64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__filename, struct utimbuf const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.utime/wutime.h>
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32utime)(char32_t const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime))((__WCHAR_TYPE__ const *)__filename, __file_times); }
#else /* LIBC: c32utime */
#include <local/parts.wchar.utime/c32utime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32utime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32utime)(char32_t const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32utime))(__filename, __file_times); })
#endif /* LIBC: c32utime */
#endif /* c32utime... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_wutime64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime64)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime64)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32)
#if __SIZEOF_WCHAR_T__ == 2
#include <local/parts.wchar.utime/wutime64.h>
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16utime64)(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))((__WCHAR_TYPE__ const *)__filename, __file_times); }
#else /* LIBC: c16utime64 */
#include <local/parts.wchar.utime/c16utime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16utime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c16utime64)(__CHAR16_TYPE__ const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16utime64))(__filename, __file_times); })
#endif /* LIBC: c16utime64 */
#endif /* c16utime64... */
#if defined(__CRT_HAVE_wutime64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32)
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.utime/wutime64.h>
__FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32utime64)(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))((__WCHAR_TYPE__ const *)__filename, __file_times); }
#else /* LIBC: c32utime64 */
#include <local/parts.wchar.utime/c32utime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32utime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL c32utime64)(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32utime64))(__filename, __file_times); })
#endif /* LIBC: c32utime64 */
#endif /* c32utime64... */
#endif /* __USE_TIME64 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_UCHAR_UTIME_H */
