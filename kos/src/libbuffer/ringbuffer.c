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
#ifndef GUARD_LIBBUFFER_RINGBUFFER_C
#define GUARD_LIBBUFFER_RINGBUFFER_C 1

#define _USE_64BIT_TIME_T 1
#define _KOS_SOURCE       1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/except.h>
#include <kos/hybrid/sched-signal.h>
#include <kos/types.h>

#include <assert.h>
#include <atomic.h>
#include <string.h>

#include <libbuffer/ringbuffer.h>

#include "ringbuffer.h"

#ifdef __KERNEL__
#include <kernel/except.h>
#include <kernel/heap.h>

#include <kos/nopf.h>
#include <sys/poll.h>
#else /* __KERNEL__ */
#include <kos/futexexpr.h>
#include <malloc.h>
#endif /* !__KERNEL__ */

DECL_BEGIN

#ifndef BLOCKING
#define BLOCKING __BLOCKING
#endif /* !BLOCKING */
#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */

#ifndef __KERNEL__
typedef struct {
	__VIRT void *_hp_ptr; /* [1.._hp_siz] Pointer base address. */
	size_t       _hp_siz; /* [!0] Size of the pointer. */
} heapptr_t;
#define heapptr_getptr(self)              ((self)._hp_ptr)
#define heapptr_getsiz(self)              ((self)._hp_siz)
#define heap_free(heap, ptr, size, flags) free(ptr)
#endif /* !__KERNEL__ */



LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(CC ringbuffer_defragment)(struct ringbuffer *__restrict self) {
	if (self->rb_rptr != 0) {
		size_t lo, hi;
		hi = self->rb_size - self->rb_rptr;
		if (hi >= self->rb_avail) {
			/* Simple case: Buffer data is linear -> Just memmove() it to the base. */
			memmovedown(self->rb_data,
			            self->rb_data + self->rb_rptr,
			            self->rb_avail);
		} else {
			lo = self->rb_avail - hi;
			/* Complicated case: The buffer current looks like this:
			 *  >> HIJKLMN?????????ABCDEFG
			 *  >> <lo--->         <hi--->
			 *
			 * And we need to get it to look like this:
			 *  >> ABCDEFGHIJKLMN?????????
			 *  >> <hi---><lo--->
			 */
			/* TODO: This could be done more efficiently by using the ????-area as a temporary buffer.
			 *       Because we're eventually trying to  get rid of that area,  we can assume that  it
			 *       is non-empty (and has quite the significant size) */
			if (hi <= lo) {
				/* Shift the entire buffer upwards `hi' times */
				do {
					byte_t temp;
					temp = self->rb_data[self->rb_size - 1];
					memmoveup(self->rb_data + 1,
					          self->rb_data,
					          self->rb_size - 1);
					self->rb_data[0] = temp;
				} while (--hi);
			} else {
				/* Shift the entire buffer downwards `lo' times */
				do {
					byte_t temp;
					temp = self->rb_data[0];
					memmovedown(self->rb_data,
					            self->rb_data + 1,
					            self->rb_size - 1);
					self->rb_data[self->rb_size - 1] = temp;
				} while (--hi);
				/* The buffer now looks like this:
				 *  ?????????ABCDEFGHIJKLMN
				 *           <hi---><lo--->
				 */
				memmovedown(self->rb_data,
				            self->rb_data + (self->rb_size - self->rb_avail),
				            self->rb_avail);
			}
		}
		self->rb_rptr  = 0;
		self->rb_rdtot = 0;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(CC ringbuffer_trimbuf_and_endwrite)(struct ringbuffer *__restrict self) {
	size_t limit, thresh, unused_bytes;
	if likely(self->rb_size) {
		limit        = atomic_read(&self->rb_limit);
		thresh       = RINGBUFFER_FREE_THRESHOLD(limit);
		unused_bytes = self->rb_size - self->rb_avail;
		if (unused_bytes >= thresh) {
			if (!self->rb_avail) {
				/* Must free the entire buffer. */
#ifdef __KERNEL__
				void *free_ptr  = self->rb_data;
				size_t free_siz = self->rb_size;
#else /* __KERNEL__ */
				void *free_ptr = self->rb_data;
#endif /* !__KERNEL__ */
				self->rb_data = NULL;
				self->rb_size = 0;
				self->rb_rptr = 0;
				ringbuffer_lock_endwrite(self);
#ifdef __KERNEL__
				heap_free(&kernel_default_heap,
				          free_ptr, free_siz, GFP_NORMAL);
#else /* __KERNEL__ */
				free(free_ptr);
#endif /* !__KERNEL__ */
				return;
			} else {
				/* Defragment buffer memory, so that all unread data is located at the start.
				 * This  is  required so  we  can trim  the  back to  release  unused memory. */
				ringbuffer_defragment(self);
				assert(self->rb_rptr == 0);
#ifdef __KERNEL__
				/* Try to trim the buffer.
				 * NOTE: We use the NX-variant + GFP_ATOMIC so that we're allowed
				 *       to use  heap functions  while  holding an  atomic  lock. */
				{
					heapptr_t ptr;
					ptr = heap_realloc_nx(&kernel_default_heap,
					                      self->rb_data,
					                      self->rb_size,
					                      self->rb_avail,
					                      GFP_NORMAL | GFP_ATOMIC,
					                      GFP_NORMAL);
					if (heapptr_getsiz(ptr)) {
						assert(heapptr_getsiz(ptr) >= self->rb_avail);
						self->rb_data = (byte_t *)heapptr_getptr(ptr);
						self->rb_size = heapptr_getsiz(ptr);
					}
				}
#else /* __KERNEL__ */
				/* XXX: atomic_realloc_nx() for user-space? */
#endif /* !__KERNEL__ */
			}
		}
	}
	ringbuffer_lock_endwrite(self);
}



/* Read data from the given ring buffer.
 * When `ringbuffer_read()' is called, and no data is available, the function
 * will block  until data  becomes available,  or the  ringbuffer is  closed.
 * NOTE:  `ringbuffer_read_nonblock()' can still throw `E_WOULDBLOCK' because
 *        it may call `task_yield()'  when trying to acquire  `self->rb_lock'
 * @return: * : The number of bytes read. */
INTERN BLOCKING NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_read(struct ringbuffer *__restrict self,
                   void __USER __CHECKED *dst, size_t num_bytes)
		THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...) {
	size_t result, temp;
	IF_KERNEL(assert(!task_wasconnected()));
	result = libringbuffer_read_nonblock(self, dst, num_bytes);
	if (result || !atomic_read(&self->rb_limit)) {
done:
		return (KERNEL_SELECT(size_t, ssize_t))result;
	}
again_connect:
#ifdef __KERNEL__
	task_connect(&self->rb_nempty);
	TRY {
		/* Try to read more data. */
		temp = libringbuffer_read_nonblock(self,
		                                   (byte_t *)dst + result,
		                                   num_bytes - result);
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}
	if unlikely(temp) {
		result += temp;
		task_disconnectall();
		goto done;
	}
	if unlikely(!atomic_read(&self->rb_limit)) {
		task_disconnectall();
		goto done;
	}
	/* Wait for data to become available. */
	task_waitfor();
#else /* __KERNEL__ */
	{
		PRIVATE struct lfutexexpr const expr[] = {
			LFUTEXEXPR_TEQUAL(struct ringbuffer, rb_avail, 0),     /* self->rb_avail == 0 */
			LFUTEXEXPR_TNOT_EQUAL(struct ringbuffer, rb_limit, 0), /* self->rb_limit != 0 */
			LFUTEXEXPR_END,
		};
		if (lfutexexpr(&self->rb_nempty, self, expr, NULL, 0) < 0)
			return -1;
	}
#endif /* !__KERNEL__ */
	/* Try to read more data. */
	temp = libringbuffer_read_nonblock(self,
	                                   (byte_t *)dst + result,
	                                   num_bytes - result);
	if (temp) {
		result += temp;
		goto done;
	}
	goto again_connect;
}


INTERN NONNULL((1)) size_t CC
libringbuffer_read_nonblock(struct ringbuffer *__restrict self,
                            void __USER __CHECKED *dst, size_t num_bytes)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	bool was_full;
	size_t result = 0;
	size_t temp;
	IF_KERNEL(size_t copy_error);
	size_t linear;
#ifdef __KERNEL__
again:
#endif /* __KERNEL__ */
	ringbuffer_lock_write(self);
#ifdef __KERNEL__
again_locked:
#endif /* __KERNEL__ */
	temp = self->rb_avail;
	assert(result <= num_bytes);
	if (temp > num_bytes - result)
		temp = num_bytes - result;
	assert(self->rb_rptr < self->rb_size ||
	       (self->rb_rptr == 0 && self->rb_size == 0));
	linear = self->rb_size - self->rb_rptr;
	if (linear >= temp) {
		/* All data can be loaded from high memory. */
#ifndef __KERNEL__
		memcpy((byte_t *)dst + result,
		       self->rb_data + self->rb_rptr, temp);
#else /* !__KERNEL__ */
		copy_error = memcpy_nopf((byte_t *)dst + result,
		                         self->rb_data + self->rb_rptr, temp);
		/* Check for a #PF copy error. */
		if unlikely(copy_error) {
			byte_t next_byte;
			size_t next_byte_pos;
			assert(copy_error <= temp);
			temp -= copy_error;
			assert(temp < (num_bytes - result));
			result += temp;
			self->rb_rptr += temp;
			self->rb_rdtot += temp;
			assert(self->rb_rptr < self->rb_size);
			was_full = self->rb_avail >= self->rb_size;
			self->rb_avail -= temp;
copy_faulting_byte:
			assert(self->rb_avail != 0);
			next_byte     = self->rb_data[self->rb_rptr];
			next_byte_pos = self->rb_rdtot;
			ringbuffer_trimbuf_and_endwrite(self);
			if (was_full) {
				/* Broadcast, since there may be multiple writers. */
				sig_broadcast(&self->rb_nfull);
			}
			/* Try to copy `next_byte' into the user-supplied buffer */
			COMPILER_WRITE_BARRIER();
			((byte_t *)dst)[result] = next_byte; /* CAUTION: SEGFAULT */
			COMPILER_WRITE_BARRIER();
			/* Try to re-acquire the lock. */
			if unlikely(!ringbuffer_lock_trywrite(self)) {
				if (!result)
					goto again; /* Don't indicate EOF if there is done. */
				goto done;      /* Better just give the caller what we've found */
			}
			COMPILER_READ_BARRIER();
			if (next_byte_pos == self->rb_rdtot && likely(self->rb_avail)) {
				/* Consume the 1 byte that we've copied manually. */
				--self->rb_avail;
				++self->rb_rptr;
				++self->rb_rdtot;
				++result;
				if unlikely(self->rb_rptr >= self->rb_size)
					self->rb_rptr = 0;
			} else {
				/* Race  condition: Some other thread read the byte we were trying
				 * to  copy  to the  user-buffer while  we  didn't have  the lock.
				 * To prevent that byte from being read twice, we mustn't indicate
				 * that the byte in question never got copied in the first  place! */
			}
			goto again_locked;
		}
#endif /* __KERNEL__ */
		self->rb_rptr += temp;
		assert((self->rb_rptr == self->rb_size) == (temp == linear));
		if (temp == linear)
			self->rb_rptr = 0;
		assert(self->rb_rptr < self->rb_size ||
		       (self->rb_rptr == 0 && self->rb_size == 0));
	} else {
		size_t low_memory_bytes;
		/* The copy operation must be performed in 2 steps:
		 *  - COPY_FROM(self->rb_rptr ... +=linear-1) // Or COPY_FROM(self->rb_rptr ... self->rb_size-1)
		 *  - COPY_FROM(0 ... (temp - linear) - 1)
		 */
		assert(self->rb_size != 0);
#ifndef __KERNEL__
		memcpy((byte_t *)dst + result,
		       self->rb_data + self->rb_rptr, linear);
#else /* !__KERNEL__ */
		copy_error = memcpy_nopf((byte_t *)dst + result,
		                         self->rb_data + self->rb_rptr, linear);
		if unlikely(copy_error) {
			assert(copy_error <= linear);
			linear -= copy_error;
			assert(linear < (num_bytes - result));
			result += linear;
			self->rb_rptr += linear;
			self->rb_rdtot += linear;
			assert(self->rb_rptr < self->rb_size);
			was_full = self->rb_avail >= self->rb_size;
			self->rb_avail -= linear;
			goto copy_faulting_byte;
		}
#endif /* __KERNEL__ */
		low_memory_bytes = temp - linear;
		/* Copy low-memory */
#ifndef __KERNEL__
		memcpy((byte_t *)dst + result + linear,
		       self->rb_data, low_memory_bytes);
#else /* !__KERNEL__ */
		copy_error = memcpy_nopf((byte_t *)dst + result + linear,
		                         self->rb_data, low_memory_bytes);
		if unlikely(copy_error) {
			assert(copy_error <= low_memory_bytes);
			low_memory_bytes -= copy_error;
			result += linear; /* High memory */
			assert(linear < (num_bytes - result));
			result += low_memory_bytes; /* Low memory */
			self->rb_rptr = low_memory_bytes;
			self->rb_rdtot += linear;           /* High memory */
			self->rb_rdtot += low_memory_bytes; /* Low memory */
			assert(self->rb_rptr < self->rb_size);
			was_full = self->rb_avail >= self->rb_size;
			self->rb_avail -= linear;           /* High memory */
			self->rb_avail -= low_memory_bytes; /* Low memory */
			assert(result < num_bytes);
			goto copy_faulting_byte;
		}
#endif /* __KERNEL__ */
		self->rb_rptr = low_memory_bytes;
		assert(self->rb_rptr < self->rb_size);
	}
	/* Track the number of available bytes. */
	was_full = self->rb_avail >= self->rb_size;
	self->rb_avail -= temp;
	self->rb_rdtot += temp;
	result += temp;
	/* Don't trim the buffer if we didn't read anything.
	 * If we'd trim it in that  scenario, too, then we might  accidentally
	 * deallocate  a freshly allocated buffer before a writer can write to
	 * it. - And while that wouldn't actually be a problem, it would cause
	 * extra work that would be unnecessary otherwise. */
	if (result) {
		ringbuffer_trimbuf_and_endwrite(self);
	} else {
		ringbuffer_lock_endwrite(self);
	}
#ifdef __KERNEL__
done:
#endif /* __KERNEL__ */
	if (was_full)
		sched_signal_broadcast(&self->rb_nfull);
	return result;
}


/* Same  as  the read  functions  above, however  `ringbuffer_write()'  will block
 * when the ring buffer's  size limit has  been reached, and  the buffer is  still
 * full (and the buffer hasn't been closed), whereas `ringbuffer_write_nonblock()'
 * will not block in that scenario.
 * If the ring buffer is closed before all data could be written, the amount of
 * data (in  bytes)  that  was  written  before  it  got  closed  is  returned.
 * `ringbuffer_writesome()' is  similar to  `ringbuffer_write()', however  will
 * return  rather than  block if some  data has already  been written, where-as
 * `ringbuffer_write()' will block indefinitely until all data was written,  or
 * the ring buffer was closed.
 * NOTE: `ringbuffer_write_nonblock()' can still throw `E_WOULDBLOCK' because
 *        it may call `task_yield()' when trying to acquire `self->rb_lock',
 *        or when allocating more heap memory.
 * @return: * : The number of bytes written.
 * @return: -1: [USERSPACE] Failed to increase the buffer size (s.a. `errno = ENOMEM') */
INTERN BLOCKING NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_write(struct ringbuffer *__restrict self,
                    void __USER __CHECKED const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...)) {
	KERNEL_SELECT(size_t, ssize_t) result, temp;
	IF_KERNEL(assert(!task_wasconnected()));
	result = libringbuffer_write_nonblock(self, src, num_bytes);
#ifndef __KERNEL__
	if unlikely(result < 0)
		goto done;
#endif /* !__KERNEL__ */
	if ((size_t)result >= num_bytes || !atomic_read(&self->rb_limit)) {
done:
		return result;
	}
again_connect:
#ifdef __KERNEL__
	task_connect(&self->rb_nfull);
	TRY {
		/* Try to write more data. */
		temp = libringbuffer_write_nonblock(self,
		                                    (byte_t const *)src + result,
		                                    num_bytes - result);
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}
	if unlikely(temp) {
		result += temp;
		if (result >= num_bytes) {
			task_disconnectall();
			goto done;
		}
	} else {
		if unlikely(!atomic_read(&self->rb_limit)) {
			task_disconnectall();
			goto done;
		}
	}
	/* Wait for data to become available. */
	task_waitfor();
#else /* __KERNEL__ */
	{
		size_t size  = atomic_read(&self->rb_size);
		size_t limit = atomic_read(&self->rb_limit);
		if unlikely(!limit)
			goto done;
		/* Wait if AVAIL >= SIZE and SIZE >= LIMIT */
		if (size >= limit) {
			struct lfutexexpr expr[4];
			expr[0] = LFUTEXEXPR_FIELD(struct ringbuffer, rb_avail) >= size;
			expr[1] = LFUTEXEXPR_FIELD(struct ringbuffer, rb_size)  == size;
			expr[2] = LFUTEXEXPR_FIELD(struct ringbuffer, rb_limit) == limit;
			expr[3] = LFUTEXEXPR_END;
			if (lfutexexpr(&self->rb_nfull, self, expr, NULL, 0) < 0)
				return -1;
		}
	}
#endif /* !__KERNEL__ */
	/* Try to read more data. */
	temp = libringbuffer_write_nonblock(self,
	                                    (byte_t const *)src + result,
	                                    num_bytes - result);
#ifndef __KERNEL__
	if unlikely(temp < 0) {
		result = temp;
		goto done;
	}
#endif /* !__KERNEL__ */
	result += temp;
	if ((size_t)result >= num_bytes)
		goto done;
	goto again_connect;
}

INTERN BLOCKING NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_writesome(struct ringbuffer *__restrict self,
                        void __USER __CHECKED const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...)) {
	KERNEL_SELECT(size_t, ssize_t) result, temp;
	IF_KERNEL(assert(!task_wasconnected()));
	result = libringbuffer_write_nonblock(self, src, num_bytes);
#ifndef __KERNEL__
	if unlikely(result < 0)
		goto done;
#endif /* !__KERNEL__ */
	if (result || !atomic_read(&self->rb_limit)) {
done:
		return result;
	}
	if unlikely(!num_bytes)
		goto done; /* No-op */
again_connect:
#ifdef __KERNEL__
	task_connect(&self->rb_nfull);
	TRY {
		/* Try to read write data. */
		temp = libringbuffer_write_nonblock(self,
		                                    (byte_t const *)src + result,
		                                    num_bytes - result);
	} EXCEPT {
		task_disconnectall();
		RETHROW();
	}
	if unlikely(temp) {
		result += temp;
		task_disconnectall();
		goto done;
	}
	if unlikely(!atomic_read(&self->rb_limit)) {
		task_disconnectall();
		goto done;
	}
	/* Wait for data to become available. */
	task_waitfor();
#else /* __KERNEL__ */
	{
		size_t size  = atomic_read(&self->rb_size);
		size_t limit = atomic_read(&self->rb_limit);
		if unlikely(!limit)
			goto done;
		/* Wait if AVAIL >= SIZE and SIZE >= LIMIT */
		if (size >= limit) {
			struct lfutexexpr expr[4];
			expr[0] = LFUTEXEXPR_FIELD(struct ringbuffer, rb_avail) >= size;
			expr[1] = LFUTEXEXPR_FIELD(struct ringbuffer, rb_size)  == size;
			expr[2] = LFUTEXEXPR_FIELD(struct ringbuffer, rb_limit) == limit;
			expr[3] = LFUTEXEXPR_END;
			if (lfutexexpr(&self->rb_nfull, self, expr, NULL, 0) < 0)
				return -1;
		}
	}
#endif /* !__KERNEL__ */
	/* Try to read more data. */
	temp = libringbuffer_write_nonblock(self,
	                                    (byte_t const *)src + result,
	                                    num_bytes - result);
	if (temp != 0) {
#ifndef __KERNEL__
		if unlikely(temp < 0) {
			result = temp;
			goto done;
		}
#endif /* !__KERNEL__ */
		result += temp;
		goto done;
	}
	goto again_connect;
}

INTERN NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_write_nonblock(struct ringbuffer *__restrict self,
                             void __USER __CHECKED const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK)) {
	size_t result;
again:
	result = libringbuffer_write_nonblock_noalloc(self, src, num_bytes);
	if (!result && atomic_read(&self->rb_limit) != 0) {
		size_t limit;
		if unlikely(!num_bytes)
			goto done; /* No-op */
		/* Check if we must allocate a new/larger buffer. */
		ringbuffer_lock_read(self);
		limit = atomic_read(&self->rb_limit);
		if (self->rb_size < limit &&
		    self->rb_avail >= self->rb_size) {
			size_t new_bufsize;
			heapptr_t new_buffer;
			/* Allocate a larger buffer. */
			new_bufsize = self->rb_avail + num_bytes;
			ringbuffer_lock_endread(self);
			if unlikely(new_bufsize > limit)
				new_bufsize = limit;
			/* Allocate the new buffer. */
#ifdef __KERNEL__
			new_buffer = heap_alloc(&kernel_default_heap,
			                        new_bufsize,
			                        GFP_NORMAL);
#else /* __KERNEL__ */
			new_buffer._hp_ptr = malloc(new_bufsize);
			if unlikely(!new_buffer._hp_ptr)
				return -1;
			new_buffer._hp_siz = malloc_usable_size(new_buffer._hp_ptr);
#endif /* !__KERNEL__ */
			assert(heapptr_getsiz(new_buffer) >= new_bufsize);
			TRY {
				ringbuffer_lock_write(self);
			} EXCEPT {
				heap_free(&kernel_default_heap,
				          heapptr_getptr(new_buffer),
				          heapptr_getsiz(new_buffer),
				          GFP_NORMAL);
				RETHROW();
			}
			/* Install the new buffer (if it is larger than the current
			 * one,   but  smaller  than  the  (now)  effective  limit) */
			if (heapptr_getsiz(new_buffer) > self->rb_size &&
			    heapptr_getsiz(new_buffer) <= atomic_read(&self->rb_limit)) {
				/* Copy old buffer data. */
				size_t old_buffer_size = self->rb_size;
				if (old_buffer_size) {
					byte_t *old_buffer_base;
					size_t lo, hi;
					old_buffer_base = self->rb_data;
					hi              = old_buffer_size - self->rb_rptr;
					if (hi >= self->rb_avail) {
						lo = 0;
						hi = self->rb_avail;
					} else {
						lo = self->rb_avail - hi;
					}
					memcpy((byte_t *)heapptr_getptr(new_buffer), old_buffer_base + self->rb_rptr, hi);
					memcpy((byte_t *)heapptr_getptr(new_buffer) + hi, old_buffer_base, lo);
					self->rb_data  = (byte_t *)heapptr_getptr(new_buffer);
					self->rb_size  = heapptr_getsiz(new_buffer);
					self->rb_rptr  = 0;
					self->rb_rdtot = 0;
					ringbuffer_lock_endwrite(self);
					heap_free(&kernel_default_heap,
					          old_buffer_base,
					          old_buffer_size,
					          GFP_NORMAL);
				} else {
					self->rb_data  = (byte_t *)heapptr_getptr(new_buffer);
					self->rb_size  = heapptr_getsiz(new_buffer);
					self->rb_rdtot = 0;
					assert(self->rb_rptr == 0);
					assert(self->rb_avail == 0);
					ringbuffer_lock_endwrite(self);
				}
			} else {
				ringbuffer_lock_endwrite(self);
				heap_free(&kernel_default_heap,
				          heapptr_getptr(new_buffer),
				          heapptr_getsiz(new_buffer),
				          GFP_NORMAL);
			}
			goto again;
		}
		ringbuffer_lock_endread(self);
	}
done:
	return result;
}

/* Same as `ringbuffer_write_nonblock()', but don't increase the buffer's size. */
INTERN NONNULL((1)) size_t CC
libringbuffer_write_nonblock_noalloc(struct ringbuffer *__restrict self,
                                     void __USER __CHECKED const *src, size_t num_bytes)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	bool was_empty;
	size_t result = 0;
	size_t temp;
	IF_KERNEL(size_t copy_error);
	size_t linear;
	size_t wptr;
	size_t limit;
#ifdef __KERNEL__
again:
#endif /* __KERNEL__ */
	ringbuffer_lock_write(self);
#ifdef __KERNEL__
again_locked:
#endif /* __KERNEL__ */
	if unlikely(!self->rb_size) {
		/* Special case: No buffer allocated
		 * This has to be checked specifically, since the module operation of
		 * the next line would otherwise cause an E_DIVIDE_BY_ZERO exception. */
		assert(self->rb_rptr == 0);
		assert(self->rb_avail == 0);
		/* Even though the buffer was empty, it still is, so we don't signal NEMPTY */
		was_empty = false;
		goto done_unlock;
	}
	assert(self->rb_rptr < self->rb_size);
	assert(self->rb_avail <= self->rb_size);
	wptr  = (self->rb_rptr + self->rb_avail) % self->rb_size;
	temp  = self->rb_size - self->rb_avail;
	limit = atomic_read(&self->rb_limit);
	/* Don't exceed the currently set buffer limit! */
	if (self->rb_size > limit) {
		/* Current buffer size is greater than the set limit */
		if (self->rb_avail >= limit) {
			/* Number of written bytes exceeds the buffer limit.
			 * -> In  this  case  we're not  allowed  to  write  anything!
			 * HINT: This is the likely case once a ringbuffer was closed! */
			was_empty = false;
			goto done_unlock;
		}
		/* Limit the amount of bytes we're allowed to
		 * write  to  the user-specified  pipe limit. */
		temp = limit - self->rb_avail;
	}
	assert(result <= num_bytes);
	if (temp > num_bytes - result)
		temp = num_bytes - result;
	linear = self->rb_size - wptr;
	if (linear >= temp) {
		/* All data can be written linearly at `wptr...+=temp' */
#ifndef __KERNEL__
		memcpy(self->rb_data + wptr,
		       (byte_t const *)src + result, temp);
#else /* !__KERNEL__ */
		copy_error = memcpy_nopf(self->rb_data + wptr,
		                         (byte_t const *)src + result, temp);
		if unlikely(copy_error) {
			/* Must copy the next byte without holding a lock. */
			byte_t next_byte;
			size_t next_byte_pos;
			assert(copy_error <= temp);
			temp -= copy_error;
			assert(temp < (num_bytes - result));
			was_empty = self->rb_avail == 0;
			self->rb_avail += temp;
			result += temp;
copy_faulting_byte:
			next_byte_pos = self->rb_rdtot + self->rb_avail;
			ringbuffer_lock_endwrite(self);
			if (was_empty)
				sched_signal_broadcast(&self->rb_nempty);
			/* Try to copy `next_byte' from the user-supplied buffer */
			COMPILER_READ_BARRIER();
			next_byte = ((byte_t const *)src)[result]; /* CAUTION: SEGFAULT */
			COMPILER_READ_BARRIER();
			/* Try to re-acquire the lock. */
			if unlikely(!ringbuffer_lock_trywrite(self)) {
				if (!result)
					goto again; /* Don't indicate EOF if there is done. */
				goto done;      /* Better just tell the caller what we've managed to copy */
			}
			COMPILER_READ_BARRIER();
			if (next_byte_pos == self->rb_rdtot + self->rb_avail &&
			    likely(self->rb_avail < self->rb_size)) {
				/* Store the 1 byte that we've copied manually. */
				wptr                = (self->rb_rptr + self->rb_avail) % self->rb_size;
				self->rb_data[wptr] = next_byte;
				++self->rb_avail;
				++result;
				if unlikely(self->rb_rptr >= self->rb_size)
					self->rb_rptr = 0;
			} else {
				/* Race  condition: Some other  thread wrote the  byte we were trying
				 * to  copy  from  the user-buffer  while  we didn't  have  the lock.
				 * To prevent that byte from being written twice, we mustn't indicate
				 * that  the byte  in question never  got copied in  the first place! */
			}
			goto again_locked;
		}
#endif /* __KERNEL__ */
	} else {
		size_t low_memory_bytes;
		/* The copy operation must be performed in 2 steps:
		 *  - COPY_TO(wptr ... +=linear-1)        // Or COPY_TO(wptr ... self->rb_size-1)
		 *  - COPY_TO(0 ... (temp - linear) - 1)
		 */
#ifndef __KERNEL__
		memcpy(self->rb_data + wptr,
		       (byte_t const *)src + result, linear);
#else /* !__KERNEL__ */
		copy_error = memcpy_nopf(self->rb_data + wptr,
		                         (byte_t const *)src + result, linear);
		if unlikely(copy_error) {
			assert(copy_error <= linear);
			linear -= copy_error;
			assert(linear < (num_bytes - result));
			result += linear;
			was_empty = self->rb_avail == 0;
			self->rb_avail += linear;
			goto copy_faulting_byte;
		}
#endif /* __KERNEL__ */
		low_memory_bytes = temp - linear;
		/* Copy low-memory */
#ifndef __KERNEL__
		memcpy(self->rb_data,
		       (byte_t const *)src + result + linear,
		       low_memory_bytes);
#else /* !__KERNEL__ */
		copy_error = memcpy_nopf(self->rb_data,
		                         (byte_t const *)src + result + linear,
		                         low_memory_bytes);
		if unlikely(copy_error) {
			assert(copy_error <= low_memory_bytes);
			low_memory_bytes -= copy_error;
			result += linear; /* High memory */
			assert(linear < (num_bytes - result));
			result += low_memory_bytes; /* Low memory */
			was_empty = self->rb_avail == 0;
			self->rb_avail += linear;           /* High memory */
			self->rb_avail += low_memory_bytes; /* Low memory */
			assert(result < num_bytes);
			goto copy_faulting_byte;
		}
#endif /* __KERNEL__ */
	}

	/* Track the number of available bytes. */
	was_empty = self->rb_avail == 0;
	self->rb_avail += temp;
	result += temp;
done_unlock:
	ringbuffer_lock_endwrite(self);
#ifdef __KERNEL__
done:
#endif /* __KERNEL__ */
	if (was_empty)
		sched_signal_broadcast(&self->rb_nempty);
	return result;
}


/* Try to unread up to `num_bytes' of data that had yet to be re-written
 * @param: p_rdtot: When non-NULL, store the new number of total read bytes since the last re-size in there
 * @return: * : The actual number of unread bytes. */
INTERN NONNULL((1)) size_t CC
libringbuffer_unread(struct ringbuffer *__restrict self,
                     size_t num_bytes, size_t *p_rdtot)
		THROWS(E_WOULDBLOCK) {
	size_t result;
	bool was_empty = false;
	ringbuffer_lock_write(self);
	/* Figure out how many bytes can potentially be unread */
	result = self->rb_size - self->rb_avail;
	/* Limit how much can be unread by the total number of read bytes. */
	if (result > self->rb_rdtot)
		result = self->rb_rdtot;
	if (result > num_bytes)
		result = num_bytes;
	if (result) {
		if (self->rb_rptr >= result) {
			self->rb_rptr -= result;
		} else {
			self->rb_rptr = self->rb_size - result;
		}
		was_empty = self->rb_avail == 0;
		self->rb_avail += result;
		self->rb_rdtot -= result;
	}
	if (p_rdtot)
		*p_rdtot = self->rb_rdtot;
	ringbuffer_lock_endwrite(self);
	if (was_empty)
		sched_signal_broadcast(&self->rb_nempty);
	return result;
}

/* Skip up to `num_bytes' of unread data, returning the actual number of skipped bytes.
 * @param: p_rdtot: When non-NULL, store the new number of total read bytes since the last re-size in there
 * @return: * : The actual number of skipped bytes. */
INTERN NONNULL((1)) size_t CC
libringbuffer_skipread(struct ringbuffer *__restrict self,
                       size_t num_bytes, size_t *p_rdtot)
		THROWS(E_WOULDBLOCK) {
	size_t result;
	bool was_full;
	ringbuffer_lock_write(self);
	result = self->rb_avail;
	if (result > num_bytes)
		result = num_bytes;
	self->rb_rptr += result;
	if (self->rb_rptr > self->rb_size)
		self->rb_rptr -= self->rb_size;
	assert(self->rb_rptr < self->rb_size ||
	       (self->rb_rptr == 0 && self->rb_size == 0));
	was_full = self->rb_avail >= self->rb_size;
	self->rb_avail -= result;
	self->rb_rdtot += result;
	if (p_rdtot)
		*p_rdtot = self->rb_rdtot;
	ringbuffer_lock_endwrite(self);
	if (was_full)
		sched_signal_broadcast(&self->rb_nfull);
	return result;
}

/* A combination of `ringbuffer_unread()' and `ringbuffer_skipread()' that can be used
 * to some-what implement support for SEEK_CUR for ring buffers, where negative values
 * for `offset'  will call  `ringbuffer_unread()', whilst  positive values  will  call
 * `ringbuffer_skipread()'
 * The return value is always the new total number of read bytes since the last re-size. */
INTERN NONNULL((1)) size_t CC
libringbuffer_rseek(struct ringbuffer *__restrict self, ssize_t offset)
		THROWS(E_WOULDBLOCK) {
	size_t result;
	if (offset < 0) {
		libringbuffer_unread(self, (size_t)-offset, &result);
	} else if (offset > 0) {
		libringbuffer_skipread(self, (size_t)offset, &result);
	} else {
		result = atomic_read(&self->rb_rdtot);
	}
	return result;
}

/* Try to unwrite up to `num_bytes' of data that had yet to be read
 * @param: p_wrtot: When non-NULL, store the new number of total written bytes since the last re-size in there
 * @return: * : The actual number of unwritten bytes. */
INTERN NONNULL((1)) size_t CC
libringbuffer_unwrite(struct ringbuffer *__restrict self,
                      size_t num_bytes, size_t *p_wrtot)
		THROWS(E_WOULDBLOCK) {
	size_t result;
	bool was_full;
	ringbuffer_lock_write(self);
	result = self->rb_avail;
	if (result > num_bytes)
		result = num_bytes;
	was_full = self->rb_avail >= self->rb_size;
	self->rb_avail -= result;
	if (p_wrtot)
		*p_wrtot = self->rb_rdtot + self->rb_avail;
	ringbuffer_lock_endwrite(self);
	if (was_full)
		sched_signal_broadcast(&self->rb_nfull);
	return result;
}

/* By using `ringbuffer_unwrite()', implement support for SEEK_CUR when `offset' is negative
 * Alternatively, when `offset' is positive, don't do anything.
 * The return value is always the new total number of written bytes since the last re-size. */
INTERN NONNULL((1)) size_t CC
libringbuffer_wseek(struct ringbuffer *__restrict self, ssize_t offset)
		THROWS(E_WOULDBLOCK) {
	size_t result;
	if (offset < 0) {
		libringbuffer_unwrite(self, (size_t)-offset, &result);
	} else {
		ringbuffer_lock_write(self);
		result = self->rb_rdtot + self->rb_avail;
		ringbuffer_lock_endwrite(self);
	}
	return result;
}

/* Set the total amount of written, but yet-to-be read bytes.
 * If `num_bytes' is larger than the previous total number of written bytes, don't truncate the buffer.
 * @return: * : The actual number of now-written bytes. */
INTERN NONNULL((1)) size_t CC
libringbuffer_setwritten(struct ringbuffer *__restrict self, size_t num_bytes)
		THROWS(E_WOULDBLOCK) {
	size_t result;
	bool was_full;
	ringbuffer_lock_write(self);
	was_full = self->rb_avail >= self->rb_size;
	if (self->rb_avail > num_bytes)
		self->rb_avail = num_bytes;
	result = self->rb_avail;
	ringbuffer_lock_endwrite(self);
	if (was_full && num_bytes < result)
		sched_signal_broadcast(&self->rb_nfull);
	return result;
}

DEFINE_PUBLIC_ALIAS(ringbuffer_read, libringbuffer_read);
DEFINE_PUBLIC_ALIAS(ringbuffer_read_nonblock, libringbuffer_read_nonblock);
DEFINE_PUBLIC_ALIAS(ringbuffer_write, libringbuffer_write);
DEFINE_PUBLIC_ALIAS(ringbuffer_writesome, libringbuffer_writesome);
DEFINE_PUBLIC_ALIAS(ringbuffer_write_nonblock, libringbuffer_write_nonblock);
DEFINE_PUBLIC_ALIAS(ringbuffer_write_nonblock_noalloc, libringbuffer_write_nonblock_noalloc);
DEFINE_PUBLIC_ALIAS(ringbuffer_unread, libringbuffer_unread);
DEFINE_PUBLIC_ALIAS(ringbuffer_skipread, libringbuffer_skipread);
DEFINE_PUBLIC_ALIAS(ringbuffer_rseek, libringbuffer_rseek);
DEFINE_PUBLIC_ALIAS(ringbuffer_unwrite, libringbuffer_unwrite);
DEFINE_PUBLIC_ALIAS(ringbuffer_wseek, libringbuffer_wseek);
DEFINE_PUBLIC_ALIAS(ringbuffer_setwritten, libringbuffer_setwritten);

DECL_END

#endif /* !GUARD_LIBBUFFER_RINGBUFFER_C */
