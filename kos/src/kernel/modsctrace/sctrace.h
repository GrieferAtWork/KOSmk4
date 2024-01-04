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
#ifndef GUARD_MODSCTRACE_SCTRACE_H
#define GUARD_MODSCTRACE_SCTRACE_H 1
#define LIBSCTRACE_WANT_PROTOTYPES

#include <kernel/compiler.h>

#include <libsctrace/api.h>

#ifdef _LIBSCTRACE_SCTRACE_H
#error "Must not #include <libsctrace/sctrace.h> before including this header!"
#endif /* _LIBSCTRACE_SCTRACE_H */

#ifdef BUILDING_MODSCTRACE
#undef LIBSCTRACE_DECL
/* Link the lib-internal variants to prevent
 * unnecessary relocations against  ourself. */
#define LIBSCTRACE_DECL INTDEF
#define sc_getdesc    libsc_getdesc
#define sc_printvalue libsc_printvalue
#endif /* BUILDING_MODSCTRACE */

#include <libsctrace/sctrace.h>
/**/

DECL_BEGIN

struct driver;
struct rpc_syscall_info;

/* The main callback registered with `syscall_trace_start()' when this driver is loaded. */
INTDEF NONNULL((1, 2)) void FCALL
sctrace(struct driver *__restrict self,
        struct rpc_syscall_info const *__restrict info);


DECL_END

#endif /* !GUARD_MODSCTRACE_SCTRACE_H */
