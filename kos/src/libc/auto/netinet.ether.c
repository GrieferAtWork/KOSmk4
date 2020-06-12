/* HASH CRC-32:0x2f04a9e2 */
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
#ifndef GUARD_LIBC_AUTO_NETINET_ETHER_C
#define GUARD_LIBC_AUTO_NETINET_ETHER_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/netinet.ether.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

#ifndef __KERNEL__
#include <net/ethernet.h>
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_RETNONNULL NONNULL((1)) char *
NOTHROW_NCX(LIBCCALL libc_ether_ntoa)(struct ether_addr const *__restrict addr) {
	static char buf[21];
	return ether_ntoa_r(addr, buf);
}
#include <net/ethernet.h>
/* Convert 48 bit Ethernet ADDRess to ASCII */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_RETNONNULL NONNULL((1, 2)) char *
NOTHROW_NCX(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *__restrict addr,
                                        char *__restrict buf) {
	sprintf(buf, "%x:%x:%x:%x:%x:%x",
	        addr->ether_addr_octet[0], addr->ether_addr_octet[1],
	        addr->ether_addr_octet[2], addr->ether_addr_octet[3],
	        addr->ether_addr_octet[4], addr->ether_addr_octet[5]);
	return buf;
}
#include <net/ethernet.h>
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_RETNONNULL NONNULL((1)) struct ether_addr *
NOTHROW_NCX(LIBCCALL libc_ether_aton)(char const *__restrict asc) {
	static struct ether_addr addr;
	return ether_aton_r(asc, &addr);
}
#include <net/ethernet.h>
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.net.ether") WUNUSED NONNULL((1, 2)) struct ether_addr *
NOTHROW_NCX(LIBCCALL libc_ether_aton_r)(char const *__restrict asc,
                                        struct ether_addr *__restrict addr) {
	return ether_paton_r((char const **)&asc, addr);
}
#include <net/ethernet.h>
/* Convert ASCII string S to 48 bit Ethernet address */
INTERN ATTR_SECTION(".text.crt.net.ether") WUNUSED NONNULL((1, 2)) struct ether_addr *
NOTHROW_NCX(LIBCCALL libc_ether_paton_r)(char const **__restrict pasc,
                                         struct ether_addr *__restrict addr) {
	unsigned int i;
	char const *asc = *pasc;
	for (i = 0; i < 6; ++i) {
		u8 octet;
		char c;
		c = *asc++;
		if (c >= '0' && c <= '9')
			octet = c - '0';
		else if (c >= 'a' && c <= 'f')
			octet = 10 + c - 'a';
		else if (c >= 'A' && c <= 'F')
			octet = 10 + c - 'A';
		else {
			return NULL;
		}
		c = *asc++;
		octet <<= 4;
		if (c >= '0' && c <= '9')
			octet |= c - '0';
		else if (c >= 'a' && c <= 'f')
			octet |= 10 + c - 'a';
		else if (c >= 'A' && c <= 'F')
			octet |= 10 + c - 'A';
		else {
			return NULL;
		}
		c = *asc++;
		if (c == ':') {
			if (i >= 5)
				return NULL;
		} else if (!c || isspace(c)) {
			if (i < 5)
				return NULL;
		} else {
			return NULL;
		}
		addr->ether_addr_octet[i] = octet;
	}
	*pasc = asc;
	return addr;
}
/* Scan LINE and set ADDR and HOSTNAME */
INTERN ATTR_SECTION(".text.crt.net.ether") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_ether_line)(char const *line,
                                      struct ether_addr *addr,
                                      char *hostname) {
	size_t hnlen;
	while (isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	if (!ether_paton_r(&line, addr))
		return -1; /* This also handles comment lines! */
	while (isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	/* The remainder of the line is the hostname. */
	for (hnlen = 0; line[hnlen] && line[hnlen] != '\r' && line[hnlen] != '\n'; ++hnlen)
		;
	while (hnlen && isspace(line[hnlen - 1]))
		--hnlen;
	if (!hnlen)
		return -1; /* No hostname */
	hostname = (char *)mempcpy(hostname, line, hnlen);
	*hostname = '\0'; /* NUL-terminate */
	return 0;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(ether_ntoa, libc_ether_ntoa);
DEFINE_PUBLIC_ALIAS(ether_ntoa_r, libc_ether_ntoa_r);
DEFINE_PUBLIC_ALIAS(ether_aton, libc_ether_aton);
DEFINE_PUBLIC_ALIAS(ether_aton_r, libc_ether_aton_r);
DEFINE_PUBLIC_ALIAS(ether_paton_r, libc_ether_paton_r);
DEFINE_PUBLIC_ALIAS(ether_line, libc_ether_line);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_NETINET_ETHER_C */
