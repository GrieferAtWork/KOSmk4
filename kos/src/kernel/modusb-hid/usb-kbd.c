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
#ifndef GUARD_MODUSB_HID_USB_KBD_C
#define GUARD_MODUSB_HID_USB_KBD_C 1

#include "usb-kbd.h"

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/driver.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <kos/io/usb-class.h>
#include <kos/io/usb-hid.h>
#include <kos/io/usb.h>

#include <kos/keyboard.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

PRIVATE NOBLOCK void
NOTHROW(FCALL usb_keyboard_post)(struct usb_keyboard_device *__restrict self, u16 key) {
	if (!key)
		return; /* No-op */
	if unlikely(!keyboard_device_putkey_nopr(self, key)) {
		printk(KERN_WARNING "[usb:%q] Keyboard buffer is full (dropping %#.4I16x)\n",
		       self->cd_name, key);
	}
}

PRIVATE u16 const usb_mod_table[8] = {
	/* [CTZ(0x01)] = */ KEY_LEFTCTRL,
	/* [CTZ(0x02)] = */ KEY_LEFTSHIFT,
	/* [CTZ(0x04)] = */ KEY_LEFTALT,
	/* [CTZ(0x08)] = */ KEY_LEFTMETA,
	/* [CTZ(0x10)] = */ KEY_RIGHTCTRL,
	/* [CTZ(0x20)] = */ KEY_RIGHTSHIFT,
	/* [CTZ(0x40)] = */ KEY_RIGHTALT,
	/* [CTZ(0x80)] = */ KEY_RIGHTMETA,
};

PRIVATE u16 const usb_key_table[256] = {
/*[[[deemon
// Sources:
//   - https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2
//   - https://www.win.tue.nl/~aeb/linux/kbd/scancodes-14.html

local keys = ["0"] * 256;

keys[0x04] = "KEY_A";
keys[0x05] = "KEY_B";
keys[0x06] = "KEY_C";
keys[0x07] = "KEY_D";
keys[0x08] = "KEY_E";
keys[0x09] = "KEY_F";
keys[0x0a] = "KEY_G";
keys[0x0b] = "KEY_H";
keys[0x0c] = "KEY_I";
keys[0x0d] = "KEY_J";
keys[0x0e] = "KEY_K";
keys[0x0f] = "KEY_L";
keys[0x10] = "KEY_M";
keys[0x11] = "KEY_N";
keys[0x12] = "KEY_O";
keys[0x13] = "KEY_P";
keys[0x14] = "KEY_Q";
keys[0x15] = "KEY_R";
keys[0x16] = "KEY_S";
keys[0x17] = "KEY_T";
keys[0x18] = "KEY_U";
keys[0x19] = "KEY_V";
keys[0x1a] = "KEY_W";
keys[0x1b] = "KEY_X";
keys[0x1c] = "KEY_Y";
keys[0x1d] = "KEY_Z";
keys[0x1e] = "KEY_1";
keys[0x1f] = "KEY_2";
keys[0x20] = "KEY_3";
keys[0x21] = "KEY_4";
keys[0x22] = "KEY_5";
keys[0x23] = "KEY_6";
keys[0x24] = "KEY_7";
keys[0x25] = "KEY_8";
keys[0x26] = "KEY_9";
keys[0x27] = "KEY_0";

keys[0x28] = "KEY_ENTER";
keys[0x29] = "KEY_ESC";
keys[0x2a] = "KEY_BACKSPACE";
keys[0x2b] = "KEY_TAB";
keys[0x2c] = "KEY_SPACE";
keys[0x2d] = "KEY_MINUS";
keys[0x2e] = "KEY_EQUAL";
keys[0x2f] = "KEY_LEFTBRACE";
keys[0x30] = "KEY_RIGHTBRACE";
keys[0x31] = "KEY_BACKSLASH";
keys[0x32] = "KEY_APOSTROPHE";
keys[0x33] = "KEY_SEMICOLON";
keys[0x34] = "KEY_APOSTROPHE";
keys[0x35] = "KEY_GRAVE";
keys[0x36] = "KEY_COMMA";
keys[0x37] = "KEY_DOT";
keys[0x38] = "KEY_SLASH";
keys[0x39] = "KEY_CAPSLOCK";
keys[0x3a] = "KEY_F1";
keys[0x3b] = "KEY_F2";
keys[0x3c] = "KEY_F3";
keys[0x3d] = "KEY_F4";
keys[0x3e] = "KEY_F5";
keys[0x3f] = "KEY_F6";
keys[0x40] = "KEY_F7";
keys[0x41] = "KEY_F8";
keys[0x42] = "KEY_F9";
keys[0x43] = "KEY_F10";
keys[0x44] = "KEY_F11";
keys[0x45] = "KEY_F12";
keys[0x46] = "KEY_PRINTSCREEN";
keys[0x47] = "KEY_SCROLLLOCK";
keys[0x48] = "KEY_PAUSE";
keys[0x49] = "KEY_INSERT";
keys[0x4a] = "KEY_HOME";
keys[0x4b] = "KEY_PAGEUP";
keys[0x4c] = "KEY_DELETE";
keys[0x4d] = "KEY_END";
keys[0x4e] = "KEY_PAGEDOWN";
keys[0x4f] = "KEY_RIGHT";
keys[0x50] = "KEY_LEFT";
keys[0x51] = "KEY_DOWN";
keys[0x52] = "KEY_UP";
keys[0x53] = "KEY_NUMLOCK";
keys[0x54] = "KEY_KPSLASH";
keys[0x55] = "KEY_KPASTERISK";
keys[0x56] = "KEY_KPMINUS";
keys[0x57] = "KEY_KPPLUS";
keys[0x58] = "KEY_KPENTER";
keys[0x59] = "KEY_KP1";
keys[0x5a] = "KEY_KP2";
keys[0x5b] = "KEY_KP3";
keys[0x5c] = "KEY_KP4";
keys[0x5d] = "KEY_KP5";
keys[0x5e] = "KEY_KP6";
keys[0x5f] = "KEY_KP7";
keys[0x60] = "KEY_KP8";
keys[0x61] = "KEY_KP9";
keys[0x62] = "KEY_KP0";
keys[0x63] = "KEY_KPDOT";
keys[0x64] = "KEY_102ND";
keys[0x65] = "KEY_COMPOSE";
keys[0x66] = "KEY_POWER";
keys[0x67] = "KEY_KPEQUAL";
keys[0x68] = "KEY_F13";
keys[0x69] = "KEY_F14";
keys[0x6a] = "KEY_F15";
keys[0x6b] = "KEY_F16";
keys[0x6c] = "KEY_F17";
keys[0x6d] = "KEY_F18";
keys[0x6e] = "KEY_F19";
keys[0x6f] = "KEY_F20";
keys[0x70] = "KEY_F21";
keys[0x71] = "KEY_F22";
keys[0x72] = "KEY_F23";
keys[0x73] = "KEY_F24";
keys[0x74] = "KEY_OPEN";
keys[0x75] = "KEY_HELP";
keys[0x76] = "KEY_PROPS";
keys[0x77] = "KEY_FRONT";
keys[0x78] = "KEY_STOP";
keys[0x79] = "KEY_AGAIN";
keys[0x7a] = "KEY_UNDO";
keys[0x7b] = "KEY_CUT";
keys[0x7c] = "KEY_COPY";
keys[0x7d] = "KEY_PASTE";
keys[0x7e] = "KEY_FIND";
keys[0x7f] = "KEY_MUTE";
keys[0x80] = "KEY_VOLUMEUP";
keys[0x81] = "KEY_VOLUMEDOWN";
// 0x82  Keyboard Locking Caps Lock
// 0x83  Keyboard Locking Num Lock
// 0x84  Keyboard Locking Scroll Lock
keys[0x85] = "KEY_KPCOMMA";
keys[0x86] = "KEY_KPEQUAL";
keys[0x87] = "KEY_RO";
keys[0x88] = "KEY_KATAKANAHIRAGANA";
keys[0x89] = "KEY_YEN";
keys[0x8a] = "KEY_HENKAN";
keys[0x8b] = "KEY_MUHENKAN";
keys[0x8c] = "KEY_KPJPCOMMA";
// 0x8d  Keyboard International7
// 0x8e  Keyboard International8
// 0x8f  Keyboard International9
keys[0x90] = "KEY_HANGEUL";
keys[0x91] = "KEY_HANJA";
keys[0x92] = "KEY_KATAKANA";
keys[0x93] = "KEY_HIRAGANA";
keys[0x94] = "KEY_ZENKAKUHANKAKU";
// 0x95  Keyboard LANG6
// 0x96  Keyboard LANG7
// 0x97  Keyboard LANG8
// 0x98  Keyboard LANG9
// 0x99  Keyboard Alternate Erase
keys[0x9a] = "KEY_SYSRQ";
keys[0x9b] = "KEY_CANCEL";
keys[0x9c] = "KEY_CLEAR";
keys[0x9d] = "KEY_PREVIOUS";
// 0x9e  Keyboard Return
// 0x9f  Keyboard Separator
// 0xa0  Keyboard Out
// 0xa1  Keyboard Open
// 0xa2  Keyboard Clear/Again
// 0xa3  Keyboard CrSel/Props
// 0xa4  Keyboard ExSel

// 0xb0  Keypad 00
// 0xb1  Keypad 000
// 0xb2  Thousands Separator
// 0xb3  Decimal Separator
// 0xb4  Currency Unit
// 0xb5  Currency Sub-unit
keys[0xb6] = "KEY_KPLEFTPAREN";
keys[0xb7] = "KEY_KPRIGHTPAREN";
// 0xb8  Keypad {
// 0xb9  Keypad }
// 0xba  Keypad Tab
// 0xbb  Keypad Backspace
// 0xbc  Keypad A
// 0xbd  Keypad B
// 0xbe  Keypad C
// 0xbf  Keypad D
// 0xc0  Keypad E
// 0xc1  Keypad F
// 0xc2  Keypad XOR
// 0xc3  Keypad ^
// 0xc4  Keypad %
// 0xc5  Keypad <
// 0xc6  Keypad >
// 0xc7  Keypad &
// 0xc8  Keypad &&
// 0xc9  Keypad |
// 0xca  Keypad ||
// 0xcb  Keypad :
// 0xcc  Keypad #
// 0xcd  Keypad Space
// 0xce  Keypad @
// 0xcf  Keypad !
// 0xd0  Keypad Memory Store
// 0xd1  Keypad Memory Recall
// 0xd2  Keypad Memory Clear
// 0xd3  Keypad Memory Add
// 0xd4  Keypad Memory Subtract
// 0xd5  Keypad Memory Multiply
// 0xd6  Keypad Memory Divide
// 0xd7  Keypad +/-
// 0xd8  Keypad Clear
// 0xd9  Keypad Clear Entry
// 0xda  Keypad Binary
// 0xdb  Keypad Octal
// 0xdc  Keypad Decimal
// 0xdd  Keypad Hexadecimal

keys[0xe0] = "KEY_LEFTCTRL";
keys[0xe1] = "KEY_LEFTSHIFT";
keys[0xe2] = "KEY_LEFTALT";
keys[0xe3] = "KEY_LEFTMETA";
keys[0xe4] = "KEY_RIGHTCTRL";
keys[0xe5] = "KEY_RIGHTSHIFT";
keys[0xe6] = "KEY_RIGHTALT";
keys[0xe7] = "KEY_RIGHTMETA";
keys[0xe8] = "KEY_MM_PLAY_PAUSE";
keys[0xe9] = "KEY_MM_STOP";
keys[0xea] = "KEY_MM_PREVIOUS_TRACK";
keys[0xeb] = "KEY_MM_NEXT_TRACK";
keys[0xec] = "KEY_EJECTCD";
keys[0xed] = "KEY_VOLUMEUP";
keys[0xee] = "KEY_VOLUMEDOWN";
keys[0xef] = "KEY_MUTE";
keys[0xf0] = "KEY_WWW";
keys[0xf1] = "KEY_WWW_BACK";
keys[0xf2] = "KEY_WWW_FORWARD";
keys[0xf3] = "KEY_MM_STOP";
keys[0xf4] = "KEY_WWW_SEARCH";
keys[0xf5] = "KEY_SCROLLUP";
keys[0xf6] = "KEY_SCROLLDOWN";
keys[0xf7] = "KEY_EDIT";
keys[0xf8] = "KEY_APIC_SLEEP";
keys[0xf9] = "KEY_COFFEE";
keys[0xfa] = "KEY_REFRESH";
keys[0xfb] = "KEY_CALC";

for (local i: [:256]) {
	if ((i % 16) == 0)
		print "\t",;
	print keys[i],;
	print ",",;
	if ((i % 16) == 15)
		print "\n",;
	else {
		print " ",;
	}
}
]]]*/
	0, 0, 0, 0, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L,
	KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_1, KEY_2,
	KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUAL, KEY_LEFTBRACE,
	KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_APOSTROPHE, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_GRAVE, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_CAPSLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
	KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINTSCREEN, KEY_SCROLLLOCK, KEY_PAUSE, KEY_INSERT, KEY_HOME, KEY_PAGEUP, KEY_DELETE, KEY_END, KEY_PAGEDOWN, KEY_RIGHT,
	KEY_LEFT, KEY_DOWN, KEY_UP, KEY_NUMLOCK, KEY_KPSLASH, KEY_KPASTERISK, KEY_KPMINUS, KEY_KPPLUS, KEY_KPENTER, KEY_KP1, KEY_KP2, KEY_KP3, KEY_KP4, KEY_KP5, KEY_KP6, KEY_KP7,
	KEY_KP8, KEY_KP9, KEY_KP0, KEY_KPDOT, KEY_102ND, KEY_COMPOSE, KEY_POWER, KEY_KPEQUAL, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20,
	KEY_F21, KEY_F22, KEY_F23, KEY_F24, KEY_OPEN, KEY_HELP, KEY_PROPS, KEY_FRONT, KEY_STOP, KEY_AGAIN, KEY_UNDO, KEY_CUT, KEY_COPY, KEY_PASTE, KEY_FIND, KEY_MUTE,
	KEY_VOLUMEUP, KEY_VOLUMEDOWN, 0, 0, 0, KEY_KPCOMMA, KEY_KPEQUAL, KEY_RO, KEY_KATAKANAHIRAGANA, KEY_YEN, KEY_HENKAN, KEY_MUHENKAN, KEY_KPJPCOMMA, 0, 0, 0,
	KEY_HANGEUL, KEY_HANJA, KEY_KATAKANA, KEY_HIRAGANA, KEY_ZENKAKUHANKAKU, 0, 0, 0, 0, 0, KEY_SYSRQ, KEY_CANCEL, KEY_CLEAR, KEY_PREVIOUS, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, KEY_KPLEFTPAREN, KEY_KPRIGHTPAREN, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	KEY_LEFTCTRL, KEY_LEFTSHIFT, KEY_LEFTALT, KEY_LEFTMETA, KEY_RIGHTCTRL, KEY_RIGHTSHIFT, KEY_RIGHTALT, KEY_RIGHTMETA, KEY_MM_PLAY_PAUSE, KEY_MM_STOP, KEY_MM_PREVIOUS_TRACK, KEY_MM_NEXT_TRACK, KEY_EJECTCD, KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_MUTE,
	KEY_WWW, KEY_WWW_BACK, KEY_WWW_FORWARD, KEY_MM_STOP, KEY_WWW_SEARCH, KEY_SCROLLUP, KEY_SCROLLDOWN, KEY_EDIT, KEY_APIC_SLEEP, KEY_COFFEE, KEY_REFRESH, KEY_CALC, 0, 0, 0, 0,
//[[[end]]]
};


PRIVATE NOBLOCK unsigned int
NOTHROW(KCALL usb_keyboard_interrupt_handler)(struct character_device *__restrict self,
                                              unsigned int status,
                                              void const *data, size_t datalen) {
	struct usb_keyboard_device *me;
	me = (struct usb_keyboard_device *)self;
	if (status == USB_INTERRUPT_HANDLER_STATUS_OK) {
		u8 mod_now, mod_delta;
		u16 key;
		unsigned int i;
		bool did_post_something = false;
		assert(datalen == 8);
		printk(KERN_NOTICE "[usb-hid] %$[hex]\n", 8, data);
		mod_now   = ((byte_t *)data)[0];
		mod_delta = mod_now ^ me->uk_last[0];
		if (mod_delta != 0) {
			/* `mod_delta' is the bitset of changed modifier keys. */
			for (i = 0; i < 8; ++i) {
				u8 mask = (u8)1 << i;
				if (!(mod_delta & mask))
					continue;
				key = usb_mod_table[i];
				if (!(mod_now & mask))
					key |= KEY_FRELEASED;
				usb_keyboard_post(me, key);
				did_post_something = true;
			}
		}
		/* Check for (and ignore) key roll-over */
		if (((byte_t *)data)[2] == 0x01) {
			for (i = 3; i < 8; ++i) {
				if (((byte_t *)data)[i] != 0x01)
					goto do_check_keys;
			}
			printk(KERN_NOTICE "[usb-hid] Keyboard roll-over detected (don't press so many keys at once)\n");
			goto done_notlast;
		}

do_check_keys:
		/* Check for keys that are being pressed. */
		for (i = 2; i < 8; ++i) {
			u8 k = ((byte_t *)data)[i];
			if (!k)
				continue;
			/* Check if the key was already held before. */
			if (memchr(me->uk_last + 2, k, 6))
				continue;
			key = usb_key_table[k];
			usb_keyboard_post(me, key);
			did_post_something = true;
		}
		/* Check for keys that are being released. */
		for (i = 2; i < 8; ++i) {
			u8 k = me->uk_last[i];
			if (!k)
				continue;
			/* Check if the key is still being held. */
			if (memchr((byte_t *)data + 2, k, 6))
				continue;
			key = usb_key_table[k] | KEY_FRELEASED;
			usb_keyboard_post(me, key);
			did_post_something = true;
		}
		/* If we haven't already posted anything, then take the
		 * last key from the set of held keys, and post it as a
		 * a repeat event. */
		if (!did_post_something) {
			u8 k;
			i = 7;
			for (;;) {
				k = ((byte_t *)data)[i];
				if (k)
					break;
				if (i == 2) {
					/* Check if the repeat happened because of modifier keys being repeated. */
					if (mod_now != 0) {
						for (i = 0; !(mod_now & ((u8)1 << i)); ++i)
							;
						key = usb_mod_table[i] | KEY_FREPEAT;
						usb_keyboard_post(me, key);
						goto done;
					}
					printk(KERN_WARNING "[usb-hid] Keyboard interrupt without anything happening?\n");
					goto done;
				}
				--i;
			}
			key = usb_key_table[k] | KEY_FREPEAT;
			usb_keyboard_post(me, key);
		}
done:
		memcpy(me->uk_last, data, 8);
done_notlast:
		;
	}
	return USB_INTERRUPT_HANDLER_RETURN_SCHED;
}


PRIVATE NOBLOCK void
NOTHROW(KCALL usb_keyboard_fini)(struct character_device *__restrict self) {
	struct usb_keyboard_device *me;
	me = (struct usb_keyboard_device *)self;
	if (me->uk_intr)
		usb_interrupt_delete(me->uk_intr);
	xdecref(me->uk_data);
	xdecref(me->uk_intf);
	xdecref(me->uk_ctrl);
	keyboard_device_fini(me);
}

PRIVATE struct keyboard_device_ops const usb_keyboard_ops = {
	/* .ko_setleds = */ NULL /* TODO */
};


INTERN bool KCALL
usb_keyboard_probe(struct usb_controller *__restrict self,
                   struct usb_interface *__restrict intf,
                   size_t endpc, struct usb_endpoint *const endpv[]) {
	size_t i;
	struct usb_endpoint *data;
	struct usb_request req;
	REF struct usb_keyboard_device *result;
	data = NULL;
	for (i = 0; i < endpc; ++i) {
		struct usb_endpoint *e;
		e = endpv[i];
		if (!(e->ue_flags & USB_ENDPOINT_FLAG_INPUT))
			continue; /* We need an input endpoint! */
		if (data) {
			printk(KERN_WARNING "[usb-hid] Multiple keyboard input endpoints (using %I8u, but %I8u also exists)\n",
			       data->ue_endp, e->ue_endp);
		} else {
			data = e;
		}
	}
	if unlikely(!data) {
		printk(KERN_ERR "[usb-hid] Failed to find keyboard data endpoint\n");
		return false;
	}
	printk(KERN_NOTICE "[usb-hid] Keyboard device detected\n");

	/* Configure the keyboard to only send interrupts when it detects changes. */
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_INTF |
	                 USB_REQUEST_RETYPE_TYPE_CLS |
	                 USB_REQUEST_RETYPE_DIR_H2D;
	req.ur_request = USB_REQUEST_SET_IDLE;
	req.ur_value   = 0;
	req.ur_index   = data->ue_interface->ui_intf;
	req.ur_length  = 0;
	usb_controller_request_sync(self, data->ue_interface, &req, NULL);

	/* Allocate the keyboard device. */
	result = CHARACTER_DEVICE_ALLOC(struct usb_keyboard_device);
	keyboard_device_init(result, &usb_keyboard_ops);
	result->cd_type.ct_fini = &usb_keyboard_fini;
	FINALLY_DECREF_UNLIKELY(result);

	/* Initialize the new keyboard device. */
	result->uk_ctrl = (REF struct usb_controller *)incref(self);
	result->uk_intf = (REF struct usb_interface *)incref(intf);
	result->uk_data = incref(data);
	result->uk_intr = usb_controller_interrupt_create(self, data,
	                                                  &usb_keyboard_interrupt_handler,
	                                                  result, 8);

	{
		static int n = 0; /* TODO: Better naming */
		sprintf(result->cd_name, "usbkb%c", 'a' + n++);
	}
	/* Register the new device. */
	character_device_register_auto(result);
	return true;
}



DECL_END

#endif /* !GUARD_MODUSB_HID_USB_KBD_C */
