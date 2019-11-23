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
#ifndef GUARD_LIBC_USER_BITS_RESOURCE_C
#define GUARD_LIBC_USER_BITS_RESOURCE_C 1

#include "../api.h"
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
	(void)pid;
	(void)resource;
	(void)new_limit;
	(void)old_limit;
	CRT_UNIMPLEMENTED("prlimit"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:prlimit]]]*/

/*[[[head:prlimit64,hash:CRC-32=0xfad2914a]]]*/
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
DEFINE_INTERN_ALIAS(libc_prlimit64, libc_prlimit);
#else
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.resource.prlimit64") int
NOTHROW_NCX(LIBCCALL libc_prlimit64)(pid_t pid,
                                     __rlimit_resource_t resource,
                                     struct rlimit64 const *new_limit,
                                     struct rlimit64 *old_limit)
/*[[[body:prlimit64]]]*/
{
	(void)pid;
	(void)resource;
	(void)new_limit;
	(void)old_limit;
	CRT_UNIMPLEMENTED("prlimit64"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
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
