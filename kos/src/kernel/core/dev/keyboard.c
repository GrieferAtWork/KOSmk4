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
#ifndef GUARD_KERNEL_SRC_DEV_KEYBOARD_C
#define GUARD_KERNEL_SRC_DEV_KEYBOARD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/entry.h>
#include <dev/ansitty.h>
#include <dev/keyboard.h>
#include <kernel/compat.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except/inval.h>
#include <kos/ioctl/keyboard.h>
#include <kos/kernel/handle.h>
#include <linux/kd.h> /* Needed to emulate the linux keyboard interface */
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unicode.h>

#include "at_scancodes.h"

DECL_BEGIN

#ifdef CONFIG_HAVE_DEBUGGER
PUBLIC NOBLOCK bool
NOTHROW(KCALL keyboard_device_putkey)(struct keyboard_device *__restrict self, u16 key) {
	pflag_t was;
	bool result;
	assert(key != KEY_NONE);
	was = PREEMPTION_PUSHOFF();
	result = keyboard_device_putkey_nopr(self, key);
	PREEMPTION_POP(was);
	return result;
}
PUBLIC NOBLOCK bool
NOTHROW(KCALL keyboard_device_putkey_nopr)(struct keyboard_device *__restrict self, u16 key) {
	if (key == KEY_F12) {
		uintptr_t flags;
again_read_flags:
		flags = ATOMIC_READ(self->kd_flags);
		if (flags & KEYBOARD_DEVICE_FLAG_DBGF12) {
			if ((flags & KEYBOARD_DEVICE_FLAG_DBGF12_MASK) == KEYBOARD_DEVICE_FLAG_DBGF12_THRICE)
				dbg();
			if (!ATOMIC_CMPXCH_WEAK(self->kd_flags, flags, flags + KEYBOARD_DEVICE_FLAG_DBGF12_ONCE))
				goto again_read_flags;
		}
	} else if ((key & ~(KEY_FRELEASED | KEY_FREPEAT)) != KEY_F12) {
		/* Clear the F12 counter mask. */
		ATOMIC_FETCHAND(self->kd_flags, ~KEYBOARD_DEVICE_FLAG_DBGF12_MASK);
	}
	return keyboard_buffer_putkey_nopr(&self->kd_buf, key);
}
#endif /* CONFIG_HAVE_DEBUGGER */

/* Add a given key to the keyboard user-input buffer.
 * NOTE: The caller must not pass `KEY_NONE' for `key'
 * @return: true:  Successfully added the key.
 * @return: false: The buffer is already full and the key was not added. */
PUBLIC NOBLOCK bool
NOTHROW(KCALL keyboard_buffer_putkey)(struct keyboard_buffer *__restrict self, u16 key) {
	pflag_t was;
	bool result;
	assert(key != KEY_NONE);
	was = PREEMPTION_PUSHOFF();
	result = keyboard_buffer_putkey_nopr(self, key);
	PREEMPTION_POP(was);
	return result;
}

PUBLIC NOBLOCK bool
NOTHROW(KCALL keyboard_buffer_putkey_nopr)(struct keyboard_buffer *__restrict self, u16 key) {
	union keyboard_buffer_state oldstate, newstate;
	assert(!PREEMPTION_ENABLED());
	assert(key != KEY_NONE);
	for (;;) {
		size_t index;
		oldstate.bs_word = ATOMIC_READ(self->kb_bufstate.bs_word);
		if (oldstate.bs_state.s_used >= CONFIG_KEYBOARD_BUFFER_SIZE)
			return false;
		index = (oldstate.bs_state.s_start +
		         oldstate.bs_state.s_used) %
		        CONFIG_KEYBOARD_BUFFER_SIZE;
		if (!ATOMIC_CMPXCH(self->kb_buffer[index], KEY_NONE, key))
			continue;
		newstate = oldstate;
		++newstate.bs_state.s_used;
		if (ATOMIC_CMPXCH_WEAK(self->kb_bufstate.bs_word,
		                       oldstate.bs_word,
		                       newstate.bs_word))
			break;
#ifdef NDEBUG
		ATOMIC_WRITE(self->kb_buffer[index], KEY_NONE);
#else /* NDEBUG */
		{
			u16 oldkey;
			oldkey = ATOMIC_XCH(self->kb_buffer[index], KEY_NONE);
			assert(oldkey == key);
		}
#endif /* !NDEBUG */
	}
	/* Send the signal for every key enqueued. */
	sig_send(&self->kb_avail);
	return true;
}


/* Try to read a key stroke from the given keyboard buffer.
 * @return: KEY_NONE: The buffer is empty. */
PUBLIC NOBLOCK u16
NOTHROW(KCALL keyboard_buffer_trygetkey)(struct keyboard_buffer *__restrict self) {
	u16 result;
	for (;;) {
		union keyboard_buffer_state oldstate, newstate;
		oldstate.bs_word = ATOMIC_READ(self->kb_bufstate.bs_word);
		if (oldstate.bs_state.s_used == 0)
			return KEY_NONE;
		assert(oldstate.bs_state.s_start < CONFIG_KEYBOARD_BUFFER_SIZE);
		newstate = oldstate;
		++newstate.bs_state.s_start;
		--newstate.bs_state.s_used;
#if IS_POWER_OF_TWO(CONFIG_KEYBOARD_BUFFER_SIZE)
		newstate.bs_state.s_start &= CONFIG_KEYBOARD_BUFFER_SIZE - 1;
#else
		if (newstate.bs_state.s_start == CONFIG_KEYBOARD_BUFFER_SIZE)
			newstate.bs_state.s_start = 0;
#endif
		if (!ATOMIC_CMPXCH_WEAK(self->kb_bufstate.bs_word,
		                        oldstate.bs_word,
		                        newstate.bs_word))
			continue;
		result = ATOMIC_XCH(self->kb_buffer[oldstate.bs_state.s_start], KEY_NONE);
		if likely(result != KEY_NONE)
			break;
	}
	return result;
}

PUBLIC u16 KCALL
keyboard_buffer_getkey(struct keyboard_buffer *__restrict self)
		THROWS(E_WOULDBLOCK) {
	u16 result;
	assert(!task_isconnected());
	while ((result = keyboard_buffer_trygetkey(self)) == KEY_NONE) {
		task_connect(&self->kb_avail);
		result = keyboard_buffer_trygetkey(self);
		if unlikely(result != KEY_NONE) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
	return result;
}


PRIVATE NOBLOCK struct keyboard_key_packet
NOTHROW(KCALL keyboard_device_trygetkey_locked_noled)(struct keyboard_device *__restrict self) {
	struct keyboard_key_packet result;
	assert(sync_reading(&self->kd_map_lock));
	result.kp_key = keyboard_buffer_trygetkey(&self->kd_buf);
	switch (result.kp_key) {

	case KEY_LCTRL:
		self->kd_mods |= KEYMOD_LCTRL;
		break;

	case KEY_LCTRL | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_LCTRL;
		break;

	case KEY_RCTRL:
		self->kd_mods |= KEYMOD_RCTRL;
		break;

	case KEY_RCTRL | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_RCTRL;
		break;

	case KEY_LSHIFT:
		self->kd_mods |= KEYMOD_LSHIFT;
		break;

	case KEY_LSHIFT | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_LSHIFT;
		break;

	case KEY_RSHIFT:
		self->kd_mods |= KEYMOD_RSHIFT;
		break;

	case KEY_RSHIFT | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_RSHIFT;
		break;

	case KEY_LGUI:
		self->kd_mods |= KEYMOD_LGUI;
		break;

	case KEY_LGUI | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_LGUI;
		break;

	case KEY_RGUI:
		self->kd_mods |= KEYMOD_RGUI;
		break;

	case KEY_RGUI | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_RGUI;
		break;

	case KEY_LALT:
		self->kd_mods |= KEYMOD_LALT;
		break;

	case KEY_LALT | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_LALT;
		break;

	case KEY_RALT:
		self->kd_mods |= KEYMOD_RALT;
		break;

	case KEY_RALT | KEY_FRELEASED:
		self->kd_mods &= ~KEYMOD_RALT;
		break;

	case KEY_CAPSLOCK:
		self->kd_mods ^= KEYMOD_CAPSLOCK;
		break;

	case KEY_SCROLLLOCK:
		self->kd_mods ^= KEYMOD_SCROLLLOCK;
		break;

	case KEY_NUMLOCK:
		self->kd_mods ^= KEYMOD_NUMLOCK;
		break;

	case KEY_KP_7:
	case KEY_KP_7 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_HOME | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_8:
	case KEY_KP_8 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_UP | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_9:
	case KEY_KP_9 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_PGUP | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_4:
	case KEY_KP_4 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_LEFT | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_5:
	case KEY_KP_5 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_NONE;
		break;

	case KEY_KP_6:
	case KEY_KP_6 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_RIGHT | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_1:
	case KEY_KP_1 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_END | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_2:
	case KEY_KP_2 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_DOWN | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_3:
	case KEY_KP_3 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_PGDOWN | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_0:
	case KEY_KP_0 | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_INSERT | (result.kp_key & KEY_FRELEASED);
		break;

	case KEY_KP_DOT:
	case KEY_KP_DOT | KEY_FRELEASED:
		if (!(self->kd_mods & KEYMOD_NUMLOCK))
			result.kp_key = KEY_DELETE | (result.kp_key & KEY_FRELEASED);
		break;

	default:
		break;
	}
	result.kp_mod = self->kd_mods;
	return result;
}


STATIC_ASSERT(KEYBOARD_LED_CAPSLOCK == KEYMOD_CAPSLOCK);
STATIC_ASSERT(KEYBOARD_LED_NUMLOCK == KEYMOD_NUMLOCK);
STATIC_ASSERT(KEYBOARD_LED_SCROLLLOCK == KEYMOD_SCROLLLOCK);

#define KEYMOD_LEDMASK (KEYMOD_CAPSLOCK | KEYMOD_NUMLOCK | KEYMOD_SCROLLLOCK)

PRIVATE void KCALL
sync_leds(struct keyboard_device *__restrict self)
		THROWS(E_IOERROR, ...) {
	for (;;) {
		u16 curmod, oldled, newled;
		curmod = ATOMIC_READ(self->kd_mods);
		oldled = ATOMIC_READ(self->kd_leds);
		newled = (oldled & ~KEYMOD_LEDMASK) | (curmod & KEYMOD_LEDMASK);
		if (oldled == newled)
			break;
		if (!sync_trywrite(&self->kd_leds_lock))
			break; /* Some other thread must already be syncing LEDs, or
			        * is deliberately setting some custom LED values */
		COMPILER_READ_BARRIER();
		if likely(self->kd_leds == oldled) {
			/* Update LEDs on the keyboard */
			if (self->kd_ops.ko_setleds) {
				TRY {
					(*self->kd_ops.ko_setleds)(self, newled);
				} EXCEPT {
					sync_endwrite(&self->kd_leds_lock);
					if (!was_thrown(E_IOERROR))
						RETHROW();
					error_printf("syncing keyboard leds");
					return;
				}
			}
			self->kd_leds = newled;
			sync_endwrite(&self->kd_leds_lock);
			break;
		}
		sync_endwrite(&self->kd_leds_lock);
	}
}



/* Try to read a key stroke from the given keyboard.
 * @return: { KEY_NONE, ? }: The buffer is empty. */
PUBLIC struct keyboard_key_packet KCALL
keyboard_device_trygetkey(struct keyboard_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct keyboard_key_packet result;
	sync_read(&self->kd_map_lock);
	result = keyboard_device_trygetkey_locked_noled(self);
	sync_endread(&self->kd_map_lock);
	if (result.kp_key == KEY_CAPSLOCK ||
	    result.kp_key == KEY_NUMLOCK ||
	    result.kp_key == KEY_SCROLLLOCK)
		sync_leds(self);
	return result;
}

PUBLIC struct keyboard_key_packet KCALL
keyboard_device_getkey(struct keyboard_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	struct keyboard_key_packet result;
	assert(!task_isconnected());
	for (;;) {
		result = keyboard_device_trygetkey(self);
		if (result.kp_key != KEY_NONE)
			break;
		task_connect(&self->kd_buf.kb_avail);
		TRY {
			result = keyboard_device_trygetkey(self);
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		if unlikely(result.kp_key != KEY_NONE) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
	return result;
}

LOCAL NOBLOCK u8
NOTHROW(KCALL get_control_key)(u8 ch) {
	/* Playing around with linux, I've noticed some mappings which I can't
	 * really explain myself, however one of them: CTRL+^ is what allows one
	 * to generate SIGQUIT with a European keyboard.
	 *       Second-Key
	 *            |  Second-Key-Ascii
	 *            |  |      Produced-ctrl-char
	 *            |  |         |   References
	 *            v  v         v     v
	 *       CTRL+  (0x20) --> 0x00 [1][3]
	 *       CTRL+" (0x22) --> 0x00 [1]           (Likely an error in the TTY I've tested; "=SHIFT+2)
	 *       CTRL+2 (0x32) --> 0x00 [1][2][3][6]
	 *       CTRL+` (0x38) --> 0x00 [3][6]
	 *       CTRL+3 (0x33) --> 0x1b [1][2][6]
	 *       CTRL+4 (0x34) --> 0x1c [1][2][5][6]
	 *       CTRL+^ (0x5e) --> 0x1c [1]
	 *       CTRL+` (0x38) --> 0x1c [4]           (!!! Collision)
	 *       CTRL+5 (0x35) --> 0x1d [1][2][6]
	 *       CTRL+& (0x26) --> 0x1e [1]           (Likely an error in the TTY I've tested; &=SHIFT+6)
	 *       CTRL+6 (0x36) --> 0x1e [1][2][3][6]
	 *       CTRL+^ (0x5e) --> 0x1e [6]           (I don't know what to say... My testing shows this to be 0x1c (^\),
	 *                                             which I know is weird and may not actually be the case, but actually
	 *                                             be related to diacritics...; 5E->1E would also make more sense than
	 *                                             5E->1C, since 0x60-0x7f -> 0x00-0x1f)
	 *       CTRL+- (0x2d) --> 0x1f [1]
	 *       CTRL+# (0x23) --> 0x1f [1]
	 *       CTRL+7 (0x37) --> 0x1f [1][2][3][6]
	 *       CTRL+/ (0x2f) --> 0x1f [3][6]
	 *       CTRL+8 (0x38) --> 0x7f [1][2][3][6]
	 *       CTRL+? (0x3f) --> 0x7f [6]
	 * References:
	 *  - [1] Own tests using PuTTY
	 *  - [2] https://unix.stackexchange.com/questions/226327/what-does-ctrl4-and-ctrl-do-in-bash
	 *  - [3] https://utcc.utoronto.ca/~cks/space/blog/unix/OddControlCharacters
	 *  - [4] https://superuser.com/a/1155763
	 *  - [5] https://bash.cyberciti.biz/guide/Shell_signal_values
	 *  - [6] https://github.com/joejulian/xterm/blob/master/input.c#L263
	 *
	 * This page seems to suggest that xterm uses `Xutf8LookupString()' for the CTRL+... translation:
	 *    https://invisible-island.net/xterm/modified-keys.html
	 *   ...
	 *   xterm calls Xutf8LookupString or XmbLookupString to obtain equivalent characters and key symbol
	 *   Both XKB (keyboard) and the X11 library contribute to the key symbol returned by the *LookupString functions.
	 *   ...
	 *   The latter has special cases for certain control keys, e.g., converting control-3 to the escape character.
	 *   ...
	 *
	 * So the rabbit hole still goes deeper...
	 *
	 */
	switch (ch) {

	case ' ':
	case '2':
	case '`':
		ch = 0x00;
		break;

	case '3':
		ch = 0x1b;
		break;

	case '4':
	case '^':
		ch = 0x1c;
		break;

	case '5':
		ch = 0x1d;
		break;

	case '6':
		ch = 0x1e;
		break;

	case '-':
	case '#':
	case '7':
		ch = 0x1f;
		break;

	case '8':
	case '?':
		ch = 0x7f;
		break;

	default:
		if (ch >= 0x40 && ch <= 0x5f)
			ch -= 0x40;
		else if (ch >= 0x60 && ch <= 0x7f)
			ch -= 0x60;
		else {
			ch = 0xff;
		}
		break;
	}
	return ch;
}

/* Perform key->char translation and store the results in `self->kd_map_pend'
 * Note that unlike `keymap_translate_buf()', this function also takes care of
 * special posix escape sequences (e.g. `\e[11~' for KEY_F1), as well as the
 * posix control character modification that causes `64' to be subtracted from
 * character ordinals in the range of '@'...'_' (with '`'...'DEL' aliasing the
 * same character) (e.g. `\3' for CTRL+C)
 * NOTE: KOS also provides for windows-style CTRL+ALT key modifiers, allowing
 *       e.g. `@' to be written on a European keyboard by pressing CTRL+ALT+Q,
 *       instead of forcing the user to press RIGHT_ALT+Q (since some people (me ;P)
 *       are using such a keyboard if you couldn't have already guessed by the
 *       presence of a de_DE layout preset)
 *       Because of this, certain key combinations are ambiguous, such as
 *       the aforementioned CTRL+ALT+Q.
 *       In these cases, we first try to decode the key through use of the
 *       keymap program, before doing UNIX ascii escape sequencing.
 */
PRIVATE NOBLOCK size_t
NOTHROW(KCALL keyboard_device_do_translate)(struct keyboard_device *__restrict self,
                                            uint16_t key, uint16_t mod) {
	size_t result;
	assert(sync_writing(&self->kd_map_lock));
	key &= ~(KEY_FREPEAT);
	result = keymap_translate_buf(&self->kd_map, key, mod, (char *)self->kd_pend,
	                              COMPILER_LENOF(self->kd_pend));
	if unlikely(result > COMPILER_LENOF(self->kd_pend))
		goto nope; /* XXX: Better handling? */
	if (!result) {
		/* No layout-specific mapping given for this key.
		 * Check for special mappings of CONTROL character, as well as
		 * other special keys that should produce escape sequences. */
		u8 ch;
		/* Y          -- 0x59 */
		/* CTRL+Y     -- 0x19 */
		/* ALT+Y      -- 0x1b 0x59 */
		/* CTRL+ALT+Y -- 0x1b 0x19 */
		if (KEYMOD_ISCTRL_ALT(mod & ~(KEYMOD_SHIFT))) {
			result = keymap_translate_buf(&self->kd_map, key,
			                              mod & ~(KEYMOD_CTRL | KEYMOD_ALT),
			                              (char *)&ch, 1);
			if (result != 1) {
				if (result == 0)
					goto done;
				goto nope;
			}
			/* Transform into a control character,
			 * and prefix with 0x1b (ESC; aka. `\e') */
			ch = get_control_key(ch);
			if (ch == 0xff)
				goto nope;
			self->kd_pend[0] = (byte_t)0x1b;
			self->kd_pend[1] = (byte_t)ch;
			result = 2;
			goto done;
		}
		if (KEYMOD_ISCTRL(mod & ~(KEYMOD_SHIFT))) {
			result = keymap_translate_buf(&self->kd_map, key,
			                              mod & ~KEYMOD_CTRL,
			                              (char *)&ch, 1);
			if (result != 1) {
				if (result == 0)
					goto done;
				goto nope;
			}
			/* Transform into a control character. */
			ch = get_control_key(ch);
			if (ch == 0xff)
				goto nope;
			self->kd_pend[0] = (byte_t)ch;
			result = 1;
			goto done;
		}
		if (KEYMOD_ISALT(mod & ~(KEYMOD_SHIFT))) {
			result = keymap_translate_buf(&self->kd_map, key,
			                              mod & ~(KEYMOD_CTRL | KEYMOD_ALT),
			                              (char *)&self->kd_pend[1],
			                              COMPILER_LENOF(self->kd_pend) - 1);
			if (result == 0)
				goto done;
			if unlikely(result > (COMPILER_LENOF(self->kd_pend) - 1))
				goto nope;
			/* Prefix with 0x1b (ESC; aka. `\e') */
			self->kd_pend[0] = (char)0x1b;
			++result;
			goto done;
		}
	}
	{
		REF struct tty_device *tty;
		struct ansitty *atty;
done:
		atty = NULL;
		tty  = self->kb_tty.get();
		if (tty && tty->t_ohandle_typ == HANDLE_TYPE_CHARACTERDEVICE) {
			struct ansitty_device *ttydev;
			ttydev = (struct ansitty_device *)tty->t_ohandle_ptr;
			if (character_device_isanansitty(ttydev))
				atty = &ttydev->at_ansi;
		}
		/* Encode a misc. key using the currently active ANSI tty settings. */
		result = ansitty_translate_misc(atty, (char *)self->kd_pend, result, key, mod);
		xdecref_unlikely(tty);
	}
	return result;
nope:
	return 0;
}


/* Apply transformations mandated by the currently
 * set code-page of a potentially connected ANSI tty. */
PRIVATE NOBLOCK /*utf-8*/ size_t
NOTHROW(KCALL keyboard_device_encode_cp)(struct keyboard_device *__restrict self,
                                         size_t len) {
	REF struct tty_device *tty;
	struct ansitty_device *atty;
	char const *reader, *end;
	char newbuf[COMPILER_LENOF(self->kd_pend)];
	size_t newlen;
	tty = self->kb_tty.get();
	if (!tty)
		goto done;
	if (tty->t_ohandle_typ != HANDLE_TYPE_CHARACTERDEVICE)
		goto done_tty;
	atty = (struct ansitty_device *)tty->t_ohandle_ptr;
	if (!character_device_isanansitty(atty))
		goto done_tty;
	/* When the TTY uses CP#0 (UTF-8), then we don't actually need to re-encode
	 * the input text sequence, since both input and output would use pure UTF-8.
	 * And given that the most likely situation has the ANSITTY be in UTF-8 mode,
	 * as everything in KOS is (at heart) designed for full UTF-8 support, check
	 * for this highly likely case and optimize for it. */
	if likely(atty->at_ansi.at_codepage == 0)
		goto done_tty;
	/* Re-encode unicode characters */
	reader = (char const *)self->kd_pend;
	end    = (char const *)self->kd_pend + len;
	newlen = 0;
	while (reader < end) {
		char32_t ch;
		char tempbuf[ANSITTY_TRANSLATE_BUFSIZE];
		size_t encoded_length;
		ch             = unicode_readutf8_n(&reader, end);
		encoded_length = ansitty_translate(&atty->at_ansi, tempbuf, ch);
		encoded_length = memlen(tempbuf, 0, encoded_length); /* Stop on the first NUL-character */
		if (!encoded_length) /* Fallback: Anything that can't be encoded must be discarded */
			continue;
		if (newlen + encoded_length >= COMPILER_LENOF(self->kd_pend))
			break; /* Sequence too long (drop trailing characters...) */
		/* Append the newly encoded `tempbuf' */
		memcpy(newbuf + newlen, tempbuf, encoded_length, sizeof(char));
		newlen += encoded_length;
	}
	assert(newlen <= COMPILER_LENOF(self->kd_pend) - 1);
	/* Apply the new pending character buffer. */
	memcpy(self->kd_pend, newbuf, newlen, sizeof(char));
	len = newlen;
done_tty:
	decref_unlikely(tty);
done:
	return len;
}



/* Try to read a single byte from the keyboard data stream.
 * Same as `keyboard_device_read()'.
 * @return: -1: No data is available at the moment. */
PUBLIC int KCALL
keyboard_device_trygetc(struct keyboard_device *__restrict self)
		THROWS(E_IOERROR, ...) {
	int result;
again:
	sync_write(&self->kd_map_lock);
	if (self->kd_pendsz) {
		result = (int)(unsigned int)self->kd_pend[0];
		--self->kd_pendsz;
		memmovedown(&self->kd_pend[0],
		            &self->kd_pend[1],
		            self->kd_pendsz);
		sync_endwrite(&self->kd_map_lock);
	} else {
		struct keyboard_key_packet packet;
		result = -1;
again_getkey:
		packet = keyboard_device_trygetkey_locked_noled(self);
		if (packet.kp_key != KEY_NONE) {
			size_t len;
			/* Figure out how we're to encode key data for the user. */
			switch (ATOMIC_READ(self->kd_flags) & KEYBOARD_DEVICE_FLAG_RDMODE) {

			case K_RAW: {
				/* Produce AT-style, scanset#1 scancodes. */
				uint16_t kc = KEYCODE(packet.kp_key);
				byte_t up   = KEY_ISDOWN(packet.kp_key) ? 0 : 0x80;
				/* Need special encoding for certain keys. */
				switch (kc) {

				case KEY_PAUSE:
					self->kd_pend[0] = 0xe1;
					self->kd_pend[0] = 0x1d | up;
					self->kd_pend[0] = 0x45 | up;
					len              = 3;
					break;

				case KEY_HANGEUL:
					if (!KEY_ISDOWN(packet.kp_key))
						goto check_led_and_try_again;
					self->kd_pend[0] = 0xf2;
					len              = 1;
					break;

				case KEY_HANJA:
					if (!KEY_ISDOWN(packet.kp_key))
						goto check_led_and_try_again;
					self->kd_pend[0] = 0xf1;
					len              = 1;
					break;

				case KEY_SYSRQ:
					if (packet.kp_mod & (KEYMOD_LALT | KEYMOD_RALT)) {
						self->kd_pend[0] = 0x54 | up;
						len              = 1;
					} else {
						self->kd_pend[0] = 0xe0;
						self->kd_pend[1] = 0x2a | up;
						self->kd_pend[2] = 0xe0;
						self->kd_pend[3] = 0x37 | up;
						len              = 4;
					}
					break;

				default: {
					u16 enc;
					if (kc > 0xff)
						goto check_led_and_try_again;
					enc = at_scancodes[kc];
					if (!enc)
						goto check_led_and_try_again;
					if (enc & 0xff00) {
						/* 2-byte encoding. */
						self->kd_pend[0] = (byte_t)(enc >> 8);
						self->kd_pend[1] = (enc & 0x7f) | up;
						len              = 2;
					} else {
						/* 1-byte encoding. */
						self->kd_pend[0] = (enc & 0x7f) | up;
						len              = 1;
					}
				}	break;
				}
			}	break;

			case K_MEDIUMRAW: {
				/* Produce specially encoded key codes. */
				uint16_t kc = KEYCODE(packet.kp_key);
				if (kc < 128) {
					self->kd_pend[0] = kc | (KEY_ISDOWN(packet.kp_key) ? 0 : 0x80);
					len              = 1;
				} else {
					self->kd_pend[0] = KEY_ISDOWN(packet.kp_key) ? 0 : 0x80;
					self->kd_pend[1] = (kc >> 7) | 0x80;
					self->kd_pend[2] = (kc & 0x7f) | 0x80;
					len = 3;
				}
			}	break;

			case K_OFF:
				/* Don't produce anything. */
				goto check_led_and_try_again;

			default:
				/* Produce ascii/unicode (XXX: currently, Kos always produces unicode). */
				if (packet.kp_key & KEY_FRELEASED)
					goto again_getkey; /* Only generate characters on make-codes */
				len = keyboard_device_do_translate(self, packet.kp_key, packet.kp_mod);
				len = keyboard_device_encode_cp(self, len);
				if (len == 0) {
					printk(KERN_DEBUG "[keyboard:%q] translate(%#I16x,%#I16x): <empty>\n",
					       self->cd_name, packet.kp_key, packet.kp_mod);
check_led_and_try_again:
					sync_endwrite(&self->kd_map_lock);
					if (packet.kp_key == KEY_CAPSLOCK ||
					    packet.kp_key == KEY_NUMLOCK ||
					    packet.kp_key == KEY_SCROLLLOCK)
						sync_leds(self);
					goto again;
				}
				printk(KERN_DEBUG "[keyboard:%q] translate(%#I16x,%#I16x): %$q\n",
				       self->cd_name, packet.kp_key, packet.kp_mod,
				       len, self->kd_pend);
				break;
			}
			result = (int)(unsigned int)(unsigned char)self->kd_pend[0];
			--len;
			memmovedown(&self->kd_pend[0],
			            &self->kd_pend[1],
			            len);
			self->kd_pendsz = len;
		}
		sync_endwrite(&self->kd_map_lock);
		if (packet.kp_key == KEY_CAPSLOCK ||
		    packet.kp_key == KEY_NUMLOCK ||
		    packet.kp_key == KEY_SCROLLLOCK)
			sync_leds(self);
	}
	return result;

}

PUBLIC byte_t KCALL
keyboard_device_getc(struct keyboard_device *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	int result;
again:
	result = keyboard_device_trygetc(self);
	if (result == -1) {
		task_connect(&self->kd_buf.kb_avail);
		result = keyboard_device_trygetc(self);
		if (result != -1) {
			task_disconnectall();
			goto done;
		}
		task_waitfor();
		goto again;
	}
done:
	return (byte_t)(unsigned int)result;
}


/* Keyboard character device operators */
PUBLIC NONNULL((1)) size_t KCALL
keyboard_device_read(struct character_device *__restrict self,
                     USER CHECKED void *dst, size_t num_bytes,
                     iomode_t mode) THROWS(...) {
	struct keyboard_device *me;
	size_t result;
	me = (struct keyboard_device *)self;
	for (result = 0; result < num_bytes; ++result) {
		int ch;
again_read_ch:
		ch = keyboard_device_trygetc(me);
		if (ch == -1) {
			if (result)
				break;
			if (mode & IO_NONBLOCK) {
				if (!result && !(mode & IO_NODATAZERO))
					THROW(E_WOULDBLOCK_WAITFORSIGNAL);
				break;
			}
			task_connect(&me->kd_buf.kb_avail);
			ch = keyboard_device_trygetc(me);
			if (ch != -1) {
				task_disconnectall();
				goto do_append_ch;
			}
			task_waitfor();
			goto again_read_ch;
		}
do_append_ch:
		((byte_t *)dst)[result] = (byte_t)(unsigned int)ch;
	}
	return result;
}

PUBLIC NONNULL((1)) void KCALL
keyboard_device_stat(struct character_device *__restrict self,
                     USER CHECKED struct stat *result) THROWS(...) {
	struct keyboard_device *me;
	size_t bufsize;
	me = (struct keyboard_device *)self;
	result->st_blksize = sizeof(char);
	bufsize = ATOMIC_READ(me->kd_pendsz);
	bufsize += ATOMIC_READ(me->kd_buf.kb_bufstate.bs_state.s_used); /* XXX: This is inexact */
	result->st_size = bufsize;
}


LOCAL bool KCALL
keyboard_device_canread(struct keyboard_device *__restrict self) {
	uintptr_half_t used;
	if (ATOMIC_READ(self->kd_pendsz) != 0)
		return true;
	used = ATOMIC_READ(self->kd_buf.kb_bufstate.bs_state.s_used);
	return used != 0;
}

PUBLIC NONNULL((1)) poll_mode_t KCALL
keyboard_device_poll(struct character_device *__restrict self,
                     poll_mode_t what) THROWS(...) {
	struct keyboard_device *me;
	me = (struct keyboard_device *)self;
	if (what & POLLIN) {
		if (keyboard_device_canread(me))
			return POLLIN;
		task_connect_for_poll(&me->kd_buf.kb_avail);
		if (keyboard_device_canread(me))
			return POLLIN;
	}
	return 0;
}

LOCAL unsigned int KCALL
linux_keyboard_getmode(struct keyboard_device *__restrict self) {
	return ATOMIC_READ(self->kd_flags) & KEYBOARD_DEVICE_FLAG_RDMODE;
}

LOCAL void KCALL
linux_keyboard_setmode(struct keyboard_device *__restrict self,
                       unsigned int mode) {
	if (mode >= K_RAW && mode <= K_OFF) {
		uintptr_t flags;
		do {
			flags = ATOMIC_READ(self->kd_flags);
		} while (!ATOMIC_CMPXCH_WEAK(self->kd_flags, flags,
		                             (flags & ~KEYBOARD_DEVICE_FLAG_RDMODE) | mode));
	} else {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_GENERIC,
		      mode);
	}
}

LOCAL unsigned int KCALL
linux_keyboard_getmeta(struct keyboard_device *__restrict self) {
	(void)self;
	return K_ESCPREFIX;
}

LOCAL void KCALL
linux_keyboard_setmeta(struct keyboard_device *__restrict self,
                       unsigned int mode) {
	(void)self;
	/* TODO: This should configure if pressing ALT will:
	 *   K_METABIT:    Or' the produced character with 0x80
	 *   K_ESCPREFIX:  Prefix the produced character with \e
	 * On KOS, this is done in `ansitty_translate_misc()'
	 * (s.a. the call to said function further up in this file)
	 */
	if (mode != K_ESCPREFIX) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_GENERIC,
		      mode);
	}
}



PUBLIC NONNULL((1)) syscall_slong_t KCALL
keyboard_device_ioctl(struct character_device *__restrict self,
                      syscall_ulong_t cmd, USER UNCHECKED void *arg,
                      iomode_t mode) THROWS(...) {
	struct keyboard_device *me;
	(void)mode;
	me = (struct keyboard_device *)self;
	switch (cmd) {

	case KBDIO_TRYGETKEY: {
		struct keyboard_key_packet key;
		validate_writable(arg, sizeof(struct keyboard_key_packet));
		key = keyboard_device_trygetkey(me);
		if (!key.kp_key)
			return -EAGAIN;
		COMPILER_WRITE_BARRIER();
		memcpy(arg, &key, sizeof(struct keyboard_key_packet));
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_GETKEY: {
		struct keyboard_key_packet key;
		validate_writable(arg, sizeof(struct keyboard_key_packet));
		key = keyboard_device_getkey(me);
		COMPILER_WRITE_BARRIER();
		memcpy(arg, &key, sizeof(struct keyboard_key_packet));
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_GETLED: {
		uintptr_t leds;
		validate_writable(arg, sizeof(__uint32_t));
		leds = ATOMIC_READ(me->kd_leds);
		COMPILER_WRITE_BARRIER();
		*(u32 *)arg = (u32)leds;
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_SETLED: {
		uintptr_t new_mods;
		validate_readable(arg, sizeof(__uint32_t));
		COMPILER_READ_BARRIER();
		new_mods = *(u32 *)arg;
		COMPILER_READ_BARRIER();
		sync_write(&me->kd_leds_lock);
		if (me->kd_leds != new_mods) {
			if (me->kd_ops.ko_setleds) {
				TRY {
					(*me->kd_ops.ko_setleds)(me, new_mods);
				} EXCEPT {
					sync_endwrite(&me->kd_leds_lock);
					RETHROW();
				}
			}
			me->kd_leds = new_mods;
		}
		sync_endwrite(&me->kd_leds_lock);
	}	break;

	case KBDIO_MASKLED: {
		USER CHECKED struct keyboard_ledmask *data;
		u32 old_leds, new_mods;
		u32 led_mask, led_flag, led_fxor;
		validate_readable(arg, sizeof(struct keyboard_ledmask));
		data = (USER CHECKED struct keyboard_ledmask *)arg;
		COMPILER_READ_BARRIER();
		led_mask = ATOMIC_READ(data->lm_mask);
		led_flag = ATOMIC_READ(data->lm_flag);
		led_fxor = ATOMIC_READ(data->lm_fxor);
		COMPILER_READ_BARRIER();
		sync_write(&me->kd_leds_lock);
		old_leds = me->kd_leds;
		new_mods = ((old_leds & led_mask) | led_flag) ^ led_fxor;
		if (old_leds != new_mods) {
			if (me->kd_ops.ko_setleds) {
				TRY {
					(*me->kd_ops.ko_setleds)(me, new_mods);
				} EXCEPT {
					sync_endwrite(&me->kd_leds_lock);
					RETHROW();
				}
			}
			me->kd_leds = new_mods;
		}
		sync_endwrite(&me->kd_leds_lock);
		COMPILER_WRITE_BARRIER();
		data->lm_oldled = old_leds;
		data->lm_newled = new_mods;
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_GETMOD: {
		uintptr_t mods;
		validate_writable(arg, sizeof(__uint32_t));
		mods = ATOMIC_READ(me->kd_mods);
		COMPILER_WRITE_BARRIER();
		*(u32 *)arg = (u32)mods;
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_SETMOD: {
		uintptr_t new_mods;
		validate_readable(arg, sizeof(__uint32_t));
		COMPILER_READ_BARRIER();
		new_mods = *(u32 *)arg;
		COMPILER_READ_BARRIER();
		ATOMIC_WRITE(me->kd_mods, new_mods);
	}	break;

	case KBDIO_MASKMOD: {
		USER CHECKED struct keyboard_ledmask *data;
		u32 old_mods, new_mods;
		u32 mod_mask, mod_flag, mod_fxor;
		validate_readable(arg, sizeof(struct keyboard_ledmask));
		data = (USER CHECKED struct keyboard_ledmask *)arg;
		COMPILER_READ_BARRIER();
		mod_mask = ATOMIC_READ(data->lm_mask);
		mod_flag = ATOMIC_READ(data->lm_flag);
		mod_fxor = ATOMIC_READ(data->lm_fxor);
		COMPILER_READ_BARRIER();
		do {
			old_mods = ATOMIC_READ(me->kd_mods);
			new_mods = ((old_mods & mod_mask) | mod_flag) ^ mod_fxor;
		} while (!ATOMIC_CMPXCH_WEAK(me->kd_mods, old_mods, new_mods));
		COMPILER_WRITE_BARRIER();
		data->lm_oldled = old_mods;
		data->lm_newled = new_mods;
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_GETKEYMAP: {
		struct keyboard_keymap data;
		size_t mapsize;
		uint8_t default_encoding;
		validate_readwrite(arg, sizeof(struct keyboard_keymap));
		memcpy(&data, arg, sizeof(struct keyboard_keymap));
		validate_writable(data.km_maptext, data.km_mapsize);
		sync_read(&me->kd_map_lock);
restart_getkeymap_locked:
		COMPILER_BARRIER();
		mapsize          = me->kd_map_extsiz;
		default_encoding = me->kd_map.km_defencoding;
		assert(mapsize == 0 || me->kd_map.km_ext != NULL);
		if (data.km_mapsize >= mapsize) {
			/* Copy the key translation map into user-space.
			 * Note that since we need to be holding an atomic lock while doing this,
			 * we have to use memcpy_nopf() and copy faulting bytes individually. */
			size_t offset = 0, error;
			byte_t *extbase = (byte_t *)me->kd_map.km_ext;
continue_copy_keymap:
			error = memcpy_nopf((byte_t *)data.km_maptext + offset,
			                    extbase + offset, mapsize);
			if unlikely(error != 0) {
				byte_t next_byte;
				offset += mapsize - error;
				next_byte = *(extbase + offset);
				sync_endread(&me->kd_map_lock);
				COMPILER_WRITE_BARRIER();
				*((byte_t *)data.km_maptext + offset) = next_byte;
				COMPILER_WRITE_BARRIER();
				sync_read(&me->kd_map_lock);
				if unlikely(extbase != (byte_t *)ATOMIC_READ(me->kd_map.km_ext))
					goto restart_getkeymap_locked;
				if unlikely(mapsize != ATOMIC_READ(me->kd_map_extsiz))
					goto restart_getkeymap_locked;
				++offset;
				goto continue_copy_keymap;
			}
		}
		sync_endread(&me->kd_map_lock);
		COMPILER_WRITE_BARRIER();
		/* Write back the required buffer size, as well as the default encoding. */
		((struct keyboard_keymap *)arg)->km_mapsize = mapsize;
		((struct keyboard_keymap *)arg)->km_defenc  = default_encoding;
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_SETKEYMAP: {
		struct keyboard_keymap data;
		byte_t *new_map, *new_map2, *old_map;
		validate_readable(arg, sizeof(struct keyboard_keymap));
		memcpy(&data, arg, sizeof(struct keyboard_keymap));
		if unlikely(data.km_mapsize > KEYMAP_MAX_CODESIZE)
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_TOO_LARGE,
			      data.km_mapsize);
		if unlikely(data.km_defenc > KMP_ENCODING_MAX)
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_ENCODING,
			      data.km_defenc);
		validate_readable(data.km_maptext, data.km_mapsize);
		while (data.km_mapsize && ATOMIC_READ(*((byte_t *)data.km_maptext + data.km_mapsize - 1)) == 0)
			--data.km_mapsize;
		new_map = (byte_t *)kmalloc(data.km_mapsize + KEYMAP_UNTRUSTED_NUM_TRAILING_ZERO_BYTES,
		                            GFP_NORMAL);
		TRY {
			ssize_t real_length;
			uint8_t reg_enc = data.km_defenc;
			memcpy(new_map, data.km_maptext, data.km_mapsize);
			memset(new_map + data.km_mapsize, 0, KEYMAP_UNTRUSTED_NUM_TRAILING_ZERO_BYTES);
			real_length = keymap_codesize(new_map, &reg_enc, data.km_defenc);
			if unlikely(real_length < 0)
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETKEYMAP_BAD_MAPTEXT, 0);
			assert((size_t)real_length <= data.km_mapsize + KEYMAP_UNTRUSTED_NUM_TRAILING_ZERO_BYTES);
			new_map2 = (byte_t *)krealloc_nx(new_map, real_length, GFP_NORMAL);
			if likely(new_map2)
				new_map = new_map2;
			data.km_mapsize = real_length;
			sync_write(&me->kd_map_lock);
		} EXCEPT {
			kfree(new_map);
			RETHROW();
		}
		/* Install the new map. */
		old_map = (byte_t *)me->kd_map.km_ext;
		me->kd_map_extsiz         = data.km_mapsize;
		me->kd_map.km_ext         = new_map;
		me->kd_map.km_defencoding = data.km_defenc;
		memset(&me->kd_map.km_basic, 0, sizeof(me->kd_map.km_basic));
		sync_endwrite(&me->kd_map_lock);
		kfree(old_map);
	}	break;

	case KBDIO_RESETKEYMAP: {
		byte_t *old_map;
		sync_write(&me->kd_map_lock);
		old_map = (byte_t *)me->kd_map.km_ext;
		keymap_init_en_US(&me->kd_map);
		sync_endwrite(&me->kd_map_lock);
		kfree(old_map);
	}	break;

	case KBDIO_FLUSHPENDING: {
		for (;;) {
			struct keyboard_key_packet packet;
			packet = keyboard_device_trygetkey(me);
			if (packet.kp_key == KEY_NONE)
				break; /* Buffer became empty. */
		}
		ATOMIC_WRITE(me->kd_pendsz, 0);
	}	break;

	case KBDIO_PUTCHAR: {
		char ch;
		validate_readable(arg, sizeof(char));
		COMPILER_READ_BARRIER();
		ch = *(char *)arg;
		COMPILER_READ_BARRIER();
		sync_write(&me->kd_map_lock);
		if (me->kd_pendsz < COMPILER_LENOF(me->kd_pend)) {
			me->kd_pend[me->kd_pendsz] = ch;
			++me->kd_pendsz;
			sync_endwrite(&me->kd_map_lock);
			/* Only one thread can read input, so use `sig_send()'! */
			sig_send(&me->kd_buf.kb_avail);
			return 1;
		}
		sync_endwrite(&me->kd_map_lock);
	}	break;

	case KBDIO_PUTSTR: {
		struct keyboard_string data;
		byte_t new_buf[COMPILER_LENOF(me->kd_pend)];
		size_t avail;
		validate_readable(arg, sizeof(struct keyboard_string));
		COMPILER_READ_BARRIER();
		memcpy(&data, arg, sizeof(struct keyboard_string));
		COMPILER_READ_BARRIER();
		validate_readable(data.ks_text, data.ks_size);
		if (data.ks_size > COMPILER_LENOF(me->kd_pend))
			data.ks_size = COMPILER_LENOF(me->kd_pend);
		memcpy(new_buf, data.ks_text, data.ks_size);
		sync_write(&me->kd_map_lock);
		avail = COMPILER_LENOF(me->kd_pend) - me->kd_pendsz;
		if (avail > data.ks_size)
			avail = data.ks_size;
		memcpy(&me->kd_pend[me->kd_pendsz], new_buf, avail);
		me->kd_pendsz += avail;
		sync_endwrite(&me->kd_map_lock);
		/* Wake up one thread for every added key. */
		if (avail)
			sig_sendmany(&me->kd_buf.kb_avail, avail);
		return avail;
	}	break;

	case KBDIO_PUTKEY: {
		u16 key;
		validate_readable(arg, sizeof(u16));
		COMPILER_READ_BARRIER();
		key = *(u16 *)arg;
		COMPILER_READ_BARRIER();
		return keyboard_device_putkey(me, key);
	}	break;

	case KBDIO_GETDBGF12: {
		validate_writable(arg, sizeof(int));
		COMPILER_WRITE_BARRIER();
#ifdef KEYBOARD_DEVICE_FLAG_DBGF12
		*(int *)arg = (ATOMIC_READ(me->kd_flags) & KEYBOARD_DEVICE_FLAG_DBGF12) ? 1 : 0;
#else /* KEYBOARD_DEVICE_FLAG_DBGF12 */
		*(int *)arg = 0;
#endif /* !KEYBOARD_DEVICE_FLAG_DBGF12 */
		COMPILER_WRITE_BARRIER();
	}	break;

	case KBDIO_SETDBGF12: {
		int f12_mode;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		f12_mode = *(int *)arg;
		COMPILER_READ_BARRIER();
		if (f12_mode == 0) {
#ifdef KEYBOARD_DEVICE_FLAG_DBGF12
			ATOMIC_FETCHAND(me->kd_flags, ~(KEYBOARD_DEVICE_FLAG_DBGF12 |
			                                KEYBOARD_DEVICE_FLAG_DBGF12_MASK));
		} else if (f12_mode == 1) {
			ATOMIC_FETCHOR(me->kd_flags, KEYBOARD_DEVICE_FLAG_DBGF12);
#endif /* KEYBOARD_DEVICE_FLAG_DBGF12 */
		} else {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_IOCTL_KBDIO_SETDBGF12_BADDMODE,
			      f12_mode);
		}
	}	break;

	case KDGETLED:
	case _IO_WITHSIZE(KDGETLED, char): {
		uintptr_t leds;
		STATIC_ASSERT(KEYBOARD_LED_SCROLLLOCK >> 8 == LED_SCR);
		STATIC_ASSERT(KEYBOARD_LED_NUMLOCK    >> 8 == LED_NUM);
		STATIC_ASSERT(KEYBOARD_LED_CAPSLOCK   >> 8 == LED_CAP);
		validate_writable(arg, sizeof(char));
		leds = ATOMIC_READ(me->kd_leds);
		COMPILER_WRITE_BARRIER();
		*(char *)arg = (char)((leds >> 8) & (LED_SCR | LED_NUM | LED_CAP));
		COMPILER_WRITE_BARRIER();
	}	break;

	case KDSETLED:
	case _IO_WITHSIZE(KDSETLED, char): {
		uintptr_t new_leds;
		validate_readable(arg, sizeof(char));
		COMPILER_READ_BARRIER();
		new_leds = (uintptr_t)(*(char *)arg << 8);
		COMPILER_READ_BARRIER();
		if unlikely(new_leds & ~((K_SCROLLLOCK | K_NUMLOCK | K_CAPSLOCK) << 8))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_GENERIC, new_leds >> 8);
		sync_write(&me->kd_leds_lock);
		new_leds |= me->kd_leds & ~((K_SCROLLLOCK | K_NUMLOCK | K_CAPSLOCK) << 8);
		if (me->kd_leds != new_leds) {
			if (me->kd_ops.ko_setleds) {
				TRY {
					(*me->kd_ops.ko_setleds)(me, new_leds);
				} EXCEPT {
					sync_endwrite(&me->kd_leds_lock);
					RETHROW();
				}
			}
			me->kd_leds = new_leds;
		}
		sync_endwrite(&me->kd_leds_lock);
	}	break;

	case KDGKBTYPE:
	case _IO_WITHSIZE(KDGKBTYPE, unsigned int):
		validate_writable(arg, sizeof(unsigned int));
		*(unsigned int *)arg = KB_101;
		break;

	case KDGKBMODE:
	case _IO_WITHSIZE(KDGKBMODE, unsigned int):
		validate_writable(arg, sizeof(unsigned int));
		*(unsigned int *)arg = linux_keyboard_getmode(me);
		break;

	case KDSKBMODE:
	case _IO_WITHSIZE(KDSKBMODE, unsigned int):
		if ((uintptr_t)arg < PAGESIZE) {
			/* Compatibility with linux. */
			linux_keyboard_setmode(me, (unsigned int)(uintptr_t)arg);
		} else {
			validate_readable(arg, sizeof(unsigned int));
			linux_keyboard_setmode(me, *(unsigned int *)arg);
		}
		break;

	case KDGKBMETA:
	case _IO_WITHSIZE(KDGKBMETA, unsigned int):
		validate_writable(arg, sizeof(unsigned int));
		*(unsigned int *)arg = linux_keyboard_getmeta(me);
		break;

	case KDSKBMETA:
	case _IO_WITHSIZE(KDSKBMETA, unsigned int):
		validate_readable(arg, sizeof(unsigned int));
		linux_keyboard_setmeta(me, *(unsigned int *)arg);
		break;


	case KDGKBLED:
	case _IO_WITHSIZE(KDGKBLED, char): {
		uintptr_t mods;
		STATIC_ASSERT(KEYMOD_SCROLLLOCK >> 8 == K_SCROLLLOCK);
		STATIC_ASSERT(KEYMOD_NUMLOCK >> 8 == K_NUMLOCK);
		STATIC_ASSERT(KEYMOD_CAPSLOCK >> 8 == K_CAPSLOCK);
		validate_writable(arg, sizeof(char));
		mods = ATOMIC_READ(me->kd_mods);
		COMPILER_WRITE_BARRIER();
		*(char *)arg = (char)((mods >> 8) & (K_SCROLLLOCK | K_NUMLOCK | K_CAPSLOCK));
		COMPILER_WRITE_BARRIER();
	}	break;

	case KDSKBLED:
	case _IO_WITHSIZE(KDSKBLED, char): {
		uintptr_t old_mods, new_mask, new_mods;
		validate_readable(arg, sizeof(char));
		COMPILER_READ_BARRIER();
		new_mask = (uintptr_t)(*(char *)arg << 8);
		COMPILER_READ_BARRIER();
		if unlikely(new_mask & ~((K_SCROLLLOCK | K_NUMLOCK | K_CAPSLOCK) << 8))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_GENERIC, new_mask >> 8);
		do {
			old_mods = ATOMIC_READ(me->kd_mods);
			new_mods = (old_mods & ~((K_SCROLLLOCK | K_NUMLOCK | K_CAPSLOCK) << 8)) | new_mask;
		} while (!ATOMIC_CMPXCH(me->kd_mods, old_mods, new_mods));
	}	break;

	/* TODO: Add an ioctl() to pre-calculate _all_ possible ASCII keymap keys.
	 *       This could be useful to improve security at a password prompt,
	 *       since a not-very-nice person could determine which keys were
	 *       pressed since initialization by enumerating all possible keys
	 *       and using a timing side-channel to determine which keys had
	 *       already been cached (the ones that were pressed), and which
	 *       had to be freshly cached then (the ones that weren't) */


	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
		break;
	}
	return 0;
}



/* Initialize/finalize the given keyboard device.
 * NOTE: Drivers that override the `ct_fini' operator of a given keyboard
 *       must ensure that `keyboard_device_fini()' is still invoked by their
 *       override.
 * NOTE: The following operators are intrinsically provided by keyboard,
 *       get initialized by `keyboard_device_init()', and should not be
 *       overwritten:
 *         - ct_read
 *         - ct_ioctl
 *         - ct_stat
 *         - ct_poll */
PUBLIC NOBLOCK void
NOTHROW(KCALL keyboard_device_init)(struct keyboard_device *__restrict self,
                                    struct keyboard_device_ops const *__restrict ops) {
	memcpy(&self->kd_ops, ops, sizeof(struct keyboard_device_ops));
	assert(self->cd_type.ct_driver != NULL);
	self->cd_type.ct_fini  = (void(KCALL *)(struct character_device *__restrict))&keyboard_device_fini;
	self->cd_type.ct_read  = &keyboard_device_read;
	self->cd_type.ct_ioctl = &keyboard_device_ioctl;
	self->cd_type.ct_stat  = &keyboard_device_stat;
	self->cd_type.ct_poll  = &keyboard_device_poll;
	self->kd_flags = K_UNICODE; /* Use unicode by default. */
	/* Enable DBGF12 by default when building with debug enabled. */
#if !defined(NDEBUG) && defined(KEYBOARD_DEVICE_FLAG_DBGF12)
	self->kd_flags |= KEYBOARD_DEVICE_FLAG_DBGF12;
#endif /* !NDEBUG && KEYBOARD_DEVICE_FLAG_DBGF12 */
	keymap_init_en_US(&self->kd_map);
	mutex_cinit(&self->kd_leds_lock);
	atomic_rwlock_cinit(&self->kd_map_lock);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL keyboard_device_fini)(struct keyboard_device *__restrict self) {
	kfree((byte_t *)self->kd_map.km_ext);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_KEYBOARD_C */
