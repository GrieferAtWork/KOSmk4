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
#ifndef _LIBBUFFER_RINGBUFFER_H
#define _LIBBUFFER_RINGBUFFER_H 1

#include "api.h"

#include <hybrid/sched/atomic-rwlock.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/hybrid/sched-signal.h>

#ifndef __INTELLISENSE__
#include <hybrid/__atomic.h>
#endif /* !__INTELLISENSE__ */

#ifdef __KERNEL__
#include <kernel/heap.h> /* heap_free */
#else /* __KERNEL__ */
#include <libc/malloc.h> /* __libc_free */
#endif /* !__KERNEL__ */


/* Implementation of the  general-purpose ring-buffer used  to
 * implement kernel-space pipes, as well as input data queues. */

#ifdef __CC__
__DECL_BEGIN

struct ringbuffer {
	struct atomic_rwlock rb_lock;   /* Lock for the buffer. */
	__byte_t            *rb_data;   /* [0..rb_size][owned][lock(rb_lock)] The ring's data buffer. */
	__size_t             rb_size;   /* [lock(rb_lock)] (heap) size of the buffer */
	__size_t             rb_rptr;   /* [lock(rb_lock)][< rb_size] Index into the buffer where the next byte to-be read is located.
	                                 * When `rb_avail' is 0,  this index points to  the location of the  next byte to-be  written. */
	__size_t             rb_avail;  /* [lock(rb_lock)][<= rb_size] Amount of available data (written/used bytes) */
	__size_t             rb_rdtot;  /* [lock(rb_lock)] Total number of bytes read since the last re-size. */
	__WEAK __size_t      rb_limit;  /* Max size to which the buffer may grow when writing (set to 0 to indicate that
	                                 * the buffer was closed, in which case both reading or writing will immediately
	                                 * indicate that no data was transferred) */
	sched_signal_t       rb_nempty; /* Signal broadcast when the buffer becomes non-empty, or gets closed */
	sched_signal_t       rb_nfull;  /* Signal broadcast when the buffer becomes non-full, or gets closed */
};

/* Helper macros for `struct ringbuffer::rb_lock' */
#define ringbuffer_lock_mustreap(self)     0
#define ringbuffer_lock_reap(self)         (void)0
#define _ringbuffer_lock_reap(self)        (void)0
#define ringbuffer_lock_write(self)        atomic_rwlock_write(&(self)->rb_lock)
#define ringbuffer_lock_write_nx(self)     atomic_rwlock_write_nx(&(self)->rb_lock)
#define ringbuffer_lock_trywrite(self)     atomic_rwlock_trywrite(&(self)->rb_lock)
#define ringbuffer_lock_endwrite(self)     (atomic_rwlock_endwrite(&(self)->rb_lock), ringbuffer_lock_reap(self))
#define _ringbuffer_lock_endwrite(self)    atomic_rwlock_endwrite(&(self)->rb_lock)
#define ringbuffer_lock_read(self)         atomic_rwlock_read(&(self)->rb_lock)
#define ringbuffer_lock_read_nx(self)      atomic_rwlock_read_nx(&(self)->rb_lock)
#define ringbuffer_lock_tryread(self)      atomic_rwlock_tryread(&(self)->rb_lock)
#define _ringbuffer_lock_endread(self)     atomic_rwlock_endread(&(self)->rb_lock)
#define ringbuffer_lock_endread(self)      (void)(atomic_rwlock_endread_ex(&(self)->rb_lock) && (ringbuffer_lock_reap(self), 0))
#define _ringbuffer_lock_end(self)         atomic_rwlock_end(&(self)->rb_lock)
#define ringbuffer_lock_end(self)          (void)(atomic_rwlock_end_ex(&(self)->rb_lock) && (ringbuffer_lock_reap(self), 0))
#define ringbuffer_lock_upgrade(self)      atomic_rwlock_upgrade(&(self)->rb_lock)
#define ringbuffer_lock_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->rb_lock)
#define ringbuffer_lock_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->rb_lock)
#define ringbuffer_lock_downgrade(self)    atomic_rwlock_downgrade(&(self)->rb_lock)
#define ringbuffer_lock_reading(self)      atomic_rwlock_reading(&(self)->rb_lock)
#define ringbuffer_lock_writing(self)      atomic_rwlock_writing(&(self)->rb_lock)
#define ringbuffer_lock_canread(self)      atomic_rwlock_canread(&(self)->rb_lock)
#define ringbuffer_lock_canwrite(self)     atomic_rwlock_canwrite(&(self)->rb_lock)
#define ringbuffer_lock_waitread(self)     atomic_rwlock_waitread(&(self)->rb_lock)
#define ringbuffer_lock_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->rb_lock)
#define ringbuffer_lock_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->rb_lock)
#define ringbuffer_lock_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->rb_lock)

/* Static initialization */
#define RINGBUFFER_DEFAULT_LIMIT         4096

/* Trim the buffer if more than `RINGBUFFER_FREE_THRESHOLD(LIMIT)' bytes are unused */
#define RINGBUFFER_FREE_THRESHOLD(limit) \
	(((limit) >> 4) >= 32 ? ((limit) >> 4) : 32)

#define RINGBUFFER_INIT_EX(limit) \
	{ ATOMIC_RWLOCK_INIT, __NULLPTR, 0, 0, 0, 0, limit, SCHED_SIGNAL_INIT, SCHED_SIGNAL_INIT }
#define RINGBUFFER_INIT \
	RINGBUFFER_INIT_EX(RINGBUFFER_DEFAULT_LIMIT)

/* Initialization / finalization */
#define ringbuffer_init_ex(self, limit)                                           \
	(atomic_rwlock_init(&(self)->rb_lock), (self)->rb_data = __NULLPTR,           \
	 (self)->rb_size = (self)->rb_rptr = (self)->rb_avail = (self)->rb_rdtot = 0, \
	 (self)->rb_limit = (limit), sched_signal_init(&(self)->rb_nempty),           \
	 sched_signal_init(&(self)->rb_nfull))
#define ringbuffer_cinit_ex(self, limit)            \
	(atomic_rwlock_cinit(&(self)->rb_lock),         \
	 __hybrid_assert((self)->rb_data == __NULLPTR), \
	 __hybrid_assert((self)->rb_size == 0),         \
	 __hybrid_assert((self)->rb_rptr == 0),         \
	 __hybrid_assert((self)->rb_avail == 0),        \
	 __hybrid_assert((self)->rb_rdtot == 0),        \
	 (self)->rb_limit = (limit),                    \
	 sched_signal_cinit(&(self)->rb_nempty),        \
	 sched_signal_cinit(&(self)->rb_nfull))
#define ringbuffer_init(self)  ringbuffer_init_ex(self, RINGBUFFER_DEFAULT_LIMIT)
#define ringbuffer_cinit(self) ringbuffer_cinit_ex(self, RINGBUFFER_DEFAULT_LIMIT)

#ifdef __KERNEL__
#define ringbuffer_fini(self)                                                        \
	(sched_signal_broadcast_for_fini(&(self)->rb_nempty),                            \
	 sched_signal_broadcast_for_fini(&(self)->rb_nfull),                             \
	 (self)->rb_size                                                                 \
	 ? heap_free(&kernel_default_heap, (self)->rb_data, (self)->rb_size, GFP_NORMAL) \
	 : (void)0)
#else /* __KERNEL__ */
#define ringbuffer_fini(self)                             \
	(sched_signal_broadcast_for_fini(&(self)->rb_nempty), \
	 sched_signal_broadcast_for_fini(&(self)->rb_nfull),  \
	 __libc_free((self)->rb_data))
#endif /* !__KERNEL__ */


/* Polling API */
#define ringbuffer_canread(self)                                       \
	(__hybrid_atomic_load(&(self)->rb_avail, __ATOMIC_ACQUIRE) != 0 || \
	 __hybrid_atomic_load(&(self)->rb_limit, __ATOMIC_ACQUIRE) == 0)
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(LIBBUFFER_CC ringbuffer_canwrite)(struct ringbuffer const *__restrict __self) {
	__size_t __limit = __hybrid_atomic_load(&__self->rb_limit, __ATOMIC_ACQUIRE);
	return __limit == 0 || __hybrid_atomic_load(&__self->rb_avail, __ATOMIC_ACQUIRE) < __limit;
}
#define ringbuffer_pollconnect_read_ex(self, cb)  cb(&(self)->rb_nempty)
#define ringbuffer_pollconnect_write_ex(self, cb) cb(&(self)->rb_nfull)
#define ringbuffer_pollread_unlikely_ex(self, cb) \
	(ringbuffer_pollconnect_read_ex(self, cb),    \
	 ringbuffer_canread(self))
#define ringbuffer_pollwrite_unlikely_ex(self, cb) \
	(ringbuffer_pollconnect_write_ex(self, cb),    \
	 ringbuffer_canwrite(self))
#ifdef __OPTIMIZE_SIZE__
#define ringbuffer_pollread_ex(self, cb) \
	ringbuffer_pollread_unlikely_ex(self, cb)
#define ringbuffer_pollwrite_ex(self, cb) \
	ringbuffer_pollwrite_unlikely_ex(self, cb)
#else /* __OPTIMIZE_SIZE__ */
#define ringbuffer_pollread_ex(self, cb)        \
	(ringbuffer_canread(self) ||                \
	 (ringbuffer_pollconnect_read_ex(self, cb), \
	  ringbuffer_canread(self)))
#define ringbuffer_pollwrite_ex(self, cb)        \
	(ringbuffer_canwrite(self) ||                \
	 (ringbuffer_pollconnect_write_ex(self, cb), \
	  ringbuffer_canwrite(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef sched_signal_connect_for_poll
#define ringbuffer_pollconnect_read(self)   ringbuffer_pollconnect_read_ex(self, sched_signal_connect_for_poll)
#define ringbuffer_pollconnect_write(self)  ringbuffer_pollconnect_write_ex(self, sched_signal_connect_for_poll)
#define ringbuffer_pollread(self)           ringbuffer_pollread_ex(self, sched_signal_connect_for_poll)
#define ringbuffer_pollread_unlikely(self)  ringbuffer_pollread_unlikely_ex(self, sched_signal_connect_for_poll)
#define ringbuffer_pollwrite(self)          ringbuffer_pollwrite_ex(self, sched_signal_connect_for_poll)
#define ringbuffer_pollwrite_unlikely(self) ringbuffer_pollwrite_unlikely_ex(self, sched_signal_connect_for_poll)
#endif /* sched_signal_connect_for_poll */




/* Close the given ring buffer, waking any remaining readers or writers. */
#ifdef __INTELLISENSE__
__NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(ringbuffer_close)(struct ringbuffer *__restrict self);
__NOBLOCK __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(ringbuffer_closed)(struct ringbuffer *__restrict self);
#else /* __INTELLISENSE__ */
#define ringbuffer_close(self)                                      \
	(__hybrid_atomic_store(&(self)->rb_limit, 0, __ATOMIC_RELEASE), \
	 sched_signal_broadcast(&(self)->rb_nempty),                    \
	 sched_signal_broadcast(&(self)->rb_nfull))
#define ringbuffer_closed(self) \
	(__hybrid_atomic_load(&(self)->rb_limit, __ATOMIC_ACQUIRE) == 0)
#endif /* !__INTELLISENSE__ */

#ifdef __KERNEL__
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_kernel
#else /* __KERNEL__ */
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_not_kernel
#endif /* !__KERNEL__ */


/* Read data from the given ring buffer.
 * When `ringbuffer_read()' is called, and no data is available, the function
 * will block  until data  becomes available,  or the  ringbuffer is  closed.
 * NOTE:  `ringbuffer_read_nonblock()' can still throw `E_WOULDBLOCK' because
 *        it may call `task_yield()'  when trying to acquire  `self->rb_lock'
 * @return: * : The number of bytes read. */
typedef __BLOCKING __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PRINGBUFFER_READ)(struct ringbuffer *__restrict __self,
                                 __NCX void *__dst,
                                 __size_t __num_bytes)
		__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...);
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_READ_NONBLOCK)(struct ringbuffer *__restrict __self,
                                          __NCX void *__dst,
                                          __size_t __num_bytes)
		__THROWS(E_SEGFAULT, E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __BLOCKING __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t) LIBBUFFER_CC
ringbuffer_read(struct ringbuffer *__restrict __self,
                __NCX void *__dst, __size_t __num_bytes)
		__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...);
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_read_nonblock(struct ringbuffer *__restrict __self,
                         __NCX void *__dst, __size_t __num_bytes)
		__THROWS(E_SEGFAULT, E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */


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
typedef __BLOCKING __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PRINGBUFFER_WRITE)(struct ringbuffer *__restrict __self,
                                  __NCX void const *__src,
                                  __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...));
typedef __BLOCKING __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PRINGBUFFER_WRITESOME)(struct ringbuffer *__restrict __self,
                                      __NCX void const *__src,
                                      __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...));
typedef __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBBUFFER_CC *PRINGBUFFER_WRITE_NONBLOCK)(struct ringbuffer *__restrict __self,
                                           __NCX void const *__src,
                                           __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK));
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __BLOCKING __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t) LIBBUFFER_CC
ringbuffer_write(struct ringbuffer *__restrict __self,
                 __NCX void const *__src, __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...));
LIBBUFFER_DECL __BLOCKING __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t) LIBBUFFER_CC
ringbuffer_writesome(struct ringbuffer *__restrict __self,
                     __NCX void const *__src, __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...));
LIBBUFFER_DECL __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t) LIBBUFFER_CC
ringbuffer_write_nonblock(struct ringbuffer *__restrict __self,
                          __NCX void const *__src, __size_t __num_bytes)
		__KERNEL_SELECT(__THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		                __THROWS(E_SEGFAULT, E_WOULDBLOCK));
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Same as `ringbuffer_write_nonblock()', but don't increase the buffer's size. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_WRITE_NONBLOCK_NOALLOC)(struct ringbuffer *__restrict __self,
                                                   __NCX void const *__src,
                                                   __size_t __num_bytes)
		__THROWS(E_SEGFAULT, E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_write_nonblock_noalloc(struct ringbuffer *__restrict __self,
                                  __NCX void const *__src, __size_t __num_bytes)
		__THROWS(E_SEGFAULT, E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* XXX: Dedicated functions for these? */
#ifdef LIBBUFFER_WANT_PROTOTYPES
__FORCELOCAL __BLOCKING __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_putc(struct ringbuffer *__restrict __self, __byte_t __ch)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...)) {
	return ringbuffer_write(__self, &__ch, 1);
}
__FORCELOCAL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_putc_nonblock(struct ringbuffer *__restrict __self, __byte_t __ch)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_BADALLOC),
		                __THROWS(E_WOULDBLOCK)) {
	return ringbuffer_write_nonblock(__self, &__ch, 1);
}
__FORCELOCAL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
__ringbuffer_putc_nonblock_noalloc(struct ringbuffer *__restrict __self, __byte_t __ch)
		__THROWS(E_WOULDBLOCK) {
	return ringbuffer_write_nonblock_noalloc(__self, &__ch, 1);
}
#endif /* LIBBUFFER_WANT_PROTOTYPES */

#undef __KERNEL_SELECT

/* Try to unread up to `num_bytes' of data that had yet to be re-written
 * @param: p_rdtot: When non-NULL, store the new number of total read bytes since the last re-size in there
 * @return: * : The actual number of unread bytes. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_UNREAD)(struct ringbuffer *__restrict __self,
                                   __size_t __num_bytes,
                                   __size_t *__p_rdtot /*__DFL(__NULLPTR)*/)
		__THROWS(E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_unread(struct ringbuffer *__restrict __self,
                  __size_t __num_bytes,
                  __size_t *__p_rdtot __DFL(__NULLPTR))
		__THROWS(E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Skip up to `num_bytes' of unread data, returning the actual number of skipped bytes.
 * @param: p_rdtot: When non-NULL, store the new number of total read bytes since the last re-size in there
 * @return: * : The actual number of skipped bytes. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_SKIPREAD)(struct ringbuffer *__restrict __self,
                                     __size_t __num_bytes,
                                     __size_t *__p_rdtot /*__DFL(__NULLPTR)*/)
		__THROWS(E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_skipread(struct ringbuffer *__restrict __self,
                    __size_t __num_bytes,
                    __size_t *__p_rdtot __DFL(__NULLPTR))
		__THROWS(E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* A combination of `ringbuffer_unread()' and `ringbuffer_skipread()' that can be used
 * to some-what implement support for SEEK_CUR for ring buffers, where negative values
 * for `offset'  will call  `ringbuffer_unread()', whilst  positive values  will  call
 * `ringbuffer_skipread()'
 * The return value is always the new total number of read bytes since the last re-size. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_RSEEK)(struct ringbuffer *__restrict __self,
                                  __ssize_t __offset)
		__THROWS(E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_rseek(struct ringbuffer *__restrict __self, __ssize_t __offset)
		__THROWS(E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Try to unwrite up to `num_bytes' of data that had yet to be read
 * @param: p_wrtot: When non-NULL, store the new number of total written bytes since the last re-size in there
 * @return: * : The actual number of unwritten bytes. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_UNWRITE)(struct ringbuffer *__restrict __self,
                                    __size_t __num_bytes,
                                    __size_t *__p_wrtot /*__DFL(__NULLPTR)*/)
		__THROWS(E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_unwrite(struct ringbuffer *__restrict __self,
                   __size_t __num_bytes,
                   __size_t *__p_wrtot __DFL(__NULLPTR))
		__THROWS(E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* By using `ringbuffer_unwrite()', implement support for SEEK_CUR when `offset' is negative
 * Alternatively, when `offset' is positive, don't do anything.
 * The return value is always the new total number of written bytes since the last re-size. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_WSEEK)(struct ringbuffer *__restrict __self,
                                  __ssize_t __offset)
		__THROWS(E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_wseek(struct ringbuffer *__restrict __self, __ssize_t __offset)
		__THROWS(E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

/* Set the total amount of written, but yet-to-be read bytes.
 * If `num_bytes' is larger than the previous total number of written bytes, don't truncate the buffer.
 * @return: * : The actual number of now-written bytes. */
typedef __ATTR_NONNULL_T((1)) __size_t
(LIBBUFFER_CC *PRINGBUFFER_SETWRITTEN)(struct ringbuffer *__restrict __self,
                                       __size_t __num_bytes)
		__THROWS(E_WOULDBLOCK);
#ifdef LIBBUFFER_WANT_PROTOTYPES
LIBBUFFER_DECL __ATTR_NONNULL((1)) __size_t LIBBUFFER_CC
ringbuffer_setwritten(struct ringbuffer *__restrict __self, __size_t __num_bytes)
		__THROWS(E_WOULDBLOCK);
#endif /* LIBBUFFER_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBBUFFER_RINGBUFFER_H */
