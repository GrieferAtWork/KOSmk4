/* HASH CRC-32:0x959f97b9 */
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
#ifndef __local_Open64_defined
#define __local_Open64_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_Open32_defined) && defined(__CRT_HAVE_Open)
#define __local___localdep_Open32_defined
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__THROWING,__localdep_Open32,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t))
#endif /* !__local___localdep_Open32_defined && __CRT_HAVE_Open */
#ifndef __local___localdep_OpenAt64_defined
#define __local___localdep_OpenAt64_defined
#if defined(__CRT_HAVE_OpenAt) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(2),__fd_t,__THROWING,__localdep_OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(2),__fd_t,__THROWING,__localdep_OpenAt64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),OpenAt64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_OpenAt)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.fcntl/OpenAt64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_OpenAt64 __LIBC_LOCAL_NAME(OpenAt64)
#else /* ... */
#undef __local___localdep_OpenAt64_defined
#endif /* !... */
#endif /* !__local___localdep_OpenAt64_defined */
__LOCAL_LIBC(Open64) __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(Open64))(char const *__filename, __oflag_t __oflags, ...) __THROWS(...) {
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))
	__result = (__NAMESPACE_LOCAL_SYM __localdep_OpenAt64)(__AT_FDCWD, __filename, __oflags, __builtin_va_arg(__args, __mode_t));
#else /* __AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt) */
#ifdef __O_LARGEFILE
	__result = (__NAMESPACE_LOCAL_SYM __localdep_Open32)(__filename, __oflags | __O_LARGEFILE, __builtin_va_arg(__args, __mode_t));
#else /* __O_LARGEFILE */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_Open32)(__filename, __oflags, __builtin_va_arg(__args, __mode_t));
#endif /* !__O_LARGEFILE */
#endif /* !__AT_FDCWD || (!__CRT_HAVE_OpenAt64 && !__CRT_HAVE_OpenAt) */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Open64_defined
#define __local___localdep_Open64_defined
#define __localdep_Open64 __LIBC_LOCAL_NAME(Open64)
#endif /* !__local___localdep_Open64_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#undef __local_Open64_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_OpenAt64 && !__CRT_HAVE_OpenAt)) && !__CRT_HAVE_Open */
#endif /* !__local_Open64_defined */
