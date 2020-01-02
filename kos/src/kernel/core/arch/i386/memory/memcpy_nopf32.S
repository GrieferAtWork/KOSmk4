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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MEMCPY_NOPF32_S
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MEMCPY_NOPF32_S 1

#include <kernel/compiler.h>

#include <asm/cfi.h>


/* Assembly function:
 * >> PUBLIC_FUNCTION(x86_memcpy_nopf)
 * >>     cld
 * >>     rep;   movsb
 * >>     ret
 * >> END(x86_memcpy_nopf)
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
.section .text
PUBLIC_FUNCTION(x86_memcpy_nopf)
	.cfi_startproc
	cld
PUBLIC_FUNCTION(x86_memcpy_nopf_rep_pointer)
	rep;   movsb
END(x86_memcpy_nopf_rep_pointer)
PUBLIC_FUNCTION(x86_memcpy_nopf_ret_pointer)
	ret
END(x86_memcpy_nopf_ret_pointer)
	.cfi_endproc
END(x86_memcpy_nopf)


#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_MEMCPY_NOPF32_S */
