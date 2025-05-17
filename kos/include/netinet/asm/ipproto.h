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
/*!replace_with_include <netinet/ipproto.h>*/
#ifndef _NETINET_ASM_IPPROTO_H
#define _NETINET_ASM_IPPROTO_H 1

#include <__stdinc.h>

/* Documentation taken from Glibc /usr/include/netinet/in.h and
 * https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers */
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


/* Standard well-defined IP protocols. */
#define __IPPROTO_IP              0   /* Dummy protocol for TCP. */
#define __IPPROTO_HOPOPTS         0   /* IPv6 Hop-by-Hop options. */
#define __IPPROTO_ICMP            1   /* Internet Control Message Protocol. */
#define __IPPROTO_IGMP            2   /* Internet Group Management Protocol. */
#define __IPPROTO_GGP             3   /* Gateway - to - Gateway Protocol RFC 823 */
#define __IPPROTO_IPIP            4   /* IPIP tunnels (older KA9Q tunnels use 94). */
#define __IPPROTO_ST              5   /* Internet Stream Protocol RFC 1190, RFC 1819 */
#define __IPPROTO_TCP             6   /* Transmission Control Protocol. */
#define __IPPROTO_CBT             7   /* Core - based trees RFC 2189 */
#define __IPPROTO_EGP             8   /* Exterior Gateway Protocol. */
#define __IPPROTO_IGP             9   /* Interior Gateway Protocol (any private interior gateway (used by Cisco for their IGRP)) */
#define __IPPROTO_BBN_RCC_MON     10  /* BBN RCC Monitoring */
#define __IPPROTO_NVP_II          11  /* Network Voice Protocol RFC 741 */
#define __IPPROTO_PUP             12  /* PUP protocol. */
#define __IPPROTO_ARGUS           13  /* ARGUS */
#define __IPPROTO_EMCON           14  /* EMCON */
#define __IPPROTO_XNET            15  /* Cross Net Debugger IEN 158 */
#define __IPPROTO_CHAOS           16  /* Chaos */
#define __IPPROTO_UDP             17  /* User Datagram Protocol. */
#define __IPPROTO_MUX             18  /* Multiplexing IEN 90 */
#define __IPPROTO_DCN_MEAS        19  /* DCN Measurement Subsystems */
#define __IPPROTO_HMP             20  /* Host Monitoring Protocol RFC 869 */
#define __IPPROTO_PRM             21  /* Packet Radio Measurement */
#define __IPPROTO_IDP             22  /* XNS IDP protocol. */
#define __IPPROTO_TRUNK1          23  /* Trunk-1 */
#define __IPPROTO_TRUNK2          24  /* Trunk-2 */
#define __IPPROTO_LEAF1           25  /* Leaf-1 */
#define __IPPROTO_LEAF2           26  /* Leaf-2 */
#define __IPPROTO_RDP             27  /* Reliable Data Protocol RFC 908 */
#define __IPPROTO_IRTP            28  /* Internet Reliable Transaction Protocol RFC 938 */
#define __IPPROTO_TP              29  /* SO Transport Protocol Class 4. */
#define __IPPROTO_NETBLT          30  /* Bulk Data Transfer Protocol RFC 998 */
#define __IPPROTO_MFE_NSP         31  /* MFE Network Services Protocol */
#define __IPPROTO_MERIT_INP       32  /* MERIT Internodal Protocol */
#define __IPPROTO_DCCP            33  /* Datagram Congestion Control Protocol. */
#define __IPPROTO_3PC             34  /* Third Party Connect Protocol */
#define __IPPROTO_IDPR            35  /* Inter-Domain Policy Routing Protocol RFC 1479 */
#define __IPPROTO_XTP             36  /* Xpress Transport Protocol */
#define __IPPROTO_DDP             37  /* Datagram Delivery Protocol */
#define __IPPROTO_IDPR_CMTP       38  /* IDPR Control Message Transport Protocol */
#define __IPPROTO_TPPP            39  /* TP++ Transport Protocol */
#define __IPPROTO_IL              40  /* IL Transport Protocol */
#define __IPPROTO_IPV6            41  /* [IPv6] IPv6 header. */
#define __IPPROTO_SDRP            42  /* Source Demand Routing Protocol RFC 1940 */
#define __IPPROTO_ROUTING         43  /* [IPv6] IPv6 routing header. */
#define __IPPROTO_FRAGMENT        44  /* [IPv6] IPv6 fragmentation header. */
#define __IPPROTO_IDRP            45  /* Inter-Domain Routing Protocol */
#define __IPPROTO_RSVP            46  /* Reservation Protocol. */
#define __IPPROTO_GRE             47  /* General Routing Encapsulation. */
#define __IPPROTO_DSR             48  /* Dynamic Source Routing Protocol RFC 4728 */
#define __IPPROTO_BNA             49  /* Burroughs Network Architecture */
#define __IPPROTO_ESP             50  /* encapsulating security payload. */
#define __IPPROTO_AH              51  /* authentication header. */
#define __IPPROTO_I_NLSP          52  /* Integrated Net Layer Security Protocol TUBA */
#define __IPPROTO_SWIPE           53  /* SwIPe RFC 5237 */
#define __IPPROTO_NARP            54  /* NBMA Address Resolution Protocol RFC 1735 */
#define __IPPROTO_MOBILE          55  /* IP Mobility (Min Encap) RFC 2004 */
#define __IPPROTO_TLSP            56  /* Transport Layer Security Protocol (using Kryptonet key management) */
#define __IPPROTO_SKIP            57  /* Simple Key-Management for Internet Protocol RFC 2356 */
#define __IPPROTO_ICMPV6          58  /* [IPv6] ICMPv6. */
#define __IPPROTO_NONE            59  /* [IPv6] IPv6 no next header. */
#define __IPPROTO_DSTOPTS         60  /* [IPv6] IPv6 destination options. */
#define __IPPROTO_CFTP            62  /* CFTP */
#define __IPPROTO_SAT_EXPAK       64  /* SATNET and Backroom EXPAK */
#define __IPPROTO_KRYPTOLAN       65  /* KRYPTOLAN Kryptolan */
#define __IPPROTO_RVD             66  /* MIT Remote Virtual Disk Protocol */
#define __IPPROTO_IPPC            67  /* Internet Pluribus Packet Core */
#define __IPPROTO_SAT_MON         69  /* SATNET Monitoring */
#define __IPPROTO_VISA            70  /* VISA Protocol */
#define __IPPROTO_IPCU            71  /* Internet Packet Core Utility */
#define __IPPROTO_CPNX            72  /* Computer Protocol Network Executive */
#define __IPPROTO_CPHB            73  /* Computer Protocol Heart Beat */
#define __IPPROTO_WSN             74  /* Wang Span Network */
#define __IPPROTO_PVP             75  /* Packet Video Protocol */
#define __IPPROTO_BR_SAT_MON      76  /*  Backroom SATNET Monitoring */
#define __IPPROTO_SUN_ND          77  /* SUN ND PROTOCOL-Temporary */
#define __IPPROTO_WB_MON          78  /* WIDEBAND Monitoring */
#define __IPPROTO_WB_EXPAK        79  /* WIDEBAND EXPAK */
#define __IPPROTO_ISO_IP          80  /* International Organization for Standardization Internet Protocol */
#define __IPPROTO_VMTP            81  /* Versatile Message Transaction Protocol RFC 1045 */
#define __IPPROTO_SECURE_VMTP     82  /* Secure Versatile Message Transaction Protocol RFC 1045 */
#define __IPPROTO_VINES           83  /* VINES */
#define __IPPROTO_TTP             84  /* TTP */
#define __IPPROTO_IPTM            84  /* Internet Protocol Traffic Manager */
#define __IPPROTO_NSFNET_IGP      85  /* NSFNET-IGP */
#define __IPPROTO_DGP             86  /* Dissimilar Gateway Protocol */
#define __IPPROTO_TCF             87  /* TCF */
#define __IPPROTO_EIGRP           88  /* EIGRP Informational RFC 7868 */
#define __IPPROTO_OSPF            89  /* Open Shortest Path First RFC 2328 */
#define __IPPROTO_SPRITE_RPC      90  /* Sprite-RPC Sprite RPC Protocol */
#define __IPPROTO_LARP            91  /* Locus Address Resolution Protocol */
#define __IPPROTO_MTP             92  /* Multicast Transport Protocol. */
#define __IPPROTO_AX25            93  /* AX.25 */
#define __IPPROTO_BEETPH          94  /* IP option pseudo header for BEET. */
#define __IPPROTO_MICP            95  /* Mobile Internetworking Control Protocol */
#define __IPPROTO_SCC_SP          96  /* Semaphore Communications Sec. Pro */
#define __IPPROTO_ETHERIP         97  /* Ethernet-within-IP Encapsulation RFC 3378 */
#define __IPPROTO_ENCAP           98  /* Encapsulation Header. */
#define __IPPROTO_GMTP            100 /* GMTP */
#define __IPPROTO_IFMP            101 /* Ipsilon Flow Management Protocol */
#define __IPPROTO_PNNI            102 /* PNNI over IP */
#define __IPPROTO_PIM             103 /* Protocol Independent Multicast. */
#define __IPPROTO_ARIS            104 /* IBM's ARIS (Aggregate Route IP Switching) Protocol */
#define __IPPROTO_SCPS            105 /* SCPS (Space Communications Protocol Standards) SCPS-TP */
#define __IPPROTO_QNX             106 /* QNX */
#define __IPPROTO_AN              107 /* A/N Active Networks */
#define __IPPROTO_COMP            108 /* Compression Header Protocol. */
#define __IPPROTO_SNP             109 /* Sitara Networks Protocol */
#define __IPPROTO_COMPAQ_PEER     110 /* Compaq Peer Protocol */
#define __IPPROTO_IPXIP           111 /* IPX in IP */
#define __IPPROTO_VRRP            112 /* Virtual Router Redundancy Protocol, Common Address Redundancy Protocol (not IANA assigned) VRRP:RFC 3768 */
#define __IPPROTO_PGM             113 /* PGM Reliable Transport Protocol RFC 3208 */
#define __IPPROTO_ANY0HOP         114 /* Any 0-hop protocol */
#define __IPPROTO_L2TP            115 /* Layer Two Tunneling Protocol Version 3 RFC 3931 */
#define __IPPROTO_DDX             116 /* D-II Data Exchange (DDX) */
#define __IPPROTO_IATP            117 /* Interactive Agent Transfer Protocol */
#define __IPPROTO_STP             118 /* Schedule Transfer Protocol */
#define __IPPROTO_SRP             119 /* SpectraLink Radio Protocol */
#define __IPPROTO_UTI             120 /* Universal Transport Interface Protocol */
#define __IPPROTO_SMP             121 /* Simple Message Protocol */
#define __IPPROTO_SM              122 /* Simple Multicast Protocol draft-perlman-simple-multicast-03 */
#define __IPPROTO_PTP             123 /* Performance Transparency Protocol */
#define __IPPROTO_IS2IS4          124 /* Intermediate System to Intermediate System (IS-IS) Protocol over IPv4 RFC 1142 and RFC 1195 */
#define __IPPROTO_FIRE            125 /* Flexible Intra-AS Routing Environment */
#define __IPPROTO_CRTP            126 /* Combat Radio Transport Protocol */
#define __IPPROTO_CRUDP           127 /* Combat Radio User Datagram */
#define __IPPROTO_SSCOPMCE        128 /* Service-Specific Connection-Oriented Protocol in a Multilink and Connectionless Environment ITU-T Q.2111 (1999) */
#define __IPPROTO_IPLT            129 /* IPLT */
#define __IPPROTO_SPS             130 /* Secure Packet Shield */
#define __IPPROTO_PIPE            131 /* Private IP Encapsulation within IP Expired I-D draft-petri-mobileip-pipe-00.txt */
#define __IPPROTO_SCTP            132 /* Stream Control Transmission Protocol. */
#define __IPPROTO_FC              133 /* Fibre Channel */
#define __IPPROTO_RSVP_E2E_IGNORE 134 /* Reservation Protocol (RSVP) End-to-End Ignore RFC 3175 */
#define __IPPROTO_MH              135 /* [IPv6] IPv6 mobility header. */
#define __IPPROTO_UDPLITE         136 /* UDP-Lite protocol. */
#define __IPPROTO_MPLS            137 /* MPLS in IP. */
#define __IPPROTO_MANET           138 /* MANET Protocols RFC 5498 */
#define __IPPROTO_HIP             139 /* Host Identity Protocol RFC 5201 */
#define __IPPROTO_SHIM6           140 /* Site Multihoming by IPv6 Intermediation RFC 5533 */
#define __IPPROTO_WESP            141 /* Wrapped Encapsulating Security Payload RFC 5840 */
#define __IPPROTO_ROHC            142 /* Robust Header Compression RFC 5856 */
#define __IPPROTO_LOUSER          253 /* Use for experimentation and testing RFC 3692 */
#define __IPPROTO_HIUSER          254 /* Use for experimentation and testing RFC 3692 */
#define __IPPROTO_RAW             255 /* Raw IP packets. */
#define __IPPROTO_MAX             256 /* WARNING: This  is  actually 1+  the max  possible IPPROTO!
                                       * The protocol-field of IP is 1-byte, so the max is 0xff=255 */

#endif /* !_NETINET_ASM_IPPROTO_H */
