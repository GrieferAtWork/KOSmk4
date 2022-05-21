/* HASH CRC-32:0x71d630bc */
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
#ifndef __local_readlinkat_defined
#define __local_readlinkat_defined
#include <__crt.h>
#ifdef __CRT_HAVE_freadlinkat
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_freadlinkat_defined
#define __local___localdep_freadlinkat_defined
__CREDIRECT(__ATTR_ACCESS_WRS(3, 4) __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_freadlinkat,(__fd_t __dfd, char const *__path, char *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags),freadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#endif /* !__local___localdep_freadlinkat_defined */
__LOCAL_LIBC(readlinkat) __ATTR_ACCESS_WRS(3, 4) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(readlinkat))(__fd_t __dfd, char const *__path, char *__buf, __SIZE_TYPE__ __buflen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_freadlinkat)(__dfd, __path, __buf, __buflen, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_readlinkat_defined
#define __local___localdep_readlinkat_defined
#define __localdep_readlinkat __LIBC_LOCAL_NAME(readlinkat)
#endif /* !__local___localdep_readlinkat_defined */
#else /* __CRT_HAVE_freadlinkat */
#undef __local_readlinkat_defined
#endif /* !__CRT_HAVE_freadlinkat */
#endif /* !__local_readlinkat_defined */
