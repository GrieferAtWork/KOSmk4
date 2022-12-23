/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBDL_ARCH_I386_RT64_S
#define GUARD_LIBDL_ARCH_I386_RT64_S 1
#define __ASSEMBLER__ 1

#include "../../api.h"
/**/

#include <hybrid/compiler.h>

#include <cfi.h>

#include "../../builtin.h"
/**/

INTERN(dl_require_global)

#define DEFINE_GLOBAL_SYMBOL_IMPORT(name)                 \
	.section .rodata.str.1;                               \
	991: .asciz #name;                                    \
	.section .text;                                       \
	INTERN_FUNCTION(name);                                \
		.cfi_startproc;                                   \
		pushq       $(0);   /* RETURN_PC_OVERRIDE */      \
		pushfq_cfi_r;                                     \
		pushq_cfi_r %rax;                                 \
		pushq_cfi_r %rcx;                                 \
		pushq_cfi_r %rdx;                                 \
		pushq_cfi_r %rsi;                                 \
		pushq_cfi_r %rdi;                                 \
		pushq_cfi_r %r8;                                  \
		pushq_cfi_r %r9;                                  \
		pushq_cfi_r %r10;                                 \
		pushq_cfi_r %r11;                                 \
		leaq   991b(%rip), %rdi;                          \
		call   dl_require_global;                         \
		movq   %rax, 80(%rsp); /* RETURN_PC_OVERRIDE */   \
		.cfi_rel_offset %rip, 80;                         \
		popq_cfi_r %r11;                                  \
		popq_cfi_r %r10;                                  \
		popq_cfi_r %r9;                                   \
		popq_cfi_r %r8;                                   \
		popq_cfi_r %rdi;                                  \
		popq_cfi_r %rsi;                                  \
		popq_cfi_r %rdx;                                  \
		popq_cfi_r %rcx;                                  \
		popq_cfi_r %rax;                                  \
		popfq_cfi_r;                                      \
		ret;                                              \
		.cfi_endproc;                                     \
	END(name)
BUILTIN_GLOBALS_ENUMERATE(DEFINE_GLOBAL_SYMBOL_IMPORT)
#undef DEFINE_GLOBAL_SYMBOL_IMPORT



INTERN_FUNCTION(libdl___tls_get_addr)
	.cfi_startproc
	/* >> typedef struct {
	 * >>     uintptr_t ti_module;
	 * >>     uintptr_t ti_offset;
	 * >> } tls_index;
	 * ARGS: tls_index *%rdi;
	 * RETURN: Address of the indicated object. */
	pushq_cfi 8(%rdi)

	/* Load the TLS base address for the given object. */
	movq   0(%rdi), %rdi
	INTERN(libdl_dltlsbase)
	call   libdl_dltlsbase

	/* Add the offset of the pointed-to symbol. */
	popq_cfi %rcx
	addq   %rcx, %rax

	ret
	.cfi_endproc
END(libdl___tls_get_addr)
DEFINE_PUBLIC_ALIAS(__tls_get_addr, libdl___tls_get_addr)





.section .text
	/* The heart-piece of lazy symbol relocations:
	 *   - This function is called by user-code the first time an R_X86_64_JMP_SLOT
	 *     relocation  is  accessed, at  which  point the  relocation  is resolved.
	 *   - See the explanation about `PLTGOT' in `rt32.S' for how this actually works.
	 */
INTERN_FUNCTION(dl_load_lazy_relocation)
	/* register/stack state:
	 *  - 0(%rsp)      == MODULE
	 *  - 8(%rsp)      == Index into `self->dm_elf.de_jmprel' for the associated jump relocation
	 *  - 16(%rsp)     == User-return-address
	 *  - 24 + ?(%rsp) == Undefined/user-owned
	 *
	 * HINT: In Glibc, this function's equivalent is called `_dl_runtime_resolve' */
	.cfi_startproc
	.cfi_adjust_cfa_offset 16 /* MODULE + JMPREL_index */
	/* Save registers */
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11

	pushfq_cfi_r

	movq   (80 + 0)(%rsp), %rdi /* MODULE */
	movq   (80 + 8)(%rsp), %rsi /* JMPREL_index */

	/* Patch the relocation. */
	INTERN(dl_bind_lazy_relocation)
	call   dl_bind_lazy_relocation

	popfq_cfi_r
	.cfi_register %rip, %rax

	popq_cfi_r %r11
	popq_cfi_r %r10
	popq_cfi_r %r9
	popq_cfi_r %r8
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx

	xchgq  %rax, (%rsp) /* RESTORE(EAX); 0(%rsp) = RESOLVED_ADDRESS */
	.cfi_same_value %rax
	.cfi_rel_offset %rip, 0
	ret    $(16)        /* EIP = [ESP]; ESP += (8 + 16);
	                     * Cleanup: RESOLVED_ADDRESS + MODULE + JMPREL_index */
	.cfi_endproc
END(dl_load_lazy_relocation)

#endif /* !GUARD_LIBDL_ARCH_I386_RT64_S */
