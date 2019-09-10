/*[[[magic
local opt = options.setdefault("GCC.options",[]);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-O3");
]]]*/
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_DEBUG_ARANGES_C
#define GUARD_LIBDEBUGINFO_DEBUG_ARANGES_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include "debug_aranges.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/dwarf.h>

DECL_BEGIN

/* Scan through the given debug_aranges blob for a descriptor referring to
 * the given `module_relative_pc'. - If found, store that descriptor's offset
 * into the .debug_info section in `*pdebug_info_cu_offset' and return success.
 * @param: pdebug_info_cu_offset: Pointer that will receive an offset into .debug_info,
 *                                which may then be used with `debuginfo_cu_parser_loadunit'
 *                                in order to load the compilation unit associated with
 *                                the `module_relative_pc' originally passed to this
 *                                function.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libdi_debugaranges_locate)(byte_t *__restrict debug_aranges_start,
                                          byte_t *__restrict debug_aranges_end,
                                          uint32_t *__restrict pdebug_info_cu_offset,
                                          uintptr_t module_relative_pc) {
	byte_t *reader, *next;
	uint32_t debug_info_cu_offset;
	reader = debug_aranges_start;
	while (reader < debug_aranges_end) {
		uint32_t length;
		uint16_t version;
		uint8_t addrsize, segsize;
		length = UNALIGNED_GET32((uint32_t *)reader);
		reader += 4;
		if unlikely(length < 2)
			break;
		if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&next))
			next = (byte_t *)-1;
		version = UNALIGNED_GET16((uint16_t *)reader);
		reader += 2;
		if unlikely(version != 2)
			return DEBUG_INFO_ERROR_CORRUPT;
		debug_info_cu_offset = UNALIGNED_GET32((uint32_t *)reader);
		reader += 4;
		addrsize = *(uint8_t *)reader, reader += 1;
		segsize  = *(uint8_t *)reader, reader += 1;
#if __SIZEOF_POINTER__ > 4
		if unlikely(addrsize != 1 && addrsize != 2 && addrsize != 4 && addrsize != 8)
			return DEBUG_INFO_ERROR_CORRUPT;
#else
		if unlikely(addrsize != 1 && addrsize != 2 && addrsize != 4)
			return DEBUG_INFO_ERROR_CORRUPT;
#endif
		if unlikely(segsize != 0)
			return DEBUG_INFO_ERROR_CORRUPT;
		/* Adjust for padding. */
		reader += (addrsize * 2) - ((reader - debug_aranges_start) % (addrsize * 2));
		while (reader < debug_aranges_end) {
			uintptr_t start, length;
			switch (addrsize) {
			case 1:
				start = *(uint8_t *)reader;
				reader += 1;
				length = *(uint8_t *)reader;
				reader += 1;
				break;
			case 2:
				start = UNALIGNED_GET16((uint16_t *)reader);
				reader += 2;
				length = UNALIGNED_GET16((uint16_t *)reader);
				reader += 2;
				break;
			case 4:
				start = UNALIGNED_GET32((uint32_t *)reader);
				reader += 4;
				length = UNALIGNED_GET32((uint32_t *)reader);
				reader += 4;
				break;
#if __SIZEOF_POINTER__ > 4
			case 8:
				start = UNALIGNED_GET64((uint64_t *)reader);
				reader += 8;
				length = UNALIGNED_GET64((uint64_t *)reader);
				reader += 8;
				break;
#endif
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
