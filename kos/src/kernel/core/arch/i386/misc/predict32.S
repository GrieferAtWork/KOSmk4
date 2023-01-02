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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_PREDICT32_S
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_PREDICT32_S 1

#include <kernel/compiler.h>

#include <cfi.h>

#ifdef CONFIG_NO_KERNEL_BRANCH_PROFILING

/* struct branch_prediction *pred = %ecx */
/* int                       expr = %dl */
.section .text.cold
.cfi_startproc
PUBLIC_FUNCTION(__predict_update_dl)
PUBLIC_FUNCTION(__predict_update_dx)
PUBLIC_FUNCTION(__predict_update_edx)
PUBLIC_FUNCTION(__predict_update_al)
PUBLIC_FUNCTION(__predict_update_ax)
PUBLIC_FUNCTION(__predict_update_eax)
	ret
END(__predict_update_eax)
END(__predict_update_ax)
END(__predict_update_al)
END(__predict_update_edx)
END(__predict_update_dx)
END(__predict_update_dl)
.cfi_endproc

#else /* CONFIG_NO_KERNEL_BRANCH_PROFILING */

/* struct branch_prediction *pred = %ecx */
/* int                       expr = %dl */
.section .text.hot
.cfi_startproc
#define DEFINE_VARIANT(name,cmpX_reg) \
PUBLIC_FUNCTION(name);                \
	.cfi_remember_state;              \
	pushfl_cfi_r;                     \
	pushl_cfi_r %eax;                 \
	cmpX_reg, 12(%ecx);               \
	jmp    1f;                        \
	.cfi_restore_state;               \
END(name);                            \
/**/
DEFINE_VARIANT(__predict_update_dl, cmpb %dl)
DEFINE_VARIANT(__predict_update_dx, cmpw %dx)
DEFINE_VARIANT(__predict_update_edx, cmpl %edx)
DEFINE_VARIANT(__predict_update_al, cmpb %al)
DEFINE_VARIANT(__predict_update_ax, cmpw %ax)
#undef DEFINE_VARIANT
PUBLIC_FUNCTION(__predict_update_eax)
	pushfl_cfi_r
	pushl_cfi_r %eax
	cmpl   %eax, 12(%ecx)
1:	movl   $(0), %eax
	sete   %al
	/* Increment the miss/hit counter */
	lock   incl 4(%ecx,%eax,4)
	popl_cfi_r %eax
	popfl_cfi_r
	ret
END(__predict_update_eax)
.cfi_endproc

#endif /* !CONFIG_NO_KERNEL_BRANCH_PROFILING */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_PREDICT32_S */
