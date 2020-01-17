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
#ifndef GUARD_LIBC_USER_BITS_RESOURCE_C
#define GUARD_LIBC_USER_BITS_RESOURCE_C 1

#include "../api.h"
/**/

#include <kos/syscalls.h>

#include "bits.resource.h"

DECL_BEGIN

/*[[[start:implementation]]]*/

/*[[[head:prlimit,hash:CRC-32=0x9eaefd14]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.prlimit") int
NOTHROW_NCX(LIBCCALL libc_prlimit)(pid_t pid,
                                   __rlimit_resource_t resource,
                                   struct rlimit const *new_limit,
                                   struct rlimit *old_limit)
/*[[[body:prlimit]]]*/
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
/*[[[end:prlimit]]]*/

/*[[[head:prlimit64,hash:CRC-32=0x6a07d8b3]]]*/
#if __SIZEOF_RLIM32_T__ == __SIZEOF_RLIM64_T__
DEFINE_INTERN_ALIAS(libc_prlimit64, libc_prlimit);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.prlimit64") int
NOTHROW_NCX(LIBCCALL libc_prlimit64)(pid_t pid,
                                     __rlimit_resource_t resource,
                                     struct rlimit64 const *new_limit,
                                     struct rlimit64 *old_limit)
/*[[[body:prlimit64]]]*/
{
	errno_t error;
	error = sys_prlimit64(pid, (syscall_ulong_t)resource, new_limit, old_limit);
	return libc_seterrno_syserr(error);
}
#endif /* MAGIC:alias */
/*[[[end:prlimit64]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xa01dde2b]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(prlimit, libc_prlimit);
DEFINE_PUBLIC_WEAK_ALIAS(prlimit64, libc_prlimit64);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_BITS_RESOURCE_C */
