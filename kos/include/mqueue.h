/* HASH CRC-32:0x76485ab3 */
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
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mqueue.h) */
/* (#) Portability: DragonFly BSD (/include/mqueue.h) */
/* (#) Portability: FreeBSD       (/include/mqueue.h) */
/* (#) Portability: GNU C Library (/rt/mqueue.h) */
/* (#) Portability: GNU Hurd      (/usr/include/mqueue.h) */
/* (#) Portability: NetBSD        (/include/mqueue.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/mqueue.h) */
/* (#) Portability: diet libc     (/include/mqueue.h) */
/* (#) Portability: libc6         (/include/mqueue.h) */
/* (#) Portability: musl libc     (/include/mqueue.h) */
/* (#) Portability: uClibc        (/include/mqueue.h) */
#ifndef _MQUEUE_H
#define _MQUEUE_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/os/mqueue.h>
#include <bits/os/sigevent.h> /* struct sigevent */
#include <bits/os/timespec.h>
#include <bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#include <fcntl.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

typedef __mqd_t mqd_t;

#ifdef __CRT_HAVE_mq_open
/* >> mq_open(3) */
__LIBC __ATTR_WUNUSED __ATTR_IN(1) mqd_t __NOTHROW_RPC(__VLIBCCALL mq_open)(char const *__restrict __name, __oflag_t __oflags, ...) __CASMNAME_SAME("mq_open");
#endif /* __CRT_HAVE_mq_open */
/* >> mq_close(3) */
__CDECLARE_OPT(,int,__NOTHROW,mq_close,(mqd_t __mqdes),(__mqdes))
/* >> mq_getattr(3) */
__CDECLARE_OPT(__ATTR_OUT(2),int,__NOTHROW_NCX,mq_getattr,(mqd_t __mqdes, struct mq_attr *__restrict __mqstat),(__mqdes,__mqstat))
/* >> mq_setattr(3) */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,mq_setattr,(mqd_t __mqdes, struct mq_attr const *__restrict __mqstat, struct mq_attr *__restrict __old_mqstat),(__mqdes,__mqstat,__old_mqstat))
/* >> mq_unlink(3) */
__CDECLARE_OPT(__ATTR_IN(1),int,__NOTHROW_NCX,mq_unlink,(char const *__name),(__name))
/* >> mq_notify(3) */
__CDECLARE_OPT(,int,__NOTHROW_NCX,mq_notify,(mqd_t __mqdes, struct sigevent const *__notification),(__mqdes,__notification))
/* >> mq_receive(3) */
__CDECLARE_OPT(__ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,mq_receive,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio))
/* >> mq_send(3) */
__CDECLARE_OPT(__ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_send,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio),(__mqdes,__msg_ptr,__msg_len,__msg_prio))

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_mq_timedreceive) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__CDECLARE(__ATTR_IN(5) __ATTR_OUTS(2, 3) __ATTR_OUT_OPT(4),__SSIZE_TYPE__,__NOTHROW_RPC,mq_timedreceive,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec const *__restrict __abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedreceive64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_OUTS(2, 3) __ATTR_OUT_OPT(4),__SSIZE_TYPE__,__NOTHROW_RPC,mq_timedreceive,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec const *__restrict __abs_timeout),mq_timedreceive64,(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_____mq_timedreceive_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_OUTS(2, 3) __ATTR_OUT_OPT(4),__SSIZE_TYPE__,__NOTHROW_RPC,mq_timedreceive,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec const *__restrict __abs_timeout),____mq_timedreceive_time64,(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedreceive64) || defined(__CRT_HAVE___mq_timedreceive_time64) || defined(__CRT_HAVE_mq_timedreceive)
#include <libc/local/mqueue/mq_timedreceive.h>
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mq_timedreceive, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_OUTS(2, 3) __ATTR_OUT_OPT(4) __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL mq_timedreceive)(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec const *__restrict __abs_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mq_timedreceive))(__mqdes, __msg_ptr, __msg_len, __pmsg_prio, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_mq_timedsend) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mq_timedsend(3), mq_timedsend64(3) */
__CDECLARE(__ATTR_IN(5) __ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_timedsend,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedsend64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mq_timedsend(3), mq_timedsend64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_timedsend,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec const *__abs_timeout),mq_timedsend64,(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#elif defined(__CRT_HAVE___mq_timedsend_time64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> mq_timedsend(3), mq_timedsend64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_timedsend,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec const *__abs_timeout),__mq_timedsend_time64,(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedsend64) || defined(__CRT_HAVE___mq_timedsend_time64) || defined(__CRT_HAVE_mq_timedsend)
#include <libc/local/mqueue/mq_timedsend.h>
/* >> mq_timedsend(3), mq_timedsend64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mq_timedsend, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_INS(2, 3) int __NOTHROW_RPC(__LIBCCALL mq_timedsend)(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec const *__abs_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mq_timedsend))(__mqdes, __msg_ptr, __msg_len, __msg_prio, __abs_timeout); })
#endif /* ... */

#ifdef __USE_TIME64
#if defined(__CRT_HAVE_mq_timedreceive) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,mq_timedreceive64,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec64 const *__restrict __abs_timeout),mq_timedreceive,(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedreceive64)
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__CDECLARE(__ATTR_IN(5) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,mq_timedreceive64,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec64 const *__restrict __abs_timeout),(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#elif defined(__CRT_HAVE___mq_timedreceive_time64)
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_OUTS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,mq_timedreceive64,(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec64 const *__restrict __abs_timeout),__mq_timedreceive_time64,(__mqdes,__msg_ptr,__msg_len,__pmsg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedreceive)
#include <libc/local/mqueue/mq_timedreceive64.h>
/* >> mq_timedreceive(3), mq_timedreceive64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mq_timedreceive64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_OUTS(2, 3) __SSIZE_TYPE__ __NOTHROW_RPC(__LIBCCALL mq_timedreceive64)(mqd_t __mqdes, char *__restrict __msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int *__pmsg_prio, struct timespec64 const *__restrict __abs_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mq_timedreceive64))(__mqdes, __msg_ptr, __msg_len, __pmsg_prio, __abs_timeout); })
#endif /* ... */
#if defined(__CRT_HAVE_mq_timedsend) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> mq_timedsend(3), mq_timedsend64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_timedsend64,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec64 const *__abs_timeout),mq_timedsend,(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedsend64)
/* >> mq_timedsend(3), mq_timedsend64(3) */
__CDECLARE(__ATTR_IN(5) __ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_timedsend64,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec64 const *__abs_timeout),(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#elif defined(__CRT_HAVE___mq_timedsend_time64)
/* >> mq_timedsend(3), mq_timedsend64(3) */
__CREDIRECT(__ATTR_IN(5) __ATTR_INS(2, 3),int,__NOTHROW_RPC,mq_timedsend64,(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec64 const *__abs_timeout),__mq_timedsend_time64,(__mqdes,__msg_ptr,__msg_len,__msg_prio,__abs_timeout))
#elif defined(__CRT_HAVE_mq_timedsend)
#include <libc/local/mqueue/mq_timedsend64.h>
/* >> mq_timedsend(3), mq_timedsend64(3) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mq_timedsend64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(5) __ATTR_INS(2, 3) int __NOTHROW_RPC(__LIBCCALL mq_timedsend64)(mqd_t __mqdes, char const *__msg_ptr, __SIZE_TYPE__ __msg_len, unsigned int __msg_prio, struct timespec64 const *__abs_timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mq_timedsend64))(__mqdes, __msg_ptr, __msg_len, __msg_prio, __abs_timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_MQUEUE_H */
