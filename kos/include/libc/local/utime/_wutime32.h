/* HASH CRC-32:0xb8903efc */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wutime32_defined
#define __local__wutime32_defined
#include <__crt.h>
#if defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64)
#include <features.h>
#include <bits/os/utimbuf.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_wutime64_defined
#define __local___localdep_crt_wutime64_defined
#ifdef __CRT_HAVE_wutime64
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,__localdep_crt_wutime64,(__WCHAR_TYPE__ const *__file, struct __utimbuf64 const *__file_times),wutime64,(__file,__file_times))
#elif defined(__CRT_HAVE__wutime64)
__CREDIRECT(__ATTR_IN(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,__localdep_crt_wutime64,(__WCHAR_TYPE__ const *__file, struct __utimbuf64 const *__file_times),_wutime64,(__file,__file_times))
#else /* ... */
#undef __local___localdep_crt_wutime64_defined
#endif /* !... */
#endif /* !__local___localdep_crt_wutime64_defined */
__LOCAL_LIBC(_wutime32) __ATTR_IN(1) __ATTR_IN_OPT(2) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_wutime32))(__WCHAR_TYPE__ const *__filename, struct __utimbuf32 __KOS_FIXED_CONST *__file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
	struct __utimbuf64 __buf64;
	if (!__file_times)
		return (__NAMESPACE_LOCAL_SYM __localdep_crt_wutime64)(__filename, __NULLPTR);
	__buf64.actime  = (__time64_t)__file_times->actime;
	__buf64.modtime = (__time64_t)__file_times->modtime;
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_wutime64)(__filename, &__buf64);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wutime32_defined
#define __local___localdep__wutime32_defined
#define __localdep__wutime32 __LIBC_LOCAL_NAME(_wutime32)
#endif /* !__local___localdep__wutime32_defined */
#else /* __CRT_HAVE_wutime64 || __CRT_HAVE__wutime64 */
#undef __local__wutime32_defined
#endif /* !__CRT_HAVE_wutime64 && !__CRT_HAVE__wutime64 */
#endif /* !__local__wutime32_defined */
