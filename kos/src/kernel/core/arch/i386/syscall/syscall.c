/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/arch/isr.h>
#include <kernel/coredump.h>
#include <kernel/cpuid.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/idt.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall-tables.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/mutex.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/tss.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <kos/bits/exception_data-convert.h>
#include <kos/bits/exception_data32.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <kos/kernel/gdt.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#include <librpc/rpc.h>
#include <libunwind/unwind.h>

DECL_BEGIN


#ifndef CONFIG_NO_SYSCALL_TRACING
PRIVATE ATTR_COLDBSS struct mutex syscall_tracing_lock = MUTEX_INIT;
INTERN ATTR_COLDBSS bool syscall_tracing_enabled = false;

#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL syscall_tracing_ipi)(struct icpustate *__restrict state,
                                   void *args[CPU_IPI_ARGCOUNT]) {
	if (CURRENT_X86_CPUID.ci_1d & CPUID_1D_SEP) {
		/* Also re-direct the `sysenter' instruction */
		__wrmsr(IA32_SYSENTER_EIP,
		        (u64)(uintptr_t)(args[0] ? (void *)&x86_syscall32_sysenter_traced
		                                 : (void *)&x86_syscall32_sysenter));
	}
#ifdef __x86_64__
	if (CURRENT_X86_CPUID.ci_80000001d & CPUID_80000001D_SYSCALL) {
		__wrmsr(IA32_LSTAR,
		        args[0] ? (u64)&x86_syscall64_syscall_traced
		                : (u64)&x86_syscall64_syscall);
	}
#endif /* __x86_64__ */
	__lidt_p(&x86_idt_ptr);
	return state;
}
#endif /* !CONFIG_NO_SMP */

#ifdef __x86_64__
INTDEF s32 x86_syscall_emulate_int80h_r_rel_x86_syscall64x64_int80;
INTDEF s32 x86_syscall_emulate_int80h_r_rel_x86_syscall64x32_int80;
INTDEF s32 x86_syscall_emulate64_int80h_r_rel_x86_syscall64x64_int80;
INTDEF s32 x86_syscall_emulate32_int80h_r_rel_x86_syscall64x32_int80;
#else /* __x86_64__ */
INTDEF s32 x86_syscall_emulate_int80h_r_rel_x86_idt_syscall;
#endif /* !__x86_64__ */
INTDEF s8 x86_syscall_emulate_r_redirection[2];
INTDEF byte_t x86_syscall_emulate_traced_r[];
INTDEF byte_t x86_syscall_emulate_r_redirection_jmp[];

#define V2P(addr) (vm_phys_t)((uintptr_t)(addr) - KERNEL_CORE_BASE)

PRIVATE NOBLOCK void
NOTHROW(FCALL setpcrel32)(s32 *pcrel, void *dest) {
	s32 offset;
	offset = (s32)(intptr_t)((uintptr_t)dest - ((uintptr_t)pcrel + 4));
	vm_writephysl_unaligned(V2P(pcrel), (u32)offset);
}


/* Enable/disable system call tracing.
 * @return: true:  Successfully changed the current tracing state.
 * @return: false: Tracing was already enabled/disabled. */
PUBLIC bool KCALL syscall_tracing_setenabled(bool enable) {
	bool result;
	struct idt_segment newsyscall;
	void *addr;
	SCOPED_WRITELOCK(&syscall_tracing_lock);

	addr = enable ? (void *)&x86_syscall32_int80_traced
	              : (void *)&x86_syscall32_int80;
#ifdef __x86_64__
	newsyscall.i_seg.s_u = SEGMENT_INTRGATE_INIT_U((uintptr_t)addr, SEGMENT_KERNEL_CODE, 0, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
	newsyscall.i_ext.s_u = SEGMENT_INTRGATE_HI_INIT_U((uintptr_t)addr, SEGMENT_KERNEL_CODE, 0, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
#else /* __x86_64__ */
	newsyscall.i_seg.s_ul = SEGMENT_INTRGATE_INIT_UL((uintptr_t)addr, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
	newsyscall.i_seg.s_uh = SEGMENT_INTRGATE_INIT_UH((uintptr_t)addr, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
#endif /* !__x86_64__ */
	/* WARNING: This call right here can throw an exception!
	 *          As such, it has to be kept near the top of this function. */
	x86_idt_modify_begin();
	x86_idt[0x80] = newsyscall;
	x86_idt_modify_end();

	/* Re-write assembly to jump to tracing handlers. */
#ifdef __x86_64__
	addr = enable ? (void *)&x86_syscall64x64_int80_traced
	              : (void *)&x86_syscall64x64_int80;
	setpcrel32(&x86_syscall_emulate_int80h_r_rel_x86_syscall64x64_int80, addr);
	setpcrel32(&x86_syscall_emulate64_int80h_r_rel_x86_syscall64x64_int80, addr);
	addr = enable ? (void *)&x86_syscall64x32_int80_traced
	              : (void *)&x86_syscall64x32_int80;
	setpcrel32(&x86_syscall_emulate_int80h_r_rel_x86_syscall64x32_int80, addr);
	setpcrel32(&x86_syscall_emulate32_int80h_r_rel_x86_syscall64x32_int80, addr);
#else /* __x86_64__ */
	setpcrel32(&x86_syscall_emulate_int80h_r_rel_x86_idt_syscall, addr);
#endif /* !__x86_64__ */

	/* Modify `syscall_emulate_r()' */
#ifdef __x86_64__
#define SYSCALL_EMULATE_DONT_TRACE_WORD 0x48f3 /* rep; REX.W */
#else /* __x86_64__ */
#define SYSCALL_EMULATE_DONT_TRACE_WORD 0xa5f3 /* rep; movsl */
#endif /* !__x86_64__ */
	vm_writephysw_unaligned(V2P(&x86_syscall_emulate_r_redirection[0]),
	                        enable ? (u16)(uintptr_t)x86_syscall_emulate_r_redirection_jmp
	                               : SYSCALL_EMULATE_DONT_TRACE_WORD);
#undef SYSCALL_EMULATE_DONT_TRACE_WORD
	/* TODO: INVALIDATE_INSTRUCTION_CACHE(); */

	result = syscall_tracing_enabled;
	syscall_tracing_enabled = enable;


#ifndef CONFIG_NO_SMP
	{
		void *argv[CPU_IPI_ARGCOUNT];
		argv[0] = (void *)(enable ? (uintptr_t)1 : (uintptr_t)0);
		cpu_broadcastipi_notthis(&syscall_tracing_ipi,
		                         argv,
#if 1
		                         CPU_IPI_FNORMAL
		                         /* NOTE: Don't wake up deep-sleep CPUs!
		                          *       When a CPU wakes up, it already has to go through all
		                          *       of the initialization that also contains the part where
		                          *       it needs to load its IDT according to tracing of syscalls
		                          *       currently being enabled. */
#else
		                         CPU_IPI_FWAKEUP
#endif
		                         );
	}
#endif /* !CONFIG_NO_SMP */

	if (CURRENT_X86_CPUID.ci_1d & CPUID_1D_SEP) {
		__wrmsr(IA32_SYSENTER_EIP,
		        enable ? (uintptr_t)&x86_syscall32_sysenter_traced
		               : (uintptr_t)&x86_syscall32_sysenter);
	}
#ifdef __x86_64__
	if (CURRENT_X86_CPUID.ci_80000001d & CPUID_80000001D_SYSCALL) {
		__wrmsr(IA32_LSTAR,
		        enable ? (u64)&x86_syscall64_syscall_traced
		               : (u64)&x86_syscall64_syscall);
	}
#endif /* __x86_64__ */
	__lidt_p(&x86_idt_ptr);
	return result;
}
/* Check if system call tracing is enabled. */
PUBLIC WUNUSED bool
NOTHROW(KCALL syscall_tracing_getenabled)(void) {
	return ATOMIC_READ(syscall_tracing_enabled);
}
#endif /* !CONFIG_NO_SYSCALL_TRACING */







INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_sysenter)(void) {
	if (CURRENT_X86_CPUID.ci_1d & CPUID_1D_SEP) {
		/* Configure support for the `sysenter' instruction. */
		__wrmsr(IA32_SYSENTER_CS, SEGMENT_KERNEL_CODE);
#ifdef __x86_64__
		__wrmsr(IA32_SYSENTER_ESP, (u64)(uintptr_t)(void *)&FORCPU(&_bootcpu, thiscpu_x86_tss).t_rsp0);
#else /* __x86_64__ */
		__wrmsr(IA32_SYSENTER_ESP, (u64)(uintptr_t)(void *)&FORCPU(&_bootcpu, thiscpu_x86_tss).t_esp0);
#endif /* !__x86_64__ */
		__wrmsr(IA32_SYSENTER_EIP, (u64)(uintptr_t)(void *)&x86_syscall32_sysenter);
	}
#ifdef __x86_64__
	if (CURRENT_X86_CPUID.ci_80000001d & CPUID_80000001D_SYSCALL) {
		__wrmsr(IA32_STAR, (u64)SEGMENT_KERNEL_CODE << 32);
		__wrmsr(IA32_LSTAR, (u64)&x86_syscall64_syscall);
		__wrmsr(IA32_FMASK, EFLAGS_IF);
	}
#endif /* __x86_64__ */
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C */
