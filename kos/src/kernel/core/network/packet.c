/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_NETWORK_PACKET_C
#define GUARD_KERNEL_SRC_NETWORK_PACKET_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/nic.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/iovec.h>

#include <hybrid/align.h>

#include <network/packet.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Append the given packet to `self'
 * @return: * : Always re-returns `packet' */
PRIVATE ATTR_RETNONNULL NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_append_inherit(struct nic_packetlist *__restrict self,
                              /*inherit(always)*/ REF struct nic_packet *__restrict packet)
		THROWS(E_BADALLOC) {
	size_t alloc = lengthof(self->npl_sta);
	if (self->npl_vec != self->npl_sta)
		alloc = kmalloc_usable_size(self->npl_vec) / sizeof(REF struct nic_packet *);
	assert(self->npl_cnt <= alloc);
	if (self->npl_cnt >= alloc) {
		REF struct nic_packet **new_vector;
		size_t new_alloc = self->npl_cnt * 2;
		assert(new_alloc > self->npl_cnt);
		new_vector = self->npl_vec == self->npl_sta
		             ? (REF struct nic_packet **)kmalloc_nx(new_alloc * sizeof(REF struct nic_packet *), GFP_NORMAL)
		             : (REF struct nic_packet **)krealloc_nx(self->npl_vec,
		                                                     new_alloc * sizeof(REF struct nic_packet *),
		                                                     GFP_NORMAL);
		if unlikely(!new_vector) {
			new_alloc  = self->npl_cnt + 1;
			TRY {
				new_vector = self->npl_vec == self->npl_sta
				             ? (REF struct nic_packet **)kmalloc(new_alloc * sizeof(REF struct nic_packet *), GFP_NORMAL)
				             : (REF struct nic_packet **)krealloc(self->npl_vec,
				                                                  new_alloc * sizeof(REF struct nic_packet *),
				                                                  GFP_NORMAL);
			} EXCEPT {
				decref(packet); /* inherit(always) */
				RETHROW();
			}
		}
		self->npl_vec = new_vector;
	}
	self->npl_vec[self->npl_cnt++] = packet; /* Inherit reference */
	return packet;
}

/* Append the given packet to `self'
 * @return: * : Always re-returns `packet' */
PUBLIC ATTR_RETNONNULL NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_append(struct nic_packetlist *__restrict self,
                      struct nic_packet *__restrict packet)
		THROWS(E_BADALLOC) {
	return nic_packetlist_append_inherit(self, incref(packet));
}

/* Truncate the length of the given packet list to `new_count'
 * @assume(new_count <= self->npl_cnt); */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL nic_packetlist_truncate)(struct nic_packetlist *__restrict self,
                                       size_t new_count) {
	size_t i;
	REF struct nic_packet **new_vector;
	assert(new_count <= self->npl_cnt);
	/* Drop references from packets that got removed. */
	for (i = new_count; i < self->npl_cnt; ++i)
		decref_likely(self->npl_vec[i]);
	/* Set the new vector size. */
	self->npl_cnt = new_count;
	if (self->npl_vec != self->npl_sta) {
		if (new_count <= lengthof(self->npl_sta)) {
			/* Switch over to the static vector. */
			memcpy(self->npl_sta, self->npl_vec,
			       new_count, sizeof(REF struct nic_packet *));
			kfree(self->npl_vec);
			self->npl_vec = self->npl_sta;
		} else {
			/* Try to truncate the allocated vector size. */
			new_vector = (REF struct nic_packet **)krealloc_nx(self->npl_vec,
			                                                   new_count * sizeof(REF struct nic_packet *),
			                                                   GFP_ATOMIC);
			if likely(new_vector)
				self->npl_vec = new_vector;
		}
	}
}

/* Reserve vector space for at least `total_count' packet references. */
PUBLIC NONNULL((1)) void KCALL
nic_packetlist_reserve(struct nic_packetlist *__restrict self,
                       size_t total_count)
		THROWS(E_BADALLOC) {
	size_t alloc;
	REF struct nic_packet **new_vector;
	if (total_count <= lengthof(self->npl_sta))
		return;
	if (self->npl_vec == self->npl_sta) {
		new_vector = (REF struct nic_packet **)kmalloc(total_count * sizeof(REF struct nic_packet *), GFP_NORMAL);
		memcpy(new_vector, self->npl_sta, self->npl_cnt, sizeof(REF struct nic_packet *));
		self->npl_vec = new_vector;
		return;
	}
	alloc = kmalloc_usable_size(self->npl_vec) / sizeof(REF struct nic_packet *);
	if (total_count <= alloc)
		return;
	new_vector = (REF struct nic_packet **)krealloc(self->npl_vec,
	                                                total_count * sizeof(REF struct nic_packet *),
	                                                GFP_NORMAL);
	self->npl_vec = new_vector;
}


/* Allocate a new NIC packet and append it to the given packet list. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_newpacket(struct nic_packetlist *__restrict self,
                         struct nicdev const *__restrict dev,
                         NCX void const *payload, size_t payload_size,
                         size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *packet;
	packet = nicdev_newpacket(dev, payload, payload_size,
	                              max_head_size, max_tail_size);
	return nic_packetlist_append_inherit(self, packet);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_newpacketv(struct nic_packetlist *__restrict self,
                          struct nicdev const *__restrict dev,
                          struct iov_buffer const *__restrict payload,
                          size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *packet;
	packet = nicdev_newpacketv(dev, payload, max_head_size, max_tail_size);
	return nic_packetlist_append_inherit(self, packet);
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct nic_packet *KCALL
nic_packetlist_newpacketh(struct nic_packetlist *__restrict self,
                          struct nicdev const *__restrict dev,
                          size_t max_head_size, size_t max_tail_size)
		THROWS(E_BADALLOC) {
	REF struct nic_packet *packet;
	packet = nicdev_newpacketh(dev, max_head_size, max_tail_size);
	return nic_packetlist_append_inherit(self, packet);
}

/* @return: * : A buffer of `buffer_size' bytes */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) void *KCALL
nic_packetlist_newpacketk(struct nic_packetlist *__restrict self,
                          struct nicdev const *__restrict dev,
                          size_t buffer_size)
		THROWS(E_BADALLOC) {
	void *result;
	REF struct nic_packet *packet;
	packet = nicdev_newpacketk(dev, &result, buffer_size);
	nic_packetlist_append_inherit(self, packet);
	return result;
}


/* Send all of the packets within the given packet-size. */
PUBLIC NONNULL((1, 2, 3)) void KCALL
nic_device_sendall(struct nicdev *__restrict self,
                   struct nic_packetlist const *__restrict packets,
                   struct aio_multihandle *__restrict aio) {
	TRY {
		size_t i;
		for (i = 0; i < packets->npl_cnt; ++i) {
			struct aio_handle *hand;
			hand = aio_multihandle_allochandle(aio);
			nicdev_send(self, packets->npl_vec[i], hand);
		}
	} EXCEPT {
		aio_multihandle_done(aio);
		aio_multihandle_cancel(aio);
		RETHROW();
	}
}


/* Same as `nic_device_sendall()', however handle _all_ exceptions as AIO-failures
 * WARNING: This function may still clobber exception pointers! */
PUBLIC NONNULL((1, 2, 3)) void
NOTHROW(KCALL nic_device_sendall_nx)(struct nicdev *__restrict self,
                                     struct nic_packetlist const *__restrict packets,
                                     struct aio_multihandle *__restrict aio) {
	TRY {
		size_t i;
		for (i = 0; i < packets->npl_cnt; ++i) {
			struct aio_handle *hand;
			hand = aio_multihandle_allochandle(aio);
			nicdev_send(self, packets->npl_vec[i], hand);
		}
	} EXCEPT {
		aio_multihandle_fail(aio);
	}
}

/* Send the given packet in the background (s.a. `aio_handle_async_alloc()')
 * NOTE: Transmit errors get logged, but are silently discarded. */
PUBLIC NONNULL((1, 2)) void KCALL
nic_device_sendall_background(struct nicdev *__restrict self,
                              struct nic_packetlist const *__restrict packets) {
	size_t i;
	/* XXX: Cancel already started packets on error! */
	for (i = 0; i < packets->npl_cnt; ++i)
		nicdev_send_background(self, packets->npl_vec[i]);
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
PUBLIC NONNULL((1, 2, 3)) size_t KCALL
nic_packetlist_segments_ex(struct nic_packetlist *__restrict self,
                           struct nicdev *__restrict dev,
                           struct nic_packet_desc const *__restrict packet,
                           size_t max_segment_payload_size,
                           size_t max_segment_head_size,
                           size_t max_segment_tail_size)
		THROWS(E_BADALLOC) {
	size_t old_size, result, total_size;
	assert(max_segment_payload_size != 0);
	old_size   = self->npl_cnt;
	total_size = nic_packet_desc_size(packet);
	result     = CEILDIV(total_size, max_segment_payload_size);
	nic_packetlist_reserve(self, self->npl_cnt + result);
	TRY {
		byte_t *head, *tail;
		size_t headsz, tailsz;
		struct nic_packet *pck;
		void *pck_buf;
		head   = packet->npd_head;
		headsz = packet->npd_headsz;
		tail   = packet->npd_tail;
		tailsz = packet->npd_tailsz;
		/* Construct whole packets for header data. */
		while unlikely(headsz >= max_segment_payload_size) {
			pck = nic_packetlist_newpacketh(self, dev,
			                                max_segment_head_size +
			                                max_segment_payload_size,
			                                max_segment_tail_size);
			pck_buf = nic_packet_allochead(pck, max_segment_payload_size);
			memcpy(pck_buf, head, max_segment_payload_size);
			head += max_segment_payload_size;
			headsz -= max_segment_payload_size;
		}
		if (packet->npd_payloadsz == 0) {
			size_t packet_rem;
			packet_rem = max_segment_payload_size - headsz;
			if (packet_rem > tailsz)
				packet_rem = tailsz;
			pck = nic_packetlist_newpacketh(self, dev,
			                                max_segment_head_size + headsz,
			                                packet_rem + max_segment_tail_size);
			pck_buf = nic_packet_allochead(pck, headsz);
			memcpy(pck_buf, head, headsz); /* The remainder of header data. */
			/* Copy tail data */
			pck_buf = nic_packet_allochead(pck, packet_rem);
			memcpy(pck_buf, tail, packet_rem); /* The remainder of header data. */
			tail += packet_rem;
			tailsz -= packet_rem;
		} else {
			/* Include the payload */
			size_t payload_offset, payloadsz;
			payloadsz = packet->npd_payloadsz;
			payload_offset = 0;
			if (headsz) {
				size_t used_payloadsz;
				used_payloadsz = max_segment_head_size - headsz;
				assert(used_payloadsz != 0);
				if (used_payloadsz <= payloadsz) {
					/* head(remainder) + payload(start) */
					struct iov_buffer buf;
					iov_buffer_init_view_before(&buf, &packet->npd_payload, used_payloadsz);
					pck = nic_packetlist_newpacketv(self, dev, &buf,
					                                max_segment_head_size + headsz,
					                                max_segment_tail_size);
					assert(pck->np_payloads == used_payloadsz);
					pck_buf = nic_packet_allochead(pck, headsz);
					memcpy(pck_buf, head, headsz); /* The remainder of header data. */
					payloadsz -= used_payloadsz;
					if (!payloadsz)
						goto done_payload;
					payload_offset = used_payloadsz;
				} else {
					/* head(remainder) + payload + tail(start) */
					size_t used_tailsz;
					assert((headsz + payloadsz) < max_segment_head_size);
					used_tailsz = max_segment_head_size - (headsz + payloadsz);
					if (used_tailsz > tailsz)
						used_tailsz = tailsz;
					pck = nic_packetlist_newpacketv(self, dev, &packet->npd_payload,
					                                max_segment_head_size + headsz,
					                                used_tailsz + max_segment_tail_size);
					pck_buf = nic_packet_allochead(pck, headsz);
					memcpy(pck_buf, head, headsz); /* The remainder of header data. */
					pck_buf = nic_packet_alloctail(pck, used_tailsz);
					memcpy(pck_buf, tail, used_tailsz); /* The start of tail data. */
					tail += used_tailsz;
					tailsz -= used_tailsz;
					goto done_payload;
				}
			}
			/* Create packets for whole-packet payload segments. */
			while (payloadsz >= max_segment_payload_size) {
				struct iov_buffer buf;
				iov_buffer_init_view(&buf, &packet->npd_payload,
				                     payload_offset, max_segment_payload_size);
#ifdef NDEBUG
				nic_packetlist_newpacketv(self, dev, &packet->npd_payload,
				                          max_segment_head_size,
				                          max_segment_tail_size);
#else /* NDEBUG */
				pck = nic_packetlist_newpacketv(self, dev, &packet->npd_payload,
				                                max_segment_head_size,
				                                max_segment_tail_size);
				assert(pck->np_payloads == max_segment_payload_size);
#endif /* !NDEBUG */
				payload_offset += max_segment_payload_size;
				payloadsz -= max_segment_payload_size;
			}
			if (payloadsz) {
				/* Include the remainder of the payload with the start of tail data. */
				size_t used_tailsz;
				struct iov_buffer buf;
				iov_buffer_init_view_after(&buf, &packet->npd_payload, payload_offset);
				used_tailsz = max_segment_payload_size - payloadsz;
				if (used_tailsz > tailsz)
					used_tailsz = tailsz;
				pck = nic_packetlist_newpacketv(self, dev, &packet->npd_payload,
				                                max_segment_head_size,
				                                used_tailsz + max_segment_tail_size);
				assert(pck->np_payloads == payloadsz);
				pck_buf = nic_packet_alloctail(pck, used_tailsz);
				memcpy(pck_buf, tail, used_tailsz); /* The start of tail data. */
				tail += used_tailsz;
				tailsz -= used_tailsz;
			}
		}
		/* Fill in remaining tail data packets. */
done_payload:
		while unlikely(tailsz) {
			size_t temp = tailsz;
			if (temp > max_segment_payload_size)
				temp = max_segment_payload_size;
			pck = nic_packetlist_newpacketh(self, dev,
			                                max_segment_head_size,
			                                temp + max_segment_tail_size);
			pck_buf = nic_packet_alloctail(pck, temp);
			memcpy(pck_buf, tail, temp);
			tail += temp;
			tailsz -= temp;
		}
	} EXCEPT {
		nic_packetlist_truncate(self, old_size);
		RETHROW();
	}
	assertf(self->npl_cnt == old_size + result,
	        "self->npl_cnt = %" PRIuSIZ "\n"
	        "old_size      = %" PRIuSIZ "\n"
	        "result        = %" PRIuSIZ "\n",
	        self->npl_cnt, old_size, result);
#ifndef NDEBUG
	{
		size_t i;
		for (i = old_size; i < self->npl_cnt; ++i) {
			assert(nic_packet_size(self->npl_vec[i]) <= max_segment_payload_size);
			assert(nic_packet_headfree(self->npl_vec[i]) >= max_segment_head_size);
			assert(nic_packet_tailfree(self->npl_vec[i]) >= max_segment_tail_size);
		}
	}
#endif /* !NDEBUG */
	return result;
}





DECL_END

#endif /* !GUARD_KERNEL_SRC_NETWORK_PACKET_C */
