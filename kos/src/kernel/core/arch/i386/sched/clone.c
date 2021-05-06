/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h> /* this_trampoline_node */
#include <kernel/mman/unmapped.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/x86/gdt.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/x86/iopl.h>

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
#include <signal.h> /* SIGCHLD */
#include <stdio.h>
#include <string.h>

#include <librpc/rpc.h>

#ifndef CONFIG_NO_USERKERN_SEGMENT
#include <kernel/rand.h>
#include <sched/userkern.h>

#include <kos/ukern.h>
#endif /* !CONFIG_NO_USERKERN_SEGMENT */

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

DATDEF ATTR_PERTASK struct mpart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");
DATDEF ATTR_PERTASK struct mnode this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
DATDEF ATTR_PERTASK struct mnode this_kernel_stackguard_ ASMNAME("this_kernel_stackguard");
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */


PRIVATE WUNUSED NONNULL((2)) struct icpustate *FCALL
task_srpc_set_child_tid(void *arg,
                        struct icpustate *__restrict state,
                        unsigned int UNUSED(reason),
                        struct rpc_syscall_info const *UNUSED(sc_info)) {
	ATOMIC_WRITE(*(USER CHECKED pid_t *)arg, task_gettid());
	return state;
}



#ifndef CONFIG_NO_USERKERN_SEGMENT
PUBLIC NOBLOCK uintptr_t
NOTHROW(KCALL x86_get_random_userkern_address)(void) {
	uintptr_t offset;
	/* Assign a random (pointer-aligned) offset into kernel-
	 * space as the base  address for the userkern  segment. */
	offset = (uintptr_t)(krand() * USERKERN_SEGMENT_ALIGN);
	offset %= ((uintptr_t)0 - KERNELSPACE_BASE) - (USERKERN_SYSCALL_MAXVALID + 1);
	offset += KERNELSPACE_BASE;
	return offset;
}

#ifdef __x86_64__
PUBLIC NOBLOCK u32
NOTHROW(KCALL x86_get_random_userkern_address32)(void) {
	u32 offset;
	/* Assign a random (pointer-aligned) offset into (compatibility-mode)
	 * kernel-space  as  the  base  address  for  the  userkern  segment. */
	offset = (u32)(krand32() * USERKERN_SEGMENT_ALIGN);
	offset %= ((u32)0 - COMPAT_KERNELSPACE_BASE) - (USERKERN_SYSCALL_MAXVALID + 1);
	offset += COMPAT_KERNELSPACE_BASE;
	return offset;
}
#endif /* __x86_64__ */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */


PRIVATE void KCALL
waitfor_vfork_completion(struct task *__restrict thread) {
	while ((ATOMIC_READ(thread->t_flags) & TASK_FVFORK) != 0) {
		struct taskpid *pid;
		pid = FORTASK(thread, this_taskpid);
		assert(pid);
		task_connect(&pid->tp_changed);
		if unlikely((ATOMIC_READ(thread->t_flags) & TASK_FVFORK) == 0) {
			task_disconnectall();
			break;
		}
		task_waitfor();
	}
}


INTERN pid_t KCALL
x86_clone_impl(struct icpustate const *__restrict init_state,
               uintptr_t clone_flags,
               USER UNCHECKED void *child_stack,
               USER UNCHECKED pid_t *parent_tidptr,
               USER UNCHECKED pid_t *child_tidptr,
               uintptr_t gsbase, uintptr_t fsbase)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	upid_t result_pid;
	struct heapptr resptr;
	REF struct task *result;
	REF struct mman *result_mman;
	struct task *caller = THIS_TASK;
	if (clone_flags & CLONE_PARENT_SETTID)
		validate_writable(parent_tidptr, sizeof(*parent_tidptr));
	if (clone_flags & (CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID))
		validate_writable(child_tidptr, sizeof(*child_tidptr));
	if (clone_flags & CLONE_VM) {
		result_mman = incref(caller->t_mman);
	} else {
		result_mman = mman_fork();
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
		incref(&mfile_zero); /* FORTASK(result, this_kernel_stackpart_).mp_file */
#define REL(x) ((x) = (__typeof__(x))(uintptr_t)((byte_t *)(x) + (uintptr_t)result))
		REL(FORTASK(result, this_kernel_stacknode_).mn_part);
		REL(FORTASK(result, this_kernel_stacknode_).mn_link.le_prev);
		REL(FORTASK(result, this_kernel_stackpart_).mp_share.lh_first);
#undef REL
		/* Set the VFORK flag to cause the thread to execute in VFORK-mode.
		 * This must be done before we  start making the thread visible  to
		 * other kernel components, since this also affects things such  as
		 * the thread's effective signal mask. */
		if (clone_flags & CLONE_VFORK)
			result->t_flags |= TASK_FVFORK;
		TRY {
			mpart_ll_allocmem(&FORTASK(result, this_kernel_stackpart_),
			                  KERNEL_STACKSIZE / PAGESIZE);
			TRY {
				syscache_version_t cache_version = SYSCACHE_VERSION_INIT;
				byte_t *stack_addr;
				byte_t *trampoline_addr;
again_lock_mman:
				mman_lock_acquire(&mman_kernel);
				stack_addr = (byte_t *)mman_findunmapped(&mman_kernel,
				                                         MHINT_GETADDR(KERNEL_MHINT_KERNSTACK),
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
				                                         CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE) + PAGESIZE,
#else /* CONFIG_HAVE_KERNEL_STACK_GUARD */
				                                         CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE),
#endif /* !CONFIG_HAVE_KERNEL_STACK_GUARD */
				                                         MHINT_GETMODE(KERNEL_MHINT_KERNSTACK));
				if unlikely(stack_addr == MAP_FAILED) {
					mman_lock_release(&mman_kernel);
					if (syscache_clear_s(&cache_version))
						goto again_lock_mman;
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
					      CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE));
				}
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
				FORTASK(result, this_kernel_stackguard_).mn_minaddr = stack_addr;
				FORTASK(result, this_kernel_stackguard_).mn_maxaddr = stack_addr + PAGESIZE - 1;
				stack_addr = (byte_t *)stack_addr + PAGESIZE;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
				FORTASK(result, this_kernel_stacknode_).mn_minaddr = stack_addr;
				FORTASK(result, this_kernel_stacknode_).mn_maxaddr = stack_addr + KERNEL_STACKSIZE - 1;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!pagedir_prepare(stack_addr, KERNEL_STACKSIZE)) {
					mman_lock_release(&mman_kernel);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, KERNEL_STACKSIZE);
				}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

				/* Map the trampoline node. */
				trampoline_addr = (byte_t *)mman_findunmapped(&mman_kernel,
				                                              MHINT_GETADDR(KERNEL_MHINT_TRAMPOLINE), PAGESIZE,
				                                              MHINT_GETMODE(KERNEL_MHINT_TRAMPOLINE));
				if unlikely(trampoline_addr == MAP_FAILED) {
					mman_lock_release(&mman_kernel);
					if (syscache_clear_s(&cache_version))
						goto again_lock_mman;
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, PAGESIZE);
				}
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!pagedir_prepareone(trampoline_addr))
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				FORTASK(result, this_trampoline_node).mn_minaddr = trampoline_addr;
				FORTASK(result, this_trampoline_node).mn_maxaddr = trampoline_addr + PAGESIZE - 1;
				/* Load nodes into the kernel VM. */
				mman_mappings_insert(&mman_kernel, &FORTASK(result, this_trampoline_node));
				mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
				mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

				/* Map the stack into memory */
				mpart_mmap_force(&FORTASK(result, this_kernel_stackpart_),
				                 stack_addr, KERNEL_STACKSIZE, 0,
				                 PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);

				/* Kernel stacks have the `MNODE_F_MPREPARED' flag set.
				 * XXX: Maybe change this in the future? */
				/*pagedir_kernelunprepare(stack_addr, KERNEL_STACKSIZE);*/
				mman_lock_release(&mman_kernel);
			} EXCEPT {
				mpart_ll_ccfreemem(&FORTASK(result, this_kernel_stackpart_));
				RETHROW();
			}
		} EXCEPT {
			decref_nokill(&mfile_zero); /* FORTASK(result, this_kernel_stacknode_).mp_file */
			heap_free(&kernel_locked_heap,
			          resptr.hp_ptr,
			          resptr.hp_siz,
			          GFP_NORMAL);
			RETHROW();
		}
	} EXCEPT {
		decref(result_mman);
		RETHROW();
	}

	{
		struct scpustate *state;
		void *kernel_stack;
		/* Initial the task's initial CPU state. */
		kernel_stack = mnode_getendaddr(&FORTASK(result, this_kernel_stacknode));

#ifdef __x86_64__
		state = icpustate_to_scpustate_p_ex(init_state,
		                                    kernel_stack,
		                                    gsbase,
		                                    fsbase,
		                                    __rdgs(),
		                                    __rdfs(),
		                                    __rdes(),
		                                    __rdds());
#else /* __x86_64__ */
		state = icpustate_to_scpustate_p(init_state, kernel_stack);
		/* Assign the used TLS segment bases. */
		FORTASK(result, this_x86_user_gsbase) = gsbase;
		FORTASK(result, this_x86_user_fsbase) = fsbase;
#endif /* !__x86_64__ */

		/* Assign the given stack pointer for the new thread. */
		scpustate_setuserpsp(state, (uintptr_t)child_stack);

		/* Reset iopl() for the child thread/process */
		if ((clone_flags & CLONE_THREAD) ? !x86_iopl_keep_after_clone
		                                 : !x86_iopl_keep_after_fork)
			state->scs_irregs.ir_pflags &= ~EFLAGS_IOPLMASK;

		/* Have `clone()' or `fork()' return `0' in the child thread/process */
		gpregs_setpax(&state->scs_gpregs, 0);

		if (clone_flags & CLONE_CHILD_SETTID) {
			/* Inject  an  RPC  for  saving  the  child's  TID  within  the  given  pointer
			 * This always needs to be done in the context of the child, so that exceptions
			 * during the write are handled in the proper context, as well as in regards to
			 * the child actually existing in a  different VM when `CLONE_VM' isn't  given. */
			state = task_push_asynchronous_rpc(state,
			                                   &task_srpc_set_child_tid,
			                                   child_tidptr);
		}
		FORTASK(result, this_sstate) = state;
	}

	result->t_mman = result_mman; /* Inherit reference. */

	/* Insert the new task into the VM */
	mman_threadslock_acquire(result_mman);
	LIST_INSERT_HEAD(&result_mman->mm_threads, result, t_mman_tasks);
	mman_threadslock_release(result_mman);

	TRY {
		pertask_init_t *iter;
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

#if 1 /* XXX: Remove me (only here to force & verify use of IPI mechanisms in multi-core situations)
       *      Basically: Only here to test a whole bunch of stuff... */
		if (cpu_count > 1) {
			static unsigned int nextcpu = 0;
			result->t_cpu = cpu_vector[(nextcpu++) % cpu_count];
		}
#endif

		/* Before  we actually start executing the child thread,
		 * check if there are any pending POSIX signals directed
		 * at us, and don't actually  start the child thread  if
		 * there are any.
		 *
		 * This must be done to prevent run-away child processes
		 * as   the  result  of  code  like  `for (;;) fork();'.
		 * Consider a user now presses `CTRL+C'.
		 *
		 * That signal will  have been sent  to all threads  apart
		 * of the existing  process group. However  this may  have
		 * been done before `result' (aka. the new thread/process)
		 * was added to that  process group, meaning that  there's
		 * a chance that it didn't get the signal.
		 *
		 * In this  scenario, we  can't allow  the new  thread/process
		 * to start executing, since that would violate the assumption
		 * that  sending a  signal to  process group  means that _all_
		 * threads that  existed at  one point  within the  group  had
		 * the signal delivered. */
		task_serve();

		/* Deal with vfork() */
		if (clone_flags & CLONE_VFORK) {
			REF struct kernel_sigmask *old_sigmask;
			struct kernel_sigmask_arref *maskref;
			maskref = &PERTASK(this_sigmask);

#ifdef CONFIG_HAVE_USERPROCMASK
			/* Special case for when the parent thread was using USERPROCMASK.
			 * In this case we must essentially disable the USERPROCMASK until
			 * our child process indicates that they're done using our VM
			 *
			 * This way, the child process can freely (and unknowingly) modify
			 * the parent process's  signal mask,  without actually  affecting
			 * anything, and without those changes remaining visible once  the
			 * parent process is resumed. */
			if (caller->t_flags & TASK_FUSERPROCMASK) {
				sigset_t saved_user_sigset;
				USER UNCHECKED sigset_t *user_sigmask;
				USER CHECKED struct userprocmask *um;
				um = PERTASK_GET(this_userprocmask_address);
				user_sigmask = ATOMIC_READ(um->pm_sigmask);
				validate_readwrite(user_sigmask, sizeof(sigset_t));
				memcpy(&saved_user_sigset, user_sigmask, sizeof(sigset_t));
				/* Switch over to a completely filled, kernel-space
				 * signal mask to-be  used by  the calling  thread. */
				old_sigmask = arref_xch(maskref, &kernel_sigmask_full);
				ATOMIC_AND(caller->t_flags, ~TASK_FUSERPROCMASK);
				TRY {
					/* Actually start execution of the newly created thread. */
					task_start(result);
					/* Wait for the thread to clear its VFORK flag. */
					waitfor_vfork_completion(result);
				} EXCEPT {
					arref_set_inherit(maskref, old_sigmask);
					ATOMIC_OR(caller->t_flags, TASK_FUSERPROCMASK);
					memcpy(user_sigmask, &saved_user_sigset, sizeof(sigset_t));
					ATOMIC_WRITE(um->pm_sigmask, user_sigmask);
					sigmask_check_after_except();
					RETHROW();
				}
				/* Restore our old kernel-space signal mask. */
				arref_set_inherit(maskref, old_sigmask);
				/* Re-enable userprocmask-mode. */
				ATOMIC_OR(caller->t_flags, TASK_FUSERPROCMASK);

				/* Restore the old (saved) state of the user-space  signal
				 * mask, as it was prior to the vfork-child being started.
				 * NOTE: Do this _after_  we've already  restored the  kernel-side
				 *       of the calling thread's TLS state. That way, if something
				 *       goes wrong while we're  restoring the user-space side  of
				 *       things, it won't actually our fault! */
				memcpy(user_sigmask, &saved_user_sigset, sizeof(sigset_t));
				ATOMIC_WRITE(um->pm_sigmask, user_sigmask);
			} else
#endif /* CONFIG_HAVE_USERPROCMASK */
			{
				/* Actually start execution of the newly created thread. */
				task_start(result);

				/* The specs say that we should ignore (mask) all POSIX
				 * signals until the  child indicate VFORK  completion. */
				old_sigmask = arref_xch(maskref, &kernel_sigmask_full);
				TRY {
					/* Wait for the thread to clear its VFORK flag. */
					waitfor_vfork_completion(result);
				} EXCEPT {
					arref_set_inherit(maskref, old_sigmask);
					sigmask_check_after_except();
					RETHROW();
				}
				arref_set_inherit(maskref, old_sigmask);
			}
			/* With the original signal mask restored, we must check if
			 * we (the parent) have received any signals while we  were
			 * waiting on the child */
			sigmask_check();
		} else {
			/* Actually start execution of the newly created thread. */
			task_start(result);
		}
	} EXCEPT {
		decref_likely(result);
		RETHROW();
	}
	decref_unlikely(result);
	return result_pid;
}





/************************************************************************/
/* clone()                                                              */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_CLONE) && defined(__x86_64__)
PRIVATE struct icpustate *FCALL
task_clone64_rpc(void *UNUSED(arg),
                 struct icpustate *__restrict state,
                 unsigned int reason,
                 struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	if (reason == TASK_RPC_REASON_SYSCALL) {
		pid_t child_tid;
		child_tid = x86_clone_impl(state,
		                           sc_info->rsi_regs[0],                         /* clone_flags */
		                           (USER UNCHECKED void *)sc_info->rsi_regs[1],  /* child_stack */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_regs[2], /* parent_tidptr */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_regs[3], /* child_tidptr */
		                           get_user_gsbase(),
		                           sc_info->rsi_regs[0] & CLONE_SETTLS ? sc_info->rsi_regs[4]
		                                                               : get_user_fsbase());
		gpregs_setpax(&state->ics_gpregs, child_tid);
	}
	return state;
}

DEFINE_SYSCALL64_5(pid_t, clone,
                   syscall_ulong_t, flags,
                   USER UNCHECKED void *, child_stack,
                   USER UNCHECKED pid_t *, ptid,
                   USER UNCHECKED pid_t *, ctid,
                   uintptr_t, newtls) {
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	(void)flags;
	(void)child_stack;
	(void)ptid;
	(void)ctid;
	(void)newtls;
	task_schedule_user_rpc(THIS_TASK,
	                       &task_clone64_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CLONE && __x86_64__ */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_CLONE) || \
     (defined(__ARCH_WANT_SYSCALL_CLONE) && !defined(__x86_64__)))
PRIVATE struct icpustate *FCALL
task_clone32_rpc(void *UNUSED(arg),
                 struct icpustate *__restrict state,
                 unsigned int reason,
                 struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	if (reason == TASK_RPC_REASON_SYSCALL) {
		pid_t child_tid;
		child_tid = x86_clone_impl(state,
		                           sc_info->rsi_regs[0],                         /* clone_flags */
		                           (USER UNCHECKED void *)sc_info->rsi_regs[1],  /* child_stack */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_regs[2], /* parent_tidptr */
		                           (USER UNCHECKED pid_t *)sc_info->rsi_regs[4], /* child_tidptr */
		                           sc_info->rsi_regs[0] & CLONE_SETTLS ? sc_info->rsi_regs[3]
		                                                               : get_user_gsbase(),
		                           get_user_fsbase());
		gpregs_setpax(&state->ics_gpregs, child_tid);
	}
	return state;
}

DEFINE_SYSCALL32_5(pid_t, clone,
                   syscall_ulong_t, flags,
                   USER UNCHECKED void *, child_stack,
                   USER UNCHECKED pid_t *, ptid,
                   uintptr_t, newtls,
                   USER UNCHECKED pid_t *, ctid) {
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	(void)flags;
	(void)child_stack;
	(void)ptid;
	(void)ctid;
	(void)newtls;
	task_schedule_user_rpc(THIS_TASK,
	                       &task_clone32_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLONE || (__ARCH_WANT_SYSCALL_CLONE && !__x86_64__) */





/************************************************************************/
/* fork()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FORK
INTERN struct icpustate *FCALL
sys_fork_impl(struct icpustate *__restrict state) {
	pid_t child_tid;
	child_tid = x86_clone_impl(state,
	                           SIGCHLD,
	                           (USER UNCHECKED void *)icpustate_getusersp(state),
	                           NULL,
	                           NULL,
	                           get_user_gsbase(),
	                           get_user_fsbase());
	gpregs_setpax(&state->ics_gpregs, child_tid);
	return state;
}

PRIVATE struct icpustate *FCALL
task_fork_rpc(void *UNUSED(arg), struct icpustate *__restrict state,
              unsigned int reason, struct rpc_syscall_info const *UNUSED(sc_info)) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	if (reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return sys_fork_impl(state);
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
#endif /* __ARCH_WANT_SYSCALL_FORK */





/************************************************************************/
/* fork()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_VFORK
INTERN struct icpustate *FCALL
sys_vfork_impl(struct icpustate *__restrict state) {
	pid_t child_tid;
	child_tid = x86_clone_impl(state,
	                           CLONE_VM | CLONE_VFORK | SIGCHLD,
	                           (USER UNCHECKED void *)icpustate_getusersp(state),
	                           NULL,
	                           NULL,
	                           get_user_gsbase(),
	                           get_user_fsbase());
	gpregs_setpax(&state->ics_gpregs, child_tid);
	return state;
}

PRIVATE struct icpustate *FCALL
task_vfork_rpc(void *UNUSED(arg), struct icpustate *__restrict state,
               unsigned int reason, struct rpc_syscall_info const *UNUSED(sc_info)) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	if (reason != TASK_RPC_REASON_SYSCALL)
		return state;
	return sys_vfork_impl(state);
}

DEFINE_SYSCALL0(pid_t, vfork) {
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &task_vfork_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_VFORK */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C */
