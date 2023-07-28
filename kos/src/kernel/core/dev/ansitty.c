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
ansittydev_v_write(struct mfile *__restrict self,
                   NCX void const *src,
                   size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	struct ansittydev *me = mfile_asansitty(self);
#if !defined(NDEBUG) && 0
	printk(KERN_DEBUG "[ansittydev_v_write] %$q\n", num_bytes, src);
#endif
	return (size_t)ansitty_printer(&me->at_ansi, (NCX char const *)src, num_bytes);
}


PUBLIC NONNULL((1)) syscall_slong_t KCALL
ansittydev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                   NCX UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	struct ansittydev *me = mfile_asansitty(self);
	switch (cmd) {

	case TIOCGWINSZ:
	case _IO_WITHTYPE(TIOCGWINSZ, struct winsize): {
		struct winsize ws;
		ansitty_coord_t sxy[2];
		validate_writable(arg, sizeof(struct winsize));
		/* These 2 operators are emulated by libansitty and should _always_ be present. */
		assert(me->at_ansi.at_ops.ato_getcursor);
		assert(me->at_ansi.at_ops.ato_setcursor);
		/* Make use of the fact that the cursor position is clamped to the display bounds.
		 * Note that libansitty makes use  of the same fact  to determine the window  size
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
			 * actual display size is described by the max valid coords +1  each. */
			++sxy[0];
			++sxy[1];
		}
		if (sxy[0] <= 1 && sxy[1] <= 1) {
			/* If we couldn't get anything useful, default to some sane values. */
			sxy[0] = 80;
			sxy[1] = 25;
		}
		ws.ws_col = sxy[0]; /* X */
		ws.ws_row = sxy[1]; /* Y */
		/* Set some sane values for pixel sizes. */
		ws.ws_xpixel = ws.ws_col * 9;
		ws.ws_ypixel = ws.ws_row * 16;
		COMPILER_WRITE_BARRIER();
		/* Copy collected data into user-space. */
		memcpy(arg, &ws, sizeof(struct winsize));
		return 0;
	}	break;

	default:
		break;
	}

	return chrdev_v_ioctl(self, cmd, arg, mode);
}

PUBLIC NONNULL((1)) void LIBANSITTY_CC
ansittydev_v_output(struct ansitty *__restrict self,
                    void const *data, size_t datalen) {
	REF struct mkttydev *output;
	struct ansittydev *me;
	me = container_of(self, struct ansittydev, at_ansi);
	output = awref_get(&me->at_tty);
	if (output) {
		FINALLY_DECREF_UNLIKELY(output);
#if 1
		/* Directly write to the input buffer, bypassing terminal
		 * keyboard  input processing functionality that might do
		 * strange stuff to our output data.
		 * Even  though it would  make sense to do  this, I'm not entirely
		 * confident  that this is really what's supposed to be done here.
		 * There is a  chance that  ANSI response  codes are  meant to  be
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


PUBLIC NONNULL((1)) void LIBANSITTY_CC
ansittydev_v_setled(struct ansitty *__restrict self,
                    uint8_t mask, uint8_t flag) {
	REF struct mkttydev *output;
	struct ansittydev *me;
	me = container_of(self, struct ansittydev, at_ansi);
	output = awref_get(&me->at_tty);
	if (output) {
		FINALLY_DECREF_UNLIKELY(output);
		if (output->mtd_ihandle_typ == HANDLE_TYPE_MFILE &&
		    mfile_iskbd((struct mfile *)output->mtd_ihandle_ptr)) {
			struct kbddev *kbd;
			uintptr_t new_leds;
			kbd = mfile_askbd((struct mfile *)output->mtd_ihandle_ptr);
			kbddev_leds_acquire(kbd);
			RAII_FINALLY { kbddev_leds_release(kbd); };
			new_leds = (kbd->kd_leds & (mask | ~0xf)) | (flag & 0xf);
			if (kbd->kd_leds != new_leds) {
				struct kbddev_ops const *ops;
				ops = kbddev_getops(kbd);
				if (ops->ko_setleds != NULL)
					(*ops->ko_setleds)(kbd, new_leds);
				kbd->kd_leds = new_leds;
			}
		}
	}
}


PUBLIC NONNULL((1, 2)) bool LIBANSITTY_CC
ansittydev_v_termios(struct ansitty *__restrict self,
                     struct termios *__restrict oldios,
                     struct termios const *newios) {
	REF struct mkttydev *output;
	struct ansittydev *me;
	me = container_of(self, struct ansittydev, at_ansi);
	output = awref_get(&me->at_tty);
	if (!output) {
		bzero(oldios, sizeof(*oldios));
	} else {
		FINALLY_DECREF_UNLIKELY(output);
		memcpy(oldios, &output->t_term.t_ios, sizeof(*oldios));
		if (newios)
			terminal_setios(&output->t_term, newios, NULL);
	}
	return true;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_ANSITTY_C */
