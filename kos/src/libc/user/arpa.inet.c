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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ARPA_INET_C
#define GUARD_LIBC_USER_ARPA_INET_C 1

#include "../api.h"
#include "arpa.inet.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:inet_addr,hash:CRC-32=0x4f469a8a]]]*/
/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_addr") in_addr_t
NOTHROW_RPC_KOS(LIBCCALL libc_inet_addr)(char const *cp)
/*[[[body:inet_addr]]]*/
{
	(void)cp;
	CRT_UNIMPLEMENTED("inet_addr"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:inet_addr]]]*/

/*[[[head:inet_lnaof,hash:CRC-32=0x3a4b7493]]]*/
/* Return the local host address part of the Internet address in IN */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_lnaof") in_addr_t
NOTHROW_RPC_KOS(LIBCCALL libc_inet_lnaof)(struct in_addr inaddr)
/*[[[body:inet_lnaof]]]*/
{
	(void)inaddr;
	CRT_UNIMPLEMENTED("inet_lnaof"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:inet_lnaof]]]*/

/*[[[head:inet_makeaddr,hash:CRC-32=0x72a1f1e8]]]*/
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_makeaddr") struct in_addr
NOTHROW_RPC_KOS(LIBCCALL libc_inet_makeaddr)(in_addr_t net,
                                             in_addr_t host)
/*[[[body:inet_makeaddr]]]*/
{
	struct in_addr result;
	(void)net;
	(void)host;
	CRT_UNIMPLEMENTED("inet_makeaddr"); /* TODO */
	result.s_addr = 0;
	libc_seterrno(ENOSYS);
	return result;
}
/*[[[end:inet_makeaddr]]]*/

/*[[[head:inet_netof,hash:CRC-32=0x4a053d3d]]]*/
/* Return network number part of the Internet address IN */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_netof") in_addr_t
NOTHROW_RPC_KOS(LIBCCALL libc_inet_netof)(struct in_addr inaddr)
/*[[[body:inet_netof]]]*/
{
	(void)inaddr;
	CRT_UNIMPLEMENTED("inet_netof"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:inet_netof]]]*/

/*[[[head:inet_network,hash:CRC-32=0xd46d0b04]]]*/
/* Extract the network number in network byte order from
 * the address in numbers-and-dots natation starting at CP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_network") in_addr_t
NOTHROW_RPC_KOS(LIBCCALL libc_inet_network)(char const *cp)
/*[[[body:inet_network]]]*/
{
	(void)cp;
	CRT_UNIMPLEMENTED("inet_network"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:inet_network]]]*/

/*[[[head:inet_ntoa,hash:CRC-32=0x17c7895a]]]*/
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_ntoa") char *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_ntoa)(struct in_addr inaddr)
/*[[[body:inet_ntoa]]]*/
{
	(void)inaddr;
	CRT_UNIMPLEMENTED("inet_ntoa"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet_ntoa]]]*/

/*[[[head:inet_pton,hash:CRC-32=0x537a65dd]]]*/
/* Convert from presentation format of an Internet number in buffer
 * starting at CP to the binary network format and store result for
 * interface type AF in buffer starting at BUF */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_pton") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_pton)(int af,
                                         char const *__restrict cp,
                                         void *__restrict buf)
/*[[[body:inet_pton]]]*/
{
	(void)af;
	(void)cp;
	(void)buf;
	CRT_UNIMPLEMENTED("inet_pton"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet_pton]]]*/

/*[[[head:inet_ntop,hash:CRC-32=0xae5e4be7]]]*/
/* Convert a Internet address in binary network format for interface
 * type AF in buffer starting at CP to presentation form and place
 * result in buffer of length LEN astarting at BUF */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_ntop") char const *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_ntop)(int af,
                                         void const *__restrict cp,
                                         char *__restrict buf,
                                         socklen_t len)
/*[[[body:inet_ntop]]]*/
{
	(void)af;
	(void)cp;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTED("inet_ntop"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet_ntop]]]*/

/*[[[head:inet_aton,hash:CRC-32=0x1be34d2b]]]*/
/* Convert Internet host address from numbers-and-dots notation in CP
 * into binary data and store the result in the structure INP */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_aton") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_aton)(char const *cp,
                                         struct in_addr *inp)
/*[[[body:inet_aton]]]*/
{
	(void)cp;
	(void)inp;
	CRT_UNIMPLEMENTED("inet_aton"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet_aton]]]*/

/*[[[head:inet_neta,hash:CRC-32=0x11c52fb0]]]*/
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_neta") char *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_neta)(in_addr_t net,
                                         char *buf,
                                         size_t len)
/*[[[body:inet_neta]]]*/
{
	(void)net;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTED("inet_neta"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet_neta]]]*/

/*[[[head:inet_net_ntop,hash:CRC-32=0xd9d375c2]]]*/
/* Convert network number for interface type AF in buffer starting at
 * CP to presentation format.  The result will specifiy BITS bits of
 * the number */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_net_ntop") char *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_ntop)(int af,
                                             void const *cp,
                                             int bits,
                                             char *buf,
                                             size_t len)
/*[[[body:inet_net_ntop]]]*/
{
	(void)af;
	(void)cp;
	(void)bits;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTED("inet_net_ntop"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet_net_ntop]]]*/

/*[[[head:inet_net_pton,hash:CRC-32=0x4caac56d]]]*/
/* Convert network number for interface type AF from presentation in
 * buffer starting at CP to network format and store result int
 * buffer starting at BUF of size LEN */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_net_pton") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_pton)(int af,
                                             char const *cp,
                                             void *buf,
                                             size_t len)
/*[[[body:inet_net_pton]]]*/
{
	(void)af;
	(void)cp;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTED("inet_net_pton"); /* TODO */
	libc_seterrno(ENOSYS);
	return -1;
}
/*[[[end:inet_net_pton]]]*/

/*[[[head:inet_nsap_addr,hash:CRC-32=0x5a92a5d4]]]*/
/* Convert ASCII representation in hexadecimal form of the Internet
 * address to binary form and place result in buffer of length LEN
 * starting at BUF */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_nsap_addr") unsigned int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_addr)(char const *cp,
                                              unsigned char *buf,
                                              int len)
/*[[[body:inet_nsap_addr]]]*/
{
	(void)cp;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTED("inet_nsap_addr"); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:inet_nsap_addr]]]*/

/*[[[head:inet_nsap_ntoa,hash:CRC-32=0x548a8291]]]*/
/* Convert internet address in binary form in LEN bytes starting
 * at CP a presentation form and place result in BUF */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_nsap_ntoa") char *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_ntoa)(int len,
                                              unsigned char const *cp,
                                              char *buf)
/*[[[body:inet_nsap_ntoa]]]*/
{
	(void)len;
	(void)cp;
	(void)buf;
	CRT_UNIMPLEMENTED("inet_nsap_ntoa"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:inet_nsap_ntoa]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xa5c8b668]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(inet_addr, libc_inet_addr);
DEFINE_PUBLIC_WEAK_ALIAS(inet_lnaof, libc_inet_lnaof);
DEFINE_PUBLIC_WEAK_ALIAS(inet_makeaddr, libc_inet_makeaddr);
DEFINE_PUBLIC_WEAK_ALIAS(inet_netof, libc_inet_netof);
DEFINE_PUBLIC_WEAK_ALIAS(inet_network, libc_inet_network);
DEFINE_PUBLIC_WEAK_ALIAS(inet_ntoa, libc_inet_ntoa);
DEFINE_PUBLIC_WEAK_ALIAS(inet_pton, libc_inet_pton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_ntop, libc_inet_ntop);
DEFINE_PUBLIC_WEAK_ALIAS(inet_aton, libc_inet_aton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_neta, libc_inet_neta);
DEFINE_PUBLIC_WEAK_ALIAS(inet_net_ntop, libc_inet_net_ntop);
DEFINE_PUBLIC_WEAK_ALIAS(inet_net_pton, libc_inet_net_pton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_nsap_addr, libc_inet_nsap_addr);
DEFINE_PUBLIC_WEAK_ALIAS(inet_nsap_ntoa, libc_inet_nsap_ntoa);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ARPA_INET_C */
