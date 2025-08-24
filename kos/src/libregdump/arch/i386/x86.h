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
#ifndef GUARD_LIBREGDUMP_ARCH_I386_X86_H
#define GUARD_LIBREGDUMP_ARCH_I386_X86_H 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <asm/isa.h>
#include <kos/types.h>

#include <format-printer.h>

#include <libregdump/x86.h>

DECL_BEGIN

/* Print a general-purpose register (id is one of { a, c, d, b, S, D, B, P } (same as gcc inline assembly register constraints, with B for %ebp and P for %esp))
 * On x86_64, use `0-7' to indicate extended registers `r8-r15' */
INTDEF NONNULL((1)) ssize_t CC libregdump_gpreg(struct regdump_printer *__restrict self, char id, uintptr_t value);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_gpregs(struct regdump_printer *__restrict self, struct gpregs const *__restrict data);
#ifdef __x86_64__
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_gpregs_with_sp(struct regdump_printer *__restrict self, struct gpregsnsp const *__restrict data, uintptr_t sp);
#else /* __x86_64__ */
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_gpregs_with_sp(struct regdump_printer *__restrict self, struct gpregs const *__restrict data, uintptr_t sp);
#endif /* !__x86_64__ */
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_sgregs(struct regdump_printer *__restrict self, struct sgregs const *__restrict data);
INTDEF NONNULL((1)) ssize_t CC libregdump_cs_ss(struct regdump_printer *__restrict self, uint16_t cs, uint16_t ss);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_sgregs_with_cs_ss(struct regdump_printer *__restrict self, struct sgregs const *__restrict data, uint16_t cs, uint16_t ss);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_sgregs_with_cs_ss_tr_ldt(struct regdump_printer *__restrict self, struct sgregs const *__restrict data, uint16_t cs, uint16_t ss, uint16_t tr, uint16_t ldt);
#ifdef __x86_64__
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_sgbase(struct regdump_printer *__restrict self, struct sgbase const *__restrict data);
#endif /* __x86_64__ */
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_coregs(struct regdump_printer *__restrict self, struct coregs const *__restrict data);
INTDEF NONNULL((1)) ssize_t CC libregdump_cr0(struct regdump_printer *__restrict self, uintptr_t cr0);
INTDEF NONNULL((1)) ssize_t CC libregdump_cr4(struct regdump_printer *__restrict self, uintptr_t cr4);
INTDEF NONNULL((1)) ssize_t CC libregdump_dr6(struct regdump_printer *__restrict self, uintptr_t dr6);
INTDEF NONNULL((1)) ssize_t CC libregdump_dr7(struct regdump_printer *__restrict self, uintptr_t dr7);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_drregs(struct regdump_printer *__restrict self, struct drregs const *__restrict data);
/* Print a segment register (id is one of { d[s], e[s], f[s], g[s], c[s], s[s], t[r], l[dt] } (pass the character that doesn't appear in brackets)) */
INTDEF NONNULL((1)) ssize_t CC libregdump_sreg(struct regdump_printer *__restrict self, char id, uint16_t value);
/* Print the eflags/rflags register */
INTDEF NONNULL((1)) ssize_t CC libregdump_flags(struct regdump_printer *__restrict self, uintptr_t flags);
/* Print the InstructionPointer register. */
INTDEF NONNULL((1)) ssize_t CC libregdump_ip(struct regdump_printer *__restrict self, uintptr_t ip_start, uintptr_t ip_end);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_gdt(struct regdump_printer *__restrict self, struct desctab const *__restrict gdt);
INTDEF NONNULL((1, 2)) ssize_t CC libregdump_idt(struct regdump_printer *__restrict self, struct desctab const *__restrict idt);

DECL_END

#endif /* !GUARD_LIBREGDUMP_ARCH_I386_X86_H */
