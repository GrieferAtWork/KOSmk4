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
#ifndef GUARD_KERNEL_SRC_NETWORK_ARP_C
#define GUARD_KERNEL_SRC_NETWORK_ARP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/printk.h>

#include <kos/net/printf.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <network/arp.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

struct ATTR_PACKED ATTR_ALIGNED(2) etharphdr_ether_in /*[PREFIX(ar_)]*/ {
	struct ethhdr  ar_eth; /* Ethernet header. */
	struct arphdr  ar_arp; /* ARP header. */
	byte_t         ar_sha[ETH_ALEN]; /* Sender mac address. */
	struct in_addr ar_sip;           /* Sender ip address. */
	byte_t         ar_tha[ETH_ALEN]; /* Target mac address. */
	struct in_addr ar_tip;           /* Target ip address. */
};

struct ATTR_PACKED ATTR_ALIGNED(2) arphdr_ether_in /*[PREFIX(ar_)]*/ {
	struct arphdr  ar_arp; /* ARP header. */
	byte_t         ar_sha[ETH_ALEN]; /* Sender mac address. */
	struct in_addr ar_sip;           /* Sender ip address. */
	byte_t         ar_tha[ETH_ALEN]; /* Target mac address. */
	struct in_addr ar_tip;           /* Target ip address. */
};


PRIVATE NOBLOCK NONNULL((1, 2)) void KCALL
arp_reply_myip(struct nicdev *__restrict dev,
               struct arphdr_ether_in const *__restrict packet) {
	struct etharphdr_ether_in *response;
	REF struct nic_packet *response_packet;
	printk(KERN_TRACE "[arp:%s] Tell " NET_PRINTF_IPADDR_FMT " [mac:" NET_PRINTF_MACADDR_FMT "] "
	                  "that we are " NET_PRINTF_IPADDR_FMT " [mac:" NET_PRINTF_MACADDR_FMT "]\n",
	       NET_PRINTF_IPADDR_ARG(packet->ar_sip.s_addr), NET_PRINTF_MACADDR_ARG(packet->ar_sha),
	       NET_PRINTF_IPADDR_ARG(dev->nd_addr.na_ip), NET_PRINTF_MACADDR_ARG(dev->nd_addr.na_hwmac));
	response_packet = nicdev_newpacketk(dev, (void **)&response, sizeof(*response));
	FINALLY_DECREF_UNLIKELY(response_packet);
	/* Construct an ARP response containing our MAC and IP addresses. */
	memcpy(response->ar_eth.h_dest, packet->ar_sha, ETH_ALEN);
	memcpy(response->ar_eth.h_source, dev->nd_addr.na_hwmac, ETH_ALEN);
	response->ar_eth.h_proto = htons(ETH_P_ARP);
	response->ar_arp.ar_hrd  = htons(ARPHRD_ETHER);
	response->ar_arp.ar_pro  = htons(ETH_P_IP);
	response->ar_arp.ar_hln  = ETH_ALEN;
	response->ar_arp.ar_pln  = sizeof(struct in_addr);
	response->ar_arp.ar_op   = htons(ARPOP_REPLY);
	memcpy(response->ar_sha, dev->nd_addr.na_hwmac, ETH_ALEN);
	response->ar_sip.s_addr = dev->nd_addr.na_ip;
	memcpy(response->ar_tha, packet->ar_sha, ETH_ALEN);
	response->ar_tip.s_addr = packet->ar_sip.s_addr;
	/* Send back the response in the background. */
	nicdev_send_background(dev, response_packet);
}


/* Route an ARP packet.
 * @assume(packet_size >= 8); */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
arp_routepacket(struct nicdev *__restrict dev,
                void const *__restrict packet_data,
                size_t packet_size) {
	struct arphdr *ahdr;
	size_t required_size;
	assert(packet_size >= 8);
	ahdr = (struct arphdr *)packet_data;
	/* We only understand ETHERNET requests (for now) */
	if (ahdr->ar_hrd != htons(ARPHRD_ETHER))
		return;
	if (ahdr->ar_hln != ETH_ALEN)
		return; /* Invalid mac address length. */
	/* Make sure that the packet is large enough! */
	required_size = sizeof(struct arphdr) +
	                ETH_ALEN * 2 +
	                ahdr->ar_pln * 2;
	if unlikely(packet_size < required_size) {
		printk(KERN_WARNING "[arp:%s] Packet too small (%" PRIuSIZ " < %" PRIuSIZ ")\n",
		       packet_size, required_size);
		return;
	}
	switch (ntohs(ahdr->ar_op)) {

	case ARPOP_REQUEST:
		if (ahdr->ar_pro == htons(ETH_P_IP)) {
			struct arphdr_ether_in *hdr;
			if (ahdr->ar_pln != sizeof(struct in_addr))
				return; /* IPv4 addresses are 4-byte long */
			/* Who has <IP:ar_tip>? Tell <IP:ar_sip,MAC:ar_sha> */
			hdr = (struct arphdr_ether_in *)packet_data;
			/* Check if this is our ip... */
			if (hdr->ar_tip.s_addr == dev->nd_addr.na_ip &&
			    dev->nd_addr.na_flags & NIC_ADDR_HAVE_IP)
				arp_reply_myip(dev, hdr); /* Tell them who we are! */
		}
		break;

	case ARPOP_REPLY:
		if (ahdr->ar_pro == htons(ETH_P_IP)) {
			struct arphdr_ether_in *hdr;
			REF struct net_peeraddrs *peers;
			struct net_peeraddr *peer;
			if (ahdr->ar_pln != sizeof(struct in_addr))
				return; /* IPv4 addresses are 4-byte long */
			hdr = (struct arphdr_ether_in *)packet_data;
			/* Check if we've asked who this is in the past. */
			peers = arref_get(&dev->nd_net.n_peers);
			peer  = net_peeraddrs_lookup_ip(peers, hdr->ar_sip.s_addr);
			if (peer) {
				/* Fill in peer information. */
				u8 oldmac[ETH_ALEN];
				memcpy(oldmac, peer->npa_hwmac, ETH_ALEN);
				memcpy(peer->npa_hwmac, hdr->ar_sha, ETH_ALEN);
				if unlikely((atomic_fetchor(&peer->npa_flags, NET_PEERADDR_HAVE_MAC) & NET_PEERADDR_HAVE_MAC) &&
				            (bcmp(peer->npa_hwmac, hdr->ar_sha, ETH_ALEN, sizeof(u8)) != 0)) {
					printk(KERN_NOTICE "[arp:%s] macaddr for " NET_PRINTF_IPADDR_FMT
					                   " changed from " NET_PRINTF_MACADDR_FMT
					                   " to " NET_PRINTF_MACADDR_FMT "\n",
					       NET_PRINTF_IPADDR_ARG(peer->npa_ip),
					       NET_PRINTF_MACADDR_ARG(oldmac),
					       NET_PRINTF_MACADDR_ARG(hdr->ar_sha));
				}
				/* Indicate that the mac address of a peer has just become available. */
				sig_broadcast(&dev->nd_net.n_addravl);
			}
			decref_unlikely(peers);
		}
		break;

	default:
		break;
	}
}

/* Construct and return a mac address request packet. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
arp_makemacrequest(struct nicdev *__restrict dev, be32 ip) {
	struct etharphdr_ether_in *req;
	REF struct nic_packet *packet;
	packet = nicdev_newpacketk(dev, (void **)&req, sizeof(*req));
	memset(req->ar_eth.h_dest, 0xff, ETH_ALEN); /* Broadcast */
	memcpy(req->ar_eth.h_source, dev->nd_addr.na_hwmac, ETH_ALEN);
	req->ar_eth.h_proto = htons(ETH_P_ARP);
	req->ar_arp.ar_hrd  = htons(ARPHRD_ETHER);
	req->ar_arp.ar_pro  = htons(ETH_P_IP);
	req->ar_arp.ar_hln  = ETH_ALEN;
	req->ar_arp.ar_pln  = sizeof(struct in_addr);
	req->ar_arp.ar_op   = htons(ARPOP_REQUEST);
	memcpy(req->ar_sha, dev->nd_addr.na_hwmac, ETH_ALEN);
	req->ar_sip.s_addr = dev->nd_addr.na_ip;
	bzero(req->ar_tha, ETH_ALEN); /* Unknown... */
	req->ar_tip.s_addr = ip;
	return packet;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_ARP_C */
