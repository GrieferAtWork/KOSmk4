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
#ifndef GUARD_KERNEL_INCLUDE_DEV_MKTTY_H
#define GUARD_KERNEL_INCLUDE_DEV_MKTTY_H 1

#include <kernel/compiler.h>

#include <dev/tty.h>

DECL_BEGIN

/* Terminal  display drivers  such as  VGA should  not implement the
 * tty interface.  Instead,  they  should  only  need  to  implement
 * the   normal  chrdev  interface   and  provide  a  write-operator
 * that implements an ansi-compliant display port (using libansitty)
 *
 * An actual `struct mkttydev' shouldn't actually be something that gets created
 * implicitly, but should be created  explicitly (using the mktty() syscall)  by
 * combining  2 arbitrary  file descriptors,  one providing  a read-operator and
 * presumably  being  implemented  by something  like  the ps2  driver,  and the
 * other  providing  a  write-operator  and  presumably  being  implemented   by
 * something like the VGA driver.
 *
 * The actual `struct mkttydev' then uses `struct terminal' to implement the TERMIOS
 * interface, forwarding/pulling data from  its connected read/write object  handles
 * as needed, while also encapsulating all of the required POSIX job control
 *
 * On-top  of this, it would then also be  possible to allow the tty objects to
 * react to the CTRL+ALT+F{1-NN} key combinations to switch between each other.
 *
 * The common base-class of this and PTY objects is `struct ttydev'
 */

#ifdef __CC__
struct mkttydev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : ttydev                         /* The underlying base-tty */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct ttydev   mtd_tty;         /* The underlying base-tty */
#define _mkttydev_astty(x) &(x)->mtd_tty
#define _mkttydev_tty_     mtd_tty.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _mkttydev_astty(x) x
#define _mkttydev_tty_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	uintptr_half_t  mtd_ihandle_typ; /* [const] Input (keyboard) handle type (One of `HANDLE_TYPE_*') */
	uintptr_half_t  mtd_ohandle_typ; /* [const] Output (display) handle type (One of `HANDLE_TYPE_*') */
	REF void       *mtd_ihandle_ptr; /* [1..1][const] Input handle pointer. */
	REF void       *mtd_ohandle_ptr; /* [1..1][const] Output handle pointer. */

	/* [1..1][const] Input handle read operator callback. */
	size_t (KCALL *mtd_ihandle_read)(void *__restrict ptr, NCX void *dst,
	                                 size_t num_bytes, iomode_t mode) /*THROWS(...)*/;

	/* [1..1][const] Input handle poll-connect operator callback. */
	void (KCALL *mtd_ihandle_pollconnect)(void *__restrict ptr, poll_mode_t what) /*THROWS(...)*/;

	/* [1..1][const] Input handle poll-test operator callback. */
	poll_mode_t (KCALL *mtd_ihandle_polltest)(void *__restrict ptr, poll_mode_t what) /*THROWS(...)*/;

	/* [1..1][const] Output handle write operator callback. */
	size_t (KCALL *mtd_ohandle_write)(void *__restrict ptr, NCX void const *src,
	                                  size_t num_bytes, iomode_t mode) /*THROWS(...)*/;
};


/* Operators used by `struct mkttydev' */
DATDEF struct ttydev_ops const mkttydev_ops;

/* Helper macros for `struct mktty' */
#define mfile_ismktty(self)   ((self)->mf_ops == &mktty_ops.to_cdev.cdo_dev.do_node.dvno_node.no_file)
#define mfile_asmktty(self)   ((struct mkttydev *)(self))
#define fnode_ismktty(self)   mfile_ismktty(_fnode_asfile(self))
#define fnode_asmktty(self)   mfile_asmktty(_fnode_asfile(self))
#define devnode_ismktty(self) fnode_ismktty(_fdevnode_asnode(self))
#define devnode_asmktty(self) fnode_asmktty(_fdevnode_asnode(self))
#define device_ismktty(self)  devnode_ismktty(_device_asdevnode(self))
#define device_asmktty(self)  devnode_asmktty(_device_asdevnode(self))
#define chrdev_ismktty(self)  device_ismktty(_chrdev_asdev(self))
#define chrdev_asmktty(self)  device_asmktty(_chrdev_asdev(self))
#define ttydev_ismktty(self)  chrdev_ismktty(_ttydev_aschr(self))
#define ttydev_asmktty(self)  chrdev_asmktty(_ttydev_aschr(self))


/* Create a new TTY device that connects the two given handles, such that
 * character-based keyboard input is taken from `ihandle_ptr', and  ansi-
 * compliant display output is written to `ohandle_ptr'.
 *
 * NOTE: The TTY is created with data forwarding disabled. */
FUNDEF ATTR_RETNONNULL REF struct mkttydev *KCALL
mkttydev_new(uintptr_half_t ihandle_typ, void *ihandle_ptr,
             uintptr_half_t ohandle_typ, void *ohandle_ptr,
             NCX char const *name, size_t namelen)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);

/* Start/Stop forwarding  input  handle  data  on  the  given  TTY
 * Note that for any given input handle, only a single TTY  should
 * ever be allowed to process data. - Allowing multiple TTYs to do
 * so could result  in weakly  undefined behavior as  it would  no
 * longer  be clear  who should  actually receive  data, causing a
 * soft race condition with the potential of data being  scattered
 * between readers, or some random reader getting all of the data.
 * @return: true:  The FWD thread was started/stopped
 * @return: false: The FWD thread was already running/halted */
FUNDEF bool KCALL
mkttydev_startfwd(struct mkttydev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
FUNDEF NOBLOCK bool
NOTHROW(KCALL mkttydev_stopfwd)(struct mkttydev *__restrict self);

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_MKTTY_H */
