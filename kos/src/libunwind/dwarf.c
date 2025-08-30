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
#ifndef GUARD_LIBUNWIND_DWARF_C
#define GUARD_LIBUNWIND_DWARF_C 1
#define _KOS_SOURCE 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/unaligned.h>

#include <kos/anno.h>
#include <kos/exec/module.h>
#include <kos/types.h>

#include <stddef.h>

#include <libunwind/cfi.h>
#include <libunwind/dwarf.h>

#ifndef __KERNEL__
#include <dlfcn.h>
#endif /* !__KERNEL__ */

/**/
#include "dwarf.h"

DECL_BEGIN

/* Decode a signed/unsigned LEB128 integer and advance `*p_reader' */
INTERN NONNULL((1)) dwarf_sleb128_t
NOTHROW_NCX(CC libuw_dwarf_decode_sleb128)(NCX byte_t const **__restrict p_reader) {
	NCX byte_t const *reader = *p_reader;
	byte_t byte;
	dwarf_sleb128_t result = 0;
	shift_t shift = 0;
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
	*p_reader = reader;
	return result;
}

INTERN NONNULL((1)) dwarf_uleb128_t
NOTHROW_NCX(CC libuw_dwarf_decode_uleb128)(NCX byte_t const **__restrict p_reader) {
	NCX byte_t const *reader = *p_reader;
	byte_t byte;
	dwarf_uleb128_t result = 0;
	shift_t shift = 0;
	for (;;) {
		byte    = *reader++;
		result |= ((byte & 0x7f) << shift);
		shift  += 7;
		if (!(byte & 0x80))
			break;
	}
	*p_reader = reader;
	return result;
}


PRIVATE NONNULL((1)) NCX byte_t *
NOTHROW_NCX(CC calculate_tbase)(NCX void const *modptr) {
	void *result = module_fromaddr_nx(modptr);
	if (result != NULL)
		result = (void *)module_get_tbase((module_t *)result);
	return (byte_t *)result;
}

PRIVATE NONNULL((1)) NCX byte_t *
NOTHROW_NCX(CC calculate_dbase)(NCX void const *modptr) {
	void *result = module_fromaddr_nx(modptr);
	if (result != NULL)
		result = (void *)module_get_dbase((module_t *)result);
	return (byte_t *)result;
}


INTERN NONNULL((1)) NCX byte_t *
NOTHROW_NCX(CC libuw_dwarf_decode_pointer)(NCX byte_t const **__restrict p_reader,
                                           uint8_t encoding, uint8_t addrsize,
                                           struct unwind_bases *dw_bases) {
	uintptr_t offset;
	NCX byte_t *result;
	NCX byte_t const *reader = *p_reader;

	/* Relative encoding formats. */
	switch (DW_EH_PE_BASE(encoding)) {

	case DW_EH_PE_pcrel:
		result = (byte_t *)reader; /* Relative to here. */
		break;

	case DW_EH_PE_textrel:
		if (dw_bases) {
			result = (byte_t *)dw_bases->ub_tbase;
			if (!result) {
				result = calculate_tbase(reader);
				dw_bases->ub_tbase = result;
			}
		} else {
			result = calculate_tbase(reader);
		}
		break;

	case DW_EH_PE_datarel:
		if (dw_bases) {
			result = (byte_t *)dw_bases->ub_dbase;
			if (!result) {
				result = calculate_dbase(reader);
				dw_bases->ub_dbase = result;
			}
		} else {
			result = calculate_dbase(reader);
		}
		break;

	case DW_EH_PE_funcrel:
		result = (byte_t *)0;
		if (dw_bases != NULL)
			result = (byte_t *)dw_bases->ub_fbase;
		break;

	case DW_EH_PE_aligned:
		reader = (byte_t const *)(((uintptr_t)reader + (addrsize - 1)) & ~(addrsize - 1));
		result = (byte_t *)0;
		break;

	default:
	case DW_EH_PE_absptr:
		result = (byte_t *)0;
		break;
	}
	switch (DW_EH_PE_OFF(encoding)) {

	case DW_EH_PE_absptr:
		if (addrsize >= sizeof(uintptr_t)) {
			offset = UNALIGNED_GET((uintptr_t const *)reader);
#if __SIZEOF_POINTER__ > 4
		} else if (addrsize >= 4) {
			offset = UNALIGNED_GET32(reader);
#endif /* __SIZEOF_POINTER__ > 4 */
		} else if (addrsize >= 2) {
			offset = UNALIGNED_GET16(reader);
		} else /*if (addrsize >= 1)*/ {
			offset = UNALIGNED_GET8(reader);
		}
		reader += addrsize;
		break;

	case DW_EH_PE_udata2:
		offset = (uintptr_t)UNALIGNED_GET16(reader);
		reader += 2;
		break;

	case DW_EH_PE_udata4:
		offset = (uintptr_t)UNALIGNED_GET32(reader);
		reader += 4;
		break;

	case DW_EH_PE_udata8:
#if __SIZEOF_POINTER__ > 4
		offset = (uintptr_t)UNALIGNED_GET64(reader);
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		offset = (uintptr_t)UNALIGNED_GET32(reader);
#else /* ... */
		offset = (uintptr_t)UNALIGNED_GET32(reader + 4);
#endif /* !... */
		reader += 8;
		break;

	case DW_EH_PE_sdata2:
		offset = (uintptr_t)(intptr_t)(int16_t)UNALIGNED_GET16(reader);
		reader += 2;
		break;

	case DW_EH_PE_sdata4:
		offset = (uintptr_t)(intptr_t)(int32_t)UNALIGNED_GET32(reader);
		reader += 4;
		break;

	case DW_EH_PE_sdata8:
#if __SIZEOF_POINTER__ > 4
		offset = (uintptr_t)(intptr_t)(int64_t)UNALIGNED_GET64(reader);
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		offset = (uintptr_t)(intptr_t)(int32_t)UNALIGNED_GET32(reader);
#else /* ... */
		offset = (uintptr_t)(intptr_t)(int32_t)UNALIGNED_GET32(reader + 4);
#endif /* !... */
		reader += 8;
		break;

	case DW_EH_PE_uleb128:
		offset = libuw_dwarf_decode_uleb128(&reader);
		break;

	case DW_EH_PE_sleb128:
		offset = libuw_dwarf_decode_sleb128(&reader);
		break;

	default:
		offset = 0;
		reader += 1; /* ??? */
		break;
	}

	/* Special ruling: "DW_EH_PE_indirect" is only applied when the preceding "offset" was non-zero!
	 * This  behavior is **REQUIRED**  for .gcc_except_table to be  parsed properly, which generally
	 * uses "encoding = 0x9b" (DW_EH_PE_indirect | DW_EH_PE_pcrel | DW_EH_PE_sdata4), and expects us
	 * to  **NOT** dereference the produced pointer when  "DW_EH_PE_sdata4" equals 0. Looking at its
	 * sample implementation of this function (then called `read_encoded_value()'), we can see this:
	 *
	 * .../gcc-12.1.0/libgcc/unwind-pe.h:210:
	 * >> switch (encoding & 0x0f)                          /// [[[ HINT: This is our DW_EH_PE_OFF(encoding) ]]]
	 * >> {
	 * >> case DW_EH_PE_absptr:
	 * >>   result = (_Unwind_Internal_Ptr) u->ptr;
	 * >>   p += sizeof (void *);
	 * >>   break;
	 * >>
	 * >> case DW_EH_PE_uleb128:
	 * >>   {
	 * >>     _uleb128_t tmp;
	 * >>     p = read_uleb128 (p, &tmp);
	 * >>     result = (_Unwind_Internal_Ptr) tmp;
	 * >>   }
	 * >>   break;
	 * >>
	 * >> case DW_EH_PE_sleb128:
	 * >>   {
	 * >>     _sleb128_t tmp;
	 * >>     p = read_sleb128 (p, &tmp);
	 * >>     result = (_Unwind_Internal_Ptr) tmp;
	 * >>   }
	 * >>   break;
	 * >>
	 * >> [...]
	 * >>
	 * >> default:
	 * >>   __gxx_abort ();
	 * >> }
	 * >>
	 * >> if (result != 0)                                  /// [[[ Deref only happens when the "offset"
	 * >> {                                                 ///     (here-called "result") is non-zero ]]]
	 * >>   [...]
	 * >>   result += ((encoding & 0x70) == DW_EH_PE_pcrel
	 * >>             ? (_Unwind_Internal_Ptr) u : base);
	 * >>   if (encoding & DW_EH_PE_indirect)
	 * >>     result = *(_Unwind_Internal_Ptr *) result;
	 * >>   [...]
	 * >> }
	 * >> *val = result;                                    /// [[[ If the "offset" was 0, then the base is discarded
	 * >> return p;                                         ///     and the returned pointer is also zero (aka. NULL) ]]]
	 *
	 * As  you can also  see, when the  offset _is_ 0, then
	 * `*val' (our return value) must be 0 (aka. NULL), too
	 */
	if (offset == 0) {
		result = NULL;
	} else {
		result += offset;
		if (encoding & DW_EH_PE_indirect) {
			if (addrsize >= sizeof(uintptr_t)) {
				result = (byte_t *)UNALIGNED_GET((uintptr_t const *)result);
#if __SIZEOF_POINTER__ > 4
			} else if (addrsize >= 4) {
				result = (byte_t *)(uintptr_t)UNALIGNED_GET32(result);
#endif /* __SIZEOF_POINTER__ > 4 */
			} else if (addrsize >= 2) {
				result = (byte_t *)(uintptr_t)UNALIGNED_GET16(result);
			} else if (addrsize >= 1) {
				result = (byte_t *)(uintptr_t)UNALIGNED_GET8(result);
			}
		}
	}
	*p_reader = reader;
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
