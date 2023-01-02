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
#ifndef GUARD_KERNEL_INCLUDE_NETWORK_PACKET_H
#define GUARD_KERNEL_INCLUDE_NETWORK_PACKET_H 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/types.h>

DECL_BEGIN

#ifdef __CC__

struct nic_packetlist {
	size_t                  npl_cnt;    /* # of used packets */
	REF struct nic_packet **npl_vec;    /* [1..1][0..npl_cnt][owned_if(npl_vec != npl_sta)] Vector of packets. */
	REF struct nic_packet  *npl_sta[4]; /* [1..1][0..npl_cnt][valid_if(npl_vec == npl_sta)] Pre-allocated packets array. */
};

/* Initialize a given packet list */
#define nic_packetlist_init(self) \
	((self)->npl_cnt = 0, (self)->npl_vec = (self)->npl_sta)

/* Finalize a given packet list */
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_packetlist_fini)(struct nic_packetlist *__restrict self) {
	size_t i;
	for (i = 0; i < self->npl_cnt; ++i)
		decref_unlikely(self->npl_vec[i]);
	if (self->npl_vec != self->npl_sta)
		kfree(self->npl_vec);
}

/* Append the given packet to `self'
 * @return: * : Always re-returns `packet' */
FUNDEF ATTR_RETNONNULL NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_append(struct nic_packetlist *__restrict self,
                      struct nic_packet *__restrict packet)
		THROWS(E_BADALLOC);

/* Truncate the length of the given packet list to `new_count'
 * @assume(new_count <= self->npl_cnt); */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_packetlist_truncate)(struct nic_packetlist *__restrict self,
                                       size_t new_count);

/* Reserve vector space for at least `total_count' packet references. */
FUNDEF NONNULL((1)) void KCALL
nic_packetlist_reserve(struct nic_packetlist *__restrict self,
                       size_t total_count)
		THROWS(E_BADALLOC);

/* Allocate a new NIC packet and append it to the given packet list. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_newpacket(struct nic_packetlist *__restrict self,
                         struct nicdev const *__restrict dev,
                         USER CHECKED void const *payload, size_t payload_size,
                         size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_newpacketv(struct nic_packetlist *__restrict self,
                          struct nicdev const *__restrict dev,
                          struct iov_buffer const *__restrict payload,
                          size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_newpacketh(struct nic_packetlist *__restrict self,
                          struct nicdev const *__restrict dev,
                          size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC);
/* @return: * : A buffer of `buffer_size' bytes */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *KCALL
nic_packetlist_newpacketk(struct nic_packetlist *__restrict self,
                          struct nicdev const *__restrict dev,
                          size_t buffer_size)
		THROWS(E_BADALLOC);



/* Send all of the packets within the given packet-size. */
FUNDEF NONNULL((1, 2, 3)) void KCALL
nic_device_sendall(struct nicdev *__restrict self,
                   struct nic_packetlist const *__restrict packets,
                   struct aio_multihandle *__restrict aio);

/* Same as `nic_device_sendall()', however handle _all_ exceptions as AIO-failures
 * WARNING:    This    function    may   still    clobber    exception   pointers! */
FUNDEF NONNULL((1, 2, 3)) void
NOTHROW(KCALL nic_device_sendall_nx)(struct nicdev *__restrict self,
                                     struct nic_packetlist const *__restrict packets,
                                     struct aio_multihandle *__restrict aio);

/* Send the given packet in the background (s.a. `aio_handle_async_alloc()')
 * NOTE:  Transmit   errors  get   logged,  but   are  silently   discarded. */
FUNDEF NONNULL((1, 2)) void KCALL
nic_device_sendall_background(struct nicdev *__restrict self,
                              struct nic_packetlist const *__restrict packets);





/************************************************************************/
/* Packet splitting support                                             */
/************************************************************************/

struct nic_packet_desc {
	byte_t           *npd_head;      /* [0..np_headsz] Start of headers */
	size_t            npd_headsz;    /* Size of headers */
	byte_t           *npd_tail;      /* [0..npd_tailsz] Start of footers */
	size_t            npd_tailsz;    /* Size of footers */
	struct iov_buffer npd_payload;   /* Packet payload data. */
	size_t            npd_payloadsz; /* [== iov_buffer_size(&np_payload)] Total payload size (in bytes) */
};

/* Return the size of some part of a given NIC packet descriptor. */
#define nic_packet_desc_headsize(self)     (self)->npd_headsz
#define nic_packet_desc_tailsize(self)     (self)->npd_tailsz
#define nic_packet_desc_headtailsize(self) ((self)->npd_headsz + (self)->npd_tailsz)

/* Return the total size of a give NIC packet descriptor. */
#define nic_packet_desc_size(self) \
	((self)->npd_headsz + (self)->npd_tailsz + (self)->npd_payloadsz)


/* Initialize a given abstract NIC packet descriptor from a NIC packet. */
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL nic_packet_desc_for_packet)(struct nic_packet_desc *__restrict self,
                                          struct nic_packet const *__restrict packet) {
	self->npd_head      = packet->np_head;
	self->npd_headsz    = nic_packet_headsize(packet);
	self->npd_tail      = packet->np_tail;
	self->npd_tailsz    = nic_packet_headsize(packet);
	self->npd_payloadsz = packet->np_payloads;
	if (packet->np_payloadc) {
		self->npd_payload.iv_entc = packet->np_payloadc;
		self->npd_payload.iv_entv = packet->np_payloadv;
		self->npd_payload.iv_head = packet->np_payloadv[0];
		self->npd_payload.iv_last = packet->np_payloadv[packet->np_payloadc - 1].ive_size;
	} else {
		self->npd_payload.iv_entc         = 1;
		self->npd_payload.iv_entv         = __NULLPTR;
		self->npd_payload.iv_head.ive_base = __NULLPTR;
		self->npd_payload.iv_head.ive_size = 0;
		self->npd_payload.iv_last         = 0;
	}
}

/* Extended version of `nic_packetlist_segments()'
 * NOTE: Memory from `packet->npd_head' and `packet->npd_tail'  will
 *       be hard-copied into the  new packets as implicit  head/tail
 *       data objects. In other words: Only `npd_payload' has to  be
 *       kept valid  until after  the packet  has been  fully  sent.
 *       As such, head/tail is meant to be used for kernel-generated
 *       descriptors,  while the payload may also contain user-space
 *       data.
 * HINT: After this call, you may assume:
 * >> for (i = self->npl_cnt - return; i < self->npl_cnt; ++i) {
 * >>     assert(nic_packet_size(self->npl_vec[i]) <= max_segment_payload_size);
 * >>     assert(nic_packet_headfree(self->npl_vec[i]) >= max_segment_head_size);
 * >>     assert(nic_packet_tailfree(self->npl_vec[i]) >= max_segment_tail_size);
 * >> } */
FUNDEF NONNULL((1, 2, 3)) size_t KCALL
nic_packetlist_segments_ex(struct nic_packetlist *__restrict self,
                           struct nicdev *__restrict dev,
                           struct nic_packet_desc const *__restrict packet,
                           size_t max_segment_payload_size,
                           size_t max_segment_head_size,
                           size_t max_segment_tail_size)
		THROWS(E_BADALLOC);

/* Split `packet' into  multiple packets that  are added to  `self'
 * All packets have a real max-size of `max_segment_payload_size  +
 * max_segment_head_size + max_segment_tail_size', where the latter
 * two are optional addend that have to be allocated through use of
 * the `nic_packet_alloc(head|tail)(...)' functions.
 * @return: * : [!0] The number of newly created packets
 *                   Note that even in the even that the given `packet'
 *                   is entirely empty, this will still be at least  1! */
LOCAL NONNULL((1, 2, 3)) size_t KCALL
nic_packetlist_segments(struct nic_packetlist *__restrict self,
                        struct nicdev *__restrict dev,
                        struct nic_packet const *__restrict packet,
                        size_t max_segment_payload_size,
                        size_t max_segment_head_size,
                        size_t max_segment_tail_size)
		THROWS(E_BADALLOC) {
	struct nic_packet_desc desc;
	nic_packet_desc_for_packet(&desc, packet);
	return nic_packetlist_segments_ex(self, dev, &desc,
	                                  max_segment_payload_size,
	                                  max_segment_head_size,
	                                  max_segment_tail_size);
}


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_NETWORK_PACKET_H */
