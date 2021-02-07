/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEV_ANSITTY_C
#define GUARD_KERNEL_SRC_DEV_ANSITTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/ansitty.h>
#include <dev/keyboard.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/user.h>

#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>
#include <sys/ioctl.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <termios.h>

#include <libansitty/ansitty.h>

DECL_BEGIN

PUBLIC NONNULL((1)) size_t KCALL
ansitty_device_write(struct character_device *__restrict self,
                     USER CHECKED void const *src,
                     size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	struct ansitty_device *me = (struct ansitty_device *)self;
#if !defined(NDEBUG) && 0
	printk(KERN_DEBUG "[ansitty_device_write] %$q\n", num_bytes, src);
#endif
	return (size_t)ansitty_printer(&me->at_ansi, (char const *)src, num_bytes);
}

PUBLIC NONNULL((1)) syscall_slong_t KCALL
ansitty_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t UNUSED(mode)) THROWS(...) {
	struct ansitty_device *me = (struct ansitty_device *)self;
	switch (cmd) {

	case TIOCGWINSZ:
	case _IOR(_IOC_TYPE(TIOCGWINSZ), _IOC_NR(TIOCGWINSZ), struct winsize): {
		struct winsize ws;
		ansitty_coord_t sxy[2];
		validate_writable(arg, sizeof(struct winsize));
		/* These 2 operators are emulated by libansitty and should _always_ be present. */
		assert(me->at_ansi.at_ops.ato_getcursor);
		assert(me->at_ansi.at_ops.ato_setcursor);
		/* Make use of the fact that the cursor position is clamped to the display bounds.
		 * Note that libansitty makes use of the same fact to determine the window size
		 * whenever it needs to know that value. */
		if (me->at_ansi.at_ops.ato_getsize) {
			(*me->at_ansi.at_ops.ato_getsize)(&me->at_ansi, sxy);
		} else {
			ansitty_coord_t xy[2];
			(*me->at_ansi.at_ops.ato_getcursor)(&me->at_ansi, xy);
			(*me->at_ansi.at_ops.ato_setcursor)(&me->at_ansi, (ansitty_coord_t)-1, (ansitty_coord_t)-1, false);
			(*me->at_ansi.at_ops.ato_getcursor)(&me->at_ansi, sxy);
			(*me->at_ansi.at_ops.ato_setcursor)(&me->at_ansi, xy[0], xy[1], false);
			/* Because the cursor coords are clamped to the max valid values, the
			 * actual display size is described by the max valid coords +1 each. */
			++sxy[0];
			++sxy[1];
		}
		if (sxy[0] == 1 && sxy[1] == 1) {
			/* If we couldn't get anything useful, default to some sane values. */
			sxy[0] = 80;
			sxy[1] = 25;
		}
		ws.ws_col = sxy[0]; /* X */
		ws.ws_row = sxy[1]; /* Y */
		/* Set some sane values for pixel sizes. */
		ws.ws_xpixel = ws.ws_col * 8;
		ws.ws_ypixel = ws.ws_row * 16;
		COMPILER_WRITE_BARRIER();
		/* Copy collected data into user-space. */
		memcpy(arg, &ws, sizeof(struct winsize));
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
		break;
	}
	return 0;
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
ansitty_device_output(struct ansitty *__restrict self,
                      void const *data, size_t datalen) {
	REF struct tty_device *output;
	struct ansitty_device *me;
	me = container_of(self, struct ansitty_device, at_ansi);
	output = awref_get(&me->at_tty);
	if (output) {
		FINALLY_DECREF_UNLIKELY(output);
#if 1
		/* Directly write to the input buffer, bypassing terminal
		 * keyboard input processing functionality that might do
		 * strange stuff to our output data.
		 * Even though it would make sense to do this, I'm not entirely
		 * confident that this is really what's supposed to be done here.
		 * There is a chance that ANSI response codes are meant to be
		 * pre-processed before being passed to the actual input buffer...
		 * (Although that wouldn't make much sense to me, since that would
		 *  also mean that the response would be echoed on-screen when ECHO
		 *  mode is enabled) */
		ringbuffer_write(&output->t_term.t_ibuf, data, datalen);
#else
		terminal_iwrite(&output->t_term, data, datalen, IO_WRONLY);
#endif
	}
}


PRIVATE NONNULL((1)) void LIBANSITTY_CC
ansitty_device_setled(struct ansitty *__restrict self,
                      uint8_t mask, uint8_t flag) {
	REF struct tty_device *output;
	struct ansitty_device *me;
	me = container_of(self, struct ansitty_device, at_ansi);
	output = awref_get(&me->at_tty);
	if (output) {
		FINALLY_DECREF_UNLIKELY(output);
		if (output->t_ihandle_typ == HANDLE_TYPE_CHARACTERDEVICE &&
		    character_device_isakeyboard((struct character_device *)output->t_ihandle_ptr)) {
			struct keyboard_device *kbd;
			uintptr_t new_leds;
			kbd = (struct keyboard_device *)output->t_ihandle_ptr;
			sync_write(&kbd->kd_leds_lock);
			new_leds = (kbd->kd_leds & (mask | ~0xf)) | (flag & 0xf);
			if (kbd->kd_leds != new_leds) {
				if (kbd->kd_ops.ko_setleds) {
					TRY {
						(*kbd->kd_ops.ko_setleds)(kbd, new_leds);
					} EXCEPT {
						sync_endwrite(&kbd->kd_leds_lock);
						RETHROW();
					}
				}
				kbd->kd_leds = new_leds;
			}
			sync_endwrite(&kbd->kd_leds_lock);
		}
	}
}


PRIVATE NONNULL((1, 2)) bool LIBANSITTY_CC
ansitty_device_termios(struct ansitty *__restrict self,
                       struct termios *__restrict oldios,
                       struct termios const *newios) {
	REF struct tty_device *output;
	struct ansitty_device *me;
	me = container_of(self, struct ansitty_device, at_ansi);
	output = awref_get(&me->at_tty);
	if (!output) {
		memset(oldios, 0, sizeof(*oldios));
	} else {
		FINALLY_DECREF_UNLIKELY(output);
		memcpy(oldios, &output->t_term.t_ios, sizeof(*oldios));
		if (newios)
			terminal_setios(&output->t_term, newios, NULL);
	}
	return true;
}



/* Initialize a given ansitty device.
 * NOTE: `ops->ato_output' must be set to NULL when calling this function.
 *       The internal routing of this callback to injecting keyboard output
 *       is done dynamically when the ANSI TTY is connected to the output
 *       channel of a `struct tty_device'
 * This function initializes the following operators:
 *   - cd_type.ct_write = &ansitty_device_write;  // Mustn't be re-assigned!
 *   - cd_type.ct_fini  = &ansitty_device_fini;   // Must be called by an override
 *   - cd_type.ct_ioctl = &ansitty_device_ioctl;  // Must be called by an override */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL ansitty_device_cinit)(struct ansitty_device *__restrict self,
                                    struct ansitty_operators const *__restrict ops) {
	assert(self);
	assert(ops);
	assertf(!ops->ato_output, "Don't provided operator `ato_output'!");
	assertf(!ops->ato_setled, "Don't provided operator `ato_setled'!");
	assertf(!ops->ato_termios, "Don't provided operator `ato_termios'!");
	ansitty_init(&self->at_ansi, ops);
	/* Provide standard operators. */
	self->cd_type.ct_write = &ansitty_device_write;
	self->cd_type.ct_ioctl = &ansitty_device_ioctl;
	/* Override the TTY output operator to try to inject responses into the keyboard queue. */
	self->at_ansi.at_ops.ato_output  = &ansitty_device_output;
	self->at_ansi.at_ops.ato_setled  = &ansitty_device_setled;
	self->at_ansi.at_ops.ato_termios = &ansitty_device_termios;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_ANSITTY_C */
