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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_IP_H
#define GUARD_KERNEL_INCLUDE_NETWORK_IP_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/malloc.h>
#include <kernel/types.h>

#include <bits/timespec.h>
#include <netinet/ip.h>

DECL_BEGIN

#ifdef __CC__

struct ip_datagram_hole {
	u16 dh_prev; /* Absolute offset (i.e. offset from `dg_buf') to the
	              * previous hole (or 0xffff if this is the last one) */
	u16 dh_end;  /* Offset of the first byte no longer apart of this hole. */
};

union ip_datagram_id {
	/* The following 3 fields are used for datagram identification
	 * s.a. `BUFID <- source|destination|protocol|identification;'
	 * in rfc791 (https://tools.ietf.org/html/rfc791#page-28)
	 * Since KOS isn't designed for packet routing, we don't account
	 * for the destination IP, but discard any packet not specifying
	 * us (or broadcast) at an earlier step. */
	struct {
		struct in_addr dg_src;  /* Source IP */
		be16           dg_did;  /* Datagram ID */
		u8             dg_pro;  /* IP Protocol number */
		u8            _dg_pad;  /* Always 0 */
	};
	u64                dg_uid;  /* Identifier used during lookup */
};

#define IP_DATAGRAM_FLAG_NORMAL  0x0000
#define IP_DATAGRAM_FLAG_GOTLAST 0x0001 /* The last fragment has already been received. */

struct iphdr;
struct ip_datagram {
	union ip_datagram_id dg_id;  /* [const] Datagram identification */
	time_t               dg_tmo; /* [lock(:network_ip_datagrams::nid_lock)]
	                              * `realtime()' timeout for when this datagram should be discarded.
	                              * Set to 60 seconds after the first fragment has arrived
	                              * (s.a. https://tools.ietf.org/html/rfc2460#page-22) */
	u32                  dg_flg; /* [lock(:network_ip_datagrams::nid_lock)] Set of `IP_DATAGRAM_FLAG_*' */
	u16                  dg_len; /* [lock(:network_ip_datagrams::nid_lock)]
	                              * [const_if(IP_DATAGRAM_FLAG_GOTLAST)][>= 20]
	                              * Current total datagram length */
	u16                  dg_hol; /* [lock(:network_ip_datagrams::nid_lock)]
	                              * Offset into `dg_buf' to the last ~hole~ (s.a. rfc815)
	                              * The structure used for this is `struct ip_datagram_hole'
	                              * Set to `0xffff' is no holes are present (in which case the
	                              * datagram may still be incomplete when `IP_DATAGRAM_FLAG_GOTLAST'
	                              * hasn't been set, yet) */
	struct iphdr        *dg_buf; /* [1..dg_len][owned] Packet buffer. */
};


/* Route a given IP packet.
 * @assume(packet_size >= 20); */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
ip_routepacket(struct nic_device *__restrict dev,
               void const *__restrict packet_data,
               size_t packet_size);

/* Route an IP datagram after it has been fully re-assembled.
 * NOTE: The following fields of `packet' should be ignored and may contain invalid values:
 *   - packet->ip_len  (use `htons(packet_size)' instead)
 *   - packet->ip_sum  (re-calculate if needed)
 * @param: packet_size: == ntohs(packet->ip_len);
 * @assume(packet_size >= 20); */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
ip_routedatagram(struct nic_device *__restrict dev,
                 struct iphdr const *__restrict packet,
                 u16 packet_size);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_IP_H */
