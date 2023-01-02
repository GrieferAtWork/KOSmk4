/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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
#include <sched/task.h>

#include <kos/net/printf.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <network/arp.h>
#include <network/ethernet.h>
#include <network/ip.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/* Route an incoming packet through the given NIC device.
 * @assume(packet_size >= ETH_ZLEN) */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
eth_routepacket(struct nicdev *__restrict dev,
                void const *__restrict packet_data,
                size_t packet_size) {
	struct ethhdr *hdr;
	hdr = (struct ethhdr *)packet_data;
	assert(packet_size >= ETH_ZLEN);
	device_getname_lock_acquire(dev);
	printk(KERN_TRACE "[eth:%s] Route eth packet ["
	                  "dst=" NET_PRINTF_MACADDR_FMT ","
	                  "src=" NET_PRINTF_MACADDR_FMT ","
	                  "prot=%#.4" PRIx16 ","
	                  "siz=%" PRIuSIZ "]\n",
	       device_getname(dev),
	       NET_PRINTF_MACADDR_ARG(hdr->h_dest),
	       NET_PRINTF_MACADDR_ARG(hdr->h_source),
	       ntohs(hdr->h_proto), packet_size);
	device_getname_lock_release(dev);
	switch (ntohs(hdr->h_proto)) {

	case ETH_P_IP:
		ip_routepacket(dev, hdr + 1, packet_size - sizeof(*hdr));
		break;

	case ETH_P_ARP:
		arp_routepacket(dev, hdr + 1, packet_size - sizeof(*hdr));
		break;

	default: {
		device_getname_lock_acquire(dev);
		printk(KERN_WARNING "[eth:%s] Unrecognized eth packet ["
		                    "dst=" NET_PRINTF_MACADDR_FMT ","
		                    "src=" NET_PRINTF_MACADDR_FMT ","
		                    "prot=%#.4" PRIx16 ","
		                    "siz=%" PRIuSIZ "]\n",
		       device_getname(dev),
		       NET_PRINTF_MACADDR_ARG(hdr->h_dest),
		       NET_PRINTF_MACADDR_ARG(hdr->h_source),
		       ntohs(hdr->h_proto), packet_size);
		device_getname_lock_release(dev);
	}	break;

	}
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_ETHERNET_C */
