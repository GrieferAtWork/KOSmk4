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
#ifndef GUARD_KERNEL_SRC_NETWORK_IP_C
#define GUARD_KERNEL_SRC_NETWORK_IP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/printk.h>

#include <bits/in.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <network/ip.h>

#include <assert.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/* Route a given IP packet.
 * @assume(packet_size >= 20); */
PUBLIC NOBLOCK NONNULL((1, 2)) void KCALL
ip_routepacket(struct nic_device *__restrict dev,
               void const *__restrict packet_data,
               size_t packet_size) {
	struct iphdr *hdr;
	assert(packet_size >= 20);
	hdr = (struct iphdr *)packet_data;

	/* TODO */

	(void)hdr;
	(void)dev;
	(void)packet_data;
	(void)packet_size;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_IP_C */
