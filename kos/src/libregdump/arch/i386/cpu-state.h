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
#ifndef GUARD_LIBREGDUMP_ARCH_I386_CPU_STATE_H
#define GUARD_LIBREGDUMP_ARCH_I386_CPU_STATE_H 1

#include "../../api.h"

#include <hybrid/compiler.h>

#include <kos/kernel/cpu-state.h>
#include <kos/types.h>

#include <format-printer.h>

#include <libregdump/cpu-state.h>

DECL_BEGIN

/* Dump the contents of the given cpu-state / context. */
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_ucpustate(struct regdump_printer *__restrict self, struct ucpustate const *__restrict data);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_lcpustate(struct regdump_printer *__restrict self, struct lcpustate const *__restrict data);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_kcpustate(struct regdump_printer *__restrict self, struct kcpustate const *__restrict data);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_fcpustate(struct regdump_printer *__restrict self, struct fcpustate const *__restrict data);

#ifdef __KERNEL__
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_icpustate(struct regdump_printer *__restrict self, struct icpustate const *__restrict data);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_scpustate(struct regdump_printer *__restrict self, struct scpustate const *__restrict data);
#endif /* __KERNEL__ */

#ifndef __KERNEL__
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_ucontext(struct regdump_printer *__restrict self, struct ucontext const *__restrict data);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_mcontext(struct regdump_printer *__restrict self, struct mcontext const *__restrict data);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBREGDUMP_ARCH_I386_CPU_STATE_H */
