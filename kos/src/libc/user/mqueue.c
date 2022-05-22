/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_MQUEUE_C
#define GUARD_LIBC_USER_MQUEUE_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include <errno.h>
#include <stdarg.h>
#include <syscall.h>
#include <unistd.h>

/**/
#include "mqueue.h"

DECL_BEGIN

/*[[[head:libc_mq_open,hash:CRC-32=0x12f8a482]]]*/
/* >> mq_open(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") WUNUSED ATTR_IN(1) mqd_t
NOTHROW_RPC(VLIBCCALL libc_mq_open)(char const *__restrict name,
                                    oflag_t oflags,
                                    ...)
/*[[[body:libc_mq_open]]]*/
{
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
	va_end(args);
	result = sys_mq_open(name, oflags, mode);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_mq_open]]]*/

/*[[[head:libc_mq_close,hash:CRC-32=0xd2af7c29]]]*/
/* >> mq_close(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") int
NOTHROW(LIBCCALL libc_mq_close)(mqd_t mqdes)
/*[[[body:libc_mq_close]]]*/
{
	return close(mqdes);
}
/*[[[end:libc_mq_close]]]*/

/*[[[head:libc_mq_getattr,hash:CRC-32=0x1c285ed1]]]*/
/* >> mq_getattr(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_mq_getattr)(mqd_t mqdes,
                                      struct mq_attr *__restrict mqstat)
/*[[[body:libc_mq_getattr]]]*/
{
	errno_t error;
	error = sys_mq_getsetattr(mqdes, NULL, mqstat);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_getattr]]]*/

/*[[[head:libc_mq_setattr,hash:CRC-32=0x8deeec62]]]*/
/* >> mq_setattr(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_IN(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_mq_setattr)(mqd_t mqdes,
                                      struct mq_attr const *__restrict mqstat,
                                      struct mq_attr *__restrict old_mqstat)
/*[[[body:libc_mq_setattr]]]*/
{
	errno_t error;
	error = sys_mq_getsetattr(mqdes, mqstat, old_mqstat);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_setattr]]]*/

/*[[[head:libc_mq_unlink,hash:CRC-32=0x530af74b]]]*/
/* >> mq_unlink(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_IN(1) int
NOTHROW_NCX(LIBCCALL libc_mq_unlink)(char const *name)
/*[[[body:libc_mq_unlink]]]*/
{
	errno_t error;
	error = sys_mq_unlink(name);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_unlink]]]*/

/*[[[head:libc_mq_notify,hash:CRC-32=0xf01b149c]]]*/
/* >> mq_notify(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") int
NOTHROW_NCX(LIBCCALL libc_mq_notify)(mqd_t mqdes,
                                     struct sigevent const *notification)
/*[[[body:libc_mq_notify]]]*/
{
	errno_t error;
	error = sys_mq_notify(mqdes, notification);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_notify]]]*/

/*[[[head:libc_mq_receive,hash:CRC-32=0x8477db5a]]]*/
/* >> mq_receive(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_mq_receive)(mqd_t mqdes,
                                      char *__restrict msg_ptr,
                                      size_t msg_len,
                                      unsigned int *pmsg_prio)
/*[[[body:libc_mq_receive]]]*/
{
	ssize_t error;
#if __SIZEOF_INT__ == 4
	error = sys_mq_timedreceive(mqdes, msg_ptr, msg_len,
	                            (uint32_t *)pmsg_prio,
	                            NULL);
#else /* __SIZEOF_INT__ == 4 */
	uint32_t prio32;
	error = sys_mq_timedreceive(mqdes, msg_ptr, msg_len,
	                            pmsg_prio ? &prio32 : NULL,
	                            NULL);
#endif /* __SIZEOF_INT__ != 4 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_receive]]]*/

/*[[[head:libc_mq_send,hash:CRC-32=0x73947e3e]]]*/
/* >> mq_send(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_INS(2, 3) int
NOTHROW_RPC(LIBCCALL libc_mq_send)(mqd_t mqdes,
                                   char const *msg_ptr,
                                   size_t msg_len,
                                   unsigned int msg_prio)
/*[[[body:libc_mq_send]]]*/
{
	errno_t error;
#ifdef SYS_mq_timedsend_time64
	error = sys_mq_timedsend_time64(mqdes, msg_ptr, msg_len, msg_prio, NULL);
#else /* SYS_mq_timedsend_time64 */
	error = sys_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, NULL);
#endif /* !SYS_mq_timedsend_time64 */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_send]]]*/

/*[[[head:libc_mq_timedreceive,hash:CRC-32=0x552da9db]]]*/
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_IN(5) ATTR_OUTS(2, 3) ATTR_OUT_OPT(4) ssize_t
NOTHROW_RPC(LIBCCALL libc_mq_timedreceive)(mqd_t mqdes,
                                           char *__restrict msg_ptr,
                                           size_t msg_len,
                                           unsigned int *pmsg_prio,
                                           struct timespec const *__restrict abs_timeout)
/*[[[body:libc_mq_timedreceive]]]*/
{
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
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_timedreceive]]]*/

/*[[[head:libc_mq_timedsend,hash:CRC-32=0xa88ea98d]]]*/
/* >> mq_timedsend(3), mq_timedsend64(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_IN(5) ATTR_INS(2, 3) int
NOTHROW_RPC(LIBCCALL libc_mq_timedsend)(mqd_t mqdes,
                                        char const *msg_ptr,
                                        size_t msg_len,
                                        unsigned int msg_prio,
                                        struct timespec const *abs_timeout)
/*[[[body:libc_mq_timedsend]]]*/
{
	errno_t error;
	error = sys_mq_timedsend(mqdes, msg_ptr, msg_len,
	                         (uint32_t)msg_prio, abs_timeout);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_mq_timedsend]]]*/

/*[[[head:libc_mq_timedreceive64,hash:CRC-32=0xcd5dafbc]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mq_timedreceive64, libc_mq_timedreceive);
#else /* MAGIC:alias */
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_IN(5) ATTR_OUTS(2, 3) ssize_t
NOTHROW_RPC(LIBCCALL libc_mq_timedreceive64)(mqd_t mqdes,
                                             char *__restrict msg_ptr,
                                             size_t msg_len,
                                             unsigned int *pmsg_prio,
                                             struct timespec64 const *__restrict abs_timeout)
/*[[[body:libc_mq_timedreceive64]]]*/
{
#ifdef SYS_mq_timedreceive_time64
	ssize_t error;
#if __SIZEOF_INT__ == 4
	error = sys_mq_timedreceive_time64(mqdes, msg_ptr, msg_len,
	                                   (uint32_t *)pmsg_prio,
	                                   abs_timeout);
#else /* __SIZEOF_INT__ == 4 */
	uint32_t prio32;
	error = sys_mq_timedreceive_time64(mqdes, msg_ptr, msg_len,
	                                   pmsg_prio ? &prio32 : NULL,
	                                   abs_timeout);
#endif /* __SIZEOF_INT__ != 4 */
	return libc_seterrno_syserr(error);
#else /* SYS_mq_timedreceive_time64 */
	struct timespec ts;
	ts.tv_sec  = (time_t)abs_timeout->tv_sec;
	ts.tv_nsec = abs_timeout->tv_nsec;
	return libc_mq_timedreceive(mqdes, msg_ptr, msg_len, pmsg_prio, &ts);
#endif /* !SYS_mq_timedreceive_time64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_mq_timedreceive64]]]*/

/*[[[head:libc_mq_timedsend64,hash:CRC-32=0xc094a13a]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_mq_timedsend64, libc_mq_timedsend);
#else /* MAGIC:alias */
/* >> mq_timedsend(3), mq_timedsend64(3) */
INTERN ATTR_SECTION(".text.crt.utility.mqueue") ATTR_IN(5) ATTR_INS(2, 3) int
NOTHROW_RPC(LIBCCALL libc_mq_timedsend64)(mqd_t mqdes,
                                          char const *msg_ptr,
                                          size_t msg_len,
                                          unsigned int msg_prio,
                                          struct timespec64 const *abs_timeout)
/*[[[body:libc_mq_timedsend64]]]*/
{
#ifdef SYS_mq_timedsend_time64
	ssize_t error;
	error = sys_mq_timedsend_time64(mqdes, msg_ptr, msg_len,
	                                (uint32_t)msg_prio,
	                                abs_timeout);
	return libc_seterrno_syserr(error);
#else /* SYS_mq_timedsend_time64 */
	struct timespec ts;
	ts.tv_sec  = (time_t)abs_timeout->tv_sec;
	ts.tv_nsec = abs_timeout->tv_nsec;
	return libc_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, &ts);
#endif /* !SYS_mq_timedsend_time64 */
}
#endif /* MAGIC:alias */
/*[[[end:libc_mq_timedsend64]]]*/

/*[[[start:exports,hash:CRC-32=0xdabc74e1]]]*/
DEFINE_PUBLIC_ALIAS(mq_open, libc_mq_open);
DEFINE_PUBLIC_ALIAS(mq_close, libc_mq_close);
DEFINE_PUBLIC_ALIAS(mq_getattr, libc_mq_getattr);
DEFINE_PUBLIC_ALIAS(mq_setattr, libc_mq_setattr);
DEFINE_PUBLIC_ALIAS(mq_unlink, libc_mq_unlink);
DEFINE_PUBLIC_ALIAS(mq_notify, libc_mq_notify);
DEFINE_PUBLIC_ALIAS(mq_receive, libc_mq_receive);
DEFINE_PUBLIC_ALIAS(mq_send, libc_mq_send);
DEFINE_PUBLIC_ALIAS(mq_timedreceive, libc_mq_timedreceive);
DEFINE_PUBLIC_ALIAS(mq_timedsend, libc_mq_timedsend);
DEFINE_PUBLIC_ALIAS(mq_timedreceive64, libc_mq_timedreceive64);
DEFINE_PUBLIC_ALIAS(mq_timedsend64, libc_mq_timedsend64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MQUEUE_C */
