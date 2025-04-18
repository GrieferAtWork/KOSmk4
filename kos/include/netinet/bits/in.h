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
/*!included_by <netinet/in.h>*/
#ifndef _NETINET_BITS_IN_H
#define _NETINET_BITS_IN_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <net/bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <stdint.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

/* Internet address. */
#ifdef __CC__
typedef __u_net32_t in_addr_t;
struct in_addr {
	in_addr_t s_addr;
};
#endif /* __CC__ */


/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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

/* Options for use with `getsockopt' and `setsockopt' at the IP level.
 * The first word in the comment at  the right is the data type  used;
 * "bool" means a boolean value stored in an `int'. */
#define IP_OPTIONS                4  /* ip_opts; IP per-packet options. */
#define IP_HDRINCL                3  /* int; Header is included with data. */
#define IP_TOS                    1  /* int; IP type of service and precedence. */
#define IP_TTL                    2  /* int; IP time to live. */
#define IP_RECVOPTS               6  /* bool; Receive all IP options w/datagram. */
/* For BSD compatibility. */
#define IP_RECVRETOPTS            IP_RETOPTS /* bool; Receive IP options for response. */
#define IP_RETOPTS                7  /* ip_opts; Set/get IP per-packet options. */
#define IP_MULTICAST_IF           32 /* in_addr; set/get IP multicast i/f */
#define IP_MULTICAST_TTL          33 /* u_char; set/get IP multicast ttl */
#define IP_MULTICAST_LOOP         34 /* i_char; set/get IP multicast loopback */
#define IP_ADD_MEMBERSHIP         35 /* ip_mreq; add an IP group membership */
#define IP_DROP_MEMBERSHIP        36 /* ip_mreq; drop an IP group membership */
#define IP_UNBLOCK_SOURCE         37 /* ip_mreq_source: unblock data from source */
#define IP_BLOCK_SOURCE           38 /* ip_mreq_source: block data from source */
#define IP_ADD_SOURCE_MEMBERSHIP  39 /* ip_mreq_source: join source group */
#define IP_DROP_SOURCE_MEMBERSHIP 40 /* ip_mreq_source: leave source group */
#define IP_MSFILTER               41

#ifdef __USE_MISC
#define MCAST_JOIN_GROUP      42 /* group_req: join any-source group */
#define MCAST_BLOCK_SOURCE    43 /* group_source_req: block from given group */
#define MCAST_UNBLOCK_SOURCE  44 /* group_source_req: unblock from given group*/
#define MCAST_LEAVE_GROUP     45 /* group_req: leave any-source group */
#define MCAST_JOIN_SOURCE_GROUP 46 /* group_source_req: join source-spec gr */
#define MCAST_LEAVE_SOURCE_GROUP 47 /* group_source_req: leave source-spec gr*/
#define MCAST_MSFILTER        48
#define IP_UNICAST_IF         50
#define MCAST_EXCLUDE         0
#define MCAST_INCLUDE         1
#endif /* __USE_MISC */

#define IP_ROUTER_ALERT    5  /* bool */
#define IP_PKTINFO         8  /* bool */
#define IP_PKTOPTIONS      9
#define IP_PMTUDISC        10 /* obsolete name? */
#define IP_MTU_DISCOVER    10 /* int; see below */
#define IP_RECVERR         11 /* bool */
#define IP_RECVTTL         12 /* bool */
#define IP_RECVTOS         13 /* bool */
#define IP_MTU             14 /* int */
#define IP_FREEBIND        15
#define IP_IPSEC_POLICY    16
#define IP_XFRM_POLICY     17
#define IP_PASSSEC         18
#define IP_TRANSPARENT     19
#define IP_MULTICAST_ALL   49 /* bool */

/* TProxy original addresses */
#define IP_ORIGDSTADDR          20
#define IP_RECVORIGDSTADDR      IP_ORIGDSTADDR
#define IP_MINTTL               21
#define IP_NODEFRAG             22
#define IP_CHECKSUM             23
#define IP_BIND_ADDRESS_NO_PORT 24

/* IP_MTU_DISCOVER arguments. */
#define IP_PMTUDISC_DONT      0 /* Never send DF frames. */
#define IP_PMTUDISC_WANT      1 /* Use per route hints. */
#define IP_PMTUDISC_DO        2 /* Always DF. */
#define IP_PMTUDISC_PROBE     3 /* Ignore dst pmtu. */
#define IP_PMTUDISC_INTERFACE 4 /* Always use interface mtu (ignores dst pmtu) but don't set DF flag.
                                 * Also incoming ICMP  frag_needed notifications will  be ignored  on
                                 * this socket to prevent accepting spoofed ones. */
#define IP_PMTUDISC_OMIT      5 /* Like IP_PMTUDISC_INTERFACE but allow packets to be fragmented. */

/* To select the IP level. */
#define SOL_IP                    0
#define IP_DEFAULT_MULTICAST_TTL  1
#define IP_DEFAULT_MULTICAST_LOOP 1
#define IP_MAX_MEMBERSHIPS        20

#ifdef __CC__
#ifdef __USE_MISC
/* Structure used to describe IP options for IP_OPTIONS and IP_RETOPTS.
 * The  `ip_dst' field is  used for the first-hop  gateway when using a
 * source route (this gets put into the header proper). */
struct ip_opts {
	struct in_addr ip_dst;      /* First hop; zero without source route. */
	char           ip_opts[40]; /* Actually variable in size. */
};

/* Like `struct ip_mreq' but including interface specification by index. */
struct ip_mreqn {
	struct in_addr imr_multiaddr; /* IP multicast address of group */
	struct in_addr imr_address;   /* local IP address of interface */
	__INT32_TYPE__ imr_ifindex;   /* Interface index */
};

/* Structure used for IP_PKTINFO. */
struct in_pktinfo {
	__INT32_TYPE__ ipi_ifindex;  /* Interface index. */
	struct in_addr ipi_spec_dst; /* Routing destination address. */
	struct in_addr ipi_addr;     /* Header destination address. */
};
#endif /* __USE_MISC */
#endif /* __CC__ */

/* Options for use with `getsockopt' and `setsockopt' at the IPv6 level.
 * The first word in  the comment at  the right is  the data type  used;
 * "bool" means a boolean value stored in an `int'. */
#define IPV6_ADDRFORM       1
#define IPV6_2292PKTINFO    2
#define IPV6_2292HOPOPTS    3
#define IPV6_2292DSTOPTS    4
#define IPV6_2292RTHDR      5
#define IPV6_2292PKTOPTIONS 6
#define IPV6_CHECKSUM       7
#define IPV6_2292HOPLIMIT   8
#define SCM_SRCRT           IPV6_RXSRCRT /* XXX: This seems to be defined nowhere... */
#define IPV6_NEXTHOP        9
#define IPV6_AUTHHDR        10
#define IPV6_UNICAST_HOPS   16
#define IPV6_MULTICAST_IF   17
#define IPV6_MULTICAST_HOPS 18
#define IPV6_MULTICAST_LOOP 19
#define IPV6_JOIN_GROUP     20
#define IPV6_LEAVE_GROUP    21
#define IPV6_ROUTER_ALERT   22
#define IPV6_MTU_DISCOVER   23
#define IPV6_MTU            24
#define IPV6_RECVERR        25
#define IPV6_V6ONLY         26
#define IPV6_JOIN_ANYCAST   27
#define IPV6_LEAVE_ANYCAST  28
#define IPV6_IPSEC_POLICY   34
#define IPV6_XFRM_POLICY    35

/* Advanced API (RFC3542) (1). */
#define IPV6_RECVPKTINFO    49
#define IPV6_PKTINFO        50
#define IPV6_RECVHOPLIMIT   51
#define IPV6_HOPLIMIT       52
#define IPV6_RECVHOPOPTS    53
#define IPV6_HOPOPTS        54
#define IPV6_RTHDRDSTOPTS   55
#define IPV6_RECVRTHDR      56
#define IPV6_RTHDR          57
#define IPV6_RECVDSTOPTS    58
#define IPV6_DSTOPTS        59
#define IPV6_RECVPATHMTU    60
#define IPV6_PATHMTU        61
#define IPV6_DONTFRAG       62

/* Advanced API (RFC3542) (2). */
#define IPV6_RECVTCLASS     66
#define IPV6_TCLASS         67

/* Obsolete synonyms for the above. */
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
#define IPV6_RXHOPOPTS      IPV6_HOPOPTS
#define IPV6_RXDSTOPTS      IPV6_DSTOPTS

/* IPV6_MTU_DISCOVER values. */
#define IPV6_PMTUDISC_DONT  0 /* Never send DF frames. */
#define IPV6_PMTUDISC_WANT  1 /* Use per route hints. */
#define IPV6_PMTUDISC_DO    2 /* Always DF. */
#define IPV6_PMTUDISC_PROBE 3 /* Ignore dst pmtu. */
#define IPV6_PMTUDISC_INTERFACE 4 /* See IP_PMTUDISC_INTERFACE. */
#define IPV6_PMTUDISC_OMIT  5 /* See IP_PMTUDISC_OMIT. */

/* Socket level values for IPv6. */
#define SOL_IPV6            41
#define SOL_ICMPV6          58

/* Routing header options for IPv6. */
#define IPV6_RTHDR_LOOSE    0 /* Hop doesn't need to be neighbor. */
#define IPV6_RTHDR_STRICT   1 /* Hop must be a neighbor. */
#define IPV6_RTHDR_TYPE_0   0 /* IPv6 Routing header type 0. */

__SYSDECL_END

#endif /* !_NETINET_BITS_IN_H */
