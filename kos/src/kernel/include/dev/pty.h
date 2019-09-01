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
#ifndef GUARD_KERNEL_INCLUDE_DEV_PTY_H
#define GUARD_KERNEL_INCLUDE_DEV_PTY_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <dev/char.h>
#include <dev/ttybase.h>
#include <libbuffer/linebuffer.h>
#include <libbuffer/ringbuffer.h>
#include <kos/dev.h>
#include <termio.h>

DECL_BEGIN

/* PTY device numbers.
 * NOTE: These must only be used for drivers allocated by `openpty()'.
 *       Any other sub-system making use of, or extending upon PTY
 *       terminal drivers must implement its own device numbering system.
 * NOTE: To register a pty master/slave pair for `openpty()', use `pty_register' below.
 */
#define PTY_DEVCNT    256
#define PTY_MASTER(n) MKDEV(2,n)
#define PTY_SLAVE(n)  MKDEV(3,n)
#define PTY_EXTCNT   (1 << MINORBITS) /* Total number of unique PTY devices. */


#ifdef __CC__
struct taskpid;
struct pty_master
#ifdef __cplusplus
	: ttybase_device
#endif
{
	/* PTY Master device */
#ifndef __cplusplus
	struct ttybase_device pm_tty;   /* The underling TTY */
#endif
	struct ringbuffer     pm_obuf;  /* Output buffer (use the PTY master to read from this) */
	WEAK struct winsize   pm_size;  /* Terminal window size. */
};
DEFINE_REFCOUNT_TYPE_SUBCLASS(pty_master, ttybase_device);

/* Check if a given TTY/character device is a PTY object. */
#define ttybase_isapty(self) \
	((self)->t_term.t_oprint == &kernel_pty_oprinter)
#define character_device_isapty(self) \
	(character_device_isattybase(self) && ttybase_isapty((struct ttybase_device *)(self)))

/* oprinter callback for PTY tty objects. */
FUNDEF ssize_t LIBTERM_CC
kernel_pty_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode);



struct pty_slave
#ifdef __cplusplus
	: character_device
#endif
{
	/* TODO: The PTY slave should implement TTY interface.
	 *       This is required, since otherwise, the slave won't count
	 *       as a TTY device and assigning a PTY will not set a valid
	 *       controlling terminal! */
	/* PTY Slave device */
#ifndef __cplusplus
	struct character_device ps_cdev;   /* The underling character-device. */
#endif
	REF struct pty_master  *ps_master; /* [1..1][const] The associated master. */
};
DEFINE_REFCOUNT_TYPE_SUBCLASS(pty_slave, character_device);


/* Allocate a new PTY master/slave
 * NOTE: The caller must still register the devices in devfs,
 *       perferably using the pty_register() function. */
FUNDEF WUNUSED ATTR_RETNONNULL ATTR_MALLOC REF struct pty_master *
KCALL pty_master_alloc(void) THROWS(E_BADALLOC);
FUNDEF WUNUSED ATTR_RETNONNULL ATTR_MALLOC NONNULL((1)) REF struct pty_slave *
KCALL pty_slave_alloc(struct pty_master *__restrict master) THROWS(E_BADALLOC);


/* Register a PTY master/slave pair within devfs, as well
 * as assign matching character device numbers to each. */
FUNDEF void KCALL
pty_register(struct pty_master *__restrict master,
             struct pty_slave *__restrict slave)
		THROWS(E_WOULDBLOCK, E_BADALLOC);




#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_PTY_H */
