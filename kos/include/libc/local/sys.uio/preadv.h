/* HASH CRC-32:0xb7fc81bb */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_preadv_defined
#define __local_preadv_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_preadv64) || defined(__CRT_HAVE_preadv)
#include <features.h>
#include <bits/iovec-struct.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: preadv32 from sys.uio */
#if !defined(__local___localdep_preadv32_defined) && defined(__CRT_HAVE_preadv)
#define __local___localdep_preadv32_defined 1
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadv32,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off32_t __offset),preadv,(__fd,__iov,__count,__offset))
#endif /* !__local___localdep_preadv32_defined && __CRT_HAVE_preadv */
/* Dependency: preadv64 from sys.uio */
#ifndef __local___localdep_preadv64_defined
#define __local___localdep_preadv64_defined 1
#ifdef __CRT_HAVE_preadv64
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadv64,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),preadv64,(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_preadv) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadv64,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),preadv,(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_preadv)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.uio/preadv64.h>
__NAMESPACE_LOCAL_BEGIN
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
#define __localdep_preadv64 __LIBC_LOCAL_NAME(preadv64)
#else /* ... */
#undef __local___localdep_preadv64_defined
#endif /* !... */
#endif /* !__local___localdep_preadv64_defined */
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__LOCAL_LIBC(preadv) __ATTR_WUNUSED __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(preadv))(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset) {

	return __localdep_preadv64(__fd, __iov, __count, (__off64_t)__offset);



}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_preadv_defined
#define __local___localdep_preadv_defined 1
#define __localdep_preadv __LIBC_LOCAL_NAME(preadv)
#endif /* !__local___localdep_preadv_defined */
#else /* __CRT_HAVE_preadv64 || __CRT_HAVE_preadv */
#undef __local_preadv_defined
#endif /* !__CRT_HAVE_preadv64 && !__CRT_HAVE_preadv */
#endif /* !__local_preadv_defined */
