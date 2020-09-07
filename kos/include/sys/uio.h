/* HASH CRC-32:0xc883bbbf */
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
#ifndef _SYS_UIO_H
#define _SYS_UIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/limits.h> /* __IOV_MAX */
#include <bits/iovec-struct.h>
#include <bits/types.h>
#include <sys/types.h>

#ifndef UIO_MAXIOV
#if !defined(__IOV_MAX) || (__IOV_MAX == -1)
#define UIO_MAXIOV 16
#else /* !__IOV_MAX || __IOV_MAX == -1 */
#define UIO_MAXIOV __IOV_MAX
#endif /* __IOV_MAX && __IOV_MAX != -1 */
#endif /* !UIO_MAXIOV */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */


#ifdef __USE_GNU
/* >> process_vm_readv(2)
 * Read memory from another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of read bytes */
__CDECLARE_OPT(__ATTR_WUNUSED,ssize_t,__NOTHROW_RPC,process_vm_readv,(__pid_t __pid, struct iovec const *__local_iov, __ULONGPTR_TYPE__ __liovcnt, struct iovec const *__remote_iov, __ULONGPTR_TYPE__ __riovcnt, __ULONGPTR_TYPE__ __flags),(__pid,__local_iov,__liovcnt,__remote_iov,__riovcnt,__flags))
/* >> process_vm_writev(2)
 * Write memory to another process's VM
 * @param: flags: Must be `0'
 * @return: * :   The actual number of written bytes */
__CDECLARE_OPT(,ssize_t,__NOTHROW_RPC,process_vm_writev,(__pid_t __pid, struct iovec const *__local_iov, __ULONGPTR_TYPE__ __liovcnt, struct iovec const *__remote_iov, __ULONGPTR_TYPE__ __riovcnt, __ULONGPTR_TYPE__ __flags),(__pid,__local_iov,__liovcnt,__remote_iov,__riovcnt,__flags))
#endif /* __USE_GNU */

/* >> readv(2)
 * Same as `read(2)', but rather than specifying a single, continuous buffer,
 * read data into `count' seperate buffers, though still return the actual
 * number of read bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only read as much data as was
 * available at the time the call was made, and throw E_WOULDBLOCK if no data
 * was available at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes
 * @return: 0                     : EOF */
__CDECLARE_OPT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,readv,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count),(__fd,__iov,__count))
/* >> writev(2)
 * Same as `write(2)', but rather than specifying a single, continuous buffer,
 * write data from `count' seperate buffers, though still return the actual
 * number of written bytes.
 * When `fd' has the `O_NONBLOCK' flag set, only write as much data
 * as possible at the time the call was made, and throw E_WOULDBLOCK
 * if no data could be written at the time.
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes
 * @return: 0                     : No more data can be written */
__CDECLARE_OPT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,writev,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count),(__fd,__iov,__count))

#ifdef __USE_MISC
#if defined(__CRT_HAVE_preadv64) && defined(__USE_FILE_OFFSET64)
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadv,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset),preadv64,(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_preadv) && !defined(__USE_FILE_OFFSET64)
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadv,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset),(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_preadv64) || defined(__CRT_HAVE_preadv)
#include <libc/local/sys.uio/preadv.h>
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(preadv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL preadv)(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadv))(__fd, __iov, __count, __offset); })
#endif /* ... */
#if defined(__CRT_HAVE_pwritev64) && defined(__USE_FILE_OFFSET64)
/* >> pwritev(2)
 * Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwritev,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset),pwritev64,(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_pwritev) && !defined(__USE_FILE_OFFSET64)
/* >> pwritev(2)
 * Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwritev,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset),(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_pwritev64) || defined(__CRT_HAVE_pwritev)
#include <libc/local/sys.uio/pwritev.h>
/* >> pwritev(2)
 * Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwritev, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pwritev)(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __FS_TYPE(off) __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwritev))(__fd, __iov, __count, __offset); })
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_preadv64
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadv64,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_preadv) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,preadv64,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),preadv,(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_preadv)
#include <libc/local/sys.uio/preadv64.h>
/* >> preadv(2)
 * Same as `readv(2)', but read data from a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of read bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(preadv64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL preadv64)(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadv64))(__fd, __iov, __count, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE_pwritev64
/* >> pwritev(2)
 * Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__CDECLARE(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwritev64,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_pwritev) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* >> pwritev(2)
 * Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__CREDIRECT(__ATTR_NONNULL((2)),ssize_t,__NOTHROW_RPC,pwritev64,(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),pwritev,(__fd,__iov,__count,__offset))
#elif defined(__CRT_HAVE_pwritev)
#include <libc/local/sys.uio/pwritev64.h>
/* >> pwritev(2)
 * Same as `writev(2)', but write data to a file at a
 * specific `offset', rather than the current R/W position
 * @return: <= SUM(iov[*].iov_len): The actual amount of written bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(pwritev64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((2)) ssize_t __NOTHROW_RPC(__LIBCCALL pwritev64)(__fd_t __fd, struct iovec const *__iov, __STDC_INT_AS_SIZE_T __count, __off64_t __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pwritev64))(__fd, __iov, __count, __offset); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* !__USE_MISC */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_UIO_H */
