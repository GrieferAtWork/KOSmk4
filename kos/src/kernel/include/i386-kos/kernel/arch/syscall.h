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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

#include <asm/unistd.h>

#ifdef __x86_64__
#include <asm/syscalls32.inl>
#endif /* __x86_64__ */

#define ATTR_SECTION_SYSCALL(name)   ATTR_SECTION(".text.x86.syscall." #name)
#ifdef __x86_64__
#define ATTR_SECTION_SYSCALL32(name) ATTR_SECTION(".text.x86.syscall32." #name)
#endif /* __x86_64__ */


/* System call calling conventions:
 *
 * i386: int $0x80
 *   - SYSNO:     %eax
 *   - ARG0:      %ebx
 *   - ARG1:      %ecx
 *   - ARG2:      %edx
 *   - ARG3:      %esi
 *   - ARG4:      %edi
 *   - ARG5:      %ebp
 *   - RET0:      %eax
 *   - RET1:      %edx
 *
 * i386: sysenter
 *   - SYSNO:     %eax
 *   - ARG0:      %ebx
 *   - ARG1:      %ecx
 *   - ARG2:      %edx
 *   - ARG3:      %esi
 *   - ARG4:    0(%ebp)
 *   - ARG5:    4(%ebp)
 *   - RET0:      %eax
 *   - RET1:      %edx
 *   - RET(%eip): %edi
 *   - RET(%esp): %ebp
 *
 * x86_64: int $0x80 / syscall
 *   - SYSNO:     %rax
 *   - ARG0:      %rdi
 *   - ARG1:      %rsi
 *   - ARG2:      %rdx
 *   - ARG3:      %r10
 *   - ARG4:      %r8
 *   - ARG5:      %r9
 *   - RET0:      %rax
 *   - RET1:      %rdx
 *
 * i386: lcall $7, $MAYBE_SYSNO
 *   - SYSNO:     MAYBE_SYSNO != 0 ? MAYBE_SYSNO : %eax
 *   - ARG0:      0(%esp)  // NOTE: Only accessed if used
 *   - ARG1:      4(%esp)  // NOTE: Only accessed if used
 *   - ARG2:      8(%esp)  // NOTE: Only accessed if used
 *   - ARG3:      12(%esp) // NOTE: Only accessed if used
 *   - ARG4:      16(%esp) // NOTE: Only accessed if used
 *   - ARG5:      20(%esp) // NOTE: Only accessed if used
 *   - RET0:      %eax
 *   - RET1:      %edx
 *
 */


#ifdef CONFIG_BUILDING_KERNEL_CORE
/* Mangled names for assembly wrappers for a given
 * system call, when invoked via the specified mechanism.
 * Any possible combination of these is pre-defined as a
 * weak-internal wrapper that calls the associated `sys_##name'
 * function whilst passing the correct number and combination
 * of arguments, before correctly propagating the system call's
 * return value back into user-space.
 * NOTE: These macros are mainly provided since some system calls
 *       are better implemented in assembly, such as sched_yield
 *       being implemented such that the task's scpustate will
 *       already point back into user-space, as well as other
 *       system calls such as `sigreturn', which don't even have
 *       any real prototype.
 * NOTE: In x86_64, the 386 symbols refer to the symbols that are
 *       called by a process in 32-bit compatibility-mode.
 * For the default implementations, see:
 *  - /src/kernel/core/arch/i386/syscall_wrappers32.S
 *  - /src/kernel/core/arch/i386/syscall_wrappers64.S
 * Register state upon entry:
 *     X86_ASMSYSCALL32_INT80:
 *         i386:    Unchanged (all registers are the same)
 *         x86_64:  Unchanged (all registers are the same) (NOTE: Compatibility-mode)
 *     X86_ASMSYSCALL32_SYSENTER:
 *         i386:    - %esp has been loaded
 *                  - A user-space IRET tail was pushed and created
 *         x86_64:  TODO: Not yet decided
 *     X86_ASMSYSCALL64:
 *         x86_64:  TODO: Not yet decided
 * HINT: The low-level interrupt/entry handlers
 *       for system calls are implemented in:
 *        - /src/kernel/core/arch/i386/syscall32.S
 *        - /src/kernel/core/arch/i386/syscall64.S
 */
#define X86_ASMSYSCALL32_INT80(name)         __asm32_int80_##name     /* Section: .text.x86.asm32_syscall_int80.<name> */
#define X86_ASMSYSCALL32_SYSENTER(name)      __asm32_sysenter_##name  /* Section: .text.x86.asm32_syscall_sysenter.<name> */
#ifdef __x86_64__
#define X86_ASMSYSCALL64(name)               __asm64_syscall_##name   /* Section: .text.x86.asm64_syscall.<name> */
#endif /* __x86_64__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */


#ifdef __CC__
DECL_BEGIN

struct icpustate;

/* Emulate an int80 / sysenter system call invocation, given a user-space register state. */
FUNDEF struct icpustate *FCALL syscall_emulate_int80(struct icpustate *__restrict regs);
FUNDEF struct icpustate *FCALL syscall_emulate_sysenter(struct icpustate *__restrict regs);


#define SYSCALL_RESTART_MODE_AUTO 0 /* Automatic restarting */
#define SYSCALL_RESTART_MODE_DONT 1 /* Don't restart */
#define SYSCALL_RESTART_MODE_MUST 2 /* Always restart */


/* System call restart mode / cancellation point configuration */
DATDEF __UINT8_TYPE__ const x86_syscall_restart_mode[];            /* 0 ... __NR_syscall_max */
DATDEF __UINT8_TYPE__ const x86_exsyscall_restart_mode[];          /* __NR_exsyscall_min ... __NR_exsyscall_max */
DATDEF __UINT8_TYPE__ const x86_syscall_is_cancellation_point[];   /* 0 ... __NR_syscall_max */
DATDEF __UINT8_TYPE__ const x86_exsyscall_is_cancellation_point[]; /* __NR_exsyscall_min ... __NR_exsyscall_max */
#ifdef __x86_64__ /* Argument counts of 386 compatibility mode system calls. */
DATDEF __UINT8_TYPE__ const x86_syscall32_restart_mode[];            /* 0 ... __NR32_syscall_max */
DATDEF __UINT8_TYPE__ const x86_exsyscall32_restart_mode[];          /* __NR32_exsyscall_min ... __NR32_exsyscall_max */
DATDEF __UINT8_TYPE__ const x86_syscall32_is_cancellation_point[];   /* 0 ... __NR_syscall_max */
DATDEF __UINT8_TYPE__ const x86_exsyscall32_is_cancellation_point[]; /* __NR_exsyscall_min ... __NR_exsyscall_max */
#endif /* __x86_64__ */

FORCELOCAL ATTR_CONST NOBLOCK __UINT8_TYPE__
NOTHROW(KCALL x86_syscall_restart_mode_get)(__UINT8_TYPE__ const *__restrict base,
                                            __REGISTER_TYPE__ rel_sysno) {
	return (base[rel_sysno / 4] >> (2 * (rel_sysno % 4))) & 3;
}

FORCELOCAL ATTR_CONST NOBLOCK __BOOL
NOTHROW(KCALL x86_exsyscall_is_cancellation_point_get)(__UINT8_TYPE__ const *__restrict base,
                                                       __REGISTER_TYPE__ rel_sysno) {
	return (base[rel_sysno / 8] >> (rel_sysno % 8)) & 1;
}

#define SYSCALL_RESTART_MODE_EX(sysno, error)                                                 \
	((sysno) <= __NR_syscall_max                                                              \
	 ? x86_syscall_restart_mode_get(x86_syscall_restart_mode, sysno)                          \
	 : ((sysno) >= __NR_exsyscall_min && (sysno) <= __NR_exsyscall_max)                       \
	   ? x86_syscall_restart_mode_get(x86_exsyscall_restart_mode, (sysno)-__NR_exsyscall_min) \
	   : (error))
#define SYSCALL_RESTART_MODE(sysno) \
	SYSCALL_RESTART_MODE_EX(sysno, SYSCALL_RESTART_MODE_AUTO)
#define SYSCALL_IS_CANCELLATION_POINT_EX(sysno, error)                                                            \
	((sysno) <= __NR_syscall_max                                                                                  \
	 ? x86_exsyscall_is_cancellation_point_get(x86_syscall_is_cancellation_point, sysno)                          \
	 : ((sysno) >= __NR_exsyscall_min && (sysno) <= __NR_exsyscall_max)                                           \
	   ? x86_exsyscall_is_cancellation_point_get(x86_exsyscall_is_cancellation_point, (sysno)-__NR_exsyscall_min) \
	   : (error))
#define SYSCALL_IS_CANCELLATION_POINT(sysno) \
	SYSCALL_IS_CANCELLATION_POINT_EX(sysno, 1)
#ifdef __x86_64__ /* Argument counts of 386 compatibility mode system calls. */
#define SYSCALL32_RESTART_MODE_EX(sysno, error)                                                   \
	((sysno) <= __NR32_syscall_max                                                                \
	 ? x86_syscall_restart_mode_get(x86_syscall32_restart_mode, sysno)                            \
	 : ((sysno) >= __NR32_exsyscall_min && (sysno) <= __NR32_exsyscall_max)                       \
	   ? x86_syscall_restart_mode_get(x86_exsyscall32_restart_mode, (sysno)-__NR32_exsyscall_min) \
	   : (error))
#define SYSCALL32_RESTART_MODE(sysno) \
	SYSCALL32_RESTART_MODE_EX(sysno, SYSCALL_RESTART_MODE_AUTO)
#define SYSCALL32_IS_CANCELLATION_POINT_EX(sysno, error)                                                              \
	((sysno) <= __NR32_syscall_max                                                                                    \
	 ? x86_exsyscall_is_cancellation_point_get(x86_syscall32_is_cancellation_point, sysno)                            \
	 : ((sysno) >= __NR32_exsyscall_min && (sysno) <= __NR32_exsyscall_max)                                           \
	   ? x86_exsyscall_is_cancellation_point_get(x86_exsyscall32_is_cancellation_point, (sysno)-__NR32_exsyscall_min) \
	   : (error))
#define SYSCALL32_IS_CANCELLATION_POINT(sysno) \
	SYSCALL32_IS_CANCELLATION_POINT_EX(sysno, 1)
#endif /* !__x86_64__ */


/* System call argument count (adjusted for the number of used registers) */
DATDEF __UINT8_TYPE__ const x86_syscall_register_count[];   /* 0 ... __NR_syscall_max */
DATDEF __UINT8_TYPE__ const x86_exsyscall_register_count[]; /* __NR_exsyscall_min ... __NR_exsyscall_max */
#ifdef __x86_64__ /* Argument counts of 386 compatibility mode system calls. */
DATDEF __UINT8_TYPE__ const x86_syscall32_register_count[];   /* 0 ... __NR32_syscall_max */
DATDEF __UINT8_TYPE__ const x86_exsyscall32_register_count[]; /* __NR32_exsyscall_min ... __NR32_exsyscall_max */
#endif /* __x86_64__ */
FORCELOCAL ATTR_CONST NOBLOCK __UINT8_TYPE__
NOTHROW(KCALL x86_syscall_register_count_get)(__UINT8_TYPE__ const *__restrict base,
                                              __REGISTER_TYPE__ rel_sysno) {
	return rel_sysno & 1
	       ? (base[rel_sysno / 2] & 0x70) >> 4
	       : (base[rel_sysno / 2] & 0x07);
}
FORCELOCAL ATTR_CONST NOBLOCK bool
NOTHROW(KCALL x86_syscall_double_wide_get)(__UINT8_TYPE__ const *__restrict base,
                                           __REGISTER_TYPE__ rel_sysno) {
	return rel_sysno & 1
	       ? (base[rel_sysno / 2] & 0x80) != 0
	       : (base[rel_sysno / 2] & 0x08) != 0;
}

/* Evaluate the number of registers used by a given system call. */
#define SYSCALL_REGISTER_COUNT(sysno) \
	SYSCALL_REGISTER_COUNT_EX(sysno, 0)
#define SYSCALL_REGISTER_COUNT_EX(sysno, error)                                                   \
	((sysno) <= __NR_syscall_max                                                                  \
	 ? x86_syscall_register_count_get(x86_syscall_register_count, sysno)                          \
	 : ((sysno) >= __NR_exsyscall_min && (sysno) <= __NR_exsyscall_max)                           \
	   ? x86_syscall_register_count_get(x86_exsyscall_register_count, (sysno)-__NR_exsyscall_min) \
	   : (error))
#ifdef __x86_64__ /* Argument counts of 386 compatibility mode system calls. */
#define SYSCALL_REGISTER_COUNT_386(sysno) \
	SYSCALL_REGISTER_COUNT_386_EX(sysno, 0)
#define SYSCALL_REGISTER_COUNT_386_EX(sysno, error)                                                   \
	((sysno) <= __NR32_syscall_max                                                                    \
	 ? x86_syscall_register_count_get(x86_syscall32_register_count, sysno)                            \
	 : ((sysno) >= __NR32_exsyscall_min && (sysno) <= __NR32_exsyscall_max)                           \
	   ? x86_syscall_register_count_get(x86_exsyscall32_register_count, (sysno)-__NR32_exsyscall_min) \
	   : (error))
#define SYSCALL32_DOUBLE_WIDE(sysno) \
	SYSCALL32_DOUBLE_WIDE_EX(sysno, 0)
#define SYSCALL32_DOUBLE_WIDE_EX(sysno, error)                                                     \
	((sysno) <= __NR32_syscall_max                                                                 \
	 ? x86_syscall_double_wide_get(x86_syscall32_register_count, sysno)                            \
	 : ((sysno) >= __NR32_exsyscall_min && (sysno) <= __NR32_exsyscall_max)                        \
	   ? x86_syscall_double_wide_get(x86_exsyscall32_register_count, (sysno)-__NR32_exsyscall_min) \
	   : (error))
#else /* __x86_64__ */
#define SYSCALL32_DOUBLE_WIDE(sysno) \
	SYSCALL32_DOUBLE_WIDE_EX(sysno, 0)
#define SYSCALL32_DOUBLE_WIDE_EX(sysno, error)                                                 \
	((sysno) <= __NR_syscall_max                                                               \
	 ? x86_syscall_double_wide_get(x86_syscall_register_count, sysno)                          \
	 : ((sysno) >= __NR_exsyscall_min && (sysno) <= __NR_exsyscall_max)                        \
	   ? x86_syscall_double_wide_get(x86_exsyscall_register_count, (sysno)-__NR_exsyscall_min) \
	   : (error))
#endif /* !__x86_64__ */

DECL_END


/* Define compatibility-mode system calls. */
#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __x86_64__
/* When defining a 64-bit system call, weakly alias the 32-bit variant onto it, thus
 * implementing system calls without dedicated compatibility-mode variants by calling
 * forward to their 64-bit (regular) variants. */

#define DEFINE_SYSCALL32_0(return_type, name)                                            \
	STATIC_ASSERT(__NR32AC_##name == 0);                                                 \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));           \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(void) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(void)
#define DEFINE_SYSCALL32_1(return_type, name, T0, N0)                                     \
	STATIC_ASSERT(__NR32AC_##name == 1);                                                  \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT0_##name, T0));                    \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0)
#define DEFINE_SYSCALL32_2(return_type, name, T0, N0, T1, N1)                                    \
	STATIC_ASSERT(__NR32AC_##name == 2);                                                         \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT0_##name, T0));                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT1_##name, T1));                           \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1)
#define DEFINE_SYSCALL32_3(return_type, name, T0, N0, T1, N1, T2, N2)                                   \
	STATIC_ASSERT(__NR32AC_##name == 3);                                                                \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));                          \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT0_##name, T0));                                  \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT1_##name, T1));                                  \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT2_##name, T2));                                  \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2)
#define DEFINE_SYSCALL32_4(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3)                                  \
	STATIC_ASSERT(__NR32AC_##name == 4);                                                                       \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));                                 \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT0_##name, T0));                                         \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT1_##name, T1));                                         \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT2_##name, T2));                                         \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT3_##name, T3));                                         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3)
#define DEFINE_SYSCALL32_5(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4)                                 \
	STATIC_ASSERT(__NR32AC_##name == 5);                                                                              \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));                                        \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT0_##name, T0));                                                \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT1_##name, T1));                                                \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT2_##name, T2));                                                \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT3_##name, T3));                                                \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT4_##name, T4));                                                \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4)
#define DEFINE_SYSCALL32_6(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4, T5, N5)                                \
	STATIC_ASSERT(__NR32AC_##name == 6);                                                                                     \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32RT_##name, return_type));                                               \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT0_##name, T0));                                                       \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT1_##name, T1));                                                       \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT2_##name, T2));                                                       \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT3_##name, T3));                                                       \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT4_##name, T4));                                                       \
	STATIC_ASSERT(__builtin_types_compatible_p(__NR32AT5_##name, T5));                                                       \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5)
#else /* __x86_64__ */
#define DEFINE_SYSCALL32_0 DEFINE_SYSCALL0
#define DEFINE_SYSCALL32_1 DEFINE_SYSCALL1
#define DEFINE_SYSCALL32_2 DEFINE_SYSCALL2
#define DEFINE_SYSCALL32_3 DEFINE_SYSCALL3
#define DEFINE_SYSCALL32_4 DEFINE_SYSCALL4
#define DEFINE_SYSCALL32_5 DEFINE_SYSCALL5
#define DEFINE_SYSCALL32_6 DEFINE_SYSCALL6
#endif /* !__x86_64__ */
#endif /* CONFIG_BUILDING_KERNEL_CORE */


#endif /* __CC__ */




#ifdef __ASSEMBLER__
#ifdef __x86_64__

#ifdef __OPTIMIZE_SIZE__
#define X86_IRET_BUT_PREFER_SYSRET iretq
#else /* __OPTIMIZE_SIZE__ */
#define X86_IRET_BUT_PREFER_SYSRET iretq /* TODO: Use sysret */
#endif /* !__OPTIMIZE_SIZE__ */

#else /* __x86_64__ */

/* A fast-path implementation for returning from sysenter-like system
 * call handlers, operating identical to the invocation of `iret' at
 * the same location. */
#ifdef __OPTIMIZE_SIZE__
#define X86_IRET_BUT_PREFER_SYSEXIT iret
#elif !defined(CONFIG_NO_VM86)
#define X86_IRET_BUT_PREFER_SYSEXIT                                           \
	cli;                                                                      \
	cmpl   $SEGMENT_USER_CODE, OFFSET_IRREGS_CS(%esp);                        \
	jne    99f;                                                               \
	testl  $EFLAGS_VM, OFFSET_IRREGS_EFLAGS(%esp);                            \
	jnz    99f;                                                               \
	movl   OFFSET_IRREGS_ESP(%esp), %ecx;                                     \
	movl   OFFSET_IRREGS_EIP(%esp), %edx;                                     \
	addl   $8, %esp;                                                          \
	.cfi_adjust_cfa_offset - 8;                                               \
	/* Prevent popfl from enabling interrupts to bypass a race condition      \
	 * that could result in an interrupt attempting to re-direct user-space   \
	 * at a time where registers it would modify were already loaded.         \
	 * This race condition doesn't happen with IRET, because it executes      \
	 * atomically (or rather: without interrupts). */                         \
	andl   $~EFLAGS_IF, (%esp);                                               \
	popfl;                                                                    \
	/* Enable interrupts in a way that delays its execution for 1             \
	 * additional instruction, meaning that no interrupts can occur           \
	 * before `sysexit' actually returns to user-space.                       \
	 * NOTE: `popfl' doesn't have this effect, so this clutch is required. */ \
	sti;                                                                      \
	sysexit;                                                                  \
	.cfi_adjust_cfa_offset 8;                                                 \
99:	iret
#else /* __OPTIMIZE_SIZE__ */
#define X86_IRET_BUT_PREFER_SYSEXIT                                           \
	cli;                                                                      \
	cmpl   $SEGMENT_USER_CODE, OFFSET_IRREGS_CS(%esp);                        \
	jne    99f;                                                               \
	movl   OFFSET_IRREGS_ESP(%esp), %ecx;                                     \
	movl   OFFSET_IRREGS_EIP(%esp), %edx;                                     \
	addl   $8, %esp;                                                          \
	.cfi_adjust_cfa_offset - 8;                                               \
	/* Prevent popfl from enabling interrupts to bypass a race condition      \
	 * that could result in an interrupt attempting to re-direct user-space   \
	 * at a time where registers it would modify were already loaded.         \
	 * This race condition doesn't happen with IRET, because it executes      \
	 * atomically (or rather: without interrupts). */                         \
	andl   $~EFLAGS_IF, (%esp);                                               \
	popfl;                                                                    \
	/* Enable interrupts in a way that delays its execution for 1             \
	 * additional instruction, meaning that no interrupts can occur           \
	 * before `sysexit' actually returns to user-space.                       \
	 * NOTE: `popfl' doesn't have this effect, so this clutch is required. */ \
	sti;                                                                      \
	sysexit;                                                                  \
	.cfi_adjust_cfa_offset 8;                                                 \
99:	iret
#endif /* ... */
#endif /* !__x86_64__ */
#endif /* __ASSEMBLER__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_SYSCALL_H */
