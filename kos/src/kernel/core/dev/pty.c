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
#ifndef GUARD_KERNEL_SRC_DEV_PTY_C
#define GUARD_KERNEL_SRC_DEV_PTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/pty.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/ramfs.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <sys/mkdev.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECL_BEGIN

/* oprinter callback for PTY tty objects. */
PRIVATE ssize_t LIBTERM_CC
ptyslave_v_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode) {
	struct ptyslave *self;
	self = container_of(term, struct ptyslave, t_term);
	return mode & IO_NONBLOCK
	       ? (ssize_t)ringbuffer_write_nonblock(&self->ps_obuf, src, num_bytes)
	       : (ssize_t)ringbuffer_write(&self->ps_obuf, src, num_bytes);
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
ptyslave_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                 NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	struct ptyslave *me = mfile_asptyslave(self);
	switch (cmd) {

	/* TODO */

	default:
		/* Fallback: Have the underlying TTY base device handle the ioctl() */
		return ttydev_v_ioctl(me, cmd, arg, mode);
	}
	return 0;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ptyslave_v_destroy)(struct mfile *__restrict self) {
	REF struct ptymaster *master;
	struct ptyslave *me = mfile_asptyslave(self);

	/* Try to clear the master's back-link to our structure. */
	master = awref_get(&me->ps_master);
	if (master) {
		assert(awref_ptr(&master->pm_slave) == me);
		awref_clear(&master->pm_slave);
		/* Unlikely,  since the controlling application is probably
		 * still holding a reference to the master side of the PTY. */
		decref_unlikely(master);
	}

	/* Finalize the used ring buffer. */
	ringbuffer_fini(&me->ps_obuf);

	/* Finalize the underlying TTY-base device. */
	ttydev_v_destroy(self);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ptymaster_v_destroy)(struct mfile *__restrict self) {
	struct ptymaster *me = mfile_asptymaster(self);
	REF struct ptyslave *slave;
	slave = awref_get(&me->pm_slave);
	if (slave) {
		assert(awref_ptr(&slave->ps_master) == self);
		awref_clear(&slave->ps_master);
		/* Close buffers of the PTY. */
		ringbuffer_close(&slave->ps_obuf);
		ringbuffer_close(&slave->t_term.t_ibuf);
		linebuffer_close(&slave->t_term.t_opend);
		linebuffer_close(&slave->t_term.t_ipend);
		linebuffer_close(&slave->t_term.t_canon);
		decref_unlikely(slave);
	}
	chrdev_v_destroy(self);
}


PRIVATE NONNULL((1)) size_t KCALL
ptymaster_v_read(struct mfile *__restrict self,
                 NCX void *dst,
                 size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct ptymaster *me = mfile_asptymaster(self);
	size_t result;
	REF struct ptyslave *slave;

again_getslave:
	slave = awref_get(&me->pm_slave);
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
			{
				FINALLY_DECREF_UNLIKELY(slave);
				if (ringbuffer_pollread_unlikely(&slave->ps_obuf)) {
					task_disconnectall();
					goto again_read;
				}
			}
			/* Wait for something to happen without holding a reference to the slave! */
			task_waitfor();
			goto again_getslave;
		}
	}
	decref_unlikely(slave);
	return result;
}


PRIVATE NONNULL((1)) size_t KCALL
ptymaster_v_write(struct mfile *__restrict self,
                  NCX void const *src,
                  size_t num_bytes, iomode_t mode)
		THROWS(...) {
	struct ptymaster *me = mfile_asptymaster(self);
	ssize_t result;
	REF struct ptyslave *slave;

again_getslave:
	slave = awref_get(&me->pm_slave);
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
			{
				FINALLY_DECREF_UNLIKELY(slave);
#define connect_to_slave_ps_obuf_ex(cb) ringbuffer_pollconnect_write_ex(&slave->ps_obuf, cb)
				if (terminal_polliwrite_unlikely(&slave->t_term,
				                                 ringbuffer_canwrite(&slave->ps_obuf),
				                                 connect_to_slave_ps_obuf_ex)) {
					task_disconnectall();
					goto again_write;
				}
#undef connect_to_slave_ps_obuf_ex
			}
			/* Wait for something to happen without holding a reference to the slave! */
			task_waitfor();
			goto again_getslave;
		}
	}
	decref_unlikely(slave);
	return (size_t)result;
}


PRIVATE NONNULL((1)) syscall_slong_t KCALL
ptymaster_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                  NCX UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	struct ptymaster *me = mfile_asptymaster(self);
	REF struct ptyslave *slave;
	syscall_slong_t result;
	slave = awref_get(&me->pm_slave);
	if unlikely(!slave) {
		THROW(E_NO_DEVICE,
		      E_NO_DEVICE_KIND_CHRDEV,
		      PTY_SLAVE(device_getminor(me)));
	}
	{
		FINALLY_DECREF_UNLIKELY(slave);
		result = ptyslave_v_ioctl(slave, cmd, arg, mode);
	}
	return result;
}


PRIVATE NONNULL((1)) void KCALL
ptymaster_v_stat(struct mfile *__restrict self,
                 NCX struct stat *result)
		THROWS(...) {
	struct ptymaster *me = mfile_asptymaster(self);
	REF struct ptyslave *slave;
	slave = awref_get(&me->pm_slave);
	if (slave) {
		FINALLY_DECREF_UNLIKELY(slave);
		result->st_size = atomic_read(&slave->ps_obuf.rb_avail);
	} else {
		result->st_size = 0;
	}
}


PRIVATE NONNULL((1)) void KCALL
ptymaster_v_pollconnect(struct mfile *__restrict self,
                        poll_mode_t what)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct ptymaster *me = mfile_asptymaster(self);
	REF struct ptyslave *slave;
	slave = awref_get(&me->pm_slave);
	if (!slave) {
		/* ... */
	} else {
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
ptymaster_v_polltest(struct mfile *__restrict self,
                     poll_mode_t what)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	struct ptymaster *me = mfile_asptymaster(self);
	REF struct ptyslave *slave;
	poll_mode_t result = 0;
	slave = awref_get(&me->pm_slave);
	if (!slave) {
		result = what;
	} else {
		FINALLY_DECREF_UNLIKELY(slave);
		if ((what & POLLINMASK) && ringbuffer_canread(&slave->ps_obuf))
			result |= POLLINMASK; /* Test for read() */
		if ((what & POLLOUTMASK) && terminal_caniwrite(&slave->t_term, ringbuffer_canwrite(&slave->ps_obuf)))
			result |= POLLOUTMASK;
	}
	return result;
}





/* Operators used by `struct ptyslave' */
PRIVATE struct mfile_stream_ops const ptyslave_stream_ops = {
	.mso_open        = &ttydev_v_open,
	.mso_read        = &ttydev_v_read,
	.mso_write       = &ttydev_v_write,
	.mso_stat        = &ttydev_v_stat,
	.mso_pollconnect = &ttydev_v_pollconnect,
	.mso_polltest    = &ttydev_v_polltest,
	.mso_ioctl       = &ptyslave_v_ioctl,
	.mso_tryas       = &ttydev_v_tryas,
};
PUBLIC_CONST struct ttydev_ops const ptyslave_ops = {{{{{
	.no_file = {
		.mo_destroy = &ptyslave_v_destroy,
		.mo_changed = &ttydev_v_changed,
		.mo_stream  = &ptyslave_stream_ops,
	},
	.no_wrattr = &ttydev_v_wrattr,
}}}}};

/* Operators used by `struct ptymaster' */
PRIVATE struct mfile_stream_ops const ptymaster_stream_ops = {
	.mso_read        = &ptymaster_v_read,
	.mso_write       = &ptymaster_v_write,
	.mso_stat        = &ptymaster_v_stat,
	.mso_pollconnect = &ptymaster_v_pollconnect,
	.mso_polltest    = &ptymaster_v_polltest,
	.mso_ioctl       = &ptymaster_v_ioctl,
	.mso_tryas       = &chrdev_v_tryas,
};
PUBLIC_CONST struct chrdev_ops const ptymaster_ops = {{{{
	.no_file = {
		.mo_destroy = &ptymaster_v_destroy,
		.mo_changed = &chrdev_v_changed,
		.mo_stream  = &ptymaster_stream_ops,
	},
	.no_wrattr = &chrdev_v_wrattr,
}}}};


/* Set the given `minor' to-be referenced by `name' */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL set_pty_name_minor)(struct devdirent *__restrict name,
                                  minor_t minor) {
	if (minor >= PTY_DEVCNT) {
		/* KOS-specific, extended PTY device. */
		static_assert(MINOR_BITS / 4 == 5);
		sprintf(name->dd_dirent.fd_name + 3,
		        "X%.5" PRIxN(__SIZEOF_MINOR_T__), minor);
		name->dd_dirent.fd_namelen = 9;
	} else {
		/* Old (BSD-style) PTY master/slave device names. */
		char temp = 'p' + (minor / 16);
		if (temp > 'z')
			temp = 'a' + (temp - 'z');
		name->dd_dirent.fd_name[3] = temp;
		name->dd_dirent.fd_name[4] = _itoa_lower_digits[minor % 16];
		name->dd_dirent.fd_name[5] = '\0';
		name->dd_dirent.fd_namelen = 5;
	}
}

INTDEF NOBLOCK NONNULL((1)) void /* From "filesys/devfs.c" */
NOTHROW(FCALL devfs_log_new_device)(struct device *__restrict self);

PRIVATE NONNULL((1, 2)) void FCALL
register_pty_pair(struct ptymaster *__restrict master,
                  struct ptyslave *__restrict slave)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct devdirent *master_name, *slave_name;
	/* KOS Extension: Since we allocate '20' bits for minor device numbers,
	 *                it's actually possible  to get _much_  more than  256
	 *                pty devices in KOS (1048576 to be exact).
	 *             >> But for all those additional nodes, we need a new
	 *                naming  scheme that isn't standardized due to its
	 *                nature of being an extension:
	 * MASTER: /dev/ptyX12345
	 * SLAVE:  /dev/ttyX12345
	 * NOTE: The 12345 is the hex value of the minor device number, using lower-case letters. */
	static_assert(MINOR_BITS / 4 == 5);
	master_name = devdirent_newf("ptyX.....");
	TRY {
		slave_name = devdirent_newf("ttyX.....");
		TRY {
			minor_t min;
			/* Mark the 2 devices such that they're _NOT_ part of the all-nodes  list.
			 * No part of the kernel holds explicit reference to PTY devices, which is
			 * important for allowing such devices to implicitly delete themselves  as
			 * soon as no-one is holding any more references to them. */
			LIST_ENTRY_UNBOUND_INIT(&master->fn_allnodes);
			LIST_ENTRY_UNBOUND_INIT(&slave->fn_allnodes);
			assert(!(master->mf_flags & MFILE_FN_GLOBAL_REF));
			assert(!(slave->mf_flags & MFILE_FN_GLOBAL_REF));

			/* Link directory entries with PTY devices. */
			awref_init(&master_name->dd_dev, master);
			awref_init(&slave_name->dd_dev, slave);
			master->dv_dirent = master_name; /* Inherit reference */
			slave->dv_dirent  = slave_name;  /* Inherit reference */

			/* Acquire locks needed for registering new devices. */
			_device_register_lock_acquire(false);

			/* Find the first unused minor */
			for (min = 0;; ++min) {
				/* Assign device number */
				master->dn_devno = PTY_MASTER(min);
				slave->dn_devno  = PTY_SLAVE(min);
				master->fn_ino   = devfs_devnode_makeino(S_IFCHR, master->dn_devno);
				slave->fn_ino    = devfs_devnode_makeino(S_IFCHR, slave->dn_devno);
				if (!_device_register_inuse_ino(master->fn_ino) &&
				    !_device_register_inuse_ino(slave->fn_ino))
					break; /* This one's not in use already! */
				if unlikely(min >= 0xfffff) {
					_device_register_lock_release(false);
					THROW(E_BADALLOC_INSUFFICIENT_DEVICE_NUMBERS,
					      E_NO_DEVICE_KIND_CHRDEV);
				}
			}

			/* Insert into the devfs INode tree. */
			fsuper_nodes_insert(&devfs, master);
			fsuper_nodes_insert(&devfs, slave);

			/* Set device names (based on minor numbers). */
			set_pty_name_minor(master_name, min);
			set_pty_name_minor(slave_name, min);

			/* Only register within the filesystem if the name isn't already in use. */
			if unlikely(_device_register_inuse_name(master_name->dd_dirent.fd_name,
			                                        master_name->dd_dirent.fd_namelen)) {
				master->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
			} else {
				devfs_byname_insert(master);
			}
			if unlikely(_device_register_inuse_name(slave_name->dd_dirent.fd_name,
			                                        slave_name->dd_dirent.fd_namelen)) {
				slave->dv_byname_node.rb_lhs = DEVICE_BYNAME_DELETED;
			} else {
				devfs_byname_insert(slave);
			}

			/* Log the creation of new device files. */
			devfs_log_new_device(master);
			devfs_log_new_device(slave);

			/* Release locks. */
			_device_register_lock_release(false);
		} EXCEPT {
			kfree(slave_name);
			RETHROW();
		}
	} EXCEPT {
		kfree(master_name);
		RETHROW();
	}
}


/* Allocate a new PTY master/slave pair.
 * Note that the device pair will have already been registered. */
PUBLIC NONNULL((1, 2)) void KCALL
pty_alloc(REF struct ptymaster **__restrict p_master,
          REF struct ptyslave **__restrict p_slave,
          NCX struct termios const *termp,
          NCX struct winsize const *winp)
		THROWS(E_BADALLOC) {
	struct ptymaster *master;
	struct ptyslave *slave;
	/* Allocate objects. */
	master = (struct ptymaster *)kmalloc(sizeof(struct ptymaster), GFP_NORMAL);
	_chrdev_init(master, &ptymaster_ops);
	master->dv_driver = incref(&drv_self);
	TRY {
		slave = (struct ptyslave *)kmalloc(sizeof(struct ptyslave), GFP_NORMAL);
		_ttydev_init(slave, &ptyslave_ops, &ptyslave_v_oprinter);
		slave->dv_driver = incref(&drv_self);
		TRY {
			/* Initialize objects. */
			master->fn_mode = S_IFCHR | 0644;
			slave->fn_mode  = S_IFCHR | 0644;
			master->fn_uid  = cred_getfsuid();
			master->fn_gid  = cred_getfsgid();
			slave->fn_uid   = master->fn_uid;
			slave->fn_gid   = master->fn_gid;
			ringbuffer_init(&slave->ps_obuf);

			/* Link the slave and master against each other. */
			awref_init(&slave->ps_master, master);
			awref_init(&master->pm_slave, slave);

			/* Load user-space provided initializers. */
			if (termp != NULL)
				memcpy(&slave->t_term.t_ios, termp, sizeof(struct termios));
			if (winp != NULL) {
				memcpy(&slave->ps_wsize, termp, sizeof(struct winsize));
			} else {
				slave->ps_wsize.ws_xpixel = slave->ps_wsize.ws_col = 80;
				slave->ps_wsize.ws_ypixel = slave->ps_wsize.ws_row = 25;
			}

			/* Register the 2 devices. */
			register_pty_pair(master, slave);
		} EXCEPT {
			decref_nokill(&drv_self);
			_ttydev_fini(slave);
			kfree(slave);
			RETHROW();
		}
	} EXCEPT {
		decref_nokill(&drv_self);
		_chrdev_fini(master);
		kfree(master);
		RETHROW();
	}
	*p_master = master; /* Inherit reference */
	*p_slave  = slave;  /* Inherit reference */
}





/************************************************************************/
/* openpty()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_OPENPTY
DEFINE_SYSCALL5(errno_t, openpty,
                NCX UNCHECKED fd_t *, amaster,
                NCX UNCHECKED fd_t *, aslave,
                NCX UNCHECKED char *, name,
                NCX UNCHECKED struct termios const *, termp,
                NCX UNCHECKED struct winsize const *, winp) {
	struct handle_install_data minstall;
	struct handle_install_data sinstall;
	fd_t mfd, sfd;
	validate_readable_opt(termp, sizeof(*termp));
	validate_readable_opt(winp, sizeof(*winp));
	validate_writable_opt(name, 1);
	validate_writable(aslave, sizeof(*aslave));
	validate_writable(amaster, sizeof(*amaster));

	/* Allocate handles. */
	mfd = handles_install_begin(&minstall);
	TRY {
		sfd = handles_install_begin(&sinstall);
		TRY {
			REF struct ptymaster *master;
			REF struct ptyslave *slave;

			/* Write handle values to user-space. */
			COMPILER_WRITE_BARRIER();
			*amaster = mfd;
			*aslave  = sfd;
			COMPILER_WRITE_BARRIER();

			/* Allocate the PTY device pair. */
			pty_alloc(&master, &slave, termp, winp);
			FINALLY_DECREF_UNLIKELY(master);
			FINALLY_DECREF_UNLIKELY(slave);
			if (name) {
				REF struct devdirent *devname;
				device_getname_lock_acquire(master);
				devname = incref(master->dv_dirent);
				device_getname_lock_release(master);
				FINALLY_DECREF_UNLIKELY(devname);
				sprintf(name, "/dev/%s", devname->dd_dirent.fd_name);
			}

			/* Install objects -- POINT OF NO RETURN */
			handles_install_commit(&minstall, master, IO_RDWR);
			handles_install_commit(&sinstall, slave, IO_RDWR);
		} EXCEPT {
			handles_install_rollback(&minstall);
			RETHROW();
		}
	} EXCEPT {
		handles_install_rollback(&sinstall);
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OPENPTY */

DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_PTY_C */
