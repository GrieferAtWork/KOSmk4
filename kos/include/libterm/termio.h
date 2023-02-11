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
#ifndef _LIBTERM_TERMIO_H
#define _LIBTERM_TERMIO_H 1

#include "api.h"
/**/

#include <hybrid/__atomic.h>
#include <hybrid/sched/atomic-rwlock.h>

#include <asm/os/termios.h> /* termios constants */
#include <bits/crt/format-printer.h>
#include <bits/os/termios.h> /* struct termios */
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/io.h>

#include <libbuffer/linebuffer.h>
#include <libbuffer/ringbuffer.h>

__DECL_BEGIN

#ifdef __CC__

#ifdef __KERNEL__
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_kernel
#else /* __KERNEL__ */
#define __KERNEL_SELECT(if_kernel, if_not_kernel) if_not_kernel
#endif /* !__KERNEL__ */


struct terminal;

/* Print the given `src' data
 * @return: >= 0: The number of printed bytes (equal to `num_bytes', unless `IO_NONBLOCK', or EOF was reached)
 * @return: < 0:  An error status that should be propagated immediately. */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t
(LIBTERM_CC *pterminal_oprinter_t)(struct terminal *__restrict term,
                                   void const *__restrict src,
                                   __size_t num_bytes, iomode_t mode);

/* Raise a given signal `signo' (one of `SIG*')
 * within the foreground process  group associated with the  terminal.
 * A negative return value of this function is propagated immediately.
 * s.a. `_task_raisesignoprocessgroup()'
 * @return: < 0:  An error status that should be propagated immediately. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBTERM_CC *pterminal_raise_t)(struct terminal *__restrict self,
                                __signo_t signo);

/* Check if the  calling process's  group leader  is apart  of the  foreground
 * process  group  associated with  the  given terminal  `self'.  - If  it is,
 * return 0. Otherwise,  the POSIX  behavior is  to raise  a signal  `SIGTTOU'
 * within  every  process   in  the  caller's   process  group,  however   the
 * implementation  of  this   function  may  also   choose  to  do   something
 * completely different. (or just be a no-op; >I'm just a sign, not a cop...<)
 * @return: < 0:  An error status that should be propagated immediately. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBTERM_CC *pterminal_check_sigttou_t)(struct terminal *__restrict self);

struct terminal {
	/* Terminal controller, implementing input/output transformations and control characters. */
	pterminal_check_sigttou_t t_chk_sigttou; /* [0..1][const] When non-NULL, called once every time `terminal_owrite()'
	                                          *               is  called   while   `t_ios.c_lflag & TOSTOP'   is   set.
	                                          * The intended use of this callback is to check if the caller is apart
	                                          * of  the foreground process  group, and suspend  them if they aren't. */
	pterminal_raise_t         t_raise;       /* [0..1][const] Raise a signal in the foreground process. */
	pterminal_oprinter_t      t_oprint;      /* [1..1][const] Print output to the screen. */
	struct ringbuffer         t_ibuf;        /* Buffer for keyboard input.
	                                          * NOTE: When `__IEOFING' is set, `t_ibuf.rb_nempty' must be broadcast! */
	struct linebuffer         t_canon;       /* Canonical buffer for line-wise input (used for input when `t_ios.c_lflag & ICANON' is set)
	                                          * NOTE:   When    `ICANON'    is    cleared,   `t_canon.lb_nful'    must    be    broadcast! */
	struct linebuffer         t_opend;       /* Buffer for pending output text (used when `t_ios.c_iflag & IXOFF' is set)
	                                          * NOTE: When  `IXOFF'  is  cleared, `t_opend.lb_nful'  must  be  broadcast!
	                                          * NOTE: When `(c_lflag & (ECHO | EXTPROC)) != ECHO', `t_opend.lb_nful' must be broadcast! */
	struct linebuffer         t_ipend;       /* Buffer for pending input text (used when `t_ios.c_iflag & __IIOFF' is set)
	                                          * NOTE: When  `__IIOFF' is  cleared,  `t_ipend.lb_nful' must  be  broadcast! */
	struct termios            t_ios;         /* Terminal I/O configuration. */
	sched_signal_t            t_ioschange;   /* Signal broadcast when: `IXOFF' is set, `(c_lflag & (ECHO | EXTPROC)) != ECHO' */
};

#define terminal_fini(self)             \
	(ringbuffer_fini(&(self)->t_ibuf),  \
	 linebuffer_fini(&(self)->t_canon), \
	 linebuffer_fini(&(self)->t_opend), \
	 linebuffer_fini(&(self)->t_ipend), \
	 sched_signal_broadcast_for_fini(&(self)->t_ioschange))

/* Initialize/Finalize the given terminal controller. */
typedef __NOBLOCK __ATTR_NONNULL_T((1, 2)) void
__NOTHROW_NCX_T(LIBTERM_CC *PTERMINAL_INIT)(struct terminal *__restrict self,
                                            pterminal_oprinter_t oprinter,
                                            pterminal_raise_t raisefunc,
                                            pterminal_check_sigttou_t chk_sigttou);
#ifdef LIBTERM_WANT_PROTOTYPES
LIBTERM_DECL __NOBLOCK __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(LIBTERM_CC terminal_init)(struct terminal *__restrict self,
                                        pterminal_oprinter_t oprinter,
                                        pterminal_raise_t raisefunc,
                                        pterminal_check_sigttou_t chk_sigttou);
#endif /* LIBTERM_WANT_PROTOTYPES */

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
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBTERM_CC *PTERMINAL_OWRITE)(struct terminal *__restrict self,
                               __USER __CHECKED void const *src,
                               __size_t num_bytes, iomode_t mode)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...));
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBTERM_CC *PTERMINAL_IWRITE)(struct terminal *__restrict self,
                               __USER __CHECKED void const *src,
                               __size_t num_bytes, iomode_t mode)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...));
#ifdef LIBTERM_WANT_PROTOTYPES
LIBTERM_DECL __ATTR_NONNULL((1)) __ssize_t LIBTERM_CC
terminal_owrite(struct terminal *__restrict self,
                __USER __CHECKED void const *src,
                __size_t num_bytes, iomode_t mode)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...));
LIBTERM_DECL __ATTR_NONNULL((1)) __ssize_t LIBTERM_CC
terminal_iwrite(struct terminal *__restrict self,
                __USER __CHECKED void const *src,
                __size_t num_bytes, iomode_t mode)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT, ...));
#endif /* LIBTERM_WANT_PROTOTYPES */


/* Read from the terminal input buffer (usually the keyboard), and into the given `dst'
 * @param: mode: Set of `0|IO_NONBLOCK'
 * @return: * :  The number of bytes read
 * @return: <0:  [USERSPACE] An error occurred (s.a. `errno') */
typedef __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBTERM_CC *PTERMINAL_IREAD)(struct terminal *__restrict self,
                              __USER __CHECKED void *dst,
                              __size_t num_bytes, iomode_t mode)
		__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT);
#ifdef LIBTERM_WANT_PROTOTYPES
LIBTERM_DECL __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t) LIBTERM_CC
terminal_iread(struct terminal *__restrict self,
               __USER __CHECKED void *dst,
               __size_t num_bytes, iomode_t mode)
		__THROWS(E_WOULDBLOCK, E_SEGFAULT, E_INTERRUPT);
#endif /* LIBTERM_WANT_PROTOTYPES */

/* Set terminal I/O settings
 * @param: old_tio: When non-NULL, store the old terminal I/O settings here.
 * @return: < 0: [USERSPACE]   A printer callback returned negative, or an error occurred (s.a. `errno')
 * @return: < 0: [KERNELSPACE] A printer callback returned negative */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t
(LIBTERM_CC *PTERMINAL_SETIOS)(struct terminal *__restrict self,
                               struct termios const *__restrict tio,
                               struct termios *old_tio)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...));
#ifdef LIBTERM_WANT_PROTOTYPES
LIBTERM_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBTERM_CC
terminal_setios(struct terminal *__restrict self,
                struct termios const *__restrict tio,
                struct termios *old_tio)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...));
#endif /* LIBTERM_WANT_PROTOTYPES */

/* Flush the input buffer canon by writing all of its contents to `t_ibuf',
 * thus allowing the data to be read by a future call to `terminal_iread()'
 * @return: * : The number of flushed characters.
 * @return: <0: [USERSPACE] An error occurred (s.a. `errno') */
typedef __ATTR_NONNULL_T((1)) __KERNEL_SELECT(__size_t, __ssize_t)
(LIBTERM_CC *PTERMINAL_FLUSH_ICANON)(struct terminal *__restrict self, iomode_t mode)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...));
#ifdef LIBTERM_WANT_PROTOTYPES
LIBTERM_DECL __ATTR_NONNULL((1)) __KERNEL_SELECT(__size_t, __ssize_t) LIBTERM_CC
terminal_flush_icanon(struct terminal *__restrict self, iomode_t mode)
		__KERNEL_SELECT(__THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC, ...),
		                __THROWS(E_WOULDBLOCK, E_INTERRUPT, ...));
#endif /* LIBTERM_WANT_PROTOTYPES */


/* Poll for `terminal_iread()' to become non-blocking. */
#define terminal_caniread(self)                                                      \
	((__hybrid_atomic_load(&(self)->t_ios.c_lflag, __ATOMIC_ACQUIRE) & __IEOFING) || \
	 ringbuffer_canread(&(self)->t_ibuf))
#define terminal_pollconnect_iread_ex(self, cb) \
	ringbuffer_pollconnect_read_ex(&(self)->t_ibuf, cb)
#ifdef __OPTIMIZE_SIZE__
#define terminal_polliread_ex(self, cb)       \
	(terminal_pollconnect_iread_ex(self, cb), \
	 terminal_caniread(self))
#else /* __OPTIMIZE_SIZE__ */
#define terminal_polliread_ex(self, cb)        \
	(terminal_caniread(self) ||                \
	 (terminal_pollconnect_iread_ex(self, cb), \
	  terminal_caniread(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef ringbuffer_pollconnect_read
#define terminal_pollconnect_iread(self) \
	ringbuffer_pollconnect_read(&(self)->t_ibuf)
#endif /* ringbuffer_pollconnect_read */
#ifdef terminal_pollconnect_iread
#ifdef __OPTIMIZE_SIZE__
#define terminal_polliread(self)       \
	(terminal_pollconnect_iread(self), \
	 terminal_caniread(self))
#else /* __OPTIMIZE_SIZE__ */
#define terminal_polliread(self)        \
	(terminal_caniread(self) ||         \
	 (terminal_pollconnect_iread(self), \
	  terminal_caniread(self)))
#endif /* !__OPTIMIZE_SIZE__ */
#endif /* terminal_pollconnect_iread */


/* Poll for `terminal_owrite()' to become non-blocking. */
#define terminal_canowrite(self, t_oprint_canwrite)                             \
	((__hybrid_atomic_load(&(self)->t_ios.c_iflag, __ATOMIC_ACQUIRE) & __IXOFF) \
	 ? linebuffer_canwrite(&(self)->t_opend)                                    \
	 : (t_oprint_canwrite))
#define terminal_pollconnect_owrite_ex(self, t_oprint_connect_ex, cb)           \
	((__hybrid_atomic_load(&(self)->t_ios.c_iflag, __ATOMIC_ACQUIRE) & __IXOFF) \
	 ? linebuffer_pollconnect_write_ex(&(self)->t_opend, cb)                    \
	 : (cb(&(self)->t_ioschange), /* Listen for `IXOFF' being set */            \
	    t_oprint_connect_ex(cb) /* Listen for the underlying device */))
#ifdef __OPTIMIZE_SIZE__
#define terminal_pollowrite_ex(self, t_oprint_canwrite, t_oprint_connect_ex, cb) \
	(terminal_pollconnect_owrite_ex(self, t_oprint_connect_ex, cb),              \
	 terminal_canowrite(self, t_oprint_canwrite))
#else /* __OPTIMIZE_SIZE__ */
#define terminal_pollowrite_ex(self, t_oprint_canwrite, t_oprint_connect_ex, cb) \
	(terminal_canowrite(self, t_oprint_canwrite) ||                              \
	 (terminal_pollconnect_owrite_ex(self, t_oprint_connect_ex, cb),             \
	  terminal_canowrite(self, t_oprint_canwrite)))
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef sched_signal_connect_for_poll
#define terminal_pollconnect_owrite(self, t_oprint_connect_ex) \
	terminal_pollconnect_owrite_ex(self, t_oprint_connect_ex, sched_signal_connect_for_poll)
#define terminal_pollowrite(self, t_oprint_canwrite, t_oprint_connect_ex) \
	terminal_pollowrite_ex(self, t_oprint_canwrite, t_oprint_connect_ex, sched_signal_connect_for_poll)
#endif /* sched_signal_connect_for_poll */



/* Poll for `terminal_iwrite()' to become non-blocking. */
#define terminal_caniwrite(self, t_oprint_canwrite)                                \
	((__hybrid_atomic_load(&(self)->t_ios.c_iflag, __ATOMIC_ACQUIRE) & __IIOFF)    \
	 ? linebuffer_canwrite(&(self)->t_ipend)                                       \
	 : (__hybrid_atomic_load(&(self)->t_ios.c_lflag, __ATOMIC_ACQUIRE) & __ICANON) \
	   ? linebuffer_canwrite(&(self)->t_canon)                                     \
	   : (ringbuffer_canwrite(&(self)->t_ibuf) &&                                  \
	      ((__hybrid_atomic_load(&(self)->t_ios.c_lflag, __ATOMIC_ACQUIRE) &       \
	        (__ECHO | __EXTPROC)) != __ECHO ||                                     \
	       terminal_canowrite(self, t_oprint_canwrite) /* For echo */)))
#define terminal_pollconnect_iwrite_ex(self, t_oprint_connect_ex, cb)              \
	((__hybrid_atomic_load(&(self)->t_ios.c_iflag, __ATOMIC_ACQUIRE) & __IIOFF)    \
	 ? (void)linebuffer_pollconnect_write_ex(&(self)->t_ipend, cb)                 \
	 : (__hybrid_atomic_load(&(self)->t_ios.c_lflag, __ATOMIC_ACQUIRE) & __ICANON) \
	   ? (void)linebuffer_pollconnect_write_ex(&(self)->t_canon, cb)               \
	   : (ringbuffer_pollconnect_write_ex(&(self)->t_ibuf, cb),                    \
	      ((__hybrid_atomic_load(&(self)->t_ios.c_lflag, __ATOMIC_ACQUIRE) &       \
	        (__ECHO | __EXTPROC)) == __ECHO                                        \
	       ? (void)terminal_pollconnect_owrite_ex(self, t_oprint_connect_ex, cb)   \
	       : (void)0)))
#define terminal_polliwrite_unlikely_ex(self, t_oprint_canwrite, t_oprint_connect_ex, cb) \
	(terminal_pollconnect_iwrite_ex(self, t_oprint_connect_ex, cb),                       \
	 terminal_caniwrite(self, t_oprint_canwrite))
#ifdef __OPTIMIZE_SIZE__
#define terminal_polliwrite_ex(self, t_oprint_canwrite, t_oprint_connect_ex, cb) \
	terminal_polliwrite_unlikely_ex(self, t_oprint_canwrite, t_oprint_connect_ex, cb)
#else /* __OPTIMIZE_SIZE__ */
#define terminal_polliwrite_ex(self, t_oprint_canwrite, t_oprint_connect_ex, cb) \
	(terminal_caniwrite(self, t_oprint_canwrite) ||                              \
	 (terminal_pollconnect_iwrite_ex(self, t_oprint_connect_ex, cb),             \
	  terminal_caniwrite(self, t_oprint_canwrite)))
#endif /* !__OPTIMIZE_SIZE__ */
#ifdef sched_signal_connect_for_poll
#define terminal_pollconnect_iwrite(self, t_oprint_connect_ex) \
	terminal_pollconnect_iwrite_ex(self, t_oprint_connect_ex, sched_signal_connect_for_poll)
#define terminal_polliwrite(self, t_oprint_canwrite, t_oprint_connect_ex) \
	terminal_polliwrite_ex(self, t_oprint_canwrite, t_oprint_connect_ex, sched_signal_connect_for_poll)
#define terminal_polliwrite_unlikely(self, t_oprint_canwrite, t_oprint_connect_ex) \
	terminal_polliwrite_unlikely_ex(self, t_oprint_canwrite, t_oprint_connect_ex, sched_signal_connect_for_poll)
#endif /* sched_signal_connect_for_poll */

#undef __KERNEL_SELECT

#endif /* __CC__ */

__DECL_END

#endif /* !_LIBTERM_TERMIO_H */
