/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBREGDUMP_REGISTER_H
#define _LIBREGDUMP_REGISTER_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

/* Print the name of a system register `regno', as it appears
 * in `E_ILLEGAL_INSTRUCTION_REGISTER' exceptions, or defined
 * in  <asm/registers.h>. When `regno'  is unknown, its value
 * is printed in a generic manner.
 * @param: printer: Output printer
 * @param: arg:     Cookie for `printer'
 * @param: regno:   One of the constants from <asm/registers.h>
 * @return: * : pformatprinter-compatible return value. */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBREGDUMP_CC *PREGDUMP_REGISTER_NAME)(__pformatprinter printer, void *arg,
                                        __uintptr_t regno);
#ifdef LIBREGDUMP_WANT_PROTOTYPES
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC
regdump_register_name(__pformatprinter printer, void *arg,
                      __uintptr_t regno);
#endif /* LIBREGDUMP_WANT_PROTOTYPES */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBREGDUMP_REGISTER_H */
