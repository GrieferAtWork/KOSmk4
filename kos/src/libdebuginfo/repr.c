/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDEBUGINFO_REPR_C
#define GUARD_LIBDEBUGINFO_REPR_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1 /* Don't profile this file */

#include "repr.h"

#include "api.h"

#include <hybrid/compiler.h>

#include <stdbool.h>
#include <stddef.h>
#include <string.h> /* strend() */

#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/repr.h>
#include <libunwind/cfi.h>

#include "debug_info.h"

DECL_BEGIN

#ifndef __KERNEL__
/* !!!This file should be optimized for size as much as possible!!!
 *
 * Encode strings in this file using `strend()^INDEX' encoding,
 * such that a lookup function would do this:
 * >> if (INDEX >= COUNT)
 * >>     return NULL;
 * >> result = base;
 * >> while (INDEX--)
 * >>     result = strend(result) + 1;
 * >> if (!*result)
 * >>     result = NULL;
 * >> return result;
 * The raw text database strings could then be encoding via an inline
 * deemon script that looks at the associated headers.
 */


/*[[[deemon
import * from deemon;
import util;
local ns = {
	("DW_TAG_",   []),
	("DW_AT_",    []),
	("DW_FORM_",  []),
	("DW_ATE_",   []),
	("DW_OP_",    []),
	("DW_CFA_",   []),
	("DW_EH_PE_", []),
};

for (local filename: [
	"../../include/libdebuginfo/dwarf.h",
	"../../include/libunwind/cfi.h",
]) {
	with (local fp = File.open(filename)) {
		for (local l: fp) {
			l = l.strip();
			local macroName, macroValue;
			try {
				macroName, macroValue = l.scanf(" # define %[^ ] %[^ ]")...;
				macroValue = int(macroValue);
			} catch (...) {
				continue;
			}
			for (local prefix, values: ns) {
				if (!macroName.startswith(prefix))
					continue;
				local name = macroName[#prefix:];
				if (name in ["lo_user", "hi_user"])
					continue;
				if (macroValue >= #values)
					values.resize(macroValue + 1);
				values[macroValue] = name;
				break;
			}
		}
	}
}

#define REPR_SPLIT_THRESHOLD 24

@@Split a given set of @values to prevent large holes within the data-set
function splitValues(values: {string...}): {(int, {string...})...} {
	local currentStart = 0;
	local numEmptySlots = 0;
	local count = #values;
	while (count && !values[count - 1])
		--count;
	for (local i = 0; i < count; ++i) {
		if (values[i]) {
			numEmptySlots = 0;
			continue;
		}
		++numEmptySlots;
		if (numEmptySlots >= REPR_SPLIT_THRESHOLD) {
			yield (currentStart, values[currentStart:i - (numEmptySlots - 1)]);
			do {
				++i;
			} while (i < count && !values[i]);
			currentStart = i;
			numEmptySlots = 0;
		}
	}
	yield (currentStart, values[currentStart:]);
}

for (local prefix, values: ns) {
	local splitSet = List(splitValues(values));
	print("#define GETBASE_", prefix.strip("_"), "(result, index) \\");
	for (local i, startAndItems: util.enumerate(splitSet)) {
		local stringName = "repr_{}_{}h"
			.format({ prefix.strip("_"), startAndItems[0].hex()[2:] });
		local minIndex = startAndItems[0];
		local maxIndex = minIndex + #startAndItems[1] - 1;
		print("\t", i ? " " : "("),;
		if (minIndex == maxIndex) {
			print("((index) == ", minIndex.hex(), ") ? ("),;
		} else if (minIndex == 0) {
			print("((index) <= ", maxIndex.hex(), ") ? ("),;
		} else {
			print("((index) >= ", minIndex.hex(), " && (index) <= ", maxIndex.hex(), ") ? ("),;
		}
		if (minIndex != 0) {
			if (minIndex == maxIndex) {
				print("(index) = 0, "),;
			} else {
				print("(index) -= ", minIndex.hex(), ", "),;
			}
		}
		print("(result) = ", stringName, ", true)"),;
		print(i == #splitSet - 1 ? " : false)" : " : \\");
	}
	for (local start, items: splitSet) {
		File.Writer text;
		for (local i, item: util.enumerate(items)) {
			if (!item)
				item = "";
			if (i != #items - 1)
				item = item + "\0";
			text << item;
		}
		print("PRIVATE REPR_RODATASECTION char const repr_",
			prefix.strip("_"), "_", start.hex()[2:], "h[] =\n",
			"\n".join(for (local e: text.string.segments(64)) repr(e)),
			";");
	}
	print;
}

]]]*/
#define GETBASE_DW_TAG(result, index) \
	(((index) <= 0x47) ? ((result) = repr_DW_TAG_0h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_0h[] =
"\0array_type\0class_type\0entry_point\0enumeration_type\0formal_param"
"eter\0\0\0imported_declaration\0\0label\0lexical_block\0\0member\0\0pointe"
"r_type\0reference_type\0compile_unit\0string_type\0structure_type\0\0s"
"ubroutine_type\0typedef\0union_type\0unspecified_parameters\0variant"
"\0common_block\0common_inclusion\0inheritance\0inlined_subroutine\0mo"
"dule\0ptr_to_member_type\0set_type\0subrange_type\0with_stmt\0access_"
"declaration\0base_type\0catch_block\0const_type\0constant\0enumerator"
"\0file_type\0friend\0namelist\0namelist_item\0packed_type\0subprogram\0"
"template_type_param\0template_value_param\0thrown_type\0try_block\0v"
"ariant_part\0variable\0volatile_type\0dwarf_procedure\0restrict_type"
"\0interface_type\0namespace\0imported_module\0unspecified_type\0parti"
"al_unit\0imported_unit\0\0condition\0shared_type\0type_unit\0rvalue_re"
"ference_type\0template_alias\0\0\0\0atomic_type";

#define GETBASE_DW_AT(result, index) \
	(((index) <= 0x6e) ? ((result) = repr_DW_AT_0h, true) : \
	 ((index) == 0x87) ? ((index) = 0, (result) = repr_DW_AT_87h, true) : \
	 ((index) >= 0x2001 && (index) <= 0x2011) ? ((index) -= 0x2001, (result) = repr_DW_AT_2001h, true) : \
	 ((index) >= 0x2101 && (index) <= 0x2135) ? ((index) -= 0x2101, (result) = repr_DW_AT_2101h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_AT_0h[] =
"\0sibling\0location\0name\0\0\0\0\0\0ordering\0\0byte_size\0bit_offset\0bit_s"
"ize\0\0\0stmt_list\0low_pc\0high_pc\0language\0\0discr\0discr_value\0visib"
"ility\0import\0string_length\0common_reference\0comp_dir\0const_value"
"\0containing_type\0default_value\0\0inline\0is_optional\0lower_bound\0\0"
"\0producer\0\0prototyped\0\0\0return_addr\0\0start_scope\0\0stride_size\0up"
"per_bound\0\0abstract_origin\0accessibility\0address_class\0artificia"
"l\0base_types\0calling_convention\0count\0data_member_location\0decl_"
"column\0decl_file\0decl_line\0declaration\0discr_list\0encoding\0exter"
"nal\0frame_base\0friend\0identifier_case\0macro_info\0namelist_item\0p"
"riority\0segment\0specification\0static_link\0type\0use_location\0vari"
"able_parameter\0virtuality\0vtable_elem_location\0allocated\0associa"
"ted\0data_location\0byte_stride\0entry_pc\0use_UTF8\0extension\0ranges"
"\0trampoline\0call_column\0call_file\0call_line\0description\0binary_s"
"cale\0decimal_scale\0small\0decimal_sign\0digit_count\0picture_string"
"\0mutable\0threads_scaled\0explicit\0object_pointer\0endianity\0elemen"
"tal\0pure\0recursive\0signature\0main_subprogram\0data_bit_offset\0con"
"st_expr\0enum_class\0linkage_name";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_87h[] =
"noreturn";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_2001h[] =
"MIPS_fde\0MIPS_loop_begin\0MIPS_tail_loop_begin\0MIPS_epilog_begin\0"
"MIPS_loop_unroll_factor\0MIPS_software_pipeline_depth\0MIPS_linkag"
"e_name\0MIPS_stride\0MIPS_abstract_name\0MIPS_clone_origin\0MIPS_has"
"_inlines\0MIPS_stride_byte\0MIPS_stride_elem\0MIPS_ptr_dopetype\0MIP"
"S_allocatable_dopetype\0MIPS_assumed_shape_dopetype\0MIPS_assumed_"
"size";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_2101h[] =
"sf_names\0src_info\0mac_info\0src_coords\0body_begin\0body_end\0GNU_ve"
"ctor\0GNU_guarded_by\0GNU_pt_guarded_by\0GNU_guarded\0GNU_pt_guarded"
"\0GNU_locks_excluded\0GNU_exclusive_locks_required\0GNU_shared_lock"
"s_required\0GNU_odr_signature\0GNU_template_name\0GNU_call_site_val"
"ue\0GNU_call_site_data_value\0GNU_call_site_target\0GNU_call_site_t"
"arget_clobbered\0GNU_tail_call\0GNU_all_tail_call_sites\0GNU_all_ca"
"ll_sites\0GNU_all_source_call_sites\0GNU_macros\0GNU_deleted\0\0\0\0\0\0\0"
"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0GNU_dwo_name\0GNU_dwo_id\0GNU_ranges_base\0GNU_addr_"
"base\0GNU_pubnames\0GNU_pubtypes";

#define GETBASE_DW_FORM(result, index) \
	(((index) <= 0x20) ? ((result) = repr_DW_FORM_0h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_FORM_0h[] =
"\0addr\0\0block2\0block4\0data2\0data4\0data8\0string\0block\0block1\0data1"
"\0flag\0sdata\0strp\0udata\0ref_addr\0ref1\0ref2\0ref4\0ref8\0ref_udata\0in"
"direct\0sec_offset\0exprloc\0flag_present\0\0\0\0\0\0\0ref_sig8";

#define GETBASE_DW_ATE(result, index) \
	(((index) <= 0x10) ? ((result) = repr_DW_ATE_0h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_ATE_0h[] =
"\0address\0boolean\0complex_float\0float\0signed\0signed_char\0unsigned"
"\0unsigned_char\0imaginary_float\0packed_decimal\0numeric_string\0edi"
"ted\0signed_fixed\0unsigned_fixed\0decimal_float\0UTF";

#define GETBASE_DW_OP(result, index) \
	(((index) <= 0x9f) ? ((result) = repr_DW_OP_0h, true) : \
	 ((index) >= 0xe0 && (index) <= 0xf0) ? ((index) -= 0xe0, (result) = repr_DW_OP_e0h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_OP_0h[] =
"\0\0\0addr\0\0\0deref\0\0const1u\0const1s\0const2u\0const2s\0const4u\0const4s"
"\0const8u\0const8s\0constu\0consts\0dup\0drop\0over\0pick\0swap\0rot\0xdere"
"f\0abs\0and\0div\0minus\0mod\0mul\0neg\0not\0or\0plus\0plus_uconst\0shl\0shr\0"
"shra\0xor\0bra\0eq\0ge\0gt\0le\0lt\0ne\0skip\0lit0\0lit1\0lit2\0lit3\0lit4\0lit"
"5\0lit6\0lit7\0lit8\0lit9\0lit10\0lit11\0lit12\0lit13\0lit14\0lit15\0lit16\0"
"lit17\0lit18\0lit19\0lit20\0lit21\0lit22\0lit23\0lit24\0lit25\0lit26\0lit2"
"7\0lit28\0lit29\0lit30\0lit31\0reg0\0reg1\0reg2\0reg3\0reg4\0reg5\0reg6\0reg"
"7\0reg8\0reg9\0reg10\0reg11\0reg12\0reg13\0reg14\0reg15\0reg16\0reg17\0reg1"
"8\0reg19\0reg20\0reg21\0reg22\0reg23\0reg24\0reg25\0reg26\0reg27\0reg28\0re"
"g29\0reg30\0reg31\0breg0\0breg1\0breg2\0breg3\0breg4\0breg5\0breg6\0breg7\0"
"breg8\0breg9\0breg10\0breg11\0breg12\0breg13\0breg14\0breg15\0breg16\0bre"
"g17\0breg18\0breg19\0breg20\0breg21\0breg22\0breg23\0breg24\0breg25\0breg"
"26\0breg27\0breg28\0breg29\0breg30\0breg31\0regx\0fbreg\0bregx\0piece\0der"
"ef_size\0xderef_size\0nop\0push_object_address\0call2\0call4\0call_ref"
"\0form_tls_address\0call_frame_cfa\0bit_piece\0implicit_value\0stack_"
"value";
PRIVATE REPR_RODATASECTION char const repr_DW_OP_e0h[] =
"GNU_push_tls_address\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0GNU_uninit";

#define GETBASE_DW_CFA(result, index) \
	(((index) <= 0x40) ? ((result) = repr_DW_CFA_0h, true) : \
	 ((index) == 0x80) ? ((index) = 0, (result) = repr_DW_CFA_80h, true) : \
	 ((index) == 0xc0) ? ((index) = 0, (result) = repr_DW_CFA_c0h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_CFA_0h[] =
"nop\0set_loc\0advance_loc1\0advance_loc2\0advance_loc4\0offset_extend"
"ed\0restore_extended\0undefined\0same_value\0register\0remember_state"
"\0restore_state\0def_cfa\0def_cfa_register\0def_cfa_offset\0def_cfa_e"
"xpression\0expression\0offset_extended_sf\0def_cfa_sf\0def_cfa_offse"
"t_sf\0val_offset\0val_offset_sf\0val_expression\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
"\0\0\0\0GNU_args_size\0GNU_negative_offset_extended\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0a"
"dvance_loc";
PRIVATE REPR_RODATASECTION char const repr_DW_CFA_80h[] =
"offset";
PRIVATE REPR_RODATASECTION char const repr_DW_CFA_c0h[] =
"restore";

#define GETBASE_DW_EH_PE(result, index) \
	(((index) <= 0x50) ? ((result) = repr_DW_EH_PE_0h, true) : \
	 ((index) == 0x80) ? ((index) = 0, (result) = repr_DW_EH_PE_80h, true) : \
	 ((index) == 0xff) ? ((index) = 0, (result) = repr_DW_EH_PE_ffh, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_EH_PE_0h[] =
"absptr\0uleb128\0udata2\0udata4\0udata8\0\0\0\0signed\0sleb128\0sdata2\0sda"
"ta4\0sdata8\0\0\0\0pcrel\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0textrel\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0datare"
"l\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0funcrel\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0aligned";
PRIVATE REPR_RODATASECTION char const repr_DW_EH_PE_80h[] =
"indirect";
PRIVATE REPR_RODATASECTION char const repr_DW_EH_PE_ffh[] =
"omit";
/*[[[end]]]*/

PRIVATE REPR_TEXTSECTION ATTR_PURE WUNUSED NONNULL((1)) char const *
NOTHROW(CC get_string_by_index)(char const *__restrict base, dwarf_uleb128_t index) {
	for (; index; --index)
		base = strend(base) + 1;
	if (!*base)
		base = NULL;
	return base;
}

/* Return the name of a given constant, or NULL if the constant isn't recognized.
 *  - debug_repr_DW_TAG():   Returns the `*' portion for one of `DW_TAG_*' (iow. excluding the `DW_TAG_' prefix)
 *  - debug_repr_DW_AT():    Returns the `*' portion for one of `DW_AT_*' (iow. excluding the `DW_AT_' prefix)
 *  - debug_repr_DW_FORM():  Returns the `*' portion for one of `DW_FORM_*' (iow. excluding the `DW_FORM_' prefix)
 *  - debug_repr_DW_ATE():   Returns the `*' portion for one of `DW_ATE_*' (iow. excluding the `DW_ATE_' prefix)
 *  - debug_repr_DW_OP():    Returns the `*' portion for one of `DW_OP_*' (iow. excluding the `DW_OP_' prefix)
 *  - debug_repr_DW_CFA():   Returns the `*' portion for one of `DW_CFA_*' (iow. excluding the `DW_CFA_' prefix)
 *  - debug_repr_DW_EH_PE(): Returns the `*' portion for one of `DW_EH_PE_*' (iow. excluding the `DW_EH_PE_' prefix)
 */
INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_TAG)(dwarf_uleb128_t value) {
	char const *result = NULL;
	if (GETBASE_DW_TAG(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_AT)(dwarf_uleb128_t value) {
	char const *result = NULL;
	if (GETBASE_DW_AT(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_FORM)(dwarf_uleb128_t value) {
	char const *result = NULL;
	if (GETBASE_DW_FORM(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_ATE)(dwarf_uleb128_t value) {
	char const *result = NULL;
	if (GETBASE_DW_ATE(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_OP)(uint8_t value) {
	char const *result = NULL;
	if (GETBASE_DW_OP(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_CFA)(uint8_t value) {
	char const *result = NULL;
	if (GETBASE_DW_CFA(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_EH_PE)(uint8_t value) {
	char const *result = NULL;
	if (GETBASE_DW_EH_PE(result, value))
		result = get_string_by_index(result, value);
	return result;
}

INTDEF char const unknown_string[];

/* Dump the given debug information in a human-readable format to `printer'
 * >>  {
 * >>   void *m = dlopen(LIBDEBUGINFO_LIBRARY_NAME,RTLD_LOCAL);
 * >> #define LOAD(T,x) T x; *(void **)&x = dlsym(m,#x); assertf(x,"Error: %s",dlerror());
 * >>   LOAD(PDEBUG_REPR_DUMP,debug_repr_dump)
 * >>   struct dl_section *debug_info   = dllocksection(dlgetmodule("c"), ".debug_info");
 * >>   struct dl_section *debug_abbrev = dllocksection(dlgetmodule("c"), ".debug_abbrev");
 * >>   struct dl_section *debug_str    = dllocksection(dlgetmodule("c"), ".debug_str");
 * >>   struct dl_section *debug_loc    = dllocksection(dlgetmodule("c"), ".debug_loc");
 * >>   debug_repr_dump(&file_printer, stdout,
 * >>                   (byte_t *)(debug_info ? debug_info->ds_data : NULL),
 * >>                   (byte_t *)(debug_info ? debug_info->ds_data + debug_info->ds_size : 0),
 * >>                   (byte_t *)(debug_abbrev ? debug_abbrev->ds_data : NULL),
 * >>                   (byte_t *)(debug_abbrev ? debug_abbrev->ds_data + debug_abbrev->ds_size : 0),
 * >>                   (byte_t *)(debug_str ? debug_str->ds_data : NULL),
 * >>                   (byte_t *)(debug_str ? debug_str->ds_data + debug_str->ds_size : 0),
 * >>                   (byte_t *)(debug_loc ? debug_loc->ds_data : NULL),
 * >>                   (byte_t *)(debug_loc ? debug_loc->ds_data + debug_loc->ds_size : 0));
 * >>  }
*/
INTERN REPR_TEXTSECTION NONNULL((1)) ssize_t CC
libdi_debug_repr_dump(pformatprinter printer, void *arg,
                      byte_t *debug_info_start, byte_t *debug_info_end,
                      byte_t *debug_abbrev_start, byte_t *debug_abbrev_end,
                      byte_t *debug_loc_start, byte_t *debug_loc_end,
                      byte_t *debug_str_start, byte_t *debug_str_end) {
	ssize_t temp, result = 0;
	char const *s;
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	di_debuginfo_cu_parser_sections_t cu_sections;
	cu_sections.cps_debug_abbrev_start = debug_abbrev_start;
	cu_sections.cps_debug_abbrev_end   = debug_abbrev_end;
	cu_sections.cps_debug_loc_start    = debug_loc_start;
	cu_sections.cps_debug_loc_end      = debug_loc_end;
	cu_sections.cps_debug_str_start    = debug_str_start;
	cu_sections.cps_debug_str_end      = debug_str_end;
#define DO(expr)                         \
	do {                                 \
		if unlikely((temp = (expr)) < 0) \
			goto err;                    \
		result += temp;                  \
	} __WHILE0
#define PRINT(s) DO((*printer)(arg, REPR_STRING(s), COMPILER_STRLEN(s)))
	while (libdi_debuginfo_cu_parser_loadunit(&debug_info_start, debug_info_end,
	                                          &cu_sections, &parser,
	                                          &abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
		do {
			DO(format_repeat(printer, arg, '\t', parser.dup_child_depth));
			DO(format_printf(printer, arg, REPR_STRING("%#p:"), parser.dup_cu_info_pos));
			s = libdi_debug_repr_DW_TAG(parser.dup_comp.dic_tag);
			DO(s ? format_printf(printer, arg, REPR_STRING("DW_TAG_%s:\n"), s)
			     : format_printf(printer, arg, REPR_STRING("%#Ix:\n"), parser.dup_comp.dic_tag));
			di_debuginfo_component_attrib_t attr;
			DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
				DO(format_repeat(printer, arg, '\t', parser.dup_child_depth + 1));
				PRINT("[");
				s = libdi_debug_repr_DW_AT(attr.dica_name);
				DO(s ? format_printf(printer, arg, REPR_STRING("DW_AT_%s:"), s)
				     : format_printf(printer, arg, REPR_STRING("%#Ix:"), attr.dica_name));
				s = libdi_debug_repr_DW_FORM(attr.dica_form);
				DO(s ? format_printf(printer, arg, REPR_STRING("DW_FORM_%s"), s)
				     : format_printf(printer, arg, REPR_STRING("%#Ix"), attr.dica_form));
				PRINT("] = ");
				switch (attr.dica_form) {

				case DW_FORM_strp:
				case DW_FORM_string: {
					char *value;
					if (!libdi_debuginfo_cu_parser_getstring(&parser, attr.dica_form, &value))
						goto err_bad_value;
					DO(format_printf(printer, arg, REPR_STRING("%q"), value));
				}	break;

				case DW_FORM_addr: {
					uintptr_t value;
					if (!libdi_debuginfo_cu_parser_getaddr(&parser, attr.dica_form, &value))
						goto err_bad_value;
					DO(format_printf(printer, arg, REPR_STRING("%#p"), value));
				}	break;

				case DW_FORM_data1:
				case DW_FORM_data2:
				case DW_FORM_data4:
				case DW_FORM_data8:
				case DW_FORM_sdata:
				case DW_FORM_udata:
				case DW_FORM_sec_offset: {
					uintptr_t value;
					if (!libdi_debuginfo_cu_parser_getconst(&parser, attr.dica_form, &value))
						goto err_bad_value;
					DO(format_printf(printer, arg, REPR_STRING("%Iu (%#Ix)"), value, value));
				}	break;

				case DW_FORM_flag:
				case DW_FORM_flag_present: {
					bool value;
					if (!libdi_debuginfo_cu_parser_getflag(&parser, attr.dica_form, &value))
						goto err_bad_value;
					DO(value ? (*printer)(arg, REPR_STRING("true"), 4)
					         : (*printer)(arg, REPR_STRING("false"), 5));
				}	break;

				case DW_FORM_ref_addr:
				case DW_FORM_ref1:
				case DW_FORM_ref2:
				case DW_FORM_ref4:
				case DW_FORM_ref8:
				case DW_FORM_ref_sig8:
				case DW_FORM_ref_udata: {
					byte_t *value;
					di_debuginfo_cu_parser_t p2;
					if (!libdi_debuginfo_cu_parser_getref(&parser, attr.dica_form, &value))
						goto err_bad_value;
					p2                 = parser;
					p2.dup_cu_info_pos = value;
					if unlikely(!libdi_debuginfo_cu_parser_next(&p2)) {
						PRINT("<BAD REFERENCE>");
					} else {
						DO(format_printf(printer, arg, REPR_STRING("%#p:"), p2.dup_cu_info_pos));
						s = libdi_debug_repr_DW_TAG(p2.dup_comp.dic_tag);
						DO(s ? format_printf(printer, arg, REPR_STRING("DW_TAG_%s"), s)
						     : format_printf(printer, arg, REPR_STRING("%#Ix"), p2.dup_comp.dic_tag));
					}
				}	break;

				case DW_FORM_exprloc: {
					di_debuginfo_location_t value;
					if (!libdi_debuginfo_cu_parser_getexpr(&parser, attr.dica_form, &value))
						goto err_bad_value;
					/* TODO: Disassemble the expression */
					PRINT("<EXPR>");
				}	break;

				default:
err_bad_value:
					DO((*printer)(arg, unknown_string, 3));
					break;
				}
				PRINT("\n");
			}
		} while (libdi_debuginfo_cu_parser_next(&parser));
		libdi_debuginfo_cu_abbrev_fini(&abbrev);
	}
#undef PRINT
#undef DO
	return result;
err:
	libdi_debuginfo_cu_abbrev_fini(&abbrev);
	return temp;
}


DEFINE_PUBLIC_ALIAS(debug_repr_DW_TAG, libdi_debug_repr_DW_TAG);
DEFINE_PUBLIC_ALIAS(debug_repr_DW_AT, libdi_debug_repr_DW_AT);
DEFINE_PUBLIC_ALIAS(debug_repr_DW_FORM, libdi_debug_repr_DW_FORM);
DEFINE_PUBLIC_ALIAS(debug_repr_DW_ATE, libdi_debug_repr_DW_ATE);
DEFINE_PUBLIC_ALIAS(debug_repr_DW_OP, libdi_debug_repr_DW_OP);
DEFINE_PUBLIC_ALIAS(debug_repr_DW_CFA, libdi_debug_repr_DW_CFA);
DEFINE_PUBLIC_ALIAS(debug_repr_DW_EH_PE, libdi_debug_repr_DW_EH_PE);
DEFINE_PUBLIC_ALIAS(debug_repr_dump, libdi_debug_repr_dump);


#undef CASE
#endif /* __KERNEL__ */


DECL_END

#endif /* !GUARD_LIBDEBUGINFO_REPR_C */
