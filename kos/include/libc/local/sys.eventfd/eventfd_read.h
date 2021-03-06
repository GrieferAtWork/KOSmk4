/* HASH CRC-32:0xf7fee902 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_eventfd_read_defined
#define __local_eventfd_read_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: read from unistd */
#ifndef __local___localdep_read_defined
#define __local___localdep_read_defined 1
#ifdef __CRT_HAVE_read
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read up to `bufsize' bytes from `fd' into `buf'
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= bufsize: The actual amount of read bytes
 * @return: 0         : EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_read_defined
#endif /* !... */
#endif /* !__local___localdep_read_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* >> eventfd_read(3)
 * Read the event counter, and (if not `O_NONBLOCK'), wait for an event to happen */
__LOCAL_LIBC(eventfd_read) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(eventfd_read))(__fd_t __fd, __UINT64_TYPE__ *__value) {
	__SSIZE_TYPE__ __error;
	__error = __localdep_read(__fd, __value, sizeof(__UINT64_TYPE__));
	if (__error == sizeof(__UINT64_TYPE__))
		return 0;
#ifdef __EINVAL
	if (__error >= 0)
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_eventfd_read_defined
#define __local___localdep_eventfd_read_defined 1
#define __localdep_eventfd_read __LIBC_LOCAL_NAME(eventfd_read)
#endif /* !__local___localdep_eventfd_read_defined */
#else /* __CRT_HAVE_read || __CRT_HAVE__read || __CRT_HAVE___read */
#undef __local_eventfd_read_defined
#endif /* !__CRT_HAVE_read && !__CRT_HAVE__read && !__CRT_HAVE___read */
#endif /* !__local_eventfd_read_defined */
