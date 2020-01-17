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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_VM_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_VM_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <hybrid/host.h>

#undef CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF
#define CONFIG_VM_ARCH_DEFINES_MEMCPY_NOPF 1

DECL_BEGIN

#ifdef __CC__

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
 *    advance the instruction pointer to the `ret' instruction, causing
 *    the `rep' to be aborted.
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
FUNDEF NOBLOCK void NOTHROW(KCALL x86_memcpy_nopf)();

/* Copy memory from `src' to `dst', but stop if any sort of #PF happens,
 * regardless of that #PF being handable or not (aka: load-on-access, or
 * copy-on-write will never be triggered by this function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
FORCELOCAL NOBLOCK WUNUSED size_t
NOTHROW(KCALL memcpy_nopf)(USER CHECKED void *dst,
                           USER CHECKED void const *src,
                           size_t num_bytes) {
	__register size_t result;
	__asm__ __volatile__("call x86_memcpy_nopf"
	                     : "=m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, dst))
	                     , "=c" (result)
	                     : "m" (__COMPILER_ASM_BUFFER(__UINT8_TYPE__, num_bytes, src))
	                     , "D" (dst)
	                     , "S" (src)
	                     , "1" (num_bytes));
	return result;
}

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_VM_H */
