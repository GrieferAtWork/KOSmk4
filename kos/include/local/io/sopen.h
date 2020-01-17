/* HASH CRC-32:0xf8d550e0 */
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
#ifndef __local_sopen_defined
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64))) || (defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE__open)
#define __local_sopen_defined 1
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "open" from "fcntl" */
#ifndef ____localdep_open_defined
#define ____localdep_open_defined 1
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat) || defined(__CRT_HAVE_openat64)))
#include <local/fcntl/open.h>
#define __localdep_open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))
#else /* CUSTOM: open */
#undef ____localdep_open_defined
#endif /* open... */
#endif /* !____localdep_open_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sopen) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(sopen))(char const *__filename,
                                                    __oflag_t __oflags,
                                                    int __sflags,
                                                    ...) {
#line 325 "kos/src/libc/magic/io.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __sflags);
	(void)__sflags;
	__result = __localdep_open(__filename, __oflags, __builtin_va_arg(__args, __mode_t));
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || (__CRT_AT_FDCWD && (__CRT_HAVE_openat || __CRT_HAVE_openat64)) || (__CRT_HAVE_open && !__USE_FILE_OFFSET64) || __CRT_HAVE___open || __CRT_HAVE__open */
#endif /* !__local_sopen_defined */
