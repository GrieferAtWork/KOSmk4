/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBDEBUGINFO_DWARF_H
#define _LIBDEBUGINFO_DWARF_H 1

#include "api.h"

/* NOTE: The DWARF implementation here is based on information gathered
 *       from  binutils,  but  mostly  from  the  online specifications
 *  - "http://www.dwarfstd.org/doc/DWARF4.pdf", section 6.2
 *  - "http://www.dwarfstd.org/doc/DWARF5.pdf", section 6.2
 *
 * SOURCES:
 *   - http://www.dwarfstd.org/doc/DWARF4.pdf
 *   - http://www.dwarfstd.org/doc/DWARF5.pdf
 *   - http://www.dwarfstd.org/doc/dwarf-2.0.0.pdf
 *   - https://sourceware.org/elfutils/DwarfExtensions
 *
 */



/* Possible values for `di_debugline_fileinfo_format_entry_t::' */
#define DW_LNCT_path            0x1 /* DW_FORM_*: string */
#define DW_LNCT_directory_index 0x2 /* DW_FORM_*: constant */
#define DW_LNCT_timestamp       0x3 /* DW_FORM_*: constant, block */
#define DW_LNCT_size            0x4 /* DW_FORM_*: constant */
#define DW_LNCT_MD5             0x5 /* DW_FORM_*: constant (DW_FORM_data16) */
#define DW_LNCT_lo_user         0x2000
#define DW_LNCT_hi_user         0x3fff


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

/*      DW_LNE_                            0x00 */
#define DW_LNE_end_sequence                0x01
#define DW_LNE_set_address                 0x02
#define DW_LNE_define_file                 0x03
#define DW_LNE_set_discriminator           0x04
/*      DW_LNE_                            0x05 */
/*      DW_LNE_                            0x06 */
/*      DW_LNE_                            0x07 */
/*      DW_LNE_                            0x08 */
/*      DW_LNE_                            0x09 */
/*      DW_LNE_                            0x0a */
/*      DW_LNE_                            0x0b */
/*      DW_LNE_                            0x0c */
/*      DW_LNE_                            0x0d */
/*      DW_LNE_                            0x0e */
/*      DW_LNE_                            0x0f */
/*      DW_LNE_                            0x10 */
#define DW_LNE_HP_negate_is_UV_update      0x11
#define DW_LNE_HP_push_context             0x12
#define DW_LNE_HP_pop_context              0x13
#define DW_LNE_HP_set_file_line_column     0x14
#define DW_LNE_HP_set_routine_name         0x15
#define DW_LNE_HP_set_sequence             0x16
#define DW_LNE_HP_negate_post_semantics    0x17
#define DW_LNE_HP_negate_function_exit     0x18
#define DW_LNE_HP_negate_front_end_logical 0x19
/*      DW_LNE_                            0x1a */
/*      DW_LNE_                            0x1b */
/*      DW_LNE_                            0x1c */
/*      DW_LNE_                            0x1d */
/*      DW_LNE_                            0x1e */
/*      DW_LNE_                            0x1f */
#define DW_LNE_HP_define_proc              0x20
/*      DW_LNE_                            0x21 */
/*      DW_LNE_                            .... */
/*      DW_LNE_                            0x7f */
#define DW_LNE_HP_source_file_correlation  0x80
#define DW_LNE_lo_user                     0x80
#define DW_LNE_hi_user                     0xff

#define DW_LNE_HP_SFC_formfeed         1
#define DW_LNE_HP_SFC_set_listing_line 2
#define DW_LNE_HP_SFC_associate        3


/* DWARF .debug_info component tags. */
#define DW_TAG_padding                0x00 /* - */
#define DW_TAG_array_type             0x01
#define DW_TAG_class_type             0x02
#define DW_TAG_entry_point            0x03
#define DW_TAG_enumeration_type       0x04
#define DW_TAG_formal_parameter       0x05
/*      DW_TAG_                       0x06 */
/*      DW_TAG_                       0x07 */
#define DW_TAG_imported_declaration   0x08
/*      DW_TAG_                       0x09 */
#define DW_TAG_label                  0x0a
#define DW_TAG_lexical_block          0x0b
/*      DW_TAG_                       0x0c */
#define DW_TAG_member                 0x0d
/*      DW_TAG_                       0x0e */
#define DW_TAG_pointer_type           0x0f
#define DW_TAG_reference_type         0x10
#define DW_TAG_compile_unit           0x11
#define DW_TAG_string_type            0x12
#define DW_TAG_structure_type         0x13
/*      DW_TAG_                       0x14 */
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
/*      DW_TAG_                       0x3e */
#define DW_TAG_condition              0x3f
#define DW_TAG_shared_type            0x40
#define DW_TAG_type_unit              0x41
#define DW_TAG_rvalue_reference_type  0x42
#define DW_TAG_template_alias         0x43
#define DW_TAG_coarray_type           0x44
#define DW_TAG_generic_subrange       0x45
#define DW_TAG_dynamic_type           0x46
#define DW_TAG_atomic_type            0x47
#define DW_TAG_call_site              0x48
#define DW_TAG_call_site_parameter    0x49
#define DW_TAG_skeleton_unit          0x4a
#define DW_TAG_immutable_type         0x4b
/*      DW_TAG_                       0x4c */
/*      DW_TAG_                       0x4d */
/*      DW_TAG_                       0x4e */
/*      DW_TAG_                       0x4f */
/*      DW_TAG_                       ... */
#define DW_TAG_lo_user                0x4080
#define DW_TAG_hi_user                0xffff

/* Extension tags */
#define DW_TAG_MIPS_loop                   0x4081
#define DW_TAG_HP_array_descriptor         0x4090
#define DW_TAG_HP_Bliss_field              0x4091
#define DW_TAG_HP_Bliss_field_set          0x4092
#define DW_TAG_format_label                0x4101
#define DW_TAG_function_template           0x4102
#define DW_TAG_class_template              0x4103
#define DW_TAG_GNU_BINCL                   0x4104
#define DW_TAG_GNU_EINCL                   0x4105
#define DW_TAG_GNU_template_template_param 0x4106
#define DW_TAG_GNU_template_parameter_pack 0x4107
#define DW_TAG_GNU_formal_parameter_pack   0x4108
#define DW_TAG_GNU_call_site               0x4109 /* (alias: DW_TAG_call_site) */
#define DW_TAG_GNU_call_site_parameter     0x410a /* (alias: DW_TAG_call_site_parameter) */
#define DW_TAG_upc_shared_type             0x8765
#define DW_TAG_upc_strict_type             0x8766
#define DW_TAG_upc_relaxed_type            0x8767
#define DW_TAG_PGI_kanji_type              0xa000
#define DW_TAG_PGI_interface_block         0xa020

/* Helpers for testing or casing for certain tags and aliases. */
#define DW_IS_TAG_call_site(tag)      \
	((tag) == DW_TAG_GNU_call_site || \
	 (tag) == DW_TAG_call_site)
#define DW_CASE_TAG_call_site  \
	case DW_TAG_GNU_call_site: \
	case DW_TAG_call_site
#define DW_IS_TAG_call_site_parameter(tag)      \
	((tag) == DW_TAG_GNU_call_site_parameter || \
	 (tag) == DW_TAG_call_site_parameter)
#define DW_CASE_TAG_call_site_parameter  \
	case DW_TAG_GNU_call_site_parameter: \
	case DW_TAG_call_site_parameter

/* Possible values for `di_debuginfo_component_t::dic_haschildren' */
#define DW_CHILDREN_no  0
#define DW_CHILDREN_yes 1

/* DWARF .debug_info component attribute names. */
/*      DW_AT_                        0x00  * ... */
#define DW_AT_sibling                 0x01 /* reference */
#define DW_AT_location                0x02 /* block, constant */
#define DW_AT_name                    0x03 /* string */
/*      DW_AT_                        0x04  * ... */
/*      DW_AT_                        0x05  * ... */
/*      DW_AT_                        0x06  * ... */
/*      DW_AT_                        0x07  * ... */
/*      DW_AT_                        0x08  * ... */
#define DW_AT_ordering                0x09 /* constant */
#define DW_AT_subscr_data             0x0a /* ??? */
/*      DW_AT_                        0x0a  * ... */
#define DW_AT_byte_size               0x0b /* constant */
#define DW_AT_bit_offset              0x0c /* constant */
#define DW_AT_bit_size                0x0d /* constant */
/*      DW_AT_                        0x0e  * ... */
/*      DW_AT_                        0x0f  * ... */
#define DW_AT_element_list            0x0f /* ??? */
#define DW_AT_stmt_list               0x10 /* constant */
#define DW_AT_low_pc                  0x11 /* address */
#define DW_AT_high_pc                 0x12 /* address, constant */
#define DW_AT_language                0x13 /* constant */
#define DW_AT_member                  0x14 /* ??? */
#define DW_AT_discr                   0x15 /* reference */
#define DW_AT_discr_value             0x16 /* constant */
#define DW_AT_visibility              0x17 /* constant */
#define DW_AT_import                  0x18 /* reference */
#define DW_AT_string_length           0x19 /* block, constant */
#define DW_AT_common_reference        0x1a /* reference */
#define DW_AT_comp_dir                0x1b /* string */
#define DW_AT_const_value             0x1c /* string, constant, block */
#define DW_AT_containing_type         0x1d /* reference */
#define DW_AT_default_value           0x1e /* reference */
/*      DW_AT_                        0x1f  * ... */
#define DW_AT_inline                  0x20 /* constant */
#define DW_AT_is_optional             0x21 /* flag */
#define DW_AT_lower_bound             0x22 /* constant, reference */
/*      DW_AT_                        0x23  * ... */
/*      DW_AT_                        0x24  * ... */
#define DW_AT_producer                0x25 /* string */
/*      DW_AT_                        0x26  * ... */
#define DW_AT_prototyped              0x27 /* flag */
/*      DW_AT_                        0x28  * ... */
/*      DW_AT_                        0x29  * ... */
#define DW_AT_return_addr             0x2a /* block, constant */
/*      DW_AT_                        0x2b  * ... */
#define DW_AT_start_scope             0x2c /* constant */
/*      DW_AT_                        0x2d  * ... */
#define DW_AT_bit_stride              0x2e /* constant (alias: DW_AT_stride_size) */
#define DW_AT_stride_size             0x2e /* constant */
#define DW_AT_upper_bound             0x2f /* constant, reference */
/*      DW_AT_                        0x30  * ... */
#define DW_AT_abstract_origin         0x31 /* reference */
#define DW_AT_accessibility           0x32 /* constant */
#define DW_AT_address_class           0x33 /* constant */
#define DW_AT_artificial              0x34 /* flag */
#define DW_AT_base_types              0x35 /* reference */
#define DW_AT_calling_convention      0x36 /* constant */
#define DW_AT_count                   0x37 /* constant, reference */
#define DW_AT_data_member_location    0x38 /* constant, block, reference */
#define DW_AT_decl_column             0x39 /* constant */
#define DW_AT_decl_file               0x3a /* constant */
#define DW_AT_decl_line               0x3b /* constant */
#define DW_AT_declaration             0x3c /* flag */
#define DW_AT_discr_list              0x3d /* block */
#define DW_AT_encoding                0x3e /* constant */
#define DW_AT_external                0x3f /* flag */
#define DW_AT_frame_base              0x40 /* block, constant */
#define DW_AT_friend                  0x41 /* reference */
#define DW_AT_identifier_case         0x42 /* constant */
#define DW_AT_macro_info              0x43 /* constant */
#define DW_AT_namelist_items          0x44 /* block (alias: DW_AT_namelist_item) */
#define DW_AT_namelist_item           0x44 /* block */
#define DW_AT_priority                0x45 /* reference */
#define DW_AT_segment                 0x46 /* block, constant */
#define DW_AT_specification           0x47 /* reference */
#define DW_AT_static_link             0x48 /* block, constant */
#define DW_AT_type                    0x49 /* reference */
#define DW_AT_use_location            0x4a /* block, constant */
#define DW_AT_variable_parameter      0x4b /* flag */
#define DW_AT_virtuality              0x4c /* constant */
#define DW_AT_vtable_elem_location    0x4d /* block, reference */
#define DW_AT_allocated               0x4e /* constant, exprloc, reference */
#define DW_AT_associated              0x4f /* constant, exprloc, reference */
#define DW_AT_data_location           0x50 /* exprloc */
#define DW_AT_byte_stride             0x51 /* constant, exprloc, reference */
#define DW_AT_entry_pc                0x52 /* address */
#define DW_AT_use_UTF8                0x53 /* flag */
#define DW_AT_extension               0x54 /* reference */
#define DW_AT_ranges                  0x55 /* rangelistptr */
#define DW_AT_trampoline              0x56 /* address, flag, reference, string */
#define DW_AT_call_column             0x57 /* constant */
#define DW_AT_call_file               0x58 /* constant */
#define DW_AT_call_line               0x59 /* constant */
#define DW_AT_description             0x5a /* string */
#define DW_AT_binary_scale            0x5b /* constant */
#define DW_AT_decimal_scale           0x5c /* constant */
#define DW_AT_small                   0x5d /* reference */
#define DW_AT_decimal_sign            0x5e /* constant */
#define DW_AT_digit_count             0x5f /* constant */
#define DW_AT_picture_string          0x60 /* string */
#define DW_AT_mutable                 0x61 /* flag */
#define DW_AT_threads_scaled          0x62 /* flag */
#define DW_AT_explicit                0x63 /* flag */
#define DW_AT_object_pointer          0x64 /* reference */
#define DW_AT_endianity               0x65 /* constant */
#define DW_AT_elemental               0x66 /* flag */
#define DW_AT_pure                    0x67 /* flag */
#define DW_AT_recursive               0x68 /* flag */
#define DW_AT_signature               0x69 /* reference */
#define DW_AT_main_subprogram         0x6a /* flag */
#define DW_AT_data_bit_offset         0x6b /* constant */
#define DW_AT_const_expr              0x6c /* flag */
#define DW_AT_enum_class              0x6d /* flag */
#define DW_AT_linkage_name            0x6e /* string */
#define DW_AT_string_length_bit_size  0x6f /* constant */
#define DW_AT_string_length_byte_size 0x70 /* constant */
#define DW_AT_rank                    0x71 /* constant, exprloc */
#define DW_AT_str_offsets_base        0x72 /* stroffsetsptr */
#define DW_AT_addr_base               0x73 /* addrptr */
#define DW_AT_rnglists_base           0x74 /* rnglistsptr */
/*      DW_AT_                        0x75  * ... */
#define DW_AT_dwo_name                0x76 /* string */
#define DW_AT_reference               0x77 /* flag */
#define DW_AT_rvalue_reference        0x78 /* flag */
#define DW_AT_macros                  0x79 /* macptr */
#define DW_AT_call_all_calls          0x7a /* flag */
#define DW_AT_call_all_source_calls   0x7b /* flag */
#define DW_AT_call_all_tail_calls     0x7c /* flag */
#define DW_AT_call_return_pc          0x7d /* address */
#define DW_AT_call_value              0x7e /* exprloc */
#define DW_AT_call_origin             0x7f /* exprloc */
#define DW_AT_call_parameter          0x80 /* reference */
#define DW_AT_call_pc                 0x81 /* ??? */
#define DW_AT_call_tail_call          0x82 /* ??? */
#define DW_AT_call_target             0x83 /* ??? */
#define DW_AT_call_target_clobbered   0x84 /* ??? */
#define DW_AT_call_data_location      0x85 /* ??? */
#define DW_AT_call_data_value         0x86 /* ??? */
#define DW_AT_noreturn                0x87 /* flag */
#define DW_AT_alignment               0x88 /* ??? */
#define DW_AT_export_symbols          0x89 /* ??? */
#define DW_AT_deleted                 0x8a /* ??? */
#define DW_AT_defaulted               0x8b /* ??? */
#define DW_AT_loclists_base           0x8c /* ??? */
/*      DW_AT_                        0x8d  * ... */
/*      DW_AT_                        ....  * ... */
#define DW_AT_lo_user                 0x2000 /* - */
#define DW_AT_hi_user                 0x3fff /* - */

/* Extensions. */
#define DW_AT_HP_block_index                 0x2000 /* ??? */
#define DW_AT_MIPS_fde                       0x2001 /* ??? */
#define DW_AT_HP_unmodifiable                0x2001 /* ??? */
#define DW_AT_MIPS_loop_begin                0x2002 /* ??? */
#define DW_AT_MIPS_tail_loop_begin           0x2003 /* ??? */
#define DW_AT_MIPS_epilog_begin              0x2004 /* ??? */
#define DW_AT_MIPS_loop_unroll_factor        0x2005 /* ??? */
#define DW_AT_HP_prologue                    0x2005 /* ??? */
#define DW_AT_MIPS_software_pipeline_depth   0x2006 /* ??? */
#define DW_AT_MIPS_linkage_name              0x2007 /* ??? */
#define DW_AT_MIPS_stride                    0x2008 /* ??? */
#define DW_AT_HP_epilogue                    0x2008 /* ??? */
#define DW_AT_MIPS_abstract_name             0x2009 /* ??? */
#define DW_AT_MIPS_clone_origin              0x200a /* ??? */
#define DW_AT_MIPS_has_inlines               0x200b /* ??? */
#define DW_AT_MIPS_stride_byte               0x200c /* ??? */
#define DW_AT_MIPS_stride_elem               0x200d /* ??? */
#define DW_AT_MIPS_ptr_dopetype              0x200e /* ??? */
#define DW_AT_MIPS_allocatable_dopetype      0x200f /* ??? */
#define DW_AT_MIPS_assumed_shape_dopetype    0x2010 /* ??? */
#define DW_AT_HP_actuals_stmt_list           0x2010 /* ??? */
#define DW_AT_MIPS_assumed_size              0x2011 /* ??? */
#define DW_AT_HP_proc_per_section            0x2011 /* ??? */
#define DW_AT_HP_raw_data_ptr                0x2012 /* ??? */
#define DW_AT_HP_pass_by_reference           0x2013 /* ??? */
#define DW_AT_HP_opt_level                   0x2014 /* ??? */
#define DW_AT_HP_prof_version_id             0x2015 /* ??? */
#define DW_AT_HP_opt_flags                   0x2016 /* ??? */
#define DW_AT_HP_cold_region_low_pc          0x2017 /* ??? */
#define DW_AT_HP_cold_region_high_pc         0x2018 /* ??? */
#define DW_AT_HP_all_variables_modifiable    0x2019 /* ??? */
#define DW_AT_HP_linkage_name                0x201a /* ??? */
#define DW_AT_HP_prof_flags                  0x201b /* ??? */
#define DW_AT_HP_unit_name                   0x201f /* ??? */
#define DW_AT_HP_unit_size                   0x2020 /* ??? */
#define DW_AT_HP_widened_byte_size           0x2021 /* ??? */
#define DW_AT_HP_definition_points           0x2022 /* ??? */
#define DW_AT_HP_default_location            0x2023 /* ??? */
#define DW_AT_HP_is_result_param             0x2029 /* ??? */
#define DW_AT_sf_names                       0x2101 /* ??? */
#define DW_AT_src_info                       0x2102 /* ??? */
#define DW_AT_mac_info                       0x2103 /* ??? */
#define DW_AT_src_coords                     0x2104 /* ??? */
#define DW_AT_body_begin                     0x2105 /* ??? */
#define DW_AT_body_end                       0x2106 /* ??? */
#define DW_AT_GNU_vector                     0x2107 /* ??? */
#define DW_AT_GNU_guarded_by                 0x2108 /* ??? */
#define DW_AT_GNU_pt_guarded_by              0x2109 /* ??? */
#define DW_AT_GNU_guarded                    0x210a /* ??? */
#define DW_AT_GNU_pt_guarded                 0x210b /* ??? */
#define DW_AT_GNU_locks_excluded             0x210c /* ??? */
#define DW_AT_GNU_exclusive_locks_required   0x210d /* ??? */
#define DW_AT_GNU_shared_locks_required      0x210e /* ??? */
#define DW_AT_GNU_odr_signature              0x210f /* ??? */
#define DW_AT_GNU_template_name              0x2110 /* ??? */
#define DW_AT_GNU_call_site_value            0x2111 /* exprloc  (same as `DW_AT_call_value') */
#define DW_AT_GNU_call_site_data_value       0x2112 /* exprloc  (same as `DW_AT_call_data_value') */
#define DW_AT_GNU_call_site_target           0x2113 /* ??? */
#define DW_AT_GNU_call_site_target_clobbered 0x2114 /* ??? */
#define DW_AT_GNU_tail_call                  0x2115 /* ??? */
#define DW_AT_GNU_all_tail_call_sites        0x2116 /* ??? */
#define DW_AT_GNU_all_call_sites             0x2117 /* ??? */
#define DW_AT_GNU_all_source_call_sites      0x2118 /* ??? */
#define DW_AT_GNU_macros                     0x2119 /* ??? */
#define DW_AT_GNU_deleted                    0x211a /* ??? */
#define DW_AT_GNU_dwo_name                   0x2130 /* ??? */
#define DW_AT_GNU_dwo_id                     0x2131 /* ??? */
#define DW_AT_GNU_ranges_base                0x2132 /* ??? */
#define DW_AT_GNU_addr_base                  0x2133 /* ??? */
#define DW_AT_GNU_pubnames                   0x2134 /* ??? */
#define DW_AT_GNU_pubtypes                   0x2135 /* ??? */
#define DW_AT_GNU_discriminator              0x2136 /* ??? */
#define DW_AT_GNU_locviews                   0x2137 /* ??? */
#define DW_AT_GNU_entry_view                 0x2138 /* ??? */
#define DW_AT_VMS_rtnbeg_pd_address          0x2201 /* ??? */
#define DW_AT_use_GNAT_descriptive_type      0x2301 /* ??? */
#define DW_AT_GNAT_descriptive_type          0x2302 /* ??? */
#define DW_AT_GNU_numerator                  0x2303 /* ??? */
#define DW_AT_GNU_denominator                0x2304 /* ??? */
#define DW_AT_GNU_bias                       0x2305 /* ??? */
#define DW_AT_upc_threads_scaled             0x3210 /* ??? */
#define DW_AT_PGI_lbase                      0x3a00 /* ??? */
#define DW_AT_PGI_soffset                    0x3a01 /* ??? */
#define DW_AT_PGI_lstride                    0x3a02 /* ??? */
#define DW_AT_APPLE_optimized                0x3fe1 /* ??? */
#define DW_AT_APPLE_flags                    0x3fe2 /* ??? */
#define DW_AT_APPLE_isa                      0x3fe3 /* ??? */
#define DW_AT_APPLE_block                    0x3fe4 /* ??? */
#define DW_AT_APPLE_major_runtime_vers       0x3fe5 /* ??? */
#define DW_AT_APPLE_runtime_class            0x3fe6 /* ??? */
#define DW_AT_APPLE_omit_frame_ptr           0x3fe7 /* ??? */
#define DW_AT_APPLE_property_name            0x3fe8 /* ??? */
#define DW_AT_APPLE_property_getter          0x3fe9 /* ??? */
#define DW_AT_APPLE_property_setter          0x3fea /* ??? */
#define DW_AT_APPLE_property_attribute       0x3feb /* ??? */
#define DW_AT_APPLE_objc_complete_type       0x3fec /* ??? */
#define DW_AT_APPLE_property                 0x3fed /* ??? */


/*      DW_LANG_                0x0000 */
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
/*      DW_LANG_                0x0015 */
#define DW_LANG_Go              0x0016
/*      DW_LANG_                0x0017 */
/*      DW_LANG_                0x0018 */
/*      DW_LANG_                0x0019 */
#define DW_LANG_C_plus_plus_11  0x001a
/*      DW_LANG_                0x001b */
/*      DW_LANG_                0x001c */
#define DW_LANG_C11             0x001d
/*      DW_LANG_                0x001e */
/*      DW_LANG_                0x001f */
/*      DW_LANG_                0x0020 */
#define DW_LANG_C_plus_plus_14  0x0021
#define DW_LANG_Fortran03       0x0022
#define DW_LANG_Fortran08       0x0023
/*      DW_LANG_                0x0024 */
/*      DW_LANG_                ...... */
#define DW_LANG_lo_user         0x8000
#define DW_LANG_hi_user         0xffff
#define DW_LANG_Mips_Assembler  0x8001
/*      DW_LANG_                0x8002 */
#define DW_LANG_HP_Bliss        0x8003
#define DW_LANG_HP_Basic91      0x8004
#define DW_LANG_HP_Pascal91     0x8005
#define DW_LANG_HP_IMacro       0x8006
#define DW_LANG_HP_Assembler    0x8007
#define DW_LANG_Upc             0x8765


/*      DW_FORM_               0x00  * ... */
#define DW_FORM_addr           0x01 /* address */
/*      DW_FORM_               0x02  * ... */
#define DW_FORM_block2         0x03 /* block */
#define DW_FORM_block4         0x04 /* block */
#define DW_FORM_data2          0x05 /* constant */
#define DW_FORM_data4          0x06 /* constant */
#define DW_FORM_data8          0x07 /* constant */
#define DW_FORM_string         0x08 /* string */
#define DW_FORM_block          0x09 /* block */
#define DW_FORM_block1         0x0a /* block */
#define DW_FORM_data1          0x0b /* constant */
#define DW_FORM_flag           0x0c /* flag */
#define DW_FORM_sdata          0x0d /* constant */
#define DW_FORM_strp           0x0e /* string */
#define DW_FORM_udata          0x0f /* constant */
#define DW_FORM_ref_addr       0x10 /* reference */
#define DW_FORM_ref1           0x11 /* reference */
#define DW_FORM_ref2           0x12 /* reference */
#define DW_FORM_ref4           0x13 /* reference */
#define DW_FORM_ref8           0x14 /* reference */
#define DW_FORM_ref_udata      0x15 /* reference */
#define DW_FORM_indirect       0x16 /* (see section 7.5.3) */
#define DW_FORM_sec_offset     0x17 /* lineptr, loclistptr, macptr, rangelistptr, addrptr, stroffsetsptr, rnglistsptr */
#define DW_FORM_exprloc        0x18 /* exprloc */
#define DW_FORM_flag_present   0x19 /* flag */
#define DW_FORM_strx           0x1a /* string */
#define DW_FORM_addrx          0x1b /* ??? */
#define DW_FORM_ref_sup4       0x1c /* ??? */
#define DW_FORM_strp_sup       0x1d /* string */
#define DW_FORM_data16         0x1e /* constant */
#define DW_FORM_line_strp      0x1f /* string */
#define DW_FORM_ref_sig8       0x20 /* reference */
#define DW_FORM_implicit_const 0x21 /* ??? */
#define DW_FORM_loclistx       0x22 /* ??? */
#define DW_FORM_rnglistx       0x23 /* ??? */
#define DW_FORM_ref_sup8       0x24 /* ??? */
#define DW_FORM_strx1          0x25 /* string */
#define DW_FORM_strx2          0x26 /* string */
#define DW_FORM_strx3          0x27 /* string */
#define DW_FORM_strx4          0x28 /* string */
#define DW_FORM_addrx1         0x29 /* ??? */
#define DW_FORM_addrx2         0x2a /* ??? */
#define DW_FORM_addrx3         0x2b /* ??? */
#define DW_FORM_addrx4         0x2c /* ??? */
/*      DW_FORM_               0x2d  * ... */
/*      DW_FORM_               0x2e  * ... */
/*      DW_FORM_               0x2f  * ... */
/*      DW_FORM_               ....  * ... */
#define DW_FORM_GNU_addr_index 0x1f01 /* ??? */
#define DW_FORM_GNU_str_index  0x1f02 /* ??? */
#define DW_FORM_GNU_ref_alt    0x1f20 /* ??? */
#define DW_FORM_GNU_strp_alt   0x1f21 /* ??? */


/* NOTE: Taken form `http://www.dwarfstd.org/doc/DWARF4.pdf' (Figure 13. Encoding attribute values) */
#define DW_ATE_void                   0x00 /* Nothing */
#define DW_ATE_address                0x01 /* linear machine address */
#define DW_ATE_boolean                0x02 /* true or false */
#define DW_ATE_complex_float          0x03 /* complex binary floating-point number */
#define DW_ATE_float                  0x04 /* binary floating-point number */
#define DW_ATE_signed                 0x05 /* signed binary integer */
#define DW_ATE_signed_char            0x06 /* signed character */
#define DW_ATE_unsigned               0x07 /* unsigned binary integer */
#define DW_ATE_unsigned_char          0x08 /* unsigned character */
#define DW_ATE_imaginary_float        0x09 /* imaginary binary floating-point number */
#define DW_ATE_packed_decimal         0x0a /* packed decimal */
#define DW_ATE_numeric_string         0x0b /* numeric string */
#define DW_ATE_edited                 0x0c /* edited string */
#define DW_ATE_signed_fixed           0x0d /* signed fixed-point scaled integer */
#define DW_ATE_unsigned_fixed         0x0e /* unsigned fixed-point scaled integer */
#define DW_ATE_decimal_float          0x0f /* decimal floating-point number */
#define DW_ATE_UTF                    0x10 /* Unicode character */
#define DW_ATE_UCS                    0x11 /* USC character */
#define DW_ATE_ASCII                  0x12 /* Ascii character */
/*      DW_ATE_                       0x13  * ... */
/*      DW_ATE_                       ....  * ... */
/*      DW_ATE_                       0x7f  * ... */
#define DW_ATE_lo_user                0x80
#define DW_ATE_HP_float80             0x80 /* 80-bit floating-point number. */
#define DW_ATE_HP_complex_float80     0x81 /* 80-bit floating-point complex number. */
#define DW_ATE_HP_float128            0x82 /* 128-bit floating-point number. */
#define DW_ATE_HP_complex_float128    0x83 /* 128-bit floating-point complex number. */
#define DW_ATE_HP_floathpintel        0x84 /* 82-bit IA64 floating-point number. */
#define DW_ATE_HP_imaginary_float80   0x85 /* 80-bit floating-point imaginary number. */
#define DW_ATE_HP_imaginary_float128  0x86 /* 128-bit floating-point imaginary number. */
#define DW_ATE_HP_VAX_float           0x88 /* ??? */
#define DW_ATE_HP_VAX_float_d         0x89 /* ??? */
#define DW_ATE_HP_packed_decimal      0x8a /* ??? */
#define DW_ATE_HP_zoned_decimal       0x8b /* ??? */
#define DW_ATE_HP_edited              0x8c /* ??? */
#define DW_ATE_HP_signed_fixed        0x8d /* ??? */
#define DW_ATE_HP_unsigned_fixed      0x8e /* ??? */
#define DW_ATE_HP_VAX_complex_float   0x8f /* ??? */
#define DW_ATE_HP_VAX_complex_float_d 0x90 /* ??? */
#define DW_ATE_hi_user                0xff


/* Possible values for `unit_type' in `.debug_info' */
#define DW_UT_compile       0x01
#define DW_UT_type          0x02
#define DW_UT_partial       0x03
#define DW_UT_skeleton      0x04
#define DW_UT_split_compile 0x05
#define DW_UT_split_type    0x06
#define DW_UT_lo_user       0x80
#define DW_UT_hi_user       0xff


#ifdef __CC__
#include "api.h"

#include <hybrid/int128.h>

#include <bits/types.h>

__DECL_BEGIN

/* Similar to the functions from `libunwind(3)', but these decode into a 64-bit integer! */
typedef __ATTR_RETNONNULL_T __ATTR_NONNULL_T((1, 2)) __byte_t const *
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDWARF_DECODE_SLEB128_64)(__byte_t const *__restrict reader,
                                                           __int64_t *__restrict p_result);
typedef __ATTR_RETNONNULL_T __ATTR_NONNULL_T((1, 2)) __byte_t const *
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDWARF_DECODE_ULEB128_64)(__byte_t const **__restrict preader,
                                                           __uint64_t *__restrict p_result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __byte_t const *
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_sleb128_64)(__byte_t const *__restrict reader,
                                                       __int64_t *__restrict p_result);
LIBDEBUGINFO_DECL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __byte_t const *
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_uleb128_64)(__byte_t const *__restrict reader,
                                                       __uint64_t *__restrict p_result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Similar to the functions from `libunwind(3)', but these actually decode into a 128-bit integer! */
typedef __ATTR_RETNONNULL_T __ATTR_NONNULL_T((1, 2)) __byte_t const *
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDWARF_DECODE_SLEB128_128)(__byte_t const *__restrict reader,
                                                            __hybrid_int128_t *__restrict p_result);
typedef __ATTR_RETNONNULL_T __ATTR_NONNULL_T((1, 2)) __byte_t const *
__NOTHROW_NCX_T(LIBDEBUGINFO_CC *PDWARF_DECODE_ULEB128_128)(__byte_t const **__restrict preader,
                                                            __hybrid_uint128_t *__restrict p_result);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __byte_t const *
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_sleb128_128)(__byte_t const *__restrict reader,
                                                        __hybrid_int128_t *__restrict p_result);
LIBDEBUGINFO_DECL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) __byte_t const *
__NOTHROW_NCX(LIBDEBUGINFO_CC dwarf_decode_uleb128_128)(__byte_t const *__restrict reader,
                                                        __hybrid_uint128_t *__restrict p_result);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */


#endif /* !_LIBDEBUGINFO_DWARF_H */
