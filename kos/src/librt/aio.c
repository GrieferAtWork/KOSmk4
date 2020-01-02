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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBRT_AIO_C
#define GUARD_LIBRT_AIO_C 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <errno.h>

#include <librt/aio.h>

#include "aio.h"

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
INTERN NONNULL((1)) void
NOTHROW_NCX(CC librt_aio_init)(struct aioinit const *init) {
	/* TODO */
	(void)init;
	COMPILER_IMPURE();
}

/* Enqueue read request for given number of bytes and the given priority */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC librt_aio_read)(struct aiocb32 *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Enqueue write request for given number of bytes and the given priority */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC librt_aio_write)(struct aiocb32 *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Initiate list of I/O requests */
INTERN NONNULL((2)) int
NOTHROW_NCX(CC librt_lio_listio)(int mode, struct aiocb32 *const list[__restrict_arr],
                                 __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig) {
	/* TODO */
	(void)mode;
	(void)list;
	(void)nent;
	(void)sig;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Retrieve error status associated with AIOCBP */
INTERN WUNUSED NONNULL((1)) int
NOTHROW_NCX(CC librt_aio_error)(struct aiocb32 const *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Return status associated with AIOCBP */
INTERN NONNULL((1)) ssize_t
NOTHROW_NCX(CC librt_aio_return)(struct aiocb32 *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
INTERN int
NOTHROW_NCX(CC librt_aio_cancel)(fd_t fildes, struct aiocb32 *aiocbp) {
	/* TODO */
	(void)fildes;
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTERN NONNULL((1)) int
NOTHROW_RPC(CC librt_aio_suspend)(struct aiocb32 const *const list[], __STDC_INT_AS_SIZE_T nent,
                                  struct timespec32 const *__restrict timeout) {
	/* TODO */
	(void)list;
	(void)nent;
	(void)timeout;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
INTERN NONNULL((2)) int
NOTHROW_NCX(CC librt_aio_fsync)(int operation, struct aiocb32 *aiocbp) {
	/* TODO */
	(void)operation;
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Enqueue read request for given number of bytes and the given priority */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC librt_aio_read64)(struct aiocb64 *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Enqueue write request for given number of bytes and the given priority */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC librt_aio_write64)(struct aiocb64 *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Initiate list of I/O requests */
INTERN NONNULL((2)) int
NOTHROW_NCX(CC librt_lio_listio64)(int mode, struct aiocb64 *const list[__restrict_arr],
                                   __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig) {
	/* TODO */
	(void)mode;
	(void)list;
	(void)nent;
	(void)sig;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Retrieve error status associated with AIOCBP */
INTERN WUNUSED NONNULL((1)) int
NOTHROW_NCX(CC librt_aio_error64)(struct aiocb64 const *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Return status associated with AIOCBP */
INTERN NONNULL((1)) ssize_t
NOTHROW_NCX(CC librt_aio_return64)(struct aiocb64 *aiocbp) {
	/* TODO */
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Try to cancel asynchronous I/O requests outstanding against file descriptor FILDES */
INTERN int
NOTHROW_NCX(CC librt_aio_cancel64)(fd_t fildes, struct aiocb64 *aiocbp) {
	/* TODO */
	(void)fildes;
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTERN NONNULL((1)) int
NOTHROW_RPC(CC librt_aio_suspend64)(struct aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent,
                                    struct timespec32 const *__restrict timeout) {
	/* TODO */
	(void)list;
	(void)nent;
	(void)timeout;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Force all operations associated with file descriptor described by `aio_fildes' member of AIOCBP. */
INTERN NONNULL((2)) int
NOTHROW_NCX(CC librt_aio_fsync64)(int operation, struct aiocb64 *aiocbp) {
	/* TODO */
	(void)operation;
	(void)aiocbp;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTERN NONNULL((1)) int
NOTHROW_RPC(CC librt_aio_suspendt64)(struct aiocb32 const *const list[], __STDC_INT_AS_SIZE_T nent,
                                     struct timespec64 const *__restrict timeout) {
	/* TODO */
	(void)list;
	(void)nent;
	(void)timeout;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}

/* Suspend calling thread until at least one of the asynchronous I/O operations referenced by LIST has completed. */
INTERN NONNULL((1)) int
NOTHROW_RPC(CC librt_aio_suspend64t64)(struct aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent,
                                       struct timespec64 const *__restrict timeout) {
	/* TODO */
	(void)list;
	(void)nent;
	(void)timeout;
	COMPILER_IMPURE();
	errno = ENOSYS;
	return -1;
}





DEFINE_PUBLIC_ALIAS(aio_init, librt_aio_init);
DEFINE_PUBLIC_ALIAS(aio_read, librt_aio_read);
DEFINE_PUBLIC_ALIAS(aio_write, librt_aio_write);
DEFINE_PUBLIC_ALIAS(lio_listio, librt_lio_listio);
DEFINE_PUBLIC_ALIAS(aio_error, librt_aio_error);
DEFINE_PUBLIC_ALIAS(aio_return, librt_aio_return);
DEFINE_PUBLIC_ALIAS(aio_cancel, librt_aio_cancel);
DEFINE_PUBLIC_ALIAS(aio_suspend, librt_aio_suspend);
DEFINE_PUBLIC_ALIAS(aio_fsync, librt_aio_fsync);
DEFINE_PUBLIC_ALIAS(aio_read64, librt_aio_read64);
DEFINE_PUBLIC_ALIAS(aio_write64, librt_aio_write64);
DEFINE_PUBLIC_ALIAS(lio_listio64, librt_lio_listio64);
DEFINE_PUBLIC_ALIAS(aio_error64, librt_aio_error64);
DEFINE_PUBLIC_ALIAS(aio_return64, librt_aio_return64);
DEFINE_PUBLIC_ALIAS(aio_cancel64, librt_aio_cancel64);
DEFINE_PUBLIC_ALIAS(aio_suspend64, librt_aio_suspend64);
DEFINE_PUBLIC_ALIAS(aio_fsync64, librt_aio_fsync64);
DEFINE_PUBLIC_ALIAS(aio_suspendt64, librt_aio_suspendt64);
DEFINE_PUBLIC_ALIAS(aio_suspend64t64, librt_aio_suspend64t64);

DECL_END

#endif /* !GUARD_LIBRT_AIO_C */
