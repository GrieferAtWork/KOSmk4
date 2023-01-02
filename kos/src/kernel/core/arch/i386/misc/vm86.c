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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_VM86_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_VM86_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/types.h>
#include <kernel/x86/vm86.h>

#include <hybrid/host.h>

DECL_BEGIN

#if !defined(__x86_64__) && !defined(__I386_NO_VM86)
PUBLIC u8 KCALL
x86_vm86_inb(struct icpustate *__restrict state, u16 port) {
	(void)state;
	(void)port;
	COMPILER_IMPURE();
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
}

PUBLIC u16 KCALL
x86_vm86_inw(struct icpustate *__restrict state, u16 port) {
	(void)state;
	(void)port;
	COMPILER_IMPURE();
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
}

PUBLIC u32 KCALL
x86_vm86_inl(struct icpustate *__restrict state, u16 port) {
	(void)state;
	(void)port;
	COMPILER_IMPURE();
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
}

PUBLIC void KCALL
x86_vm86_outb(struct icpustate *__restrict state, u16 port, u8 value) {
	(void)state;
	(void)port;
	(void)value;
	COMPILER_IMPURE();
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
}

PUBLIC void KCALL
x86_vm86_outw(struct icpustate *__restrict state, u16 port, u16 value) {
	(void)state;
	(void)port;
	(void)value;
	COMPILER_IMPURE();
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
}

PUBLIC void KCALL
x86_vm86_outl(struct icpustate *__restrict state, u16 port, u32 value) {
	(void)state;
	(void)port;
	(void)value;
	COMPILER_IMPURE();
	THROW(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE);
}

#endif /* !__x86_64__ && !__I386_NO_VM86 */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_VM86_C */
