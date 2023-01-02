/*[[[magic
// Because g++ is dumb and refuses to parse array
// initializers, compile this file as C, rather than C++
options["COMPILE.language"] = "c";
local gcc_opt = options.setdefault("GCC.options", []);
gcc_opt.remove("-fno-rtti");
gcc_opt.append("-fexceptions");
]]]*/
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
#ifndef GUARD_MODGDBSERVER_HEX_C
#define GUARD_MODGDBSERVER_HEX_C 1

#include <kernel/compiler.h>

#include "gdb.h"

DECL_BEGIN

INTERN_CONST char const GDB_HexChars[16] = {
	[0x0] = '0',
	[0x1] = '1',
	[0x2] = '2',
	[0x3] = '3',
	[0x4] = '4',
	[0x5] = '5',
	[0x6] = '6',
	[0x7] = '7',
	[0x8] = '8',
	[0x9] = '9',
	[0xa] = 'a',
	[0xb] = 'b',
	[0xc] = 'c',
	[0xd] = 'd',
	[0xe] = 'e',
	[0xf] = 'f',
};

#pragma GCC diagnostic ignored "-Woverride-init"
INTERN_CONST u8 const GDB_HexValues[256] = {
	[0 ... 255] = 0,

	['0'] = 0x0,
	['1'] = 0x1,
	['2'] = 0x2,
	['3'] = 0x3,
	['4'] = 0x4,
	['5'] = 0x5,
	['6'] = 0x6,
	['7'] = 0x7,
	['8'] = 0x8,
	['9'] = 0x9,

	['a'] = 0xa,
	['b'] = 0xb,
	['c'] = 0xc,
	['d'] = 0xd,
	['e'] = 0xe,
	['f'] = 0xf,

	['A'] = 0xa,
	['B'] = 0xb,
	['C'] = 0xc,
	['D'] = 0xd,
	['E'] = 0xe,
	['F'] = 0xf,

};


DECL_END

#endif /* !GUARD_MODGDBSERVER_HEX_C */
