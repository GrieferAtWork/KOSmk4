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
%(c_prefix){
/* (#) Portability: GNU C Library (/inet/netinet/ether.h) */
/* (#) Portability: diet libc     (/include/netinet/ether.h) */
/* (#) Portability: libc6         (/include/netinet/ether.h) */
/* (#) Portability: musl libc     (/include/netinet/ether.h) */
/* (#) Portability: uClibc        (/include/netinet/ether.h) */
}

%[default:section(".text.crt{|.dos}.net.ether")]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <net/ethernet.h>
)]%[insert:prefix(
#include <netinet/if_ether.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

@@Convert `addr' into a 20-character-long string that
@@uses the the standard `AA:BB:CC:DD:EE:FF' notation.
[[decl_prefix(struct ether_addr;)]]
[[nonnull, wunused, impl_include("<net/ethernet.h>")]]
char *ether_ntoa([[in]] struct ether_addr const *__restrict addr) {
	static char buf[21];
	return ether_ntoa_r(addr, buf);
}

[[decl_prefix(struct ether_addr;)]]
[[doc_alias("ether_ntoa"), impl_include("<net/ethernet.h>")]]
[[nonnull]] char *ether_ntoa_r([[in]] struct ether_addr const *__restrict addr,
                               [[out]] char *__restrict buf) {
	sprintf(buf, "%x:%x:%x:%x:%x:%x",
	        addr->@ether_addr_octet@[0], addr->@ether_addr_octet@[1],
	        addr->@ether_addr_octet@[2], addr->@ether_addr_octet@[3],
	        addr->@ether_addr_octet@[4], addr->@ether_addr_octet@[5]);
	return buf;
}

@@To   the   reverse  of   `ether_ntoa()'   and  convert
@@a `AA:BB:CC:DD:EE:FF'-string into an ethernet address.
[[decl_prefix(struct ether_addr;)]]
[[wunused, nonnull, impl_include("<net/ethernet.h>")]]
struct ether_addr *ether_aton([[in]] char const *__restrict asc) {
	static struct @ether_addr@ addr;
	return ether_aton_r(asc, &addr);
}

[[decl_prefix(struct ether_addr;)]]
[[wunused, doc_alias("ether_aton"), impl_include("<net/ethernet.h>")]]
struct ether_addr *ether_aton_r([[in]] char const *__restrict asc,
                                [[out]] struct ether_addr *__restrict addr) {
	return ether_paton_r((char const **)&asc, addr);
}

%#ifdef __USE_KOS
[[decl_prefix(struct ether_addr;)]]
[[wunused, doc_alias("ether_aton")]]
[[impl_include("<net/ethernet.h>", "<libc/template/hex.h>")]]
struct ether_addr *ether_paton_r([[inout]] char const **__restrict pasc,
                                 [[out]] struct ether_addr *__restrict addr) {
	unsigned int i;
	char const *asc = *pasc;
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
		} else if (!c || isspace(c)) {
			if (i < 5)
				return NULL;
		} else {
			return NULL;
		}
		addr->@ether_addr_octet@[i] = octet;
	}
	*pasc = asc;
	return addr;
}
%#endif /* __USE_KOS */

@@Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
@@its `addr' and `hostname' parts. For this purpose, the  given
@@`line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
@@@return: 0 : Success
@@@return: -1: Failed to parse the  `addr'-portion
@@             (`ether_paton_r()' returned `NULL')
[[decl_prefix(struct ether_addr;)]]
[[wunused, impl_include("<net/ethernet.h>")]]
int ether_line([[in]] char const *line,
               [[out]] struct ether_addr *addr,
               [[out]] char *hostname) {
	size_t hnlen;
	while (isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	if (!ether_paton_r(&line, addr))
		return -1; /* This also handles comment lines! */
	while (isspace(*line) && *line != '\r' && *line != '\n')
		++line;
	/* The remainder of the line is the hostname. */
	for (hnlen = 0;
	     line[hnlen] &&
	     line[hnlen] != '\r' &&
	     line[hnlen] != '\n';
	     ++hnlen)
		;
	while (hnlen && isspace(line[hnlen - 1]))
		--hnlen;
	if (!hnlen)
		return -1; /* No hostname */
	hostname = (char *)mempcpy(hostname, line, hnlen);
	*hostname = '\0'; /* NUL-terminate */
	return 0;
}

@@Map a given `addr' to its corresponding hostname from `/etc/ethers'
@@@return: 0 : Success
@@@return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist.
[[cp_kos, decl_prefix(struct ether_addr;)]]
int ether_ntohost([[out]] char *hostname,
                  [[in]] struct ether_addr const *addr);
/* TODO: Implement `ether_ntohost()' inline */


@@Map a given `hostname' into its corresponding address from `/etc/ethers'
@@@return: 0 : Success
@@@return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist.
[[cp_kos, decl_prefix(struct ether_addr;)]]
int ether_hostton([[in]] char const *hostname,
                  [[out]] struct ether_addr *addr);
/* TODO: Implement `ether_hostton()' inline */


%{

__SYSDECL_END
#endif /* __CC__ */

}
