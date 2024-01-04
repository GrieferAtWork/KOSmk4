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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_IP_H
#define GUARD_KERNEL_INCLUDE_NETWORK_IP_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/malloc.h>
#include <kernel/types.h>

#include <bits/os/timespec.h>
#include <netinet/ip.h>
#include <network/ethernet.h>

DECL_BEGIN

/* IP packet requirements */
#define IP_PACKET_HEADSIZE (ETH_PACKET_HEADSIZE + 20)
#define IP_PACKET_TAILSIZE (ETH_PACKET_TAILSIZE)

#ifdef __CC__

struct ip_datagram_hole {
	u16 dh_prev; /* Absolute offset (i.e. offset from `dg_buf') to the
	              * previous hole (or 0xffff if this is the last  one) */
	u16 dh_end;  /* Offset of the first byte no longer apart of this hole. */
};

union ip_datagram_id {
	/* The following 3 fields  are used for datagram  identification
	 * s.a.   `BUFID <- source|destination|protocol|identification;'
	 * in    rfc791     (https://tools.ietf.org/html/rfc791#page-28)
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
	                              * Set  to  60  seconds  after  the  first  fragment  has   arrived
	                              * (s.a. https://tools.ietf.org/html/rfc2460#page-22) */
	u32                  dg_flg; /* [lock(:network_ip_datagrams::nid_lock)] Set of `IP_DATAGRAM_FLAG_*' */
	u16                  dg_len; /* [lock(:network_ip_datagrams::nid_lock)]
	                              * [const_if(IP_DATAGRAM_FLAG_GOTLAST)][>= 20]
	                              * Current total datagram length */
	u16                  dg_hol; /* [lock(:network_ip_datagrams::nid_lock)]
	                              * Offset  into  `dg_buf'   to  the  last   ~hole~  (s.a.   rfc815)
	                              * The  structure  used   for  this  is   `struct ip_datagram_hole'
	                              * Set  to  `0xffff' is  no holes  are present  (in which  case the
	                              * datagram may still be incomplete when `IP_DATAGRAM_FLAG_GOTLAST'
	                              * hasn't been set, yet) */
	struct iphdr        *dg_buf; /* [1..dg_len][owned] Packet buffer. */
};


/* Route a given IP packet.
 * @assume(packet_size >= 20); */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
ip_routepacket(struct nicdev *__restrict dev,
               void const *__restrict packet_data,
               size_t packet_size);

/* Route an IP datagram after it has been fully re-assembled.
 * @assume(packet->ip_hl >= 5);
 * @assume(packet_size >= 20); */
FUNDEF NOBLOCK NONNULL((1, 2)) void KCALL
ip_routedatagram(struct nicdev *__restrict dev,
                 struct iphdr const *__restrict packet,
                 u16 packet_size);

/* Send a given IP datagram packet `packet'.
 * NOTE: The caller is responsible to ensure that `packet'
 *       still  has sufficient head/tail memory to include
 *       ethernet headers.
 * Or in other words, this function assumes that:
 * >> assert(nic_packet_headfree(packet) >= ETH_PACKET_HEADSIZE);
 * >> assert(nic_packet_tailfree(packet) >= ETH_PACKET_TAILSIZE);
 * - Additionally,  the  caller  is  responsible  to  ensure  that   the
 *   partially initialized IP  header (i.e.  `struct iphdr') is  pointed
 *   to  by  `packet->np_head' upon  entry,  as this  function  will try
 *   to read/write from that structure in order to figure out addressing
 *   information  required  for  filling in  information  for underlying
 *   network layers.
 * - NOTE: If necessary, this function will also perform the required
 *         ARP network traffic  in order to  translate the target  IP
 *         address pointed to by the IP header of `packet'.
 *         This is done asynchronously, and transparently to the caller.
 * NOTE: This function automatically fills in the following fields of the IP header:
 *   - ip_v      (With the value `4')
 *   - ip_len    (With the value `nic_packet_size(packet)')
 *   - ip_id     (using `struct net_peeraddr::npa_ipgramid')
 *   - ip_off    (as required for fragmentation; the RF and DF flags are not overwritten!)
 *   - ip_sum    (Only if not done by hardware, then will be filled with the correct value)
 * With this in mind, the caller must have already filled in:
 *   - ip_hl     (header length divided by 4; set to `5' if no IP options are present)
 *   - ip_tos    (Type of IP service)
 *   - ip_off.RF (Should already be cleared)
 *   - ip_off.DF (Don't-fragment flag)
 *   - ip_ttl    (Time to live)
 *   - ip_p      (IP Protocol; One of `IPPROTO_*')
 *   - ip_src    (Sender IP address (usually `dev->nd_addr.na_ip', or a broadcast IP))
 *   - ip_dst    (Target IP address) */
FUNDEF NONNULL((1, 2, 3)) void KCALL
ip_senddatagram(struct nicdev *__restrict dev,
                struct nic_packet *__restrict packet,
                struct aio_handle *__restrict aio);

struct nic_packet_desc;

/* Similar to `ip_senddatagram()',  however instead of  taking a  NIC
 * packet object, this function takes a packet descriptor. With  this
 * in mind, this function is more efficient in cases where the caller
 * isn't given a packet object, but rather, is presented with an I/O-
 * vector, or similar.
 * Note however that if you've been given a NIC packet, you should really
 * use the above function instead, since  doing so reduces the amount  of
 * copying necessary when the datagram can fit into a single fragment.
 * NOTE: This function automatically fills in the following fields of the IP header:
 *   - ip_v      (With the value `4')
 *   - ip_len    (With the value `nic_packet_size(packet)')
 *   - ip_id     (using `struct net_peeraddr::npa_ipgramid')
 *   - ip_off    (as required for fragmentation; the RF and DF flags are not overwritten!)
 *   - ip_sum    (Only if not done by hardware, then will be filled with the correct value)
 * With this in mind, the caller must have already filled in:
 *   - ip_hl     (header length divided by 4; set to `5' if no IP options are present)
 *   - ip_tos    (Type of IP service)
 *   - ip_off.RF (Should already be cleared)
 *   - ip_off.DF (Don't-fragment flag)
 *   - ip_ttl    (Time to live)
 *   - ip_p      (IP Protocol; One of `IPPROTO_*')
 *   - ip_src    (Sender IP address (usually `dev->nd_addr.na_ip', or a broadcast IP))
 *   - ip_dst    (Target IP address) */
FUNDEF NONNULL((1, 2, 3)) void KCALL
ip_senddatagram_ex(struct nicdev *__restrict dev,
                   struct nic_packet_desc const *__restrict packet,
                   struct aio_handle *__restrict aio);



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_IP_H */
