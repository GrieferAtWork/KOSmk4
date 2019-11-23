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
#ifndef GUARD_LIBC_USER_IFADDRS_C
#define GUARD_LIBC_USER_IFADDRS_C 1

#include "../api.h"
#include "ifaddrs.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:getifaddrs,hash:CRC-32=0xe4d9ffa]]]*/
/* Create a linked list of `struct ifaddrs' structures, one for each
 * network interface on the host machine. If successful, store the
 * list in *IFAP and return 0. On errors, return -1 and set `errno'.
 * The storage returned in *IFAP is allocated dynamically and can
 * only be properly freed by passing it to `freeifaddrs' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.getifaddrs") int
NOTHROW_NCX(LIBCCALL libc_getifaddrs)(struct ifaddrs **ifap)
/*[[[body:getifaddrs]]]*/
{
	(void)ifap;
	CRT_UNIMPLEMENTED("getifaddrs"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:getifaddrs]]]*/

/*[[[head:freeifaddrs,hash:CRC-32=0x90a6ae29]]]*/
/* Reclaim the storage allocated by a previous `getifaddrs' call */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unsorted.freeifaddrs") void
NOTHROW_NCX(LIBCCALL libc_freeifaddrs)(struct ifaddrs *ifa)
/*[[[body:freeifaddrs]]]*/
{
	(void)ifa;
	CRT_UNIMPLEMENTED("freeifaddrs"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:freeifaddrs]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xb53e034d]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(getifaddrs, libc_getifaddrs);
DEFINE_PUBLIC_WEAK_ALIAS(freeifaddrs, libc_freeifaddrs);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_IFADDRS_C */
