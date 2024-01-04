/* HASH CRC-32:0x413735c9 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_readlink_defined
#define __local_readlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_readlinkat) || defined(__CRT_HAVE_freadlinkat))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_readlinkat_defined
#define __local___localdep_readlinkat_defined
#ifdef __CRT_HAVE_readlinkat
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_OUTS(3, 4),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_readlinkat,(__fd_t __dfd, char const *__path, char *__buf, __SIZE_TYPE__ __buflen),readlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_freadlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/readlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_readlinkat __LIBC_LOCAL_NAME(readlinkat)
#else /* ... */
#undef __local___localdep_readlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_readlinkat_defined */
__LOCAL_LIBC(readlink) __ATTR_IN(1) __ATTR_OUTS(2, 3) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(readlink))(char const *__path, char *__buf, __SIZE_TYPE__ __buflen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_readlinkat)(__AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_readlink_defined
#define __local___localdep_readlink_defined
#define __localdep_readlink __LIBC_LOCAL_NAME(readlink)
#endif /* !__local___localdep_readlink_defined */
#else /* __AT_FDCWD && (__CRT_HAVE_readlinkat || __CRT_HAVE_freadlinkat) */
#undef __local_readlink_defined
#endif /* !__AT_FDCWD || (!__CRT_HAVE_readlinkat && !__CRT_HAVE_freadlinkat) */
#endif /* !__local_readlink_defined */
