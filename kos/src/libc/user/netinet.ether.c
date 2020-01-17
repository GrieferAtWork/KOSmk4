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

/*[[[head:ether_ntoa,hash:CRC-32=0x6872e776]]]*/
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_ntoa") char *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntoa)(struct ether_addr const *addr)
/*[[[body:ether_ntoa]]]*/
{
	(void)addr;
	CRT_UNIMPLEMENTED("ether_ntoa"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_ntoa]]]*/

/*[[[head:ether_ntoa_r,hash:CRC-32=0x9c4a939]]]*/
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_ntoa_r") char *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *addr,
                                            char *buf)
/*[[[body:ether_ntoa_r]]]*/
{
	(void)addr;
	(void)buf;
	CRT_UNIMPLEMENTED("ether_ntoa_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_ntoa_r]]]*/

/*[[[head:ether_aton,hash:CRC-32=0x88bf789c]]]*/
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_aton") struct ether_addr *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_aton)(char const *asc)
/*[[[body:ether_aton]]]*/
{
	(void)asc;
	CRT_UNIMPLEMENTED("ether_aton"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_aton]]]*/

/*[[[head:ether_aton_r,hash:CRC-32=0xf6e0249c]]]*/
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_aton_r") struct ether_addr *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_aton_r)(char const *asc,
                                            struct ether_addr *addr)
/*[[[body:ether_aton_r]]]*/
{
	(void)asc;
	(void)addr;
	CRT_UNIMPLEMENTED("ether_aton_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_aton_r]]]*/

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

/*[[[head:ether_line,hash:CRC-32=0xf8c61a51]]]*/
/* Scan LINE and set ADDR and HOSTNAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_line") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_line)(char const *line,
                                          struct ether_addr *addr,
                                          char *hostname)
/*[[[body:ether_line]]]*/
{
	(void)line;
	(void)addr;
	(void)hostname;
	CRT_UNIMPLEMENTED("ether_line"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ether_line]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc34b092b]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(ether_ntoa, libc_ether_ntoa);
DEFINE_PUBLIC_WEAK_ALIAS(ether_ntoa_r, libc_ether_ntoa_r);
DEFINE_PUBLIC_WEAK_ALIAS(ether_aton, libc_ether_aton);
DEFINE_PUBLIC_WEAK_ALIAS(ether_aton_r, libc_ether_aton_r);
DEFINE_PUBLIC_WEAK_ALIAS(ether_ntohost, libc_ether_ntohost);
DEFINE_PUBLIC_WEAK_ALIAS(ether_hostton, libc_ether_hostton);
DEFINE_PUBLIC_WEAK_ALIAS(ether_line, libc_ether_line);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_ETHER_C */
