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
#ifndef GUARD_LIBDEBUGINFO_REPR_C
#define GUARD_LIBDEBUGINFO_REPR_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */

#include "api.h"

#ifndef __KERNEL__
#include <hybrid/compiler.h>

#include <hybrid/unaligned.h>

#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h> /* strend() */

#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/repr.h>
#include <libunwind/cfi.h>

#include "debug_info.h"

/**/
#include "repr.h"

DECL_BEGIN

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
 * deemon    script   that   looks   at   the   associated   headers.
 */


/*[[[deemon
import * from deemon;
import * from ...misc.libgen.strendN;
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

for (local macroName, macroValue: enumerateMacrosFromFiles({
	"../../include/libdebuginfo/dwarf.h",
	"../../include/libunwind/dwarf.h",
	"../../include/libunwind/cfi.h",
})) {
	macroValue = getMacroIntValue(macroValue);
	if (macroValue !is int)
		continue;
	if (macroName.startswith("DW_CFA_register_rule_"))
		continue;
	for (local prefix, values: ns) {
		if (!macroName.startswith(prefix))
			continue;
		local name = macroName[#prefix:];
		if (name in ["lo_user", "hi_user", "OFFMASK", "BASEMASK"])
			continue;
		if (macroValue >= #values)
			values.resize(macroValue + 1);
		values[macroValue] = name;
		break;
	}
}

for (local prefix, values: ns)
	printStrendNDatabase(prefix, values, attr: "REPR_RODATASECTION");
]]]*/
#define GETBASE_DW_TAG(result, index) \
	(((index) <= 0x4b) ? ((result) = repr_DW_TAG_0h, true) : \
	 ((index) >= 0x4081 && (index) <= 0x4092) ? ((index) -= 0x4081, (result) = repr_DW_TAG_4081h, true) : \
	 ((index) >= 0x4101 && (index) <= 0x410a) ? ((index) -= 0x4101, (result) = repr_DW_TAG_4101h, true) : \
	 ((index) >= 0x8765 && (index) <= 0x8767) ? ((index) -= 0x8765, (result) = repr_DW_TAG_8765h, true) : \
	 ((index) == 0xa000) ? ((index) = 0, (result) = repr_DW_TAG_a000h, true) : \
	 ((index) == 0xa020) ? ((index) = 0, (result) = repr_DW_TAG_a020h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_0h[] =
"padding\0array_type\0class_type\0entry_point\0enumeration_type\0forma"
"l_parameter\0\0\0imported_declaration\0\0label\0lexical_block\0\0member\0"
"\0pointer_type\0reference_type\0compile_unit\0string_type\0structure_"
"type\0\0subroutine_type\0typedef\0union_type\0unspecified_parameters\0"
"variant\0common_block\0common_inclusion\0inheritance\0inlined_subrou"
"tine\0module\0ptr_to_member_type\0set_type\0subrange_type\0with_stmt\0"
"access_declaration\0base_type\0catch_block\0const_type\0constant\0enu"
"merator\0file_type\0friend\0namelist\0namelist_item\0packed_type\0subp"
"rogram\0template_type_param\0template_value_param\0thrown_type\0try_"
"block\0variant_part\0variable\0volatile_type\0dwarf_procedure\0restri"
"ct_type\0interface_type\0namespace\0imported_module\0unspecified_typ"
"e\0partial_unit\0imported_unit\0\0condition\0shared_type\0type_unit\0rv"
"alue_reference_type\0template_alias\0coarray_type\0generic_subrange"
"\0dynamic_type\0atomic_type\0call_site\0call_site_parameter\0skeleton"
"_unit\0immutable_type";
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_4081h[] =
"MIPS_loop\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0HP_array_descriptor\0HP_Bliss_field\0HP_Bl"
"iss_field_set";
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_4101h[] =
"format_label\0function_template\0class_template\0GNU_BINCL\0GNU_EINC"
"L\0GNU_template_template_param\0GNU_template_parameter_pack\0GNU_fo"
"rmal_parameter_pack\0GNU_call_site\0GNU_call_site_parameter";
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_8765h[] =
"upc_shared_type\0upc_strict_type\0upc_relaxed_type";
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_a000h[] =
"PGI_kanji_type";
PRIVATE REPR_RODATASECTION char const repr_DW_TAG_a020h[] =
"PGI_interface_block";

#define GETBASE_DW_AT(result, index) \
	(((index) <= 0x8c) ? ((result) = repr_DW_AT_0h, true) : \
	 ((index) >= 0x2000 && (index) <= 0x2029) ? ((index) -= 0x2000, (result) = repr_DW_AT_2000h, true) : \
	 ((index) >= 0x2101 && (index) <= 0x2138) ? ((index) -= 0x2101, (result) = repr_DW_AT_2101h, true) : \
	 ((index) == 0x2201) ? ((index) = 0, (result) = repr_DW_AT_2201h, true) : \
	 ((index) >= 0x2301 && (index) <= 0x2305) ? ((index) -= 0x2301, (result) = repr_DW_AT_2301h, true) : \
	 ((index) == 0x3210) ? ((index) = 0, (result) = repr_DW_AT_3210h, true) : \
	 ((index) >= 0x3a00 && (index) <= 0x3a02) ? ((index) -= 0x3a00, (result) = repr_DW_AT_3a00h, true) : \
	 ((index) >= 0x3fe1 && (index) <= 0x3fed) ? ((index) -= 0x3fe1, (result) = repr_DW_AT_3fe1h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_AT_0h[] =
"\0sibling\0location\0name\0\0\0\0\0\0ordering\0subscr_data\0byte_size\0bit_o"
"ffset\0bit_size\0\0element_list\0stmt_list\0low_pc\0high_pc\0language\0m"
"ember\0discr\0discr_value\0visibility\0import\0string_length\0common_r"
"eference\0comp_dir\0const_value\0containing_type\0default_value\0\0inl"
"ine\0is_optional\0lower_bound\0\0\0producer\0\0prototyped\0\0\0return_addr"
"\0\0start_scope\0\0stride_size\0upper_bound\0\0abstract_origin\0accessib"
"ility\0address_class\0artificial\0base_types\0calling_convention\0cou"
"nt\0data_member_location\0decl_column\0decl_file\0decl_line\0declarat"
"ion\0discr_list\0encoding\0external\0frame_base\0friend\0identifier_ca"
"se\0macro_info\0namelist_items\0priority\0segment\0specification\0stat"
"ic_link\0type\0use_location\0variable_parameter\0virtuality\0vtable_e"
"lem_location\0allocated\0associated\0data_location\0byte_stride\0entr"
"y_pc\0use_UTF8\0extension\0ranges\0trampoline\0call_column\0call_file\0"
"call_line\0description\0binary_scale\0decimal_scale\0small\0decimal_s"
"ign\0digit_count\0picture_string\0mutable\0threads_scaled\0explicit\0o"
"bject_pointer\0endianity\0elemental\0pure\0recursive\0signature\0main_"
"subprogram\0data_bit_offset\0const_expr\0enum_class\0linkage_name\0st"
"ring_length_bit_size\0string_length_byte_size\0rank\0str_offsets_ba"
"se\0addr_base\0rnglists_base\0\0dwo_name\0reference\0rvalue_reference\0"
"macros\0call_all_calls\0call_all_source_calls\0call_all_tail_calls\0"
"call_return_pc\0call_value\0call_origin\0call_parameter\0call_pc\0cal"
"l_tail_call\0call_target\0call_target_clobbered\0call_data_location"
"\0call_data_value\0noreturn\0alignment\0export_symbols\0deleted\0defau"
"lted\0loclists_base";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_2000h[] =
"HP_block_index\0MIPS_fde\0MIPS_loop_begin\0MIPS_tail_loop_begin\0MIP"
"S_epilog_begin\0MIPS_loop_unroll_factor\0MIPS_software_pipeline_de"
"pth\0MIPS_linkage_name\0HP_epilogue\0MIPS_abstract_name\0MIPS_clone_"
"origin\0MIPS_has_inlines\0MIPS_stride_byte\0MIPS_stride_elem\0MIPS_p"
"tr_dopetype\0MIPS_allocatable_dopetype\0HP_actuals_stmt_list\0MIPS_"
"assumed_size\0HP_raw_data_ptr\0HP_pass_by_reference\0HP_opt_level\0H"
"P_prof_version_id\0HP_opt_flags\0HP_cold_region_low_pc\0HP_cold_reg"
"ion_high_pc\0HP_all_variables_modifiable\0HP_linkage_name\0HP_prof_"
"flags\0\0\0\0HP_unit_name\0HP_unit_size\0HP_widened_byte_size\0HP_defin"
"ition_points\0HP_default_location\0\0\0\0\0\0HP_is_result_param";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_2101h[] =
"sf_names\0src_info\0mac_info\0src_coords\0body_begin\0body_end\0GNU_ve"
"ctor\0GNU_guarded_by\0GNU_pt_guarded_by\0GNU_guarded\0GNU_pt_guarded"
"\0GNU_locks_excluded\0GNU_exclusive_locks_required\0GNU_shared_lock"
"s_required\0GNU_odr_signature\0GNU_template_name\0GNU_call_site_val"
"ue\0GNU_call_site_data_value\0GNU_call_site_target\0GNU_call_site_t"
"arget_clobbered\0GNU_tail_call\0GNU_all_tail_call_sites\0GNU_all_ca"
"ll_sites\0GNU_all_source_call_sites\0GNU_macros\0GNU_deleted\0\0\0\0\0\0\0"
"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0GNU_dwo_name\0GNU_dwo_id\0GNU_ranges_base\0GNU_addr_"
"base\0GNU_pubnames\0GNU_pubtypes\0GNU_discriminator\0GNU_locviews\0GN"
"U_entry_view";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_2201h[] =
"VMS_rtnbeg_pd_address";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_2301h[] =
"use_GNAT_descriptive_type\0GNAT_descriptive_type\0GNU_numerator\0GN"
"U_denominator\0GNU_bias";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_3210h[] =
"upc_threads_scaled";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_3a00h[] =
"PGI_lbase\0PGI_soffset\0PGI_lstride";
PRIVATE REPR_RODATASECTION char const repr_DW_AT_3fe1h[] =
"APPLE_optimized\0APPLE_flags\0APPLE_isa\0APPLE_block\0APPLE_major_ru"
"ntime_vers\0APPLE_runtime_class\0APPLE_omit_frame_ptr\0APPLE_proper"
"ty_name\0APPLE_property_getter\0APPLE_property_setter\0APPLE_proper"
"ty_attribute\0APPLE_objc_complete_type\0APPLE_property";

#define GETBASE_DW_FORM(result, index) \
	(((index) <= 0x2c) ? ((result) = repr_DW_FORM_0h, true) : \
	 ((index) >= 0x1f01 && (index) <= 0x1f02) ? ((index) -= 0x1f01, (result) = repr_DW_FORM_1f01h, true) : \
	 ((index) >= 0x1f20 && (index) <= 0x1f21) ? ((index) -= 0x1f20, (result) = repr_DW_FORM_1f20h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_FORM_0h[] =
"\0addr\0\0block2\0block4\0data2\0data4\0data8\0string\0block\0block1\0data1"
"\0flag\0sdata\0strp\0udata\0ref_addr\0ref1\0ref2\0ref4\0ref8\0ref_udata\0in"
"direct\0sec_offset\0exprloc\0flag_present\0strx\0addrx\0ref_sup4\0strp_"
"sup\0data16\0line_strp\0ref_sig8\0implicit_const\0loclistx\0rnglistx\0r"
"ef_sup8\0strx1\0strx2\0strx3\0strx4\0addrx1\0addrx2\0addrx3\0addrx4";
PRIVATE REPR_RODATASECTION char const repr_DW_FORM_1f01h[] =
"GNU_addr_index\0GNU_str_index";
PRIVATE REPR_RODATASECTION char const repr_DW_FORM_1f20h[] =
"GNU_ref_alt\0GNU_strp_alt";

#define GETBASE_DW_ATE(result, index) \
	(((index) <= 0x12) ? ((result) = repr_DW_ATE_0h, true) : \
	 ((index) >= 0x80 && (index) <= 0x90) ? ((index) -= 0x80, (result) = repr_DW_ATE_80h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_ATE_0h[] =
"void\0address\0boolean\0complex_float\0float\0signed\0signed_char\0unsi"
"gned\0unsigned_char\0imaginary_float\0packed_decimal\0numeric_string"
"\0edited\0signed_fixed\0unsigned_fixed\0decimal_float\0UTF\0UCS\0ASCII";
PRIVATE REPR_RODATASECTION char const repr_DW_ATE_80h[] =
"HP_float80\0HP_complex_float80\0HP_float128\0HP_complex_float128\0HP"
"_floathpintel\0HP_imaginary_float80\0HP_imaginary_float128\0\0HP_VAX"
"_float\0HP_VAX_float_d\0HP_packed_decimal\0HP_zoned_decimal\0HP_edit"
"ed\0HP_signed_fixed\0HP_unsigned_fixed\0HP_VAX_complex_float\0HP_VAX"
"_complex_float_d";

#define GETBASE_DW_OP(result, index) \
	(((index) <= 0xa9) ? ((result) = repr_DW_OP_0h, true) : \
	 ((index) >= 0xe0 && (index) <= 0xfd) ? ((index) -= 0xe0, (result) = repr_DW_OP_e0h, true) : false)
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
"value\0implicit_pointer\0addrx\0constx\0entry_value\0const_type\0regva"
"l_type\0deref_type\0xderef_type\0convert\0reinterpret";
PRIVATE REPR_RODATASECTION char const repr_DW_OP_e0h[] =
"HP_unknown\0HP_is_value\0HP_fltconst4\0HP_fltconst8\0HP_mod_range\0HP"
"_unmod_range\0HP_tls\0\0\0\0AARCH64_operation\0\0\0\0\0\0GNU_uninit\0GNU_enc"
"oded_addr\0GNU_implicit_pointer\0GNU_entry_value\0GNU_const_type\0GN"
"U_regval_type\0GNU_deref_type\0GNU_convert\0PGI_omp_thread_num\0GNU_"
"reinterpret\0GNU_parameter_ref\0GNU_addr_index\0GNU_const_index\0GNU"
"_variable_value";

#define GETBASE_DW_CFA(result, index) \
	(((index) <= 0x40) ? ((result) = repr_DW_CFA_0h, true) : \
	 ((index) == 0x80) ? ((index) = 0, (result) = repr_DW_CFA_80h, true) : \
	 ((index) == 0xc0) ? ((index) = 0, (result) = repr_DW_CFA_c0h, true) : false)
PRIVATE REPR_RODATASECTION char const repr_DW_CFA_0h[] =
"nop\0set_loc\0advance_loc1\0advance_loc2\0advance_loc4\0offset_extend"
"ed\0restore_extended\0undefined\0same_value\0register\0remember_state"
"\0restore_state\0def_cfa\0def_cfa_register\0def_cfa_offset\0def_cfa_e"
"xpression\0expression\0offset_extended_sf\0def_cfa_sf\0def_cfa_offse"
"t_sf\0val_offset\0val_offset_sf\0val_expression\0\0\0\0\0\0\0MIPS_advance_"
"loc8\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0AARCH64_negate_ra_state\0GNU_args_size\0GNU_ne"
"gative_offset_extended\0\0\0\0\0\0\0\0\0KOS_startcapsule\0KOS_endcapsule\0\0"
"\0\0\0\0\0advance_loc";
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
 *  - debug_repr_DW_EH_PE(): Returns the `*' portion for one of `DW_EH_PE_*' (iow. excluding the `DW_EH_PE_' prefix) */
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



/************************************************************************/
#define DO(expr)                         \
	do {                                 \
		if unlikely((temp = (expr)) < 0) \
			goto err;                    \
		result += temp;                  \
	}	__WHILE0
#define PRINT(s)            DO((*printer)(arg, REPR_STRING(s), COMPILER_STRLEN(s)))
#define PRINTF(format, ...) DO(format_printf(printer, arg, REPR_STRING(format), ##__VA_ARGS__))

INTDEF char const unknown_string[];

struct label_entry {
	byte_t const *le_dest; /* [1..1] Label destination address. */
};
struct label_buffer {
	size_t                                      lb_alloc;    /* Allocated size. */
	size_t                                      lb_count;    /* Used size. */
	COMPILER_FLEXIBLE_ARRAY(struct label_entry, lb_entries); /* [lb_count] Label entries. (sorted ascendingly) */
};

/* Return the entry associated with `addr' (if any) or NULLO */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1, 2)) struct label_entry const *
NOTHROW(CC label_buffer_locate)(struct label_buffer const *__restrict self,
                                byte_t const *__restrict addr) {
	size_t lo, hi;
	lo = 0;
	hi = self->lb_count;
	while (lo < hi) {
		size_t index;
		index = (lo + hi) / 2;
		if (addr < self->lb_entries[index].le_dest) {
			hi = index;
		} else if (addr > self->lb_entries[index].le_dest) {
			lo = index + 1;
		} else {
			/* Address is already being tracked. */
			return &self->lb_entries[index];
		}
	}
	return NULL;
}

/* Insert (if  sufficient space  is available)  the given  address
 * into the label buffer (at  the proper location). When no  space
 * is available, still increment the count variable but do nothing
 * else. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(CC label_buffer_insert)(struct label_buffer *__restrict self,
                                byte_t const *__restrict addr) {
	size_t lo, hi;
	if unlikely(self->lb_count >= self->lb_alloc)
		goto done;
	/* Find the appropriate location where `addr' should be inserted. */
	lo = 0;
	hi = self->lb_count;
	while (lo < hi) {
		size_t index;
		index = (lo + hi) / 2;
		if (addr < self->lb_entries[index].le_dest) {
			hi = index;
		} else if (addr > self->lb_entries[index].le_dest) {
			lo = index + 1;
		} else {
			/* Address is already being tracked. */
			return;
		}
	}
	/* Insert at `index = lo = hi' */
	assert(lo == hi);
	memmoveup(&self->lb_entries[lo + 1],
	          &self->lb_entries[lo],
	          (self->lb_count + 1) - lo,
	          sizeof(struct label_entry));
	self->lb_entries[lo].le_dest = addr;
done:
	++self->lb_count;
}


/* Same as `unwind_instruction_succ()', but never returns
 * NULL. Also guarantied to always  `return > unwind_pc'. */
PRIVATE ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t const *CC
unwind_instruction_succ_failsafe(byte_t const *__restrict unwind_pc,
                                 byte_t addrsize, byte_t ptrsize) {
	byte_t const *result;
	result = unwind_instruction_succ(unwind_pc, addrsize, ptrsize);
	if unlikely(result == NULL)
		result = unwind_pc + 1;
	assert(result > unwind_pc);
	return result;
}


/* Read the expression length as ULEB128 from `*expr' and print
 * the  disassembled contents of the succeeding CFI expression.
 * Same as `debug_repr_cfi_expression_with_length()'
 * @param: printer:  Output printer.
 * @param: arg:      Output printer cookie.
 * @param: pc:       Starting address of the expression.
 * @param: addrsize: s.a. `unwind_instruction_succ(3)'
 * @param: ptrsize:  s.a. `unwind_instruction_succ(3)'
 * @return: * : The usual pformatprinter-style value. */
INTDEF NONNULL((1, 3)) ssize_t CC
libdl_debug_repr_cfi_expression(pformatprinter printer, void *arg,
                                byte_t const *__restrict expr, size_t indent,
                                byte_t addrsize, byte_t ptrsize);


PRIVATE REPR_TEXTSECTION NONNULL((1, 3, 6)) ssize_t CC
print_cfi_instruction(pformatprinter printer, void *arg,
                      byte_t const *__restrict reader,
                      byte_t addrsize, byte_t ptrsize,
                      struct label_buffer const *__restrict labels,
                      size_t indent) {
	ssize_t result, temp;
	byte_t opcode = *reader;
	char const *name;
	/* Try to decode the name of the instruction. */
	name = libdi_debug_repr_DW_OP(opcode);
	if likely(name) {
		result = (*printer)(arg, REPR_STRING("DW_OP_"), 6);
		if unlikely(result < 0)
			goto done;
		DO((*printer)(arg, name, strlen(name)));
		/* Print operands. */
		++reader;
		switch (opcode) {

		case DW_OP_bra:
		case DW_OP_skip: {
			int16_t offset;
			struct label_entry const *label;
			offset = (int16_t)UNALIGNED_GET16(reader);
			reader += 2;
			reader += offset;
			label = label_buffer_locate(labels, reader);
			if likely(label) {
				PRINTF("\tL%" PRIuSIZ, (size_t)(label - labels->lb_entries));
			} else {
				PRINTF("\t.%+" PRIdSIZ, (ssize_t)(offset - 3));
			}
		}	break;

		case DW_OP_addr: {
			uintmax_t addend;
			if (addrsize >= sizeof(uintmax_t)) {
#if __SIZEOF_INTMAX_T__ == 8
		case DW_OP_const8u:
#define HAVE_CASE_DW_OP_const8u
#endif /* __SIZEOF_INTMAX_T__ > 8 */
				addend = UNALIGNED_GET((uintmax_t const *)reader);
#if __SIZEOF_INTMAX_T__ > 8
			} else if (addrsize >= 8) {
		case DW_OP_const8u:
#define HAVE_CASE_DW_OP_const8u
				addend = UNALIGNED_GET64(reader);
#endif /* __SIZEOF_INTMAX_T__ > 8 */
#if __SIZEOF_INTMAX_T__ > 4
			} else if (addrsize >= 4) {
		case DW_OP_const4u:
		case DW_OP_call4:
#define HAVE_CASE_DW_OP_const4u
				addend = UNALIGNED_GET32(reader);
#endif /* __SIZEOF_INTMAX_T__ > 4 */
			} else if (addrsize >= 2) {
		case DW_OP_const2u:
		case DW_OP_call2:
				addend = UNALIGNED_GET16(reader);
			} else {
		case DW_OP_const1u:
				addend = UNALIGNED_GET8(reader);
			}
#ifndef HAVE_CASE_DW_OP_const8u
			__IF0 {
		case DW_OP_const8u:
				addend = (uintmax_t)UNALIGNED_GET64(reader);
			}
#endif /* !HAVE_CASE_DW_OP_const8u */
#ifndef HAVE_CASE_DW_OP_const4u
			__IF0 {
		case DW_OP_const4u:
		case DW_OP_call4:
				addend = (uintmax_t)UNALIGNED_GET32(reader);
			}
#endif /* !HAVE_CASE_DW_OP_const4u */
			__IF0 {
		case DW_OP_constu:
		case DW_OP_plus_uconst:
		case DW_OP_call_ref:
		case DW_OP_addrx:
		case DW_OP_GNU_addr_index:
		case DW_OP_constx:
		case DW_OP_GNU_const_index:
				addend = dwarf_decode_uleb128((byte_t const **)&reader);
			}
			PRINTF("\t$%#" PRIxMAX, addend);
		}	break;

		{
			intmax_t addend;
			__IF0 { case DW_OP_const1s: addend = (intmax_t)(int8_t)UNALIGNED_GET8(reader); }
			__IF0 { case DW_OP_const2s: addend = (intmax_t)(int16_t)UNALIGNED_GET16(reader); }
			__IF0 { case DW_OP_const4s: addend = (intmax_t)(int32_t)UNALIGNED_GET32(reader); }
			__IF0 { case DW_OP_const8s: addend = (intmax_t)(int64_t)UNALIGNED_GET64(reader); }
			__IF0 {
		case DW_OP_consts:
		case DW_OP_breg0 ... DW_OP_breg31:
		case DW_OP_fbreg:
				addend = (intmax_t)dwarf_decode_sleb128((byte_t const **)&reader);
			}
			PRINTF("\t$%" PRIdMAX, addend);
		}	break;

		case DW_OP_pick:
		case DW_OP_deref_size:
		case DW_OP_xderef_size: {
			uint8_t value = *(uint8_t const *)reader;
			PRINTF("\t$%#" PRIu8, value);
		}	break;

		case DW_OP_regx:
		case DW_OP_piece: {
			uintptr_t value;
			value = dwarf_decode_uleb128((byte_t const **)&reader);
			PRINTF("\t$%" PRIuPTR, value);
		}	break;

		case DW_OP_bregx: {
			uintptr_t regno;
			intptr_t offset;
			regno  = dwarf_decode_uleb128((byte_t const **)&reader);
			offset = dwarf_decode_sleb128((byte_t const **)&reader);
			PRINTF("\t$%" PRIuPTR ", $%" PRIdPTR, regno, offset);
		}	break;

		case DW_OP_bit_piece: {
			uintptr_t size;
			uintptr_t offset;
			size   = dwarf_decode_uleb128((byte_t const **)&reader);
			offset = dwarf_decode_uleb128((byte_t const **)&reader);
			PRINTF("\t$%" PRIuPTR ", $%" PRIuPTR, size, offset);
		}	break;

		case DW_OP_implicit_value: {
			uintptr_t size;
			size = dwarf_decode_uleb128((byte_t const **)&reader);
			PRINTF("\t%$q", size, reader);
		}	break;

		case DW_OP_entry_value:
		case DW_OP_GNU_entry_value:
			PRINT("\t");
			DO(libdl_debug_repr_cfi_expression(printer, arg, reader, indent + 1, addrsize, ptrsize));
			break;

		case DW_OP_GNU_encoded_addr: {
			uint8_t encoding = *reader++;
			void *pointer    = dwarf_decode_pointer((byte_t const **)&reader, encoding, addrsize, NULL);
			PRINTF("\t$%#" PRIxPTR, pointer);
		}	break;

		default:
			break;
		}
	} else {
		/* Fallback: emit raw bytes. */
		size_t i, length;
		length = (size_t)(unwind_instruction_succ_failsafe(reader,
		                                                   addrsize,
		                                                   ptrsize) -
		                  reader);
		assert(length >= 1);
		result = (*printer)(arg, REPR_STRING(".cfi_escape "), 12);
		if unlikely(result < 0)
			goto done;
		for (i = 0; i < length; ++i) {
			if (i != 0)
				PRINT(",");
			PRINTF("%#.2" PRIx8, reader[i]);
		}
	}
done:
	return result;
err:
	return temp;
}

PRIVATE ATTR_NOINLINE REPR_TEXTSECTION NONNULL((1, 3)) ssize_t CC
print_cfi_expression_with_labels(pformatprinter printer, void *arg,
                                 byte_t const *__restrict pc, size_t length,
                                 size_t indent, byte_t addrsize, byte_t ptrsize,
                                 struct label_buffer const *__restrict labels,
                                 bool indent_on_first_line) {
	ssize_t temp, result = 0;
	byte_t const *reader, *end;
	bool is_first;
	reader   = pc;
	end      = pc + length;
	is_first = true;
	while (reader < end) {
		struct label_entry const *label;
		if (!is_first)
			PRINT("\n");
		/* Check if there is a label at this instruction. */
		label = label_buffer_locate(labels, reader);
		if (label != NULL) {
			if (indent_on_first_line && indent >= 2)
				DO(format_repeat(printer, arg, '\t', indent - 1));
			PRINTF("L%" PRIuSIZ ":\t", (size_t)(label - labels->lb_entries));
		} else if (indent_on_first_line) {
			DO(format_repeat(printer, arg, '\t', indent));
		}
		/* Print the actual instruction. */
		DO(print_cfi_instruction(printer, arg, reader, addrsize, ptrsize, labels, indent));
		is_first             = false;
		indent_on_first_line = true;
		/* Advance to the next instruction */
		reader = unwind_instruction_succ_failsafe(reader, addrsize, ptrsize);
	}
	return result;
err:
	return temp;
}

PRIVATE ATTR_NOINLINE REPR_TEXTSECTION NONNULL((1, 3)) size_t CC
print_cfi_expression_with_label_bufsize(pformatprinter printer, void *arg,
                                        byte_t const *__restrict pc, size_t length,
                                        size_t indent, size_t label_bufsize,
                                        ssize_t *__restrict presult,
                                        byte_t addrsize, byte_t ptrsize,
                                        bool indent_on_first_line) {
	byte_t const *reader, *end;
	struct label_buffer *labels;
	labels = (struct label_buffer *)alloca(offsetof(struct label_buffer, lb_entries) +
	                                       (label_bufsize * sizeof(struct label_entry)));
	labels->lb_count = 0;
	labels->lb_alloc = label_bufsize;
	/* Scan for labels. */
	reader = pc;
	end    = pc + length;
	while (reader < end) {
		byte_t opcode;
		opcode = *reader;
		if (opcode == DW_OP_skip || opcode == DW_OP_bra) {
			int16_t offset;
			reader += 1;
			offset = (int16_t)UNALIGNED_GET16(reader);
			reader += 2;
			label_buffer_insert(labels, reader + offset);
		} else {
			reader = unwind_instruction_succ_failsafe(reader, addrsize, ptrsize);
		}
	}
	if (labels->lb_count <= labels->lb_alloc) {
		/* All labels were gathered. -> Actually print the thing! */
		*presult = print_cfi_expression_with_labels(printer, arg, pc, length, indent,
		                                            addrsize, ptrsize, labels,
		                                            indent_on_first_line);
	}
	return labels->lb_count;
}


/* Print the  disassembly of  a given  CFI expression  starting at  `pc',
 * covering a total  of `length'  bytes. One instruction  is printed  per
 * line, and  no trailing  line-feed is  printed. Each  new-line that  is
 * printed is  succeeded  by  `indent' TAB-characters  (unless  the  line
 * starts with a label definition, in which case `indent ? indent - 1: 0'
 * leading TAB  characters  are  printed, followed  by  the  label  name,
 * followed by another TAB character).
 * @param: printer:              Output printer.
 * @param: arg:                  Output printer cookie.
 * @param: pc:                   Starting address of the expression.
 * @param: length:               Length (in bytes) of the expression.
 * @param: addrsize:             s.a. `unwind_instruction_succ(3)'
 * @param: ptrsize:              s.a. `unwind_instruction_succ(3)'
 * @param: indent_on_first_line: When true, also output an indentation
 *                               before the first  line, the same  way
 *                               it would be if it wasn't actually the
 *                               first line.
 * @return: * : The usual pformatprinter-style value. */
INTERN REPR_TEXTSECTION NONNULL((1, 3)) ssize_t CC
libdl_debug_repr_cfi_expression_ex(pformatprinter printer, void *arg,
                                   byte_t const *__restrict pc, size_t length,
                                   size_t indent, byte_t addrsize, byte_t ptrsize,
                                   bool indent_on_first_line) {
	ssize_t result;
	size_t req_label_bufsize, label_bufsize = 0;
	for (;;) {
		req_label_bufsize = print_cfi_expression_with_label_bufsize(printer, arg, pc, length,
		                                                            indent, label_bufsize, &result,
		                                                            addrsize, ptrsize,
		                                                            indent_on_first_line);
		if (req_label_bufsize <= label_bufsize)
			break;
		label_bufsize = req_label_bufsize;
	}
	return result;
}

/* Same as `debug_repr_cfi_expression_ex(3)', but wrap the expression in
 * a pair of `{ ... }', either  like `{ nop }' when the expression  only
 * contains a single instruction, or
 *                     {
 *     [\t * (indent+1)] nop
 *     [\t * (indent+1)] nop
 *     [\t * (indent)] }
 * When where are at least 2 instructions. No trailing linefeed is printed.
 * @param: printer:  Output printer.
 * @param: arg:      Output printer cookie.
 * @param: pc:       Starting address of the expression.
 * @param: length:   Length (in bytes) of the expression.
 * @param: addrsize: s.a. `unwind_instruction_succ(3)'
 * @param: ptrsize:  s.a. `unwind_instruction_succ(3)'
 * @return: * : The usual pformatprinter-style value. */
INTERN REPR_TEXTSECTION NONNULL((1, 3)) ssize_t CC
libdl_debug_repr_cfi_expression_with_length(pformatprinter printer, void *arg,
                                            byte_t const *__restrict expr,
                                            size_t length, size_t indent,
                                            byte_t addrsize, byte_t ptrsize) {
	ssize_t temp, result = 0;
	if unlikely(!length) {
		result = (*printer)(arg, REPR_STRING("{}"), 2);
	} else {
		byte_t const *instr2;
		instr2 = unwind_instruction_succ_failsafe(expr, addrsize, ptrsize);
		if (instr2 >= expr + length) {
			/* Single instruction -> Print in-line. */
			result = (*printer)(arg, REPR_STRING("{ "), 2);
			if unlikely(result < 0)
				goto done;
			DO(libdl_debug_repr_cfi_expression_ex(printer, arg, expr, length, 0,
			                                      addrsize, ptrsize, false));
			PRINT(" }");
		} else {
			/* Multiple instructions -> Print one per line. */
			PRINT("{\n");
			DO(libdl_debug_repr_cfi_expression_ex(printer, arg, expr, length,
			                                      indent + 1, addrsize, ptrsize,
			                                      true));
			PRINT("\n");
			DO(format_repeat(printer, arg, '\t', indent));
			PRINT("}");
		}
	}
done:
	return result;
err:
	return temp;
}

/* Read the expression length as ULEB128 from `*expr' and print
 * the  disassembled contents of the succeeding CFI expression.
 * Same as `debug_repr_cfi_expression_with_length()'
 * @param: printer:  Output printer.
 * @param: arg:      Output printer cookie.
 * @param: pc:       Starting address of the expression.
 * @param: addrsize: s.a. `unwind_instruction_succ(3)'
 * @param: ptrsize:  s.a. `unwind_instruction_succ(3)'
 * @return: * : The usual pformatprinter-style value. */
INTERN REPR_TEXTSECTION NONNULL((1, 3)) ssize_t CC
libdl_debug_repr_cfi_expression(pformatprinter printer, void *arg,
                                byte_t const *__restrict expr, size_t indent,
                                byte_t addrsize, byte_t ptrsize) {
	size_t length = dwarf_decode_uleb128((byte_t const **)&expr);
	return libdl_debug_repr_cfi_expression_with_length(printer, arg, expr, length,
	                                                   indent, addrsize, ptrsize);
}


/* Dump the given debug information in a human-readable format to `printer':
 * >> void *dump_module = dlgetmodule("libc");
 * >> size_t debug_info_size, debug_abbrev_size, debug_str_size, debug_loclists_size, debug_loc_size, debug_line_str_size;
 * >> byte_t const *debug_info_data, *debug_abbrev_data, *debug_str_data, *debug_loclists_data, *debug_loc_data, *debug_line_str_data;
 * >> PDEBUG_REPR_DUMP debug_repr_dump;
 * >> *(void **)&debug_repr_dump = dlsym(dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LOCAL), "debug_repr_dump");
 * >> debug_info_data     = (byte_t const *)dlinflatesection(dllocksection(dump_module, ".debug_info"), &debug_info_size);
 * >> debug_abbrev_data   = (byte_t const *)dlinflatesection(dllocksection(dump_module, ".debug_abbrev"), &debug_abbrev_size);
 * >> debug_str_data      = (byte_t const *)dlinflatesection(dllocksection(dump_module, ".debug_str"), &debug_str_size);
 * >> debug_loc_data      = (byte_t const *)dlinflatesection(dllocksection(dump_module, ".debug_loc"), &debug_loc_size);
 * >> debug_loclists_data = (byte_t const *)dlinflatesection(dllocksection(dump_module, ".debug_loclists"), &debug_loclists_size);
 * >> debug_line_str_data = (byte_t const *)dlinflatesection(dllocksection(dump_module, ".debug_line_str"), &debug_line_str_size);
 * >> debug_repr_dump(&file_printer, stdout,
 * >>                 debug_info_data, debug_info_data + debug_info_size,
 * >>                 debug_abbrev_data, debug_abbrev_data + debug_abbrev_size,
 * >>                 debug_loc_data, debug_loc_data + debug_loc_size,
 * >>                 debug_loclists_data, debug_loclists_data + debug_loclists_size,
 * >>                 debug_str_data, debug_str_data + debug_str_size); */
INTERN REPR_TEXTSECTION NONNULL((1)) ssize_t CC
libdi_debug_repr_dump(pformatprinter printer, void *arg,
                      byte_t const *debug_info_start, byte_t const *debug_info_end,
                      byte_t const *debug_abbrev_start, byte_t const *debug_abbrev_end,
                      byte_t const *debug_loc_start, byte_t const *debug_loc_end,
                      byte_t const *debug_loclists_start, byte_t const *debug_loclists_end,
                      byte_t const *debug_str_start, byte_t const *debug_str_end,
                      byte_t const *debug_line_str_start, byte_t const *debug_line_str_end) {
	ssize_t temp, result = 0;
	char const *s;
	byte_t const *debug_info_iter;
	di_debuginfo_cu_parser_t parser;
	di_debuginfo_cu_abbrev_t abbrev;
	di_debuginfo_cu_parser_sections_t cu_sections;
	debug_info_iter                      = debug_info_start;
	cu_sections.cps_debug_abbrev_start   = debug_abbrev_start;
	cu_sections.cps_debug_abbrev_end     = debug_abbrev_end;
	cu_sections.cps_debug_info_start     = debug_info_start;
	cu_sections.cps_debug_info_end       = debug_info_end;
	cu_sections.cps_debug_loc_start      = debug_loc_start;
	cu_sections.cps_debug_loc_end        = debug_loc_end;
	cu_sections.cps_debug_loclists_start = debug_loclists_start;
	cu_sections.cps_debug_loclists_end   = debug_loclists_end;
	cu_sections.cps_debug_str_start      = debug_str_start;
	cu_sections.cps_debug_str_end        = debug_str_end;
	cu_sections.cps_debug_line_str_start = debug_line_str_start;
	cu_sections.cps_debug_line_str_end   = debug_line_str_end;
	while (libdi_debuginfo_cu_parser_loadunit(&debug_info_iter, debug_info_end,
	                                          &cu_sections, &parser,
	                                          &abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
		do {
			DO(format_repeat(printer, arg, '\t', parser.dup_child_depth));
			PRINTF("%#p:", parser.dsp_cu_info_pos - debug_info_start);
			s = libdi_debug_repr_DW_TAG(parser.dup_comp.dic_tag);
			DO(s ? format_printf(printer, arg, REPR_STRING("DW_TAG_%s:\n"), s)
			     : format_printf(printer, arg, REPR_STRING("%#" PRIxPTR ":\n"), (uintptr_t)parser.dup_comp.dic_tag));
			di_debuginfo_component_attrib_t attr;
			DI_DEBUGINFO_CU_PARSER_EACHATTR(attr, &parser) {
				byte_t const *orig_reader = parser.dsp_cu_info_pos;
				DO(format_repeat(printer, arg, '\t', parser.dup_child_depth + 1));
				PRINT("[");
				s = libdi_debug_repr_DW_AT(attr.dica_name);
				DO(s ? format_printf(printer, arg, REPR_STRING("DW_AT_%s:"), s)
				     : format_printf(printer, arg, REPR_STRING("%#" PRIxPTR ":"), (uintptr_t)attr.dica_name));
decode_form:
				s = libdi_debug_repr_DW_FORM(attr.dica_form);
				DO(s ? format_printf(printer, arg, REPR_STRING("DW_FORM_%s"), s)
				     : format_printf(printer, arg, REPR_STRING("%#" PRIxPTR ""), (uintptr_t)attr.dica_form));
				PRINT("] = ");
				switch (attr.dica_form) {

				case DW_FORM_indirect:
					attr.dica_form = dwarf_decode_uleb128(&parser.dsp_cu_info_pos);
					PRINT("[");
					goto decode_form;

				case DW_FORM_strp:
				case DW_FORM_string:
				case DW_FORM_strx:
				case DW_FORM_strp_sup:
				case DW_FORM_line_strp:
				case DW_FORM_GNU_str_index:
				case DW_FORM_GNU_strp_alt: {
					char const *value;
					if (!libdi_debuginfo_cu_parser_getstring(&parser, attr.dica_form, &value))
						goto err_bad_value;
					PRINTF("%q", value);
				}	break;

				case DW_FORM_addr:
				case DW_FORM_addrx:
				case DW_FORM_GNU_addr_index: {
					uintptr_t value;
					if (!libdi_debuginfo_cu_parser_getaddr(&parser, attr.dica_form, &value))
						goto err_bad_value;
					PRINTF("%#p", value);
				}	break;

				case DW_FORM_data1:
				case DW_FORM_data2:
				case DW_FORM_data4:
				case DW_FORM_data8:
				case DW_FORM_data16:
				case DW_FORM_sdata:
				case DW_FORM_udata:
				case DW_FORM_sec_offset:
				case DW_FORM_implicit_const:
				case DW_FORM_loclistx:
				case DW_FORM_rnglistx: {
					uintptr_t value;
					if (!libdi_debuginfo_cu_parser_getconst(&parser, attr.dica_form, &value, _attr_reader))
						goto err_bad_value;
					PRINTF("%" PRIuPTR " (%#" PRIxPTR ")", value, value);
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
				case DW_FORM_ref_udata:
				case DW_FORM_ref_sup4:
				case DW_FORM_ref_sup8:
				case DW_FORM_GNU_ref_alt: {
					byte_t const *value;
					di_debuginfo_cu_parser_t p2;
					if (!libdi_debuginfo_cu_parser_getref(&parser, attr.dica_form, &value))
						goto err_bad_value;
					p2                 = parser;
					p2.dsp_cu_info_pos = value;
					if unlikely(!libdi_debuginfo_cu_parser_next(&p2)) {
						PRINT("<BAD REFERENCE>");
					} else {
						PRINTF("%#p:", p2.dsp_cu_info_pos - debug_info_start);
						s = libdi_debug_repr_DW_TAG(p2.dup_comp.dic_tag);
						DO(s ? format_printf(printer, arg, REPR_STRING("DW_TAG_%s"), s)
						     : format_printf(printer, arg, REPR_STRING("%#" PRIxPTR),
						                     (uintptr_t)p2.dup_comp.dic_tag));
					}
				}	break;

				case DW_FORM_block:
				case DW_FORM_block1:
				case DW_FORM_block2:
				case DW_FORM_block4: {
#define MAX_BLOCK_LINE_LENGTH 32
					di_debuginfo_block_t block;
					if (!libdi_debuginfo_cu_parser_getblock(&parser, attr.dica_form, &block))
						goto err_bad_value;
					if (block.b_size == 0) {
						PRINT("{}");
					} else {
						int digits;
						size_t offset = 0;
						PRINT("{\n");
						if (block.b_size > 0xffff) {
							digits = 8;
						} else if (block.b_size > 0xff) {
							digits = 4;
						} else {
							digits = 2;
						}
						while (block.b_size) {
							size_t i, linelen;
							char repr[MAX_BLOCK_LINE_LENGTH];
							DO(format_repeat(printer, arg, '\t', parser.dup_child_depth + 2));
							linelen = block.b_size;
							if (linelen > MAX_BLOCK_LINE_LENGTH)
								linelen = MAX_BLOCK_LINE_LENGTH;
							PRINTF("%.*" PRIxSIZ ":", digits, offset);
							for (i = 0; i < linelen; ++i)
								PRINTF(" %.2" PRIX8, block.b_addr[i]);
							i = 1;
							if (linelen < MAX_BLOCK_LINE_LENGTH && offset != 0)
								i += MAX_BLOCK_LINE_LENGTH - linelen;
							DO(format_repeat(printer, arg, ' ', i * 3));
							for (i = 0; i < linelen; ++i) {
								char ch = (char)block.b_addr[i];
								if (!isprint(ch))
									ch = '.';
								repr[i] = ch;
							}
							DO((*printer)(arg, repr, linelen));
							block.b_addr += linelen;
							block.b_size -= linelen;
							offset += linelen;
							PRINT("\n");
						}
						DO(format_repeat(printer, arg, '\t', parser.dup_child_depth + 1));
						PRINT("}");
					}
#undef MAX_BLOCK_LINE_LENGTH
				}	break;

				case DW_FORM_exprloc: {
					di_debuginfo_location_t value;
					if (!libdi_debuginfo_cu_parser_getexpr(&parser, attr.dica_form, &value))
						goto err_bad_value;
					assert((value.l_llist4 || value.l_llist5) || value.l_expr);
					assert(!((value.l_llist4 || value.l_llist5) && value.l_expr));
					if (value.l_expr) {
						DO(libdl_debug_repr_cfi_expression(printer, arg, value.l_expr,
						                                   parser.dup_child_depth + 1,
						                                   parser.dsp_addrsize,
						                                   parser.dsp_ptrsize));
					} else if (value.l_llist5) {
						/* TODO */
					} else {
						uintptr_t cu_base;
						size_t indent;
						bool isfirst;
						indent  = parser.dup_child_depth + 2;
						cu_base = 0;
						isfirst = true;
						for (;;) {
							uint16_t length;
							uintptr_t range_start, range_end;
							if (parser.dsp_addrsize >= sizeof(uintptr_t)) {
								range_start = UNALIGNED_GET((uintptr_t const *)value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
								range_end = UNALIGNED_GET((uintptr_t const *)value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
#if __SIZEOF_POINTER__ > 4
							} else if (parser.dsp_addrsize >= 4) {
								range_start = UNALIGNED_GET32(value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
								range_end = UNALIGNED_GET32(value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
#endif /* __SIZEOF_POINTER__ > 4 */
							} else if (parser.dsp_addrsize >= 2) {
								range_start = UNALIGNED_GET16(value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
								range_end = UNALIGNED_GET16(value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
							} else {
								range_start = UNALIGNED_GET8(value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
								range_end = UNALIGNED_GET8(value.l_llist4);
								value.l_llist4 += parser.dsp_addrsize;
							}
							length = UNALIGNED_GET16(value.l_llist4);
							value.l_llist4 += 2;
							if (range_start == (uintptr_t)-1) {
								/* Base address selection entry! */
								cu_base = range_end;
							} else if (!range_start && !range_end) {
								break; /* Location list end entry. */
							} else {
								if (isfirst) {
									PRINT("{\n");
									isfirst = false;
								}
								range_start += cu_base;
								range_end += cu_base;
								DO(format_repeat(printer, arg, '\t', indent));
								PRINTF("%#" PRIxPTR "-%#" PRIxPTR ": ", range_start, range_end);
								DO(libdl_debug_repr_cfi_expression_with_length(printer, arg, value.l_llist4,
								                                               length, indent,
								                                               parser.dsp_addrsize,
								                                               parser.dsp_ptrsize));
							}
							value.l_llist4 += length;
						}
						if unlikely(isfirst) {
							PRINT("{}");
						} else {
							DO(format_repeat(printer, arg, '\t', indent - 1));
							PRINT("}");
						}
					}
				}	break;

				default:
err_bad_value:
					DO((*printer)(arg, unknown_string, 3));
					break;
				}
				PRINT("\n");
				parser.dsp_cu_info_pos = orig_reader;
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
DEFINE_PUBLIC_ALIAS(debug_repr_cfi_expression_ex, libdl_debug_repr_cfi_expression_ex);
DEFINE_PUBLIC_ALIAS(debug_repr_cfi_expression_with_length, libdl_debug_repr_cfi_expression_with_length);
DEFINE_PUBLIC_ALIAS(debug_repr_cfi_expression, libdl_debug_repr_cfi_expression);

DECL_END
#endif /* __KERNEL__ */

#endif /* !GUARD_LIBDEBUGINFO_REPR_C */
