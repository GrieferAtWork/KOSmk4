/* HASH CRC-32:0xb375b2cc */
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
#ifndef __local__utime32_defined
#if defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64)
#define __local__utime32_defined 1
#include <__crt.h>
/* Dependency: "crt_utime64" from "utime" */
#ifndef ____localdep_crt_utime64_defined
#define ____localdep_crt_utime64_defined 1
#ifdef __CRT_HAVE_utime64
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_utime64,(char const *__filename, struct __utimbuf64 const *__file_times),utime64,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_crt_utime64,(char const *__filename, struct __utimbuf64 const *__file_times),_utime64,(__filename,__file_times))
#else /* LIBC: utime64 */
#undef ____localdep_crt_utime64_defined
#endif /* crt_utime64... */
#endif /* !____localdep_crt_utime64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_utime32) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_utime32))(char const *__filename,
                                                      struct __utimbuf32 __KOS_FIXED_CONST *__file_times) {
#line 214 "kos/src/libc/magic/utime.c"
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return __localdep_crt_utime64(__filename, __NULLPTR);
	__buf64.actime  = (__time64_t)__file_times->actime;
	__buf64.modtime = (__time64_t)__file_times->modtime;
	return __localdep_crt_utime64(__filename, &__buf64);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_utime64 || __CRT_HAVE__utime64 */
#endif /* !__local__utime32_defined */
