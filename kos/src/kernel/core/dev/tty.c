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
#ifndef GUARD_KERNEL_SRC_DEV_TTY_C
#define GUARD_KERNEL_SRC_DEV_TTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/ansitty.h>
#include <dev/keyboard.h>
#include <dev/tty.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/async.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <termios.h> /* For ioctl() commands */

DECL_BEGIN

PRIVATE ssize_t LIBTERM_CC
tty_device_oprinter(struct terminal *__restrict term,
                    void const *__restrict src,
                    size_t num_bytes, iomode_t mode) {
	size_t result;
	struct tty_device *me;
	me = container_of(term, struct tty_device, t_term);
	/* Forward output text to the display data handler. */
	result = (*me->t_ohandle_write)(me->t_ohandle_ptr,
	                                src, num_bytes, mode);
	return (ssize_t)result;
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL tty_device_fini)(struct character_device *__restrict self) {
	struct tty_device *me;
	me = (struct tty_device *)self;
	/* Stop the associated forwarding thread (if one is running) */
	tty_device_stopfwd(me);
	if (me->t_ihandle_typ == HANDLE_TYPE_CHARACTERDEVICE &&
	    character_device_isakeyboard((struct character_device *)me->t_ihandle_ptr)) {
		struct keyboard_device *idev;
		idev = (struct keyboard_device *)me->t_ihandle_ptr;
		idev->kb_tty.cmpxch(me, NULL);
	}
	if (me->t_ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE &&
	    character_device_isanansitty((struct character_device *)me->t_ohandle_ptr)) {
		struct ansitty_device *odev;
		odev = (struct ansitty_device *)me->t_ohandle_ptr;
		/* Try to unbind this TTY from an ansi tty output device. */
		odev->at_tty.cmpxch(me, NULL);
	}
	/* Drop references from input/output handles. */
	(*handle_type_db.h_decref[me->t_ohandle_typ])(me->t_ohandle_ptr);
	(*handle_type_db.h_decref[me->t_ihandle_typ])(me->t_ihandle_ptr);
	ttybase_device_fini(self);
}



PUBLIC NONNULL((1)) void KCALL
tty_device_pollconnect(struct character_device *__restrict self, poll_mode_t what) THROWS(...) {
	struct tty_device *me;
	me = (struct tty_device *)self;
	if (what & POLLINMASK) {
		/* Poll the input buffer. */
		terminal_pollconnect_iread(&me->t_term);
	}
	if (what & POLLOUTMASK) {
		/* Poll the output buffer, as well as the underlying output driver for writing. */
#define connect_to_output_driver_write(cb) \
		(*handle_type_db.h_pollconnect[me->t_ohandle_typ])(me->t_ohandle_ptr, POLLOUTMASK)
		terminal_pollconnect_owrite(&me->t_term, connect_to_output_driver_write);
#undef connect_to_output_driver_write
	}
}

PUBLIC NONNULL((1)) poll_mode_t KCALL
tty_device_polltest(struct character_device *__restrict self, poll_mode_t what) THROWS(...) {
	poll_mode_t result = 0;
	struct tty_device *me;
	me = (struct tty_device *)self;
	if (what & POLLINMASK) {
		/* Poll the input buffer, as well as the underlying input driver for reading. */
		if (terminal_caniread(&me->t_term))
			result |= POLLINMASK;
	}
	if (what & POLLOUTMASK) {
		/* Poll the output buffer, as well as the underlying output driver for writing. */
		if (terminal_canowrite(&me->t_term,
		                       (*handle_type_db.h_polltest[me->t_ohandle_typ])(me->t_ohandle_ptr,
		                                                                       POLLOUTMASK) != 0))
			result |= POLLOUTMASK;
	}
	return result;
}

PRIVATE NONNULL((1, 2)) bool ASYNC_CALLBACK_CC
ttyfwd_poll(void *__restrict arg,
            void *__restrict UNUSED(cookie)) {
	struct tty_device *tty;
	poll_mode_t what;
	tty  = (struct tty_device *)arg;
	what = (*tty->t_ihandle_polltest)(tty->t_ihandle_ptr, POLLINMASK) & POLLINMASK;
	if (what)
		return true;
	(*tty->t_ihandle_pollconnect)(tty->t_ihandle_ptr, POLLINMASK);
	what = (*tty->t_ihandle_polltest)(tty->t_ihandle_ptr, POLLINMASK) & POLLINMASK;
	return what != 0;
}

PRIVATE NONNULL((1)) void ASYNC_CALLBACK_CC
ttyfwd_work(void *__restrict arg) {
	char buf[256];
	struct tty_device *tty;
	tty  = (struct tty_device *)arg;
	for (;;) {
		size_t count;
		TRY {
			count = (*tty->t_ihandle_read)(tty->t_ihandle_ptr, buf, sizeof(buf),
			                               IO_RDONLY | IO_NONBLOCK | IO_NODATAZERO);
		} EXCEPT {
			if (was_thrown(E_WOULDBLOCK))
				goto done;
			RETHROW();
		}
		if (!count)
			break;
		/* NOTE: Data also gets written with the `IO_NONBLOCK' flag set.
		 *       This has to be done because control characters still have
		 *       to be processed, even when canon buffers have filled up.
		 *       Otherwise, you would no longer be able to CTRL+C a hung
		 *       application after hammering away at your keyboard for a
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
	;
}


PRIVATE struct async_worker_callbacks const ttyfwd_cb = {
	/* .awc_poll = */ &ttyfwd_poll,
	/* .awc_work = */ &ttyfwd_work,
	/* .awc_test = */ NULL
};

/* Start/Stop forwarding input handle data on the given TTY
 * Note that for any given input handle, only a single TTY should
 * ever be allowed to process data. - Allowing multiple TTYs to do
 * so could result in weakly undefined behavior as it would no
 * longer be clear who should actually receive data, causing a
 * soft race condition with the potential of data being scattered
 * between readers, or some random reader getting all of the data.
 * @return: true:  The FWD thread was started/stopped
 * @return: false: The FWD thread was already running/halted */
PUBLIC bool KCALL
tty_device_startfwd(struct tty_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	bool result;
	result = register_async_worker(&ttyfwd_cb, self);
	return result;
}

PUBLIC NOBLOCK bool
NOTHROW(KCALL tty_device_stopfwd)(struct tty_device *__restrict self) {
	bool result;
	result = unregister_async_worker(&ttyfwd_cb, self);
	return result;
}



PRIVATE NONNULL((1)) syscall_slong_t KCALL
tty_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct tty_device *me;
	me = (struct tty_device *)self;
	switch (cmd) {

	/* TODO: KOS-specific ioctl()s to access the connected input/output devices. */

	default: {
		syscall_slong_t result;
		if (_IOC_ISKOS(cmd)) {
			if (_IOC_TYPE(cmd) == 'K') /* KBDIO_* */
				goto predict_input_device_command;
			if (_IOC_TYPE(cmd) == 'V') /* VIDEOIO_* */
				goto predict_output_device_command;
		} else {
			if (_IOC_TYPE(cmd) == 'K') /* <linux/kd.h> */
				goto predict_input_device_command;
			if (_IOC_TYPE(cmd) == 'V') /* <linux/vt.h> */
				goto predict_output_device_command;
		}
		result = ttybase_device_tryioctl(self, cmd, arg, mode);
		if (result != -EINVAL)
			return result;
		/* Try to have the connected output device handle the command. */
		TRY {
			result = (*handle_type_db.h_ioctl[me->t_ohandle_typ])(me->t_ohandle_ptr, cmd, arg, mode);
			return result;
		} EXCEPT {
			/* Rethrow everything that isn't
			 *    E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND:cmd */
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) ||
			    PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) != E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND ||
			    PERTASK_GET(this_exception_args.e_invalid_argument.ia_unknown_command.uc_command) != cmd)
				RETHROW();
		}
		/* Try to have the input device handle the command. */
		result = (*handle_type_db.h_ioctl[me->t_ihandle_typ])(me->t_ihandle_ptr, cmd, arg, mode);
		return result;
	}	break;
	}
	return 0;
	{
		syscall_slong_t result;
predict_input_device_command:
		TRY {
			return (*handle_type_db.h_ioctl[me->t_ihandle_typ])(me->t_ihandle_ptr, cmd, arg, mode);
		} EXCEPT {
			/* Rethrow everything that isn't
			 *    E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND:cmd */
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) ||
			    PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) != E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND ||
			    PERTASK_GET(this_exception_args.e_invalid_argument.ia_unknown_command.uc_command) != cmd)
				RETHROW();
		}
		result = ttybase_device_tryioctl(self, cmd, arg, mode);
		if (result != -EINVAL)
			return result;
		/* Try to have the output device handle the command. */
		return (*handle_type_db.h_ioctl[me->t_ohandle_typ])(me->t_ohandle_ptr, cmd, arg, mode);
	}
	{
		syscall_slong_t result;
predict_output_device_command:
		TRY {
			return (*handle_type_db.h_ioctl[me->t_ohandle_typ])(me->t_ohandle_ptr, cmd, arg, mode);
		} EXCEPT {
			/* Rethrow everything that isn't
			 *    E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND:cmd */
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) ||
			    PERTASK_GET(this_exception_args.e_invalid_argument.ia_context) != E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND ||
			    PERTASK_GET(this_exception_args.e_invalid_argument.ia_unknown_command.uc_command) != cmd)
				RETHROW();
		}
		result = ttybase_device_tryioctl(self, cmd, arg, mode);
		if (result != -EINVAL)
			return result;
		/* Try to have the input device handle the command. */
		return (*handle_type_db.h_ioctl[me->t_ihandle_typ])(me->t_ihandle_ptr, cmd, arg, mode);
	}
}


INTERN NONNULL((1, 2, 3, 4, 5)) REF struct vm_datablock *KCALL
tty_device_mmap(struct character_device *__restrict self,
                pos_t *__restrict pminoffset,
                pos_t *__restrict pnumbytes,
                REF struct path **__restrict pdatablock_fspath,
                REF struct directory_entry **__restrict pdatablock_fsname)
		THROWS(...) {
	struct tty_device *me;
	REF struct vm_datablock *result;
	me = (struct tty_device *)self;
	/* mmap() may be implemented by the display handle (e.g. for direct framebuffer access),
	 * so forward any request for mapping data into memory to it, and it alone. */
	result = (*handle_type_db.h_mmap[me->t_ohandle_typ])(me->t_ohandle_ptr,
	                                                     pminoffset,
	                                                     pnumbytes,
	                                                     pdatablock_fspath,
	                                                     pdatablock_fsname);
	return result;
}




/* Create (but don't register) a new TTY device that connects the two given
 * handles, such that character-based keyboard input is taken from `ihandle_ptr',
 * and ansi-compliant display output is written to `ohandle_ptr'
 * For this purpose, special handling is done for certain handles:
 *   - ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE && character_device_isanansitty(ohandle_ptr):
 *     `((struct ansitty_device *)ohandle_ptr)->at_tty' will be bound to the newly created tty device
 *     (s.a.. `return'), such that its output gets injected as `terminal_iwrite(&return->t_term, ...)'
 *     When the returned tty device is destroyed, this link gets severed automatically.
 * Upon success, the caller should:
 *   - Initialize `return->cd_name'
 *   - Register the device using one of:
 *      - `character_device_register(return, ...)'
 *      - `character_device_register_auto(return)' */
PUBLIC ATTR_RETNONNULL REF struct tty_device *KCALL
tty_device_alloc(uintptr_half_t ihandle_typ, void *ihandle_ptr,
                 uintptr_half_t ohandle_typ, void *ohandle_ptr)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	typedef size_t (KCALL *phandle_read_function_t)(void *__restrict ptr, USER CHECKED void *, size_t, iomode_t) /*THROWS(...)*/;
	typedef size_t (KCALL *phandle_write_function_t)(void *__restrict ptr, USER CHECKED void const *, size_t, iomode_t) /*THROWS(...)*/;
	typedef void (KCALL *phandle_pollconnect_function_t)(void *__restrict ptr, poll_mode_t) /*THROWS(...)*/;
	typedef poll_mode_t (KCALL *phandle_polltest_function_t)(void *__restrict ptr, poll_mode_t) /*THROWS(...)*/;
	REF struct tty_device *result;
	assert(ihandle_typ < HANDLE_TYPE_COUNT);
	assert(ohandle_typ < HANDLE_TYPE_COUNT);
	result = CHARACTER_DEVICE_ALLOC(struct tty_device);
	ttybase_device_cinit(result, &tty_device_oprinter);
	result->cd_type.ct_fini        = &tty_device_fini;
	result->cd_type.ct_write       = &ttybase_device_owrite;
	result->cd_type.ct_pollconnect = &tty_device_pollconnect;
	result->cd_type.ct_polltest    = &tty_device_polltest;
	result->cd_type.ct_ioctl       = &tty_device_ioctl;
	result->cd_type.ct_mmap        = &tty_device_mmap;
	result->t_ihandle_typ          = ihandle_typ;
	result->t_ohandle_typ          = ohandle_typ;
	result->t_ihandle_ptr          = ihandle_ptr;
	result->t_ohandle_ptr          = ohandle_ptr;
	result->t_ihandle_read         = handle_type_db.h_read[ihandle_typ];
	result->t_ihandle_pollconnect  = handle_type_db.h_pollconnect[ihandle_typ];
	result->t_ihandle_polltest     = handle_type_db.h_polltest[ihandle_typ];
	result->t_ohandle_write        = handle_type_db.h_write[ohandle_typ];
	/* Optimization to by-pass handle operators for known character devices. */
	if (ihandle_typ == HANDLE_TYPE_CHARACTERDEVICE) {
		struct character_device *cdev;
		cdev = (struct character_device *)ihandle_ptr;
		if (cdev->cd_type.ct_read)
			result->t_ihandle_read = (phandle_read_function_t)cdev->cd_type.ct_read;
		assert((cdev->cd_type.ct_pollconnect != NULL) ==
		       (cdev->cd_type.ct_polltest != NULL));
		if (cdev->cd_type.ct_pollconnect) {
			result->t_ihandle_pollconnect = (phandle_pollconnect_function_t)cdev->cd_type.ct_pollconnect;
			result->t_ihandle_polltest    = (phandle_polltest_function_t)cdev->cd_type.ct_polltest;
		}
	}
	if (ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE) {
		struct character_device *cdev;
		cdev = (struct character_device *)ohandle_ptr;
		if (cdev->cd_type.ct_write)
			result->t_ohandle_write = (phandle_write_function_t)cdev->cd_type.ct_write;
	}
	/* incref() input and output handles, since we keep references to each. */
	(*handle_type_db.h_incref[ihandle_typ])(ihandle_ptr);
	(*handle_type_db.h_incref[ohandle_typ])(ohandle_ptr);
	COMPILER_BARRIER();
	/* Special case: Always read characters from a connected
	 *               keyboard device, rather than reading key codes. */
	if (ihandle_typ == HANDLE_TYPE_CHARACTERDEVICE &&
	    character_device_isakeyboard((struct character_device *)ihandle_ptr)) {
		struct keyboard_device *idev;
		idev = (struct keyboard_device *)ihandle_ptr;
		COMPILER_BARRIER();
		/* When the output handle is an ansitty, then we must somehow register
		 * that ansitty within the keyboard, such that the keyboard can call
		 * into `ansitty_translate()' for the encoding of keyboard input into
		 * a CP-specific, encoded byte sequence! */
		if (ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE &&
		    character_device_isanansitty((struct character_device *)ohandle_ptr))
			idev->kb_tty.cmpxch(NULL, result);
	}
	/* Try to bind the new TTY device to an ANSI TTY output device.
	 * Note that a single output device may have multiple TTY drivers
	 * associated with it, as is the case for the CTRL+ALT+F{1-12} TTYs. */
	if (ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE &&
	    character_device_isanansitty((struct character_device *)ohandle_ptr)) {
		struct ansitty_device *odev;
		odev = (struct ansitty_device *)ohandle_ptr;
		odev->at_tty.cmpxch(NULL, result);
	}
	return result;
}





/************************************************************************/
/* mktty()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MKTTY
DEFINE_SYSCALL4(fd_t, mktty,
                USER UNCHECKED char const *, name,
                fd_t, keyboard, fd_t, display,
                syscall_ulong_t, reserved) {
	unsigned int result;
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
	if unlikely(namelen >= COMPILER_LENOF(((struct character_device *)0)->cd_name)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MKTTY_NAME,
		      namelen,
		      COMPILER_LENOF(((struct character_device *)0)->cd_name));
	}
	hkeyboard = handle_lookup((unsigned int)keyboard);
	TRY {
		hdisplay = handle_lookup((unsigned int)display);
		TRY {
			REF struct tty_device *tty;
			/* Ensure that the caller has permission to:
			 *   - Read from the keyboard
			 *   - Write from to the display
			 */
			if (!IO_CANREAD(hkeyboard.h_mode))
				THROW(E_INVALID_HANDLE_OPERATION,
				      (unsigned int)keyboard,
				      E_INVALID_HANDLE_OPERATION_READ,
				      hkeyboard.h_mode);
			if (!IO_CANWRITE(hdisplay.h_mode))
				THROW(E_INVALID_HANDLE_OPERATION,
				      (unsigned int)display,
				      E_INVALID_HANDLE_OPERATION_WRITE,
				      hdisplay.h_mode);
			/* Construct the new TTY device. */
			tty = tty_device_alloc(hkeyboard.h_type, hkeyboard.h_data,
			                       hdisplay.h_type, hdisplay.h_data);
			TRY {
				/* Assign a name to the new device. */
				memcpy(tty->cd_name, name, namelen, sizeof(char));
				assert(tty->cd_name[namelen] == '\0');
				/* Register the device, and add it to the devfs. */
				character_device_register_auto(tty);
				TRY {
					struct handle htty;
					/* Start forwarding input data. */
					tty_device_startfwd(tty);
					/* Store the new TTY into a handle. */
					htty.h_type = HANDLE_TYPE_CHARACTERDEVICE;
					htty.h_mode = IO_RDWR;
					htty.h_data = tty;
					result = handle_install(THIS_HANDLE_MANAGER, htty);
				} EXCEPT {
					character_device_unregister(tty);
					RETHROW();
				}
			} EXCEPT {
				decref_unlikely(tty);
				RETHROW();
			}
		} EXCEPT {
			decref(hdisplay);
			RETHROW();
		}
	} EXCEPT {
		decref(hkeyboard);
		RETHROW();
	}
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_MKTTY */

DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_TTY_C */
