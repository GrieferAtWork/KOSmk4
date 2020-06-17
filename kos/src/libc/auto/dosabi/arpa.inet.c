/* HASH CRC-32:0x22178095 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_ARPA_INET_C
#define GUARD_LIBC_AUTO_DOSABI_ARPA_INET_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/arpa.inet.h"

DECL_BEGIN

/* Return network number part of the Internet address IN */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_CONST WUNUSED uint32_t
NOTHROW_NCX(LIBDCALL libd_inet_netof)(struct in_addr inaddr) {
	return libc_inet_netof(inaddr);
}
/* Return the local host address part of the Internet address in IN */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_CONST WUNUSED uint32_t
NOTHROW_NCX(LIBDCALL libd_inet_lnaof)(struct in_addr inaddr) {
	return libc_inet_lnaof(inaddr);
}
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_CONST WUNUSED struct in_addr
NOTHROW_NCX(LIBDCALL libd_inet_makeaddr)(uint32_t net,
                                         uint32_t host) {
	return libc_inet_makeaddr(net, host);
}
/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct) */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_PURE NONNULL((1)) in_addr_t
NOTHROW_NCX(LIBDCALL libd_inet_addr)(char const *__restrict cp) {
	return libc_inet_addr(cp);
}
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_RETNONNULL WUNUSED char *
NOTHROW_NCX(LIBDCALL libd_inet_ntoa)(struct in_addr inaddr) {
	return libc_inet_ntoa(inaddr);
}
/* Re-entrant version of `inet_ntoa()' */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_RETNONNULL NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_inet_ntoa_r)(struct in_addr inaddr,
                                       char buf[16]) {
	return libc_inet_ntoa_r(inaddr, buf);
}
/* This function is the same as `inet_addr()', except that
 * the return value is in host-endian, rather than net-endian */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") ATTR_PURE NONNULL((1)) uint32_t
NOTHROW_NCX(LIBDCALL libd_inet_network)(char const *__restrict cp) {
	return libc_inet_network(cp);
}
/* Convert Internet host address from numbers-and-dots notation in
 * CP into binary data and store the result in the structure INP
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_inet_aton)(char const *__restrict cp,
                                     struct in_addr *__restrict inp) {
	return libc_inet_aton(cp, inp);
}
/* Same as `inet_aton()', but update `*pcp' to point after the address
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") WUNUSED NONNULL((1, 2)) int
NOTHROW_NCX(LIBDCALL libd_inet_paton)(char const **__restrict pcp,
                                      struct in_addr *__restrict inp,
                                      int network_addr) {
	return libc_inet_paton(pcp, inp, network_addr);
}
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") NONNULL((2)) char *
NOTHROW_NCX(LIBDCALL libd_inet_neta)(uint32_t net,
                                     char *buf,
                                     size_t len) {
	return libc_inet_neta(net, buf, len);
}
/* Convert network number for interface type AF in buffer starting at CP
 * to presentation format. The result will specify BITS bits of the number */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") char *
NOTHROW_RPC_KOS(LIBDCALL libd_inet_net_ntop)(int af,
                                             void const *cp,
                                             int bits,
                                             char *buf,
                                             size_t len) {
	return libc_inet_net_ntop(af, cp, bits, buf, len);
}
/* Convert network number for interface type AF from presentation in buffer starting
 * at CP to network format and store result int buffer starting at BUF of size LEN */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet_net_pton)(int af,
                                             char const *cp,
                                             void *buf,
                                             size_t len) {
	return libc_inet_net_pton(af, cp, buf, len);
}
/* Convert ASCII representation in hexadecimal form of the Internet address
 * to binary form and place result in buffer of length LEN starting at BUF */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") unsigned int
NOTHROW_RPC_KOS(LIBDCALL libd_inet_nsap_addr)(char const *cp,
                                              unsigned char *buf,
                                              int len) {
	return libc_inet_nsap_addr(cp, buf, len);
}
/* Convert internet address in binary form in LEN bytes
 * starting at CP a presentation form and place result in BUF */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") char *
NOTHROW_RPC_KOS(LIBDCALL libd_inet_nsap_ntoa)(int len,
                                              unsigned char const *cp,
                                              char *buf) {
	return libc_inet_nsap_ntoa(len, cp, buf);
}
/* Convert from presentation format of an Internet number in buffer
 * starting at CP to the binary network format and store result for
 * interface type AF in buffer starting at BUF */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") int
NOTHROW_RPC_KOS(LIBDCALL libd_inet_pton)(int af,
                                         char const *__restrict cp,
                                         void *__restrict buf) {
	return libc_inet_pton(af, cp, buf);
}
/* Convert a Internet address in binary network format for interface
 * type AF in buffer starting at CP to presentation form and place
 * result in buffer of length LEN starting at BUF */
INTERN ATTR_SECTION(".text.crt.dos.net.inet") char const *
NOTHROW_RPC_KOS(LIBDCALL libd_inet_ntop)(int af,
                                         void const *__restrict cp,
                                         char *__restrict buf,
                                         socklen_t len) {
	return libc_inet_ntop(af, cp, buf, len);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$inet_netof, libd_inet_netof);
DEFINE_PUBLIC_ALIAS(DOS$inet_lnaof, libd_inet_lnaof);
DEFINE_PUBLIC_ALIAS(DOS$inet_makeaddr, libd_inet_makeaddr);
DEFINE_PUBLIC_ALIAS(DOS$inet_addr, libd_inet_addr);
DEFINE_PUBLIC_ALIAS(DOS$inet_ntoa, libd_inet_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$inet_ntoa_r, libd_inet_ntoa_r);
DEFINE_PUBLIC_ALIAS(DOS$inet_network, libd_inet_network);
DEFINE_PUBLIC_ALIAS(DOS$inet_aton, libd_inet_aton);
DEFINE_PUBLIC_ALIAS(DOS$inet_paton, libd_inet_paton);
DEFINE_PUBLIC_ALIAS(DOS$inet_neta, libd_inet_neta);
DEFINE_PUBLIC_ALIAS(DOS$inet_net_ntop, libd_inet_net_ntop);
DEFINE_PUBLIC_ALIAS(DOS$inet_net_pton, libd_inet_net_pton);
DEFINE_PUBLIC_ALIAS(DOS$inet_nsap_addr, libd_inet_nsap_addr);
DEFINE_PUBLIC_ALIAS(DOS$inet_nsap_ntoa, libd_inet_nsap_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$inet_pton, libd_inet_pton);
DEFINE_PUBLIC_ALIAS(DOS$inet_ntop, libd_inet_ntop);

#endif /* !GUARD_LIBC_AUTO_DOSABI_ARPA_INET_C */
