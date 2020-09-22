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
#ifndef _LIBRT_AIO_H
#define _LIBRT_AIO_H 1

#include "api.h"
/**/

#include <__crt.h>

#include <bits/os/timespec.h>
#include <bits/sigevent.h>
#include <bits/types.h>

#include <librt/asm/aio.h>
#include <librt/bits/aiocb.h>
#include <librt/bits/aioinit.h>

/* Documentation derived from Glibc /usr/include/aio.h */
/* Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>. */

#ifdef __CC__
__DECL_BEGIN

/* Allow user to specify optimization */
typedef __ATTR_NONNULL((1)) void
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_INIT)(struct aioinit const *__init);

/* Enqueue read request for given number of bytes and the given priority */
typedef __ATTR_NONNULL((1)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_READ)(struct __aiocb32 *__aiocbp);

/* Enqueue write request for given number of bytes and the given priority */
typedef __ATTR_NONNULL((1)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_WRITE)(struct __aiocb32 *__aiocbp);

/* Initiate list of I/O requests */
typedef __ATTR_NONNULL((2)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PLIO_LISTIO)(int __mode, struct __aiocb32 *const __list[__restrict_arr],
                                           __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig);

/* Retrieve error status associated with AIOCBP */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_ERROR)(struct __aiocb32 const *__aiocbp);

/* Return status associated with AIOCBP */
typedef __ATTR_NONNULL((1)) __ssize_t
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_RETURN)(struct __aiocb32 *__aiocbp);

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
typedef int /*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_CANCEL)(__fd_t __fildes, struct __aiocb32 *__aiocbp);

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
typedef __ATTR_NONNULL((1)) int
/*__NOTHROW_RPC*/(__LIBRT_CC *PAIO_SUSPEND)(struct __aiocb32 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                            struct __timespec32 const *__restrict __timeout);

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
typedef __ATTR_NONNULL((2)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_FSYNC)(int __operation, struct __aiocb32 *__aiocbp);

/* Enqueue read request for given number of bytes and the given priority */
typedef __ATTR_NONNULL((1)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_READ64)(struct __aiocb64 *__aiocbp);

/* Enqueue write request for given number of bytes and the given priority */
typedef __ATTR_NONNULL((1)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_WRITE64)(struct __aiocb64 *__aiocbp);

/* Initiate list of I/O requests */
typedef __ATTR_NONNULL((2)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PLIO_LISTIO64)(int __mode, struct __aiocb64 *const __list[__restrict_arr],
                                             __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig);

/* Retrieve error status associated with AIOCBP */
typedef __ATTR_WUNUSED __ATTR_NONNULL((1)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_ERROR64)(struct __aiocb64 const *__aiocbp);

/* Return status associated with AIOCBP */
typedef __ATTR_NONNULL((1)) __ssize_t
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_RETURN64)(struct __aiocb64 *__aiocbp);

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
typedef int /*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_CANCEL64)(__fd_t __fildes, struct __aiocb64 *__aiocbp);

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
typedef __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC *PAIO_SUSPEND64)(struct __aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                          struct __timespec32 const *__restrict __timeout);

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
typedef __ATTR_NONNULL((2)) int
/*__NOTHROW_NCX*/(__LIBRT_CC *PAIO_FSYNC64)(int __operation, struct __aiocb64 *__aiocbp);

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
typedef __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC *PAIO_SUSPENDT64)(struct __aiocb32 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                           struct __timespec64 const *__restrict __timeout);

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
typedef __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC *PAIO_SUSPEND64T64)(struct __aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                             struct __timespec64 const *__restrict __timeout);



#ifdef LIBRT_WANT_PROTOTYPES
/* Allow user to specify optimization */
#ifndef __aio_init_defined
#define __aio_init_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBRT_CC aio_init)(struct aioinit const *__init);
#endif /* !__aio_init_defined */

/* Enqueue read request for given number of bytes and the given priority */
#ifndef __aio_read_defined
#define __aio_read_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_read)(struct __aiocb32 *__aiocbp);
#endif /* !__aio_read_defined */

/* Enqueue write request for given number of bytes and the given priority */
#ifndef __aio_write_defined
#define __aio_write_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_write)(struct __aiocb32 *__aiocbp);
#endif /* !__aio_write_defined */

/* Initiate list of I/O requests */
#ifndef __lio_listio_defined
#define __lio_listio_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC lio_listio)(int __mode, struct __aiocb32 *const __list[__restrict_arr],
                                     __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig);
#endif /* !__lio_listio_defined */

/* Retrieve error status associated with AIOCBP */
#ifndef __aio_error_defined
#define __aio_error_defined 1
__LIBRT_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_error)(struct __aiocb32 const *__aiocbp);
#endif /* !__aio_error_defined */

/* Return status associated with AIOCBP */
#ifndef __aio_return_defined
#define __aio_return_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(__LIBRT_CC aio_return)(struct __aiocb32 *__aiocbp);
#endif /* !__aio_return_defined */

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
#ifndef __aio_cancel_defined
#define __aio_cancel_defined 1
__LIBRT_DECL int __NOTHROW_NCX(__LIBRT_CC aio_cancel)(__fd_t __fildes, struct __aiocb32 *__aiocbp);
#endif /* !__aio_cancel_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspend_defined
#define __aio_suspend_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspend)(struct __aiocb32 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                      struct __timespec32 const *__restrict __timeout);
#endif /* !__aio_suspend_defined */

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
#ifndef __aio_fsync_defined
#define __aio_fsync_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC aio_fsync)(int __operation, struct __aiocb32 *__aiocbp);
#endif /* !__aio_fsync_defined */

/* Enqueue read request for given number of bytes and the given priority */
#ifndef __aio_read64_defined
#define __aio_read64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_read64)(struct __aiocb64 *__aiocbp);
#endif /* !__aio_read64_defined */

/* Enqueue write request for given number of bytes and the given priority */
#ifndef __aio_write64_defined
#define __aio_write64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_write64)(struct __aiocb64 *__aiocbp);
#endif /* !__aio_write64_defined */

/* Initiate list of I/O requests */
#ifndef __lio_listio64_defined
#define __lio_listio64_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC lio_listio64)(int __mode, struct __aiocb64 *const __list[__restrict_arr],
                                       __STDC_INT_AS_SIZE_T __nent, struct sigevent *__restrict __sig);
#endif /* !__lio_listio64_defined */

/* Retrieve error status associated with AIOCBP */
#ifndef __aio_error64_defined
#define __aio_error64_defined 1
__LIBRT_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC aio_error64)(struct __aiocb64 const *__aiocbp);
#endif /* !__aio_error64_defined */

/* Return status associated with AIOCBP */
#ifndef __aio_return64_defined
#define __aio_return64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) __ssize_t
__NOTHROW_NCX(__LIBRT_CC aio_return64)(struct __aiocb64 *__aiocbp);
#endif /* !__aio_return64_defined */

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
#ifndef __aio_cancel64_defined
#define __aio_cancel64_defined 1
__LIBRT_DECL int
__NOTHROW_NCX(__LIBRT_CC aio_cancel64)(__fd_t __fildes, struct __aiocb64 *__aiocbp);
#endif /* !__aio_cancel64_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspend64_defined
#define __aio_suspend64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspend64)(struct __aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                        struct __timespec32 const *__restrict __timeout);
#endif /* !__aio_suspend64_defined */

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
#ifndef __aio_fsync64_defined
#define __aio_fsync64_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC aio_fsync64)(int __operation, struct __aiocb64 *__aiocbp);
#endif /* !__aio_fsync64_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspendt64_defined
#define __aio_suspendt64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspendt64)(struct __aiocb32 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                         struct __timespec64 const *__restrict __timeout);
#endif /* !__aio_suspendt64_defined */

/* Suspend calling thread until at least one of the asynchronous
 * I/O operations referenced by LIST has completed. */
#ifndef __aio_suspend64t64_defined
#define __aio_suspend64t64_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBRT_CC aio_suspend64t64)(struct __aiocb64 const *const __list[], __STDC_INT_AS_SIZE_T __nent,
                                           struct __timespec64 const *__restrict __timeout);
#endif /* !__aio_suspend64t64_defined */
#endif /* LIBRT_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBRT_AIO_H */
