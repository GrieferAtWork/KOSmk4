/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_MKTTY_C
#define GUARD_KERNEL_SRC_DEV_MKTTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/ansitty.h>
#include <dev/keyboard.h>
#include <dev/mktty.h>
#include <dev/tty.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/fs/devfs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/async.h>
#include <sched/cred.h>
#include <sched/pertask.h>

#include <kos/aref.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/kernel/handle.h>
#include <sys/ioctl.h>
#include <sys/mkdev.h>

#include <errno.h>
#include <stddef.h>
#include <string.h>

#include <libterm/api.h>
#include <libterm/termio.h>

DECL_BEGIN

PRIVATE ssize_t LIBTERM_CC
mkttydev_v_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode) {
	size_t result;
	struct mkttydev *me;
	me = container_of(term, struct mkttydev, t_term);
	/* Forward output text to the display data handler. */
	result = (*me->mtd_ohandle_write)(me->mtd_ohandle_ptr,
	                                src, num_bytes, mode);
	return (ssize_t)result;
}



PRIVATE NONNULL((1)) void KCALL
mkttydev_v_pollconnect(struct mfile *__restrict self,
                       poll_mode_t what) THROWS(...) {
	struct mkttydev *me = mfile_asmktty(self);
	if (what & POLLINMASK) {
		/* Poll the input buffer. */
		terminal_pollconnect_iread(&me->t_term);
	}
	if (what & POLLOUTMASK) {
		/* Poll the output buffer, as well as the underlying output driver for writing. */
#define connect_to_output_driver_write(cb) \
		(*handle_type_db.h_pollconnect[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr, POLLOUTMASK)
		terminal_pollconnect_owrite(&me->t_term, connect_to_output_driver_write);
#undef connect_to_output_driver_write
	}
}


PUBLIC NONNULL((1)) poll_mode_t KCALL
mkttydev_v_polltest(struct mfile *__restrict self,
                    poll_mode_t what) THROWS(...) {
	poll_mode_t result  = 0;
	struct mkttydev *me = mfile_asmktty(self);
	if (what & POLLINMASK) {
		/* Poll the input buffer, as well as the underlying input driver for reading. */
		if (terminal_caniread(&me->t_term))
			result |= POLLINMASK;
	}
	if (what & POLLOUTMASK) {
		/* Poll the output buffer, as well as the underlying output driver for writing. */
		if (terminal_canowrite(&me->t_term,
		                       (*handle_type_db.h_polltest[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr,
		                                                                         POLLOUTMASK) != 0))
			result |= POLLOUTMASK;
	}
	return result;
}

PRIVATE NONNULL((1)) ktime_t FCALL
ttyfwd_connect(void *__restrict arg) {
	struct mkttydev *tty;
	tty = (struct mkttydev *)arg;
	(*tty->mtd_ihandle_pollconnect)(tty->mtd_ihandle_ptr, POLLINMASK);
	return KTIME_INFINITE;
}

PRIVATE NONNULL((1)) bool FCALL
ttyfwd_test(void *__restrict arg) {
	struct mkttydev *tty;
	poll_mode_t what;
	tty  = (struct mkttydev *)arg;
	what = (*tty->mtd_ihandle_polltest)(tty->mtd_ihandle_ptr, POLLINMASK) & POLLINMASK;
	return what != 0;
}

PRIVATE NONNULL((1)) unsigned int FCALL
ttyfwd_work(void *__restrict arg) {
	char buf[256];
	struct mkttydev *tty;
	tty  = (struct mkttydev *)arg;
	for (;;) {
		size_t count;
		TRY {
			count = (*tty->mtd_ihandle_read)(tty->mtd_ihandle_ptr, buf, sizeof(buf),
			                                 IO_RDONLY | IO_NONBLOCK | IO_NODATAZERO);
		} EXCEPT {
			if (was_thrown(E_WOULDBLOCK))
				goto done;
			RETHROW();
		}
		if (!count)
			break;
		/* NOTE: Data also gets written  with the `IO_NONBLOCK' flag  set.
		 *       This has to be done because control characters still have
		 *       to be processed, even when canon buffers have filled  up.
		 *       Otherwise, you would no longer  be able to CTRL+C a  hung
		 *       application after hammering away  at your keyboard for  a
		 *       couple of minutes. */
		TRY {
			terminal_iwrite(&tty->t_term, buf, count,
			                IO_WRONLY | IO_NONBLOCK | IO_NODATAZERO);
		} EXCEPT {
			if (!was_thrown(E_WOULDBLOCK))
				RETHROW();
		}
	}
done:
	return ASYNC_RESUME;
}


PRIVATE struct async_worker_ops const ttyfwd_cb = {
	.awo_async   = ASYNC_WORKER_OPS_INIT_BASE,
	.awo_connect = &ttyfwd_connect,
	.awo_test    = &ttyfwd_test,
	.awo_work    = &ttyfwd_work,
};

/* Start/Stop forwarding input handle data on the given TTY.
 *
 * Note that for any given input handle, only a single TTY  should
 * ever be allowed to process data. - Allowing multiple TTYs to do
 * so could result  in weakly  undefined behavior as  it would  no
 * longer  be clear  who should  actually receive  data, causing a
 * soft race condition with the potential of data being  scattered
 * between readers, or some random reader getting all of the data.
 *
 * @return: true:  The FWD thread was started/stopped
 * @return: false: The FWD thread was already running/halted */
PUBLIC NONNULL((1)) bool KCALL
mkttydev_startfwd(struct mkttydev *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	bool result;
	result = register_async_worker(&ttyfwd_cb, self);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL mkttydev_stopfwd)(struct mkttydev *__restrict self) {
	bool result;
	result = unregister_async_worker(&ttyfwd_cb, self);
	return result;
}



PRIVATE NONNULL((1)) syscall_slong_t KCALL
mkttydev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                 NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct mkttydev *me = mfile_asmktty(self);
	switch (cmd) {

	/* TODO: KOS-specific ioctl()s to access the connected input/output devices. */

	default: {
		syscall_slong_t result;
		if (_IOC_TYPE(cmd) == 'K') /* _IOC_ISKOS(cmd) ? KBD_IOC_* : <linux/kd.h> */
			goto predict_input_device_command;
		if (_IOC_TYPE(cmd) == 'V') /* _IOC_ISKOS(cmd) ? VID_IOC_* : <linux/vt.h> */
			goto predict_output_device_command;
		result = _ttydev_tryioctl(self, cmd, arg, mode);
		if (result != -EINVAL)
			return result;
		/* Try to have the connected output device handle the command. */
		TRY {
			result = (*handle_type_db.h_ioctl[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr, cmd, arg, mode);
			return result;
		} EXCEPT {
			/* Rethrow everything that isn't
			 *    E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND:cmd */
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) ||
			    PERTASK_NE(this_exception_args.e_invalid_argument.ia_context, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) ||
			    PERTASK_NE(this_exception_args.e_invalid_argument.ia_unknown_command.uc_command, cmd))
				RETHROW();
		}
		/* Try to have the input device handle the command. */
		result = (*handle_type_db.h_ioctl[me->mtd_ihandle_typ])(me->mtd_ihandle_ptr, cmd, arg, mode);
		return result;
	}	break;
	}
	return 0;
	{
		syscall_slong_t result;
predict_input_device_command:
		TRY {
			return (*handle_type_db.h_ioctl[me->mtd_ihandle_typ])(me->mtd_ihandle_ptr, cmd, arg, mode);
		} EXCEPT {
			/* Rethrow everything that isn't
			 *    E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND:cmd */
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) ||
			    PERTASK_NE(this_exception_args.e_invalid_argument.ia_context, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) ||
			    PERTASK_NE(this_exception_args.e_invalid_argument.ia_unknown_command.uc_command, cmd))
				RETHROW();
		}
		result = _ttydev_tryioctl(self, cmd, arg, mode);
		if (result != -EINVAL)
			return result;
		/* Try to have the output device handle the command. */
		return (*handle_type_db.h_ioctl[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr, cmd, arg, mode);
	}
	{
		syscall_slong_t result;
predict_output_device_command:
		TRY {
			return (*handle_type_db.h_ioctl[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr, cmd, arg, mode);
		} EXCEPT {
			/* Rethrow everything that isn't
			 *    E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND:cmd */
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) ||
			    PERTASK_NE(this_exception_args.e_invalid_argument.ia_context, E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND) ||
			    PERTASK_NE(this_exception_args.e_invalid_argument.ia_unknown_command.uc_command, cmd))
				RETHROW();
		}
		result = _ttydev_tryioctl(self, cmd, arg, mode);
		if (result != -EINVAL)
			return result;
		/* Try to have the input device handle the command. */
		return (*handle_type_db.h_ioctl[me->mtd_ihandle_typ])(me->mtd_ihandle_ptr, cmd, arg, mode);
	}
}


PRIVATE NONNULL((1, 2)) void KCALL
mkttydev_v_mmap(struct mfile *__restrict self,
                struct handle_mmap_info *__restrict info)
		THROWS(...) {
	struct mkttydev *me = mfile_asmktty(self);

	/* mmap() may be implemented by the display handle (e.g. for direct framebuffer access),
	 * so  forward  any  request  for  mapping  data  into  memory  to  it,  and  it  alone. */
	(*handle_type_db.h_mmap[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr, info);
}




PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mkttydev_v_destroy)(struct mfile *__restrict self) {
	struct mkttydev *me = mfile_asmktty(self);

	/* Stop the associated forwarding thread (if one is running) */
	mkttydev_stopfwd(me);

	if (me->mtd_ohandle_typ == HANDLE_TYPE_MFILE &&
	    mfile_isansitty((struct mfile *)me->mtd_ohandle_ptr)) {
		struct ansittydev *atty = mfile_asansitty((struct mfile *)me->mtd_ohandle_ptr);
		if (me->mtd_ihandle_typ == HANDLE_TYPE_MFILE && mfile_iskbd((struct mfile *)me->mtd_ihandle_ptr)) {
			struct kbddev *kbd = mfile_askbd((struct mfile *)me->mtd_ihandle_ptr);
			awref_cmpxch(&kbd->kd_tty, me, NULL);
		}
		awref_cmpxch(&atty->at_tty, me, NULL);
	}

	/* Drop references from input/output handles. */
	(*handle_type_db.h_decref[me->mtd_ohandle_typ])(me->mtd_ohandle_ptr);
	(*handle_type_db.h_decref[me->mtd_ihandle_typ])(me->mtd_ihandle_ptr);

	/* Destroy the underlying TTY */
	ttydev_v_destroy(self);
}


typedef size_t (KCALL *phandle_read_function_t)(void *__restrict ptr, NCX void *, size_t, iomode_t) /*THROWS(...)*/;
typedef size_t (KCALL *phandle_write_function_t)(void *__restrict ptr, NCX void const *, size_t, iomode_t) /*THROWS(...)*/;
typedef void (KCALL *phandle_pollconnect_function_t)(void *__restrict ptr, poll_mode_t) /*THROWS(...)*/;
typedef poll_mode_t (KCALL *phandle_polltest_function_t)(void *__restrict ptr, poll_mode_t) /*THROWS(...)*/;


PRIVATE struct mfile_stream_ops const mktty_stream_ops = {
	.mso_open        = &ttydev_v_open,
	.mso_read        = &ttydev_v_read,
	.mso_write       = &ttydev_v_write,
	.mso_mmap        = &mkttydev_v_mmap,
	.mso_stat        = &ttydev_v_stat,
	.mso_pollconnect = &mkttydev_v_pollconnect,
	.mso_polltest    = &mkttydev_v_polltest,
	.mso_ioctl       = &mkttydev_v_ioctl,
	.mso_tryas       = &ttydev_v_tryas,
};

/* Operators used by `struct mkttydev' */
PUBLIC_CONST struct ttydev_ops const mkttydev_ops = {{{{{
	.no_file = {
		.mo_destroy = &mkttydev_v_destroy,
		.mo_changed = &ttydev_v_changed,
		.mo_stream  = &mktty_stream_ops,
	},
	.no_wrattr = &ttydev_v_wrattr,
}}}}};


/* Create a new TTY device that connects the two given handles, such that
 * character-based keyboard input is taken from `ihandle_ptr', and  ansi-
 * compliant display output is written to `ohandle_ptr'.
 *
 * NOTE: The TTY is created with data forwarding disabled. */
PUBLIC ATTR_RETNONNULL REF struct mkttydev *KCALL
mkttydev_new(uintptr_half_t ihandle_typ, void *ihandle_ptr,
             uintptr_half_t ohandle_typ, void *ohandle_ptr,
             NCX char const *name, size_t namelen)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	struct mkttydev *result;
	result = (struct mkttydev *)kmalloc(sizeof(struct mkttydev), GFP_NORMAL);
	_ttydev_init(result, &mkttydev_ops, &mkttydev_v_oprinter);
	result->fn_mode   = S_IFCHR | 0644;
	result->fn_uid    = cred_getfsuid();
	result->fn_gid    = cred_getfsgid();
	result->dv_driver = incref(&drv_self);

	/* Fill in mkttydev-specific fields. */
	result->mtd_ihandle_typ = ihandle_typ;
	result->mtd_ohandle_typ = ohandle_typ;
	result->mtd_ihandle_ptr = ihandle_ptr;
	result->mtd_ohandle_ptr = ohandle_ptr;

	/* Fill in short-circuit handle operators. */
	result->mtd_ihandle_read        = handle_type_db.h_read[ihandle_typ];
	result->mtd_ihandle_pollconnect = handle_type_db.h_pollconnect[ihandle_typ];
	result->mtd_ihandle_polltest    = handle_type_db.h_polltest[ihandle_typ];
	result->mtd_ohandle_write       = handle_type_db.h_write[ohandle_typ];

	/* Optimize handle operators for MFILE-derived objects. */
	if (ihandle_typ == HANDLE_TYPE_MFILE) {
		struct mfile *in;
		struct mfile_stream_ops const *stream;
		in     = (struct mfile *)ihandle_ptr;
		stream = in->mf_ops->mo_stream;
		if (stream != NULL) {
			if (stream->mso_read != NULL)
				result->mtd_ihandle_read = (phandle_read_function_t)stream->mso_read;
			if (stream->mso_pollconnect != NULL)
				result->mtd_ihandle_pollconnect = (phandle_pollconnect_function_t)stream->mso_pollconnect;
			if (stream->mso_polltest != NULL)
				result->mtd_ihandle_polltest = (phandle_polltest_function_t)stream->mso_polltest;
		}
	}
	if (ohandle_typ == HANDLE_TYPE_MFILE) {
		struct mfile *out;
		struct mfile_stream_ops const *stream;
		out    = (struct mfile *)ohandle_ptr;
		stream = out->mf_ops->mo_stream;
		if (stream != NULL) {
			if (stream->mso_write != NULL)
				result->mtd_ohandle_write = (phandle_write_function_t)stream->mso_write;
		}
	}

	/* incref() input and output handles, since we keep references to each. */
	(*handle_type_db.h_incref[ihandle_typ])(ihandle_ptr);
	(*handle_type_db.h_incref[ohandle_typ])(ohandle_ptr);

	TRY {
		/* Register the device */
		device_registerf(result, makedev(MKDEV_MAJOR_AUTO, 0),
		                 "%$s", namelen, name);
	} EXCEPT {
		(*handle_type_db.h_decref[ihandle_typ])(ihandle_ptr);
		(*handle_type_db.h_decref[ohandle_typ])(ohandle_ptr);
		decref_unlikely(&drv_self);
		_ttydev_fini(result);
		kfree(result);
		RETHROW();
	}

	/* Try to bind  the new  TTY device to  an ANSI  TTY output  device.
	 * Note  that a single  output device may  have multiple TTY drivers
	 * associated with it, as is the case for the CTRL+ALT+F{1-12} TTYs. */
	if (ohandle_typ == HANDLE_TYPE_MFILE && mfile_isansitty((struct mfile *)ohandle_ptr)) {
		struct ansittydev *atty = mfile_asansitty((struct mfile *)ohandle_ptr);

		/* When the output handle is an ansitty, then we must somehow register
		 * that ansitty within the keyboard,  such that the keyboard can  call
		 * into `ansitty_translate()' for the encoding of keyboard input  into
		 * a CP-specific, encoded byte sequence! */
		if (ihandle_typ == HANDLE_TYPE_MFILE && mfile_iskbd((struct mfile *)ihandle_ptr)) {
			struct kbddev *kbd = mfile_askbd((struct mfile *)ihandle_ptr);
			awref_cmpxch(&kbd->kd_tty, NULL, result);
		}
		awref_cmpxch(&atty->at_tty, NULL, result);
	}
	return result;
}





#ifndef MKTTY_NAME_MAXLEN
#define MKTTY_NAME_MAXLEN 64
#endif /* !MKTTY_NAME_MAXLEN */

/************************************************************************/
/* mktty()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MKTTY
DEFINE_SYSCALL4(fd_t, mktty,
                NCX UNCHECKED char const *, name,
                fd_t, keyboard, fd_t, display,
                syscall_ulong_t, reserved) {
	fd_t result;
	struct handle_install_data install;
	REF struct mkttydev *tty;
	struct handle hkeyboard;
	struct handle hdisplay;
	size_t namelen;
	validate_readable(name, 1);
	if unlikely(reserved != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_MKTTY_FLAGS,
		      reserved);
	}
	namelen = strlen(name);
	if unlikely(namelen >= MKTTY_NAME_MAXLEN) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME,
		      namelen,
		      MKTTY_NAME_MAXLEN);
	}

	result = handles_install_begin(&install);
	TRY {
		{
			hkeyboard = handles_lookup(keyboard);
			RAII_FINALLY { decref_unlikely(hkeyboard); };
			hdisplay = handles_lookup(display);
			RAII_FINALLY { decref_unlikely(hdisplay); };
			/* Ensure that the caller has permission to:
			 *   - Read from the keyboard
			 *   - Write from to the display
			 */
			if unlikely(!IO_CANREAD(hkeyboard.h_mode)) {
				THROW(E_INVALID_HANDLE_OPERATION, (syscall_slong_t)keyboard,
				      E_INVALID_HANDLE_OPERATION_READ, hkeyboard.h_mode);
			}
			if unlikely(!IO_CANWRITE(hdisplay.h_mode)) {
				THROW(E_INVALID_HANDLE_OPERATION, (syscall_slong_t)display,
				      E_INVALID_HANDLE_OPERATION_WRITE, hdisplay.h_mode);
			}

			/* Construct the new TTY device. */
			tty = mkttydev_new(hkeyboard.h_type, hkeyboard.h_data,
			                   hdisplay.h_type, hdisplay.h_data,
			                   name, namelen);
		}
		FINALLY_DECREF_UNLIKELY(tty);

		/* Start forwarding input data. */
		TRY {
			mkttydev_startfwd(tty);
		} EXCEPT {
			device_delete(tty);
			RETHROW();
		}

		/* Install the tty. */
		handles_install_commit(&install, tty, IO_RDWR);
	} EXCEPT {
		handles_install_rollback(&install);
		RETHROW();
	}
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_MKTTY */

DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_MKTTY_C */
