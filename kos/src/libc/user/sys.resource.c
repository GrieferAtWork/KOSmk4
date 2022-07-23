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
#ifndef GUARD_LIBC_USER_SYS_RESOURCE_C
#define GUARD_LIBC_USER_SYS_RESOURCE_C 1

#include "../api.h"
/**/

#include <bits/os/rusage-convert.h>
#include <kos/syscalls.h>

#include "sys.resource.h"

DECL_BEGIN

/*[[[head:libc_prlimit,hash:CRC-32=0x8c307272]]]*/
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_IN_OPT(3) ATTR_OUT_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_prlimit)(pid_t pid,
                                   __rlimit_resource_t resource,
                                   struct rlimit const *new_limit,
                                   struct rlimit *old_limit)
/*[[[body:libc_prlimit]]]*/
{
	errno_t error;
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
	error = sys_prlimit64(pid, (syscall_ulong_t)resource,
	                      (struct rlimit64 const *)new_limit,
	                      (struct rlimit64 *)old_limit);
#else /* __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__ */
	struct rlimit64 nl, ol;
	if (new_limit) {
		nl.rlim_cur = (rlim64_t)new_limit->rlim_cur;
		nl.rlim_max = (rlim64_t)new_limit->rlim_max;
	}
	error = sys_prlimit64(pid, (syscall_ulong_t)resource,
	                      new_limit ? &nl : NULL,
	                      old_limit ? &ol : NULL);
	if (old_limit && E_ISOK(error)) {
		old_limit->rlim_cur = (rlim_t)ol.rlim_cur;
		old_limit->rlim_max = (rlim_t)ol.rlim_max;
	}
#endif /* __SIZEOF_RLIM32_T__ != __SIZEOF_RLIM64_T__ */
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_prlimit]]]*/

/*[[[head:libc_prlimit64,hash:CRC-32=0x1ac4e6a]]]*/
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
DEFINE_INTERN_ALIAS(libc_prlimit64, libc_prlimit);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_IN_OPT(3) ATTR_OUT_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_prlimit64)(pid_t pid,
                                     __rlimit_resource_t resource,
                                     struct rlimit64 const *new_limit,
                                     struct rlimit64 *old_limit)
/*[[[body:libc_prlimit64]]]*/
{
	errno_t error;
	error = sys_prlimit64(pid, (syscall_ulong_t)resource, new_limit, old_limit);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_prlimit64]]]*/

/*[[[head:libc_getrlimit,hash:CRC-32=0xa563f118]]]*/
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getrlimit)(__rlimit_resource_t resource,
                                     struct rlimit *rlimits)
/*[[[body:libc_getrlimit]]]*/
{
	errno_t error;
	error = sys_getrlimit((syscall_ulong_t)resource, rlimits);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getrlimit]]]*/

/*[[[head:libc_getrlimit64,hash:CRC-32=0x902089e9]]]*/
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
DEFINE_INTERN_ALIAS(libc_getrlimit64, libc_getrlimit);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getrlimit64)(__rlimit_resource_t resource,
                                       struct rlimit64 *rlimits)
/*[[[body:libc_getrlimit64]]]*/
{
	return libc_prlimit64(0, resource, NULL, rlimits);
}
#endif /* MAGIC:alias */
/*[[[end:libc_getrlimit64]]]*/

/*[[[head:libc_setrlimit,hash:CRC-32=0xbd0184d0]]]*/
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_setrlimit)(__rlimit_resource_t resource,
                                     struct rlimit const *rlimits)
/*[[[body:libc_setrlimit]]]*/
{
	errno_t error;
	error = sys_setrlimit((syscall_ulong_t)resource, rlimits);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setrlimit]]]*/

/*[[[head:libc_setrlimit64,hash:CRC-32=0x4bbde954]]]*/
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
DEFINE_INTERN_ALIAS(libc_setrlimit64, libc_setrlimit);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_setrlimit64)(__rlimit_resource_t resource,
                                       struct rlimit64 const *rlimits)
/*[[[body:libc_setrlimit64]]]*/
{
	return libc_prlimit64(0, resource, rlimits, NULL);
}
#endif /* MAGIC:alias */
/*[[[end:libc_setrlimit64]]]*/

/*[[[head:libc_getrusage,hash:CRC-32=0xf8cd9fa2]]]*/
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getrusage)(__rusage_who_t who,
                                     struct rusage *usage)
/*[[[body:libc_getrusage]]]*/
{
	errno_t error;
	error = sys_getrusage((syscall_slong_t)who, usage);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_getrusage]]]*/

/*[[[head:libc_getrusage64,hash:CRC-32=0xbeb9ead8]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_getrusage64, libc_getrusage);
#else /* MAGIC:alias */
INTERN ATTR_SECTION(".text.crt.sched.resource") ATTR_OUT(2) int
NOTHROW_NCX(LIBCCALL libc_getrusage64)(__rusage_who_t who,
                                       struct rusage64 *usage)
/*[[[body:libc_getrusage64]]]*/
{
	errno_t error;
#ifdef SYS_getrusage64
	error = sys_getrusage64((syscall_slong_t)who, usage);
#else /* SYS_getrusage64 */
	struct rusage ru;
	error = sys_getrusage((syscall_slong_t)who, &ru);
	if (E_ISOK(error))
		rusage32_to_rusage64(&ru, usage);
#endif /* !SYS_getrusage64 */
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:libc_getrusage64]]]*/

/*[[[head:libc_getpriority,hash:CRC-32=0xff1d3dce]]]*/
/* >> getpriority(2), setpriority(2)
 * @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER'
 * @param: who:   An ID in the namespace indicated by `which' */
INTERN ATTR_SECTION(".text.crt.sched.resource") int
NOTHROW_NCX(LIBCCALL libc_getpriority)(__priority_which_t which,
                                       id_t who)
/*[[[body:libc_getpriority]]]*/
{
	syscall_slong_t result;
	result = sys_getpriority((syscall_ulong_t)which, who);
	if unlikely(E_ISERR(result))
		return libc_seterrno_neg(result);
	return (int)(20 - result);
}
/*[[[end:libc_getpriority]]]*/

/*[[[head:libc_setpriority,hash:CRC-32=0x1a043b74]]]*/
/* >> getpriority(2), setpriority(2)
 * @param: which: One of `PRIO_PROCESS', `PRIO_PGRP' or `PRIO_USER'
 * @param: who:   An ID in the namespace indicated by `which' */
INTERN ATTR_SECTION(".text.crt.sched.resource") int
NOTHROW_NCX(LIBCCALL libc_setpriority)(__priority_which_t which,
                                       id_t who,
                                       int prio)
/*[[[body:libc_setpriority]]]*/
{
	errno_t error;
	error = sys_setpriority((syscall_ulong_t)which, who, (syscall_ulong_t)(20 - prio));
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_setpriority]]]*/





/*[[[start:exports,hash:CRC-32=0xda0b99f9]]]*/
DEFINE_PUBLIC_ALIAS(prlimit, libc_prlimit);
DEFINE_PUBLIC_ALIAS(prlimit64, libc_prlimit64);
DEFINE_PUBLIC_ALIAS(__getrlimit, libc_getrlimit);
DEFINE_PUBLIC_ALIAS(__libc_getrlimit, libc_getrlimit);
DEFINE_PUBLIC_ALIAS(getrlimit, libc_getrlimit);
DEFINE_PUBLIC_ALIAS(__setrlimit, libc_setrlimit);
DEFINE_PUBLIC_ALIAS(__libc_setrlimit, libc_setrlimit);
DEFINE_PUBLIC_ALIAS(setrlimit, libc_setrlimit);
DEFINE_PUBLIC_ALIAS(__getrusage, libc_getrusage);
DEFINE_PUBLIC_ALIAS(__libc_getrusage, libc_getrusage);
DEFINE_PUBLIC_ALIAS(getrusage, libc_getrusage);
DEFINE_PUBLIC_ALIAS(getrusage64, libc_getrusage64);
DEFINE_PUBLIC_ALIAS(getpriority, libc_getpriority);
DEFINE_PUBLIC_ALIAS(__setpriority, libc_setpriority);
DEFINE_PUBLIC_ALIAS(__libc_setpriority, libc_setpriority);
DEFINE_PUBLIC_ALIAS(setpriority, libc_setpriority);
DEFINE_PUBLIC_ALIAS(getrlimit64, libc_getrlimit64);
DEFINE_PUBLIC_ALIAS(setrlimit64, libc_setrlimit64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RESOURCE_C */
