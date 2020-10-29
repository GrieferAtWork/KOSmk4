/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_INCLUDE_CPRINT_H
#define GUARD_MODDBX_INCLUDE_CPRINT_H 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>

#include <bits/crt/format-printer.h>

#include <libdebuginfo/debug_info.h> /* debuginfo_print_format_t */

/**/
#include "error.h"
#include "ctype.h"

#ifdef CONFIG_HAVE_DEBUGGER
DECL_BEGIN

struct cprinter {
	__pformatprinter         cp_printer;    /* [1..1] Pointer */
	void                    *cp_arg;        /* [?..?] Pointer cookie */
	debuginfo_print_format_t cp_format;     /* [0..1] Format-pointer */
	void                    *cp_format_arg; /* [?..?] Format-pointer cookie */
};

/* Print the correct representation of the given type, including
 * an optional, contained variable name that is also printed at
 * the proper location. */
FUNDEF NONNULL((1, 2)) ssize_t KCALL
ctyperef_printname(struct ctyperef const *__restrict self,
                   struct cprinter const *__restrict printer,
                   char const *varname DFL(__NULLPTR),
                   size_t varname_len DFL(0));
FUNDEF NONNULL((1, 2)) ssize_t KCALL
ctype_printname(struct ctype const *__restrict self,
                struct cprinter const *__restrict printer,
                char const *varname DFL(__NULLPTR),
                size_t varname_len DFL(0));

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_INCLUDE_CPRINT_H */
