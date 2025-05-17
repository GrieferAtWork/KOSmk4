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
#ifndef _NETINET_IPPROTO_H
#define _NETINET_IPPROTO_H 1

#include <__stdinc.h>

#include <netinet/asm/ipproto.h>

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
#if !defined(IPPROTO_IP) && defined(__IPPROTO_IP)
#define IPPROTO_IP              __IPPROTO_IP              /* Dummy protocol for TCP. */
#endif /* !IPPROTO_IP && __IPPROTO_IP */
#if !defined(IPPROTO_HOPOPTS) && defined(__IPPROTO_HOPOPTS)
#define IPPROTO_HOPOPTS         __IPPROTO_HOPOPTS         /* IPv6 Hop-by-Hop options. */
#endif /* !IPPROTO_HOPOPTS && __IPPROTO_HOPOPTS */
#if !defined(IPPROTO_ICMP) && defined(__IPPROTO_ICMP)
#define IPPROTO_ICMP            __IPPROTO_ICMP            /* Internet Control Message Protocol. */
#endif /* !IPPROTO_ICMP && __IPPROTO_ICMP */
#if !defined(IPPROTO_IGMP) && defined(__IPPROTO_IGMP)
#define IPPROTO_IGMP            __IPPROTO_IGMP            /* Internet Group Management Protocol. */
#endif /* !IPPROTO_IGMP && __IPPROTO_IGMP */
#if !defined(IPPROTO_GGP) && defined(__IPPROTO_GGP)
#define IPPROTO_GGP             __IPPROTO_GGP             /* Gateway - to - Gateway Protocol RFC 823 */
#endif /* !IPPROTO_GGP && __IPPROTO_GGP */
#if !defined(IPPROTO_IPIP) && defined(__IPPROTO_IPIP)
#define IPPROTO_IPIP            __IPPROTO_IPIP            /* IPIP tunnels (older KA9Q tunnels use 94). */
#endif /* !IPPROTO_IPIP && __IPPROTO_IPIP */
#if !defined(IPPROTO_ST) && defined(__IPPROTO_ST)
#define IPPROTO_ST              __IPPROTO_ST              /* Internet Stream Protocol RFC 1190, RFC 1819 */
#endif /* !IPPROTO_ST && __IPPROTO_ST */
#if !defined(IPPROTO_TCP) && defined(__IPPROTO_TCP)
#define IPPROTO_TCP             __IPPROTO_TCP             /* Transmission Control Protocol. */
#endif /* !IPPROTO_TCP && __IPPROTO_TCP */
#if !defined(IPPROTO_CBT) && defined(__IPPROTO_CBT)
#define IPPROTO_CBT             __IPPROTO_CBT             /* Core - based trees RFC 2189 */
#endif /* !IPPROTO_CBT && __IPPROTO_CBT */
#if !defined(IPPROTO_EGP) && defined(__IPPROTO_EGP)
#define IPPROTO_EGP             __IPPROTO_EGP             /* Exterior Gateway Protocol. */
#endif /* !IPPROTO_EGP && __IPPROTO_EGP */
#if !defined(IPPROTO_IGP) && defined(__IPPROTO_IGP)
#define IPPROTO_IGP             __IPPROTO_IGP             /* Interior Gateway Protocol (any private interior gateway (used by Cisco for their IGRP)) */
#endif /* !IPPROTO_IGP && __IPPROTO_IGP */
#if !defined(IPPROTO_BBN_RCC_MON) && defined(__IPPROTO_BBN_RCC_MON)
#define IPPROTO_BBN_RCC_MON     __IPPROTO_BBN_RCC_MON     /* BBN RCC Monitoring */
#endif /* !IPPROTO_BBN_RCC_MON && __IPPROTO_BBN_RCC_MON */
#if !defined(IPPROTO_NVP_II) && defined(__IPPROTO_NVP_II)
#define IPPROTO_NVP_II          __IPPROTO_NVP_II          /* Network Voice Protocol RFC 741 */
#endif /* !IPPROTO_NVP_II && __IPPROTO_NVP_II */
#if !defined(IPPROTO_PUP) && defined(__IPPROTO_PUP)
#define IPPROTO_PUP             __IPPROTO_PUP             /* PUP protocol. */
#endif /* !IPPROTO_PUP && __IPPROTO_PUP */
#if !defined(IPPROTO_ARGUS) && defined(__IPPROTO_ARGUS)
#define IPPROTO_ARGUS           __IPPROTO_ARGUS           /* ARGUS */
#endif /* !IPPROTO_ARGUS && __IPPROTO_ARGUS */
#if !defined(IPPROTO_EMCON) && defined(__IPPROTO_EMCON)
#define IPPROTO_EMCON           __IPPROTO_EMCON           /* EMCON */
#endif /* !IPPROTO_EMCON && __IPPROTO_EMCON */
#if !defined(IPPROTO_XNET) && defined(__IPPROTO_XNET)
#define IPPROTO_XNET            __IPPROTO_XNET            /* Cross Net Debugger IEN 158 */
#endif /* !IPPROTO_XNET && __IPPROTO_XNET */
#if !defined(IPPROTO_CHAOS) && defined(__IPPROTO_CHAOS)
#define IPPROTO_CHAOS           __IPPROTO_CHAOS           /* Chaos */
#endif /* !IPPROTO_CHAOS && __IPPROTO_CHAOS */
#if !defined(IPPROTO_UDP) && defined(__IPPROTO_UDP)
#define IPPROTO_UDP             __IPPROTO_UDP             /* User Datagram Protocol. */
#endif /* !IPPROTO_UDP && __IPPROTO_UDP */
#if !defined(IPPROTO_MUX) && defined(__IPPROTO_MUX)
#define IPPROTO_MUX             __IPPROTO_MUX             /* Multiplexing IEN 90 */
#endif /* !IPPROTO_MUX && __IPPROTO_MUX */
#if !defined(IPPROTO_DCN_MEAS) && defined(__IPPROTO_DCN_MEAS)
#define IPPROTO_DCN_MEAS        __IPPROTO_DCN_MEAS        /* DCN Measurement Subsystems */
#endif /* !IPPROTO_DCN_MEAS && __IPPROTO_DCN_MEAS */
#if !defined(IPPROTO_HMP) && defined(__IPPROTO_HMP)
#define IPPROTO_HMP             __IPPROTO_HMP             /* Host Monitoring Protocol RFC 869 */
#endif /* !IPPROTO_HMP && __IPPROTO_HMP */
#if !defined(IPPROTO_PRM) && defined(__IPPROTO_PRM)
#define IPPROTO_PRM             __IPPROTO_PRM             /* Packet Radio Measurement */
#endif /* !IPPROTO_PRM && __IPPROTO_PRM */
#if !defined(IPPROTO_IDP) && defined(__IPPROTO_IDP)
#define IPPROTO_IDP             __IPPROTO_IDP             /* XNS IDP protocol. */
#endif /* !IPPROTO_IDP && __IPPROTO_IDP */
#if !defined(IPPROTO_TRUNK1) && defined(__IPPROTO_TRUNK1)
#define IPPROTO_TRUNK1          __IPPROTO_TRUNK1          /* Trunk-1 */
#endif /* !IPPROTO_TRUNK1 && __IPPROTO_TRUNK1 */
#if !defined(IPPROTO_TRUNK2) && defined(__IPPROTO_TRUNK2)
#define IPPROTO_TRUNK2          __IPPROTO_TRUNK2          /* Trunk-2 */
#endif /* !IPPROTO_TRUNK2 && __IPPROTO_TRUNK2 */
#if !defined(IPPROTO_LEAF1) && defined(__IPPROTO_LEAF1)
#define IPPROTO_LEAF1           __IPPROTO_LEAF1           /* Leaf-1 */
#endif /* !IPPROTO_LEAF1 && __IPPROTO_LEAF1 */
#if !defined(IPPROTO_LEAF2) && defined(__IPPROTO_LEAF2)
#define IPPROTO_LEAF2           __IPPROTO_LEAF2           /* Leaf-2 */
#endif /* !IPPROTO_LEAF2 && __IPPROTO_LEAF2 */
#if !defined(IPPROTO_RDP) && defined(__IPPROTO_RDP)
#define IPPROTO_RDP             __IPPROTO_RDP             /* Reliable Data Protocol RFC 908 */
#endif /* !IPPROTO_RDP && __IPPROTO_RDP */
#if !defined(IPPROTO_IRTP) && defined(__IPPROTO_IRTP)
#define IPPROTO_IRTP            __IPPROTO_IRTP            /* Internet Reliable Transaction Protocol RFC 938 */
#endif /* !IPPROTO_IRTP && __IPPROTO_IRTP */
#if !defined(IPPROTO_TP) && defined(__IPPROTO_TP)
#define IPPROTO_TP              __IPPROTO_TP              /* SO Transport Protocol Class 4. */
#endif /* !IPPROTO_TP && __IPPROTO_TP */
#if !defined(IPPROTO_NETBLT) && defined(__IPPROTO_NETBLT)
#define IPPROTO_NETBLT          __IPPROTO_NETBLT          /* Bulk Data Transfer Protocol RFC 998 */
#endif /* !IPPROTO_NETBLT && __IPPROTO_NETBLT */
#if !defined(IPPROTO_MFE_NSP) && defined(__IPPROTO_MFE_NSP)
#define IPPROTO_MFE_NSP         __IPPROTO_MFE_NSP         /* MFE Network Services Protocol */
#endif /* !IPPROTO_MFE_NSP && __IPPROTO_MFE_NSP */
#if !defined(IPPROTO_MERIT_INP) && defined(__IPPROTO_MERIT_INP)
#define IPPROTO_MERIT_INP       __IPPROTO_MERIT_INP       /* MERIT Internodal Protocol */
#endif /* !IPPROTO_MERIT_INP && __IPPROTO_MERIT_INP */
#if !defined(IPPROTO_DCCP) && defined(__IPPROTO_DCCP)
#define IPPROTO_DCCP            __IPPROTO_DCCP            /* Datagram Congestion Control Protocol. */
#endif /* !IPPROTO_DCCP && __IPPROTO_DCCP */
#if !defined(IPPROTO_3PC) && defined(__IPPROTO_3PC)
#define IPPROTO_3PC             __IPPROTO_3PC             /* Third Party Connect Protocol */
#endif /* !IPPROTO_3PC && __IPPROTO_3PC */
#if !defined(IPPROTO_IDPR) && defined(__IPPROTO_IDPR)
#define IPPROTO_IDPR            __IPPROTO_IDPR            /* Inter-Domain Policy Routing Protocol RFC 1479 */
#endif /* !IPPROTO_IDPR && __IPPROTO_IDPR */
#if !defined(IPPROTO_XTP) && defined(__IPPROTO_XTP)
#define IPPROTO_XTP             __IPPROTO_XTP             /* Xpress Transport Protocol */
#endif /* !IPPROTO_XTP && __IPPROTO_XTP */
#if !defined(IPPROTO_DDP) && defined(__IPPROTO_DDP)
#define IPPROTO_DDP             __IPPROTO_DDP             /* Datagram Delivery Protocol */
#endif /* !IPPROTO_DDP && __IPPROTO_DDP */
#if !defined(IPPROTO_IDPR_CMTP) && defined(__IPPROTO_IDPR_CMTP)
#define IPPROTO_IDPR_CMTP       __IPPROTO_IDPR_CMTP       /* IDPR Control Message Transport Protocol */
#endif /* !IPPROTO_IDPR_CMTP && __IPPROTO_IDPR_CMTP */
#if !defined(IPPROTO_TPPP) && defined(__IPPROTO_TPPP)
#define IPPROTO_TPPP            __IPPROTO_TPPP            /* TP++ Transport Protocol */
#endif /* !IPPROTO_TPPP && __IPPROTO_TPPP */
#if !defined(IPPROTO_IL) && defined(__IPPROTO_IL)
#define IPPROTO_IL              __IPPROTO_IL              /* IL Transport Protocol */
#endif /* !IPPROTO_IL && __IPPROTO_IL */
#if !defined(IPPROTO_IPV6) && defined(__IPPROTO_IPV6)
#define IPPROTO_IPV6            __IPPROTO_IPV6            /* [IPv6] IPv6 header. */
#endif /* !IPPROTO_IPV6 && __IPPROTO_IPV6 */
#if !defined(IPPROTO_SDRP) && defined(__IPPROTO_SDRP)
#define IPPROTO_SDRP            __IPPROTO_SDRP            /* Source Demand Routing Protocol RFC 1940 */
#endif /* !IPPROTO_SDRP && __IPPROTO_SDRP */
#if !defined(IPPROTO_ROUTING) && defined(__IPPROTO_ROUTING)
#define IPPROTO_ROUTING         __IPPROTO_ROUTING         /* [IPv6] IPv6 routing header. */
#endif /* !IPPROTO_ROUTING && __IPPROTO_ROUTING */
#if !defined(IPPROTO_FRAGMENT) && defined(__IPPROTO_FRAGMENT)
#define IPPROTO_FRAGMENT        __IPPROTO_FRAGMENT        /* [IPv6] IPv6 fragmentation header. */
#endif /* !IPPROTO_FRAGMENT && __IPPROTO_FRAGMENT */
#if !defined(IPPROTO_IDRP) && defined(__IPPROTO_IDRP)
#define IPPROTO_IDRP            __IPPROTO_IDRP            /* Inter-Domain Routing Protocol */
#endif /* !IPPROTO_IDRP && __IPPROTO_IDRP */
#if !defined(IPPROTO_RSVP) && defined(__IPPROTO_RSVP)
#define IPPROTO_RSVP            __IPPROTO_RSVP            /* Reservation Protocol. */
#endif /* !IPPROTO_RSVP && __IPPROTO_RSVP */
#if !defined(IPPROTO_GRE) && defined(__IPPROTO_GRE)
#define IPPROTO_GRE             __IPPROTO_GRE             /* General Routing Encapsulation. */
#endif /* !IPPROTO_GRE && __IPPROTO_GRE */
#if !defined(IPPROTO_DSR) && defined(__IPPROTO_DSR)
#define IPPROTO_DSR             __IPPROTO_DSR             /* Dynamic Source Routing Protocol RFC 4728 */
#endif /* !IPPROTO_DSR && __IPPROTO_DSR */
#if !defined(IPPROTO_BNA) && defined(__IPPROTO_BNA)
#define IPPROTO_BNA             __IPPROTO_BNA             /* Burroughs Network Architecture */
#endif /* !IPPROTO_BNA && __IPPROTO_BNA */
#if !defined(IPPROTO_ESP) && defined(__IPPROTO_ESP)
#define IPPROTO_ESP             __IPPROTO_ESP             /* encapsulating security payload. */
#endif /* !IPPROTO_ESP && __IPPROTO_ESP */
#if !defined(IPPROTO_AH) && defined(__IPPROTO_AH)
#define IPPROTO_AH              __IPPROTO_AH              /* authentication header. */
#endif /* !IPPROTO_AH && __IPPROTO_AH */
#if !defined(IPPROTO_I_NLSP) && defined(__IPPROTO_I_NLSP)
#define IPPROTO_I_NLSP          __IPPROTO_I_NLSP          /* Integrated Net Layer Security Protocol TUBA */
#endif /* !IPPROTO_I_NLSP && __IPPROTO_I_NLSP */
#if !defined(IPPROTO_SWIPE) && defined(__IPPROTO_SWIPE)
#define IPPROTO_SWIPE           __IPPROTO_SWIPE           /* SwIPe RFC 5237 */
#endif /* !IPPROTO_SWIPE && __IPPROTO_SWIPE */
#if !defined(IPPROTO_NARP) && defined(__IPPROTO_NARP)
#define IPPROTO_NARP            __IPPROTO_NARP            /* NBMA Address Resolution Protocol RFC 1735 */
#endif /* !IPPROTO_NARP && __IPPROTO_NARP */
#if !defined(IPPROTO_MOBILE) && defined(__IPPROTO_MOBILE)
#define IPPROTO_MOBILE          __IPPROTO_MOBILE          /* IP Mobility (Min Encap) RFC 2004 */
#endif /* !IPPROTO_MOBILE && __IPPROTO_MOBILE */
#if !defined(IPPROTO_TLSP) && defined(__IPPROTO_TLSP)
#define IPPROTO_TLSP            __IPPROTO_TLSP            /* Transport Layer Security Protocol (using Kryptonet key management) */
#endif /* !IPPROTO_TLSP && __IPPROTO_TLSP */
#if !defined(IPPROTO_SKIP) && defined(__IPPROTO_SKIP)
#define IPPROTO_SKIP            __IPPROTO_SKIP            /* Simple Key-Management for Internet Protocol RFC 2356 */
#endif /* !IPPROTO_SKIP && __IPPROTO_SKIP */
#if !defined(IPPROTO_ICMPV6) && defined(__IPPROTO_ICMPV6)
#define IPPROTO_ICMPV6          __IPPROTO_ICMPV6          /* [IPv6] ICMPv6. */
#endif /* !IPPROTO_ICMPV6 && __IPPROTO_ICMPV6 */
#if !defined(IPPROTO_NONE) && defined(__IPPROTO_NONE)
#define IPPROTO_NONE            __IPPROTO_NONE            /* [IPv6] IPv6 no next header. */
#endif /* !IPPROTO_NONE && __IPPROTO_NONE */
#if !defined(IPPROTO_DSTOPTS) && defined(__IPPROTO_DSTOPTS)
#define IPPROTO_DSTOPTS         __IPPROTO_DSTOPTS         /* [IPv6] IPv6 destination options. */
#endif /* !IPPROTO_DSTOPTS && __IPPROTO_DSTOPTS */
#if !defined(IPPROTO_CFTP) && defined(__IPPROTO_CFTP)
#define IPPROTO_CFTP            __IPPROTO_CFTP            /* CFTP */
#endif /* !IPPROTO_CFTP && __IPPROTO_CFTP */
#if !defined(IPPROTO_SAT_EXPAK) && defined(__IPPROTO_SAT_EXPAK)
#define IPPROTO_SAT_EXPAK       __IPPROTO_SAT_EXPAK       /* SATNET and Backroom EXPAK */
#endif /* !IPPROTO_SAT_EXPAK && __IPPROTO_SAT_EXPAK */
#if !defined(IPPROTO_KRYPTOLAN) && defined(__IPPROTO_KRYPTOLAN)
#define IPPROTO_KRYPTOLAN       __IPPROTO_KRYPTOLAN       /* KRYPTOLAN Kryptolan */
#endif /* !IPPROTO_KRYPTOLAN && __IPPROTO_KRYPTOLAN */
#if !defined(IPPROTO_RVD) && defined(__IPPROTO_RVD)
#define IPPROTO_RVD             __IPPROTO_RVD             /* MIT Remote Virtual Disk Protocol */
#endif /* !IPPROTO_RVD && __IPPROTO_RVD */
#if !defined(IPPROTO_IPPC) && defined(__IPPROTO_IPPC)
#define IPPROTO_IPPC            __IPPROTO_IPPC            /* Internet Pluribus Packet Core */
#endif /* !IPPROTO_IPPC && __IPPROTO_IPPC */
#if !defined(IPPROTO_SAT_MON) && defined(__IPPROTO_SAT_MON)
#define IPPROTO_SAT_MON         __IPPROTO_SAT_MON         /* SATNET Monitoring */
#endif /* !IPPROTO_SAT_MON && __IPPROTO_SAT_MON */
#if !defined(IPPROTO_VISA) && defined(__IPPROTO_VISA)
#define IPPROTO_VISA            __IPPROTO_VISA            /* VISA Protocol */
#endif /* !IPPROTO_VISA && __IPPROTO_VISA */
#if !defined(IPPROTO_IPCU) && defined(__IPPROTO_IPCU)
#define IPPROTO_IPCU            __IPPROTO_IPCU            /* Internet Packet Core Utility */
#endif /* !IPPROTO_IPCU && __IPPROTO_IPCU */
#if !defined(IPPROTO_CPNX) && defined(__IPPROTO_CPNX)
#define IPPROTO_CPNX            __IPPROTO_CPNX            /* Computer Protocol Network Executive */
#endif /* !IPPROTO_CPNX && __IPPROTO_CPNX */
#if !defined(IPPROTO_CPHB) && defined(__IPPROTO_CPHB)
#define IPPROTO_CPHB            __IPPROTO_CPHB            /* Computer Protocol Heart Beat */
#endif /* !IPPROTO_CPHB && __IPPROTO_CPHB */
#if !defined(IPPROTO_WSN) && defined(__IPPROTO_WSN)
#define IPPROTO_WSN             __IPPROTO_WSN             /* Wang Span Network */
#endif /* !IPPROTO_WSN && __IPPROTO_WSN */
#if !defined(IPPROTO_PVP) && defined(__IPPROTO_PVP)
#define IPPROTO_PVP             __IPPROTO_PVP             /* Packet Video Protocol */
#endif /* !IPPROTO_PVP && __IPPROTO_PVP */
#if !defined(IPPROTO_BR_SAT_MON) && defined(__IPPROTO_BR_SAT_MON)
#define IPPROTO_BR_SAT_MON      __IPPROTO_BR_SAT_MON      /*  Backroom SATNET Monitoring */
#endif /* !IPPROTO_BR_SAT_MON && __IPPROTO_BR_SAT_MON */
#if !defined(IPPROTO_SUN_ND) && defined(__IPPROTO_SUN_ND)
#define IPPROTO_SUN_ND          __IPPROTO_SUN_ND          /* SUN ND PROTOCOL-Temporary */
#endif /* !IPPROTO_SUN_ND && __IPPROTO_SUN_ND */
#if !defined(IPPROTO_WB_MON) && defined(__IPPROTO_WB_MON)
#define IPPROTO_WB_MON          __IPPROTO_WB_MON          /* WIDEBAND Monitoring */
#endif /* !IPPROTO_WB_MON && __IPPROTO_WB_MON */
#if !defined(IPPROTO_WB_EXPAK) && defined(__IPPROTO_WB_EXPAK)
#define IPPROTO_WB_EXPAK        __IPPROTO_WB_EXPAK        /* WIDEBAND EXPAK */
#endif /* !IPPROTO_WB_EXPAK && __IPPROTO_WB_EXPAK */
#if !defined(IPPROTO_ISO_IP) && defined(__IPPROTO_ISO_IP)
#define IPPROTO_ISO_IP          __IPPROTO_ISO_IP          /* International Organization for Standardization Internet Protocol */
#endif /* !IPPROTO_ISO_IP && __IPPROTO_ISO_IP */
#if !defined(IPPROTO_VMTP) && defined(__IPPROTO_VMTP)
#define IPPROTO_VMTP            __IPPROTO_VMTP            /* Versatile Message Transaction Protocol RFC 1045 */
#endif /* !IPPROTO_VMTP && __IPPROTO_VMTP */
#if !defined(IPPROTO_SECURE_VMTP) && defined(__IPPROTO_SECURE_VMTP)
#define IPPROTO_SECURE_VMTP     __IPPROTO_SECURE_VMTP     /* Secure Versatile Message Transaction Protocol RFC 1045 */
#endif /* !IPPROTO_SECURE_VMTP && __IPPROTO_SECURE_VMTP */
#if !defined(IPPROTO_VINES) && defined(__IPPROTO_VINES)
#define IPPROTO_VINES           __IPPROTO_VINES           /* VINES */
#endif /* !IPPROTO_VINES && __IPPROTO_VINES */
#if !defined(IPPROTO_TTP) && defined(__IPPROTO_TTP)
#define IPPROTO_TTP             __IPPROTO_TTP             /* TTP */
#endif /* !IPPROTO_TTP && __IPPROTO_TTP */
#if !defined(IPPROTO_IPTM) && defined(__IPPROTO_IPTM)
#define IPPROTO_IPTM            __IPPROTO_IPTM            /* Internet Protocol Traffic Manager */
#endif /* !IPPROTO_IPTM && __IPPROTO_IPTM */
#if !defined(IPPROTO_NSFNET_IGP) && defined(__IPPROTO_NSFNET_IGP)
#define IPPROTO_NSFNET_IGP      __IPPROTO_NSFNET_IGP      /* NSFNET-IGP */
#endif /* !IPPROTO_NSFNET_IGP && __IPPROTO_NSFNET_IGP */
#if !defined(IPPROTO_DGP) && defined(__IPPROTO_DGP)
#define IPPROTO_DGP             __IPPROTO_DGP             /* Dissimilar Gateway Protocol */
#endif /* !IPPROTO_DGP && __IPPROTO_DGP */
#if !defined(IPPROTO_TCF) && defined(__IPPROTO_TCF)
#define IPPROTO_TCF             __IPPROTO_TCF             /* TCF */
#endif /* !IPPROTO_TCF && __IPPROTO_TCF */
#if !defined(IPPROTO_EIGRP) && defined(__IPPROTO_EIGRP)
#define IPPROTO_EIGRP           __IPPROTO_EIGRP           /* EIGRP Informational RFC 7868 */
#endif /* !IPPROTO_EIGRP && __IPPROTO_EIGRP */
#if !defined(IPPROTO_OSPF) && defined(__IPPROTO_OSPF)
#define IPPROTO_OSPF            __IPPROTO_OSPF            /* Open Shortest Path First RFC 2328 */
#endif /* !IPPROTO_OSPF && __IPPROTO_OSPF */
#if !defined(IPPROTO_SPRITE_RPC) && defined(__IPPROTO_SPRITE_RPC)
#define IPPROTO_SPRITE_RPC      __IPPROTO_SPRITE_RPC      /* Sprite-RPC Sprite RPC Protocol */
#endif /* !IPPROTO_SPRITE_RPC && __IPPROTO_SPRITE_RPC */
#if !defined(IPPROTO_LARP) && defined(__IPPROTO_LARP)
#define IPPROTO_LARP            __IPPROTO_LARP            /* Locus Address Resolution Protocol */
#endif /* !IPPROTO_LARP && __IPPROTO_LARP */
#if !defined(IPPROTO_MTP) && defined(__IPPROTO_MTP)
#define IPPROTO_MTP             __IPPROTO_MTP             /* Multicast Transport Protocol. */
#endif /* !IPPROTO_MTP && __IPPROTO_MTP */
#if !defined(IPPROTO_AX25) && defined(__IPPROTO_AX25)
#define IPPROTO_AX25            __IPPROTO_AX25            /* AX.25 */
#endif /* !IPPROTO_AX25 && __IPPROTO_AX25 */
#if !defined(IPPROTO_BEETPH) && defined(__IPPROTO_BEETPH)
#define IPPROTO_BEETPH          __IPPROTO_BEETPH          /* IP option pseudo header for BEET. */
#endif /* !IPPROTO_BEETPH && __IPPROTO_BEETPH */
#if !defined(IPPROTO_MICP) && defined(__IPPROTO_MICP)
#define IPPROTO_MICP            __IPPROTO_MICP            /* Mobile Internetworking Control Protocol */
#endif /* !IPPROTO_MICP && __IPPROTO_MICP */
#if !defined(IPPROTO_SCC_SP) && defined(__IPPROTO_SCC_SP)
#define IPPROTO_SCC_SP          __IPPROTO_SCC_SP          /* Semaphore Communications Sec. Pro */
#endif /* !IPPROTO_SCC_SP && __IPPROTO_SCC_SP */
#if !defined(IPPROTO_ETHERIP) && defined(__IPPROTO_ETHERIP)
#define IPPROTO_ETHERIP         __IPPROTO_ETHERIP         /* Ethernet-within-IP Encapsulation RFC 3378 */
#endif /* !IPPROTO_ETHERIP && __IPPROTO_ETHERIP */
#if !defined(IPPROTO_ENCAP) && defined(__IPPROTO_ENCAP)
#define IPPROTO_ENCAP           __IPPROTO_ENCAP           /* Encapsulation Header. */
#endif /* !IPPROTO_ENCAP && __IPPROTO_ENCAP */
#if !defined(IPPROTO_GMTP) && defined(__IPPROTO_GMTP)
#define IPPROTO_GMTP            __IPPROTO_GMTP            /* GMTP */
#endif /* !IPPROTO_GMTP && __IPPROTO_GMTP */
#if !defined(IPPROTO_IFMP) && defined(__IPPROTO_IFMP)
#define IPPROTO_IFMP            __IPPROTO_IFMP            /* Ipsilon Flow Management Protocol */
#endif /* !IPPROTO_IFMP && __IPPROTO_IFMP */
#if !defined(IPPROTO_PNNI) && defined(__IPPROTO_PNNI)
#define IPPROTO_PNNI            __IPPROTO_PNNI            /* PNNI over IP */
#endif /* !IPPROTO_PNNI && __IPPROTO_PNNI */
#if !defined(IPPROTO_PIM) && defined(__IPPROTO_PIM)
#define IPPROTO_PIM             __IPPROTO_PIM             /* Protocol Independent Multicast. */
#endif /* !IPPROTO_PIM && __IPPROTO_PIM */
#if !defined(IPPROTO_ARIS) && defined(__IPPROTO_ARIS)
#define IPPROTO_ARIS            __IPPROTO_ARIS            /* IBM's ARIS (Aggregate Route IP Switching) Protocol */
#endif /* !IPPROTO_ARIS && __IPPROTO_ARIS */
#if !defined(IPPROTO_SCPS) && defined(__IPPROTO_SCPS)
#define IPPROTO_SCPS            __IPPROTO_SCPS            /* SCPS (Space Communications Protocol Standards) SCPS-TP */
#endif /* !IPPROTO_SCPS && __IPPROTO_SCPS */
#if !defined(IPPROTO_QNX) && defined(__IPPROTO_QNX)
#define IPPROTO_QNX             __IPPROTO_QNX             /* QNX */
#endif /* !IPPROTO_QNX && __IPPROTO_QNX */
#if !defined(IPPROTO_AN) && defined(__IPPROTO_AN)
#define IPPROTO_AN              __IPPROTO_AN              /* A/N Active Networks */
#endif /* !IPPROTO_AN && __IPPROTO_AN */
#if !defined(IPPROTO_COMP) && defined(__IPPROTO_COMP)
#define IPPROTO_COMP            __IPPROTO_COMP            /* Compression Header Protocol. */
#endif /* !IPPROTO_COMP && __IPPROTO_COMP */
#if !defined(IPPROTO_SNP) && defined(__IPPROTO_SNP)
#define IPPROTO_SNP             __IPPROTO_SNP             /* Sitara Networks Protocol */
#endif /* !IPPROTO_SNP && __IPPROTO_SNP */
#if !defined(IPPROTO_COMPAQ_PEER) && defined(__IPPROTO_COMPAQ_PEER)
#define IPPROTO_COMPAQ_PEER     __IPPROTO_COMPAQ_PEER     /* Compaq Peer Protocol */
#endif /* !IPPROTO_COMPAQ_PEER && __IPPROTO_COMPAQ_PEER */
#if !defined(IPPROTO_IPXIP) && defined(__IPPROTO_IPXIP)
#define IPPROTO_IPXIP           __IPPROTO_IPXIP           /* IPX in IP */
#endif /* !IPPROTO_IPXIP && __IPPROTO_IPXIP */
#if !defined(IPPROTO_VRRP) && defined(__IPPROTO_VRRP)
#define IPPROTO_VRRP            __IPPROTO_VRRP            /* Virtual Router Redundancy Protocol, Common Address Redundancy Protocol (not IANA assigned) VRRP:RFC 3768 */
#endif /* !IPPROTO_VRRP && __IPPROTO_VRRP */
#if !defined(IPPROTO_PGM) && defined(__IPPROTO_PGM)
#define IPPROTO_PGM             __IPPROTO_PGM             /* PGM Reliable Transport Protocol RFC 3208 */
#endif /* !IPPROTO_PGM && __IPPROTO_PGM */
#if !defined(IPPROTO_ANY0HOP) && defined(__IPPROTO_ANY0HOP)
#define IPPROTO_ANY0HOP         __IPPROTO_ANY0HOP         /* Any 0-hop protocol */
#endif /* !IPPROTO_ANY0HOP && __IPPROTO_ANY0HOP */
#if !defined(IPPROTO_L2TP) && defined(__IPPROTO_L2TP)
#define IPPROTO_L2TP            __IPPROTO_L2TP            /* Layer Two Tunneling Protocol Version 3 RFC 3931 */
#endif /* !IPPROTO_L2TP && __IPPROTO_L2TP */
#if !defined(IPPROTO_DDX) && defined(__IPPROTO_DDX)
#define IPPROTO_DDX             __IPPROTO_DDX             /* D-II Data Exchange (DDX) */
#endif /* !IPPROTO_DDX && __IPPROTO_DDX */
#if !defined(IPPROTO_IATP) && defined(__IPPROTO_IATP)
#define IPPROTO_IATP            __IPPROTO_IATP            /* Interactive Agent Transfer Protocol */
#endif /* !IPPROTO_IATP && __IPPROTO_IATP */
#if !defined(IPPROTO_STP) && defined(__IPPROTO_STP)
#define IPPROTO_STP             __IPPROTO_STP             /* Schedule Transfer Protocol */
#endif /* !IPPROTO_STP && __IPPROTO_STP */
#if !defined(IPPROTO_SRP) && defined(__IPPROTO_SRP)
#define IPPROTO_SRP             __IPPROTO_SRP             /* SpectraLink Radio Protocol */
#endif /* !IPPROTO_SRP && __IPPROTO_SRP */
#if !defined(IPPROTO_UTI) && defined(__IPPROTO_UTI)
#define IPPROTO_UTI             __IPPROTO_UTI             /* Universal Transport Interface Protocol */
#endif /* !IPPROTO_UTI && __IPPROTO_UTI */
#if !defined(IPPROTO_SMP) && defined(__IPPROTO_SMP)
#define IPPROTO_SMP             __IPPROTO_SMP             /* Simple Message Protocol */
#endif /* !IPPROTO_SMP && __IPPROTO_SMP */
#if !defined(IPPROTO_SM) && defined(__IPPROTO_SM)
#define IPPROTO_SM              __IPPROTO_SM              /* Simple Multicast Protocol draft-perlman-simple-multicast-03 */
#endif /* !IPPROTO_SM && __IPPROTO_SM */
#if !defined(IPPROTO_PTP) && defined(__IPPROTO_PTP)
#define IPPROTO_PTP             __IPPROTO_PTP             /* Performance Transparency Protocol */
#endif /* !IPPROTO_PTP && __IPPROTO_PTP */
#if !defined(IPPROTO_IS2IS4) && defined(__IPPROTO_IS2IS4)
#define IPPROTO_IS2IS4          __IPPROTO_IS2IS4          /* Intermediate System to Intermediate System (IS-IS) Protocol over IPv4 RFC 1142 and RFC 1195 */
#endif /* !IPPROTO_IS2IS4 && __IPPROTO_IS2IS4 */
#if !defined(IPPROTO_FIRE) && defined(__IPPROTO_FIRE)
#define IPPROTO_FIRE            __IPPROTO_FIRE            /* Flexible Intra-AS Routing Environment */
#endif /* !IPPROTO_FIRE && __IPPROTO_FIRE */
#if !defined(IPPROTO_CRTP) && defined(__IPPROTO_CRTP)
#define IPPROTO_CRTP            __IPPROTO_CRTP            /* Combat Radio Transport Protocol */
#endif /* !IPPROTO_CRTP && __IPPROTO_CRTP */
#if !defined(IPPROTO_CRUDP) && defined(__IPPROTO_CRUDP)
#define IPPROTO_CRUDP           __IPPROTO_CRUDP           /* Combat Radio User Datagram */
#endif /* !IPPROTO_CRUDP && __IPPROTO_CRUDP */
#if !defined(IPPROTO_SSCOPMCE) && defined(__IPPROTO_SSCOPMCE)
#define IPPROTO_SSCOPMCE        __IPPROTO_SSCOPMCE        /* Service-Specific Connection-Oriented Protocol in a Multilink and Connectionless Environment ITU-T Q.2111 (1999) */
#endif /* !IPPROTO_SSCOPMCE && __IPPROTO_SSCOPMCE */
#if !defined(IPPROTO_IPLT) && defined(__IPPROTO_IPLT)
#define IPPROTO_IPLT            __IPPROTO_IPLT            /* IPLT */
#endif /* !IPPROTO_IPLT && __IPPROTO_IPLT */
#if !defined(IPPROTO_SPS) && defined(__IPPROTO_SPS)
#define IPPROTO_SPS             __IPPROTO_SPS             /* Secure Packet Shield */
#endif /* !IPPROTO_SPS && __IPPROTO_SPS */
#if !defined(IPPROTO_PIPE) && defined(__IPPROTO_PIPE)
#define IPPROTO_PIPE            __IPPROTO_PIPE            /* Private IP Encapsulation within IP Expired I-D draft-petri-mobileip-pipe-00.txt */
#endif /* !IPPROTO_PIPE && __IPPROTO_PIPE */
#if !defined(IPPROTO_SCTP) && defined(__IPPROTO_SCTP)
#define IPPROTO_SCTP            __IPPROTO_SCTP            /* Stream Control Transmission Protocol. */
#endif /* !IPPROTO_SCTP && __IPPROTO_SCTP */
#if !defined(IPPROTO_FC) && defined(__IPPROTO_FC)
#define IPPROTO_FC              __IPPROTO_FC              /* Fibre Channel */
#endif /* !IPPROTO_FC && __IPPROTO_FC */
#if !defined(IPPROTO_RSVP_E2E_IGNORE) && defined(__IPPROTO_RSVP_E2E_IGNORE)
#define IPPROTO_RSVP_E2E_IGNORE __IPPROTO_RSVP_E2E_IGNORE /* Reservation Protocol (RSVP) End-to-End Ignore RFC 3175 */
#endif /* !IPPROTO_RSVP_E2E_IGNORE && __IPPROTO_RSVP_E2E_IGNORE */
#if !defined(IPPROTO_MH) && defined(__IPPROTO_MH)
#define IPPROTO_MH              __IPPROTO_MH              /* [IPv6] IPv6 mobility header. */
#endif /* !IPPROTO_MH && __IPPROTO_MH */
#if !defined(IPPROTO_UDPLITE) && defined(__IPPROTO_UDPLITE)
#define IPPROTO_UDPLITE         __IPPROTO_UDPLITE         /* UDP-Lite protocol. */
#endif /* !IPPROTO_UDPLITE && __IPPROTO_UDPLITE */
#if !defined(IPPROTO_MPLS) && defined(__IPPROTO_MPLS)
#define IPPROTO_MPLS            __IPPROTO_MPLS            /* MPLS in IP. */
#endif /* !IPPROTO_MPLS && __IPPROTO_MPLS */
#if !defined(IPPROTO_MANET) && defined(__IPPROTO_MANET)
#define IPPROTO_MANET           __IPPROTO_MANET           /* MANET Protocols RFC 5498 */
#endif /* !IPPROTO_MANET && __IPPROTO_MANET */
#if !defined(IPPROTO_HIP) && defined(__IPPROTO_HIP)
#define IPPROTO_HIP             __IPPROTO_HIP             /* Host Identity Protocol RFC 5201 */
#endif /* !IPPROTO_HIP && __IPPROTO_HIP */
#if !defined(IPPROTO_SHIM6) && defined(__IPPROTO_SHIM6)
#define IPPROTO_SHIM6           __IPPROTO_SHIM6           /* Site Multihoming by IPv6 Intermediation RFC 5533 */
#endif /* !IPPROTO_SHIM6 && __IPPROTO_SHIM6 */
#if !defined(IPPROTO_WESP) && defined(__IPPROTO_WESP)
#define IPPROTO_WESP            __IPPROTO_WESP            /* Wrapped Encapsulating Security Payload RFC 5840 */
#endif /* !IPPROTO_WESP && __IPPROTO_WESP */
#if !defined(IPPROTO_ROHC) && defined(__IPPROTO_ROHC)
#define IPPROTO_ROHC            __IPPROTO_ROHC            /* Robust Header Compression RFC 5856 */
#endif /* !IPPROTO_ROHC && __IPPROTO_ROHC */
#if !defined(IPPROTO_LOUSER) && defined(__IPPROTO_LOUSER)
#define IPPROTO_LOUSER          __IPPROTO_LOUSER          /* Use for experimentation and testing RFC 3692 */
#endif /* !IPPROTO_LOUSER && __IPPROTO_LOUSER */
#if !defined(IPPROTO_HIUSER) && defined(__IPPROTO_HIUSER)
#define IPPROTO_HIUSER          __IPPROTO_HIUSER          /* Use for experimentation and testing RFC 3692 */
#endif /* !IPPROTO_HIUSER && __IPPROTO_HIUSER */
#if !defined(IPPROTO_RAW) && defined(__IPPROTO_RAW)
#define IPPROTO_RAW             __IPPROTO_RAW             /* Raw IP packets. */
#endif /* !IPPROTO_RAW && __IPPROTO_RAW */
#if !defined(IPPROTO_MAX) && defined(__IPPROTO_MAX)
#define IPPROTO_MAX             __IPPROTO_MAX             /* WARNING: This  is  actually 1+  the max  possible IPPROTO!
                                                           * The protocol-field of IP is 1-byte, so the max is 0xff=255 */
#endif /* !IPPROTO_MAX && __IPPROTO_MAX */

#endif /* !_NETINET_IPPROTO_H */
