/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_ARPA_INET_C
#define GUARD_LIBC_USER_ARPA_INET_C 1

#include "../api.h"
#include "arpa.inet.h"

DECL_BEGIN

/*[[[head:libc_inet_pton,hash:CRC-32=0xf535c570]]]*/
/* >> inet_pton(3)
 * TODO: Implement & document */
INTERN ATTR_SECTION(".text.crt.net.inet") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_pton)(int af,
                                         char const *__restrict cp,
                                         void *__restrict buf)
/*[[[body:libc_inet_pton]]]*/
/*AUTO*/{
	(void)af;
	(void)cp;
	(void)buf;
	CRT_UNIMPLEMENTEDF("inet_pton(%x, %q, %p)", af, cp, buf); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_inet_pton]]]*/

/*[[[head:libc_inet_ntop,hash:CRC-32=0x6ab482a4]]]*/
/* >> inet_ntop(3)
 * TODO: Implement & document */
INTERN ATTR_SECTION(".text.crt.net.inet") char const *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_ntop)(int af,
                                         void const *__restrict cp,
                                         char *__restrict buf,
                                         socklen_t len)
/*[[[body:libc_inet_ntop]]]*/
/*AUTO*/{
	(void)af;
	(void)cp;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTEDF("inet_ntop(%x, %p, %q, %" PRIxN(__SIZEOF_SOCKLEN_T__) ")", af, cp, buf, len); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_inet_ntop]]]*/



/*[[[head:libc_inet_net_ntop,hash:CRC-32=0x96151268]]]*/
/* >> inet_net_ntop(3)
 * TODO: Implement & document */
INTERN ATTR_SECTION(".text.crt.net.inet") char *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_ntop)(int af,
                                             void const *cp,
                                             int bits,
                                             char *buf,
                                             size_t len)
/*[[[body:libc_inet_net_ntop]]]*/
/*AUTO*/{
	(void)af;
	(void)cp;
	(void)bits;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTEDF("inet_net_ntop(%x, %p, %x, %q, %Ix)", af, cp, bits, buf, len); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_inet_net_ntop]]]*/

/*[[[head:libc_inet_net_pton,hash:CRC-32=0xbbc0060]]]*/
/* >> inet_net_pton(3)
 * TODO: Implement & document */
INTERN ATTR_SECTION(".text.crt.net.inet") int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_pton)(int af,
                                             char const *cp,
                                             void *buf,
                                             size_t len)
/*[[[body:libc_inet_net_pton]]]*/
/*AUTO*/{
	(void)af;
	(void)cp;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTEDF("inet_net_pton(%x, %q, %p, %Ix)", af, cp, buf, len); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_inet_net_pton]]]*/

/*[[[head:libc_inet_nsap_addr,hash:CRC-32=0xbb5daf7a]]]*/
/* >> inet_nsap_addr(3)
 * TODO: Implement & document */
INTERN ATTR_SECTION(".text.crt.net.inet") unsigned int
NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_addr)(char const *cp,
                                              unsigned char *buf,
                                              int len)
/*[[[body:libc_inet_nsap_addr]]]*/
/*AUTO*/{
	(void)cp;
	(void)buf;
	(void)len;
	CRT_UNIMPLEMENTEDF("inet_nsap_addr(%q, %p, %x)", cp, buf, len); /* TODO */
	return (unsigned int)libc_seterrno(ENOSYS);
}
/*[[[end:libc_inet_nsap_addr]]]*/





/*[[[head:libc_inet_nsap_ntoa,hash:CRC-32=0xe4c3ff62]]]*/
/* >> inet_nsap_ntoa(3)
 * TODO: Implement & document */
INTERN ATTR_SECTION(".text.crt.net.inet") char *
NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_ntoa)(int len,
                                              unsigned char const *cp,
                                              char *buf)
/*[[[body:libc_inet_nsap_ntoa]]]*/
/*AUTO*/{
	(void)len;
	(void)cp;
	(void)buf;
	CRT_UNIMPLEMENTEDF("inet_nsap_ntoa(%x, %p, %q)", len, cp, buf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc_inet_nsap_ntoa]]]*/



/*[[[start:exports,hash:CRC-32=0xb02206ab]]]*/
DEFINE_PUBLIC_ALIAS(inet_net_ntop, libc_inet_net_ntop);
DEFINE_PUBLIC_ALIAS(inet_net_pton, libc_inet_net_pton);
DEFINE_PUBLIC_ALIAS(inet_nsap_addr, libc_inet_nsap_addr);
DEFINE_PUBLIC_ALIAS(inet_nsap_ntoa, libc_inet_nsap_ntoa);
DEFINE_PUBLIC_ALIAS(inet_pton, libc_inet_pton);
DEFINE_PUBLIC_ALIAS(inet_ntop, libc_inet_ntop);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ARPA_INET_C */
