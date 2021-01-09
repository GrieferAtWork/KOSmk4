/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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

/*[[[head:libc_sysinfo,hash:CRC-32=0x8a97e059]]]*/
INTERN ATTR_SECTION(".text.crt.system.info") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sysinfo)(struct sysinfo *info)
/*[[[body:libc_sysinfo]]]*/
{
	errno_t error;
	error = sys_sysinfo(info);
	return libc_seterrno_syserr(error);
}
/*[[[end:libc_sysinfo]]]*/

/*[[[head:libc_get_nprocs_conf,hash:CRC-32=0x53f971d4]]]*/
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED int
NOTHROW_RPC(LIBCCALL libc_get_nprocs_conf)(void)
/*[[[body:libc_get_nprocs_conf]]]*/
{
	/* TODO: Configured processor count (aka: The kernel's `cpu_count' global) */
	CRT_UNIMPLEMENTED("get_nprocs_conf"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:libc_get_nprocs_conf]]]*/

/*[[[head:libc_get_nprocs,hash:CRC-32=0xfaee0d0a]]]*/
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED int
NOTHROW_RPC(LIBCCALL libc_get_nprocs)(void)
/*[[[body:libc_get_nprocs]]]*/
{
	struct sysinfo info;
	if (libc_sysinfo(&info))
		return -1;
	return info.procs;
}
/*[[[end:libc_get_nprocs]]]*/

/*[[[head:libc_get_phys_pages,hash:CRC-32=0x168dd9bc]]]*/
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED intptr_t
NOTHROW_RPC(LIBCCALL libc_get_phys_pages)(void)
/*[[[body:libc_get_phys_pages]]]*/
{
	struct sysinfo info;
	if (libc_sysinfo(&info))
		return -1;
	return info.totalram / info.mem_unit;
}
/*[[[end:libc_get_phys_pages]]]*/

/*[[[head:libc_get_avphys_pages,hash:CRC-32=0xce963906]]]*/
INTERN ATTR_SECTION(".text.crt.system.info") WUNUSED intptr_t
NOTHROW_RPC(LIBCCALL libc_get_avphys_pages)(void)
/*[[[body:libc_get_avphys_pages]]]*/
{
	struct sysinfo info;
	if (libc_sysinfo(&info))
		return -1;
	return info.freeram / info.mem_unit;
}
/*[[[end:libc_get_avphys_pages]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xb9ffe000]]]*/
DEFINE_PUBLIC_ALIAS(sysinfo, libc_sysinfo);
DEFINE_PUBLIC_ALIAS(get_nprocs_conf, libc_get_nprocs_conf);
DEFINE_PUBLIC_ALIAS(get_nprocs, libc_get_nprocs);
DEFINE_PUBLIC_ALIAS(get_phys_pages, libc_get_phys_pages);
DEFINE_PUBLIC_ALIAS(get_avphys_pages, libc_get_avphys_pages);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_SYSINFO_C */
