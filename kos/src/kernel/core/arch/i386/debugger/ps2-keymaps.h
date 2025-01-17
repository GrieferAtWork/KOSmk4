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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_PS2_KEYMAPS_H
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_PS2_KEYMAPS_H 1
#define _KOS_SOURCE 1

#include <hybrid/compiler.h>
#include <kernel/types.h>
#include <kos/keyboard.h>

DECL_BEGIN

/* Keycode translation maps for PS/2 standard scancode sets. */

#define KEYMAP_GET_PS2_SCANSET1(c) \
      ((uint16_t)keymap_ps2_scanset_1[(c)&0x7f]|((uint16_t)(c&0x80) << 8))
#define KEYMAP_GET_PS2_SCANSET1_E0(c) \
      ((uint16_t)keymap_ps2_scanset_1_e0[(c)&0x7f]|((uint16_t)(c&0x80) << 8))

#if 0
PRIVATE u8 const keymap_ps2_scanset_1[128] = {0};
PRIVATE u8 const keymap_ps2_scanset_1_e0[128] = {0};
PRIVATE u8 const keymap_ps2_scanset_2[256] = {0};
PRIVATE u16 const keymap_ps2_scanset_2_e0[128] = {0};
PRIVATE u8 const keymap_ps2_scanset_3[256] = {0};
#else

/* NOTE: To save on space, only the lower key-byte is saved in this table. */
PRIVATE u8 const keymap_ps2_scanset_1[128] = {
/*[[[deemon
local l = ["0"] * 128;
l[0x01] = "KEY_ESC";
l[0x02] = "KEY_1";
l[0x03] = "KEY_2";
l[0x04] = "KEY_3";
l[0x05] = "KEY_4";
l[0x06] = "KEY_5";
l[0x07] = "KEY_6";
l[0x08] = "KEY_7";
l[0x09] = "KEY_8";
l[0x0a] = "KEY_9";
l[0x0b] = "KEY_0";
l[0x0c] = "KEY_MINUS";
l[0x0d] = "KEY_EQUALS";
l[0x0e] = "KEY_BACKSPACE";
l[0x0f] = "KEY_TAB";
l[0x10] = "KEY_Q";
l[0x11] = "KEY_W";
l[0x12] = "KEY_E";
l[0x13] = "KEY_R";
l[0x14] = "KEY_T";
l[0x15] = "KEY_Y";
l[0x16] = "KEY_U";
l[0x17] = "KEY_I";
l[0x18] = "KEY_O";
l[0x19] = "KEY_P";
l[0x1a] = "KEY_LBRACKET";
l[0x1b] = "KEY_RBRACKET";
l[0x1c] = "KEY_ENTER";
l[0x1d] = "KEY_LCTRL";
l[0x1e] = "KEY_A";
l[0x1f] = "KEY_S";
l[0x20] = "KEY_D";
l[0x21] = "KEY_F";
l[0x22] = "KEY_G";
l[0x23] = "KEY_H";
l[0x24] = "KEY_J";
l[0x25] = "KEY_K";
l[0x26] = "KEY_L";
l[0x27] = "KEY_SEMICOLON";
l[0x28] = "KEY_SINGLEQUOTE";
l[0x29] = "KEY_BACKTICK";
l[0x2a] = "KEY_LSHIFT";
l[0x2b] = "KEY_BACKSLASH";
l[0x2c] = "KEY_Z";
l[0x2d] = "KEY_X";
l[0x2e] = "KEY_C";
l[0x2f] = "KEY_V";
l[0x30] = "KEY_B";
l[0x31] = "KEY_N";
l[0x32] = "KEY_M";
l[0x33] = "KEY_COMMA";
l[0x34] = "KEY_DOT";
l[0x35] = "KEY_SLASH";
l[0x36] = "KEY_RSHIFT";
l[0x37] = "KEY_KP_STAR";
l[0x38] = "KEY_LALT";
l[0x39] = "KEY_SPACE";
l[0x3a] = "KEY_CAPSLOCK";
l[0x3b] = "KEY_F1";
l[0x3c] = "KEY_F2";
l[0x3d] = "KEY_F3";
l[0x3e] = "KEY_F4";
l[0x3f] = "KEY_F5";
l[0x40] = "KEY_F6";
l[0x41] = "KEY_F7";
l[0x42] = "KEY_F8";
l[0x43] = "KEY_F9";
l[0x44] = "KEY_F10";
l[0x45] = "KEY_NUMLOCK";
l[0x46] = "KEY_SCROLLLOCK";
l[0x47] = "KEY_KP_7";
l[0x48] = "KEY_KP_8";
l[0x49] = "KEY_KP_9";
l[0x4a] = "KEY_KP_MINUS";
l[0x4b] = "KEY_KP_4";
l[0x4c] = "KEY_KP_5";
l[0x4d] = "KEY_KP_6";
l[0x4e] = "KEY_KP_PLUS";
l[0x4f] = "KEY_KP_1";
l[0x50] = "KEY_KP_2";
l[0x51] = "KEY_KP_3";
l[0x52] = "KEY_KP_0";
l[0x53] = "KEY_KP_DOT";
l[0x57] = "KEY_F11";
l[0x58] = "KEY_F12";
#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print x,;
}
]]]*/
	0,KEY_ESC,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUALS,KEY_BACKSPACE,KEY_TAB,
	KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LBRACKET,KEY_RBRACKET,KEY_ENTER,KEY_LCTRL,KEY_A,KEY_S,
	KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_SINGLEQUOTE,KEY_BACKTICK,KEY_LSHIFT,KEY_BACKSLASH,KEY_Z,KEY_X,KEY_C,KEY_V,
	KEY_B,KEY_N,KEY_M,KEY_COMMA,KEY_DOT,KEY_SLASH,KEY_RSHIFT,KEY_KP_STAR,KEY_LALT,KEY_SPACE,KEY_CAPSLOCK,KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,
	KEY_F6,KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_NUMLOCK,KEY_SCROLLLOCK,KEY_KP_7,KEY_KP_8,KEY_KP_9,KEY_KP_MINUS,KEY_KP_4,KEY_KP_5,KEY_KP_6,KEY_KP_PLUS,KEY_KP_1,
	KEY_KP_2,KEY_KP_3,KEY_KP_0,KEY_KP_DOT,0,0,0,KEY_F11,KEY_F12,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//[[[end]]]
};

PRIVATE u8 const keymap_ps2_scanset_1_e0[128] = {
/*[[[deemon
local l = ["0"] * 128;
l[0x1c] = "KEY_KP_ENTER";
l[0x1d] = "KEY_RCTRL";
l[0x35] = "KEY_KP_SLASH";
l[0x38] = "KEY_RALT";
l[0x47] = "KEY_HOME";
l[0x48] = "KEY_UP";
l[0x49] = "KEY_PGUP";
l[0x4b] = "KEY_LEFT";
l[0x4d] = "KEY_RIGHT";
l[0x4f] = "KEY_END";
l[0x50] = "KEY_DOWN";
l[0x51] = "KEY_PGDOWN";
l[0x52] = "KEY_INSERT";
l[0x53] = "KEY_DELETE";
l[0x5b] = "KEY_LGUI";
l[0x5c] = "KEY_RGUI";
l[0x5d] = "KEY_APPS";

#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print x,;
}
]]]*/
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,KEY_KP_ENTER,KEY_RCTRL,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,KEY_KP_SLASH,0,0,KEY_RALT,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,KEY_HOME,KEY_UP,KEY_PGUP,0,KEY_LEFT,0,KEY_RIGHT,0,KEY_END,
	KEY_DOWN,KEY_PGDOWN,KEY_INSERT,KEY_DELETE,0,0,0,0,0,0,0,KEY_LGUI,KEY_RGUI,KEY_APPS,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//[[[end]]]
};


PRIVATE u8 const keymap_ps2_scanset_2[256] = {
/*[[[deemon
local l = ["0"] * 256;
l[0x01] = "KEY_F9";
l[0x03] = "KEY_F5";
l[0x04] = "KEY_F3";
l[0x05] = "KEY_F1";
l[0x06] = "KEY_F2";
l[0x07] = "KEY_F12";
l[0x09] = "KEY_F10";
l[0x0a] = "KEY_F8";
l[0x0b] = "KEY_F6";
l[0x0c] = "KEY_F4";
l[0x0d] = "KEY_TAB";
l[0x0e] = "KEY_BACKTICK";
l[0x11] = "KEY_LALT";
l[0x12] = "KEY_LSHIFT";
l[0x14] = "KEY_LCTRL";
l[0x15] = "KEY_Q";
l[0x16] = "KEY_1";
l[0x1a] = "KEY_Z";
l[0x1b] = "KEY_S";
l[0x1c] = "KEY_A";
l[0x1d] = "KEY_W";
l[0x1e] = "KEY_2";
l[0x21] = "KEY_C";
l[0x22] = "KEY_X";
l[0x23] = "KEY_D";
l[0x24] = "KEY_E";
l[0x25] = "KEY_4";
l[0x26] = "KEY_3";
l[0x29] = "KEY_SPACE";
l[0x2a] = "KEY_V";
l[0x2b] = "KEY_F";
l[0x2c] = "KEY_T";
l[0x2d] = "KEY_R";
l[0x2e] = "KEY_5";
l[0x31] = "KEY_N";
l[0x32] = "KEY_B";
l[0x33] = "KEY_H";
l[0x34] = "KEY_G";
l[0x35] = "KEY_Y";
l[0x36] = "KEY_6";
l[0x3a] = "KEY_M";
l[0x3b] = "KEY_J";
l[0x3c] = "KEY_U";
l[0x3d] = "KEY_7";
l[0x3e] = "KEY_8";
l[0x41] = "KEY_COMMA";
l[0x42] = "KEY_K";
l[0x43] = "KEY_I";
l[0x44] = "KEY_O";
l[0x45] = "KEY_0";
l[0x46] = "KEY_9";
l[0x49] = "KEY_DOT";
l[0x4a] = "KEY_SLASH";
l[0x4b] = "KEY_L";
l[0x4c] = "KEY_SEMICOLON";
l[0x4d] = "KEY_P";
l[0x4e] = "KEY_MINUS";
l[0x52] = "KEY_SINGLEQUOTE";
l[0x54] = "KEY_LBRACKET";
l[0x55] = "KEY_EQUALS";
l[0x58] = "KEY_CAPSLOCK";
l[0x59] = "KEY_RSHIFT";
l[0x5a] = "KEY_ENTER";
l[0x5b] = "KEY_RBRACKET";
l[0x5d] = "KEY_BACKSLASH";
l[0x61] = "KEY_LESS";
l[0x66] = "KEY_BACKSPACE";
l[0x69] = "KEY_KP_1";
l[0x6b] = "KEY_KP_4";
l[0x6c] = "KEY_KP_7";
l[0x70] = "KEY_KP_0";
l[0x71] = "KEY_KP_DOT";
l[0x72] = "KEY_KP_2";
l[0x73] = "KEY_KP_5";
l[0x74] = "KEY_KP_6";
l[0x75] = "KEY_KP_8";
l[0x76] = "KEY_ESC";
l[0x77] = "KEY_NUMLOCK";
l[0x78] = "KEY_F11";
l[0x79] = "KEY_KP_PLUS";
l[0x7a] = "KEY_KP_3";
l[0x7b] = "KEY_KP_MINUS";
l[0x7c] = "KEY_KP_STAR";
l[0x7d] = "KEY_KP_9";
l[0x7e] = "KEY_SCROLLLOCK";
l[0x7f] = "KEY_PRINTSCREEN"; // ... At least they are in QEMU...
l[0x83] = "KEY_F7";

#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print x,;
}
]]]*/
	0,KEY_F9,0,KEY_F5,KEY_F3,KEY_F1,KEY_F2,KEY_F12,0,KEY_F10,KEY_F8,KEY_F6,KEY_F4,KEY_TAB,KEY_BACKTICK,0,
	0,KEY_LALT,KEY_LSHIFT,0,KEY_LCTRL,KEY_Q,KEY_1,0,0,0,KEY_Z,KEY_S,KEY_A,KEY_W,KEY_2,0,
	0,KEY_C,KEY_X,KEY_D,KEY_E,KEY_4,KEY_3,0,0,KEY_SPACE,KEY_V,KEY_F,KEY_T,KEY_R,KEY_5,0,
	0,KEY_N,KEY_B,KEY_H,KEY_G,KEY_Y,KEY_6,0,0,0,KEY_M,KEY_J,KEY_U,KEY_7,KEY_8,0,
	0,KEY_COMMA,KEY_K,KEY_I,KEY_O,KEY_0,KEY_9,0,0,KEY_DOT,KEY_SLASH,KEY_L,KEY_SEMICOLON,KEY_P,KEY_MINUS,0,
	0,0,KEY_SINGLEQUOTE,0,KEY_LBRACKET,KEY_EQUALS,0,0,KEY_CAPSLOCK,KEY_RSHIFT,KEY_ENTER,KEY_RBRACKET,0,KEY_BACKSLASH,0,0,
	0,KEY_LESS,0,0,0,0,KEY_BACKSPACE,0,0,KEY_KP_1,0,KEY_KP_4,KEY_KP_7,0,0,0,
	KEY_KP_0,KEY_KP_DOT,KEY_KP_2,KEY_KP_5,KEY_KP_6,KEY_KP_8,KEY_ESC,KEY_NUMLOCK,KEY_F11,KEY_KP_PLUS,KEY_KP_3,KEY_KP_MINUS,KEY_KP_STAR,KEY_KP_9,KEY_SCROLLLOCK,KEY_PRINTSCREEN,
	0,0,0,KEY_F7,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//[[[end]]]
};

PRIVATE u16 const keymap_ps2_scanset_2_e0[128] = {
/*[[[deemon
local l = ["0"] * 128;
l[0x08] = "KEY_RALT"; // ... At least in QEMU...
l[0x10] = "KEY_WWW_SEARCH";
l[0x11] = "KEY_RALT";
l[0x14] = "KEY_RCTRL";
l[0x15] = "KEY_MM_PREVIOUS_TRACK";
l[0x18] = "KEY_WWW_FAVORITES";
l[0x1f] = "KEY_LGUI";
l[0x20] = "KEY_WWW_REFRESH";
l[0x21] = "KEY_VOLUME_DOWN";
l[0x23] = "KEY_VOLUME_MUTE";
l[0x27] = "KEY_RGUI";
l[0x28] = "KEY_WWW_STOP";
l[0x2b] = "KEY_CALCULATOR";
l[0x2f] = "KEY_APPS";
l[0x30] = "KEY_WWW_FORWARD";
l[0x32] = "KEY_VOLUME_UP";
l[0x34] = "KEY_MM_PLAY_PAUSE";
l[0x37] = "KEY_APIC_POWER";
l[0x38] = "KEY_WWW_BACK";
l[0x3a] = "KEY_WWW_HOME";
l[0x3b] = "KEY_MM_STOP";
l[0x3f] = "KEY_APIC_SLEEP";
l[0x40] = "KEY_MY_COMPUTER";
l[0x48] = "KEY_EMAIL_CLIENT";
l[0x4a] = "KEY_KP_SLASH";
l[0x4d] = "KEY_MM_NEXT_TRACK";
l[0x50] = "KEY_MM_SELECT";
l[0x5a] = "KEY_KP_ENTER";
l[0x5e] = "KEY_APIC_WAKE";
l[0x69] = "KEY_END";
l[0x6b] = "KEY_LEFT";
l[0x6c] = "KEY_HOME";
l[0x70] = "KEY_INSERT";
l[0x71] = "KEY_DELETE";
l[0x72] = "KEY_DOWN";
l[0x74] = "KEY_RIGHT";
l[0x75] = "KEY_UP";
l[0x7a] = "KEY_PGDOWN";
l[0x7d] = "KEY_PGUP";

#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print x,;
}
]]]*/
	0,0,0,0,0,0,0,0,KEY_RALT,0,0,0,0,0,0,0,
	KEY_WWW_SEARCH,KEY_RALT,0,0,KEY_RCTRL,KEY_MM_PREVIOUS_TRACK,0,0,KEY_WWW_FAVORITES,0,0,0,0,0,0,KEY_LGUI,
	KEY_WWW_REFRESH,KEY_VOLUME_DOWN,0,KEY_VOLUME_MUTE,0,0,0,KEY_RGUI,KEY_WWW_STOP,0,0,KEY_CALCULATOR,0,0,0,KEY_APPS,
	KEY_WWW_FORWARD,0,KEY_VOLUME_UP,0,KEY_MM_PLAY_PAUSE,0,0,KEY_APIC_POWER,KEY_WWW_BACK,0,KEY_WWW_HOME,KEY_MM_STOP,0,0,0,KEY_APIC_SLEEP,
	KEY_MY_COMPUTER,0,0,0,0,0,0,0,KEY_EMAIL_CLIENT,0,KEY_KP_SLASH,0,0,KEY_MM_NEXT_TRACK,0,0,
	KEY_MM_SELECT,0,0,0,0,0,0,0,0,0,KEY_KP_ENTER,0,0,0,KEY_APIC_WAKE,0,
	0,0,0,0,0,0,0,0,0,KEY_END,0,KEY_LEFT,KEY_HOME,0,0,0,
	KEY_INSERT,KEY_DELETE,KEY_DOWN,0,KEY_RIGHT,KEY_UP,0,0,0,0,KEY_PGDOWN,0,0,KEY_PGUP,0,0
//[[[end]]]
};


PRIVATE u8 const keymap_ps2_scanset_3[256] = {
/*[[[deemon
local l = ["0"] * 256;
l[0x07] = "KEY_F1";
l[0x08] = "KEY_ESC";
l[0x0d] = "KEY_TAB";
l[0x0e] = "KEY_BACKTICK";
l[0x0f] = "KEY_F2";
l[0x11] = "KEY_LCTRL";
l[0x12] = "KEY_LSHIFT";
l[0x14] = "KEY_CAPSLOCK";
l[0x15] = "KEY_Q";
l[0x16] = "KEY_1";
l[0x17] = "KEY_F3";
l[0x19] = "KEY_LALT";
l[0x1a] = "KEY_Z";
l[0x1b] = "KEY_S";
l[0x1c] = "KEY_A";
l[0x1d] = "KEY_W";
l[0x1e] = "KEY_2";
l[0x1f] = "KEY_F4";
l[0x21] = "KEY_C";
l[0x22] = "KEY_X";
l[0x23] = "KEY_D";
l[0x24] = "KEY_E";
l[0x25] = "KEY_4";
l[0x26] = "KEY_3";
l[0x27] = "KEY_F5";
l[0x29] = "KEY_SPACE";
l[0x2a] = "KEY_V";
l[0x2b] = "KEY_F";
l[0x2c] = "KEY_T";
l[0x2d] = "KEY_R";
l[0x2e] = "KEY_5";
l[0x2f] = "KEY_F6";
l[0x31] = "KEY_N";
l[0x32] = "KEY_B";
l[0x33] = "KEY_H";
l[0x34] = "KEY_G";
l[0x35] = "KEY_Y";
l[0x36] = "KEY_6";
l[0x37] = "KEY_F7";
l[0x39] = "KEY_RALT";
l[0x3a] = "KEY_M";
l[0x3b] = "KEY_J";
l[0x3c] = "KEY_U";
l[0x3d] = "KEY_7";
l[0x3e] = "KEY_8";
l[0x3f] = "KEY_F8";
l[0x41] = "KEY_COMMA";
l[0x42] = "KEY_K";

// CAUTION: The online doc says the break code for this is `0xc0 0x48'.
// But why would it be? (Also: It's the usual `0xc0 0x43')
l[0x43] = "KEY_I";
l[0x48] = "KEY_I"; // Just in case: Map 0x48 to 'I' as well (most likely wrong)

l[0x44] = "KEY_O";
l[0x45] = "KEY_0";
l[0x46] = "KEY_9";
l[0x47] = "KEY_F9";
l[0x49] = "KEY_DOT";
l[0x4a] = "KEY_SLASH";
l[0x4b] = "KEY_L";
l[0x4c] = "KEY_SEMICOLON";
l[0x4d] = "KEY_P";
l[0x4e] = "KEY_MINUS";
l[0x4f] = "KEY_F10";
l[0x52] = "KEY_SINGLEQUOTE";
l[0x54] = "KEY_LBRACKET";
l[0x55] = "KEY_EQUALS";
l[0x56] = "KEY_F11";
l[0x57] = "KEY_PRINTSCREEN";
l[0x58] = "KEY_RCTRL";
l[0x59] = "KEY_RSHIFT";
l[0x5a] = "KEY_ENTER";
l[0x5b] = "KEY_RBRACKET";
l[0x5c] = "KEY_BACKSLASH";
l[0x5e] = "KEY_F12";
l[0x5f] = "KEY_SCROLLLOCK";
l[0x60] = "KEY_DOWN";
l[0x61] = "KEY_LEFT";
l[0x62] = "KEY_PAUSE";
l[0x63] = "KEY_UP";
l[0x64] = "KEY_DELETE";
l[0x65] = "KEY_END";
l[0x66] = "KEY_BACKSPACE";
l[0x67] = "KEY_INSERT";
l[0x69] = "KEY_KP_1";
l[0x6a] = "KEY_RIGHT";
l[0x6b] = "KEY_KP_4";
l[0x6c] = "KEY_KP_7";
l[0x6d] = "KEY_PGDOWN";
l[0x6e] = "KEY_HOME";
l[0x6f] = "KEY_PGUP";
l[0x70] = "KEY_KP_0";
l[0x71] = "KEY_KP_DOT";
l[0x72] = "KEY_KP_2";
l[0x73] = "KEY_KP_5";
l[0x74] = "KEY_KP_6";
l[0x75] = "KEY_KP_8";
l[0x76] = "KEY_NUMLOCK";
l[0x79] = "KEY_KP_ENTER";
l[0x7a] = "KEY_KP_3";
l[0x7c] = "KEY_KP_PLUS";
l[0x7d] = "KEY_KP_9";
l[0x7e] = "KEY_KP_STAR";
l[0x8b] = "KEY_LGUI";
l[0x8c] = "KEY_RGUI";
l[0x8d] = "KEY_APPS";

#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print x,;
}
]]]*/
	0,0,0,0,0,0,0,KEY_F1,KEY_ESC,0,0,0,0,KEY_TAB,KEY_BACKTICK,KEY_F2,
	0,KEY_LCTRL,KEY_LSHIFT,0,KEY_CAPSLOCK,KEY_Q,KEY_1,KEY_F3,0,KEY_LALT,KEY_Z,KEY_S,KEY_A,KEY_W,KEY_2,KEY_F4,
	0,KEY_C,KEY_X,KEY_D,KEY_E,KEY_4,KEY_3,KEY_F5,0,KEY_SPACE,KEY_V,KEY_F,KEY_T,KEY_R,KEY_5,KEY_F6,
	0,KEY_N,KEY_B,KEY_H,KEY_G,KEY_Y,KEY_6,KEY_F7,0,KEY_RALT,KEY_M,KEY_J,KEY_U,KEY_7,KEY_8,KEY_F8,
	0,KEY_COMMA,KEY_K,KEY_I,KEY_O,KEY_0,KEY_9,KEY_F9,KEY_I,KEY_DOT,KEY_SLASH,KEY_L,KEY_SEMICOLON,KEY_P,KEY_MINUS,KEY_F10,
	0,0,KEY_SINGLEQUOTE,0,KEY_LBRACKET,KEY_EQUALS,KEY_F11,KEY_PRINTSCREEN,KEY_RCTRL,KEY_RSHIFT,KEY_ENTER,KEY_RBRACKET,KEY_BACKSLASH,0,KEY_F12,KEY_SCROLLLOCK,
	KEY_DOWN,KEY_LEFT,KEY_PAUSE,KEY_UP,KEY_DELETE,KEY_END,KEY_BACKSPACE,KEY_INSERT,0,KEY_KP_1,KEY_RIGHT,KEY_KP_4,KEY_KP_7,KEY_PGDOWN,KEY_HOME,KEY_PGUP,
	KEY_KP_0,KEY_KP_DOT,KEY_KP_2,KEY_KP_5,KEY_KP_6,KEY_KP_8,KEY_NUMLOCK,0,0,KEY_KP_ENTER,KEY_KP_3,0,KEY_KP_PLUS,KEY_KP_9,KEY_KP_STAR,0,
	0,0,0,0,0,0,0,0,0,0,0,KEY_LGUI,KEY_RGUI,KEY_APPS,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//[[[end]]]
};
#endif

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_PS2_KEYMAPS_H */
