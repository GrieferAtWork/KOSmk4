/* HASH CRC-32:0x18c35eff */
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
#ifndef __local_eventfd_write_defined
#define __local_eventfd_write_defined
#include <__crt.h>
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_write_defined
#define __local___localdep_write_defined
#ifdef __CRT_HAVE_write
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___libc_write)
__CREDIRECT(__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__libc_write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(eventfd_write) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(eventfd_write))(__fd_t __fd, __UINT64_TYPE__ ___value) {
	__SSIZE_TYPE__ __error;
	__error = (__NAMESPACE_LOCAL_SYM __localdep_write)(__fd, &___value, sizeof(__UINT64_TYPE__));
	if (__error == sizeof(__UINT64_TYPE__))
		return 0;
#ifdef __EINVAL
	if (__error >= 0)
		(void)__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_eventfd_write_defined
#define __local___localdep_eventfd_write_defined
#define __localdep_eventfd_write __LIBC_LOCAL_NAME(eventfd_write)
#endif /* !__local___localdep_eventfd_write_defined */
#else /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
#undef __local_eventfd_write_defined
#endif /* !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write */
#endif /* !__local_eventfd_write_defined */
