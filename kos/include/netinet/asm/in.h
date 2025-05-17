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
/*!replace_with_include <netinet/in.h>*/
#ifndef _NETINET_ASM_IN_H
#define _NETINET_ASM_IN_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>

/* Integer net address classification macros */
#define __IN_CLASSA(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0x80000000)) == 0)
#define __IN_CLASSA_NET              __UINT32_C(0xff000000)
#define __IN_CLASSA_NSHIFT           24
#define __IN_CLASSA_HOST             __UINT32_C(0x00ffffff) /* 0xffffffff & ~IN_CLASSA_NET */
#define __IN_CLASSA_MAX              __UINT8_C(128)
#define __IN_CLASSB(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xc0000000)) == __UINT32_C(0x80000000))
#define __IN_CLASSB_NET              __UINT32_C(0xffff0000)
#define __IN_CLASSB_NSHIFT           16
#define __IN_CLASSB_HOST             __UINT32_C(0x0000ffff) /* 0xffffffff & ~IN_CLASSB_NET */
#define __IN_CLASSB_MAX              __UINT16_C(65536)
#define __IN_CLASSC(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xe0000000)) == __UINT32_C(0xc0000000))
#define __IN_CLASSC_NET              __UINT32_C(0xffffff00)
#define __IN_CLASSC_NSHIFT           8
#define __IN_CLASSC_HOST             __UINT32_C(0x000000ff) /* 0xffffffff & ~IN_CLASSC_NET */
#define __IN_CLASSC_MAX              __UINT32_C(16777216)
#define __IN_CLASSD(/*u32*/ a)       (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xf0000000)) == __UINT32_C(0xe0000000))
#define __IN_MULTICAST(/*u32*/ a)    __IN_CLASSD(a)
#define __IN_EXPERIMENTAL(/*u32*/ a) (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xe0000000)) == __UINT32_C(0xe0000000))
#define __IN_BADCLASS(/*u32*/ a)     (((__CCAST(__uint32_t)(a)) & __UINT32_C(0xf0000000)) == __UINT32_C(0xf0000000))

#define __INADDR_ANY       __UINT32_C(0x00000000) /* Address: accept any incoming messages. */
#define __INADDR_BROADCAST __UINT32_C(0xffffffff) /* Address: send to all hosts. */
#define __INADDR_NONE      __UINT32_C(0xffffffff) /* Address: error/none. */

#define __IN_LOOPBACKNET  127                    /* == INADDR_LOOPBACK & IN_CLASSA_NET */
#define __INADDR_LOOPBACK __UINT32_C(0x7f000001) /* Your typical `127.0.0.1' */

/* Special, multicast internet addresses. */
#define __INADDR_UNSPEC_GROUP    0xe0000000 /* 224.0.0.0 */
#define __INADDR_ALLHOSTS_GROUP  0xe0000001 /* 224.0.0.1 */
#define __INADDR_ALLRTRS_GROUP   0xe0000002 /* 224.0.0.2 */
#define __INADDR_MAX_LOCAL_GROUP 0xe00000ff /* 224.0.0.255 */


/* Comments taken from GLibc. See the following copyright notice: */
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
#define __IP_OPTIONS                4  /* ip_opts; IP per-packet options. */
#define __IP_HDRINCL                3  /* int; Header is included with data. */
#define __IP_TOS                    1  /* int; IP type of service and precedence. */
#define __IP_TTL                    2  /* int; IP time to live. */
#define __IP_RECVOPTS               6  /* bool; Receive all IP options w/datagram. */
#define __IP_RETOPTS                7  /* ip_opts; Set/get IP per-packet options. */
#define __IP_MULTICAST_IF           32 /* in_addr; set/get IP multicast i/f */
#define __IP_MULTICAST_TTL          33 /* u_char; set/get IP multicast ttl */
#define __IP_MULTICAST_LOOP         34 /* i_char; set/get IP multicast loopback */
#define __IP_ADD_MEMBERSHIP         35 /* ip_mreq; add an IP group membership */
#define __IP_DROP_MEMBERSHIP        36 /* ip_mreq; drop an IP group membership */
#define __IP_UNBLOCK_SOURCE         37 /* ip_mreq_source: unblock data from source */
#define __IP_BLOCK_SOURCE           38 /* ip_mreq_source: block data from source */
#define __IP_ADD_SOURCE_MEMBERSHIP  39 /* ip_mreq_source: join source group */
#define __IP_DROP_SOURCE_MEMBERSHIP 40 /* ip_mreq_source: leave source group */
#define __IP_MSFILTER               41

#define __MCAST_JOIN_GROUP         42 /* group_req: join any-source group */
#define __MCAST_BLOCK_SOURCE       43 /* group_source_req: block from given group */
#define __MCAST_UNBLOCK_SOURCE     44 /* group_source_req: unblock from given group*/
#define __MCAST_LEAVE_GROUP        45 /* group_req: leave any-source group */
#define __MCAST_JOIN_SOURCE_GROUP  46 /* group_source_req: join source-spec gr */
#define __MCAST_LEAVE_SOURCE_GROUP 47 /* group_source_req: leave source-spec gr*/
#define __MCAST_MSFILTER           48
#define __IP_UNICAST_IF            50
#define __MCAST_EXCLUDE            0
#define __MCAST_INCLUDE            1

#define __IP_ROUTER_ALERT    5  /* bool */
#define __IP_PKTINFO         8  /* bool */
#define __IP_PKTOPTIONS      9
#define __IP_MTU_DISCOVER    10 /* int; see below */
#define __IP_RECVERR         11 /* bool */
#define __IP_RECVTTL         12 /* bool */
#define __IP_RECVTOS         13 /* bool */
#define __IP_MTU             14 /* int */
#define __IP_FREEBIND        15
#define __IP_IPSEC_POLICY    16
#define __IP_XFRM_POLICY     17
#define __IP_PASSSEC         18
#define __IP_TRANSPARENT     19
#define __IP_MULTICAST_ALL   49 /* bool */

/* TProxy original addresses */
#define __IP_ORIGDSTADDR          20
#define __IP_MINTTL               21
#define __IP_NODEFRAG             22
#define __IP_CHECKSUM             23
#define __IP_BIND_ADDRESS_NO_PORT 24

/* IP_MTU_DISCOVER arguments. */
#define __IP_PMTUDISC_DONT      0 /* Never send DF frames. */
#define __IP_PMTUDISC_WANT      1 /* Use per route hints. */
#define __IP_PMTUDISC_DO        2 /* Always DF. */
#define __IP_PMTUDISC_PROBE     3 /* Ignore dst pmtu. */
#define __IP_PMTUDISC_INTERFACE 4 /* Always use interface mtu (ignores dst pmtu) but don't set DF flag.
                                   * Also incoming ICMP  frag_needed notifications will  be ignored  on
                                   * this socket to prevent accepting spoofed ones. */
#define __IP_PMTUDISC_OMIT      5 /* Like IP_PMTUDISC_INTERFACE but allow packets to be fragmented. */

/* To select the IP level. */
#define __SOL_IP                    0
#define __IP_DEFAULT_MULTICAST_TTL  1
#define __IP_DEFAULT_MULTICAST_LOOP 1
#define __IP_MAX_MEMBERSHIPS        20

/* Options for use with `getsockopt' and `setsockopt' at the IPv6 level.
 * The first word in  the comment at  the right is  the data type  used;
 * "bool" means a boolean value stored in an `int'. */
#define __IPV6_ADDRFORM       1
#define __IPV6_2292PKTINFO    2
#define __IPV6_2292HOPOPTS    3
#define __IPV6_2292DSTOPTS    4
#define __IPV6_2292RTHDR      5
#define __IPV6_2292PKTOPTIONS 6
#define __IPV6_CHECKSUM       7
#define __IPV6_2292HOPLIMIT   8
#define __IPV6_NEXTHOP        9
#define __IPV6_AUTHHDR        10
#define __IPV6_UNICAST_HOPS   16
#define __IPV6_MULTICAST_IF   17
#define __IPV6_MULTICAST_HOPS 18
#define __IPV6_MULTICAST_LOOP 19
#define __IPV6_JOIN_GROUP     20
#define __IPV6_LEAVE_GROUP    21
#define __IPV6_ROUTER_ALERT   22
#define __IPV6_MTU_DISCOVER   23
#define __IPV6_MTU            24
#define __IPV6_RECVERR        25
#define __IPV6_V6ONLY         26
#define __IPV6_JOIN_ANYCAST   27
#define __IPV6_LEAVE_ANYCAST  28
#define __IPV6_IPSEC_POLICY   34
#define __IPV6_XFRM_POLICY    35

/* Advanced API (RFC3542) (1). */
#define __IPV6_RECVPKTINFO  49
#define __IPV6_PKTINFO      50
#define __IPV6_RECVHOPLIMIT 51
#define __IPV6_HOPLIMIT     52
#define __IPV6_RECVHOPOPTS  53
#define __IPV6_HOPOPTS      54
#define __IPV6_RTHDRDSTOPTS 55
#define __IPV6_RECVRTHDR    56
#define __IPV6_RTHDR        57
#define __IPV6_RECVDSTOPTS  58
#define __IPV6_DSTOPTS      59
#define __IPV6_RECVPATHMTU  60
#define __IPV6_PATHMTU      61
#define __IPV6_DONTFRAG     62

/* Advanced API (RFC3542) (2). */
#define __IPV6_RECVTCLASS 66
#define __IPV6_TCLASS     67

/* IPV6_MTU_DISCOVER values. */
#define __IPV6_PMTUDISC_DONT      0 /* Never send DF frames. */
#define __IPV6_PMTUDISC_WANT      1 /* Use per route hints. */
#define __IPV6_PMTUDISC_DO        2 /* Always DF. */
#define __IPV6_PMTUDISC_PROBE     3 /* Ignore dst pmtu. */
#define __IPV6_PMTUDISC_INTERFACE 4 /* See IP_PMTUDISC_INTERFACE. */
#define __IPV6_PMTUDISC_OMIT      5 /* See IP_PMTUDISC_OMIT. */

/* Socket level values for IPv6. */
#define __SOL_IPV6   41
#define __SOL_ICMPV6 58

/* Routing header options for IPv6. */
#define __IPV6_RTHDR_LOOSE  0 /* Hop doesn't need to be neighbor. */
#define __IPV6_RTHDR_STRICT 1 /* Hop must be a neighbor. */
#define __IPV6_RTHDR_TYPE_0 0 /* IPv6 Routing header type 0. */
/* =================== END OF DERIVED COMMENTS */


#define __INET_ADDRSTRLEN  16 /* Max # of characters written by `inet_ntoa_r' (e.g. `111.111.111.111\0') */
#define __INET6_ADDRSTRLEN 46 /* Length of the string form for IPv6. */


#endif /* !_NETINET_ASM_IN_H */
