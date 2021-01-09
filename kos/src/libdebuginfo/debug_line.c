/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_LINE_C
#define GUARD_LIBDEBUGINFO_DEBUG_LINE_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/types.h>

#include <stdint.h>
#include <string.h>

#include <libdebuginfo/debug_line.h>
#include <libdebuginfo/dwarf.h>

#include "debug_line.h"

DECL_BEGIN

/* Given a pointer to the start of a debug_line CU (or a pointer to the start of
 * the .debug_line section), initialize the given debugline CU structure `result',
 * and advance `*preader' to the start of the next unit:
 * >> #define _KOS_SOURCE 1
 * >> #include <dlfcn.h>
 * >> #include <stdio.h>
 * >> #include <libdebuginfo/debug_line.h>
 * >>
 * >> // Print the source location for a given address `p'
 * >> void print_addr2line(void *p) {
 * >>     struct dl_section *s = NULL;
 * >>     di_debugline_unit_t unit;
 * >>     byte_t const *reader;
 * >>     uintptr_t relpc;
 * >>     void *m;
 * >>     if ((m = dlgethandle(p, DLGETHANDLE_FNORMAL)) == NULL)
 * >>         goto done;
 * >>     if ((s = dllocksection(m, ".debug_line")) == NULL)
 * >>         goto done;
 * >>     reader = (byte_t *)s->ds_data;
 * >>     relpc = (uintptr_t)((__byte_t *)p - (__byte_t *)dlmodulebase(m));
 * >>     while (debugline_loadunit(reader, reader + s->ds_size, &unit) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>         di_debugline_info_t info;
 * >>         if (debugline_scanunit(&unit, &info, relpc) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>             char *file,*path;
 * >>             debugline_loadfile(&unit, info.dl_srcfile, &file, &path);
 * >>             printf("path: %s\n", path);
 * >>             printf("file: %s\n", file);
 * >>             printf("line: %d\n", (int)info.dl_srcline);
 * >>             printf("col:  %u\n", (unsigned int)info.dl_srccol);
 * >>             goto done;
 * >>         }
 * >>     }
 * >>     printf("Unknown: %p\n", p);
 * >> done:
 * >>     dlunlocksection(s);
 * >> }
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1, 2, 3)) unsigned int
NOTHROW_NCX(CC libdi_debugline_loadunit)(byte_t const **__restrict preader,
                                         byte_t const *__restrict text_end,
                                         di_debugline_unit_t *__restrict result) {
	uintptr_t length;
	uint16_t version;
	byte_t const *reader;
	byte_t const *next_cu, *cu_text;
	reader = *preader;
again:
	if (reader >= text_end)
		goto section_eof;
	length = UNALIGNED_GET32((uint32_t const *)reader);
	if (length <= 15)     /* 15: Minimum size of the DWARF LineInfo header. */
		goto section_eof; /* Sentinel */
	reader += 4;
	if unlikely(length == UINT32_C(0xffffffff)) {
		length = (uintptr_t)UNALIGNED_GET64((uint64_t const *)reader);
		if (length <= 15)
			goto section_eof; /* Sentinel */
		reader += 8;
		if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&next_cu) || next_cu > text_end)
			next_cu = text_end;
		version = UNALIGNED_GET16((uint16_t const *)reader);
		reader += 2;
		length = (uintptr_t)UNALIGNED_GET64((uint64_t const *)reader);
		reader += 8;
		if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&cu_text) || cu_text > next_cu)
			goto do_next_chunk;
	} else {
		if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&next_cu) || next_cu > text_end)
			next_cu = text_end;
		version = UNALIGNED_GET16((uint16_t const *)reader);
		reader += 2;
		length = UNALIGNED_GET32((uint32_t const *)reader);
		reader += 4;
		if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&cu_text) || cu_text > next_cu) {
do_next_chunk:
			reader = next_cu;
			goto again;
		}
	}
	/* Save initial information. */
	result->dlu_headerbase = reader;
	result->dlu_textbase   = cu_text;
	result->dlu_cuend      = next_cu;
	result->dlu_version    = version;
	/* Decode the CU header. */
	result->dlu_min_insn_length = *(uint8_t const *)reader;
	if unlikely(!result->dlu_min_insn_length)
		result->dlu_min_insn_length = 1;
	reader += 1;
	result->dlu_max_ops_per_insn = 1;
	if (version >= 4) {
		result->dlu_max_ops_per_insn = *(uint8_t const *)reader;
		reader += 1;
		if unlikely(!result->dlu_max_ops_per_insn)
			result->dlu_max_ops_per_insn = 1;
	}
	result->dlu_default_isstmt = *(uint8_t const *)reader;
	reader += 1;
	result->dlu_line_base = *(int8_t const *)reader;
	reader += 1;
	result->dlu_line_range = *(uint8_t const *)reader;
	reader += 1;
	result->dlu_opcode_base = *(uint8_t const *)reader;
	reader += 1;
	result->dlu_opcode_lengths = reader;
	if unlikely(!result->dlu_line_range)
		result->dlu_line_range = 1;
	if (result->dlu_opcode_base)
		reader += result->dlu_opcode_base - 1;
	if unlikely(reader > cu_text)
		goto err_corrupted; /* Illegal overflow */
	result->dlu_pathtable = (char *)reader;
	result->dlu_pathcount = 0;
	for (;;) {
		if (!*(char *)reader) {
			++reader;
			break;
		}
		if unlikely(reader >= cu_text) {
			reader = cu_text;
			break;
		}
		reader = (byte_t *)(strend((char *)reader) + 1);
		++result->dlu_pathcount;
	}
	result->dlu_filetable = (di_debugline_fileent_t *)reader;
	*preader              = next_cu;
	return DEBUG_INFO_ERROR_SUCCESS;
section_eof:
	return DEBUG_INFO_ERROR_NOFRAME;
err_corrupted:
	return DEBUG_INFO_ERROR_CORRUPT;
}

typedef struct {
	/* Register state for `libdi_debugline_scanunit()' */
	uintptr_t       address;
	dwarf_uleb128_t file;
	dwarf_sleb128_t line;
	dwarf_uleb128_t column;
	dwarf_uleb128_t discrim;
	uint8_t         flags;
	uint8_t         op_index;
} dl_registers_t;


/* GCC warns that members of `old_state' may be uninitialized after `found_state',
 * because it doesn't understand that `old_state.address' is set to (uintptr_t)-1
 * at the beginning, which prevents `found_state' from being reached until all of
 * the other fields of `old_state' have also been populated. */
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif /* __GNUC__ */


/* Scan the given .debug_line unit `self' for information related to the given
 * `module_relative_pc', and store that information into `*result' upon success.
 * @param: module_relative_pc: The starting address of the instruction to scan for.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1, 2)) unsigned int
NOTHROW_NCX(CC libdi_debugline_scanunit)(di_debugline_unit_t const *__restrict self,
                                         di_debugline_info_t *__restrict result,
                                         uintptr_t module_relative_pc) {
	byte_t const *reader = self->dlu_textbase;
	dl_registers_t old_state, state;
#define RESET_STATE()                                                        \
	(memset(&state, 0, sizeof(state)),                                       \
	 state.file = 1, state.line = 1,                                         \
	 state.flags = self->dlu_default_isstmt                                  \
	               ? (DI_DEBUGLINE_INFO_FPROLOG | DI_DEBUGLINE_INFO_FISSTMT) \
	               : (DI_DEBUGLINE_INFO_FPROLOG))
	RESET_STATE();
	old_state.address = (uintptr_t)-1;
	while (reader < self->dlu_cuend) {
		uint8_t opcode = *reader++;
		if (opcode >= self->dlu_opcode_base) {
			/* Handle so-called special opcodes. */
			size_t temp;
			opcode -= self->dlu_opcode_base;
			temp = opcode / self->dlu_line_range;
			if (self->dlu_max_ops_per_insn == 1) {
				temp *= self->dlu_min_insn_length;
				state.address += temp;
			} else {
				state.address += ((state.op_index + temp) /
				                  self->dlu_max_ops_per_insn) *
				                 self->dlu_min_insn_length;
				state.op_index = (state.op_index + temp) %
				                 self->dlu_max_ops_per_insn;
			}
			state.line += (intptr_t)(opcode % self->dlu_line_range) +
			              self->dlu_line_base;
#define TEST_MATCH()                                           \
			{                                                  \
				if (old_state.address <= module_relative_pc && \
				    state.address > module_relative_pc)        \
					goto found_state;                          \
			}
			if (old_state.address <= module_relative_pc &&
			    state.address > module_relative_pc) {
found_state:
				/* Save location information. */
				result->dl_linestart     = old_state.address;
				result->dl_lineend       = state.address;
				result->dl_srcline       = old_state.line;
				result->dl_srccol        = old_state.column;
				result->dl_flags         = old_state.flags;
				result->dl_srcfile       = old_state.file;
				result->dl_discriminator = old_state.discrim;
				return DEBUG_INFO_ERROR_SUCCESS;
			}
			memcpy(&old_state, &state, sizeof(state));
		} else {
			switch (opcode) {

			case DW_LNS_extended_op: {
				byte_t const *ext_data;
				uintptr_t temp;
				temp     = dwarf_decode_uleb128(&reader);
				ext_data = reader;
				if unlikely(OVERFLOW_UADD((uintptr_t)reader, temp,
				                          (uintptr_t *)&reader))
					goto done;
				if unlikely(reader > self->dlu_cuend)
					goto done;
				if (temp != 0) {
					opcode = *ext_data++;
					/* Extended opcodes. */
					switch (opcode) {

					case DW_LNE_end_sequence:
						/* Reset the state machine. */
						TEST_MATCH();
						RESET_STATE();
						old_state.address = (uintptr_t)-1;
						break;

					case DW_LNE_set_address: {
						uintptr_t new_address;
						if ((size_t)temp - 1 >= 8)
							new_address = (uintptr_t)*(uint64_t const *)ext_data;
						else if ((size_t)temp - 1 >= 4)
							new_address = (uintptr_t)*(uint32_t const *)ext_data;
						else if ((size_t)temp - 1 >= 2)
							new_address = (uintptr_t)*(uint16_t const *)ext_data;
						else {
							new_address = (uintptr_t)*(uint8_t const *)ext_data;
						}
						state.address  = new_address;
						state.op_index = 0;
					}	break;

					case DW_LNE_define_file:
						/* ... */
						break;

					case DW_LNE_set_discriminator:
						state.discrim = dwarf_decode_uleb128(&ext_data);
						break;

					default:
						break;
					}
				}
			}	break;

			case DW_LNS_copy:
				TEST_MATCH();
				state.discrim = 0;
				state.flags &= ~(DI_DEBUGLINE_INFO_FBBLOCK |
				                 DI_DEBUGLINE_INFO_FEPILOG);
				state.flags |= DI_DEBUGLINE_INFO_FPROLOG;
				memcpy(&old_state, &state, sizeof(state));
				break;

			case DW_LNS_advance_pc: {
				uintptr_t temp;
				temp = dwarf_decode_uleb128(&reader);
				if (self->dlu_max_ops_per_insn == 1) {
					temp *= self->dlu_min_insn_length;
					state.address += temp;
				} else {
					state.address += ((state.op_index + temp) / self->dlu_max_ops_per_insn) *
					                 self->dlu_min_insn_length;
					state.op_index = ((state.op_index + temp) % self->dlu_max_ops_per_insn);
				}
			}	break;

			case DW_LNS_advance_line:
				state.line += dwarf_decode_sleb128(&reader);
				break;

			case DW_LNS_set_file:
				state.file = (size_t)dwarf_decode_uleb128(&reader);
				break;

			case DW_LNS_set_column:
				state.column = dwarf_decode_uleb128(&reader);
				break;

			case DW_LNS_negate_stmt:
				state.flags ^= DI_DEBUGLINE_INFO_FISSTMT;
				break;

			case DW_LNS_set_basic_block:
				state.flags |= DI_DEBUGLINE_INFO_FBBLOCK;
				break;

			case DW_LNS_const_add_pc: {
				uintptr_t temp;
				temp = (255 - self->dlu_opcode_base) / self->dlu_line_range;
				if (self->dlu_max_ops_per_insn == 1) {
					temp *= self->dlu_min_insn_length;
					state.address += temp;
				} else {
					state.address += ((state.op_index + temp) /
					                  self->dlu_max_ops_per_insn) *
					                 self->dlu_min_insn_length;
					state.op_index = (state.op_index + temp) %
					                 self->dlu_max_ops_per_insn;
				}
			}	break;

			case DW_LNS_fixed_advance_pc:
				state.address += UNALIGNED_GET16((uint16_t const *)reader);
				state.op_index = 0;
				reader += 2;
				break;

			case DW_LNS_set_prologue_end:
				state.flags &= ~DI_DEBUGLINE_INFO_FPROLOG;
				break;

			case DW_LNS_set_epilogue_begin:
				state.flags |= DI_DEBUGLINE_INFO_FEPILOG;
				break;

			case DW_LNS_set_isa:
				dwarf_decode_uleb128(&reader);
				break;

			default:
				if (opcode < self->dlu_opcode_base) {
					/* Custom opcode. */
					uint8_t n = self->dlu_opcode_lengths[opcode - 1];
					while (n--)
						dwarf_decode_uleb128(&reader);
				}
				break;
			}
		}
	}
done:
	return DEBUG_INFO_ERROR_NOFRAME;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */


DEFINE_PUBLIC_ALIAS(debugline_loadunit, libdi_debugline_loadunit);
DEFINE_PUBLIC_ALIAS(debugline_scanunit, libdi_debugline_scanunit);


DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_LINE_C */
