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
#ifndef GUARD_LIBDISASM_COMMON_H
#define GUARD_LIBDISASM_COMMON_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libdisasm/disassembler.h>

DECL_BEGIN

/* Quick and simple function for disassembling text into a given printer.
 * This is equivalent to:
 * >> struct disassembler da;
 * >> disasm_init(&da, printer, arg, pc, target, flags, 0);
 * >> return disasm_print_until(&da, (byte_t *)pc + num_bytes);
 * @return: * : The sum of all callbacks to `printer' ever executed with `self'
 * @return: <0: The first negative return value of `printer'. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm(pformatprinter printer, void *arg, void const *pc, size_t num_bytes,
             uintptr_half_t target DFL(DISASSEMBLER_TARGET_CURRENT),
             uintptr_half_t flags DFL(DISASSEMBLER_FNORMAL));


/* Quick and simple function for disassembling a single instruction.
 * This is equivalent to:
 * >> struct disassembler da;
 * >> disasm_init(&da, printer, arg, pc, target, flags, 0);
 * >> return disasm_print_instruction(&da);
 * @return: * : The sum of all callbacks to `printer' ever executed with `self'
 * @return: <0: The first negative return value of `printer'. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm_single(pformatprinter printer, void *arg, void const *pc,
                    uintptr_half_t target DFL(DISASSEMBLER_TARGET_CURRENT),
                    uintptr_half_t flags DFL(DISASSEMBLER_FNORMAL));

/* Disassemble and print lines (s.a. `disasm_print_line()') until `endpc'
 * has been reached, or a printer error has occurred.
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm_print_until(struct disassembler *__restrict self,
                         void const *endpc);

/* Disassemble a single  instruction line, following  formatting rules  specified
 * by `DISASSEMBLER_F*', potentially printing multiple lines of the instruction's
 * bytes don't all fit into a single line (s.a. `d_maxbytes').
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm_print_line(struct disassembler *__restrict self);

/* Same as `libda_disasm_print_line()', but don't print a trailing line-feed. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm_print_line_nolf(struct disassembler *__restrict self);

/* Disassemble a single instruction, including its mnemonic, and all operands.
 * This  function does not include any prefix,  nor does it append a trailing.
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm_print_instruction(struct disassembler *__restrict self);

/* Print the name+offset/address of a symbol at `symbol_addr'
 * @return: * : The sum of all printer callbacks ever executed with `self'
 * @return: <0: The printer error that has occurred. */
INTDEF NONNULL((1)) ssize_t CC
libda_disasm_print_symbol(struct disassembler *__restrict self,
                          void const *symbol_addr);

/* Returns the length (in bytes) of the next instruction to-be disassembled. */
INTDEF NONNULL((1)) size_t CC
libda_disasm_instrlen(struct disassembler *__restrict self);

/* Return the default number of max instruction bytes to print for `target' */
INTDEF ATTR_CONST uintptr_half_t CC
libda_disasm_default_maxbytes(uintptr_half_t target DFL(DISASSEMBLER_TARGET_CURRENT));

INTDEF NONNULL((1)) void CC
libda_single_generic(struct disassembler *__restrict self);


DECL_END


#endif /* !GUARD_LIBDISASM_COMMON_H */
