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
#ifndef GUARD_LIBC_USER_SYS_SYSINFO_C
#define GUARD_LIBC_USER_SYS_SYSINFO_C 1

#include "../api.h"
#include "sys.sysinfo.h"

#include <kos/syscalls.h>

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:sysinfo,hash:CRC-32=0x26384dcb]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.system.info.sysinfo") int
NOTHROW_RPC(LIBCCALL libc_sysinfo)(struct sysinfo *info)
/*[[[body:sysinfo]]]*/
{
	errno_t error;
	error = sys_sysinfo(info);
	return libc_seterrno_syserr(error);
}
/*[[[end:sysinfo]]]*/

/*[[[head:get_nprocs_conf,hash:CRC-32=0x5fbd960b]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.info.get_nprocs_conf") int
NOTHROW_RPC(LIBCCALL libc_get_nprocs_conf)(void)
/*[[[body:get_nprocs_conf]]]*/
{
	/* TODO: Configured processor count (aka: The kernel's `cpu_count' global) */
	CRT_UNIMPLEMENTED("get_nprocs_conf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:get_nprocs_conf]]]*/

/*[[[head:get_nprocs,hash:CRC-32=0xd29da6c8]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.info.get_nprocs") int
NOTHROW_RPC(LIBCCALL libc_get_nprocs)(void)
/*[[[body:get_nprocs]]]*/
{
	struct sysinfo info;
	if (libc_sysinfo(&info))
		return -1;
	return info.procs;
}
/*[[[end:get_nprocs]]]*/

/*[[[head:get_phys_pages,hash:CRC-32=0x88c7fce5]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.info.get_phys_pages") __INTPTR_TYPE__
NOTHROW_RPC(LIBCCALL libc_get_phys_pages)(void)
/*[[[body:get_phys_pages]]]*/
{
	struct sysinfo info;
	if (libc_sysinfo(&info))
		return -1;
	return info.totalram / info.mem_unit;
}
/*[[[end:get_phys_pages]]]*/

/*[[[head:get_avphys_pages,hash:CRC-32=0x46d41c4c]]]*/
INTERN WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.system.info.get_avphys_pages") __INTPTR_TYPE__
NOTHROW_RPC(LIBCCALL libc_get_avphys_pages)(void)
/*[[[body:get_avphys_pages]]]*/
{
	struct sysinfo info;
	if (libc_sysinfo(&info))
		return -1;
	return info.freeram / info.mem_unit;
}
/*[[[end:get_avphys_pages]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0x8a6ea4c]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(sysinfo, libc_sysinfo);
DEFINE_PUBLIC_WEAK_ALIAS(get_nprocs_conf, libc_get_nprocs_conf);
DEFINE_PUBLIC_WEAK_ALIAS(get_nprocs, libc_get_nprocs);
DEFINE_PUBLIC_WEAK_ALIAS(get_phys_pages, libc_get_phys_pages);
DEFINE_PUBLIC_WEAK_ALIAS(get_avphys_pages, libc_get_avphys_pages);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSINFO_C */
