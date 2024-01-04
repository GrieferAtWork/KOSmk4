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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/netpacket/packet.h) */
/* (#) Portability: diet libc     (/include/netpacket/packet.h) */
/* (#) Portability: libc6         (/include/netpacket/packet.h) */
/* (#) Portability: musl libc     (/include/netpacket/packet.h) */
/* (#) Portability: uClibc        (/include/netpacket/packet.h) */
#ifndef _NETPACKET_PACKET_H
#define _NETPACKET_PACKET_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* Definitions for use with Linux AF_PACKET sockets.
   Copyright (C) 1998-2016 Free Software Foundation, Inc.
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

__DECL_BEGIN

#ifdef __CC__
struct sockaddr_ll {
	__UINT16_TYPE__ sll_family;
	__UINT16_TYPE__ sll_protocol;
	__INT32_TYPE__  sll_ifindex;
	__UINT16_TYPE__ sll_hatype;
	__UINT8_TYPE__  sll_pkttype;
	__UINT8_TYPE__  sll_halen;
	__UINT8_TYPE__  sll_addr[8];
};
#endif /* __CC__ */

/* Packet types. */

#define PACKET_HOST      0 /* To us. */
#define PACKET_BROADCAST 1 /* To all. */
#define PACKET_MULTICAST 2 /* To group. */
#define PACKET_OTHERHOST 3 /* To someone else. */
#define PACKET_OUTGOING  4 /* Originated by us . */
#define PACKET_LOOPBACK  5
#define PACKET_FASTROUTE 6

/* Packet socket options. */

#define PACKET_ADD_MEMBERSHIP  1
#define PACKET_DROP_MEMBERSHIP 2
#define PACKET_RECV_OUTPUT     3
#define PACKET_RX_RING         5
#define PACKET_STATISTICS      6
#define PACKET_COPY_THRESH     7
#define PACKET_AUXDATA         8
#define PACKET_ORIGDEV         9
#define PACKET_VERSION         10
#define PACKET_HDRLEN          11
#define PACKET_RESERVE         12
#define PACKET_TX_RING         13
#define PACKET_LOSS            14
#define PACKET_VNET_HDR        15
#define PACKET_TX_TIMESTAMP    16
#define PACKET_TIMESTAMP       17
#define PACKET_FANOUT          18
#define PACKET_TX_HAS_OFF      19
#define PACKET_QDISC_BYPASS    20
#define PACKET_ROLLOVER_STATS  21
#define PACKET_FANOUT_DATA     22

#ifdef __CC__
struct packet_mreq {
	__INT32_TYPE__  mr_ifindex;
	__UINT16_TYPE__ mr_type;
	__UINT16_TYPE__ mr_alen;
	__UINT8_TYPE__  mr_address[8];
};
#endif /* __CC__ */

#define PACKET_MR_MULTICAST 0
#define PACKET_MR_PROMISC   1
#define PACKET_MR_ALLMULTI  2
#define PACKET_MR_UNICAST   3

__DECL_END

#endif /* !_NETPACKET_PACKET_H */
