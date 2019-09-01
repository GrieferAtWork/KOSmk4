/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NET_IF_ARP_H
#define _NET_IF_ARP_H 1

#include <__stdinc.h>
#include <sys/types.h>
#include <sys/socket.h>

__SYSDECL_BEGIN

/* Definitions for Address Resolution Protocol.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

/* Based on the 4.4BSD and Linux version of this file.  */


/* Some internals from deep down in the kernel.  */
#define MAX_ADDR_LEN	7


/* This structure defines an ethernet arp header. */

/* ARP protocol opcodes. */
#define ARPOP_REQUEST     1 /* ARP request. */
#define ARPOP_REPLY       2 /* ARP reply. */
#define ARPOP_RREQUEST    3 /* RARP request. */
#define ARPOP_RREPLY      4 /* RARP reply. */
#define ARPOP_InREQUEST   8 /* InARP request. */
#define ARPOP_InREPLY     9 /* InARP reply. */
#define ARPOP_NAK        10 /* (ATM)ARP NAK. */

/* See RFC 826 for protocol description. ARP packets are variable
 * in size; the arphdr structure defines the fixed-length portion.
 * Protocol type values are the same as those for 10 Mb/s Ethernet.
 * It is followed by the variable-sized fields ar_sha, arp_spa,
 * arp_tha and arp_tpa in that order, according to the lengths
 * specified. Field names used correspond to RFC 826. */

#ifdef __CC__
#ifndef __arphdr_defined
#define __arphdr_defined 1
struct arphdr {
	unsigned short int ar_hrd; /* Format of hardware address. */
	unsigned short int ar_pro; /* Format of protocol address. */
	unsigned char      ar_hln; /* Length of hardware address. */
	unsigned char      ar_pln; /* Length of protocol address. */
	unsigned short int ar_op;  /* ARP opcode (command). */
#if 0
	/* Ethernet looks like this : This bit is variable sized however... */
	unsigned char __ar_sha[ETH_ALEN]; /* Sender hardware address. */
	unsigned char __ar_sip[4];        /* Sender IP address. */
	unsigned char __ar_tha[ETH_ALEN]; /* Target hardware address. */
	unsigned char __ar_tip[4];        /* Target IP address. */
#endif
};
#endif /* !__arphdr_defined */
#endif /* __CC__ */


/* ARP protocol HARDWARE identifiers. */
#define ARPHRD_NETROM      0  /* From KA9Q: NET/ROM pseudo. */
#define ARPHRD_ETHER       1  /* Ethernet 10/100Mbps. */
#define ARPHRD_EETHER      2  /* Experimental Ethernet. */
#define ARPHRD_AX25        3  /* AX.25 Level 2. */
#define ARPHRD_PRONET      4  /* PROnet token ring. */
#define ARPHRD_CHAOS       5  /* Chaosnet. */
#define ARPHRD_IEEE802     6  /* IEEE 802.2 Ethernet/TR/TB. */
#define ARPHRD_ARCNET      7  /* ARCnet. */
#define ARPHRD_APPLETLK    8  /* APPLEtalk. */
#define ARPHRD_DLCI        15 /* Frame Relay DLCI. */
#define ARPHRD_ATM         19 /* ATM. */
#define ARPHRD_METRICOM    23 /* Metricom STRIP (new IANA id). */
#define ARPHRD_IEEE1394    24 /* IEEE 1394 IPv4 - RFC 2734. */
#define ARPHRD_EUI64       27 /* EUI-64. */
#define ARPHRD_INFINIBAND  32 /* InfiniBand. */

/* Dummy types for non ARP hardware */
#define ARPHRD_SLIP               256
#define ARPHRD_CSLIP              257
#define ARPHRD_SLIP6              258
#define ARPHRD_CSLIP6             259
#define ARPHRD_RSRVD              260 /* Notional KISS type. */
#define ARPHRD_ADAPT              264
#define ARPHRD_ROSE               270
#define ARPHRD_X25                271 /* CCITT X.25. */
#define ARPHRD_HWX25              272 /* Boards with X.25 in firmware. */
#define ARPHRD_PPP                512
#define ARPHRD_CISCO              513 /* Cisco HDLC. */
#define ARPHRD_HDLC               ARPHRD_CISCO
#define ARPHRD_LAPB               516 /* LAPB. */
#define ARPHRD_DDCMP              517 /* Digital's DDCMP. */
#define ARPHRD_RAWHDLC            518 /* Raw HDLC. */

#define ARPHRD_TUNNEL             768 /* IPIP tunnel. */
#define ARPHRD_TUNNEL6            769 /* IPIP6 tunnel. */
#define ARPHRD_FRAD               770 /* Frame Relay Access Device. */
#define ARPHRD_SKIP               771 /* SKIP vif. */
#define ARPHRD_LOOPBACK           772 /* Loopback device. */
#define ARPHRD_LOCALTLK           773 /* Localtalk device. */
#define ARPHRD_FDDI               774 /* Fiber Distributed Data Interface. */
#define ARPHRD_BIF                775 /* AP1000 BIF. */
#define ARPHRD_SIT                776 /* sit0 device - IPv6-in-IPv4. */
#define ARPHRD_IPDDP              777 /* IP-in-DDP tunnel. */
#define ARPHRD_IPGRE              778 /* GRE over IP. */
#define ARPHRD_PIMREG             779 /* PIMSM register interface. */
#define ARPHRD_HIPPI              780 /* High Performance Parallel I'face. */
#define ARPHRD_ASH                781 /* (Nexus Electronics) Ash. */
#define ARPHRD_ECONET             782 /* Acorn Econet. */
#define ARPHRD_IRDA               783 /* Linux-IrDA. */
#define ARPHRD_FCPP               784 /* Point to point fibrechanel. */
#define ARPHRD_FCAL               785 /* Fibrechanel arbitrated loop. */
#define ARPHRD_FCPL               786 /* Fibrechanel public loop. */
#define ARPHRD_FCFABRIC           787 /* Fibrechanel fabric. */
#define ARPHRD_IEEE802_TR         800 /* Magic type ident for TR. */
#define ARPHRD_IEEE80211          801 /* IEEE 802.11. */
#define ARPHRD_IEEE80211_PRISM    802 /* IEEE 802.11 + Prism2 header. */
#define ARPHRD_IEEE80211_RADIOTAP 803 /* IEEE 802.11 + radiotap header. */
#define ARPHRD_IEEE802154         804 /* IEEE 802.15.4 header. */
#define ARPHRD_IEEE802154_PHY     805 /* IEEE 802.15.4 PHY header. */

#define ARPHRD_VOID 0xffff /* Void type, nothing is known. */
#define ARPHRD_NONE 0xfffe /* Zero header length. */


/* ARP ioctl request. */
#ifdef __CC__
#ifndef __arpreq_defined
#define __arpreq_defined 1
struct arpreq {
	struct sockaddr arp_pa;      /* Protocol address. */
	struct sockaddr arp_ha;      /* Hardware address. */
	int             arp_flags;   /* Flags. */
	struct sockaddr arp_netmask; /* Netmask (only for proxy arps). */
	char            arp_dev[16];
};
#endif /* !__arpreq_defined */
#endif /* __CC__ */

#ifdef __CC__
#ifndef __arpreq_old_defined
#define __arpreq_old_defined 1
struct arpreq_old {
	struct sockaddr arp_pa;      /* Protocol address. */
	struct sockaddr arp_ha;      /* Hardware address. */
	int             arp_flags;   /* Flags. */
	struct sockaddr arp_netmask; /* Netmask (only for proxy arps). */
};
#endif /* !__arpreq_old_defined */
#endif /* __CC__ */

/* ARP Flag values. */
#define ATF_COM         0x02 /* Completed entry (ha valid). */
#define ATF_PERM        0x04 /* Permanent entry. */
#define ATF_PUBL        0x08 /* Publish entry. */
#define ATF_USETRAILERS 0x10 /* Has requested trailers. */
#define ATF_NETMASK     0x20 /* Want to use a netmask (only for proxy entries). */
#define ATF_DONTPUB     0x40 /* Don't answer this addresses. */
#define ATF_MAGIC       0x80 /* Automatically added entry. */


/* Support for the user space arp daemon, arpd. */
#define ARPD_UPDATE    0x01
#define ARPD_LOOKUP    0x02
#define ARPD_FLUSH     0x03

#ifdef __CC__
struct arpd_request {
	unsigned short int req;        /* Request type. */
	u_int32_t ip;            /* IP address of entry. */
	unsigned long int dev;        /* Device entry is tied to. */
	unsigned long int stamp;
	unsigned long int updated;
	unsigned char ha[MAX_ADDR_LEN];    /* Hardware address. */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NET_IF_ARP_H */
