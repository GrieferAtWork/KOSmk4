/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBUNWIND_DWARF_C
#define GUARD_LIBUNWIND_DWARF_C 1

#include "api.h"

#include <hybrid/compiler.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <libunwind/dwarf.h>

/**/
#include "dwarf.h"

DECL_BEGIN

/* Decode a signed/unsigned LEB128 integer and advance `*preader' */
INTERN NONNULL((1)) dwarf_sleb128_t
NOTHROW_NCX(CC libuw_dwarf_decode_sleb128)(byte_t const **__restrict preader) {
	byte_t byte;
	byte_t const *reader   = *preader;
	dwarf_sleb128_t result = 0;
	unsigned int shift     = 0;
	for (;;) {
		byte = *reader++;
		result |= ((byte & 0x7f) << shift);
		shift += 7;
		if (!(byte & 0x80))
			break;
	}
	if ((byte & 0x40) &&
	    (shift < sizeof(dwarf_sleb128_t) * 8))
		result |= -((dwarf_sleb128_t)1 << shift);
	*preader = reader;
	return result;
}

INTERN NONNULL((1)) dwarf_uleb128_t
NOTHROW_NCX(CC libuw_dwarf_decode_uleb128)(byte_t const **__restrict preader) {
	byte_t byte;
	byte_t const *reader   = *preader;
	dwarf_uleb128_t result = 0;
	unsigned int shift     = 0;
	for (;;) {
		byte    = *reader++;
		result |= ((byte & 0x7f) << shift);
		shift  += 7;
		if (!(byte & 0x80))
			break;
	}
	*preader = reader;
	return result;
}




INTERN NONNULL((1)) uintptr_t
NOTHROW_NCX(CC libuw_dwarf_decode_pointer)(byte_t const **__restrict preader,
                                           uint8_t encoding, uint8_t addrsize,
                                           uintptr_t textbase, uintptr_t database,
                                           uintptr_t funcbase) {
	uintptr_t result;
	byte_t const *reader = *preader;

	/* Relative encoding formats. */
	switch (encoding & 0x70) {

	case DW_EH_PE_pcrel:
		result = (uintptr_t)reader; /* Relative to here. */
		break;

	case DW_EH_PE_textrel:
		result = textbase; /* TODO: DLAUXCTRL_GET_TEXTBASE */
		break;

	case DW_EH_PE_datarel:
		result = database; /* TODO: DLAUXCTRL_GET_DATABASE */
		break;

	case DW_EH_PE_funcrel:
		result = funcbase;
		break;

	case DW_EH_PE_aligned:
		reader = (byte_t const *)(((uintptr_t)reader + (addrsize - 1)) & ~(addrsize - 1));
		result = 0;
		break;

	default:
	case DW_EH_PE_absptr:
		result = 0;
		break;
	}
	switch (encoding & 0xf) {

	case DW_EH_PE_absptr:
		if (addrsize >= sizeof(uintptr_t)) {
			result += UNALIGNED_GET((uintptr_t const *)reader);
#if __SIZEOF_POINTER__ > 4
		} else if (addrsize >= 4) {
			result += UNALIGNED_GET32((uint32_t const *)reader);
#endif /* __SIZEOF_POINTER__ > 4 */
		} else if (addrsize >= 2) {
			result += UNALIGNED_GET16((uint16_t const *)reader);
		} else if (addrsize >= 1) {
			result += *(uint8_t const *)reader;
		}
		reader += addrsize;
		break;

	case DW_EH_PE_udata2:
		result += (uintptr_t)UNALIGNED_GET16((uint16_t const *)reader);
		reader += 2;
		break;

	case DW_EH_PE_udata4:
		result += (uintptr_t)UNALIGNED_GET32((uint32_t const *)reader);
		reader += 4;
		break;

	case DW_EH_PE_udata8:
#if __SIZEOF_POINTER__ > 4
		result += (uintptr_t)UNALIGNED_GET64((uint64_t const *)reader);
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		result += (uintptr_t)UNALIGNED_GET32((uint32_t const *)reader);
#else /* ... */
		result += (uintptr_t)UNALIGNED_GET32((uint32_t const *)reader + 1);
#endif /* !... */
		reader += 8;
		break;

	case DW_EH_PE_sdata2:
		result += (uintptr_t)(intptr_t)(int16_t)UNALIGNED_GET16((uint16_t const *)reader);
		reader += 2;
		break;

	case DW_EH_PE_sdata4:
		result += (uintptr_t)(intptr_t)(int32_t)UNALIGNED_GET32((uint32_t const *)reader);
		reader += 4;
		break;

	case DW_EH_PE_sdata8:
#if __SIZEOF_POINTER__ > 4
		result += (uintptr_t)(intptr_t)(int64_t)UNALIGNED_GET64((uint64_t const *)reader);
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		result += (uintptr_t)(intptr_t)(int32_t)UNALIGNED_GET32((uint32_t const *)reader);
#else /* ... */
		result += (uintptr_t)(intptr_t)(int32_t)UNALIGNED_GET32((uint32_t const *)reader + 1);
#endif /* !... */
		reader += 8;
		break;

	case DW_EH_PE_uleb128:
		result += libuw_dwarf_decode_uleb128(&reader);
		break;

	case DW_EH_PE_sleb128:
		result += libuw_dwarf_decode_sleb128(&reader);
		break;

	default:
		reader += 1; /* ??? */
		break;
	}
	if (encoding & DW_EH_PE_indirect) {
		if (addrsize >= sizeof(uintptr_t)) {
			result = UNALIGNED_GET((uintptr_t const *)result);
#if __SIZEOF_POINTER__ > 4
		} else if (addrsize >= 4) {
			result = UNALIGNED_GET32((uint32_t const *)result);
#endif /* __SIZEOF_POINTER__ > 4 */
		} else if (addrsize >= 2) {
			result = UNALIGNED_GET16((uint16_t const *)result);
		} else if (addrsize >= 1) {
			result = *(uint8_t const *)result;
		}
	}
	*preader = reader;
	return result;
}

#undef dwarf_decode_sleb128
#undef dwarf_decode_uleb128
#undef dwarf_decode_pointer
DEFINE_PUBLIC_ALIAS(dwarf_decode_sleb128, libuw_dwarf_decode_sleb128);
DEFINE_PUBLIC_ALIAS(dwarf_decode_uleb128, libuw_dwarf_decode_uleb128);
DEFINE_PUBLIC_ALIAS(dwarf_decode_pointer, libuw_dwarf_decode_pointer);

DECL_END

#endif /* !GUARD_LIBUNWIND_DWARF_C */
