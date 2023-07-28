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
#ifndef GUARD_LIBTERM_TERMIO_H
#define GUARD_LIBTERM_TERMIO_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stdbool.h>
#include <libterm/termio.h>

DECL_BEGIN

/* Initialize/Finalize the given terminal controller. */
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW_NCX(CC libterminal_init)(struct terminal *__restrict self,
                                 pterminal_oprinter_t oprinter,
                                 pterminal_raise_t raisefunc,
                                 pterminal_check_sigttou_t chk_sigttou);

/* Print output (display) or input (keyboard) to a given terminal
 * @param: mode:   I/O mode (set of `IO_*'; the terminal sub-system recognizes `IO_NONBLOCK')
 * @return: >= 0 : The sum of return values from calls to the associated printer
 *                 - The usual rules apply where negative return values are propagated immediately.
 *                 - Data printed when an I/O buffer is flushed is not added to this sum, however
 *                   negative values  resulting  from  this case  are  propagated  none-the-less.
 *                 - In cases where  data is written  to multiple printers  (e.g. terminal_iwrite() w/  ECHO),
 *                   only the return  value of  the intended  printer (in this  case `t_iprint')  is added  to
 *                   the  eventually  returned sum.  - Additionally,  in this  case, the  lower of  the return
 *                   value of the original call to `t_iprint' and num_bytes passed to it is used as the number
 *                   of bytes that  would be echoed  on-screen. (meaning  that no characters  will get  echoed
 *                   that can't be added to the input queue)
 * @return: < 0:   A format-printer returned a negative value
 * @return: -1:   [USERSPACE] Printing to one of the linebuffers failed (s.a. `linebuffer_write()'; `errno') */
INTDEF NONNULL((1)) ssize_t CC
libterminal_owrite(struct terminal *__restrict self,
                   NCX void const *__restrict src,
                   size_t num_bytes, iomode_t mode)
	KERNEL_SELECT(THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
	              THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...));
INTDEF NONNULL((1)) ssize_t CC
libterminal_iwrite(struct terminal *__restrict self,
                   NCX void const *src,
                   size_t num_bytes, iomode_t mode)
	KERNEL_SELECT(THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
	              THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...));

/* Read from the terminal input buffer (usually the keyboard), and into the given `dst'
 * @param: mode: Set of `0|IO_NONBLOCK'
 * @return: * :  The number of bytes read
 * @return: <0:  [USERSPACE] An error occurred (s.a. `errno') */
INTDEF NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libterminal_iread(struct terminal *__restrict self,
                  NCX void *dst,
                  size_t num_bytes, iomode_t mode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT);

/* Set terminal I/O settings
 * @return: < 0: [USERSPACE]   A printer callback returned negative, or an error occurred (s.a. `errno')
 * @return: < 0: [KERNELSPACE] A printer callback returned negative */
INTDEF NONNULL((1, 2)) ssize_t CC
libterminal_setios(struct terminal *__restrict self,
                   struct termios const *__restrict tio,
                   struct termios *old_tio)
	KERNEL_SELECT(THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
	              THROWS(E_WOULDBLOCK, E_INTERRUPT, ...));

/* Flush the input buffer canon by writing all of its contents to `t_ibuf',
 * thus allowing the data to be read by a future call to `terminal_iread()'
 * @return: * : The number of flushed characters.
 * @return: <0: [USERSPACE] An error occurred (s.a. `errno') */
INTDEF NONNULL((1)) KERNEL_SELECT(size_t, ssize_t) CC
libterminal_flush_icanon(struct terminal *__restrict self, iomode_t mode)
		KERNEL_SELECT(THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		              THROWS(E_WOULDBLOCK, E_INTERRUPT, ...));

DECL_END

#endif /* !GUARD_LIBTERM_TERMIO_H */
