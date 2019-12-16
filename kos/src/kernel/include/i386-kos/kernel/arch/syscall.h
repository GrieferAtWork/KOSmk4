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
#include <bits/types.h>

#ifdef __ASSEMBLER__
#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>
#endif /* __ASSEMBLER__ */

#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __x86_64__
#if !defined(__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT) || \
    !defined(__NR32FEAT_DEFINED_SYSCALL_RETURN_TYPES) || \
    !defined(__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES)
#undef __WANT_SYSCALL_ARGUMENT_COUNT
#undef __WANT_SYSCALL_RETURN_TYPES
#undef __WANT_SYSCALL_ARGUMENT_TYPES
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_RETURN_TYPES   1
#define __WANT_SYSCALL_ARGUMENT_TYPES 1
#include <asm/syscalls-proto32_d.h>
#endif /* !... */

#define ATTR_SECTION_SYSCALL32(name) ATTR_SECTION(".text.x86.syscall32." #name)
#endif /* __x86_64__ */

#define ATTR_SECTION_SYSCALL(name)   ATTR_SECTION(".text.x86.syscall." #name)
#endif /* CONFIG_BUILDING_KERNEL_CORE */


#ifdef __CC__
DECL_BEGIN

struct icpustate;
struct rpc_syscall_info;

/* Emulate a system call invocation, given a user-space register state. */
#ifdef __x86_64__
#define x86_syscall_emulate64_int80h    x86_syscall_emulate_int80h
#define x86_syscall_emulate64_sysvabi   x86_syscall_emulate_sysvabi
#define x86_syscall_emulate64_int80h_r  x86_syscall_emulate_int80h_r
#define x86_syscall_emulate64_sysvabi_r x86_syscall_emulate_sysvabi_r
FUNDEF struct icpustate *FCALL x86_syscall_emulate64_int80h(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate64_sysvabi(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);
FUNDEF ATTR_NORETURN void FCALL x86_syscall_emulate64_int80h_r(struct icpustate *__restrict state);
FUNDEF ATTR_NORETURN void FCALL x86_syscall_emulate64_sysvabi_r(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);
#else /* __x86_64__ */
#define x86_syscall_emulate32_int80h     x86_syscall_emulate_int80h
#define x86_syscall_emulate32_sysenter   x86_syscall_emulate_sysenter
#define x86_syscall_emulate32_cdecl      x86_syscall_emulate_cdecl
#define x86_syscall_emulate32_int80h_r   x86_syscall_emulate_int80h_r
#define x86_syscall_emulate32_sysenter_r x86_syscall_emulate_sysenter_r
#define x86_syscall_emulate32_cdecl_r    x86_syscall_emulate_cdecl_r
#endif /* !__x86_64__ */
FUNDEF struct icpustate *FCALL x86_syscall_emulate32_int80h(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate32_sysenter(struct icpustate *__restrict state);
FUNDEF struct icpustate *FCALL x86_syscall_emulate32_cdecl(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);
FUNDEF ATTR_NORETURN void FCALL x86_syscall_emulate32_int80h_r(struct icpustate *__restrict state);
FUNDEF ATTR_NORETURN void FCALL x86_syscall_emulate32_sysenter_r(struct icpustate *__restrict state);
FUNDEF ATTR_NORETURN void FCALL x86_syscall_emulate32_cdecl_r(struct icpustate *__restrict state, __syscall_ulong_t sysno, bool enable_except);

/* Emulate a system call using a standard function call */
#ifdef __x86_64__
#define syscall_emulate_callback   x86_syscall_emulate64_sysvabi
#define syscall_emulate_callback_r x86_syscall_emulate64_sysvabi_r
#else /* __x86_64__ */
#define syscall_emulate_callback   x86_syscall_emulate32_cdecl
#define syscall_emulate_callback_r x86_syscall_emulate32_cdecl_r
#endif /* !__x86_64__ */

/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however
 *       will reset the kernel-space stack to `state', and immediately return
 *       to userspace after the system call has returned (or unwind any exception
 *       that was thrown by the system call, also dealing with the possibility
 *       of RPC function handling, as well as system call restarting) */
FUNDEF WUNUSED struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict state,
                struct rpc_syscall_info *__restrict sc_info);
FUNDEF ATTR_NORETURN void FCALL
syscall_emulate_r(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info);

#ifdef __x86_64__
FUNDEF WUNUSED struct icpustate *FCALL
syscall_emulate32(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info);
FUNDEF WUNUSED struct icpustate *FCALL
syscall_emulate64(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info);
#else /* __x86_64__ */
#define syscall_emulate32 syscall_emulate
#endif /* !__x86_64__ */

DECL_END


/* Define compatibility-mode system calls. */
#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifdef __x86_64__
/* When defining a 64-bit system call, weakly alias the 32-bit variant onto it, thus
 * implementing system calls without dedicated compatibility-mode variants by calling
 * forward to their 64-bit (regular) variants. */
#ifndef __PRIVATE_SYSCALL_GET_ESCAPED_TYPE
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2(a, b) b
#define __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(t) __PRIVATE_SYSCALL_GET_ESCAPED_TYPE2 t
#endif /* !__PRIVATE_SYSCALL_GET_ESCAPED_TYPE */

#define DEFINE_SYSCALL32_0(return_type, name)                                                                      \
	STATIC_ASSERT(__NR32AC_##name == 0);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(void) ASMNAME("sys32_" #name);                           \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(void)
#define DEFINE_SYSCALL32_1(return_type, name, T0, N0)                                                              \
	STATIC_ASSERT(__NR32AC_##name == 1);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0) ASMNAME("sys32_" #name);                          \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0)
#define DEFINE_SYSCALL32_2(return_type, name, T0, N0, T1, N1)                                                      \
	STATIC_ASSERT(__NR32AC_##name == 2);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1) ASMNAME("sys32_" #name);                   \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1)
#define DEFINE_SYSCALL32_3(return_type, name, T0, N0, T1, N1, T2, N2)                                              \
	STATIC_ASSERT(__NR32AC_##name == 3);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2) ASMNAME("sys32_" #name);            \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2)
#define DEFINE_SYSCALL32_4(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3)                                      \
	STATIC_ASSERT(__NR32AC_##name == 4);                                                                           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type)); \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));         \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), T3));         \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3) ASMNAME("sys32_" #name);     \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3)
#define DEFINE_SYSCALL32_5(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4)                                 \
	STATIC_ASSERT(__NR32AC_##name == 5);                                                                              \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type));    \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), T3));            \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT4_##name), T4));            \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4)
#define DEFINE_SYSCALL32_6(return_type, name, T0, N0, T1, N1, T2, N2, T3, N3, T4, N4, T5, N5)                                \
	STATIC_ASSERT(__NR32AC_##name == 6);                                                                                     \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32RT_##name), return_type));           \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT0_##name), T0));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT1_##name), T1));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT2_##name), T2));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT3_##name), T3));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT4_##name), T4));                   \
	STATIC_ASSERT(__builtin_types_compatible_p(__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NR32AT5_##name), T5));                   \
	FUNDEF return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5) ASMNAME("sys32_" #name); \
	PUBLIC ATTR_SECTION_SYSCALL32(name) return_type __ARCH_SYSCALLCC impl_sys32_##name(T0 N0, T1 N1, T2 N2, T3 N3, T4 N4, T5 N5)
#define DEFINE_SYSCALL64_0 DEFINE_SYSCALL0
#define DEFINE_SYSCALL64_1 DEFINE_SYSCALL1
#define DEFINE_SYSCALL64_2 DEFINE_SYSCALL2
#define DEFINE_SYSCALL64_3 DEFINE_SYSCALL3
#define DEFINE_SYSCALL64_4 DEFINE_SYSCALL4
#define DEFINE_SYSCALL64_5 DEFINE_SYSCALL5
#define DEFINE_SYSCALL64_6 DEFINE_SYSCALL6
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
	cmpl   $(SEGMENT_USER_CODE), OFFSET_IRREGS_CS(%esp);                      \
	jne    99f;                                                               \
	testl  $(EFLAGS_VM), OFFSET_IRREGS_EFLAGS(%esp);                          \
	jnz    99f;                                                               \
	movl   OFFSET_IRREGS_ESP(%esp), %ecx;                                     \
	movl   OFFSET_IRREGS_EIP(%esp), %edx;                                     \
	addl   $(8), %esp;                                                        \
	.cfi_adjust_cfa_offset - 8;                                               \
	/* Prevent popfl from enabling interrupts to bypass a race condition      \
	 * that could result in an interrupt attempting to re-direct user-space   \
	 * at a time where registers it would modify were already loaded.         \
	 * This race condition doesn't happen with IRET, because it executes      \
	 * atomically (or rather: without interrupts). */                         \
	andl   $(~EFLAGS_IF), (%esp);                                             \
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
	addl   $(8), %esp;                                                        \
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
