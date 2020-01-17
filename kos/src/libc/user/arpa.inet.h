/* HASH CRC-32:0x97a3f6ae */
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
#ifndef GUARD_LIBC_USER_ARPA_INET_H
#define GUARD_LIBC_USER_ARPA_INET_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <arpa/inet.h>

DECL_BEGIN

/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order */
INTDEF in_addr_t NOTHROW_RPC_KOS(LIBCCALL libc_inet_addr)(char const *cp);
/* Return the local host address part of the Internet address in IN */
INTDEF in_addr_t NOTHROW_RPC_KOS(LIBCCALL libc_inet_lnaof)(struct in_addr inaddr);
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
INTDEF struct in_addr NOTHROW_RPC_KOS(LIBCCALL libc_inet_makeaddr)(in_addr_t net, in_addr_t host);
/* Return network number part of the Internet address IN */
INTDEF in_addr_t NOTHROW_RPC_KOS(LIBCCALL libc_inet_netof)(struct in_addr inaddr);
/* Extract the network number in network byte order from
 * the address in numbers-and-dots natation starting at CP */
INTDEF in_addr_t NOTHROW_RPC_KOS(LIBCCALL libc_inet_network)(char const *cp);
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_inet_ntoa)(struct in_addr inaddr);
/* Convert from presentation format of an Internet number in buffer
 * starting at CP to the binary network format and store result for
 * interface type AF in buffer starting at BUF */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet_pton)(int af, char const *__restrict cp, void *__restrict buf);
/* Convert a Internet address in binary network format for interface
 * type AF in buffer starting at CP to presentation form and place
 * result in buffer of length LEN astarting at BUF */
INTDEF char const *NOTHROW_RPC_KOS(LIBCCALL libc_inet_ntop)(int af, void const *__restrict cp, char *__restrict buf, socklen_t len);
/* Convert Internet host address from numbers-and-dots notation in CP
 * into binary data and store the result in the structure INP */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet_aton)(char const *cp, struct in_addr *inp);
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_inet_neta)(in_addr_t net, char *buf, size_t len);
/* Convert network number for interface type AF in buffer starting at
 * CP to presentation format.  The result will specifiy BITS bits of
 * the number */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_ntop)(int af, void const *cp, int bits, char *buf, size_t len);
/* Convert network number for interface type AF from presentation in
 * buffer starting at CP to network format and store result int
 * buffer starting at BUF of size LEN */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_inet_net_pton)(int af, char const *cp, void *buf, size_t len);
/* Convert ASCII representation in hexadecimal form of the Internet
 * address to binary form and place result in buffer of length LEN
 * starting at BUF */
INTDEF unsigned int NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_addr)(char const *cp, unsigned char *buf, int len);
/* Convert internet address in binary form in LEN bytes starting
 * at CP a presentation form and place result in BUF */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_inet_nsap_ntoa)(int len, unsigned char const *cp, char *buf);

DECL_END

#endif /* !GUARD_LIBC_USER_ARPA_INET_H */
