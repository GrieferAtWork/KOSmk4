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
#ifndef _LIBDEBUGINFO_DWARF_H
#define _LIBDEBUGINFO_DWARF_H 1

#include "api.h"
#include <bits/types.h>
#include <hybrid/__unaligned.h>

/* NOTE: The DWARF implementation here is based on information gathered
 *       from binutils, but mostly from the online specifications
 *       "http://www.dwarfstd.org/doc/DWARF4.pdf", section 6.2
 *
 * SOURCES:
 *   - http://www.dwarfstd.org/doc/DWARF4.pdf
 *   - http://www.dwarfstd.org/doc/dwarf-2.0.0.pdf
 *   - https://sourceware.org/elfutils/DwarfExtensions
 *
 */

#define DW_LNS_extended_op        0
#define DW_LNS_copy               1
#define DW_LNS_advance_pc         2
#define DW_LNS_advance_line       3
#define DW_LNS_set_file           4
#define DW_LNS_set_column         5
#define DW_LNS_negate_stmt        6
#define DW_LNS_set_basic_block    7
#define DW_LNS_const_add_pc       8
#define DW_LNS_fixed_advance_pc   9
#define DW_LNS_set_prologue_end   10
#define DW_LNS_set_epilogue_begin 11
#define DW_LNS_set_isa            12

#define DW_LNE_end_sequence                1
#define DW_LNE_set_address                 2
#define DW_LNE_define_file                 3
#define DW_LNE_set_discriminator           4
#define DW_LNE_HP_negate_is_UV_update      0x11
#define DW_LNE_HP_push_context             0x12
#define DW_LNE_HP_pop_context              0x13
#define DW_LNE_HP_set_file_line_column     0x14
#define DW_LNE_HP_set_routine_name         0x15
#define DW_LNE_HP_set_sequence             0x16
#define DW_LNE_HP_negate_post_semantics    0x17
#define DW_LNE_HP_negate_function_exit     0x18
#define DW_LNE_HP_negate_front_end_logical 0x19
#define DW_LNE_HP_define_proc              0x20
#define DW_LNE_HP_source_file_correlation  0x80
#define DW_LNE_lo_user                     0x80
#define DW_LNE_hi_user                     0xff

#define DW_LNE_HP_SFC_formfeed         1
#define DW_LNE_HP_SFC_set_listing_line 2
#define DW_LNE_HP_SFC_associate        3

#define DW_TAG_array_type             0x01
#define DW_TAG_class_type             0x02
#define DW_TAG_entry_point            0x03
#define DW_TAG_enumeration_type       0x04
#define DW_TAG_formal_parameter       0x05
#define DW_TAG_imported_declaration   0x08
#define DW_TAG_label                  0x0a
#define DW_TAG_lexical_block          0x0b
#define DW_TAG_member                 0x0d
#define DW_TAG_pointer_type           0x0f
#define DW_TAG_reference_type         0x10
#define DW_TAG_compile_unit           0x11
#define DW_TAG_string_type            0x12
#define DW_TAG_structure_type         0x13
#define DW_TAG_subroutine_type        0x15
#define DW_TAG_typedef                0x16
#define DW_TAG_union_type             0x17
#define DW_TAG_unspecified_parameters 0x18
#define DW_TAG_variant                0x19
#define DW_TAG_common_block           0x1a
#define DW_TAG_common_inclusion       0x1b
#define DW_TAG_inheritance            0x1c
#define DW_TAG_inlined_subroutine     0x1d
#define DW_TAG_module                 0x1e
#define DW_TAG_ptr_to_member_type     0x1f
#define DW_TAG_set_type               0x20
#define DW_TAG_subrange_type          0x21
#define DW_TAG_with_stmt              0x22
#define DW_TAG_access_declaration     0x23
#define DW_TAG_base_type              0x24
#define DW_TAG_catch_block            0x25
#define DW_TAG_const_type             0x26
#define DW_TAG_constant               0x27
#define DW_TAG_enumerator             0x28
#define DW_TAG_file_type              0x29
#define DW_TAG_friend                 0x2a
#define DW_TAG_namelist               0x2b
#define DW_TAG_namelist_item          0x2c
#define DW_TAG_packed_type            0x2d
#define DW_TAG_subprogram             0x2e
#define DW_TAG_template_type_param    0x2f
#define DW_TAG_template_value_param   0x30
#define DW_TAG_thrown_type            0x31
#define DW_TAG_try_block              0x32
#define DW_TAG_variant_part           0x33
#define DW_TAG_variable               0x34
#define DW_TAG_volatile_type          0x35
#define DW_TAG_dwarf_procedure        0x36
#define DW_TAG_restrict_type          0x37
#define DW_TAG_interface_type         0x38
#define DW_TAG_namespace              0x39
#define DW_TAG_imported_module        0x3a
#define DW_TAG_unspecified_type       0x3b
#define DW_TAG_partial_unit           0x3c
#define DW_TAG_imported_unit          0x3d
#define DW_TAG_condition              0x3f
#define DW_TAG_shared_type            0x40
#define DW_TAG_type_unit              0x41
#define DW_TAG_rvalue_reference_type  0x42
#define DW_TAG_template_alias         0x43
#define DW_TAG_atomic_type            0x47
#define DW_TAG_lo_user                0x4080
#define DW_TAG_hi_user                0xffff

#define DW_CHILDREN_no      0
#define DW_CHILDREN_yes     1

#define DW_AT_sibling              0x01 /* reference */
#define DW_AT_location             0x02 /* block, constant */
#define DW_AT_name                 0x03 /* string */
#define DW_AT_ordering             0x09 /* constant */
#define DW_AT_byte_size            0x0b /* constant */
#define DW_AT_bit_offset           0x0c /* constant */
#define DW_AT_bit_size             0x0d /* constant */
#define DW_AT_stmt_list            0x10 /* constant */
#define DW_AT_low_pc               0x11 /* address */
#define DW_AT_high_pc              0x12 /* address, constant */
#define DW_AT_language             0x13 /* constant */
#define DW_AT_discr                0x15 /* reference */
#define DW_AT_discr_value          0x16 /* constant */
#define DW_AT_visibility           0x17 /* constant */
#define DW_AT_import               0x18 /* reference */
#define DW_AT_string_length        0x19 /* block, constant */
#define DW_AT_common_reference     0x1a /* reference */
#define DW_AT_comp_dir             0x1b /* string */
#define DW_AT_const_value          0x1c /* string, constant, block */
#define DW_AT_containing_type      0x1d /* reference */
#define DW_AT_default_value        0x1e /* reference */
#define DW_AT_inline               0x20 /* constant */
#define DW_AT_is_optional          0x21 /* flag */
#define DW_AT_lower_bound          0x22 /* constant, reference */
#define DW_AT_producer             0x25 /* string */
#define DW_AT_prototyped           0x27 /* flag */
#define DW_AT_return_addr          0x2a /* block, constant */
#define DW_AT_start_scope          0x2c /* constant */
#define DW_AT_stride_size          0x2e /* constant */
#define DW_AT_upper_bound          0x2f /* constant, reference */
#define DW_AT_abstract_origin      0x31 /* reference */
#define DW_AT_accessibility        0x32 /* constant */
#define DW_AT_address_class        0x33 /* constant */
#define DW_AT_artificial           0x34 /* flag */
#define DW_AT_base_types           0x35 /* reference */
#define DW_AT_calling_convention   0x36 /* constant */
#define DW_AT_count                0x37 /* constant, reference */
#define DW_AT_data_member_location 0x38 /* block, reference */
#define DW_AT_decl_column          0x39 /* constant */
#define DW_AT_decl_file            0x3a /* constant */
#define DW_AT_decl_line            0x3b /* constant */
#define DW_AT_declaration          0x3c /* flag */
#define DW_AT_discr_list           0x3d /* block */
#define DW_AT_encoding             0x3e /* constant */
#define DW_AT_external             0x3f /* flag */
#define DW_AT_frame_base           0x40 /* block, constant */
#define DW_AT_friend               0x41 /* reference */
#define DW_AT_identifier_case      0x42 /* constant */
#define DW_AT_macro_info           0x43 /* constant */
#define DW_AT_namelist_item        0x44 /* block */
#define DW_AT_priority             0x45 /* reference */
#define DW_AT_segment              0x46 /* block, constant */
#define DW_AT_specification        0x47 /* reference */
#define DW_AT_static_link          0x48 /* block, constant */
#define DW_AT_type                 0x49 /* reference */
#define DW_AT_use_location         0x4a /* block, constant */
#define DW_AT_variable_parameter   0x4b /* flag */
#define DW_AT_virtuality           0x4c /* constant */
#define DW_AT_vtable_elem_location 0x4d /* block, reference */
#define DW_AT_allocated            0x4e /* constant, exprloc, reference */
#define DW_AT_associated           0x4f /* constant, exprloc, reference */
#define DW_AT_data_location        0x50 /* exprloc */
#define DW_AT_byte_stride          0x51 /* constant, exprloc, reference */
#define DW_AT_entry_pc             0x52 /* address */
#define DW_AT_use_UTF8             0x53 /* flag */
#define DW_AT_extension            0x54 /* reference */
#define DW_AT_ranges               0x55 /* rangelistptr */
#define DW_AT_trampoline           0x56 /* address, flag, reference, string */
#define DW_AT_call_column          0x57 /* constant */
#define DW_AT_call_file            0x58 /* constant */
#define DW_AT_call_line            0x59 /* constant */
#define DW_AT_description          0x5a /* string */
#define DW_AT_binary_scale         0x5b /* constant */
#define DW_AT_decimal_scale        0x5c /* constant */
#define DW_AT_small                0x5d /* reference */
#define DW_AT_decimal_sign         0x5e /* constant */
#define DW_AT_digit_count          0x5f /* constant */
#define DW_AT_picture_string       0x60 /* string */
#define DW_AT_mutable              0x61 /* flag */
#define DW_AT_threads_scaled       0x62 /* flag */
#define DW_AT_explicit             0x63 /* flag */
#define DW_AT_object_pointer       0x64 /* reference */
#define DW_AT_endianity            0x65 /* constant */
#define DW_AT_elemental            0x66 /* flag */
#define DW_AT_pure                 0x67 /* flag */
#define DW_AT_recursive            0x68 /* flag */
#define DW_AT_signature            0x69 /* reference */
#define DW_AT_main_subprogram      0x6a /* flag */
#define DW_AT_data_bit_offset      0x6b /* constant */
#define DW_AT_const_expr           0x6c /* flag */
#define DW_AT_enum_class           0x6d /* flag */
#define DW_AT_linkage_name         0x6e /* string */
#define DW_AT_lo_user              0x2000 /* - */
#define DW_AT_hi_user              0x3fff /* - */


#define DW_AT_noreturn                       0x87   /* Identifies a subprogram that does not return to its caller, DWARFv5             GCC5             Constant only */
#define DW_AT_MIPS_fde                       0x2001 /* subprogram tag attribute, offset into .debug_frame section, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_loop_begin                0x2002 /* Never implemented, mips_extensions             Nothing             Constant only */
#define DW_AT_MIPS_tail_loop_begin           0x2003 /* Never implemented, mips_extensions             Nothing             Constant only */
#define DW_AT_MIPS_epilog_begin              0x2004 /* Never implemented, mips_extensions             Nothing             Constant only */
#define DW_AT_MIPS_loop_unroll_factor        0x2005 /* Never implemented, mips_extensions             Nothing             Constant only */
#define DW_AT_MIPS_software_pipeline_depth   0x2006 /* Never implemented, mips_extensions             Nothing             Constant only */
#define DW_AT_MIPS_linkage_name              0x2007 /* Same as DWARF4 DW_AT_linkage_name             GCC             Constant only */
#define DW_AT_MIPS_stride                    0x2008 /* F90 array stride, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_abstract_name             0x2009 /* name of inlined_subroutine with abstract root in other CU, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_clone_origin              0x200a /* name of non-specialed version of cloned subroutine, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_has_inlines               0x200b /* hint for inlined subroutines under subprogram DIE, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_stride_byte               0x200c /* F90 array stride, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_stride_elem               0x200d /* F90 array stride, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_ptr_dopetype              0x200e /* F90 Dope Vector, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_allocatable_dopetype      0x200f /* F90 Dope Vector, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_assumed_shape_dopetype    0x2010 /* F90 Dope Vector, mips_extensions             Unknown             Constant only */
#define DW_AT_MIPS_assumed_size              0x2011 /* F90 arrays, mips_extensions             Unknown             Constant only */
#define DW_AT_sf_names                       0x2101 /* DWARF1 only?             Unknown             Constant only */
#define DW_AT_src_info                       0x2102 /* DWARF1 only?             Unknown             Constant only */
#define DW_AT_mac_info                       0x2103 /* DWARF1 only?             Unknown             Constant only */
#define DW_AT_src_coords                     0x2104 /* DWARF1 only?             Unknown             Constant only */
#define DW_AT_body_begin                     0x2105 /* DWARF1 only?             Unknown             Constant only */
#define DW_AT_body_end                       0x2106 /* DWARF1 only?             Unknown             Constant only */
#define DW_AT_GNU_vector                     0x2107 /* ppc/ppc64 Altivec return value             GCC             dwfl_module_return_value_location */
#define DW_AT_GNU_guarded_by                 0x2108 /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_pt_guarded_by              0x2109 /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_guarded                    0x210a /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_pt_guarded                 0x210b /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_locks_excluded             0x210c /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_exclusive_locks_required   0x210d /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_shared_locks_required      0x210e /* GNU ThreadSafetyAnnotations             Not implemented             Constant only */
#define DW_AT_GNU_odr_signature              0x210f /* link-time ODR checking part of GNU DwarfSeparateTypeInfo             GCC             Constant only */
#define DW_AT_GNU_template_name              0x2110 /* GNU Template Parms and DWARF5 proposal             G++             Constant only */
#define DW_AT_GNU_call_site_value            0x2111 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_call_site_data_value       0x2112 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_call_site_target           0x2113 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_call_site_target_clobbered 0x2114 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_tail_call                  0x2115 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_all_tail_call_sites        0x2116 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_all_call_sites             0x2117 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_all_source_call_sites      0x2118 /* GNU call site DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_macros                     0x2119 /* GNU .debug_macro DWARF5 proposal             GCC             Recognized in readelf */
#define DW_AT_GNU_deleted                    0x211a /* Attribute added for C++11 deleted special member functions (= delete;)             G++             Constant only */
#define DW_AT_GNU_dwo_name                   0x2130 /* GNU Fission DWARF5 proposal             Unknown             No support */
#define DW_AT_GNU_dwo_id                     0x2131 /* GNU Fission DWARF5 proposal             Unknown             No support */
#define DW_AT_GNU_ranges_base                0x2132 /* GNU Fission DWARF5 proposal             Unknown             No support */
#define DW_AT_GNU_addr_base                  0x2133 /* GNU Fission DWARF5 proposal             Unknown             No support */
#define DW_AT_GNU_pubnames                   0x2134 /* GNU Fission DWARF5 proposal             GCC             No support */
#define DW_AT_GNU_pubtypes                   0x2135 /* GNU Fission DWARF5 proposal             GCC             No support  */


#define DW_LANG_C89             0x0001
#define DW_LANG_C               0x0002
#define DW_LANG_Ada83           0x0003
#define DW_LANG_C_plus_plus     0x0004
#define DW_LANG_Cobol74         0x0005
#define DW_LANG_Cobol85         0x0006
#define DW_LANG_Fortran77       0x0007
#define DW_LANG_Fortran90       0x0008
#define DW_LANG_Pascal83        0x0009
#define DW_LANG_Modula2         0x000a
#define DW_LANG_Java            0x000b
#define DW_LANG_C99             0x000c
#define DW_LANG_Ada95           0x000d
#define DW_LANG_Fortran95       0x000e
#define DW_LANG_PLI             0x000f
#define DW_LANG_ObjC            0x0010
#define DW_LANG_ObjC_plus_plus  0x0011
#define DW_LANG_UPC             0x0012
#define DW_LANG_D               0x0013
#define DW_LANG_Python          0x0014
#define DW_LANG_Go              0x0016
#define DW_LANG_C_plus_plus_11  0x001a
#define DW_LANG_C11             0x001d
#define DW_LANG_C_plus_plus_14  0x0021
#define DW_LANG_Fortran03       0x0022
#define DW_LANG_Fortran08       0x0023
#define DW_LANG_lo_user         0x8000
#define DW_LANG_hi_user         0xffff
#define DW_LANG_Mips_Assembler  0x8001
#define DW_LANG_Upc             0x8765
#define DW_LANG_HP_Bliss        0x8003
#define DW_LANG_HP_Basic91      0x8004
#define DW_LANG_HP_Pascal91     0x8005
#define DW_LANG_HP_IMacro       0x8006
#define DW_LANG_HP_Assembler    0x8007


#define DW_FORM_addr         0x01 /* address */
#define DW_FORM_block2       0x03 /* block */
#define DW_FORM_block4       0x04 /* block */
#define DW_FORM_data2        0x05 /* constant */
#define DW_FORM_data4        0x06 /* constant */
#define DW_FORM_data8        0x07 /* constant */
#define DW_FORM_string       0x08 /* string */
#define DW_FORM_block        0x09 /* block */
#define DW_FORM_block1       0x0a /* block */
#define DW_FORM_data1        0x0b /* constant */
#define DW_FORM_flag         0x0c /* flag */
#define DW_FORM_sdata        0x0d /* constant */
#define DW_FORM_strp         0x0e /* string */
#define DW_FORM_udata        0x0f /* constant */
#define DW_FORM_ref_addr     0x10 /* reference */
#define DW_FORM_ref1         0x11 /* reference */
#define DW_FORM_ref2         0x12 /* reference */
#define DW_FORM_ref4         0x13 /* reference */
#define DW_FORM_ref8         0x14 /* reference */
#define DW_FORM_ref_udata    0x15 /* reference */
#define DW_FORM_indirect     0x16 /* (see section 7.5.3) */
#define DW_FORM_sec_offset   0x17 /* lineptr, loclistptr, macptr, rangelistptr */
#define DW_FORM_exprloc      0x18 /* exprloc */
#define DW_FORM_flag_present 0x19 /* flag */
#define DW_FORM_ref_sig8     0x20 /* reference */


/* NOTE: Taken form `http://www.dwarfstd.org/doc/DWARF4.pdf' (Figure 13. Encoding attribute values) */
#define DW_ATE_address               0x01 /* linear machine address */
#define DW_ATE_boolean               0x02 /* true or false */
#define DW_ATE_complex_float         0x03 /* complex binary floating-point number */
#define DW_ATE_float                 0x04 /* binary floating-point number */
#define DW_ATE_signed                0x05 /* signed binary integer */
#define DW_ATE_signed_char           0x06 /* signed character */
#define DW_ATE_unsigned              0x07 /* unsigned binary integer */
#define DW_ATE_unsigned_char         0x08 /* unsigned character */
#define DW_ATE_imaginary_float       0x09 /* imaginary binary floating-point number */
#define DW_ATE_packed_decimal        0x0a /* packed decimal */
#define DW_ATE_numeric_string        0x0b /* numeric string */
#define DW_ATE_edited                0x0c /* edited string */
#define DW_ATE_signed_fixed          0x0d /* signed fixed-point scaled integer */
#define DW_ATE_unsigned_fixed        0x0e /* unsigned fixed-point scaled integer */
#define DW_ATE_decimal_float         0x0f /* decimal floating-point number */
#define DW_ATE_UTF                   0x10 /* Unicode character */
#define DW_ATE_lo_user               0x80
#define DW_ATE_hi_user               0xff

/* Absolute pointer encoding formats */
#define DW_EH_PE_absptr   0x00
#define DW_EH_PE_uleb128  0x01
#define DW_EH_PE_udata2   0x02
#define DW_EH_PE_udata4   0x03
#define DW_EH_PE_udata8   0x04
#define DW_EH_PE_signed   0x08
#define DW_EH_PE_sleb128  0x09
#define DW_EH_PE_sdata2   0x0a
#define DW_EH_PE_sdata4   0x0b
#define DW_EH_PE_sdata8   0x0c
/* Relative pointer encoding formats */
#define DW_EH_PE_pcrel    0x10
#define DW_EH_PE_textrel  0x20
#define DW_EH_PE_datarel  0x30
#define DW_EH_PE_funcrel  0x40
#define DW_EH_PE_aligned  0x50
/* Special */
#define DW_EH_PE_omit     0xff /* Omit the pointer. */
#define DW_EH_PE_indirect 0x80 /* FLAG */



#ifdef __CC__
__DECL_BEGIN

typedef __intptr_t  dwarf_sleb128_t;
typedef __uintptr_t dwarf_uleb128_t;

/* Decode a signed/unsigned LEB128 integer and advance `*ptext' */
__LOCAL __ATTR_NONNULL((1)) dwarf_sleb128_t
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_sleb128)(__byte_t **__restrict ptext) {
	/* TODO: Make this one an external in-library function! */
	__byte_t byte,*text = *ptext;
	dwarf_sleb128_t result = 0;
	unsigned int shift = 0;
	for (;;) {
		byte    = *text++;
		result |= ((byte & 0x7f) << shift);
		shift  += 7;
		if __untraced(!(byte & 0x80))
			break;
	}
	if __untraced((byte & 0x40) &&
	              (shift < sizeof(dwarf_sleb128_t) * 8))
		result |= -((dwarf_sleb128_t)1 << shift);
	*ptext = text;
	return result;
}

__LOCAL __ATTR_NONNULL((1)) dwarf_uleb128_t
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_uleb128)(__byte_t **__restrict ptext) {
	/* TODO: Make this one an external in-library function! */
	__byte_t byte,*text = *ptext;
	unsigned int shift = 0;
	dwarf_uleb128_t result = 0;
	for (;;) {
		byte    = *text++;
		result |= ((byte & 0x7f) << shift);
		shift  += 7;
		if __untraced(!(byte & 0x80))
			break;
	}
	*ptext = text;
	return result;
}


__LOCAL __ATTR_NONNULL((1)) __uintptr_t
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_pointer)(__byte_t **__restrict preader,
                                                    __uint8_t encoding,
                                                    __uint8_t addrsize,
                                                    __uintptr_t textbase,
                                                    __uintptr_t database,
                                                    __uintptr_t funcbase) {
	/* TODO: Make this one an external in-library function! */
	__uintptr_t result;
	__byte_t *text = *preader;
	/* Relative encoding formats. */
	switch (encoding & 0x70) {

	case DW_EH_PE_pcrel:
		result = (__uintptr_t)text; /* Relative to here. */
		break;

	case DW_EH_PE_textrel:
		result = textbase;
		break;

	case DW_EH_PE_datarel:
		result = database;
		break;

	case DW_EH_PE_funcrel:
		result = funcbase;
		break;

	case DW_EH_PE_aligned:
		text   = (__byte_t *)(((__uintptr_t)text + (addrsize - 1)) & ~(addrsize - 1));
		result = 0;
		break;

	default:
	case DW_EH_PE_absptr:
		result = 0;
		break;
	}
	switch (encoding & 0xf) {

	case DW_EH_PE_absptr:
		if __untraced(addrsize >= sizeof(__uintptr_t)) {
			result += __hybrid_unaligned_get((__uintptr_t *)text);
#if __SIZEOF_POINTER__ > 4
		} else if __untraced(addrsize >= 4) {
			result += __hybrid_unaligned_get32((__uint32_t *)text);
#endif
		} else if __untraced(addrsize >= 2) {
			result += __hybrid_unaligned_get16((__uint16_t *)text);
		} else if __untraced(addrsize >= 1) {
			result += *(__uint8_t *)text;
		}
		text += addrsize;
		break;

	case DW_EH_PE_udata2:
		result += __hybrid_unaligned_get16((__uint16_t *)text);
		text += 2;
		break;

	case DW_EH_PE_udata4:
		result += __hybrid_unaligned_get32((__uint32_t *)text);
		text += 4;
		break;

	case DW_EH_PE_udata8:
#if __SIZEOF_POINTER__ > 4
		result += __hybrid_unaligned_get64((__uint64_t *)text);
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		result += __hybrid_unaligned_get32((__uint32_t *)text);
#else
		result += __hybrid_unaligned_get32((__uint32_t *)text + 1);
#endif
		text += 8;
		break;

	case DW_EH_PE_sdata2:
		result += (__int16_t)__hybrid_unaligned_get16((__uint16_t *)text);
		text += 2;
		break;

	case DW_EH_PE_sdata4:
		result += (__int32_t)__hybrid_unaligned_get32((__uint32_t *)text);
		text += 4;
		break;

	case DW_EH_PE_sdata8:
#if __SIZEOF_POINTER__ > 4
		result += (__int64_t)__hybrid_unaligned_get64((__uint64_t *)text);
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		result += (__int32_t)__hybrid_unaligned_get32((__uint32_t *)text);
#else
		result += (__int32_t)__hybrid_unaligned_get32((__uint32_t *)text + 1);
#endif
		text += 8;
		break;

	case DW_EH_PE_uleb128:
		result += dwarf_decode_uleb128(&text);
		break;

	case DW_EH_PE_sleb128:
		result += dwarf_decode_sleb128(&text);
		break;

	default:
		text += 1; /* ??? */
		break;
	}
	if __untraced(encoding & DW_EH_PE_indirect) {
		if __untraced(addrsize >= sizeof(__uintptr_t)) {
			result = __hybrid_unaligned_get((__uintptr_t *)result);
#if __SIZEOF_POINTER__ > 4
		} else if __untraced(addrsize >= 4) {
			result = __hybrid_unaligned_get32((__uint32_t *)result);
#endif
		} else if __untraced(addrsize >= 2) {
			result = __hybrid_unaligned_get16((__uint16_t *)result);
		} else if __untraced(addrsize >= 1) {
			result = *(__uint8_t *)result;
		}
	}
	*preader = text;
	return result;
}



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DWARF_H */
