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
#ifndef GUARD_LIBDEMANGLE_DEMANGLE_H
#define GUARD_LIBDEMANGLE_DEMANGLE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libdemangle/api.h>
#include <libdemangle/demangle.h>

DECL_BEGIN


/* Print the demangled form of the given `mangled_name'
 * This function will automatically (try to) detect the mangling used
 * to encode type information in `mangled_name', but will re-print the
 * given `mangled_name' if the detection was unsuccessful.
 * Other than that, this function behaves like any other format-printer
 * compatible API, returning the sum of all callbacks, or the first
 * negative return value upon error. */
INTDEF NONNULL((1, 3)) ssize_t CC
libdm_demangle(pformatprinter printer, void *arg,
               char const *__restrict mangled_name);


DECL_END

#endif /* !GUARD_LIBDEMANGLE_DEMANGLE_H */
