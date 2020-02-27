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
#ifndef GUARD_LIBC_USER_NETINET_ETHER_C
#define GUARD_LIBC_USER_NETINET_ETHER_C 1

#include "../api.h"
#include "netinet.ether.h"

DECL_BEGIN





/*[[[start:implementation]]]*/





/*[[[head:ether_ntohost,hash:CRC-32=0x5eed1bb3]]]*/
/* Map 48 bit Ethernet number ADDR to HOSTNAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_ntohost") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntohost)(char *hostname,
                                             struct ether_addr const *addr)
/*[[[body:ether_ntohost]]]*/
{
	(void)hostname;
	(void)addr;
	CRT_UNIMPLEMENTED("ether_ntohost"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ether_ntohost]]]*/

/*[[[head:ether_hostton,hash:CRC-32=0xf9ac0d61]]]*/
/* Map HOSTNAME to 48 bit Ethernet address */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_hostton") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_hostton)(char const *hostname,
                                             struct ether_addr *addr)
/*[[[body:ether_hostton]]]*/
{
	(void)hostname;
	(void)addr;
	CRT_UNIMPLEMENTED("ether_hostton"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ether_hostton]]]*/


/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xbc051e5a]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(ether_ntohost, libc_ether_ntohost);
DEFINE_PUBLIC_WEAK_ALIAS(ether_hostton, libc_ether_hostton);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_ETHER_C */
