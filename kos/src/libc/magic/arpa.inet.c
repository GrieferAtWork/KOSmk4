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

%[default_impl_section(".text.crt.net.inet")]
%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[define_replacement(in_addr_t = __u_net32_t)]

%{
#include <features.h>
#include <bits/types.h>
#include <netinet/in.h>

/* Documentation derived from Glibc /usr/include/arpa/inet.h */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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


__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

}

@@Return network number part of the Internet address IN
[[wunused, ATTR_CONST]]
[[impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
$uint32_t inet_netof(struct in_addr inaddr) {
	uint32_t addr = __hybrid_betoh32(inaddr.@s_addr@);
	if (@IN_CLASSA@(addr)) {
		return (addr & @IN_CLASSA_NET@) >> @IN_CLASSA_NSHIFT@;
	} else if (@IN_CLASSB@(addr)) {
		return (addr & @IN_CLASSB_NET@) >> @IN_CLASSB_NSHIFT@;
	} else {
		return (addr & @IN_CLASSC_NET@) >> @IN_CLASSC_NSHIFT@;
	}
}

@@Return the local host address part of the Internet address in IN
[[wunused, ATTR_CONST]]
[[impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
$uint32_t inet_lnaof(struct in_addr inaddr) {
	uint32_t addr = __hybrid_betoh32(inaddr.@s_addr@);
	if (@IN_CLASSA@(addr)) {
		return addr & @IN_CLASSA_HOST@;
	} else if (@IN_CLASSB@(addr)) {
		return addr & @IN_CLASSB_HOST@;
	} else {
		return addr & @IN_CLASSC_HOST@;
	}
}

@@Make Internet host address in network byte order by
@@combining the network number NET with the local address HOST
[[wunused, ATTR_CONST]]
[[impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
struct in_addr inet_makeaddr($uint32_t net, $uint32_t host) {
	struct @in_addr@ result;
	uint32_t result_addr;
	if (net < @IN_CLASSA_MAX@)
		result_addr = (net << @IN_CLASSA_NSHIFT@) | (host & @IN_CLASSA_HOST@);
	else if (net < @IN_CLASSB_MAX@)
		result_addr = (net << @IN_CLASSB_NSHIFT@) | (host & @IN_CLASSB_HOST@);
	else if (net < @IN_CLASSC_MAX@)
		result_addr = (net << @IN_CLASSC_NSHIFT@) | (host & @IN_CLASSC_HOST@);
	else {
		result_addr = net | host;
	}
	result.@s_addr@ = __hybrid_htobe32(result_addr);
	return result;
}

@@Convert Internet host address from numbers-and-dots
@@notation in CP into binary data in network byte order
@@Accepted notations are:
@@    a.b.c.d  (1.2.3.4)
@@    a.b.cd   (1.2.52)
@@    a.bcd    (1.564)
@@    abcd     (4660)
@@With each number allowed to be written in as one of:
@@    123      (decimal)
@@    0x123    (hex)
@@    0123     (oct)
[[ATTR_PURE, impl_include("<netinet/in.h>")]]
in_addr_t inet_addr([[nonnull]] char const *__restrict cp) {
	struct @in_addr@ addr;
	if (!inet_paton((char const **)&cp, &addr, 0) || *cp)
		return @INADDR_NONE@;
	return addr.@s_addr@;
}

@@Convert Internet number in IN to ASCII representation. The return
@@value is a pointer to an internal array containing the string
[[wunused]]
[[nonnull]] char *inet_ntoa(struct in_addr inaddr) {
	static char buf[16];
	return inet_ntoa_r(inaddr, buf);
}

%#ifdef __USE_KOS
%#define INET_NTOA_R_MAXLEN 16 /* Max # of characters written by `inet_ntoa_r' (e.g. `111.111.111.111\0') */
@@Re-entrant version of `inet_ntoa()'
[[impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
[[nonnull]] char *inet_ntoa_r(struct in_addr inaddr, [[nonnull]] char buf[16]) {
	uint32_t addr = __hybrid_betoh32(inaddr.@s_addr@);
	sprintf(buf, "%u.%u.%u.%u",
	        (unsigned int)(u8)((addr & __UINT32_C(0xff000000)) >> 24),
	        (unsigned int)(u8)((addr & __UINT32_C(0x00ff0000)) >> 16),
	        (unsigned int)(u8)((addr & __UINT32_C(0x0000ff00)) >> 8),
	        (unsigned int)(u8)((addr & __UINT32_C(0x000000ff))));
	return buf;
}
%#endif /* __USE_KOS */

@@This function is the same as `inet_addr()', except that
@@the return value is in host-endian, rather than net-endian
[[ATTR_PURE, impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
$uint32_t inet_network([[nonnull]] char const *__restrict cp) {
	struct @in_addr@ addr;
	if (!inet_paton((char const **)&cp, &addr, 1) || *cp)
		return @INADDR_NONE@;
	return addr.@s_addr@;
}

%
%/* The following functions are not part of XNS 5.2. */
%#ifdef __USE_MISC

@@Convert Internet host address from numbers-and-dots notation in
@@CP into binary data and store the result in the structure INP
@@Accepted notations are:
@@    a.b.c.d  (1.2.3.4)
@@    a.b.cd   (1.2.52)
@@    a.bcd    (1.564)
@@    abcd     (4660)
@@With each number allowed to be written in as one of:
@@    123      (decimal)
@@    0x123    (hex)
@@    0123     (oct)
@@@return: 0: Bad input format
@@@return: 1: Success
int inet_aton([[nonnull]] char const *__restrict cp,
              [[nonnull]] struct in_addr *__restrict inp) {
	return inet_paton((char const **)&cp, inp, 0) && !*cp;
}

%#ifdef __USE_KOS
@@Same as `inet_aton()', but update `*pcp' to point after the address
@@Accepted notations are:
@@    a.b.c.d  (1.2.3.4)
@@    a.b.cd   (1.2.52)
@@    a.bcd    (1.564)
@@    abcd     (4660)
@@With each number allowed to be written in as one of:
@@    123      (decimal)
@@    0x123    (hex)
@@    0123     (oct)
@@@param: network_addr: When non-zero, `*pcp' is a network address
@@@return: 0: Bad input format
@@@return: 1: Success
[[wunused, impl_include("<hybrid/__byteswap.h>")]]
int inet_paton([[nonnull]] char const **__restrict pcp,
               [[nonnull]] struct in_addr *__restrict inp,
               int network_addr) {
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
	inp->@s_addr@ = __hybrid_htobe32(result);
	*pcp = cp;
	return 1;
err:
	return 0;
}
%#endif /* __USE_KOS */

@@Format a network number NET into presentation format and place
@@result in buffer starting at BUF with length of LEN bytes
[[impl_include("<parts/errno.h>")]]
char *inet_neta($uint32_t net, [[outp(len)]] char *buf, $size_t len) {
	size_t reqlen;
	if (net <= 0xff) {
		if (!net) {
			reqlen = 8;
			if likely(len >= 8)
				memcpy(buf, "0.0.0.0", 8 * sizeof(char));
		} else {
			reqlen = snprintf(buf, len, "%u", (unsigned int)net);
		}
	} else if (net <= 0xffff) {
		reqlen = snprintf(buf, len, "%u.%u",
		                  (unsigned int)((net & 0xff00) >> 8),
		                  (unsigned int)(net & 0xff));
	} else if (net <= 0xffffff) {
		reqlen = snprintf(buf, len, "%u.%u.%u",
		                  (unsigned int)((net & 0xff0000) >> 16),
		                  (unsigned int)((net & 0xff00) >> 8),
		                  (unsigned int)(net & 0xff));
	} else {
		reqlen = snprintf(buf, len, "%u.%u.%u.%u",
		                  (unsigned int)((net & 0xff000000) >> 24),
		                  (unsigned int)((net & 0xff0000) >> 16),
		                  (unsigned int)((net & 0xff00) >> 8),
		                  (unsigned int)(net & 0xff));
	}
	if unlikely(reqlen > len)
		goto too_small;
	return buf;
too_small:
#ifdef EMSGSIZE
	__libc_seterrno(EMSGSIZE);
#elif defined(ERANGE)
	__libc_seterrno(ERANGE);
#elif defined(EINVAL)
	__libc_seterrno(EINVAL);
#endif
	return NULL;
}

@@Convert network number for interface type AF in buffer starting at CP
@@to presentation format. The result will specify BITS bits of the number
[[cp_kos]]
char *inet_net_ntop(int af, void const *cp, int bits, char *buf, $size_t len);

@@Convert network number for interface type AF from presentation in buffer starting
@@at CP to network format and store result int buffer starting at BUF of size LEN
[[cp_kos]]
int inet_net_pton(int af, char const *cp, void *buf, $size_t len);

@@Convert ASCII representation in hexadecimal form of the Internet address
@@to binary form and place result in buffer of length LEN starting at BUF
[[cp_kos]]
unsigned int inet_nsap_addr(char const *cp, unsigned char *buf, int len);

@@Convert internet address in binary form in LEN bytes
@@starting at CP a presentation form and place result in BUF
[[cp_kos]]
char *inet_nsap_ntoa(int len, unsigned char const *cp, char *buf);

%#endif /* __USE_MISC */

@@Convert from presentation format of an Internet number in buffer
@@starting at CP to the binary network format and store result for
@@interface type AF in buffer starting at BUF
[[cp_kos]]
int inet_pton(int af, char const *__restrict cp, void *__restrict buf);

@@Convert a Internet address in binary network format for interface
@@type AF in buffer starting at CP to presentation form and place
@@result in buffer of length LEN starting at BUF
[[cp_kos]]
char const *inet_ntop(int af, void const *__restrict cp,
                      char *__restrict buf, socklen_t len);


%{

#endif /* __CC__ */

__SYSDECL_END

}