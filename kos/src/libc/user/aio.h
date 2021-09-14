/* HASH CRC-32:0x4ef4c6f1 */
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
#ifndef GUARD_LIBC_USER_AIO_H
#define GUARD_LIBC_USER_AIO_H 1

#include "../api.h"
#include "../auto/aio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <aio.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> aio_read(3)
 * Begin an async `read(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_read)(struct aiocb *aiocbp);
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_write)(struct aiocb *aiocbp);
/* >> aio_fsync(3)
 * Begin an async `fsync(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_aio_fsync)(int operation, struct aiocb *aiocbp);
/* >> lio_listio(3)
 * Execute/perform a `list' of AIO operations
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT' */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_lio_listio)(int mode, struct aiocb *const list[__restrict_arr], __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig);
/* >> aio_error(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress
 * @return: ECANCELED:   Operation was cancelled
 * @return: * :          The  `errno'  with  which  the  async  operation  failed.
 *                       s.a. `read(2)', `write(2)', `fsync(2)' and `fdatasync(2)' */
INTDEF WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc_aio_error)(struct aiocb const *aiocbp);
/* >> aio_return(3)
 * @return: * : Return value of async `read(2)', `write(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_aio_return)(struct aiocb *aiocbp);
/* >> aio_cancel(3)
 * @return: AIO_CANCELED:    Operations cancelled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_aio_cancel)(fd_t fildes, struct aiocb *aiocbp);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_aio_suspend)(struct aiocb const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec const *__restrict timeout);
/* >> aio_read(3)
 * Begin an async `read(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_read64)(struct aiocb64 *aiocbp);
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_write64)(struct aiocb64 *aiocbp);
/* >> aio_fsync(3)
 * Begin an async `fsync(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_aio_fsync64)(int operation, struct aiocb64 *aiocbp);
/* >> aio_write(3)
 * Begin an async `write(2)' operation (TODO: Document fields used) */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_lio_listio64)(int mode, struct aiocb64 *const list[__restrict_arr], __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig);
/* >> aio_error(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress
 * @return: ECANCELED:   Operation was cancelled
 * @return: * :          The  `errno'  with  which  the  async  operation  failed.
 *                       s.a. `read(2)', `write(2)', `fsync(2)' and `fdatasync(2)' */
INTDEF WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_error64)(struct aiocb64 const *aiocbp);
/* >> aio_return(3)
 * @return: * : Return value of async `read(2)', `write(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_aio_return64)(struct aiocb64 *aiocbp);
/* >> aio_cancel(3)
 * @return: AIO_CANCELED:    Operations cancelled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 * @return: AIO_ALLDONE:     Operations were already completed before the call was made
 * @return: -1:              Error (s.a. `errno') */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBCCALL libc_aio_cancel64)(fd_t fildes, struct aiocb64 *aiocbp);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_suspend64)(struct aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec const *__restrict timeout);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_suspendt64)(struct aiocb const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec64 const *__restrict timeout);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend the calling thread until at least one of the given AIO operations
 * has been completed, a signal is delivered to, or (if non-NULL) the given
 * timeout expired.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The given timeout expired
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread
 * @return: -1: Error (s.a. `errno') */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_aio_suspend64t64)(struct aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec64 const *__restrict timeout);
/* >> aio_init(3) */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_aio_init)(struct aioinit const *init);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_AIO_H */
