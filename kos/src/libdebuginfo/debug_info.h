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
#ifndef GUARD_LIBDEBUGINFO_DEBUG_INFO_H
#define GUARD_LIBDEBUGINFO_DEBUG_INFO_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>
#include <stdbool.h>
#include <stddef.h>

#include <libdebuginfo/debug_info.h>

DECL_BEGIN

/* Initialize an iterator for enumerating ranges stored within a given debug_info range selector.
 * >> uintptr_t start_pc, end_pc;
 * >> di_debuginfo_ranges_iterator_t iter;
 * >> di_debuginfo_ranges_iterator_init(&iter, ...);
 * >> while (di_debuginfo_ranges_iterator_next(&iter, &start_pc, &end_pc)) {
 * >>     ...
 * >> }
 * @param: debug_ranges_start: Starting address of the `.debug_ranges' section.
 * @param: debug_ranges_end:   End address of the `.debug_ranges' section. */
INTDEF NONNULL((1, 2, 3, 5, 6)) void
NOTHROW_NCX(CC libdi_debuginfo_ranges_iterator_init)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                     di_debuginfo_ranges_t const *__restrict ranges,
                                                     di_debuginfo_cu_parser_t const *__restrict parser,
                                                     uintptr_t cu_base,
                                                     byte_t const *__restrict debug_ranges_start,
                                                     byte_t const *__restrict debug_ranges_end);

/* Yield the next range accessible through a given debug-ranges iterator. */
INTDEF NONNULL((1, 2, 3)) bool
NOTHROW_NCX(CC libdi_debuginfo_ranges_iterator_next)(di_debuginfo_ranges_iterator_t *__restrict self,
                                                     uintptr_t *__restrict pmodule_relative_start_pc,
                                                     uintptr_t *__restrict pmodule_relative_end_pc);

/* Check if a given `module_relative_pc' is apart of the given range selector.
 * @param: self: The ranges object to query for `module_relative_pc' */
INTDEF NONNULL((1, 2, 5, 6)) unsigned int
NOTHROW_NCX(CC libdi_debuginfo_ranges_contains)(di_debuginfo_ranges_t const *__restrict self,
                                                di_debuginfo_cu_parser_t const *__restrict parser,
                                                uintptr_t cu_base,
                                                uintptr_t module_relative_pc,
                                                byte_t const *__restrict debug_ranges_start,
                                                byte_t const *__restrict debug_ranges_end);
INTDEF NONNULL((1, 2, 5, 6, 7, 8)) unsigned int
NOTHROW_NCX(CC libdi_debuginfo_ranges_contains_ex)(di_debuginfo_ranges_t const *__restrict self,
                                                   di_debuginfo_cu_parser_t const *__restrict parser,
                                                   uintptr_t cu_base,
                                                   uintptr_t module_relative_pc,
                                                   byte_t const *__restrict debug_ranges_start,
                                                   byte_t const *__restrict debug_ranges_end,
                                                   uintptr_t *__restrict poverlap_start,
                                                   uintptr_t *__restrict poverlap_end);


#define debuginfo_cu_parser_skipform(...) \
	libdi_debuginfo_cu_parser_skipform(__VA_ARGS__)

/* Given  a pointer to the start of a  debug_info CU (or a pointer to the start
 * of the .debug_info section), as well as the start & end of the .debug_abbrev
 * section, initialize the  given debuginfo CU  parser structure `result',  and
 * advance `*pdebug_info_reader' to the start of the next unit.
 * NOTE: Upon success (return == DEBUG_INFO_ERROR_SUCCESS), the caller is responsible for
 *       finalizing the given `abbrev' through use of `debuginfo_cu_abbrev_fini(abbrev)',
 *       once the associated parser `result' is no longer being used.
 * @param: first_component_pointer: A pointer to the first component to load, or `NULL'
 *                                  to simply load  the first  component following  the
 *                                  start of the associated CU descriptor.
 * @return: DEBUG_INFO_ERROR_SUCCESS: ...
 * @return: DEBUG_INFO_ERROR_NOFRAME: All units have been loaded.
 * @return: DEBUG_INFO_ERROR_CORRUPT: ... */
INTDEF NONNULL((1, 2, 3, 4, 5)) unsigned int
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadunit)(byte_t const **__restrict pdebug_info_reader,
                                                   byte_t const *__restrict debug_info_end,
                                                   di_debuginfo_cu_parser_sections_t const *__restrict sectinfo,
                                                   di_debuginfo_cu_parser_t *__restrict result,
                                                   di_debuginfo_cu_abbrev_t *__restrict abbrev,
                                                   byte_t const *first_component_pointer);


/* Finalize the given abbreviation code controller. */
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libdi_debuginfo_cu_abbrev_fini)(di_debuginfo_cu_abbrev_t *__restrict self);


/* Skip data associated with the given attribute form.
 * @param: form: One of `DW_FORM_*' */
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libdi_debuginfo_cu_parser_skipform)(di_debuginfo_cu_parser_t *__restrict self,
                                                   dwarf_uleb128_t form);

/* Start a new component.
 * @return: true:  ...
 * @return: false: [debuginfo_cu_parser_next] All components have been parsed.
 * @return: false: [*] The next component doesn't exist, or isn't a child/sibling/parent. */
INTDEF NONNULL((1)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_next)(di_debuginfo_cu_parser_t *__restrict self);
INTDEF NONNULL((1)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_nextchild)(di_debuginfo_cu_parser_t *__restrict self);
INTDEF NONNULL((1)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_nextsibling)(di_debuginfo_cu_parser_t *__restrict self);
INTDEF NONNULL((1)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_nextparent)(di_debuginfo_cu_parser_t *__restrict self);

/* Same as `libdi_debuginfo_cu_parser_next()', but store a pointer to the
 * debug information start location of  the next componet within  `*pdip' */
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_next_with_dip)(di_debuginfo_cu_parser_t *__restrict self, byte_t const **__restrict pdip);

/* Skip the attributes  of the  current component  (must be  called if  not
 * parsed explicitly prior to the next call to `debuginfo_cu_parser_next*') */
INTDEF NONNULL((1)) void NOTHROW_NCX(CC libdi_debuginfo_cu_parser_skipattr)(di_debuginfo_cu_parser_t *__restrict self);

/* Load the current debug information as an attribute encoded  as
 * `form' into a storage class matching the given result-operand.
 *  - debuginfo_cu_parser_getstring(): DW_FORM_strp, DW_FORM_string
 *  - debuginfo_cu_parser_getaddr():   DW_FORM_addr
 *  - debuginfo_cu_parser_getconst():  DW_FORM_data1, DW_FORM_data2, DW_FORM_data4, DW_FORM_data8, DW_FORM_sdata, DW_FORM_udata, DW_FORM_sec_offset
 *  - debuginfo_cu_parser_getflag():   DW_FORM_flag, DW_FORM_flag_present
 *  - debuginfo_cu_parser_getref():    DW_FORM_ref_addr, DW_FORM_ref1, DW_FORM_ref2, DW_FORM_ref4, DW_FORM_ref8, DW_FORM_ref_sig8, DW_FORM_ref_udata
 *  - debuginfo_cu_parser_getexpr():   DW_FORM_exprloc
 *  - debuginfo_cu_parser_getblock():  DW_FORM_block, DW_FORM_block1, DW_FORM_block2, DW_FORM_block4 */
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getstring)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, char const **__restrict presult);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getaddr)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, uintptr_t *__restrict presult);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getconst)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, uintptr_t *__restrict presult);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getflag)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, bool *__restrict presult);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getref)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, byte_t const **__restrict presult);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getexpr)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, di_debuginfo_location_t *__restrict result);
INTDEF NONNULL((1, 3)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_getblock)(di_debuginfo_cu_parser_t const *__restrict self, uintptr_t form, di_debuginfo_block_t *__restrict result);


/* Load attributes specific to a certain component:
 *   - debuginfo_cu_parser_loadattr_compile_unit():        DW_TAG_compile_unit
 *   - debuginfo_cu_parser_loadattr_compile_unit_simple(): DW_TAG_compile_unit
 *   - debuginfo_cu_parser_loadattr_subprogram():          DW_TAG_subprogram
 *   - debuginfo_cu_parser_loadattr_inlined_subroutine():  DW_TAG_inlined_subroutine
 *   - debuginfo_cu_parser_loadattr_lexical_block():       DW_TAG_lexical_block, DW_TAG_try_block, DW_TAG_catch_block
 *   - debuginfo_cu_parser_loadattr_type():                DW_TAG_*_type
 *   - debuginfo_cu_parser_loadattr_member():              DW_TAG_member
 *   - debuginfo_cu_parser_loadattr_variable():            DW_TAG_variable, DW_TAG_formal_parameter
 * @return: true:  Successfully loaded the component attributes.
 * @return: false: Corrupted/incomplete attributes. */
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_compile_unit)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_compile_unit_simple)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_compile_unit_simple_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_subprogram)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_subprogram_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_inlined_subroutine)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_inlined_subroutine_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_lexical_block)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_lexical_block_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_type)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_type_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_member)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_member_t *__restrict result);
INTDEF NONNULL((1, 2)) bool NOTHROW_NCX(CC libdi_debuginfo_cu_parser_loadattr_variable)(di_debuginfo_cu_parser_t *__restrict self, di_debuginfo_variable_t *__restrict result);


/* Print the C/C++-like representation of a given value, given DWARF debug information
 * about  its typing, where `parser' must have been  set up to have already loaded the
 * given `type' component for the given data blob:
 * >> di_debuginfo_variable_t var;
 * >> ... // Load `var'
 * >> {
 * >>     di_debuginfo_cu_parser_t pp = parser;
 * >>     di_debuginfo_type_t typ;
 * >>     void *buffer;
 * >>
 * >>     // Load type information for the variable.
 * >>     pp.dup_cu_info_pos = var.v_type;
 * >>     debuginfo_cu_parser_loadattr_type(&pp, &typ);
 * >>
 * >>     // Load the value of this variable.
 * >>     buffer = malloca(typ.t_sizeof);
 * >>     size_t num_written_bits;
 * >>     debuginfo_location_getvalue(&var.v_location,
 * >>                                 <sections>,
 * >>                                 &<get_register>,
 * >>                                 &<registers>,
 * >>                                 &<cu>,
 * >>                                 module_relative_pc,
 * >>                                 buffer,
 * >>                                 typ.t_sizeof,
 * >>                                 &num_written_bits,
 * >>                                 &<sp>->sp_frame_base,
 * >>                                 NULL,
 * >>                                 parser->dup_addrsize,
 * >>                                 parser->dup_ptrsize);
 * >>
 * >>     // Print a representation of the variable, and its data.
 * >>     debuginfo_print_value(printer, arg, &pp, &type, v.v_name, buffer, typ.t_sizeof);
 * >> }
 * @param: varname: Name of the value (when NULL, print as a cast-like expression;
 *                  otherwise, print as an declaration)
 * @param: flags:   Set of `DEBUGINFO_PRINT_VALUE_F*' */
INTDEF NONNULL((1, 3, 4, 6)) ssize_t CC
libdi_debuginfo_print_value(pformatprinter printer, void *arg,
                            di_debuginfo_cu_parser_t const *__restrict parser,
                            di_debuginfo_type_t const *__restrict type,
                            char const *varname, void const *__restrict data,
                            size_t datasize, size_t newline_indentation,
                            debuginfo_print_format_t format_printer,
                            void *format_arg, unsigned int flags);
INTDEF NONNULL((1, 3, 4)) ssize_t CC
libdi_debuginfo_print_typename(pformatprinter printer, void *arg,
                               di_debuginfo_cu_parser_t const *__restrict parser,
                               di_debuginfo_type_t const *__restrict type,
                               char const *varname,
                               debuginfo_print_format_t format_printer,
                               void *format_arg);


/* Enumerate all local variables visible at a given source location
 * @return: >= 0: The sum of all invocations of `*callback'.
 * @return: <  0: The first negative return value of `*callback'. */
INTDEF NONNULL((1, 3)) ssize_t CC
libdi_debuginfo_enum_locals(di_enum_locals_sections_t const *__restrict sectinfo,
                            uintptr_t module_relative_pc,
                            debuginfo_enum_locals_callback_t callback, void *arg);


INTDEF NONNULL((2, 3)) void
NOTHROW_NCX(CC libdi_debug_sections_lock)(module_t *dl_handle,
                                          di_debug_sections_t *__restrict sections,
                                          di_debug_dl_sections_t *__restrict dl_sections);
INTDEF NONNULL((1)) void
NOTHROW_NCX(CC libdi_debug_sections_unlock)(di_debug_dl_sections_t *__restrict dl_sections);


DECL_END

#endif /* !GUARD_LIBDEBUGINFO_DEBUG_INFO_H */
