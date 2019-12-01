/* HASH 0x8cf0debf */
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
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_COUNT_386 1

#include <hybrid/compiler.h>

#include <kernel/except.h>

#include <asm/cfi.h>
#include <asm/instr/interrupt.h>
#include <asm/instr/movzxq.h>
#include <asm/syscalls32_d.h>
#include <asm/syscalls64_d.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

#include <librpc/rpc.h>

.section .text.hot
INTERN_CONST(__x86_idtdpl_syscall, 3)
INTERN_FUNCTION(x86_idt_syscall)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Only get here from user-space, so we can do an unconditional swapgs on entry! */
	swapgs
	/* Check if we got here from compatibility mode.
	 * Note that this check must be done before re-enabling interrupts, since
	 * once that is done, our iret tail may have already been redirected! */
	cmpq   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS64_CS(%rsp)
	/* Unconditionally re-enable interrupts (only get here from user-space) */
	sti
	je     .Ldo_asm32_syscall_int80 /* Compatibility mode! */
.Ldo_asm64_syscall_int80:
	/* Route a 64-bit system call. */
	EXTERN(__x86_asm64_syscall_break)
#if __NR64_syscall0_min != 0
	cmpq   $(__NR64_syscall0_min), %rax
	jb     __x86_asm64_syscall_break
#endif /* __NR64_syscall0_min != 0 */
	cmpq   $(__NR64_syscall0_max), %rax
	ja     1f
	EXTERN(x86_sysroute0_asm64_syscall)
	jmpq   *(x86_sysroute0_asm64_syscall - ((__NR64_syscall0_min * 8) & 0xffffffffffffffff))(,%rax,8)
1:	cmpq   $(__NR64_syscall1_min), %rax
	jb     __x86_asm64_syscall_break
	cmpq   $(__NR64_syscall1_max), %rax
	ja     __x86_asm64_syscall_break
	EXTERN(x86_sysroute1_asm64_syscall)
	jmpq   *(x86_sysroute1_asm64_syscall - ((__NR64_syscall1_min * 8) & 0xffffffffffffffff))(,%rax,8)

.Ldo_asm32_syscall_int80:
	movzlq %eax, %rax
.Ldo_asm32_syscall_int80_rax:
	EXTERN(__x86_asm32_int80_break)
#if __NR32_syscall0_min != 0
	cmpq   $(__NR32_syscall0_min), %rax
	jb     __x86_asm32_int80_break
#endif /* __NR32_syscall0_min != 0 */
	cmpq   $(__NR32_syscall0_max), %rax
	ja     1f
	EXTERN(x86_sysroute0_asm32_int80)
	jmpq   *x86_sysroute0_asm32_int80(,%rax,8)
1:	movabs $(__NR32_syscall1_min), %r8
	cmpq   %r8, %rax
	jb     __x86_asm32_int80_break
	movabs $(__NR32_syscall1_max), %r8
	cmpq   %r8, %rax
	ja     __x86_asm32_int80_break
	EXTERN(x86_sysroute1_asm32_int80)
	jmpq   *(x86_sysroute1_asm32_int80 - ((__NR32_syscall1_min * 8) & 0xffffffffffffffff))(,%rax,8)
	.cfi_endproc
END(x86_idt_syscall)


#ifndef CONFIG_NO_SYSCALL_TRACING
.section .text.hot
INTERN_FUNCTION(x86_idt_syscall_traced)
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %rsp, 0
	/* Only get here from user-space, so we can do an unconditional swapgs on entry! */
	swapgs
	/* Check if we got here from compatibility mode.
	 * Note that this check must be done before re-enabling interrupts, since
	 * once that is done, our iret tail may have already been redirected! */
	cmpq   $(SEGMENT_USER_CODE32_RPL), OFFSET_IRREGS64_CS(%rsp)
	/* Unconditionally re-enable interrupts (only get here from user-space) */
	sti
	je     1f /* Compatibility mode */

	pushq_cfi_r %rcx
	pushq_cfi_r %r11
	pushq_cfi_r %r9  /* ARG[5] */
	pushq_cfi_r %r8  /* ARG[4] */
	pushq_cfi_r %r10 /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rsi /* ARG[1] */
	pushq_cfi_r %rdi /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	movq   %rsp, %rdi
	EXTERN(syscall_trace)
	call   syscall_trace

	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rdi /* ARG[0] */
	popq_cfi_r %rsi /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %r10 /* ARG[3] */
	popq_cfi_r %r8  /* ARG[4] */
	popq_cfi_r %r9  /* ARG[5] */
	popq_cfi_r %r11
	popq_cfi_r %rcx
	jmp    .Ldo_asm64_syscall_int80

1:	movzlq %eax, %rax
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	pushq_cfi_r %rbp /* ARG[5] */
	pushq_cfi_r %rdi /* ARG[4] */
	pushq_cfi_r %rsi /* ARG[3] */
	pushq_cfi_r %rdx /* ARG[2] */
	pushq_cfi_r %rcx /* ARG[1] */
	pushq_cfi_r %rbx /* ARG[0] */
	pushq_cfi_r %rax /* SYSNO */

	movq   %rsp, %rdi
	EXTERN(syscall_trace_compat)
	call   syscall_trace_compat

	popq_cfi_r %rax /* SYSNO */
	popq_cfi_r %rbx /* ARG[0] */
	popq_cfi_r %rcx /* ARG[1] */
	popq_cfi_r %rdx /* ARG[2] */
	popq_cfi_r %rsi /* ARG[3] */
	popq_cfi_r %rdi /* ARG[4] */
	popq_cfi_r %rbp /* ARG[5] */
	popq_cfi_r %r11
	popq_cfi_r %r10
	popq_cfi_r %r9
	popq_cfi_r %r8
	jmp    .Ldo_asm32_syscall_int80_rax
	.cfi_endproc
END(x86_idt_syscall_traced)
#endif /* !CONFIG_NO_SYSCALL_TRACING */






.section .text.cold
/* SyscallInvalidFlags(Count) */
#define SIF(c) \
	(RPC_SYSCALL_INFO_METHOD_OTHER_64 | RPC_SYSCALL_INFO_FEXCEPT | \
	 ((1 << (c)) - 1) << RPC_SYSCALL_INFO_FARGVALID_SHIFT)

/* Called when a system call is recognized, but hasn't been implemented yet */
.cfi_startproc
INTERN_FUNCTION(sys_invalid0)
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(0)), %rdx /* pointers[0] = flags */
	movq   $(2), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
END(sys_invalid0)

INTERN_FUNCTION(sys_invalid1)
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(1)), %rdx /* pointers[0] = flags */
	movq   $(3), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
END(sys_invalid1)

INTERN_FUNCTION(sys_invalid2)
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(2)), %rdx /* pointers[0] = flags */
	movq   $(4), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
END(sys_invalid2)

INTERN_FUNCTION(sys_invalid3)
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(3)), %rdx /* pointers[0] = flags */
	movq   $(5), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -8
END(sys_invalid3)

INTERN_FUNCTION(sys_invalid4)
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(4)), %rdx /* pointers[0] = flags */
	movq   $(6), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -16
END(sys_invalid4)

INTERN_FUNCTION(sys_invalid5)
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(5)), %rdx /* pointers[0] = flags */
	movq   $(7), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -24
END(sys_invalid5)

INTERN_FUNCTION(sys_invalid6)
	pushq_cfi %r9          /* pointers[7] = arg[5] */
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(6)), %rdx /* pointers[0] = flags */
	movq   $(8), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -32
END(sys_invalid6)

.cfi_endproc
#undef SIF

#define __SYSCALL(name) \
	DEFINE_PUBLIC_WEAK_ALIAS(sys_##name, PP_CAT2(sys_invalid, __NR64AC_##name));
#include <asm/ls-syscalls64.h>
#undef __SYSCALL



.section .text.cold
/* SyscallInvalidFlags(Count) */
#define SIF(c) \
	(RPC_SYSCALL_INFO_METHOD_OTHER_32 | RPC_SYSCALL_INFO_FEXCEPT | \
	 ((1 << (c)) - 1) << RPC_SYSCALL_INFO_FARGVALID_SHIFT)

/* Called when a system call is recognized, but hasn't been implemented yet */
.cfi_startproc
INTERN_FUNCTION(sys32_invalid0)
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(0)), %rdx /* pointers[0] = flags */
	movq   $(2), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
END(sys32_invalid0)

INTERN_FUNCTION(sys32_invalid1)
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(1)), %rdx /* pointers[0] = flags */
	movq   $(3), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
END(sys32_invalid1)

INTERN_FUNCTION(sys32_invalid2)
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(2)), %rdx /* pointers[0] = flags */
	movq   $(4), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
END(sys32_invalid2)

INTERN_FUNCTION(sys32_invalid3)
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(3)), %rdx /* pointers[0] = flags */
	movq   $(5), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -8
END(sys32_invalid3)

INTERN_FUNCTION(sys32_invalid4)
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(4)), %rdx /* pointers[0] = flags */
	movq   $(6), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -16
END(sys32_invalid4)

INTERN_FUNCTION(sys32_invalid5)
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(5)), %rdx /* pointers[0] = flags */
	movq   $(7), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -24
END(sys32_invalid5)

INTERN_FUNCTION(sys32_invalid6)
	pushq_cfi %r9          /* pointers[7] = arg[5] */
	pushq_cfi %r8          /* pointers[6] = arg[4] */
	pushq_cfi %rcx         /* pointers[5] = arg[3] */
	pushq_cfi %rdx         /* pointers[4] = arg[2] */
	movq   %rsi, %r9       /* pointers[3] = arg[1] */
	movq   %rdi, %r8       /* pointers[2] = arg[0] */
	movq   %rax, %rcx      /* pointers[1] = sysno */
	movq   $(SIF(6)), %rdx /* pointers[0] = flags */
	movq   $(8), %rsi                                  /* argc */
	movq   $(ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL)), %rdi /* code */
	call   error_thrown
	.cfi_adjust_cfa_offset -32
END(sys32_invalid6)

.cfi_endproc
#undef SIF

#define __SYSCALL(name) \
	DEFINE_PUBLIC_WEAK_ALIAS(sys32_##name, PP_CAT2(sys32_invalid, __NR32AC_##name));
#include <asm/ls-syscalls64.h>
#undef __SYSCALL


/* TODO:
 * .weak sys32_foo
 * .global sys32_foo
 * .if defined(sys_foo) && __NR64AC_foo == __NR32AC_foo
 * sys32_foo = sys_foo
 * .elif !HAS_DOUBLE_WIDE_REGISTERS_foo
 * sys32_foo = sys32_invalid##__NR64AC_foo
 * .else
 * sys32_foo:
 *     <EXPAND_DOUBLE_WIDE_REGISTER_ARGUMENTS>
 *     jmp sys32_invalid##__NR386AC_foo
 * .endif
 */
