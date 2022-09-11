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
#ifndef GUARD_KERNEL_INCLUDE_DEV_PTY_H
#define GUARD_KERNEL_INCLUDE_DEV_PTY_H 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/types.h>

#include <bits/os/termio.h>  /* struct winsize */
#include <bits/os/termios.h> /* struct termios */
#include <kos/aref.h>
#include <sys/mkdev.h>

#include <libbuffer/ringbuffer.h>

/* PTY device numbers. */
#define PTY_DEVCNT    256
#define PTY_MASTER(n) makedev(2, n)
#define PTY_SLAVE(n)  makedev(3, n)
#define PTY_EXTCNT    MINOR_MAX /* Total number of unique PTY devices. */


#ifdef __CC__
DECL_BEGIN

struct ptymaster;
struct ptyslave;

#ifndef __ptymaster_awref_defined
#define __ptymaster_awref_defined
AWREF(ptymaster_awref, ptymaster);
#endif /* !__ptymaster_awref_defined */

#ifndef __ptyslave_awref_defined
#define __ptyslave_awref_defined
AWREF(ptyslave_awref, ptyslave);
#endif /* !__ptyslave_awref_defined */

struct ptyslave
#ifndef __WANT_FS_INLINE_STRUCTURES
    : ttydev                          /* The underlying tty device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct ttydev          ps_tty;    /* The underlying tty device */
#define _ptyslave_astty(x) &(x)->ps_tty
#define _ptyslave_tty_     ps_tty.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _ptyslave_astty(x) x
#define _ptyslave_tty_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct ringbuffer      ps_obuf;   /* Output buffer (use the PTY master to read from this) */
	WEAK struct winsize    ps_wsize;  /* Terminal window size. */
	struct ptymaster_awref ps_master; /* [0..1] The terminal's master side (cleared when destroyed) */
};

struct ptymaster
#ifdef __cplusplus
    : chrdev                         /* The underlying character device */
#endif /* __cplusplus */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct chrdev          pm_cdev;  /* The underlying character device */
#define _ptymaster_aschr(x) &(x)->pm_cdev
#define _ptymaster_chr_     pm_cdev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _ptymaster_aschr(x) x
#define _ptymaster_chr_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct ptyslave_awref  pm_slave; /* [0..1] The terminal's slave side (cleared when destroyed) */
};

/* Operators used by `struct ptyslave' */
DATDEF struct ttydev_ops const ptyslave_ops;

/* Operators used by `struct ptymaster' */
DATDEF struct chrdev_ops const ptymaster_ops;

/* Helper macros for `struct ptyslave' */
#define mfile_isptyslave(self)   ((self)->mf_ops == &ptyslave_ops.to_cdev.cdo_dev.do_node.dvno_node.no_file)
#define mfile_asptyslave(self)   ((struct ptyslave *)(self))
#define fnode_isptyslave(self)   mfile_isptyslave(_fnode_asfile(self))
#define fnode_asptyslave(self)   mfile_asptyslave(_fnode_asfile(self))
#define devnode_isptyslave(self) fnode_isptyslave(_fdevnode_asnode(self))
#define devnode_asptyslave(self) fnode_asptyslave(_fdevnode_asnode(self))
#define device_isptyslave(self)  devnode_isptyslave(_device_asdevnode(self))
#define device_asptyslave(self)  devnode_asptyslave(_device_asdevnode(self))
#define chrdev_isptyslave(self)  device_isptyslave(_chrdev_asdev(self))
#define chrdev_asptyslave(self)  device_asptyslave(_chrdev_asdev(self))
#define ttydev_isptyslave(self)  chrdev_isptyslave(_ttydev_aschr(self))
#define ttydev_asptyslave(self)  chrdev_asptyslave(_ttydev_aschr(self))

/* Helper macros for `struct ptymaster' */
#define mfile_isptymaster(self)   ((self)->mf_ops == &ptymaster_ops.cdo_dev.do_node.dvno_node.no_file)
#define mfile_asptymaster(self)   ((struct ptymaster *)(self))
#define fnode_isptymaster(self)   mfile_isptymaster(_fnode_asfile(self))
#define fnode_asptymaster(self)   mfile_asptymaster(_fnode_asfile(self))
#define devnode_isptymaster(self) fnode_isptymaster(_fdevnode_asnode(self))
#define devnode_asptymaster(self) fnode_asptymaster(_fdevnode_asnode(self))
#define device_isptymaster(self)  devnode_isptymaster(_device_asdevnode(self))
#define device_asptymaster(self)  devnode_asptymaster(_device_asdevnode(self))
#define chrdev_isptymaster(self)  device_isptymaster(_chrdev_asdev(self))
#define chrdev_asptymaster(self)  device_asptymaster(_chrdev_asdev(self))

/* Allocate a new PTY master/slave pair.
 * Note that the device pair will have already been registered. */
FUNDEF NONNULL((1, 2)) void KCALL
pty_alloc(REF struct ptymaster **__restrict p_master,
          REF struct ptyslave **__restrict p_slave,
          USER CHECKED struct termios const *termp,
          USER CHECKED struct winsize const *winp)
		THROWS(E_BADALLOC);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_DEV_PTY_H */
