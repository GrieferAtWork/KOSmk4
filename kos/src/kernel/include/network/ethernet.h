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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_ETHERNET_H
#define GUARD_KERNEL_INCLUDE_NETWORK_ETHERNET_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>

DECL_BEGIN

/* Ethernet packet requirements */
#define ETH_PACKET_HEADSIZE ETH_HLEN
#define ETH_PACKET_TAILSIZE 0

#ifdef __CC__

/* Route an incoming packet through the given NIC device.
 * @assume(packet_size >= ETH_ZLEN) */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
eth_routepacket(struct nicdev *__restrict dev,
                void const *__restrict packet_data,
                size_t packet_size);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_ETHERNET_H */
