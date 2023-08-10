/* HASH CRC-32:0xafa9725 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_AIO_H
#define GUARD_LIBC_AUTO_AIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <aio.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_aio_read)(struct aiocb *self);
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_aio_write)(struct aiocb *self);
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_aio_fsync)(oflag_t operation, struct aiocb *self);
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
INTDEF ATTR_INS(2, 3) int NOTHROW_NCX(LIBDCALL libd_lio_listio)(int mode, struct aiocb *const list[__restrict_arr], __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sigev);
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
INTDEF WUNUSED ATTR_IN(1) errno_t NOTHROW_NCX(LIBDCALL libd_aio_error)(struct aiocb const *self);
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
INTDEF ATTR_INOUT(1) ssize_t NOTHROW_NCX(LIBDCALL libd_aio_return)(struct aiocb *self);
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_aio_cancel)(fd_t fd, struct aiocb *self);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
INTDEF ATTR_INS(1, 2) int NOTHROW_RPC(LIBDCALL libd_aio_suspend)(struct aiocb const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec const *__restrict rel_timeout);
/* >> aio_read(3), aio_read64(3)
 * Begin an async `pread(2)' operation:
 * >> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `read(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_aio_read64)(struct aiocb64 *self);
/* >> aio_write(3), aio_write64(3)
 * Begin an async `pwrite(2)' operation:
 * >> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
 * then `write(2)' is called instead (in which case `self->aio_offset' is ignored) */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_aio_write64)(struct aiocb64 *self);
/* >> aio_fsync(3), aio_fsync64(3)
 * Begin an async `fsync(2)' or `fdatasync(2)' operation:
 * >> if (operation == O_SYNC) {
 * >>     fsync(self->aio_fildes);
 * >> } else if (operation == O_DSYNC) {
 * >>     fdatasync(self->aio_fildes);
 * >> }
 * >> NOTIFY_COMPLETION(&self->aio_sigevent);
 * @param: operation: One of `O_SYNC' or `O_DSYNC'
 * @return: 0 : Operation was started successfully
 * @return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
 *                             didn't want to use that errno for whatever reason...)
 * @return: -1: [errno=EINVAL] `operation' was invalid */
INTDEF NONNULL((2)) int NOTHROW_NCX(LIBDCALL libd_aio_fsync64)(int operation, struct aiocb64 *self);
/* >> lio_listio(3), lio_listio64(3)
 * Execute/perform  a `list' of  AIO operations, where  each element of `list'
 * describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
 * or no-op (`LIO_NOP') operation.
 *
 * Once all operations are in progress, and `mode == LIO_WAIT', wait for all
 * of  them to complete  and return `0' on  success, or `-1'  is any of them
 * failed (individual errors/return values can be queried via `aio_error(3)'
 * and `aio_return(3)' on each of the elements from `list')
 *
 * Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
 * and the function returns immediately once all operations have been started.
 * If  this was successful, return `0', or  `-1' if doing so failed (`errno').
 * Note that upon error here, no AIO operations will have been started, yet.
 *
 * Additionally, the given `sigev' (if non-NULL) will be assigned as a master
 * completion event that is only triggered  once _all_ of the AIO  operations
 * have completed. Note that in this case, `sigev' will/has always be invoked
 * if this function returns  `0', even if  any of the  AIO operations end  up
 * being canceled (s.a. `aio_cancel(3)') before they could be performed.
 *
 * @param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
 * @return: 0 : Success
 * @return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
 * @return: -1: [errno=EINVAL] Invalid `mode'
 * @return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
 *                             Note that in  this case incomplete  AIO operations  will
 *                             continue to run and that  the caller should handle  this
 *                             case by looping over  all and using `aio_suspend(3)'  to
 *                             wait for each until doing so has succeeded at least once
 *                             for every entry.
 * @return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
 *                             failed (s.a. `aio_error(3)') */
INTDEF ATTR_INS(2, 3) int NOTHROW_NCX(LIBDCALL libd_lio_listio64)(int mode, struct aiocb64 *const list[__restrict_arr], __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sigev);
/* >> aio_error(3), aio_error64(3)
 * @return: 0 :          Operation completed
 * @return: EINPROGRESS: Async operation is still in progress (or pending)
 * @return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
 * @return: EINVAL:      `self' is invalid, or its return value has already been read.
 * @return: * :          The   `errno'  with  which   the  async  operation  failed.
 *                       s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)' */
INTDEF WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_aio_error64)(struct aiocb64 const *self);
/* >> aio_return(3), aio_return64(3)
 * @return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
 * @return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
 * @return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
 *                                  in progress), or  its return value  has already been  read. */
INTDEF ATTR_INOUT(1) ssize_t NOTHROW_NCX(LIBDCALL libd_aio_return64)(struct aiocb64 *self);
/* >> aio_cancel(3), aio_cancel64(3)
 * Cancel  a specific AIO  operation (self != NULL),  or all operations currently
 * operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
 * purpose,  it is undefined if the numerical value of `fd' is used for searching
 * active operations, or the pointed-to kernel object. As such, it is recommended
 * that you always aio_cancel the same fd as was also used when the AIO operation
 * was initiated.
 * NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
 *       as  specified in `self->aio_sigevent'  will have been triggered,
 *       as completion events are triggered even for canceled operations.
 * @return: AIO_CANCELED:    At least one operation was canceled successfully
 * @return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
 *                           This KOS implementation never returns  this value, as it  includes
 *                           facilities to force-abort any async operation (in the same vain as
 *                           sending SIGKILL can also force-aborts a process)
 *                           NOTE: In other implementations, this return value outweighs
 *                                 `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
 *                                 AIO operations.
 * @return: AIO_ALLDONE:     Operations had  already been  completed
 *                           (or canceled) before the call was made.
 * @return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
 * @return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes' */
INTDEF ATTR_FDARG(1) int NOTHROW_NCX(LIBDCALL libd_aio_cancel64)(fd_t fildes, struct aiocb64 *self);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_aio_suspend64)(struct aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec const *__restrict rel_timeout);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_aio_suspendt64)(struct aiocb const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec64 const *__restrict rel_timeout);
/* >> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
 * Suspend  the calling thread until at least  one of the given AIO operations
 * has been completed, a  signal is delivered to,  or (if non-NULL) the  given
 * `rel_timeout' expired.
 * @param: rel_timeout: The amount of time (relative) for which to wait.
 * @return: 0:  Success (At least one of the given AIO operations has completed)
 * @return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
 * @return: -1: [errno=EINTR]  A signal was delivered to the calling thread */
INTDEF ATTR_INS(1, 2) int NOTHROW_NCX(LIBDCALL libd_aio_suspend64t64)(struct aiocb64 const *const list[], __STDC_INT_AS_SIZE_T nent, struct timespec64 const *__restrict rel_timeout);
/* >> aio_init(3) */
INTDEF ATTR_IN(1) void NOTHROW_NCX(LIBDCALL libd_aio_init)(struct aioinit const *init);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_AIO_H */
