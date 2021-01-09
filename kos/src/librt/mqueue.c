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
#ifndef GUARD_LIBRT_MQUEUE_C
#define GUARD_LIBRT_MQUEUE_C 1
#define _TIME64_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "api.h"
/**/

#include <kos/syscalls.h>

#include <errno.h>
#include <stdarg.h>
#include <syscall.h>
#include <unistd.h>

#include <librt/mqueue.h>

#include "mqueue.h"

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

#ifdef SYS_mq_timedreceive_time64
#define sys_mq_timedreceive64 sys_mq_timedreceive_time64
#endif /* SYS_mq_timedreceive_time64 */

#ifdef SYS_mq_timedsend_time64
#define sys_mq_timedsend64 sys_mq_timedsend_time64
#endif /* SYS_mq_timedsend_time64 */

DECL_BEGIN


/* Establish connection between a process and a message queue NAME and
 * return message queue descriptor or (mqd_t)-1 on error. OFLAGS determines
 * the type of access used. If O_CREAT is on OFLAGS, the third argument is
 * taken as a `mode_t', the mode of the created message queue, and the fourth
 * argument is taken as `struct mq_attr *', pointer to message queue
 * attributes. If the fourth argument is NULL, default attributes are used. */
INTERN WUNUSED NONNULL((1)) mqd_t
NOTHROW_NCX(VCC librt_mq_open)(char const *__restrict name, oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
	va_end(args);
	result = sys_mq_open(name, oflags, mode);
	if unlikely(E_ISERR(result)) {
		errno  = -result;
		result = -1;
	}
	return result;
}

/* Removes the association between message queue descriptor MQDES and its message queue. */
INTERN int NOTHROW(CC librt_mq_close)(mqd_t mqdes) {
	return close(mqdes);
}

/* Query status and attributes of message queue MQDES. */
INTERN NONNULL((2)) int
NOTHROW_NCX(CC librt_mq_getattr)(mqd_t mqdes, struct mq_attr *__restrict mqstat) {
	errno_t error;
	error = sys_mq_getsetattr(mqdes, NULL, mqstat);
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

/* Set attributes associated with message queue MQDES and if OMQSTAT is
   not NULL also query its old attributes. */
INTERN NONNULL((2)) int
NOTHROW_NCX(CC librt_mq_setattr)(mqd_t mqdes,
                                 struct mq_attr const *__restrict mqstat,
                                 struct mq_attr *__restrict omqstat) {
	errno_t error;
	error = sys_mq_getsetattr(mqdes, mqstat, omqstat);
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

/* Remove message queue named NAME. */
INTERN NONNULL((1)) int
NOTHROW_NCX(CC librt_mq_unlink)(char const *name) {
	errno_t error;
	error = sys_mq_unlink(name);
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

/* Register notification issued upon message arrival to an empty message queue MQDES. */
INTERN int
NOTHROW_NCX(CC librt_mq_notify)(mqd_t mqdes, struct sigevent const *notification) {
	errno_t error;
	error = sys_mq_notify(mqdes, notification);
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

PRIVATE NONNULL((2, 5)) ssize_t
NOTHROW_RPC(CC mq_timedreceive_impl32)(mqd_t mqdes, char *__restrict msg_ptr,
                                       size_t msg_len, unsigned int *pmsg_prio,
                                       struct timespec32 const *__restrict abs_timeout) {
	ssize_t error;
#if __SIZEOF_INT__ == 4
	error = sys_mq_timedreceive(mqdes, msg_ptr, msg_len,
	                            (uint32_t *)pmsg_prio,
	                            abs_timeout);
#else /* __SIZEOF_INT__ == 4 */
	uint32_t prio32;
	error = sys_mq_timedreceive(mqdes, msg_ptr, msg_len,
	                            pmsg_prio ? &prio32 : NULL,
	                            abs_timeout);
#endif /* __SIZEOF_INT__ != 4 */
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
PRIVATE NONNULL((2, 5)) ssize_t
NOTHROW_RPC(CC mq_timedreceive_impl64)(mqd_t mqdes, char *__restrict msg_ptr,
                                       size_t msg_len, unsigned int *pmsg_prio,
                                       struct timespec64 const *__restrict abs_timeout) {
	ssize_t error;
#if __SIZEOF_INT__ == 4
	error = sys_mq_timedreceive64(mqdes, msg_ptr, msg_len,
	                              (uint32_t *)pmsg_prio,
	                              abs_timeout);
#else /* __SIZEOF_INT__ == 4 */
	uint32_t prio32;
	error = sys_mq_timedreceive64(mqdes, msg_ptr, msg_len,
	                              pmsg_prio ? &prio32 : NULL,
	                              abs_timeout);
#endif /* __SIZEOF_INT__ != 4 */
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

/* Receive the oldest from highest priority messages in message queue MQDES. */
INTERN NONNULL((2)) ssize_t
NOTHROW_RPC(CC librt_mq_receive)(mqd_t mqdes, char *__restrict msg_ptr,
                                 size_t msg_len, unsigned int *pmsg_prio) {
	return mq_timedreceive_impl32(mqdes, msg_ptr, msg_len, pmsg_prio, NULL);
}

/* Add message pointed by MSG_PTR to message queue MQDES. */
INTERN NONNULL((2)) int
NOTHROW_RPC(CC librt_mq_send)(mqd_t mqdes, char const *msg_ptr,
                              size_t msg_len, unsigned int msg_prio) {
	errno_t error;
#ifdef __NR_mq_timedsend64
	error = sys_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, NULL);
#else /* __NR_mq_timedsend64 */
	error = sys_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, NULL);
#endif /* !__NR_mq_timedsend64 */
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

/* Receive the oldest from highest priority messages in
 * message queue MQDES, stop waiting if ABS_TIMEOUT expires. */
INTERN NONNULL((2, 5)) ssize_t
NOTHROW_RPC(CC librt_mq_timedreceive)(mqd_t mqdes, char *__restrict msg_ptr,
                                      size_t msg_len, unsigned int *pmsg_prio,
                                      struct timespec32 const *__restrict abs_timeout) {
	return mq_timedreceive_impl32(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout);
}

/* Add message pointed by MSG_PTR to message queue MQDES, stop
 * blocking on full message queue if ABS_TIMEOUT expires. */
INTERN NONNULL((2, 5)) int
NOTHROW_RPC(CC librt_mq_timedsend)(mqd_t mqdes, char const *msg_ptr,
                                   size_t msg_len, unsigned int msg_prio,
                                   struct timespec32 const *abs_timeout) {
	errno_t error;
	error = sys_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(librt_mq_timedreceive64, librt_mq_timedreceive);
DEFINE_INTERN_ALIAS(librt_mq_timedsend64, librt_mq_timedsend);
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
/* Receive the oldest from highest priority messages in
 * message queue MQDES, stop waiting if ABS_TIMEOUT expires. */
INTERN NONNULL((2, 5)) ssize_t
NOTHROW_RPC(CC librt_mq_timedreceive64)(mqd_t mqdes, char *__restrict msg_ptr,
                                        size_t msg_len, unsigned int *pmsg_prio,
                                        struct timespec64 const *__restrict abs_timeout) {
	return mq_timedreceive_impl64(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout);
}

/* Add message pointed by MSG_PTR to message queue MQDES, stop
 * blocking on full message queue if ABS_TIMEOUT expires. */
INTERN NONNULL((2, 5)) int
NOTHROW_RPC(CC librt_mq_timedsend64)(mqd_t mqdes, char const *msg_ptr,
                                     size_t msg_len, unsigned int msg_prio,
                                     struct timespec64 const *abs_timeout) {
	errno_t error;
	error = sys_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
	if unlikely(E_ISERR(error)) {
		errno = -error;
		error = -1;
	}
	return error;
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */



DEFINE_PUBLIC_ALIAS(mq_open, librt_mq_open);
DEFINE_PUBLIC_ALIAS(mq_close, librt_mq_close);
DEFINE_PUBLIC_ALIAS(mq_getattr, librt_mq_getattr);
DEFINE_PUBLIC_ALIAS(mq_setattr, librt_mq_setattr);
DEFINE_PUBLIC_ALIAS(mq_unlink, librt_mq_unlink);
DEFINE_PUBLIC_ALIAS(mq_notify, librt_mq_notify);
DEFINE_PUBLIC_ALIAS(mq_receive, librt_mq_receive);
DEFINE_PUBLIC_ALIAS(mq_send, librt_mq_send);
DEFINE_PUBLIC_ALIAS(mq_timedreceive, librt_mq_timedreceive);
DEFINE_PUBLIC_ALIAS(mq_timedsend, librt_mq_timedsend);
DEFINE_PUBLIC_ALIAS(mq_timedreceive64, librt_mq_timedreceive64);
DEFINE_PUBLIC_ALIAS(mq_timedsend64, librt_mq_timedsend64);

DECL_END

#endif /* !GUARD_LIBRT_MQUEUE_C */
