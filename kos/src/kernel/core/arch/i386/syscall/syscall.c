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
#include <kernel/syscall.h>
#include <kernel/tss.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/mutex.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>

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

#include "../except.h"

DECL_BEGIN



/* Serve all user-space redirection RPCs
 * @return: * :   The new CPU state to restore
 * @param: prestart_system_call: If `reason == TASK_RPC_REASON_SYSCALL', whilst an `E_INTERRUPT_USER_RPC'
 *                               exception was handled, when `RPC_KIND_USER_SYNC' RPCs exist that cannot
 *                               be handled in the current context, then set to true. */
INTDEF struct icpustate *
NOTHROW(FCALL rpc_serve_user_redirection_all)(struct icpustate *__restrict state,
                                              unsigned int reason,
                                              struct rpc_syscall_info const *sc_info,
                                              bool *prestart_system_call);


INTDEF void FCALL
halt_unhandled_exception(unsigned int error,
                         struct kcpustate *__restrict unwind_state);

#define X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG   ((uintptr_t)UINT32_C(0x40000000))

LOCAL void FCALL
scinfo_get32_int80h(struct rpc_syscall_info *__restrict self,
                    struct ucpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ucs_gpregs);
	self->rsi_args[4] = gpregs_getpdi(&state->ucs_gpregs);
	self->rsi_args[5] = gpregs_getpbp(&state->ucs_gpregs);
}

LOCAL void FCALL
scinfo_get32_sysenter(struct rpc_syscall_info *__restrict self,
                      struct ucpustate const *__restrict state) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSENTER_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3);
	if (ucpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ucs_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ucs_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ucs_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ucs_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ucs_gpregs);
	regcount = SYSCALL32_REGISTER_COUNT(self->rsi_sysno);
	if (regcount >= 5) {
		u32 *ebp = (u32 *)(uintptr_t)(u32)gpregs_getpbp(&state->ucs_gpregs);
		validate_readable(ebp, 4);
		self->rsi_args[4] = __hybrid_atomic_load(ebp[0], __ATOMIC_ACQUIRE);
		self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(4);
		if (regcount >= 6) {
			self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(5);
			self->rsi_args[5] = __hybrid_atomic_load(ebp[1], __ATOMIC_ACQUIRE);
		}
	}
}



/* The personality function used to handle exceptions propagated through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL x86_syscall_personality)(struct unwind_fde_struct *__restrict fde,
                                       struct kcpustate *__restrict state,
                                       byte_t *__restrict lsda) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void *pc = (void *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or alternatively: indicates a user-space redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
	/* System calls encode their vector number as the LSDA pointer, so that
	 * when unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function caused the exception, as well as
	 * implement system call restarting. */
	if (((uintptr_t)lsda & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG) !=
	    ((uintptr_t)-1 & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG))
		gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)lsda & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG);
	if ((uintptr_t)lsda & X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG) {
		scinfo_get32_sysenter(&info, &ustate);
	} else {
		scinfo_get32_int80h(&info, &ustate);
	}
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}


INTDEF byte_t x86_sysenter_main[];

#ifndef CONFIG_NO_SYSCALL_TRACING
PRIVATE ATTR_COLDBSS struct mutex syscall_tracing_lock = MUTEX_INIT;
INTERN ATTR_COLDBSS bool syscall_tracing_enabled = false;

INTDEF byte_t x86_idt_syscall[];
INTDEF byte_t x86_idt_syscall_traced[];
INTDEF byte_t x86_sysenter_main_traced[];


PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL syscall_tracing_ipi)(struct icpustate *__restrict state,
                                   void *args[CPU_IPI_ARGCOUNT]) {
	if (CPUID_FEATURES.ci_1d & CPUID_1D_SEP) {
		/* Also re-direct the `sysenter' instruction */
		__wrmsr(IA32_SYSENTER_EIP,
		        args[0] ? (uintptr_t)x86_sysenter_main_traced
		                : (uintptr_t)x86_sysenter_main);
	}
	__lidt_p(&x86_idt_ptr);
	return state;
}

/* Enable/disable system call tracing.
 * @return: true:  Successfully changed the current tracing state.
 * @return: false: Tracing was already enabled/disabled. */
PUBLIC bool KCALL syscall_tracing_setenabled(bool enable) {
	bool result;
	void *argv[CPU_IPI_ARGCOUNT];
	struct idt_segment newsyscall;
	uintptr_t addr;
	SCOPED_WRITELOCK(&syscall_tracing_lock);
	argv[0] = (void *)(enable ? (uintptr_t)1 : (uintptr_t)0);
	addr = enable ? (uintptr_t)x86_idt_syscall
	              : (uintptr_t)x86_idt_syscall_traced;
#ifdef __x86_64__
	newsyscall.i_seg.s_u = SEGMENT_INTRGATE_INIT_U(addr, SEGMENT_KERNEL_CODE, 0, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
	newsyscall.i_ext.s_u = SEGMENT_INTRGATE_HI_INIT_U(addr, SEGMENT_KERNEL_CODE, 0, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
#else /* __x86_64__ */
	newsyscall.i_seg.s_ul = SEGMENT_INTRGATE_INIT_UL(addr, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
	newsyscall.i_seg.s_uh = SEGMENT_INTRGATE_INIT_UH(addr, SEGMENT_KERNEL_CODE, SEGMENT_DESCRIPTOR_TYPE_TRAPGATE, 3, 1);
#endif /* !__x86_64__ */
	/* TODO: This method of changing the IDT is racy.
	 *       A proper solution would be to:
	 *         - Temporary copy the entire IDT somewhere else
	 *         - Broadcast an IPI to have all other CPUs load the address of the IDT copy
	 *         - Modify the original IDT
	 *         - Broadcast an IPI to have all other CPUs load the original IDT
	 *         - Free the copy */
	x86_idt[0x80] = newsyscall;

	result = syscall_tracing_enabled;
	syscall_tracing_enabled = enable;
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
	if (CPUID_FEATURES.ci_1d & CPUID_1D_SEP) {
		__wrmsr(IA32_SYSENTER_EIP,
		        enable ? (uintptr_t)x86_sysenter_main_traced
		               : (uintptr_t)x86_sysenter_main);
	}
	__lidt_p(&x86_idt_ptr);
	return result;
}
/* Check if system call tracing is enabled. */
PUBLIC WUNUSED bool
NOTHROW(KCALL syscall_tracing_getenabled)(void) {
	return ATOMIC_READ(syscall_tracing_enabled);
}
#endif /* !CONFIG_NO_SYSCALL_TRACING */


#ifdef __x86_64__

/* TODO */

#else /* __x86_64__ */



typedef syscall_ulong_t (__ARCH_SYSCALLCC *syscall_proto_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                                            syscall_ulong_t arg2, syscall_ulong_t arg3,
                                                            syscall_ulong_t arg4, syscall_ulong_t arg5);
typedef u64 (__ARCH_SYSCALLCC *syscall_proto64_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                                  syscall_ulong_t arg2, syscall_ulong_t arg3,
                                                  syscall_ulong_t arg4, syscall_ulong_t arg5);
INTDEF syscall_proto_t const __c32_syscallrouter[];
INTDEF syscall_proto_t const __c32_exsyscallrouter[];



/* GCC doesn't like our casts to `syscall_proto64_t' */
#pragma GCC diagnostic ignored "-Wcast-function-type"


struct x86_lcall7_syscall_data {
	uintptr_t          unwind_sysno;
	uintptr_t          saved_edx;
	uintptr_t          saved_ecx;
	uintptr_t          saved_fs;
	uintptr_t          saved_es;
	uintptr_t          saved_ds;
	struct irregs_user iret;
};

INTDEF byte_t x86_lcall7_syscall_guard[];

INTERN unsigned int
NOTHROW(KCALL x86_syscall_lcall7_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                              struct kcpustate *__restrict state,
                                              byte_t *__restrict UNUSED(lsda)) {
	struct x86_lcall7_syscall_data *data;
	if (kcpustate_getpc(state) != (uintptr_t)x86_lcall7_syscall_guard)
		return DWARF_PERSO_CONTINUE_UNWIND;
	data = (struct x86_lcall7_syscall_data *)kcpustate_getsp(state);
	assertf((uintptr_t)(data + 1) == (uintptr_t)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1),
	        "%p != %p",
	        (uintptr_t)(data + 1),
	        (uintptr_t)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1));

	/* TODO: Custom unwind handler. */

	return DWARF_PERSO_CONTINUE_UNWIND;
}

INTERN syscall_ulong_t FCALL
x86_lcall7_syscall_main(struct x86_lcall7_syscall_data *__restrict data,
                        syscall_ulong_t sysno) {
	unsigned int argc;
	syscall_ulong_t result;
	syscall_ulong_t argv[6];
	USER syscall_ulong_t *usp;
	bool double_wide;
	syscall_proto_t proto;
	memset(argv, 0, sizeof(argv));
	usp = (USER syscall_ulong_t *)data->iret.ir_esp;
	if (sysno <= __NR_syscall_max) {
		proto       = __c32_syscallrouter[sysno];
		argc        = x86_syscall_register_count_get(x86_syscall_register_count, sysno);
		double_wide = x86_syscall_double_wide_get(x86_syscall_register_count, sysno);
	} else if (sysno >= __NR_exsyscall_min && sysno <= __NR_exsyscall_max) {
		proto       = __c32_exsyscallrouter[sysno - __NR_exsyscall_min];
		argc        = x86_syscall_register_count_get(x86_exsyscall_register_count, sysno - __NR_exsyscall_min);
		double_wide = x86_syscall_double_wide_get(x86_exsyscall_register_count, sysno - __NR_exsyscall_min);
	} else {
		goto err_nosys;
	}
	if unlikely(!ADDR_IS_USER(usp)) {
		if (argc != 0)
			THROW(E_SEGFAULT_UNMAPPED, usp, E_SEGFAULT_CONTEXT_USERCODE);
	} else {
		switch (argc) {
		case 6:
			argv[5] = ATOMIC_READ(usp[5]);
			ATTR_FALLTHROUGH
		case 5:
			argv[4] = ATOMIC_READ(usp[4]);
			ATTR_FALLTHROUGH
		case 4:
			argv[3] = ATOMIC_READ(usp[3]);
			ATTR_FALLTHROUGH
		case 3:
			argv[2] = ATOMIC_READ(usp[2]);
			ATTR_FALLTHROUGH
		case 2:
			argv[1] = ATOMIC_READ(usp[1]);
			ATTR_FALLTHROUGH
		case 1:
			argv[0] = ATOMIC_READ(usp[0]);
			ATTR_FALLTHROUGH
		case 0:
			break;
		default: __builtin_unreachable();
		}
	}
	if (double_wide) {
		u64 result64;
		result64 = (*(syscall_proto64_t)proto)(argv[0], argv[1],
		                                       argv[2], argv[3],
		                                       argv[4], argv[5]);
		data->saved_edx = (u32)(result64 >> 32);
		result = (u32)result64;
	} else {
		result = (*proto)(argv[0], argv[1],
		                  argv[2], argv[3],
		                  argv[4], argv[5]);
	}
	return result;
err_nosys:
	if (!(data->iret.ir_eflags & EFLAGS_CF))
		return (syscall_ulong_t)-ENOSYS;
	if likely(ADDR_IS_USER(usp)) {
		TRY {
			argv[5] = ATOMIC_READ(usp[5]);
			argv[4] = ATOMIC_READ(usp[4]);
			argv[3] = ATOMIC_READ(usp[3]);
			argv[2] = ATOMIC_READ(usp[2]);
			argv[1] = ATOMIC_READ(usp[1]);
			argv[0] = ATOMIC_READ(usp[0]);
		} EXCEPT {
		}
	}
	THROW(E_UNKNOWN_SYSTEMCALL,
	      sysno,
	      argv[0], argv[1], argv[2],
	      argv[3], argv[4], argv[5]);
}
#endif /* !__x86_64__ */






INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_sysenter)(void) {
	if (CPUID_FEATURES.ci_1d & CPUID_1D_SEP) {
		/* Configure support for the `sysenter' instruction. */
		__wrmsr(IA32_SYSENTER_CS, SEGMENT_KERNEL_CODE);
#ifdef __x86_64__
		__wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&FORCPU(&_bootcpu, x86_cputss).t_rsp0);
#else /* __x86_64__ */
		__wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&FORCPU(&_bootcpu, x86_cputss).t_esp0);
#endif /* !__x86_64__ */
		__wrmsr(IA32_SYSENTER_EIP, (uintptr_t)x86_sysenter_main);
	}
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_SYSCALL_C */
