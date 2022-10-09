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
#ifndef GUARD_LIBANSITTY_CP_C
#define GUARD_LIBANSITTY_CP_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <stddef.h>

#include "cp.h"

DECL_BEGIN

/* Ansi box character set (translate to the unicode equivalents) */
#define LDM_CHARS_START '_'
PRIVATE char16_t const ldm_chars[] = {
	/* s.a.: https://vt100.net/docs/vt100-ug/table3-9.html
	 * NOTE: Link has gone dead. - Use this WayBackMachine snapshot:
	 * https://web.archive.org/web/20191225064516/https://vt100.net/docs/vt100-ug/table3-9.html
	 */
#ifdef __INTELLISENSE__
#define CHR(x) [x - LDM_CHARS_START] =
#else /* __INTELLISENSE__ */
#define CHR(x) /* nothing */
#endif /* !__INTELLISENSE__ */
	CHR('_') ' ',    /* Blank */
	CHR('`') 0x22c4, /* Diamond */
	CHR('a') 0x2593, /* Checkerboard */
	CHR('b') 0x0009, /* Horizontal tab */
	CHR('c') 0x000c, /* Form Feed */
	CHR('d') '\r',   /* Carriage return */
	CHR('e') '\n',   /* Line feed */
	CHR('f') 0x00b0, /* ° Degree symbol */
	CHR('g') 0x00b1, /* ± Plus/minus */
	CHR('h') '\n',   /* New line */
	CHR('i') 0x000b, /* Vertical tab */
	CHR('j') 0x2518, /* Lower-right corner */
	CHR('k') 0x2510, /* Upper-right corner */
	CHR('l') 0x250c, /* Upper-left corner*/
	CHR('m') 0x2514, /* Lower-left corner */
	CHR('n') 0x253c, /* Crossing lines */
	CHR('o') 0x2500, /* Horizontal line - Scan 1 */
	CHR('p') 0x2500, /* Horizontal line - Scan 3 */
	CHR('q') 0x2500, /* Horizontal line - Scan 5 */
	CHR('r') 0x2500, /* Horizontal line - Scan 7 */
	CHR('s') 0x2500, /* Horizontal line - Scan 9 */
	CHR('t') 0x251c, /* Left "T" */
	CHR('u') 0x2524, /* Right "T" */
	CHR('v') 0x2534, /* Bottom "T" */
	CHR('w') 0x252c, /* Top "T" */
	CHR('x') 0x2502, /* | Vertical bar */
	CHR('y') 0x2264, /* Less than or equal to */
	CHR('z') 0x2265, /* Greater than or equal to */
	CHR('{') 0x03c0, /* Pi */
	CHR('|') 0x2260, /* Not equal to */
	CHR('}') 0x00a3, /* UK pound sign */
	CHR('~') 0x2219, /* Centered dot */
#undef CHR
};

INTERN ATTR_CONST WUNUSED char32_t
NOTHROW(FCALL libansitty_decode_cp_ldm)(uint8_t byte) {
	/* Translate line-drawing-mode characters. */
	char32_t result = (char32_t)byte;
	if (byte >= LDM_CHARS_START &&
	    byte < (LDM_CHARS_START + lengthof(ldm_chars)))
		result = ldm_chars[byte - LDM_CHARS_START];
	return result;
}


#define BEGIN_CP(name)                                         \
	INTERN ATTR_CONST WUNUSED char32_t                         \
	NOTHROW(FCALL libansitty_decode_cp_##name)(uint8_t byte) { \
		char32_t result = byte;                                \
		switch (byte) {
#define MAP(cp_char, uni_char) \
		case cp_char:          \
			result = uni_char; \
			break;
#define MAP_ALIAS MAP
#define END_CP(name)    \
		default: break; \
		}               \
		return result;  \
	}
#include "cp.def"
#undef END_CP
#undef MAP_ALIAS
#undef MAP
#undef BEGIN_CP



#define BEGIN_CP(name)                                        \
	INTERN ATTR_CONST WUNUSED uint8_t                         \
	NOTHROW(FCALL libansitty_encode_cp_##name)(char32_t ch) { \
		uint8_t result = (uint8_t)ch;                         \
		switch (ch) {
#define MAP(cp_char, uni_char) \
		case uni_char:         \
			result = cp_char;  \
			break;
#define MAP_ALIAS(cp_char, uni_char) /* nothing */
#define END_CP(name)        \
		default:            \
			if (ch > 0xff)  \
				result = 0; \
			break;          \
		}                   \
		return result;      \
	}
#include "cp.def"
#undef END_CP
#undef MAP_ALIAS
#undef MAP
#undef BEGIN_CP



DECL_END

#endif /* !GUARD_LIBANSITTY_CP_C */
