/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NET_ETHERNET_H
#define _NET_ETHERNET_H 1

#include <__stdinc.h>
#include <sys/types.h>
#include <linux/if_ether.h>     /* IEEE 802.3 Ethernet constants */

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
	u_int8_t ether_addr_octet[ETH_ALEN];
};
#endif /* __CC__ */

/* 10Mb/s ethernet header */
#ifdef __CC__
struct __ATTR_PACKED ether_header {
	u_int8_t  ether_dhost[ETH_ALEN];    /* destination eth addr */
	u_int8_t  ether_shost[ETH_ALEN];    /* source ether addr */
	u_int16_t ether_type;                /* packet type ID field */
};
#endif /* __CC__ */

/* Ethernet protocol ID's */
#define ETHERTYPE_PUP       0x0200 /* Xerox PUP */
#define ETHERTYPE_SPRITE    0x0500 /* Sprite */
#define ETHERTYPE_IP        0x0800 /* IP */
#define ETHERTYPE_ARP       0x0806 /* Address resolution */
#define ETHERTYPE_REVARP    0x8035 /* Reverse ARP */
#define ETHERTYPE_AT        0x809B /* AppleTalk protocol */
#define ETHERTYPE_AARP      0x80F3 /* AppleTalk ARP */
#define ETHERTYPE_VLAN      0x8100 /* IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_IPX       0x8137 /* IPX */
#define ETHERTYPE_IPV6      0x86dd /* IP protocol version 6 */
#define ETHERTYPE_LOOPBACK  0x9000 /* used to test interfaces */


#define ETHER_ADDR_LEN   ETH_ALEN                       /* size of ethernet addr */
#define ETHER_TYPE_LEN   2                              /* bytes in type field */
#define ETHER_CRC_LEN    4                              /* bytes in CRC field */
#define ETHER_HDR_LEN    ETH_HLEN                       /* total octets in header */
#define ETHER_MIN_LEN   (ETH_ZLEN + ETHER_CRC_LEN)      /* min packet length */
#define ETHER_MAX_LEN   (ETH_FRAME_LEN + ETHER_CRC_LEN) /* max packet length */

/* make sure ethenet length is valid */
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
