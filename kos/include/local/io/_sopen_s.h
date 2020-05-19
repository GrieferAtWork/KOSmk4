/* HASH CRC-32:0xdb5de80b */
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
#ifndef __local__sopen_s_defined
#if defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64))) || defined(__CRT_HAVE_sopen) || defined(__CRT_HAVE__sopen)
#define __local__sopen_s_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/types.h>
#include <parts/errno.h>
/* Dependency: "sopen" from "io" */
#ifndef ____localdep_sopen_defined
#define ____localdep_sopen_defined 1
#ifdef __CRT_HAVE_sopen
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_sopen,(char const *__filename, __oflag_t __oflags, int __sflags),sopen,(__filename,__oflags,__sflags),__sflags,1,(__mode_t))
#elif defined(__CRT_HAVE__sopen)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_sopen,(char const *__filename, __oflag_t __oflags, int __sflags),_sopen,(__filename,__oflags,__sflags),__sflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#include <local/io/sopen.h>
#define __localdep_sopen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sopen))
#else /* CUSTOM: sopen */
#undef ____localdep_sopen_defined
#endif /* sopen... */
#endif /* !____localdep_sopen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_sopen_s) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_sopen_s))(__fd_t *__fd,
                                                      char const *__filename,
                                                      __oflag_t __oflags,
                                                      int __sflags,
                                                      __mode_t __mode) {
#line 228 "kos/src/libc/magic/io.c"
	__fd_t __result;
	if (!__fd) {
#ifdef __EINVAL
		return __EINVAL;
#else /* EINVAL */
		return 1;
#endif /* !EINVAL */
	}
	__result = __localdep_sopen(__filename, __oflags, __sflags, __mode);
	if (__result < 0) {
#ifdef __libc_geterrno
		return __libc_geterrno();
#else /* __libc_geterrno */
		return 1;
#endif /* !__libc_geterrno */
	}
	*__fd = __result;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE_open64 || __CRT_HAVE___open64 || (__CRT_AT_FDCWD && (__CRT_HAVE_openat || __CRT_HAVE_openat64)) || __CRT_HAVE_sopen || __CRT_HAVE__sopen */
#endif /* !__local__sopen_s_defined */
