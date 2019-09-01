/* HASH 0x7a503f39 */
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
#ifndef __local_c32utime_defined
#if (defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64))
#define __local_c32utime_defined 1
/* Dependency: "crt_wutime32" from "parts.wchar.utime" */
#ifndef ____localdep_crt_c32utime32_defined
#define ____localdep_crt_c32utime32_defined 1
#if defined(__CRT_HAVE_crt_wutime32) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c32utime32,(__CHAR32_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),crt_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c32utime32,(__CHAR32_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#else /* LIBC: crt_wutime32 */
#undef ____localdep_crt_c32utime32_defined
#endif /* crt_c32utime32... */
#endif /* !____localdep_crt_c32utime32_defined */

/* Dependency: "wutime64" from "parts.wchar.utime" */
#ifndef ____localdep_c32utime64_defined
#define ____localdep_c32utime64_defined 1
#if defined(__CRT_HAVE_wutime64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE_wutime) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (__SIZEOF_WCHAR_T__ == 4))
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_c32utime64,(__CHAR32_TYPE__ const *__filename, struct utimbuf64 const *__file_times),wutime,(__filename,__file_times))
#elif (defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32))
#if __SIZEOF_WCHAR_T__ == 4
#include <local/parts.wchar.utime/wutime64.h>
#define __localdep_c32utime64(filename, file_times) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wutime64))((__WCHAR_TYPE__ const *)(filename), file_times)
#else /* LIBC: c32utime64 */
#include <local/parts.wchar.utime/c32utime64.h>
#define __localdep_c32utime64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32utime64))
#endif /* LIBC: c32utime64 */
#else /* CUSTOM: wutime64 */
#undef ____localdep_c32utime64_defined
#endif /* c32utime64... */
#endif /* !____localdep_c32utime64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32utime) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32utime))(__CHAR32_TYPE__ const *__filename,
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
		return __localdep_crt_c32utime32(__filename, __NULLPTR);
	__buf32.actime  = (__time32_t)__file_times->actime;
	__buf32.modtime = (__time32_t)__file_times->modtime;
	return __localdep_crt_c32utime32(__filename, &__buf32);
#else
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return __localdep_c32utime64(__filename, __NULLPTR);
	__buf64.actime  = (__time64_t)__file_times->actime;
	__buf64.modtime = (__time64_t)__file_times->modtime;
	return __localdep_c32utime64(__filename, &__buf64);
#endif
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)) */
#endif /* !__local_c32utime_defined */
