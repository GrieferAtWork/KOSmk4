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
#ifndef _MQUEUE_H
#define _MQUEUE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/sigevent.h> /* struct sigevent */
#include <bits/timespec.h>
#include <bits/types.h>

#include <librt/_api.h>
#include <librt/bits/mqueue.h>
#ifdef __USE_GLIBC
#include <sys/types.h>
#include <fcntl.h>
#endif /* __USE_GLIBC */


/* Documentation taken from Glibc /usr/include/mqueue.h */
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

__SYSDECL_BEGIN


#ifdef __CC__

#ifndef __sigevent_t_defined
#define __sigevent_t_defined 1
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */


/* Establish connection between a process and a message queue NAME and
 * return message queue descriptor or (mqd_t)-1 on error. OFLAGS determines
 * the type of access used. If O_CREAT is on OFLAGS, the third argument is
 * taken as a `mode_t', the mode of the created message queue, and the fourth
 * argument is taken as `struct mq_attr *', pointer to message queue
 * attributes. If the fourth argument is NULL, default attributes are used. */
#ifndef __mq_open_defined
#define __mq_open_defined 1
__LIBRT_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) mqd_t
__NOTHROW_NCX(__LIBRT_VCC mq_open)(char const *__restrict __name, __oflag_t __oflags, ...);
#endif /* !__mq_open_defined */

/* Removes the association between message queue descriptor MQDES and its message queue. */
#ifndef __mq_close_defined
#define __mq_close_defined 1
__LIBRT_DECL int __NOTHROW(__LIBRT_CC mq_close)(mqd_t __mqdes);
#endif /* !__mq_close_defined */

/* Query status and attributes of message queue MQDES. */
#ifndef __mq_getattr_defined
#define __mq_getattr_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC mq_getattr)(mqd_t __mqdes, struct mq_attr *__restrict __mqstat);
#endif /* !__mq_getattr_defined */

/* Set attributes associated with message queue MQDES and if OMQSTAT is
   not NULL also query its old attributes. */
#ifndef __mq_setattr_defined
#define __mq_setattr_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_NCX(__LIBRT_CC mq_setattr)(mqd_t __mqdes,
                                     struct mq_attr const *__restrict __mqstat,
                                     struct mq_attr *__restrict __omqstat);
#endif /* !__mq_setattr_defined */

/* Remove message queue named NAME. */
#ifndef __mq_unlink_defined
#define __mq_unlink_defined 1
__LIBRT_DECL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBRT_CC mq_unlink)(char const *__name);
#endif /* !__mq_unlink_defined */

/* Register notification issued upon message arrival to an empty message queue MQDES. */
#ifndef __mq_notify_defined
#define __mq_notify_defined 1
__LIBRT_DECL int
__NOTHROW_NCX(__LIBRT_CC mq_notify)(mqd_t __mqdes, struct sigevent const *__notification);
#endif /* !__mq_notify_defined */

/* Receive the oldest from highest priority messages in message queue MQDES. */
#ifndef __mq_receive_defined
#define __mq_receive_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) __ssize_t
__NOTHROW_RPC(__LIBRT_CC mq_receive)(mqd_t __mqdes, char *__restrict __msg_ptr,
                                     __size_t __msg_len, unsigned int *__pmsg_prio);
#endif /* !__mq_receive_defined */

/* Add message pointed by MSG_PTR to message queue MQDES. */
#ifndef __mq_send_defined
#define __mq_send_defined 1
__LIBRT_DECL __ATTR_NONNULL((2)) int
__NOTHROW_RPC(__LIBRT_CC mq_send)(mqd_t __mqdes, char const *__msg_ptr,
                                  __size_t __msg_len, unsigned int __msg_prio);
#endif /* !__mq_send_defined */

#ifdef __USE_XOPEN2K
/* Receive the oldest from highest priority messages in
 * message queue MQDES, stop waiting if ABS_TIMEOUT expires. */
#ifndef __mq_timedreceive_defined
#define __mq_timedreceive_defined 1
#ifdef __USE_TIME_BITS64
__COMPILER_REDIRECT(__LIBRT_DECL,__ATTR_NONNULL((2, 5)),__ssize_t,__NOTHROW_RPC,__LIBRT_CC,
                    mq_timedreceive,(mqd_t __mqdes, char *__restrict __msg_ptr,
                                     __size_t __msg_len, unsigned int *__pmsg_prio,
                                     struct timespec const *__restrict __abs_timeout),
                    mq_timedreceive64,(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#else /* __USE_TIME_BITS64 */
__LIBRT_DECL __ATTR_NONNULL((2, 5)) __ssize_t
__NOTHROW_RPC(__LIBRT_CC mq_timedreceive)(mqd_t __mqdes, char *__restrict __msg_ptr,
                                          __size_t __msg_len, unsigned int *__pmsg_prio,
                                          struct timespec const *__restrict __abs_timeout);
#endif /* !__USE_TIME_BITS64 */
#endif /* !__mq_timedreceive_defined */

/* Add message pointed by MSG_PTR to message queue MQDES, stop
 * blocking on full message queue if ABS_TIMEOUT expires. */
#ifndef __mq_timedsend_defined
#define __mq_timedsend_defined 1
#ifdef __USE_TIME_BITS64
__COMPILER_REDIRECT(__LIBRT_DECL,__ATTR_NONNULL((2, 5)),int,__NOTHROW_RPC,__LIBRT_CC,
                    mq_timedsend,(mqd_t __mqdes, char const *__msg_ptr,
                                  __size_t __msg_len, unsigned int __msg_prio,
                                  struct timespec const *__abs_timeout),
                    mq_timedsend64,(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#else /* __USE_TIME_BITS64 */
__LIBRT_DECL __ATTR_NONNULL((2, 5)) int
__NOTHROW_RPC(__LIBRT_CC mq_timedsend)(mqd_t __mqdes, char const *__msg_ptr,
                                       __size_t __msg_len, unsigned int __msg_prio,
                                       struct timespec const *__abs_timeout);
#endif /* !__USE_TIME_BITS64 */
#endif /* !__mq_timedsend_defined */

#ifdef __USE_TIME64
/* Receive the oldest from highest priority messages in
 * message queue MQDES, stop waiting if ABS_TIMEOUT expires. */
#ifndef __mq_timedreceive64_defined
#define __mq_timedreceive64_defined 1
__LIBRT_DECL __ATTR_NONNULL((2, 5)) __ssize_t
__NOTHROW_RPC(__LIBRT_CC mq_timedreceive64)(mqd_t __mqdes, char *__restrict __msg_ptr,
                                            __size_t __msg_len, unsigned int *__pmsg_prio,
                                            struct timespec64 const *__restrict __abs_timeout);
#endif /* !__mq_timedreceive64_defined */

/* Add message pointed by MSG_PTR to message queue MQDES, stop
 * blocking on full message queue if ABS_TIMEOUT expires. */
#ifndef __mq_timedsend64_defined
#define __mq_timedsend64_defined 1
__LIBRT_DECL __ATTR_NONNULL((2, 5)) int
__NOTHROW_RPC(__LIBRT_CC mq_timedsend64)(mqd_t __mqdes, char const *__msg_ptr,
                                         __size_t __msg_len, unsigned int __msg_prio,
                                         struct timespec64 const *__abs_timeout);
#endif /* !__mq_timedsend64_defined */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_MQUEUE_H */
