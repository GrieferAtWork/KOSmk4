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
%[default_impl_section(".text.crt.net.ether")]

%{
#include <features.h>
#include <netinet/if_ether.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/netinet/ether.h */
/* Functions for storing Ethernet addresses in ASCII and mapping to hostnames.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef __CC__

}

@@Convert 48 bit Ethernet ADDRess to ASCII
[[impl_include("<net/ethernet.h>")]]
[[nonnull]] char *ether_ntoa([[nonnull]] struct ether_addr const *__restrict addr) {
	static char buf[21];
	return ether_ntoa_r(addr, buf);
}

[[doc_alias("ether_ntoa"), impl_include("<net/ethernet.h>")]]
[[nonnull]] char *ether_ntoa_r([[nonnull]] struct ether_addr const *__restrict addr,
                               [[nonnull]] char *__restrict buf) {
	sprintf(buf, "%x:%x:%x:%x:%x:%x",
	        addr->@ether_addr_octet@[0], addr->@ether_addr_octet@[1],
	        addr->@ether_addr_octet@[2], addr->@ether_addr_octet@[3],
	        addr->@ether_addr_octet@[4], addr->@ether_addr_octet@[5]);
	return buf;
}

@@Convert ASCII string S to 48 bit Ethernet address
[[impl_include("<net/ethernet.h>")]]
[[nonnull]] struct ether_addr *ether_aton([[nonnull]] char const *__restrict asc) {
	static struct @ether_addr@ addr;
	return ether_aton_r(asc, &addr);
}

[[wunused, doc_alias("ether_aton"), impl_include("<net/ethernet.h>")]]
struct ether_addr *ether_aton_r([[nonnull]] char const *__restrict asc,
                                [[nonnull]] struct ether_addr *__restrict addr) {
	return ether_paton_r((char const **)&asc, addr);
}

%#ifdef __USE_KOS
[[wunused, doc_alias("ether_aton"), impl_include("<net/ethernet.h>")]]
struct ether_addr *ether_paton_r([[nonnull]] char const **__restrict pasc,
                                 [[nonnull]] struct ether_addr *__restrict addr) {
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
		addr->@ether_addr_octet@[i] = octet;
	}
	*pasc = asc;
	return addr;
}
%#endif /* __USE_KOS */

@@Scan LINE and set ADDR and HOSTNAME
int ether_line([[nonnull]] char const *line,
               [[nonnull]] struct ether_addr *addr,
               [[nonnull]] char *hostname) {
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

@@Map 48 bit Ethernet number ADDR to HOSTNAME
[[cp_kos]]
int ether_ntohost(char *hostname, struct ether_addr const *addr);

@@Map HOSTNAME to 48 bit Ethernet address
[[cp_kos]]
int ether_hostton(char const *hostname, struct ether_addr *addr);


%{

#endif /* __CC__ */

__SYSDECL_END

}