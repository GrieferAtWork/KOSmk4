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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C 1
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
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/iopl.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/debugtrap.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

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

DATDEF ATTR_PERTASK struct vm_node this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
DATDEF ATTR_PERTASK struct vm_datapart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


PRIVATE WUNUSED NONNULL((2)) struct icpustate *FCALL
task_srpc_set_child_tid(void *arg,
                        struct icpustate *__restrict state,
                        unsigned int UNUSED(reason),
                        struct rpc_syscall_info const *UNUSED(sc_info)) {
	ATOMIC_WRITE(*(USER CHECKED pid_t *)arg, task_gettid());
	return state;
}

#if 0
PRIVATE struct icpustate *FCALL
kernel_debugtrap_fork_thread_entry(void *UNUSED(arg),
                                   struct icpustate *__restrict state,
                                   unsigned int reason,
                                   struct rpc_syscall_info const *UNUSED(sc_info)) {
	if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
		struct debugtrap_reason r;
		r.dtr_signo  = SIGTRAP;
		r.dtr_reason = DEBUGTRAP_REASON_LIBRARY;
		kernel_debugtrap(&r);
	}
	return state;
}
#endif



INTERN pid_t KCALL
x86_task_clone(struct icpustate const *__restrict init_state,
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
		incref(&vm_datablock_anonymous); /* FORTASK(result,this_kernel_stacknode_).vn_block */
		incref(&vm_datablock_anonymous); /* FORTASK(result,this_kernel_stackpart_).dp_block */
#define REL(x) ((x) = (__typeof__(x))(uintptr_t)((byte_t *)(x) + (uintptr_t)result))
		REL(FORTASK(result, this_kernel_stacknode_).vn_part);
		REL(FORTASK(result, this_kernel_stacknode_).vn_link.ln_pself);
		REL(FORTASK(result, this_kernel_stackpart_).dp_srefs);
#undef REL
		TRY {
			vm_datapart_do_allocram(&FORTASK(result, this_kernel_stackpart_));
			TRY {
				uintptr_t cache_version;
				void *stack_addr;
				void *trampoline_addr;
				cache_version = 0;
again_lock_vm:
				sync_write(&vm_kernel.v_treelock);
				stack_addr = vm_getfree(&vm_kernel,
				                        HINT_GETADDR(KERNEL_VMHINT_KERNSTACK),
				                        CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE),
				                        PAGESIZE,
				                        HINT_GETMODE(KERNEL_VMHINT_KERNSTACK));
				if unlikely(stack_addr == VM_GETFREE_ERROR) {
					sync_endwrite(&vm_kernel.v_treelock);
					if (system_clearcaches_s(&cache_version))
						goto again_lock_vm;
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
					      CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE));
				}
				FORTASK(result, this_kernel_stacknode_).vn_node.a_vmin = PAGEID_ENCODE((byte_t *)stack_addr);
				FORTASK(result, this_kernel_stacknode_).vn_node.a_vmax = PAGEID_ENCODE((byte_t *)stack_addr + CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE) - 1);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!npagedir_prepare_map(stack_addr, CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE))) {
					sync_endwrite(&vm_kernel.v_treelock);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE));
				}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				vm_node_insert(&FORTASK(result, this_kernel_stacknode_));

				/* Map the trampoline node. */
				trampoline_addr = vm_getfree(&vm_kernel,
				                             HINT_GETADDR(KERNEL_VMHINT_TRAMPOLINE),
				                             PAGESIZE, PAGESIZE,
				                             HINT_GETMODE(KERNEL_VMHINT_TRAMPOLINE));
				if unlikely(trampoline_addr == VM_GETFREE_ERROR) {
					vm_node_remove(&vm_kernel, stack_addr);
					sync_endwrite(&vm_kernel.v_treelock);
					if (system_clearcaches_s(&cache_version))
						goto again_lock_vm;
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, PAGESIZE);
				}
				FORTASK(result, this_trampoline_node).vn_node.a_vmin = PAGEID_ENCODE(trampoline_addr);
				FORTASK(result, this_trampoline_node).vn_node.a_vmax = PAGEID_ENCODE(trampoline_addr);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!npagedir_prepare_mapone(trampoline_addr))
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				/* Load the trampoline node into the kernel VM. */
				vm_node_insert(&FORTASK(result, this_trampoline_node));

				/* Map the stack into memory */
				vm_datapart_map_ram(&FORTASK(result, this_kernel_stackpart_),
				                    stack_addr,
				                    PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
				sync_endwrite(&vm_kernel.v_treelock);
			} EXCEPT {
				vm_datapart_do_ccfreeram(&FORTASK(result, this_kernel_stackpart_));
				RETHROW();
			}
		} EXCEPT {
			decref_nokill(&vm_datablock_anonymous); /* FORTASK(result,this_kernel_stackpart_).dp_block */
			decref_nokill(&vm_datablock_anonymous); /* FORTASK(result,this_kernel_stacknode_).vn_block */
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

	{
		struct scpustate *state;
		void *kernel_stack;
		/* Initial the task's initial CPU state. */
		kernel_stack = (void *)vm_node_getend(&FORTASK(result, this_kernel_stacknode));
		state        = icpustate_to_scpustate_p(init_state, kernel_stack);

		/* Reset iopl() for the child thread/process */
		if ((clone_flags & CLONE_THREAD) ? !x86_iopl_keep_after_clone
		                                 : !x86_iopl_keep_after_fork)
			state->scs_irregs.ir_pflags &= ~EFLAGS_IOPLMASK;

		/* Have `clone()' or `fork()' return `0' in the child thread/process */
		gpregs_setpax(&state->scs_gpregs, 0);

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
			state = task_push_asynchronous_rpc(state,
			                                   &task_srpc_set_child_tid,
			                                   child_tidptr);
		}
		result->t_sched.s_state = state;
	}

#ifndef __x86_64__
	/* Assign the used TLS segment bases. */
	FORTASK(result, this_x86_user_gsbase) = clone_flags & CLONE_SETTLS ? newtls : get_user_gsbase();
	FORTASK(result, this_x86_user_fsbase) = get_user_fsbase();
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
			FORTASK(result, this_tid_address) = child_tidptr;
		}

#if 0 /* XXX: Remove me (only here to force & verify use of IPI mechanisms in multi-core situations)
       *      Basically: Only here to test a whole bunch of stuff... */
		if (cpu_count > 1)
			result->t_cpu = cpu_vector[1];
#endif

		if (kernel_debugtrap_enabled()) {
			struct debugtrap_reason r;
			r.dtr_signo  = SIGTRAP;
			r.dtr_reason = DEBUGTRAP_REASON_FORK;
			r.dtr_ptrarg = result;
			kernel_debugtrap(&r);
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
		child_tid = x86_task_clone(state,
		                           sc_info->rsi_args[0],                         /* clone_flags */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_args[2], /* parent_tidptr */
#ifndef __x86_64__
		                           sc_info->rsi_args[3],                        /* newtls */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_args[4] /* child_tidptr */
#else /* !__x86_64__ */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_args[3] /* child_tidptr */
#endif /* __x86_64__ */
		                           );
		gpregs_setpax(&state->ics_gpregs, child_tid);
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
		child_tid = x86_task_clone(state,
		                           SIGCHLD,
		                           NULL,
#ifndef __x86_64__
		                           0, /* Ignored because we don't set CLONE_SETTLS */
#endif /* !__x86_64__ */
		                           NULL);
		gpregs_setpax(&state->ics_gpregs, child_tid);
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
	(void)flags;
	(void)child_stack;
	(void)ptid;
	(void)ctid;
	(void)newtls;
	task_schedule_user_rpc(THIS_TASK,
	                       &task_clone_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
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
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C */
