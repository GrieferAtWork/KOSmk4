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
#ifndef _LIBREGDUMP_PRINTER_H
#define _LIBREGDUMP_PRINTER_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>

/* We  re-use  (some of)  libdisasm's formatting  constants to
 * describe how registers and/or values should be highlighted. */
#include <libdisasm/format.h>

/* Format codes for `regdump_print_format_t' */
#define REGDUMP_FORMAT_REGISTER_PREFIX DISASSEMBLER_FORMAT_REGISTER_PREFIX  /* Prefix for register names. */
#define REGDUMP_FORMAT_REGISTER_SUFFIX DISASSEMBLER_FORMAT_REGISTER_SUFFIX  /* Suffix for register names. */
#define REGDUMP_FORMAT_VALUE_PREFIX    DISASSEMBLER_FORMAT_IMMEDIATE_PREFIX /* Prefix for register values. */
#define REGDUMP_FORMAT_VALUE_SUFFIX    DISASSEMBLER_FORMAT_IMMEDIATE_SUFFIX /* Suffix for register values. */
#define REGDUMP_FORMAT_OFFSET_PREFIX   DISASSEMBLER_FORMAT_OFFSET_PREFIX    /* Prefix for memory offsets. */
#define REGDUMP_FORMAT_OFFSET_SUFFIX   DISASSEMBLER_FORMAT_OFFSET_SUFFIX    /* Suffix for memory offsets. */
#define REGDUMP_FORMAT_FLAG_PREFIX     DISASSEMBLER_FORMAT_SYMBOL_PREFIX    /* Prefix for register flags. */
#define REGDUMP_FORMAT_FLAG_SUFFIX     DISASSEMBLER_FORMAT_SYMBOL_SUFFIX    /* Suffix for register flags. */
#define REGDUMP_FORMAT_ERROR_PREFIX    0x1002 /* Prefix for error messages. */
#define REGDUMP_FORMAT_ERROR_SUFFIX    0x1003 /* Suffix for error messages. */
#define REGDUMP_FORMAT_INDENT          0x1010 /* Indent printed before any line. */

#ifdef __CC__
__DECL_BEGIN

struct regdump_printer;

/* Print prefix/suffix strings for various target-specific components.
 *  -> Intended for encoding ANSI-TTY color codes in order to allow for syntax highlighting
 * @param: format_option: The format string being requested (one of `REGDUMP_FORMAT_*')
 * @return: * :  The sum of return  values from calls to  `self->d_printer',
 *               or a negative  value if an  error occurred while  printing,
 *               or  alternatively `0' in  case `disasm_print()' and friends
 *               were used to print output, rather than the printer callback
 *               itself directly. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBREGDUMP_CC *regdump_print_format_t)(struct regdump_printer *__restrict __self,
                                        unsigned int __format_option);


struct regdump_printer {
	__pformatprinter       rdp_printer;     /* [1..1] Output printer. */
	void                  *rdp_printer_arg; /* [?..?] Argument for `rdp_printer'. */
	regdump_print_format_t rdp_format;      /* [0..1] Custom printer for syntax highlighting. */
};

__FORCELOCAL __ssize_t LIBREGDUMP_CC
regdump_printer_format(struct regdump_printer *__restrict __self,
                       unsigned int __format_option) {
	return __self->rdp_format != __NULLPTR
	       ? (*__self->rdp_format)(__self, __format_option)
	       : 0;
}



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBREGDUMP_PRINTER_H */
