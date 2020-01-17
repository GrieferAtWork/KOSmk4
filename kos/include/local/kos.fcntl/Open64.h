/* HASH CRC-32:0xfa9ffd75 */
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
#ifndef __local_Open64_defined
#if (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64))) || defined(__CRT_HAVE_Open)
#define __local_Open64_defined 1
#include <kos/anno.h>
#include <bits/types.h>
#include <bits/types.h>
#include <bits/fcntl.h>
/* Dependency: "OpenAt64" from "kos.fcntl" */
#ifndef ____localdep_OpenAt64_defined
#define ____localdep_OpenAt64_defined 1
#ifdef __CRT_HAVE_OpenAt64
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,,__localdep_OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_OpenAt) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,,__localdep_OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_OpenAt)
#include <local/kos.fcntl/OpenAt64.h>
#define __localdep_OpenAt64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(OpenAt64))
#else /* CUSTOM: OpenAt64 */
#undef ____localdep_OpenAt64_defined
#endif /* OpenAt64... */
#endif /* !____localdep_OpenAt64_defined */

/* Dependency: "Open32" from "kos.fcntl" */
#ifndef ____localdep_Open32_defined
#define ____localdep_Open32_defined 1
#ifdef __CRT_HAVE_Open
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open32,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#else /* LIBC: Open */
#undef ____localdep_Open32_defined
#endif /* Open32... */
#endif /* !____localdep_Open32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(Open64) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(Open64))(char const *__filename,
                                        __oflag_t __oflags,
                                        ...) __THROWS(...) {
#line 75 "kos/src/libc/magic/kos.fcntl.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64)
	__result = __localdep_OpenAt64(__CRT_AT_FDCWD, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
#else /* __CRT_AT_FDCWD && OpenAt64... */
#ifdef __O_LARGEFILE
	__result = __localdep_Open32(__filename, __oflags|__O_LARGEFILE, __builtin_va_arg(__args, __mode_t));
#else /* __O_LARGEFILE */
	__result = __localdep_Open32(__filename, __oflags, __builtin_va_arg(__args, __mode_t));
#endif /* !__O_LARGEFILE */
#endif /* !__CRT_AT_FDCWD || !OpenAt64... */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_AT_FDCWD && (__CRT_HAVE_OpenAt || __CRT_HAVE_OpenAt64)) || __CRT_HAVE_Open */
#endif /* !__local_Open64_defined */
