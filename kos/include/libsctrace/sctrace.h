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
#ifndef _LIBSCTRACE_SCTRACE_H
#define _LIBSCTRACE_SCTRACE_H 1

#include "api.h"
/**/

#include <bits/crt/format-printer.h>
#include <bits/types.h>

#include "repr-types.h"


__DECL_BEGIN

#ifdef __CC__

union sc_argval {
	__uint64_t sv_u64;
};

struct sc_argument {
	char const         *sa_name;  /* [0..1] Name of the argument (or `NULL' if unknown) */
	__uintptr_t         sa_type;  /* [< LIBSCTRACE_COUNT] Argument representation type (one of `SC_REPR_*') */
	struct sc_argument *sa_link;  /* [0..1] Linked argument (if defined) */
	union sc_argval     sa_value; /* Argument value */
};

struct sc_desc {
	char const        *sc_name;    /* [0..1] Name of the system call (or `NULL' if unknown) */
	__size_t           sc_argc;    /* [<= 6] # of arguments taken by the system call. */
	struct sc_argument sc_argv[6]; /* [sc_argc] Info about individual syscall arguments. */
};

struct rpc_syscall_info;

/* Get a description  of the  system call  described by  `sc_info' in  `desc'
 * This  is  the main  function used  to access  the system  call description
 * database for the purpose of doing things such as printing a representation
 * of a system call invocation.
 * @return: true:  The system call was recognized, and `desc' was filled accordingly.
 * @return: false: Unknown system call (`desc' was filled with stub-values) */
typedef __ATTR_NONNULL_T((1, 2)) __BOOL
__NOTHROW_NCX_T(LIBSCTRACE_CC *PSC_GETDESC)(struct rpc_syscall_info const *__restrict sc_info,
                                            struct sc_desc *__restrict desc);
#ifdef LIBSCTRACE_WANT_PROTOTYPES
LIBSCTRACE_DECL __ATTR_NONNULL((1, 2)) __BOOL
__NOTHROW_NCX(LIBSCTRACE_CC sc_getdesc)(struct rpc_syscall_info const *__restrict sc_info,
                                        struct sc_desc *__restrict desc);
#endif /* LIBSCTRACE_WANT_PROTOTYPES */

/* Print the representation of a given system call argument
 * value, given both its `argtype' (one of `SC_REPR_*'), as
 * well as its `value'.
 * WARNING: Depending on `argtype', an exception may be thrown
 *          if the system call invoker has passed some invalid
 *          argument to a system  call (i.e. a faulty  pointer
 *          when a structure pointer or string was expected) */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(LIBSCTRACE_CC *PSC_PRINTVALUE)(__pformatprinter printer, void *arg,
                                __uintptr_t argtype, union sc_argval value,
                                struct sc_argument *link);
#ifdef LIBSCTRACE_WANT_PROTOTYPES
LIBSCTRACE_DECL __ATTR_NONNULL((1)) __ssize_t LIBSCTRACE_CC
sc_printvalue(__pformatprinter printer, void *arg,
              __uintptr_t argtype, union sc_argval value,
              struct sc_argument *link);
#endif /* LIBSCTRACE_WANT_PROTOTYPES */


#endif /* __CC__ */

__DECL_END

#endif /* !_LIBSCTRACE_SCTRACE_H */
