/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_NETWORK_UDP_C
#define GUARD_KERNEL_SRC_NETWORK_UDP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/printk.h>

#include <kos/net/printf.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <network/ip.h>
#include <network/network.h>
#include <network/udp.h>

#include <assert.h>
#include <inttypes.h>

DECL_BEGIN

/* Route a UDP packet.
 * @assume(packet_size >= sizeof(struct udphdr)); */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
udp_routepacket(struct nic_device *__restrict dev,
                struct udphdr const *__restrict packet, u16 packet_size,
                struct iphdr const *__restrict ip_header) {
	byte_t const *payload;
	u16 payload_length;
	assert(packet_size >= sizeof(struct udphdr));
	payload        = (byte_t const *)packet + sizeof(struct udphdr);
	payload_length = ntohs(packet->uh_ulen);
	/* Ensure that the */
	if unlikely(payload_length < sizeof(struct udphdr)) {
		printk(KERN_ERR "[udp:%s] udp packet udp.size=%" PRIu16 " from "
		                "[" NET_PRINTF_IPADDRPORT_FMT "] to "
		                "[" NET_PRINTF_IPADDRPORT_FMT "] "
		                "is too small\n",
		       dev->cd_name, payload_length,
		       NET_PRINTF_IPADDRPORT_ARG(ip_header->ip_src.s_addr,
		                                 ntohs(packet->uh_sport)),
		       NET_PRINTF_IPADDRPORT_ARG(ip_header->ip_dst.s_addr,
		                                 ntohs(packet->uh_dport)));
		return;
	}
	if unlikely(payload_length > packet_size) {
		printk(KERN_ERR "[udp:%s] udp packet udp.size=%" PRIu16 " from "
		                "[" NET_PRINTF_IPADDRPORT_FMT "] to "
		                "[" NET_PRINTF_IPADDRPORT_FMT "] "
		                "exceeds ip.size=%" PRIu16 "\n",
		       dev->cd_name, payload_length,
		       NET_PRINTF_IPADDRPORT_ARG(ip_header->ip_src.s_addr,
		                                 ntohs(packet->uh_sport)),
		       NET_PRINTF_IPADDRPORT_ARG(ip_header->ip_dst.s_addr,
		                                 ntohs(packet->uh_dport)),
		       packet_size);
		return;
	}
	payload_length -= sizeof(struct udphdr);

#if 1
	printk(KERN_TRACE "[udp:%s] Packet from "
	                  "[" NET_PRINTF_IPADDRPORT_FMT "] to "
	                  "[" NET_PRINTF_IPADDRPORT_FMT "]:\n"
	                  "%$[hex:P]\n",
	       dev->cd_name,
	       NET_PRINTF_IPADDRPORT_ARG(ip_header->ip_src.s_addr,
	                                 ntohs(packet->uh_sport)),
	       NET_PRINTF_IPADDRPORT_ARG(ip_header->ip_dst.s_addr,
	                                 ntohs(packet->uh_dport)),
	       payload_length, payload);
#endif
	(void)dev;
	(void)packet;
	(void)packet_size;
	(void)ip_header;
	(void)payload_length;
	(void)payload;
	/* TODO */
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_UDP_C */
