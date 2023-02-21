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
#ifndef _LIBBUFFER_PACKETBUFFER_H
#define _LIBBUFFER_PACKETBUFFER_H 1

#include "api.h"

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#include <hybrid/__overflow.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/hybrid/sched-signal.h>

#include <libc/string.h>

#ifndef __INTELLISENSE__
#ifdef __KERNEL__
#include <kernel/heap.h>
#else /* __KERNEL__ */
#include <libc/malloc.h>
#endif /* !__KERNEL__ */
#endif /* !__INTELLISENSE__ */

#ifndef __INTELLISENSE__
#include <hybrid/__atomic.h>
#endif /* !__INTELLISENSE__ */

#ifndef __CEIL_ALIGN
#define __CEIL_ALIGN(x, align) (((x) + ((align)-1)) & ~((align)-1))
#endif /* !__CEIL_ALIGN */

/* Implementation of the general-purpose packet-buffer
 * used  to  implement  kernel-space  socket   queues. */


/* Min alignment of all packet buffer data. */
#define PACKET_BUFFER_ALIGNMENT __SIZEOF_POINTER__


#define PB_PACKET_STATE_UNDEF    0 /* Undefined packet state (cannot happen) */
#define PB_PACKET_STATE_INIT     1 /* Packet is being initialized. This state may transition to:
                                    * - PB_PACKET_STATE_READABLE  (s.a. `pb_buffer_endwrite_commit()')
                                    * - PB_PACKET_STATE_DISCARD   (s.a. `pb_buffer_endwrite_abort()') */
#define PB_PACKET_STATE_READABLE 2 /* Packet is available to be read. */
#define PB_PACKET_STATE_READING  3 /* Packet is currently being read. */
#define PB_PACKET_STATE_DISCARD  4 /* Packet has been discarded. */
#define PB_PACKET_STATE_INUSE(x) ((x) & 1) /* Check if a given packet is in use, and mustn't be realloc()'ed */


#define PB_PACKET_HEADER_SIZE   8
#define PB_PACKET_NEXTLINK_SIZE (8 + 2 * __SIZEOF_POINTER__)

#ifdef __CC__
__DECL_BEGIN

struct pb_packet {
	__uint16_t p_total;     /* [!0][const]  Total  size size  of the  packet  (in bytes,  including this
	                         * header and any trailing data used for padding, as well as ancillary data)
	                         * NOTE: Aligned by `PACKET_BUFFER_ALIGNMENT' */
	__uint8_t  p_state;     /* [lock(pb_lock)] Packet state (one of `PB_PACKET_STATE_*') */
	__uint8_t  p_payoff;    /* [lock(p_state == PB_PACKET_STATE_READABLE)] Offset to the start of payload data. */
	__uint16_t p_payload;   /* [lock(p_state == PB_PACKET_STATE_READABLE)] Size of the packet's payload
	                         * (located  immediately  after the  header)  NOTE: Allowed  to  be ZERO(0) */
	__uint16_t p_ancillary; /* [lock(p_state == PB_PACKET_STATE_READABLE)] Size of ancillary data
	                         * (in   bytes;   located  at   the   next  `PACKET_BUFFER_ALIGNMENT'
	                         * aligned address after  the payload, and  spans for  `p_ancillary')
	                         * With that in mind:
	                         * >> `p_payoff + p_payload + p_ancillary <= p_total' */
	/* OFFSET_FROM_BASE == PB_PACKET_HEADER_SIZE */
#if 0
	__byte_t _p_payload_offs[p_payoff - PB_PACKET_HEADER_SIZE];
	__byte_t  p_payload_data[p_payload];
	__byte_t _p_ancillary_align[ALIGN(PACKET_BUFFER_ALIGNMENT)];
	__byte_t  p_ancillary_data[p_ancillary];
#endif
	struct pb_packet *p_cont; /* [1..1][valid_if(p_total == 0)] Pointer to the first packet of the next buffer. */
	__byte_t         *p_base; /* [1..1][valid_if(p_total == 0)][owned] Base address of the buffer which this packet terminates. */
	/* OFFSET_FROM_BASE == PB_PACKET_NEXTLINK_SIZE */
};

/* The max possible packet payload size. */
#define PB_PACKET_MAX_PAYLOAD                           \
	((0xffff - __CEIL_ALIGN(PB_PACKET_HEADER_SIZE,      \
	                        PACKET_BUFFER_ALIGNMENT)) & \
	 ~(PACKET_BUFFER_ALIGNMENT - 1))


/* Return a pointer to the payload of `self'
 * The returned pointer points to a data-blob of `self->p_payload' bytes. */
#define pb_packet_payload(self) \
	((__byte_t *)(self) + (self)->p_payoff)

/* Return a pointer to ancillary data stored within `self'
 * The returned pointer points to a data-blob of `self->p_ancillary' bytes. */
#define pb_packet_ancillary(self)                                  \
	((__byte_t *)(self) + (((self)->p_payoff + (self)->p_payload + \
	                        (PACKET_BUFFER_ALIGNMENT - 1)) &       \
	                       ~(PACKET_BUFFER_ALIGNMENT - 1)))


/* Return the base address/size of the containing buffer for buffer control packet.
 * NOTE: Buffer control packets  can be identified  by having `p_total == 0',  though
 *       also note that the public pb_buffer API never exposes buffer control packets
 *       to the user.
 * Also note that `_pb_packet_bufctl_bufsize()' is only valid when the packet-buffer
 * API was built with `#define PB_BUFFER_BLOB_FREE_NEEDS_SIZE' */
#define _pb_packet_bufctl_bufbase(self) ((self)->p_base)
#define _pb_packet_bufctl_bufsize(self) (__size_t)(((__byte_t *)(self) + (self)->p_ancillary) - (self)->p_base)


/* Packet buffer data blob free function */
#undef pb_buffer_blob_free
#undef pb_buffer_blob_free_p
#ifdef __INTELLISENSE__
#ifdef __KERNEL__
#define PB_BUFFER_BLOB_FREE_NEEDS_SIZE 1
#endif /* __KERNEL__ */
#define pb_buffer_blob_free(ptr, num_bytes)   (void)0
#define pb_buffer_blob_free_p(ptr, num_bytes) (void)0
#elif defined(__KERNEL__)
#define PB_BUFFER_BLOB_FREE_NEEDS_SIZE 1
#define pb_buffer_blob_free(ptr, num_bytes) \
	heap_free(&kernel_default_heap, ptr, num_bytes, GFP_NORMAL)
#define pb_buffer_blob_free_p(ptr, num_bytes)                            \
	((ptr) ? heap_free(&kernel_default_heap, ptr, num_bytes, GFP_NORMAL) \
	       : (void)0)
#else /* __KERNEL__ */
#undef PB_BUFFER_BLOB_FREE_NEEDS_SIZE
#define pb_buffer_blob_free(ptr, num_bytes)   __libc_free(ptr)
#define pb_buffer_blob_free_p(ptr, num_bytes) __libc_free(ptr)
#endif /* !__KERNEL__ */



struct pb_buffer {
	/* Packet buffer API:
	 *
	 * >> struct pb_packet *
	 * >> begin_read() {
	 * >>     struct pb_packet *packet;
	 * >> again:
	 * >>     lock();
	 * >> again_locked:
	 * >>     packet = pb_rptr;
	 * >>     if (packet == self->pb_wptr) {
	 * >>         // Nothing to read
	 * >>         unlock();
	 * >>         return NULL;
	 * >>     }
	 * >>     if (packet->p_total == 0) {
	 * >>         // Packet exists the next buffer over!
	 * >>         pb_rptr = packet->p_cont;
	 * >>         unlock();
	 * >>         pb_buffer_blob_free(_pb_packet_bufctl_bufbase(packet),
	 * >>                             _pb_packet_bufctl_bufsize(packet));
	 * >>         goto again;
	 * >>     }
	 * >>     if (packet->p_state != PB_PACKET_STATE_READABLE) {
	 * >>         if (packet->p_state == PB_PACKET_STATE_DISCARD) {
	 * >>             // Skip packets that were discarded
	 * >>             pb_used -= packet->p_total; // atomic!
	 * >>             pb_rptr += packet->p_total;
	 * >>             goto again_locked;
	 * >>         }
	 * >>         unlock();
	 * >>         // Let the caller handle all of the blocking.
	 * >>         return NULL;
	 * >>     }
	 * >>     packet->p_state = PB_PACKET_STATE_READING; // atomic!
	 * >>     unlock();
	 * >>     return packet;
	 * >> }
	 *
	 * >> struct pb_packet *
	 * >> NOBLOCK read_truncate(struct pb_packet *packet, uint16_t num_bytes) {
	 * >>     struct pb_packet *result;
	 * >>     uint16_t new_payload_start;
	 * >>     uint16_t new_packet_offset;
	 * >>     assert(bytes_to_consume < packet->p_payload);
	 * >>     packet->p_payload -= bytes_to_consume;
	 * >>     new_payload_start = packet->p_payoff + bytes_to_consume;
	 * >>     if (new_payload_start <= 0xff) {
	 * >>         // Simple case: Can just edit `packet->p_payoff'
	 * >>         packet->p_payoff = new_payload_start;
	 * >>         return packet;
	 * >>     }
	 * >>     // Difficult case: Must actually move the packet's header.
	 * >>     new_packet_offset = new_payload_start & ~(PACKET_BUFFER_ALIGNMENT - 1);
	 * >>     result = (struct pb_packet *)((byte_t *)packet + new_packet_offset);
	 * >>     // Fill in the new packet header.
	 * >>     result->p_total     = packet->p_total - new_packet_offset;
	 * >>     result->p_state     = PB_PACKET_STATE_READING;
	 * >>     result->p_payoff    = new_payload_start & (PACKET_BUFFER_ALIGNMENT - 1);
	 * >>     result->p_payload   = packet->p_payload;
	 * >>     result->p_ancillary = packet->p_ancillary;
	 * >>     // Account for all of the memory that just became unused.
	 * >>     pb_used -= new_packet_offset; // atomic!
	 * >>     return result;
	 * >> }
	 *
	 * // End reading, but allow `packet' to be returned by `begin_read()' once again
	 * // HINT: This is actually the same as `end_read_update()', but may assume that
	 * //       the   given   packet   pointer   hasn't   actually   been   modified.
	 * >> NOBLOCK end_read_abort(struct pb_packet *packet) {
	 * >>     assert(packet          == pb_rptr);
	 * >>     assert(packet->p_state == PB_PACKET_STATE_READING);
	 * >>     packet->p_state = PB_PACKET_STATE_READABLE; // atomic!
	 * >> }
	 *
	 * // End reading, and discard the given `packet'
	 * >> NOBLOCK end_read_consume(struct pb_packet *packet) {
	 * >>     assert(packet          == pb_rptr);
	 * >>     assert(packet->p_state == PB_PACKET_STATE_READING);
	 * >>     total    = packet->p_total; // atomic!
	 * >>     pb_used -= total;           // atomic!
	 * >>     pb_rptr += total;           // atomic!
	 * >> }
	 *
	 * >> struct pb_packet *
	 * >> begin_write(u16 payload_size, u16 ancillary_size) {
	 * >>     total_size = CEIL_ALIGN(payload_size,          PACKET_BUFFER_ALIGNMENT) +
	 * >>                  CEIL_ALIGN(ancillary_size,        PACKET_BUFFER_ALIGNMENT) +
	 * >>                  CEIL_ALIGN(PB_PACKET_HEADER_SIZE, PACKET_BUFFER_ALIGNMENT);
	 * >>     lock();
	 * >> again_locked:
	 * >>     if (pb_rptr == pb_wptr) {
	 * >>         // Rewind the packet buffer
	 * >>         pb_rptr = pb_bbas; // This must happen atomically!
	 * >>         pb_wptr = pb_bbas;
	 * >>     }
	 * >>     avail = pb_bend - pb_wptr;
	 * >>     if (avail <= total_size + PB_PACKET_NEXTLINK_SIZE) {
	 * >>         struct pb_packet *packet;
	 * >>         if (!pb_limt) {
	 * >>             // Special case: The buffer was closed
	 * >>             unlock();
	 * >>             return NULL;
	 * >>         }
	 * >>         packet = pb_wptr;
	 * >>         packet->p_total     = total_size;
	 * >>         packet->p_state     = PB_PACKET_STATE_INIT;
	 * >>         packet->p_payoff    = PB_PACKET_HEADER_SIZE;
	 * >>         packet->p_payload   = payload_size;
	 * >>         packet->p_ancillary = ancillary_size;
	 * >>         pb_wptr += total_size;
	 * >>         pb_used += total_size; // atomic!
	 * >>         unlock();
	 * >>         return packet;
	 * >>     }
	 * >>     if (pb_used + total_size >= pb_limt) {
	 * >>         unlock();
	 * >>         if (SHOULD_BLOCK) {
	 * >>             wait_for_packets_to_be_read();
	 * >>             goto again_locked;
	 * >>         }
	 * >>         return NULL;
	 * >>     }
	 * >>     FOREACH_UNREAD_PACKET(p) {
	 * >>         if (!(p >= pb_bbas && p < pb_bend))
	 * >>             continue;
	 * >>         if (PB_PACKET_STATE_INUSE(p->p_state)) {
	 * >>             // Try to NONBLOCK_REALLOC_IN_PLACE_NX() to get more memory
	 * >>             if (HAS_NONBLOCK_REALLOC_IN_PLACE_NX) {
	 * >>                 size_t minsize;
	 * >>                 minsize = (pb_wptr - pb_bbas) + total_size + PB_PACKET_NEXTLINK_SIZE;
	 * >>                 if (NONBLOCK_REALLOC_IN_PLACE_NX(pb_bbas, minsize)) {
	 * >>                     pb_bend = buf + USABLE_SIZE_OR(pb_bbas, minsize);
	 * >>                     goto again_locked;
	 * >>                 }
	 * >>             }
	 * >>             // Cannot realloc the current buffer, so must alloc a new one
	 * >>             byte_t *buf;
	 * >> allocate_buffer_extension:
	 * >> #if !defined(__OPTIMIZE_SIZE__) && defined(HAS_NONBLOCK_MALLOC_NX)
	 * >>             buf = NONBLOCK_MALLOC_NX(total_size + PB_PACKET_NEXTLINK_SIZE);
	 * >>             if (!buf)
	 * >> #endif
	 * >>             {
	 * >>                 unlock();
	 * >>                 buf = MALLOC_UNX(total_size + PB_PACKET_NEXTLINK_SIZE);
	 * >> #ifndef __KERNEL__
	 * >>                 if (!buf)
	 * >>                     return NULL;
	 * >> #endif
	 * >>                 lock();
	 * >>                 RECHECK_IF_WE_WOULD_STILL_GET_HERE_AFTER_THE_UNLOCK_AND_LOCK(
	 * >>                     IF_NOT(pb_buffer_blob_free(buf, USABLE_SIZE_OR(buf, total_size + PB_PACKET_NEXTLINK_SIZE));
	 * >>                            goto again_locked;
	 * >>                     ));
	 * >>             }
	 * >>             if (pb_rptr == pb_wptr) {
	 * >>                 pb_rptr = buf;
	 * >>                 pb_buffer_blob_free(pb_bbas,
	 * >>                                     pb_bend - pb_bbas);
	 * >>             } else {
	 * >>                 struct pb_packet *link_packet;
	 * >>                 link_packet              = pb_wptr;
	 * >>                 link_packet->p_total     = 0;
	 * >> #ifdef PB_BUFFER_BLOB_FREE_NEEDS_SIZE
	 * >>                 link_packet->p_ancillary = avail;
	 * >> #endif
	 * >>                 link_packet->p_cont      = buf;
	 * >>                 link_packet->p_base      = pb_bbas;
	 * >>             }
	 * >>             pb_wptr = buf;
	 * >>             pb_bbas = buf;
	 * >>             pb_bend = buf + ALLOCATED_BUFFER_SIZE;
	 * >>             goto again_locked;
	 * >>         }
	 * >>     }
	 * >> #ifndef __OPTIMIZE_SIZE__
	 * >>     if (pb_rptr > pb_bbas && pb_rptr <= pb_bend) {
	 * >>         // Try to shift unread packets downwards,
	 * >>         // so-as to reclaim buffer space near the top.
	 * >>         size_t reclaim, used;
	 * >>         reclaim = (byte_t *)pb_rptr - (byte_t *)pb_bbas;
	 * >>         used    = (size_t)((byte_t *)pb_wptr - (byte_t *)pb_rptr);
	 * >>         pb_rptr = memmovedown(pb_bbas, pb_rptr, used);
	 * >>         pb_wptr -= reclaim;
	 * >>         goto again_locked;
	 * >>     }
	 * >> #endif
	 * >>     if (!HAS_NONBLOCK_REALLOC_NX)
	 * >>         goto allocate_buffer_extension_after_truncate;
	 * >>     {
	 * >>         byte_t *buf;
	 * >>         size_t minsize;
	 * >>         minsize = (pb_wptr - pb_bbas) + total_size + PB_PACKET_NEXTLINK_SIZE;
	 * >>         buf = NONBLOCK_REALLOC_NX(pb_bbas, minsize);
	 * >>         if (!buf) {
	 * >>             // Allocation failed, or would have had to block
	 * >> allocate_buffer_extension_after_truncate:
	 * >>             if (HAS_NONBLOCK_REALLOC_IN_PLACE_NX) {
	 * >>                 // Try to reclaim unused memory
	 * >>                 size_t final_size;
	 * >>                 final_size = (pb_wptr - pb_bbas) + PB_PACKET_NEXTLINK_SIZE;
	 * >>                 if (NONBLOCK_REALLOC_IN_PLACE_NX(pb_bbas, final_size)) {
	 * >> #ifdef PB_BUFFER_BLOB_FREE_NEEDS_SIZE
	 * >>                     pb_bend = pb_bbas + final_size;
	 * >> #endif
	 * >>                 }
	 * >>             }
	 * >>             goto allocate_buffer_extension;
	 * >>         }
	 * >>         // Reallocate read/write pointers for the new buffer
	 * >>         pb_rptr = buf + ((byte_t *)pb_rptr - (byte_t *)pb_bbas);
	 * >>         pb_wptr = buf + ((byte_t *)pb_wptr - (byte_t *)pb_bbas);
	 * >>         // Install the extended buffer
	 * >>         pb_bbas = buf;
	 * >>         pb_bend = buf + USABLE_SIZE_OR(buf, minsize);
	 * >>     }
	 * >>     goto again_locked;
	 * >> }
	 *
	 * >> NOBLOCK commit_write(struct pb_packet *packet) {
	 * >>     atomic_write(&packet->p_state, PB_PACKET_STATE_READABLE);
	 * >> }
	 *
	 * >> NOBLOCK abort_write(struct pb_packet *packet) {
	 * >>     atomic_write(&packet->p_state, PB_PACKET_STATE_DISCARD);
	 * >>     if (trylock()) {
	 * >>         // Optional: Try to reclaim unused packet memory, if the one
	 * >>         //           being discarded is still the most recent packet.
	 * >>         if (pb_wptr == (byte_t *)packet + packet->p_total) {
	 * >>             pb_used -= packet->p_total; // atomic!
	 * >>             pb_wptr = packet;
	 * >>         }
	 * >>         unlock();
	 * >>     }
	 * >> }
	 */
	struct atomic_rwlock pb_lock; /* Lock for this packet buffer. */
	__byte_t            *pb_bbas; /* [lock(pb_lock)][<= pb_bend][owned] Base address of the current buffer data blob. */
	__byte_t            *pb_bend; /* [lock(pb_lock)][>= pb_bbas] End address of the current buffer data blob. */
#ifdef PB_BUFFER_WANT_PB_RPTR_UINTPTR_ALIAS
	union {
		struct pb_packet*pb_rptr; /* [lock(pb_lock || PB_PACKET_STATE_READING)][1..1][valid_if(!= pb_wptr)]
		                           * Pointer  to the  next unread  packet/the packet  currently being read. */
		__uintptr_t      pb_rptr_uint;
	};
#else /* PB_BUFFER_WANT_PB_RPTR_UINTPTR_ALIAS */
	struct pb_packet    *pb_rptr; /* [lock(pb_lock || PB_PACKET_STATE_READING)][1..1][valid_if(!= pb_wptr)]
	                               * Pointer  to the  next unread  packet/the packet  currently being read. */
#endif /* !PB_BUFFER_WANT_PB_RPTR_UINTPTR_ALIAS */
	struct pb_packet    *pb_wptr; /* [lock(pb_lock)][1..1] Offset to the end of the last unread packet. */
	__WEAK __size_t      pb_used; /* Total amount of used buffer space. (checked against `pb_limt') */
	__WEAK __size_t      pb_limt; /* Max size of the packet buffer. (set to 0 when the buffer was closed) */
	sched_signal_t       pb_psta; /* Signal broadcast any packet changes state to one of:
	                               *   - PB_PACKET_STATE_READABLE
	                               *   - PB_PACKET_STATE_DISCARD
	                               * NOTE: Also broadcast when a packet was consumed!
	                               * NOTE: Also broadcast when `pb_limt' is increased or set to 0! */
};

/* Helper macros for `struct pb_buffer::pb_lock' */
#define pb_buffer_lock_mustreap(self)     0
#define pb_buffer_lock_reap(self)         (void)0
#define _pb_buffer_lock_reap(self)        (void)0
#define pb_buffer_lock_write(self)        atomic_rwlock_write(&(self)->pb_lock)
#define pb_buffer_lock_write_nx(self)     atomic_rwlock_write_nx(&(self)->pb_lock)
#define pb_buffer_lock_trywrite(self)     atomic_rwlock_trywrite(&(self)->pb_lock)
#define pb_buffer_lock_endwrite(self)     (atomic_rwlock_endwrite(&(self)->pb_lock), pb_buffer_lock_reap(self))
#define _pb_buffer_lock_endwrite(self)    atomic_rwlock_endwrite(&(self)->pb_lock)
#define pb_buffer_lock_read(self)         atomic_rwlock_read(&(self)->pb_lock)
#define pb_buffer_lock_read_nx(self)      atomic_rwlock_read_nx(&(self)->pb_lock)
#define pb_buffer_lock_tryread(self)      atomic_rwlock_tryread(&(self)->pb_lock)
#define _pb_buffer_lock_endread(self)     atomic_rwlock_endread(&(self)->pb_lock)
#define pb_buffer_lock_endread(self)      (void)(atomic_rwlock_endread(&(self)->pb_lock) && (pb_buffer_lock_reap(self), 0))
#define _pb_buffer_lock_end(self)         atomic_rwlock_end(&(self)->pb_lock)
#define pb_buffer_lock_end(self)          (void)(atomic_rwlock_end(&(self)->pb_lock) && (pb_buffer_lock_reap(self), 0))
#define pb_buffer_lock_upgrade(self)      atomic_rwlock_upgrade(&(self)->pb_lock)
#define pb_buffer_lock_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->pb_lock)
#define pb_buffer_lock_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->pb_lock)
#define pb_buffer_lock_downgrade(self)    atomic_rwlock_downgrade(&(self)->pb_lock)
#define pb_buffer_lock_reading(self)      atomic_rwlock_reading(&(self)->pb_lock)
#define pb_buffer_lock_writing(self)      atomic_rwlock_writing(&(self)->pb_lock)
#define pb_buffer_lock_canread(self)      atomic_rwlock_canread(&(self)->pb_lock)
#define pb_buffer_lock_canwrite(self)     atomic_rwlock_canwrite(&(self)->pb_lock)
#define pb_buffer_lock_waitread(self)     atomic_rwlock_waitread(&(self)->pb_lock)
#define pb_buffer_lock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->pb_lock)
#define pb_buffer_lock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->pb_lock)
#define pb_buffer_lock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->pb_lock)

/* Broadcast the `pb_psta' signal.
 * NOTE: In user-space,  we  increment  the signal  counter  before  broadcasting,
 *       since  other code uses  the value of the  signal itself for inter-locking
 *       with the monitoring of changes made to components affected by the signal. */
#ifdef __KERNEL__
#define pb_buffer_psta_broadcast(self)          sig_broadcast(&(self)->pb_psta)
#define pb_buffer_psta_broadcast_for_fini(self) sig_broadcast_for_fini(&(self)->pb_psta)
#define pb_buffer_psta_send(self)               sig_send(&(self)->pb_psta)
#else /* __KERNEL__ */
#define pb_buffer_psta_broadcast(self)                        \
	(__hybrid_atomic_inc(&(self)->pb_psta, __ATOMIC_SEQ_CST), \
	 sched_signal_broadcast(&(self)->pb_psta))
#define pb_buffer_psta_broadcast_for_fini(self) \
	sched_signal_broadcast_for_fini(&(self)->pb_psta)
#define pb_buffer_psta_send(self)                             \
	(__hybrid_atomic_inc(&(self)->pb_psta, __ATOMIC_SEQ_CST), \
	 sched_signal_send(&(self)->pb_psta))
#endif /* !__KERNEL__ */


/* The default buffer size limit for packet buffers. */
#define PB_BUFFER_DEFAULT_LIMIT 8192

/* Initialize a given packet-buffer. */
#define PB_BUFFER_INIT PB_BUFFER_INIT_EX(PB_BUFFER_DEFAULT_LIMIT)
#define PB_BUFFER_INIT_EX(limit)                \
	{ ATOMIC_RWLOCK_INIT, __NULLPTR, __NULLPTR, \
	  __NULLPTR, __NULLPTR, 0, limit, SCHED_SIGNAL_INIT }

/* Initialize a given packet-buffer. */
#ifdef __INTELLISENSE__
__NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(pb_buffer_init)(struct pb_buffer *__restrict self);
__NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(pb_buffer_cinit)(struct pb_buffer *__restrict self);
__NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(pb_buffer_init_ex)(struct pb_buffer *__restrict self, __size_t limit);
__NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(pb_buffer_cinit_ex)(struct pb_buffer *__restrict self, __size_t limit);
#else /* __INTELLISENSE__ */
#define pb_buffer_init(self)  pb_buffer_init_ex(self, PB_BUFFER_DEFAULT_LIMIT)
#define pb_buffer_cinit(self) pb_buffer_cinit_ex(self, PB_BUFFER_DEFAULT_LIMIT)
#define pb_buffer_init_ex(self, limit)     \
	(atomic_rwlock_init(&(self)->pb_lock), \
	 (self)->pb_bbas = __NULLPTR,          \
	 (self)->pb_bend = __NULLPTR,          \
	 (self)->pb_rptr = __NULLPTR,          \
	 (self)->pb_wptr = __NULLPTR,          \
	 (self)->pb_used = 0,                  \
	 (self)->pb_limt = (limit),            \
	 sched_signal_init(&(self)->pb_psta))
#define pb_buffer_cinit_ex(self, limit)             \
	(atomic_rwlock_cinit(&(self)->pb_lock),         \
	 __hybrid_assert((self)->pb_bbas == __NULLPTR), \
	 __hybrid_assert((self)->pb_bend == __NULLPTR), \
	 __hybrid_assert((self)->pb_rptr == __NULLPTR), \
	 __hybrid_assert((self)->pb_wptr == __NULLPTR), \
	 __hybrid_assert((self)->pb_used == 0),         \
	 (self)->pb_limt = (limit),                     \
	 sched_signal_cinit(&(self)->pb_psta))
#endif /* !__INTELLISENSE__ */

#if defined(NDEBUG) || defined(NDEBUG_FINI)
#define __pb_buffer_fini_debug(self) (void)0
#else /* NDEBUG || NDEBUG_FINI */
#define __pb_buffer_fini_debug(self) __libc_memset(self, 0xcc, sizeof(struct pb_buffer))
#endif /* !NDEBUG && !NDEBUG_FINI */
#define __pb_buffer_cb_fini_ancillary_noop(packet) (void)0


/* Finalize the given packet-buffer.
 * If given, `cb_fini_ancillary(struct pb_packet *packet)' is invoked
 * for  the ancillary  data blob of  any packet that  was never read. */
#define pb_buffer_fini(self) pb_buffer_fini_ex(self, __pb_buffer_cb_fini_ancillary_noop)
#define pb_buffer_fini_ex(self, cb_fini_ancillary)                     \
	do {                                                               \
		struct pb_packet *_rptr;                                       \
		struct pb_packet *_wptr;                                       \
		_rptr = (self)->pb_rptr;                                       \
		_wptr = (self)->pb_wptr;                                       \
		while (_rptr != _wptr) {                                       \
			if (!_rptr->p_total) {                                     \
				struct pb_packet *_cptr;                               \
				/* Buffer control packet */                            \
				_cptr = _rptr->p_cont;                                 \
				pb_buffer_blob_free(_pb_packet_bufctl_bufbase(_rptr),  \
				                    _pb_packet_bufctl_bufsize(_rptr)); \
				_rptr = _cptr;                                         \
				continue;                                              \
			}                                                          \
			cb_fini_ancillary(_rptr);                                  \
			_rptr = (struct pb_packet *)((__byte_t *)_rptr +           \
			                             _rptr->p_total);              \
		}                                                              \
		/* Free the current buffer */                                  \
		pb_buffer_blob_free_p((self)->pb_bbas,                         \
		                      (__size_t)((self)->pb_bend -             \
		                                 (self)->pb_bbas));            \
		pb_buffer_psta_broadcast_for_fini(self);                       \
		__pb_buffer_fini_debug(self);                                  \
	}	__WHILE0

/* Close the given packet buffer, making it impossible to enqueue as further packets.
 * Any  attempt at writing  more data will  result in `pb_buffer_startwrite()' simply
 * returning `NULL' */
#ifdef __INTELLISENSE__
__NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(pb_buffer_close)(struct pb_buffer *__restrict self);
#else /* __INTELLISENSE__ */
#define pb_buffer_close(self)                                      \
	(__hybrid_atomic_store(&(self)->pb_limt, 0, __ATOMIC_RELEASE), \
	 pb_buffer_psta_broadcast(self))
#endif /* !__INTELLISENSE__ */


/* Check if the given buffer was closed. */
#ifdef __INTELLISENSE__
__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(pb_buffer_closed)(struct pb_buffer const *__restrict self);
#else /* __INTELLISENSE__ */
#define pb_buffer_closed(self) \
	(__hybrid_atomic_load(&(self)->pb_limt, __ATOMIC_ACQUIRE) == 0)
#endif /* !__INTELLISENSE__ */



#define pb_packet_get_totalsize_s(payload_size, ancillary_size)                 \
	(__CEIL_ALIGN(__CCAST(__size_t)(payload_size), PACKET_BUFFER_ALIGNMENT) +   \
	 __CEIL_ALIGN(__CCAST(__size_t)(ancillary_size), PACKET_BUFFER_ALIGNMENT) + \
	 __CEIL_ALIGN(PB_PACKET_HEADER_SIZE, PACKET_BUFFER_ALIGNMENT))


/* Calculate the required total size of a packet, and check for overflow.
 * @return: true:  Success
 * @return: false: Overflow */
__LOCAL __NOBLOCK __ATTR_WUNUSED __BOOL
__NOTHROW(pb_packet_get_totalsize)(__size_t payload_size,
                                   __size_t ancillary_size,
                                   __uint16_t *__restrict ptotal_size) {
	__size_t total;
	total = pb_packet_get_totalsize_s(payload_size, ancillary_size);
	*ptotal_size = (__uint16_t)total;
	return total <= 0xffff;
}


#define PB_BUFFER_STARTWRITE_TOOLARGE ((struct pb_packet *)-1) /* Packet is _always_ too large */
#define PB_BUFFER_STARTWRITE_READSOME ((struct pb_packet *)-2) /* Must read some packets before this one can be written. */
#ifdef __KERNEL__
#define PB_BUFFER_STARTWRITE_ISOK(x) ((uintptr_t)(x) < (uintptr_t)-2)
#else /* __KERNEL__ */
#define PB_BUFFER_STARTWRITE_BADALLOC ((struct pb_packet *)-3) /* Failed to allocate more memory. */
#define PB_BUFFER_STARTWRITE_ISOK(x) ((uintptr_t)(x) < (uintptr_t)-3)
#endif /* !__KERNEL__ */


/* Begin construction of a new packet to-be appended to `self'
 * NOTES:
 *   - All of the packet's struct fields will have already been filled in by this function.
 *   - It is weakly undefined when a packet that was started before another was committed
 *     will  be  read.   It  may   happen  before,  but   it  may   also  happen   after.
 *   - The  only guaranty in concerns to packet read order is that packets that are
 *     generated linearly by the same thread will always be read in that same order
 *     in relation to each other.
 *   - Similarly, a packet that for which `pb_buffer_endwrite_commit()' was caled before
 *     the  call  to  `pb_buffer_startwrite()' of  another  packet will  always  be read
 *     before that other packet.
 * @return: * : Pointer to the packet's descriptor. Once the caller has finished filling
 *              in the packet's contents, they must use `pb_buffer_endwrite_commit()' in
 *              order to make the packet available for being read.
 *              In case that packet initialization should fail, `pb_buffer_endwrite_abort()'
 *              may  be  called  to  undo  what  was  previously  done  by  this   function.
 *              NOTE: The payload and ancillary data blobs of the packet should be accessed with:
 *                    >> void *pb_packet_payload(struct pb_packet *);
 *                    >> void *pb_packet_ancillary(struct pb_packet *);
 * @return: PB_BUFFER_STARTWRITE_TOOLARGE: [...]
 * @return: PB_BUFFER_STARTWRITE_READSOME: [...]
 * @return: PB_BUFFER_STARTWRITE_BADALLOC: [...] (user-space only)
 * @throw: E_BADALLOC: Failed to allocate more buffer memory (kernel only) */
#ifdef __KERNEL__
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct pb_packet *
(LIBBUFFER_CC *PPB_BUFFER_STARTWRITE)(struct pb_buffer *__restrict self,
                                      __size_t payload_size,
                                      __size_t ancillary_size)
		__THROWS(E_BADALLOC);
#else /* __KERNEL__ */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct pb_packet *
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_STARTWRITE)(struct pb_buffer *__restrict self,
                                                 __size_t payload_size,
                                                 __size_t ancillary_size);
#endif /* !__KERNEL__ */
#ifdef LIBBUFFER_WANT_PROTOTYPES
#ifdef __KERNEL__
LIBBUFFER_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pb_packet *LIBBUFFER_CC
pb_buffer_startwrite(struct pb_buffer *__restrict self,
                     __size_t payload_size,
                     __size_t ancillary_size)
		__THROWS(E_BADALLOC);
#else /* __KERNEL__ */
LIBBUFFER_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pb_packet *
__NOTHROW(LIBBUFFER_CC pb_buffer_startwrite)(struct pb_buffer *__restrict self,
                                             __size_t payload_size,
                                             __size_t ancillary_size);
#endif /* !__KERNEL__ */
#endif /* LIBBUFFER_WANT_PROTOTYPES */


/* Commit a given `packet' to the packet stream. */
#ifdef __INTELLISENSE__
__NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW(pb_buffer_endwrite_commit)(struct pb_buffer *__restrict self,
                                     struct pb_packet *__restrict packet);
#else /* __INTELLISENSE__ */
#define pb_buffer_endwrite_commit(self, packet)                                             \
	(__hybrid_atomic_store(&(packet)->p_state, PB_PACKET_STATE_READABLE, __ATOMIC_RELEASE), \
	 pb_buffer_psta_send(self))
#endif /* !__INTELLISENSE__ */

/* Abort writing/discard the given `packet' from the packet stream. */
typedef __NOBLOCK __ATTR_NONNULL_T((1, 2)) void
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_ENDWRITE_ABORT)(struct pb_buffer *__restrict self,
                                                     struct pb_packet *__restrict packet);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW(LIBBUFFER_CC pb_buffer_endwrite_abort)(struct pb_buffer *__restrict self,
                                                 struct pb_packet *__restrict packet);
#endif /* LIBBUFFER_WANT_PROTOTYPES */


/* Try to begin reading the next unread packet. If no unread packet exists,
 * or if the next unread packet is already being read at the moment, return
 * NULL without blocking.
 * In this case, the caller may wait for the next readable packet by doing
 * >> while ((packet = pb_buffer_startread(self)) == NULL) {
 * >> #ifdef __KERNEL__
 * >>     task_connect(&self->pb_psta);
 * >>     packet = pb_buffer_startread(self);
 * >>     if (packet) {
 * >>         task_disconnectall();
 * >>         break;
 * >>     }
 * >>     task_waitfor();
 * >> #else // __KERNEL__
 * >>     lfutex_t status;
 * >>     status = atomic_read(&self->pb_psta);
 * >>     packet = pb_buffer_startread(self);
 * >>     if (packet)
 * >>         break;
 * >>     futex_waitwhile(&self->pb_psta, status);
 * >> #endif // !__KERNEL__
 * >> }
 * Note that with this design, recursive- or parallel read operations
 * aren't allowed (which also wouldn't really make much sense,  since
 * packets are meant to be read in order, alongside the guaranty that
 * any packet will only ever be read once).
 * However, due to things such as VIO,  there is a good chance that  a
 * malicious program  might cause  a recursive  read operation  to  be
 * performed. (i.e. recv(2) is called  with a VIO-buffer, who's  write
 * callbacks  will invoke  recv(2) again).  If this  happens, then the
 * second call to recv(2) will  block indefinitely, and the  malicious
 * program will be soft-locked (but can still be CTRL+C'd, so it's ok)
 *
 * @return: * :   A pointer to a read-handle for the packet that is next-in-line to-be received.
 *                This handle must be released by a call to one of the  pb_buffer_read_[end/...]
 *                functions.
 * @return: NULL: No unread packet is available at the moment, or the most recent packet is
 *                currently being read. */
#ifdef __KERNEL__
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct pb_packet *
(LIBBUFFER_CC *PPB_BUFFER_STARTREAD)(struct pb_buffer *__restrict self)
		__THROWS(E_WOULDBLOCK);
#else /* __KERNEL__ */
typedef __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) struct pb_packet *
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_STARTREAD)(struct pb_buffer *__restrict self);
#endif /* !__KERNEL__ */
#ifdef LIBBUFFER_WANT_PROTOTYPES
#ifdef __KERNEL__
LIBBUFFER_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pb_packet *LIBBUFFER_CC
pb_buffer_startread(struct pb_buffer *__restrict self)
		__THROWS(E_WOULDBLOCK);
#else /* __KERNEL__ */
LIBBUFFER_DECL __ATTR_WUNUSED __ATTR_NONNULL((1)) struct pb_packet *
__NOTHROW_NCX(LIBBUFFER_CC pb_buffer_startread)(struct pb_buffer *__restrict self);
#endif /* !__KERNEL__ */
#endif /* LIBBUFFER_WANT_PROTOTYPES */


/* Truncate the packet from which the  caller is currently reading by  updating
 * its base-pointer, acting as though the first `bytes_to_consume' bytes of the
 * packet weren't actually apart of its payload.
 * This  can be called any number of times, though the caller must always ensure
 * that `bytes_to_consume <= packet->p_payload', and  that the returned  pointer
 * becomes the new handle that must be used for reading from the current packet:
 * >> struct pb_packet *packet;
 * >> packet = pb_buffer_startread(self);
 * >> if (packet) {
 * >>     size_t bytes_consumed;
 * >>     while ((bytes_consumed = PROCESS_PACKET(self)) != 0)
 * >>         packet = pb_buffer_truncate_packet(self, packet, bytes_consumed);
 * >>     if (SHOULD_CONSUME(packet)) {
 * >>         pb_buffer_endread_consume(self, packet);
 * >>     } else {
 * >>         pb_buffer_endread_restore(self, packet);
 * >>     }
 * >> }
 * @return: * : A new handle that should be used for reading packet data. */
typedef __NOBLOCK __ATTR_RETNONNULL_T __ATTR_WUNUSED_T __ATTR_NONNULL_T((1, 2)) struct pb_packet *
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_TRUNCATE_PACKET)(struct pb_buffer *__restrict self,
                                                      struct pb_packet *__restrict packet,
                                                      __uint16_t bytes_to_consume);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __NOBLOCK __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct pb_packet *
__NOTHROW(LIBBUFFER_CC pb_buffer_truncate_packet)(struct pb_buffer *__restrict self,
                                                  struct pb_packet *__restrict packet,
                                                  __uint16_t bytes_to_consume);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* End reading the  current packet, and  discard the packet  from the data  stream.
 * The next call to `pb_buffer_startread()' will return NULL or a different packet. */
typedef __NOBLOCK __ATTR_NONNULL_T((1, 2)) void
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_ENDREAD_CONSUME)(struct pb_buffer *__restrict self,
                                                         struct pb_packet *__restrict packet);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW(LIBBUFFER_CC pb_buffer_endread_consume)(struct pb_buffer *__restrict self,
                                                  struct pb_packet *__restrict packet);
#endif /* LIBBUFFER_WANT_PROTOTYPES */


/* End reading the current packet, and restore it to have it
 * be  returned by the  next call to `pb_buffer_startread()' */
#ifdef __INTELLISENSE__
__NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(pb_buffer_endread_restore)(struct pb_buffer *__restrict self,
                                         struct pb_packet *__restrict packet);
#else /* __INTELLISENSE__ */
#define pb_buffer_endread_restore(self, packet)                                                 \
	(__hybrid_assertf((packet) == (self)->pb_rptr, "%p != %p", (packet), (self)->pb_rptr),      \
	 __hybrid_assertf((packet)->p_state == PB_PACKET_STATE_READING, "%I8u", (packet)->p_state), \
	 __hybrid_atomic_store(&(packet)->p_state, PB_PACKET_STATE_READABLE, __ATOMIC_RELEASE),     \
	 pb_buffer_psta_broadcast(self))
#endif /* !__INTELLISENSE__ */



/* Snapshot-style checks if reading/writing packets is possible right now. */
#ifdef __KERNEL__
typedef __NOBLOCK __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
(LIBBUFFER_CC *PPB_BUFFER_CANREAD)(struct pb_buffer *__restrict self)
		__THROWS(E_WOULDBLOCK);
typedef __NOBLOCK __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
(LIBBUFFER_CC *PPB_BUFFER_CANWRITE)(struct pb_buffer *__restrict self,
                                    __size_t payload_size,
                                    __size_t ancillary_size)
		__THROWS(E_WOULDBLOCK);
#else /* __KERNEL__ */
typedef __NOBLOCK __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_CANREAD)(struct pb_buffer *__restrict self);
typedef __NOBLOCK __ATTR_WUNUSED_T __ATTR_NONNULL_T((1)) __BOOL
__NOTHROW_T(LIBBUFFER_CC *PPB_BUFFER_CANWRITE)(struct pb_buffer *__restrict self,
                                               __size_t payload_size,
                                               __size_t ancillary_size);
#endif /* !__KERNEL__ */
#ifdef LIBBUFFER_WANT_PROTOTYPES
#ifdef __KERNEL__
LIBBUFFER_DECL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(LIBBUFFER_CC pb_buffer_canread)(struct pb_buffer *__restrict self)
		__THROWS(E_WOULDBLOCK);
LIBBUFFER_DECL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
(LIBBUFFER_CC pb_buffer_canwrite)(struct pb_buffer *__restrict self,
                                  __size_t payload_size,
                                  __size_t ancillary_size)
		__THROWS(E_WOULDBLOCK);
#else /* __KERNEL__ */
LIBBUFFER_DECL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(LIBBUFFER_CC pb_buffer_canread)(struct pb_buffer *__restrict self);
LIBBUFFER_DECL __NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(LIBBUFFER_CC pb_buffer_canwrite)(struct pb_buffer *__restrict self,
                                           __size_t payload_size,
                                           __size_t ancillary_size);
#endif /* !__KERNEL__ */
#endif /* LIBBUFFER_WANT_PROTOTYPES */




/* Packet buffer polling API. */
#define pb_buffer_pollconnect_ex(self, cb)       cb(&(self)->pb_psta)
#define pb_buffer_pollconnect_read_ex(self, cb)  cb(&(self)->pb_psta)
#define pb_buffer_pollconnect_write_ex(self, cb) cb(&(self)->pb_psta)
#ifdef sched_signal_connect_for_poll
#define pb_buffer_pollconnect(self)       pb_buffer_pollconnect_ex(self, sched_signal_connect_for_poll)
#define pb_buffer_pollconnect_read(self)  pb_buffer_pollconnect_read_ex(self, sched_signal_connect_for_poll)
#define pb_buffer_pollconnect_write(self) pb_buffer_pollconnect_write_ex(self, sched_signal_connect_for_poll)
#endif /* sched_signal_connect_for_poll */

#ifdef LIBBUFFER_WANT_PROTOTYPES
#ifdef __OPTIMIZE_SIZE__
#define pb_buffer_pollread_ex(self, cb)       \
	(pb_buffer_pollconnect_read_ex(self, cb), \
	 pb_buffer_canread(self))
#define pb_buffer_pollwrite_ex(self, payload_size, ancillary_size, cb) \
	(pb_buffer_pollconnect_write_ex(self, cb),                         \
	 pb_buffer_canwrite(self, payload_size, ancillary_size))
#else /* __OPTIMIZE_SIZE__ */
#define pb_buffer_pollread_ex(self, cb)        \
	(pb_buffer_canread(self) ||                \
	 (pb_buffer_pollconnect_read_ex(self, cb), \
	  pb_buffer_canread(self)))
#define pb_buffer_pollwrite_ex(self, payload_size, ancillary_size, cb) \
	(pb_buffer_canwrite(self, payload_size, ancillary_size) ||         \
	 (pb_buffer_pollconnect_write_ex(self, cb),                        \
	  pb_buffer_canwrite(self, payload_size, ancillary_size)))
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef sched_signal_connect_for_poll
#define pb_buffer_pollread(self) \
	pb_buffer_pollread_ex(self, sched_signal_connect_for_poll)
#define pb_buffer_pollwrite(self, payload_size, ancillary_size) \
	pb_buffer_pollwrite_ex(self, payload_size, ancillary_size, sched_signal_connect_for_poll)
#endif /* sched_signal_connect_for_poll */
#endif /* LIBBUFFER_WANT_PROTOTYPES */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBBUFFER_PACKETBUFFER_H */
