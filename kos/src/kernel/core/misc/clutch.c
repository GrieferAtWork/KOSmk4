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
#ifndef GUARD_KERNEL_SRC_MISC_CLUTCH_C
#define GUARD_KERNEL_SRC_MISC_CLUTCH_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/addr2line.h>
#include <kernel/types.h>

#include <stddef.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>

DECL_BEGIN

struct ATTR_PACKED debug_abbrev_clutch {
	u8  da_code; /* == 0 */
};

struct ATTR_PACKED debug_info_clutch {
	u32 di_length;      /* Structure length following (not including) this field. */
	u16 di_version;     /* Version (== 2) */
	u32 di_abbrev;      /* Offset into .debug_abbrev */
	u8  di_addrsize;    /* == sizeof(void *) */
	u8  di_abbrev_code; /* First abbrev code (uleb128) */
};

struct ATTR_PACKED debug_loc_clutch {
	uintptr_t dl_start; /* Start */
	uintptr_t dl_end;   /* end */
};

struct ATTR_PACKED debug_str_clutch {
	char ds_string[1];
};

struct ATTR_PACKED debug_line_clutch {
	u32  dl_length;           /* Structure length following (not including) this field. */
	u16  dl_version;          /* Version (== 4) */
	u32  dl_toffset;          /* Additional data length (Offset from here to the `dl_text') */
	u8   dl_min_insn_length;  /* Min instruction length (== 1) */
	u8   dl_max_ops_per_insn; /* Max operands per instruction (== 1) */
	u8   dl_default_isstmt;   /* Default is-statement (== 1) */
	u8   dl_line_base;        /* Line base (== 1?) */
	u8   dl_line_range;       /* Line range (== 1?) */
	u8   dl_opcode_base;      /* Opcode base (== 0?) */
	char dl_file_table[1];    /* File table */
	u8   dl_text[2];          /* Line program (== DW_LNS_extended_op, DW_LNE_end_sequence) */
};

struct ATTR_PACKED debug_arange_clutch {
	u32        da_length;           /* Structure length following (not including) this field. */
	u16        da_version;          /* Version (== 2) */
	u32        da_debug_info;       /* Pointer to __kernel_debug_info_clutch */
	u8         da_addrsize;         /* Address size */
	u8         da_segsize;          /* Segment size */
	/* Align to da_addrsize here */
	uintptr_t  da_start;            /* Starting address */
	uintptr_t  da_end;              /* Ending address */
};

struct ATTR_PACKED debug_range_clutch {
	uintptr_t  da_start;            /* Starting address */
	uintptr_t  da_end;              /* Ending address */
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_abbrev.clutch")
struct debug_abbrev_clutch const __kernel_debug_abbrev_clutch = {
	/* .da_code = */ 0
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_info.clutch")
struct debug_info_clutch const __kernel_debug_info_clutch = {
	/* .di_length      = */ sizeof(struct debug_info_clutch) - 4,
	/* .di_version     = */ 2,
	/* .di_abbrev      = */ (u32)(uintptr_t)(void *)&__kernel_debug_abbrev_clutch,
	/* .di_addrsize    = */ sizeof(void *),
	/* .di_abbrev_code = */ 0
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_loc.clutch")
struct debug_loc_clutch const __kernel_debug_loc_clutch = {
	/* .dl_start = */ 0,
	/* .dl_end   = */ 0
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_line.clutch")
struct debug_line_clutch const __kernel_debug_line_clutch = {
	/* .dl_length           = */ sizeof(struct debug_line_clutch) - 4,
	/* .dl_version          = */ 4,
	/* .dl_toffset          = */ (offsetof(struct debug_line_clutch, dl_text) -
	                              offsetafter(struct debug_line_clutch, dl_toffset)),
	/* .dl_min_insn_length  = */ 1,
	/* .dl_max_ops_per_insn = */ 1,
	/* .dl_default_isstmt   = */ 1,
	/* .dl_line_base        = */ 1,
	/* .dl_line_range       = */ 1,
	/* .dl_opcode_base      = */ 0,
	/* .dl_file_table       = */ { '\0' },
	/* .dl_text             = */ {
		DW_LNS_extended_op,
		DW_LNE_end_sequence
	}
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_aranges.clutch")
struct debug_arange_clutch const __kernel_debug_aranges_clutch = {
	/* .da_length     = */ sizeof(struct debug_arange_clutch) - 4,
	/* .da_version    = */ 2,
	/* .da_debug_info = */ (u32)(uintptr_t)(void *)&__kernel_debug_info_clutch,
	/* .da_addrsize   = */ sizeof(void *),
	/* .da_segsize    = */ 0,
	/* .da_start      = */ 0,
	/* .da_end        = */ 0
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_str.clutch")
struct debug_str_clutch const __kernel_debug_str_clutch = {
	/* .ds_string */ { '\0' }
};

PRIVATE ATTR_USED ATTR_ALIGNED(1) ATTR_SECTION(".rodata.debug_ranges.clutch")
struct debug_range_clutch const __kernel_debug_ranges_clutch = {
	/* .da_start = */ 0,
	/* .da_end   = */ 0
};


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_CLUTCH_C */
