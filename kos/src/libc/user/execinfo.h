/* HASH CRC-32:0xa30c8ab9 */
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
#ifndef GUARD_LIBC_USER_EXECINFO_H
#define GUARD_LIBC_USER_EXECINFO_H 1

#include "../api.h"
#include "../auto/execinfo.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <execinfo.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> backtrace(3)
 * Create a  traceback of  up to  `size' instruction  pointers  from
 * the  calling function, their  caller, and so  forth. On KOS, this
 * information is constructed with the help of CFI  instrumentation,
 * and  the  functions  from  `<libunwind/...>'.  However,  on other
 * systems, this function is fairly dumb and relies on all traversed
 * code having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `array' (always `<= size') */
INTDEF ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T NOTHROW_NCX(LIBCCALL libc_backtrace)(void **array, __STDC_INT_AS_SIZE_T size);
/* >> backtrace_symbol_printf(3)
 * Print the formatted representation of `address' to `printer'
 *  - The used format is `format' (or "%a <%n%D> at %f" if NULL)
 *  - No trailing linefeed is printed
 *  - If debug information could not be loaded, use "???" for strings
 * @return: * : pformatprinter-compatible return value */
INTDEF ATTR_IN_OPT(4) NONNULL((1)) ssize_t NOTHROW_NCX(LIBCCALL libc_backtrace_symbol_printf)(pformatprinter printer, void *arg, void const *address, char const *format);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_EXECINFO_H */
