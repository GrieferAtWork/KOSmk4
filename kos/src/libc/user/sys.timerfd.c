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
#ifndef GUARD_LIBC_USER_SYS_TIMERFD_C
#define GUARD_LIBC_USER_SYS_TIMERFD_C 1

#include "../api.h"
#include "sys.timerfd.h"
#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_timerfd_create,hash:CRC-32=0xef68c1f9]]]*/
/* >> timerfd_create(2)
 * @param: flags: Set of `0 | TFD_NONBLOCK | TFD_CLOEXEC | TFD_CLOFORK' */
INTERN ATTR_SECTION(".text.crt.timer") fd_t
NOTHROW(LIBCCALL libc_timerfd_create)(clockid_t clock_id,
                                      __STDC_INT_AS_UINT_T flags)
/*[[[body:libc_timerfd_create]]]*/
{
	fd_t result;
	result = sys_timerfd_create(clock_id, flags);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_timerfd_create]]]*/

/*[[[head:libc_timerfd_settime,hash:CRC-32=0xe5c6c4a9]]]*/
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_FDARG(1) ATTR_IN(3) ATTR_OUT_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_timerfd_settime)(fd_t ufd,
                                           __STDC_INT_AS_UINT_T flags,
                                           struct itimerspec const *utmr,
                                           struct itimerspec *otmr)
/*[[[body:libc_timerfd_settime]]]*/
{
	errno_t error;
	error = sys_timerfd_settime(ufd, (syscall_ulong_t)flags, utmr, otmr);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timerfd_settime]]]*/

/*[[[head:libc_timerfd_gettime,hash:CRC-32=0x673d7632]]]*/
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_FDARG(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_timerfd_gettime)(fd_t ufd,
                                           struct itimerspec *__restrict otmr)
/*[[[body:libc_timerfd_gettime]]]*/
{
	errno_t error;
	error = sys_timerfd_gettime(ufd, otmr);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_timerfd_gettime]]]*/

/*[[[head:libc_timerfd_settime64,hash:CRC-32=0x707ececc]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timerfd_settime64, libc_timerfd_settime);
#else /* MAGIC:alias */
/* >> timerfd_settime(2), timerfd_settime64(2)
 * @param: flags: Set of `0 | TFD_TIMER_ABSTIME' */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_FDARG(1) ATTR_IN(3) ATTR_OUT_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_timerfd_settime64)(fd_t ufd,
                                             __STDC_INT_AS_UINT_T flags,
                                             struct itimerspec64 const *utmr,
                                             struct itimerspec64 *otmr)
/*[[[body:libc_timerfd_settime64]]]*/
{
	errno_t error;
	error = sys_timerfd_settime64(ufd, (syscall_ulong_t)flags, utmr, otmr);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_timerfd_settime64]]]*/

/*[[[head:libc_timerfd_gettime64,hash:CRC-32=0x95dc9f2c]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_timerfd_gettime64, libc_timerfd_gettime);
#else /* MAGIC:alias */
/* >> timerfd_gettime(2), timerfd_gettime64(2) */
INTERN ATTR_SECTION(".text.crt.timer") ATTR_FDARG(1) ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_timerfd_gettime64)(fd_t ufd,
                                             struct itimerspec64 *__restrict otmr)
/*[[[body:libc_timerfd_gettime64]]]*/
{
	errno_t error;
	error = sys_timerfd_gettime64(ufd, otmr);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_timerfd_gettime64]]]*/





/*[[[start:exports,hash:CRC-32=0xcd802ea5]]]*/
DEFINE_PUBLIC_ALIAS(timerfd_create, libc_timerfd_create);
DEFINE_PUBLIC_ALIAS(timerfd_settime, libc_timerfd_settime);
DEFINE_PUBLIC_ALIAS(timerfd_gettime, libc_timerfd_gettime);
#include <bits/types.h>
#if __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__
DEFINE_PUBLIC_ALIAS(__timerfd_settime64, libc_timerfd_settime64);
DEFINE_PUBLIC_ALIAS(timerfd_settime64, libc_timerfd_settime64);
DEFINE_PUBLIC_ALIAS(__timerfd_gettime64, libc_timerfd_gettime64);
DEFINE_PUBLIC_ALIAS(timerfd_gettime64, libc_timerfd_gettime64);
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMERFD_C */
