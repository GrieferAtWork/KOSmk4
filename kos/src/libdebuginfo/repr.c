/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
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

#include <stddef.h>

#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/dwarf.h>
#include <libdebuginfo/repr.h>
#include <libunwind/cfi.h>

#include "debug_info.h"

DECL_BEGIN

#ifndef __KERNEL__
#undef CASE
#define CASE(prefix, name)                                                                 \
	case prefix##name: {                                                                   \
		PRIVATE REPR_STRINGSECTION ATTR_ALIGNED(1) char const _s_##prefix##name[] = #name; \
		result = _s_##prefix##name;                                                        \
	}	break;

/* Return the name of a given constant, or NULL if the constant isn't recognized.
 *  - debug_repr_DW_TAG():   Returns the `*' portion for one of `DW_TAG_*' (i.e. excluding the `DW_TAG_' prefix)
 *  - debug_repr_DW_AT():    Returns the `*' portion for one of `DW_AT_*' (i.e. excluding the `DW_AT_' prefix)
 *  - debug_repr_DW_FORM():  Returns the `*' portion for one of `DW_FORM_*' (i.e. excluding the `DW_FORM_' prefix)
 *  - debug_repr_DW_ATE():   Returns the `*' portion for one of `DW_ATE_*' (i.e. excluding the `DW_ATE_' prefix)
 *  - debug_repr_DW_OP():    Returns the `*' portion for one of `DW_OP_*' (i.e. excluding the `DW_OP_' prefix)
 *  - debug_repr_DW_CFA():   Returns the `*' portion for one of `DW_CFA_*' (i.e. excluding the `DW_CFA_' prefix)
 *  - debug_repr_DW_EH_PE(): Returns the `*' portion for one of `DW_EH_PE_*' (i.e. excluding the `DW_EH_PE_' prefix)
 */
INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_TAG)(dwarf_uleb128_t value) {
	char const *result;
	switch (value) {
	CASE(DW_TAG_, array_type)
	CASE(DW_TAG_, class_type)
	CASE(DW_TAG_, entry_point)
	CASE(DW_TAG_, enumeration_type)
	CASE(DW_TAG_, formal_parameter)
	CASE(DW_TAG_, imported_declaration)
	CASE(DW_TAG_, label)
	CASE(DW_TAG_, lexical_block)
	CASE(DW_TAG_, member)
	CASE(DW_TAG_, pointer_type)
	CASE(DW_TAG_, reference_type)
	CASE(DW_TAG_, compile_unit)
	CASE(DW_TAG_, string_type)
	CASE(DW_TAG_, structure_type)
	CASE(DW_TAG_, subroutine_type)
	CASE(DW_TAG_, typedef)
	CASE(DW_TAG_, union_type)
	CASE(DW_TAG_, unspecified_parameters)
	CASE(DW_TAG_, variant)
	CASE(DW_TAG_, common_block)
	CASE(DW_TAG_, common_inclusion)
	CASE(DW_TAG_, inheritance)
	CASE(DW_TAG_, inlined_subroutine)
	CASE(DW_TAG_, module)
	CASE(DW_TAG_, ptr_to_member_type)
	CASE(DW_TAG_, set_type)
	CASE(DW_TAG_, subrange_type)
	CASE(DW_TAG_, with_stmt)
	CASE(DW_TAG_, access_declaration)
	CASE(DW_TAG_, base_type)
	CASE(DW_TAG_, catch_block)
	CASE(DW_TAG_, const_type)
	CASE(DW_TAG_, constant)
	CASE(DW_TAG_, enumerator)
	CASE(DW_TAG_, file_type)
	CASE(DW_TAG_, friend)
	CASE(DW_TAG_, namelist)
	CASE(DW_TAG_, namelist_item)
	CASE(DW_TAG_, packed_type)
	CASE(DW_TAG_, subprogram)
	CASE(DW_TAG_, template_type_param)
	CASE(DW_TAG_, template_value_param)
	CASE(DW_TAG_, thrown_type)
	CASE(DW_TAG_, try_block)
	CASE(DW_TAG_, variant_part)
	CASE(DW_TAG_, variable)
	CASE(DW_TAG_, volatile_type)
	CASE(DW_TAG_, dwarf_procedure)
	CASE(DW_TAG_, restrict_type)
	CASE(DW_TAG_, interface_type)
	CASE(DW_TAG_, namespace)
	CASE(DW_TAG_, imported_module)
	CASE(DW_TAG_, unspecified_type)
	CASE(DW_TAG_, partial_unit)
	CASE(DW_TAG_, imported_unit)
	CASE(DW_TAG_, condition)
	CASE(DW_TAG_, shared_type)
	CASE(DW_TAG_, type_unit)
	CASE(DW_TAG_, rvalue_reference_type)
	CASE(DW_TAG_, template_alias)
	CASE(DW_TAG_, atomic_type)
	default: result = NULL; break;
	}
	return result;
}
INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_AT)(dwarf_uleb128_t value) {
	char const *result;
	switch (value) {
	CASE(DW_AT_, sibling)
	CASE(DW_AT_, location)
	CASE(DW_AT_, name)
	CASE(DW_AT_, ordering)
	CASE(DW_AT_, byte_size)
	CASE(DW_AT_, bit_offset)
	CASE(DW_AT_, bit_size)
	CASE(DW_AT_, stmt_list)
	CASE(DW_AT_, low_pc)
	CASE(DW_AT_, high_pc)
	CASE(DW_AT_, language)
	CASE(DW_AT_, discr)
	CASE(DW_AT_, discr_value)
	CASE(DW_AT_, visibility)
	CASE(DW_AT_, import)
	CASE(DW_AT_, string_length)
	CASE(DW_AT_, common_reference)
	CASE(DW_AT_, comp_dir)
	CASE(DW_AT_, const_value)
	CASE(DW_AT_, containing_type)
	CASE(DW_AT_, default_value)
	CASE(DW_AT_, inline)
	CASE(DW_AT_, is_optional)
	CASE(DW_AT_, lower_bound)
	CASE(DW_AT_, producer)
	CASE(DW_AT_, prototyped)
	CASE(DW_AT_, return_addr)
	CASE(DW_AT_, start_scope)
	CASE(DW_AT_, stride_size)
	CASE(DW_AT_, upper_bound)
	CASE(DW_AT_, abstract_origin)
	CASE(DW_AT_, accessibility)
	CASE(DW_AT_, address_class)
	CASE(DW_AT_, artificial)
	CASE(DW_AT_, base_types)
	CASE(DW_AT_, calling_convention)
	CASE(DW_AT_, count)
	CASE(DW_AT_, data_member_location)
	CASE(DW_AT_, decl_column)
	CASE(DW_AT_, decl_file)
	CASE(DW_AT_, decl_line)
	CASE(DW_AT_, declaration)
	CASE(DW_AT_, discr_list)
	CASE(DW_AT_, encoding)
	CASE(DW_AT_, external)
	CASE(DW_AT_, frame_base)
	CASE(DW_AT_, friend)
	CASE(DW_AT_, identifier_case)
	CASE(DW_AT_, macro_info)
	CASE(DW_AT_, namelist_item)
	CASE(DW_AT_, priority)
	CASE(DW_AT_, segment)
	CASE(DW_AT_, specification)
	CASE(DW_AT_, static_link)
	CASE(DW_AT_, type)
	CASE(DW_AT_, use_location)
	CASE(DW_AT_, variable_parameter)
	CASE(DW_AT_, virtuality)
	CASE(DW_AT_, vtable_elem_location)
	CASE(DW_AT_, allocated)
	CASE(DW_AT_, associated)
	CASE(DW_AT_, data_location)
	CASE(DW_AT_, byte_stride)
	CASE(DW_AT_, entry_pc)
	CASE(DW_AT_, use_UTF8)
	CASE(DW_AT_, extension)
	CASE(DW_AT_, ranges)
	CASE(DW_AT_, trampoline)
	CASE(DW_AT_, call_column)
	CASE(DW_AT_, call_file)
	CASE(DW_AT_, call_line)
	CASE(DW_AT_, description)
	CASE(DW_AT_, binary_scale)
	CASE(DW_AT_, decimal_scale)
	CASE(DW_AT_, small)
	CASE(DW_AT_, decimal_sign)
	CASE(DW_AT_, digit_count)
	CASE(DW_AT_, picture_string)
	CASE(DW_AT_, mutable)
	CASE(DW_AT_, threads_scaled)
	CASE(DW_AT_, explicit)
	CASE(DW_AT_, object_pointer)
	CASE(DW_AT_, endianity)
	CASE(DW_AT_, elemental)
	CASE(DW_AT_, pure)
	CASE(DW_AT_, recursive)
	CASE(DW_AT_, signature)
	CASE(DW_AT_, main_subprogram)
	CASE(DW_AT_, data_bit_offset)
	CASE(DW_AT_, const_expr)
	CASE(DW_AT_, enum_class)
	CASE(DW_AT_, linkage_name)
	CASE(DW_AT_, noreturn)
	CASE(DW_AT_, MIPS_fde)
	CASE(DW_AT_, MIPS_loop_begin)
	CASE(DW_AT_, MIPS_tail_loop_begin)
	CASE(DW_AT_, MIPS_epilog_begin)
	CASE(DW_AT_, MIPS_loop_unroll_factor)
	CASE(DW_AT_, MIPS_software_pipeline_depth)
	CASE(DW_AT_, MIPS_linkage_name)
	CASE(DW_AT_, MIPS_stride)
	CASE(DW_AT_, MIPS_abstract_name)
	CASE(DW_AT_, MIPS_clone_origin)
	CASE(DW_AT_, MIPS_has_inlines)
	CASE(DW_AT_, MIPS_stride_byte)
	CASE(DW_AT_, MIPS_stride_elem)
	CASE(DW_AT_, MIPS_ptr_dopetype)
	CASE(DW_AT_, MIPS_allocatable_dopetype)
	CASE(DW_AT_, MIPS_assumed_shape_dopetype)
	CASE(DW_AT_, MIPS_assumed_size)
	CASE(DW_AT_, sf_names)
	CASE(DW_AT_, src_info)
	CASE(DW_AT_, mac_info)
	CASE(DW_AT_, src_coords)
	CASE(DW_AT_, body_begin)
	CASE(DW_AT_, body_end)
	CASE(DW_AT_, GNU_vector)
	CASE(DW_AT_, GNU_guarded_by)
	CASE(DW_AT_, GNU_pt_guarded_by)
	CASE(DW_AT_, GNU_guarded)
	CASE(DW_AT_, GNU_pt_guarded)
	CASE(DW_AT_, GNU_locks_excluded)
	CASE(DW_AT_, GNU_exclusive_locks_required)
	CASE(DW_AT_, GNU_shared_locks_required)
	CASE(DW_AT_, GNU_odr_signature)
	CASE(DW_AT_, GNU_template_name)
	CASE(DW_AT_, GNU_call_site_value)
	CASE(DW_AT_, GNU_call_site_data_value)
	CASE(DW_AT_, GNU_call_site_target)
	CASE(DW_AT_, GNU_call_site_target_clobbered)
	CASE(DW_AT_, GNU_tail_call)
	CASE(DW_AT_, GNU_all_tail_call_sites)
	CASE(DW_AT_, GNU_all_call_sites)
	CASE(DW_AT_, GNU_all_source_call_sites)
	CASE(DW_AT_, GNU_macros)
	CASE(DW_AT_, GNU_deleted)
	CASE(DW_AT_, GNU_dwo_name)
	CASE(DW_AT_, GNU_dwo_id)
	CASE(DW_AT_, GNU_ranges_base)
	CASE(DW_AT_, GNU_addr_base)
	CASE(DW_AT_, GNU_pubnames)
	CASE(DW_AT_, GNU_pubtypes)
	default: result = NULL; break;
	}
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_FORM)(dwarf_uleb128_t value) {
	char const *result;
	switch (value) {
	CASE(DW_FORM_, addr)
	CASE(DW_FORM_, block2)
	CASE(DW_FORM_, block4)
	CASE(DW_FORM_, data2)
	CASE(DW_FORM_, data4)
	CASE(DW_FORM_, data8)
	CASE(DW_FORM_, string)
	CASE(DW_FORM_, block)
	CASE(DW_FORM_, block1)
	CASE(DW_FORM_, data1)
	CASE(DW_FORM_, flag)
	CASE(DW_FORM_, sdata)
	CASE(DW_FORM_, strp)
	CASE(DW_FORM_, udata)
	CASE(DW_FORM_, ref_addr)
	CASE(DW_FORM_, ref1)
	CASE(DW_FORM_, ref2)
	CASE(DW_FORM_, ref4)
	CASE(DW_FORM_, ref8)
	CASE(DW_FORM_, ref_udata)
	CASE(DW_FORM_, indirect)
	CASE(DW_FORM_, sec_offset)
	CASE(DW_FORM_, exprloc)
	CASE(DW_FORM_, flag_present)
	CASE(DW_FORM_, ref_sig8)
	default: result = NULL; break;
	}
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_ATE)(dwarf_uleb128_t value) {
	char const *result;
	switch (value) {
	CASE(DW_ATE_, address)
	CASE(DW_ATE_, boolean)
	CASE(DW_ATE_, complex_float)
	CASE(DW_ATE_, float)
	CASE(DW_ATE_, signed)
	CASE(DW_ATE_, signed_char)
	CASE(DW_ATE_, unsigned)
	CASE(DW_ATE_, unsigned_char)
	CASE(DW_ATE_, imaginary_float)
	CASE(DW_ATE_, packed_decimal)
	CASE(DW_ATE_, numeric_string)
	CASE(DW_ATE_, edited)
	CASE(DW_ATE_, signed_fixed)
	CASE(DW_ATE_, unsigned_fixed)
	CASE(DW_ATE_, decimal_float)
	CASE(DW_ATE_, UTF)
	default: result = NULL; break;
	}
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_OP)(uint8_t value) {
	char const *result;
	switch (value) {
	CASE(DW_OP_, addr)
	CASE(DW_OP_, deref)
	CASE(DW_OP_, const1u)
	CASE(DW_OP_, const1s)
	CASE(DW_OP_, const2u)
	CASE(DW_OP_, const2s)
	CASE(DW_OP_, const4u)
	CASE(DW_OP_, const4s)
	CASE(DW_OP_, const8u)
	CASE(DW_OP_, const8s)
	CASE(DW_OP_, constu)
	CASE(DW_OP_, consts)
	CASE(DW_OP_, dup)
	CASE(DW_OP_, drop)
	CASE(DW_OP_, over)
	CASE(DW_OP_, pick)
	CASE(DW_OP_, swap)
	CASE(DW_OP_, rot)
	CASE(DW_OP_, xderef)
	CASE(DW_OP_, abs)
	CASE(DW_OP_, and)
	CASE(DW_OP_, div)
	CASE(DW_OP_, minus)
	CASE(DW_OP_, mod)
	CASE(DW_OP_, mul)
	CASE(DW_OP_, neg)
	CASE(DW_OP_, not)
	CASE(DW_OP_, or)
	CASE(DW_OP_, plus)
	CASE(DW_OP_, plus_uconst)
	CASE(DW_OP_, shl)
	CASE(DW_OP_, shr)
	CASE(DW_OP_, shra)
	CASE(DW_OP_, xor)
	CASE(DW_OP_, skip)
	CASE(DW_OP_, bra)
	CASE(DW_OP_, eq)
	CASE(DW_OP_, ge)
	CASE(DW_OP_, gt)
	CASE(DW_OP_, le)
	CASE(DW_OP_, lt)
	CASE(DW_OP_, ne)
	CASE(DW_OP_, lit0)
	CASE(DW_OP_, lit1)
	CASE(DW_OP_, lit2)
	CASE(DW_OP_, lit3)
	CASE(DW_OP_, lit4)
	CASE(DW_OP_, lit5)
	CASE(DW_OP_, lit6)
	CASE(DW_OP_, lit7)
	CASE(DW_OP_, lit8)
	CASE(DW_OP_, lit9)
	CASE(DW_OP_, lit10)
	CASE(DW_OP_, lit11)
	CASE(DW_OP_, lit12)
	CASE(DW_OP_, lit13)
	CASE(DW_OP_, lit14)
	CASE(DW_OP_, lit15)
	CASE(DW_OP_, lit16)
	CASE(DW_OP_, lit17)
	CASE(DW_OP_, lit18)
	CASE(DW_OP_, lit19)
	CASE(DW_OP_, lit20)
	CASE(DW_OP_, lit21)
	CASE(DW_OP_, lit22)
	CASE(DW_OP_, lit23)
	CASE(DW_OP_, lit24)
	CASE(DW_OP_, lit25)
	CASE(DW_OP_, lit26)
	CASE(DW_OP_, lit27)
	CASE(DW_OP_, lit28)
	CASE(DW_OP_, lit29)
	CASE(DW_OP_, lit30)
	CASE(DW_OP_, lit31)
	CASE(DW_OP_, reg0)
	CASE(DW_OP_, reg1)
	CASE(DW_OP_, reg2)
	CASE(DW_OP_, reg3)
	CASE(DW_OP_, reg4)
	CASE(DW_OP_, reg5)
	CASE(DW_OP_, reg6)
	CASE(DW_OP_, reg7)
	CASE(DW_OP_, reg8)
	CASE(DW_OP_, reg9)
	CASE(DW_OP_, reg10)
	CASE(DW_OP_, reg11)
	CASE(DW_OP_, reg12)
	CASE(DW_OP_, reg13)
	CASE(DW_OP_, reg14)
	CASE(DW_OP_, reg15)
	CASE(DW_OP_, reg16)
	CASE(DW_OP_, reg17)
	CASE(DW_OP_, reg18)
	CASE(DW_OP_, reg19)
	CASE(DW_OP_, reg20)
	CASE(DW_OP_, reg21)
	CASE(DW_OP_, reg22)
	CASE(DW_OP_, reg23)
	CASE(DW_OP_, reg24)
	CASE(DW_OP_, reg25)
	CASE(DW_OP_, reg26)
	CASE(DW_OP_, reg27)
	CASE(DW_OP_, reg28)
	CASE(DW_OP_, reg29)
	CASE(DW_OP_, reg30)
	CASE(DW_OP_, reg31)
	CASE(DW_OP_, breg0)
	CASE(DW_OP_, breg1)
	CASE(DW_OP_, breg2)
	CASE(DW_OP_, breg3)
	CASE(DW_OP_, breg4)
	CASE(DW_OP_, breg5)
	CASE(DW_OP_, breg6)
	CASE(DW_OP_, breg7)
	CASE(DW_OP_, breg8)
	CASE(DW_OP_, breg9)
	CASE(DW_OP_, breg10)
	CASE(DW_OP_, breg11)
	CASE(DW_OP_, breg12)
	CASE(DW_OP_, breg13)
	CASE(DW_OP_, breg14)
	CASE(DW_OP_, breg15)
	CASE(DW_OP_, breg16)
	CASE(DW_OP_, breg17)
	CASE(DW_OP_, breg18)
	CASE(DW_OP_, breg19)
	CASE(DW_OP_, breg20)
	CASE(DW_OP_, breg21)
	CASE(DW_OP_, breg22)
	CASE(DW_OP_, breg23)
	CASE(DW_OP_, breg24)
	CASE(DW_OP_, breg25)
	CASE(DW_OP_, breg26)
	CASE(DW_OP_, breg27)
	CASE(DW_OP_, breg28)
	CASE(DW_OP_, breg29)
	CASE(DW_OP_, breg30)
	CASE(DW_OP_, breg31)
	CASE(DW_OP_, regx)
	CASE(DW_OP_, fbreg)
	CASE(DW_OP_, bregx)
	CASE(DW_OP_, piece)
	CASE(DW_OP_, deref_size)
	CASE(DW_OP_, xderef_size)
	CASE(DW_OP_, nop)
	CASE(DW_OP_, push_object_address)
	CASE(DW_OP_, call2)
	CASE(DW_OP_, call4)
	CASE(DW_OP_, call_ref)
	CASE(DW_OP_, form_tls_address)
	CASE(DW_OP_, call_frame_cfa)
	CASE(DW_OP_, bit_piece)
	CASE(DW_OP_, implicit_value)
	CASE(DW_OP_, stack_value)
	default: result = NULL; break;
	}
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_CFA)(uint8_t value) {
	char const *result;
	switch (value) {
	CASE(DW_CFA_, advance_loc)
	CASE(DW_CFA_, offset)
	CASE(DW_CFA_, restore)
	CASE(DW_CFA_, nop)
	CASE(DW_CFA_, set_loc)
	CASE(DW_CFA_, advance_loc1)
	CASE(DW_CFA_, advance_loc2)
	CASE(DW_CFA_, advance_loc4)
	CASE(DW_CFA_, offset_extended)
	CASE(DW_CFA_, restore_extended)
	CASE(DW_CFA_, undefined)
	CASE(DW_CFA_, same_value)
	CASE(DW_CFA_, register)
	CASE(DW_CFA_, remember_state)
	CASE(DW_CFA_, restore_state)
	CASE(DW_CFA_, def_cfa)
	CASE(DW_CFA_, def_cfa_register)
	CASE(DW_CFA_, def_cfa_offset)
	CASE(DW_CFA_, def_cfa_expression)
	CASE(DW_CFA_, expression)
	CASE(DW_CFA_, offset_extended_sf)
	CASE(DW_CFA_, def_cfa_sf)
	CASE(DW_CFA_, def_cfa_offset_sf)
	CASE(DW_CFA_, val_offset)
	CASE(DW_CFA_, val_offset_sf)
	CASE(DW_CFA_, val_expression)
	CASE(DW_CFA_, GNU_args_size)
	CASE(DW_CFA_, GNU_negative_offset_extended)
	default: result = NULL; break;
	}
	return result;
}

INTERN REPR_TEXTSECTION ATTR_CONST WUNUSED char const *
NOTHROW(CC libdi_debug_repr_DW_EH_PE)(uint8_t value) {
	char const *result;
	switch (value) {
	CASE(DW_EH_PE_, absptr)
	CASE(DW_EH_PE_, uleb128)
	CASE(DW_EH_PE_, udata2)
	CASE(DW_EH_PE_, udata4)
	CASE(DW_EH_PE_, udata8)
	CASE(DW_EH_PE_, sleb128)
	CASE(DW_EH_PE_, sdata2)
	CASE(DW_EH_PE_, sdata4)
	CASE(DW_EH_PE_, sdata8)
	CASE(DW_EH_PE_, pcrel)
	CASE(DW_EH_PE_, textrel)
	CASE(DW_EH_PE_, datarel)
	CASE(DW_EH_PE_, funcrel)
	CASE(DW_EH_PE_, aligned)
	CASE(DW_EH_PE_, omit)
	default: result = NULL; break;
	}
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
	                                          &cu_sections, &parser, &abbrev, NULL) == DEBUG_INFO_ERROR_SUCCESS) {
		do {
			DO(format_repeat(printer, arg, '\t', parser.dup_child_depth));
			DO(format_printf(printer, arg, REPR_STRING("%#p:"), parser.dup_cu_info_pos));
			s = libdi_debug_repr_DW_TAG(parser.dup_comp.dic_tag);
			DO(s ? format_printf(printer, arg, REPR_STRING("DW_TAG_%s:\n"), s) : format_printf(printer, arg, REPR_STRING("%#Ix:\n"), parser.dup_comp.dic_tag));
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
