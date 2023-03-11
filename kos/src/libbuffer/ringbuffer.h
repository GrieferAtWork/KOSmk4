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
#ifndef GUARD_LIBBUFFER_RINGBUFFER_H
#define GUARD_LIBBUFFER_RINGBUFFER_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libbuffer/ringbuffer.h>

DECL_BEGIN

#ifndef BLOCKING
#define BLOCKING __BLOCKING
#endif /* !BLOCKING */

#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */



/* Read data from the given ring buffer.
 * When `ringbuffer_read()' is called, and no data is available, the function
 * will block  until data  becomes available,  or the  ringbuffer is  closed.
 * NOTE:  `ringbuffer_read_nonblock()' can still throw `E_WOULDBLOCK' because
 *        it may call `task_yield()'  when trying to acquire  `self->rb_lock'
 * @return: * : The number of bytes read. */
INTDEF BLOCKING NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_read(struct ringbuffer *__restrict self,
                   __USER __CHECKED void *dst, size_t num_bytes)
		THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...);
INTDEF NONNULL((1)) size_t CC
libringbuffer_read_nonblock(struct ringbuffer *__restrict self,
                            __USER __CHECKED void *dst, size_t num_bytes)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);


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
INTDEF BLOCKING NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_write(struct ringbuffer *__restrict self,
                    __USER __CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...));
INTDEF BLOCKING NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_writesome(struct ringbuffer *__restrict self,
                        __USER __CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, ...));
INTDEF NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libringbuffer_write_nonblock(struct ringbuffer *__restrict self,
                             __USER __CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK));

/* Same as `ringbuffer_write_nonblock()', but don't increase the buffer's size. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_write_nonblock_noalloc(struct ringbuffer *__restrict self,
                                     __USER __CHECKED void const *src, size_t num_bytes)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

/* Try to unread up to `num_bytes' of data that had yet to be re-written
 * @param: p_rdtot: When non-NULL, store the new number of total read bytes since the last re-size in there
 * @return: * : The actual number of unread bytes. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_unread(struct ringbuffer *__restrict self,
                     size_t num_bytes,
                     size_t *p_rdtot DFL(NULL))
		THROWS(E_WOULDBLOCK);

/* Skip up to `num_bytes' of unread data, returning the actual number of skipped bytes.
 * @param: p_rdtot: When non-NULL, store the new number of total read bytes since the last re-size in there
 * @return: * : The actual number of skipped bytes. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_skipread(struct ringbuffer *__restrict self,
                       size_t num_bytes,
                       size_t *p_rdtot DFL(NULL))
		THROWS(E_WOULDBLOCK);

/* A combination of `ringbuffer_unread()' and `ringbuffer_skipread()' that can be used
 * to some-what implement support for SEEK_CUR for ring buffers, where negative values
 * for `offset'  will call  `ringbuffer_unread()', whilst  positive values  will  call
 * `ringbuffer_skipread()'
 * The return value is always the new total number of read bytes since the last re-size. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_rseek(struct ringbuffer *__restrict self,
                    ssize_t offset)
		THROWS(E_WOULDBLOCK);

/* Try to unwrite up to `num_bytes' of data that had yet to be read
 * @param: p_wrtot: When non-NULL, store the new number of total written bytes since the last re-size in there
 * @return: * : The actual number of unwritten bytes. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_unwrite(struct ringbuffer *__restrict self,
                      size_t num_bytes,
                      size_t *p_wrtot DFL(NULL))
		THROWS(E_WOULDBLOCK);

/* By using `ringbuffer_unwrite()', implement support for SEEK_CUR when `offset' is negative
 * Alternatively, when `offset' is positive, don't do anything.
 * The return value is always the new total number of written bytes since the last re-size. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_wseek(struct ringbuffer *__restrict self, ssize_t offset)
		THROWS(E_WOULDBLOCK);

/* Set the total amount of written, but yet-to-be read bytes.
 * If `num_bytes' is larger than the previous total number of written bytes, don't truncate the buffer.
 * @return: * : The actual number of now-written bytes. */
INTDEF NONNULL((1)) size_t CC
libringbuffer_setwritten(struct ringbuffer *__restrict self, size_t num_bytes)
		THROWS(E_WOULDBLOCK);

DECL_END

#endif /* !GUARD_LIBBUFFER_RINGBUFFER_H */
