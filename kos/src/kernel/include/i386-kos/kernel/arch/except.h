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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXCEPT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXCEPT_H 1

#include <kernel/compiler.h>
#include <hybrid/typecore.h>

DECL_BEGIN

#ifdef __CC__

struct unwind_fde_struct;
struct kcpustate;
/* The prototype by which custom personality function must abide within the KOS kernel.
 * When called, `state' refers to the state _within_ the associated function. - Not the
 * state after that function has been unwound!
 * HINT: `.cfi_personality 0, <some-function-implemented-as-dwarf_perso_t>'
 * HINT: The `lsda' argument is the `lsda-value' in `.cfi_lsda 0, <lsda-value>'
 * NOTE: The PC-register of `state' is set to point _AFTER_ the instruction
 *       that caused/propagated an exception (aka. the return address)
 * @param: fde:  The FDE pointing to @this personality function.
 * @param: lsda: A pointer to the LanguageSpecificDAta specified within the FDE.
 * @return: * :  One of `DWARF_PERSO_*' */
typedef NONNULL((1, 2)) unsigned int
/*NOTHROW*/ (KCALL *dwarf_perso_t)(struct unwind_fde_struct *__restrict fde,
                                  struct kcpustate *__restrict state,
                                  void *lsda);
#endif /* __CC__ */
#define DWARF_PERSO_EXECUTE_HANDLER     0x0000 /* An exception handler was found, and `state' was updated */
#define DWARF_PERSO_EXECUTE_HANDLER_NOW 0x0001 /* Same as `DWARF_PERSO_EXECUTE_HANDLER', but don't adjust for `DW_CFA_GNU_args_size' */
#define DWARF_PERSO_CONTINUE_UNWIND     0x0002 /* Continue unwinding to search for an exception handler. */
#define DWARF_PERSO_ABORT_SEARCH        0x0003 /* Abort the search for exception handlers, and panic(). */



#ifdef __ASSEMBLER__
#define EXCEPT_HANDLERS_START \
	.global x86_asm_except_personality; \
	.cfi_personality 0,  x86_asm_except_personality; \
	.cfi_lsda 0,  1f; \
	.pushsection .rodata.cold; \
1:
#ifdef __x86_64__
#define EXCEPT_HANDLERS_CATCHALL(start, end, entry) \
	.local entry; .quad entry; \
	.local start; .quad start; \
	.local end;   .quad end; \
	.quad -1;
#define EXCEPT_HANDLERS_CATCH(code, start, end, entry) \
	.local entry; .quad entry; \
	.local start; .quad start; \
	.local end;   .quad end; \
	.quad ERROR_CODEOF(code);
#else /* __x86_64__ */
#define EXCEPT_HANDLERS_CATCHALL(start, end, entry) \
	.local entry; .long entry; \
	.local start; .long start; \
	.local end;   .long end; \
	.long -1;
#define EXCEPT_HANDLERS_CATCH(code, start, end, entry) \
	.local entry; .long entry; \
	.local start; .long start; \
	.local end;   .long end; \
	.long ERROR_CODEOF(code);
#endif /* !__x86_64__ */
#define EXCEPT_HANDLERS_END \
	.long 0; \
	.popsection;
#endif /* __ASSEMBLER__ */


#ifdef __CC__
struct x86_asm_except_entry {
	__UINTPTR_TYPE__ ee_entry; /* Exception handler entry PC (or 0 as sentinel) */
	__UINTPTR_TYPE__ ee_start; /* Exception handler start PC */
	__UINTPTR_TYPE__ ee_end;   /* Exception handler end PC */
	__UINTPTR_TYPE__ ee_mask;  /* Catch mask, or (uintptr_t)-1 to catch anything */
};

/* A helpful, predefined personality function that is meant to be used for assembly
 * function which need to be able to handle exceptions in a fairly user-friendly manner.
 * NOTE: In order to define handlers, make use of the macros defined above.
 * NOTE: When the handler is entered, `%eax', `%edx' and `%ecx' may have been clobbered,
 *       though all other registers have the same value as they would have had after a
 *       throwing function had returned normally, or after a throwing instruction had
 *       completed normally (with the obvious exception of `%eip')
 *       Separately, you may include `DW_CFA_GNU_args_size' directies within your function,
 *       which are recognized as adjustments for `%esp' and are applied prior to execution
 *       or the specified handler. */
FUNDEF unsigned int
NOTHROW(KCALL x86_asm_except_personality)(struct unwind_fde_struct *__restrict fde,
                                          struct kcpustate *__restrict state,
                                          void *lsda);
#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_EXCEPT_H */
