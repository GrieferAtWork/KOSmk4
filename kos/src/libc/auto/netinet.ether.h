/* HASH CRC-32:0x5cded6dd */
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
#ifndef GUARD_LIBC_AUTO_NETINET_ETHER_H
#define GUARD_LIBC_AUTO_NETINET_ETHER_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netinet/ether.h>

DECL_BEGIN

#ifndef __KERNEL__
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTDEF ATTR_RETNONNULL NONNULL((1)) char *NOTHROW_NCX(LIBCCALL libc_ether_ntoa)(struct ether_addr const *__restrict addr);
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTDEF ATTR_RETNONNULL NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *__restrict addr, char *__restrict buf);
/* Convert ASCII string S to 48 bit Ethernet address */
INTDEF ATTR_RETNONNULL NONNULL((1)) struct ether_addr *NOTHROW_NCX(LIBCCALL libc_ether_aton)(char const *__restrict asc);
/* Convert ASCII string S to 48 bit Ethernet address */
INTDEF WUNUSED NONNULL((1, 2)) struct ether_addr *NOTHROW_NCX(LIBCCALL libc_ether_aton_r)(char const *__restrict asc, struct ether_addr *__restrict addr);
/* Convert ASCII string S to 48 bit Ethernet address */
INTDEF WUNUSED NONNULL((1, 2)) struct ether_addr *NOTHROW_NCX(LIBCCALL libc_ether_paton_r)(char const **__restrict pasc, struct ether_addr *__restrict addr);
/* Scan LINE and set ADDR and HOSTNAME */
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_ether_line)(char const *line, struct ether_addr *addr, char *hostname);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETINET_ETHER_H */
