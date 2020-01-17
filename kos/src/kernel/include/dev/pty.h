/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DEV_PTY_H
#define GUARD_KERNEL_INCLUDE_DEV_PTY_H 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <dev/ttybase.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>

#include <kos/dev.h>

#include <termios.h>

#include <libbuffer/ringbuffer.h>

DECL_BEGIN

/* PTY device numbers.
 * NOTE: These must only be used for drivers allocated by `openpty()'.
 *       Any other sub-system making use of, or extending upon PTY
 *       terminal drivers must implement its own device numbering system.
 * NOTE: To register a pty master/slave pair for `openpty()', use `pty_register' below.
 */
#define PTY_DEVCNT    256
#define PTY_MASTER(n) MKDEV(2, n)
#define PTY_SLAVE(n)  MKDEV(3, n)
#define PTY_EXTCNT    (1 << MINORBITS) /* Total number of unique PTY devices. */


#ifdef __CC__

struct pty_master;
struct pty_slave;

struct pty_slave
#ifdef __cplusplus
    : ttybase_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct ttybase_device                ps_base;   /* The underlying base-tty */
#endif /* !__cplusplus */
	struct ringbuffer                    ps_obuf;   /* Output buffer (use the PTY master to read from this) */
	WEAK struct winsize                  ps_wsize;  /* Terminal window size. */
	XATOMIC_WEAKLYREF(struct pty_master) ps_master; /* [0..1] The terminal's master side (cleared when destroyed) */
};
DEFINE_REFCOUNT_TYPE_SUBCLASS(pty_slave, ttybase_device);

struct pty_master
#ifdef __cplusplus
    : character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device             pm_base;  /* The underlying base-tty */
#endif /* !__cplusplus */
	XATOMIC_WEAKLYREF(struct pty_slave) pm_slave; /* [0..1] The terminal's slave side (cleared when destroyed) */
};
DEFINE_REFCOUNT_TYPE_SUBCLASS(pty_master, character_device);

/* Check if a given TTY/character device is a `struct pty_slave'. */
#define ttybase_isapty(self) \
	((self)->t_term.t_oprint == &kernel_pty_oprinter)
#define character_device_isapty(self) \
	(character_device_isattybase(self) && ttybase_isapty((struct ttybase_device *)(self)))

/* oprinter callback for `struct pty_slave' tty objects. */
FUNDEF ssize_t LIBTERM_CC
kernel_pty_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode);

/* Allocate a new PTY master/slave pair.
 * Note that the device pair will have already been registered. */
FUNDEF NONNULL((1, 2)) void KCALL
pty_alloc(REF struct pty_master **__restrict pmaster,
          REF struct pty_slave **__restrict pslave,
          USER CHECKED struct termios const *termp,
          USER CHECKED struct winsize const *winp)
		THROWS(E_BADALLOC);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_PTY_H */
