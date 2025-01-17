/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_VM86_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_VM86_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <hybrid/host.h>

DECL_BEGIN

#ifdef __CC__
#if !defined(__I386_NO_VM86) && !defined(__x86_64__)
FUNDEF u8 KCALL x86_vm86_inb(struct icpustate *__restrict state, u16 port) THROWS(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
FUNDEF u16 KCALL x86_vm86_inw(struct icpustate *__restrict state, u16 port) THROWS(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
FUNDEF u32 KCALL x86_vm86_inl(struct icpustate *__restrict state, u16 port) THROWS(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
FUNDEF void KCALL x86_vm86_outb(struct icpustate *__restrict state, u16 port, u8 value) THROWS(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
FUNDEF void KCALL x86_vm86_outw(struct icpustate *__restrict state, u16 port, u16 value) THROWS(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
FUNDEF void KCALL x86_vm86_outl(struct icpustate *__restrict state, u16 port, u32 value) THROWS(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
/* TODO: int */
/* TODO: cli */
/* TODO: sti */
/* TODO: pushf */
/* TODO: popf */
/* TODO: iret */
#endif /* !__I386_NO_VM86 && !__x86_64__ */
#endif


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_VM86_H */
