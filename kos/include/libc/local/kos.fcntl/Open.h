/* HASH CRC-32:0x383d4499 */
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
#ifndef __local_Open_defined
#define __local_Open_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <features.h>
#if defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Open64_defined
#define __local___localdep_Open64_defined
#if defined(__CRT_HAVE_Open) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),__localdep_Open64,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_Open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__THROWING(...),__localdep_Open64,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.fcntl/Open64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_Open64 __LIBC_LOCAL_NAME(Open64)
#else /* ... */
#undef __local___localdep_Open64_defined
#endif /* !... */
#endif /* !__local___localdep_Open64_defined */
#ifndef __local___localdep_OpenAt_defined
#define __local___localdep_OpenAt_defined
#if defined(__CRT_HAVE_OpenAt) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),__localdep_OpenAt,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt64) && (defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(2),__fd_t,__THROWING(...),__localdep_OpenAt,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.fcntl/OpenAt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_OpenAt __LIBC_LOCAL_NAME(OpenAt)
#else /* ... */
#undef __local___localdep_OpenAt_defined
#endif /* !... */
#endif /* !__local___localdep_OpenAt_defined */
__LOCAL_LIBC(Open) __ATTR_WUNUSED __ATTR_IN(1) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(Open))(char const *__filename, __oflag_t __oflags, ...) __THROWS(...) {
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);

	__result = (__NAMESPACE_LOCAL_SYM __localdep_Open64)(__filename, __oflags, __builtin_va_arg(__args, __mode_t));



	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Open_defined
#define __local___localdep_Open_defined
#define __localdep_Open __LIBC_LOCAL_NAME(Open)
#endif /* !__local___localdep_Open_defined */
#else /* __CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#undef __local_Open_defined
#endif /* !__CRT_HAVE_Open64 && (!__AT_FDCWD || (!__CRT_HAVE_OpenAt64 && !__CRT_HAVE_OpenAt)) && !__CRT_HAVE_Open */
#endif /* !__local_Open_defined */
