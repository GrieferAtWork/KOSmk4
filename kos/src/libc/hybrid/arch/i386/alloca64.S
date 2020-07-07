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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_ALLOCA64_S
#define GUARD_LIBC_HYBRID_ARCH_I386_ALLOCA64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>
#include <asm/cfi.h>
#include <asm/instr/compat.h>

#undef alloca
#undef _alloca

.section .text.crt.utility.alloca
INTERN_FUNCTION(libc_alloca)
	.cfi_startproc
	popq_cfi %rcx            /* return address */
	.cfi_register %rip, %rcx
	addq   $(4 - 1), %rdi
	andq   $(~(4 - 1)), %rdi /* %rdi = CEIL_ALIGN(num_bytes, 4) */
	subq   %rdi, %rsp        /* Allocate stack memory */
	.cfi_same_value %rsp
	movq   %rsp, %rax        /* Also re-return the new stack pointer in `%rax' */
	jmpq   *%rcx             /* Return to caller */
	.cfi_endproc
END(libc_alloca)

DEFINE_PUBLIC_ALIAS(alloca, libc_alloca)
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(_alloca, libc_alloca)
#endif /* !__KERNEL__ */

#ifndef __KERNEL__
.section .text.crt.dos.utility.alloca
INTERN_FUNCTION(libd_alloca)
	.cfi_startproc
	popq_cfi %rdx            /* return address */
	.cfi_register %rip, %rdx
	addq   $(4 - 1), %rcx
	andq   $(~(4 - 1)), %rcx /* %rcx = CEIL_ALIGN(num_bytes, 4) */
	subq   %rcx, %rsp        /* Allocate stack memory */
	.cfi_same_value %rsp
	movq   %rsp, %rax        /* Also re-return the new stack pointer in `%rax' */
	jmpq   *%rdx             /* Return to caller */
	.cfi_endproc
END(libd_alloca)

DEFINE_PUBLIC_ALIAS(DOS$alloca, libd_alloca)
DEFINE_PUBLIC_ALIAS(DOS$_alloca, libd_alloca)
#endif /* !__KERNEL__ */



#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_ALLOCA64_S */
