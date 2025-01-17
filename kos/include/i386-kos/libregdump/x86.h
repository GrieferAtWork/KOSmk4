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
#ifndef _I386_KOS_LIBREGDUMP_X86_H
#define _I386_KOS_LIBREGDUMP_X86_H 1

#include <libregdump/api.h>
/**/

#include <asm/isa.h>
#include <bits/types.h>

#include <libregdump/printer.h>

/* Print a human-readable dump of all of the registers within the given cpu-state/context. */

#ifdef __x86_64__
#define REGDUMP_GPREG_RAX 'a'
#define REGDUMP_GPREG_RCX 'c'
#define REGDUMP_GPREG_RDX 'd'
#define REGDUMP_GPREG_RBX 'b'
#define REGDUMP_GPREG_RSI 'S'
#define REGDUMP_GPREG_RDI 'D'
#define REGDUMP_GPREG_RBP 'B'
#define REGDUMP_GPREG_RSP 'P'
#define REGDUMP_GPREG_R8  '0'
#define REGDUMP_GPREG_R9  '1'
#define REGDUMP_GPREG_R10 '2'
#define REGDUMP_GPREG_R11 '3'
#define REGDUMP_GPREG_R12 '4'
#define REGDUMP_GPREG_R13 '5'
#define REGDUMP_GPREG_R14 '6'
#define REGDUMP_GPREG_R15 '7'
#else /* __x86_64__ */
#define REGDUMP_GPREG_EAX 'a'
#define REGDUMP_GPREG_ECX 'c'
#define REGDUMP_GPREG_EDX 'd'
#define REGDUMP_GPREG_EBX 'b'
#define REGDUMP_GPREG_ESI 'S'
#define REGDUMP_GPREG_EDI 'D'
#define REGDUMP_GPREG_EBP 'B'
#define REGDUMP_GPREG_ESP 'P'
#endif /* !__x86_64__ */


#ifdef __CC__
__DECL_BEGIN

struct gpregs;
#ifdef __x86_64__
struct gpregsnsp;
#endif /* !__x86_64__ */
struct sgregs;
struct coregs;
struct drregs;
struct desctab;

/* NOTE: Some printers will emit additional information while in kernel-space,
 *       as  some of the  possibly dumped information  is locked behind RING#0
 *       access requirements. */


/* Print a general-purpose register (id is one of { a, c, d, b, S, D, B, P } (same as gcc inline assembly register constraints, with B for %ebp and P for %esp))
 * On x86_64, use `0-7' to indicate extended registers `r8-r15' */
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_GPREG)(struct regdump_printer *__restrict __self, char __id, __uintptr_t __value);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_GPREGS)(struct regdump_printer *__restrict __self, struct gpregs const *__restrict __data);
#ifdef __x86_64__
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_GPREGS_WITH_SP)(struct regdump_printer *__restrict __self, struct gpregsnsp const *__restrict __data, __uintptr_t __sp);
#else /* __x86_64__ */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_GPREGS_WITH_SP)(struct regdump_printer *__restrict __self, struct gpregs const *__restrict __data, __uintptr_t __sp);
#endif /* !__x86_64__ */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_SGREGS)(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_SGREGS_WITH_CS_SS)(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data, __uint16_t __cs, __uint16_t __ss);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_SGREGS_WITH_CS_SS_TR_LDT)(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data, __uint16_t __cs, __uint16_t __ss, __uint16_t __tr, __uint16_t __ldt);
#ifdef __x86_64__
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_SGBASE)(struct regdump_printer *__restrict __self, struct sgbase const *__restrict __data);
#endif /* __x86_64__ */
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_COREGS)(struct regdump_printer *__restrict __self, struct coregs const *__restrict __data);
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_CR0)(struct regdump_printer *__restrict __self, __uintptr_t __cr0);
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_CR4)(struct regdump_printer *__restrict __self, __uintptr_t __cr4);
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_DR6)(struct regdump_printer *__restrict __self, __uintptr_t __dr6);
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_DR7)(struct regdump_printer *__restrict __self, __uintptr_t __dr7);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_DRREGS)(struct regdump_printer *__restrict __self, struct drregs const *__restrict __data);
/* Print a segment register (id is one of { d[s], e[s], f[s], g[s], c[s], s[s], t[r], l[dt] } (pass the character that doesn't appear in brackets)) */
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_SREG)(struct regdump_printer *__restrict __self, char __id, __uint16_t __value);
/* Print the eflags/rflags register */
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_FLAGS)(struct regdump_printer *__restrict __self, __uintptr_t __flags);
/* Print the InstructionPointer register. */
typedef __ATTR_NONNULL_T((1)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_IP)(struct regdump_printer *__restrict __self, __uintptr_t __ip);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_GDT)(struct regdump_printer *__restrict __self, struct desctab const *__restrict __gdt);
typedef __ATTR_NONNULL_T((1, 2)) __ssize_t (LIBREGDUMP_CC *PREGDUMP_IDT)(struct regdump_printer *__restrict __self, struct desctab const *__restrict __idt);
#ifdef LIBREGDUMP_WANT_PROTOTYPES
/* Print a general-purpose register (id is one of { a, c, d, b, S, D, B, P } (same as gcc inline assembly register constraints, with B for %ebp and P for %esp))
 * On x86_64, use `0-7' to indicate extended registers `r8-r15' */
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_gpreg(struct regdump_printer *__restrict __self, char __id, __uintptr_t __value);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_gpregs(struct regdump_printer *__restrict __self, struct gpregs const *__restrict __data);
#ifdef __x86_64__
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_gpregs_with_sp(struct regdump_printer *__restrict __self, struct gpregsnsp const *__restrict __data, __uintptr_t __sp);
#else /* __x86_64__ */
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_gpregs_with_sp(struct regdump_printer *__restrict __self, struct gpregs const *__restrict __data, __uintptr_t __sp);
#endif /* !__x86_64__ */
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_sgregs(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_sgregs_with_cs_ss(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data, __uint16_t __cs, __uint16_t __ss);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_sgregs_with_cs_ss_tr_ldt(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data, __uint16_t __cs, __uint16_t __ss, __uint16_t __tr, __uint16_t __ldt);
#ifdef __x86_64__
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_sgbase(struct regdump_printer *__restrict __self, struct sgbase const *__restrict __data);
#endif /* __x86_64__ */
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_coregs(struct regdump_printer *__restrict __self, struct coregs const *__restrict __data);
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_cr0(struct regdump_printer *__restrict __self, __uintptr_t __cr0);
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_cr4(struct regdump_printer *__restrict __self, __uintptr_t __cr4);
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_dr6(struct regdump_printer *__restrict __self, __uintptr_t __dr6);
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_dr7(struct regdump_printer *__restrict __self, __uintptr_t __dr7);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_drregs(struct regdump_printer *__restrict __self, struct drregs const *__restrict __data);
/* Print a segment register (id is one of { d[s], e[s], f[s], g[s], c[s], s[s], t[r], l[dt] } (pass the character that doesn't appear in brackets)) */
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_sreg(struct regdump_printer *__restrict __self, char __id, __uint16_t __value);
/* Print the eflags/rflags register */
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_flags(struct regdump_printer *__restrict __self, __uintptr_t __flags);
/* Print the InstructionPointer register. */
LIBREGDUMP_DECL __ATTR_NONNULL((1)) __ssize_t LIBREGDUMP_CC regdump_ip(struct regdump_printer *__restrict __self, __uintptr_t __ip, isa_t __isa);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_gdt(struct regdump_printer *__restrict __self, struct desctab const *__restrict __gdt);
LIBREGDUMP_DECL __ATTR_NONNULL((1, 2)) __ssize_t LIBREGDUMP_CC regdump_idt(struct regdump_printer *__restrict __self, struct desctab const *__restrict __idt);

#ifdef __cplusplus
extern "C++" {
__COMPILER_REDIRECT(LIBREGDUMP_DECL,__ATTR_NONNULL((1, 2)),__ssize_t,,LIBREGDUMP_CC,regdump,(struct regdump_printer *__restrict __self, struct gpregs const *__restrict __data),regdump_gpregs,(__self,__data))
__COMPILER_REDIRECT(LIBREGDUMP_DECL,__ATTR_NONNULL((1, 2)),__ssize_t,,LIBREGDUMP_CC,regdump,(struct regdump_printer *__restrict __self, struct sgregs const *__restrict __data),regdump_sgregs,(__self,__data))
__COMPILER_REDIRECT(LIBREGDUMP_DECL,__ATTR_NONNULL((1, 2)),__ssize_t,,LIBREGDUMP_CC,regdump,(struct regdump_printer *__restrict __self, struct coregs const *__restrict __data),regdump_coregs,(__self,__data))
__COMPILER_REDIRECT(LIBREGDUMP_DECL,__ATTR_NONNULL((1, 2)),__ssize_t,,LIBREGDUMP_CC,regdump,(struct regdump_printer *__restrict __self, struct drregs const *__restrict __data),regdump_drregs,(__self,__data))
} /* extern "C++" */
#endif /* __cplusplus */
#endif /* LIBREGDUMP_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBREGDUMP_X86_H */
