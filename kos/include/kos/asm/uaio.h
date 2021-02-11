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
#ifndef _KOS_ASM_UAIO_H
#define _KOS_ASM_UAIO_H 1

/* UAIO operations. (for `struct uaio::ua_op')
 * HINT: If the documented operation throws an exception, that exception
 *       can    be     retrieved    using     `uaio_rethrow(..., ua_id)' */
#define UAIO_OP_NOOP      0x0000 /* Does nothing */
#define UAIO_OP_READ      0x0001 /* pread(2) */
#define UAIO_OP_READV     0x0002 /* preadv(2) */
#define UAIO_OP_WRITE     0x0003 /* pwrite(2) */
#define UAIO_OP_WRITEV    0x0004 /* pwritev(2) */
#define UAIO_OP_CONNECT   0x0005 /* connect(2) */
#define UAIO_OP_RECV      0x0006 /* recv(2) */
#define UAIO_OP_RECVV     0x0007 /* recv(2) (with iovec) */
#define UAIO_OP_SEND      0x0008 /* send(2) */
#define UAIO_OP_SENDV     0x0009 /* send(2) (with iovec) */

/* UAIO operation flags. (for `struct uaio::ua_flag') */
#define UAIO_F_RUNSTAT 0x0001 /* Broadcast the status futex for `UAIO_STATUS_RUNNING' */
#define UAIO_F_WAITFOR 0x0002 /* Asynchronously wait for all currently running AIO operations
                               * before proceeding with the operation pointed to by `ua_next'
                               * Using  this flag, you  can enforce happens-before semantics,
                               * as may be necessary when you're re-using memory buffers,  or
                               * want  to use the memory written by one AIO operation getting
                               * used by the next operation. */


/* UAIO status codes. (for `struct uaio::ua_status') */
#define UAIO_STATUS_PENDING 0x00 /* The initial AIO status: Not started, yet. */
#define UAIO_STATUS_RUNNING 0x01 /* In-progress status value (this status being set
                                  * will  not trigger a futex broadcast, unless the
                                  * `UAIO_F_RUNSTAT' flag had been set). */
#define UAIO_STATUS_SUCCESS 0x10 /* Exit status: The operation was successful. */
#define UAIO_STATUS_NOTSUPP 0x11 /* Exit status: The given `ua_fd' doesn't support `ua_op'
                                  *              Re-try   the   operation   synchronously. */
#define UAIO_STATUS_FAILED  0x12 /* Exit   status:  The  operation  failed  with  an  exception
                                  * (use `uaio_rethrow(..., ua_id)' to re-throw that exception) */
#define UAIO_STATUS_CANCEL  0x13 /* Exit status: The operation was canceled.
                                  * This exit status is set when `uaio_cancel()' is used,
                                  * and  the AIO operation hadn't already been completed. */

/* Flags for `uaio_create()' */
#define UAIO_CREATE_NONBLOCK 0x000800 /* Set the IO_NONBLOCK flag. */
#define UAIO_CREATE_CLOEXEC  0x080000 /* Set the IO_CLOEXEC flag */
#define UAIO_CREATE_CLOFORK  0x100000 /* Set the IO_CLOFORK flag */


#endif /* !_KOS_ASM_UAIO_H */
