/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: DragonFly BSD (/sys/net/ethernet.h) */
/* (#) Portability: FreeBSD       (/sys/net/ethernet.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/net/ethernet.h) */
/* (#) Portability: GNU Hurd      (/usr/include/net/ethernet.h) */
/* (#) Portability: diet libc     (/include/net/ethernet.h) */
/* (#) Portability: libc6         (/include/net/ethernet.h) */
/* (#) Portability: mintlib       (/include/net/ethernet.h) */
/* (#) Portability: musl libc     (/include/net/ethernet.h) */
/* (#) Portability: uClibc        (/include/net/ethernet.h) */
#ifndef _NET_ETHERNET_H
#define _NET_ETHERNET_H 1

#include <__stdinc.h>
#include <features.h>

#include <linux/if_ether.h> /* IEEE 802.3 Ethernet constants */
#include <bits/types.h>
#include <net/bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

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

/* Based on the FreeBSD version of this file. Curiously, that file
   lacks a copyright in the header. */

__SYSDECL_BEGIN

/* This is a name for the 48 bit ethernet address available on many systems. */
#ifdef __CC__
struct __ATTR_PACKED ether_addr {
	__uint8_t ether_addr_octet[ETH_ALEN];
};
#endif /* __CC__ */

/* 10Mb/s ethernet header */
#ifdef __CC__
#ifndef __USE_KOS_PURE /* Use `struct ethhdr' (it's the same structure with different names) */
struct __ATTR_PACKED ether_header {
	__uint8_t   ether_dhost[ETH_ALEN]; /* destination eth addr */
	__uint8_t   ether_shost[ETH_ALEN]; /* source ether addr */
	__u_net16_t ether_type;            /* packet type ID field */
};
#endif /* !__USE_KOS_PURE */
#endif /* __CC__ */

/* Ethernet protocol ID's */
#ifndef __USE_KOS_PURE /* Use the underlying macros instead */
#define ETHERTYPE_PUP       ETH_P_PUP      /* Xerox PUP */
#define ETHERTYPE_SPRITE    ETH_P_SPRITE   /* Sprite */
#define ETHERTYPE_IP        ETH_P_IP       /* IP */
#define ETHERTYPE_ARP       ETH_P_ARP      /* Address resolution */
#define ETHERTYPE_REVARP    ETH_P_RARP     /* Reverse ARP */
#define ETHERTYPE_AT        ETH_P_ATALK    /* AppleTalk protocol */
#define ETHERTYPE_AARP      ETH_P_AARP     /* AppleTalk ARP */
#define ETHERTYPE_VLAN      ETH_P_8021Q    /* IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_IPX       ETH_P_IPX      /* IPX */
#define ETHERTYPE_IPV6      ETH_P_IPV6     /* IP protocol version 6 */
#define ETHERTYPE_LOOPBACK  ETH_P_LOOPBACK /* used to test interfaces */
#endif /* !__USE_KOS_PURE */

#define ETHER_ADDR_LEN   ETH_ALEN                       /* size of ethernet addr */
#define ETHER_TYPE_LEN   (ETH_HLEN - (2 * ETH_ALEN))    /* bytes in type field */
#define ETHER_CRC_LEN    ETH_FCS_LEN                    /* bytes in CRC field */
#define ETHER_HDR_LEN    ETH_HLEN                       /* total octets in header */
#define ETHER_MIN_LEN   (ETH_ZLEN + ETHER_CRC_LEN)      /* min packet length */
#define ETHER_MAX_LEN   (ETH_FRAME_LEN + ETHER_CRC_LEN) /* max packet length */

/* make sure ethernet length is valid */
#define ETHER_IS_VALID_LEN(foo) \
	((foo) >= ETHER_MIN_LEN && (foo) <= ETHER_MAX_LEN)

/* The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header. */
#define ETHERTYPE_TRAIL    0x1000 /* Trailer packet */
#define ETHERTYPE_NTRAILER 16

#define ETHERMTU   ETH_DATA_LEN
#define ETHERMIN  (ETHER_MIN_LEN - ETHER_HDR_LEN - ETHER_CRC_LEN)

__SYSDECL_END

#endif /* !_NET_ETHERNET_H */
