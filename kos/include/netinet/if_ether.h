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
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/if_ether.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/if_ether.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/netinet/if_ether.h) */
/* (#) Portability: NetBSD        (/sys/netinet/if_ether.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/if_ether.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/if_ether.h) */
/* (#) Portability: diet libc     (/include/netinet/if_ether.h) */
/* (#) Portability: libc6         (/include/netinet/if_ether.h) */
/* (#) Portability: mintlib       (/include/netinet/if_ether.h) */
/* (#) Portability: musl libc     (/include/netinet/if_ether.h) */
/* (#) Portability: uClibc        (/include/netinet/if_ether.h) */
#ifndef _NETINET_IF_ETHER_H
#define _NETINET_IF_ETHER_H  1

#include <__stdinc.h>
#include <features.h>
#include <linux/if_ether.h>

#ifdef __USE_MISC
#include <net/ethernet.h>
#include <net/bits/types.h>
#include <net/if_arp.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

__DECL_BEGIN

/* Ethernet-Address-Resolution-Protocol. */
#ifdef __CC__
struct ether_arp {
#ifdef __USE_KOS_PURE
	struct arphdr ea_hdr; /* fixed-size header. */
#elif (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
       defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		struct arphdr   ea_hdr; /* fixed-size header. */
		struct {
			__u_net16_t arp_hrd; /* format of hardware address. (One of `ARPHRD_*') */
			__u_net16_t arp_pro; /* format of protocol address. (One of `ETH_P_*' from <linux/if_ether.h>) */
			__uint8_t   arp_hln; /* length of hardware address (in bytes). */
			__uint8_t   arp_pln; /* length of protocol address (in bytes). */
			__u_net16_t arp_op;  /* ARP opcode (command). (One of `ARPOP_*') */
		};
	};
#else /* ... */
	struct arphdr ea_hdr; /* fixed-size header. */
#define arp_hrd   ea_hdr.ar_hrd
#define arp_pro   ea_hdr.ar_pro
#define arp_hln   ea_hdr.ar_hln
#define arp_pln   ea_hdr.ar_pln
#define arp_op    ea_hdr.ar_op
#endif /* !... */
	__uint8_t     arp_sha[ETH_ALEN]; /* Sender hardware address. */
	__uint8_t     arp_spa[4];        /* Sender protocol address. */
	__uint8_t     arp_tha[ETH_ALEN]; /* Target hardware address. */
	__uint8_t     arp_tpa[4];        /* Target protocol address. */
};
#endif /* __CC__ */

/* Macro to map an IP multicast address to an Ethernet multicast  address.
 * The high-order 25 bits of the Ethernet address are statically assigned,
 * and the low-order 23 bits are taken from the low end of the IP address. */
#ifdef __CC__
#define ETHER_MAP_IP_MULTICAST(/*struct in_addr **/ ipaddr,      \
                               /*u_char*/ enaddr /*[ETH_ALEN]*/) \
	((enaddr)[0] = 0x01, (enaddr)[1] = 0x00, (enaddr)[2] = 0x5e, \
	 (enaddr)[3] = ((u_int8_t *)(ipaddr))[1] & 0x7f,             \
	 (enaddr)[4] = ((u_int8_t *)(ipaddr))[2],                    \
	 (enaddr)[5] = ((u_int8_t *)(ipaddr))[3])
#endif /* __CC__ */

__DECL_END
#endif /* __USE_MISC */

#endif /* !_NETINET_IF_ETHER_H */
