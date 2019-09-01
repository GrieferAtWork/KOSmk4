/* HASH 0xda9b0096 */
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
#ifndef __local_Open_defined
#if (defined(__CRT_HAVE_Open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64))))
#define __local_Open_defined 1
#include <kos/anno.h>
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "Open64" from "kos.fcntl" */
#ifndef ____localdep_Open64_defined
#define ____localdep_Open64_defined 1
#if defined(__CRT_HAVE_Open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open64,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_Open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open64,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_Open)
#include <local/kos.fcntl/Open64.h>
#define __localdep_Open64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open64))
#else /* CUSTOM: Open64 */
#undef ____localdep_Open64_defined
#endif /* Open64... */
#endif /* !____localdep_Open64_defined */

/* Dependency: "OpenAt" from "kos.fcntl" */
#ifndef ____localdep_OpenAt_defined
#define ____localdep_OpenAt_defined 1
#if defined(__CRT_HAVE_Openat64) && (defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,,__localdep_OpenAt,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),Openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_OpenAt) && (!defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,,__localdep_OpenAt,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_OpenAt64)
#include <local/kos.fcntl/OpenAt.h>
#define __localdep_OpenAt (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(OpenAt))
#else /* CUSTOM: OpenAt */
#undef ____localdep_OpenAt_defined
#endif /* OpenAt... */
#endif /* !____localdep_OpenAt_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(Open) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(Open))(char const *__filename,
                                      __oflag_t __oflags,
                                      ...) __THROWS(...) {
#line 41 "kos/src/libc/magic/kos.fcntl.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#ifdef __CRT_HAVE_Open64
	__result = __localdep_Open64(__filename, __oflags, __builtin_va_arg(__args, __mode_t));
#else /* __CRT_HAVE_Open64 */
	__result = __localdep_OpenAt(__CRT_AT_FDCWD, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
#endif /* !__CRT_HAVE_Open64 */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_Open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64)))) */
#endif /* !__local_Open_defined */
