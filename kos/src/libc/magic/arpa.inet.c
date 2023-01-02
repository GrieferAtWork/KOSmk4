/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/arpa/inet.h) */
/* (#) Portability: DragonFly BSD (/include/arpa/inet.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/arpa/inet.h) */
/* (#) Portability: FreeBSD       (/include/arpa/inet.h) */
/* (#) Portability: GNU C Library (/inet/arpa/inet.h) */
/* (#) Portability: GNU Hurd      (/usr/include/arpa/inet.h) */
/* (#) Portability: NetBSD        (/include/arpa/inet.h) */
/* (#) Portability: OpenBSD       (/include/arpa/inet.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/arpa/inet.h) */
/* (#) Portability: diet libc     (/include/arpa/inet.h) */
/* (#) Portability: libc4/5       (/include/arpa/inet.h) */
/* (#) Portability: libc6         (/include/arpa/inet.h) */
/* (#) Portability: mintlib       (/include/arpa/inet.h) */
/* (#) Portability: musl libc     (/include/arpa/inet.h) */
/* (#) Portability: uClibc        (/include/arpa/inet.h) */
}

%[default:section(".text.crt{|.dos}.net.inet")]
%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[define_replacement(in_addr_t = __u_net32_t)]
%[define_replacement(socklen_t = __socklen_t)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <netinet/in.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

}

@@>> inet_netof(3)
@@Return the network-number-part of the Internet address `INADDR'
[[const, wunused]]
[[decl_include("<hybrid/typecore.h>", "<netinet/bits/in.h>")]]
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

@@>> inet_lnaof(3)
@@Return the local-host-address-part of the Internet address `INADDR'
[[const, wunused]]
[[decl_include("<hybrid/typecore.h>", "<netinet/bits/in.h>")]]
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

@@>> inet_makeaddr(3)
@@Construct  an  Internet-host-address in  network byte  order from
@@the combination of its network (`net'), and host (`host') number.
@@The `net' and `host' arguments  can later be re-extracted by  use
@@of `inet_netof(3)' and `inet_lnaof(3)'
[[const, wunused]]
[[decl_include("<hybrid/typecore.h>", "<netinet/bits/in.h>")]]
[[impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
struct in_addr inet_makeaddr($uint32_t net, $uint32_t host) {
	struct @in_addr@ result;
	uint32_t result_addr;
	if (net < @IN_CLASSA_MAX@) {
		result_addr = (net << @IN_CLASSA_NSHIFT@) | (host & @IN_CLASSA_HOST@);
	} else if (net < @IN_CLASSB_MAX@) {
		result_addr = (net << @IN_CLASSB_NSHIFT@) | (host & @IN_CLASSB_HOST@);
	} else if (net < @IN_CLASSC_MAX@) {
		result_addr = (net << @IN_CLASSC_NSHIFT@) | (host & @IN_CLASSC_HOST@);
	} else {
		result_addr = net | host;
	}
	result.@s_addr@ = __hybrid_htobe32(result_addr);
	return result;
}

@@>> inet_addr(3)
@@Convert an  Internet host  address  `CP' from  its  numbers-and-dots
@@notational form into its binary representation in network byte order
@@Accepted notations are:
@@    a.b.c.d (1.2.3.4)
@@    a.b.cd   (1.2.52)
@@    a.bcd     (1.564)
@@    abcd (4660)
@@With each number allowed to be written in as one of:
@@    123      (decimal)
@@    0x123 (hex)
@@    0123  (oct)
[[pure, impl_include("<netinet/in.h>"), decl_include("<net/bits/types.h>")]]
in_addr_t inet_addr([[in]] char const *__restrict cp) {
	struct @in_addr@ addr;
	if (!inet_paton((char const **)&cp, &addr, 0) || *cp)
		return @INADDR_NONE@;
	return addr.@s_addr@;
}

@@>> inet_ntoa(3)
@@Return   the   conventional  numbers-and-dots   representation   of  a
@@given  Internet  host  address  `inaddr'.  The  returned  pointer   is
@@apart of a static buffer and  may change in subsequence (or  parallel)
@@calls. For a re-entrant version of this function, see `inet_ntoa_r(3)'
[[wunused, nonnull]]
char *inet_ntoa(struct in_addr inaddr) {
	static char buf[16];
	return inet_ntoa_r(inaddr, buf);
}

%#ifdef __USE_KOS
%#define INET_NTOA_R_MAXLEN 16 /* Max # of characters written by `inet_ntoa_r' (e.g. `111.111.111.111\0') */

@@>> inet_ntoa_r(3)
@@Re-entrant version of `inet_ntoa()'
[[decl_include("<netinet/bits/in.h>")]]
[[impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
[[nonnull]]
char *inet_ntoa_r(struct in_addr inaddr, [[out]] char buf[16]) {
	uint32_t addr = __hybrid_betoh32(inaddr.@s_addr@);
	sprintf(buf, "%u.%u.%u.%u",
	        (unsigned int)(u8)((addr & __UINT32_C(0xff000000)) >> 24),
	        (unsigned int)(u8)((addr & __UINT32_C(0x00ff0000)) >> 16),
	        (unsigned int)(u8)((addr & __UINT32_C(0x0000ff00)) >> 8),
	        (unsigned int)(u8)((addr & __UINT32_C(0x000000ff))));
	return buf;
}
%#endif /* __USE_KOS */

@@>> inet_network(3)
@@This function is  the same as  `inet_addr()', except  that
@@the return value is in host-endian, rather than net-endian
[[decl_include("<hybrid/typecore.h>")]]
[[pure, impl_include("<netinet/in.h>", "<hybrid/__byteswap.h>")]]
$uint32_t inet_network([[in]] char const *__restrict cp) {
	struct @in_addr@ addr;
	if (!inet_paton((char const **)&cp, &addr, 1) || *cp)
		return @INADDR_NONE@;
	return addr.@s_addr@;
}

%
%/* The following functions are not part of XNS 5.2. */
%#ifdef __USE_MISC

@@>> inet_aton(3)
@@Convert an Internet host address `CP' from its numbers-and-dots
@@notational form into its binary representation in network  byte
@@order. The result is then stored in `*INP'
@@Accepted notations are:
@@    a.b.c.d (1.2.3.4)
@@    a.b.cd   (1.2.52)
@@    a.bcd     (1.564)
@@    abcd (4660)
@@With each number allowed to be written in as one of:
@@    123      (decimal)
@@    0x123 (hex)
@@    0123  (oct)
@@@return: 0: Bad input format
@@@return: 1: Success
[[decl_include("<netinet/bits/in.h>")]]
int inet_aton([[in]] char const *__restrict cp,
              [[out]] struct in_addr *__restrict inp) {
	return inet_paton((char const **)&cp, inp, 0) && !*cp;
}

%#ifdef __USE_KOS
@@>> inet_paton(3)
@@Same as `inet_aton()', but update `*pcp' to point past the address
@@Accepted notations are:
@@    a.b.c.d (1.2.3.4)
@@    a.b.cd   (1.2.52)
@@    a.bcd     (1.564)
@@    abcd (4660)
@@With each number allowed to be written in as one of:
@@    123      (decimal)
@@    0x123 (hex)
@@    0123  (oct)
@@@param: network_addr: When non-zero, `*pcp' is a network address
@@@return: 0: Bad input format
@@@return: 1: Success
[[wunused]]
[[decl_include("<netinet/bits/in.h>")]]
[[impl_include("<hybrid/__byteswap.h>", "<libc/template/hex.h>")]]
int inet_paton([[inout]] char const **__restrict pcp,
               [[out]] struct in_addr *__restrict inp,
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
					if (!__libc_hex2int(ch, &digit))
						break;
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

@@>> inet_neta(3)
@@Similar to `inet_ntoa_r(3)', but use smaller formats if possible:
@@    0.0.0.0      For net = 0
@@    %u           For net <= 255
@@    %u.%u        For net <= 65535
@@    %u.%u.%u     For net <= 16777215
@@    %u.%u.%u.%u  For everything else
@@@return: buf:  Success
@@@return: NULL: [errno=EMSGSIZE]: The given `len' is too small
[[impl_include("<libc/errno.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
char *inet_neta($uint32_t net, [[out(? <= len)]] char *buf, $size_t len) {
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
@@pp_ifdef EMSGSIZE@@
	(void)libc_seterrno(EMSGSIZE);
@@pp_elif defined(ERANGE)@@
	(void)libc_seterrno(ERANGE);
@@pp_elif defined(EINVAL)@@
	(void)libc_seterrno(EINVAL);
@@pp_endif@@
	return NULL;
}

@@>> inet_net_ntop(3)
@@TODO: Implement & document
[[cp_kos, decl_include("<hybrid/typecore.h>")]]
char *inet_net_ntop(int af, void const *cp, int bits, char *buf, $size_t len);

@@>> inet_net_pton(3)
@@TODO: Implement & document
[[cp_kos, decl_include("<hybrid/typecore.h>")]]
int inet_net_pton(int af, char const *cp, void *buf, $size_t len);

@@>> inet_nsap_addr(3)
@@TODO: Implement & document
[[cp_kos]]
unsigned int inet_nsap_addr(char const *cp, unsigned char *buf, int len);

@@>> inet_nsap_ntoa(3)
@@TODO: Implement & document
[[cp_kos]]
char *inet_nsap_ntoa(int len, unsigned char const *cp, char *buf);

%#endif /* __USE_MISC */

@@>> inet_pton(3)
@@TODO: Implement & document
[[cp_kos]]
int inet_pton(int af, char const *__restrict cp, void *__restrict buf);

@@>> inet_ntop(3)
@@TODO: Implement & document
[[cp_kos, decl_include("<bits/types.h>")]]
char const *inet_ntop(int af, void const *__restrict cp,
                      char *__restrict buf, socklen_t len);


%{

__SYSDECL_END
#endif /* __CC__ */

}
