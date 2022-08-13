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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_BREAK32_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_BREAK32_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <cfi.h>
#include <kos/rpc.h>

#ifndef __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
#include "../../../../../../include/i386-kos/asm/syscalls32_d.h"
#endif /* !__NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT */






.section .text.cold
#define SYS_INVALID_ENCODE_COUNT(count) (count+2)

/* Called when a system call is recognized, but hasn't been implemented yet */
INTERN_FUNCTION(sys_break0)
	.cfi_startproc
	movl   $(SYS_INVALID_ENCODE_COUNT(0)), %ecx
.Lsys_break_common:
	xchgl  0(%esp), %eax
	.cfi_register %eip, %eax
	pushl_cfi $(0) /* flags (filled in later) */
	pushl_cfi %ecx /* argc */
	/* *(u32 *)(ESP + 4) = (RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT |
	 *                      ((1 << (%ecx - 2)) - 1) << RPC_SYSCALL_INFO_FREGVALID_SHIFT); */
	subl   $(2), %ecx
	movl   $(1), %edx
	shll   %cl, %edx
	decl   %edx
	shll   $(RPC_SYSCALL_INFO_FREGVALID_SHIFT), %edx
	orl    $(RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT), %edx
	movl   %edx, 4(%esp) /* flags */
	pushl_cfi $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL))
	call   except_thrown
	.cfi_endproc
END(sys_break0)
.cfi_startproc
INTERN_FUNCTION(sys_break1)
	movl   $(SYS_INVALID_ENCODE_COUNT(1)), %ecx
	jmp    .Lsys_break_common
END(sys_break1)
INTERN_FUNCTION(sys_break2)
	movl   $(SYS_INVALID_ENCODE_COUNT(2)), %ecx
	jmp    .Lsys_break_common
END(sys_break2)
INTERN_FUNCTION(sys_break3)
	movl   $(SYS_INVALID_ENCODE_COUNT(3)), %ecx
	jmp    .Lsys_break_common
END(sys_break3)
INTERN_FUNCTION(sys_break4)
	movl   $(SYS_INVALID_ENCODE_COUNT(4)), %ecx
	jmp    .Lsys_break_common
END(sys_break4)
INTERN_FUNCTION(sys_break5)
	movl   $(SYS_INVALID_ENCODE_COUNT(5)), %ecx
	jmp    .Lsys_break_common
END(sys_break5)
INTERN_FUNCTION(sys_break6)
	movl   $(SYS_INVALID_ENCODE_COUNT(6)), %ecx
	jmp    .Lsys_break_common
END(sys_break6)
.cfi_endproc

/* Force `sys_break' to use the max number of registers */
#undef __NR32RC_break
#define __NR32RC_break __NR32FEAT_SYSCALL_REGISTER_MAX_COUNT

/* Define all unimplemented system calls as weak aliases
 * of  `sys_breakN',  where  N  is  the  register  count */
#define __SYSINVALID_OF2(register_count) sys_break##register_count
#define __SYSINVALID_OF(register_count) __SYSINVALID_OF2(register_count)
#define __SYSCALL(name) \
	DEFINE_PUBLIC_WEAK_ALIAS(sys_##name, __SYSINVALID_OF(__NR32RC_##name))
#include "../../../../../../include/i386-kos/asm/ls-syscalls32.h"

/* Define the 32-bit break system call (if it wasn't already defined by <i386-kos/asm/syscalls32.def>) */
.ifndef sys_break
DEFINE_PUBLIC_ALIAS(sys_break, sys_break6)
.endif /* !sys_break */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_BREAK32_S */
