/* HASH CRC-32:0x34337c2d */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_NETINET_ETHER_C
#define GUARD_LIBC_AUTO_DOSABI_NETINET_ETHER_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/netinet.ether.h"

DECL_BEGIN

/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBDCALL libd_ether_ntoa)(struct ether_addr const *__restrict addr) {
	return libc_ether_ntoa(addr);
}
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_ether_ntoa_r)(struct ether_addr const *__restrict addr,
                                        char *__restrict buf) {
	return libc_ether_ntoa_r(addr, buf);
}
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") ATTR_RETNONNULL NONNULL((1)) struct ether_addr *
NOTHROW_NCX(LIBDCALL libd_ether_aton)(char const *__restrict asc) {
	return libc_ether_aton(asc);
}
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") WUNUSED NONNULL((1, 2)) struct ether_addr *
NOTHROW_NCX(LIBDCALL libd_ether_aton_r)(char const *__restrict asc,
                                        struct ether_addr *__restrict addr) {
	return libc_ether_aton_r(asc, addr);
}
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") WUNUSED NONNULL((1, 2)) struct ether_addr *
NOTHROW_NCX(LIBDCALL libd_ether_paton_r)(char const **__restrict pasc,
                                         struct ether_addr *__restrict addr) {
	return libc_ether_paton_r(pasc, addr);
}
/* Scan LINE and set ADDR and HOSTNAME */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_ether_line)(char const *line,
                                      struct ether_addr *addr,
                                      char *hostname) {
	return libc_ether_line(line, addr, hostname);
}
/* Map 48 bit Ethernet number ADDR to HOSTNAME */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") int
NOTHROW_RPC_KOS(LIBDCALL libd_ether_ntohost)(char *hostname,
                                             struct ether_addr const *addr) {
	return libc_ether_ntohost(hostname, addr);
}
/* Map HOSTNAME to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.dos.net.ether") int
NOTHROW_RPC_KOS(LIBDCALL libd_ether_hostton)(char const *hostname,
                                             struct ether_addr *addr) {
	return libc_ether_hostton(hostname, addr);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$ether_ntoa, libd_ether_ntoa);
DEFINE_PUBLIC_ALIAS(DOS$ether_ntoa_r, libd_ether_ntoa_r);
DEFINE_PUBLIC_ALIAS(DOS$ether_aton, libd_ether_aton);
DEFINE_PUBLIC_ALIAS(DOS$ether_aton_r, libd_ether_aton_r);
DEFINE_PUBLIC_ALIAS(DOS$ether_paton_r, libd_ether_paton_r);
DEFINE_PUBLIC_ALIAS(DOS$ether_line, libd_ether_line);
DEFINE_PUBLIC_ALIAS(DOS$ether_ntohost, libd_ether_ntohost);
DEFINE_PUBLIC_ALIAS(DOS$ether_hostton, libd_ether_hostton);

#endif /* !GUARD_LIBC_AUTO_DOSABI_NETINET_ETHER_C */
