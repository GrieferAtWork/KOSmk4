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
#ifndef GUARD_LIBC_USER_SCHED_C
#define GUARD_LIBC_USER_SCHED_C 1

#include "../api.h"
#include "sched.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:libc_sched_setparam,hash:CRC-32=0xcfb2c3b7]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_setparam)(pid_t pid,
                                          struct sched_param const *param)
/*[[[body:libc_sched_setparam]]]*/
{
	errno_t result;
	result = sys_sched_setparam(pid, param);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_setparam]]]*/

/*[[[head:libc_sched_getparam,hash:CRC-32=0xb62a1dfb]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_getparam)(pid_t pid,
                                          struct sched_param *param)
/*[[[body:libc_sched_getparam]]]*/
{
	errno_t result;
	result = sys_sched_getparam(pid, param);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_getparam]]]*/

/*[[[head:libc_sched_setscheduler,hash:CRC-32=0xb5266c22]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_setscheduler)(pid_t pid,
                                              int policy,
                                              struct sched_param const *param)
/*[[[body:libc_sched_setscheduler]]]*/
{
	errno_t result;
	result = sys_sched_setscheduler(pid,
	                                (syscall_ulong_t)(unsigned int)policy,
	                                param);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_setscheduler]]]*/

/*[[[head:libc_sched_getscheduler,hash:CRC-32=0x73b26a5e]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_getscheduler)(pid_t pid)
/*[[[body:libc_sched_getscheduler]]]*/
{
	syscall_slong_t result;
	result = sys_sched_getscheduler(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_getscheduler]]]*/

/*[[[head:libc_sched_yield,hash:CRC-32=0x87ccb48a]]]*/
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
INTERN ATTR_SECTION(".text.crt.sched.thread") int
NOTHROW_NCX(LIBCCALL libc_sched_yield)(void)
/*[[[body:libc_sched_yield]]]*/
{
	errno_t result;
	result = sys_sched_yield();
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_yield]]]*/

/*[[[head:libc_sched_get_priority_max,hash:CRC-32=0xdd40b0c3]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_get_priority_max)(int algorithm)
/*[[[body:libc_sched_get_priority_max]]]*/
{
	syscall_slong_t result;
	result = sys_sched_get_priority_max((syscall_ulong_t)(unsigned int)algorithm);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_get_priority_max]]]*/

/*[[[head:libc_sched_get_priority_min,hash:CRC-32=0xf43e4ddb]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_get_priority_min)(int algorithm)
/*[[[body:libc_sched_get_priority_min]]]*/
{
	syscall_slong_t result;
	result = sys_sched_get_priority_min((syscall_ulong_t)(unsigned int)algorithm);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_get_priority_min]]]*/

/*[[[head:libc_sched_setaffinity,hash:CRC-32=0x29051901]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_setaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t const *cpuset)
/*[[[body:libc_sched_setaffinity]]]*/
{
	errno_t result;
	result = sys_sched_setaffinity(pid, cpusetsize, cpuset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_setaffinity]]]*/

/*[[[head:libc_sched_getaffinity,hash:CRC-32=0xf881fa30]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_getaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t *cpuset)
/*[[[body:libc_sched_getaffinity]]]*/
{
	errno_t result;
	result = sys_sched_getaffinity(pid, cpusetsize, cpuset);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_getaffinity]]]*/

/*[[[head:libc_sched_rr_get_interval,hash:CRC-32=0x6fe03650]]]*/
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval)(pid_t pid,
                                                 struct timespec *tms)
/*[[[body:libc_sched_rr_get_interval]]]*/
{
	errno_t result;
	result = sys_sched_rr_get_interval(pid, tms);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sched_rr_get_interval]]]*/

/*[[[head:libc_sched_rr_get_interval64,hash:CRC-32=0xf43b85ed]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sched_rr_get_interval64, libc_sched_rr_get_interval);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.param") int
NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval64)(pid_t pid,
                                                   struct timespec64 *tms)
/*[[[body:libc_sched_rr_get_interval64]]]*/
{
	errno_t result;
	result = sys_sched_rr_get_interval64(pid, tms);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_sched_rr_get_interval64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x772b6425]]]*/
DEFINE_PUBLIC_ALIAS(sched_setparam, libc_sched_setparam);
DEFINE_PUBLIC_ALIAS(__sched_getparam, libc_sched_getparam);
DEFINE_PUBLIC_ALIAS(sched_getparam, libc_sched_getparam);
DEFINE_PUBLIC_ALIAS(__sched_setscheduler, libc_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(sched_setscheduler, libc_sched_setscheduler);
DEFINE_PUBLIC_ALIAS(__sched_getscheduler, libc_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(sched_getscheduler, libc_sched_getscheduler);
DEFINE_PUBLIC_ALIAS(thrd_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(pthread_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(__sched_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(sched_yield, libc_sched_yield);
DEFINE_PUBLIC_ALIAS(__sched_get_priority_max, libc_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(sched_get_priority_max, libc_sched_get_priority_max);
DEFINE_PUBLIC_ALIAS(__sched_get_priority_min, libc_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(sched_get_priority_min, libc_sched_get_priority_min);
DEFINE_PUBLIC_ALIAS(sched_setaffinity, libc_sched_setaffinity);
DEFINE_PUBLIC_ALIAS(sched_getaffinity, libc_sched_getaffinity);
DEFINE_PUBLIC_ALIAS(sched_rr_get_interval, libc_sched_rr_get_interval);
DEFINE_PUBLIC_ALIAS(sched_rr_get_interval64, libc_sched_rr_get_interval64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SCHED_C */
