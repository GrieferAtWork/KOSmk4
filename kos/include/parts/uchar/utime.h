/* HASH CRC-32:0x2b6851b9 */
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

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

#include <bits/types.h>
#if defined(__CRT_HAVE_wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),_wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),_wutime,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),_wutime32,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),_wutime32,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime,(char16_t const *__file, struct utimbuf const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64) || ((defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 2)
#include <libc/local/parts.wchar.utime/wutime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16utime)(char16_t const *__file, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime))((__WCHAR_TYPE__ const *)__file, __file_times); }
#elif defined(__CRT_HAVE_DOS$wutime) || defined(__CRT_HAVE_DOS$_wutime) || defined(__CRT_HAVE_DOS$_wutime32) || defined(__CRT_HAVE_DOS$wutime64) || defined(__CRT_HAVE_DOS$_wutime64) || ((defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.uchar.utime/c16utime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16utime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16utime)(char16_t const *__file, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16utime))(__file, __file_times); })
#endif /* ... */
#if defined(__CRT_HAVE_wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),_wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$_wutime) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),_wutime,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),_wutime32,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$_wutime32) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),_wutime32,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$_wutime64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime,(char32_t const *__file, struct utimbuf const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64) || ((defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4)
#include <libc/local/parts.wchar.utime/wutime.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32utime)(char32_t const *__file, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime))((__WCHAR_TYPE__ const *)__file, __file_times); }
#elif defined(__CRT_HAVE_KOS$wutime) || defined(__CRT_HAVE_KOS$_wutime) || defined(__CRT_HAVE_KOS$_wutime32) || defined(__CRT_HAVE_KOS$wutime64) || defined(__CRT_HAVE_KOS$_wutime64) || ((defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)))
#include <libc/local/parts.uchar.utime/c32utime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32utime, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32utime)(char32_t const *__file, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32utime))(__file, __file_times); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime64)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime64)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c16utime64,(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime) || defined(__CRT_HAVE__wutime32)) && __SIZEOF_WCHAR_T__ == 2)
#include <libc/local/parts.wchar.utime/wutime64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16utime64)(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))((__WCHAR_TYPE__ const *)__file, __file_times); }
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 2) || defined(__CRT_HAVE_DOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime) || (defined(__CRT_HAVE__wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime32)
#include <libc/local/parts.uchar.utime/c16utime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c16utime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBDCALL c16utime64)(__CHAR16_TYPE__ const *__file, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16utime64))(__file, __file_times); })
#endif /* ... */
#if defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime,(__file,__file_times))
#elif defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime64)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE_KOS$_wutime64)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,c32utime64,(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && (defined(__CRT_HAVE_convert_wcstombs) || defined(__CRT_HAVE_convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || ((defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime) || defined(__CRT_HAVE__wutime32)) && __SIZEOF_WCHAR_T__ == 4)
#include <libc/local/parts.wchar.utime/wutime64.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32utime64)(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))((__WCHAR_TYPE__ const *)__file, __file_times); }
#elif ((defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)) && ((defined(__CRT_HAVE_convert_wcstombs) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombs) || (defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))) || (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wutime) || (defined(__CRT_HAVE__wutime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wutime32)
#include <libc/local/parts.uchar.utime/c32utime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(c32utime64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBKCALL c32utime64)(__CHAR32_TYPE__ const *__file, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32utime64))(__file, __file_times); })
#endif /* ... */
#endif /* __USE_TIME64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_PARTS_UCHAR_UTIME_H */
