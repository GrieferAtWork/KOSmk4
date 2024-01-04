/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_UDP_H
#define GUARD_KERNEL_INCLUDE_NETWORK_UDP_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>

#include <network/ip.h>

DECL_BEGIN

/* UDP packet requirements */
#define UDP_PACKET_HEADSIZE (IP_PACKET_HEADSIZE + 8)
#define UDP_PACKET_TAILSIZE (IP_PACKET_TAILSIZE)

#ifdef __CC__

struct udphdr;
struct iphdr;

/* Route a UDP packet.
 * @assume(packet_size >= sizeof(struct udphdr)); */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
udp_routepacket(struct nicdev *__restrict dev,
                struct udphdr const *__restrict packet, u16 packet_size,
                struct iphdr const *__restrict ip_header);

/* TODO: Implement UDP support */
/* TODO: Implement DHCP support */
/* TODO: Use DHCP to automatically configure `nic_addresses::na_ip' the
 *       first time that we need our own IP address for some  protocol. */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_UDP_H */
