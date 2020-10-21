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
#ifndef GUARD_KERNEL_SRC_DEV_PTY_C
#define GUARD_KERNEL_SRC_DEV_PTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <dev/pty.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <hybrid/atomic.h>

#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

/* oprinter callback for PTY tty objects. */
PUBLIC ssize_t LIBTERM_CC
kernel_pty_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode) {
	struct pty_slave *self;
	self = container_of(term, struct pty_slave, t_term);
	return mode & IO_NONBLOCK
	       ? (ssize_t)ringbuffer_write_nonblock(&self->ps_obuf, src, num_bytes)
	       : (ssize_t)ringbuffer_write(&self->ps_obuf, src, num_bytes);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pty_slave_fini)(struct character_device *__restrict self) {
	struct pty_slave *me;
	REF struct pty_master *master;
	me = (struct pty_slave *)self;
	/* Try to clear the master's back-link to our structure. */
	master = me->ps_master.get();
	if (master) {
		assert(master->pm_slave.m_pointer == me);
		master->pm_slave.clear();
		/* Unlikely, since the controlling application is probably
		 * still holding a reference to the master side of the PTY. */
		decref_unlikely(master);
	}
	/* Finalize the used ring buffer. */
	ringbuffer_fini(&me->ps_obuf);
	/* Finalize the underlying TTY-base device. */
	ttybase_device_fini(me);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
pty_slave_ioctl(struct character_device *__restrict self,
                syscall_ulong_t cmd,
                USER UNCHECKED void *arg,
                iomode_t mode)
		THROWS(...) {
	struct pty_slave *me;
	me = (struct pty_slave *)self;
	switch (cmd) {

	/* TODO */

	default:
		/* Fallback: Have the underlying TTY base device handle the ioctl() */
		return ttybase_device_ioctl(me, cmd, arg, mode);
	}
	return 0;
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pty_master_fini)(struct character_device *__restrict self) {
	struct pty_master *me;
	REF struct pty_slave *slave;
	me    = (struct pty_master *)self;
	slave = me->pm_slave.get();
	if (slave) {
		assert(slave->ps_master.m_pointer == self);
		slave->ps_master.clear();
		/* Close buffers of the PTY. */
		ringbuffer_close(&slave->ps_obuf);
		ringbuffer_close(&slave->t_term.t_ibuf);
		linebuffer_close(&slave->t_term.t_opend);
		linebuffer_close(&slave->t_term.t_ipend);
		linebuffer_close(&slave->t_term.t_canon);
		decref_unlikely(slave);
	}
}

PRIVATE NONNULL((1)) size_t KCALL
pty_master_read(struct character_device *__restrict self,
                USER CHECKED void *dst,
                size_t num_bytes, iomode_t mode)
		THROWS(...) {
	size_t result;
	struct pty_master *me;
	REF struct pty_slave *slave;
	me = (struct pty_master *)self;
again_getslave:
	slave = me->pm_slave.get();
	if unlikely(!slave)
		return 0; /* EOF */
	/* Read from the PTY output buffer (allowing the master application to process TTY output) */
again_read:
	TRY {
		result = ringbuffer_read_nonblock(&slave->ps_obuf, dst, num_bytes);
	} EXCEPT {
		decref_unlikely(slave);
		RETHROW();
	}
	if (!result) {
		if (mode & IO_NONBLOCK) {
			if (!(mode & IO_NODATAZERO) && !ringbuffer_closed(&slave->ps_obuf))
				THROW(E_WOULDBLOCK_WAITFORSIGNAL); /* No data available. */
		} else {
			/* Must not keep a reference to the slave while sleeping! */
			TRY {
				if (ringbuffer_pollread_unlikely(&slave->ps_obuf)) {
					task_disconnectall();
					goto again_read;
				}
			} EXCEPT {
				decref_unlikely(slave);
				RETHROW();
			}
			/* Wait for something to happen without holding a reference to the slave! */
			decref_unlikely(slave);
			task_waitfor();
			goto again_getslave;
		}
	}
	decref_unlikely(slave);
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
pty_master_write(struct character_device *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t mode)
		THROWS(...) {
	ssize_t result;
	struct pty_master *me;
	REF struct pty_slave *slave;
	me = (struct pty_master *)self;
again_getslave:
	slave = me->pm_slave.get();
	if unlikely(!slave)
		return 0; /* EOF */
	/* Write to the input buffer, allowing the master application to provide keyboard input. */
again_write:
	TRY {
		result = terminal_iwrite(&slave->t_term,
		                         src, num_bytes,
		                         mode | IO_NONBLOCK);
	} EXCEPT {
		decref_unlikely(slave);
		RETHROW();
	}
	assert((size_t)result <= num_bytes);
	if (!result) {
		if (mode & IO_NONBLOCK) {
			if (!(mode & IO_NODATAZERO))
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
		} else {
			/* Must not keep a reference to the slave while sleeping! */
			TRY {
#define connect_to_slave_ps_obuf_ex(cb) ringbuffer_pollconnect_write_ex(&slave->ps_obuf, cb)
				if (terminal_polliwrite_unlikely(&slave->t_term,
				                                 ringbuffer_canwrite(&slave->ps_obuf),
				                                 connect_to_slave_ps_obuf_ex)) {
					task_disconnectall();
					goto again_write;
				}
#undef connect_to_slave_ps_obuf_ex
			} EXCEPT {
				decref_unlikely(slave);
				RETHROW();
			}
			/* Wait for something to happen without holding a reference to the slave! */
			decref_unlikely(slave);
			task_waitfor();
			goto again_getslave;
		}
	}
	decref_unlikely(slave);
	return (size_t)result;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
pty_master_ioctl(struct character_device *__restrict self,
                 syscall_ulong_t cmd,
                 USER UNCHECKED void *arg,
                 iomode_t mode)
		THROWS(...) {
	struct pty_master *me;
	REF struct pty_slave *slave;
	syscall_slong_t result;
	me    = (struct pty_master *)self;
	slave = me->pm_slave.get();
	if unlikely(!slave) {
		THROW(E_NO_DEVICE,
		      E_NO_DEVICE_KIND_CHARACTER_DEVICE,
		      PTY_SLAVE(MINOR(character_device_devno(self))));
	}
	{
		FINALLY_DECREF_UNLIKELY(slave);
		result = pty_slave_ioctl(slave, cmd, arg, mode);
	}
	return result;
}

PRIVATE NONNULL((1)) void KCALL
pty_master_stat(struct character_device *__restrict self,
                USER CHECKED struct stat *result)
		THROWS(...) {
	struct pty_master *me;
	REF struct pty_slave *slave;
	me    = (struct pty_master *)self;
	slave = me->pm_slave.get();
	if (slave) {
		FINALLY_DECREF_UNLIKELY(slave);
		result->st_size = ATOMIC_READ(slave->ps_obuf.rb_avail);
	} else {
		result->st_size = 0;
	}
}

PRIVATE NONNULL((1)) void KCALL
pty_master_pollconnect(struct character_device *__restrict self,
                       poll_mode_t what)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct pty_master *me;
	REF struct pty_slave *slave;
	me    = (struct pty_master *)self;
	slave = me->pm_slave.get();
	if (!slave)
		;
	else {
		FINALLY_DECREF_UNLIKELY(slave);
		if (what & POLLINMASK)
			ringbuffer_pollconnect_read(&slave->ps_obuf); /* Poll for read() */
		if (what & POLLOUTMASK) {
			/* Poll for write() */
#define connect_to_slave_ps_obuf_ex(cb) ringbuffer_pollconnect_write_ex(&slave->ps_obuf, cb)
			terminal_pollconnect_iwrite(&slave->t_term, connect_to_slave_ps_obuf_ex);
#undef connect_to_slave_ps_obuf_ex
		}
	}
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
pty_master_polltest(struct character_device *__restrict self,
                    poll_mode_t what)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct pty_master *me;
	REF struct pty_slave *slave;
	poll_mode_t result = 0;
	me    = (struct pty_master *)self;
	slave = me->pm_slave.get();
	if (!slave)
		result = what;
	else {
		FINALLY_DECREF_UNLIKELY(slave);
		if ((what & POLLINMASK) && ringbuffer_canread(&slave->ps_obuf))
			result |= POLLINMASK; /* Test for read() */
		if ((what & POLLOUTMASK) && terminal_caniwrite(&slave->t_term, ringbuffer_canwrite(&slave->ps_obuf)))
			result |= POLLOUTMASK;
	}
	return result;
}



LOCAL REF struct pty_slave *KCALL pty_slave_alloc(void) {
	REF struct pty_slave *result;
	result = CHARACTER_DEVICE_ALLOC(struct pty_slave);
	/* Initialize the underlying TTY-device base layer. */
	ttybase_device_cinit(result, &kernel_pty_oprinter);
	/* Override device operators. */
	result->cd_type.ct_fini  = &pty_slave_fini;
	result->cd_type.ct_ioctl = &pty_slave_ioctl;
	/* Initialize the output buffer. */
	ringbuffer_cinit(&result->ps_obuf);
	return result;
}

LOCAL REF struct pty_master *KCALL pty_master_alloc(void) {
	REF struct pty_master *result;
	result = CHARACTER_DEVICE_ALLOC(struct pty_master);
	/* Initialize device operators. */
	result->cd_type.ct_fini        = &pty_master_fini;
	result->cd_type.ct_read        = &pty_master_read;
	result->cd_type.ct_write       = &pty_master_write;
	result->cd_type.ct_ioctl       = &pty_master_ioctl;
	result->cd_type.ct_stat        = &pty_master_stat;
	result->cd_type.ct_pollconnect = &pty_master_pollconnect;
	result->cd_type.ct_polltest    = &pty_master_polltest;
	return result;
}

INTDEF void KCALL
pty_register(struct pty_master *__restrict master,
             struct pty_slave *__restrict slave)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Allocate a new PTY master/slave pair.
 * Note that the device pair will have already been registered. */
PUBLIC NONNULL((1, 2)) void KCALL
pty_alloc(REF struct pty_master **__restrict pmaster,
          REF struct pty_slave **__restrict pslave,
          USER CHECKED struct termios const *termp,
          USER CHECKED struct winsize const *winp)
		THROWS(E_BADALLOC) {
	REF struct pty_slave *slave;
	REF struct pty_master *master;
	/* Allocate the slave and master control structures. */
	slave = pty_slave_alloc();
	TRY {
		master = pty_master_alloc();
		TRY {
			/* Link the slave and master against each other. */
			xatomic_weaklyref_cinit(&slave->ps_master, master);
			xatomic_weaklyref_cinit(&master->pm_slave, slave);
			/* Load user-space provided initializers. */
			if (termp)
				memcpy(&slave->t_term.t_ios, termp, sizeof(struct termios));
			if (winp)
				memcpy(&slave->ps_wsize, termp, sizeof(struct winsize));
			else {
				slave->ps_wsize.ws_xpixel = slave->ps_wsize.ws_col = 80;
				slave->ps_wsize.ws_ypixel = slave->ps_wsize.ws_row = 25;
			}
			/* Set the weak-registration flags for the master slave PTY devices.
			 * This allows the devices to automatically be deleted once user-space
			 * gets rid of the last reference to any of them! */
			master->cd_flags |= CHARACTER_DEVICE_FLAG_WEAKREG;
			slave->cd_flags |= CHARACTER_DEVICE_FLAG_WEAKREG;

			/* Assign names, MKDEV(), and register in /dev */
			pty_register(master, slave);
		} EXCEPT {
			decref_unlikely(master);
			RETHROW();
		}
	} EXCEPT {
		decref_unlikely(slave);
		RETHROW();
	}
	*pslave  = slave;  /* Inherit reference */
	*pmaster = master; /* Inherit reference */
}





/************************************************************************/
/* openpty()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_OPENPTY
DEFINE_SYSCALL5(errno_t, openpty,
                USER UNCHECKED fd_t *, amaster,
                USER UNCHECKED fd_t *, aslave,
                USER UNCHECKED char *, name,
                USER UNCHECKED struct termios const *, termp,
                USER UNCHECKED struct winsize const *, winp) {
	struct handle temp;
	fd_t fdmaster, fdslave;
	REF struct pty_master *master;
	REF struct pty_slave *slave;
	validate_readable_opt(termp, sizeof(*termp));
	validate_readable_opt(winp, sizeof(*winp));
	validate_writable_opt(name, 1);
	validate_writable(aslave, sizeof(*aslave));
	validate_writable(amaster, sizeof(*amaster));
	/* Allocate the PTY device pair. */
	pty_alloc(&master, &slave, termp, winp);
	FINALLY_DECREF_UNLIKELY(master);
	FINALLY_DECREF_UNLIKELY(slave);
	if (name)
		sprintf(name, "/dev/%s", master->cd_name);
	temp.h_type = HANDLE_TYPE_CHARACTERDEVICE;
	temp.h_mode = IO_RDWR;
	temp.h_data = master;
	fdmaster    = handle_install(THIS_HANDLE_MANAGER, temp);
	TRY {
		temp.h_data = slave;
		fdslave     = handle_install(THIS_HANDLE_MANAGER, temp);
		TRY {
			/* Save the master/slave handlers into their user-space pointers. */
			ATOMIC_WRITE(*amaster, fdmaster);
			ATOMIC_WRITE(*aslave, fdslave);
		} EXCEPT {
			handle_tryclose_nosym(fdslave, THIS_HANDLE_MANAGER);
			RETHROW();
		}
	} EXCEPT {
		handle_tryclose_nosym(fdmaster, THIS_HANDLE_MANAGER);
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OPENPTY */

DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_PTY_C */
