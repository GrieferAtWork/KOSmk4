/* HASH CRC-32:0x39d965c8 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_NETINET_ETHER_C
#define GUARD_LIBC_AUTO_NETINET_ETHER_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "netinet.ether.h"
#include "../user/ctype.h"
#include "../user/libiberty.h"
#include "../user/stdio.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/util.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <net/ethernet.h>
#include "../libc/tls-globals.h"
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_RETNONNULL WUNUSED ATTR_IN(1) char *
NOTHROW_NCX(LIBCCALL libc_ether_ntoa)(struct ether_addr const *__restrict addr) {

	char **const _p_ether_ntoa_buf = &libc_get_tlsglobals()->ltg_ether_ntoa_buf;
#define ether_ntoa_buf (*_p_ether_ntoa_buf)
	if (ether_ntoa_buf == NULL)
		ether_ntoa_buf = (char *)libc_xmalloc(21 * sizeof(char));
	return libc_ether_ntoa_r(addr, ether_ntoa_buf);




}
#undef ether_ntoa_buf
#include <net/ethernet.h>
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ether_ntoa_r)(struct ether_addr const *__restrict addr,
                                        char *__restrict buf) {
	libc_sprintf(buf, "%x:%x:%x:%x:%x:%x",
	        addr->ether_addr_octet[0], addr->ether_addr_octet[1],
	        addr->ether_addr_octet[2], addr->ether_addr_octet[3],
	        addr->ether_addr_octet[4], addr->ether_addr_octet[5]);
	return buf;
}
#include <net/ethernet.h>
#include "../libc/tls-globals.h"
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_RETNONNULL WUNUSED ATTR_IN(1) struct ether_addr *
NOTHROW_NCX(LIBCCALL libc_ether_aton)(char const *__restrict asc) {
	byte_t (*const _p_ether_aton_addr)[6] = &libc_get_tlsglobals()->ltg_ether_aton_addr;
#define ether_aton_addr (*_p_ether_aton_addr)
	return libc_ether_aton_r(asc, (struct ether_addr *)ether_aton_addr);
}
#undef ether_aton_addr
#include <net/ethernet.h>
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTERN ATTR_SECTION(".text.crt.net.ether") WUNUSED ATTR_IN(1) ATTR_OUT(2) struct ether_addr *
NOTHROW_NCX(LIBCCALL libc_ether_aton_r)(char const *__restrict asc,
                                        struct ether_addr *__restrict addr) {
	return libc_ether_aton_np(asc, addr) ? addr : NULL;
}
#include <net/ethernet.h>
#include <libc/template/hex.h>
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
INTERN ATTR_SECTION(".text.crt.net.ether") WUNUSED ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ether_aton_np)(char const *__restrict asc,
                                         struct ether_addr *__restrict addr) {
	unsigned int i;
	for (i = 0; i < 6; ++i) {
		u8 octet, lo_octet;
		char c;
		c = *asc++;
		if (!__libc_hex2int(c, &octet))
			return NULL;
		c = *asc++;
		octet <<= 4;
		if (!__libc_hex2int(c, &lo_octet))
			return NULL;
		octet |= lo_octet;
		c = *asc++;
		if (c == ':') {
			if (i >= 5)
				return NULL;
		} else if (!c || libc_isspace(c)) {
			if (i < 5)
				return NULL;
		} else {
			return NULL;
		}
		addr->ether_addr_octet[i] = octet;
	}
	return (char *)asc;
}
#include <net/ethernet.h>
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
INTERN ATTR_SECTION(".text.crt.net.ether") WUNUSED ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3) int
NOTHROW_NCX(LIBCCALL libc_ether_line)(char const *line,
                                      struct ether_addr *addr,
                                      char *hostname) {
	size_t hnlen;
	while (libc_isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	line = libc_ether_aton_np(line, addr);
	if (!line)
		return -1; /* This also handles comment lines! */
	while (libc_isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	/* The remainder of the line is the hostname. */
	for (hnlen = 0;
	     line[hnlen] &&
	     line[hnlen] != '\r' &&
	     line[hnlen] != '\n';
	     ++hnlen)
		;
	while (hnlen && libc_isspace(line[hnlen - 1]))
		--hnlen;
	if (!hnlen)
		return -1; /* No hostname */
	hostname = (char *)libc_mempcpy(hostname, line, hnlen);
	*hostname = '\0'; /* NUL-terminate */
	return 0;
}
#include <net/ethernet.h>
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
INTERN ATTR_SECTION(".text.crt.net.ether") WUNUSED ATTR_IN(1) ATTR_OUT(2) char *
NOTHROW_NCX(LIBCCALL libc_ether_line_np)(char *line,
                                         struct ether_addr *addr) {
	size_t hnlen;
	while (libc_isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	line = libc_ether_aton_np(line, addr);
	if (!line)
		return NULL; /* This also handles comment lines! */
	while (libc_isspace(*line) && *line != '\r' && *line != '\n')
		++line;

	/* The remainder of the line is the hostname. */
	for (hnlen = 0;
	     line[hnlen] &&
	     line[hnlen] != '\r' &&
	     line[hnlen] != '\n';
	     ++hnlen)
		;
	while (hnlen && libc_isspace(line[hnlen - 1]))
		--hnlen;
	if (!hnlen)
		return NULL; /* No hostname */
	line[hnlen] = '\0'; /* NUL-terminate */
	return line;
}
/* >> ether_ntohost(3)
 * Map a given `addr' to its corresponding hostname from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist. */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_IN(2) ATTR_OUT(1) int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_ntohost)(char *hostname,
                                             struct ether_addr const *addr) {
	char *line;
	FILE *fp = libc_fopen("/etc/ethers", "rb");
	if unlikely(!fp)
		goto err;
	while ((line = libc_fparseln(fp, NULL, NULL, "\0\0#", 0)) != NULL) {
		struct ether_addr laddr;
		char *lhost;
		if (!*line) {

			libc_free(line);

			break;
		}
		lhost = libc_ether_line_np(line, &laddr);
		if (lhost && libc_memcmp(&laddr, addr, sizeof(laddr)) == 0) {
			libc_strcpy(hostname, lhost); /* Yes: no way to prevent overflow here :( */

			libc_free(line);


			(void)libc_fclose(fp);

			return 0;
		}

		libc_free(line);

	}

	(void)libc_fclose(fp);

err:
	return -1;
}
/* >> ether_hostton(3)
 * Map a given `hostname' into its corresponding address from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist. */
INTERN ATTR_SECTION(".text.crt.net.ether") ATTR_IN(1) ATTR_OUT(2) int
NOTHROW_RPC_KOS(LIBCCALL libc_ether_hostton)(char const *hostname,
                                             struct ether_addr *addr) {
	char *line;
	FILE *fp = libc_fopen("/etc/ethers", "rb");
	if unlikely(!fp)
		goto err;
	while ((line = libc_fparseln(fp, NULL, NULL, "\0\0#", 0)) != NULL) {
		char *lhost;
		if (!*line) {

			libc_free(line);

			break;
		}
		lhost = libc_ether_line_np(line, addr);
		if (lhost && libc_strcmp(hostname, lhost) == 0) {

			libc_free(line);


			(void)libc_fclose(fp);

			return 0;
		}

		libc_free(line);

	}

	(void)libc_fclose(fp);

err:
	return -1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(ether_ntoa,libc_ether_ntoa,ATTR_RETNONNULL WUNUSED ATTR_IN(1),char *,NOTHROW_NCX,LIBCCALL,(struct ether_addr const *__restrict addr),(addr));
DEFINE_PUBLIC_ALIAS_P(ether_ntoa_r,libc_ether_ntoa_r,ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(struct ether_addr const *__restrict addr, char *__restrict buf),(addr,buf));
DEFINE_PUBLIC_ALIAS_P(ether_aton,libc_ether_aton,ATTR_RETNONNULL WUNUSED ATTR_IN(1),struct ether_addr *,NOTHROW_NCX,LIBCCALL,(char const *__restrict asc),(asc));
DEFINE_PUBLIC_ALIAS_P(ether_aton_r,libc_ether_aton_r,WUNUSED ATTR_IN(1) ATTR_OUT(2),struct ether_addr *,NOTHROW_NCX,LIBCCALL,(char const *__restrict asc, struct ether_addr *__restrict addr),(asc,addr));
DEFINE_PUBLIC_ALIAS_P(ether_aton_np,libc_ether_aton_np,WUNUSED ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(char const *__restrict asc, struct ether_addr *__restrict addr),(asc,addr));
DEFINE_PUBLIC_ALIAS_P(ether_line,libc_ether_line,WUNUSED ATTR_IN(1) ATTR_OUT(2) ATTR_OUT(3),int,NOTHROW_NCX,LIBCCALL,(char const *line, struct ether_addr *addr, char *hostname),(line,addr,hostname));
DEFINE_PUBLIC_ALIAS_P(ether_line_np,libc_ether_line_np,WUNUSED ATTR_IN(1) ATTR_OUT(2),char *,NOTHROW_NCX,LIBCCALL,(char *line, struct ether_addr *addr),(line,addr));
DEFINE_PUBLIC_ALIAS_P(ether_ntohost,libc_ether_ntohost,ATTR_IN(2) ATTR_OUT(1),int,NOTHROW_RPC_KOS,LIBCCALL,(char *hostname, struct ether_addr const *addr),(hostname,addr));
DEFINE_PUBLIC_ALIAS_P(ether_hostton,libc_ether_hostton,ATTR_IN(1) ATTR_OUT(2),int,NOTHROW_RPC_KOS,LIBCCALL,(char const *hostname, struct ether_addr *addr),(hostname,addr));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_NETINET_ETHER_C */
