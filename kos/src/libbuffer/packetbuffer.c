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
#ifndef GUARD_LIBBUFFER_PACKETBUFFER_C
#define GUARD_LIBBUFFER_PACKETBUFFER_C 1
#define PB_BUFFER_WANT_PB_RPTR_UINTPTR_ALIAS 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/align.h>

#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include <libbuffer/packetbuffer.h>

#include "packetbuffer.h"

#ifdef __KERNEL__
#include <kernel/except.h>
#endif /* __KERNEL__ */

DECL_BEGIN

#define lock()    pb_buffer_lock_write(self)
#define trylock() pb_buffer_lock_trywrite(self)
#define unlock()  pb_buffer_lock_endwrite(self)

#define rlock()    pb_buffer_lock_read(self)
#define tryrlock() pb_buffer_lock_tryread(self)
#define runlock()  pb_buffer_lock_endread(self)


#ifdef __KERNEL__
typedef heapptr_t heapptr_t;
#define HEAPPTR_ISOK(self) (heapptr_getsiz(self) != 0)
#define HEAPPTR_BASE       heapptr_getptr
#define HEAPPTR_SIZE       heapptr_getsiz
#define HEAP_MALLOC_UNX(num_bytes) \
	heap_alloc(&kernel_default_heap, num_bytes, GFP_NORMAL)
#define HEAP_REALLOC_UNX(oldptr, oldsiz, newsiz) \
	heap_realloc(&kernel_default_heap, oldptr, oldsiz, newsiz, GFP_NORMAL, GFP_NORMAL)
#define HEAP_NONBLOCK_MALLOC_NX(num_bytes) \
	heap_alloc_nx(&kernel_default_heap, num_bytes, GFP_ATOMIC)
#define HEAP_NONBLOCK_REALLOC_NX(oldptr, oldsiz, newsiz) \
	heap_realloc_nx(&kernel_default_heap, oldptr, oldsiz, newsiz, GFP_ATOMIC, GFP_ATOMIC)
#define HEAP_NONBLOCK_REALLOC_IN_PLACE_NX(oldptr, oldsiz, newsiz)                \
	heapptr_getsiz(heap_realloc_nx(&kernel_default_heap, oldptr, oldsiz, newsiz, \
	                               GFP_ATOMIC | GFP_NOMOVE, GFP_ATOMIC | GFP_NOMOVE))
#define HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX HEAP_NONBLOCK_REALLOC_IN_PLACE_NX
#else /* __KERNEL__ */
typedef void *heapptr_t;
#define HEAPPTR_ISOK(self)                       ((self) != NULL)
#define HEAPPTR_BASE(self)                       (self)
#define HEAPPTR_SIZE(self)                       malloc_usable_size(self)
#define HEAP_MALLOC_UNX(num_bytes)               malloc(num_bytes)
#define HEAP_REALLOC_UNX(oldptr, oldsiz, newsiz) realloc(oldptr, newsiz)
#if 0 /* None of these would actually be non-blocking... \
       * XXX: Should user-space ever get non-blocking variants of these, link them here! */
#define HEAP_NONBLOCK_MALLOC_NX(num_bytes)                           malloc(num_bytes)
#define HEAP_NONBLOCK_REALLOC_NX(oldptr, oldsiz, newsiz)             realloc(oldptr, newsiz)
#define HEAP_NONBLOCK_REALLOC_IN_PLACE_NX(oldptr, oldsiz, newsiz)    (realloc_in_place(oldptr, newsiz) ? malloc_usable_size(oldptr) : 0)
#define HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX(oldptr, oldsiz, newsiz)   (realloc_in_place(oldptr, newsiz), malloc_usable_size(oldptr))
#define HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX_V(oldptr, oldsiz, newsiz) (realloc_in_place(oldptr, newsiz))
#endif
#endif /* !__KERNEL__ */



/* Return a pointer to the packet that follows after `self' */
PRIVATE NOBLOCK ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) struct pb_packet *
NOTHROW(CC next_packet)(struct pb_packet *__restrict self) {
	struct pb_packet *result;
	result = (struct pb_packet *)((byte_t *)self + self->p_total);
	while (result->p_total == 0) {
		/* Buffer control packet: The next packet is apart of the linked buffer! */
		result = result->p_cont;
	}
	return result;
}

/* Iterate over all unread packets. */
#define FOREACH_UNREAD_PACKET(p) \
	for (p = self->pb_rptr; p != self->pb_wptr; p = next_packet(p))

/* Check if there are packets from the current buffer that
 * are  used  externally  any  may  not  be  realloc()'ed. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(CC are_packets_from_the_current_buffer_in_use)(struct pb_buffer const *__restrict self) {
	struct pb_packet *p;
	/* Iterate all unread packets. */
	FOREACH_UNREAD_PACKET(p) {
		/* Check if the packet is even apart of our current buffer. */
		if (!((byte_t *)p >= self->pb_bbas && (byte_t *)p < self->pb_bend))
			continue;
		/* Check if the packet is currently in use. */
		if (!PB_PACKET_STATE_INUSE(p->p_state))
			continue;
		/* Found a packet */
		return true;
	}
	return false;
}



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
INTERN WUNUSED NONNULL((1)) struct pb_packet *CC
lib_pb_buffer_startwrite(struct pb_buffer *__restrict self,
                         size_t payload_size,
                         size_t ancillary_size)
		THROWS(E_BADALLOC)
#else /* __KERNEL__ */
INTERN WUNUSED NONNULL((1)) struct pb_packet *
NOTHROW(CC lib_pb_buffer_startwrite)(struct pb_buffer *__restrict self,
                                     size_t payload_size,
                                     size_t ancillary_size)
#endif /* !__KERNEL__ */
{
	size_t avail;
	uint16_t total_size;
	/* Calculate the total required size for the packet. */
	if (!pb_packet_get_totalsize(payload_size,
	                             ancillary_size,
	                             &total_size))
		return PB_BUFFER_STARTWRITE_TOOLARGE; /* Packet is _always_ too large! */
again:
	lock();
again_locked:
	/* try to rewind the packet buffer */
	if (atomic_cmpxch(&self->pb_rptr,
	                  self->pb_wptr,
	                  (struct pb_packet *)self->pb_bbas))
		self->pb_wptr = (struct pb_packet *)self->pb_bbas;
	avail = (size_t)(self->pb_bend - (byte_t *)self->pb_wptr);
	if (avail >= (size_t)total_size + PB_PACKET_NEXTLINK_SIZE) {
		struct pb_packet *packet;
		if unlikely(!self->pb_limt) {
			/* Special case: The buffer was closed */
unlock_and_return_too_large:
			unlock();
			return PB_BUFFER_STARTWRITE_TOOLARGE;
		}
		packet              = self->pb_wptr;
		packet->p_total     = total_size;
		packet->p_payoff    = PB_PACKET_HEADER_SIZE;
		packet->p_payload   = (uint16_t)payload_size;
		packet->p_ancillary = (uint16_t)ancillary_size;
		packet->p_state     = PB_PACKET_STATE_INIT;
		self->pb_wptr = (struct pb_packet *)((byte_t *)self->pb_wptr + total_size);
		atomic_fetchadd(&self->pb_used, total_size);
		unlock();
		return packet;
	}
	/* Check if the buffer size limit allows for a packet of this size to be added. */
	if unlikely(self->pb_used + total_size > self->pb_limt) {
		/* Check if the packet would _always_ be too large. */
		if (total_size > self->pb_limt)
			goto unlock_and_return_too_large;
		unlock();
		return PB_BUFFER_STARTWRITE_READSOME;
	}
	if (are_packets_from_the_current_buffer_in_use(self)) {
		/* We can't realloc() the current buffer!
		 * -> Try to realloc_in_place() to get more memory */
		heapptr_t buf;
#ifdef HEAP_NONBLOCK_REALLOC_IN_PLACE_NX
		{
			size_t minsize, newsize;
			minsize = (size_t)((byte_t *)self->pb_wptr - (byte_t *)self->pb_bbas) +
			          total_size + PB_PACKET_NEXTLINK_SIZE;
			newsize = HEAP_NONBLOCK_REALLOC_IN_PLACE_NX(self->pb_bbas,
			                                            (size_t)(self->pb_bend -
			                                                     self->pb_bbas),
			                                            minsize);
			if (newsize) {
				self->pb_bend = self->pb_bbas + newsize;
				goto again_locked;
			}
		}
#endif /* HEAP_NONBLOCK_REALLOC_IN_PLACE_NX */
allocate_buffer_extension:
		/* Cannot realloc the current buffer, so must alloc a new one */
#if !defined(__OPTIMIZE_SIZE__) && defined(HEAP_NONBLOCK_MALLOC_NX)
		buf = HEAP_NONBLOCK_MALLOC_NX(total_size + PB_PACKET_NEXTLINK_SIZE);
		if (!HEAPPTR_ISOK(buf))
#endif /* !__OPTIMIZE_SIZE__ && HEAP_NONBLOCK_MALLOC_NX */
		{
			unlock();
			buf = HEAP_MALLOC_UNX(total_size + PB_PACKET_NEXTLINK_SIZE);
#ifndef __KERNEL__
			if (!HEAPPTR_ISOK(buf))
				return PB_BUFFER_STARTWRITE_BADALLOC;
#endif /* !__KERNEL__ */
			lock();
			/* Check if something changed while we weren't holding the lock. */
			avail = (size_t)(self->pb_bend - (byte_t *)self->pb_wptr);
			if ((avail <= (size_t)total_size + PB_PACKET_NEXTLINK_SIZE) ||
			    (self->pb_used + total_size >= self->pb_limt) ||
			    (!are_packets_from_the_current_buffer_in_use(self))) {
				pb_buffer_blob_free(HEAPPTR_BASE(buf),
				                    HEAPPTR_SIZE(buf));
				goto again_locked;
			}
		}
		/* NOTE: The  following  can  happen  even  when  `HEAP_REALLOC_UNX'  is  defined,
		 *       since  another  thread may  have previously  been  reading from  a packet
		 *       of the current buffer (s.a.  `are_packets_from_the_current_buffer_in_use'
		 *       above), but has since finished reading by calling `lib_pb_buffer_canread'
		 *       That last call doesn't acquire any locks, so we must deal with the chance
		 *       that the read-pointer has changed in the mean time! */
		if (atomic_read(&self->pb_rptr) == self->pb_wptr) {
			/* Special case: old buffer was empty. */
			self->pb_rptr = (struct pb_packet *)HEAPPTR_BASE(buf);
			if (self->pb_bend != self->pb_bbas) {
				/* free() the previous buffer now, since it wouldn't make sense
				 * to have the unread packet chain start out with a bufctl link
				 * packet. */
				byte_t *oldbuf;
#ifdef PB_BUFFER_BLOB_FREE_NEEDS_SIZE
				size_t oldsiz;
#endif /* PB_BUFFER_BLOB_FREE_NEEDS_SIZE */
				oldbuf = self->pb_bbas;
#ifdef PB_BUFFER_BLOB_FREE_NEEDS_SIZE
				oldsiz = (size_t)(self->pb_bend - self->pb_bbas);
#endif /* PB_BUFFER_BLOB_FREE_NEEDS_SIZE */
				self->pb_wptr = (struct pb_packet *)HEAPPTR_BASE(buf);
				self->pb_bbas = (byte_t *)HEAPPTR_BASE(buf);
				self->pb_bend = (byte_t *)HEAPPTR_BASE(buf) + HEAPPTR_SIZE(buf);
				unlock();
				pb_buffer_blob_free(oldbuf, oldsiz);
				goto again;
			}
		} else {
			struct pb_packet *link_packet;
			link_packet          = self->pb_wptr;
			link_packet->p_total = 0;
#ifdef PB_BUFFER_BLOB_FREE_NEEDS_SIZE
			/* NOTE: avail == self->pb_bend - link_packet */
			link_packet->p_ancillary = avail;
#endif /* PB_BUFFER_BLOB_FREE_NEEDS_SIZE */
			link_packet->p_cont = (struct pb_packet *)HEAPPTR_BASE(buf);
			link_packet->p_base = self->pb_bbas;
		}
		self->pb_wptr = (struct pb_packet *)HEAPPTR_BASE(buf);
		self->pb_bbas = (byte_t *)HEAPPTR_BASE(buf);
		self->pb_bend = (byte_t *)HEAPPTR_BASE(buf) + HEAPPTR_SIZE(buf);
		goto again_locked;
	}
	/* NOTE: We're allowed to modify the pointer  to the next packet to-be  read,
	 *       since  we've already  checked if anyone  is using one  of the unread
	 *       packets from our current buffer (and noone is, and if someone wanted
	 *       to do so, they'd first have to acquire `lock()', which we're already
	 *       holding!) */
#ifndef __OPTIMIZE_SIZE__
	if ((byte_t *)self->pb_rptr > self->pb_bbas &&
	    (byte_t *)self->pb_rptr <= self->pb_bend) {
		/* Try  to  shift  unread  packets  downwards,
		 * so-as to reclaim buffer space near the top. */
		size_t reclaim, used;
		reclaim       = (size_t)((byte_t *)self->pb_rptr - (byte_t *)self->pb_bbas);
		used          = (size_t)((byte_t *)self->pb_wptr - (byte_t *)self->pb_rptr);
		self->pb_rptr = (struct pb_packet *)memmovedown(self->pb_bbas, self->pb_rptr, used);
		self->pb_wptr = (struct pb_packet *)((byte_t *)self->pb_wptr - reclaim);
		goto again_locked;
	}
#endif /* !__OPTIMIZE_SIZE__ */
	{
		/* Try to allocate more buffer memory without blocking. */
#ifdef HEAP_NONBLOCK_REALLOC_NX
		heapptr_t buf;
		size_t minsize;
		minsize = ((byte_t *)self->pb_wptr - self->pb_bbas) +
		          total_size + PB_PACKET_NEXTLINK_SIZE;
		buf = HEAP_NONBLOCK_REALLOC_NX(self->pb_bbas,
		                               (size_t)(self->pb_bend - self->pb_bbas),
		                               minsize);
		if (HEAPPTR_ISOK(buf)) {
			/* Reallocate read/write pointers for the new buffer */
#define RELOC(p) ((byte_t *)HEAPPTR_BASE(buf) + ((byte_t *)(p) - (byte_t *)self->pb_bbas))
			self->pb_rptr = (struct pb_packet *)RELOC(self->pb_rptr);
			self->pb_wptr = (struct pb_packet *)RELOC(self->pb_wptr);
#undef RELOC
			/* Install the extended buffer */
			self->pb_bbas = (byte_t *)HEAPPTR_BASE(buf);
			self->pb_bend = (byte_t *)HEAPPTR_BASE(buf) + HEAPPTR_SIZE(buf);
			goto again_locked;
		}
#endif  /* HEAP_NONBLOCK_REALLOC_NX */

		/* If the buffer is empty (self->pb_rptr == self->pb_wptr), then we
		 * can steal the old buffer and try to realloc() it without holding
		 * the lock! */
#ifdef HEAP_REALLOC_UNX
		if ((byte_t *)self->pb_wptr == (byte_t *)self->pb_rptr &&
		    (byte_t *)self->pb_wptr == (byte_t *)self->pb_bbas &&
		    (byte_t *)self->pb_bend != (byte_t *)self->pb_bbas) {
			heapptr_t newbuf;
			byte_t *oldbuf;
			size_t oldsiz;
			oldbuf = self->pb_bbas;
			oldsiz = (size_t)(self->pb_bend - oldbuf);
			self->pb_bbas = NULL;
			self->pb_bend = NULL;
			self->pb_rptr = NULL;
			self->pb_wptr = NULL;
			unlock();
#ifdef __KERNEL__
			TRY {
				newbuf = HEAP_REALLOC_UNX(oldbuf, oldsiz, total_size + PB_PACKET_NEXTLINK_SIZE);
			} EXCEPT
#define PROPAGATE_BADALLOC RETHROW()
#else /* __KERNEL__ */
			newbuf = HEAP_REALLOC_UNX(oldbuf, oldsiz, total_size + PB_PACKET_NEXTLINK_SIZE);
			if unlikely(!HEAPPTR_ISOK(newbuf))
#define PROPAGATE_BADALLOC return PB_BUFFER_STARTWRITE_BADALLOC
#endif /* !__KERNEL__ */
			{
				if (trylock()) {
					if (!self->pb_bbas) {
						self->pb_bbas = (byte_t *)oldbuf;
						self->pb_bend = (byte_t *)oldbuf + oldsiz;
						self->pb_rptr = (struct pb_packet *)oldbuf;
						self->pb_wptr = (struct pb_packet *)oldbuf;
						unlock();
						PROPAGATE_BADALLOC;
					}
					unlock();
				}
				pb_buffer_blob_free(oldbuf, oldsiz);
				PROPAGATE_BADALLOC;
			}
#undef PROPAGATE_BADALLOC
			lock();
			if unlikely(self->pb_bbas) {
				unlock();
				pb_buffer_blob_free(HEAPPTR_BASE(newbuf),
				                    HEAPPTR_SIZE(newbuf));
				goto again;
			}
			/* Install the new buffer. */
			self->pb_bbas = (byte_t *)HEAPPTR_BASE(newbuf);
			self->pb_bend = (byte_t *)HEAPPTR_BASE(newbuf) + HEAPPTR_SIZE(newbuf);
			self->pb_rptr = (struct pb_packet *)HEAPPTR_BASE(newbuf);
			self->pb_wptr = (struct pb_packet *)HEAPPTR_BASE(newbuf);
			goto again_locked;
		}
#endif /* HEAP_REALLOC_UNX */

		/* Allocation failed, or would have had to block
		 * -> At least try to reclaim unused buffer memory */
#if (defined(HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX) || \
     (!defined(PB_BUFFER_BLOB_FREE_NEEDS_SIZE) &&   \
      defined(HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX_V)))
		if (self->pb_bbas < self->pb_bend) {
			size_t final_size;
			final_size = ((byte_t *)self->pb_wptr -
			              self->pb_bbas) +
			             PB_PACKET_NEXTLINK_SIZE;
			assert(final_size <= (size_t)(self->pb_bend - self->pb_bbas));
#if !defined(PB_BUFFER_BLOB_FREE_NEEDS_SIZE) && defined(HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX_V)
			HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX_V(self->pb_bbas,
			                                     (size_t)(self->pb_bend - self->pb_bbas),
			                                     final_size);
#elif defined(PB_BUFFER_BLOB_FREE_NEEDS_SIZE)
			final_size = HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX(self->pb_bbas,
			                                                (size_t)(self->pb_bend - self->pb_bbas),
			                                                final_size);
			self->pb_bend = self->pb_bbas + final_size;
#else /* ... */
			HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX(self->pb_bbas,
			                                   (size_t)(self->pb_bend - self->pb_bbas),
			                                   final_size);
#endif /* !... */
		}
#endif /* HEAP_NONBLOCK_TRUNCATE_IN_PLACE_NX || ... */
		goto allocate_buffer_extension;
	}
}


/* Abort writing/discard the given `packet' from the packet stream. */
INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(CC lib_pb_buffer_endwrite_abort)(struct pb_buffer *__restrict self,
                                         struct pb_packet *__restrict packet) {
	atomic_write(&packet->p_state, PB_PACKET_STATE_DISCARD);
	if (trylock()) {
		/* Optional: Try to reclaim unused packet memory, if the  one
		 *           being discarded is still the most recent packet. */
		if (self->pb_wptr == (struct pb_packet *)((byte_t *)packet + packet->p_total)) {
			atomic_fetchsub(&self->pb_used, packet->p_total);
			self->pb_wptr = packet;
		}
		unlock();
	}
}



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
 * >> #else
 * >>     lfutex_t status;
 * >>     status = atomic_read(&self->pb_psta);
 * >>     packet = pb_buffer_startread(self);
 * >>     if (packet)
 * >>         break;
 * >>     futex_waitwhile(&self->pb_psta, status);
 * >> #endif
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
INTERN WUNUSED NONNULL((1)) struct pb_packet *CC
lib_pb_buffer_startread(struct pb_buffer *__restrict self)
		THROWS(E_WOULDBLOCK)
#else /* __KERNEL__ */
INTERN WUNUSED NONNULL((1)) struct pb_packet *
NOTHROW(CC lib_pb_buffer_startread)(struct pb_buffer *__restrict self)
#endif /* !__KERNEL__ */
{
	struct pb_packet *packet;
again:
	lock();
again_locked:
	packet = self->pb_rptr;
	if (packet == self->pb_wptr) {
		/* Nothing to read. */
		goto unlock_and_return_NULL;
	}
	if (packet->p_total == 0) {
		/* Packet exists the next buffer over! */
		self->pb_rptr = packet->p_cont;
		unlock();
		pb_buffer_blob_free(_pb_packet_bufctl_bufbase(packet),
		                    _pb_packet_bufctl_bufsize(packet));
		goto again;
	}
	if (packet->p_state != PB_PACKET_STATE_READABLE) {
		if (packet->p_state == PB_PACKET_STATE_DISCARD) {
			/* Skip packets that were discarded */
			atomic_fetchsub(&self->pb_used, packet->p_total);
			self->pb_rptr = (struct pb_packet *)((byte_t *)self->pb_rptr +
			                                     packet->p_total);
			goto again_locked;
		}
unlock_and_return_NULL:
		unlock();
		/* Let the caller handle all of the blocking. */
		return NULL;
	}
	atomic_write(&packet->p_state, PB_PACKET_STATE_READING);
	unlock();
	return packet;
}






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
 * >>         packet = pb_buffer_truncate(self, packet, bytes_consumed);
 * >>     if (SHOULD_CONSUME(packet)) {
 * >>         pb_buffer_endread_consume(self, packet);
 * >>     } else {
 * >>         pb_buffer_endread_restore(self, packet);
 * >>     }
 * >> }
 * @return: * : A new handle that should be used for reading packet data. */
INTERN NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct pb_packet *
NOTHROW(CC lib_pb_buffer_truncate_packet)(struct pb_buffer *__restrict self,
                                          struct pb_packet *__restrict packet,
                                          uint16_t bytes_to_consume) {
	struct pb_packet *result;
	uint16_t new_payload_start;
	uint16_t new_packet_offset;
	/* NOTE: This function has to be careful to maintain a valid packet header
	 *       at the original location of the packet (that is: `self->pb_rptr')
	 *       at all times. Otherwise, some  other thread may think that  we're
	 *       not actually still reading from a packet!
	 * For this purpose, we must ensure the following invariants:
	 *    - self->pb_rptr->p_total != 0;
	 *    - self->pb_rptr->p_state == PB_PACKET_STATE_READING;
	 *    - self->pb_rptr + self->pb_rptr->p_total == <next_unread_packet or
	 *                                                 buffer_control_packet or
	 *                                                 equal_to(self->pb_wptr)>
	 *
	 * Because  of these invariants,  there needs to be  a `p_payoff' pointer, since
	 * otherwise  we'd have  no way  of consuming  less than `PB_PACKET_HEADER_SIZE'
	 * bytes of payload data from  any packet, since trying  to create a new  packet
	 * header that overlaps with the old header would mean that we'd be  overwriting
	 * parts of the old header, potentially corruption the requirements of the above
	 * invariant.
	 * Without the  last  invariant,  we  could have  used  a  static  fake-packet  that
	 * just  contained  the p_total  and  p_state fields,  but  we must  actually ensure
	 * that  the chain of packets pointed-to by `pb_rptr'  can be read by anyone that is
	 * holding a lock to `self->pb_lock' (which is made use of in pb_buffer_startwrite).
	 */
	assert(packet == self->pb_rptr);
	assert(bytes_to_consume < packet->p_payload);
	/* Truncate the packet's payload size. */
	packet->p_payload -= bytes_to_consume;
	/* Figure out the packet's new payload offset. */
	new_payload_start = packet->p_payoff + bytes_to_consume;
	if (new_payload_start <= 0xff) {
		/* Simple case: Can just edit `packet->p_payoff' */
		packet->p_payoff = new_payload_start;
		return packet;
	}

	/* Difficult case: Must actually move the packet's header. */
	new_packet_offset = new_payload_start & ~(PACKET_BUFFER_ALIGNMENT - 1);
	result = (struct pb_packet *)((byte_t *)packet + new_packet_offset);

	/* Fill in the new packet header. */
	result->p_total     = packet->p_total - new_packet_offset;
	result->p_state     = PB_PACKET_STATE_READING;
	result->p_payoff    = new_payload_start & (PACKET_BUFFER_ALIGNMENT - 1);
	result->p_payload   = packet->p_payload;
	result->p_ancillary = packet->p_ancillary;

	/* Account for all of the memory that just became unused. */
	atomic_fetchsub(&self->pb_used, new_packet_offset);

	/* Update the  current read-pointer  to keep  on
	 * pointing at the header of the current packet. */
#ifdef NDEBUG
	atomic_write(&self->pb_rptr, result);
#else /* NDEBUG */
	{
		struct pb_packet *old_rptr;
		old_rptr = atomic_xch(&self->pb_rptr, result);
		assertf(old_rptr == packet,
		        "old_rptr = %p\n"
		        "packet   = %p\n",
		        old_rptr, packet);
	}
#endif /* !NDEBUG */

	/* Given the caller the new packet base pointer. */
	return result;
}






/* End reading the  current packet, and  discard the packet  from the data  stream.
 * The next call to `pb_buffer_startread()' will return NULL or a different packet. */
INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(CC lib_pb_buffer_endread_consume)(struct pb_buffer *__restrict self,
                                          struct pb_packet *__restrict packet) {
	uint16_t total;
	assert(packet == self->pb_rptr);
	assert(packet->p_state == PB_PACKET_STATE_READING);

	/* Note the order of read/writes here! */
	total = atomic_read(&packet->p_total);
	assert(total != 0);

	/* Update the used-counter to reflect the amount of bytes that went away. */
	atomic_fetchsub(&self->pb_used, total);

	/* At this point, the buffer's `pb_rptr' still points to our packet, meaning that
	 * we  still have an  effective lock on  `pb_buffer_startread()'. We release that
	 * locked by atomically moving the read-header  forward to the next packet  to-be
	 * read, which will simultaneously bring the buffer as a whole into a  consistent
	 * state. */
	atomic_fetchadd(&self->pb_rptr_uint, total);

	/* Because we've moved the read-pointer ahead, `self->pb_rptr->p_state' should now
	 * have changed away from `PB_PACKET_STATE_READING'.  In the event that there  are
	 * more packets to-be read, it  will be `PB_PACKET_STATE_READABLE', in which  case
	 * we have to broadcast the packet-state-changed-signal. In case there are no more
	 * packets,  `self->pb_rptr == self->pb_wptr', in which  case we wouldn't actually
	 * have to broadcast the state-changed signal. However, we do so anyways since  we
	 * have no way of reading from `pb_wptr' without introducing a race condition, and
	 * as with all signals, no harm is done by sending spurious signals. */
	pb_buffer_psta_broadcast(self);
}



/* Snapshot-style checks if reading/writing packets is possible right now. */
#ifdef __KERNEL__
INTERN NOBLOCK WUNUSED NONNULL((1)) bool
(CC lib_pb_buffer_canread)(struct pb_buffer *__restrict self)
		THROWS(E_WOULDBLOCK)
#else /* __KERNEL__ */
INTERN NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(CC lib_pb_buffer_canread)(struct pb_buffer *__restrict self)
#endif /* !__KERNEL__ */
{
	struct pb_packet *packet;
again:
	rlock();
again_locked:
	packet = self->pb_rptr;
	if (packet == self->pb_wptr) {
		/* Nothing to read. */
		goto unlock_and_return_false;
	}
	if (packet->p_total == 0) {
		/* Packet exists the next buffer over! */
		self->pb_rptr = packet->p_cont;
		runlock();
		pb_buffer_blob_free(_pb_packet_bufctl_bufbase(packet),
		                    _pb_packet_bufctl_bufsize(packet));
		goto again;
	}
	if (packet->p_state != PB_PACKET_STATE_READABLE) {
		if (packet->p_state == PB_PACKET_STATE_DISCARD) {
			/* Skip packets that were discarded */
			atomic_fetchsub(&self->pb_used, packet->p_total);
			self->pb_rptr = (struct pb_packet *)((byte_t *)self->pb_rptr +
			                                     packet->p_total);
			goto again_locked;
		}
unlock_and_return_false:
		runlock();
		/* Let the caller handle all of the blocking. */
		return false;
	}
	runlock();
	return true;
}


/* Snapshot-style checks if reading/writing packets is possible right now. */
#ifdef __KERNEL__
INTERN NOBLOCK WUNUSED NONNULL((1)) bool
(CC lib_pb_buffer_canwrite)(struct pb_buffer *__restrict self,
                            size_t payload_size,
                            size_t ancillary_size)
		THROWS(E_WOULDBLOCK)
#else /* __KERNEL__ */
INTERN NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(CC lib_pb_buffer_canwrite)(struct pb_buffer *__restrict self,
                                   size_t payload_size,
                                   size_t ancillary_size)
#endif /* !__KERNEL__ */
{
	bool result;
	uint16_t total_size;
	/* Calculate the total required size for the packet. */
	if (!pb_packet_get_totalsize(payload_size,
	                             ancillary_size,
	                             &total_size))
		return false; /* Packet is _always_ too large! */
	rlock();
	/* Check if the buffer size limit allows for a packet of this size to be added. */
	if unlikely(self->pb_used + total_size >= self->pb_limt) {
		/* Packet would be too large.
		 *
		 * However,  if it's only  too large because  the buffer was closed,
		 * we must still indicate that  writing is possible (and the  caller
		 * must deal with the case of an attempted write after having closed
		 * the buffer) */
		result = self->pb_limt == 0;
	} else {
		/* Sufficient space is available. */
		result = true;
	}
	runlock();
	return result;
}




DEFINE_PUBLIC_ALIAS(pb_buffer_startwrite, lib_pb_buffer_startwrite);
DEFINE_PUBLIC_ALIAS(pb_buffer_endwrite_abort, lib_pb_buffer_endwrite_abort);
DEFINE_PUBLIC_ALIAS(pb_buffer_startread, lib_pb_buffer_startread);
DEFINE_PUBLIC_ALIAS(pb_buffer_truncate_packet, lib_pb_buffer_truncate_packet);
DEFINE_PUBLIC_ALIAS(pb_buffer_endread_consume, lib_pb_buffer_endread_consume);
DEFINE_PUBLIC_ALIAS(pb_buffer_canread, lib_pb_buffer_canread);
DEFINE_PUBLIC_ALIAS(pb_buffer_canwrite, lib_pb_buffer_canwrite);

DECL_END

#endif /* !GUARD_LIBBUFFER_PACKETBUFFER_C */
