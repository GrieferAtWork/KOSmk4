/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_SYSCALL_TABLES_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_SYSCALL_TABLES_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>

#include <asm/unistd.h>

#ifndef __NR32FEAT_SYSCALL_TABLE_COUNT
#include <asm/syscalls32_d.h>
#endif /* !__NR32FEAT_SYSCALL_TABLE_COUNT */

#ifdef BUILDING_KERNEL_CORE
/* Mangled   names   for   assembly   wrappers   for   a  given
 * system  call,  when  invoked  via  the  specified mechanism.
 * Any possible  combination  of  these  is  pre-defined  as  a
 * weak-internal wrapper that calls the associated `sys_##name'
 * function  whilst passing the  correct number and combination
 * of arguments, before correctly propagating the system call's
 * return value back into user-space.
 * NOTE: These macros are mainly provided since some system calls
 *       are  better implemented in assembly, such as sched_yield
 *       being implemented such  that the  task's scpustate  will
 *       already point  back into  user-space, as  well as  other
 *       system calls such as `sigreturn', which don't even  have
 *       any real prototype.
 * NOTE: In x86_64, the 386 symbols refer to the symbols that are
 *       called   by  a  process  in  32-bit  compatibility-mode.
 * For the default implementations, see:
 *  - /src/kernel/core/arch/i386/syscall/wrappers32.S
 *  - /src/kernel/core/arch/i386/syscall/wrappers64.S
 * Register state upon entry:
 *     X86_ASMSYSCALL32_INT80:
 *         i386:    Unchanged (all registers are the same)
 *         x86_64:  Unchanged (all registers are the same) (NOTE: Compatibility-mode)
 *     X86_ASMSYSCALL32_SYSENTER:
 *         i386:    - %esp has been loaded
 *                  - A user-space IRET tail was pushed and created
 *         x86_64:  - %rsp has been loaded
 *                  - A user-space IRET tail was pushed and created
 *                  - Compatibility-mode
 *     X86_ASMSYSCALL32_RUNC32:
 *         x86_64:  SYSVABI-compatible, takes a  register vector  `u64 *regv = %rdi'
 *                  Used to wrap around `sys32_*' system calls, handling double-wide
 *                  registers,  as  well as  smaller-than-32-bit arguments  by zero-
 *                  extending them when necessary.
 *     X86_ASMSYSCALL64:
 *         x86_64:  SYSVABI-compatible
 * HINT: The low-level interrupt/entry handlers
 *       for system calls  are implemented  in:
 *        - /src/kernel/core/arch/i386/syscall/wrappers32.S
 *        - /src/kernel/core/arch/i386/syscall/wrappers64.S
 */
#define X86_ASMSYSCALL32_INT80(name)    __x86_asm32_int80_##name    /* Section: .text.x86.asm32_syscall_int80.<name> */
#define X86_ASMSYSCALL32_SYSENTER(name) __x86_asm32_sysenter_##name /* Section: .text.x86.asm32_syscall_sysenter.<name> */
#ifdef __x86_64__
#define X86_ASMSYSCALL32_RUNC32(name)   __x86_asm32_sysrun32_##name /* Section: .text.x86.asm32_syscall_sysrun32.<name> */
#define X86_ASMSYSCALL64(name)          __x86_asm64_syscall_##name  /* Section: .text.x86.asm64_syscall.<name> */
#endif /* __x86_64__ */
#endif /* BUILDING_KERNEL_CORE */


#ifdef __CC__
DECL_BEGIN


/* Define tables used during system call routing. */
#ifdef __x86_64__
#define DEFINE_KERNEL_SYSCALL_ROUTES(id)                                                                           \
	DATDEF void *const x86_sysroute##id##_c[__NR_syscall##id##_cnt];                /* sys_XXX */                  \
	DATDEF void *const x86_sysroute##id##_asm64_syscall[__NR32_syscall##id##_cnt];  /* __x86_asm64_syscall_XXX */  \
	DATDEF void *const x86_sysroute##id##_runc32[__NR32_syscall##id##_cnt];         /* __x86_asm32_sysrun32_XXX */ \
	DATDEF void *const x86_sysroute##id##_asm32_int80[__NR32_syscall##id##_cnt];    /* __x86_asm32_int80_XXX */    \
	DATDEF void *const x86_sysroute##id##_asm32_sysenter[__NR32_syscall##id##_cnt]; /* __x86_asm32_sysenter_XXX */
#else /* __x86_64__ */
#define DEFINE_KERNEL_SYSCALL_ROUTES(id)                                                                        \
	DATDEF void *const x86_sysroute##id##_c[__NR_syscall##id##_cnt];                /* sys_XXX */               \
	DATDEF void *const x86_sysroute##id##_asm32_int80[__NR32_syscall##id##_cnt];    /* __x86_asm32_int80_XXX */ \
	DATDEF void *const x86_sysroute##id##_asm32_sysenter[__NR32_syscall##id##_cnt]; /* __x86_asm32_sysenter_XXX */
#endif /* !__x86_64__ */
__NRFEAT_SYSCALL_TABLE_FOREACH(DEFINE_KERNEL_SYSCALL_ROUTES)
#undef DEFINE_KERNEL_SYSCALL_ROUTES


/* Define some system call routing aliases. */
#ifdef __x86_64__
#define x86_sysroute0_c64 x86_sysroute0_c
#define x86_sysroute1_c64 x86_sysroute1_c
#else /* __x86_64__ */
#define x86_sysroute0_c32 x86_sysroute0_c
#define x86_sysroute1_c32 x86_sysroute1_c
#endif /* !__x86_64__ */


/* Entry point for  `sysenter' (32-bit  system call  invocation)
 * NOTE: When this function is called, no IRET tail exists, yet.
 * Method:
 *    RPC_SYSCALL_INFO_METHOD_SYSENTER_32
 * In:
 *    %eax:       System call number (`__NR32_*')
 *    %ebx:       Arg #0  (If `kernel_syscall32_regcnt(%eax) >= 1')
 *    %ecx:       Arg #1  (If `kernel_syscall32_regcnt(%eax) >= 2')
 *    %edx:       Arg #2  (If `kernel_syscall32_regcnt(%eax) >= 3')
 *    %esi:       Arg #3  (If `kernel_syscall32_regcnt(%eax) >= 4')
 *    0(%ebp):    Arg #4  (If `kernel_syscall32_regcnt(%eax) >= 5')
 *    4(%ebp):    Arg #5  (If `kernel_syscall32_regcnt(%eax) >= 6')
 *    %edi:       Return-%eip
 *    %ebp:       Return-%esp
 *    %eflags.DF: Set to enable exception propagation. (s.a. `sys_set_exception_handler()')
 * Out:
 *    %eax:       low  32-bit of return value
 *    %edx:       high 32-bit of return value (If `kernel_syscall32_doublewide(IN(%eax))')
 *    %eip:       Always set to `IN(%edi)'
 *    %esp:       Always set to `IN(%ebp)'
 *    %ecx:       May be clobbered
 *    %edx:       May be clobbered
 *    *:          All other registers are preserved by default, though individual
 *                system calls may cause specific registers to become  clobbered. */
FUNDEF void ASMCALL x86_syscall32_sysenter(void);
FUNDEF void ASMCALL x86_syscall32_sysenter_traced(void);

/* Entry point for `int $0x80' (32-bit system call invocation)
 * Method:
 *    RPC_SYSCALL_INFO_METHOD_INT80H_32
 * In:
 *    %eax:       System call number (`__NR32_*')
 *    %ebx:       Arg #0  (If `kernel_syscall32_regcnt(%eax) >= 1')
 *    %ecx:       Arg #1  (If `kernel_syscall32_regcnt(%eax) >= 2')
 *    %edx:       Arg #2  (If `kernel_syscall32_regcnt(%eax) >= 3')
 *    %esi:       Arg #3  (If `kernel_syscall32_regcnt(%eax) >= 4')
 *    %edi:       Arg #4  (If `kernel_syscall32_regcnt(%eax) >= 5')
 *    %ebp:       Arg #5  (If `kernel_syscall32_regcnt(%eax) >= 6')
 *    %eflags.DF: Set to enable exception propagation. (s.a. `sys_set_exception_handler()')
 * Out:
 *    %eax:       low  32-bit of return value
 *    %edx:       high 32-bit of return value (If `kernel_syscall32_doublewide(IN(%eax))')
 *    *:          All other registers are preserved by default, though individual
 *                system calls may cause specific registers to become  clobbered. */
FUNDEF void ASMCALL x86_syscall32_int80(void) ASMNAME("x86_idt_syscall");
FUNDEF void ASMCALL x86_syscall32_int80_traced(void) ASMNAME("x86_idt_syscall_traced");
#ifdef __x86_64__
/* int80 entry points for 64-bit mode.
 * Note that these are actually identical to the 32-bit mode entry points, as the actual
 * behavior  to-be used is decided at run-time,  based on whether the calling user-space
 * code was running in compatibility mode.
 * NOTE: The register conventions for a 64-bit int80h system call are identical to the
 *       64-bit    `syscall'    system    call    (s.a.     `x86_syscall64_syscall()') */
FUNDEF void ASMCALL x86_syscall64_int80(void) ASMNAME("x86_idt_syscall");
FUNDEF void ASMCALL x86_syscall64_int80_traced(void) ASMNAME("x86_idt_syscall_traced");
/* Same as above, but these symbols point after the swapgs+sti introductory part.
 * As such, these are used by system call emulation. */
FUNDEF void ASMCALL x86_syscall64_int80_after_swapgs(void);
FUNDEF void ASMCALL x86_syscall64_int80_after_swapgs_traced(void);
/* System call entry point labels with x32 vs. x64 mode already decided */
FUNDEF void ASMCALL x86_syscall64x64_int80(void);
FUNDEF void ASMCALL x86_syscall64x32_int80(void);
FUNDEF void ASMCALL x86_syscall64x64_int80_traced(void);
FUNDEF void ASMCALL x86_syscall64x32_int80_traced(void);
#endif /* __x86_64__ */



#ifdef __x86_64__
/* Entry  point  for `syscall'  (64-bit system  call invocation)
 * NOTE: When this function is called, no IRET tail exists, yet.
 * Method:
 *    RPC_SYSCALL_INFO_METHOD_INT80H_64
 * In:
 *    %rax:    System call number (`__NR64_*')
 *    %rdi:    Arg #0  (If `kernel_syscall64_regcnt(%rax) >= 1')
 *    %rsi:    Arg #1  (If `kernel_syscall64_regcnt(%rax) >= 2')
 *    %rdx:    Arg #2  (If `kernel_syscall64_regcnt(%rax) >= 3')
 *    %r10:    Arg #3  (If `kernel_syscall64_regcnt(%rax) >= 4')
 *    %r8:     Arg #4  (If `kernel_syscall64_regcnt(%rax) >= 5')
 *    %r9:     Arg #5  (If `kernel_syscall64_regcnt(%rax) >= 6')
 *    %rcx:    Return-%rip
 *    %r11:    Return-%rflags
 *    %r11.DF: Set to enable exception propagation. (s.a. `sys_set_exception_handler()')
 * Out:
 *    %rax:    low  64-bit of return value
 *    %rdx:    high 64-bit of return value (If `kernel_syscall64_doublewide(IN(%rax))')
 *    %eip:    Always set to `IN(%edi)'
 *             When cleared on entry, set on return if an exception was propagated
 *    *:       All other registers are preserved by default, though individual
 *             system calls may cause specific registers to become  clobbered. */
FUNDEF void ASMCALL x86_syscall64_syscall(void);
FUNDEF void ASMCALL x86_syscall64_syscall_traced(void);
#endif /* __x86_64__ */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_SYSCALL_TABLES_H */
