/* HASH CRC-32:0xdb40bc7a */
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
#ifndef GUARD_LIBC_USER_NETINET_ETHER_H
#define GUARD_LIBC_USER_NETINET_ETHER_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netinet/ether.h>

DECL_BEGIN

/* Convert 48 bit Ethernet ADDRess to ASCII */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntoa)(struct ether_addr const *addr);
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTDEF char *NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *addr, char *buf);
/* Convert ASCII string S to 48 bit Ethernet address */
INTDEF struct ether_addr *NOTHROW_RPC_KOS(LIBCCALL libc_ether_aton)(char const *asc);
/* Convert ASCII string S to 48 bit Ethernet address */
INTDEF struct ether_addr *NOTHROW_RPC_KOS(LIBCCALL libc_ether_aton_r)(char const *asc, struct ether_addr *addr);
/* Map 48 bit Ethernet number ADDR to HOSTNAME */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntohost)(char *hostname, struct ether_addr const *addr);
/* Map HOSTNAME to 48 bit Ethernet address */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_ether_hostton)(char const *hostname, struct ether_addr *addr);
/* Scan LINE and set ADDR and HOSTNAME */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_ether_line)(char const *line, struct ether_addr *addr, char *hostname);

DECL_END

#endif /* !GUARD_LIBC_USER_NETINET_ETHER_H */
