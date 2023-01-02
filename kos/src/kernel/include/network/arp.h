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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_ARP_H
#define GUARD_KERNEL_INCLUDE_NETWORK_ARP_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

/* Route an ARP packet.
 * @assume(packet_size >= 8); */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
arp_routepacket(struct nicdev *__restrict dev,
                void const *__restrict packet_data,
                size_t packet_size);

/* Construct and return a mac address request packet.
 * NOTE: The caller should  also make  use of  `nic_device_requireip()'
 *       to ensure that the associated network peer descriptor has been
 *       allocated, and that its MAC field  will be filled in once  the
 *       named device responds back to the given NIC. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct nic_packet *KCALL
arp_makemacrequest(struct nicdev *__restrict dev, be32 ip);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_ARP_H */
