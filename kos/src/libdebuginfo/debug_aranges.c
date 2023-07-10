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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_ARANGES_C
#define GUARD_LIBDEBUGINFO_DEBUG_ARANGES_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <stdint.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/errno.h>

#include "debug_aranges.h"

DECL_BEGIN

/* Scan through  the given  debug_aranges blob  for a  descriptor referring  to
 * the given `module_relative_pc'. - If  found, store that descriptor's  offset
 * into the .debug_info section in `*pdebug_info_cu_offset' and return success.
 * @param: pdebug_info_cu_offset: Pointer that will  receive an  offset into  `.debug_info',
 *                                which may then be used with `debuginfo_cu_parser_loadunit'
 *                                in order to load the compilation unit associated with  the
 *                                `module_relative_pc' originally passed  to this  function.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1, 2, 3)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debugaranges_locate)(byte_t __CHECKED const *__restrict debug_aranges_start,
                                          byte_t __CHECKED const *__restrict debug_aranges_end,
                                          uintptr_t *__restrict pdebug_info_cu_offset,
                                          uintptr_t module_relative_pc) {
	byte_t __CHECKED const *reader, *next;
	uintptr_t debug_info_cu_offset;
	reader = debug_aranges_start;
	while (reader < debug_aranges_end) {
		uintptr_t length;
		uint16_t version;
		uint8_t addrsize, segsize;
		/* 6.1.2 Lookup by Address */
		length = UNALIGNED_GET32(reader); /* unit_length */
		reader += 4;
		if (length >= UINT32_C(0xfffffff0)) {
			if (length == UINT32_C(0xffffffff)) {
				/* 7.4 32-Bit and 64-Bit DWARF Formats
				 * In the 64-bit DWARF format, an initial length field is 96 bits in size, and has two parts:
				 *  - The first 32-bits have the value 0xffffffff.
				 *  - The following 64-bits contain the actual length represented as an unsigned 64-bit integer. */
				length = (uintptr_t)UNALIGNED_GET64(reader);
				reader += 8;
			} else {
				/* 7.2.2 Initial Length Values
				 * ...
				 * values 0xfffffff0 through 0xffffffff are reserved by DWARF */
				return DEBUG_INFO_ERROR_CORRUPT;
			}
		}
		if unlikely(length < 2)
			break;
		if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&next))
			next = (byte_t *)-1;
		version = UNALIGNED_GET16(reader); /* version */
		reader += 2;
		if unlikely(version != 2)
			return DEBUG_INFO_ERROR_CORRUPT;
		debug_info_cu_offset = UNALIGNED_GET32(reader); /* debug_info_offset */
		reader += 4;
		if (debug_info_cu_offset == UINT32_C(0xffffffff)) {
			length = (uintptr_t)UNALIGNED_GET64(reader);
			reader += 8;
		}
		addrsize = *(uint8_t __CHECKED const *)reader, reader += 1; /* address_size */
		segsize  = *(uint8_t __CHECKED const *)reader, reader += 1; /* segment_size */
#if __SIZEOF_POINTER__ > 4
		if unlikely(addrsize != 1 && addrsize != 2 && addrsize != 4 && addrsize != 8)
			return DEBUG_INFO_ERROR_CORRUPT;
#else /* __SIZEOF_POINTER__ > 4 */
		if unlikely(addrsize != 1 && addrsize != 2 && addrsize != 4)
			return DEBUG_INFO_ERROR_CORRUPT;
#endif /* __SIZEOF_POINTER__ <= 4 */
		if unlikely(segsize != 0)
			return DEBUG_INFO_ERROR_CORRUPT;
		/* Adjust for padding. */
		reader += (addrsize * 2) - ((reader - debug_aranges_start) % (addrsize * 2));
		while (reader < debug_aranges_end) {
			uintptr_t start, length;
			switch (addrsize) {

			case 1:
				start = UNALIGNED_GET8(reader);
				reader += 1;
				length = UNALIGNED_GET8(reader);
				reader += 1;
				break;

			case 2:
				start = UNALIGNED_GET16(reader);
				reader += 2;
				length = UNALIGNED_GET16(reader);
				reader += 2;
				break;

			case 4:
				start = UNALIGNED_GET32(reader);
				reader += 4;
				length = UNALIGNED_GET32(reader);
				reader += 4;
				break;

#if __SIZEOF_POINTER__ > 4
			case 8:
				start = UNALIGNED_GET64(reader);
				reader += 8;
				length = UNALIGNED_GET64(reader);
				reader += 8;
				break;
#endif /* __SIZEOF_POINTER__ > 4 */

			default: __builtin_unreachable();
			}
			if (!start && !length)
				break;
			if (module_relative_pc >= start &&
			    module_relative_pc < start + length) {
				*pdebug_info_cu_offset = debug_info_cu_offset; /* Found it! */
				return DEBUG_INFO_ERROR_SUCCESS;
			}
		}
/*do_next:*/
		reader = next;
	}
	return DEBUG_INFO_ERROR_NOFRAME;
}


DEFINE_PUBLIC_ALIAS(debugaranges_locate, libdi_debugaranges_locate);

DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_ARANGES_C */
