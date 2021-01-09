/* HASH CRC-32:0x60fcfe33 */
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
#ifndef __local_c16utime64_defined
#define __local_c16utime64_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wutime) || (defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$_wutime32)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_c16utime32 from parts.uchar.utime */
#ifndef __local___localdep_crt_c16utime32_defined
#define __local___localdep_crt_c16utime32_defined 1
#if defined(__CRT_HAVE_wutime) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$wutime)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime32)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#else /* ... */
#undef __local___localdep_crt_c16utime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_c16utime32_defined */
__LOCAL_LIBC(c16utime64) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16utime64))(__CHAR16_TYPE__ const *__filename, struct __utimbuf64 const *__file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
	struct __utimbuf32 __buf32;
	if (!__file_times)
		return __localdep_crt_c16utime32(__filename, __NULLPTR);
	__buf32.actime  = (__time32_t)__file_times->actime;
	__buf32.modtime = (__time32_t)__file_times->modtime;
	return __localdep_crt_c16utime32(__filename, &__buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16utime64_defined
#define __local___localdep_c16utime64_defined 1
#define __localdep_c16utime64 __LIBC_LOCAL_NAME(c16utime64)
#endif /* !__local___localdep_c16utime64_defined */
#else /* (__CRT_HAVE_wutime && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wutime || (__CRT_HAVE__wutime32 && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$_wutime32 */
#undef __local_c16utime64_defined
#endif /* (!__CRT_HAVE_wutime || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wutime && (!__CRT_HAVE__wutime32 || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$_wutime32 */
#endif /* !__local_c16utime64_defined */
