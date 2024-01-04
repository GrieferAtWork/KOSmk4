/*[[[magic
// Because g++ is dumb and refuses to parse array
// initializers, compile this file as C, rather than C++
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-fno-rtti");
gcc_opt.append("-fexceptions");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEV_AT_SCANCODES_C
#define GUARD_KERNEL_SRC_DEV_AT_SCANCODES_C 1

#include <kernel/compiler.h>

#include <kos/keyboard.h>
/**/

#include "at_scancodes.h"

DECL_BEGIN

__pragma_GCC_diagnostic_ignored(Woverride_init)

/* AT scancode mappings  for kos's linux-compatible,  device-
 * independent keycodes (aka. `KEY_*' from  <kos/keyboard.h>)
 * Only KEY_* codes below 256 can be encoded as AT scancodes.
 *
 * AT scancode bytes are encoded in `at_scancodes[KEY_*] & 0x7f',
 * and  AT  scancode  sequences  that  should  be  prefixed  by a
 * second byte  have that  byte encoded  as a  non-zero value  in
 * `at_scancodes[KEY_*] & 0xff'.
 * The value of `at_scancodes[KEY_*] & 0x80' is reserved and is
 * currently always 0. */
INTERN_CONST uint16_t const at_scancodes[256] = {
	[0 ... 255] = 0x0000,

	[KEY_ESC]          = 0x0001,
	[KEY_1]            = 0x0002,
	[KEY_2]            = 0x0003,
	[KEY_3]            = 0x0004,
	[KEY_4]            = 0x0005,
	[KEY_5]            = 0x0006,
	[KEY_6]            = 0x0007,
	[KEY_7]            = 0x0008,
	[KEY_8]            = 0x0009,
	[KEY_9]            = 0x000a,
	[KEY_0]            = 0x000b,
	[KEY_MINUS]        = 0x000c,
	[KEY_EQUALS]       = 0x000d,
	[KEY_BACKSPACE]    = 0x000e,
	[KEY_TAB]          = 0x000f,
	[KEY_Q]            = 0x0010,
	[KEY_W]            = 0x0011,
	[KEY_E]            = 0x0012,
	[KEY_R]            = 0x0013,
	[KEY_T]            = 0x0014,
	[KEY_Y]            = 0x0015,
	[KEY_U]            = 0x0016,
	[KEY_I]            = 0x0017,
	[KEY_O]            = 0x0018,
	[KEY_P]            = 0x0019,
	[KEY_LBRACKET]     = 0x001a,
	[KEY_RBRACKET]     = 0x001b,
	[KEY_ENTER]        = 0x001c,
	[KEY_LCTRL]        = 0x001d,
	[KEY_A]            = 0x001e,
	[KEY_S]            = 0x001f,
	[KEY_D]            = 0x0020,
	[KEY_F]            = 0x0021,
	[KEY_G]            = 0x0022,
	[KEY_H]            = 0x0023,
	[KEY_J]            = 0x0024,
	[KEY_K]            = 0x0025,
	[KEY_L]            = 0x0026,
	[KEY_SEMICOLON]    = 0x0027,
	[KEY_APOSTROPHE]   = 0x0028,
	[KEY_GRAVE_ACCENT] = 0x0029,
	[KEY_LSHIFT]       = 0x002a,
	[KEY_BACKSLASH]    = 0x002b,
	[KEY_Z]            = 0x002c,
	[KEY_X]            = 0x002d,
	[KEY_C]            = 0x002e,
	[KEY_V]            = 0x002f,
	[KEY_B]            = 0x0030,
	[KEY_N]            = 0x0031,
	[KEY_M]            = 0x0032,
	[KEY_COMMA]        = 0x0033,
	[KEY_DOT]          = 0x0034,
	[KEY_SLASH]        = 0x0035,
	[KEY_RSHIFT]       = 0x0036,
	[KEY_KP_MULTIPLY]  = 0x0037,
	[KEY_LALT]         = 0x0038,
	[KEY_SPACE]        = 0x0039,
	[KEY_CAPSLOCK]     = 0x003a,
	[KEY_F1]           = 0x003b,
	[KEY_F2]           = 0x003c,
	[KEY_F3]           = 0x003d,
	[KEY_F4]           = 0x003e,
	[KEY_F5]           = 0x003f,
	[KEY_F6]           = 0x0040,
	[KEY_F7]           = 0x0041,
	[KEY_F8]           = 0x0042,
	[KEY_F9]           = 0x0043,
	[KEY_F10]          = 0x0044,
	[KEY_NUMLOCK]      = 0x0045,
	[KEY_SCROLLLOCK]   = 0x0046,
	[KEY_KP_7]         = 0x0047,
	[KEY_KP_8]         = 0x0048,
	[KEY_KP_9]         = 0x0049,
	[KEY_KP_SUBTRACT]  = 0x004a,
	[KEY_KP_4]         = 0x004b,
	[KEY_KP_5]         = 0x004c,
	[KEY_KP_6]         = 0x004d,
	[KEY_KP_ADD]       = 0x004e,
	[KEY_KP_1]         = 0x004f,
	[KEY_KP_2]         = 0x0050,
	[KEY_KP_3]         = 0x0051,
	[KEY_KP_0]         = 0x0052,
	[KEY_KP_DECIMAL]   = 0x0053,
	[KEY_SYSRQ]        = 0x0054,
	[KEY_LESS]         = 0x0056,
	[KEY_F11]          = 0x0057,
	[KEY_F12]          = 0x0058,
	[KEY_RO]           = 0x0073,
	[KEY_KP_COMMA]     = 0x007e,

	[KEY_MM_PREVIOUS_TRACK] = 0xe010,
	[KEY_MM_NEXT_TRACK]     = 0xe019,
	[KEY_KP_ENTER]          = 0xe01c,
	[KEY_RCTRL]             = 0xe01d,
	[KEY_VOLUME_MUTE]       = 0xe020,
	[KEY_CALCULATOR]        = 0xe021,
	[KEY_MM_PLAY_PAUSE]     = 0xe022,
	[KEY_MM_STOP]           = 0xe024,
	[KEY_VOLUME_DOWN]       = 0xe02e,
	[KEY_VOLUME_UP]         = 0xe030,
	[KEY_WWW_HOME]          = 0xe032,
	[KEY_KP_DIVIDE]         = 0xe035,
	[KEY_PRINTSCREEN]       = 0xe037,
	[KEY_RALT]              = 0xe038,
//	[KEY_BREAK]             = 0xe046,
	[KEY_HOME]              = 0xe047,
	[KEY_UP]                = 0xe048,
	[KEY_PGUP]              = 0xe049,
	[KEY_LEFT]              = 0xe04b,
	[KEY_RIGHT]             = 0xe04d,
	[KEY_END]               = 0xe04f,
	[KEY_DOWN]              = 0xe050,
	[KEY_PGDOWN]            = 0xe051,
	[KEY_INSERT]            = 0xe052,
	[KEY_DELETE]            = 0xe053,
	[KEY_LGUI]              = 0xe05b,
	[KEY_RGUI]              = 0xe05c,
	[KEY_MENU]              = 0xe05d,
	[KEY_APIC_POWER]        = 0xe05e,
	[KEY_APIC_SLEEP]        = 0xe05f,
	[KEY_APIC_WAKE]         = 0xe063,
	[KEY_WWW_SEARCH]        = 0xe065,
	[KEY_WWW_FAVORITES]     = 0xe066,
	[KEY_WWW_REFRESH]       = 0xe067,
	[KEY_WWW_STOP]          = 0xe068,
	[KEY_WWW_FORWARD]       = 0xe069,
	[KEY_WWW_BACK]          = 0xe06a,
	[KEY_MY_COMPUTER]       = 0xe06b,
	[KEY_EMAIL_CLIENT]      = 0xe06c,
	[KEY_MM_SELECT]         = 0xe06d,
};

DECL_END

#endif /* !GUARD_KERNEL_SRC_DEV_AT_SCANCODES_C */
