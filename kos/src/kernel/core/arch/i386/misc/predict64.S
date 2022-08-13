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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_PREDICT64_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_PREDICT64_S 1

#include <kernel/compiler.h>

#include <cfi.h>

#ifdef CONFIG_NO_KERNEL_BRANCH_PROFILING

/* struct branch_prediction *pred = %rdi */
.section .text.cold
.cfi_startproc
PUBLIC_FUNCTION(__predict_update_sil)
PUBLIC_FUNCTION(__predict_update_si)
PUBLIC_FUNCTION(__predict_update_esi)
PUBLIC_FUNCTION(__predict_update_rsi)
PUBLIC_FUNCTION(__predict_update_dl)
PUBLIC_FUNCTION(__predict_update_dx)
PUBLIC_FUNCTION(__predict_update_edx)
PUBLIC_FUNCTION(__predict_update_rdx)
PUBLIC_FUNCTION(__predict_update_cl)
PUBLIC_FUNCTION(__predict_update_cx)
PUBLIC_FUNCTION(__predict_update_ecx)
PUBLIC_FUNCTION(__predict_update_rcx)
PUBLIC_FUNCTION(__predict_update_al)
PUBLIC_FUNCTION(__predict_update_ax)
PUBLIC_FUNCTION(__predict_update_eax)
PUBLIC_FUNCTION(__predict_update_rax)
	ret
END(__predict_update_rax)
END(__predict_update_eax)
END(__predict_update_ax)
END(__predict_update_al)
END(__predict_update_rcx)
END(__predict_update_ecx)
END(__predict_update_cx)
END(__predict_update_cl)
END(__predict_update_rdx)
END(__predict_update_edx)
END(__predict_update_dx)
END(__predict_update_dl)
END(__predict_update_rsi)
END(__predict_update_esi)
END(__predict_update_si)
END(__predict_update_sil)
.cfi_endproc

#else /* CONFIG_NO_KERNEL_BRANCH_PROFILING */

/* struct branch_prediction *pred = %rdi */
.section .text.hot
.cfi_startproc
#define DEFINE_VARIANT(name,cmpX_reg) \
PUBLIC_FUNCTION(name);                \
	.cfi_remember_state;              \
	pushfq_cfi_r;                     \
	pushq_cfi_r %rax;                 \
	cmpX_reg, 12(%rdi);               \
	jmp    1f;                        \
	.cfi_restore_state;               \
END(name);                            \
/**/
DEFINE_VARIANT(__predict_update_sil, cmpb %sil)
DEFINE_VARIANT(__predict_update_si, cmpw %si)
DEFINE_VARIANT(__predict_update_esi, cmpl %esi)
DEFINE_VARIANT(__predict_update_rsi, cmpl %esi)

DEFINE_VARIANT(__predict_update_dl, cmpb %dl)
DEFINE_VARIANT(__predict_update_dx, cmpw %dx)
DEFINE_VARIANT(__predict_update_edx, cmpl %edx)
DEFINE_VARIANT(__predict_update_rdx, cmpl %edx)

DEFINE_VARIANT(__predict_update_cl, cmpb %cl)
DEFINE_VARIANT(__predict_update_cx, cmpw %cx)
DEFINE_VARIANT(__predict_update_ecx, cmpl %ecx)
DEFINE_VARIANT(__predict_update_rcx, cmpl %ecx)

DEFINE_VARIANT(__predict_update_al, cmpb %al)
DEFINE_VARIANT(__predict_update_ax, cmpw %ax)
DEFINE_VARIANT(__predict_update_eax, cmpl %eax)
#undef DEFINE_VARIANT
PUBLIC_FUNCTION(__predict_update_rax)
	pushfq_cfi_r
	pushq_cfi_r %rax
	cmpl   %eax, 12(%rdi)
1:	movq   $(0), %rax
	sete   %al
	/* Increment the miss/hit counter */
	lock   incl 4(%rdi,%rax,4)
	popq_cfi_r %rax
	popfq_cfi_r
	ret
END(__predict_update_rax)
.cfi_endproc

#endif /* !CONFIG_NO_KERNEL_BRANCH_PROFILING */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_PREDICT64_S */
