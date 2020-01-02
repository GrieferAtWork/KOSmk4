/* HASH CRC-32:0xcf8888ce */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_OpenAt64_defined
#ifdef __CRT_HAVE_OpenAt
#define __local_OpenAt64_defined 1
#include <kos/anno.h>
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "OpenAt32" from "kos.fcntl" */
#ifndef ____localdep_OpenAt32_defined
#define ____localdep_OpenAt32_defined 1
#ifdef __CRT_HAVE_OpenAt
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,__localdep_OpenAt32,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#else /* LIBC: OpenAt */
#undef ____localdep_OpenAt32_defined
#endif /* OpenAt32... */
#endif /* !____localdep_OpenAt32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(OpenAt64) __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(OpenAt64))(__fd_t __dirfd,
                                          char const *__filename,
                                          __oflag_t __oflags,
                                          ...) __THROWS(...) {
#line 128 "kos/src/libc/magic/kos.fcntl.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#ifdef __O_LARGEFILE
	__result = __localdep_OpenAt32(__dirfd, __filename, __oflags|__O_LARGEFILE, __builtin_va_arg(__args, __mode_t));
#else /* __O_LARGEFILE */
	__result = __localdep_OpenAt32(__dirfd, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
#endif /* !__O_LARGEFILE */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_OpenAt */
#endif /* !__local_OpenAt64_defined */
