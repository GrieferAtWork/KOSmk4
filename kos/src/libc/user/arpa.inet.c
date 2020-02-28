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
#ifndef GUARD_LIBC_USER_ARPA_INET_C
#define GUARD_LIBC_USER_ARPA_INET_C 1

#include "../api.h"
#include "arpa.inet.h"

DECL_BEGIN





/*[[[start:implementation]]]*/







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

/*[[[head:inet_ntop,hash:CRC-32=0x6bc41ef7]]]*/
/* Convert a Internet address in binary network format for interface
 * type AF in buffer starting at CP to presentation form and place
 * result in buffer of length LEN starting at BUF */
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



/*[[[head:inet_net_ntop,hash:CRC-32=0x87c1ed22]]]*/
/* Convert network number for interface type AF in buffer starting at CP
 * to presentation format. The result will specify BITS bits of the number */
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

/*[[[head:inet_net_pton,hash:CRC-32=0xbb662b9e]]]*/
/* Convert network number for interface type AF from presentation in buffer starting
 * at CP to network format and store result int buffer starting at BUF of size LEN */
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

/*[[[head:inet_nsap_addr,hash:CRC-32=0xb379172f]]]*/
/* Convert ASCII representation in hexadecimal form of the Internet address
 * to binary form and place result in buffer of length LEN starting at BUF */
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

/*[[[head:inet_nsap_ntoa,hash:CRC-32=0x37f0e109]]]*/
/* Convert internet address in binary form in LEN bytes
 * starting at CP a presentation form and place result in BUF */
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



/*[[[start:exports,hash:CRC-32=0x2bdd37d7]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(inet_net_ntop, libc_inet_net_ntop);
DEFINE_PUBLIC_WEAK_ALIAS(inet_net_pton, libc_inet_net_pton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_nsap_addr, libc_inet_nsap_addr);
DEFINE_PUBLIC_WEAK_ALIAS(inet_nsap_ntoa, libc_inet_nsap_ntoa);
DEFINE_PUBLIC_WEAK_ALIAS(inet_pton, libc_inet_pton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_ntop, libc_inet_ntop);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ARPA_INET_C */
