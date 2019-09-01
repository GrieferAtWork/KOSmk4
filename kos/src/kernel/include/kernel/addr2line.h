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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_ADDR2LINE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_ADDR2LINE_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>

#include <stdbool.h>
#include <features.h>
#include <libdebuginfo/addr2line.h>
#include <bits/format-printer.h>

DECL_BEGIN

#ifdef __CC__
typedef unsigned int addr2line_errno_t; /* One of `ADDR2LINE_ERROR_*' */
#endif /* __CC__ */


#ifdef __CC__
/* Lookup addr2line information for the given source address.
 * >> di_debug_addr2line_t info;
 * >> addr2line_errno_t error;
 * >> uintptr_t level = 0;
 * >> do {
 * >>     error = addr2line((uintptr_t)ptr,&info,level);
 * >>     if (error != DEBUG_INFO_ERROR_SUCCESS)
 * >>         break;
 * >>     printk("%s(%Iu) : %s : HERE\n",
 * >>            info.al_srcfile,
 * >>            info.al_srcline,
 * >>            info.al_name);
 * >> } while (++level < info.al_levelcnt);
 */
FUNDEF addr2line_errno_t
NOTHROW(KCALL addr2line)(uintptr_t abs_pc,
                         di_debug_addr2line_t *__restrict result,
                         uintptr_t level DFL(0));

/* Print addr2line information for the given source address:
 * @param: printer:  The printer to which to output data.
 * @param: arg:      Argument to-be passed to `printer'
 * @param: start_pc: Starting program counter position (the one to pass to `addr2line')
 *                   This should be the address of the instruction who's source location
 *                   should be displayed.
 * @param: end_pc:   Ending program counter position.
 *                   This should be the address of the instruction following the one who's
 *                   source location should be displayed.
 *                   Note that the PC found in tracebacks, or exception information always
 *                   points to the _FOLLOWING_ PC, meaning that this argument should THAT
 *                   PC, whilst `start_pc' should be `arch_instruction_tryprev(end_pc)'
 * @param: message_format: printf-format of a message to print on each line
 * Example (of an inlined function):
 * >> /cygdrive/e/c/kls/kos/src/kernel/core/foo/bar.c(9) : my_inline_function+8 : c010783a+4 : Called from here
 * >> /cygdrive/e/c/kls/kos/src/kernel/core/foo/bar.c(42) : my_function+26 : c0107828+38 : Called from here
 * The format used is:
 *    debug_print_filename(SRC) + "(" + al_srcline + (al_srccol ? ("," + al_srccol) : "") + ")" +
 *    " : " + (al_rawname ? al_rawname : al_name ? al_name : "???") + "+" +
 *            (level == 0 ? (start_pc - al_symstart) : level == 0 ? (al_linestart - al_symstart)) +
 *    " : " + (level == 0 ? (start_pc.hex() + "+" + (end_pc - start_pc))
 *                        : (al_symstart.hex() + "+" + (al_symend - al_symstart).hex())) +
 *   (message_format ? (" : " + message_format % args) : "") + "\n";
 * Or in other words:
 * >> filename(line[,col]) : name+offset_of_instr_start_from_sym_start : instr_start+instr_length[ : message]
 * Where `instr_start' and `instr_length' refer to the inlined function for levels > 0
 * Additionally, when no addr2line information is available, the following is printed:
 * >> start_pc+end_pc_minus_start_pc[ : message] */
FUNDEF ssize_t
(VCALL addr2line_printf)(__pformatprinter printer, void *arg, uintptr_t start_pc,
                         uintptr_t end_pc, char const *message_format, ...);
FUNDEF ssize_t
(KCALL addr2line_vprintf)(__pformatprinter printer, void *arg, uintptr_t start_pc,
                          uintptr_t end_pc, char const *message_format,
                          __builtin_va_list args);

#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_ADDR2LINE_H */
