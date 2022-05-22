/* HASH CRC-32:0xf5f47c0b */
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
#ifndef __local_utime64_defined
#define __local_utime64_defined
#include <__crt.h>
#if defined(__CRT_HAVE_utime) || defined(__CRT_HAVE___utime) || defined(__CRT_HAVE___libc_utime) || defined(__CRT_HAVE__utime) || defined(__CRT_HAVE__utime32)
#include <bits/os/utimbuf.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_utime32_defined
#define __local___localdep_crt_utime32_defined
#ifdef __CRT_HAVE_utime
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_crt_utime32,(char const *__filename, struct __utimbuf32 const *__file_times),utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___utime)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_crt_utime32,(char const *__filename, struct __utimbuf32 const *__file_times),__utime,(__filename,__file_times))
#elif defined(__CRT_HAVE___libc_utime)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_crt_utime32,(char const *__filename, struct __utimbuf32 const *__file_times),__libc_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_crt_utime32,(char const *__filename, struct __utimbuf32 const *__file_times),_utime,(__filename,__file_times))
#elif defined(__CRT_HAVE__utime32)
__CREDIRECT(__ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2),int,__NOTHROW_RPC,__localdep_crt_utime32,(char const *__filename, struct __utimbuf32 const *__file_times),_utime32,(__filename,__file_times))
#else /* ... */
#undef __local___localdep_crt_utime32_defined
#endif /* !... */
#endif /* !__local___localdep_crt_utime32_defined */
__LOCAL_LIBC(utime64) __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO_OPT(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(utime64))(char const *__filename, struct __utimbuf64 const *__file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
	struct __utimbuf32 __buf32;
	if (!__file_times)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_utime32)(__filename, __NULLPTR);
	__buf32.actime  = (__time32_t)__file_times->actime;
	__buf32.modtime = (__time32_t)__file_times->modtime;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_utime32)(__filename, &__buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_utime64_defined
#define __local___localdep_utime64_defined
#define __localdep_utime64 __LIBC_LOCAL_NAME(utime64)
#endif /* !__local___localdep_utime64_defined */
#else /* __CRT_HAVE_utime || __CRT_HAVE___utime || __CRT_HAVE___libc_utime || __CRT_HAVE__utime || __CRT_HAVE__utime32 */
#undef __local_utime64_defined
#endif /* !__CRT_HAVE_utime && !__CRT_HAVE___utime && !__CRT_HAVE___libc_utime && !__CRT_HAVE__utime && !__CRT_HAVE__utime32 */
#endif /* !__local_utime64_defined */
