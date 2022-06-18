/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPS2_KEYBOARD_C
#define GUARD_MODPS2_KEYBOARD_C 1
#define _KOS_SOURCE 1

#include "keyboard.h"

#include <kernel/compiler.h>

#include <dev/keyboard.h>
#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/entropy.h>
#include <kernel/isr.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <kos/ioctl/kbd.h>

#include <assert.h>
#include <stdio.h>

#include "keyboard-scansets.h"
#include "ps2.h"

DECL_BEGIN

PRIVATE REF struct ps2_keyboard *ps2_keyboards[PS2_PORTCOUNT];

PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL ps2_keyboard_postkey)(struct ps2_keyboard *__restrict self, u16 key) {
	unsigned int bits;
	assert(key != KEY_NONE); /* Use KEY_UNKNOWN instead! */

	/* Feed a little bit of entropy based on the current timestamp.
	 * We  feed more data during down-up since key-down may just be
	 * the result of a key-repeat (in  which case we can only  feed
	 * data relating to timing inaccuracies)
	 * Otherwise,  we rely on the human element, going off on the
	 * presumption that a human typing will have inherent random-
	 * ness when it comes to how fast they type. */
	bits = 3;
	if (KEY_ISUP(key))
		bits = 12;
	entropy_giveint_nopr(tsc_get(THIS_CPU), bits);

#if 1
	device_getname_lock_acquire(self);
	printk(KERN_DEBUG "[ps2:%q] Post key %#.4I16x [state=%u]\n",
	       device_getname(self), key, (unsigned int)self->pk_state);
	device_getname_lock_release(self);
#endif

	/* Schedule the key */
	if unlikely(!kbddev_putkey_nopr(self, key)) {
		device_getname_lock_acquire(self);
		printk(KERN_WARNING "[ps2:%q] Keyboard buffer is full (dropping %#.4I16x)\n",
		       device_getname(self), key);
		device_getname_lock_release(self);
	}
}

PRIVATE NOBLOCK NOPREEMPT void
NOTHROW(FCALL ps2_keyboard_do_handle_isr)(struct ps2_keyboard *__restrict self) {
	u8 data = inb(PS2_DATA);
	if (data == 0xfa)
		ATOMIC_OR(self->pk_errors, PS2_KEYBOARD_ERROR_ACK);
	else if (data == 0xfe)
		ATOMIC_OR(self->pk_errors, PS2_KEYBOARD_ERROR_RESEND);
	else {
		u16 key;
		switch (self->pk_state) {

		/************************************************************************
		 * Scan set #1                                                          *
		 ************************************************************************/
		case PS2_KEYBOARD_STATE_SS1:
			if (data == 0xe0) {
				self->pk_state = PS2_KEYBOARD_STATE_SS1_E0;
				goto done;
			} else if (data == 0xe1) {
				self->pk_state = PS2_KEYBOARD_STATE_SS1_E1;
				goto done;
			}
			key = ps2_keyboard_ss1[data & 0x7f];
			if (data & 0x80)
				key |= KEY_FRELEASED;
			break;

		case PS2_KEYBOARD_STATE_SS1_E0:
			if (data == 0x2a) {
				self->pk_state = PS2_KEYBOARD_STATE_SS1_E0_2A;
				goto done;
			}
			if (data == 0xb7) {
				self->pk_state = PS2_KEYBOARD_STATE_SS1_E0_B7;
				goto done;
			}
			key = ps2_keyboard_ss1_e0[data & 0x7f];
			if (data & 0x80)
				key |= KEY_FRELEASED;
			self->pk_state = PS2_KEYBOARD_STATE_SS1;
			break;

		case PS2_KEYBOARD_STATE_SS1_E1:
			if (data != 0x1d) {
ss1_reset:
				self->pk_state = PS2_KEYBOARD_STATE_SS1;
				key = KEY_UNKNOWN;
				break;
			}
			self->pk_state = PS2_KEYBOARD_STATE_SS1_E1_1D;
			goto done;

		case PS2_KEYBOARD_STATE_SS1_E1_1D:
			if (data != 0x45)
				goto ss1_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS1_E1_1D_45;
			goto done;

		case PS2_KEYBOARD_STATE_SS1_E1_1D_45:
			if (data != 0x91)
				goto ss1_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS1_E1_1D_45_91;
			goto done;

		case PS2_KEYBOARD_STATE_SS1_E1_1D_45_91:
			if (data != 0x9d)
				goto ss1_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS1_E1_1D_45_91_9D;
			goto done;

		case PS2_KEYBOARD_STATE_SS1_E1_1D_45_91_9D:
			if (data != 0xc5)
				goto ss1_reset;
			ps2_keyboard_postkey(self, KEY_PAUSE); /* Make */
			key = KEY_PAUSE | KEY_FRELEASED;       /* Break */
			self->pk_state = PS2_KEYBOARD_STATE_SS1;
			break;

		case PS2_KEYBOARD_STATE_SS1_E0_2A:
			if (data != 0xe0)
				goto ss1_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS1_E0_2A_E0;
			goto done;

		case PS2_KEYBOARD_STATE_SS1_E0_2A_E0:
			if (data != 0x37)
				goto ss1_reset;
			key = KEY_PRINTSCREEN;
			self->pk_state = PS2_KEYBOARD_STATE_SS1;
			break;

		case PS2_KEYBOARD_STATE_SS1_E0_B7:
			if (data != 0xe0)
				goto ss1_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS1_E0_B7_E0;
			goto done;

		case PS2_KEYBOARD_STATE_SS1_E0_B7_E0:
			if (data != 0xaa)
				goto ss1_reset;
			key = KEY_PRINTSCREEN | KEY_FRELEASED;
			self->pk_state = PS2_KEYBOARD_STATE_SS1;
			break;



		/************************************************************************
		 * Scan set #2                                                          *
		 ************************************************************************/
		case PS2_KEYBOARD_STATE_SS2:
			if (data == 0xe0) {
				self->pk_state = PS2_KEYBOARD_STATE_SS2_E0;
				goto done;
			} else if (data == 0xe1) {
				self->pk_state = PS2_KEYBOARD_STATE_SS2_E1;
				goto done;
			} else if (data == 0xf0) {
				self->pk_state = PS2_KEYBOARD_STATE_SS2_F0;
				goto done;
			}
			if likely(data < COMPILER_LENOF(ps2_keyboard_ss2)) {
				key = ps2_keyboard_ss2[data];
			} else {
				key = KEY_UNKNOWN;
			}
			break;

		case PS2_KEYBOARD_STATE_SS2_E0:
			if (data == 0x12) {
				self->pk_state = PS2_KEYBOARD_STATE_SS2_E0_12;
				goto done;
			} else if (data == 0xf0) {
				self->pk_state = PS2_KEYBOARD_STATE_SS2_E0_F0;
				goto done;
			}
			if likely(data < COMPILER_LENOF(ps2_keyboard_ss2_e0)) {
				key = ps2_keyboard_ss2_e0[data];
			} else {
				key = KEY_UNKNOWN;
			}
			self->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;

		case PS2_KEYBOARD_STATE_SS2_E0_12:
			if (data != 0xe0) {
ss2_reset:
				self->pk_state = PS2_KEYBOARD_STATE_SS2;
				key = KEY_UNKNOWN;
				break;
			}
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E0_12_E0;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E0_12_E0:
			if (data != 0x7c)
				goto ss2_reset;
			key = KEY_PRINTSCREEN;
			self->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;

		case PS2_KEYBOARD_STATE_SS2_E0_F0:
			if (data == 0x7c) {
				self->pk_state = PS2_KEYBOARD_STATE_SS2_E0_F0_7C;
				goto done;
			}
			if likely(data < COMPILER_LENOF(ps2_keyboard_ss2_e0)) {
				key = KEY_FRELEASED | ps2_keyboard_ss2_e0[data];
			} else {
				key = KEY_FRELEASED | KEY_UNKNOWN;
			}
			self->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;

		case PS2_KEYBOARD_STATE_SS2_E0_F0_7C:
			if (data != 0xe0)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E0_F0_7C_E0;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E0_F0_7C_E0:
			if (data != 0xf0)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E0_F0_7C_E0_F0;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E0_F0_7C_E0_F0:
			if (data != 0x12)
				goto ss2_reset;
			key = KEY_FRELEASED | KEY_PRINTSCREEN;
			self->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;

		case PS2_KEYBOARD_STATE_SS2_E1:
			if (data != 0x14)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E1_14;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E1_14:
			if (data != 0x77)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E1_14_77;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E1_14_77:
			if (data != 0xe1)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E1_14_77_E1;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E1_14_77_E1:
			if (data != 0xf0)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0:
			if (data != 0x14)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0_14;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0_14:
			if (data != 0xf0)
				goto ss2_reset;
			self->pk_state = PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0_14_F0;
			goto done;

		case PS2_KEYBOARD_STATE_SS2_E1_14_77_E1_F0_14_F0:
			if (data != 0x77)
				goto ss2_reset;
			ps2_keyboard_postkey(self, KEY_PAUSE); /* Make */
			key = KEY_PAUSE | KEY_FRELEASED;       /* Break */
			self->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;

		case PS2_KEYBOARD_STATE_SS2_F0:
			if likely(data < COMPILER_LENOF(ps2_keyboard_ss2)) {
				key = KEY_FRELEASED | ps2_keyboard_ss2[data];
			} else {
				key = KEY_FRELEASED | KEY_UNKNOWN;
			}
			self->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;


		/************************************************************************
		 * Scan set #3                                                          *
		 ************************************************************************/
		case PS2_KEYBOARD_STATE_SS3:
			if (data == 0xf0) {
				self->pk_state = PS2_KEYBOARD_STATE_SS3_F0;
				goto done;
			}
			key = ps2_keyboard_ss3[data];
			break;

		case PS2_KEYBOARD_STATE_SS3_F0:
			key = KEY_FRELEASED | ps2_keyboard_ss3[data];
			self->pk_state = PS2_KEYBOARD_STATE_SS3;
			break;

		default:
			__builtin_unreachable();
		}
		ps2_keyboard_postkey(self, key);
	}
done:
	;
}


PRIVATE NOBLOCK NOPREEMPT bool
NOTHROW(FCALL ps2_keyboard_isr_handler)(void *arg) {
	u8 status = inb(PS2_STATUS);
	struct ps2_keyboard *me;
	me = (struct ps2_keyboard *)arg;
	if (status & PS2_STATUS_OUTFULL2) {
		if (me->pk_portno == PS2_PORT2)
			goto do_handle_isr;
	} else if (status & PS2_STATUS_OUTFULL) {
		if (me->pk_portno == PS2_PORT1) {
do_handle_isr:
			ps2_keyboard_do_handle_isr(me);
			return true;
		}
	}
	return false;
}


PRIVATE void KCALL
ps2_keyboard_send_command_byte_and_wait_for_ack(struct ps2_keyboard *__restrict self,
                                                u8 command_byte) THROWS(E_IOERROR) {
	u8 errors;
	unsigned int attempt = 0;
again:
	ATOMIC_WRITE(self->pk_errors, 0);
	ps2_write_data(self->pk_portno, command_byte);
	while ((errors = ATOMIC_READ(self->pk_errors)) == 0) {
		ktime_t tmo;
		task_connect_for_poll(&self->pk_errors_sig);
		errors = ATOMIC_READ(self->pk_errors);
		if unlikely(errors != 0) {
			task_disconnectall();
			break;
		}
		tmo = ktime();
		tmo += relktime_from_milliseconds(ps2_command_timeout);
		if (!task_waitfor(tmo)) {
			errors = ATOMIC_READ(self->pk_errors);
			if (errors != 0)
				break;
			THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HID);
		}
	}
	if (errors & PS2_KEYBOARD_ERROR_ACK)
		return;
	if unlikely(attempt >= ps2_command_attempts)
		THROW(E_IOERROR_ERRORBIT, E_IOERROR_SUBSYSTEM_HID);
	++attempt;
	goto again;
}

PRIVATE void KCALL
ps2_keyboard_setleds(struct kbddev *__restrict self,
                     uintptr_t new_leds) THROWS(E_IOERROR) {
	struct ps2_keyboard *me;
	u8 new_ps2_leds;
	me = (struct ps2_keyboard *)self;
	new_ps2_leds = 0;
	if (new_leds & KEYBOARD_LED_SCROLLLOCK)
		new_ps2_leds |= PS2_KEYBOARD_CMD_SETLED_SCROLLLOCK;
	if (new_leds & KEYBOARD_LED_NUMLOCK)
		new_ps2_leds |= PS2_KEYBOARD_CMD_SETLED_NUMLOCK;
	if (new_leds & KEYBOARD_LED_CAPSLOCK)
		new_ps2_leds |= PS2_KEYBOARD_CMD_SETLED_CAPSLOCK;
	shared_lock_acquire(&me->pk_cmdlock);
	RAII_FINALLY { shared_lock_release(&me->pk_cmdlock); };
	ps2_keyboard_send_command_byte_and_wait_for_ack(me, PS2_KEYBOARD_CMD_SETLED);
	ps2_keyboard_send_command_byte_and_wait_for_ack(me, new_ps2_leds);
}


PRIVATE struct kbddev_ops const ps2_keyboard_ops = {
	.ko_cdev = {{{{
		.no_file = {
			.mo_destroy = &kbddev_v_destroy,
			.mo_changed = &kbddev_v_changed,
			.mo_stream  = &kbddev_v_stream_ops,
		},
		.no_wrattr = &kbddev_v_wrattr,
	}}}},
	.ko_setleds = &ps2_keyboard_setleds
};


static_assert(PS2_KEYBOARD_CMD_SCANSET_SET1 == 1);
static_assert(PS2_KEYBOARD_CMD_SCANSET_SET2 == 2);
static_assert(PS2_KEYBOARD_CMD_SCANSET_SET3 == 3);
DEFINE_CMDLINE_PARAM_UINT8_VAR(ps2_keyboard_preferred_scanset, "preferred_scanset", 2);

INTERN ATTR_FREETEXT void KCALL
ps2_keyboard_create(struct ps2_probe_data *__restrict probe_data,
                    ps2_portid_t portno) {
	REF struct ps2_keyboard *kbd;
	u8 used_scanset;
	if unlikely(ps2_keyboards[portno])
		return;
	printk(KERN_INFO "[ps2] Detected keyboard on port #%u\n", portno + 1);
	/* Try to configure scanset #2, but allow the keyboard to ignore
	 * us  and use whatever scanset it indicates we should be using. */
	ps2_probe_run_simple_ack_command(probe_data, portno, PS2_KEYBOARD_CMD_SCANSET);
	if (ps2_keyboard_preferred_scanset < 1 || ps2_keyboard_preferred_scanset > 3)
		ps2_keyboard_preferred_scanset = 2;
	ps2_probe_run_simple_ack_command(probe_data, portno, ps2_keyboard_preferred_scanset);
	ps2_probe_run_simple_ack_command(probe_data, portno, PS2_KEYBOARD_CMD_SCANSET);
	used_scanset = ps2_probe_run_ack_plus_data_command(probe_data, portno, PS2_KEYBOARD_CMD_SCANSET_GET);
	ps2_probe_run_simple_ack_command(probe_data, portno, PS2_KEYBOARD_CMD_ENABLE_SCANNING);
	if unlikely(used_scanset < 1 || used_scanset > 3) {
		printk(KERN_INFO "[ps2] Keyboard on port #%u indicated unknown scanset #%u (use scanset #2 instead)\n",
		       portno + 1, used_scanset);
		used_scanset = 2;
	}

	kbd = (REF struct ps2_keyboard *)kmalloc(sizeof(struct ps2_keyboard), GFP_CALLOC);
	_kbddev_cinit(kbd, &ps2_keyboard_ops);
	kbd->fn_mode   = S_IFCHR | 0644;
	kbd->dv_driver = incref(&drv_self);
	TRY {
		shared_lock_cinit(&kbd->pk_cmdlock);
		kbd->pk_portno = portno;
		switch (used_scanset) {
		case 1:
			kbd->pk_state = PS2_KEYBOARD_STATE_SS1;
			break;
		case 2:
			kbd->pk_state = PS2_KEYBOARD_STATE_SS2;
			break;
		case 3:
			kbd->pk_state = PS2_KEYBOARD_STATE_SS3;
			break;
		default: __builtin_unreachable();
		}
		COMPILER_BARRIER();
		hisr_register_at(PS2_GET_ISR_FOR_PORT(portno), &ps2_keyboard_isr_handler, kbd);
		TRY {
			device_registerf(kbd, MKDEV(DEV_MAJOR_AUTO, 0),
			                 "ps2kbd%u", portno + 1);
		} EXCEPT {
			hisr_unregister_at(PS2_GET_ISR_FOR_PORT(portno), &ps2_keyboard_isr_handler, kbd);
			RETHROW();
		}
	} EXCEPT {
		_kbddev_fini(kbd);
		decref_unlikely(&drv_self);
		kfree(kbd);
		RETHROW();
	}
	ps2_keyboards[portno] = kbd;
}

PRIVATE DRIVER_FINI void KCALL ps2_keyboard_driver_fini(void) {
	if (ps2_keyboards[0]) {
		hisr_unregister_at(PS2_GET_ISR_FOR_PORT(PS2_PORT1),
		                   &ps2_keyboard_isr_handler,
		                   ps2_keyboards[0]);
		device_delete(ps2_keyboards[0]);
		decref(ps2_keyboards[0]);
		ps2_keyboards[0] = NULL;
	}
	if (ps2_keyboards[1]) {
		hisr_unregister_at(PS2_GET_ISR_FOR_PORT(PS2_PORT2),
		                   &ps2_keyboard_isr_handler,
		                   ps2_keyboards[1]);
		device_delete(ps2_keyboards[1]);
		decref(ps2_keyboards[1]);
		ps2_keyboards[1] = NULL;
	}
}


DECL_END

#endif /* !GUARD_MODPS2_KEYBOARD_C */
