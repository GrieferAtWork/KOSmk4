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
#ifndef _LIBDISASM_FORMAT_H
#define _LIBDISASM_FORMAT_H 1

#include "api.h"
/**/

#include <hybrid/host.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#include <libc/string.h>

/* Format codes for `diasm_print_format_t' */
#define DISASSEMBLER_FORMAT_REGISTER_PREFIX   0x0002 /* Prefix for register names. */
#define DISASSEMBLER_FORMAT_REGISTER_SUFFIX   0x0003 /* Suffix for register names. */
#define DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX  0x0004 /* Prefix for immediate values. */
#define DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX  0x0005 /* Suffix for immediate values. */
#define DISASSEMBLER_FORMAT_OFFSET_PREFIX     0x0006 /* Prefix for memory offsets. */
#define DISASSEMBLER_FORMAT_OFFSET_SUFFIX     0x0007 /* Suffix for memory offsets. */
#define DISASSEMBLER_FORMAT_SYMBOL_PREFIX     0x0008 /* Prefix for symbol names/values. */
#define DISASSEMBLER_FORMAT_SYMBOL_SUFFIX     0x0009 /* Suffix for symbol names/values. */
#define DISASSEMBLER_FORMAT_PSEUDOOP_PREFIX   0x000a /* Prefix for pseudo-opcodes. */
#define DISASSEMBLER_FORMAT_PSEUDOOP_SUFFIX   0x000b /* Suffix for pseudo-opcodes. */
#define DISASSEMBLER_FORMAT_MNEMONIC_PREFIX   0x000c /* Prefix for instruction mnemonics. */
#define DISASSEMBLER_FORMAT_MNEMONIC_SUFFIX   0x000d /* Suffix for instruction mnemonics. */
#define DISASSEMBLER_FORMAT_SCALE_PREFIX      0x000e /* Prefix for x86 modrm scale operands. */
#define DISASSEMBLER_FORMAT_SCALE_SUFFIX      0x000f /* Suffix for x86 modrm scale operands. */
#define DISASSEMBLER_FORMAT_ISPREFIX(x) (!((x) & DISASSEMBLER_FORMAT_SUFFIX_FLAG))
#define DISASSEMBLER_FORMAT_ISSUFFIX(x)   ((x) & DISASSEMBLER_FORMAT_SUFFIX_FLAG)
#define DISASSEMBLER_FORMAT_SUFFIX_FLAG       0x0001 /* Is this a suffix? */


#ifdef __CC__
__DECL_BEGIN

struct disassembler;

/* Print prefix/suffix strings for various target-specific components.
 *  -> Intended for encoding ANSI-TTY color codes in order to allow for syntax highlighting
 * @param: format_option: The format string being requested (one of `DISASSEMBLER_FORMAT_*')
 * @return: * :  The sum of return  values from calls to  `self->d_printer',
 *               or a negative  value if an  error occurred while  printing,
 *               or  alternatively `0' in  case `disasm_print()' and friends
 *               were used to print output, rather than the printer callback
 *               itself directly. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBDISASM_CC *diasm_print_format_t)(struct disassembler *__restrict self,
                                     unsigned int format_option);

__DECL_END

#endif /* __CC__ */

#endif /* !_LIBDISASM_FORMAT_H */
