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
#ifndef _BITS_IN_H
#define _BITS_IN_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <features.h>

#ifdef __USE_GLIBC
#include <stdint.h>
#endif /* __USE_GLIBC */

__SYSDECL_BEGIN

/* Internet address. */
#ifdef __CC__
typedef __UINT32_TYPE__ in_addr_t;
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
 * The first word in the comment at the right is the data type used;
 * "bool" means a boolean value stored in an `int'. */
#ifndef IP_OPTIONS
#define IP_OPTIONS                4  /* ip_opts; IP per-packet options. */
#endif /* !IP_OPTIONS */
#ifndef IP_HDRINCL
#define IP_HDRINCL                3  /* int; Header is included with data. */
#endif /* !IP_HDRINCL */
#ifndef IP_TOS
#define IP_TOS                    1  /* int; IP type of service and precedence. */
#endif /* !IP_TOS */
#ifndef IP_TTL
#define IP_TTL                    2  /* int; IP time to live. */
#endif /* !IP_TTL */
#ifndef IP_RECVOPTS
#define IP_RECVOPTS               6  /* bool; Receive all IP options w/datagram. */
#endif /* !IP_RECVOPTS */
/* For BSD compatibility. */
#ifndef IP_RECVRETOPTS
#define IP_RECVRETOPTS            IP_RETOPTS /* bool; Receive IP options for response. */
#endif /* !IP_RECVRETOPTS */
#ifndef IP_RETOPTS
#define IP_RETOPTS                7  /* ip_opts; Set/get IP per-packet options. */
#endif /* !IP_RETOPTS */
#ifndef IP_MULTICAST_IF
#define IP_MULTICAST_IF           32 /* in_addr; set/get IP multicast i/f */
#endif /* !IP_MULTICAST_IF */
#ifndef IP_MULTICAST_TTL
#define IP_MULTICAST_TTL          33 /* u_char; set/get IP multicast ttl */
#endif /* !IP_MULTICAST_TTL */
#ifndef IP_MULTICAST_LOOP
#define IP_MULTICAST_LOOP         34 /* i_char; set/get IP multicast loopback */
#endif /* !IP_MULTICAST_LOOP */
#ifndef IP_ADD_MEMBERSHIP
#define IP_ADD_MEMBERSHIP         35 /* ip_mreq; add an IP group membership */
#endif /* !IP_ADD_MEMBERSHIP */
#ifndef IP_DROP_MEMBERSHIP
#define IP_DROP_MEMBERSHIP        36 /* ip_mreq; drop an IP group membership */
#endif /* !IP_DROP_MEMBERSHIP */
#ifndef IP_UNBLOCK_SOURCE
#define IP_UNBLOCK_SOURCE         37 /* ip_mreq_source: unblock data from source */
#endif /* !IP_UNBLOCK_SOURCE */
#ifndef IP_BLOCK_SOURCE
#define IP_BLOCK_SOURCE           38 /* ip_mreq_source: block data from source */
#endif /* !IP_BLOCK_SOURCE */
#ifndef IP_ADD_SOURCE_MEMBERSHIP
#define IP_ADD_SOURCE_MEMBERSHIP  39 /* ip_mreq_source: join source group */
#endif /* !IP_ADD_SOURCE_MEMBERSHIP */
#ifndef IP_DROP_SOURCE_MEMBERSHIP
#define IP_DROP_SOURCE_MEMBERSHIP 40 /* ip_mreq_source: leave source group */
#endif /* !IP_DROP_SOURCE_MEMBERSHIP */
#ifndef IP_MSFILTER
#define IP_MSFILTER               41
#endif /* !IP_MSFILTER */

#ifdef __USE_MISC
#ifndef MCAST_JOIN_GROUP
#define MCAST_JOIN_GROUP      42 /* group_req: join any-source group */
#endif /* !MCAST_JOIN_GROUP */
#ifndef MCAST_BLOCK_SOURCE
#define MCAST_BLOCK_SOURCE    43 /* group_source_req: block from given group */
#endif /* !MCAST_BLOCK_SOURCE */
#ifndef MCAST_UNBLOCK_SOURCE
#define MCAST_UNBLOCK_SOURCE  44 /* group_source_req: unblock from given group*/
#endif /* !MCAST_UNBLOCK_SOURCE */
#ifndef MCAST_LEAVE_GROUP
#define MCAST_LEAVE_GROUP     45 /* group_req: leave any-source group */
#endif /* !MCAST_LEAVE_GROUP */
#ifndef MCAST_JOIN_SOURCE_GROUP
#define MCAST_JOIN_SOURCE_GROUP 46 /* group_source_req: join source-spec gr */
#endif /* !MCAST_JOIN_SOURCE_GROUP */
#ifndef MCAST_LEAVE_SOURCE_GROUP
#define MCAST_LEAVE_SOURCE_GROUP 47 /* group_source_req: leave source-spec gr*/
#endif /* !MCAST_LEAVE_SOURCE_GROUP */
#ifndef MCAST_MSFILTER
#define MCAST_MSFILTER        48
#endif /* !MCAST_MSFILTER */
#ifndef IP_MULTICAST_ALL
#define IP_MULTICAST_ALL      49
#endif /* !IP_MULTICAST_ALL */
#ifndef IP_UNICAST_IF
#define IP_UNICAST_IF         50
#endif /* !IP_UNICAST_IF */
#ifndef MCAST_EXCLUDE
#define MCAST_EXCLUDE         0
#endif /* !MCAST_EXCLUDE */
#ifndef MCAST_INCLUDE
#define MCAST_INCLUDE         1
#endif /* !MCAST_INCLUDE */
#endif /* __USE_MISC */

#ifndef IP_ROUTER_ALERT
#define IP_ROUTER_ALERT    5  /* bool */
#endif /* !IP_ROUTER_ALERT */
#ifndef IP_PKTINFO
#define IP_PKTINFO         8  /* bool */
#endif /* !IP_PKTINFO */
#ifndef IP_PKTOPTIONS
#define IP_PKTOPTIONS      9
#endif /* !IP_PKTOPTIONS */
#ifndef IP_PMTUDISC
#define IP_PMTUDISC        10 /* obsolete name? */
#endif /* !IP_PMTUDISC */
#ifndef IP_MTU_DISCOVER
#define IP_MTU_DISCOVER    10 /* int; see below */
#endif /* !IP_MTU_DISCOVER */
#ifndef IP_RECVERR
#define IP_RECVERR         11 /* bool */
#endif /* !IP_RECVERR */
#ifndef IP_RECVTTL
#define IP_RECVTTL         12 /* bool */
#endif /* !IP_RECVTTL */
#ifndef IP_RECVTOS
#define IP_RECVTOS         13 /* bool */
#endif /* !IP_RECVTOS */
#ifndef IP_MTU
#define IP_MTU             14 /* int */
#endif /* !IP_MTU */
#ifndef IP_FREEBIND
#define IP_FREEBIND        15
#endif /* !IP_FREEBIND */
#ifndef IP_IPSEC_POLICY
#define IP_IPSEC_POLICY    16
#endif /* !IP_IPSEC_POLICY */
#ifndef IP_XFRM_POLICY
#define IP_XFRM_POLICY     17
#endif /* !IP_XFRM_POLICY */
#ifndef IP_PASSSEC
#define IP_PASSSEC         18
#endif /* !IP_PASSSEC */
#ifndef IP_TRANSPARENT
#define IP_TRANSPARENT     19
#endif /* !IP_TRANSPARENT */
#ifndef IP_MULTICAST_ALL
#define IP_MULTICAST_ALL   49 /* bool */
#endif /* !IP_MULTICAST_ALL */

/* TProxy original addresses */
#ifndef IP_ORIGDSTADDR
#define IP_ORIGDSTADDR     20
#endif /* !IP_ORIGDSTADDR */
#ifndef IP_RECVORIGDSTADDR
#define IP_RECVORIGDSTADDR IP_ORIGDSTADDR
#endif /* !IP_RECVORIGDSTADDR */

#ifndef IP_MINTTL
#define IP_MINTTL          21
#endif /* !IP_MINTTL */
#ifndef IP_NODEFRAG
#define IP_NODEFRAG        22
#endif /* !IP_NODEFRAG */
#ifndef IP_CHECKSUM
#define IP_CHECKSUM        23
#endif /* !IP_CHECKSUM */
#ifndef IP_BIND_ADDRESS_NO_PORT
#define IP_BIND_ADDRESS_NO_PORT 24
#endif /* !IP_BIND_ADDRESS_NO_PORT */

/* IP_MTU_DISCOVER arguments. */
#ifndef IP_PMTUDISC_DONT
#define IP_PMTUDISC_DONT   0 /* Never send DF frames. */
#endif /* !IP_PMTUDISC_DONT */
#ifndef IP_PMTUDISC_WANT
#define IP_PMTUDISC_WANT   1 /* Use per route hints. */
#endif /* !IP_PMTUDISC_WANT */
#ifndef IP_PMTUDISC_DO
#define IP_PMTUDISC_DO     2 /* Always DF. */
#endif /* !IP_PMTUDISC_DO */
#ifndef IP_PMTUDISC_PROBE
#define IP_PMTUDISC_PROBE  3 /* Ignore dst pmtu. */
#endif /* !IP_PMTUDISC_PROBE */
/* Always use interface mtu (ignores dst pmtu) but don't set DF flag.
   Also incoming ICMP frag_needed notifications will be ignored on
   this socket to prevent accepting spoofed ones. */
#ifndef IP_PMTUDISC_INTERFACE
#define IP_PMTUDISC_INTERFACE 4
#endif /* !IP_PMTUDISC_INTERFACE */
/* Like IP_PMTUDISC_INTERFACE but allow packets to be fragmented. */
#ifndef IP_PMTUDISC_OMIT
#define IP_PMTUDISC_OMIT    5
#endif /* !IP_PMTUDISC_OMIT */

#ifndef IP_MULTICAST_IF
#define IP_MULTICAST_IF           32
#endif /* !IP_MULTICAST_IF */
#ifndef IP_MULTICAST_TTL
#define IP_MULTICAST_TTL          33
#endif /* !IP_MULTICAST_TTL */
#ifndef IP_MULTICAST_LOOP
#define IP_MULTICAST_LOOP         34
#endif /* !IP_MULTICAST_LOOP */
#ifndef IP_ADD_MEMBERSHIP
#define IP_ADD_MEMBERSHIP         35
#endif /* !IP_ADD_MEMBERSHIP */
#ifndef IP_DROP_MEMBERSHIP
#define IP_DROP_MEMBERSHIP        36
#endif /* !IP_DROP_MEMBERSHIP */
#ifndef IP_UNBLOCK_SOURCE
#define IP_UNBLOCK_SOURCE         37
#endif /* !IP_UNBLOCK_SOURCE */
#ifndef IP_BLOCK_SOURCE
#define IP_BLOCK_SOURCE           38
#endif /* !IP_BLOCK_SOURCE */
#ifndef IP_ADD_SOURCE_MEMBERSHIP
#define IP_ADD_SOURCE_MEMBERSHIP  39
#endif /* !IP_ADD_SOURCE_MEMBERSHIP */
#ifndef IP_DROP_SOURCE_MEMBERSHIP
#define IP_DROP_SOURCE_MEMBERSHIP 40
#endif /* !IP_DROP_SOURCE_MEMBERSHIP */
#ifndef IP_MSFILTER
#define IP_MSFILTER               41
#endif /* !IP_MSFILTER */
#ifndef IP_MULTICAST_ALL
#define IP_MULTICAST_ALL          49
#endif /* !IP_MULTICAST_ALL */
#ifndef IP_UNICAST_IF
#define IP_UNICAST_IF             50
#endif /* !IP_UNICAST_IF */

/* To select the IP level. */
#ifndef SOL_IP
#define SOL_IP                    0
#endif /* !SOL_IP */
#ifndef IP_DEFAULT_MULTICAST_TTL
#define IP_DEFAULT_MULTICAST_TTL  1
#endif /* !IP_DEFAULT_MULTICAST_TTL */
#ifndef IP_DEFAULT_MULTICAST_LOOP
#define IP_DEFAULT_MULTICAST_LOOP 1
#endif /* !IP_DEFAULT_MULTICAST_LOOP */
#ifndef IP_MAX_MEMBERSHIPS
#define IP_MAX_MEMBERSHIPS        20
#endif /* !IP_MAX_MEMBERSHIPS */

#ifdef __CC__
#ifdef __USE_MISC
/* Structure used to describe IP options for IP_OPTIONS and IP_RETOPTS.
 * The `ip_dst' field is used for the first-hop gateway when using a
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
 * The first word in the comment at the right is the data type used;
 * "bool" means a boolean value stored in an `int'. */
#ifndef IPV6_ADDRFORM
#define IPV6_ADDRFORM       1
#endif /* !IPV6_ADDRFORM */
#ifndef IPV6_2292PKTINFO
#define IPV6_2292PKTINFO    2
#endif /* !IPV6_2292PKTINFO */
#ifndef IPV6_2292HOPOPTS
#define IPV6_2292HOPOPTS    3
#endif /* !IPV6_2292HOPOPTS */
#ifndef IPV6_2292DSTOPTS
#define IPV6_2292DSTOPTS    4
#endif /* !IPV6_2292DSTOPTS */
#ifndef IPV6_2292RTHDR
#define IPV6_2292RTHDR      5
#endif /* !IPV6_2292RTHDR */
#ifndef IPV6_2292PKTOPTIONS
#define IPV6_2292PKTOPTIONS 6
#endif /* !IPV6_2292PKTOPTIONS */
#ifndef IPV6_CHECKSUM
#define IPV6_CHECKSUM       7
#endif /* !IPV6_CHECKSUM */
#ifndef IPV6_2292HOPLIMIT
#define IPV6_2292HOPLIMIT   8
#endif /* !IPV6_2292HOPLIMIT */
#ifndef SCM_SRCRT
#define SCM_SRCRT           IPV6_RXSRCRT
#endif /* !SCM_SRCRT */
#ifndef IPV6_NEXTHOP
#define IPV6_NEXTHOP        9
#endif /* !IPV6_NEXTHOP */
#ifndef IPV6_AUTHHDR
#define IPV6_AUTHHDR        10
#endif /* !IPV6_AUTHHDR */
#ifndef IPV6_UNICAST_HOPS
#define IPV6_UNICAST_HOPS   16
#endif /* !IPV6_UNICAST_HOPS */
#ifndef IPV6_MULTICAST_IF
#define IPV6_MULTICAST_IF   17
#endif /* !IPV6_MULTICAST_IF */
#ifndef IPV6_MULTICAST_HOPS
#define IPV6_MULTICAST_HOPS 18
#endif /* !IPV6_MULTICAST_HOPS */
#ifndef IPV6_MULTICAST_LOOP
#define IPV6_MULTICAST_LOOP 19
#endif /* !IPV6_MULTICAST_LOOP */
#ifndef IPV6_JOIN_GROUP
#define IPV6_JOIN_GROUP     20
#endif /* !IPV6_JOIN_GROUP */
#ifndef IPV6_LEAVE_GROUP
#define IPV6_LEAVE_GROUP    21
#endif /* !IPV6_LEAVE_GROUP */
#ifndef IPV6_ROUTER_ALERT
#define IPV6_ROUTER_ALERT   22
#endif /* !IPV6_ROUTER_ALERT */
#ifndef IPV6_MTU_DISCOVER
#define IPV6_MTU_DISCOVER   23
#endif /* !IPV6_MTU_DISCOVER */
#ifndef IPV6_MTU
#define IPV6_MTU            24
#endif /* !IPV6_MTU */
#ifndef IPV6_RECVERR
#define IPV6_RECVERR        25
#endif /* !IPV6_RECVERR */
#ifndef IPV6_V6ONLY
#define IPV6_V6ONLY         26
#endif /* !IPV6_V6ONLY */
#ifndef IPV6_JOIN_ANYCAST
#define IPV6_JOIN_ANYCAST   27
#endif /* !IPV6_JOIN_ANYCAST */
#ifndef IPV6_LEAVE_ANYCAST
#define IPV6_LEAVE_ANYCAST  28
#endif /* !IPV6_LEAVE_ANYCAST */
#ifndef IPV6_IPSEC_POLICY
#define IPV6_IPSEC_POLICY   34
#endif /* !IPV6_IPSEC_POLICY */
#ifndef IPV6_XFRM_POLICY
#define IPV6_XFRM_POLICY    35
#endif /* !IPV6_XFRM_POLICY */

/* Advanced API (RFC3542) (1). */
#ifndef IPV6_RECVPKTINFO
#define IPV6_RECVPKTINFO    49
#endif /* !IPV6_RECVPKTINFO */
#ifndef IPV6_PKTINFO
#define IPV6_PKTINFO        50
#endif /* !IPV6_PKTINFO */
#ifndef IPV6_RECVHOPLIMIT
#define IPV6_RECVHOPLIMIT   51
#endif /* !IPV6_RECVHOPLIMIT */
#ifndef IPV6_HOPLIMIT
#define IPV6_HOPLIMIT       52
#endif /* !IPV6_HOPLIMIT */
#ifndef IPV6_RECVHOPOPTS
#define IPV6_RECVHOPOPTS    53
#endif /* !IPV6_RECVHOPOPTS */
#ifndef IPV6_HOPOPTS
#define IPV6_HOPOPTS        54
#endif /* !IPV6_HOPOPTS */
#ifndef IPV6_RTHDRDSTOPTS
#define IPV6_RTHDRDSTOPTS   55
#endif /* !IPV6_RTHDRDSTOPTS */
#ifndef IPV6_RECVRTHDR
#define IPV6_RECVRTHDR      56
#endif /* !IPV6_RECVRTHDR */
#ifndef IPV6_RTHDR
#define IPV6_RTHDR          57
#endif /* !IPV6_RTHDR */
#ifndef IPV6_RECVDSTOPTS
#define IPV6_RECVDSTOPTS    58
#endif /* !IPV6_RECVDSTOPTS */
#ifndef IPV6_DSTOPTS
#define IPV6_DSTOPTS        59
#endif /* !IPV6_DSTOPTS */
#ifndef IPV6_RECVPATHMTU
#define IPV6_RECVPATHMTU    60
#endif /* !IPV6_RECVPATHMTU */
#ifndef IPV6_PATHMTU
#define IPV6_PATHMTU        61
#endif /* !IPV6_PATHMTU */
#ifndef IPV6_DONTFRAG
#define IPV6_DONTFRAG       62
#endif /* !IPV6_DONTFRAG */

/* Advanced API (RFC3542) (2). */
#ifndef IPV6_RECVTCLASS
#define IPV6_RECVTCLASS     66
#endif /* !IPV6_RECVTCLASS */
#ifndef IPV6_TCLASS
#define IPV6_TCLASS         67
#endif /* !IPV6_TCLASS */

/* Obsolete synonyms for the above. */
#ifndef IPV6_ADD_MEMBERSHIP
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#endif /* !IPV6_ADD_MEMBERSHIP */
#ifndef IPV6_DROP_MEMBERSHIP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
#endif /* !IPV6_DROP_MEMBERSHIP */
#ifndef IPV6_RXHOPOPTS
#define IPV6_RXHOPOPTS      IPV6_HOPOPTS
#endif /* !IPV6_RXHOPOPTS */
#ifndef IPV6_RXDSTOPTS
#define IPV6_RXDSTOPTS      IPV6_DSTOPTS
#endif /* !IPV6_RXDSTOPTS */

/* IPV6_MTU_DISCOVER values. */
#ifndef IPV6_PMTUDISC_DONT
#define IPV6_PMTUDISC_DONT  0 /* Never send DF frames. */
#endif /* !IPV6_PMTUDISC_DONT */
#ifndef IPV6_PMTUDISC_WANT
#define IPV6_PMTUDISC_WANT  1 /* Use per route hints. */
#endif /* !IPV6_PMTUDISC_WANT */
#ifndef IPV6_PMTUDISC_DO
#define IPV6_PMTUDISC_DO    2 /* Always DF. */
#endif /* !IPV6_PMTUDISC_DO */
#ifndef IPV6_PMTUDISC_PROBE
#define IPV6_PMTUDISC_PROBE 3 /* Ignore dst pmtu. */
#endif /* !IPV6_PMTUDISC_PROBE */
#ifndef IPV6_PMTUDISC_INTERFACE
#define IPV6_PMTUDISC_INTERFACE 4 /* See IP_PMTUDISC_INTERFACE. */
#endif /* !IPV6_PMTUDISC_INTERFACE */
#ifndef IPV6_PMTUDISC_OMIT
#define IPV6_PMTUDISC_OMIT  5 /* See IP_PMTUDISC_OMIT. */
#endif /* !IPV6_PMTUDISC_OMIT */

/* Socket level values for IPv6. */
#ifndef SOL_IPV6
#define SOL_IPV6            41
#endif /* !SOL_IPV6 */
#ifndef SOL_ICMPV6
#define SOL_ICMPV6          58
#endif /* !SOL_ICMPV6 */

/* Routing header options for IPv6. */
#ifndef IPV6_RTHDR_LOOSE
#define IPV6_RTHDR_LOOSE    0 /* Hop doesn't need to be neighbor. */
#endif /* !IPV6_RTHDR_LOOSE */
#ifndef IPV6_RTHDR_STRICT
#define IPV6_RTHDR_STRICT   1 /* Hop must be a neighbor. */
#endif /* !IPV6_RTHDR_STRICT */
#ifndef IPV6_RTHDR_TYPE_0
#define IPV6_RTHDR_TYPE_0   0 /* IPv6 Routing header type 0. */
#endif /* !IPV6_RTHDR_TYPE_0 */

__SYSDECL_END

#endif /* !_BITS_IN_H */
