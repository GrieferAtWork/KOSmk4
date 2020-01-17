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
#ifndef _LINUX_IF_ARG_H
#define _LINUX_IF_ARG_H 1

#include <__stdinc.h>
#include <kos/bits/types.h>
#include <bits/socket.h> /* struct sockaddr */
//#include <linux/netdevice.h>

__SYSDECL_BEGIN

/* Based on the linux header of the same name. */

/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Global definitions for the ARP (RFC 826) protocol.
 *
 * Version:	@(#)if_arp.h	1.0.1	04/16/93
 *
 * Authors:	Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988
 *		Portions taken from the KA9Q/NOS (v2.00m PA0GRI) source.
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Florian La Roche,
 *		Jonathan Layes <layes@loran.com>
 *		Arnaldo Carvalho de Melo <acme@conectiva.com.br> ARPHRD_HWX25
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */

/* ARP protocol HARDWARE identifiers. */
#define ARPHRD_NETROM      0 /* from KA9Q: NET/ROM pseudo. */
#define ARPHRD_ETHER       1 /* Ethernet 10Mbps. */
#define ARPHRD_EETHER      2 /* Experimental Ethernet. */
#define ARPHRD_AX25        3 /* AX.25 Level 2. */
#define ARPHRD_PRONET      4 /* PROnet token ring. */
#define ARPHRD_CHAOS       5 /* Chaosnet. */
#define ARPHRD_IEEE802     6 /* IEEE 802.2 Ethernet/TR/TB. */
#define ARPHRD_ARCNET      7 /* ARCnet. */
#define ARPHRD_APPLETLK    8 /* APPLEtalk. */
#define ARPHRD_DLCI       15 /* Frame Relay DLCI. */
#define ARPHRD_ATM        19 /* ATM. */
#define ARPHRD_METRICOM   23 /* Metricom STRIP (new IANA id). */
#define ARPHRD_IEEE1394   24 /* IEEE 1394 IPv4 - RFC 2734. */
#define ARPHRD_EUI64      27 /* EUI-64. */
#define ARPHRD_INFINIBAND 32 /* InfiniBand. */

/* Dummy types for non ARP hardware */
#define ARPHRD_SLIP       256
#define ARPHRD_CSLIP      257
#define ARPHRD_SLIP6      258
#define ARPHRD_CSLIP6     259
#define ARPHRD_RSRVD      260 /* Notional KISS type. */
#define ARPHRD_ADAPT      264
#define ARPHRD_ROSE       270
#define ARPHRD_X25        271 /* CCITT X.25. */
#define ARPHRD_HWX25      272 /* Boards with X.25 in firmware. */
#define ARPHRD_CAN        280 /* Controller Area Network. */
#define ARPHRD_PPP        512
#define ARPHRD_CISCO      513 /* Cisco HDLC. */
#define ARPHRD_HDLC       ARPHRD_CISCO
#define ARPHRD_LAPB       516 /* LAPB. */
#define ARPHRD_DDCMP      517 /* Digital's DDCMP protocol. */
#define ARPHRD_RAWHDLC    518 /* Raw HDLC. */

#define ARPHRD_TUNNEL     768 /* IPIP tunnel. */
#define ARPHRD_TUNNEL6    769 /* IP6IP6 tunnel. */
#define ARPHRD_FRAD       770 /* Frame Relay Access Device. */
#define ARPHRD_SKIP       771 /* SKIP vif. */
#define ARPHRD_LOOPBACK   772 /* Loopback device. */
#define ARPHRD_LOCALTLK   773 /* Localtalk device. */
#define ARPHRD_FDDI       774 /* Fiber Distributed Data Interface. */
#define ARPHRD_BIF        775 /* AP1000 BIF. */
#define ARPHRD_SIT        776 /* sit0 device - IPv6-in-IPv4. */
#define ARPHRD_IPDDP      777 /* IP over DDP tunneller. */
#define ARPHRD_IPGRE      778 /* GRE over IP. */
#define ARPHRD_PIMREG     779 /* PIMSM register interface. */
#define ARPHRD_HIPPI      780 /* High Performance Parallel Interface. */
#define ARPHRD_ASH        781 /* Nexus 64Mbps Ash. */
#define ARPHRD_ECONET     782 /* Acorn Econet. */
#define ARPHRD_IRDA       783 /* Linux-IrDA. */
/* ARP works differently on different FC media .. so  */
#define ARPHRD_FCPP       784 /* Point to point fibrechannel. */
#define ARPHRD_FCAL       785 /* Fibrechannel arbitrated loop. */
#define ARPHRD_FCPL       786 /* Fibrechannel public loop. */
#define ARPHRD_FCFABRIC   787 /* Fibrechannel fabric. */
/* 787->799 reserved for fibrechannel media types. */
#define ARPHRD_IEEE802_TR 800 /* Magic type ident for TR. */
#define ARPHRD_IEEE80211  801 /* IEEE 802.11. */
#define ARPHRD_IEEE80211_PRISM 802 /* IEEE 802.11 + Prism2 header  */
#define ARPHRD_IEEE80211_RADIOTAP 803 /* IEEE 802.11 + radiotap header */
#define ARPHRD_IEEE802154 804
#define ARPHRD_IEEE802154_MONITOR 805 /* IEEE 802.15.4 network monitor */

#define ARPHRD_PHONET     820  /* PhoNet media type. */
#define ARPHRD_PHONET_PIPE 821 /* PhoNet pipe header. */
#define ARPHRD_CAIF       822  /* CAIF media type. */
#define ARPHRD_IP6GRE     823  /* GRE over IPv6. */
#define ARPHRD_NETLINK    824  /* Netlink header. */
#define ARPHRD_6LOWPAN    825  /* IPv6 over LoWPAN. */

#define ARPHRD_VOID 0xFFFF /* Void type, nothing is known. */
#define ARPHRD_NONE 0xFFFE /* zero header length. */

/* ARP protocol opcodes. */
#define ARPOP_REQUEST   1  /* ARP request. */
#define ARPOP_REPLY     2  /* ARP reply. */
#define ARPOP_RREQUEST  3  /* RARP request. */
#define ARPOP_RREPLY    4  /* RARP reply. */
#define ARPOP_InREQUEST 8  /* InARP request. */
#define ARPOP_InREPLY   9  /* InARP reply. */
#define ARPOP_NAK       10 /* (ATM)ARP NAK. */


/* ARP ioctl request. */
#ifdef __CC__
#ifndef __arpreq_defined
#define __arpreq_defined 1
struct arpreq {
	struct sockaddr arp_pa;      /* protocol address. */
	struct sockaddr arp_ha;      /* hardware address. */
	__INT32_TYPE__  arp_flags;   /* flags. */
	struct sockaddr arp_netmask; /* netmask (only for proxy arps). */
	char            arp_dev[16];
};
#endif /* !__arpreq_defined */

#ifndef __arpreq_old_defined
#define __arpreq_old_defined 1
struct arpreq_old {
	struct sockaddr arp_pa;      /* protocol address. */
	struct sockaddr arp_ha;      /* hardware address. */
	__INT32_TYPE__  arp_flags;   /* flags. */
	struct sockaddr arp_netmask; /* netmask (only for proxy arps). */
};
#endif /* !__arpreq_old_defined */
#endif /* __CC__ */

/* ARP Flag values. */
#define ATF_COM         0x02 /* completed entry (ha valid). */
#define ATF_PERM        0x04 /* permanent entry. */
#define ATF_PUBL        0x08 /* publish entry. */
#define ATF_USETRAILERS 0x10 /* has requested trailers. */
#define ATF_NETMASK     0x20 /* want to use a netmask (only for proxy entries). */
#define ATF_DONTPUB     0x40 /* don't answer this addresses. */

/* This structure defines an ethernet arp header. */
#ifdef __CC__
#ifndef __arphdr_defined
#define __arphdr_defined 1
struct arphdr {
	__be16        ar_hrd; /* format of hardware address. */
	__be16        ar_pro; /* format of protocol address. */
	unsigned char ar_hln; /* length of hardware address. */
	unsigned char ar_pln; /* length of protocol address. */
	__be16        ar_op;  /* ARP opcode (command). */
#if 0 /* The variable part looks like this: */
	unsigned char ar_sha[ar_hln]; /* sender hardware address. */
	unsigned char ar_sip[ar_pln]; /* sender protocol address. */
	unsigned char ar_tha[ar_hln]; /* target hardware address. */
	unsigned char ar_tip[ar_pln]; /* target protocol address. */
#endif
};
#endif /* !__arphdr_defined */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_LINUX_IF_ARG_H */
