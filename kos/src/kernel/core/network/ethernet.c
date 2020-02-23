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
#ifndef GUARD_KERNEL_SRC_NETWORK_ETHERNET_C
#define GUARD_KERNEL_SRC_NETWORK_ETHERNET_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/printk.h>

#include <linux/if_ether.h>
#include <netinet/in.h>
#include <network/arp.h>
#include <network/ethernet.h>
#include <network/ip.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Route an incoming packet through the given NIC device. */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
eth_routepacket(struct nic_device *__restrict self,
                void const *__restrict packet_data,
                size_t packet_size) {
	struct ethhdr *hdr;
	assert(packet_size >= ETH_ZLEN);
	printk(KERN_TRACE "[nic:%s] Route eth-packet (%Iu bytes):\n",
	       self->cd_name, packet_size);
	hdr = (struct ethhdr *)packet_data;
	switch (ntohs(hdr->h_proto)) {

	case ETH_P_IP:
		ip_routepacket(self, hdr + 1, packet_size - sizeof(*hdr));
		break;

	case ETH_P_ARP:
		arp_routepacket(self, hdr + 1, packet_size - sizeof(*hdr));
		break;

	default:
		printk(KERN_WARNING "[nic:%s] Unrecognized eth-protocol (%#.4I16x, size=%Iu)\n",
		       ntohs(hdr->h_proto), packet_size);
		break;
	}
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_ETHERNET_C */
