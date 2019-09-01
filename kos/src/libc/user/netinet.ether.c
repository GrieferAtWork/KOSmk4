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
#ifndef GUARD_LIBC_USER_NETINET_ETHER_C
#define GUARD_LIBC_USER_NETINET_ETHER_C 1

#include "../api.h"
#include "netinet.ether.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:ether_ntoa,hash:0x8b24cc46]]]*/
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_ntoa") char *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntoa)(struct ether_addr const *addr)
/*[[[body:ether_ntoa]]]*/
{
	CRT_UNIMPLEMENTED("ether_ntoa"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_ntoa]]]*/

/*[[[head:ether_ntoa_r,hash:0xc66dd6fe]]]*/
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_ntoa_r") char *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *addr,
                                            char *buf)
/*[[[body:ether_ntoa_r]]]*/
{
	CRT_UNIMPLEMENTED("ether_ntoa_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_ntoa_r]]]*/

/*[[[head:ether_aton,hash:0xf1570449]]]*/
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_aton") struct ether_addr *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_aton)(char const *asc)
/*[[[body:ether_aton]]]*/
{
	CRT_UNIMPLEMENTED("ether_aton"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_aton]]]*/

/*[[[head:ether_aton_r,hash:0xfdadc05e]]]*/
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_aton_r") struct ether_addr *
NOTHROW_RPC_KOS(LIBCCALL libc_ether_aton_r)(char const *asc,
                                            struct ether_addr *addr)
/*[[[body:ether_aton_r]]]*/
{
	CRT_UNIMPLEMENTED("ether_aton_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:ether_aton_r]]]*/

/*[[[head:ether_ntohost,hash:0xd9b2cdea]]]*/
/* Map 48 bit Ethernet number ADDR to HOSTNAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_ntohost") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntohost)(char *hostname,
                                             struct ether_addr const *addr)
/*[[[body:ether_ntohost]]]*/
{
	CRT_UNIMPLEMENTED("ether_ntohost"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ether_ntohost]]]*/

/*[[[head:ether_hostton,hash:0xee934618]]]*/
/* Map HOSTNAME to 48 bit Ethernet address */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_hostton") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_hostton)(char const *hostname,
                                             struct ether_addr *addr)
/*[[[body:ether_hostton]]]*/
{
	CRT_UNIMPLEMENTED("ether_hostton"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ether_hostton]]]*/

/*[[[head:ether_line,hash:0xf98c4249]]]*/
/* Scan LINE and set ADDR and HOSTNAME */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.ether.ether_line") int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_line)(char const *line,
                                          struct ether_addr *addr,
                                          char *hostname)
/*[[[body:ether_line]]]*/
{
	CRT_UNIMPLEMENTED("ether_line"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:ether_line]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0x7d181380]]]*/
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
