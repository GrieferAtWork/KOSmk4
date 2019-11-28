/* HASH CRC-32:0xf6c46d22 */
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
#ifndef _PARTS_WCHAR_UTIME_H
#define _PARTS_WCHAR_UTIME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#ifndef _UTIME_H
#include <utime.h>
#endif /* !_UTIME_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_wutime64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime,(wchar_t const *__filename, struct utimbuf const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime,(wchar_t const *__filename, struct utimbuf const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && (!defined(__USE_TIME_BITS64))
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime,(wchar_t const *__filename, struct utimbuf const *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && (!defined(__USE_TIME_BITS64))
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime,(wchar_t const *__filename, struct utimbuf const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)
#include <local/parts.wchar.utime/wutime.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wutime, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wutime)(wchar_t const *__filename, struct utimbuf const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime))(__filename, __file_times); })
#endif /* wutime... */

#ifdef __USE_TIME64
#ifdef __CRT_HAVE_wutime64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime64,(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times),(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime64,(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,wutime64,(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32)
#include <local/parts.wchar.utime/wutime64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(wutime64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL wutime64)(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))(__filename, __file_times); })
#endif /* wutime64... */
#endif /* __USE_TIME64 */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_PARTS_WCHAR_UTIME_H */
