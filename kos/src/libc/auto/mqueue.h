/* HASH CRC-32:0x97e47e72 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_MQUEUE_H
#define GUARD_LIBC_AUTO_MQUEUE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <mqueue.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mq_open(3) */
INTDEF WUNUSED ATTR_IN(1) mqd_t NOTHROW_RPC(VLIBDCALL libd_mq_open)(char const *__restrict name, oflag_t oflags, ...);
/* >> mq_close(3) */
INTDEF int NOTHROW(LIBDCALL libd_mq_close)(mqd_t mqdes);
/* >> mq_getattr(3) */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_mq_getattr)(mqd_t mqdes, struct mq_attr *__restrict mqstat);
/* >> mq_setattr(3) */
INTDEF ATTR_IN(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_mq_setattr)(mqd_t mqdes, struct mq_attr const *__restrict mqstat, struct mq_attr *__restrict old_mqstat);
/* >> mq_unlink(3) */
INTDEF ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_mq_unlink)(char const *name);
/* >> mq_notify(3) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_mq_notify)(mqd_t mqdes, struct sigevent const *notification);
/* >> mq_receive(3) */
INTDEF ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_mq_receive)(mqd_t mqdes, char *__restrict msg_ptr, size_t msg_len, unsigned int *pmsg_prio);
/* >> mq_send(3) */
INTDEF ATTR_INS(2, 3) int NOTHROW_RPC(LIBDCALL libd_mq_send)(mqd_t mqdes, char const *msg_ptr, size_t msg_len, unsigned int msg_prio);
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
INTDEF ATTR_IN(5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(4) ssize_t NOTHROW_RPC(LIBDCALL libd_mq_timedreceive)(mqd_t mqdes, char *__restrict msg_ptr, size_t msg_len, unsigned int *pmsg_prio, struct timespec const *__restrict abs_timeout);
/* >> mq_timedsend(3), mq_timedsend64(3) */
INTDEF ATTR_IN(5) ATTR_INS(2, 3) int NOTHROW_RPC(LIBDCALL libd_mq_timedsend)(mqd_t mqdes, char const *msg_ptr, size_t msg_len, unsigned int msg_prio, struct timespec const *abs_timeout);
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
INTDEF ATTR_IN(5) ATTR_OUTS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_mq_timedreceive64)(mqd_t mqdes, char *__restrict msg_ptr, size_t msg_len, unsigned int *pmsg_prio, struct timespec64 const *__restrict abs_timeout);
/* >> mq_timedsend(3), mq_timedsend64(3) */
INTDEF ATTR_IN(5) ATTR_INS(2, 3) int NOTHROW_RPC(LIBDCALL libd_mq_timedsend64)(mqd_t mqdes, char const *msg_ptr, size_t msg_len, unsigned int msg_prio, struct timespec64 const *abs_timeout);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_MQUEUE_H */
