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
#ifndef _NETINET_IPPROTO_H
#define _NETINET_IPPROTO_H 1

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
#define IPPROTO_IP       0   /* Dummy protocol for TCP. */
#define IPPROTO_HOPOPTS  0   /* IPv6 Hop-by-Hop options. */
#define IPPROTO_ICMP     1   /* Internet Control Message Protocol. */
#define IPPROTO_IGMP     2   /* Internet Group Management Protocol. */
#define IPPROTO_GGP      3   /* Gateway - to - Gateway Protocol RFC 823 */
#define IPPROTO_IPIP     4   /* IPIP tunnels (older KA9Q tunnels use 94). */
#define IPPROTO_ST       5   /* Internet Stream Protocol RFC 1190, RFC 1819 */
#define IPPROTO_TCP      6   /* Transmission Control Protocol. */
#define IPPROTO_CBT      7   /* Core - based trees RFC 2189 */
#define IPPROTO_EGP      8   /* Exterior Gateway Protocol. */
#define IPPROTO_IGP      9   /* Interior Gateway Protocol (any private interior gateway (used by Cisco for their IGRP)) */
#define IPPROTO_BBN_RCC_MON 10 /* BBN RCC Monitoring */
#define IPPROTO_NVP_II   11  /* Network Voice Protocol RFC 741 */
#define IPPROTO_PUP      12  /* PUP protocol. */
#define IPPROTO_ARGUS    13  /* ARGUS */
#define IPPROTO_EMCON    14  /* EMCON */
#define IPPROTO_XNET     15  /* Cross Net Debugger IEN 158 */
#define IPPROTO_CHAOS    16  /* Chaos */
#define IPPROTO_UDP      17  /* User Datagram Protocol. */
#define IPPROTO_MUX      18  /* Multiplexing IEN 90 */
#define IPPROTO_DCN_MEAS 19  /* DCN Measurement Subsystems */
#define IPPROTO_HMP      20  /* Host Monitoring Protocol RFC 869 */
#define IPPROTO_PRM      21  /* Packet Radio Measurement */
#define IPPROTO_IDP      22  /* XNS IDP protocol. */
#define IPPROTO_TRUNK1   23  /* Trunk-1 */
#define IPPROTO_TRUNK2   24  /* Trunk-2 */
#define IPPROTO_LEAF1    25  /* Leaf-1 */
#define IPPROTO_LEAF2    26  /* Leaf-2 */
#define IPPROTO_RDP      27  /* Reliable Data Protocol RFC 908 */
#define IPPROTO_IRTP     28  /* Internet Reliable Transaction Protocol RFC 938 */
#define IPPROTO_TP       29  /* SO Transport Protocol Class 4. */
#define IPPROTO_NETBLT   30  /* Bulk Data Transfer Protocol RFC 998 */
#define IPPROTO_MFE_NSP  31  /* MFE Network Services Protocol */
#define IPPROTO_MERIT_INP 32 /* MERIT Internodal Protocol */
#define IPPROTO_DCCP     33  /* Datagram Congestion Control Protocol. */
#define IPPROTO_3PC      34  /* Third Party Connect Protocol */
#define IPPROTO_IDPR     35  /* Inter-Domain Policy Routing Protocol RFC 1479 */
#define IPPROTO_XTP      36  /* Xpress Transport Protocol */
#define IPPROTO_DDP      37  /* Datagram Delivery Protocol */
#define IPPROTO_IDPR_CMTP 38 /* IDPR Control Message Transport Protocol */
#define IPPROTO_TPPP     39  /* TP++ Transport Protocol */
#define IPPROTO_IL       40  /* IL Transport Protocol */
#define IPPROTO_IPV6     41  /* [IPv6] IPv6 header. */
#define IPPROTO_SDRP     42  /* Source Demand Routing Protocol RFC 1940 */
#define IPPROTO_ROUTING  43  /* [IPv6] IPv6 routing header. */
#define IPPROTO_FRAGMENT 44  /* [IPv6] IPv6 fragmentation header. */
#define IPPROTO_IDRP     45  /* Inter-Domain Routing Protocol */
#define IPPROTO_RSVP     46  /* Reservation Protocol. */
#define IPPROTO_GRE      47  /* General Routing Encapsulation. */
#define IPPROTO_DSR      48  /* Dynamic Source Routing Protocol RFC 4728 */
#define IPPROTO_BNA      49  /* Burroughs Network Architecture */
#define IPPROTO_ESP      50  /* encapsulating security payload. */
#define IPPROTO_AH       51  /* authentication header. */
#define IPPROTO_I_NLSP   52  /* Integrated Net Layer Security Protocol TUBA */
#define IPPROTO_SWIPE    53  /* SwIPe RFC 5237 */
#define IPPROTO_NARP     54  /* NBMA Address Resolution Protocol RFC 1735 */
#define IPPROTO_MOBILE   55  /* IP Mobility (Min Encap) RFC 2004 */
#define IPPROTO_TLSP     56  /* Transport Layer Security Protocol (using Kryptonet key management) */
#define IPPROTO_SKIP     57  /* Simple Key-Management for Internet Protocol RFC 2356 */
#define IPPROTO_ICMPV6   58  /* [IPv6] ICMPv6. */
#define IPPROTO_NONE     59  /* [IPv6] IPv6 no next header. */
#define IPPROTO_DSTOPTS  60  /* [IPv6] IPv6 destination options. */
#define IPPROTO_CFTP     62  /* CFTP */
#define IPPROTO_SAT_EXPAK 64 /* SATNET and Backroom EXPAK */
#define IPPROTO_KRYPTOLAN 65 /* KRYPTOLAN Kryptolan */
#define IPPROTO_RVD      66  /* MIT Remote Virtual Disk Protocol */
#define IPPROTO_IPPC     67  /* Internet Pluribus Packet Core */
#define IPPROTO_SAT_MON  69  /* SATNET Monitoring */
#define IPPROTO_VISA     70  /* VISA Protocol */
#define IPPROTO_IPCU     71  /* Internet Packet Core Utility */
#define IPPROTO_CPNX     72  /* Computer Protocol Network Executive */
#define IPPROTO_CPHB     73  /* Computer Protocol Heart Beat */
#define IPPROTO_WSN      74  /* Wang Span Network */
#define IPPROTO_PVP      75  /* Packet Video Protocol */
#define IPPROTO_BR_SAT_MON 76 /*  Backroom SATNET Monitoring */
#define IPPROTO_SUN_ND   77  /* SUN ND PROTOCOL-Temporary */
#define IPPROTO_WB_MON   78  /* WIDEBAND Monitoring */
#define IPPROTO_WB_EXPAK 79  /* WIDEBAND EXPAK */
#define IPPROTO_ISO_IP   80  /* International Organization for Standardization Internet Protocol */
#define IPPROTO_VMTP     81  /* Versatile Message Transaction Protocol RFC 1045 */
#define IPPROTO_SECURE_VMTP 82 /* Secure Versatile Message Transaction Protocol RFC 1045 */
#define IPPROTO_VINES    83  /* VINES */
#define IPPROTO_TTP      84  /* TTP */
#define IPPROTO_IPTM     84  /* Internet Protocol Traffic Manager */
#define IPPROTO_NSFNET_IGP 85 /* NSFNET-IGP */
#define IPPROTO_DGP      86  /* Dissimilar Gateway Protocol */
#define IPPROTO_TCF      87  /* TCF */
#define IPPROTO_EIGRP    88  /* EIGRP Informational RFC 7868 */
#define IPPROTO_OSPF     89  /* Open Shortest Path First RFC 2328 */
#define IPPROTO_SPRITE_RPC 90 /* Sprite-RPC Sprite RPC Protocol */
#define IPPROTO_LARP     91  /* Locus Address Resolution Protocol */
#define IPPROTO_MTP      92  /* Multicast Transport Protocol. */
#define IPPROTO_AX25     93  /* AX.25 */
#define IPPROTO_BEETPH   94  /* IP option pseudo header for BEET. */
#define IPPROTO_MICP     95  /* Mobile Internetworking Control Protocol */
#define IPPROTO_SCC_SP   96  /* Semaphore Communications Sec. Pro */
#define IPPROTO_ETHERIP  97  /* Ethernet-within-IP Encapsulation RFC 3378 */
#define IPPROTO_ENCAP    98  /* Encapsulation Header. */
#define IPPROTO_GMTP     100 /* GMTP */
#define IPPROTO_IFMP     101 /* Ipsilon Flow Management Protocol */
#define IPPROTO_PNNI     102 /* PNNI over IP */
#define IPPROTO_PIM      103 /* Protocol Independent Multicast. */
#define IPPROTO_ARIS     104 /* IBM's ARIS (Aggregate Route IP Switching) Protocol */
#define IPPROTO_SCPS     105 /* SCPS (Space Communications Protocol Standards) SCPS-TP */
#define IPPROTO_QNX      106 /* QNX */
#define IPPROTO_AN       107 /* A/N Active Networks */
#define IPPROTO_COMP     108 /* Compression Header Protocol. */
#define IPPROTO_SNP      109 /* Sitara Networks Protocol */
#define IPPROTO_COMPAQ_PEER 110 /* Compaq Peer Protocol */
#define IPPROTO_IPXIP    111 /* IPX in IP */
#define IPPROTO_VRRP     112 /* Virtual Router Redundancy Protocol, Common Address Redundancy Protocol (not IANA assigned) VRRP:RFC 3768 */
#define IPPROTO_PGM      113 /* PGM Reliable Transport Protocol RFC 3208 */
#define IPPROTO_ANY0HOP  114 /* Any 0-hop protocol */
#define IPPROTO_L2TP     115 /* Layer Two Tunneling Protocol Version 3 RFC 3931 */
#define IPPROTO_DDX      116 /* D-II Data Exchange (DDX) */
#define IPPROTO_IATP     117 /* Interactive Agent Transfer Protocol */
#define IPPROTO_STP      118 /* Schedule Transfer Protocol */
#define IPPROTO_SRP      119 /* SpectraLink Radio Protocol */
#define IPPROTO_UTI      120 /* Universal Transport Interface Protocol */
#define IPPROTO_SMP      121 /* Simple Message Protocol */
#define IPPROTO_SM       122 /* Simple Multicast Protocol draft-perlman-simple-multicast-03 */
#define IPPROTO_PTP      123 /* Performance Transparency Protocol */
#define IPPROTO_IS2IS4   124 /* Intermediate System to Intermediate System (IS-IS) Protocol over IPv4 RFC 1142 and RFC 1195 */
#define IPPROTO_FIRE     125 /* Flexible Intra-AS Routing Environment */
#define IPPROTO_CRTP     126 /* Combat Radio Transport Protocol */
#define IPPROTO_CRUDP    127 /* Combat Radio User Datagram */
#define IPPROTO_SSCOPMCE 128 /* Service-Specific Connection-Oriented Protocol in a Multilink and Connectionless Environment ITU-T Q.2111 (1999) */
#define IPPROTO_IPLT     129 /* IPLT */
#define IPPROTO_SPS      130 /* Secure Packet Shield */
#define IPPROTO_PIPE     131 /* Private IP Encapsulation within IP Expired I-D draft-petri-mobileip-pipe-00.txt */
#define IPPROTO_SCTP     132 /* Stream Control Transmission Protocol. */
#define IPPROTO_FC       133 /* Fibre Channel */
#define IPPROTO_RSVP_E2E_IGNORE 134 /* Reservation Protocol (RSVP) End-to-End Ignore RFC 3175 */
#define IPPROTO_MH       135 /* [IPv6] IPv6 mobility header. */
#define IPPROTO_UDPLITE  136 /* UDP-Lite protocol. */
#define IPPROTO_MPLS     137 /* MPLS in IP. */
#define IPPROTO_MANET    138 /* MANET Protocols RFC 5498 */
#define IPPROTO_HIP      139 /* Host Identity Protocol RFC 5201 */
#define IPPROTO_SHIM6    140 /* Site Multihoming by IPv6 Intermediation RFC 5533 */
#define IPPROTO_WESP     141 /* Wrapped Encapsulating Security Payload RFC 5840 */
#define IPPROTO_ROHC     142 /* Robust Header Compression RFC 5856 */
#define IPPROTO_LOUSER   253 /* Use for experimentation and testing RFC 3692 */
#define IPPROTO_HIUSER   254 /* Use for experimentation and testing RFC 3692 */
#define IPPROTO_RAW      255 /* Raw IP packets. */
#define IPPROTO_MAX      256 /* WARNING: This  is  actually 1+  the max  possible IPPROTO!
                              * The protocol-field of IP is 1-byte, so the max is 0xff=255 */


#endif /* !_NETINET_IPPROTO_H */
