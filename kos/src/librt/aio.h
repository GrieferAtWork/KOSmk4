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
#ifndef GUARD_LIBRT_AIO_H
#define GUARD_LIBRT_AIO_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <librt/aio.h>

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

DECL_BEGIN

/* Allow user to specify optimization */
INTDEF NONNULL((1)) void NOTHROW_NCX(CC librt_aio_init)(struct aioinit const *init);
/* Enqueue read request for given number of bytes and the given priority */
INTDEF NONNULL((1)) int NOTHROW_NCX(CC librt_aio_read)(struct __aiocb32 *aiocbp);
/* Enqueue write request for given number of bytes and the given priority */
INTDEF NONNULL((1)) int NOTHROW_NCX(CC librt_aio_write)(struct __aiocb32 *aiocbp);
/* Initiate list of I/O requests */
INTDEF NONNULL((2)) int NOTHROW_NCX(CC librt_lio_listio)(int mode, struct __aiocb32 *const list[__restrict_arr], __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig);
/* Retrieve error status associated with AIOCBP */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(CC librt_aio_error)(struct __aiocb32 const *aiocbp);
/* Return status associated with AIOCBP */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(CC librt_aio_return)(struct __aiocb32 *aiocbp);
/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
INTDEF int NOTHROW_NCX(CC librt_aio_cancel)(fd_t fildes, struct __aiocb32 *aiocbp);
/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTDEF NONNULL((1)) int NOTHROW_RPC(CC librt_aio_suspend)(struct __aiocb32 const *const list[], __STDC_INT_AS_SIZE_T nent, struct __timespec32 const *__restrict timeout);
/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
INTDEF NONNULL((2)) int NOTHROW_NCX(CC librt_aio_fsync)(int operation, struct __aiocb32 *aiocbp);
/* Enqueue read request for given number of bytes and the given priority */
INTDEF NONNULL((1)) int NOTHROW_NCX(CC librt_aio_read64)(struct __aiocb64 *aiocbp);
/* Enqueue write request for given number of bytes and the given priority */
INTDEF NONNULL((1)) int NOTHROW_NCX(CC librt_aio_write64)(struct __aiocb64 *aiocbp);
/* Initiate list of I/O requests */
INTDEF NONNULL((2)) int NOTHROW_NCX(CC librt_lio_listio64)(int mode, struct __aiocb64 *const list[__restrict_arr], __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig);
/* Retrieve error status associated with AIOCBP */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(CC librt_aio_error64)(struct __aiocb64 const *aiocbp);
/* Return status associated with AIOCBP */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(CC librt_aio_return64)(struct __aiocb64 *aiocbp);
/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
INTDEF int NOTHROW_NCX(CC librt_aio_cancel64)(fd_t fildes, struct __aiocb64 *aiocbp);
/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTDEF NONNULL((1)) int NOTHROW_RPC(CC librt_aio_suspend64)(struct __aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent, struct __timespec32 const *__restrict timeout);
/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
INTDEF NONNULL((2)) int NOTHROW_NCX(CC librt_aio_fsync64)(int operation, struct __aiocb64 *aiocbp);
/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTDEF NONNULL((1)) int NOTHROW_RPC(CC librt_aio_suspendt64)(struct __aiocb32 const *const list[], __STDC_INT_AS_SIZE_T nent, struct __timespec64 const *__restrict timeout);
/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTDEF NONNULL((1)) int NOTHROW_RPC(CC librt_aio_suspend64t64)(struct __aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent, struct __timespec64 const *__restrict timeout);


DECL_END

#endif /* !GUARD_LIBRT_AIO_H */
