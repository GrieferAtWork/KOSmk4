/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SYS_SYSINFO_C
#define GUARD_LIBC_USER_SYS_SYSINFO_C 1

#include "../api.h"
/**/

#include "sys.sysinfo.h"

#include <kos/syscalls.h>

DECL_BEGIN

/*[[[head:libc_sysinfo,hash:CRC-32=0x9ceb1159]]]*/
/* >> sysinfo(2)
 * Return current system information */
INTERN ATTR_SECTION(".text.crt.system.info") ATTR_OUT(1) int
NOTHROW_NCX(LIBCCALL libc_sysinfo)(struct sysinfo *info)
/*[[[body:libc_sysinfo]]]*/
{
	errno_t error;
	error = sys_sysinfo(info);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_sysinfo]]]*/

/*[[[head:libc_get_nprocs_conf,hash:CRC-32=0xd8904d5f]]]*/
/* >> get_nprocs_conf(3)
 * Return the # of configured online processors */
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED int
NOTHROW(LIBCCALL libc_get_nprocs_conf)(void)
/*[[[body:libc_get_nprocs_conf]]]*/
{
	/* TODO: Configured processor count (aka: The kernel's `cpu_count' global) */
	CRT_UNIMPLEMENTED("get_nprocs_conf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_get_nprocs_conf]]]*/

/*[[[head:libc_get_nprocs,hash:CRC-32=0x97ca2425]]]*/
/* >> get_nprocs(3)
 * Return the # of currently online processors */
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED int
NOTHROW(LIBCCALL libc_get_nprocs)(void)
/*[[[body:libc_get_nprocs]]]*/
{
	/* TODO: Active processor count (aka: The kernel's `cpu_online_count' global) */
	CRT_UNIMPLEMENTED("get_nprocs"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_get_nprocs]]]*/



/*[[[start:exports,hash:CRC-32=0x75ef5eda]]]*/
DEFINE_PUBLIC_ALIAS(__sysinfo, libc_sysinfo);
DEFINE_PUBLIC_ALIAS(__libc_sysinfo, libc_sysinfo);
DEFINE_PUBLIC_ALIAS(sysinfo, libc_sysinfo);
DEFINE_PUBLIC_ALIAS(__get_nprocs_conf, libc_get_nprocs_conf);
DEFINE_PUBLIC_ALIAS(get_nprocs_conf, libc_get_nprocs_conf);
DEFINE_PUBLIC_ALIAS(__get_nprocs, libc_get_nprocs);
DEFINE_PUBLIC_ALIAS(get_nprocs, libc_get_nprocs);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSINFO_C */
