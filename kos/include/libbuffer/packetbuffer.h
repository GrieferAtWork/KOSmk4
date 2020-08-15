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
#ifndef _LIBBUFFER_PACKETBUFFER_H
#define _LIBBUFFER_PACKETBUFFER_H 1

#include "api.h"

#include <hybrid/sync/atomic-rwlock.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/hybrid/sched-signal.h>

#ifndef __INTELLISENSE__
#include <hybrid/__atomic.h>
#endif /* !__INTELLISENSE__ */

/* Implementation of the general-purpose packet-buffer
 * used to implement kernel-space socket queues. */


/* Min alignment of all packet buffer data. */
#define PACKET_BUFFER_ALIGNMENT 8

#ifdef __CC__
__DECL_BEGIN

#ifdef __KERNEL__
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_kernel
#else /* __KERNEL__ */
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_not_kernel
#endif /* !__KERNEL__ */

#define PB_PACKET_STATE_UNDEF    0 /* Undefined packet state (cannot happen) */
#define PB_PACKET_STATE_INIT     1 /* Packet is being initialized. This state may transition to:
                                    * - PB_PACKET_STATE_READABLE  (s.a. `pb_buffer_packet_commit()')
                                    * - PB_PACKET_STATE_DISCARD   (s.a. `pb_buffer_packet_abort()') */
#define PB_PACKET_STATE_READABLE 2 /* Packet is available to be read. */
#define PB_PACKET_STATE_READING  3 /* Packet is currently being read. */
#define PB_PACKET_STATE_DISCARD  4 /* Packet has been discarded. */
#define PB_PACKET_STATE_INUSE(x) ((x) & 1) /* Check if a given packet is in use, and mustn't be realloc()'ed */


#define PB_PACKET_HEADER_SIZE   8
#define PB_PACKET_NEXTLINK_SIZE (8 + 2 * __SIZEOF_POINTER__)
struct pb_packet {
	__uint16_t p_total;     /* [!0][const] Total size size of the packet (in bytes, including this
	                         * header and any trailing data used for padding, as well as ancillary data)
	                         * NOTE: Aligned by `PACKET_BUFFER_ALIGNMENT' */
	__uint16_t p_payload;   /* [lock(p_state == PB_PACKET_STATE_READABLE)] Size of the packet's payload
	                         * (located immediately after the header) NOTE: Allowed to be ZERO(0) */
	__uint16_t p_ancillary; /* [lock(p_state == PB_PACKET_STATE_READABLE)] Size of ancillary data
	                         * (in bytes; located at the next `PACKET_BUFFER_ALIGNMENT'
	                         * aligned address after the payload, and spans for `p_ancillary')
	                         * With that in mind:
	                         * >> `PB_PACKET_HEADER_SIZE + p_payload + p_ancillary <= p_total' */
	__uint16_t p_state;     /* [lock(pb_lock)] Packet state (one of `PB_PACKET_STATE_*') */
#if 0
	__byte_t  p_payload_data[p_payload];
	__byte_t _p_ancillary_align[ALIGN(PACKET_BUFFER_ALIGNMENT)];
	__byte_t  p_ancillary_data[p_ancillary];
#endif
	struct pb_packet *p_cont; /* [1..1][valid_if(p_total == 0)] Pointer to the first packet of the next buffer. */
	__byte_t         *p_base; /* [1..1][valid_if(p_total == 0)][owned] Base address of the buffer which this packet terminates. */
};


struct pb_buffer {
	/* Buffer API:
	 *
	 * >> struct pb_packet *
	 * >> begin_read() {
	 * >>     struct pb_packet *packet;
	 * >> again:
	 * >>     lock();
	 * >> again_locked:
	 * >>     packet = pb_rptr;
	 * >>     if (packet->p_total == 0) {
	 * >>         // Packet exists the next buffer over!
	 * >>         pb_rptr = packet->p_cont;
	 * >>         unlock();
	 * >>         free(packet->p_base);
	 * >>         goto again;
	 * >>     }
	 * >>     if (packet->p_state != PB_PACKET_STATE_READABLE) {
	 * >>         if (packet->p_state == PB_PACKET_STATE_DISCARD) {
	 * >>             // Skip packet
	 * >>             pb_used -= packet->p_total;
	 * >>             pb_rptr += packet->p_total;
	 * >>             goto again_locked;
	 * >>         }
	 * >>         if (packet->p_state == PB_PACKET_STATE_INIT) {
	 * >>             // Wait for packet to become initialized
	 * >>             unlock();
	 * >>             WAIT_FOR_PACKET_TO_CHANGE_STATE_TO_READABLE_OR_DISCARD();
	 * >>             goto again;
	 * >>         }
	 * >>         unlock();
	 * >>         task_serve();  // Allow CTRL+C in case we got here recursively (e.g. through VIO)
	 * >>         task_yield();
	 * >>         goto again;
	 * >>     }
	 * >>     packet->p_state = PB_PACKET_STATE_READING;
	 * >>     unlock();
	 * >>     return packet;
	 * >> }
	 *
	 * >> end_read(bool discard_packet) {
	 * >>     struct pb_packet *packet;
	 * >>     lock();
	 * >>     packet = pb_rptr;
	 * >>     assert(packet->p_state == PB_PACKET_STATE_READING);
	 * >>     if (discard_packet) {
	 * >>         pb_used -= packet->p_total;
	 * >>         pb_rptr += packet->p_total;
	 * >>     } else {
	 * >>         packet->p_state = PB_PACKET_STATE_READABLE;
	 * >>     }
	 * >>     unlock();
	 * >> }
	 *
	 * >> struct pb_packet *
	 * >> begin_write(u16 payload_size, u16 ancillary_size) {
	 * >>     struct pb_packet *packet;
	 * >>     total_size = CEIL_ALIGN(payload_size + ancillary_size +
	 * >>                             PB_PACKET_HEADER_SIZE,
	 * >>                             PACKET_BUFFER_ALIGNMENT);
	 * >>     lock();
	 * >> again_locked:
	 * >>     if (pb_rptr == pb_wptr) {
	 * >>         // Rewind unread packet buffer
	 * >>         pb_rptr = pb_bbas;
	 * >>         pb_wptr = pb_bbas;
	 * >>     }
	 * >>     avail = pb_bend - pb_wptr;
	 * >>     if (avail <= total_size + PB_PACKET_NEXTLINK_SIZE) {
	 * >>         packet = pb_wptr;
	 * >>         packet->p_total     = total_size;
	 * >>         packet->p_payload   = payload_size;
	 * >>         packet->p_ancillary = ancillary_size;
	 * >>         packet->p_state     = PB_PACKET_STATE_INIT;
	 * >>         pb_wptr += total_size;
	 * >>         pb_used += total_size;
	 * >>         unlock();
	 * >>         return packet;
	 * >>     }
	 * >>     if (pb_used + total_size + PB_PACKET_NEXTLINK_SIZE >= pb_limt) {
	 * >>         unlock();
	 * >>         if (SHOULD_BLOCK) {
	 * >>             wait_for_packets_to_be_read();
	 * >>             goto again_locked;
	 * >>         }
	 * >>         return NULL;
	 * >>     }
	 * >>     FOR_EACH_UNREAD_PACKET(p) {
	 * >>         if (PB_PACKET_STATE_INUSE(p->p_state)) {
	 * >>             // Try to nonblocking_realloc_in_place() to get more memory
	 * >>             if (HAS_NONBLOCKING_REALLOC_IN_PLACE) {
	 * >>                 size_t minsize;
	 * >>                 minsize = (pb_wptr - pb_bbas) + total_size + PB_PACKET_NEXTLINK_SIZE;
	 * >>                 if (nonblocking_realloc_in_place(pb_bbas, minsize)) {
	 * >>                     pb_bend = buf + malloc_usable_size(pb_bbas);
	 * >>                     goto again_locked;
	 * >>                 }
	 * >>             }
	 * >>             // Cannot realloc the current buffer, but must alloc a new one
	 * >>             byte_t *buf;
	 * >> allocate_buffer_extension:
	 * >>             unlock();
	 * >>             buf = ALLOC_BUFFER_WITH_AT_LEAST(total_size + PB_PACKET_NEXTLINK_SIZE);
	 * >>             lock();
	 * >>             RECHECK_IF_WE_WOULD_STILL_GET_HERE_AFTER_THE_UNLOCK_AND_LOCK();
	 * >>             struct pb_packet *link_packet;
	 * >>             link_packet          = pb_wptr;
	 * >>             link_packet->p_total = 0;
	 * >>             link_packet->p_cont  = buf;
	 * >>             link_packet->p_base  = pb_bbas;
	 * >>             pb_wptr              = buf;
	 * >>             pb_bbas              = buf;
	 * >>             pb_bend              = buf + ALLOCATED_BUFFER_SIZE;
	 * >>             goto again_locked;
	 * >>         }
	 * >>     }
	 * >> #ifndef __OPTIMIZE_SIZE__
	 * >>     if (pb_rptr > pb_bbas && pb_rptr <= pb_bend) {
	 * >>         // Try to shift unread packets downwards,
	 * >>         // so-as to reclaim buffer space near the top.
	 * >>         size_t reclaim;
	 * >>         reclaim = (byte_t *)pb_rptr - (byte_t *)pb_bbas;
	 * >>         assert(pb_used == (size_t)((byte_t *)pb_wptr - (byte_t *)pb_rptr));
	 * >>         pb_rptr = memmovedown(pb_bbas, pb_rptr, pb_used);
	 * >>         pb_wptr -= reclaim;
	 * >>         goto again_locked;
	 * >>     }
	 * >> #endif
	 * >>     if (!HAS_NONBLOCKING_REALLOC)
	 * >>         goto allocate_buffer_extension_after_truncate;
	 * >>     {
	 * >>         byte_t *buf;
	 * >>         size_t minsize;
	 * >>         minsize = (pb_wptr - pb_bbas) + total_size + PB_PACKET_NEXTLINK_SIZE;
	 * >>         buf = NONBLOCKING_REALLOC_WITH_AT_LEAST(pb_bbas, minsize);
	 * >>         if (!buf) {
	 * >>             // Allocation failed, or would have had to block
	 * >> allocate_buffer_extension_after_truncate:
	 * >>             if (HAS_NONBLOCKING_REALLOC_IN_PLACE) {
	 * >>                 // Try to reclaim unused memory
	 * >>                 size_t final_size;
	 * >>                 final_size = (pb_wptr - pb_bbas) + PB_PACKET_NEXTLINK_SIZE;
	 * >>                 if (nonblocking_realloc_in_place(pb_bbas, final_size)) {
	 * >>                     // pb_bend = pb_bbas + final_size; // Assignment not actually needed
	 * >>                 }
	 * >>             }
	 * >>             goto allocate_buffer_extension;
	 * >>         }
	 * >>         // Reallocate read/write pointers for the new buffer
	 * >>         pb_rptr = buf + ((byte_t *)pb_rptr - (byte_t *)pb_bbas);
	 * >>         pb_wptr = buf + ((byte_t *)pb_wptr - (byte_t *)pb_bbas);
	 * >>         // Install the extended buffer
	 * >>         pb_bbas = buf;
	 * >>         pb_bend = buf + malloc_usable_size(buf);
	 * >>     }
	 * >>     goto again_locked;
	 * >> }
	 *
	 * >> commit_write(struct pb_packet *packet) {
	 * >>     ATOMIC_WRITE(packet->p_state, PB_PACKET_STATE_READABLE);
	 * >> }
	 *
	 * >> abort_write(struct pb_packet *packet) {
	 * >>     ATOMIC_WRITE(packet->p_state, PB_PACKET_STATE_DISCARD);
	 * >>     if (trylock()) {
	 * >>         // Optional: Try to reclaim unused packet memory, if the one
	 * >>         //           being discarded is still the most recent packet.
	 * >>         if (pb_wptr == (byte_t *)packet + packet->p_total) {
	 * >>             pb_used -= packet->p_total;
	 * >>             pb_wptr = packet;
	 * >>         }
	 * >>         unlock();
	 * >>     }
	 * >> }
	 *
	 */

	struct atomic_rwlock pb_lock; /* Lock for this packet buffer. */
	__byte_t            *pb_bbas; /* [lock(pb_lock)][<= pb_bend][owned] Base address of the current buffer data blob. */
	__byte_t            *pb_bend; /* [lock(pb_lock)][>= pb_bbas] End address of the current buffer data blob. */
	struct pb_packet    *pb_rptr; /* [lock(pb_lock)][1..1][valid_if(!= pb_wptr)] Pointer to the next unread packet/the packet currently being read. */
	struct pb_packet    *pb_wptr; /* [lock(pb_lock)][1..1] Offset to the end of the last unread packet. */
	__size_t             pb_used; /* [lock(pb_lock)] Amount of allocated buffer memory. */
	__WEAK __size_t      pb_limt; /* Max size of the packet buffer. */
	sched_signal_t       pb_psta; /* Signal broadcast any packet changes state to one of:
	                               *   - PB_PACKET_STATE_READABLE
	                               *   - PB_PACKET_STATE_DISCARD
	                               */
};


/* Begin construction of a new packet to-be appended to `self'
 * NOTES:
 *   - All of the packet's struct fields will have already been filled in by this function.
 *   - It is weakly undefined when a packet that was started before another was committed
 *     will be read. It may happen before, but it may also happen after.
 *   - The only guaranty in concerns to packet read order is that packets that are
 *     generated linearly by the same thread will always be read in that same order
 *     in relation to each other.
 *   - Similarly, a packet that for which `pb_buffer_packet_commit()' was caled before
 *     the call to `pb_buffer_packet_begin()' of another packet will always be read
 *     before that other packet.
 * @return: * : Pointer to the packet's descriptor. Once the caller has finished filling
 *              in the packet's contents, they must use `pb_buffer_packet_commit()' in
 *              order to make the packet available for being read.
 *              In case that packet initialization should fail, `pb_buffer_packet_abort()'
 *              may be called to undo what was previously done by this function.
 * @return: NULL: [kernel || errno == UNCHANGED] Packet too large (`pb_limt' would be exceeded)
 * @return: NULL: [kernel || errno == UNCHANGED] 
 * @return: NULL: [!kernel && errno == ENOMEM]   Failed to allocate more buffer memory
 * @throw: E_BADALLOC: [kernel]                  Failed to allocate more buffer memory */
#ifdef __KERNEL__
LIBBUFFER_DECL struct pb_packet *LIBBUFFER_CC
pb_buffer_packet_begin(struct pb_buffer *__restrict self,
                       __uint16_t payload_size,
                       __uint16_t ancillary_size)
		__THROWS(E_BADALLOC);
#else /* __KERNEL__ */
LIBBUFFER_DECL struct pb_packet *
__NOTHROW_NCX(LIBBUFFER_CC pb_buffer_packet_begin)(struct pb_buffer *__restrict self,
                                                   __uint16_t payload_size,
                                                   __uint16_t ancillary_size);
#endif /* !__KERNEL__ */

/* Commit a given `packet' to the packet stream */
LIBBUFFER_DECL void
__NOTHROW(LIBBUFFER_CC pb_buffer_packet_commit)(struct pb_buffer *__restrict self,
                                                struct pb_packet *__restrict packet);

LIBBUFFER_DECL void
__NOTHROW(LIBBUFFER_CC pb_buffer_packet_abort)(struct pb_buffer *__restrict self,
                                               struct pb_packet *__restrict packet);




#undef __KERNEL_SELECT

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBBUFFER_PACKETBUFFER_H */
