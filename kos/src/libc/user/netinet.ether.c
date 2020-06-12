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





/*[[[head:libc_ether_ntohost,hash:CRC-32=0xde2eeb9d]]]*/
/* Map 48 bit Ethernet number ADDR to HOSTNAME */
INTERN ATTR_SECTION(".text.crt.net.ether") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntohost)(char *hostname,
                                             struct ether_addr const *addr)
/*[[[body:libc_ether_ntohost]]]*/
/*AUTO*/{
	(void)hostname;
	(void)addr;
	CRT_UNIMPLEMENTED("ether_ntohost"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ether_ntohost]]]*/

/*[[[head:libc_ether_hostton,hash:CRC-32=0x48f2c32b]]]*/
/* Map HOSTNAME to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.net.ether") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_hostton)(char const *hostname,
                                             struct ether_addr *addr)
/*[[[body:libc_ether_hostton]]]*/
/*AUTO*/{
	(void)hostname;
	(void)addr;
	CRT_UNIMPLEMENTED("ether_hostton"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_ether_hostton]]]*/


/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xa341c61b]]]*/
DEFINE_PUBLIC_ALIAS(ether_ntohost, libc_ether_ntohost);
DEFINE_PUBLIC_ALIAS(ether_hostton, libc_ether_hostton);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_ETHER_C */
