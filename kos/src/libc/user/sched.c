/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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

/*[[[head:sched_setparam,hash:0x732e3a11]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_setparam") int
NOTHROW_NCX(LIBCCALL libc_sched_setparam)(pid_t pid,
                                          struct sched_param const *param)
/*[[[body:sched_setparam]]]*/
{
	errno_t result;
	result = sys_sched_setparam(pid, param);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_setparam]]]*/

/*[[[head:sched_getparam,hash:0xfe915620]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_getparam") int
NOTHROW_NCX(LIBCCALL libc_sched_getparam)(pid_t pid,
                                          struct sched_param *param)
/*[[[body:sched_getparam]]]*/
{
	errno_t result;
	result = sys_sched_getparam(pid, param);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_getparam]]]*/

/*[[[head:sched_setscheduler,hash:0x60db43cf]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_setscheduler") int
NOTHROW_NCX(LIBCCALL libc_sched_setscheduler)(pid_t pid,
                                              int policy,
                                              struct sched_param const *param)
/*[[[body:sched_setscheduler]]]*/
{
	errno_t result;
	result = sys_sched_setscheduler(pid,
	                                (syscall_ulong_t)(unsigned int)policy,
	                                param);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_setscheduler]]]*/

/*[[[head:sched_getscheduler,hash:0x910b5243]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_getscheduler") int
NOTHROW_NCX(LIBCCALL libc_sched_getscheduler)(pid_t pid)
/*[[[body:sched_getscheduler]]]*/
{
	syscall_slong_t result;
	result = sys_sched_getscheduler(pid);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_getscheduler]]]*/

/*[[[head:sched_yield,hash:0x9019085c]]]*/
/* @return: 1: Another thread was executed prior to the function returning
 *             The thread may not necessarily be apart of the calling process
 * @return: 0: The function returned immediately when no other thread was executed */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.thread.sched_yield") int
NOTHROW_NCX(LIBCCALL libc_sched_yield)(void)
/*[[[body:sched_yield]]]*/
{
	errno_t result;
	result = sys_sched_yield();
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_yield]]]*/

/*[[[head:sched_get_priority_max,hash:0x3cd840ff]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_get_priority_max") int
NOTHROW_NCX(LIBCCALL libc_sched_get_priority_max)(int algorithm)
/*[[[body:sched_get_priority_max]]]*/
{
	syscall_slong_t result;
	result = sys_sched_get_priority_max((syscall_ulong_t)(unsigned int)algorithm);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_get_priority_max]]]*/

/*[[[head:sched_get_priority_min,hash:0x1d398b47]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_get_priority_min") int
NOTHROW_NCX(LIBCCALL libc_sched_get_priority_min)(int algorithm)
/*[[[body:sched_get_priority_min]]]*/
{
	syscall_slong_t result;
	result = sys_sched_get_priority_min((syscall_ulong_t)(unsigned int)algorithm);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_get_priority_min]]]*/

/*[[[head:sched_setaffinity,hash:0xf5de87e4]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_setaffinity") int
NOTHROW_NCX(LIBCCALL libc_sched_setaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t const *cpuset)
/*[[[body:sched_setaffinity]]]*/
{
	errno_t result;
	result = sys_sched_setaffinity(pid, cpusetsize, cpuset);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_setaffinity]]]*/

/*[[[head:sched_getaffinity,hash:0x347f1597]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_getaffinity") int
NOTHROW_NCX(LIBCCALL libc_sched_getaffinity)(pid_t pid,
                                             size_t cpusetsize,
                                             cpu_set_t *cpuset)
/*[[[body:sched_getaffinity]]]*/
{
	errno_t result;
	result = sys_sched_getaffinity(pid, cpusetsize, cpuset);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_getaffinity]]]*/

/*[[[head:sched_rr_get_interval,hash:0xb45ded83]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_rr_get_interval") int
NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval)(pid_t pid,
                                                 struct timespec *tms)
/*[[[body:sched_rr_get_interval]]]*/
{
	errno_t result;
	result = sys_sched_rr_get_interval(pid, tms);
	return libc_seterrno_syserr(result);
}
/*[[[end:sched_rr_get_interval]]]*/

/*[[[head:sched_rr_get_interval64,hash:0xabc4a16e]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sched_rr_get_interval64, libc_sched_rr_get_interval);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.param.sched_rr_get_interval64") int
NOTHROW_NCX(LIBCCALL libc_sched_rr_get_interval64)(pid_t pid,
                                                   struct timespec64 *tms)
/*[[[body:sched_rr_get_interval64]]]*/
{
	errno_t result;
	result = sys_sched_rr_get_interval64(pid, tms);
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:sched_rr_get_interval64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xfc364c5e]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(sched_setparam, libc_sched_setparam);
DEFINE_PUBLIC_WEAK_ALIAS(sched_getparam, libc_sched_getparam);
DEFINE_PUBLIC_WEAK_ALIAS(sched_setscheduler, libc_sched_setscheduler);
DEFINE_PUBLIC_WEAK_ALIAS(sched_getscheduler, libc_sched_getscheduler);
DEFINE_PUBLIC_WEAK_ALIAS(sched_yield, libc_sched_yield);
DEFINE_PUBLIC_WEAK_ALIAS(sched_get_priority_max, libc_sched_get_priority_max);
DEFINE_PUBLIC_WEAK_ALIAS(sched_get_priority_min, libc_sched_get_priority_min);
DEFINE_PUBLIC_WEAK_ALIAS(sched_setaffinity, libc_sched_setaffinity);
DEFINE_PUBLIC_WEAK_ALIAS(sched_getaffinity, libc_sched_getaffinity);
DEFINE_PUBLIC_WEAK_ALIAS(sched_rr_get_interval, libc_sched_rr_get_interval);
DEFINE_PUBLIC_WEAK_ALIAS(sched_rr_get_interval64, libc_sched_rr_get_interval64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SCHED_C */
