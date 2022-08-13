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
#ifdef __INTELLISENSE__
#define __ASSEMBLER__ 1
//#define SYSCALL_FASTPASS_KIND_SYS32_SYSENTER 1
#define SYSCALL_FASTPASS_KIND_SYS32_INT80 1
//#define    SYSCALL_FASTPASS_KIND_SYS64    1
#endif /* __INTELLISENSE__ */


/* NOTE:
 *  SYSCALL_FASTPASS_KIND_SYS32_SYSENTER -- x86_syscall32_sysenter[_traced]
 *  SYSCALL_FASTPASS_KIND_SYS32_INT80    -- x86_syscall32_int80[_traced]
 *  SYSCALL_FASTPASS_KIND_SYS64          -- x86_syscall64_int80[_traced]
 */
#if (defined(SYSCALL_FASTPASS_KIND_SYS32_SYSENTER) + \
     defined(SYSCALL_FASTPASS_KIND_SYS32_INT80) +  \
     defined(SYSCALL_FASTPASS_KIND_SYS64)) != 1
#error "Must #define exactly one of the above macros!"
#endif /* ... */

#undef __WANT_SYSCALL_REGISTER_COUNT
#define __WANT_SYSCALL_REGISTER_COUNT 1

#include <hybrid/compiler.h>

#include <kernel/arch/syscall.h>
#include <kernel/syscall.h>
#include <kernel/x86/syscall-tables.h>

#include <hybrid/typecore.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/movzxq.h>
#include <kos/asm/rpc-method.h>
#include <kos/asm/rpc.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>
#include <kos/kernel/syscalls.h>

#ifdef __x86_64__
#include <asm/instr/interrupt.h>
#endif /* __x86_64__ */

/* System call numbers */
#ifndef __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#ifdef __x86_64__
#ifndef __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT
#define __NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT 1
#include <asm/syscalls64_d.h>
#endif /* !__NR64FEAT_DEFINED_SYSCALL_REGISTER_COUNT */
#endif /* __x86_64__ */

/* Headers needed by the actual fastpass implementations. */
#include <fcntl.h> /* AT_FDCWD */

#ifndef Pn
#define Pn(x) ((x)*__SIZEOF_POINTER__)
#endif /* !Pn */


#ifndef IS_DEFINED
#define ARG_PLACEHOLDER_ ,
#define TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define TAKE_SECOND_ARG(x) TAKE_SECOND_ARG_IMPL x
#define IS_DEFINED3(...) TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define IS_DEFINED2(x) IS_DEFINED3(ARG_PLACEHOLDER_##x)
#define IS_DEFINED(x) IS_DEFINED2(x)
#endif /* !IS_DEFINED */


/* Define some kind-specific macros:
 *   - _SYSFAST_WANT(NAME, name): Expands to non-zero if `NAME' should be defined as a system call.
 *                                Note that `NAME' must be written in upper-case!
 *   - _SYSFAST_SECTNAME(name):   System call definition section names.
 *                                Note that we use a unique section name for  fastpass
 *                                system calls, so-as to allow --gc-sections to delete
 *                                the unused auto-generated system call wrappers.
 *   - _SYSFAST_FUNCNAME(name):   Symbol name generator for the low-level system call
 *                                entry points. - All of these are already defined as
 *                                ATTR_WEAK, auto-generated functions.
 *   - _SYSFAST_SYSNO(name):      The actual system call number of the system call that
 *                                is being invoked.
 *   - _SYSFAST_PERSO:            The CFI personality function that must be used to
 *                                properly handle exception unwinding.
 *   - _SYSFAST_SETALIAS(name):   Define possibly aliasing symbols for `_SYSFAST_SECTNAME(name)'
 */
#ifdef SYSCALL_FASTPASS_KIND_SYS32_SYSENTER
#define _SYSFAST_RPCMETHOD      RPC_SYSCALL_INFO_METHOD_SYSENTER_32
#define _SYSFAST_SECTNAME(name) .text.x86.asm32_syscall_sysenter.fastpass_##name
#define _SYSFAST_FUNCNAME       X86_ASMSYSCALL32_SYSENTER
#define _SYSFAST_SYSNO(name)    __NR32_##name
#define _SYSFAST_PERSO          x86_syscall_personality_asm32_sysenter
#elif defined(SYSCALL_FASTPASS_KIND_SYS32_INT80)
#define _SYSFAST_RPCMETHOD      RPC_SYSCALL_INFO_METHOD_INT80H_32
#define _SYSFAST_SECTNAME(name) .text.x86.asm32_syscall_int80.fastpass_##name
#define _SYSFAST_FUNCNAME       X86_ASMSYSCALL32_INT80
#define _SYSFAST_SYSNO(name)    __NR32_##name
#define _SYSFAST_PERSO          x86_syscall_personality_asm32_int80
#elif defined(SYSCALL_FASTPASS_KIND_SYS64)
#define _SYSFAST_RPCMETHOD      RPC_SYSCALL_INFO_METHOD_INT80H_64
#define _SYSFAST_SECTNAME(name) .text.x86.asm64_syscall.fastpass_##name
#define _SYSFAST_FUNCNAME       X86_ASMSYSCALL64
#define _SYSFAST_SYSNO(name)    __NR64_##name
#define _SYSFAST_PERSO          x86_syscall_personality_asm64_syscall
#endif /* SYSCALL_FASTPASS_KIND_... */


/* System call argument registers. */
#ifdef SYSCALL_FASTPASS_KIND_SYS64
#define _SYSFAST_R_arg1 %rdi
#define _SYSFAST_R_arg2 %rsi
#define _SYSFAST_R_arg3 %rdx
#define _SYSFAST_R_arg4 %r10
#define _SYSFAST_R_arg5 %r8
#define _SYSFAST_R_arg6 %r9
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
#define _SYSFAST_R_arg1 %ebx
#define _SYSFAST_R_arg2 %ecx
#define _SYSFAST_R_arg3 %edx
#define _SYSFAST_R_arg4 %esi
#ifdef SYSCALL_FASTPASS_KIND_SYS32_SYSENTER
#define _SYSFAST_R_arg5 0(%ebp)
#define _SYSFAST_R_arg6 4(%ebp)
#else /* SYSCALL_FASTPASS_KIND_SYS32_SYSENTER */
#define _SYSFAST_R_arg5 %edi
#define _SYSFAST_R_arg6 %ebp
#endif /* !SYSCALL_FASTPASS_KIND_SYS32_SYSENTER */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */


/* _SYSFAST_WANT(NAME, name) =
 * - SYSCALL_FASTPASS_KIND_SYS64:
 *   >>   defined(__ARCH_WANT_SYSCALL_##NAME)
 * - SYSCALL_FASTPASS_KIND_SYS32_INT80:
 *   >>   defined(__ARCH_WANT_SYSCALL_##NAME) || (defined(__x86_64__) && defined(__ARCH_WANT_COMPAT_SYSCALL_##NAME))
 * - SYSCALL_FASTPASS_KIND_SYS32_SYSENTER:
 *   >>   (defined(__ARCH_WANT_SYSCALL_##NAME) || (defined(__x86_64__) && defined(__ARCH_WANT_COMPAT_SYSCALL_##NAME))) &&
 *   >>   (__NR32RC_##name >= 5) // NOTE: Variants with register-count 0..4 are binary-compatible with int80!
 */
#ifdef SYSCALL_FASTPASS_KIND_SYS64
#define _SYSFAST_WANT(NAME, name) IS_DEFINED(__ARCH_WANT_SYSCALL_##NAME)
#define _SYSFAST_SETALIAS(name)   /* nothing */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
#ifndef __SYSFAST_ARCH_WANT
#ifdef __x86_64__
#define __SYSFAST_ARCH_WANT_00     0
#define __SYSFAST_ARCH_WANT_01     1
#define __SYSFAST_ARCH_WANT_10     1
#define __SYSFAST_ARCH_WANT_11     1
#define __SYSFAST_ARCH_WANT3(a, b) __SYSFAST_ARCH_WANT_##a##b
#define __SYSFAST_ARCH_WANT2(a, b) __SYSFAST_ARCH_WANT3(a, b)
#define __SYSFAST_ARCH_WANT(NAME)                                \
	__SYSFAST_ARCH_WANT2(IS_DEFINED(__ARCH_WANT_SYSCALL_##NAME), \
	                     IS_DEFINED(__ARCH_WANT_COMPAT_SYSCALL_##NAME))
#else /* __x86_64__ */
#define __SYSFAST_ARCH_WANT(NAME) IS_DEFINED(__ARCH_WANT_SYSCALL_##NAME)
#endif /* !__x86_64__ */
/* Expand to 1 if `__NR32RC_##name in [5,6]' */
#define __PRIVATE_SYSFAST_ARCH_ISREG_0   0
#define __PRIVATE_SYSFAST_ARCH_ISREG_1   0
#define __PRIVATE_SYSFAST_ARCH_ISREG_2   0
#define __PRIVATE_SYSFAST_ARCH_ISREG_3   0
#define __PRIVATE_SYSFAST_ARCH_ISREG_4   0
#define __PRIVATE_SYSFAST_ARCH_ISREG_5   1
#define __PRIVATE_SYSFAST_ARCH_ISREG_6   1
#define __PRIVATE_SYSFAST_ARCH_ISREG2(n) __PRIVATE_SYSFAST_ARCH_ISREG_##n
#define __PRIVATE_SYSFAST_ARCH_ISREG(n) __PRIVATE_SYSFAST_ARCH_ISREG2(n)
#define __SYSFAST_ARCH_ISREG_56(name) __PRIVATE_SYSFAST_ARCH_ISREG(__NR32RC_##name)

/* if (!c) { DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(name), X86_ASMSYSCALL32_INT80(name)); } */
#define __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT_0(name) DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_SYSENTER(name), X86_ASMSYSCALL32_INT80(name))
#define __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT_1(name) /* nothing */
#define __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT2(c, name) __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT_##c(name)
#define __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT(c, name) __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT2(c, name)
#endif /* !__SYSFAST_ARCH_WANT */

#ifdef SYSCALL_FASTPASS_KIND_SYS32_SYSENTER
#define _SYSFAST_WANT(NAME, name) (__SYSFAST_ARCH_WANT(NAME) && __NR32RC_##name >= 5)
#define _SYSFAST_SETALIAS(name)   /* nothing */
#else /* SYSCALL_FASTPASS_KIND_SYS32_SYSENTER */
#define _SYSFAST_WANT(NAME, name) __SYSFAST_ARCH_WANT(NAME)
#define _SYSFAST_SETALIAS(name)   __SYSFAST_SETALIAS_INT80_SYSENTER_IF_NOT(__SYSFAST_ARCH_ISREG_56(name), name)
#endif /* !SYSCALL_FASTPASS_KIND_SYS32_SYSENTER */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */


#undef SC_IRET
#undef SC_IRET_NOCLOBBER
#ifdef __x86_64__
#ifdef SYSCALL_FASTPASS_KIND_SYS32_SYSENTER
/* We can just use `sysret' as a drop-in replacement for `sysexit', since
 * `sysret' doesn't clobber any  32-bit registers that `sysexit'  doesn't
 * also clobber! */
#define SC_IRET X86_IRET_BUT_PREFER_SYSRET32
#elif defined(SYSCALL_FASTPASS_KIND_SYS32_INT80)
/* Mustn't clobber %ecx, so always use `iret' in this case! */
#define SC_IRET intr_exit
#elif defined(SYSCALL_FASTPASS_KIND_SYS64)
/* NOTE: On x86_64, 64-bit system calls can be invoked in 1 of 2 ways:
 *       - int 80h
 *       - syscall
 * Documentation throughout the kernel states that both of these methods
 * yield identical results, though one  minor detail that is  documented
 * nowhere else is left to use to decide upon:
 *       `int 80h' on x86_64 is allowed to clobber %rcx and %r11
 * By allowing for  this, we  can use identical  return-paths for  both
 * invocation methods, by trying to make use of `sysret' in both cases. */
#define SC_IRET X86_IRET_BUT_PREFER_SYSRET64
#endif /* ... */
#define SC_IRET_NOCLOBBER intr_exit
#elif defined(SYSCALL_FASTPASS_KIND_SYS32_SYSENTER)
#define SC_IRET           X86_IRET_BUT_PREFER_SYSEXIT
#define SC_IRET_NOCLOBBER iret
#else /* ... */
#define SC_IRET           iret
#define SC_IRET_NOCLOBBER iret
#endif /* !... */

/* Prefix for accessing linear memory without loading segment registers */
#undef CSMEM
#ifdef __x86_64__
#define CSMEM /* nothing */
#else /* __x86_64__ */
#define CSMEM %cs:
#endif /* !__x86_64__ */



/* Define _all_ low-level system call variants of a  system
 * call that is  entirely unable to  throw any  exceptions.
 * Such a system call can be defined a bit simpler, however
 * if the implementation  somehow does manage  to throw  an
 * exception, then the behavior is undefined.
 * Essentially, only stub/no-op system calls (such as `rtm_test()')
 * fall under this category. */
#ifndef SC_BEGIN_ALL_NOTHROW
#ifdef __x86_64__
#define SC_BEGIN_ALL_NOTHROW(name)                                                          \
	.section _SYSFAST_SECTNAME(name);                                                       \
	INTERN_FUNCTION(X86_ASMSYSCALL32_SYSENTER(name));                                       \
		DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_INT80(name), X86_ASMSYSCALL32_SYSENTER(name)); \
		DEFINE_INTERN_ALIAS(X86_ASMSYSCALL64(name), X86_ASMSYSCALL32_SYSENTER(name));       \
		.cfi_startproc simple;                                                              \
		.cfi_iret_signal_frame;                                                             \
		.cfi_def_cfa %Psp, 0
#else /* __x86_64__ */
#define SC_BEGIN_ALL_NOTHROW(name)                                                          \
	.section _SYSFAST_SECTNAME(name);                                                       \
	INTERN_FUNCTION(X86_ASMSYSCALL32_SYSENTER(name));                                       \
		DEFINE_INTERN_ALIAS(X86_ASMSYSCALL32_INT80(name), X86_ASMSYSCALL32_SYSENTER(name)); \
		.cfi_startproc simple;                                                              \
		.cfi_iret_signal_frame;                                                             \
		.cfi_def_cfa %Psp, 0
#endif /* !__x86_64__ */
#define SC_END_ALL_NOTHROW(name) \
		.cfi_endproc;            \
	END(X86_ASMSYSCALL32_SYSENTER(name))
#endif /* !SC_BEGIN_ALL_NOTHROW */

#ifndef SC_BEGIN
/* Begin/End a system call definition.
 * Upon entry ...:
 *   - ... a `struct irregs_user' exists as `0(%Psp)'
 *   - ... EFLAGS.IF is enabled
 *   - ... on x86_64, `swapgs' was called (i.e. %gs.base is loaded for kernel-space)
 *   - ... %Pax has an undefined value (the original user-space was `_SYSFAST_SYSNO(name)')
 */
#define SC_BEGIN(name)                        \
	.section _SYSFAST_SECTNAME(name);         \
	INTERN_FUNCTION(_SYSFAST_FUNCNAME(name)); \
		_SYSFAST_SETALIAS(name);              \
		.cfi_startproc simple;                \
		.cfi_personality 0, _SYSFAST_PERSO;   \
		.cfi_lsda 0, _SYSFAST_SYSNO(name);    \
		.cfi_iret_signal_frame;               \
		.cfi_def_cfa %Psp, 0
#define SC_END(name)  \
		.cfi_endproc; \
	END(_SYSFAST_FUNCNAME(name))

/* On i386 only: push/pop %ds, %es and %fs. (no-op on x86_64)
 * NOTE: `SC386_INIT_SEGMENT_REGISTERS' will load kernel segments on i386! */
#ifdef __x86_64__
#define SC386_PUSH_SEGMENT_REGISTERS /* nothing */
#define SC386_INIT_SEGMENT_REGISTERS /* nothing */
#define SC386_POP_SEGMENT_REGISTERS  /* nothing */
#else /* __x86_64__ */
#define SC386_PUSH_SEGMENT_REGISTERS   \
	pushl_cfi %ds;                     \
	.cfi_restore_iret_ds_or_offset -4; \
	pushl_cfi %es;                     \
	.cfi_restore_iret_es_or_offset -8; \
	pushl_cfi %fs;                     \
	.cfi_restore_iret_fs_or_offset -12
#define SC386_INIT_SEGMENT_REGISTERS       \
	movl   $(SEGMENT_USER_DATA_RPL), %eax; \
	movl   %eax, %ds;                      \
	movl   %eax, %es;                      \
	movl   $(SEGMENT_KERNEL_FSBASE), %eax; \
	movl   %eax, %fs;                      \
	movl   %esp, %eax
#define SC386_POP_SEGMENT_REGISTERS \
	popl_cfi %fs;                   \
	.cfi_restore_iret_fs;           \
	popl_cfi %es;                   \
	.cfi_restore_iret_es;           \
	popl_cfi %ds;                   \
	.cfi_restore_iret_ds
#endif /* !__x86_64__ */

#endif /* SC_BEGIN */

/* Push/pop a `struct icpustate' to/from `0(%Psp)'
 * NOTES:
 *  - SC_PUSH_ICPUSTATE:
 *     - On i386, also includes `SC386_INIT_SEGMENT_REGISTERS'!
 *  - SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION:
 *     - Verifies that the sysenter argument extension vector
 *       doesn't point into kernel-space.
 *       Must be used when 5 or 6 registers are used by the system call.
 */
#ifdef __x86_64__
#ifndef SC_PUSH_ICPUSTATE
#define SC_PUSH_ICPUSTATE        ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R
#define SC_POP_ICPUSTATE         ASM_POP_ICPUSTATE_BEFORE_IRET_CFI_R
#define SC_POP_CLOBBER_NOPAX_ICPUSTATE \
	addq  $(32), %rsp;                 \
	.cfi_restore %r15;                 \
	.cfi_restore %r14;                 \
	.cfi_restore %r13;                 \
	.cfi_restore %r12;                 \
	popq_cfi_r %r11;                   \
	popq_cfi_r %r10;                   \
	popq_cfi_r %r9;                    \
	popq_cfi_r %r8;                    \
	popq_cfi_r %rdi;                   \
	popq_cfi_r %rsi;                   \
	movq  16(%rsp), %rdx;              \
	.cfi_restore %rdx;                 \
	movq  24(%rsp), %rcx;              \
	.cfi_restore %rcx;                 \
	addq  $(40), %rsp;                 \
	.cfi_restore %rbp;                 \
	.cfi_restore %rbx;                 \
	.cfi_restore %rax
#endif /* !SC_PUSH_ICPUSTATE */
#else /* __x86_64__ */
#ifndef SC_PUSH_ICPUSTATE
#define SC_PUSH_ICPUSTATE         \
	SC386_PUSH_SEGMENT_REGISTERS; \
	pushal_cfi_r;                 \
	SC386_INIT_SEGMENT_REGISTERS
#define SC_POP_ICPUSTATE \
	popal_cfi_r;         \
	SC386_POP_SEGMENT_REGISTERS
/* Only restore clobber-registers, excluding %Pax */
#define SC_POP_CLOBBER_NOPAX_ICPUSTATE     \
	movl  OFFSET_GPREGS32_EDX(%esp), %edx; \
	.cfi_restore %edx;                     \
	movl  OFFSET_GPREGS32_ECX(%esp), %ecx; \
	.cfi_restore %ecx;                     \
	addl  $(32), %esp;                     \
	.cfi_adjust_cfa_offset -32;            \
	.cfi_restore %edi;                     \
	.cfi_restore %esi;                     \
	.cfi_restore %ebp;                     \
/*	.cfi_restore %esp; */                  \
	.cfi_restore %ebx;                     \
	.cfi_restore %eax;                     \
	SC386_POP_SEGMENT_REGISTERS
#endif /* !SC_PUSH_ICPUSTATE */
#undef SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION
#ifdef SYSCALL_FASTPASS_KIND_SYS32_SYSENTER
#define SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION \
	SC386_PUSH_SEGMENT_REGISTERS;                      \
	cmpl   $(KERNELSPACE_BASE), %ebp;                  \
	jae    __asm32_bad_sysenter_extension;             \
	pushal_cfi_r;                                      \
	SC386_INIT_SEGMENT_REGISTERS
#endif /* SYSCALL_FASTPASS_KIND_SYS32_SYSENTER */
#endif /* !__x86_64__ */
#ifndef SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION
#define SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION \
	SC_PUSH_ICPUSTATE
#endif /* !SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION */








/* >> errno_t execveat(fd_t dirfd,
 * >>                  char const *filename,
 * >>                  char const *const *argv,
 * >>                  char const *const *envp,
 * >>                  atflag_t flags); */
#if _SYSFAST_WANT(EXECVEAT, execveat)
SC_BEGIN(execveat)
	SC_PUSH_ICPUSTATE_AND_CHECK_SYSENTER_EXTENSION
#ifdef __x86_64__
	pushq_cfi %rsp               /* struct icpustate  *state */
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	xorq   %r9, %r9              /* bool argv_is_compat = false */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	movq   $(1), %r9             /* bool argv_is_compat = true */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
#ifdef SYSCALL_FASTPASS_KIND_SYS64
/*  movq   _SYSFAST_R_arg5, %r8   * atflag_t           flags    (already set correctly) */
	movq   _SYSFAST_R_arg4, %rcx /* char const *const *envp = _SYSFAST_R_arg4(%r10) */
/*  movq   _SYSFAST_R_arg3, %rdx  * char const *const *argv     (already set correctly) */
/*  movq   _SYSFAST_R_arg2, %rsi  * char const        *pathname (already set correctly) */
/*  movq   _SYSFAST_R_arg1, %rdi  * fd_t               dirfd    (already set correctly) */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	movzlq _SYSFAST_R_arg5, %r8  /* atflag_t           flags */
	xchgl  %ecx, %esi            /* pathname / envp */
	movzlq %esi, %rsi            /* char const        *pathname */
	movzlq %ecx, %rcx            /* char const *const *envp */
	movzlq %edx, %rdx            /* char const *const *argv */
	movslq %ebx, %rdi            /* fd_t               dirfd */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
#else /* __x86_64__ */
	pushl_cfi %esp               /* struct icpustate  *state */
	pushl_cfi _SYSFAST_R_arg5    /* atflag_t           flags */
	pushl_cfi _SYSFAST_R_arg4    /* char const *const *envp */
	pushl_cfi _SYSFAST_R_arg3    /* char const *const *argv */
	pushl_cfi _SYSFAST_R_arg2    /* char const        *pathname */
	pushl_cfi _SYSFAST_R_arg1    /* fd_t               dirfd */
#endif /* !__x86_64__ */

	/* Call the high-level execv() handler function. */
	EXTERN(kernel_execveat)
	call   kernel_execveat

#ifndef __x86_64__
	.cfi_adjust_cfa_offset -24 /* STDCALL does callee-cleanup */
#else /* !__x86_64__ */
	addq   $(8), %rsp
	.cfi_adjust_cfa_offset -8
#endif /* __x86_64__ */

	/* Load the new register context stack. */
	movP   %Pax, %Psp
	SC_POP_ICPUSTATE
	/* Don't  clobber  registers, which  have painstakingly
	 * been set-up by the program loader. - _ALL_ registers
	 * must be well defined after an exec()! */
	SC_IRET_NOCLOBBER
SC_END(execveat)
#endif /* execveat... */








/* >> errno_t execve(char const *filename,
 * >>                char const const *argv,
 * >>                char const const *envp); */
#if _SYSFAST_WANT(EXECVE, execve)
SC_BEGIN(execve)
	SC_PUSH_ICPUSTATE
#ifdef __x86_64__
	pushq_cfi %rsp               /* struct icpustate  *state */
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	xorq   %r9, %r9              /* bool argv_is_compat = false */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	movq   $(1), %r9             /* bool argv_is_compat = true */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
	xorq   %r8, %r8              /* atflag_t           flags */
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	movq   %rdx,            %rcx /* char const *const *envp */
	movq   %rsi,            %rdx /* char const *const *argv */
	movq   %rdi,            %rsi /* char const        *pathname */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	xchgl  %ecx, %edx
	movzlq %ecx,            %rcx /* char const *const *envp */
	movzlq %edx,            %rdx /* char const *const *argv */
	movzlq %ebx,            %rsi /* char const        *pathname */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
	movq   $(AT_FDCWD),     %rdi /* fd_t               dirfd */
#else /* __x86_64__ */
	pushl_cfi %esp               /* struct icpustate  *state */
	pushl_cfi $(0)               /* atflag_t           flags */
	pushl_cfi _SYSFAST_R_arg3    /* char const *const *envp */
	pushl_cfi _SYSFAST_R_arg2    /* char const *const *argv */
	pushl_cfi _SYSFAST_R_arg1    /* char const        *pathname */
	pushl_cfi $(AT_FDCWD)        /* fd_t               dirfd */
#endif /* !__x86_64__ */

	/* Call the high-level execv() handler function. */
	EXTERN(kernel_execveat)
	call   kernel_execveat

#ifndef __x86_64__
	.cfi_adjust_cfa_offset -24 /* STDCALL does callee-cleanup */
#else /* !__x86_64__ */
	addq   $(8), %rsp
	.cfi_adjust_cfa_offset -8
#endif /* __x86_64__ */

	/* Load the new register context stack. */
	movP   %Pax, %Psp
	SC_POP_ICPUSTATE
	/* Don't  clobber  registers, which  have painstakingly
	 * been set-up by the program loader. - _ALL_ registers
	 * must be well defined after an exec()! */
	SC_IRET_NOCLOBBER
SC_END(execve)
#endif /* execve... */








/* >> errno_t debugtrap(struct ucpustate const *state,
 * >>                   struct debugtrap_reason const *reason); */
#if _SYSFAST_WANT(DEBUGTRAP, debugtrap)
SC_BEGIN(debugtrap)
	SC_PUSH_ICPUSTATE

	/* Call forward to `sys_debugtrap(32|64)_impl()' */
#ifdef __x86_64__
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	movq   %rsi, %rdx   /* Arg #2 (struct debugtrap_reason const *ureason) */
	movq   %rdi, %rsi   /* Arg #1 (struct ucpustate const *state) */
	movq   %rsp, %rdi   /* struct icpustate *return_state */
	EXTERN(sys_debugtrap64_impl)
	call   sys_debugtrap64_impl
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	movzlq %ecx, %rdx   /* Arg #2 (struct debugtrap_reason const *ureason) */
	movzlq %ebx, %rsi   /* Arg #1 (struct ucpustate const *state) */
	movq   %rsp, %rdi   /* struct icpustate *return_state */
	EXTERN(sys_debugtrap32_impl)
	call   sys_debugtrap32_impl
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
#else /* __x86_64__ */
	pushl_cfi %ecx        /* Arg #2 (struct debugtrap_reason const *ureason) */
	movl   %ebx, %edx     /* Arg #1 (struct ucpustate const *state) */
	leal   4(%esp), %ecx  /* struct icpustate *return_state */
	EXTERN(sys_debugtrap32_impl)
	call   sys_debugtrap32_impl
	.cfi_adjust_cfa_offset -4
#endif /* !__x86_64__ */

	/* Load the new register context stack. */
	movP   %Pax, %Psp
	SC_POP_ICPUSTATE
	SC_IRET_NOCLOBBER /* State may have been modified; -- Mustn't clobber any registers! */
SC_END(debugtrap)
#endif /* debugtrap... */








/* >> errno_t iopl(syscall_ulong_t level); */
#if _SYSFAST_WANT(IOPL, iopl)
SC_BEGIN(iopl)
	/* XXX: Don't need a full icpustate!
	 *      sys_iopl_impl() only needs to set %Pflags! */
	SC_PUSH_ICPUSTATE

	/* Call forward to `sys_iopl_impl()' */
#if defined(__x86_64__) && !defined(SYSCALL_FASTPASS_KIND_SYS64)
	movzlq _SYSFAST_R_arg1, %R_fcall1P /* level */
#else /* __x86_64__ && !SYSCALL_FASTPASS_KIND_SYS64 */
	movP   _SYSFAST_R_arg1, %R_fcall1P /* level */
#endif /* !__x86_64__ || SYSCALL_FASTPASS_KIND_SYS64 */
	movP   %Psp,            %R_fcall0P /* struct icpustate *state */
	EXTERN(sys_iopl_impl)
	call   sys_iopl_impl

	/* Load the new register context stack. */
	movP   %Pax, %Psp
	SC_POP_ICPUSTATE
	SC_IRET
SC_END(iopl)
#endif /* iopl... */








/* >> pid_t clone3(struct clone_args *args, size_t size); */
#if _SYSFAST_WANT(CLONE3, clone3)
SC_BEGIN(clone3)
	SC_PUSH_ICPUSTATE

	/* Call forward to `sys_clone3(32|64)_impl()' */
#ifdef __x86_64__
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	movq   %rsi, %rdx   /* Arg #2 (struct clone3_reason const *ureason) */
	movq   %rdi, %rsi   /* Arg #1 (struct ucpustate const *state) */
	movq   %rsp, %rdi   /* struct icpustate *return_state */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	movzlq %ecx, %rdx   /* Arg #2 (struct clone3_reason const *ureason) */
	movzlq %ebx, %rsi   /* Arg #1 (struct ucpustate const *state) */
	movq   %rsp, %rdi   /* struct icpustate *return_state */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
	EXTERN(sys_clone3_impl)
	call   sys_clone3_impl
#else /* __x86_64__ */
	pushl_cfi %ecx        /* Arg #2 (struct clone3_reason const *ureason) */
	movl   %ebx, %edx     /* Arg #1 (struct ucpustate const *state) */
	leal   4(%esp), %ecx  /* struct icpustate *return_state */
	EXTERN(sys_clone3_impl)
	call   sys_clone3_impl
	.cfi_adjust_cfa_offset -4
#endif /* !__x86_64__ */

	SC_POP_CLOBBER_NOPAX_ICPUSTATE
	SC_IRET
SC_END(clone3)
#endif /* clone3... */








/* >> pid_t fork(void); */
#if _SYSFAST_WANT(FORK, fork)
SC_BEGIN(fork)
	SC_PUSH_ICPUSTATE
	movP   %Psp, %R_fcall0P
	EXTERN(sys_fork_impl)
	call   sys_fork_impl
	SC_POP_CLOBBER_NOPAX_ICPUSTATE
	SC_IRET
SC_END(fork)
#endif /* fork... */








/* >> pid_t vfork(void); */
#if _SYSFAST_WANT(VFORK, vfork)
SC_BEGIN(vfork)
	SC_PUSH_ICPUSTATE
	movP   %Psp, %R_fcall0P
	EXTERN(sys_vfork_impl)
	call   sys_vfork_impl
	SC_POP_CLOBBER_NOPAX_ICPUSTATE
	SC_IRET
SC_END(vfork)
#endif /* vfork... */








/* >> rtm_status_t rtm_begin(void); */
#if _SYSFAST_WANT(RTM_BEGIN, rtm_begin)
SC_BEGIN(rtm_begin)
	SC_PUSH_ICPUSTATE
	movP   %Psp, %R_fcall0P
	EXTERN(sys_rtm_begin_impl)
	call   sys_rtm_begin_impl
	movP   %Pax, %Psp
	SC_POP_ICPUSTATE
	SC_IRET_NOCLOBBER /* State may have been modified; -- Mustn't clobber any registers! */
SC_END(rtm_begin)
#endif /* rtm_begin... */








/* >> syscall_ulong_t rtm_test(void); */
#if _SYSFAST_WANT(RTM_TEST, rtm_test)
#ifndef _SC_RTM_TEST_DEFINED
#define _SC_RTM_TEST_DEFINED 1
SC_BEGIN_ALL_NOTHROW(rtm_test)
	/* Special arch-specific system call behavior:
	 *    In order to more closely match the behavior  of
	 *    the x86  `xtest' instruction  (which sets  ZF=1
	 *    when outside of RTM mode), we do the same, thus
	 *    simplifying the user-space RTM testing code.
	 */
	orP  $(EFLAGS_ZF), CSMEM OFFSET_IRREGS_PFLAGS(%Psp)
	/* return 0 */
	xorP %Pax, %Pax
	SC_IRET
SC_END_ALL_NOTHROW(rtm_test)
#endif /* !_SC_RTM_TEST_DEFINED */
#endif /* rtm_test... */








/* >> errno_t rtm_abort(syscall_ulong_t code); */
#if _SYSFAST_WANT(RTM_ABORT, rtm_abort)
#ifndef _SC_RTM_ABORT_DEFINED
#define _SC_RTM_ABORT_DEFINED 1
SC_BEGIN_ALL_NOTHROW(rtm_abort)
	/* return -EOK; */
	xorP %Pax, %Pax
	SC_IRET
SC_END_ALL_NOTHROW(rtm_abort)
#endif /* !_SC_RTM_ABORT_DEFINED */
#endif /* rtm_abort... */








/* >> errno_t sigsuspend(USER UNCHECKED sigset_t const *unot_these); */
#if _SYSFAST_WANT(SIGSUSPEND, sigsuspend)
SC_BEGIN(sigsuspend)
	SC_PUSH_ICPUSTATE
#ifdef __x86_64__ /* Because %R_fcall0P <=> %R_syscall0P <=> %rdi */
	subP   $(Pn(5)), %Psp                                           /* rpc_syscall_info::rsi_regs[1-5] */
	.cfi_adjust_cfa_offset Pn(5)
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	pushq_cfi %rdi                                                  /* rpc_syscall_info::rsi_regs[0] */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
	movzlq %ebx, %rbx
	pushq_cfi %rbx                                                  /* rpc_syscall_info::rsi_regs[0] */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
	leaP   Pn(6)(%Psp), %R_fcall0P              /* arg: sys_sigsuspend_impl@state */
#else /* __x86_64__ */
	movP   %Psp, %R_fcall0P                     /* arg: sys_sigsuspend_impl@state */
	subP   $(Pn(5)), %Psp                                           /* rpc_syscall_info::rsi_regs[1-5] */
	.cfi_adjust_cfa_offset Pn(5)
	pushl_cfi %ebx                                                  /* rpc_syscall_info::rsi_regs[0] */
#endif /* !__x86_64__ */
	pushP_cfi $(_SYSFAST_SYSNO(sigsuspend))                         /* rpc_syscall_info::rsi_sysno */
	pushP_cfi $(_SYSFAST_RPCMETHOD | RPC_SYSCALL_INFO_FREGVALID(0)) /* rpc_syscall_info::rsi_flags */
	testP  $(EFLAGS_DF), OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_PFLAGS(%R_fcall0P)
	jz     1f
	orP    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%Psp)
1:	movP   %Psp, %R_fcall1P                         /* arg: sys_sigsuspend_impl@sc_info */
#ifdef __x86_64__
	movP   $(__SIZEOF_OLD_SIGSET_T__), %R_sysvabi2P /* arg: sys_sigsuspend_impl@sigsetsize */
#else /* __x86_64__ */
	pushP_cfi $(__SIZEOF_OLD_SIGSET_T__)            /* arg: sys_sigsuspend_impl@sigsetsize */
#endif /* !__x86_64__ */
	EXTERN(sys_sigsuspend_impl)
	call   sys_sigsuspend_impl
	/* Never returns in a normal way */
	nop
SC_END(sigsuspend)
#endif /* sigsuspend... */








/* >> errno_t rt_sigsuspend(USER UNCHECKED sigset_t const *unot_these, size_t sigsetsize); */
#if _SYSFAST_WANT(RT_SIGSUSPEND, rt_sigsuspend)
SC_BEGIN(rt_sigsuspend)
	SC_PUSH_ICPUSTATE
	subP   $(Pn(4)), %Psp                                           /* rpc_syscall_info::rsi_regs[2-5] */
	.cfi_adjust_cfa_offset Pn(4)
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	pushP_cfi %R_syscall1P                                          /* rpc_syscall_info::rsi_regs[1] */
	pushP_cfi %R_syscall0P                                          /* rpc_syscall_info::rsi_regs[0] */
#else /* SYSCALL_FASTPASS_KIND_SYS64 */
#ifdef __x86_64__
	movzlq %ecx, %rcx /* Zero-extend */
	movzlq %ebx, %rbx /* Zero-extend */
#endif /* __x86_64__ */
	pushP_cfi %Pcx  /* %R_syscall1P */                              /* rpc_syscall_info::rsi_regs[1] */
	pushP_cfi %Pbx  /* %R_syscall0P */                              /* rpc_syscall_info::rsi_regs[0] */
#endif /* !SYSCALL_FASTPASS_KIND_SYS64 */
	pushP_cfi $(_SYSFAST_SYSNO(rt_sigsuspend))                      /* rpc_syscall_info::rsi_sysno */
	pushP_cfi $(_SYSFAST_RPCMETHOD | RPC_SYSCALL_INFO_FREGVALID(0) | \
	            RPC_SYSCALL_INFO_FREGVALID(1))                      /* rpc_syscall_info::rsi_flags */
	testP  $(EFLAGS_DF), (OFFSET_ICPUSTATE_IRREGS+OFFSET_IRREGS_PFLAGS+Pn(8))(%Psp)
	jz     1f
	orP    $(RPC_SYSCALL_INFO_FEXCEPT), 0(%Psp)
1:
#ifdef SYSCALL_FASTPASS_KIND_SYS64
	/* TRANSFORM:
	 *   %Psp       --> %Psi   (%Psp         --> %R_sysvabi1P)
	 *   %Psi       --> %Pdx   (%R_syscall1P --> %R_sysvabi2P)
	 *   %Psp+Pn(8) --> %Pdi   (%Psp+Pn(8)   --> %R_sysvabi0P) */
	leaP   Pn(8)(%Psp),  %R_sysvabi0P /* arg: sys_sigsuspend_impl@state */
	movP   %R_syscall1P, %R_sysvabi2P /* arg: sys_sigsuspend_impl@sigsetsize */
	movP   %Psp,         %R_sysvabi1P /* arg: sys_sigsuspend_impl@sc_info */
#elif defined(__x86_64__)
	/* TRANSFORM:
	 *   %Psp       --> %Psi   (%Psp                --> %R_sysvabi1P)
	 *   %Pcx       --> %Pdx   (%COMPAT_R_syscall1P --> %R_sysvabi2P)
	 *   %Psp+Pn(8) --> %Pdi   (%Psp+Pn(8)          --> %R_sysvabi0P) */
	leaP   Pn(8)(%Psp),  %R_sysvabi0P /* arg: sys_sigsuspend_impl@state */
	movP   %Pcx,         %R_sysvabi2P /* arg: sys_sigsuspend_impl@sigsetsize */
	movP   %Psp,         %R_sysvabi1P /* arg: sys_sigsuspend_impl@sc_info */
#else /* __x86_64__ */
	/* TRANSFORM:
	 *   %Psp       --> %Pdx   (%Psp                --> %R_fcall1P)
	 *   pushP %Pcx            (pushP %R_syscall1P)
	 *   %Psp+Pn(8) --> %Pcx   (%Psp+Pn(8)          --> %R_fcall0P) */
	movP   %Psp, %R_fcall1P           /* arg: sys_sigsuspend_impl@sc_info */
	pushP_cfi %R_syscall1P            /* arg: sys_sigsuspend_impl@sigsetsize */
	leaP   Pn(9)(%Psp), %R_fcall0P    /* arg: sys_sigsuspend_impl@state */
#endif /* !__x86_64__ */
	EXTERN(sys_sigsuspend_impl)
	call   sys_sigsuspend_impl
	/* Never returns in a normal way */
	nop
SC_END(rt_sigsuspend)
#endif /* rt_sigsuspend... */








/* TODO: sigreturn() / rt_sigreturn() */
/* TODO: clone() */
/* TODO: coredump() */

#undef _SYSFAST_R_arg1
#undef _SYSFAST_R_arg2
#undef _SYSFAST_R_arg3
#undef _SYSFAST_R_arg4
#undef _SYSFAST_R_arg5
#undef _SYSFAST_R_arg6

#undef _SYSFAST_SECTNAME
#undef _SYSFAST_FUNCNAME
#undef _SYSFAST_RPCMETHOD
#undef _SYSFAST_SYSNO
#undef _SYSFAST_PERSO
#undef _SYSFAST_SETALIAS
#undef _SYSFAST_WANT

#undef SYSCALL_FASTPASS_KIND_SYS32_SYSENTER
#undef SYSCALL_FASTPASS_KIND_SYS32_INT80
#undef SYSCALL_FASTPASS_KIND_SYS64
