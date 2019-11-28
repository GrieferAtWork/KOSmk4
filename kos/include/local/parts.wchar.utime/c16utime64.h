/* HASH CRC-32:0xb20f7481 */
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
#ifndef __local_c16utime64_defined
#if defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32)
#define __local_c16utime64_defined 1
/* Dependency: "crt_wutime32" from "parts.wchar.utime" */
#ifndef ____localdep_crt_c16utime32_defined
#define ____localdep_crt_c16utime32_defined 1
#if defined(__CRT_HAVE_crt_wutime32) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),crt_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime32) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$_wutime32)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),_wutime32,(__filename,__file_times))
#elif defined(__CRT_HAVE_DOS$crt_wutime32)
__CREDIRECT_DOS(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_c16utime32,(__CHAR16_TYPE__ const *__filename, struct __utimbuf32 const *__file_times),crt_wutime32,(__filename,__file_times))
#else /* LIBC: crt_wutime32 */
#undef ____localdep_crt_c16utime32_defined
#endif /* crt_c16utime32... */
#endif /* !____localdep_crt_c16utime32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16utime64) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16utime64))(__CHAR16_TYPE__ const *__filename,
                                                        struct utimbuf64 const *__file_times) {
#line 82 "kos/src/libc/magic/parts.wchar.utime.c"
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
#endif /* __CRT_HAVE_wutime || __CRT_HAVE__wutime32 */
#endif /* !__local_c16utime64_defined */
