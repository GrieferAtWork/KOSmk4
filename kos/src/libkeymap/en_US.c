/*[[[magic
// Because g++ is dumb and refuses to parse array
// initializers, compile this file as C, rather than C++
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-fno-rtti");
gcc_opt.append("-fexceptions");
]]]*/
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
#ifndef GUARD_LIBKEYMAP_EN_US_C
#define GUARD_LIBKEYMAP_EN_US_C 1

#include "api.h"
/**/

#include <kos/keyboard.h>
#include <kos/types.h>

#include <string.h>

#include <libkeymap/keymap.h>


DECL_BEGIN

PRIVATE struct basic_key const basic_keys_en_US[128] = {
#define DEF(key, lower, upper) [key] = { lower, upper }

	DEF(KEY_BACKTICK, '`', '~'),
	DEF(KEY_1, '1', '!'),
	DEF(KEY_2, '2', '@'),
	DEF(KEY_3, '3', '#'),
	DEF(KEY_4, '4', '$'),
	DEF(KEY_5, '5', '%'),
	DEF(KEY_6, '6', '^'),
	DEF(KEY_7, '7', '&'),
	DEF(KEY_8, '8', '*'),
	DEF(KEY_9, '9', '('),
	DEF(KEY_0, '0', ')'),
	DEF(KEY_MINUS, '-', '_'),
	DEF(KEY_EQUALS, '=', '+'),
	DEF(KEY_BACKSLASH, '\\', '|'),

	DEF(KEY_Q, 'q', 'Q'),
	DEF(KEY_W, 'w', 'W'),
	DEF(KEY_E, 'e', 'E'),
	DEF(KEY_R, 'r', 'R'),
	DEF(KEY_T, 't', 'T'),
	DEF(KEY_Y, 'y', 'Y'),
	DEF(KEY_U, 'u', 'U'),
	DEF(KEY_I, 'i', 'I'),
	DEF(KEY_O, 'o', 'O'),
	DEF(KEY_P, 'p', 'P'),
	DEF(KEY_LBRACKET, '[', '{'),
	DEF(KEY_RBRACKET, ']', '}'),

	DEF(KEY_A, 'a', 'A'),
	DEF(KEY_S, 's', 'S'),
	DEF(KEY_D, 'd', 'D'),
	DEF(KEY_F, 'f', 'F'),
	DEF(KEY_G, 'g', 'G'),
	DEF(KEY_H, 'h', 'H'),
	DEF(KEY_J, 'j', 'J'),
	DEF(KEY_K, 'k', 'K'),
	DEF(KEY_L, 'l', 'L'),
	DEF(KEY_SEMICOLON, ';', ':'),
	DEF(KEY_SINGLEQUOTE, '\'', '\"'),

	DEF(KEY_Z, 'z', 'Z'),
	DEF(KEY_X, 'x', 'X'),
	DEF(KEY_C, 'c', 'C'),
	DEF(KEY_V, 'v', 'V'),
	DEF(KEY_B, 'b', 'B'),
	DEF(KEY_N, 'n', 'N'),
	DEF(KEY_M, 'm', 'M'),
	DEF(KEY_COMMA, ',', '<'),
	DEF(KEY_DOT, '.', '>'),
	DEF(KEY_SLASH, '/', '?'),
#undef DEF
};


/* Initialize the given keymap to represent the map keys according to the en_US layout.
 * This function should be used as fallback when the caller is unable to initialize the
 * desired keyboard layout, as ~any~ mapping is still better than no mapping at all. */
INTERN NONNULL((1)) void
NOTHROW_NCX(CC libkeymap_init_en_US)(struct keymap *__restrict self) {
	memcpy(self->km_basic, basic_keys_en_US, sizeof(self->km_basic));
	self->km_ext         = NULL;
	self->km_defencoding = KMP_ENCODING_ASCII;
}


DEFINE_PUBLIC_ALIAS(keymap_init_en_US, libkeymap_init_en_US);

DECL_END

#endif /* !GUARD_LIBKEYMAP_EN_US_C */
