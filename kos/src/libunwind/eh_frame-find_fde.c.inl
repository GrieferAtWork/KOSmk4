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
#ifdef __INTELLISENSE__
#include "eh_frame.c"
#define FIND_SPECIFIC_ADDRESS 1
#endif /* !__INTELLISENSE__ */

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/kernel/types.h>

#include <stdint.h>
#include <string.h>

#ifdef GUARD_LIBUNWIND_API_H
#include "dwarf.h"
#else /* GUARD_LIBUNWIND_API_H */
#include <libunwind/dwarf.h>
#endif /* !GUARD_LIBUNWIND_API_H */

DECL_BEGIN


#ifndef FIND_SPECIFIC_ADDRESS
/* Load the next eh_frame function  descriptor from `*peh_frame_reader', which  must
 * either be a  pointer to the  start of the  `.eh_frame' section, or  be the  value
 * written back to `*peh_frame_reader' after a previous call to `unwind_fde_load()'.
 * @return: UNWIND_SUCCESS:  Successfully read the next FDE entry.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
#ifdef DEBUG_FRAME
INTERN NONNULL((1, 2, 3, 4)) unwind_errno_t
#else /* DEBUG_FRAME */
INTERN NONNULL((1, 2, 3)) unwind_errno_t
#endif /* !DEBUG_FRAME */
NOTHROW_NCX(CC libuw_unwind_fde_load)(byte_t const **__restrict peh_frame_reader,
#ifdef DEBUG_FRAME
                                      byte_t const *eh_frame_start,
#endif /* DEBUG_FRAME */
                                      byte_t const *eh_frame_end,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address)
#else /* !FIND_SPECIFIC_ADDRESS */
/* Same as `unwind_fde_load()', but quickly search for and return the
 * FDE descriptor containing  the given  `absolute_pc' text  address.
 * @return: UNWIND_SUCCESS:  Found the FDE entry associated with `absolute_pc'.
 * @return: UNWIND_NO_FRAME: Failed to read an FDE entry (Assume EOF) */
INTERN NONNULL((1, 2, 4)) unwind_errno_t
NOTHROW_NCX(CC libuw_unwind_fde_scan)(byte_t const *reader,
                                      byte_t const *eh_frame_end,
                                      void const *absolute_pc,
                                      unwind_fde_t *__restrict result,
                                      uint8_t sizeof_address)
#endif /* FIND_SPECIFIC_ADDRESS */
{
#ifndef FIND_SPECIFIC_ADDRESS
	byte_t const *reader = *peh_frame_reader;
#ifndef DEBUG_FRAME
	byte_t const *eh_frame_start = reader;
#endif /* DEBUG_FRAME */
#else /* !FIND_SPECIFIC_ADDRESS */
	byte_t const *eh_frame_start = reader;
#endif /* !FIND_SPECIFIC_ADDRESS */
	byte_t const *next_chunk;
	byte_t const *cie_reader, *fde_reader;
	size_t length;
#ifdef DEBUG_FRAME
	uintptr_t cie_offset;
#else /* DEBUG_FRAME */
	uint32_t cie_offset;
#endif /* !DEBUG_FRAME */
	uint8_t enclsda;
	uint8_t version;
	uint8_t used_sizeof_address;
	char const *cie_augstr;
	struct CIE const *cie;

	/* Must initialize the FBASE field. Otherwise, maliciously crafted  CFI
	 * instrumentation could access the FBASE field before it is *normally*
	 * initialized. */
	result->f_bases.ub_fbase = NULL;
again:
	if (reader >= eh_frame_end)
		ERROR(err_noframe);
	length = (size_t)UNALIGNED_GET32(reader); /* eh_chunk_size */
	reader += 4;
	if unlikely((uint32_t)length == (uint32_t)-1) {
#if __SIZEOF_POINTER__ > 4
		length = (size_t)UNALIGNED_GET64(reader); /* eh_chunk_size64 */
		reader += 8;
#else /* __SIZEOF_POINTER__ > 4 */
		ERROR(err_noframe); /* Too large. Impossible to represent. */
#endif /* __SIZEOF_POINTER__ <= 4 */
	}
	if unlikely(!length)
		ERROR(err_noframe);
	next_chunk = reader + length;
	cie_offset = UNALIGNED_GET32(reader); /* eh_cie_offset */
#ifdef DEBUG_FRAME
	if (cie_offset == UINT32_C(0xffffffff))
		goto do_next_chunk; /* This is a CIE, not an FDE */
	fde_reader = reader + 4;
	cie = (struct CIE const *)(eh_frame_start + cie_offset);
#else /* DEBUG_FRAME */
	if (cie_offset == 0)
		goto do_next_chunk; /* This is a CIE, not an FDE */
	cie = (struct CIE const *)(reader - cie_offset);
	fde_reader = reader + 4;
#endif /* !DEBUG_FRAME */
	if unlikely(!((byte_t const *)cie >= eh_frame_start &&
	              (byte_t const *)cie < eh_frame_end))
		ERRORF(err_noframe, "cie=%p, eh_frame_start=%p, eh_frame_end=%p\n",
		       cie, eh_frame_start, eh_frame_end);

	/* Load the augmentation string of the associated CIE. */
	cie_reader = (byte_t const *)cie;
	cie_reader += 4; /* cie_size */
	if (UNALIGNED_GET32(&((uint32_t const *)cie_reader)[-1]) == (uint32_t)-1) {
#if __SIZEOF_POINTER__ > 4
		cie_reader += 8; /* cie_size64 */
#else /* __SIZEOF_POINTER__ > 4 */
		goto do_next_chunk;
#endif /* __SIZEOF_POINTER__ <= 4 */
	}
	cie_reader += 4;                        /* uint32_t cie_id */
	version = *(uint8_t const *)cie_reader; /* uint8_t  cie_version */
	cie_reader += 1;                        /* ... */
	cie_augstr = (char const *)cie_reader;  /* char     cie_augstr[] */
	cie_reader = (byte_t const *)strend(cie_augstr) + 1;
	used_sizeof_address = sizeof_address;
	if unlikely(version >= 4) {
		used_sizeof_address = *(uint8_t const *)cie_reader; /* uint8_t cie_addrsize */
		cie_reader += 1;                                    /* ... */
		cie_reader += 1;                                    /* uint8_t cie_segsize */
	}

	/* Read code and data alignments. */
	result->f_codealign = dwarf_decode_uleb128(&cie_reader); /* uleb128_t cie_codealign */
	result->f_dataalign = dwarf_decode_sleb128(&cie_reader); /* uleb128_t cie_dataalign */
	if likely(version >= 3) {
		result->f_retreg = (unwind_regno_t)dwarf_decode_uleb128(&cie_reader); /* cie_retreg */
	} else {
		/* dwarf-2 variant */
		result->f_retreg = *(uint8_t const *)cie_reader; /* cie_retreg */
		cie_reader += 1;                                 /* ... */
	}

	/* Pointer encodings default to `DW_EH_PE_absptr'. */
	result->f_ptrenc   = DW_EH_PE_absptr;
	enclsda            = DW_EH_PE_absptr;
	result->f_sigframe = 0;

	/* No personality function by default. */
	result->f_persofun = NULL;
	result->f_lsdaaddr = NULL;
	if (cie_augstr[0] == 'z') {
		char const *aug_iter = cie_augstr;
		/* Interpret the augmentation string. */
		uintptr_t aug_length;
		byte_t const *aug_end;
		aug_length = dwarf_decode_uleb128(&cie_reader); /* uleb128_t cie_auglen */
		aug_end    = cie_reader + aug_length;
		if unlikely(aug_end < cie_reader || aug_end > eh_frame_end) {
			/* Check for overflow/underflow. */
			ERRORF(err_noframe, "cie_reader=%p, aug_end=%p, eh_frame_end=%p\n",
			       cie_reader, aug_end, eh_frame_end);
		}
		while (*++aug_iter && cie_reader < aug_end) {
			if (*aug_iter == 'L') {
				enclsda = *cie_reader++; /* uint8_t cie_lsdaenc */
			} else if (*aug_iter == 'P') {
				uint8_t encperso   = *cie_reader++; /* uint8_t  cie_persoenc */
				result->f_persofun = (void *)dwarf_decode_pointer(&cie_reader,
				                                                  encperso,
				                                                  used_sizeof_address,
				                                                  &result->f_bases);
			} else if (*aug_iter == 'R') {
				result->f_ptrenc = *cie_reader++;
			} else {
				/* XXX: What then? */
			}
		}
		/* `aug_end' now points at `c_initinstr' */
		cie_reader = aug_end;
	}

	/* fde_funbase */
	result->f_pcstart = dwarf_decode_pointer(&fde_reader,
	                                         result->f_ptrenc,
	                                         used_sizeof_address,
	                                         &result->f_bases);

	/* fde_funsize */
	result->f_pcend = dwarf_decode_pointer(&fde_reader,
	                                       DW_EH_PE_OFF(result->f_ptrenc),
	                                       used_sizeof_address,
	                                       &result->f_bases);
	if (OVERFLOW_UADD((uintptr_t)result->f_pcstart,
	                  (uintptr_t)result->f_pcend,
	                  (uintptr_t *)&result->f_pcend))
		goto do_next_chunk;

	/* Check if the CIE points to the proper bounds. */
#ifdef FIND_SPECIFIC_ADDRESS
	if (absolute_pc < result->f_pcstart)
		goto do_next_chunk;
	if (absolute_pc >= result->f_pcend)
		goto do_next_chunk;
#endif /* FIND_SPECIFIC_ADDRESS */

	/* Found it! - Save the pointer to the initial instruction set. */
	result->f_inittext = cie_reader; /* cie_inittxsiz */

	/* Figure out the max length of that instruction set. */
	cie_reader = (byte_t const *)cie;
	length     = UNALIGNED_GET32(cie_reader); /* cie_inittxsiz */
	cie_reader += 4;

#if __SIZEOF_POINTER__ > 4
	if unlikely((uint32_t)length == (uint32_t)-1) {
		/* Above code already asserted that the length fits into 32 bits of the CIE. */
		length = (size_t)(*(u64 const *)reader);
		reader += 8;
	}
#endif /* __SIZEOF_POINTER__ > 4 */
	cie_reader += length;
	result->f_inittextend = cie_reader;

	/* Parse augmentation data of the FDE. */
	if (cie_augstr[0] == 'z') {
		uintptr_t aug_length;
		byte_t const *aug_end;
		aug_length = dwarf_decode_uleb128(&fde_reader); /* c_auglength */
		aug_end    = fde_reader + aug_length;
		while (*++cie_augstr && fde_reader <= aug_end) {
			if (*cie_augstr == 'L') {
				if unlikely(fde_reader == aug_end)
					break;
				result->f_lsdaaddr = dwarf_decode_pointer(&fde_reader, enclsda,
				                                          used_sizeof_address,
				                                          &result->f_bases);
			} else if (*cie_augstr == 'S') {
				result->f_sigframe = 1;
			}
		}
		fde_reader = aug_end;
	}
	result->f_evaltext    = fde_reader;
	result->f_evaltextend = next_chunk;
	result->f_addrsize    = used_sizeof_address;
#ifndef FIND_SPECIFIC_ADDRESS
	*peh_frame_reader = next_chunk;
#endif /* FIND_SPECIFIC_ADDRESS */
	return UNWIND_SUCCESS;
do_next_chunk:
	if unlikely(next_chunk < reader) {
		/* Underflow */
		ERRORF(err_noframe, "next_chunk=%p, reader=%p\n", next_chunk, reader);
	}
	reader = next_chunk;
	goto again;
err_noframe:
	return UNWIND_NO_FRAME;
}
#undef FIND_SPECIFIC_ADDRESS

DECL_END
