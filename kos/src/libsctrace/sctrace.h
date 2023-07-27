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
#ifndef GUARD_LIBSCTRACE_SCTRACE_H
#define GUARD_LIBSCTRACE_SCTRACE_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/bits/syscall-info.h> /* struct rpc_syscall_info */
#include <kos/types.h>

#include <format-printer.h>
#include <stdbool.h>

#include <libsctrace/repr-types.h>
#include <libsctrace/sctrace.h>

DECL_BEGIN

/* Get a description  of the  system call  described by  `sc_info' in  `desc'
 * This  is  the main  function used  to access  the system  call description
 * database for the purpose of doing things such as printing a representation
 * of a system call invocation.
 * @return: true:  The system call was recognized, and `desc' was filled accordingly.
 * @return: false: Unknown system call (`desc' was filled with stub-values) */
INTDEF NONNULL((1, 2)) bool
NOTHROW_NCX(CC libsc_getdesc)(struct rpc_syscall_info const *__restrict sc_info,
                              struct sc_desc *__restrict desc);

/* Print the representation of a given system call argument
 * value, given both its `argtype' (one of `SC_REPR_*'), as
 * well as its `value'.
 * WARNING: Depending on `argtype', an exception may be thrown
 *          if the system call invoker has passed some invalid
 *          argument to a system  call (i.e. a faulty  pointer
 *          when a structure pointer or string was expected) */
INTDEF NONNULL((1)) ssize_t
NOTHROW_CB_NCX(CC libsc_printvalue)(pformatprinter printer, void *arg,
                                    uintptr_t argtype, union sc_argval value,
                                    struct sc_argument *link);

DECL_END

#endif /* !GUARD_LIBSCTRACE_SCTRACE_H */
