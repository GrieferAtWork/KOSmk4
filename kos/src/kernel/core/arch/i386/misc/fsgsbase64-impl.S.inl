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
#include <kernel/compiler.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>

#ifdef __INTELLISENSE__
#define TARGET_REGISTER rax
#define TARGET_REGISTER_IS_RAX 1
//#define TARGET_REGISTER_IS_RDX 1
//#define TARGET_REGISTER_IS_RCX 1
#endif
#ifndef TARGET_REGISTER
#error "Must #define TARGET_REGISTER before #include-ing this file"
#endif /* !TARGET_REGISTER */

.section .text
INTERN_FUNCTION(PP_CAT2(__x64_rdfsbase_, TARGET_REGISTER))
	.cfi_startproc
	pushfq_cfi_r
#ifndef TARGET_REGISTER_IS_RAX
	pushq_cfi_r %rax
#endif /* !TARGET_REGISTER_IS_RAX */
#ifndef TARGET_REGISTER_IS_RCX
	pushq_cfi_r %rcx
#endif /* !TARGET_REGISTER_IS_RCX */
#ifndef TARGET_REGISTER_IS_RDX
	pushq_cfi_r %rdx
#endif /* !TARGET_REGISTER_IS_RDX */
	xorq   %rax, %rax
	movl   $(IA32_FS_BASE), %ecx
	rdmsr
	shlq   $(32), %rdx
#ifdef TARGET_REGISTER_IS_RDX
	orq    %rax, %rdx
#else /* TARGET_REGISTER_IS_RDX */
	orq    %rdx, %rax
#ifndef TARGET_REGISTER_IS_RAX
	movq   %rax, %TARGET_REGISTER
#endif /* !TARGET_REGISTER_IS_RAX */
#endif /* !TARGET_REGISTER_IS_RDX */
#ifndef TARGET_REGISTER_IS_RDX
	popq_cfi_r %rdx
#endif /* !TARGET_REGISTER_IS_RDX */
#ifndef TARGET_REGISTER_IS_RCX
	popq_cfi_r %rcx
#endif /* !TARGET_REGISTER_IS_RCX */
#ifndef TARGET_REGISTER_IS_RAX
	popq_cfi_r %rax
#endif /* !TARGET_REGISTER_IS_RAX */
	popfq_cfi_r
	ret
	.cfi_endproc
END(PP_CAT2(__x64_rdfsbase_, TARGET_REGISTER))



.section .text
INTERN_FUNCTION(PP_CAT2(__x64_rdgsbase_, TARGET_REGISTER))
	.cfi_startproc
	pushfq_cfi_r
#ifndef TARGET_REGISTER_IS_RAX
	pushq_cfi_r %rax
#endif /* !TARGET_REGISTER_IS_RAX */
#ifndef TARGET_REGISTER_IS_RCX
	pushq_cfi_r %rcx
#endif /* !TARGET_REGISTER_IS_RCX */
#ifndef TARGET_REGISTER_IS_RDX
	pushq_cfi_r %rdx
#endif /* !TARGET_REGISTER_IS_RDX */
	xorq   %rax, %rax
	movl   $(IA32_GS_BASE), %ecx
	rdmsr
	shlq   $(32), %rdx
#ifdef TARGET_REGISTER_IS_RDX
	orq    %rax, %rdx
#else /* TARGET_REGISTER_IS_RDX */
	orq    %rdx, %rax
#ifndef TARGET_REGISTER_IS_RAX
	movq   %rax, %TARGET_REGISTER
#endif /* !TARGET_REGISTER_IS_RAX */
#endif /* !TARGET_REGISTER_IS_RDX */
#ifndef TARGET_REGISTER_IS_RDX
	popq_cfi_r %rdx
#endif /* !TARGET_REGISTER_IS_RDX */
#ifndef TARGET_REGISTER_IS_RCX
	popq_cfi_r %rcx
#endif /* !TARGET_REGISTER_IS_RCX */
#ifndef TARGET_REGISTER_IS_RAX
	popq_cfi_r %rax
#endif /* !TARGET_REGISTER_IS_RAX */
	popfq_cfi_r
	ret
	.cfi_endproc
END(PP_CAT2(__x64_rdgsbase_, TARGET_REGISTER))




.section .text
INTERN_FUNCTION(PP_CAT2(__x64_wrfsbase_, TARGET_REGISTER))
	.cfi_startproc
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
#if defined(TARGET_REGISTER_IS_RAX)
	movq   %rax, %rdx
#elif defined(TARGET_REGISTER_IS_RDX)
	movq   %rdx, %rax
#else
	movq   %TARGET_REGISTER, %rax
	movq   %TARGET_REGISTER, %rdx
#endif
	shrq   $(32), %rdx
	movl   $(IA32_FS_BASE), %ecx
	wrmsr
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	popq_cfi_r %rax
	popfq_cfi_r
	ret
	.cfi_endproc
END(PP_CAT2(__x64_wrfsbase_, TARGET_REGISTER))


.section .text
INTERN_FUNCTION(PP_CAT2(__x64_wrgsbase_, TARGET_REGISTER))
	.cfi_startproc
	pushfq_cfi_r
	pushq_cfi_r %rax
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
#if defined(TARGET_REGISTER_IS_RAX)
	movq   %rax, %rdx
#elif defined(TARGET_REGISTER_IS_RDX)
	movq   %rdx, %rax
#else
	movq   %TARGET_REGISTER, %rax
	movq   %TARGET_REGISTER, %rdx
#endif
	shrq   $(32), %rdx
	movl   $(IA32_GS_BASE), %ecx
	wrmsr
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	popq_cfi_r %rax
	popfq_cfi_r
	ret
	.cfi_endproc
END(PP_CAT2(__x64_wrgsbase_, TARGET_REGISTER))


#undef TARGET_REGISTER_IS_RCX
#undef TARGET_REGISTER_IS_RDX
#undef TARGET_REGISTER_IS_RAX
#undef TARGET_REGISTER
