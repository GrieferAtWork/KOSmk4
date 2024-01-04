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
#ifndef GUARD_LIBREGDUMP_ARCH_I386_REGISTER_H
#define GUARD_LIBREGDUMP_ARCH_I386_REGISTER_H 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libregdump/register.h>

DECL_BEGIN

/* Print the name of a system register `regno', as it appears
 * in `E_ILLEGAL_INSTRUCTION_REGISTER' exceptions, or defined
 * in  <asm/registers.h>. When `regno'  is unknown, its value
 * is printed in a generic manner.
 * @param: printer: Output printer
 * @param: arg:     Cookie for `printer'
 * @param: regno:   One of the constants from <asm/registers.h>
 * @return: * : pformatprinter-compatible return value. */
INTDEF NONNULL((1)) ssize_t CC
libregdump_register_name(pformatprinter printer, void *arg,
                         uintptr_t regno);

DECL_END

#endif /* !GUARD_LIBREGDUMP_ARCH_I386_REGISTER_H */
