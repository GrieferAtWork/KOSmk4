/* HASH 0xa6b0014e */
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
#ifndef __local__wutime32_defined
#if (defined(__CRT_HAVE__wutime64) || defined(__CRT_HAVE_wutime64))
#define __local__wutime32_defined 1
/* Dependency: "crt_wutime64" from "parts.wchar.utime" */
#ifndef ____localdep_crt_wutime64_defined
#define ____localdep_crt_wutime64_defined 1
#if defined(__CRT_HAVE_wutime64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_wutime64,(__WCHAR_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),wutime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__wutime64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_wutime64,(__WCHAR_TYPE__ const *__filename, struct __utimbuf64 const *__file_times),_wutime64,(__filename,__file_times))
#else /* LIBC: wutime64 */
#undef ____localdep_crt_wutime64_defined
#endif /* crt_wutime64... */
#endif /* !____localdep_crt_wutime64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wutime32) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_wutime32))(__WCHAR_TYPE__ const *__filename,
                                                       struct __utimbuf32 __KOS_FIXED_CONST *__file_times) {
#line 243 "kos/src/libc/magic/utime.c"
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return __localdep_crt_wutime64(__filename,__NULLPTR);
	__buf64.__actime  = (__time64_t)__file_times->__actime;
	__buf64.__modtime = (__time64_t)__file_times->__modtime;
	return __localdep_crt_wutime64(__filename,&__buf64);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE__wutime64) || defined(__CRT_HAVE_wutime64)) */
#endif /* !__local__wutime32_defined */
