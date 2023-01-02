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
#ifndef GUARD_LIBBUFFER_LINEBUFFER_H
#define GUARD_LIBBUFFER_LINEBUFFER_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libbuffer/linebuffer.h>

DECL_BEGIN

#ifdef __KERNEL__
typedef size_t linebuffer_retval_t;
#else /* __KERNEL__ */
typedef ssize_t linebuffer_retval_t;
#endif /* !__KERNEL__ */



/* Re-write  the  used area  of the  given capture  within the  given buffer.
 * For  this  purpose, try  to re-instate  `capture' as  the active  line, or
 * alternatively (when new data has already been written), write the contents
 * of the capture using `linebuffer_write()', before destroying the  capture.
 * @return: * : The number of re-written bytes.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTDEF NONNULL((1, 2)) linebuffer_retval_t CC
liblinebuffer_rewrite(struct linebuffer *__restrict self,
                      /*inherit(always)*/ struct linecapture *__restrict capture)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));

/* Append up to `num_bytes' of data from `src' to the current  line.
 * If the line is too small to contain all data, wait until the line
 * is emptied before writing more data.
 * If the linebuffer is closed before  all data could be written,  return
 * the amount of written data, or 0 if the buffer was already closed when
 * the function was called.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTDEF NONNULL((1)) linebuffer_retval_t CC
liblinebuffer_write(struct linebuffer *__restrict self,
                    USER CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));

/* Similar to `linebuffer_write()',  but only  block if the  line was  full
 * the first time  the function  was called.  If the  linebuffer is  closed
 * before at  least  1  byte of  data  could  be written,  0  is  returned.
 * Alternatively, if the given buffer is zero-length, 0 is always returned.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTDEF NONNULL((1)) linebuffer_retval_t CC
liblinebuffer_writesome(struct linebuffer *__restrict self,
                        USER CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK, E_INTERRUPT));

/* Similar to `linebuffer_write()', but  never block before writing  data.
 * If the given buffer was full at the time of this function being called,
 * or had been closed, then 0 is returned immediately.
 * @return: -1: [USERSPACE] An error occurred (s.a. `errno'). */
INTDEF NONNULL((1)) linebuffer_retval_t CC
liblinebuffer_write_nonblock(struct linebuffer *__restrict self,
                             USER CHECKED void const *src, size_t num_bytes)
		KERNEL_SELECT(THROWS(E_SEGFAULT, E_WOULDBLOCK, E_BADALLOC),
		              THROWS(E_SEGFAULT, E_WOULDBLOCK));


DECL_END

#endif /* !GUARD_LIBBUFFER_LINEBUFFER_H */
