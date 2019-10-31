/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBBUFFER_LINEBUFFER_C
#define GUARD_LIBBUFFER_LINEBUFFER_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <kos/except.h>
#include <hybrid/compiler.h>
#include <hybrid/atomic.h>

#include <libbuffer/linebuffer.h>
#include <assert.h>
#include <string.h>

#include "linebuffer.h"

#ifdef __KERNEL__
#include <kernel/vm.h>
#include <kernel/except.h>
#include <sched/signal.h>
#define HEAP_FREE(base, size) \
	((size) ? heap_free(&kernel_default_heap, base, size, GFP_NORMAL) : (void)0)
#else /* __KERNEL__ */
#include <stddef.h>
#include <malloc.h>
#include <kos/futexexpr.h>
#define HEAP_FREE(base, size) free(base)
#endif /* !__KERNEL__ */




DECL_BEGIN


#ifndef __KERNEL__

struct heapptr {
	__VIRT void *hp_ptr; /* [1..hp_siz] Pointer base address. */
	size_t       hp_siz; /* [!0] Size of the pointer. */
};


PRIVATE NONNULL((1)) int CC
linebuffer_waitfor(struct linebuffer *__restrict self) {
	/* We've got 2 conditions that must be met in order to be allowed to wait:
	 *  - self->lb_limt == CACHED_LIMIT
	 *  - self->lb_line.lc_size >= CACHED_LIMIT
	 * ... where `CACHED_LIMIT' is is the lazily loaded value of `self->lb_limt'
	 */
	struct lfutexexpr expr[2];
	size_t limit = ATOMIC_READ(self->lb_limt);
	if (!limit)
		return 1; /* Empty limit */
	if (ATOMIC_READ(self->lb_line.lc_size) < limit)
		return 1;
	/* Verify that our read limit is still correct */
	expr[0] = LFUTEXEXPR_FIELD(struct linebuffer, lb_limt) == limit;
	/* Verify that the current line cannot be extended with our read limit. */
	expr[1] = LFUTEXEXPR_FIELD(struct linebuffer, lb_line.lc_size) >= limit;
	return lfutexlockexpr(&self->lb_nful, self,
	                      COMPILER_LENOF(expr), expr,
	                      NULL, 0);
}

#endif /* !__KERNEL__ */


/* Re-write the used area of the given capture within the given buffer.
 * For this purpose, try to re-instate `capture' as the active line, or
 * alternatively (when new data has already been written), write the contents
 * of the capture using `linebuffer_write()', before destroying the capture.
 * @return: * : The number of re-written bytes.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTERN NONNULL((1, 2)) linebuffer_retval_t CC
liblinebuffer_rewrite(struct linebuffer *__restrict self,
                      /*inherit(always)*/ struct linecapture *__restrict capture)
		KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		              __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT)) {
	linebuffer_retval_t result;
	if unlikely(!capture->lc_alloc)
		return 0;
	atomic_rwlock_write(&self->lb_lock);
	if likely(!self->lb_line.lc_alloc) {
		self->lb_line = *capture;
		result        = capture->lc_size;
		atomic_rwlock_endwrite(&self->lb_lock);
	} else {
		atomic_rwlock_endwrite(&self->lb_lock);
		TRY {
			result = liblinebuffer_write(self,
			                             capture->lc_base,
			                             capture->lc_size);
		} EXCEPT {
			HEAP_FREE(capture->lc_base,
			          capture->lc_alloc);
			RETHROW();
		}
		HEAP_FREE(capture->lc_base,
		          capture->lc_alloc);
	}
#ifndef NDEBUG
	memset(capture, 0xcc, sizeof(*capture));
#endif
	return result;
}

/* Append up to `num_bytes' of data from `src' to the current line.
 * If the line is too small to contain all data, wait until the line
 * is emptied before writing more data.
 * If the linebuffer is closed before all data could be written, return
 * the amount of written data, or 0 if the buffer was already closed when
 * the function was called.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTERN NONNULL((1)) linebuffer_retval_t CC
liblinebuffer_write(struct linebuffer *__restrict self,
                    __USER __CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		              __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT)) {
	linebuffer_retval_t temp, result = 0;
#ifdef __KERNEL__
	assert(!task_isconnected());
#endif /* __KERNEL__ */
again:
	assert((size_t)result <= num_bytes);
	temp = liblinebuffer_write_nonblock(self,
	                                    (byte_t *)src + result,
	                                    num_bytes - result);
	if likely(temp) {
#ifdef __KERNEL__
account_temp:
#else /* __KERNEL__ */
		if unlikely(temp < 0)
			return temp;
#endif /* !__KERNEL__ */
		result += temp;
		assert((size_t)result <= num_bytes);
		if ((size_t)result >= num_bytes) {
done:
			return result;
		}
		goto again;
	}
	if unlikely(!ATOMIC_READ(self->lb_limt))
		goto done;
	if unlikely(!num_bytes)
		goto done; /* We weren't actually supposed to do anything... */
#ifdef __KERNEL__
	/* Wait for the buffer */
	task_connect(&self->lb_nful);
	temp = linebuffer_write_nonblock(self,
	                                 src,
	                                 num_bytes);
	if likely(!temp) {
		if unlikely(!ATOMIC_READ(self->lb_limt)) {
			task_disconnectall();
			goto done;
		}
		task_waitfor();
		goto again;
	}
	task_disconnectall();
	goto account_temp;
#else /* __KERNEL__ */
	/* Wait for data to become available. */
	if unlikely(linebuffer_waitfor(self) < 0)
		return -1;
	goto again;
#endif /* !__KERNEL__ */
}

/* Similar to `linebuffer_write()', but only block if the line was full
 * the first time the function was called. If the linebuffer is closed
 * before at least 1 byte of data could be written, 0 is returned.
 * Alternatively, if the given buffer is zero-length, 0 is always returned.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTERN NONNULL((1)) linebuffer_retval_t CC
liblinebuffer_writesome(struct linebuffer *__restrict self,
                        __USER __CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		              __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT)) {
	linebuffer_retval_t result;
#ifdef __KERNEL__
	assert(!task_isconnected());
#endif /* __KERNEL__ */
again:
	result = liblinebuffer_write_nonblock(self,
	                                      src,
	                                      num_bytes);
#ifdef __KERNEL__
	assert(result <= num_bytes);
#else /* __KERNEL__ */
	assert(result < 0 || (size_t)result <= num_bytes);
#endif /* !__KERNEL__ */
	if (!result && ATOMIC_READ(self->lb_limt) != 0) {
#ifdef __KERNEL__
		/* Wait for the buffer */
		task_connect(&self->lb_nful);
		result = liblinebuffer_write_nonblock(self,
		                                      src,
		                                      num_bytes);
		assert(result <= num_bytes);
		if likely(!result && ATOMIC_READ(self->lb_limt)) {
			task_waitfor();
			goto again;
		}
		task_disconnectall();
#else /* __KERNEL__ */
		if unlikely(linebuffer_waitfor(self) < 0)
			return -1;
		goto again;
#endif /* !__KERNEL__ */
	}
	return result;
}

/* Similar to `linebuffer_write()', but never block before writing data.
 * If the given buffer was full at the time of this function being called,
 * or had been closed, then 0 is returned immediately.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTERN NONNULL((1)) linebuffer_retval_t CC
liblinebuffer_write_nonblock(struct linebuffer *__restrict self,
                             __USER __CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		              __THROWS(E_SEGFAULT, E_WOULDBLOCK)) {
#ifdef __KERNEL__
	size_t temp, result = 0;
#endif /* !__KERNEL__ */
	size_t maxwrite, limit;
again:
	atomic_rwlock_write(&self->lb_lock);
#ifdef __KERNEL__
	assert(result <= num_bytes);
again_locked:
#endif /* __KERNEL__ */
	limit = ATOMIC_READ(self->lb_limt);
	if unlikely(self->lb_line.lc_size >= limit) {
		atomic_rwlock_endwrite(&self->lb_lock);
		return 0; /* Cannot write anything now... */
	}
	assert(self->lb_line.lc_alloc >= self->lb_line.lc_size);
	maxwrite = self->lb_line.lc_alloc - self->lb_line.lc_size;
#ifdef __KERNEL__
	assert(result <= num_bytes);
	if (maxwrite >= num_bytes - result)
		maxwrite = num_bytes - result;
	else
#else /* __KERNEL__ */
	if (maxwrite >= num_bytes)
		maxwrite = num_bytes;
	else
#endif /* !__KERNEL__ */
	{
		/* Allocate a new buffer.
		 * NOTE: We try this once in atomic mode so we get a chance to re-
		 *       allocate the existing buffer without having to allocate 2
		 *       of them at any point. */
		size_t new_size;
		struct heapptr newline;
#ifdef __KERNEL__
		new_size = self->lb_line.lc_size + (num_bytes - result);
#else /* __KERNEL__ */
		new_size = self->lb_line.lc_size + num_bytes;
#endif /* !__KERNEL__ */
		if unlikely(new_size > limit)
			new_size = limit;
		assert(new_size > self->lb_line.lc_size);
#ifdef __KERNEL__
		newline = heap_realloc_nx(&kernel_default_heap,
		                          self->lb_line.lc_base,
		                          self->lb_line.lc_alloc,
		                          new_size,
		                          GFP_NORMAL | GFP_ATOMIC,
		                          GFP_NORMAL | GFP_ATOMIC);
		if (newline.hp_siz) {
			assert(newline.hp_siz >= new_size);
			assert(newline.hp_siz >= self->lb_line.lc_size);
			/* Install the new buffer directly. */
			maxwrite               = newline.hp_siz - self->lb_line.lc_size;
			self->lb_line.lc_base  = (byte_t *)newline.hp_ptr;
			self->lb_line.lc_alloc = newline.hp_siz;
			if (maxwrite > num_bytes)
				maxwrite = num_bytes;
		} else
#else /* __KERNEL__ */
		/* XXX: atomic_realloc_nx() for userspace? */
#endif /* !__KERNEL__ */
		{
			struct heapptr oldline;
			/* Need to release the line-lock to allocate a new buffer. */
			atomic_rwlock_endwrite(&self->lb_lock);
#ifdef __KERNEL__
			newline = heap_alloc(&kernel_default_heap,
			                     new_size,
			                     GFP_NORMAL);
#else /* __KERNEL__ */
			newline.hp_ptr = malloc(new_size);
			newline.hp_siz = malloc_usable_size(newline.hp_ptr);
#endif /* !__KERNEL__ */
			oldline = newline;
			atomic_rwlock_write(&self->lb_lock);
			COMPILER_READ_BARRIER();
			/* Check for race condition: Another thread expanded the buffer in
			 * the mean time, or the buffer was closed/before more limited. */
			limit = ATOMIC_READ(self->lb_limt);
			if likely(self->lb_line.lc_alloc < newline.hp_siz && new_size <= limit) {
				assert(self->lb_line.lc_size <= self->lb_line.lc_alloc);
				oldline.hp_ptr = self->lb_line.lc_base;
				oldline.hp_siz = self->lb_line.lc_alloc;
				memcpy(newline.hp_ptr,
				       oldline.hp_ptr,
				       self->lb_line.lc_size);
				self->lb_line.lc_base  = (byte_t *)newline.hp_ptr;
				self->lb_line.lc_alloc = newline.hp_siz;
			}
			atomic_rwlock_endwrite(&self->lb_lock);
			/* We could keep our lock to `lb_lock' here, but it's better to
			 * only ever be holding atomic locks for as short as possible. */
			HEAP_FREE(oldline.hp_ptr,
			          oldline.hp_siz);
			goto again;
		}
		assert(maxwrite != 0);
#ifdef __KERNEL__
		assert((result + maxwrite) <= num_bytes);
		assert(result < num_bytes);
#else /* __KERNEL__ */
		assert(maxwrite <= num_bytes);
#endif /* !__KERNEL__ */
	}
	assert(maxwrite || !num_bytes);

	/* Copy data to the buffer. */
#ifdef __KERNEL__
	assert((result + maxwrite) <= num_bytes);
	temp = memcpy_nopf(self->lb_line.lc_base + self->lb_line.lc_size,
	                   (byte_t *)src + result, maxwrite);
	if unlikely(temp) {
		byte_t next_byte;
		maxwrite -= temp;
		result += maxwrite;
		assert(result <= num_bytes);
		atomic_rwlock_endwrite(&self->lb_lock);
		/* Need to copy a single byte from the user-buffer. */
		COMPILER_READ_BARRIER();
		next_byte = ((byte_t *)src)[result];
		COMPILER_READ_BARRIER();
		atomic_rwlock_write(&self->lb_lock);
		COMPILER_READ_BARRIER();
		if likely(self->lb_line.lc_size < self->lb_line.lc_alloc) {
			self->lb_line.lc_base[self->lb_line.lc_size] = next_byte;
			++self->lb_line.lc_size;
			++result;
			assert(result <= num_bytes);
		}
		goto again_locked;
	}
	result += maxwrite;
	assert(result <= num_bytes);
#else /* __KERNEL__ */
	memcpy(self->lb_line.lc_base + self->lb_line.lc_size,
	       src, maxwrite);
#endif /* !__KERNEL__ */
	/* Account for written data. */
	self->lb_line.lc_size += maxwrite;
	assert(self->lb_line.lc_size <= self->lb_line.lc_alloc);
/*done:*/
	atomic_rwlock_endwrite(&self->lb_lock);
#ifdef __KERNEL__
	assert(result <= num_bytes);
	return result;
#else /* __KERNEL__ */
	assert(maxwrite <= num_bytes);
	return maxwrite;
#endif /* !__KERNEL__ */
}


DEFINE_PUBLIC_ALIAS(linebuffer_rewrite, liblinebuffer_rewrite);
DEFINE_PUBLIC_ALIAS(linebuffer_write, liblinebuffer_write);
DEFINE_PUBLIC_ALIAS(linebuffer_writesome, liblinebuffer_writesome);
DEFINE_PUBLIC_ALIAS(linebuffer_write_nonblock, liblinebuffer_write_nonblock);

DECL_END

#endif /* !GUARD_LIBBUFFER_LINEBUFFER_C */
