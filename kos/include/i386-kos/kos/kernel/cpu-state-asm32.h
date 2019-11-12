/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_ASM32_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_ASM32_H 1

#include <hybrid/host.h>

#include "cpu-state32.h"

#if defined(__i386__) && !defined(__x86_64__)
#include <hybrid/__asm.h>

#define ASM_CFI_REL_OFFSET_RESTORE_GPREGSNSP(offset)              \
	__ASM_L(.cfi_rel_offset %edi, ((offset) + OFFSET_GPREGS_EDI)) \
	__ASM_L(.cfi_rel_offset %esi, ((offset) + OFFSET_GPREGS_ESI)) \
	__ASM_L(.cfi_rel_offset %ebp, ((offset) + OFFSET_GPREGS_EBP)) \
	__ASM_L(.cfi_rel_offset %ebx, ((offset) + OFFSET_GPREGS_EBX)) \
	__ASM_L(.cfi_rel_offset %edx, ((offset) + OFFSET_GPREGS_EDX)) \
	__ASM_L(.cfi_rel_offset %ecx, ((offset) + OFFSET_GPREGS_ECX)) \
	__ASM_L(.cfi_rel_offset %eax, ((offset) + OFFSET_GPREGS_EAX))


#endif /* __i386__ && !__x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_ASM32_H */
