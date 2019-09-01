/* HASH 0xaabdaadb */
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
#ifndef __local_openat_defined
#if defined(__CRT_HAVE_openat64)
#define __local_openat_defined 1
#include <bits/types.h>
#include <bits/types.h>
#include <bits/fcntl.h>
/* Dependency: "openat64" from "fcntl" */
#ifndef ____localdep_openat64_defined
#define ____localdep_openat64_defined 1
#if defined(__CRT_HAVE_openat64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
#include <local/fcntl/openat64.h>
#define __localdep_openat64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat64))
#else /* CUSTOM: openat64 */
#undef ____localdep_openat64_defined
#endif /* openat64... */
#endif /* !____localdep_openat64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(openat) __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(openat))(__fd_t __dirfd,
                                                     char const *__filename,
                                                     __oflag_t __oflags,
                                                     ...) {
#line 261 "kos/src/libc/magic/fcntl.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
	__result = __localdep_openat64(__dirfd, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_openat64) */
#endif /* !__local_openat_defined */
