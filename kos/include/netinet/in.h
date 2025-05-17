/* HASH CRC-32:0x566d23c */
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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/in.h) */
/* (#) Portability: DJGPP         (/include/netinet/in.h) */
/* (#) Portability: DragonFly BSD (/sys/netinet/in.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/in.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/in.h) */
/* (#) Portability: GNU C Library (/inet/netinet/in.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netinet/in.h) */
/* (#) Portability: NetBSD        (/sys/netinet/in.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/in.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/in.h) */
/* (#) Portability: diet libc     (/include/netinet/in.h) */
/* (#) Portability: libc4/5       (/include/netinet/in.h) */
/* (#) Portability: libc6         (/include/netinet/in.h) */
/* (#) Portability: mintlib       (/include/netinet/in.h) */
/* (#) Portability: musl libc     (/include/netinet/in.h) */
/* (#) Portability: uClibc        (/include/netinet/in.h) */
#ifndef _NETINET_IN_H
#define _NETINET_IN_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/byteorder.h>
#include <hybrid/__byteswap.h>
#include <hybrid/typecore.h>

#include <bits/os/sockaddr-common.h>
#include <bits/os/sockaddr.h>
#include <bits/os/sockaddr_storage.h>
#include <bits/types.h>
#include <net/bits/types.h>
#include <netinet/asm/in.h> /* Macro constants... */
#include <netinet/bits/in_addr.h> /* struct in_addr */
#include <netinet/bits/sockaddr_in.h> /* struct sockaddr_in */
#include <netinet/bits/sockaddr_in6.h> /* struct sockaddr_in6 */
#include <netinet/bits/ipv6_mreq.h> /* struct ipv6_mreq */

#include <netinet/ipport.h>  /* IPPORT_* */
#include <netinet/ipproto.h> /* IPPROTO_* */

#ifdef __USE_MISC
#include <netinet/bits/group_req.h>   /* struct group_req, struct group_source_req */
#include <netinet/bits/in_pktinfo.h>  /* struct in_pktinfo */
#include <netinet/bits/ip_mreq.h>     /* struct ip_mreq, struct ip_mreq_source */
#include <netinet/bits/ip_mreqn.h>    /* struct ip_mreqn */
#include <netinet/bits/ip_msfilter.h> /* struct ip_msfilter, struct group_filter */
#include <netinet/bits/ip_opts.h>     /* struct ip_opts */
#endif /* __USE_MISC */

#ifdef __USE_GNU
#include <netinet/bits/in6_pktinfo.h>
#include <netinet/bits/ip6_mtuinfo.h>
#endif /* __USE_GNU */

#ifdef __INTELLISENSE__
#include <bits/types/uintN_t.h> /* Only uint32_t+uint8_t! */
#endif /* __INTELLISENSE__ */

#ifdef __USE_GLIBC_BLOAT
#include <endian.h>
#include <stdint.h>
#endif /* __USE_GLIBC_BLOAT */

/* susv4-2018: Inclusion  of  the  <netinet/in.h> header  may  also make
 *             visible all symbols from <inttypes.h> and <sys/socket.h>. */
#ifdef __USE_POSIX_BLOAT
#include <sys/socket.h>
#include <inttypes.h>
#endif /* __USE_POSIX_BLOAT */


/* Integer net address classification macros */
#if !defined(IN_CLASSA) && defined(__IN_CLASSA)
#define IN_CLASSA        __IN_CLASSA
#endif /* !IN_CLASSA && __IN_CLASSA */
#if !defined(IN_CLASSA_NET) && defined(__IN_CLASSA_NET)
#define IN_CLASSA_NET    __IN_CLASSA_NET
#endif /* !IN_CLASSA_NET && __IN_CLASSA_NET */
#if !defined(IN_CLASSA_NSHIFT) && defined(__IN_CLASSA_NSHIFT)
#define IN_CLASSA_NSHIFT __IN_CLASSA_NSHIFT
#endif /* !IN_CLASSA_NSHIFT && __IN_CLASSA_NSHIFT */
#if !defined(IN_CLASSA_HOST) && defined(__IN_CLASSA_HOST)
#define IN_CLASSA_HOST   __IN_CLASSA_HOST
#endif /* !IN_CLASSA_HOST && __IN_CLASSA_HOST */
#if !defined(IN_CLASSA_MAX) && defined(__IN_CLASSA_MAX)
#define IN_CLASSA_MAX    __IN_CLASSA_MAX
#endif /* !IN_CLASSA_MAX && __IN_CLASSA_MAX */
#if !defined(IN_CLASSB) && defined(__IN_CLASSB)
#define IN_CLASSB        __IN_CLASSB
#endif /* !IN_CLASSB && __IN_CLASSB */
#if !defined(IN_CLASSB_NET) && defined(__IN_CLASSB_NET)
#define IN_CLASSB_NET    __IN_CLASSB_NET
#endif /* !IN_CLASSB_NET && __IN_CLASSB_NET */
#if !defined(IN_CLASSB_NSHIFT) && defined(__IN_CLASSB_NSHIFT)
#define IN_CLASSB_NSHIFT __IN_CLASSB_NSHIFT
#endif /* !IN_CLASSB_NSHIFT && __IN_CLASSB_NSHIFT */
#if !defined(IN_CLASSB_HOST) && defined(__IN_CLASSB_HOST)
#define IN_CLASSB_HOST   __IN_CLASSB_HOST
#endif /* !IN_CLASSB_HOST && __IN_CLASSB_HOST */
#if !defined(IN_CLASSB_MAX) && defined(__IN_CLASSB_MAX)
#define IN_CLASSB_MAX    __IN_CLASSB_MAX
#endif /* !IN_CLASSB_MAX && __IN_CLASSB_MAX */
#if !defined(IN_CLASSC) && defined(__IN_CLASSC)
#define IN_CLASSC        __IN_CLASSC
#endif /* !IN_CLASSC && __IN_CLASSC */
#if !defined(IN_CLASSC_NET) && defined(__IN_CLASSC_NET)
#define IN_CLASSC_NET    __IN_CLASSC_NET
#endif /* !IN_CLASSC_NET && __IN_CLASSC_NET */
#if !defined(IN_CLASSC_NSHIFT) && defined(__IN_CLASSC_NSHIFT)
#define IN_CLASSC_NSHIFT __IN_CLASSC_NSHIFT
#endif /* !IN_CLASSC_NSHIFT && __IN_CLASSC_NSHIFT */
#if !defined(IN_CLASSC_HOST) && defined(__IN_CLASSC_HOST)
#define IN_CLASSC_HOST   __IN_CLASSC_HOST
#endif /* !IN_CLASSC_HOST && __IN_CLASSC_HOST */
#if !defined(IN_CLASSC_MAX) && defined(__IN_CLASSC_MAX)
#define IN_CLASSC_MAX    __IN_CLASSC_MAX
#endif /* !IN_CLASSC_MAX && __IN_CLASSC_MAX */
#if !defined(IN_CLASSD) && defined(__IN_CLASSD)
#define IN_CLASSD        __IN_CLASSD
#endif /* !IN_CLASSD && __IN_CLASSD */
#if !defined(IN_MULTICAST) && defined(__IN_MULTICAST)
#define IN_MULTICAST     __IN_MULTICAST
#endif /* !IN_MULTICAST && __IN_MULTICAST */
#if !defined(IN_EXPERIMENTAL) && defined(__IN_EXPERIMENTAL)
#define IN_EXPERIMENTAL  __IN_EXPERIMENTAL
#endif /* !IN_EXPERIMENTAL && __IN_EXPERIMENTAL */
#if !defined(IN_BADCLASS) && defined(__IN_BADCLASS)
#define IN_BADCLASS      __IN_BADCLASS
#endif /* !IN_BADCLASS && __IN_BADCLASS */

#if !defined(INADDR_ANY) && defined(__INADDR_ANY)
#define INADDR_ANY       __INADDR_ANY       /* Address: accept any incoming messages. */
#endif /* !INADDR_ANY && __INADDR_ANY */
#if !defined(INADDR_BROADCAST) && defined(__INADDR_BROADCAST)
#define INADDR_BROADCAST __INADDR_BROADCAST /* Address: send to all hosts. */
#endif /* !INADDR_BROADCAST && __INADDR_BROADCAST */
#if !defined(INADDR_NONE) && defined(__INADDR_NONE)
#define INADDR_NONE      __INADDR_NONE      /* Address: error/none. */
#endif /* !INADDR_NONE && __INADDR_NONE */

#if !defined(IN_LOOPBACKNET) && defined(__IN_LOOPBACKNET)
#define IN_LOOPBACKNET  __IN_LOOPBACKNET  /* == INADDR_LOOPBACK & IN_CLASSA_NET */
#endif /* !IN_LOOPBACKNET && __IN_LOOPBACKNET */
#if !defined(INADDR_LOOPBACK) && defined(__INADDR_LOOPBACK)
#define INADDR_LOOPBACK __INADDR_LOOPBACK /* Your typical `127.0.0.1' */
#endif /* !INADDR_LOOPBACK && __INADDR_LOOPBACK */

/* Special, multicast internet addresses. */
#if !defined(INADDR_UNSPEC_GROUP) && defined(__INADDR_UNSPEC_GROUP)
#define INADDR_UNSPEC_GROUP    __INADDR_UNSPEC_GROUP    /* 224.0.0.0 */
#endif /* !INADDR_UNSPEC_GROUP && __INADDR_UNSPEC_GROUP */
#if !defined(INADDR_ALLHOSTS_GROUP) && defined(__INADDR_ALLHOSTS_GROUP)
#define INADDR_ALLHOSTS_GROUP  __INADDR_ALLHOSTS_GROUP  /* 224.0.0.1 */
#endif /* !INADDR_ALLHOSTS_GROUP && __INADDR_ALLHOSTS_GROUP */
#if !defined(INADDR_ALLRTRS_GROUP) && defined(__INADDR_ALLRTRS_GROUP)
#define INADDR_ALLRTRS_GROUP   __INADDR_ALLRTRS_GROUP   /* 224.0.0.2 */
#endif /* !INADDR_ALLRTRS_GROUP && __INADDR_ALLRTRS_GROUP */
#if !defined(INADDR_MAX_LOCAL_GROUP) && defined(__INADDR_MAX_LOCAL_GROUP)
#define INADDR_MAX_LOCAL_GROUP __INADDR_MAX_LOCAL_GROUP /* 224.0.0.255 */
#endif /* !INADDR_MAX_LOCAL_GROUP && __INADDR_MAX_LOCAL_GROUP */


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
#if !defined(IP_OPTIONS) && defined(__IP_OPTIONS)
#define IP_OPTIONS                __IP_OPTIONS                /* ip_opts; IP per-packet options. */
#endif /* !IP_OPTIONS && __IP_OPTIONS */
#if !defined(IP_HDRINCL) && defined(__IP_HDRINCL)
#define IP_HDRINCL                __IP_HDRINCL                /* int; Header is included with data. */
#endif /* !IP_HDRINCL && __IP_HDRINCL */
#if !defined(IP_TOS) && defined(__IP_TOS)
#define IP_TOS                    __IP_TOS                    /* int; IP type of service and precedence. */
#endif /* !IP_TOS && __IP_TOS */
#if !defined(IP_TTL) && defined(__IP_TTL)
#define IP_TTL                    __IP_TTL                    /* int; IP time to live. */
#endif /* !IP_TTL && __IP_TTL */
#if !defined(IP_RECVOPTS) && defined(__IP_RECVOPTS)
#define IP_RECVOPTS               __IP_RECVOPTS               /* bool; Receive all IP options w/datagram. */
#endif /* !IP_RECVOPTS && __IP_RECVOPTS */
#if !defined(IP_RECVRETOPTS) && defined(__IP_RETOPTS)
#define IP_RECVRETOPTS            __IP_RETOPTS                /* For BSD compatibility. bool; Receive IP options for response. */
#endif /* !IP_RECVRETOPTS && __IP_RETOPTS */
#if !defined(IP_RETOPTS) && defined(__IP_RETOPTS)
#define IP_RETOPTS                __IP_RETOPTS                /* ip_opts; Set/get IP per-packet options. */
#endif /* !IP_RETOPTS && __IP_RETOPTS */
#if !defined(IP_MULTICAST_IF) && defined(__IP_MULTICAST_IF)
#define IP_MULTICAST_IF           __IP_MULTICAST_IF           /* in_addr; set/get IP multicast i/f */
#endif /* !IP_MULTICAST_IF && __IP_MULTICAST_IF */
#if !defined(IP_MULTICAST_TTL) && defined(__IP_MULTICAST_TTL)
#define IP_MULTICAST_TTL          __IP_MULTICAST_TTL          /* u_char; set/get IP multicast ttl */
#endif /* !IP_MULTICAST_TTL && __IP_MULTICAST_TTL */
#if !defined(IP_MULTICAST_LOOP) && defined(__IP_MULTICAST_LOOP)
#define IP_MULTICAST_LOOP         __IP_MULTICAST_LOOP         /* i_char; set/get IP multicast loopback */
#endif /* !IP_MULTICAST_LOOP && __IP_MULTICAST_LOOP */
#if !defined(IP_ADD_MEMBERSHIP) && defined(__IP_ADD_MEMBERSHIP)
#define IP_ADD_MEMBERSHIP         __IP_ADD_MEMBERSHIP         /* ip_mreq; add an IP group membership */
#endif /* !IP_ADD_MEMBERSHIP && __IP_ADD_MEMBERSHIP */
#if !defined(IP_DROP_MEMBERSHIP) && defined(__IP_DROP_MEMBERSHIP)
#define IP_DROP_MEMBERSHIP        __IP_DROP_MEMBERSHIP        /* ip_mreq; drop an IP group membership */
#endif /* !IP_DROP_MEMBERSHIP && __IP_DROP_MEMBERSHIP */
#if !defined(IP_UNBLOCK_SOURCE) && defined(__IP_UNBLOCK_SOURCE)
#define IP_UNBLOCK_SOURCE         __IP_UNBLOCK_SOURCE         /* ip_mreq_source: unblock data from source */
#endif /* !IP_UNBLOCK_SOURCE && __IP_UNBLOCK_SOURCE */
#if !defined(IP_BLOCK_SOURCE) && defined(__IP_BLOCK_SOURCE)
#define IP_BLOCK_SOURCE           __IP_BLOCK_SOURCE           /* ip_mreq_source: block data from source */
#endif /* !IP_BLOCK_SOURCE && __IP_BLOCK_SOURCE */
#if !defined(IP_ADD_SOURCE_MEMBERSHIP) && defined(__IP_ADD_SOURCE_MEMBERSHIP)
#define IP_ADD_SOURCE_MEMBERSHIP  __IP_ADD_SOURCE_MEMBERSHIP  /* ip_mreq_source: join source group */
#endif /* !IP_ADD_SOURCE_MEMBERSHIP && __IP_ADD_SOURCE_MEMBERSHIP */
#if !defined(IP_DROP_SOURCE_MEMBERSHIP) && defined(__IP_DROP_SOURCE_MEMBERSHIP)
#define IP_DROP_SOURCE_MEMBERSHIP __IP_DROP_SOURCE_MEMBERSHIP /* ip_mreq_source: leave source group */
#endif /* !IP_DROP_SOURCE_MEMBERSHIP && __IP_DROP_SOURCE_MEMBERSHIP */
#if !defined(IP_MSFILTER) && defined(__IP_MSFILTER)
#define IP_MSFILTER               __IP_MSFILTER
#endif /* !IP_MSFILTER && __IP_MSFILTER */

#ifdef __USE_MISC
#if !defined(MCAST_JOIN_GROUP) && defined(__MCAST_JOIN_GROUP)
#define MCAST_JOIN_GROUP         __MCAST_JOIN_GROUP /* group_req: join any-source group */
#endif /* !MCAST_JOIN_GROUP && __MCAST_JOIN_GROUP */
#if !defined(MCAST_BLOCK_SOURCE) && defined(__MCAST_BLOCK_SOURCE)
#define MCAST_BLOCK_SOURCE       __MCAST_BLOCK_SOURCE /* group_source_req: block from given group */
#endif /* !MCAST_BLOCK_SOURCE && __MCAST_BLOCK_SOURCE */
#if !defined(MCAST_UNBLOCK_SOURCE) && defined(__MCAST_UNBLOCK_SOURCE)
#define MCAST_UNBLOCK_SOURCE     __MCAST_UNBLOCK_SOURCE /* group_source_req: unblock from given group*/
#endif /* !MCAST_UNBLOCK_SOURCE && __MCAST_UNBLOCK_SOURCE */
#if !defined(MCAST_LEAVE_GROUP) && defined(__MCAST_LEAVE_GROUP)
#define MCAST_LEAVE_GROUP        __MCAST_LEAVE_GROUP /* group_req: leave any-source group */
#endif /* !MCAST_LEAVE_GROUP && __MCAST_LEAVE_GROUP */
#if !defined(MCAST_JOIN_SOURCE_GROUP) && defined(__MCAST_JOIN_SOURCE_GROUP)
#define MCAST_JOIN_SOURCE_GROUP  __MCAST_JOIN_SOURCE_GROUP /* group_source_req: join source-spec gr */
#endif /* !MCAST_JOIN_SOURCE_GROUP && __MCAST_JOIN_SOURCE_GROUP */
#if !defined(MCAST_LEAVE_SOURCE_GROUP) && defined(__MCAST_LEAVE_SOURCE_GROUP)
#define MCAST_LEAVE_SOURCE_GROUP __MCAST_LEAVE_SOURCE_GROUP /* group_source_req: leave source-spec gr*/
#endif /* !MCAST_LEAVE_SOURCE_GROUP && __MCAST_LEAVE_SOURCE_GROUP */
#if !defined(MCAST_MSFILTER) && defined(__MCAST_MSFILTER)
#define MCAST_MSFILTER           __MCAST_MSFILTER
#endif /* !MCAST_MSFILTER && __MCAST_MSFILTER */
#if !defined(IP_UNICAST_IF) && defined(__IP_UNICAST_IF)
#define IP_UNICAST_IF            __IP_UNICAST_IF
#endif /* !IP_UNICAST_IF && __IP_UNICAST_IF */
#if !defined(MCAST_EXCLUDE) && defined(__MCAST_EXCLUDE)
#define MCAST_EXCLUDE            __MCAST_EXCLUDE
#endif /* !MCAST_EXCLUDE && __MCAST_EXCLUDE */
#if !defined(MCAST_INCLUDE) && defined(__MCAST_INCLUDE)
#define MCAST_INCLUDE            __MCAST_INCLUDE
#endif /* !MCAST_INCLUDE && __MCAST_INCLUDE */
#endif /* __USE_MISC */

#if !defined(IP_ROUTER_ALERT) && defined(__IP_ROUTER_ALERT)
#define IP_ROUTER_ALERT  __IP_ROUTER_ALERT /* bool */
#endif /* !IP_ROUTER_ALERT && __IP_ROUTER_ALERT */
#if !defined(IP_PKTINFO) && defined(__IP_PKTINFO)
#define IP_PKTINFO       __IP_PKTINFO      /* bool */
#endif /* !IP_PKTINFO && __IP_PKTINFO */
#if !defined(IP_PKTOPTIONS) && defined(__IP_PKTOPTIONS)
#define IP_PKTOPTIONS    __IP_PKTOPTIONS
#endif /* !IP_PKTOPTIONS && __IP_PKTOPTIONS */
#if !defined(IP_PMTUDISC) && defined(__IP_MTU_DISCOVER)
#define IP_PMTUDISC      __IP_MTU_DISCOVER /* obsolete name? */
#endif /* !IP_PMTUDISC && __IP_MTU_DISCOVER */
#if !defined(IP_MTU_DISCOVER) && defined(__IP_MTU_DISCOVER)
#define IP_MTU_DISCOVER  __IP_MTU_DISCOVER /* int; see below */
#endif /* !IP_MTU_DISCOVER && __IP_MTU_DISCOVER */
#if !defined(IP_RECVERR) && defined(__IP_RECVERR)
#define IP_RECVERR       __IP_RECVERR      /* bool */
#endif /* !IP_RECVERR && __IP_RECVERR */
#if !defined(IP_RECVTTL) && defined(__IP_RECVTTL)
#define IP_RECVTTL       __IP_RECVTTL      /* bool */
#endif /* !IP_RECVTTL && __IP_RECVTTL */
#if !defined(IP_RECVTOS) && defined(__IP_RECVTOS)
#define IP_RECVTOS       __IP_RECVTOS      /* bool */
#endif /* !IP_RECVTOS && __IP_RECVTOS */
#if !defined(IP_MTU) && defined(__IP_MTU)
#define IP_MTU           __IP_MTU          /* int */
#endif /* !IP_MTU && __IP_MTU */
#if !defined(IP_FREEBIND) && defined(__IP_FREEBIND)
#define IP_FREEBIND      __IP_FREEBIND
#endif /* !IP_FREEBIND && __IP_FREEBIND */
#if !defined(IP_IPSEC_POLICY) && defined(__IP_IPSEC_POLICY)
#define IP_IPSEC_POLICY  __IP_IPSEC_POLICY
#endif /* !IP_IPSEC_POLICY && __IP_IPSEC_POLICY */
#if !defined(IP_XFRM_POLICY) && defined(__IP_XFRM_POLICY)
#define IP_XFRM_POLICY   __IP_XFRM_POLICY
#endif /* !IP_XFRM_POLICY && __IP_XFRM_POLICY */
#if !defined(IP_PASSSEC) && defined(__IP_PASSSEC)
#define IP_PASSSEC       __IP_PASSSEC
#endif /* !IP_PASSSEC && __IP_PASSSEC */
#if !defined(IP_TRANSPARENT) && defined(__IP_TRANSPARENT)
#define IP_TRANSPARENT   __IP_TRANSPARENT
#endif /* !IP_TRANSPARENT && __IP_TRANSPARENT */
#if !defined(IP_MULTICAST_ALL) && defined(__IP_MULTICAST_ALL)
#define IP_MULTICAST_ALL __IP_MULTICAST_ALL /* bool */
#endif /* !IP_MULTICAST_ALL && __IP_MULTICAST_ALL */

/* TProxy original addresses */
#if !defined(IP_ORIGDSTADDR) && defined(__IP_ORIGDSTADDR)
#define IP_ORIGDSTADDR          __IP_ORIGDSTADDR
#endif /* !IP_ORIGDSTADDR && __IP_ORIGDSTADDR */
#if !defined(IP_RECVORIGDSTADDR) && defined(__IP_ORIGDSTADDR)
#define IP_RECVORIGDSTADDR      __IP_ORIGDSTADDR
#endif /* !IP_RECVORIGDSTADDR && __IP_ORIGDSTADDR */
#if !defined(IP_MINTTL) && defined(__IP_MINTTL)
#define IP_MINTTL               __IP_MINTTL
#endif /* !IP_MINTTL && __IP_MINTTL */
#if !defined(IP_NODEFRAG) && defined(__IP_NODEFRAG)
#define IP_NODEFRAG             __IP_NODEFRAG
#endif /* !IP_NODEFRAG && __IP_NODEFRAG */
#if !defined(IP_CHECKSUM) && defined(__IP_CHECKSUM)
#define IP_CHECKSUM             __IP_CHECKSUM
#endif /* !IP_CHECKSUM && __IP_CHECKSUM */
#if !defined(IP_BIND_ADDRESS_NO_PORT) && defined(__IP_BIND_ADDRESS_NO_PORT)
#define IP_BIND_ADDRESS_NO_PORT __IP_BIND_ADDRESS_NO_PORT
#endif /* !IP_BIND_ADDRESS_NO_PORT && __IP_BIND_ADDRESS_NO_PORT */

/* IP_MTU_DISCOVER arguments. */
#if !defined(IP_PMTUDISC_DONT) && defined(__IP_PMTUDISC_DONT)
#define IP_PMTUDISC_DONT      __IP_PMTUDISC_DONT      /* Never send DF frames. */
#endif /* !IP_PMTUDISC_DONT && __IP_PMTUDISC_DONT */
#if !defined(IP_PMTUDISC_WANT) && defined(__IP_PMTUDISC_WANT)
#define IP_PMTUDISC_WANT      __IP_PMTUDISC_WANT      /* Use per route hints. */
#endif /* !IP_PMTUDISC_WANT && __IP_PMTUDISC_WANT */
#if !defined(IP_PMTUDISC_DO) && defined(__IP_PMTUDISC_DO)
#define IP_PMTUDISC_DO        __IP_PMTUDISC_DO        /* Always DF. */
#endif /* !IP_PMTUDISC_DO && __IP_PMTUDISC_DO */
#if !defined(IP_PMTUDISC_PROBE) && defined(__IP_PMTUDISC_PROBE)
#define IP_PMTUDISC_PROBE     __IP_PMTUDISC_PROBE     /* Ignore dst pmtu. */
#endif /* !IP_PMTUDISC_PROBE && __IP_PMTUDISC_PROBE */
#if !defined(IP_PMTUDISC_INTERFACE) && defined(__IP_PMTUDISC_INTERFACE)
#define IP_PMTUDISC_INTERFACE __IP_PMTUDISC_INTERFACE /* Always use interface mtu (ignores dst pmtu) but don't set DF flag.
                                                       * Also incoming ICMP  frag_needed notifications will  be ignored  on
                                                       * this socket to prevent accepting spoofed ones. */
#endif /* !IP_PMTUDISC_INTERFACE && __IP_PMTUDISC_INTERFACE */
#if !defined(IP_PMTUDISC_OMIT) && defined(__IP_PMTUDISC_OMIT)
#define IP_PMTUDISC_OMIT      __IP_PMTUDISC_OMIT      /* Like IP_PMTUDISC_INTERFACE but allow packets to be fragmented. */
#endif /* !IP_PMTUDISC_OMIT && __IP_PMTUDISC_OMIT */

/* To select the IP level. */
#if !defined(SOL_IP) && defined(__SOL_IP)
#define SOL_IP                    __SOL_IP
#endif /* !SOL_IP && __SOL_IP */
#if !defined(IP_DEFAULT_MULTICAST_TTL) && defined(__IP_DEFAULT_MULTICAST_TTL)
#define IP_DEFAULT_MULTICAST_TTL  __IP_DEFAULT_MULTICAST_TTL
#endif /* !IP_DEFAULT_MULTICAST_TTL && __IP_DEFAULT_MULTICAST_TTL */
#if !defined(IP_DEFAULT_MULTICAST_LOOP) && defined(__IP_DEFAULT_MULTICAST_LOOP)
#define IP_DEFAULT_MULTICAST_LOOP __IP_DEFAULT_MULTICAST_LOOP
#endif /* !IP_DEFAULT_MULTICAST_LOOP && __IP_DEFAULT_MULTICAST_LOOP */
#if !defined(IP_MAX_MEMBERSHIPS) && defined(__IP_MAX_MEMBERSHIPS)
#define IP_MAX_MEMBERSHIPS        __IP_MAX_MEMBERSHIPS
#endif /* !IP_MAX_MEMBERSHIPS && __IP_MAX_MEMBERSHIPS */

/* Options for use with `getsockopt' and `setsockopt' at the IPv6 level.
 * The first word in  the comment at  the right is  the data type  used;
 * "bool" means a boolean value stored in an `int'. */
#if !defined(IPV6_ADDRFORM) && defined(__IPV6_ADDRFORM)
#define IPV6_ADDRFORM       __IPV6_ADDRFORM
#endif /* !IPV6_ADDRFORM && __IPV6_ADDRFORM */
#if !defined(IPV6_2292PKTINFO) && defined(__IPV6_2292PKTINFO)
#define IPV6_2292PKTINFO    __IPV6_2292PKTINFO
#endif /* !IPV6_2292PKTINFO && __IPV6_2292PKTINFO */
#if !defined(IPV6_2292HOPOPTS) && defined(__IPV6_2292HOPOPTS)
#define IPV6_2292HOPOPTS    __IPV6_2292HOPOPTS
#endif /* !IPV6_2292HOPOPTS && __IPV6_2292HOPOPTS */
#if !defined(IPV6_2292DSTOPTS) && defined(__IPV6_2292DSTOPTS)
#define IPV6_2292DSTOPTS    __IPV6_2292DSTOPTS
#endif /* !IPV6_2292DSTOPTS && __IPV6_2292DSTOPTS */
#if !defined(IPV6_2292RTHDR) && defined(__IPV6_2292RTHDR)
#define IPV6_2292RTHDR      __IPV6_2292RTHDR
#endif /* !IPV6_2292RTHDR && __IPV6_2292RTHDR */
#if !defined(IPV6_2292PKTOPTIONS) && defined(__IPV6_2292PKTOPTIONS)
#define IPV6_2292PKTOPTIONS __IPV6_2292PKTOPTIONS
#endif /* !IPV6_2292PKTOPTIONS && __IPV6_2292PKTOPTIONS */
#if !defined(IPV6_CHECKSUM) && defined(__IPV6_CHECKSUM)
#define IPV6_CHECKSUM       __IPV6_CHECKSUM
#endif /* !IPV6_CHECKSUM && __IPV6_CHECKSUM */
#if !defined(IPV6_2292HOPLIMIT) && defined(__IPV6_2292HOPLIMIT)
#define IPV6_2292HOPLIMIT   __IPV6_2292HOPLIMIT
#endif /* !IPV6_2292HOPLIMIT && __IPV6_2292HOPLIMIT */
#if !defined(IPV6_NEXTHOP) && defined(__IPV6_NEXTHOP)
#define IPV6_NEXTHOP        __IPV6_NEXTHOP
#endif /* !IPV6_NEXTHOP && __IPV6_NEXTHOP */
#if !defined(IPV6_AUTHHDR) && defined(__IPV6_AUTHHDR)
#define IPV6_AUTHHDR        __IPV6_AUTHHDR
#endif /* !IPV6_AUTHHDR && __IPV6_AUTHHDR */
#if !defined(IPV6_UNICAST_HOPS) && defined(__IPV6_UNICAST_HOPS)
#define IPV6_UNICAST_HOPS   __IPV6_UNICAST_HOPS
#endif /* !IPV6_UNICAST_HOPS && __IPV6_UNICAST_HOPS */
#if !defined(IPV6_MULTICAST_IF) && defined(__IPV6_MULTICAST_IF)
#define IPV6_MULTICAST_IF   __IPV6_MULTICAST_IF
#endif /* !IPV6_MULTICAST_IF && __IPV6_MULTICAST_IF */
#if !defined(IPV6_MULTICAST_HOPS) && defined(__IPV6_MULTICAST_HOPS)
#define IPV6_MULTICAST_HOPS __IPV6_MULTICAST_HOPS
#endif /* !IPV6_MULTICAST_HOPS && __IPV6_MULTICAST_HOPS */
#if !defined(IPV6_MULTICAST_LOOP) && defined(__IPV6_MULTICAST_LOOP)
#define IPV6_MULTICAST_LOOP __IPV6_MULTICAST_LOOP
#endif /* !IPV6_MULTICAST_LOOP && __IPV6_MULTICAST_LOOP */
#if !defined(IPV6_JOIN_GROUP) && defined(__IPV6_JOIN_GROUP)
#define IPV6_JOIN_GROUP     __IPV6_JOIN_GROUP
#endif /* !IPV6_JOIN_GROUP && __IPV6_JOIN_GROUP */
#if !defined(IPV6_LEAVE_GROUP) && defined(__IPV6_LEAVE_GROUP)
#define IPV6_LEAVE_GROUP    __IPV6_LEAVE_GROUP
#endif /* !IPV6_LEAVE_GROUP && __IPV6_LEAVE_GROUP */
#if !defined(IPV6_ROUTER_ALERT) && defined(__IPV6_ROUTER_ALERT)
#define IPV6_ROUTER_ALERT   __IPV6_ROUTER_ALERT
#endif /* !IPV6_ROUTER_ALERT && __IPV6_ROUTER_ALERT */
#if !defined(IPV6_MTU_DISCOVER) && defined(__IPV6_MTU_DISCOVER)
#define IPV6_MTU_DISCOVER   __IPV6_MTU_DISCOVER
#endif /* !IPV6_MTU_DISCOVER && __IPV6_MTU_DISCOVER */
#if !defined(IPV6_MTU) && defined(__IPV6_MTU)
#define IPV6_MTU            __IPV6_MTU
#endif /* !IPV6_MTU && __IPV6_MTU */
#if !defined(IPV6_RECVERR) && defined(__IPV6_RECVERR)
#define IPV6_RECVERR        __IPV6_RECVERR
#endif /* !IPV6_RECVERR && __IPV6_RECVERR */
#if !defined(IPV6_V6ONLY) && defined(__IPV6_V6ONLY)
#define IPV6_V6ONLY         __IPV6_V6ONLY
#endif /* !IPV6_V6ONLY && __IPV6_V6ONLY */
#if !defined(IPV6_JOIN_ANYCAST) && defined(__IPV6_JOIN_ANYCAST)
#define IPV6_JOIN_ANYCAST   __IPV6_JOIN_ANYCAST
#endif /* !IPV6_JOIN_ANYCAST && __IPV6_JOIN_ANYCAST */
#if !defined(IPV6_LEAVE_ANYCAST) && defined(__IPV6_LEAVE_ANYCAST)
#define IPV6_LEAVE_ANYCAST  __IPV6_LEAVE_ANYCAST
#endif /* !IPV6_LEAVE_ANYCAST && __IPV6_LEAVE_ANYCAST */
#if !defined(IPV6_IPSEC_POLICY) && defined(__IPV6_IPSEC_POLICY)
#define IPV6_IPSEC_POLICY   __IPV6_IPSEC_POLICY
#endif /* !IPV6_IPSEC_POLICY && __IPV6_IPSEC_POLICY */
#if !defined(IPV6_XFRM_POLICY) && defined(__IPV6_XFRM_POLICY)
#define IPV6_XFRM_POLICY    __IPV6_XFRM_POLICY
#endif /* !IPV6_XFRM_POLICY && __IPV6_XFRM_POLICY */

/* Advanced API (RFC3542) (1). */
#if !defined(IPV6_RECVPKTINFO) && defined(__IPV6_RECVPKTINFO)
#define IPV6_RECVPKTINFO  __IPV6_RECVPKTINFO
#endif /* !IPV6_RECVPKTINFO && __IPV6_RECVPKTINFO */
#if !defined(IPV6_PKTINFO) && defined(__IPV6_PKTINFO)
#define IPV6_PKTINFO      __IPV6_PKTINFO
#endif /* !IPV6_PKTINFO && __IPV6_PKTINFO */
#if !defined(IPV6_RECVHOPLIMIT) && defined(__IPV6_RECVHOPLIMIT)
#define IPV6_RECVHOPLIMIT __IPV6_RECVHOPLIMIT
#endif /* !IPV6_RECVHOPLIMIT && __IPV6_RECVHOPLIMIT */
#if !defined(IPV6_HOPLIMIT) && defined(__IPV6_HOPLIMIT)
#define IPV6_HOPLIMIT     __IPV6_HOPLIMIT
#endif /* !IPV6_HOPLIMIT && __IPV6_HOPLIMIT */
#if !defined(IPV6_RECVHOPOPTS) && defined(__IPV6_RECVHOPOPTS)
#define IPV6_RECVHOPOPTS  __IPV6_RECVHOPOPTS
#endif /* !IPV6_RECVHOPOPTS && __IPV6_RECVHOPOPTS */
#if !defined(IPV6_HOPOPTS) && defined(__IPV6_HOPOPTS)
#define IPV6_HOPOPTS      __IPV6_HOPOPTS
#endif /* !IPV6_HOPOPTS && __IPV6_HOPOPTS */
#if !defined(IPV6_RTHDRDSTOPTS) && defined(__IPV6_RTHDRDSTOPTS)
#define IPV6_RTHDRDSTOPTS __IPV6_RTHDRDSTOPTS
#endif /* !IPV6_RTHDRDSTOPTS && __IPV6_RTHDRDSTOPTS */
#if !defined(IPV6_RECVRTHDR) && defined(__IPV6_RECVRTHDR)
#define IPV6_RECVRTHDR    __IPV6_RECVRTHDR
#endif /* !IPV6_RECVRTHDR && __IPV6_RECVRTHDR */
#if !defined(IPV6_RTHDR) && defined(__IPV6_RTHDR)
#define IPV6_RTHDR        __IPV6_RTHDR
#endif /* !IPV6_RTHDR && __IPV6_RTHDR */
#if !defined(IPV6_RECVDSTOPTS) && defined(__IPV6_RECVDSTOPTS)
#define IPV6_RECVDSTOPTS  __IPV6_RECVDSTOPTS
#endif /* !IPV6_RECVDSTOPTS && __IPV6_RECVDSTOPTS */
#if !defined(IPV6_DSTOPTS) && defined(__IPV6_DSTOPTS)
#define IPV6_DSTOPTS      __IPV6_DSTOPTS
#endif /* !IPV6_DSTOPTS && __IPV6_DSTOPTS */
#if !defined(IPV6_RECVPATHMTU) && defined(__IPV6_RECVPATHMTU)
#define IPV6_RECVPATHMTU  __IPV6_RECVPATHMTU
#endif /* !IPV6_RECVPATHMTU && __IPV6_RECVPATHMTU */
#if !defined(IPV6_PATHMTU) && defined(__IPV6_PATHMTU)
#define IPV6_PATHMTU      __IPV6_PATHMTU
#endif /* !IPV6_PATHMTU && __IPV6_PATHMTU */
#if !defined(IPV6_DONTFRAG) && defined(__IPV6_DONTFRAG)
#define IPV6_DONTFRAG     __IPV6_DONTFRAG
#endif /* !IPV6_DONTFRAG && __IPV6_DONTFRAG */

/* Advanced API (RFC3542) (2). */
#if !defined(IPV6_RECVTCLASS) && defined(__IPV6_RECVTCLASS)
#define IPV6_RECVTCLASS __IPV6_RECVTCLASS
#endif /* !IPV6_RECVTCLASS && __IPV6_RECVTCLASS */
#if !defined(IPV6_TCLASS) && defined(__IPV6_TCLASS)
#define IPV6_TCLASS     __IPV6_TCLASS
#endif /* !IPV6_TCLASS && __IPV6_TCLASS */

/* Obsolete synonyms for the above. */
#if !defined(IPV6_ADD_MEMBERSHIP) && defined(IPV6_JOIN_GROUP)
#define IPV6_ADD_MEMBERSHIP  IPV6_JOIN_GROUP
#endif /* !IPV6_ADD_MEMBERSHIP && IPV6_JOIN_GROUP */
#if !defined(IPV6_DROP_MEMBERSHIP) && defined(IPV6_LEAVE_GROUP)
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
#endif /* !IPV6_DROP_MEMBERSHIP && IPV6_LEAVE_GROUP */
#if !defined(IPV6_RXHOPOPTS) && defined(IPV6_HOPOPTS)
#define IPV6_RXHOPOPTS       IPV6_HOPOPTS
#endif /* !IPV6_RXHOPOPTS && IPV6_HOPOPTS */
#if !defined(IPV6_RXDSTOPTS) && defined(IPV6_DSTOPTS)
#define IPV6_RXDSTOPTS       IPV6_DSTOPTS
#endif /* !IPV6_RXDSTOPTS && IPV6_DSTOPTS */

/* IPV6_MTU_DISCOVER values. */
#if !defined(IPV6_PMTUDISC_DONT) && defined(__IPV6_PMTUDISC_DONT)
#define IPV6_PMTUDISC_DONT      __IPV6_PMTUDISC_DONT      /* Never send DF frames. */
#endif /* !IPV6_PMTUDISC_DONT && __IPV6_PMTUDISC_DONT */
#if !defined(IPV6_PMTUDISC_WANT) && defined(__IPV6_PMTUDISC_WANT)
#define IPV6_PMTUDISC_WANT      __IPV6_PMTUDISC_WANT      /* Use per route hints. */
#endif /* !IPV6_PMTUDISC_WANT && __IPV6_PMTUDISC_WANT */
#if !defined(IPV6_PMTUDISC_DO) && defined(__IPV6_PMTUDISC_DO)
#define IPV6_PMTUDISC_DO        __IPV6_PMTUDISC_DO        /* Always DF. */
#endif /* !IPV6_PMTUDISC_DO && __IPV6_PMTUDISC_DO */
#if !defined(IPV6_PMTUDISC_PROBE) && defined(__IPV6_PMTUDISC_PROBE)
#define IPV6_PMTUDISC_PROBE     __IPV6_PMTUDISC_PROBE     /* Ignore dst pmtu. */
#endif /* !IPV6_PMTUDISC_PROBE && __IPV6_PMTUDISC_PROBE */
#if !defined(IPV6_PMTUDISC_INTERFACE) && defined(__IPV6_PMTUDISC_INTERFACE)
#define IPV6_PMTUDISC_INTERFACE __IPV6_PMTUDISC_INTERFACE /* See IP_PMTUDISC_INTERFACE. */
#endif /* !IPV6_PMTUDISC_INTERFACE && __IPV6_PMTUDISC_INTERFACE */
#if !defined(IPV6_PMTUDISC_OMIT) && defined(__IPV6_PMTUDISC_OMIT)
#define IPV6_PMTUDISC_OMIT      __IPV6_PMTUDISC_OMIT      /* See IP_PMTUDISC_OMIT. */
#endif /* !IPV6_PMTUDISC_OMIT && __IPV6_PMTUDISC_OMIT */

/* Socket level values for IPv6. */
#if !defined(SOL_IPV6) && defined(__SOL_IPV6)
#define SOL_IPV6   __SOL_IPV6
#endif /* !SOL_IPV6 && __SOL_IPV6 */
#if !defined(SOL_ICMPV6) && defined(__SOL_ICMPV6)
#define SOL_ICMPV6 __SOL_ICMPV6
#endif /* !SOL_ICMPV6 && __SOL_ICMPV6 */

/* Routing header options for IPv6. */
#if !defined(IPV6_RTHDR_LOOSE) && defined(__IPV6_RTHDR_LOOSE)
#define IPV6_RTHDR_LOOSE  __IPV6_RTHDR_LOOSE  /* Hop doesn't need to be neighbor. */
#endif /* !IPV6_RTHDR_LOOSE && __IPV6_RTHDR_LOOSE */
#if !defined(IPV6_RTHDR_STRICT) && defined(__IPV6_RTHDR_STRICT)
#define IPV6_RTHDR_STRICT __IPV6_RTHDR_STRICT /* Hop must be a neighbor. */
#endif /* !IPV6_RTHDR_STRICT && __IPV6_RTHDR_STRICT */
#if !defined(IPV6_RTHDR_TYPE_0) && defined(__IPV6_RTHDR_TYPE_0)
#define IPV6_RTHDR_TYPE_0 __IPV6_RTHDR_TYPE_0 /* IPv6 Routing header type 0. */
#endif /* !IPV6_RTHDR_TYPE_0 && __IPV6_RTHDR_TYPE_0 */
/* =================== END OF DERIVED COMMENTS */



#if !defined(INET_ADDRSTRLEN) && defined(__INET_ADDRSTRLEN)
#define INET_ADDRSTRLEN  __INET_ADDRSTRLEN /* Max # of characters written by `inet_ntoa_r' (e.g. `111.111.111.111\0') */
#endif /* !INET_ADDRSTRLEN && __INET_ADDRSTRLEN */
#if !defined(INET6_ADDRSTRLEN) && defined(__INET6_ADDRSTRLEN)
#define INET6_ADDRSTRLEN __INET6_ADDRSTRLEN
#endif /* !INET6_ADDRSTRLEN && __INET6_ADDRSTRLEN */


#ifdef __USE_MISC
#if !defined(IP_MSFILTER_SIZE) && defined(__IP_MSFILTER_SIZE)
#define IP_MSFILTER_SIZE  __IP_MSFILTER_SIZE
#endif /* !IP_MSFILTER_SIZE && __IP_MSFILTER_SIZE */
#if !defined(GROUP_FILTER_SIZE) && defined(__GROUP_FILTER_SIZE)
#define GROUP_FILTER_SIZE __GROUP_FILTER_SIZE
#endif /* !GROUP_FILTER_SIZE && __GROUP_FILTER_SIZE */
#endif /* __USE_MISC */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sa_family_t_defined
#define __sa_family_t_defined
typedef __sa_family_t sa_family_t; /* One of `AF_*' */
#endif /* !__sa_family_t_defined */

#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifndef __in_port_t_defined
#define __in_port_t_defined
typedef __in_port_t in_port_t; /* Type to represent a port. */
#endif /* !__in_port_t_defined */

/* Only uint32_t+uint8_t! */
#ifndef __uint8_t_defined
#define __uint8_t_defined
#ifdef __CC__
__DECL_BEGIN
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif /* __UINT64_TYPE__ */
__DECL_END
#endif /* __CC__ */
#endif /* !__uint8_t_defined */


/* Initializers for `struct in6_addr' */
#if !defined(IN6ADDR_ANY_INIT) && defined(__IN6ADDR_ANY_INIT)
#define IN6ADDR_ANY_INIT      __IN6ADDR_ANY_INIT
#endif /* !IN6ADDR_ANY_INIT && __IN6ADDR_ANY_INIT */
#if !defined(IN6ADDR_LOOPBACK_INIT) && defined(__IN6ADDR_LOOPBACK_INIT)
#define IN6ADDR_LOOPBACK_INIT __IN6ADDR_LOOPBACK_INIT
#endif /* !IN6ADDR_LOOPBACK_INIT && __IN6ADDR_LOOPBACK_INIT */

#if !defined(in6addr_any) && defined(__CRT_HAVE_in6addr_any)
__CSDECLARE(,struct in6_addr const,in6addr_any) /* :: */
#define in6addr_any in6addr_any
#endif /* !in6addr_any && __CRT_HAVE_in6addr_any */
#if !defined(in6addr_loopback) && defined(__CRT_HAVE_in6addr_loopback)
__CSDECLARE(,struct in6_addr const,in6addr_loopback) /* ::1 */
#define in6addr_loopback in6addr_loopback
#endif /* !in6addr_loopback && __CRT_HAVE_in6addr_loopback */



#ifndef __htons_defined
#define __htons_defined
#ifdef __CRT_HAVE_htons
__CEIDECLARE(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#elif defined(__CRT_HAVE_ntohs) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),ntohs,{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#elif defined(__CRT_HAVE___htons)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),__htons,{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#elif defined(__CRT_HAVE___ntohs) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,htons,(__UINT16_TYPE__ __hostword),__ntohs,{ return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); })
#else /* ... */
__LOCAL __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__LIBCCALL htons)(__UINT16_TYPE__ __hostword) { return (__UINT16_TYPE__)__hybrid_htobe32(__hostword); }
#endif /* !... */
#endif /* !__htons_defined */
#ifndef __ntohs_defined
#define __ntohs_defined
#ifdef __CRT_HAVE_ntohs
__CEIDECLARE(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#elif defined(__CRT_HAVE_htons) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),htons,{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#elif defined(__CRT_HAVE___ntohs)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),__ntohs,{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#elif defined(__CRT_HAVE___htons) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,__UINT16_TYPE__,__NOTHROW,ntohs,(__UINT16_TYPE__ __netshort),__htons,{ return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); })
#else /* ... */
__LOCAL __ATTR_CONST __UINT16_TYPE__ __NOTHROW(__LIBCCALL ntohs)(__UINT16_TYPE__ __netshort) { return (__UINT16_TYPE__)__hybrid_betoh16(__netshort); }
#endif /* !... */
#endif /* !__ntohs_defined */
#ifndef __htonl_defined
#define __htonl_defined
#ifdef __CRT_HAVE_htonl
__CEIDECLARE(__ATTR_CONST,uint32_t,__NOTHROW,htonl,(uint32_t __hostlong),{ return (uint32_t)__hybrid_htobe32(__hostlong); })
#elif defined(__CRT_HAVE_ntohl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW,htonl,(uint32_t __hostlong),ntohl,{ return (uint32_t)__hybrid_htobe32(__hostlong); })
#elif defined(__CRT_HAVE___htonl)
__CEIREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW,htonl,(uint32_t __hostlong),__htonl,{ return (uint32_t)__hybrid_htobe32(__hostlong); })
#elif defined(__CRT_HAVE___ntohl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW,htonl,(uint32_t __hostlong),__ntohl,{ return (uint32_t)__hybrid_htobe32(__hostlong); })
#else /* ... */
__LOCAL __ATTR_CONST uint32_t __NOTHROW(__LIBCCALL htonl)(uint32_t __hostlong) { return (uint32_t)__hybrid_htobe32(__hostlong); }
#endif /* !... */
#endif /* !__htonl_defined */
#ifndef __ntohl_defined
#define __ntohl_defined
#ifdef __CRT_HAVE_ntohl
__CEIDECLARE(__ATTR_CONST,uint32_t,__NOTHROW,ntohl,(uint32_t __netlong),{ return (uint32_t)__hybrid_betoh32(__netlong); })
#elif defined(__CRT_HAVE_htonl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW,ntohl,(uint32_t __netlong),htonl,{ return (uint32_t)__hybrid_betoh32(__netlong); })
#elif defined(__CRT_HAVE___ntohl)
__CEIREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW,ntohl,(uint32_t __netlong),__ntohl,{ return (uint32_t)__hybrid_betoh32(__netlong); })
#elif defined(__CRT_HAVE___htonl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW,ntohl,(uint32_t __netlong),__htonl,{ return (uint32_t)__hybrid_betoh32(__netlong); })
#else /* ... */
__LOCAL __ATTR_CONST uint32_t __NOTHROW(__LIBCCALL ntohl)(uint32_t __netlong) { return (uint32_t)__hybrid_betoh32(__netlong); }
#endif /* !... */
#endif /* !__ntohl_defined */
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#ifdef __CRT_HAVE_htonq
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,htonq,(__UINT64_TYPE__ __hostquad),{ return (__UINT64_TYPE__)__hybrid_htobe64(__hostquad); })
#elif defined(__CRT_HAVE_ntohq) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,htonq,(__UINT64_TYPE__ __hostquad),ntohq,{ return (__UINT64_TYPE__)__hybrid_htobe64(__hostquad); })
#else /* ... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW(__LIBCCALL htonq)(__UINT64_TYPE__ __hostquad) { return (__UINT64_TYPE__)__hybrid_htobe64(__hostquad); }
#endif /* !... */
#ifdef __CRT_HAVE_ntohq
__CEIDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,ntohq,(__UINT64_TYPE__ __netquad),{ return (__UINT64_TYPE__)__hybrid_betoh64(__netquad); })
#elif defined(__CRT_HAVE_htonq) && defined(__HYBRID_HTOBE_IS_BETOH)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__UINT64_TYPE__,__NOTHROW,ntohq,(__UINT64_TYPE__ __netquad),htonq,{ return (__UINT64_TYPE__)__hybrid_betoh64(__netquad); })
#else /* ... */
__LOCAL __ATTR_CONST __ATTR_WUNUSED __UINT64_TYPE__ __NOTHROW(__LIBCCALL ntohq)(__UINT64_TYPE__ __netquad) { return (__UINT64_TYPE__)__hybrid_betoh64(__netquad); }
#endif /* !... */
#endif /* __USE_KOS && __UINT64_TYPE__ */

#ifdef __USE_KOS_ALTERATIONS
#ifndef htons
#define htons(x) __hybrid_htobe16(x)
#endif /* !htons */
#ifndef ntohs
#define ntohs(x) __hybrid_betoh16(x)
#endif /* !ntohs */
#ifndef htonl
#define htonl(x) __hybrid_htobe32(x)
#endif /* !htonl */
#ifndef ntohl
#define ntohl(x) __hybrid_betoh32(x)
#endif /* !ntohl */
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#ifndef htonq
#define htonq(x) __hybrid_htobe64(x)
#endif /* !htonq */
#ifndef ntohq
#define ntohq(x) __hybrid_betoh64(x)
#endif /* !ntohq */
#endif /* __USE_KOS && __UINT64_TYPE__ */
#else /* __USE_KOS_ALTERATIONS */
#ifndef htons
#define htons(x) __CCAST(__uint16_t)__hybrid_htobe16(x)
#endif /* !htons */
#ifndef ntohs
#define ntohs(x) __CCAST(__uint16_t)__hybrid_betoh16(x)
#endif /* !ntohs */
#ifndef htonl
#define htonl(x) __CCAST(__uint32_t)__hybrid_htobe32(x)
#endif /* !htonl */
#ifndef ntohl
#define ntohl(x) __CCAST(__uint32_t)__hybrid_betoh32(x)
#endif /* !ntohl */
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#ifndef htonq
#define htonq(x) __CCAST(__uint64_t)__hybrid_htobe64(x)
#endif /* !htonq */
#ifndef ntohq
#define ntohq(x) __CCAST(__uint64_t)__hybrid_betoh64(x)
#endif /* !ntohq */
#endif /* __USE_KOS && __UINT64_TYPE__ */
#endif /* !__USE_KOS_ALTERATIONS */

#if !defined(IN6_IS_ADDR_LINKLOCAL) && defined(__IN6_IS_ADDR_LINKLOCAL)
#define IN6_IS_ADDR_LINKLOCAL(a)    __IN6_IS_ADDR_LINKLOCAL(a)
#endif /* !IN6_IS_ADDR_LINKLOCAL && __IN6_IS_ADDR_LINKLOCAL */
#if !defined(IN6_IS_ADDR_SITELOCAL) && defined(__IN6_IS_ADDR_SITELOCAL)
#define IN6_IS_ADDR_SITELOCAL(a)    __IN6_IS_ADDR_SITELOCAL(a)
#endif /* !IN6_IS_ADDR_SITELOCAL && __IN6_IS_ADDR_SITELOCAL */
#if !defined(IN6_IS_ADDR_MULTICAST) && defined(__IN6_IS_ADDR_MULTICAST)
#define IN6_IS_ADDR_MULTICAST(a)    __IN6_IS_ADDR_MULTICAST(a)
#endif /* !IN6_IS_ADDR_MULTICAST && __IN6_IS_ADDR_MULTICAST */
#if !defined(IN6_IS_ADDR_UNSPECIFIED) && defined(__IN6_IS_ADDR_UNSPECIFIED)
#define IN6_IS_ADDR_UNSPECIFIED(a)  __IN6_IS_ADDR_UNSPECIFIED(a)
#endif /* !IN6_IS_ADDR_UNSPECIFIED && __IN6_IS_ADDR_UNSPECIFIED */
#if !defined(IN6_IS_ADDR_LOOPBACK) && defined(__IN6_IS_ADDR_LOOPBACK)
#define IN6_IS_ADDR_LOOPBACK(a)     __IN6_IS_ADDR_LOOPBACK(a)
#endif /* !IN6_IS_ADDR_LOOPBACK && __IN6_IS_ADDR_LOOPBACK */
#if !defined(IN6_IS_ADDR_V4MAPPED) && defined(__IN6_IS_ADDR_V4MAPPED)
#define IN6_IS_ADDR_V4MAPPED(a)     __IN6_IS_ADDR_V4MAPPED(a)
#endif /* !IN6_IS_ADDR_V4MAPPED && __IN6_IS_ADDR_V4MAPPED */
#if !defined(IN6_IS_ADDR_V4COMPAT) && defined(__IN6_IS_ADDR_V4COMPAT)
#define IN6_IS_ADDR_V4COMPAT(a)     __IN6_IS_ADDR_V4COMPAT(a)
#endif /* !IN6_IS_ADDR_V4COMPAT && __IN6_IS_ADDR_V4COMPAT */
#if !defined(IN6_ARE_ADDR_EQUAL) && defined(__IN6_ARE_ADDR_EQUAL)
#define IN6_ARE_ADDR_EQUAL(a, b)    __IN6_ARE_ADDR_EQUAL(a, b)
#endif /* !IN6_ARE_ADDR_EQUAL && __IN6_ARE_ADDR_EQUAL */
#if !defined(IN6_IS_ADDR_MC_NODELOCAL) && defined(__IN6_IS_ADDR_MC_NODELOCAL)
#define IN6_IS_ADDR_MC_NODELOCAL(a) __IN6_IS_ADDR_MC_NODELOCAL(a)
#endif /* !IN6_IS_ADDR_MC_NODELOCAL && __IN6_IS_ADDR_MC_NODELOCAL */
#if !defined(IN6_IS_ADDR_MC_LINKLOCAL) && defined(__IN6_IS_ADDR_MC_LINKLOCAL)
#define IN6_IS_ADDR_MC_LINKLOCAL(a) __IN6_IS_ADDR_MC_LINKLOCAL(a)
#endif /* !IN6_IS_ADDR_MC_LINKLOCAL && __IN6_IS_ADDR_MC_LINKLOCAL */
#if !defined(IN6_IS_ADDR_MC_SITELOCAL) && defined(__IN6_IS_ADDR_MC_SITELOCAL)
#define IN6_IS_ADDR_MC_SITELOCAL(a) __IN6_IS_ADDR_MC_SITELOCAL(a)
#endif /* !IN6_IS_ADDR_MC_SITELOCAL && __IN6_IS_ADDR_MC_SITELOCAL */
#if !defined(IN6_IS_ADDR_MC_ORGLOCAL) && defined(__IN6_IS_ADDR_MC_ORGLOCAL)
#define IN6_IS_ADDR_MC_ORGLOCAL(a)  __IN6_IS_ADDR_MC_ORGLOCAL(a)
#endif /* !IN6_IS_ADDR_MC_ORGLOCAL && __IN6_IS_ADDR_MC_ORGLOCAL */
#if !defined(IN6_IS_ADDR_MC_GLOBAL) && defined(__IN6_IS_ADDR_MC_GLOBAL)
#define IN6_IS_ADDR_MC_GLOBAL(a)    __IN6_IS_ADDR_MC_GLOBAL(a)
#endif /* !IN6_IS_ADDR_MC_GLOBAL && __IN6_IS_ADDR_MC_GLOBAL */


#ifdef __USE_MISC
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC,bindresvport,(__fd_t __sockfd, struct sockaddr_in *__sock_in),(__sockfd,__sock_in))
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC,bindresvport6,(__fd_t __sockfd, struct sockaddr_in6 *__sock_in),(__sockfd,__sock_in))
#endif /* __USE_MISC */

#ifdef __USE_GNU
struct cmsghdr;

__CDECLARE_OPT(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_space,(int __nbytes),(__nbytes))
__CDECLARE_OPT(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_init,(void *__bp, struct cmsghdr **__cmsgp, int __type),(__bp,__cmsgp,__type))
__CDECLARE_OPT(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_append,(struct cmsghdr *__cmsg, uint8_t const *__typep, int __multx, int __plusy),(__cmsg,__typep,__multx,__plusy))
__CDECLARE_OPT(__ATTR_DEPRECATED_,uint8_t *,__NOTHROW_RPC_KOS,inet6_option_alloc,(struct cmsghdr *__cmsg, int __datalen, int __multx, int __plusy),(__cmsg,__datalen,__multx,__plusy))
__CDECLARE_OPT(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_next,(struct cmsghdr const *__cmsg, uint8_t **__tptrp),(__cmsg,__tptrp))
__CDECLARE_OPT(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_find,(struct cmsghdr const *__cmsg, uint8_t **__tptrp, int __type),(__cmsg,__tptrp,__type))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_init,(void *__extbuf, socklen_t __extlen),(__extbuf,__extlen))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_append,(void *__extbuf, socklen_t __extlen, int __offset, uint8_t __type, socklen_t __len, uint8_t __align, void **__databufp),(__extbuf,__extlen,__offset,__type,__len,__align,__databufp))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_finish,(void *__extbuf, socklen_t __extlen, int __offset),(__extbuf,__extlen,__offset))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_set_val,(void *__databuf, int __offset, void *__val, socklen_t __vallen),(__databuf,__offset,__val,__vallen))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_next,(void *__extbuf, socklen_t __extlen, int __offset, uint8_t *__typep, socklen_t *__lenp, void **__databufp),(__extbuf,__extlen,__offset,__typep,__lenp,__databufp))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_find,(void *__extbuf, socklen_t __extlen, int __offset, uint8_t __type, socklen_t *__lenp, void **__databufp),(__extbuf,__extlen,__offset,__type,__lenp,__databufp))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_opt_get_val,(void *__databuf, int __offset, void *__val, socklen_t __vallen),(__databuf,__offset,__val,__vallen))
__CDECLARE_OPT(,socklen_t,__NOTHROW_RPC_KOS,inet6_rth_space,(int __type, int __segments),(__type,__segments))
__CDECLARE_OPT(,void *,__NOTHROW_RPC_KOS,inet6_rth_init,(void *__bp, socklen_t __bp_len, int __type, int __segments),(__bp,__bp_len,__type,__segments))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_rth_add,(void *__bp, struct in6_addr const *__addr),(__bp,__addr))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_rth_reverse,(void const *___in, void *___out),(___in,___out))
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet6_rth_segments,(void const *__bp),(__bp))
__CDECLARE_OPT(,struct in6_addr *,__NOTHROW_RPC_KOS,inet6_rth_getaddr,(void const *__bp, int __index),(__bp,__index))
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC_KOS,getipv4sourcefilter,(__fd_t __sockfd, struct in_addr __interface_addr, struct in_addr __group, uint32_t *__fmode, uint32_t *__numsrc, struct in_addr *__slist),(__sockfd,__interface_addr,__group,__fmode,__numsrc,__slist))
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC_KOS,setipv4sourcefilter,(__fd_t __sockfd, struct in_addr __interface_addr, struct in_addr __group, uint32_t __fmode, uint32_t __numsrc, struct in_addr const *__slist),(__sockfd,__interface_addr,__group,__fmode,__numsrc,__slist))
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC_KOS,getsourcefilter,(__fd_t __sockfd, uint32_t __interface_addr, struct sockaddr const *__group, socklen_t __grouplen, uint32_t *__fmode, uint32_t *__numsrc, struct sockaddr_storage *__slist),(__sockfd,__interface_addr,__group,__grouplen,__fmode,__numsrc,__slist))
__CDECLARE_OPT(__ATTR_FDARG(1),int,__NOTHROW_RPC_KOS,setsourcefilter,(__fd_t __sockfd, uint32_t __interface_addr, struct sockaddr const *__group, socklen_t __grouplen, uint32_t __fmode, uint32_t __numsrc, struct sockaddr_storage const *__slist),(__sockfd,__interface_addr,__group,__grouplen,__fmode,__numsrc,__slist))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_IN_H */
