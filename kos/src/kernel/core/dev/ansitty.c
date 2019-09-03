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
#ifndef GUARD_KERNEL_SRC_DEV_ANSITTY_C
#define GUARD_KERNEL_SRC_DEV_ANSITTY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <kos/kernel/handle.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <dev/ansitty.h>
#include <dev/keyboard.h>
#include <libansitty/ansitty.h>

DECL_BEGIN

PUBLIC NONNULL((1)) size_t KCALL
ansitty_device_write(struct character_device *__restrict self,
                     USER CHECKED void const *src,
                     size_t num_bytes, iomode_t mode) THROWS(...) {
	struct ansitty_device *me = (struct ansitty_device *)self;
	return (size_t)ansitty_printer(&me->at_ansi, (char const *)src, num_bytes);
}

PUBLIC NONNULL((1)) syscall_slong_t KCALL
ansitty_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd,
                     USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct ansitty_device *me = (struct ansitty_device *)self;
	(void)me;
	(void)cmd;
	(void)arg;
	(void)mode;
	/* TODO: Add ANSI configuration ioctl()s here (I'm certain there are at least some...) */
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
ansitty_device_output(struct ansitty *__restrict self,
                      void const *data, size_t datalen) {
	REF struct tty_device *output;
	struct ansitty_device *me;
	me = container_of(self, struct ansitty_device, at_ansi);
	output = me->at_tty.get();
	if (output) {
		FINALLY_DECREF_UNLIKELY(output);
#if 1
		/* Directory write to the input buffer, bypassing terminal
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
	output = me->at_tty.get();
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
	output = me->at_tty.get();
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
 *       channel of a `struct tty'
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
