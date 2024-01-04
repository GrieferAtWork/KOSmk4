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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ADDR2LINE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ADDR2LINE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <bits/crt/format-printer.h> /* __pformatprinter */
#include <kos/exec/module.h>         /* module_t */

#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/errno.h>

DECL_BEGIN


#ifdef __CC__
struct addr2line_buf {
	di_addr2line_sections_t    ds_info;     /* Section pointers */
	di_addr2line_dl_sections_t ds_sect;     /* Section references */
	REF module_t              *ds_mod;      /* [0..1] The linked module. */
};


/* Lookup addr2line information for the given source address.
 * >> di_debug_addr2line_t info;
 * >> debuginfo_errno_t error;
 * >> uintptr_t level = 0;
 * >> do {
 * >>     error = addr2line((uintptr_t)ptr, &info, level);
 * >>     if (error != DEBUG_INFO_ERROR_SUCCESS)
 * >>         break;
 * >>     printk("%s(%" PRIuPTR ") : %s : HERE\n",
 * >>            info.al_srcfile,
 * >>            info.al_srcline,
 * >>            info.al_name);
 * >> } while (++level < info.al_levelcnt);
 * @param: module_relative_pc: The return value of `addr2line_begin()'
 */
FUNDEF WUNUSED NONNULL((1, 3)) debuginfo_errno_t
NOTHROW(KCALL addr2line)(struct addr2line_buf const *__restrict info,
                         uintptr_t module_relative_pc,
                         di_debug_addr2line_t *__restrict result,
                         uintptr_t level DFL(0));
FUNDEF WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL addr2line_begin)(struct addr2line_buf *__restrict buf,
                               void const *abs_pc);
FUNDEF NONNULL((1)) void
NOTHROW(KCALL addr2line_end)(struct addr2line_buf *__restrict buf);


/* Print addr2line information for the given source address:
 * @param: printer:  The printer to which to output data.
 * @param: arg:      Argument to-be passed to `printer'
 * @param: start_pc: Starting program counter position (the one to pass to  `addr2line')
 *                   This should be the address of the instruction who's source location
 *                   should be displayed.
 * @param: end_pc:   Ending program counter position.
 *                   This should be the address of the instruction following the one who's
 *                   source location should be displayed.
 *                   Note that the PC found in tracebacks, or exception information always
 *                   points  to the _FOLLOWING_ PC, meaning that this argument should THAT
 *                   PC, whilst `start_pc' should be `arch_instruction_tryprev(end_pc)'
 * @param: message_format: printf-format of a message to print on each line
 * Example (of an inlined function):
 * >> /cygdrive/e/c/kls/kos/src/kernel/core/foo/bar.c(9) : my_inline_function+8 : c010783a+4 : Called from here
 * >> /cygdrive/e/c/kls/kos/src/kernel/core/foo/bar.c(42) : my_function+26 : c0107828+38 : Called from here
 * The format used is:
 *    debug_addr2line_print_filename(src) + "(" + al_srcline + (al_srccol ? ("," + al_srccol) : "") + ")" +
 *    " : " + (al_rawname  ?  al_rawname  :  al_name  ?  al_name  :  "???")  +  "+"  +
 *            (level == 0 ? (start_pc - al_symstart) : (al_linestart - al_symstart)) +
 *    " : " + (level == 0 ? (start_pc.hex() + "+" + (end_pc - start_pc))
 *                        : (al_symstart.hex() + "+" + (al_symend - al_symstart).hex())) +
 *   (message_format ? (" : " + message_format % args) : "") + "\n";
 * Or in other words:
 * >> filename(line[,col]) : name+offset_of_instr_start_from_sym_start : instr_start+instr_length[ : message]
 * Where   `instr_start'   and   `instr_length'   refer   to   the   inlined   function   for   levels   >  0
 * Additionally,    when   no   addr2line    information   is   available,    the   following   is   printed:
 * >> start_pc+end_pc_minus_start_pc[ : message] */
FUNDEF NONNULL((1)) ssize_t
(VCALL addr2line_printf)(__pformatprinter printer, void *arg, void const *start_pc,
                         void const *end_pc, char const *message_format, ...);
FUNDEF NONNULL((1)) ssize_t
(KCALL addr2line_vprintf)(__pformatprinter printer, void *arg, void const *start_pc,
                          void const *end_pc, char const *message_format,
                          __builtin_va_list args);

#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ADDR2LINE_H */
