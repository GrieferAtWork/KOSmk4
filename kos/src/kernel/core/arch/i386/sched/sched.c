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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/fs.h>
#include <kernel/handle.h>
#include <kernel/mman/mnode.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rt/except-personality.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/gdt.h>
#include <kernel/x86/pic.h>
#include <kernel/x86/pit.h>
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/rpc.h>
#include <sched/task-clone.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <kos/compat/linux-ldt.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <sys/io.h>

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#include <libunwind/unwind.h>

DECL_BEGIN

PRIVATE ATTR_FREETEXT void KCALL
kernel_initialize_threadstack(struct task *__restrict thread,
                              byte_t *__restrict sp_base,
                              size_t sp_size,
                              void *__restrict entry) {
	struct scpustate *init_state;
	FORTASK(thread, _this_x86_kernel_psp0) = (uintptr_t)(sp_base + sp_size);
	/* Initialize the CPU state of the boot CPU's idle thread. */
#ifdef __x86_64__
	init_state = (struct scpustate *)((sp_base + sp_size) - SIZEOF_SCPUSTATE);
	bzero(init_state, SIZEOF_SCPUSTATE);
	init_state->scs_sgbase.sg_gsbase = (u64)thread;
	init_state->scs_sgregs.sg_gs     = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_fs     = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_es     = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_ds     = SEGMENT_USER_DATA_RPL;
	init_state->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
	init_state->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA0;
	init_state->scs_irregs.ir_rsp    = (u64)(sp_base + sp_size);
#else /* __x86_64__ */
	init_state = (struct scpustate *)((sp_base + sp_size) - (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
	bzero(init_state, OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	init_state->scs_sgregs.sg_gs   = SEGMENT_USER_GSBASE_RPL;
	init_state->scs_sgregs.sg_fs   = SEGMENT_KERNEL_FSBASE;
	init_state->scs_sgregs.sg_es   = SEGMENT_USER_DATA_RPL;
	init_state->scs_sgregs.sg_ds   = SEGMENT_USER_DATA_RPL;
	init_state->scs_irregs_k.ir_cs = SEGMENT_KERNEL_CODE;
#endif /* !__x86_64__ */
	init_state->scs_irregs.ir_Pip    = (uintptr_t)(void *)entry;
	init_state->scs_irregs.ir_Pflags = EFLAGS_IF;
	FORTASK(thread, this_sstate) = init_state;
}

INTDEF byte_t __kernel_boottask_stack[KERNEL_STACKSIZE];
INTDEF byte_t __kernel_bootidle_stack[KERNEL_IDLE_STACKSIZE];
INTDEF byte_t __kernel_asyncwork_stack[KERNEL_STACKSIZE];

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler_arch)(void) {
	/* Initialize the CPU state of the boot CPU's idle thread, as well as the ASYNC worker thread. */
	FORTASK(&boottask, _this_x86_kernel_psp0) = (uintptr_t)COMPILER_ENDOF(__kernel_boottask_stack);
	kernel_initialize_threadstack(&bootidle, __kernel_bootidle_stack, KERNEL_IDLE_STACKSIZE, (void *)&cpu_idlemain);
	kernel_initialize_threadstack(&asyncwork, __kernel_asyncwork_stack, KERNEL_STACKSIZE, (void *)&_asyncmain);
}


PUBLIC NOBLOCK ATTR_RETNONNULL ATTR_SENTINEL NONNULL((1, 2)) struct task *
NOTHROW(VCALL task_setup_kernel)(struct task *__restrict thread,
                                 thread_main_t thread_main,
                                 size_t argc, ...) {
#ifdef __x86_64__
	struct scpustate *state;
	va_list args; byte_t *dest;
	va_start(args, argc);
	dest = (byte_t *)FORTASK(thread, this_x86_kernel_psp0);
	*(u64 *)(dest -= 8) = (u64)(void *)((void *)(void(FCALL *)(uint16_t))&task_exit);
	if (argc > 6)
		dest -= (argc - 6) * 8;
	state = (struct scpustate *)(dest - SIZEOF_SCPUSTATE);
	/* Initialize the thread's entry state. */
	bzero(state, sizeof(*state));
	state->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
	state->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA0;
	state->scs_irregs.ir_rsp    = (u64)dest;
	state->scs_irregs.ir_rflags = EFLAGS_IF;
	state->scs_irregs.ir_rip    = (u64)(void *)thread_main;
	state->scs_sgregs.sg_gs     = SEGMENT_USER_DATA_RPL; /* Doesn't really matter, but stick to the likely case of this being USER_GSBASE */
	state->scs_sgregs.sg_fs     = SEGMENT_USER_DATA_RPL;
	state->scs_sgregs.sg_es     = SEGMENT_USER_DATA_RPL;
	state->scs_sgregs.sg_ds     = SEGMENT_USER_DATA_RPL;
	state->scs_sgbase.sg_gsbase = (u64)thread;
	/* Fill in arguments */
	if (argc >= 1)
		state->scs_gpregs.gp_rdi = va_arg(args, u64);
	if (argc >= 2)
		state->scs_gpregs.gp_rsi = va_arg(args, u64);
	if (argc >= 3)
		state->scs_gpregs.gp_rdx = va_arg(args, u64);
	if (argc >= 4)
		state->scs_gpregs.gp_rcx = va_arg(args, u64);
	if (argc >= 5)
		state->scs_gpregs.gp_r8 = va_arg(args, u64);
	if (argc >= 6)
		state->scs_gpregs.gp_r9 = va_arg(args, u64);
	if (argc > 6) {
		size_t i;
		for (i = 0; i < (argc - 6); ++i)
			((u64 *)dest)[i] = va_arg(args, u64);
	}
#else /* __x86_64__ */
	byte_t *dest = (byte_t *)FORTASK(thread, this_x86_kernel_psp0);
	struct scpustate *state;
#define PUSH(x) (dest -= sizeof(u32), *(u32 *)dest = (x))
	dest -= argc * sizeof(void *);
	memcpy(dest, &argc + 1, argc, sizeof(void *));
	PUSH((u32)(void *)(void(FCALL *)(uint16_t))&task_exit); /* Return address */
	dest -= OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL;
	state = (struct scpustate *)dest;
	/* Initialize the thread's entry state. */
	state->scs_irregs_k.ir_cs     = SEGMENT_KERNEL_CODE;
	state->scs_irregs_k.ir_eflags = EFLAGS_IF;
	state->scs_irregs_k.ir_eip    = (u32)(void *)thread_main;
	state->scs_sgregs.sg_gs       = SEGMENT_USER_GSBASE_RPL; /* Doesn't really matter, but stick to the likely case of this being USER_GSBASE */
	state->scs_sgregs.sg_fs       = SEGMENT_KERNEL_FSBASE;
	state->scs_sgregs.sg_es       = SEGMENT_USER_DATA_RPL;
	state->scs_sgregs.sg_ds       = SEGMENT_USER_DATA_RPL;
	/* No special values required for general purpose registers. */
	bzero(&state->scs_gpregs, sizeof(state->scs_gpregs));
#undef PUSH
#endif /* !__x86_64__ */
	/* TODO: Must also execute thread startup callbacks! */
	thread->t_flags |= TASK_FKERNTHREAD;
	_task_init_arch_sstate(thread, THIS_TASK, &state);
	FORTASK(thread, this_sstate) = state;
	if (!FORTASK(thread, this_fs))
		FORTASK(thread, this_fs) = incref(&fs_kernel);
#ifndef CONFIG_EVERYONE_IS_ROOT
	if (!FORTASK(thread, this_cred))
		FORTASK(thread, this_cred) = incref(&cred_kernel);
#endif /* !CONFIG_EVERYONE_IS_ROOT */
	if (!FORTASK(thread, this_handle_manager))
		FORTASK(thread, this_handle_manager) = incref(&handle_manager_kernel);
	return thread;
}


#ifndef __x86_64__
#ifndef __I386_NO_VM86
PRIVATE NOBLOCK ATTR_COLD u32
NOTHROW(KCALL get_userspace_eflags)(struct task const *__restrict self) {
	struct ucpustate st, ost;
	void const *unwind_pc;
	unsigned int unwind_error;
	assert(!PREEMPTION_ENABLED());
	assert(self->t_cpu == THIS_CPU);
	assert(!(self->t_flags & TASK_FKERNTHREAD));
	if (self == THIS_TASK) {
		ucpustate_current(&st);
	} else {
		scpustate_to_ucpustate(FORTASK(self, this_sstate), &st);
	}
	unwind_pc = ucpustate_getpc(&st);
	for (;;) {
		memcpy(&ost, &st, sizeof(struct ucpustate));
		unwind_error = unwind(unwind_pc,
		                      &unwind_getreg_ucpustate, &ost,
		                      &unwind_setreg_ucpustate, &st);
		if unlikely(unwind_error != UNWIND_SUCCESS) {
			/* XXX: There may be cases where this is allowed.
			 *      Maybe custom task termination  protocols? */
			kernel_panic("Unwind failed: %u", unwind_error);
		}
		if (!ucpustate_iskernel(&st))
			break;
		unwind_pc = ucpustate_getpc(&st) - 1;
	}
	return st.ucs_eflags;
}

/* Return  a  pointer  to   the  original  user-space  IRET   tail  of  the  calling   thread.
 * This is the pointer to the IRET structure located at the base of the caller's kernel stack.
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that  `thread' is  hosted by  the calling  CPU. */
PUBLIC NOBLOCK ATTR_CONST ATTR_RETNONNULL NONNULL((1)) struct irregs_user *
NOTHROW(FCALL x86_get_irregs)(struct task const *__restrict self) {
	struct irregs_user *result;
	pflag_t was;
	assert(self == THIS_TASK || (!PREEMPTION_ENABLED() && self->t_cpu == THIS_CPU));
	assert(!(self->t_flags & TASK_FKERNTHREAD));
#define stacktop() ((byte_t *)FORTASK(self, this_x86_kernel_psp0))
	result = (struct irregs_user *)(stacktop() - SIZEOF_IRREGS_USER);
	/* We need to account for the special case of the IRET tail pointing a VM86 thread!
	 * If  this  is  the  case,  then  fields  of  `result'  are  currently  mapped as:
	 *  - ((u32 *)result)[-4] = real_result->ir_eip
	 *  - ((u32 *)result)[-3] = real_result->ir_cs
	 *  - ((u32 *)result)[-2] = real_result->ir_eflags
	 *  - ((u32 *)result)[-1] = real_result->ir_esp
	 *  - result->ir_eip      = real_result->ir_ss
	 *  - result->ir_cs       = real_result->ir_es
	 *  - result->ir_eflags   = real_result->ir_ds
	 *  - result->ir_esp      = real_result->ir_fs
	 *  - result->ir_ss       = real_result->ir_gs */
	was = PREEMPTION_PUSHOFF();
	if (!(result->ir_esp & 0xffff0000) &&
	    !(result->ir_eip & 0xffff0000) &&
	    !(result->ir_eflags & 0xffff0000) &&
	    (((u32 *)result)[-2] & (EFLAGS_VM | EFLAGS_IF)) == (EFLAGS_VM | EFLAGS_IF) &&
	    !(((u32 *)result)[-3] & 0xffff0000) &&
	    ADDR_ISUSER(((u32 *)result)[-4])) {
		/* There is a very good chance that this is a vm86 thread, however we _really_
		 * have to be sure about this, and the only way to be 100% sure, is to  unwind
		 * the stack until we hit user-space, at which point we can unwind the %eflags
		 * register to see if it has the VM bit set. */
		u32 userspace_eflags;
		userspace_eflags = get_userspace_eflags(self);
		if (userspace_eflags & EFLAGS_VM) {
			/* It _really_ is a vm86 self! */
			result = (struct irregs_user *)((byte_t *)result -
			                                (SIZEOF_IRREGS_VM86 -
			                                 SIZEOF_IRREGS_USER));
			assertf(result->ir_eflags == userspace_eflags ||
			        (!(result->ir_eflags & EFLAGS_VM) &&
			         result->ir_eip == (uintptr_t)&x86_userexcept_sysret &&
			         SEGMENT_IS_VALID_KERNCODE(result->ir_cs)),
			        "Unexpected eflags at %p (found: %#" PRIxPTR ", expected: %#" PRIxPTR ")",
			        &result->ir_eflags, result->ir_eflags, userspace_eflags);
			printk(KERN_TRACE "[x86] Detected iret.vm86 tail at %p\n", result);
		}
	}
#undef stacktop
#ifndef NDEBUG
	if (result->ir_eflags & EFLAGS_VM) {
		assertf(result->ir_eflags & EFLAGS_IF,
		        "User-space IRET without EFLAGS.IF (%p)", result->ir_eflags);
	} else if (result->ir_eip != (uintptr_t)&x86_userexcept_sysret ||
	           !SEGMENT_IS_VALID_KERNCODE(result->ir_cs)) {
		assertf(SEGMENT_IS_VALID_USERCODE(result->ir_cs),
		        "User-space IRET with invalid CS (%p)", result->ir_cs);
		assertf(result->ir_eflags & EFLAGS_IF,
		        "User-space IRET without EFLAGS.IF (%p)", result->ir_eflags);
	}
#endif /* !NDEBUG */
	PREEMPTION_POP(was);
	return result;
}
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */




#ifndef __x86_64__
DEFINE_SYSCALL3(syscall_slong_t, modify_ldt,
                syscall_ulong_t, func,
                USER UNCHECKED void *, ptr,
                syscall_ulong_t, bytecount) {
	switch (func) {

	case 2:
		validate_writable(ptr, bytecount);
		bzero(ptr, bytecount);
		break;

	case 1:
	case 0x11: {
		struct linux_user_desc *desc;
		unsigned int entry;
		validate_readable(ptr, bytecount);
		if (bytecount < sizeof(struct linux_user_desc))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct linux_user_desc), bytecount);
		desc  = (struct linux_user_desc *)ptr;
		entry = ATOMIC_READ(desc->entry_number);
		/* We ignore everything except for `base_addr' */
		if ((entry & ~7) == SEGMENT_USER_FSBASE) {
			x86_set_user_fsbase(ATOMIC_READ(desc->base_addr)); /* %fs */
		} else if ((entry & ~7) == SEGMENT_USER_GSBASE) {
			x86_set_user_gsbase(ATOMIC_READ(desc->base_addr)); /* %gs */
		} else {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, entry);
		}
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_GENERIC,
		      func);
		break;
	}
	return 0;
}
#endif /* !__x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_SCHED_C */
