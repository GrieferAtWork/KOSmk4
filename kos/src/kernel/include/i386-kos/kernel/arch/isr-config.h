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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_CONFIG_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_CONFIG_H 1

/* ISR pushes-error-code selector */
#define ISR_X86_CONFIG_PUSHESERRORS(vector_id)                   \
	((vector_id) == 0x08 /* #DF  Double Fault. */ ||             \
	 (vector_id) == 0x0a /* #TS  Invalid TSS. */ ||              \
	 (vector_id) == 0x0b /* #NP  Segment Not Present. */ ||      \
	 (vector_id) == 0x0c /* #SS  Stack-Segment Fault. */ ||      \
	 (vector_id) == 0x0d /* #GP  General Protection Fault. */ || \
	 (vector_id) == 0x0e /* #PF  Page Fault. */ ||               \
	 (vector_id) == 0x11 /* #AC  Alignment Check. */ ||          \
	 (vector_id) == 0x1e /* #SX  Security Exception. */)

/* ISR user-space access selector */
#define ISR_X86_CONFIG_ALLOWUSER(vector_id)                 \
	((vector_id) == 0x80 /* Syscall */ ||                   \
	 (vector_id) == 0x29 /* __fastfail() */ ||              \
	 (vector_id) == 0x05 /* #BR  Bound Range Exceeded */ || \
	 (vector_id) == 0x04 /* #OF  Overflow */ ||             \
	 (vector_id) == 0x03 /* #BP  Breakpoint */)

/* Return the DPL to-be configured for a given ISR vector. */
#define ISR_X86_CONFIG_GETDPL(vector_id) \
	(ISR_X86_CONFIG_ALLOWUSER(vector_id) ? 3 : 0)

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_ISR_CONFIG_H */
