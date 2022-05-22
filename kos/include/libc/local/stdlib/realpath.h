/* HASH CRC-32:0x4e9d1825 */
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
#ifndef __local_realpath_defined
#define __local_realpath_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_frealpathat)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_frealpathat_defined
#define __local___localdep_frealpathat_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(2) __ATTR_OUT_OPT(3),char *,__NOTHROW_RPC,__localdep_frealpathat,(__fd_t __dirfd, char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),frealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#endif /* !__local___localdep_frealpathat_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/limits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(realpath) __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(realpath))(char const *__filename, char *__resolved) {
#if defined(__PATH_MAX) && __PATH_MAX != -1
	return (__NAMESPACE_LOCAL_SYM __localdep_frealpathat)(__AT_FDCWD, __filename, __resolved, __resolved ? __PATH_MAX : 0, 0);
#else /* __PATH_MAX && __PATH_MAX != -1 */
	return (__NAMESPACE_LOCAL_SYM __localdep_frealpathat)(__AT_FDCWD, __filename, __resolved, __resolved ? 256 : 0, 0);
#endif /* !__PATH_MAX || __PATH_MAX == -1 */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_realpath_defined
#define __local___localdep_realpath_defined
#define __localdep_realpath __LIBC_LOCAL_NAME(realpath)
#endif /* !__local___localdep_realpath_defined */
#else /* __AT_FDCWD && __CRT_HAVE_frealpathat */
#undef __local_realpath_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_frealpathat */
#endif /* !__local_realpath_defined */
