/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBDEBUGINFO_DEBUG_REPR_H
#define _LIBDEBUGINFO_DEBUG_REPR_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>
#include <kos/anno.h>

#include <libunwind/dwarf.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __KERNEL__
/* Return the name of a given constant, or NULL if the constant isn't recognized.
 *  - debug_repr_DW_TAG():   Returns the `*' portion for one of `DW_TAG_*' (iow. excluding the `DW_TAG_' prefix)
 *  - debug_repr_DW_AT():    Returns the `*' portion for one of `DW_AT_*' (iow. excluding the `DW_AT_' prefix)
 *  - debug_repr_DW_FORM():  Returns the `*' portion for one of `DW_FORM_*' (iow. excluding the `DW_FORM_' prefix)
 *  - debug_repr_DW_ATE():   Returns the `*' portion for one of `DW_ATE_*' (iow. excluding the `DW_ATE_' prefix)
 *  - debug_repr_DW_OP():    Returns the `*' portion for one of `DW_OP_*' (iow. excluding the `DW_OP_' prefix)
 *  - debug_repr_DW_CFA():   Returns the `*' portion for one of `DW_CFA_*' (iow. excluding the `DW_CFA_' prefix)
 *  - debug_repr_DW_EH_PE(): Returns the `*' portion for one of `DW_EH_PE_*' (iow. excluding the `DW_EH_PE_' prefix) */
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_TAG)(dwarf_uleb128_t value);
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_AT)(dwarf_uleb128_t value);
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_FORM)(dwarf_uleb128_t value);
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_ATE)(dwarf_uleb128_t value);
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_OP)(__uint8_t value);
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_CFA)(__uint8_t value);
typedef __ATTR_CONST_T __ATTR_WUNUSED_T char const *__NOTHROW_T(LIBDEBUGINFO_CC *PDEBUG_REPR_DW_EH_PE)(__uint8_t value);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_TAG)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_AT)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_FORM)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_ATE)(dwarf_uleb128_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_OP)(__uint8_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_CFA)(__uint8_t value);
LIBDEBUGINFO_DECL __ATTR_CONST __ATTR_WUNUSED char const *__NOTHROW(LIBDEBUGINFO_CC debug_repr_DW_EH_PE)(__uint8_t value);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

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
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUG_REPR_DUMP)(__pformatprinter printer, void *arg,
                                    __NCX __byte_t const *debug_info_start, __NCX __byte_t const *debug_info_end,
                                    __NCX __byte_t const *debug_abbrev_start, __NCX __byte_t const *debug_abbrev_end,
                                    __NCX __byte_t const *debug_loclists_start, __NCX __byte_t const *debug_loclists_end,
                                    __NCX __byte_t const *debug_loc_start, __NCX __byte_t const *debug_loc_end,
                                    __NCX __byte_t const *debug_str_start, __NCX __byte_t const *debug_str_end,
                                    __NCX __byte_t const *debug_line_str_start, __NCX __byte_t const *debug_line_str_end);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1)) __ssize_t
(LIBDEBUGINFO_CC debug_repr_dump)(__pformatprinter printer, void *arg,
                                  __NCX __byte_t const *debug_info_start, __NCX __byte_t const *debug_info_end,
                                  __NCX __byte_t const *debug_abbrev_start, __NCX __byte_t const *debug_abbrev_end,
                                  __NCX __byte_t const *debug_loclists_start, __NCX __byte_t const *debug_loclists_end,
                                  __NCX __byte_t const *debug_loc_start, __NCX __byte_t const *debug_loc_end,
                                  __NCX __byte_t const *debug_str_start, __NCX __byte_t const *debug_str_end,
                                  __NCX __byte_t const *debug_line_str_start, __NCX __byte_t const *debug_line_str_end);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


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
typedef __ATTR_NONNULL_T((1, 3)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUG_REPR_CFI_EXPRESSION_EX)(__pformatprinter printer, void *arg,
                                                 __NCX __byte_t const *__restrict pc, __size_t length,
                                                 __size_t indent, __byte_t addrsize, __byte_t ptrsize,
                                                 __BOOL indent_on_first_line);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __ssize_t LIBDEBUGINFO_CC
debug_repr_cfi_expression_ex(__pformatprinter printer, void *arg,
                             __NCX __byte_t const *__restrict pc, __size_t length,
                             __size_t indent, __byte_t addrsize, __byte_t ptrsize,
                             __BOOL indent_on_first_line);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

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
typedef __ATTR_NONNULL_T((1, 3)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUG_REPR_CFI_EXPRESSION_WITH_LENGTH)(__pformatprinter printer, void *arg,
                                                          __NCX __byte_t const *__restrict expr,
                                                          __size_t length, __size_t indent,
                                                          __byte_t addrsize, __byte_t ptrsize);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __ssize_t LIBDEBUGINFO_CC
debug_repr_cfi_expression_with_length(__pformatprinter printer, void *arg,
                                      __NCX __byte_t const *__restrict expr,
                                      __size_t length, __size_t indent,
                                      __byte_t addrsize, __byte_t ptrsize);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */

/* Read the expression length as ULEB128 from `*expr' and print
 * the  disassembled contents of the succeeding CFI expression.
 * Same as `debug_repr_cfi_expression_with_length()'
 * @param: printer:  Output printer.
 * @param: arg:      Output printer cookie.
 * @param: pc:       Starting address of the expression.
 * @param: addrsize: s.a. `unwind_instruction_succ(3)'
 * @param: ptrsize:  s.a. `unwind_instruction_succ(3)'
 * @return: * : The usual pformatprinter-style value. */
typedef __ATTR_NONNULL_T((1, 3)) __ssize_t
(LIBDEBUGINFO_CC *PDEBUG_REPR_CFI_EXPRESSION)(__pformatprinter printer, void *arg,
                                              __NCX __byte_t const *__restrict expr, __size_t indent,
                                              __byte_t addrsize, __byte_t ptrsize);
#ifdef LIBDEBUGINFO_WANT_PROTOTYPES
LIBDEBUGINFO_DECL __ATTR_NONNULL((1, 3)) __ssize_t LIBDEBUGINFO_CC
debug_repr_cfi_expression(__pformatprinter printer, void *arg,
                          __NCX __byte_t const *__restrict expr, __size_t indent,
                          __byte_t addrsize, __byte_t ptrsize);
#endif /* LIBDEBUGINFO_WANT_PROTOTYPES */


#endif /* __KERNEL__ */


__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDEBUGINFO_DEBUG_REPR_H */
