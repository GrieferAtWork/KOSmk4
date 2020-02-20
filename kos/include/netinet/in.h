/* HASH CRC-32:0xc3bf2693 */
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
#ifndef _NETINET_IN_H
#define _NETINET_IN_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <hybrid/__byteorder.h>
#include <hybrid/__byteswap.h>

#include <bits/in.h>
#include <bits/sockaddr-struct.h>
#include <bits/sockaddr.h>
#include <bits/sockaddr_storage-struct.h>
#include <bits/types.h>
#include <net/types.h>

#include <stdint.h>

#ifdef __USE_GLIBC
#include <sys/socket.h>
#endif /* __USE_GLIBC */

/* Documentation taken from Glibc /usr/include/netinet/in.h */
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

__SYSDECL_BEGIN

/* Standard well-defined IP protocols. */
#undef IPPROTO_IP
#undef IPPROTO_ICMP
#undef IPPROTO_IGMP
#undef IPPROTO_IPIP
#undef IPPROTO_TCP
#undef IPPROTO_EGP
#undef IPPROTO_PUP
#undef IPPROTO_UDP
#undef IPPROTO_IDP
#undef IPPROTO_TP
#undef IPPROTO_DCCP
#undef IPPROTO_IPV6
#undef IPPROTO_RSVP
#undef IPPROTO_GRE
#undef IPPROTO_ESP
#undef IPPROTO_AH
#undef IPPROTO_MTP
#undef IPPROTO_BEETPH
#undef IPPROTO_ENCAP
#undef IPPROTO_PIM
#undef IPPROTO_COMP
#undef IPPROTO_SCTP
#undef IPPROTO_UDPLITE
#undef IPPROTO_MPLS
#undef IPPROTO_RAW
#undef IPPROTO_MAX
#ifdef __CC__
enum {
	IPPROTO_IP      = 0,   /* Dummy protocol for TCP. */
	IPPROTO_ICMP    = 1,   /* Internet Control Message Protocol. */
	IPPROTO_IGMP    = 2,   /* Internet Group Management Protocol. */
	IPPROTO_IPIP    = 4,   /* IPIP tunnels (older KA9Q tunnels use 94). */
	IPPROTO_TCP     = 6,   /* Transmission Control Protocol. */
	IPPROTO_EGP     = 8,   /* Exterior Gateway Protocol. */
	IPPROTO_PUP     = 12,  /* PUP protocol. */
	IPPROTO_UDP     = 17,  /* User Datagram Protocol. */
	IPPROTO_IDP     = 22,  /* XNS IDP protocol. */
	IPPROTO_TP      = 29,  /* SO Transport Protocol Class 4. */
	IPPROTO_DCCP    = 33,  /* Datagram Congestion Control Protocol. */
	IPPROTO_IPV6    = 41,  /* IPv6 header. */
	IPPROTO_RSVP    = 46,  /* Reservation Protocol. */
	IPPROTO_GRE     = 47,  /* General Routing Encapsulation. */
	IPPROTO_ESP     = 50,  /* encapsulating security payload. */
	IPPROTO_AH      = 51,  /* authentication header. */
	IPPROTO_MTP     = 92,  /* Multicast Transport Protocol. */
	IPPROTO_BEETPH  = 94,  /* IP option pseudo header for BEET. */
	IPPROTO_ENCAP   = 98,  /* Encapsulation Header. */
	IPPROTO_PIM     = 103, /* Protocol Independent Multicast. */
	IPPROTO_COMP    = 108, /* Compression Header Protocol. */
	IPPROTO_SCTP    = 132, /* Stream Control Transmission Protocol. */
	IPPROTO_UDPLITE = 136, /* UDP-Lite protocol. */
	IPPROTO_MPLS    = 137, /* MPLS in IP. */
	IPPROTO_RAW     = 255, /* Raw IP packets. */
	IPPROTO_MAX     = 256
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define IPPROTO_IP      IPPROTO_IP      /* Dummy protocol for TCP. */
#define IPPROTO_ICMP    IPPROTO_ICMP    /* Internet Control Message Protocol. */
#define IPPROTO_IGMP    IPPROTO_IGMP    /* Internet Group Management Protocol. */
#define IPPROTO_IPIP    IPPROTO_IPIP    /* IPIP tunnels (older KA9Q tunnels use 94). */
#define IPPROTO_TCP     IPPROTO_TCP     /* Transmission Control Protocol. */
#define IPPROTO_EGP     IPPROTO_EGP     /* Exterior Gateway Protocol. */
#define IPPROTO_PUP     IPPROTO_PUP     /* PUP protocol. */
#define IPPROTO_UDP     IPPROTO_UDP     /* User Datagram Protocol. */
#define IPPROTO_IDP     IPPROTO_IDP     /* XNS IDP protocol. */
#define IPPROTO_TP      IPPROTO_TP      /* SO Transport Protocol Class 4. */
#define IPPROTO_DCCP    IPPROTO_DCCP    /* Datagram Congestion Control Protocol. */
#define IPPROTO_IPV6    IPPROTO_IPV6    /* IPv6 header. */
#define IPPROTO_RSVP    IPPROTO_RSVP    /* Reservation Protocol. */
#define IPPROTO_GRE     IPPROTO_GRE     /* General Routing Encapsulation. */
#define IPPROTO_ESP     IPPROTO_ESP     /* encapsulating security payload. */
#define IPPROTO_AH      IPPROTO_AH      /* authentication header. */
#define IPPROTO_MTP     IPPROTO_MTP     /* Multicast Transport Protocol. */
#define IPPROTO_BEETPH  IPPROTO_BEETPH  /* IP option pseudo header for BEET. */
#define IPPROTO_ENCAP   IPPROTO_ENCAP   /* Encapsulation Header. */
#define IPPROTO_PIM     IPPROTO_PIM     /* Protocol Independent Multicast. */
#define IPPROTO_COMP    IPPROTO_COMP    /* Compression Header Protocol. */
#define IPPROTO_SCTP    IPPROTO_SCTP    /* Stream Control Transmission Protocol. */
#define IPPROTO_UDPLITE IPPROTO_UDPLITE /* UDP-Lite protocol. */
#define IPPROTO_MPLS    IPPROTO_MPLS    /* MPLS in IP. */
#define IPPROTO_RAW     IPPROTO_RAW     /* Raw IP packets. */
#define IPPROTO_MAX     IPPROTO_MAX
#else /* __COMPILER_PREFERR_ENUMS */
#define IPPROTO_IP      0   /* Dummy protocol for TCP. */
#define IPPROTO_ICMP    1   /* Internet Control Message Protocol. */
#define IPPROTO_IGMP    2   /* Internet Group Management Protocol. */
#define IPPROTO_IPIP    4   /* IPIP tunnels (older KA9Q tunnels use 94). */
#define IPPROTO_TCP     6   /* Transmission Control Protocol. */
#define IPPROTO_EGP     8   /* Exterior Gateway Protocol. */
#define IPPROTO_PUP     12  /* PUP protocol. */
#define IPPROTO_UDP     17  /* User Datagram Protocol. */
#define IPPROTO_IDP     22  /* XNS IDP protocol. */
#define IPPROTO_TP      29  /* SO Transport Protocol Class 4. */
#define IPPROTO_DCCP    33  /* Datagram Congestion Control Protocol. */
#define IPPROTO_IPV6    41  /* IPv6 header. */
#define IPPROTO_RSVP    46  /* Reservation Protocol. */
#define IPPROTO_GRE     47  /* General Routing Encapsulation. */
#define IPPROTO_ESP     50  /* encapsulating security payload. */
#define IPPROTO_AH      51  /* authentication header. */
#define IPPROTO_MTP     92  /* Multicast Transport Protocol. */
#define IPPROTO_BEETPH  94  /* IP option pseudo header for BEET. */
#define IPPROTO_ENCAP   98  /* Encapsulation Header. */
#define IPPROTO_PIM     103 /* Protocol Independent Multicast. */
#define IPPROTO_COMP    108 /* Compression Header Protocol. */
#define IPPROTO_SCTP    132 /* Stream Control Transmission Protocol. */
#define IPPROTO_UDPLITE 136 /* UDP-Lite protocol. */
#define IPPROTO_MPLS    137 /* MPLS in IP. */
#define IPPROTO_RAW     255 /* Raw IP packets. */
#define IPPROTO_MAX     256
#endif /* !__COMPILER_PREFERR_ENUMS */


#undef IPPROTO_HOPOPTS
#undef IPPROTO_ROUTING
#undef IPPROTO_FRAGMENT
#undef IPPROTO_ICMPV6
#undef IPPROTO_NONE
#undef IPPROTO_DSTOPTS
#undef IPPROTO_MH
#ifdef __CC__
enum {
	IPPROTO_HOPOPTS  = 0,   /* IPv6 Hop-by-Hop options. */
	IPPROTO_ROUTING  = 43,  /* IPv6 routing header. */
	IPPROTO_FRAGMENT = 44,  /* IPv6 fragmentation header. */
	IPPROTO_ICMPV6   = 58,  /* ICMPv6. */
	IPPROTO_NONE     = 59,  /* IPv6 no next header. */
	IPPROTO_DSTOPTS  = 60,  /* IPv6 destination options. */
	IPPROTO_MH       = 135 /* IPv6 mobility header. */
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define IPPROTO_HOPOPTS  IPPROTO_HOPOPTS  /* IPv6 Hop-by-Hop options. */
#define IPPROTO_ROUTING  IPPROTO_ROUTING  /* IPv6 routing header. */
#define IPPROTO_FRAGMENT IPPROTO_FRAGMENT /* IPv6 fragmentation header. */
#define IPPROTO_ICMPV6   IPPROTO_ICMPV6   /* ICMPv6. */
#define IPPROTO_NONE     IPPROTO_NONE     /* IPv6 no next header. */
#define IPPROTO_DSTOPTS  IPPROTO_DSTOPTS  /* IPv6 destination options. */
#define IPPROTO_MH       IPPROTO_MH       /* IPv6 mobility header. */
#else /* __COMPILER_PREFERR_ENUMS */
#define IPPROTO_HOPOPTS  0   /* IPv6 Hop-by-Hop options. */
#define IPPROTO_ROUTING  43  /* IPv6 routing header. */
#define IPPROTO_FRAGMENT 44  /* IPv6 fragmentation header. */
#define IPPROTO_ICMPV6   58  /* ICMPv6. */
#define IPPROTO_NONE     59  /* IPv6 no next header. */
#define IPPROTO_DSTOPTS  60  /* IPv6 destination options. */
#define IPPROTO_MH       135 /* IPv6 mobility header. */
#endif /* !__COMPILER_PREFERR_ENUMS */


/* Standard well-known ports. */
#undef IPPORT_ECHO
#undef IPPORT_DISCARD
#undef IPPORT_SYSTAT
#undef IPPORT_DAYTIME
#undef IPPORT_NETSTAT
#undef IPPORT_FTP
#undef IPPORT_TELNET
#undef IPPORT_SMTP
#undef IPPORT_TIMESERVER
#undef IPPORT_NAMESERVER
#undef IPPORT_WHOIS
#undef IPPORT_MTP
#undef IPPORT_TFTP
#undef IPPORT_RJE
#undef IPPORT_FINGER
#undef IPPORT_TTYLINK
#undef IPPORT_SUPDUP
#undef IPPORT_EXECSERVER
#undef IPPORT_LOGINSERVER
#undef IPPORT_CMDSERVER
#undef IPPORT_EFSSERVER
#undef IPPORT_BIFFUDP
#undef IPPORT_WHOSERVER
#undef IPPORT_ROUTESERVER
#undef IPPORT_RESERVED
#undef IPPORT_USERRESERVED
#ifdef __CC__
enum {
	IPPORT_ECHO         = 7,    /* Echo service. */
	IPPORT_DISCARD      = 9,    /* Discard transmissions service. */
	IPPORT_SYSTAT       = 11,   /* System status service. */
	IPPORT_DAYTIME      = 13,   /* Time of day service. */
	IPPORT_NETSTAT      = 15,   /* Network status service. */
	IPPORT_FTP          = 21,   /* File Transfer Protocol. */
	IPPORT_TELNET       = 23,   /* Telnet protocol. */
	IPPORT_SMTP         = 25,   /* Simple Mail Transfer Protocol. */
	IPPORT_TIMESERVER   = 37,   /* Timeserver service. */
	IPPORT_NAMESERVER   = 42,   /* Domain Name Service. */
	IPPORT_WHOIS        = 43,   /* Internet Whois service. */
	IPPORT_MTP          = 57,
	IPPORT_TFTP         = 69,   /* Trivial File Transfer Protocol. */
	IPPORT_RJE          = 77,
	IPPORT_FINGER       = 79,   /* Finger service. */
	IPPORT_TTYLINK      = 87,
	IPPORT_SUPDUP       = 95,   /* SUPDUP protocol. */
	IPPORT_EXECSERVER   = 512,  /* execd service. */
	IPPORT_LOGINSERVER  = 513,  /* rlogind service. */
	IPPORT_CMDSERVER    = 514,
	IPPORT_EFSSERVER    = 520,
	IPPORT_BIFFUDP      = 512,  /* UDP ports. */
	IPPORT_WHOSERVER    = 513,  /* ... */
	IPPORT_ROUTESERVER  = 520,  /* ... */
	IPPORT_RESERVED     = 1024, /* Ports less than this value are reserved for privileged processes. */
	IPPORT_USERRESERVED = 5000 /* Ports greater this value are reserved for (non-privileged) servers. */
};
#endif /* __CC__ */
#ifdef __COMPILER_PREFERR_ENUMS
#define IPPORT_ECHO         IPPORT_ECHO         /* Echo service. */
#define IPPORT_DISCARD      IPPORT_DISCARD      /* Discard transmissions service. */
#define IPPORT_SYSTAT       IPPORT_SYSTAT       /* System status service. */
#define IPPORT_DAYTIME      IPPORT_DAYTIME      /* Time of day service. */
#define IPPORT_NETSTAT      IPPORT_NETSTAT      /* Network status service. */
#define IPPORT_FTP          IPPORT_FTP          /* File Transfer Protocol. */
#define IPPORT_TELNET       IPPORT_TELNET       /* Telnet protocol. */
#define IPPORT_SMTP         IPPORT_SMTP         /* Simple Mail Transfer Protocol. */
#define IPPORT_TIMESERVER   IPPORT_TIMESERVER   /* Timeserver service. */
#define IPPORT_NAMESERVER   IPPORT_NAMESERVER   /* Domain Name Service. */
#define IPPORT_WHOIS        IPPORT_WHOIS        /* Internet Whois service. */
#define IPPORT_MTP          IPPORT_MTP
#define IPPORT_TFTP         IPPORT_TFTP         /* Trivial File Transfer Protocol. */
#define IPPORT_RJE          IPPORT_RJE
#define IPPORT_FINGER       IPPORT_FINGER       /* Finger service. */
#define IPPORT_TTYLINK      IPPORT_TTYLINK
#define IPPORT_SUPDUP       IPPORT_SUPDUP       /* SUPDUP protocol. */
#define IPPORT_EXECSERVER   IPPORT_EXECSERVER   /* execd service. */
#define IPPORT_LOGINSERVER  IPPORT_LOGINSERVER  /* rlogind service. */
#define IPPORT_CMDSERVER    IPPORT_CMDSERVER
#define IPPORT_EFSSERVER    IPPORT_EFSSERVER
#define IPPORT_BIFFUDP      IPPORT_BIFFUDP      /* UDP ports. */
#define IPPORT_WHOSERVER    IPPORT_WHOSERVER    /* ... */
#define IPPORT_ROUTESERVER  IPPORT_ROUTESERVER  /* ... */
#define IPPORT_RESERVED     IPPORT_RESERVED     /* Ports less than this value are reserved for privileged processes. */
#define IPPORT_USERRESERVED IPPORT_USERRESERVED /* Ports greater this value are reserved for (non-privileged) servers. */
#else /* __COMPILER_PREFERR_ENUMS */
#define IPPORT_ECHO         7    /* Echo service. */
#define IPPORT_DISCARD      9    /* Discard transmissions service. */
#define IPPORT_SYSTAT       11   /* System status service. */
#define IPPORT_DAYTIME      13   /* Time of day service. */
#define IPPORT_NETSTAT      15   /* Network status service. */
#define IPPORT_FTP          21   /* File Transfer Protocol. */
#define IPPORT_TELNET       23   /* Telnet protocol. */
#define IPPORT_SMTP         25   /* Simple Mail Transfer Protocol. */
#define IPPORT_TIMESERVER   37   /* Timeserver service. */
#define IPPORT_NAMESERVER   42   /* Domain Name Service. */
#define IPPORT_WHOIS        43   /* Internet Whois service. */
#define IPPORT_MTP          57
#define IPPORT_TFTP         69   /* Trivial File Transfer Protocol. */
#define IPPORT_RJE          77
#define IPPORT_FINGER       79   /* Finger service. */
#define IPPORT_TTYLINK      87
#define IPPORT_SUPDUP       95   /* SUPDUP protocol. */
#define IPPORT_EXECSERVER   512  /* execd service. */
#define IPPORT_LOGINSERVER  513  /* rlogind service. */
#define IPPORT_CMDSERVER    514
#define IPPORT_EFSSERVER    520
#define IPPORT_BIFFUDP      512  /* UDP ports. */
#define IPPORT_WHOSERVER    513  /* ... */
#define IPPORT_ROUTESERVER  520  /* ... */
#define IPPORT_RESERVED     1024 /* Ports less than this value are reserved for privileged processes. */
#define IPPORT_USERRESERVED 5000 /* Ports greater this value are reserved for (non-privileged) servers. */
#endif /* !__COMPILER_PREFERR_ENUMS */


/* Definitions of the bits in an Internet address integer.
 * On subnets, host and network parts are found according to
 * the subnet mask, not these masks. */
#define IN_CLASSA(a)       (((__CCAST(in_addr_t)(a)) & 0x80000000) == 0)
#define IN_CLASSA_NET         0xff000000
#define IN_CLASSA_NSHIFT      24
#define IN_CLASSA_HOST       (0xffffffff & ~IN_CLASSA_NET)
#define IN_CLASSA_MAX         128
#define IN_CLASSB(a)       (((__CCAST(in_addr_t)(a)) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET         0xffff0000
#define IN_CLASSB_NSHIFT      16
#define IN_CLASSB_HOST       (0xffffffff & ~IN_CLASSB_NET)
#define IN_CLASSB_MAX         65536
#define IN_CLASSC(a)       (((__CCAST(in_addr_t)(a)) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET         0xffffff00
#define IN_CLASSC_NSHIFT      8
#define IN_CLASSC_HOST       (0xffffffff & ~IN_CLASSC_NET)
#define IN_CLASSD(a)       (((__CCAST(in_addr_t)(a)) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(a)       IN_CLASSD(a)
#define IN_EXPERIMENTAL(a) (((__CCAST(in_addr_t)(a)) & 0xe0000000) == 0xe0000000)
#define IN_BADCLASS(a)     (((__CCAST(in_addr_t)(a)) & 0xf0000000) == 0xf0000000)

#define INADDR_ANY           (__CCAST(in_addr_t)0x00000000) /* Address to accept any incoming messages. */
#define INADDR_BROADCAST     (__CCAST(in_addr_t)0xffffffff) /* Address to send to all hosts. */
#define INADDR_NONE          (__CCAST(in_addr_t)0xffffffff) /* Address indicating an error return. */

#define IN_LOOPBACKNET         127 /* Network number for local host loopback. */
#ifndef INADDR_LOOPBACK /* Address to loopback in software to local host. */
#define INADDR_LOOPBACK      (__CCAST(in_addr_t)0x7f000001) /* Inet 127.0.0.1. */
#endif /* !INADDR_LOOPBACK */

/* Defines for Multicast INADDR. */
#define INADDR_UNSPEC_GROUP    (__CCAST(in_addr_t)0xe0000000) /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP  (__CCAST(in_addr_t)0xe0000001) /* 224.0.0.1 */
#define INADDR_ALLRTRS_GROUP   (__CCAST(in_addr_t)0xe0000002) /* 224.0.0.2 */
#define INADDR_MAX_LOCAL_GROUP (__CCAST(in_addr_t)0xe00000ff) /* 224.0.0.255 */


#ifdef __CC__

typedef __u_net16_t in_port_t; /* Type to represent a port. */

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */


/* IPv6 address */
struct in6_addr {
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
#undef s6_addr
		__uint8_t  s6_addr[16];
#ifdef __USE_MISC
#undef s6_addr16
#undef s6_addr32
		__u_net16_t s6_addr16[8];
		__u_net32_t s6_addr32[4];
#endif /* __USE_MISC */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		__uint8_t  __u6_addr8[16];
#undef s6_addr
#define s6_addr      __in6_u.__u6_addr8
#ifdef __USE_MISC
		__u_net16_t __u6_addr16[8];
		__u_net32_t __u6_addr32[4];
#undef s6_addr16
#undef s6_addr32
#define s6_addr16 __in6_u.__u6_addr16
#define s6_addr32 __in6_u.__u6_addr32
#endif /* __USE_MISC */
	} __in6_u;
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};

#ifdef __CRT_HAVE_in6addr_any
#undef in6addr_any
__LIBC struct in6_addr const (in6addr_any); /* :: */
#endif /* __CRT_HAVE_in6addr_any */
#ifdef __CRT_HAVE_in6addr_loopback
#undef in6addr_loopback
__LIBC struct in6_addr const (in6addr_loopback); /* ::1 */
#endif /* __CRT_HAVE_in6addr_loopback */

#define IN6ADDR_ANY_INIT      { { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } } }
#define IN6ADDR_LOOPBACK_INIT { { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 } } }
#define INET_ADDRSTRLEN  16
#define INET6_ADDRSTRLEN 46

/* Structure describing an Internet socket address. */
struct sockaddr_in {
	__SOCKADDR_COMMON(sin_);
	in_port_t      sin_port; /* Port number. */
	struct in_addr sin_addr; /* Internet address. */
	/* Pad to size of `struct sockaddr'. */
	unsigned char sin_zero[sizeof(struct sockaddr) -
	                       (__SOCKADDR_COMMON_SIZE +
	                        sizeof(in_port_t) +
	                        sizeof(struct in_addr))];
};

struct sockaddr_in6 {
	__SOCKADDR_COMMON(sin6_);
	in_port_t       sin6_port;     /* Transport layer port # */
	__u_net32_t     sin6_flowinfo; /* IPv6 flow information */
	struct in6_addr sin6_addr;     /* IPv6 address */
	__u_net32_t     sin6_scope_id; /* IPv6 scope-id */
};

#ifdef __USE_MISC
/* IPv4 multicast request. */
struct ip_mreq {
	struct in_addr imr_multiaddr; /* IP multicast address of group. */
	struct in_addr imr_interface; /* Local IP address of interface. */
};
struct ip_mreq_source {
	struct in_addr imr_multiaddr;  /* IP multicast address of group. */
	struct in_addr imr_interface;  /* IP address of source. */
	struct in_addr imr_sourceaddr; /* IP address of interface. */
};
#endif /* __USE_MISC */

/* IPv6 multicast request. */
struct ipv6_mreq {
	struct in6_addr         ipv6mr_multiaddr; /* IPv6 multicast address of group */
	__STDC_UINT32_AS_SIZE_T ipv6mr_interface; /* local interface */
};

#ifdef __USE_MISC
/* Multicast group request. */
struct group_req {
	uint32_t                gr_interface; /* Interface index. */
	struct sockaddr_storage gr_group;     /* Group address. */
};

struct group_source_req {
	uint32_t                gsr_interface; /* Interface index. */
	struct sockaddr_storage gsr_group;     /* Group address. */
	struct sockaddr_storage gsr_source;    /* Source address. */
};

/* Full-state filter operations. */
struct ip_msfilter {
	struct in_addr imsf_multiaddr; /* IP multicast address of group. */
	struct in_addr imsf_interface; /* Local IP address of interface. */
	uint32_t       imsf_fmode;     /* Filter mode. */
	uint32_t       imsf_numsrc;    /* Number of source addresses. */
	struct in_addr imsf_slist[1];  /* Source addresses. */
};
#define IP_MSFILTER_SIZE(numsrc)  \
	(sizeof(struct ip_msfilter) - \
	 sizeof(struct in_addr) +     \
	 ((numsrc) * sizeof(struct in_addr)))

struct group_filter {
	uint32_t                gf_interface; /* Interface index. */
	struct sockaddr_storage gf_group;     /* Group address. */
	uint32_t                gf_fmode;     /* Filter mode. */
	uint32_t                gf_numsrc;    /* Number of source addresses. */
	struct sockaddr_storage gf_slist[1];  /* Source addresses. */
};
#define GROUP_FILTER_SIZE(numsrc)      \
	(sizeof(struct group_filter) -     \
	 sizeof(struct sockaddr_storage) + \
	 ((numsrc) * sizeof(struct sockaddr_storage)))
#endif /* __USE_MISC */

#ifdef __CRT_HAVE_htons
__CDECLARE(__ATTR_CONST,uint16_t,__NOTHROW_NCX,htons,(uint16_t __hostword),(__hostword))
#elif defined(__CRT_HAVE_ntohs) && defined(__HYBRID_HTOBE_IS_BETOH)
__CREDIRECT(__ATTR_CONST,uint16_t,__NOTHROW_NCX,htons,(uint16_t __hostword),ntohs,(__hostword))
#else /* LIBC: htons */
#include <local/netinet.in/htons.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(htons, __FORCELOCAL __ATTR_CONST uint16_t __NOTHROW_NCX(__LIBCCALL htons)(uint16_t __hostword) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(htons))(__hostword); })
#endif /* htons... */
#ifdef __CRT_HAVE_ntohs
__CDECLARE(__ATTR_CONST,uint16_t,__NOTHROW_NCX,ntohs,(uint16_t __netshort),(__netshort))
#elif defined(__CRT_HAVE_htons) && defined(__HYBRID_HTOBE_IS_BETOH)
__CREDIRECT(__ATTR_CONST,uint16_t,__NOTHROW_NCX,ntohs,(uint16_t __netshort),htons,(__netshort))
#else /* LIBC: ntohs */
#include <local/netinet.in/ntohs.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntohs, __FORCELOCAL __ATTR_CONST uint16_t __NOTHROW_NCX(__LIBCCALL ntohs)(uint16_t __netshort) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntohs))(__netshort); })
#endif /* ntohs... */
#ifdef __CRT_HAVE_htonl
__CDECLARE(__ATTR_CONST,uint32_t,__NOTHROW_NCX,htonl,(uint32_t __hostlong),(__hostlong))
#elif defined(__CRT_HAVE_ntohl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW_NCX,htonl,(uint32_t __hostlong),ntohl,(__hostlong))
#else /* LIBC: htonl */
#include <local/netinet.in/htonl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(htonl, __FORCELOCAL __ATTR_CONST uint32_t __NOTHROW_NCX(__LIBCCALL htonl)(uint32_t __hostlong) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(htonl))(__hostlong); })
#endif /* htonl... */
#ifdef __CRT_HAVE_ntohl
__CDECLARE(__ATTR_CONST,uint32_t,__NOTHROW_NCX,ntohl,(uint32_t __netlong),(__netlong))
#elif defined(__CRT_HAVE_htonl) && defined(__HYBRID_HTOBE_IS_BETOH)
__CREDIRECT(__ATTR_CONST,uint32_t,__NOTHROW_NCX,ntohl,(uint32_t __netlong),htonl,(__netlong))
#else /* LIBC: ntohl */
#include <local/netinet.in/ntohl.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntohl, __FORCELOCAL __ATTR_CONST uint32_t __NOTHROW_NCX(__LIBCCALL ntohl)(uint32_t __netlong) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntohl))(__netlong); })
#endif /* ntohl... */
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#ifdef __CRT_HAVE_htonq
__CDECLARE(__ATTR_CONST,uint64_t,__NOTHROW_NCX,htonq,(uint64_t __hostlong),(__hostlong))
#elif defined(__CRT_HAVE_ntohq) && defined(__HYBRID_HTOBE_IS_BETOH)
__CREDIRECT(__ATTR_CONST,uint64_t,__NOTHROW_NCX,htonq,(uint64_t __hostlong),ntohq,(__hostlong))
#else /* LIBC: htonq */
#include <local/netinet.in/htonq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(htonq, __FORCELOCAL __ATTR_CONST uint64_t __NOTHROW_NCX(__LIBCCALL htonq)(uint64_t __hostlong) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(htonq))(__hostlong); })
#endif /* htonq... */
#ifdef __CRT_HAVE_ntohq
__CDECLARE(__ATTR_CONST,uint64_t,__NOTHROW_NCX,ntohq,(uint64_t __netlong),(__netlong))
#elif defined(__CRT_HAVE_htonq) && defined(__HYBRID_HTOBE_IS_BETOH)
__CREDIRECT(__ATTR_CONST,uint64_t,__NOTHROW_NCX,ntohq,(uint64_t __netlong),htonq,(__netlong))
#else /* LIBC: ntohq */
#include <local/netinet.in/ntohq.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(ntohq, __FORCELOCAL __ATTR_CONST uint64_t __NOTHROW_NCX(__LIBCCALL ntohq)(uint64_t __netlong) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ntohq))(__netlong); })
#endif /* ntohq... */
#endif /* __USE_KOS && __UINT64_TYPE__ */


#ifdef __USE_KOS
#define htons(x) __hybrid_htobe16(x)
#define ntohs(x) __hybrid_betoh16(x)
#define htonl(x) __hybrid_htobe32(x)
#define ntohl(x) __hybrid_betoh32(x)
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#define htonq(x) __hybrid_htobe64(x)
#define ntohq(x) __hybrid_betoh64(x)
#endif /* __USE_KOS && __UINT64_TYPE__ */
#else /* __USE_KOS */
#define htons(x) __CCAST(__uint16_t)__hybrid_htobe16(x)
#define ntohs(x) __CCAST(__uint16_t)__hybrid_betoh16(x)
#define htonl(x) __CCAST(__uint32_t)__hybrid_htobe32(x)
#define ntohl(x) __CCAST(__uint32_t)__hybrid_betoh32(x)
#if defined(__USE_KOS) && defined(__UINT64_TYPE__)
#define htonq(x) __CCAST(__uint64_t)__hybrid_htobe64(x)
#define ntohq(x) __CCAST(__uint64_t)__hybrid_betoh64(x)
#endif /* __USE_KOS && __UINT64_TYPE__ */
#endif /* !__USE_KOS */

#ifndef __NO_XBLOCK
#define IN6_IS_ADDR_UNSPECIFIED(a) __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); __XRETURN __a->s6_addr32[0] == 0 && __a->s6_addr32[1] == 0 && __a->s6_addr32[2] == 0 && __a->s6_addr32[3] == 0; })
#define IN6_IS_ADDR_LOOPBACK(a)    __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); __XRETURN __a->s6_addr32[0] == 0 && __a->s6_addr32[1] == 0 && __a->s6_addr32[2] == 0 && __a->s6_addr32[3] == htonl(1); }))
#define IN6_IS_ADDR_LINKLOCAL(a)   __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); __XRETURN (__a->s6_addr32[0] & htonl(0xffc00000)) == htonl(0xfe800000); })
#define IN6_IS_ADDR_SITELOCAL(a)   __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); __XRETURN (__a->s6_addr32[0] & htonl(0xffc00000)) == htonl(0xfec00000); })
#define IN6_IS_ADDR_V4MAPPED(a)    __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); __XRETURN __a->s6_addr32[0] == 0 && __a->s6_addr32[1] == 0 && __a->s6_addr32[2] == htonl(0xffff); })
#define IN6_IS_ADDR_V4COMPAT(a)    __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); __XRETURN __a->s6_addr32[0] == 0 && __a->s6_addr32[1] == 0 && __a->s6_addr32[2] == 0 && ntohl (__a->s6_addr32[3]) > 1; })
#define IN6_ARE_ADDR_EQUAL(a, b)   __XBLOCK({ struct in6_addr const *__a = (struct in6_addr const *)(a); \
                                              struct in6_addr const *__b = (struct in6_addr const *)(b); \
                                              __XRETURN __a->s6_addr32[0] == __b->s6_addr32[0] && \
                                                        __a->s6_addr32[1] == __b->s6_addr32[1] && \
                                                        __a->s6_addr32[2] == __b->s6_addr32[2] && \
                                                        __a->s6_addr32[3] == __b->s6_addr32[3]; }))
#else /* !__NO_XBLOCK */
#define IN6_IS_ADDR_UNSPECIFIED(a) (((const uint32_t *)(a))[0] == 0 && ((const uint32_t *)(a))[1] == 0 && ((const uint32_t *)(a))[2] == 0 && ((const uint32_t *)(a))[3] == 0)
#define IN6_IS_ADDR_LOOPBACK(a)    (((const uint32_t *)(a))[0] == 0 && ((const uint32_t *)(a))[1] == 0 && ((const uint32_t *)(a))[2] == 0 && ((const uint32_t *)(a))[3] == htonl(1))
#define IN6_IS_ADDR_LINKLOCAL(a)  ((((const uint32_t *)(a))[0] & htonl(0xffc00000)) == htonl(0xfe800000))
#define IN6_IS_ADDR_SITELOCAL(a)  ((((const uint32_t *)(a))[0] & htonl(0xffc00000)) == htonl(0xfec00000))
#define IN6_IS_ADDR_V4MAPPED(a)   ((((const uint32_t *)(a))[0] == 0) && (((const uint32_t *)(a))[1] == 0) && (((const uint32_t *)(a))[2] == htonl(0xffff)))
#define IN6_IS_ADDR_V4COMPAT(a)   ((((const uint32_t *)(a))[0] == 0) && (((const uint32_t *)(a))[1] == 0) && (((const uint32_t *)(a))[2] == 0) && (ntohl (((const uint32_t *)(a))[3]) > 1))
#define IN6_ARE_ADDR_EQUAL(a, b)  ((((const uint32_t *)(a))[0] == ((const uint32_t *)(b))[0]) && \
                                   (((const uint32_t *)(a))[1] == ((const uint32_t *)(b))[1]) && \
                                   (((const uint32_t *)(a))[2] == ((const uint32_t *)(b))[2]) && \
                                   (((const uint32_t *)(a))[3] == ((const uint32_t *)(b))[3]))
#endif /* __NO_XBLOCK */
#define IN6_IS_ADDR_MULTICAST(a)    (((uint8_t const *)(a))[0] == 0xff)

#ifdef __USE_MISC
#ifdef __CRT_HAVE_bindresvport
/* Bind socket to a privileged IP port */
__CDECLARE(,int,__NOTHROW_RPC,bindresvport,(__fd_t __sockfd, struct sockaddr_in *__sock_in),(__sockfd,__sock_in))
#endif /* bindresvport... */
#ifdef __CRT_HAVE_bindresvport6
/* The IPv6 version of this function */
__CDECLARE(,int,__NOTHROW_RPC,bindresvport6,(__fd_t __sockfd, struct sockaddr_in6 *__sock_in),(__sockfd,__sock_in))
#endif /* bindresvport6... */
#endif /* __USE_MISC */

#define IN6_IS_ADDR_MC_NODELOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t const *)(a))[1] & 0xf) == 0x1))
#define IN6_IS_ADDR_MC_LINKLOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t const *)(a))[1] & 0xf) == 0x2))
#define IN6_IS_ADDR_MC_SITELOCAL(a) (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t const *)(a))[1] & 0xf) == 0x5))
#define IN6_IS_ADDR_MC_ORGLOCAL(a)  (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t const *)(a))[1] & 0xf) == 0x8))
#define IN6_IS_ADDR_MC_GLOBAL(a)    (IN6_IS_ADDR_MULTICAST(a) && ((((uint8_t const *)(a))[1] & 0xf) == 0xe))

#ifdef __USE_GNU
struct cmsghdr;

/* IPv6 packet information. */
struct in6_pktinfo {
	struct in6_addr ipi6_addr;    /* src/dst IPv6 address */
	unsigned int    ipi6_ifindex; /* send/recv interface index */
};

/* IPv6 MTU information. */
struct ip6_mtuinfo {
	struct sockaddr_in6 ip6m_addr; /* dst address including zone ID */
	uint32_t            ip6m_mtu;  /* path MTU in host byte order */
};

#ifdef __CRT_HAVE_inet6_option_space
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
__CDECLARE(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_space,(int __nbytes),(__nbytes))
#endif /* inet6_option_space... */
#ifdef __CRT_HAVE_inet6_option_init
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
__CDECLARE(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_init,(void *__bp, struct cmsghdr **__cmsgp, int __type),(__bp,__cmsgp,__type))
#endif /* inet6_option_init... */
#ifdef __CRT_HAVE_inet6_option_append
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
__CDECLARE(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_append,(struct cmsghdr *__cmsg, uint8_t const *__typep, int __multx, int __plusy),(__cmsg,__typep,__multx,__plusy))
#endif /* inet6_option_append... */
#ifdef __CRT_HAVE_inet6_option_alloc
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
__CDECLARE(__ATTR_DEPRECATED_,uint8_t *,__NOTHROW_RPC_KOS,inet6_option_alloc,(struct cmsghdr *__cmsg, int __datalen, int __multx, int __plusy),(__cmsg,__datalen,__multx,__plusy))
#endif /* inet6_option_alloc... */
#ifdef __CRT_HAVE_inet6_option_next
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
__CDECLARE(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_next,(struct cmsghdr const *__cmsg, uint8_t **__tptrp),(__cmsg,__tptrp))
#endif /* inet6_option_next... */
#ifdef __CRT_HAVE_inet6_option_find
/* Obsolete hop-by-hop and Destination Options Processing (RFC 2292) */
__CDECLARE(__ATTR_DEPRECATED_,int,__NOTHROW_RPC_KOS,inet6_option_find,(struct cmsghdr const *__cmsg, uint8_t **__tptrp, int __type),(__cmsg,__tptrp,__type))
#endif /* inet6_option_find... */
#ifdef __CRT_HAVE_inet6_opt_init
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_init,(void *__extbuf, socklen_t __extlen),(__extbuf,__extlen))
#endif /* inet6_opt_init... */
#ifdef __CRT_HAVE_inet6_opt_append
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_append,(void *__extbuf, socklen_t __extlen, int __offset, uint8_t __type, socklen_t __len, uint8_t __align, void **__databufp),(__extbuf,__extlen,__offset,__type,__len,__align,__databufp))
#endif /* inet6_opt_append... */
#ifdef __CRT_HAVE_inet6_opt_finish
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_finish,(void *__extbuf, socklen_t __extlen, int __offset),(__extbuf,__extlen,__offset))
#endif /* inet6_opt_finish... */
#ifdef __CRT_HAVE_inet6_opt_set_val
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_set_val,(void *__databuf, int __offset, void *__val, socklen_t __vallen),(__databuf,__offset,__val,__vallen))
#endif /* inet6_opt_set_val... */
#ifdef __CRT_HAVE_inet6_opt_next
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_next,(void *__extbuf, socklen_t __extlen, int __offset, uint8_t *__typep, socklen_t *__lenp, void **__databufp),(__extbuf,__extlen,__offset,__typep,__lenp,__databufp))
#endif /* inet6_opt_next... */
#ifdef __CRT_HAVE_inet6_opt_find
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_find,(void *__extbuf, socklen_t __extlen, int __offset, uint8_t __type, socklen_t *__lenp, void **__databufp),(__extbuf,__extlen,__offset,__type,__lenp,__databufp))
#endif /* inet6_opt_find... */
#ifdef __CRT_HAVE_inet6_opt_get_val
/* Hop-by-Hop and Destination Options Processing (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_opt_get_val,(void *__databuf, int __offset, void *__val, socklen_t __vallen),(__databuf,__offset,__val,__vallen))
#endif /* inet6_opt_get_val... */
#ifdef __CRT_HAVE_inet6_rth_space
/* Routing Header Option (RFC 3542) */
__CDECLARE(,socklen_t,__NOTHROW_RPC_KOS,inet6_rth_space,(int __type, int __segments),(__type,__segments))
#endif /* inet6_rth_space... */
#ifdef __CRT_HAVE_inet6_rth_init
/* Routing Header Option (RFC 3542) */
__CDECLARE(,void *,__NOTHROW_RPC_KOS,inet6_rth_init,(void *__bp, socklen_t __bp_len, int __type, int __segments),(__bp,__bp_len,__type,__segments))
#endif /* inet6_rth_init... */
#ifdef __CRT_HAVE_inet6_rth_add
/* Routing Header Option (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_rth_add,(void *__bp, struct in6_addr const *__addr),(__bp,__addr))
#endif /* inet6_rth_add... */
#ifdef __CRT_HAVE_inet6_rth_reverse
/* Routing Header Option (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_rth_reverse,(void const *__in, void *__out),(__in,__out))
#endif /* inet6_rth_reverse... */
#ifdef __CRT_HAVE_inet6_rth_segments
/* Routing Header Option (RFC 3542) */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet6_rth_segments,(void const *__bp),(__bp))
#endif /* inet6_rth_segments... */
#ifdef __CRT_HAVE_inet6_rth_getaddr
/* Routing Header Option (RFC 3542) */
__CDECLARE(,struct in6_addr *,__NOTHROW_RPC_KOS,inet6_rth_getaddr,(void const *__bp, int __index),(__bp,__index))
#endif /* inet6_rth_getaddr... */
#ifdef __CRT_HAVE_getipv4sourcefilter
/* Get IPv4 source filter */
__CDECLARE(,int,__NOTHROW_RPC_KOS,getipv4sourcefilter,(__fd_t __sockfd, struct in_addr __interface_addr, struct in_addr __group, uint32_t *__fmode, uint32_t *__numsrc, struct in_addr *__slist),(__sockfd,__interface_addr,__group,__fmode,__numsrc,__slist))
#endif /* getipv4sourcefilter... */
#ifdef __CRT_HAVE_setipv4sourcefilter
/* Set IPv4 source filter */
__CDECLARE(,int,__NOTHROW_RPC_KOS,setipv4sourcefilter,(__fd_t __sockfd, struct in_addr __interface_addr, struct in_addr __group, uint32_t __fmode, uint32_t __numsrc, const struct in_addr *__slist),(__sockfd,__interface_addr,__group,__fmode,__numsrc,__slist))
#endif /* setipv4sourcefilter... */
#ifdef __CRT_HAVE_getsourcefilter
/* Get source filter */
__CDECLARE(,int,__NOTHROW_RPC_KOS,getsourcefilter,(__fd_t __sockfd, uint32_t __interface_addr, struct sockaddr const *__group, socklen_t __grouplen, uint32_t *__fmode, uint32_t *__numsrc, struct sockaddr_storage *__slist),(__sockfd,__interface_addr,__group,__grouplen,__fmode,__numsrc,__slist))
#endif /* getsourcefilter... */
#ifdef __CRT_HAVE_setsourcefilter
/* Set source filter */
__CDECLARE(,int,__NOTHROW_RPC_KOS,setsourcefilter,(__fd_t __sockfd, uint32_t __interface_addr, struct sockaddr const *__group, socklen_t __grouplen, uint32_t __fmode, uint32_t __numsrc, const struct sockaddr_storage *__slist),(__sockfd,__interface_addr,__group,__grouplen,__fmode,__numsrc,__slist))
#endif /* setsourcefilter... */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NETINET_IN_H */
