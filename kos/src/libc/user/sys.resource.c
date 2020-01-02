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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_RESOURCE_C
#define GUARD_LIBC_USER_SYS_RESOURCE_C 1

#include "../api.h"
#include "sys.resource.h"
#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:getrlimit,hash:CRC-32=0xf680a78f]]]*/
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.getrlimit") int
NOTHROW_NCX(LIBCCALL libc_getrlimit)(__rlimit_resource_t resource,
                                     struct rlimit *rlimits)
/*[[[body:getrlimit]]]*/
{
	errno_t error;
	error = sys_getrlimit((syscall_ulong_t)resource, rlimits);
	return libc_seterrno_syserr(error);
}
/*[[[end:getrlimit]]]*/

/*[[[head:setrlimit,hash:CRC-32=0xd8b536dc]]]*/
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.setrlimit") int
NOTHROW_NCX(LIBCCALL libc_setrlimit)(__rlimit_resource_t resource,
                                     struct rlimit const *rlimits)
/*[[[body:setrlimit]]]*/
{
	errno_t error;
	error = sys_setrlimit((syscall_ulong_t)resource, rlimits);
	return libc_seterrno_syserr(error);
}
/*[[[end:setrlimit]]]*/

/*[[[head:getrusage,hash:CRC-32=0xbec786ef]]]*/
/* Return resource usage information on process indicated by WHO
 * and put it in *USAGE. Returns 0 for success, -1 for failure */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.getrusage") int
NOTHROW_NCX(LIBCCALL libc_getrusage)(__rusage_who_t who,
                                     struct rusage *usage)
/*[[[body:getrusage]]]*/
{
	errno_t error;
	error = sys_getrusage((syscall_slong_t)who, usage);
	return libc_seterrno_syserr(error);
}
/*[[[end:getrusage]]]*/

/*[[[head:getpriority,hash:CRC-32=0x67344261]]]*/
/* Return the highest priority of any process specified by WHICH and
 * WHO (see above); if WHO is zero, the current process, process group,
 * or user (as specified by WHO) is used.  A lower priority number means
 * higher priority. Priorities range from PRIO_MIN to PRIO_MAX (above) */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.getpriority") int
NOTHROW_NCX(LIBCCALL libc_getpriority)(__priority_which_t which,
                                       id_t who)
/*[[[body:getpriority]]]*/
{
	syscall_slong_t result;
	result = sys_getpriority((syscall_ulong_t)which, who);
	if unlikely(E_ISERR(result)) {
		libc_seterrno(-result);
		return -1;
	}
	return (int)(20 - result);
}
/*[[[end:getpriority]]]*/

/*[[[head:setpriority,hash:CRC-32=0xc81fe9d0]]]*/
/* Set the priority of all processes specified by WHICH and WHO (see above) to PRIO.
 * Returns 0 on success, -1 on errors */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.setpriority") int
NOTHROW_NCX(LIBCCALL libc_setpriority)(__priority_which_t which,
                                       id_t who,
                                       int prio)
/*[[[body:setpriority]]]*/
{
	errno_t error;
	error = sys_setpriority((syscall_ulong_t)which, who, (syscall_ulong_t)(20 - prio));
	return libc_seterrno_syserr(error);
}
/*[[[end:setpriority]]]*/

/*[[[head:getrlimit64,hash:CRC-32=0xcdba0ca9]]]*/
/* Put the soft and hard limits for RESOURCE in *RLIMITS.
 * Returns 0 if successful, -1 if not (and sets errno) */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_getrlimit64, libc_getrlimit);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.getrlimit64") int
NOTHROW_NCX(LIBCCALL libc_getrlimit64)(__rlimit_resource_t resource,
                                       struct rlimit64 *rlimits)
/*[[[body:getrlimit64]]]*/
{
	(void)resource;
	(void)rlimits;
	CRT_UNIMPLEMENTED("getrlimit64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:getrlimit64]]]*/

/*[[[head:setrlimit64,hash:CRC-32=0x9cb114d0]]]*/
/* Set the soft and hard limits for RESOURCE to *RLIMITS.
 * Only the super-user can increase hard limits.
 * Return 0 if successful, -1 if not (and sets errno) */
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_setrlimit64, libc_setrlimit);
#else
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.setrlimit64") int
NOTHROW_NCX(LIBCCALL libc_setrlimit64)(__rlimit_resource_t resource,
                                       struct rlimit64 const *rlimits)
/*[[[body:setrlimit64]]]*/
{
	(void)resource;
	(void)rlimits;
	CRT_UNIMPLEMENTED("setrlimit64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
#endif /* MAGIC:alias */
/*[[[end:setrlimit64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x181f7199]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(getrlimit, libc_getrlimit);
DEFINE_PUBLIC_WEAK_ALIAS(setrlimit, libc_setrlimit);
DEFINE_PUBLIC_WEAK_ALIAS(getrusage, libc_getrusage);
DEFINE_PUBLIC_WEAK_ALIAS(getpriority, libc_getpriority);
DEFINE_PUBLIC_WEAK_ALIAS(setpriority, libc_setpriority);
DEFINE_PUBLIC_WEAK_ALIAS(getrlimit64, libc_getrlimit64);
DEFINE_PUBLIC_WEAK_ALIAS(setrlimit64, libc_setrlimit64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_RESOURCE_C */
