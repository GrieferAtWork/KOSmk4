/* HASH CRC-32:0xd9a1e72c */
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
#ifndef __local_openat_defined
#define __local_openat_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: openat64 from fcntl */
#ifndef __local___localdep_openat64_defined
#define __local___localdep_openat64_defined 1
#ifdef __CRT_HAVE_openat64
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
__NAMESPACE_LOCAL_END
#include <local/fcntl/openat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_openat64 __LIBC_LOCAL_NAME(openat64)
#else /* ... */
#undef __local___localdep_openat64_defined
#endif /* !... */
#endif /* !__local___localdep_openat64_defined */
__LOCAL_LIBC(openat) __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(openat))(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) {
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
	__result = __localdep_openat64(__dirfd, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_openat_defined
#define __local___localdep_openat_defined 1
#define __localdep_openat __LIBC_LOCAL_NAME(openat)
#endif /* !__local___localdep_openat_defined */
#else /* __CRT_HAVE_openat64 || __CRT_HAVE_openat */
#undef __local_openat_defined
#endif /* !__CRT_HAVE_openat64 && !__CRT_HAVE_openat */
#endif /* !__local_openat_defined */
