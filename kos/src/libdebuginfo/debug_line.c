/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_DEBUG_LINE_C
#define GUARD_LIBDEBUGINFO_DEBUG_LINE_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <kos/anno.h>
#include <kos/types.h>

#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/errno.h>
#include <libunwind/dwarf.h>

#include "debug_info.h"
#include "debug_line.h"

DECL_BEGIN

PRIVATE NONNULL((1, 2)) bool
NOTHROW_NCX(CC skip_fileinfo)(di_debuginfo_cu_simple_parser_t *__restrict parser,
                              di_debugline_fileinfo_format_t const *__restrict format) {
	NCX byte_t const *fmtreader;
	uint8_t fmtcount;
	fmtreader = (byte_t const *)format;
	fmtcount  = *(uint8_t const *)fmtreader;
	fmtreader += 1;
	for (; fmtcount; --fmtcount) {
		dwarf_uleb128_t form;
		if unlikely(parser->dsp_cu_info_pos >= parser->dsp_cu_info_end) {
			CORRUPT();
			return false;
		}
		dwarf_decode_uleb128(&fmtreader);        /* file_name_entry_format.type */
		form = dwarf_decode_uleb128(&fmtreader); /* file_name_entry_format.form */
		libdi_debuginfo_cu_parser_skipform(parser, form, &fmtreader);
	}
	return true;
}

PRIVATE NONNULL((1)) size_t
NOTHROW_NCX(CC debugline_unit_count_dwarf4_numfiles)(di_debugline_unit_t const *__restrict self) {
	size_t result = 0;
	NCX byte_t const *reader;
	reader = self->dlu_filedata;
	for (;;) {
		if (!*(char *)reader)
			break;
		if unlikely(reader >= self->dlu_textbase)
			break;
		reader = (byte_t *)(strend((char *)reader) + 1);
		dwarf_decode_uleb128((byte_t const **)&reader);
		dwarf_decode_uleb128((byte_t const **)&reader);
		dwarf_decode_uleb128((byte_t const **)&reader);
		++result;
	}
	return result;
}

/* Find the data-blob associated with the `nth' extended file descriptor. */
PRIVATE WUNUSED NONNULL((1)) NCX byte_t const *
NOTHROW_NCX(CC debugline_unit_get_extra_file)(di_debugline_unit_t const *__restrict self,
                                              dwarf_uleb128_t nth) {
	NCX byte_t const *reader = self->dlu_textbase;
	while (reader < self->dlu_cuend) {
		uint8_t opcode = *reader++;
		switch (opcode) {

		case DW_LNS_extended_op: {
			NCX byte_t const *ext_data;
			uintptr_t temp;
			temp     = dwarf_decode_uleb128(&reader);
			ext_data = reader;
			if unlikely(OVERFLOW_UADD((uintptr_t)reader, temp,
			                          (uintptr_t *)&reader))
				ERROR(done);
			if unlikely(reader > self->dlu_cuend)
				ERROR(done);
			if (temp != 0) {
				opcode = *ext_data++;
				/* Check for extended file entries. */
				if (opcode == DW_LNE_define_file) {
					if (nth == 0)
						return ext_data;
					--nth;
				}
			}
		}	break;

		case DW_LNS_advance_pc:
		case DW_LNS_set_file:
		case DW_LNS_set_column:
		case DW_LNS_set_isa:
			dwarf_decode_uleb128(&reader);
			break;

		case DW_LNS_advance_line:
			dwarf_decode_sleb128(&reader);
			break;

		case DW_LNS_fixed_advance_pc:
			reader += 2;
			break;

		case DW_LNS_negate_stmt:
		case DW_LNS_set_basic_block:
		case DW_LNS_const_add_pc:
		case DW_LNS_set_prologue_end:
		case DW_LNS_set_epilogue_begin:
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
done:
	return NULL;
}

/* Decode a given file index into its filename and pathname components. */
INTERN NONNULL((1, 3, 4)) void
NOTHROW_NCX(CC libdi_debugline_loadfile)(di_debugline_unit_t *__restrict self, /* Only non-const for lazy init */
                                         dwarf_uleb128_t index, di_debugline_fileinfo_t *__restrict result,
                                         struct di_string_sections_struct const *__restrict sections) {
	di_debuginfo_cu_simple_parser_t parser;
	bzero(result, sizeof(*result));
	if (self->dlu_version < 5) {
		if (!index)
			return;
		--index;

		/* Lazily calculate file counts. */
		if (self->dlu_filecount == 0)
			self->dlu_filecount = debugline_unit_count_dwarf4_numfiles(self);
	}

	/* Load a parser for file data. */
	parser.dsp_cu_info_end = self->dlu_textbase;
	parser.dsp_cu_info_pos = self->dlu_filedata;
	parser.dsp_ptrsize     = self->dlu_ptrsize;
	parser.dsp_addrsize    = self->dlu_addrsize;
	parser.dsp_version     = self->dlu_version;

	if (index >= self->dlu_filecount) {
		/* Must be an extended file (~ala `DW_LNE_define_file')
		 * NOTE: Officially, these were removed  in dwarf-5, but since  we
		 *       also support dwarf-4, we still have to support them also!
		 * s.a. DWARF4.pdf -- Section 6.2.5.3 -- 3. DW_LNE_define_file */
		index -= self->dlu_filecount;
		parser.dsp_cu_info_pos = debugline_unit_get_extra_file(self, index);
		if unlikely(!parser.dsp_cu_info_pos)
			ERRORF(err_corrupt, "index = %" PRIuSIZ, index);
	} else {
		/* Skip entries that we don't care about. */
		for (; index; --index) {
			if unlikely(!skip_fileinfo(&parser, self->dlu_filefmt))
				ERROR(err_corrupt);
		}
	}

	/* Decode our own entry! */
	{
		NCX byte_t const *fmtreader;
		uint8_t fmtcount;
		fmtreader = (byte_t const *)self->dlu_filefmt;
		fmtcount  = *(uint8_t const *)fmtreader;
		fmtreader += 1;
		index = (dwarf_uleb128_t)-1;
		for (; fmtcount; --fmtcount) {
			dwarf_uleb128_t type, form;
			type = dwarf_decode_uleb128(&fmtreader); /* file_name_entry_format.type */
			form = dwarf_decode_uleb128(&fmtreader); /* file_name_entry_format.form */
			switch (type) {
			case DW_LNCT_directory_index:
				if (!libdi_debuginfo_cu_parser_getconst(&parser, form, &index, fmtreader))
					index = (dwarf_uleb128_t)-1;
				break;
			case DW_LNCT_path:
				if (!libdi_debuginfo_cu_parser_getstring_ex(&parser, form,
				                                            &result->dlfi_file,
				                                            sections))
					result->dlfi_file = NULL;
				break;
			default:
				break;
			}
			libdi_debuginfo_cu_parser_skipform(&parser, form, &fmtreader);
		}
	}

	/* Verify that we have a path index. */
	if (index == (dwarf_uleb128_t)-1)
		return;
	if (self->dlu_version < 5) {
		if (!index)
			return;
		--index;
	}
	if unlikely(index >= self->dlu_pathcount)
		ERROR(err_corrupt); /* Shouldn't happen */

	/* Modify the parser to decode path- rather than file-names. */
	parser.dsp_cu_info_pos = self->dlu_pathdata;

	/* Skip entries that we don't care about. */
	for (; index; --index) {
		if unlikely(!skip_fileinfo(&parser, self->dlu_pathfmt))
			ERROR(err_corrupt);
	}

	/* Decode our path index! */
	{
		NCX byte_t const *fmtreader;
		uint8_t fmtcount;
		fmtreader = (byte_t const *)self->dlu_pathfmt;
		fmtcount  = *(uint8_t const *)fmtreader;
		fmtreader += 1;
		for (; fmtcount; --fmtcount) {
			dwarf_uleb128_t type, form;
			type = dwarf_decode_uleb128(&fmtreader); /* file_name_entry_format.type */
			form = dwarf_decode_uleb128(&fmtreader); /* file_name_entry_format.form */
			switch (type) {
			case DW_LNCT_path:
				if (!libdi_debuginfo_cu_parser_getstring_ex(&parser, form,
				                                            &result->dlfi_path,
				                                            sections))
					result->dlfi_path = NULL;
				break;
			default:
				break;
			}
			libdi_debuginfo_cu_parser_skipform(&parser, form, &fmtreader);
		}
	}
	return;
err_corrupt:
	return;
}


/* DWARF5-style format descriptor for DWARF4 path/file info (di_debugline_fileinfo_format_t) */
PRIVATE byte_t const dwarf4_lne_pathfmt[] = {
	1,              /* dlff_count */
	DW_LNCT_path,   /* dlff_entries[0].dlffe_type */
	DW_FORM_string, /* dlff_entries[0].dlffe_form */
};

/* NOTE: In DWARF4, file information looked like this:
 * >> typedef struct __ATTR_PACKED {
 * >>     char            fe_name[1024]; // Filename (NUL-terminated)
 * >>     dwarf_uleb128_t fe_path;       // File path index.
 * >>     dwarf_uleb128_t fe_b;          // timestamp...
 * >>     dwarf_uleb128_t fe_c;          // file size...
 * >> } di_debugline_fileent_t; */
PRIVATE byte_t const dwarf4_lne_filefmt[] = {
	4,                       /* dlff_count */
	DW_LNCT_path,            /* dlff_entries[0].dlffe_type -- fe_name */
	DW_FORM_string,          /* dlff_entries[0].dlffe_form -- fe_name */
	DW_LNCT_directory_index, /* dlff_entries[1].dlffe_type -- fe_path */
	DW_FORM_udata,           /* dlff_entries[1].dlffe_form -- fe_path */
	DW_LNCT_timestamp,       /* dlff_entries[2].dlffe_type -- fe_b */
	DW_FORM_udata,           /* dlff_entries[2].dlffe_form -- fe_b */
	DW_LNCT_size,            /* dlff_entries[3].dlffe_type -- fe_c */
	DW_FORM_udata,           /* dlff_entries[3].dlffe_form -- fe_c */
};



/* Given a pointer to the start of a .debug_line CU (or a pointer to the start  of
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
 * >>     relpc = (uintptr_t)((byte_t *)p - (byte_t *)dlmodulebase(m));
 * >>     while (debugline_loadunit(reader, reader + s->ds_size, &unit) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>         di_debugline_info_t info;
 * >>         if (debugline_scanunit(&unit, &info, relpc) == DEBUG_INFO_ERROR_SUCCESS) {
 * >>             char *file, *path;
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
INTERN TEXTSECTION NONNULL((1, 3)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debugline_loadunit)(NCX byte_t const **__restrict preader,
                                         NCX byte_t const *text_end,
                                         di_debugline_unit_t *__restrict result) {
	uintptr_t length;
	NCX byte_t const *reader;
	NCX byte_t const *next_cu, *cu_text;
	reader = *preader;
again:
	if (reader >= text_end)
		goto section_eof;

	/* 6.2.4 The Line Number Program Header */
	length = UNALIGNED_GET32(reader);
	if (length <= 15)     /* 15: Minimum size of the DWARF LineInfo header. */
		goto section_eof; /* Sentinel */
	reader += 4;
	result->dlu_ptrsize = 4;
	if unlikely(length == UINT32_C(0xffffffff)) {
		length = (uintptr_t)UNALIGNED_GET64(reader);
		if (length <= 15)
			goto section_eof; /* Sentinel */
		result->dlu_ptrsize = 8;
		reader += 8;
	}
	if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&next_cu) || next_cu > text_end)
		next_cu = text_end;
	result->dlu_version = UNALIGNED_GET16(reader); /* version */
	reader += 2;
	result->dlu_addrsize = sizeof(void *);
	if (result->dlu_version >= 5) {
		result->dlu_addrsize = *(uint8_t const *)reader; /* address_size */
		reader += 1;
		/*segment_selector_size = *(uint8_t const *)reader;*/ /* segment_selector_size */
		reader += 1;
	}

	/* header_length */
	length = result->dlu_ptrsize == 8 ? (uintptr_t)UNALIGNED_GET64(reader)
	                                  : (uintptr_t)UNALIGNED_GET32(reader);
	reader += result->dlu_ptrsize;
	if (OVERFLOW_UADD((uintptr_t)reader, length, (uintptr_t *)&cu_text) || cu_text > next_cu) {
		reader = next_cu;
		goto again;
	}

	/* Save initial information. */
	result->dlu_headerbase = reader;
	result->dlu_textbase   = cu_text;
	result->dlu_cuend      = next_cu;

	/* Decode the CU header. */
	result->dlu_min_insn_length = *(uint8_t const *)reader; /* minimum_instruction_length */
	reader += 1;
	if unlikely(!result->dlu_min_insn_length)
		result->dlu_min_insn_length = 1;

	result->dlu_max_ops_per_insn = 1;
	if (result->dlu_version >= 4) {
		result->dlu_max_ops_per_insn = *(uint8_t const *)reader; /* maximum_operations_per_instruction */
		reader += 1;
		if unlikely(!result->dlu_max_ops_per_insn)
			result->dlu_max_ops_per_insn = 1;
	}
	result->dlu_default_isstmt = *(uint8_t const *)reader; /* default_is_stmt */
	reader += 1;
	result->dlu_line_base = *(int8_t const *)reader; /* line_base */
	reader += 1;
	result->dlu_line_range = *(uint8_t const *)reader; /* line_range */
	reader += 1;
	result->dlu_opcode_base = *(uint8_t const *)reader; /* opcode_base */
	reader += 1;
	result->dlu_opcode_lengths = reader; /* standard_opcode_lengths */
	if unlikely(!result->dlu_line_range)
		result->dlu_line_range = 1;
	if (result->dlu_opcode_base)
		reader += result->dlu_opcode_base - 1;
	if unlikely(reader >= cu_text)
		goto err_corrupted; /* Illegal overflow */
	if (result->dlu_version >= 5) {
		uint8_t count;

		/* Directory format table. */
		result->dlu_pathfmt = (di_debugline_fileinfo_format_t const *)reader;
		count = *(uint8_t const *)reader; /* directory_entry_format_count */
		reader += 1;
		for (; count; --count) {
			dwarf_decode_uleb128(&reader); /* directory_entry_format.type */
			dwarf_decode_uleb128(&reader); /* directory_entry_format.form */
		}

		/* Directory table. */
		result->dlu_pathcount = dwarf_decode_uleb128(&reader); /* directories_count */
		result->dlu_pathdata  = reader;                        /* directories */

		/* Skip `directories' table */
		{
			size_t i;
			di_debuginfo_cu_simple_parser_t parser;
			parser.dsp_cu_info_end = cu_text;
			parser.dsp_cu_info_pos = reader;
			parser.dsp_ptrsize     = result->dlu_ptrsize;
			parser.dsp_addrsize    = result->dlu_addrsize;
			parser.dsp_version     = result->dlu_version;
			for (i = 0; i < result->dlu_pathcount; ++i) {
				if unlikely(!skip_fileinfo(&parser, result->dlu_pathfmt))
					ERROR(err_corrupted);
			}
			reader = parser.dsp_cu_info_pos;
		}

		/* File format table. */
		result->dlu_filefmt = (di_debugline_fileinfo_format_t const *)reader;
		count = *(uint8_t const *)reader; /* file_name_entry_format_count */
		reader += 1;
		for (; count; --count) {
			dwarf_decode_uleb128(&reader); /* file_name_entry_format.type */
			dwarf_decode_uleb128(&reader); /* file_name_entry_format.form */
		}

		/* File table. */
		result->dlu_filecount = dwarf_decode_uleb128(&reader); /* file_names_count */
		result->dlu_filedata  = reader;                        /* file_names */
	} else {
		result->dlu_pathfmt = (di_debugline_fileinfo_format_t const *)dwarf4_lne_pathfmt;
		result->dlu_filefmt = (di_debugline_fileinfo_format_t const *)dwarf4_lne_filefmt;

		/* Scan path table. */
		result->dlu_pathdata  = reader;
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
		result->dlu_filedata  = reader;
		result->dlu_filecount = 0; /* Calculated lazily */
	}
	*preader = next_cu;
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
 * because it doesn't understand that `old_state.address' is set to  (uintptr_t)-1
 * at the beginning, which prevents `found_state' from being reached until all  of
 * the other fields of `old_state' have also been populated. */
__pragma_GCC_diagnostic_push_ignored(Wmaybe_uninitialized)


/* Scan the given .debug_line unit `self'  for information related to the  given
 * `module_relative_pc', and store that information into `*result' upon success.
 * @param: module_relative_pc: The starting address of the instruction to scan for.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: ...
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTERN TEXTSECTION NONNULL((1, 2)) debuginfo_errno_t
NOTHROW_NCX(CC libdi_debugline_scanunit)(di_debugline_unit_t const *__restrict self,
                                         di_debugline_info_t *__restrict result,
                                         uintptr_t module_relative_pc) {
	NCX byte_t const *reader = self->dlu_textbase;
	dl_registers_t old_state, state;
#define RESET_STATE()                                                        \
	(bzero(&state, sizeof(state)),                                           \
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
				NCX byte_t const *ext_data;
				uintptr_t temp;
				temp     = dwarf_decode_uleb128(&reader);
				ext_data = reader;
				if unlikely(OVERFLOW_UADD((uintptr_t)reader, temp,
				                          (uintptr_t *)&reader))
					ERROR(done);
				if unlikely(reader > self->dlu_cuend)
					ERROR(done);
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
						if ((size_t)temp - 1 >= 8) {
							new_address = (uintptr_t)UNALIGNED_GET64(ext_data);
						} else if ((size_t)temp - 1 >= 4) {
							new_address = (uintptr_t)UNALIGNED_GET32(ext_data);
						} else if ((size_t)temp - 1 >= 2) {
							new_address = (uintptr_t)UNALIGNED_GET16(ext_data);
						} else {
							new_address = (uintptr_t)UNALIGNED_GET8(ext_data);
						}
						state.address  = new_address;
						state.op_index = 0;
					}	break;

					case DW_LNE_define_file:
						/* Handled by `debugline_unit_get_extra_file()' */
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
				state.address += UNALIGNED_GET16(reader);
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

__pragma_GCC_diagnostic_pop_ignored(Wmaybe_uninitialized)

DEFINE_PUBLIC_ALIAS(debugline_loadfile, libdi_debugline_loadfile);
DEFINE_PUBLIC_ALIAS(debugline_loadunit, libdi_debugline_loadunit);
DEFINE_PUBLIC_ALIAS(debugline_scanunit, libdi_debugline_scanunit);


DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_LINE_C */
