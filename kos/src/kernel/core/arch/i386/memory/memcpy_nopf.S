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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MEMCPY_NOPF_S
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MEMCPY_NOPF_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <asm/cfi.h>
#include <asm/instr/compat.h>


.section .text
.cfi_startproc
PUBLIC_LABEL(x86_nopf_begin):

PUBLIC_FUNCTION(x86_nopf_movb_Pax_al)
	clc
	movb   (%Pax), %al
	ret
END(x86_nopf_movb_Pax_al)

PUBLIC_FUNCTION(x86_nopf_movw_Pax_ax)
	clc
	movw   (%Pax), %ax
	ret
END(x86_nopf_movw_Pax_ax)

PUBLIC_FUNCTION(x86_nopf_movl_Pax_eax)
	clc
	movl   (%Pax), %eax
	ret
END(x86_nopf_movl_Pax_eax)

#ifdef __x86_64__
PUBLIC_FUNCTION(x86_nopf_movq_Pax_rax)
	clc
	movq   (%Pax), %rax
	ret
END(x86_nopf_movq_Pax_rax)
#endif /* __x86_64__ */

PUBLIC_FUNCTION(x86_nopf_movb_al_Pcx)
	clc
	movb   %al, (%Pcx)
	ret
END(x86_nopf_movb_al_Pcx)

PUBLIC_FUNCTION(x86_nopf_movw_ax_Pcx)
	clc
	movw   %ax, (%Pcx)
	ret
END(x86_nopf_movw_ax_Pcx)

PUBLIC_FUNCTION(x86_nopf_movl_eax_Pcx)
	clc
	movl   %eax, (%Pcx)
	ret
END(x86_nopf_movl_eax_Pcx)

#ifdef __x86_64__
PUBLIC_FUNCTION(x86_nopf_movq_rax_Pcx)
	clc
	movq   %rax, (%Pcx)
	ret
END(x86_nopf_movq_rax_Pcx)
#endif /* __x86_64__ */

PUBLIC_LABEL(x86_nopf_end_clc):




PUBLIC_FUNCTION(x86_nopf_rep_insb)
	cld
	rep;   insb
	ret
END(x86_nopf_rep_insb)

PUBLIC_FUNCTION(x86_nopf_rep_insw)
	cld
	rep;   insw
	ret
END(x86_nopf_rep_insw)

PUBLIC_FUNCTION(x86_nopf_rep_insl)
	cld
	rep;   insl
	ret
END(x86_nopf_rep_insl)

PUBLIC_FUNCTION(x86_nopf_rep_outsb)
	cld
	rep;   outsb
	ret
END(x86_nopf_rep_outsb)

PUBLIC_FUNCTION(x86_nopf_rep_outsw)
	cld
	rep;   outsw
	ret
END(x86_nopf_rep_outsw)

PUBLIC_FUNCTION(x86_nopf_rep_outsl)
	cld
	rep;   outsl
	ret
END(x86_nopf_rep_outsl)


PUBLIC_FUNCTION(x86_nopf_repe_cmpsb)
	cld
	repe;  cmpsb
	ret
END(x86_nopf_repe_cmpsb)

PUBLIC_FUNCTION(x86_nopf_rep_stosb)
	cld
	rep;   stosb
	ret
END(x86_nopf_rep_stosb)

/* Assembly function:
 * >> PUBLIC_FUNCTION(x86_nopf_rep_movsb)
 * >>     cld
 * >>     rep;   movsb
 * >>     ret
 * >> END(x86_nopf_rep_movsb)
 * Yes. - That's literally the implementation,
 * however there is something very special about it:
 *  - Whenever a #PF happens, the kernel will see if it originated from
 *    that `rep movsb' instruction.
 *    If it did, then instead of actually handling the #PF, the kernel will
 *    instead advance the instruction pointer to the `ret' instruction,
 *    causing the `rep' to be aborted.
 * IN:
 *   - USER CHECKED void       *%edi:  Destination pointer
 *   - USER CHECKED void const *%esi:  Source pointer
 *   - size_t                   %ecx:  Copy size
 * OUT:
 *   - %edi:  == IN(%edi) + (IN(%ecx) - OUT(%ecx))
 *   - %esi:  == IN(%esi) + (IN(%ecx) - OUT(%ecx))
 *   - %ecx:  Number of bytes that were not copied.
 *   - %cr2:  if (OUT(%ecx) == 0)
 *                <UNCHANGED>
 *            else if (OUT(%cr2) == OUT(%edi))
 *                <#PF in `dst'>
 *            else if (OUT(%cr2) == OUT(%esi))
 *                <#PF in `src'>
 */
PUBLIC_FUNCTION(x86_nopf_rep_movsb)
	cld
	rep;   movsb
PUBLIC_LABEL(x86_nopf_end):
PUBLIC_FUNCTION(x86_nopf_ret)
	ret
END(x86_nopf_rep_movsb)
END(x86_nopf_ret)

PUBLIC_FUNCTION(x86_nopf_ret_stc)
	stc
	ret
END(x86_nopf_ret_stc)
.cfi_endproc

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MEMCPY_NOPF_S */
