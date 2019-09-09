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
#ifndef GUARD_KERNEL_SRC_DEV_PTY_C
#define GUARD_KERNEL_SRC_DEV_PTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <dev/pty.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/syscall.h>
#include <kernel/handle.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/io.h>
#include <sys/stat.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <termios.h>

#include <libterm/termio.h>

DECL_BEGIN


/* TODO: Completely re-write the PTY implementation! */

/* oprinter callback for PTY tty objects. */
PUBLIC ssize_t LIBTERM_CC
kernel_pty_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode) {
	struct pty_master *self;
	self = container_of(term, struct pty_master, t_term);
	return mode & IO_NONBLOCK
	       ? (ssize_t)ringbuffer_write_nonblock(&self->pm_obuf, src, num_bytes)
	       : (ssize_t)ringbuffer_write(&self->pm_obuf, src, num_bytes);
}









PRIVATE NONNULL((1)) syscall_slong_t KCALL
pty_master_ioctl(struct pty_master *__restrict self,
                 syscall_ulong_t cmd,
                 USER UNCHECKED void *arg,
                 iomode_t mode) {
	switch (cmd) {

	case TIOCGWINSZ:
	case _IOR(_IOC_TYPE(TIOCGWINSZ), _IOC_NR(TIOCGWINSZ), struct winsize):
		validate_writable(arg, sizeof(self->pm_size));
		COMPILER_WRITE_BARRIER();
		memcpy(arg, &self->pm_size, sizeof(self->pm_size));
		break;

	case TIOCSWINSZ:
	case _IOW(_IOC_TYPE(TIOCSWINSZ), _IOC_NR(TIOCSWINSZ), struct winsize):
		validate_readable(arg, sizeof(self->pm_size));
		COMPILER_READ_BARRIER();
		memcpy(&self->pm_size, arg, sizeof(self->pm_size));
		kernel_terminal_raise(&self->t_term, SIGWINCH);
		break;

	case TCSBRK:
		if (arg) {
			/* Wait for `self->pm_obuf' to become empty. */
			while (ATOMIC_READ(self->pm_obuf.rb_avail))
				task_yield();
			break;
		}
		break;

	case TCXONC:
		switch ((uintptr_t)arg) {
		case TCOOFF:
			ATOMIC_FETCHOR(self->t_term.t_ios.c_iflag, IXOFF);
			break;
		case TCOON:
			if (ATOMIC_FETCHAND(self->t_term.t_ios.c_iflag, ~IXOFF) & IXOFF) {
				sig_broadcast(&self->t_term.t_opend.lb_nful);
				sig_broadcast(&self->pm_obuf.rb_nempty);
			}
			break;
		case TCIOFF:
			ATOMIC_FETCHOR(self->t_term.t_ios.c_iflag, __IIOFF);
			break;
		case TCION:
			if (ATOMIC_FETCHAND(self->t_term.t_ios.c_iflag, ~__IIOFF) & __IIOFF)
				sig_broadcast(&self->t_term.t_ibuf.rb_nfull);
			break;
		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_TCXONC_COMMAND,
			      (uintptr_t)arg);
			break;
		}
		break;

	case TIOCOUTQ:
	case _IOR(_IOC_TYPE(TIOCOUTQ), _IOC_NR(TIOCOUTQ), int):
		validate_writable(arg, sizeof(unsigned int));
		*(USER CHECKED unsigned int *)arg = (unsigned int)(ATOMIC_READ(self->t_term.t_opend.lb_line.lc_size) +
		                                                   ATOMIC_READ(self->pm_obuf.rb_avail));
		break;
#if __SIZEOF_SIZE_T__ != __SIZEOF_INT__
	case _IOR(_IOC_TYPE(TIOCOUTQ), _IOC_NR(TIOCOUTQ), size_t):
		validate_writable(arg, sizeof(size_t));
		*(USER CHECKED size_t *)arg = ATOMIC_READ(self->t_term.t_opend.lb_line.lc_size) +
		                              ATOMIC_READ(self->pm_obuf.rb_avail);
		break;
#endif /* __SIZEOF_SIZE_T__ != __SIZEOF_INT__ */

	default:
		return ttybase_device_ioctl(self, cmd, arg, mode);
		break;
	}
	return 0;
}





PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pty_master_fini)(struct pty_master *__restrict self) {
	ringbuffer_fini(&self->pm_obuf);
	ttybase_device_fini(self);
}
PRIVATE NONNULL((1)) size_t KCALL
pty_master_read(struct pty_master *__restrict self,
                USER CHECKED void *dst,
                size_t num_bytes, iomode_t mode) {
	size_t result;
	result = mode & IO_NONBLOCK
	         ? ringbuffer_read_nonblock(&self->pm_obuf, dst, num_bytes)
	         : ringbuffer_read(&self->pm_obuf, dst, num_bytes);
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
pty_master_write(struct pty_master *__restrict self,
                 USER CHECKED void const *src,
                 size_t num_bytes, iomode_t mode) {
	ssize_t result;
	result = terminal_iwrite(&self->t_term, src, num_bytes, mode);
	assert((size_t)result <= num_bytes);
	return (size_t)result;
}

PRIVATE NONNULL((1)) void KCALL
pty_master_stat(struct pty_master *__restrict self,
                USER CHECKED struct stat *result) {
	size_t avail;
	avail              = ATOMIC_READ(self->pm_obuf.rb_avail);
	result->st_size    = avail;
	result->st_blksize = S_BLKSIZE;
	result->st_blocks  = CEILDIV(avail, S_BLKSIZE);
}
PRIVATE NONNULL((1)) poll_mode_t KCALL
pty_master_poll(struct pty_master *__restrict self,
                poll_mode_t what){
	poll_mode_t result = 0;
	if (what & POLLIN)
		result |= ringbuffer_poll(&self->pm_obuf, POLLIN);
	if (what & POLLOUT)
		result |= ringbuffer_poll(&self->t_term.t_ibuf, POLLOUT);
	return result;
}



PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pty_slave_fini)(struct pty_slave *__restrict self) {
	struct pty_master *master;
	master = self->ps_master;
	/* Close all of the master's buffers. */
	ringbuffer_close(&master->pm_obuf);
	ringbuffer_close(&master->t_term.t_ibuf);
	linebuffer_close(&master->t_term.t_opend);
	linebuffer_close(&master->t_term.t_ipend);
	linebuffer_close(&master->t_term.t_canon);
	/* Drop our reference to the master.
	 * NOTE: The controlling application is likely to still be
	 *       holding a reference, so this decref is unlikely. */
	decref_unlikely(master);
}


PRIVATE NONNULL((1)) size_t KCALL
pty_slave_read(struct pty_slave *__restrict self,
               USER CHECKED void *dst,
               size_t num_bytes, iomode_t mode) {
	size_t result;
#if 1
	assert(character_device_isattybase(self->ps_master));
	result = terminal_iread(&self->ps_master->t_term, dst, num_bytes, mode);
#else
	result = ttybase_iread(self->ps_master, dst, num_bytes, mode);
#endif
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
pty_slave_write(struct pty_slave *__restrict self,
                USER CHECKED void const *src,
                size_t num_bytes, iomode_t mode) {
	ssize_t result;
#if 1
	assert(character_device_isattybase(self->ps_master));
	result = terminal_owrite(&self->ps_master->t_term, src, num_bytes, mode);
#else
	result = ttybase_owrite(self->ps_master, src, num_bytes, mode);
#endif
	assert((size_t)result <= num_bytes);
	return (size_t)result;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
pty_slave_ioctl(struct pty_slave *__restrict self,
                syscall_ulong_t cmd,
                USER UNCHECKED void *arg,
                iomode_t mode) {
	return pty_master_ioctl(self->ps_master,
	                        cmd,
	                        arg,
	                        mode);
}

PRIVATE NONNULL((1)) void KCALL
pty_slave_stat(struct pty_slave *__restrict self,
               USER CHECKED struct stat *result) {
	size_t avail;
	avail              = ATOMIC_READ(self->ps_master->t_term.t_ibuf.rb_avail);
	result->st_size    = avail;
	result->st_blksize = S_BLKSIZE;
	result->st_blocks  = CEILDIV(avail, S_BLKSIZE);
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
pty_slave_poll(struct pty_slave *__restrict self,
               poll_mode_t what){
	poll_mode_t result = 0;
	struct pty_master *master;
	master = self->ps_master;
	if (what & POLLIN)
		result |= ringbuffer_poll(&master->t_term.t_ibuf, POLLIN);
	if (what & POLLOUT)
		result |= ringbuffer_poll(&master->pm_obuf, POLLOUT);
	return result;
}



/* Allocate a new PTY master/slave
 * NOTE: The caller must still register the devices in devfs,
 *       perferably using the pty_register() function. */
PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC REF struct pty_master *
KCALL pty_master_alloc(void) THROWS(E_BADALLOC) {
	REF struct pty_master *result;
	result = CHARACTER_DEVICE_ALLOC(struct pty_master);
	ttybase_device_cinit(result, &kernel_pty_oprinter);
	result->cd_type.ct_fini  = (void /*NOTHROW*/ (KCALL *)(struct character_device * __restrict))&pty_master_fini;
	result->cd_type.ct_read  = (size_t(KCALL *)(struct character_device * __restrict, USER CHECKED void *, size_t, iomode_t))&pty_master_read;
	result->cd_type.ct_write = (size_t(KCALL *)(struct character_device * __restrict, USER CHECKED void const *, size_t, iomode_t))&pty_master_write;
	result->cd_type.ct_ioctl = (syscall_slong_t(KCALL *)(struct character_device * __restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&pty_master_ioctl;
	result->cd_type.ct_stat  = (void(KCALL *)(struct character_device * __restrict, USER CHECKED struct stat *))&pty_master_stat;
	result->cd_type.ct_poll  = (poll_mode_t(KCALL *)(struct character_device * __restrict, poll_mode_t))&pty_master_poll;
	ringbuffer_cinit(&result->pm_obuf);
	return result;
}
PUBLIC WUNUSED ATTR_RETNONNULL ATTR_MALLOC NONNULL((1)) REF struct pty_slave *
KCALL pty_slave_alloc(struct pty_master *__restrict master) THROWS(E_BADALLOC) {
	REF struct pty_slave *result;
	result                   = CHARACTER_DEVICE_ALLOC(struct pty_slave);
	result->ps_master        = (REF struct pty_master *)incref(master);
	result->cd_type.ct_fini  = (void /*NOTHROW*/ (KCALL *)(struct character_device * __restrict))&pty_slave_fini;
	result->cd_type.ct_read  = (size_t(KCALL *)(struct character_device * __restrict, USER CHECKED void *, size_t, iomode_t))&pty_slave_read;
	result->cd_type.ct_write = (size_t(KCALL *)(struct character_device * __restrict, USER CHECKED void const *, size_t, iomode_t))&pty_slave_write;
	result->cd_type.ct_ioctl = (syscall_slong_t(KCALL *)(struct character_device * __restrict, syscall_ulong_t, USER UNCHECKED void *, iomode_t))&pty_slave_ioctl;
	result->cd_type.ct_stat  = (void(KCALL *)(struct character_device * __restrict, USER CHECKED struct stat *))&pty_slave_stat;
	result->cd_type.ct_poll  = (poll_mode_t(KCALL *)(struct character_device * __restrict, poll_mode_t))&pty_slave_poll;
	return result;
}


DEFINE_SYSCALL5(errno_t,openpty,
                USER UNCHECKED fd_t *,amaster,
                USER UNCHECKED fd_t *,aslave,
                USER UNCHECKED char *,name,
                USER UNCHECKED struct termios const *,termp,
                USER UNCHECKED struct winsize const *,winp) {
	REF struct pty_master *master;
	REF struct pty_slave *slave;
	validate_readable_opt(termp, sizeof(*termp));
	validate_readable_opt(winp, sizeof(*winp));
	validate_writable_opt(name, 1);
	validate_writable(aslave, sizeof(*aslave));
	validate_writable(amaster, sizeof(*amaster));
	/* Allocate a new PTY master. */
	master = pty_master_alloc();
	FINALLY_DECREF_UNLIKELY(master);
	/* Initialize the master. */
	if (termp) {
		memcpy(&master->t_term.t_ios, termp, sizeof(*termp));
	} else {
		master->t_term.t_ios.c_iflag = (ICRNL | BRKINT | IXON | IMAXBEL | IUTF8);
		master->t_term.t_ios.c_oflag = (OPOST);
		master->t_term.t_ios.c_lflag = (ISIG | ICANON | ECHO | ECHOE | ECHOK |
		                                TOSTOP | ECHOCTL | ECHOKE | IEXTEN);
		master->t_term.t_ios.c_cflag = (CREAD);
#define CTRL_CODE(x) ((x)-64)                            /* ^x */
		master->t_term.t_ios.c_cc[VMIN]     = 1;               /*  */
		master->t_term.t_ios.c_cc[VEOF]     = CTRL_CODE('D');  /* ^D. */
		master->t_term.t_ios.c_cc[VERASE]   = '\b';
		master->t_term.t_ios.c_cc[VINTR]    = CTRL_CODE('C');  /* ^C. */
		master->t_term.t_ios.c_cc[VKILL]    = CTRL_CODE('U');  /* ^U. */
		master->t_term.t_ios.c_cc[VQUIT]    = CTRL_CODE('\\'); /* ^\ */
		master->t_term.t_ios.c_cc[VSTART]   = CTRL_CODE('Q');  /* ^Q. */
		master->t_term.t_ios.c_cc[VSTOP]    = CTRL_CODE('S');  /* ^S. */
		master->t_term.t_ios.c_cc[VSUSP]    = CTRL_CODE('Z');  /* ^Z. */
		master->t_term.t_ios.c_cc[VWERASE]  = CTRL_CODE('W');  /* ^W. */
		master->t_term.t_ios.c_cc[VLNEXT]   = CTRL_CODE('V');  /* ^V. */
		master->t_term.t_ios.c_cc[VREPRINT] = CTRL_CODE('R');  /* ^R. */
#undef CTRL_CODE
	}
	if (winp) {
		memcpy(&master->pm_size, winp, sizeof(*winp));
	} else {
		master->pm_size.ws_xpixel = master->pm_size.ws_col = 80;
		master->pm_size.ws_ypixel = master->pm_size.ws_row = 25;
	}
	/* Allocate the slave. */
	slave = pty_slave_alloc(master);
	FINALLY_DECREF_UNLIKELY(slave);
	/* Register the master/slave pair. */
	pty_register(master, slave);
	TRY {
		struct handle temp;
		fd_t fdmaster, fdslave;
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
				/* Save the master/slave handlers into the user-space pointers. */
				ATOMIC_WRITE(*amaster, fdmaster);
				ATOMIC_WRITE(*aslave, fdslave);
			} EXCEPT {
				handle_close(THIS_HANDLE_MANAGER, fdslave);
				RETHROW();
			}
		} EXCEPT {
			handle_close(THIS_HANDLE_MANAGER, fdmaster);
			RETHROW();
		}
	} EXCEPT {
		character_device_unregister(master);
		character_device_unregister(slave);
		RETHROW();
	}
	return -EOK;
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_PTY_C */
