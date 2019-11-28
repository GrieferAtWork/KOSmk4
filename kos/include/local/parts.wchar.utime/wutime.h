/* HASH CRC-32:0xc6e9d054 */
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
#ifndef __local_wutime_defined
#if defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)
#define __local_wutime_defined 1
/* Dependency: "crt_wutime32" from "parts.wchar.utime" */
#ifndef ____localdep_crt_wutime32_defined
#define ____localdep_crt_wutime32_defined 1
#ifdef __CRT_HAVE_wutime
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_wutime32,(__WCHAR_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_wutime32,(__WCHAR_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#else /* LIBC: wutime */
#undef ____localdep_crt_wutime32_defined
#endif /* crt_wutime32... */
#endif /* !____localdep_crt_wutime32_defined */

/* Dependency: "wutime64" from "parts.wchar.utime" */
#ifndef ____localdep_wutime64_defined
#define ____localdep_wutime64_defined 1
#ifdef __CRT_HAVE_wutime64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_wutime64,(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_wutime64,(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_wutime64,(__WCHAR_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32)
#include <local/parts.wchar.utime/wutime64.h>
#define __localdep_wutime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))
#else /* CUSTOM: wutime64 */
#undef ____localdep_wutime64_defined
#endif /* wutime64... */
#endif /* !____localdep_wutime64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wutime) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wutime))(__WCHAR_TYPE__ const *__filename,
                                                    struct utimbuf const *__file_times) {
#line 50 "kos/src/libc/magic/parts.wchar.utime.c"
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
#if defined(__CRT_HAVE_utime) || defined(__CRT_HAVE__utime32)
	struct __utimbuf32 __buf32;
	if (!__file_times)
		return __localdep_crt_wutime32(__filename, __NULLPTR);
	__buf32.actime  = (__time32_t)__file_times->actime;
	__buf32.modtime = (__time32_t)__file_times->modtime;
	return __localdep_crt_wutime32(__filename, &__buf32);
#else
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return __localdep_wutime64(__filename, __NULLPTR);
	__buf64.actime  = (__time64_t)__file_times->actime;
	__buf64.modtime = (__time64_t)__file_times->modtime;
	return __localdep_wutime64(__filename, &__buf64);
#endif
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_wutime || __CRT_HAVE__wutime32 || __CRT_HAVE_wutime64 || __CRT_HAVE__wutime64 */
#endif /* !__local_wutime_defined */
