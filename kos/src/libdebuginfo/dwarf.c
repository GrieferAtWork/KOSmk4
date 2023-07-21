/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
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
#ifndef GUARD_LIBDEBUGINFO_DWARF_C
#define GUARD_LIBDEBUGINFO_DWARF_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <int128.h>

#include "dwarf.h"


DECL_BEGIN

/* Similar to the functions from `libunwind(3)', but decode into a 64-bit integer! */
INTERN ATTR_RETNONNULL NONNULL((1, 2)) CHECKED byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_sleb128_64)(CHECKED byte_t const *__restrict reader,
                                              int64_t *__restrict p_result) {
	byte_t byte;
	shift_t shift = 0;
	*p_result = 0;
	for (;;) {
		byte = *reader++;
		*p_result |= ((byte & 0x7f) << shift);
		shift += 7;
		if (!(byte & 0x80))
			break;
	}
	if ((byte & 0x40) && (shift < 64))
		*p_result |= -(int64_t)((uint64_t)1 << shift);
	return reader;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2)) CHECKED byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_uleb128_64)(CHECKED byte_t const *__restrict reader,
                                              uint64_t *__restrict p_result) {
	byte_t byte;
	shift_t shift = 0;
	*p_result = 0;
	for (;;) {
		byte = *reader++;
		*p_result |= ((byte & 0x7f) << shift);
		shift  += 7;
		if (!(byte & 0x80))
			break;
	}
	return reader;
}


/* Similar to the functions from `libunwind(3)', but these actually decode into a 128-bit integer! */
INTERN ATTR_RETNONNULL NONNULL((1, 2)) CHECKED byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_sleb128_128)(CHECKED byte_t const *__restrict reader,
                                               int128_t *__restrict p_result) {
	byte_t byte;
	shift_t shift = 0;
	int128_setzero(*p_result);
	for (;;) {
		int128_t temp;
		byte = *reader++;
		int128_set8(temp, byte & 0x7f);
		int128_shl(temp, shift);
		int128_or128(*p_result, temp);
		shift += 7;
		if (!(byte & 0x80))
			break;
	}
	if ((byte & 0x40) && (shift < 128)) {
		int128_t temp;
		int128_setone(temp);
		int128_shl(temp, shift);
		int128_neg(temp);
		int128_or128(*p_result, temp);
	}
	return reader;
}

INTERN ATTR_RETNONNULL NONNULL((1, 2)) CHECKED byte_t const *
NOTHROW_NCX(CC libdi_dwarf_decode_uleb128_128)(CHECKED byte_t const *__restrict reader,
                                               uint128_t *__restrict p_result) {
	byte_t byte;
	shift_t shift = 0;
	uint128_setzero(*p_result);
	for (;;) {
		uint128_t temp;
		byte = *reader++;
		uint128_set8(temp, byte & 0x7f);
		uint128_shl(temp, shift);
		uint128_or128(*p_result, temp);
		shift  += 7;
		if (!(byte & 0x80))
			break;
	}
	return reader;
}

DEFINE_PUBLIC_ALIAS(dwarf_decode_sleb128_64, libdi_dwarf_decode_sleb128_64);
DEFINE_PUBLIC_ALIAS(dwarf_decode_uleb128_64, libdi_dwarf_decode_uleb128_64);
DEFINE_PUBLIC_ALIAS(dwarf_decode_sleb128_128, libdi_dwarf_decode_sleb128_128);
DEFINE_PUBLIC_ALIAS(dwarf_decode_uleb128_128, libdi_dwarf_decode_uleb128_128);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DWARF_C */
