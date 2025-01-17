/* HASH CRC-32:0xa59bbddb */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_OpenAt_defined
#define __local_OpenAt_defined
#include <__crt.h>
#include <asm/os/oflags.h>
#if defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_OpenAt32_defined) && defined(__CRT_HAVE_OpenAt)
#define __local___localdep_OpenAt32_defined
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),__localdep_OpenAt32,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#endif /* !__local___localdep_OpenAt32_defined && __CRT_HAVE_OpenAt */
#ifndef __local___localdep_OpenAt64_defined
#define __local___localdep_OpenAt64_defined
#if defined(__CRT_HAVE_OpenAt) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),__localdep_OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),__localdep_OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.fcntl/OpenAt64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_OpenAt64 __LIBC_LOCAL_NAME(OpenAt64)
#else /* ... */
#undef __local___localdep_OpenAt64_defined
#endif /* !... */
#endif /* !__local___localdep_OpenAt64_defined */
__LOCAL_LIBC(OpenAt) __ATTR_WUNUSED __ATTR_IN(2) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(OpenAt))(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __THROWS(...) {
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);

	__result = (__NAMESPACE_LOCAL_SYM __localdep_OpenAt64)(__dirfd, __filename, __oflags, __builtin_va_arg(__args, __mode_t));



	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_OpenAt_defined
#define __local___localdep_OpenAt_defined
#define __localdep_OpenAt __LIBC_LOCAL_NAME(OpenAt)
#endif /* !__local___localdep_OpenAt_defined */
#else /* __CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt */
#undef __local_OpenAt_defined
#endif /* !__CRT_HAVE_OpenAt64 && !__CRT_HAVE_OpenAt */
#endif /* !__local_OpenAt_defined */
