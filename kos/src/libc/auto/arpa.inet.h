/* HASH CRC-32:0x4d5018e6 */
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
#ifndef GUARD_LIBC_AUTO_ARPA_INET_H
#define GUARD_LIBC_AUTO_ARPA_INET_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <arpa/inet.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_netof(3)
 * Return the network-number-part of the Internet address `INADDR' */
INTDEF ATTR_CONST WUNUSED uint32_t NOTHROW_NCX(LIBDCALL libd_inet_netof)(struct in_addr inaddr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_netof(3)
 * Return the network-number-part of the Internet address `INADDR' */
INTDEF ATTR_CONST WUNUSED uint32_t NOTHROW_NCX(LIBCCALL libc_inet_netof)(struct in_addr inaddr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_lnaof(3)
 * Return the local-host-address-part of the Internet address `INADDR' */
INTDEF ATTR_CONST WUNUSED uint32_t NOTHROW_NCX(LIBDCALL libd_inet_lnaof)(struct in_addr inaddr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_lnaof(3)
 * Return the local-host-address-part of the Internet address `INADDR' */
INTDEF ATTR_CONST WUNUSED uint32_t NOTHROW_NCX(LIBCCALL libc_inet_lnaof)(struct in_addr inaddr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_makeaddr(3)
 * Construct  an  Internet-host-address in  network byte  order from
 * the combination of its network (`net'), and host (`host') number.
 * The `net' and `host' arguments  can later be re-extracted by  use
 * of `inet_netof(3)' and `inet_lnaof(3)' */
INTDEF ATTR_CONST WUNUSED struct in_addr NOTHROW_NCX(LIBDCALL libd_inet_makeaddr)(uint32_t net, uint32_t host);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_makeaddr(3)
 * Construct  an  Internet-host-address in  network byte  order from
 * the combination of its network (`net'), and host (`host') number.
 * The `net' and `host' arguments  can later be re-extracted by  use
 * of `inet_netof(3)' and `inet_lnaof(3)' */
INTDEF ATTR_CONST WUNUSED struct in_addr NOTHROW_NCX(LIBCCALL libc_inet_makeaddr)(uint32_t net, uint32_t host);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_addr(3)
 * Convert an  Internet host  address  `CP' from  its  numbers-and-dots
 * notational form into its binary representation in network byte order
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct) */
INTDEF ATTR_PURE ATTR_IN(1) in_addr_t NOTHROW_NCX(LIBDCALL libd_inet_addr)(char const *__restrict cp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_addr(3)
 * Convert an  Internet host  address  `CP' from  its  numbers-and-dots
 * notational form into its binary representation in network byte order
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct) */
INTDEF ATTR_PURE ATTR_IN(1) in_addr_t NOTHROW_NCX(LIBCCALL libc_inet_addr)(char const *__restrict cp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_ntoa(3)
 * Return   the   conventional  numbers-and-dots   representation   of  a
 * given  Internet  host  address  `inaddr'.  The  returned  pointer   is
 * apart of a static buffer and  may change in subsequence (or  parallel)
 * calls. For a re-entrant version of this function, see `inet_ntoa_r(3)' */
INTDEF ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBDCALL libd_inet_ntoa)(struct in_addr inaddr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_ntoa(3)
 * Return   the   conventional  numbers-and-dots   representation   of  a
 * given  Internet  host  address  `inaddr'.  The  returned  pointer   is
 * apart of a static buffer and  may change in subsequence (or  parallel)
 * calls. For a re-entrant version of this function, see `inet_ntoa_r(3)' */
INTDEF ATTR_RETNONNULL WUNUSED char *NOTHROW_NCX(LIBCCALL libc_inet_ntoa)(struct in_addr inaddr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_ntoa_r(3)
 * Re-entrant version of `inet_ntoa()' */
INTDEF ATTR_RETNONNULL ATTR_OUT(2) char *NOTHROW_NCX(LIBDCALL libd_inet_ntoa_r)(struct in_addr inaddr, char buf[16]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_ntoa_r(3)
 * Re-entrant version of `inet_ntoa()' */
INTDEF ATTR_RETNONNULL ATTR_OUT(2) char *NOTHROW_NCX(LIBCCALL libc_inet_ntoa_r)(struct in_addr inaddr, char buf[16]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_network(3)
 * This function is  the same as  `inet_addr()', except  that
 * the return value is in host-endian, rather than net-endian */
INTDEF ATTR_PURE ATTR_IN(1) uint32_t NOTHROW_NCX(LIBDCALL libd_inet_network)(char const *__restrict cp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_network(3)
 * This function is  the same as  `inet_addr()', except  that
 * the return value is in host-endian, rather than net-endian */
INTDEF ATTR_PURE ATTR_IN(1) uint32_t NOTHROW_NCX(LIBCCALL libc_inet_network)(char const *__restrict cp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_aton(3)
 * Convert an Internet host address `CP' from its numbers-and-dots
 * notational form into its binary representation in network  byte
 * order. The result is then stored in `*INP'
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_inet_aton)(char const *__restrict cp, struct in_addr *__restrict inp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_aton(3)
 * Convert an Internet host address `CP' from its numbers-and-dots
 * notational form into its binary representation in network  byte
 * order. The result is then stored in `*INP'
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_inet_aton)(char const *__restrict cp, struct in_addr *__restrict inp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_paton(3)
 * Same as `inet_aton()', but update `*pcp' to point past the address
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_inet_paton)(char const **__restrict pcp, struct in_addr *__restrict inp, int network_addr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_paton(3)
 * Same as `inet_aton()', but update `*pcp' to point past the address
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
INTDEF WUNUSED ATTR_INOUT(1) ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_inet_paton)(char const **__restrict pcp, struct in_addr *__restrict inp, int network_addr);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_neta(3)
 * Similar to `inet_ntoa_r(3)', but use smaller formats if possible:
 *     0.0.0.0      For net = 0
 *     %u           For net <= 255
 *     %u.%u        For net <= 65535
 *     %u.%u.%u     For net <= 16777215
 *     %u.%u.%u.%u  For everything else
 * @return: buf:  Success
 * @return: NULL: [errno=EMSGSIZE]: The given `len' is too small */
INTDEF ATTR_OUTS(2, 3) char *NOTHROW_NCX(LIBDCALL libd_inet_neta)(uint32_t net, char *buf, size_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> inet_neta(3)
 * Similar to `inet_ntoa_r(3)', but use smaller formats if possible:
 *     0.0.0.0      For net = 0
 *     %u           For net <= 255
 *     %u.%u        For net <= 65535
 *     %u.%u.%u     For net <= 16777215
 *     %u.%u.%u.%u  For everything else
 * @return: buf:  Success
 * @return: NULL: [errno=EMSGSIZE]: The given `len' is too small */
INTDEF ATTR_OUTS(2, 3) char *NOTHROW_NCX(LIBCCALL libc_inet_neta)(uint32_t net, char *buf, size_t len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> inet_net_ntop(3)
 * TODO: Implement & document */
INTDEF char *NOTHROW_RPC_KOS(LIBDCALL libd_inet_net_ntop)(int af, void const *cp, int bits, char *buf, size_t len);
/* >> inet_net_pton(3)
 * TODO: Implement & document */
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet_net_pton)(int af, char const *cp, void *buf, size_t len);
/* >> inet_nsap_addr(3)
 * TODO: Implement & document */
INTDEF unsigned int NOTHROW_RPC_KOS(LIBDCALL libd_inet_nsap_addr)(char const *cp, unsigned char *buf, int len);
/* >> inet_nsap_ntoa(3)
 * TODO: Implement & document */
INTDEF char *NOTHROW_RPC_KOS(LIBDCALL libd_inet_nsap_ntoa)(int len, unsigned char const *cp, char *buf);
/* >> inet_pton(3)
 * TODO: Implement & document */
INTDEF int NOTHROW_RPC_KOS(LIBDCALL libd_inet_pton)(int af, char const *__restrict cp, void *__restrict buf);
/* >> inet_ntop(3)
 * TODO: Implement & document */
INTDEF char const *NOTHROW_RPC_KOS(LIBDCALL libd_inet_ntop)(int af, void const *__restrict cp, char *__restrict buf, socklen_t len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ARPA_INET_H */
