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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXCEPT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXCEPT_H 1

#include <kernel/compiler.h>

#include <hybrid/typecore.h>

#ifdef __ASSEMBLER__
#define EXCEPT_HANDLERS_START                        \
	.global x86_asm_except_personality;              \
	.cfi_personality 0,  x86_asm_except_personality; \
	.cfi_lsda 0,  991f;                              \
	.pushsection .rodata.cold;                       \
991:
#ifdef __x86_64__
#define EXCEPT_HANDLERS_CATCHALL(start, end, entry) \
	.local entry; .quad entry;                      \
	.local start; .quad start;                      \
	.local end;   .quad end;                        \
	.quad -1;
#define EXCEPT_HANDLERS_CATCH(code, start, end, entry) \
	.local entry; .quad entry;                         \
	.local start; .quad start;                         \
	.local end;   .quad end;                           \
	.quad EXCEPT_CODEOF(code);
#define EXCEPT_HANDLERS_END \
	.quad 0;                \
	.popsection;
#else /* __x86_64__ */
#define EXCEPT_HANDLERS_CATCHALL(start, end, entry) \
	.local entry; .long entry;                      \
	.local start; .long start;                      \
	.local end;   .long end;                        \
	.long -1;
#define EXCEPT_HANDLERS_CATCH(code, start, end, entry) \
	.local entry; .long entry;                         \
	.local start; .long start;                         \
	.local end;   .long end;                           \
	.long EXCEPT_CODEOF(code);
#define EXCEPT_HANDLERS_END \
	.long 0;                \
	.popsection;
#endif /* !__x86_64__ */
#endif /* __ASSEMBLER__ */


#ifdef __CC__
#include <kernel/arch/rt/except-personality.h>

#ifndef EXCEPT_PERSONALITY_CC
#define EXCEPT_PERSONALITY_CC KCALL
#endif /* !EXCEPT_PERSONALITY_CC */


DECL_BEGIN

struct x86_asm_except_entry {
	void const      *ee_entry; /* Exception handler entry PC (or 0 as sentinel) */
	void const      *ee_start; /* Exception handler start PC */
	void const      *ee_end;   /* Exception handler end PC */
	__UINTPTR_TYPE__ ee_mask;  /* Catch mask, or (uintptr_t)-1 to catch anything */
};
struct unwind_fde_struct;
struct kcpustate;

/* A helpful, predefined  personality function  that is meant  to be  used for  assembly
 * function which need to be able to handle exceptions in a fairly user-friendly manner.
 * NOTE: In order to define handlers, make use of the macros defined above.
 * NOTE: When   the  handler  is   entered,  callee-clobber  registers   may  have  been  clobbered
 *       if the exception was thrown  by a called function  that didn't encode CFI  instrumentation
 *       for preserving those  registers. All other  registers have  the same value  as they  would
 *       have had after a throwing function had returned normally, or before a throwing instruction
 *       had been invoked (with the obvious exception of `%Pip')
 *       Separately, you may include `DW_CFA_GNU_args_size' directives within your function,
 *       which  are recognized as adjustments for `%esp'  and are applied prior to execution
 *       or the specified handler. */
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_asm_except_personality)(struct unwind_fde_struct *__restrict fde,
                                                          struct kcpustate *__restrict state);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXCEPT_H */
