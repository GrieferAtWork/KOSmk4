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
#ifndef GUARD_LIBRT_MQUEUE_H
#define GUARD_LIBRT_MQUEUE_H 1

#include "api.h"
/**/

#include <kos/types.h>

#include <librt/mqueue.h>

/* Documentation derived from Glibc /usr/include/mqueue.h */
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

/* Establish  connection  between  a process  and  a message  queue  NAME and
 * return message queue descriptor or  (mqd_t)-1 on error. OFLAGS  determines
 * the type of access used.  If O_CREAT is on  OFLAGS, the third argument  is
 * taken as a `mode_t', the mode of the created message queue, and the fourth
 * argument  is  taken  as  `struct mq_attr *',  pointer  to  message   queue
 * attributes. If the fourth argument  is NULL, default attributes are  used. */
INTDEF WUNUSED NONNULL((1)) mqd_t
NOTHROW_NCX(VCC librt_mq_open)(char const *__restrict name, oflag_t oflags, ...);

/* Removes the association between message queue descriptor MQDES and its message queue. */
INTDEF int NOTHROW(CC librt_mq_close)(mqd_t mqdes);

/* Query status and attributes of message queue MQDES. */
INTDEF NONNULL((2)) int
NOTHROW_NCX(CC librt_mq_getattr)(mqd_t mqdes, struct mq_attr *__restrict mqstat);

/* Set attributes associated with message queue MQDES and if OMQSTAT is
   not NULL also query its old attributes. */
INTDEF NONNULL((2)) int
NOTHROW_NCX(CC librt_mq_setattr)(mqd_t mqdes,
                                 struct mq_attr const *__restrict mqstat,
                                 struct mq_attr *__restrict omqstat);

/* Remove message queue named NAME. */
INTDEF NONNULL((1)) int
NOTHROW_NCX(CC librt_mq_unlink)(char const *name);

/* Register notification issued upon message arrival to an empty message queue MQDES. */
INTDEF int
NOTHROW_NCX(CC librt_mq_notify)(mqd_t mqdes, struct sigevent const *notification);

/* Receive the oldest from highest priority messages in message queue MQDES. */
INTDEF NONNULL((2)) ssize_t
NOTHROW_RPC(CC librt_mq_receive)(mqd_t mqdes, char *__restrict msg_ptr,
                                 size_t msg_len, unsigned int *pmsg_prio);

/* Add message pointed by MSG_PTR to message queue MQDES. */
INTDEF NONNULL((2)) int
NOTHROW_RPC(CC librt_mq_send)(mqd_t mqdes, char const *msg_ptr,
                              size_t msg_len, unsigned int msg_prio);

/* Receive  the  oldest  from highest  priority  messages in
 * message queue MQDES, stop waiting if ABS_TIMEOUT expires. */
INTDEF NONNULL((2, 5)) ssize_t
NOTHROW_RPC(CC librt_mq_timedreceive)(mqd_t mqdes, char *__restrict msg_ptr,
                                      size_t msg_len, unsigned int *pmsg_prio,
                                      struct __timespec32 const *__restrict abs_timeout);

/* Add message pointed by MSG_PTR to message queue MQDES, stop
 * blocking  on  full  message queue  if  ABS_TIMEOUT expires. */
INTDEF NONNULL((2, 5)) int
NOTHROW_RPC(CC librt_mq_timedsend)(mqd_t mqdes, char const *msg_ptr,
                                   size_t msg_len, unsigned int msg_prio,
                                   struct __timespec32 const *abs_timeout);

/* Receive  the  oldest  from highest  priority  messages in
 * message queue MQDES, stop waiting if ABS_TIMEOUT expires. */
INTDEF NONNULL((2, 5)) ssize_t
NOTHROW_RPC(CC librt_mq_timedreceive64)(mqd_t mqdes, char *__restrict msg_ptr,
                                        size_t msg_len, unsigned int *pmsg_prio,
                                        struct __timespec64 const *__restrict abs_timeout);

/* Add message pointed by MSG_PTR to message queue MQDES, stop
 * blocking  on  full  message queue  if  ABS_TIMEOUT expires. */
INTDEF NONNULL((2, 5)) int
NOTHROW_RPC(CC librt_mq_timedsend64)(mqd_t mqdes, char const *msg_ptr,
                                     size_t msg_len, unsigned int msg_prio,
                                     struct __timespec64 const *abs_timeout);

DECL_END

#endif /* !GUARD_LIBRT_MQUEUE_H */
