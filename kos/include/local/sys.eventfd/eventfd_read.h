/* HASH CRC-32:0x36a87c20 */
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
#ifndef __local_eventfd_read_defined
#if (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read))
#define __local_eventfd_read_defined 1
#include <parts/errno.h>
/* Dependency: "read" */
#ifndef ____localdep_read_defined
#define ____localdep_read_defined 1
#if defined(__CRT_HAVE_read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),_read,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___read)
/* >> read(2)
 * Read data from a given file descriptor `FD' and return the number of bytes read.
 * A return value of ZERO(0) is indicative of EOF */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_read,(__fd_t __fd, void *__buf, __SIZE_TYPE__ __bufsize),__read,(__fd,__buf,__bufsize))
#else /* LIBC: read */
#undef ____localdep_read_defined
#endif /* read... */
#endif /* !____localdep_read_defined */

__NAMESPACE_LOCAL_BEGIN
/* Read event counter and possibly wait for events */
__LOCAL_LIBC(eventfd_read) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(eventfd_read))(__fd_t __fd,
                                                          eventfd_t *__value) {
#line 67 "kos/src/libc/magic/sys.eventfd.c"
	__SSIZE_TYPE__ __error;
	__error = __localdep_read(__fd, __value, sizeof(__eventfd_t));
	if (__error == sizeof(__eventfd_t))
		return 0;
#ifdef __EINVAL
	if (__error >= 0)
		__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
	return -1;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_read) || defined(__CRT_HAVE__read) || defined(__CRT_HAVE___read)) */
#endif /* !__local_eventfd_read_defined */
