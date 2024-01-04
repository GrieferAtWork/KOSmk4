/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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

#include <hw/hid/usb-hid.h>
#include <hw/hid/usbkbd.h>
#include <hw/usb/class.h>
#include <hw/usb/usb.h>
#include <kos/keyboard.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

PRIVATE NOBLOCK void
NOTHROW(FCALL usb_keyboard_post)(struct usb_keyboard_device *__restrict self, u16 key) {
	if (!key)
		return; /* No-op */
	if unlikely(!kbddev_putkey_nopr(self, key)) {
		printk(KERN_WARNING "[usb:%q] Keyboard buffer is full (dropping %#.4I16x)\n",
		       self->cd_name, key);
	}
}

PRIVATE u16 const usb_mod_table[8] = {
	[USBKBD_MODSHIFT_LEFTCTRL]  = KEY_LEFTCTRL,
	[USBKBD_MODSHIFT_LEFTSHIFT] = KEY_LEFTSHIFT,
	[USBKBD_MODSHIFT_LEFTALT]   = KEY_LEFTALT,
	[USBKBD_MODSHIFT_LEFTMETA]  = KEY_LEFTMETA,
	[USBKBD_MODSHIFT_RIGHTCTRL] = KEY_RIGHTCTRL,
	[USBKBD_MODSHIFT_RIGHTSHIF] = KEY_RIGHTSHIFT,
	[USBKBD_MODSHIFT_RIGHTALT]  = KEY_RIGHTALT,
	[USBKBD_MODSHIFT_RIGHTMETA] = KEY_RIGHTMETA,
};

PRIVATE u16 const usb_key_table[256] = {
	[0x00]                              = KEY_NONE,
	[0x01]                              = KEY_NONE,
	[0x02]                              = KEY_NONE,
	[0x03]                              = KEY_NONE,
	[USBKBD_KEY_A]                      = KEY_A,
	[USBKBD_KEY_B]                      = KEY_B,
	[USBKBD_KEY_C]                      = KEY_C,
	[USBKBD_KEY_D]                      = KEY_D,
	[USBKBD_KEY_E]                      = KEY_E,
	[USBKBD_KEY_F]                      = KEY_F,
	[USBKBD_KEY_G]                      = KEY_G,
	[USBKBD_KEY_H]                      = KEY_H,
	[USBKBD_KEY_I]                      = KEY_I,
	[USBKBD_KEY_J]                      = KEY_J,
	[USBKBD_KEY_K]                      = KEY_K,
	[USBKBD_KEY_L]                      = KEY_L,
	[USBKBD_KEY_M]                      = KEY_M,
	[USBKBD_KEY_N]                      = KEY_N,
	[USBKBD_KEY_O]                      = KEY_O,
	[USBKBD_KEY_P]                      = KEY_P,
	[USBKBD_KEY_Q]                      = KEY_Q,
	[USBKBD_KEY_R]                      = KEY_R,
	[USBKBD_KEY_S]                      = KEY_S,
	[USBKBD_KEY_T]                      = KEY_T,
	[USBKBD_KEY_U]                      = KEY_U,
	[USBKBD_KEY_V]                      = KEY_V,
	[USBKBD_KEY_W]                      = KEY_W,
	[USBKBD_KEY_X]                      = KEY_X,
	[USBKBD_KEY_Y]                      = KEY_Y,
	[USBKBD_KEY_Z]                      = KEY_Z,
	[USBKBD_KEY_1]                      = KEY_1,
	[USBKBD_KEY_2]                      = KEY_2,
	[USBKBD_KEY_3]                      = KEY_3,
	[USBKBD_KEY_4]                      = KEY_4,
	[USBKBD_KEY_5]                      = KEY_5,
	[USBKBD_KEY_6]                      = KEY_6,
	[USBKBD_KEY_7]                      = KEY_7,
	[USBKBD_KEY_8]                      = KEY_8,
	[USBKBD_KEY_9]                      = KEY_9,
	[USBKBD_KEY_0]                      = KEY_0,
	[USBKBD_KEY_ENTER]                  = KEY_ENTER,
	[USBKBD_KEY_ESC]                    = KEY_ESC,
	[USBKBD_KEY_BACKSPACE]              = KEY_BACKSPACE,
	[USBKBD_KEY_TAB]                    = KEY_TAB,
	[USBKBD_KEY_SPACE]                  = KEY_SPACE,
	[USBKBD_KEY_MINUS]                  = KEY_MINUS,
	[USBKBD_KEY_EQUAL]                  = KEY_EQUAL,
	[USBKBD_KEY_LEFTBRACE]              = KEY_LEFTBRACE,
	[USBKBD_KEY_RIGHTBRACE]             = KEY_RIGHTBRACE,
	[USBKBD_KEY_BACKSLASH]              = KEY_BACKSLASH,
	[USBKBD_KEY_POUND]                  = KEY_APOSTROPHE,
	[USBKBD_KEY_SEMICOLON]              = KEY_SEMICOLON,
	[USBKBD_KEY_APOSTROPHE]             = KEY_APOSTROPHE,
	[USBKBD_KEY_GRAVE]                  = KEY_GRAVE,
	[USBKBD_KEY_COMMA]                  = KEY_COMMA,
	[USBKBD_KEY_DOT]                    = KEY_DOT,
	[USBKBD_KEY_SLASH]                  = KEY_SLASH,
	[USBKBD_KEY_CAPSLOCK]               = KEY_CAPSLOCK,
	[USBKBD_KEY_F1]                     = KEY_F1,
	[USBKBD_KEY_F2]                     = KEY_F2,
	[USBKBD_KEY_F3]                     = KEY_F3,
	[USBKBD_KEY_F4]                     = KEY_F4,
	[USBKBD_KEY_F5]                     = KEY_F5,
	[USBKBD_KEY_F6]                     = KEY_F6,
	[USBKBD_KEY_F7]                     = KEY_F7,
	[USBKBD_KEY_F8]                     = KEY_F8,
	[USBKBD_KEY_F9]                     = KEY_F9,
	[USBKBD_KEY_F10]                    = KEY_F10,
	[USBKBD_KEY_F11]                    = KEY_F11,
	[USBKBD_KEY_F12]                    = KEY_F12,
	[USBKBD_KEY_PRINTSCREEN]            = KEY_PRINTSCREEN,
	[USBKBD_KEY_SCROLLLOCK]             = KEY_SCROLLLOCK,
	[USBKBD_KEY_PAUSE]                  = KEY_PAUSE,
	[USBKBD_KEY_INSERT]                 = KEY_INSERT,
	[USBKBD_KEY_HOME]                   = KEY_HOME,
	[USBKBD_KEY_PAGEUP]                 = KEY_PAGEUP,
	[USBKBD_KEY_DELETE]                 = KEY_DELETE,
	[USBKBD_KEY_END]                    = KEY_END,
	[USBKBD_KEY_PAGEDOWN]               = KEY_PAGEDOWN,
	[USBKBD_KEY_RIGHT]                  = KEY_RIGHT,
	[USBKBD_KEY_LEFT]                   = KEY_LEFT,
	[USBKBD_KEY_DOWN]                   = KEY_DOWN,
	[USBKBD_KEY_UP]                     = KEY_UP,
	[USBKBD_KEY_NUMLOCK]                = KEY_NUMLOCK,
	[USBKBD_KEY_KPSLASH]                = KEY_KPSLASH,
	[USBKBD_KEY_KPASTERISK]             = KEY_KPASTERISK,
	[USBKBD_KEY_KPMINUS]                = KEY_KPMINUS,
	[USBKBD_KEY_KPPLUS]                 = KEY_KPPLUS,
	[USBKBD_KEY_KPENTER]                = KEY_KPENTER,
	[USBKBD_KEY_KP1]                    = KEY_KP1,
	[USBKBD_KEY_KP2]                    = KEY_KP2,
	[USBKBD_KEY_KP3]                    = KEY_KP3,
	[USBKBD_KEY_KP4]                    = KEY_KP4,
	[USBKBD_KEY_KP5]                    = KEY_KP5,
	[USBKBD_KEY_KP6]                    = KEY_KP6,
	[USBKBD_KEY_KP7]                    = KEY_KP7,
	[USBKBD_KEY_KP8]                    = KEY_KP8,
	[USBKBD_KEY_KP9]                    = KEY_KP9,
	[USBKBD_KEY_KP0]                    = KEY_KP0,
	[USBKBD_KEY_KPDOT]                  = KEY_KPDOT,
	[USBKBD_KEY_102ND]                  = KEY_102ND,
	[USBKBD_KEY_COMPOSE]                = KEY_COMPOSE,
	[USBKBD_KEY_POWER]                  = KEY_POWER,
	[USBKBD_KEY_KPEQUAL]                = KEY_KPEQUAL,
	[USBKBD_KEY_F13]                    = KEY_F13,
	[USBKBD_KEY_F14]                    = KEY_F14,
	[USBKBD_KEY_F15]                    = KEY_F15,
	[USBKBD_KEY_F16]                    = KEY_F16,
	[USBKBD_KEY_F17]                    = KEY_F17,
	[USBKBD_KEY_F18]                    = KEY_F18,
	[USBKBD_KEY_F19]                    = KEY_F19,
	[USBKBD_KEY_F20]                    = KEY_F20,
	[USBKBD_KEY_F21]                    = KEY_F21,
	[USBKBD_KEY_F22]                    = KEY_F22,
	[USBKBD_KEY_F23]                    = KEY_F23,
	[USBKBD_KEY_F24]                    = KEY_F24,
	[USBKBD_KEY_EXECUTE]                = KEY_OPEN,
	[USBKBD_KEY_HELP]                   = KEY_HELP,
	[USBKBD_KEY_PROPS]                  = KEY_PROPS,
	[USBKBD_KEY_FRONT]                  = KEY_FRONT,
	[USBKBD_KEY_STOP]                   = KEY_STOP,
	[USBKBD_KEY_AGAIN]                  = KEY_AGAIN,
	[USBKBD_KEY_UNDO]                   = KEY_UNDO,
	[USBKBD_KEY_CUT]                    = KEY_CUT,
	[USBKBD_KEY_COPY]                   = KEY_COPY,
	[USBKBD_KEY_PASTE]                  = KEY_PASTE,
	[USBKBD_KEY_FIND]                   = KEY_FIND,
	[USBKBD_KEY_MUTE]                   = KEY_MUTE,
	[USBKBD_KEY_VOLUMEUP]               = KEY_VOLUMEUP,
	[USBKBD_KEY_VOLUMEDOWN]             = KEY_VOLUMEDOWN,
	[USBKBD_KEY_LOCKING_CAPS_LOCK]      = KEY_NONE,
	[USBKBD_KEY_LOCKING_NUM_LOCK]       = KEY_NONE,
	[USBKBD_KEY_LOCKING_SCROLL_LOCK]    = KEY_NONE,
	[USBKBD_KEY_KPCOMMA]                = KEY_KPCOMMA,
	[USBKBD_KEY_KPEQUAL2]               = KEY_KPEQUAL,
	[USBKBD_KEY_RO]                     = KEY_RO,
	[USBKBD_KEY_KATAKANAHIRAGANA]       = KEY_KATAKANAHIRAGANA,
	[USBKBD_KEY_YEN]                    = KEY_YEN,
	[USBKBD_KEY_HENKAN]                 = KEY_HENKAN,
	[USBKBD_KEY_MUHENKAN]               = KEY_MUHENKAN,
	[USBKBD_KEY_KPJPCOMMA]              = KEY_KPJPCOMMA,
	[USBKBD_KEY_INTERNATIONAL7]         = KEY_NONE,
	[USBKBD_KEY_INTERNATIONAL8]         = KEY_NONE,
	[USBKBD_KEY_INTERNATIONAL9]         = KEY_NONE,
	[USBKBD_KEY_KEY_HANGEUL]            = KEY_HANGEUL,
	[USBKBD_KEY_KEY_HANJA]              = KEY_HANJA,
	[USBKBD_KEY_KEY_KATAKANA]           = KEY_KATAKANA,
	[USBKBD_KEY_KEY_HIRAGANA]           = KEY_HIRAGANA,
	[USBKBD_KEY_KEY_ZENKAKUHANKAKU]     = KEY_ZENKAKUHANKAKU,
	[USBKBD_KEY_LANG6]                  = KEY_NONE,
	[USBKBD_KEY_LANG7]                  = KEY_NONE,
	[USBKBD_KEY_LANG8]                  = KEY_NONE,
	[USBKBD_KEY_LANG9]                  = KEY_NONE,
	[USBKBD_KEY_ALTERNATE_ERASE]        = KEY_NONE,
	[USBKBD_KEY_SYSRQ]                  = KEY_SYSRQ,
	[USBKBD_KEY_CANCEL]                 = KEY_CANCEL,
	[USBKBD_KEY_CLEAR]                  = KEY_CLEAR,
	[USBKBD_KEY_PREVIOUS]               = KEY_PREVIOUS,
	[USBKBD_KEY_RETURN]                 = KEY_NONE,
	[USBKBD_KEY_SEPARATOR]              = KEY_NONE,
	[USBKBD_KEY_OUT]                    = KEY_NONE,
	[USBKBD_KEY_OPEN]                   = KEY_OPEN,
	[USBKBD_KEY_CLEAR_AGAIN]            = KEY_NONE,
	[USBKBD_KEY_CRSEL_PROPS]            = KEY_NONE,
	[USBKBD_KEY_EXSEL]                  = KEY_NONE,
	[0xa5]                              = KEY_NONE,
	[0xa6]                              = KEY_NONE,
	[0xa7]                              = KEY_NONE,
	[0xa8]                              = KEY_NONE,
	[0xa9]                              = KEY_NONE,
	[0xaa]                              = KEY_NONE,
	[0xab]                              = KEY_NONE,
	[0xac]                              = KEY_NONE,
	[0xad]                              = KEY_NONE,
	[0xae]                              = KEY_NONE,
	[0xaf]                              = KEY_NONE,
	[USBKBD_KEY_KP_00]                  = KEY_NONE,
	[USBKBD_KEY_KP_000]                 = KEY_NONE,
	[USBKBD_KEY_KP_THOUSANDS_SEPARATOR] = KEY_NONE,
	[USBKBD_KEY_KP_DECIMAL_SEPARATOR]   = KEY_NONE,
	[USBKBD_KEY_KP_CURRENCY_UNIT]       = KEY_NONE,
	[USBKBD_KEY_KP_CURRENCY_SUB_UNIT]   = KEY_NONE,
	[USBKBD_KEY_KP_LEFTPAREN]           = KEY_KPLEFTPAREN,
	[USBKBD_KEY_KP_RIGHTPAREN]          = KEY_KPRIGHTPAREN,
	[USBKBD_KEY_KP_LBRACE]              = KEY_NONE,
	[USBKBD_KEY_KP_RBRACE]              = KEY_NONE,
	[USBKBD_KEY_KP_TAB]                 = KEY_NONE,
	[USBKBD_KEY_KP_BACKSPACE]           = KEY_NONE,
	[USBKBD_KEY_KP_A]                   = KEY_NONE,
	[USBKBD_KEY_KP_B]                   = KEY_NONE,
	[USBKBD_KEY_KP_C]                   = KEY_NONE,
	[USBKBD_KEY_KP_D]                   = KEY_NONE,
	[USBKBD_KEY_KP_E]                   = KEY_NONE,
	[USBKBD_KEY_KP_F]                   = KEY_NONE,
	[USBKBD_KEY_KP_XOR]                 = KEY_NONE,
	[USBKBD_KEY_KP_CARET]               = KEY_NONE,
	[USBKBD_KEY_KP_PERCENT]             = KEY_NONE,
	[USBKBD_KEY_KP_LESS]                = KEY_NONE,
	[USBKBD_KEY_KP_MORE]                = KEY_NONE,
	[USBKBD_KEY_KP_AND]                 = KEY_NONE,
	[USBKBD_KEY_KP_ANDAND]              = KEY_NONE,
	[USBKBD_KEY_KP_PIPE]                = KEY_NONE,
	[USBKBD_KEY_KP_PIPEPIPE]            = KEY_NONE,
	[USBKBD_KEY_KP_COLON]               = KEY_NONE,
	[USBKBD_KEY_KP_POUND]               = KEY_NONE,
	[USBKBD_KEY_KP_SPACE]               = KEY_NONE,
	[USBKBD_KEY_KP_AT]                  = KEY_NONE,
	[USBKBD_KEY_KP_EXCLAIM]             = KEY_NONE,
	[USBKBD_KEY_KP_MEM_STORE]           = KEY_NONE,
	[USBKBD_KEY_KP_MEM_RECALL]          = KEY_NONE,
	[USBKBD_KEY_KP_MEM_CLEAR]           = KEY_NONE,
	[USBKBD_KEY_KP_MEM_ADD]             = KEY_NONE,
	[USBKBD_KEY_KP_MEM_SUBTRACT]        = KEY_NONE,
	[USBKBD_KEY_KP_MEM_MULTIPLY]        = KEY_NONE,
	[USBKBD_KEY_KP_MEM_DIVIDE]          = KEY_NONE,
	[USBKBD_KEY_KP_PLUSMINUS]           = KEY_NONE,
	[USBKBD_KEY_KP_CLEAR]               = KEY_NONE,
	[USBKBD_KEY_KP_CLEAR_ENTRY]         = KEY_NONE,
	[USBKBD_KEY_KP_BINARY]              = KEY_NONE,
	[USBKBD_KEY_KP_OCTAL]               = KEY_NONE,
	[USBKBD_KEY_KP_DECIMAL]             = KEY_NONE,
	[USBKBD_KEY_KP_HEXADECIMAL]         = KEY_NONE,
	[0xde]                              = KEY_NONE,
	[0xdf]                              = KEY_NONE,
	[USBKBD_KEY_LEFTCTRL]               = KEY_LEFTCTRL,
	[USBKBD_KEY_LEFTSHIFT]              = KEY_LEFTSHIFT,
	[USBKBD_KEY_LEFTALT]                = KEY_LEFTALT,
	[USBKBD_KEY_LEFTMETA]               = KEY_LEFTMETA,
	[USBKBD_KEY_RIGHTCTRL]              = KEY_RIGHTCTRL,
	[USBKBD_KEY_RIGHTSHIFT]             = KEY_RIGHTSHIFT,
	[USBKBD_KEY_RIGHTALT]               = KEY_RIGHTALT,
	[USBKBD_KEY_RIGHTMETA]              = KEY_RIGHTMETA,
	[USBKBD_KEY_MM_PLAY_PAUSE]          = KEY_MM_PLAY_PAUSE,
	[USBKBD_KEY_MM_STOP]                = KEY_MM_STOP,
	[USBKBD_KEY_MM_PREVIOUS_TRACK]      = KEY_MM_PREVIOUS_TRACK,
	[USBKBD_KEY_MM_NEXT_TRACK]          = KEY_MM_NEXT_TRACK,
	[USBKBD_KEY_EJECTCD]                = KEY_EJECTCD,
	[USBKBD_KEY_VOLUMEUP2]              = KEY_VOLUMEUP,
	[USBKBD_KEY_VOLUMEDOWN2]            = KEY_VOLUMEDOWN,
	[USBKBD_KEY_MUTE2]                  = KEY_MUTE,
	[USBKBD_KEY_WWW]                    = KEY_WWW,
	[USBKBD_KEY_WWW_BACK]               = KEY_WWW_BACK,
	[USBKBD_KEY_WWW_FORWARD]            = KEY_WWW_FORWARD,
	[USBKBD_KEY_WWW_STOP]               = KEY_WWW_STOP,
	[USBKBD_KEY_WWW_SEARCH]             = KEY_WWW_SEARCH,
	[USBKBD_KEY_SCROLLUP]               = KEY_SCROLLUP,
	[USBKBD_KEY_SCROLLDOWN]             = KEY_SCROLLDOWN,
	[USBKBD_KEY_EDIT]                   = KEY_EDIT,
	[USBKBD_KEY_APIC_SLEEP]             = KEY_APIC_SLEEP,
	[USBKBD_KEY_COFFEE]                 = KEY_COFFEE,
	[USBKBD_KEY_REFRESH]                = KEY_REFRESH,
	[USBKBD_KEY_CALC]                   = KEY_CALC,
	[0xfc]                              = KEY_NONE,
	[0xfd]                              = KEY_NONE,
	[0xfe]                              = KEY_NONE,
	[0xff]                              = KEY_NONE
};


PRIVATE NOBLOCK unsigned int
NOTHROW(KCALL usb_keyboard_interrupt_handler)(struct chrdev *__restrict self,
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
NOTHROW(KCALL usb_keyboard_fini)(struct chrdev *__restrict self) {
	struct usb_keyboard_device *me;
	me = (struct usb_keyboard_device *)self;
	if (me->uk_intr)
		usb_interrupt_delete(me->uk_intr);
	xdecref(me->uk_data);
	xdecref(me->uk_intf);
	xdecref(me->uk_ctrl);
	keyboard_device_fini(me);
}

PRIVATE struct kbddev_ops const usb_keyboard_ops = {
	.ko_setleds = NULL /* TODO */
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
	result = CHRDEV_ALLOC(struct usb_keyboard_device);
	kbddev_init(result, &usb_keyboard_ops);
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
	chrdev_register_auto(result);
	return true;
}



DECL_END

#endif /* !GUARD_MODUSB_HID_USB_KBD_C */
