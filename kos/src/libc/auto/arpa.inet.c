/* HASH CRC-32:0xd5db193d */
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
#ifndef GUARD_LIBC_AUTO_ARPA_INET_C
#define GUARD_LIBC_AUTO_ARPA_INET_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "arpa.inet.h"
#include "stdio.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <netinet/in.h>

#include <hybrid/__byteswap.h>
/* Return network number part of the Internet address IN */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_netof") uint32_t
NOTHROW_NCX(LIBCCALL libc_inet_netof)(struct in_addr inaddr) {
#line 65 "kos/src/libc/magic/arpa.inet.c"
	uint32_t addr = __hybrid_betoh32(inaddr.s_addr);
	if (IN_CLASSA(addr)) {
		return (addr & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT;
	} else if (IN_CLASSB(addr)) {
		return (addr & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT;
	} else {
		return (addr & IN_CLASSC_NET) >> IN_CLASSC_NSHIFT;
	}
}

#include <netinet/in.h>

#include <hybrid/__byteswap.h>
/* Return the local host address part of the Internet address in IN */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_lnaof") uint32_t
NOTHROW_NCX(LIBCCALL libc_inet_lnaof)(struct in_addr inaddr) {
#line 80 "kos/src/libc/magic/arpa.inet.c"
	uint32_t addr = __hybrid_betoh32(inaddr.s_addr);
	if (IN_CLASSA(addr)) {
		return addr & IN_CLASSA_HOST;
	} else if (IN_CLASSB(addr)) {
		return addr & IN_CLASSB_HOST;
	} else {
		return addr & IN_CLASSC_HOST;
	}
}

#include <netinet/in.h>

#include <hybrid/__byteswap.h>
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
INTERN ATTR_CONST WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_makeaddr") struct in_addr
NOTHROW_NCX(LIBCCALL libc_inet_makeaddr)(uint32_t net,
                                         uint32_t host) {
#line 96 "kos/src/libc/magic/arpa.inet.c"
	struct in_addr result;
	uint32_t result_addr;
	if (net < IN_CLASSA_MAX)
		result_addr = (net << IN_CLASSA_NSHIFT) | (host & IN_CLASSA_HOST);
	else if (net < IN_CLASSB_MAX)
		result_addr = (net << IN_CLASSB_NSHIFT) | (host & IN_CLASSB_HOST);
	else if (net < IN_CLASSC_MAX)
		result_addr = (net << IN_CLASSC_NSHIFT) | (host & IN_CLASSC_HOST);
	else {
		result_addr = net | host;
	}
	result.s_addr = __hybrid_htobe32(result_addr);
	return result;
}

#include <netinet/in.h>
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
INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_addr") in_addr_t
NOTHROW_NCX(LIBCCALL libc_inet_addr)(char const *__restrict cp) {
#line 124 "kos/src/libc/magic/arpa.inet.c"
	struct in_addr addr;
	if (!libc_inet_paton((char const **)&cp, &addr, 0) || *cp)
		return INADDR_NONE;
	return addr.s_addr;
}

/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
INTERN ATTR_RETNONNULL WUNUSED
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_ntoa") char *
NOTHROW_NCX(LIBCCALL libc_inet_ntoa)(struct in_addr inaddr) {
#line 134 "kos/src/libc/magic/arpa.inet.c"
	static char buf[16];
	return libc_inet_ntoa_r(inaddr, buf);
}

#include <netinet/in.h>

#include <hybrid/__byteswap.h>
/* Re-entrant version of `inet_ntoa()' */
INTERN ATTR_RETNONNULL NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_ntoa_r") char *
NOTHROW_NCX(LIBCCALL libc_inet_ntoa_r)(struct in_addr inaddr,
                                       char buf[16]) {
#line 144 "kos/src/libc/magic/arpa.inet.c"
	uint32_t addr = __hybrid_betoh32(inaddr.s_addr);
	libc_sprintf(buf, "%u.%u.%u.%u",
	        (unsigned int)(u8)((addr & __UINT32_C(0xff000000)) >> 24),
	        (unsigned int)(u8)((addr & __UINT32_C(0x00ff0000)) >> 16),
	        (unsigned int)(u8)((addr & __UINT32_C(0x0000ff00)) >> 8),
	        (unsigned int)(u8)((addr & __UINT32_C(0x000000ff))));
	return buf;
}

#include <netinet/in.h>

#include <hybrid/__byteswap.h>
/* This function is the same as `inet_addr()', except that
 * the return value is in host-endian, rather than net-endian */
INTERN ATTR_PURE NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_network") uint32_t
NOTHROW_NCX(LIBCCALL libc_inet_network)(char const *__restrict cp) {
#line 159 "kos/src/libc/magic/arpa.inet.c"
	struct in_addr addr;
	if (!libc_inet_paton((char const **)&cp, &addr, 1) || *cp)
		return INADDR_NONE;
	return addr.s_addr;
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
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_aton") int
NOTHROW_NCX(LIBCCALL libc_inet_aton)(char const *__restrict cp,
                                     struct in_addr *__restrict inp) {
#line 184 "kos/src/libc/magic/arpa.inet.c"
	return libc_inet_paton((char const **)&cp, inp, 0) && !*cp;
}

#include <hybrid/__byteswap.h>
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
INTERN WUNUSED NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_paton") int
NOTHROW_NCX(LIBCCALL libc_inet_paton)(char const **__restrict pcp,
                                      struct in_addr *__restrict inp,
                                      int network_addr) {
#line 205 "kos/src/libc/magic/arpa.inet.c"
	uint32_t result;
	uint32_t parts[4];
	char const *cp = *pcp;
	unsigned int i;
	for (i = 0;;) {
		char ch = *cp;
		uint32_t part, new_part;
		if (ch != '0') {
			/* Decimal. */
			if unlikely(!(ch >= '0' && ch <= '9'))
				goto err; /* Bad format. */
			part = ch - '0';
			++cp;
			for (;;) {
				ch = *cp;
				if (!(ch >= '0' && ch <= '9'))
					break;
				new_part = part * 10;
				new_part += ch - '0';
				if unlikely(new_part < part)
					goto err; /* Overflow */
				part = new_part;
				++cp;
			}
		} else {
			++cp;
			ch = *cp;
			if (ch == 'x' || ch == 'X') {
				/* Hex-part */
				part = 0;
				++cp;
				for (;;) {
					uint8_t digit;
					ch = *cp;
					if (ch >= '0' && ch <= '9') {
						digit = ch - '0';
					} else if (ch >= 'a' && ch <= 'f') {
						digit = 10 + ch - 'a';
					} else if (ch >= 'A' && ch <= 'F') {
						digit = 10 + ch - 'A';
					} else {
						break;
					}
					new_part = part * 16;
					new_part += digit;
					if unlikely(new_part < part)
						goto err; /* Overflow */
					part = new_part;
					++cp;
				}
			} else if (ch >= '0' && ch <= '7') {
				/* Oct-part */
				part = ch - '0';
				++cp;
				for (;;) {
					ch = *cp;
					if (!(ch >= '0' && ch <= '7'))
						break;
					new_part = part * 8;
					new_part += ch - '0';
					if unlikely(new_part < part)
						goto err; /* Overflow */
					part = new_part;
					++cp;
				}
			} else {
				/* Zero-part */
				part = 0;
			}
		}
		parts[i] = part;
		++i;
		if (i >= 4) {
			if unlikely(*cp == '.')
				goto err; /* Bad format. */
			break;
		}
		if (*cp != '.')
			break;
		if unlikely(part > 0xff)
			goto err; /* Only the last part can be > 255 */
		++cp;
	}
	switch (__builtin_expect(i, 4)) {
	case 4:
		if unlikely(parts[3] > 0xff)
			goto err;
		result = parts[0] << 24 |
		         parts[1] << 16 |
		         parts[2] << 8 |
		         parts[3];
		break;
	case 3:
		if (network_addr) {
			if unlikely(parts[2] > 0xff)
				goto err;
			result = parts[0] << 16 |
			         parts[1] << 8 |
			         parts[2];
		} else {
			if unlikely(parts[2] > 0xffff)
				goto err;
			result = parts[0] << 24 |
			         parts[1] << 16 |
			         parts[2];
		}
		break;
	case 2:
		if (network_addr) {
			if unlikely(parts[1] > 0xff)
				goto err;
			result = parts[0] << 8 |
			         parts[1];
		} else {
			if unlikely(parts[1] > 0xffffff)
				goto err;
			result = parts[0] << 24 |
			         parts[1];
		}
		break;
	case 1:
		if (network_addr) {
			if unlikely(parts[0] > 0xff)
				goto err;
		}
		result = parts[0];
		break;
	default: __builtin_unreachable();
	}
	inp->s_addr = __hybrid_htobe32(result);
	*pcp = cp;
	return 1;
err:
	return 0;
}

#include <parts/errno.h>
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
INTERN NONNULL((2))
ATTR_WEAK ATTR_SECTION(".text.crt.net.inet.inet_neta") char *
NOTHROW_NCX(LIBCCALL libc_inet_neta)(uint32_t net,
                                     char *buf,
                                     size_t len) {
#line 346 "kos/src/libc/magic/arpa.inet.c"
	size_t reqlen;
	if (net <= 0xff) {
		if (!net) {
			reqlen = 8;
			if likely(len >= 8)
				memcpy(buf, "0.0.0.0", 8 * sizeof(char));
		} else {
			reqlen = libc_snprintf(buf, len, "%u", (unsigned int)net);
		}
	} else if (net <= 0xffff) {
		reqlen = libc_snprintf(buf, len, "%u.%u",
		                  (unsigned int)((net & 0xff00) >> 8),
		                  (unsigned int)(net & 0xff));
	} else if (net <= 0xffffff) {
		reqlen = libc_snprintf(buf, len, "%u.%u.%u",
		                  (unsigned int)((net & 0xff0000) >> 16),
		                  (unsigned int)((net & 0xff00) >> 8),
		                  (unsigned int)(net & 0xff));
	} else {
		reqlen = libc_snprintf(buf, len, "%u.%u.%u.%u",
		                  (unsigned int)((net & 0xff000000) >> 24),
		                  (unsigned int)((net & 0xff0000) >> 16),
		                  (unsigned int)((net & 0xff00) >> 8),
		                  (unsigned int)(net & 0xff));
	}
	if unlikely(reqlen > len)
		goto too_small;
	return buf;
too_small:
#ifdef __EMSGSIZE
	__libc_seterrno(__EMSGSIZE);
#elif defined(__ERANGE)
	__libc_seterrno(__ERANGE);
#elif defined(__EINVAL)
	__libc_seterrno(__EINVAL);
#endif
	return NULL;
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(inet_netof, libc_inet_netof);
DEFINE_PUBLIC_WEAK_ALIAS(inet_lnaof, libc_inet_lnaof);
DEFINE_PUBLIC_WEAK_ALIAS(inet_makeaddr, libc_inet_makeaddr);
DEFINE_PUBLIC_WEAK_ALIAS(inet_addr, libc_inet_addr);
DEFINE_PUBLIC_WEAK_ALIAS(inet_ntoa, libc_inet_ntoa);
DEFINE_PUBLIC_WEAK_ALIAS(inet_ntoa_r, libc_inet_ntoa_r);
DEFINE_PUBLIC_WEAK_ALIAS(inet_network, libc_inet_network);
DEFINE_PUBLIC_WEAK_ALIAS(inet_aton, libc_inet_aton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_paton, libc_inet_paton);
DEFINE_PUBLIC_WEAK_ALIAS(inet_neta, libc_inet_neta);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ARPA_INET_C */
