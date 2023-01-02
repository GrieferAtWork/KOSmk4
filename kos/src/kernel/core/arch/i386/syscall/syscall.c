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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/hook.h>
#include <debugger/io.h>
#include <kernel/arch/isr.h>
#include <kernel/coredump.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/mman/phys.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall-trace.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/x86/cpuid.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/x86/tss.h>

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
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/tss-compat.h>
#include <kos/kernel/x86/tss.h>
#include <kos/sched/shared-lock.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#include <libunwind/unwind.h>

#ifndef __x86_64__
#include <kernel/rt/except-handler.h>
#endif /* !__x86_64__ */

DECL_BEGIN

/* Error  throwing function for when `sysenter' is  used with a illegal extension address
 * Can't happen on x86_64, since it defines any 32-bit user-space address as valid, which
 * is what sysenter extensions vectors are limited to in compatibility mode. */
#ifndef __x86_64__
INTERN ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL __asm32_bad_sysenter_extension_impl)(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc_info;
	struct exception_info *info = except_info();

	/* Fill in system call information (as far as we can) */
	sc_info.rsi_flags   = (RPC_SYSCALL_INFO_FREGVALID(0) | RPC_SYSCALL_INFO_FREGVALID(1) |
	                       RPC_SYSCALL_INFO_FREGVALID(2) | RPC_SYSCALL_INFO_FREGVALID(3) |
	                       RPC_SYSCALL_INFO_METHOD_SYSENTER_32);
	sc_info.rsi_sysno   = state->ics_gpregs.gp_eax;
	sc_info.rsi_regs[0] = state->ics_gpregs.gp_ebx;
	sc_info.rsi_regs[1] = state->ics_gpregs.gp_ecx;
	sc_info.rsi_regs[2] = state->ics_gpregs.gp_edx;
	sc_info.rsi_regs[3] = state->ics_gpregs.gp_esi;

	/* Fill in exception information. */
	bzero(info, sizeof(*info));
	info->ei_code = EXCEPT_CODEOF(E_SEGFAULT_UNMAPPED);
	info->ei_data.e_args.e_segfault.s_addr    = state->ics_gpregs.gp_ebp;
	info->ei_data.e_args.e_segfault.s_context = E_SEGFAULT_CONTEXT_FAULT;
	icpustate_to_kcpustate(state, &info->ei_state);
	info->ei_data.e_faultaddr = (void *)info->ei_state.kcs_eip;
	if (info->ei_state.kcs_eflags & EFLAGS_DF)
		sc_info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;

	/* Handle the exception. */
	state = userexcept_handler(state, &sc_info);

	/* Restart? - ok... */
	return state;
}
#endif /* !__x86_64__ */


#ifndef CONFIG_NO_KERNEL_SYSCALL_TRACING
INTERN ATTR_COLDBSS bool syscall_tracing_enabled = false;
PRIVATE ATTR_COLDBSS struct shared_lock syscall_tracing_lock = SHARED_LOCK_INIT;

#ifndef CONFIG_NO_SMP
PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL syscall_tracing_ipi)(struct icpustate *__restrict state,
                                   void *args[CPU_IPI_ARGCOUNT]) {
	if (X86_THISCPU_HAVE_SYSENTER) {
		/* Also re-direct the `sysenter' instruction */
		__wrmsr(IA32_SYSENTER_EIP,
		        (u64)(uintptr_t)(args[0] ? (void *)&x86_syscall32_sysenter_traced
		                                 : (void *)&x86_syscall32_sysenter));
	}
#ifdef __x86_64__
	if (X86_THISCPU_HAVE_SYSCALL) {
		__wrmsr(IA32_LSTAR,
		        args[0] ? (u64)&x86_syscall64_syscall_traced
		                : (u64)&x86_syscall64_syscall);
	}
#endif /* __x86_64__ */
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
INTDEF byte_t x86_syscall_emulate_r_redirection_inl[];

#define V2P(addr) (physaddr_t)((uintptr_t)(addr) - KERNEL_CORE_BASE)

PRIVATE NOBLOCK void
NOTHROW(FCALL setpcrel32)(s32 *pcrel, void const *dest) {
	s32 offset;
	offset = (s32)(intptr_t)((uintptr_t)dest - ((uintptr_t)pcrel + 4));
	pokephysl_unaligned(V2P(pcrel), (u32)offset);
}


/* Low-level, arch-specific enable/disable system call tracing.
 * NOTE: Don't   call   `arch_syscall_tracing_setenabled()'    directly.
 *       Low-level system call tracing is enabled/disabled automatically
 *       when tracing callbacks are  installed/deleted as the result  of
 *       calls to  `syscall_trace_start()'  and  `syscall_trace_stop()'.
 *       Manually enabling/disable tracing will work, however attempting
 *       to  start/stop  tracing  via  installation  of  dynamic tracing
 *       callbacks may break, since those  functions may only call  this
 *       one when the first callback is registered, or the last callback
 *       is deleted.
 * NOTE: A user can manually invoke this function from the builtin debugger
 *       through use of the `sctrace 0|1' command.
 * @param: nx:     When true, don't throw an exception or block.
 * @return: true:  Successfully changed the current tracing state.
 * @return: false: Tracing was already enabled/disabled, or could
 *                 not  be  enabled/disabled  when  `nx == true'. */
PUBLIC bool KCALL arch_syscall_tracing_setenabled(bool enable, bool nx) {
	bool result;
	struct idt_segment newsyscall;
	void const *addr;
	if (!shared_lock_tryacquire(&syscall_tracing_lock)) {
		if (nx)
			return false;
		shared_lock_acquire(&syscall_tracing_lock);
	}
	RAII_FINALLY { shared_lock_release(&syscall_tracing_lock); };

	addr = enable ? (void const *)&x86_syscall32_int80_traced
	              : (void const *)&x86_syscall32_int80;
#ifdef __x86_64__
	/* NOTE: On x86_64, we  must use `SEGMENT_DESCRIPTOR_TYPE_INTRGATE'  as gate  type
	 *       for int80h because we always _need_ to enter the kernel with #IF disabled
	 *       in order to account for `swapgs' if `(IRET.CS AND 3) != 0' */
	newsyscall.i_seg.s_u = SEGMENT_INTRGATE_INIT_U((uintptr_t)addr, SEGMENT_KERNEL_CODE, 0, SEGMENT_DESCRIPTOR_TYPE_INTRGATE, 3, 1);
	newsyscall.i_ext.s_u = SEGMENT_INTRGATE_HI_INIT_U((uintptr_t)addr, SEGMENT_KERNEL_CODE, 0, SEGMENT_DESCRIPTOR_TYPE_INTRGATE, 3, 1);
#else /* __x86_64__ */
	newsyscall.i_seg.s_ul = SEGMENT_INTRGATE_INIT_UL((uintptr_t)addr, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
	newsyscall.i_seg.s_uh = SEGMENT_INTRGATE_INIT_UH((uintptr_t)addr, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
#endif /* !__x86_64__ */
	/* WARNING: This call right here can throw an exception!
	 *          As such, it has to be kept near the top of this function. */
	if (!x86_idt_modify_begin(nx))
		return false;
	x86_idt[0x80] = newsyscall;
	x86_idt_modify_end();

	/* Re-write assembly to jump to tracing handlers. */
#ifdef __x86_64__
	addr = enable ? (void const *)&x86_syscall64x64_int80_traced
	              : (void const *)&x86_syscall64x64_int80;
	setpcrel32(&x86_syscall_emulate_int80h_r_rel_x86_syscall64x64_int80, addr);
	setpcrel32(&x86_syscall_emulate64_int80h_r_rel_x86_syscall64x64_int80, addr);
	addr = enable ? (void const *)&x86_syscall64x32_int80_traced
	              : (void const *)&x86_syscall64x32_int80;
	setpcrel32(&x86_syscall_emulate_int80h_r_rel_x86_syscall64x32_int80, addr);
	setpcrel32(&x86_syscall_emulate32_int80h_r_rel_x86_syscall64x32_int80, addr);
#else /* __x86_64__ */
	setpcrel32(&x86_syscall_emulate_int80h_r_rel_x86_idt_syscall, addr);
#endif /* !__x86_64__ */

	/* Modify `syscall_emulate_r()' */
	pokephysw_unaligned(V2P(&x86_syscall_emulate_r_redirection[0]),
	                    enable ? (u16)(uintptr_t)x86_syscall_emulate_r_redirection_jmp
	                           : (u16)(uintptr_t)x86_syscall_emulate_r_redirection_inl);
	__flush_instruction_cache();
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
		                          *       When  a CPU  wakes up, it  already has to  go through all
		                          *       of the initialization that  also contains the part  where
		                          *       it needs to load its IDT according to tracing of syscalls
		                          *       currently being enabled. */
#else
		                         CPU_IPI_FWAKEUP
#endif
		                         );
	}
#endif /* !CONFIG_NO_SMP */

	if (X86_THISCPU_HAVE_SYSENTER) {
		__wrmsr(IA32_SYSENTER_EIP,
		        enable ? (uintptr_t)&x86_syscall32_sysenter_traced
		               : (uintptr_t)&x86_syscall32_sysenter);
	}
#ifdef __x86_64__
	if (X86_THISCPU_HAVE_SYSCALL) {
		__wrmsr(IA32_LSTAR,
		        enable ? (u64)&x86_syscall64_syscall_traced
		               : (u64)&x86_syscall64_syscall);
	}
#endif /* __x86_64__ */

	/* Since we modified various bits of program text,
	 * we  must  also  flush  the  instruction  cache. */
	__flush_instruction_cache();
	return result;
}

/* Check if system call tracing is enabled. */
PUBLIC WUNUSED bool
NOTHROW(KCALL arch_syscall_tracing_getenabled)(void) {
	return ATOMIC_READ(syscall_tracing_enabled);
}
#endif /* !CONFIG_NO_KERNEL_SYSCALL_TRACING */







INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_sysenter)(void) {
	if (X86_HAVE_SYSENTER) {
		/* Configure support for the `sysenter' instruction. */
		__wrmsr(IA32_SYSENTER_CS, SEGMENT_KERNEL_CODE);
		__wrmsr(IA32_SYSENTER_ESP, (u64)(uintptr_t)(void *)&FORCPU(&bootcpu, thiscpu_x86_tss).t_psp0);
		__wrmsr(IA32_SYSENTER_EIP, (u64)(uintptr_t)(void *)&x86_syscall32_sysenter);
	} else {
#ifndef __x86_64__
		/* Entirely disable use of `sysexit' in `__i386_syscall_iret'
		 * NOTE: Write-protections aren't in effect yet,
		 *       so  we can just re-write the code here! */
		extern byte_t __i386_syscall_iret[];
		__i386_syscall_iret[0] = 0xcf; /* iret */
#endif /* __x86_64__ */
	}

#ifdef __x86_64__
	if (X86_HAVE_SYSCALL) {
		/* Must preserve the lower 32 bits of `IA32_STAR'!
		 * Intel defines these bits as RESERVED, so they mustn't be altered. */
		__wrmsr(IA32_STAR, __rdmsr32(IA32_STAR) |
		                   (u64)SEGMENT_KERNEL_CODE << 32 |
		                   (u64)SEGMENT_USER_CODE32_RPL << 48);
		__wrmsr(IA32_LSTAR, (u64)&x86_syscall64_syscall);
		/* TODO: `IA32_CSTAR' must be set to some kernel-space PC location
		 *       that is used  to handle user-space  using `syscall'  from
		 *       32-bit mode!
		 *       On  Intel CPUs, this MSR isn't used, and the CPU natively
		 *       causes a #UD to  be thrown, but AMD  CPUs do make use  of
		 *       this MSR, so we must still program it, else the CPU might
		 *       end up jumping  to some user-space  text location when  a
		 *       32-bit program makes use of `syscall'! */
		__wrmsr(IA32_FMASK, EFLAGS_IF);
	} else {
		/* Re-write `__x86_32_syscall_iret' and `__x86_64_syscall_iret' to
		 * do the equivalent  of `intr_exit', without  all of the  special
		 * handling for `sysret' */
		PRIVATE ATTR_FREERODATA byte_t const intr_exit[] = {
			0xfa,                         /*     cli                   */
			0xf6, 0x44, 0x24, 0x08, 0x03, /*     testb  $0x3,0x8(%rsp) */
			0x74, 0x03,                   /*     jz     1f             */
			0x0f, 0x01, 0xf8,             /*     swapgs                */
			0x48, 0xcf                    /* 1:  iretq                 */
		};
		extern byte_t __x86_32_syscall_iret[];
		extern byte_t __x86_64_syscall_iret[];
		memcpy(__x86_32_syscall_iret, intr_exit, sizeof(intr_exit));
		memcpy(__x86_64_syscall_iret, intr_exit, sizeof(intr_exit));
	}
#endif /* __x86_64__ */
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C */
