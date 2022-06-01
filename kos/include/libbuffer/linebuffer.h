/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBBUFFER_LINEBUFFER_H
#define _LIBBUFFER_LINEBUFFER_H 1

#include "api.h"

#include <hybrid/__atomic.h>
#include <hybrid/sched/atomic-lock.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/hybrid/sched-signal.h>

#ifndef _POSIX_MAX_INPUT
#include <limits.h>
#endif /* !_POSIX_MAX_INPUT */

#ifdef __KERNEL__
#include <kernel/heap.h> /* heap_free */
#else /* __KERNEL__ */
#include <libc/malloc.h> /* __libc_free */
#endif /* !__KERNEL__ */

#ifndef __INTELLISENSE__
#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>
#endif /* !__INTELLISENSE__ */

/* Implementation of the canonical line-buffer used
 * to store the contents of unconfirmed user-input. */

__DECL_BEGIN

#ifdef __CC__

struct linecapture {
	/* Descriptor for data captured from a linebuffer */
	__byte_t   *lc_base;  /* [0..lc_size|alloc(lc_alloc)][owned] Captured data */
	__size_t    lc_size;  /* Used buffer size */
	__size_t    lc_alloc; /* Allocated buffer size */
};

#ifdef __KERNEL__
#define linecapture_fini(self)         \
	((self)->lc_alloc                  \
	 ? heap_free(&kernel_default_heap, \
	             (self)->lc_base,      \
	             (self)->lc_alloc,     \
	             GFP_NORMAL)           \
	 : (void)0)
#elif defined(__CRT_HAVE_free)
#define linecapture_fini(self) \
	__libc_free((self)->lc_base)
#else /* ... */
#define linecapture_fini(self) \
	(void)0
#endif /* !... */



struct linebuffer {
	/* A linebuffer  is a  special kind  of buffer  that is  designed to  be
	 * written to in  a way similar  to a ring  buffer (in that  consecutive
	 * writes will form a continuous data  stream, and in that there  exists
	 * a maximal size to which a line buffer may grow), however unlike  with
	 * a ring buffer, a line buffer is not read linearly. - Instead, reading
	 * is done by capturing the entirety of the line buffer's contents as  a
	 * whole, and stealing them, to-be processed afterwards, and  eventually
	 * re-used, or destroyed when data has been processed.
	 * This  in turn allows  data to be collected  before being processed in
	 * larger batches. -  It also  offers itself  as a  way of  implementing
	 * canonical line-buffers in TTYs, where user-input needs to be buffered
	 * until an end-of-line character is received. */
	struct atomic_lock lb_lock; /* Lock for this line buffer */
	struct linecapture lb_line; /* [lock(lb_lock)] The current line */
	__WEAK __size_t    lb_limt; /* Max # of bytes that may appear in a single line
	                             * When set to 0, the buffer is considered  closed */
	sched_signal_t     lb_nful; /* Signal broadcast when the buffer becomes non-full, or gets closed */
};

/* Static initialization */
#define LINEBUFFER_DEFAULT_LIMIT  _POSIX_MAX_INPUT
#define LINEBUFFER_INIT_EX(limit) { ATOMIC_LOCK_INIT, { __NULLPTR, 0, 0 }, limit, SCHED_SIGNAL_INIT }
#define LINEBUFFER_INIT           LINEBUFFER_INIT_EX(LINEBUFFER_DEFAULT_LIMIT)

/* Initialization / finalization */
#define linebuffer_init_ex(self, limit)                      \
	(atomic_lock_init(&(self)->lb_lock),                     \
	 (self)->lb_line.lc_size = (self)->lb_line.lc_alloc = 0, \
	 (self)->lb_limt = (limit), sched_signal_init(&(self)->lb_nful))
#define linebuffer_cinit_ex(self, limit)                    \
	(atomic_lock_cinit(&(self)->lb_lock),                   \
	 __hybrid_assert((self)->lb_line.lc_base == __NULLPTR), \
	 __hybrid_assert((self)->lb_line.lc_size == 0),         \
	 __hybrid_assert((self)->lb_line.lc_alloc == 0),        \
	 (self)->lb_limt = (limit),                             \
	 sched_signal_cinit(&(self)->lb_nful))
#define linebuffer_init(self)   linebuffer_init_ex(self, LINEBUFFER_DEFAULT_LIMIT)
#define linebuffer_cinit(self)  linebuffer_cinit_ex(self, LINEBUFFER_DEFAULT_LIMIT)
#define linebuffer_fini(self)                           \
	(sched_signal_broadcast_for_fini(&(self)->lb_nful), \
	 linecapture_fini(&(self)->lb_line))


/* Helper macros for `struct linebuffer::lb_lock' */
#define _linebuffer_lock_reap(self)      (void)0
#define linebuffer_lock_reap(self)       (void)0
#define linebuffer_lock_mustreap(self)   0
#define linebuffer_lock_tryacquire(self) atomic_lock_tryacquire(&(self)->lb_lock)
#define linebuffer_lock_acquire(self)    atomic_lock_acquire(&(self)->lb_lock)
#define linebuffer_lock_acquire_nx(self) atomic_lock_acquire_nx(&(self)->lb_lock)
#define _linebuffer_lock_release(self)   atomic_lock_release(&(self)->lb_lock)
#define linebuffer_lock_release(self)    (atomic_lock_release(&(self)->lb_lock), linebuffer_lock_reap(self))
#define linebuffer_lock_acquired(self)   atomic_lock_acquired(&(self)->lb_lock)
#define linebuffer_lock_available(self)  atomic_lock_available(&(self)->lb_lock)
#define linebuffer_lock_waitfor(self)    atomic_lock_waitfor(&(self)->lb_lock)
#define linebuffer_lock_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->lb_lock)


/* Poll for writing to become possible. */
#define linebuffer_canwrite(self)                                      \
	(__hybrid_atomic_load((self)->lb_line.lc_size, __ATOMIC_ACQUIRE) < \
	 __hybrid_atomic_load((self)->lb_limt, __ATOMIC_ACQUIRE))
#define linebuffer_pollconnect_write_ex(self, cb) cb(&(self)->lb_nful)
#ifdef __OPTIMIZE_SIZE__
#define linebuffer_pollwrite_ex(self, cb)       \
	(linebuffer_pollconnect_write_ex(self, cb), \
	 linebuffer_canwrite(self))
#else /* __OPTIMIZE_SIZE__ */
#define linebuffer_pollwrite_ex(self, cb)        \
	(linebuffer_canwrite(self) ||                \
	 (linebuffer_pollconnect_write_ex(self, cb), \
	  linebuffer_canwrite(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef sched_signal_connect_for_poll
#define linebuffer_pollconnect_write(self) linebuffer_pollconnect_write_ex(self, sched_signal_connect_for_poll)
#define linebuffer_pollwrite(self)         linebuffer_pollwrite_ex(self, sched_signal_connect_for_poll)
#endif /* sched_signal_connect_for_poll */


/* Close the given line buffer, waking any remaining readers or writers. */
#ifdef __INTELLISENSE__
LIBBUFFER_DECL __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(LIBBUFFER_CC linebuffer_close)(struct linebuffer *__restrict __self);
#else /* __INTELLISENSE__ */
#define linebuffer_close(self)                                    \
	(__hybrid_atomic_store((self)->lb_limt, 0, __ATOMIC_RELEASE), \
	 sched_signal_broadcast(&(self)->lb_nful))
#endif /* !__INTELLISENSE__ */


/* Acquire a capture of the given linebuffer */
__LOCAL __ATTR_NONNULL((1, 2)) void
(LIBBUFFER_CC linebuffer_capture)(struct linebuffer *__restrict __self,
                                  struct linecapture *__restrict __capture) __THROWS(E_WOULDBLOCK);
#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW(LIBBUFFER_CC linebuffer_capture_nx)(struct linebuffer *__restrict __self,
                                              struct linecapture *__restrict __capture);
#endif /* __KERNEL__ && __KOS_VERSION__ && __KOS_VERSION__ >= 400 */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW(LIBBUFFER_CC linebuffer_trycapture)(struct linebuffer *__restrict __self,
                                              struct linecapture *__restrict __capture);

/* Release a previous capture of the given linebuffer */
__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW(LIBBUFFER_CC linebuffer_release)(struct linebuffer *__restrict __self,
                                           struct linecapture const *__restrict __capture);

/* Clear all written data from the given linebuffer */
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(LIBBUFFER_CC linebuffer_clear)(struct linebuffer *__restrict __self);


#ifdef __KERNEL__
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_kernel
#else /* __KERNEL__ */
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_not_kernel
#endif /* !__KERNEL__ */


/* Re-write  the  used area  of the  given capture  within the  given buffer.
 * For  this  purpose, try  to re-instate  `capture' as  the active  line, or
 * alternatively (when new data has already been written), write the contents
 * of the capture using `linebuffer_write()', before destroying the  capture.
 * @return: * : The number of re-written bytes.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
typedef __ATTR_NONNULL_T((1, 2)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PLINEBUFFER_REWRITE)(struct linebuffer *__restrict __self,
                                    /*inherit(always)*/ struct linecapture *__restrict __capture)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1, 2)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC linebuffer_rewrite)(struct linebuffer *__restrict __self,
                                  /*inherit(always)*/ struct linecapture *__restrict __capture)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Append up to `num_bytes' of data from `src' to the current  line.
 * If the line is too small to contain all data, wait until the line
 * is emptied before writing more data.
 * If the linebuffer is closed before  all data could be written,  return
 * the amount of written data, or 0 if the buffer was already closed when
 * the function was called.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
typedef __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PLINEBUFFER_WRITE)(struct linebuffer *__restrict __self,
                                  __USER __CHECKED void const *__src,
                                  __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC linebuffer_write)(struct linebuffer *__restrict __self,
                                __USER __CHECKED void const *__src,
                                __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Similar to `linebuffer_write()',  but only  block if the  line was  full
 * the first time  the function  was called.  If the  linebuffer is  closed
 * before at  least  1  byte of  data  could  be written,  0  is  returned.
 * Alternatively, if the given buffer is zero-length, 0 is always returned.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
typedef __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PLINEBUFFER_WRITESOME)(struct linebuffer *__restrict __self,
                                      __USER __CHECKED void const *__src,
                                      __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC linebuffer_writesome)(struct linebuffer *__restrict __self,
                                    __USER __CHECKED void const *__src,
                                    __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Similar to `linebuffer_write()', but  never block before writing  data.
 * If the given buffer was full at the time of this function being called,
 * or had been closed, then 0 is returned immediately.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
typedef __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PLINEBUFFER_WRITE_NONBLOCK)(struct linebuffer *__restrict __self,
                                           __USER __CHECKED void const *__src,
                                           __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK));
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC linebuffer_write_nonblock)(struct linebuffer *__restrict __self,
                                         __USER __CHECKED void const *__src,
                                         __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK));
#endif /* LIBBUFFER_WANT_PROTOTYPES */

#undef __KERNEL_SELECT


#ifndef __INTELLISENSE__

__LOCAL __ATTR_NONNULL((1, 2)) void
(LIBBUFFER_CC linebuffer_capture)(struct linebuffer *__restrict __self,
                                  struct linecapture *__restrict __capture)
		__THROWS(E_WOULDBLOCK) {
	__BOOL __was_full;
	linebuffer_lock_acquire(__self);
	*__capture = __self->lb_line;
	__hybrid_assert(__self->lb_line.lc_size <= __self->lb_line.lc_alloc);
	__was_full = __self->lb_line.lc_size >= __self->lb_line.lc_alloc;
	__self->lb_line.lc_base  = __NULLPTR;
	__self->lb_line.lc_alloc = 0;
	__self->lb_line.lc_size  = 0;
	linebuffer_lock_release(__self);
	if (__was_full)
		sched_signal_broadcast(&__self->lb_nful);
}

#if defined(__KERNEL__) && defined(__KOS_VERSION__) && __KOS_VERSION__ >= 400
__LOCAL __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW(LIBBUFFER_CC linebuffer_capture_nx)(struct linebuffer *__restrict __self,
                                              struct linecapture *__restrict __capture) {
	__BOOL __was_full;
	if (!linebuffer_lock_acquire_nx(__self))
		return 0;
	*__capture = __self->lb_line;
	__hybrid_assert(__self->lb_line.lc_size <= __self->lb_line.lc_alloc);
	__was_full = __self->lb_line.lc_size >= __self->lb_line.lc_alloc;
	__self->lb_line.lc_base  = __NULLPTR;
	__self->lb_line.lc_alloc = 0;
	__self->lb_line.lc_size  = 0;
	linebuffer_lock_release(__self);
	if (__was_full)
		sched_signal_broadcast(&__self->lb_nful);
	return 1;
}
#endif /* __KERNEL__ && __KOS_VERSION__ && __KOS_VERSION__ >= 400 */

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW(LIBBUFFER_CC linebuffer_trycapture)(struct linebuffer *__restrict __self,
                                              struct linecapture *__restrict __capture) {
	__BOOL __was_full;
	if (!linebuffer_lock_tryacquire(__self))
		return 0;
	*__capture = __self->lb_line;
	__hybrid_assert(__self->lb_line.lc_size <= __self->lb_line.lc_alloc);
	__was_full = __self->lb_line.lc_size >= __self->lb_line.lc_alloc;
	__self->lb_line.lc_base  = __NULLPTR;
	__self->lb_line.lc_alloc = 0;
	__self->lb_line.lc_size  = 0;
	linebuffer_lock_release(__self);
	if (__was_full)
		sched_signal_broadcast(&__self->lb_nful);
	return 1;
}

__LOCAL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW(LIBBUFFER_CC linebuffer_release)(struct linebuffer *__restrict __self,
                                           struct linecapture const *__restrict __capture) {
	if (linebuffer_lock_tryacquire(__self)) {
		__COMPILER_READ_BARRIER();
		if __unlikely(__self->lb_line.lc_alloc != 0) {
			linebuffer_lock_release(__self);
			goto __free_capture;
		}
		__hybrid_assert(__self->lb_line.lc_size == 0);
		__self->lb_line.lc_base  = __capture->lc_base;
		__self->lb_line.lc_alloc = __capture->lc_alloc;
		linebuffer_lock_release(__self);
	} else {
__free_capture:
		linecapture_fini(__capture);
	}
}

/* Clear all written data from the given linebuffer */
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(LIBBUFFER_CC linebuffer_clear)(struct linebuffer *__restrict __self) {
	/* Just override the line-size field with 0, thus clearing its effective size. */
	__hybrid_atomic_store(__self->lb_line.lc_size, 0, __ATOMIC_RELEASE);
}

#endif /* !__INTELLISENSE__ */

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBBUFFER_LINEBUFFER_H */
