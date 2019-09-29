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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_TASK_CLONE_C
#define GUARD_KERNEL_CORE_ARCH_I386_TASK_CLONE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/except-handler.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/debugtrap.h>

#include <assert.h>
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>

#include <librpc/rpc.h>

DECL_BEGIN

typedef void (KCALL *pertask_init_t)(struct task *__restrict self);
INTDEF pertask_init_t __kernel_pertask_init_start[];
INTDEF pertask_init_t __kernel_pertask_init_end[];

typedef void (KCALL *pertask_fini_t)(struct task *__restrict self);
INTDEF pertask_fini_t __kernel_pertask_fini_start[];
INTDEF pertask_fini_t __kernel_pertask_fini_end[];

typedef void (KCALL *pertask_clone_t)(struct task *__restrict new_thread, uintptr_t flags);
INTDEF pertask_clone_t __kernel_pertask_clone_start[];
INTDEF pertask_clone_t __kernel_pertask_clone_end[];


INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];

DATDEF ATTR_PERTASK struct vm_node __this_kernel_stack ASMNAME("_this_kernel_stack");
DATDEF ATTR_PERTASK struct vm_datapart __this_kernel_stack_part ASMNAME("_this_kernel_stack_part");

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


PRIVATE void FCALL
task_srpc_set_child_tid(/*USER CHECKED pid_t*/void *arg) {
	ATOMIC_WRITE(*(pid_t *)arg, task_gettid());
}

#if 0
PRIVATE struct icpustate *FCALL
kernel_debugtrap_fork_thread_entry(void *UNUSED(arg),
                                   struct icpustate *__restrict state,
                                   unsigned int reason,
                                   struct rpc_syscall_info const *UNUSED(sc_info)) {
	if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
		char regbuf[64];
		sprintf(regbuf, DEBUG_TRAP_REGISTER_FORK ":%p;", THIS_TASK);
		state = kernel_debugtrap_r(state, SIGTRAP, regbuf);
	}
	return state;
}
#endif



INTERN pid_t KCALL
x86_task_clone(struct ucpustate const *__restrict init_state,
               uintptr_t clone_flags,
               USER UNCHECKED pid_t *parent_tidptr,
#ifndef __x86_64__
               uintptr_t newtls,
#endif /* !__x86_64__ */
               USER UNCHECKED pid_t *child_tidptr)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	upid_t result_pid;
	REF struct task *result;
	struct heapptr resptr;
	REF struct vm *result_vm;
	struct task *caller = THIS_TASK;
	if (clone_flags & CLONE_PARENT_SETTID)
		validate_writable(parent_tidptr, sizeof(*parent_tidptr));
	if (clone_flags & (CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID))
		validate_writable(child_tidptr, sizeof(*child_tidptr));
	if (clone_flags & CLONE_VM) {
		result_vm = incref(caller->t_vm);
	} else {
		result_vm = vm_clone(caller->t_vm, false);
	}
	TRY {
		/* Allocate a new task structure. */
		resptr = heap_alloc(&kernel_locked_heap,
		                    (size_t)__kernel_pertask_size,
		                    GFP_LOCKED | GFP_PREFLT);
		result = (REF struct task *)resptr.hp_ptr;
		/* Copy the per-task initialization template. */
		memcpy(result, __kernel_pertask_start, (size_t)__kernel_pertask_size);
		result->t_heapsz = resptr.hp_siz;
		result->t_self   = result;
		incref(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack).vn_block */
		incref(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack_part).dp_block */
		*(uintptr_t *)&FORTASK(result, __this_kernel_stack).vn_part += (uintptr_t)result;
		*(uintptr_t *)&FORTASK(result, __this_kernel_stack).vn_link.ln_pself += (uintptr_t)result;
		*(uintptr_t *)&FORTASK(result, __this_kernel_stack_part).dp_srefs += (uintptr_t)result;
		TRY {
			vm_datapart_do_allocram(&FORTASK(result, __this_kernel_stack_part));
			TRY {
				uintptr_t cache_version;
				vm_vpage_t stack_page;
				vm_vpage_t trampoline_page;
				cache_version = 0;
again_lock_vm:
				sync_write(&vm_kernel.v_treelock);
				stack_page = vm_getfree(&vm_kernel,
				                        (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_KERNSTACK),
				                        CEILDIV(KERNEL_STACKSIZE, PAGESIZE), 1,
				                        HINT_GETMODE(KERNEL_VMHINT_KERNSTACK));
				if unlikely(stack_page == VM_GETFREE_ERROR) {
					sync_endwrite(&vm_kernel.v_treelock);
					if (system_clearcaches_s(&cache_version))
						goto again_lock_vm;
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
					      (uintptr_t)CEILDIV(KERNEL_STACKSIZE, PAGESIZE));
				}
				FORTASK(result, __this_kernel_stack).vn_node.a_vmin = stack_page;
				FORTASK(result, __this_kernel_stack).vn_node.a_vmax = stack_page + CEILDIV(KERNEL_STACKSIZE, PAGESIZE) - 1;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!pagedir_prepare_map(stack_page, CEILDIV(KERNEL_STACKSIZE, PAGESIZE))) {
					sync_endwrite(&vm_kernel.v_treelock);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, (uintptr_t)1);
				}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				vm_node_insert(&FORTASK(result, __this_kernel_stack));

				/* Map the trampoline node. */
				trampoline_page = vm_getfree(&vm_kernel,
				                             (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE), 1, 1,
				                             HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
				if unlikely(trampoline_page == VM_GETFREE_ERROR) {
					vm_node_remove(&vm_kernel, stack_page);
					sync_endwrite(&vm_kernel.v_treelock);
					if (system_clearcaches_s(&cache_version))
						goto again_lock_vm;
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, (uintptr_t)1);
				}
				FORTASK(result, _this_trampoline_node).vn_node.a_vmin = trampoline_page;
				FORTASK(result, _this_trampoline_node).vn_node.a_vmax = trampoline_page;
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!pagedir_prepare_mapone(trampoline_page))
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, (uintptr_t)1);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				/* Load the trampoline node into the kernel VM. */
				vm_node_insert(&FORTASK(result, _this_trampoline_node));

				/* Map the stack into memory */
				vm_datapart_map_ram(&FORTASK(result, __this_kernel_stack_part), stack_page,
				                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
				sync_endwrite(&vm_kernel.v_treelock);
			} EXCEPT {
				vm_datapart_do_ccfreeram(&FORTASK(result, __this_kernel_stack_part));
				RETHROW();
			}
		} EXCEPT {
			decref_nokill(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack_part).dp_block */
			decref_nokill(&vm_datablock_anonymous); /* FORTASK(result,__this_kernel_stack).vn_block */
			heap_free(&kernel_locked_heap,
			          resptr.hp_ptr,
			          resptr.hp_siz,
			          GFP_NORMAL);
			RETHROW();
		}
	} EXCEPT {
		decref(result_vm);
		RETHROW();
	}

	/* Initial the task's initial CPU state. */
	{
		struct scpustate *state;
#ifdef __x86_64__
		state = (struct scpustate *)(VM_NODE_ENDADDR(&FORTASK(result, _this_kernel_stack)) - SIZEOF_SCPUSTATE);
#else /* __x86_64__ */
		if (init_state->ucs_eflags & EFLAGS_VM)
			result->t_flags |= TASK_FX86_VM86;
		state = (struct scpustate *)(VM_NODE_ENDADDR(&FORTASK(result, _this_kernel_stack)) -
		                             (OFFSET_SCPUSTATE_IRREGS +
		                              (init_state->ucs_eflags & EFLAGS_VM ? SIZEOF_IRREGS_VM86 : init_state->ucs_cs & 3 ? SIZEOF_IRREGS_USER : SIZEOF_IRREGS_KERNEL)));
#endif /* !__x86_64__ */
#ifdef __x86_64__
		GPREGS_TO_GPREGSNSP(state->scs_gpregs, init_state->ucs_gpregs);
		state->scs_sgregs = init_state->ucs_sgregs;
		state->scs_sgbase = init_state->ucs_sgbase;
		state->scs_irregs.ir_rip    = init_state->ucs_rip;
		state->scs_irregs.ir_cs     = init_state->ucs_cs;
		state->scs_irregs.ir_rflags = init_state->ucs_rflags;
		state->scs_irregs.ir_ss     = init_state->ucs_ss;
		state->scs_irregs.ir_rsp    = init_state->ucs_gpregs.gp_rsp;
#else /* __x86_64__ */
		state->scs_gpregs             = init_state->ucs_gpregs;
		state->scs_sgregs             = init_state->ucs_sgregs;
		state->scs_irregs_u.ir_eip    = init_state->ucs_eip;
		state->scs_irregs_u.ir_cs     = init_state->ucs_cs;
		state->scs_irregs_u.ir_eflags = init_state->ucs_eflags;
		if (init_state->ucs_eflags & EFLAGS_VM) {
			state->scs_irregs_u.ir_esp = init_state->ucs_gpregs.gp_esp;
			state->scs_irregs_u.ir_ss  = init_state->ucs_ss;
			state->scs_irregs_v.ir_es  = init_state->ucs_sgregs.sg_es;
			state->scs_irregs_v.ir_ds  = init_state->ucs_sgregs.sg_ds;
			state->scs_irregs_v.ir_fs  = init_state->ucs_sgregs.sg_fs;
			state->scs_irregs_v.ir_gs  = init_state->ucs_sgregs.sg_gs;
		} else if (init_state->ucs_cs & 3) {
			state->scs_irregs_u.ir_esp = init_state->ucs_gpregs.gp_esp;
			state->scs_irregs_u.ir_ss  = init_state->ucs_ss;
		}
#endif /* !__x86_64__ */
#if 0
		if (kernel_debugtrap_enabled()) {
			/* When debug traps are enabled, trigger a FORK trap
			 * before jump to user-space within the new thread. */
			state = task_push_asynchronous_rpc(state, &kernel_debugtrap_fork_thread_entry, NULL, NULL);
		}
#endif
		if (clone_flags & CLONE_CHILD_SETTID) {
			/* Inject an RPC for saving the child's TID within the given pointer
			 * This always needs to be done in the context of the child, so that exceptions
			 * during the write are handled in the proper context, as well as in regards to
			 * the child actually existing in a different VM when `CLONE_VM' isn't given. */
			state = task_push_asynchronous_srpc(state,
			                                    &task_srpc_set_child_tid,
			                                    child_tidptr,
			                                    NULL);
		}
		result->t_sched.s_state = state;
	}

#ifndef __x86_64__
	/* Assign the used TLS segment bases. */
	FORTASK(result, x86_this_user_gsbase) = clone_flags & CLONE_SETTLS ? newtls : get_user_gsbase();
	FORTASK(result, x86_this_user_fsbase) = get_user_fsbase();
#endif /* !__x86_64__ */

	result->t_vm = result_vm; /* Inherit reference. */
	TRY {
		pertask_init_t *iter;
		assert(!result->t_vm_tasks.ln_pself);

		/* Insert the new task into the VM */
		vm_tasklock_write(result_vm);
		LLIST_INSERT(result_vm->v_tasks, result, t_vm_tasks);
		vm_tasklock_endwrite(result_vm);

		iter = __kernel_pertask_init_start;
		for (; iter < __kernel_pertask_init_end; ++iter)
			(**iter)(result);
	} EXCEPT {
		ATOMIC_WRITE(result->t_refcnt, 0);
		/* Destroy the task if an initializer threw another exception. */
		destroy(result);
		RETHROW();
	}
	TRY {
		/* Invoke clone() callbacks */
		pertask_clone_t *iter;
		for (iter = __kernel_pertask_clone_start;
		     iter < __kernel_pertask_clone_end; ++iter)
			(**iter)(result, clone_flags);

		/* Load the PID that has been assigned to the target thread. */
		result_pid = task_gettid_of(result);

		if (clone_flags & CLONE_PARENT_SETTID)
			ATOMIC_WRITE(*parent_tidptr, result_pid);
		if (clone_flags & CLONE_CHILD_CLEARTID) {
			/* `set_tid_address(child_tidptr)' */
			FORTASK(result, _this_tid_address) = child_tidptr;
		}

#if 0 /* XXX: Remove me (only here to force & verify use of IPI mechanisms in multi-core situations)
       *      Basically: Only here to test a whole bunch of stuff... */
		if (cpu_count > 1)
			result->t_cpu = cpu_vector[1];
#endif

		if (kernel_debugtrap_enabled()) {
			char regbuf[64];
			/* FIXME: Actually telling GDB about the correct thread ID (which by the way is impossible
			 *        to do for us dynamically, since its format depends on configurations only known
			 *        to the gdbstub driver), causes GDB to freeze with its process taking up 100% cpu
			 *        usage (though mind you, only using a single core of my host which equates to 8%)
			 *        However, just putting in the multiprocess-compliant pid=1;tid=1 seems to prevent
			 *        it from hanging itself...
			 *        Looking at the GDB source code I've started to get the feeling that it expects 2
			 *        trap interrupts when a fork happens (???), however this can only ever be done in
			 *        non-stop mode (which is a way bigger thing of weirdness that the online documentation
			 *        fails to let me comprehend), so I don't really know what GDB wants from me...
			 *        Anyways, the online documentation of the `fork' stop reply packet ...
			 *        https://sourceware.org/gdb/onlinedocs/gdb/Stop-Reply-Packets.html#Stop-Reply-Packets
			 *        ... doesn't even mention the fact that a fork always implies there being 2 processes,
			 *        nor does it mention which of them should send the stop reply.
			 *        Inference from other stop reply packets also doesn't help:
			 *         #1: Since a vfork() reply exists, and a vfork() always implies that the parent process
			 *             remains suspended until the child exit()- or exec()s would imply that it is the
			 *             child process (and only the child?) which is supposed to send fork notifications
			 *             However, since the docs _do_ mention that the fork stop reason should be followed
			 *             by the _child_ thread-id, GDB would never know who the parent is, so while vfork()
			 *             isn't even on the table, its similarity poses more questions than it answers
			 *         #2: Since fork() should include the thread-ID of the child process, it would seem
			 *             obvious that the parent process should send a packet like:
			 *             $T05[...]thread:<PARENT_THREAD_ID>;[...]fork:<CHILD_THREAD_ID>;#[...]
			 *             However, having tried this, it is what causes GDB to hang itself, so either I'm
			 *             doing this part wrong, or this isn't the answer either.
			 * NOTE: This FIXME is mirrored in `/kos/src/kernel/modgdbstu/gdb.c'
			 */
			sprintf(regbuf, DEBUG_TRAP_REGISTER_FORK ":p1.1;" /*, (uintptr_t)result - KERNEL_BASE*/);
			kernel_debugtrap(SIGTRAP, regbuf);
		}

		/* Actually start execution of the newly created thread. */
		task_start(result);
	} EXCEPT {
		decref_likely(result);
		RETHROW();
	}
	decref_unlikely(result);

	return result_pid;
}


PRIVATE struct icpustate *FCALL
task_clone_rpc(void *UNUSED(arg),
               struct icpustate *__restrict state,
               unsigned int reason,
               struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	if (reason == TASK_RPC_REASON_SYSCALL) {
		pid_t child_tid;
		struct ucpustate ustate;
#ifdef __x86_64__
		GPREGSNSP_TO_GPREGS(ustate.ucs_gpregs,
		                    state->ics_gpregs,
		                    sc_info->rsi_args[1]); /* child_stack */
		ustate.ucs_sgbase.sg_fsbase = get_user_fsbase();
		ustate.ucs_sgbase.sg_gsbase = get_user_gsbase();
		ustate.ucs_sgregs.sg_ds     = __rdds();
		ustate.ucs_sgregs.sg_es     = __rdes();
		ustate.ucs_sgregs.sg_fs     = __rdfs();
		ustate.ucs_sgregs.sg_gs     = __rdgs();
		ustate.ucs_cs               = irregs_rdcs(&state->ics_irregs);
		ustate.ucs_ss               = irregs_rdss(&state->ics_irregs);
		ustate.ucs_rflags           = irregs_rdflags(&state->ics_irregs);
		ustate.ucs_rip              = irregs_rdip(&state->ics_irregs);
		if (sc_info->rsi_args[0] & CLONE_SETTLS)
			ustate.ucs_sgbase.sg_gsbase = sc_info->rsi_args[4]; /* newtls */
#else /* __x86_64__ */
		ustate.ucs_gpregs        = state->ics_gpregs;
		ustate.ucs_sgregs.sg_ds  = state->ics_ds;
		ustate.ucs_sgregs.sg_es  = state->ics_es;
		ustate.ucs_sgregs.sg_fs  = state->ics_fs;
		ustate.ucs_sgregs.sg_gs  = __rdgs();
		ustate.ucs_cs            = SEGMENT_USER_CODE_RPL;
		ustate.ucs_ss            = SEGMENT_USER_DATA_RPL;
		ustate.ucs_eflags        = irregs_rdflags(&state->ics_irregs_k);
		ustate.ucs_eip           = irregs_rdip(&state->ics_irregs_k);
		ustate.ucs_gpregs.gp_esp = (uintptr_t)sc_info->rsi_args[1]; /* child_stack */
		ustate.ucs_gpregs.gp_eax = 0;
#endif /* !__x86_64__ */

		child_tid = x86_task_clone(&ustate,
		                           sc_info->rsi_args[0],                         /* clone_flags */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_args[2], /* parent_tidptr */
#ifndef __x86_64__
		                           sc_info->rsi_args[3],                        /* newtls */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_args[4] /* child_tidptr */
#else /* !__x86_64__ */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_args[3] /* child_tidptr */
#endif /* __x86_64__ */
		                           );
#ifdef __x86_64__
		state->ics_gpregs.gp_rax = child_tid;
#else /* __x86_64__ */
		state->ics_gpregs.gp_eax = child_tid;
#endif /* !__x86_64__ */
	}
	return state;
}

PRIVATE struct icpustate *FCALL
task_fork_rpc(void *UNUSED(arg), struct icpustate *__restrict state,
              unsigned int reason, struct rpc_syscall_info const *UNUSED(sc_info)) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	if (reason != TASK_RPC_REASON_SHUTDOWN) {
		pid_t child_tid;
		struct ucpustate ustate;
#ifdef __x86_64__
		GPREGSNSP_TO_GPREGS(ustate.ucs_gpregs,
		                    state->ics_gpregs,
		                    irregs_rdsp(&state->ics_irregs));
		ustate.ucs_sgregs.sg_ds  = __rdds();
		ustate.ucs_sgregs.sg_es  = __rdes();
		ustate.ucs_sgregs.sg_fs  = __rdfs();
		ustate.ucs_sgregs.sg_gs  = __rdgs();
		ustate.ucs_cs            = irregs_rdcs(&state->ics_irregs);
		ustate.ucs_ss            = irregs_rdss(&state->ics_irregs);
		ustate.ucs_rflags        = irregs_rdflags(&state->ics_irregs);
		ustate.ucs_rip           = irregs_rdip(&state->ics_irregs);
		ustate.ucs_gpregs.gp_rax = 0; /* Return 0 for in the child process. */
#else /* __x86_64__ */
		ustate.ucs_gpregs        = state->ics_gpregs;
		ustate.ucs_sgregs.sg_ds  = state->ics_ds;
		ustate.ucs_sgregs.sg_es  = state->ics_es;
		ustate.ucs_sgregs.sg_fs  = state->ics_fs;
		ustate.ucs_sgregs.sg_gs  = __rdgs();
		ustate.ucs_cs            = irregs_rdcs(&state->ics_irregs_k);
		ustate.ucs_ss            = state->ics_irregs_u.ir_ss;
		ustate.ucs_gpregs.gp_esp = irregs_rdsp(&state->ics_irregs_k);
		ustate.ucs_eflags        = irregs_rdflags(&state->ics_irregs_k);
		ustate.ucs_eip           = irregs_rdip(&state->ics_irregs_k);
		ustate.ucs_gpregs.gp_eax = 0;
#endif /* !__x86_64__ */
		child_tid = x86_task_clone(&ustate,
		                           SIGCHLD,
		                           NULL,
#ifndef __x86_64__
		                           0, /* Ignored because we don't set CLONE_SETTLS */
#endif /* !__x86_64__ */
		                           NULL);
#ifdef __x86_64__
		state->ics_gpregs.gp_rax = child_tid;
#else /* __x86_64__ */
		state->ics_gpregs.gp_eax = child_tid;
#endif /* !__x86_64__ */
	}
	return state;
}




#ifdef __x86_64__
DEFINE_SYSCALL5(pid_t, clone,
                syscall_ulong_t, flags,
                USER UNCHECKED void *, child_stack,
                USER UNCHECKED pid_t *, ptid,
                USER UNCHECKED pid_t *, ctid,
                uintptr_t, newtls)
#else /* __x86_64__ */
DEFINE_SYSCALL5(pid_t, clone,
                syscall_ulong_t, flags,
                USER UNCHECKED void *, child_stack,
                USER UNCHECKED pid_t *, ptid,
                uintptr_t, newtls,
                USER UNCHECKED pid_t *, ctid)
#endif /* !__x86_64__ */
{
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &task_clone_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       NULL,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}

DEFINE_SYSCALL0(pid_t, fork) {
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &task_fork_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       NULL,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_TASK_CLONE_C */
