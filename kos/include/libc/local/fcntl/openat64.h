/* HASH CRC-32:0xfbd25214 */
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
#ifndef __local_openat64_defined
#define __local_openat64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_openat
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_openat32_defined
#define __local___localdep_openat32_defined
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(2),__fd_t,__NOTHROW_RPC,__localdep_openat32,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#endif /* !__local___localdep_openat32_defined */
__LOCAL_LIBC(openat64) __ATTR_WUNUSED __ATTR_ACCESS_RO(2) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(openat64))(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) {
	__fd_t __result;
	__builtin_va_list __args;
	__mode_t __mode;
	__builtin_va_start(__args, __oflags);
	__mode = __builtin_va_arg(__args, __mode_t);
#ifdef __O_LARGEFILE
	__result = (__NAMESPACE_LOCAL_SYM __localdep_openat32)(__dirfd, __filename, __oflags | __O_LARGEFILE, __mode);
#else /* __O_LARGEFILE */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_openat32)(__dirfd, __filename, __oflags, __mode);
#endif /* !__O_LARGEFILE */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_openat64_defined
#define __local___localdep_openat64_defined
#define __localdep_openat64 __LIBC_LOCAL_NAME(openat64)
#endif /* !__local___localdep_openat64_defined */
#else /* __CRT_HAVE_openat */
#undef __local_openat64_defined
#endif /* !__CRT_HAVE_openat */
#endif /* !__local_openat64_defined */
