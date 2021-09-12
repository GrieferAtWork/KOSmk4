/* HASH CRC-32:0x325c82ea */
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
#ifndef __local_c32utime_defined
#define __local_c32utime_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wutime32) || (defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wutime64) || (defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wutime64)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32utime64_defined
#define __local___localdep_c32utime64_defined 1
#if defined(__CRT_HAVE_wutime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime64)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_KOS$_wutime64)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif (defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.utime/wutime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32utime64 __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__CHAR32_TYPE__ const *,struct __utimbuf64 const *),int(__LIBKCALL&)(__CHAR32_TYPE__ const *,struct __utimbuf64 const *),wutime64)
#elif (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wutime32)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.utime/c32utime64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32utime64 __LIBC_LOCAL_NAME(c32utime64)
#else /* ... */
#undef __local___localdep_c32utime64_defined
#endif /* !... */
#endif /* !__local___localdep_c32utime64_defined */
#ifndef __local___localdep_crt_c32utime32_defined
#define __local___localdep_crt_c32utime32_defined 1
#if defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c32utime32,(__CHAR32_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_KOS$wutime)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c32utime32,(__CHAR32_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c32utime32,(__CHAR32_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_KOS$_wutime32)
__CREDIRECT_KOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c32utime32,(__CHAR32_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#else /* ... */
#undef __local___localdep_crt_c32utime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_c32utime32_defined */
__LOCAL_LIBC(c32utime) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32utime))(__CHAR32_TYPE__ const *__filename, struct utimbuf const *__file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
#if (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$_wutime32)
	struct __utimbuf32 __buf32;
	if (!__file_times)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_c32utime32)(__filename, __NULLPTR);
	__buf32.actime  = (__time32_t)__file_times->actime;
	__buf32.modtime = (__time32_t)__file_times->modtime;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_c32utime32)(__filename, &__buf32);
#else /* (__CRT_HAVE_wutime && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wutime || (__CRT_HAVE__wutime32 && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wutime32 */
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return (__NAMESPACE_LOCAL_SYM __localdep_c32utime64)(__filename, __NULLPTR);
	__buf64.actime  = (__time64_t)__file_times->actime;
	__buf64.modtime = (__time64_t)__file_times->modtime;
	return (__NAMESPACE_LOCAL_SYM __localdep_c32utime64)(__filename, &__buf64);
#endif /* (!__CRT_HAVE_wutime || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wutime && (!__CRT_HAVE__wutime32 || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wutime32 */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32utime_defined
#define __local___localdep_c32utime_defined 1
#define __localdep_c32utime __LIBC_LOCAL_NAME(c32utime)
#endif /* !__local___localdep_c32utime_defined */
#else /* (__CRT_HAVE_wutime && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wutime || (__CRT_HAVE__wutime32 && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wutime32 || (__CRT_HAVE_wutime64 && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wutime64 || (__CRT_HAVE__wutime64 && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$_wutime64 */
#undef __local_c32utime_defined
#endif /* (!__CRT_HAVE_wutime || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wutime && (!__CRT_HAVE__wutime32 || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wutime32 && (!__CRT_HAVE_wutime64 || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wutime64 && (!__CRT_HAVE__wutime64 || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$_wutime64 */
#endif /* !__local_c32utime_defined */
