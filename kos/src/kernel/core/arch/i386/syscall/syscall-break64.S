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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_BREAK64_S
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_BREAK64_S 1
#define __ASSEMBLER__ 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <cfi.h>
#include <kos/rpc.h>

#ifndef __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
/* #include <asm/syscalls64_d.h> */
#include "../../../../../../include/i386-kos/asm/syscalls64_d.h"
#endif /* !__NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT */

#ifndef __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1
/* #include <asm/syscalls32_d.h> */
#include "../../../../../../include/i386-kos/asm/syscalls32_d.h"
#endif /* !__NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT */





.section .text.cold
/* SyscallInvalidFlags(Count) */
#define SIF(c) \
	(RPC_SYSCALL_INFO_METHOD_OTHER_64 | RPC_SYSCALL_INFO_FEXCEPT | \
	 ((1 << (c)) - 1) << RPC_SYSCALL_INFO_FREGVALID_SHIFT)

/* Called when a system call is recognized, but hasn't been implemented yet */
.cfi_startproc
INTERN_FUNCTION(sys_break0)
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(0)), %rdx /* pointers[0] = flags */
	movq   $(2), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
END(sys_break0)

INTERN_FUNCTION(sys_break1)
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(1)), %rdx /* pointers[0] = flags */
	movq   $(3), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
END(sys_break1)

INTERN_FUNCTION(sys_break2)
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(2)), %rdx /* pointers[0] = flags */
	movq   $(4), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
END(sys_break2)

INTERN_FUNCTION(sys_break3)
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(3)), %rdx /* pointers[0] = flags */
	movq   $(5), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -8
END(sys_break3)

INTERN_FUNCTION(sys_break4)
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(4)), %rdx /* pointers[0] = flags */
	movq   $(6), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -16
END(sys_break4)

INTERN_FUNCTION(sys_break5)
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(5)), %rdx /* pointers[0] = flags */
	movq   $(7), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -24
END(sys_break5)

INTERN_FUNCTION(sys_break6)
	pushq_cfi %r9          /* pointers[7] = arg[5] */
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(6)), %rdx /* pointers[0] = flags */
	movq   $(8), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -32
END(sys_break6)

.cfi_endproc
#undef SIF

/* Force `sys_break' to use the max number of registers */
#undef __NR64RC_break
#define __NR64RC_break __NR64FEAT_SYSCALL_REGISTER_MAX_COUNT

/* Define all unimplemented system calls as weak aliases
 * of  `sys_breakN',  where  N  is  the  register  count */
#define __SYSINVALID_OF2(register_count) sys_break##register_count
#define __SYSINVALID_OF(register_count) __SYSINVALID_OF2(register_count)
#define __SYSCALL(name) \
	DEFINE_PUBLIC_WEAK_ALIAS(sys_##name, __SYSINVALID_OF(__NR64RC_##name))
/* #include <asm/ls-syscalls64.h> */
#include "../../../../../../include/i386-kos/asm/ls-syscalls64.h"

/* Define the 64-bit break system call (if it wasn't already defined by <i386-kos/asm/syscalls64.def>) */
.ifndef sys_break
DEFINE_PUBLIC_ALIAS(sys_break, sys_break6)
.endif /* !sys_break */




.section .text.cold
/* SyscallInvalidFlags(Count) */
#define SIF(c) \
	(RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT | \
	 ((1 << (c)) - 1) << RPC_SYSCALL_INFO_FREGVALID_SHIFT)

/* Called when a system call is recognized, but hasn't been implemented yet */
.cfi_startproc
INTERN_FUNCTION(sys32_break0)
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(0)), %rdx /* pointers[0] = flags */
	movq   $(2), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
END(sys32_break0)

INTERN_FUNCTION(sys32_break1)
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(1)), %rdx /* pointers[0] = flags */
	movq   $(3), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
END(sys32_break1)

INTERN_FUNCTION(sys32_break2)
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(2)), %rdx /* pointers[0] = flags */
	movq   $(4), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
END(sys32_break2)

INTERN_FUNCTION(sys32_break3)
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(3)), %rdx /* pointers[0] = flags */
	movq   $(5), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -8
END(sys32_break3)

INTERN_FUNCTION(sys32_break4)
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(4)), %rdx /* pointers[0] = flags */
	movq   $(6), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -16
END(sys32_break4)

INTERN_FUNCTION(sys32_break5)
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(5)), %rdx /* pointers[0] = flags */
	movq   $(7), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -24
END(sys32_break5)

INTERN_FUNCTION(sys32_break6)
	pushq_cfi %r9          /* pointers[7] = arg[5] */
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(6)), %rdx /* pointers[0] = flags */
	movq   $(8), %rsi                                  /* argc */
	movq   $(EXCEPT_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   except_thrown
	.cfi_adjust_cfa_offset -32
END(sys32_break6)

.cfi_endproc
#undef SIF

/* Force `sys32_break' to use the max number of registers */
#undef __NR32RC_break
#define __NR32RC_break __NR32FEAT_SYSCALL_REGISTER_MAX_COUNT

#define __SYSINVALID32_OF2(register_count) sys32_break##register_count
#define __SYSINVALID32_OF(register_count) __SYSINVALID32_OF2(register_count)
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_0(name) DEFINE_INTERN_WEAK_ALIAS(__x86_asm32_sysrun32_##name, sys32_break0)
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_1(name) /* nothing */
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_2(name) /* nothing */
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_3(name) /* nothing */
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_4(name) /* nothing */
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_5(name) /* nothing */
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_6(name) /* nothing */
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS2(name, register_count) \
	__DEFINE_SYSRUN32_ALIAS_IF_NOREGS2_##register_count(name)
#define __DEFINE_SYSRUN32_ALIAS_IF_NOREGS(name, register_count) \
	__DEFINE_SYSRUN32_ALIAS_IF_NOREGS2(name, register_count)
#define __SYSCALL(name)                                                        \
	DEFINE_PUBLIC_WEAK_ALIAS(sys32_##name, __SYSINVALID32_OF(__NR32RC_##name)) \
	__DEFINE_SYSRUN32_ALIAS_IF_NOREGS(name, __NR32RC_##name)

/* #include <asm/ls-syscalls32.h> */
#include "../../../../../../include/i386-kos/asm/ls-syscalls32.h"

/* Define the 32-bit break system call (if it wasn't already defined by <i386-kos/asm/syscalls32.def>) */
.ifndef sys32_break
DEFINE_PUBLIC_ALIAS(sys32_break, sys32_break6)
.endif /* !sys32_break */



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_BREAK64_S */
