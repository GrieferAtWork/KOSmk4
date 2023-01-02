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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_NOPF_S
#define GUARD_LIBC_HYBRID_ARCH_I386_NOPF_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <cfi.h>
#include <asm/instr/compat.h>

#ifdef __KERNEL__
#define KERNEL_cld cld /* Because the kernel is built with -mcld */
#else /* __KERNEL__ */
#define KERNEL_cld /* nothing */
#endif /* !__KERNEL__ */

.section .text.string.nopf
.cfi_startproc
INTERN_LABEL(libc_x86_nopf_begin):

INTERN_FUNCTION(libc_x86_nopf_movb_Pax_al)
	clc
	movb   (%Pax), %al
	ret
END(libc_x86_nopf_movb_Pax_al)

INTERN_FUNCTION(libc_x86_nopf_movw_Pax_ax)
	clc
	movw   (%Pax), %ax
	ret
END(libc_x86_nopf_movw_Pax_ax)

INTERN_FUNCTION(libc_x86_nopf_movl_Pax_eax)
	clc
	movl   (%Pax), %eax
	ret
END(libc_x86_nopf_movl_Pax_eax)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_movq_Pax_rax)
	clc
	movq   (%Pax), %rax
	ret
END(libc_x86_nopf_movq_Pax_rax)
#endif /* __x86_64__ */

INTERN_FUNCTION(libc_x86_nopf_movb_al_Pcx)
	clc
	movb   %al, (%Pcx)
	ret
END(libc_x86_nopf_movb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_movw_ax_Pcx)
	clc
	movw   %ax, (%Pcx)
	ret
END(libc_x86_nopf_movw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_movl_eax_Pcx)
	clc
	movl   %eax, (%Pcx)
	ret
END(libc_x86_nopf_movl_eax_Pcx)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_movq_rax_Pcx)
	clc
	movq   %rax, (%Pcx)
	ret
END(libc_x86_nopf_movq_rax_Pcx)
#endif /* __x86_64__ */

INTERN_FUNCTION(libc_x86_nopf_movb_fsPax_al)
	clc
	movb   %fs:(%Pax), %al
	ret
END(libc_x86_nopf_movb_Pax_al)

INTERN_FUNCTION(libc_x86_nopf_movw_fsPax_ax)
	clc
	movw   %fs:(%Pax), %ax
	ret
END(libc_x86_nopf_movw_Pax_ax)

INTERN_FUNCTION(libc_x86_nopf_movl_fsPax_eax)
	clc
	movl   %fs:(%Pax), %eax
	ret
END(libc_x86_nopf_movl_Pax_eax)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_movq_fsPax_rax)
	clc
	movq   %fs:(%Pax), %rax
	ret
END(libc_x86_nopf_movq_Pax_rax)
#endif /* __x86_64__ */

INTERN_FUNCTION(libc_x86_nopf_movb_al_fsPcx)
	clc
	movb   %al, %fs:(%Pcx)
	ret
END(libc_x86_nopf_movb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_movw_ax_fsPcx)
	clc
	movw   %ax, %fs:(%Pcx)
	ret
END(libc_x86_nopf_movw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_movl_eax_fsPcx)
	clc
	movl   %eax, %fs:(%Pcx)
	ret
END(libc_x86_nopf_movl_eax_Pcx)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_movq_rax_fsPcx)
	clc
	movq   %rax, %fs:(%Pcx)
	ret
END(libc_x86_nopf_movq_rax_Pcx)
#endif /* __x86_64__ */

INTERN_FUNCTION(libc_x86_nopf_movb_gsPax_al)
	clc
	movb   %gs:(%Pax), %al
	ret
END(libc_x86_nopf_movb_Pax_al)

INTERN_FUNCTION(libc_x86_nopf_movw_gsPax_ax)
	clc
	movw   %gs:(%Pax), %ax
	ret
END(libc_x86_nopf_movw_Pax_ax)

INTERN_FUNCTION(libc_x86_nopf_movl_gsPax_eax)
	clc
	movl   %gs:(%Pax), %eax
	ret
END(libc_x86_nopf_movl_Pax_eax)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_movq_gsPax_rax)
	clc
	movq   %gs:(%Pax), %rax
	ret
END(libc_x86_nopf_movq_Pax_rax)
#endif /* __x86_64__ */

INTERN_FUNCTION(libc_x86_nopf_movb_al_gsPcx)
	clc
	movb   %al, %gs:(%Pcx)
	ret
END(libc_x86_nopf_movb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_movw_ax_gsPcx)
	clc
	movw   %ax, %gs:(%Pcx)
	ret
END(libc_x86_nopf_movw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_movl_eax_gsPcx)
	clc
	movl   %eax, %gs:(%Pcx)
	ret
END(libc_x86_nopf_movl_eax_Pcx)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_movq_rax_gsPcx)
	clc
	movq   %rax, %gs:(%Pcx)
	ret
END(libc_x86_nopf_movq_rax_Pcx)
#endif /* __x86_64__ */



/* Atomic *_nopf operations. */
INTERN_FUNCTION(libc_x86_nopf_lock_xchgb_al_Pcx)
	clc
	/*lock*/ xchgb    %al, (%Pcx)
	ret
END(libc_x86_nopf_lock_xchgb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xchgw_ax_Pcx)
	clc
	/*lock*/ xchgw    %ax, (%Pcx)
	ret
END(libc_x86_nopf_lock_xchgw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xchgl_eax_Pcx)
	clc
	/*lock*/ xchgl    %eax, (%Pcx)
	ret
END(libc_x86_nopf_lock_xchgl_eax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xaddb_al_Pcx)
	lock xaddb    %al, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xaddb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xaddw_ax_Pcx)
	lock xaddw    %ax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xaddw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xaddl_eax_Pcx)
	lock xaddl    %eax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xaddl_eax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_cmpxchgb_dl_Pcx)
	lock cmpxchgb %dl, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_cmpxchgb_dl_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_cmpxchgw_dx_Pcx)
	lock cmpxchgw %dx, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_cmpxchgw_dx_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_cmpxchgl_edx_Pcx)
	lock cmpxchgl %edx, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_cmpxchgl_edx_Pcx)


INTERN_FUNCTION(libc_x86_nopf_lock_andb_al_Pcx)
	lock andb     %al, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_andb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_andw_ax_Pcx)
	lock andw     %ax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_andw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_andl_eax_Pcx)
	lock andl     %eax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_andl_eax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_orb_al_Pcx)
	lock orb      %al, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_orb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_orw_ax_Pcx)
	lock orw      %ax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_orw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_orl_eax_Pcx)
	lock orl      %eax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_orl_eax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xorb_al_Pcx)
	lock xorb     %al, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xorb_al_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xorw_ax_Pcx)
	lock xorw     %ax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xorw_ax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xorl_eax_Pcx)
	lock xorl     %eax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xorl_eax_Pcx)

#ifdef __x86_64__
INTERN_FUNCTION(libc_x86_nopf_lock_xchgq_rax_Pcx)
	clc
	/*lock*/ xchgq    %rax, (%Pcx)
	ret
END(libc_x86_nopf_lock_xchgq_rax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xaddq_rax_Pcx)
	lock xaddq    %rax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xaddq_rax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_cmpxchgq_rdx_Pcx)
	lock cmpxchgq %rdx, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_cmpxchgq_rdx_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_andq_rax_Pcx)
	lock andq     %rax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_andq_rax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_orq_rax_Pcx)
	lock orq      %rax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_orq_rax_Pcx)

INTERN_FUNCTION(libc_x86_nopf_lock_xorq_rax_Pcx)
	lock xorq     %rax, (%Pcx)
	clc
	ret
END(libc_x86_nopf_lock_xorq_rax_Pcx)
#endif /* __x86_64__ */




INTERN_LABEL(libc_x86_nopf_end_clc):




INTERN_FUNCTION(libc_x86_nopf_rep_insb)
	KERNEL_cld
	rep    insb
	ret
END(libc_x86_nopf_rep_insb)

INTERN_FUNCTION(libc_x86_nopf_rep_insw)
	KERNEL_cld
	rep    insw
	ret
END(libc_x86_nopf_rep_insw)

INTERN_FUNCTION(libc_x86_nopf_rep_insl)
	KERNEL_cld
	rep    insl
	ret
END(libc_x86_nopf_rep_insl)

INTERN_FUNCTION(libc_x86_nopf_rep_outsb)
	KERNEL_cld
	rep    outsb
	ret
END(libc_x86_nopf_rep_outsb)

INTERN_FUNCTION(libc_x86_nopf_rep_outsw)
	KERNEL_cld
	rep    outsw
	ret
END(libc_x86_nopf_rep_outsw)

INTERN_FUNCTION(libc_x86_nopf_rep_outsl)
	KERNEL_cld
	rep    outsl
	ret
END(libc_x86_nopf_rep_outsl)


INTERN_FUNCTION(libc_x86_nopf_repe_cmpsb)
	KERNEL_cld
	repe   cmpsb
	ret
END(libc_x86_nopf_repe_cmpsb)

INTERN_FUNCTION(libc_x86_nopf_rep_stosb)
	KERNEL_cld
	rep    stosb
	ret
END(libc_x86_nopf_rep_stosb)

/* Assembly function:
 * >> INTERN_FUNCTION(libc_x86_nopf_rep_movsb)
 * >> #ifdef __KERNEL__
 * >>     cld
 * >> #endif // __KERNEL__
 * >>     rep    movsb
 * >>     ret
 * >> END(x86_nopf_rep_movsb)
 * Yes.  -  That's  literally  the   implementation,
 * however there is something very special about it:
 *  - Whenever a #PF happens, the kernel will see if it originated from
 *    that `rep movsb' instruction.
 *    If it did, then instead of actually handling the #PF, the kernel will
 *    instead advance  the instruction  pointer to  the `ret'  instruction,
 *    causing the `rep' to be aborted.
 * IN:
 *   - USER CHECKED void       *%Pdi:  Destination pointer
 *   - USER CHECKED void const *%Psi:  Source pointer
 *   - size_t                   %Pcx:  Copy size
 * OUT:
 *   - %Pdi:  == IN(%Pdi) + (IN(%Pcx) - OUT(%Pcx))
 *   - %Psi:  == IN(%Psi) + (IN(%Pcx) - OUT(%Pcx))
 *   - %Pcx:  Number of bytes that were not copied.
 *   - %cr2:  if (OUT(%Pcx) == 0)
 *                <UNCHANGED>
 *            else if (OUT(%cr2) == OUT(%Pdi))
 *                <#PF in `dst'>
 *            else if (OUT(%cr2) == OUT(%Psi))
 *                <#PF in `src'>
 */
INTERN_FUNCTION(libc_x86_nopf_rep_movsb)
	KERNEL_cld
	rep    movsb
INTERN_LABEL(libc_x86_nopf_end):
INTERN_FUNCTION(libc_x86_nopf_ret)
	ret
END(libc_x86_nopf_rep_movsb)
END(libc_x86_nopf_ret)

INTERN_FUNCTION(libc_x86_nopf_ret_stc)
	stc
	ret
END(libc_x86_nopf_ret_stc)
.cfi_endproc



DEFINE_PUBLIC_ALIAS(x86_nopf_begin, libc_x86_nopf_begin);
DEFINE_PUBLIC_ALIAS(x86_nopf_movb_Pax_al, libc_x86_nopf_movb_Pax_al);
DEFINE_PUBLIC_ALIAS(x86_nopf_movw_Pax_ax, libc_x86_nopf_movw_Pax_ax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movl_Pax_eax, libc_x86_nopf_movl_Pax_eax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movb_al_Pcx, libc_x86_nopf_movb_al_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movw_ax_Pcx, libc_x86_nopf_movw_ax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movl_eax_Pcx, libc_x86_nopf_movl_eax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movb_fsPax_al, libc_x86_nopf_movb_fsPax_al);
DEFINE_PUBLIC_ALIAS(x86_nopf_movw_fsPax_ax, libc_x86_nopf_movw_fsPax_ax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movl_fsPax_eax, libc_x86_nopf_movl_fsPax_eax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movb_al_fsPcx, libc_x86_nopf_movb_al_fsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movw_ax_fsPcx, libc_x86_nopf_movw_ax_fsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movl_eax_fsPcx, libc_x86_nopf_movl_eax_fsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movb_gsPax_al, libc_x86_nopf_movb_gsPax_al);
DEFINE_PUBLIC_ALIAS(x86_nopf_movw_gsPax_ax, libc_x86_nopf_movw_gsPax_ax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movl_gsPax_eax, libc_x86_nopf_movl_gsPax_eax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movb_al_gsPcx, libc_x86_nopf_movb_al_gsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movw_ax_gsPcx, libc_x86_nopf_movw_ax_gsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movl_eax_gsPcx, libc_x86_nopf_movl_eax_gsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xchgb_al_Pcx, libc_x86_nopf_lock_xchgb_al_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xchgw_ax_Pcx, libc_x86_nopf_lock_xchgw_ax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xchgl_eax_Pcx, libc_x86_nopf_lock_xchgl_eax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xaddb_al_Pcx, libc_x86_nopf_lock_xaddb_al_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xaddw_ax_Pcx, libc_x86_nopf_lock_xaddw_ax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xaddl_eax_Pcx, libc_x86_nopf_lock_xaddl_eax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_cmpxchgb_dl_Pcx, libc_x86_nopf_lock_cmpxchgb_dl_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_cmpxchgw_dx_Pcx, libc_x86_nopf_lock_cmpxchgw_dx_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_cmpxchgl_edx_Pcx, libc_x86_nopf_lock_cmpxchgl_edx_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_andb_al_Pcx, libc_x86_nopf_lock_andb_al_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_andw_ax_Pcx, libc_x86_nopf_lock_andw_ax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_andl_eax_Pcx, libc_x86_nopf_lock_andl_eax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_orb_al_Pcx, libc_x86_nopf_lock_orb_al_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_orw_ax_Pcx, libc_x86_nopf_lock_orw_ax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_orl_eax_Pcx, libc_x86_nopf_lock_orl_eax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xorb_al_Pcx, libc_x86_nopf_lock_xorb_al_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xorw_ax_Pcx, libc_x86_nopf_lock_xorw_ax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xorl_eax_Pcx, libc_x86_nopf_lock_xorl_eax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_end_clc, libc_x86_nopf_end_clc);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_insb, libc_x86_nopf_rep_insb);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_insw, libc_x86_nopf_rep_insw);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_insl, libc_x86_nopf_rep_insl);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_outsb, libc_x86_nopf_rep_outsb);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_outsw, libc_x86_nopf_rep_outsw);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_outsl, libc_x86_nopf_rep_outsl);
DEFINE_PUBLIC_ALIAS(x86_nopf_repe_cmpsb, libc_x86_nopf_repe_cmpsb);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_stosb, libc_x86_nopf_rep_stosb);
DEFINE_PUBLIC_ALIAS(x86_nopf_rep_movsb, libc_x86_nopf_rep_movsb);
DEFINE_PUBLIC_ALIAS(x86_nopf_end, libc_x86_nopf_end);
DEFINE_PUBLIC_ALIAS(x86_nopf_ret, libc_x86_nopf_ret);
DEFINE_PUBLIC_ALIAS(x86_nopf_ret_stc, libc_x86_nopf_ret_stc);
#ifdef __x86_64__
DEFINE_PUBLIC_ALIAS(x86_nopf_movq_Pax_rax, libc_x86_nopf_movq_Pax_rax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movq_rax_Pcx, libc_x86_nopf_movq_rax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movq_fsPax_rax, libc_x86_nopf_movq_fsPax_rax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movq_rax_fsPcx, libc_x86_nopf_movq_rax_fsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_movq_gsPax_rax, libc_x86_nopf_movq_gsPax_rax);
DEFINE_PUBLIC_ALIAS(x86_nopf_movq_rax_gsPcx, libc_x86_nopf_movq_rax_gsPcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xchgq_rax_Pcx, libc_x86_nopf_lock_xchgq_rax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xaddq_rax_Pcx, libc_x86_nopf_lock_xaddq_rax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_cmpxchgq_rdx_Pcx, libc_x86_nopf_lock_cmpxchgq_rdx_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_andq_rax_Pcx, libc_x86_nopf_lock_andq_rax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_orq_rax_Pcx, libc_x86_nopf_lock_orq_rax_Pcx);
DEFINE_PUBLIC_ALIAS(x86_nopf_lock_xorq_rax_Pcx, libc_x86_nopf_lock_xorq_rax_Pcx);
#endif /* __x86_64__ */


#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_NOPF_S */
