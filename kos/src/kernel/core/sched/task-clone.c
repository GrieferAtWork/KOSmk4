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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_CLONE_C
#define GUARD_KERNEL_SRC_SCHED_TASK_CLONE_C 1

#include <kernel/compiler.h>

#include <kernel/fs/fs.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h> /* this_trampoline_node */
#include <kernel/mman/unmapped.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/signal.h>
#include <sched/task-clone.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>

#include <assert.h>
#include <string.h>

#if defined(__i386__) || defined(__x86_64__)
#include <kernel/x86/gdt.h>
#include <sched/x86/iobm.h>
#include <sched/x86/iopl.h>
#include <sched/x86/tss.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-compat.h>
#endif /* __i386__ || __x86_64__ */

DECL_BEGIN

typedef void (KCALL *pertask_clone_t)(struct task *__restrict result, uintptr_t flags);
INTDEF pertask_clone_t __kernel_pertask_clone_start[];
INTDEF pertask_clone_t __kernel_pertask_clone_end[];


/************************************************************************/
/* Per-task initialization template                                     */
/************************************************************************/
INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];

DATDEF ATTR_PERTASK struct mnode this_trampoline_node_ ASMNAME("this_trampoline_node");
DATDEF ATTR_PERTASK struct mpart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");
DATDEF ATTR_PERTASK struct mnode this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
DATDEF ATTR_PERTASK struct mnode this_kernel_stackguard_ ASMNAME("this_kernel_stackguard");
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

INTDEF NOBLOCK NONNULL((1)) void /* From "sched/task.c" */
NOTHROW(KCALL task_unmap_stack_and_free)(struct task *__restrict self);

#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
#define KERNEL_STACKSIZE_WITH_GUARD (CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE) + PAGESIZE)
#define IF_HAVE_STACK_GUARD(...)    __VA_ARGS__
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define LOCAL_INITIALIZE_STACKGUARD_BEFORE(result, mapaddr)                          \
	(FORTASK(result, this_kernel_stackguard_).mn_minaddr = (mapaddr),                \
	 FORTASK(result, this_kernel_stackguard_).mn_maxaddr = (mapaddr) + PAGESIZE - 1, \
	 (mapaddr) += PAGESIZE)
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
#ifdef __ARCH_STACK_GROWS_UPWARDS
#define LOCAL_INITIALIZE_STACKGUARD_AFTER(result, mapaddr)            \
	((mapaddr) += KERNEL_STACKSIZE,                                   \
	 FORTASK(result, this_kernel_stackguard_).mn_minaddr = (mapaddr), \
	 FORTASK(result, this_kernel_stackguard_).mn_maxaddr = (mapaddr) + PAGESIZE - 1)
#endif /* __ARCH_STACK_GROWS_UPWARDS */
#else /* CONFIG_HAVE_KERNEL_STACK_GUARD */
#define KERNEL_STACKSIZE_WITH_GUARD CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE)
#define IF_HAVE_STACK_GUARD(...)    /* nothing */
#endif /* !CONFIG_HAVE_KERNEL_STACK_GUARD */

#ifndef LOCAL_INITIALIZE_STACKGUARD_BEFORE
#define LOCAL_INITIALIZE_STACKGUARD_BEFORE(result, mapaddr) (void)0
#endif /* !LOCAL_INITIALIZE_STACKGUARD_BEFORE */

#ifndef LOCAL_INITIALIZE_STACKGUARD_AFTER
#define LOCAL_INITIALIZE_STACKGUARD_AFTER(result, mapaddr) (void)0
#endif /* !LOCAL_INITIALIZE_STACKGUARD_AFTER */

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
clone_set_child_tid(struct rpc_context *__restrict UNUSED(ctx), void *cookie) {
	ATOMIC_WRITE(*(USER CHECKED pid_t *)cookie, task_gettid());
}

PRIVATE NONNULL((1)) void FCALL
waitfor_vfork_completion(struct task *__restrict thread)
		THROWS(E_INTERRUPT) {
	while ((ATOMIC_READ(thread->t_flags) & TASK_FVFORK) != 0) {
		struct taskpid *pid;
		pid = FORTASK(thread, this_taskpid);
		assert(pid);
		task_connect(&pid->tp_changed);
		if unlikely((ATOMIC_READ(thread->t_flags) & TASK_FVFORK) == 0) {
			task_disconnectall();
			break;
		}

		/* Because we're doing a wait with a custom signal mask, we  have
		 * to  inject the current  system call's return  path with a call
		 * to `userexcept_sysret()' that will check for posix signal that
		 * may have become pending while we  were waiting with a mask  in
		 * which those signals were being suppressed.
		 *
		 * This always has to happen in the parent process of a vfork(2). */
		userexcept_sysret_inject_self();

		/* The specs say that we should ignore (mask) all POSIX
		 * signals until the  child indicate VFORK  completion.
		 *
		 * We do  this by  simply doing  the wait  using  a
		 * custom mask that has all signal bits set to `1'.
		 *
		 * s.a. `__ARCH_HAVE_SIGBLOCK_VFORK' */
		task_waitfor_with_sigmask(&kernel_sigmask_full.sm_mask);
	}
}


/* Clone the calling thread's signal mask into `result'. */
PRIVATE NONNULL((1, 2)) void KCALL
task_clone_sigmask(struct task *__restrict result,
                   struct task *__restrict caller,
                   uintptr_t clone_flags) {
	/* Clone the current signal mask. */
	(void)clone_flags;
	assert(arref_ptr(&FORTASK(result, this_kernel_sigmask)) == &kernel_sigmask_empty);
#ifdef CONFIG_HAVE_USERPROCMASK
	if (caller->t_flags & TASK_FUSERPROCMASK) {
		struct userprocmask *um;
		um = FORTASK(caller, this_userprocmask_address);
		if (!(clone_flags & CLONE_VM)) {
			/* Special case:
			 * ```
			 *  During a call to fork() or clone() (w/o CLONE_VM), the parent
			 *  thread's TASK_FUSERPROCMASK attribute is inherited unconditionally.
			 * ```
			 */
inherit_parent_userprocmask:
			FORTASK(result, this_userprocmask_address) = um;
			result->t_flags |= TASK_FUSERPROCMASK;
			/* The static initialization for the kernel-space `this_kernel_sigmask' is sufficient in this case! */
			/*FORTASK(result, this_kernel_sigmask) = ARREF_INIT(&kernel_sigmask_empty);*/
		} else if (clone_flags & CLONE_VFORK) {
			/* Special case:
			 * ```
			 *  During a vfork(2), where the parent thread has the TASK_FUSERPROCMASK
			 *  attribute set [...]
			 *  The  child  thread is  started  with the  `TASK_FUSERPROCMASK'  attribute set,
			 *  which will be cleared the normal way once the child performs a successful call
			 *  to either exec(2) or  _Exit(2), at which pointer  the process will once  again
			 *  wake up.
			 * ```
			 */
			goto inherit_parent_userprocmask;
		} else {
			/* Special case:
			 * ```
			 *  During a call to clone(CLONE_VM), where the parent is a userprocmask  thread,
			 *  prior to clone() returning in either the parent or child, the parent thread's
			 *  user-space `pm_sigmask' is copied into  the kernel-space buffer of the  child
			 *  thread, while the child thread will start with TASK_FUSERPROCMASK=0.
			 * ```
			 *
			 * In other words: We must copy `um->pm_sigmask' into `FORTASK(result, this_kernel_sigmask)'
			 */
			struct kernel_sigmask *new_thread_mask;
			new_thread_mask = (struct kernel_sigmask *)kmalloc(sizeof(struct kernel_sigmask),
			                                                   GFP_NORMAL);
			TRY {
				USER UNCHECKED sigset_t *parent_umask;
				parent_umask = ATOMIC_READ(um->pm_sigmask);
				validate_readable(parent_umask, sizeof(sigset_t));
				memcpy(&new_thread_mask->sm_mask, parent_umask, sizeof(sigset_t));
			} EXCEPT {
				kfree(new_thread_mask);
				RETHROW();
			}
			new_thread_mask->sm_refcnt = 1;
			new_thread_mask->sm_share  = 1;
			/* Initialize the new  thread's signal mask  with
			 * the copy of the parent's current userprocmask. */
			arref_init(&FORTASK(result, this_kernel_sigmask), new_thread_mask);
		}
	} else
#endif /* CONFIG_HAVE_USERPROCMASK */
	{
		if (sigmask_kernel_getrd() == &kernel_sigmask_empty) {
			/* Nothing to do here! */
		} else {
			REF struct kernel_sigmask *mask;
			struct kernel_sigmask_arref *maskref;
			maskref = &PERTASK(this_kernel_sigmask);
			mask    = arref_get(maskref);
			assert(mask != &kernel_sigmask_empty);
			ATOMIC_INC(mask->sm_share);
			COMPILER_WRITE_BARRIER();
			arref_init(&FORTASK(result, this_kernel_sigmask), mask); /* Inherit reference. */
			COMPILER_WRITE_BARRIER();
		}
	}
}


/* Clone the calling thread's signal handlers into `result'. */
PRIVATE NONNULL((1, 2)) void KCALL
task_clone_sighand(struct task *__restrict result,
                   struct task *__restrict caller,
                   uintptr_t clone_flags) {
	if (clone_flags & CLONE_SIGHAND) {
		/* Must share signal handlers. */
		REF struct sighand_ptr *myptr;
		myptr = FORTASK(caller, this_sighand_ptr);
		if (!myptr) {
			/* Must allocate the signal handler table pointer so we can share it! */
			myptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
			                                          GFP_NORMAL);
			myptr->sp_refcnt = 2;
			atomic_rwlock_init(&myptr->sp_lock);
			myptr->sp_hand = NULL;
			assert(!FORTASK(caller, this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, myptr);
		} else {
			incref(myptr);
		}
		FORTASK(result, this_sighand_ptr) = myptr;
	} else {
		/* Set signal handlers of the thread as a copy of the caller. */
		struct sighand_ptr *myptr;
		myptr = FORTASK(caller, this_sighand_ptr);
		if (!myptr) {
			/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
		} else {
			REF struct sighand_ptr *newptr;
			struct sighand *myhand;
			newptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
			                                           GFP_NORMAL);
again_lock_myptr:
			TRY {
				sync_read(myptr);
				COMPILER_READ_BARRIER();
				myhand = myptr->sp_hand;
				COMPILER_READ_BARRIER();
				if (!myhand) {
					/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
					sync_endread(myptr);
					kfree(newptr);
					newptr = NULL;
				} else {
					if (!sync_trywrite(myhand)) {
						sync_endread(myptr);
						task_yield();
						goto again_lock_myptr;
					}
					sync_endread(myptr);
					sighand_incshare(myhand);
					sync_endwrite(myhand);

					/* Still share the handler table as copy-on-write. */
					atomic_rwlock_init(&newptr->sp_lock);
					newptr->sp_refcnt = 1;
					newptr->sp_hand = myhand;
				}
			} EXCEPT {
				kfree(newptr);
				RETHROW();
			}
			FORTASK(result, this_sighand_ptr) = newptr;
		}
	}
}



#if defined(__i386__) || defined(__x86_64__)
/* Check  if `self' is currently mapped with  write permissions within the calling CPU.
 * If  this is the case, get rid of those write permissions, but keep the ioperm bitmap
 * itself mapped as read-only (used to implement copy-on-write during clone() in  order
 * to prevent a race condition when user-space calls `clone()' followed by  `ioperm()',
 * where we need  to prevent  the `ioperm()' call  from potentially  modifying the  I/O
 * permissions bitmap of the child thread, which it otherwise would if the child thread
 * got scheduled on a different CPU, or hasn't yet received its first quantum) */
LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL x86_ioperm_bitmap_unset_write_access)(struct task *__restrict caller,
                                                    struct ioperm_bitmap *__restrict self) {
	pflag_t was       = PREEMPTION_PUSHOFF();
	struct cpu *mycpu = caller->t_cpu;
	if (FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == self) {
		/* Re-map, and only include read permissions. */
		pagedir_map(FORCPU(mycpu, thiscpu_x86_iob),
		            2 * PAGESIZE,
		            self->ib_pages,
		            PAGEDIR_PROT_READ);
	}
	PREEMPTION_POP(was);
}
#endif /* __i386__ || __x86_64__ */



/* High-level implementation for the `clone(2)' system call.
 * @param: init_state:    The CPU state of the thead that called `clone(2)'
 * @param: clone_flags:   Set of `CLONE_*' (as defined in <sched.h>)
 * @param: parent_tidptr: [valid_if(CLONE_PARENT_SETTID)]
 *                        Store child TID here in parent process
 * @param: child_tidptr:  [valid_if(CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID)]
 *                        Store child TID here in child process
 * @param: ARCH_CLONE__PARAMS: Additional, arch-specific parameters */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *KCALL
task_clone(struct icpustate const *__restrict init_state,
           uintptr_t clone_flags,
           USER UNCHECKED pid_t *parent_tidptr,
           USER UNCHECKED pid_t *child_tidptr
           ARCH_CLONE__PARAMS)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct task *result;
	struct task *caller = THIS_TASK;

	/* Validate arguments. */
	if (clone_flags & CLONE_PARENT_SETTID)
		validate_writable(parent_tidptr, sizeof(*parent_tidptr));
	if (clone_flags & (CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID))
		validate_writable(child_tidptr, sizeof(*child_tidptr));

	/* Allocate a new task structure. */
	{
		heapptr_t resptr;
		resptr = heap_alloc(&kernel_locked_heap,
		                    (size_t)__kernel_pertask_size,
		                    GFP_LOCKED | GFP_PREFLT);
		result = (REF struct task *)heapptr_getptr(resptr);
		memcpy(result, __kernel_pertask_start, (size_t)__kernel_pertask_size);
		result->t_heapsz = heapptr_getsiz(resptr);
	}

	TRY {
		byte_t *mapaddr;

#if 1 /* XXX: Remove me (only here to force & verify use of IPI mechanisms in multi-core situations)
       *      Basically: Only here to test a whole bunch of stuff... */
		if (cpu_count > 1) {
			static unsigned int nextcpu = 0;
			result->t_cpu = cpu_vector[(nextcpu++) % cpu_count];
		}
#endif
		/* Initialize the new task. */
		_task_init_relocations(result);

		/* Assign the thread's mman */
		assert(result->t_mman == NULL);
		if (clone_flags & (CLONE_VM | CLONE_VFORK)) {
			/* The mman is being shared */
			result->t_mman = incref(caller->t_mman);
			/* Set the VFORK flag to cause the thread to execute in VFORK-mode.
			 * This must be done before we  start making the thread visible  to
			 * other kernel components, since this also affects things such  as
			 * the thread's effective signal mask. */
			if (clone_flags & CLONE_VFORK)
				result->t_flags |= TASK_FVFORK;
		} else {
			/* The new thread has its own mman */
			result->t_mman = mman_fork();
		}

		/* Allocate a kernel stack for the new thread. */
		assert(FORTASK(result, this_kernel_stackpart_).mp_state == MPART_ST_VOID);
		assert(FORTASK(result, this_kernel_stacknode_).mn_minaddr == (byte_t *)MAP_FAILED);
		mpart_ll_allocmem(&FORTASK(result, this_kernel_stackpart_),
		                  KERNEL_STACKSIZE / PAGESIZE);

		/* Map the new thread's kernel stack. */
		mman_lock_acquire(&mman_kernel);
		KERNEL_STACKSIZE_WITH_GUARD;
		mapaddr = (byte_t *)mman_findunmapped(&mman_kernel,
		                                      MHINT_GETADDR(KERNEL_MHINT_KERNSTACK),
		                                      KERNEL_STACKSIZE_WITH_GUARD,
		                                      MHINT_GETMODE(KERNEL_MHINT_KERNSTACK));
		if unlikely(mapaddr == (byte_t *)MAP_FAILED) {
			struct ccinfo cc;
			for (;;) {
				mman_lock_release(&mman_kernel);
				ccinfo_init(&cc, GFP_NORMAL, KERNEL_STACKSIZE_WITH_GUARD);
				system_cc_virtual_memory(&cc);
				mman_lock_acquire(&mman_kernel);
				mapaddr = (byte_t *)mman_findunmapped(&mman_kernel,
				                                      MHINT_GETADDR(KERNEL_MHINT_KERNSTACK),
				                                      KERNEL_STACKSIZE_WITH_GUARD,
				                                      MHINT_GETMODE(KERNEL_MHINT_KERNSTACK));
				if (mapaddr != (byte_t *)MAP_FAILED)
					break;
			}
		}
		LOCAL_INITIALIZE_STACKGUARD_BEFORE(result, mapaddr);
		FORTASK(result, this_kernel_stacknode_).mn_minaddr = mapaddr;
		FORTASK(result, this_kernel_stacknode_).mn_maxaddr = mapaddr + KERNEL_STACKSIZE - 1;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		if unlikely(!pagedir_kernelprepare(mapaddr, KERNEL_STACKSIZE)) {
			mman_lock_release(&mman_kernel);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		LOCAL_INITIALIZE_STACKGUARD_AFTER(result, mapaddr);
		mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
		IF_HAVE_STACK_GUARD(mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stackguard_)));

		/* Map the trampoline node. */
		mapaddr = (byte_t *)mman_findunmapped(&mman_kernel,
		                                      MHINT_GETADDR(KERNEL_MHINT_TRAMPOLINE), PAGESIZE,
		                                      MHINT_GETMODE(KERNEL_MHINT_TRAMPOLINE));
		if unlikely(mapaddr == (byte_t *)MAP_FAILED) {
			struct ccinfo cc;
			for (;;) {
				pagedir_kernelunprepare(FORTASK(result, this_kernel_stacknode_).mn_minaddr, KERNEL_STACKSIZE);
				mman_mappings_removenode(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
				IF_HAVE_STACK_GUARD(mman_mappings_removenode(&mman_kernel, &FORTASK(result, this_kernel_stackguard_)));
again_release_kernel_and_cc:
				mman_lock_release(&mman_kernel);
				FORTASK(result, this_kernel_stacknode_).mn_minaddr = (byte_t *)MAP_FAILED;
				ccinfo_init(&cc, GFP_NORMAL, KERNEL_STACKSIZE_WITH_GUARD + PAGESIZE);
				system_cc_virtual_memory(&cc);
				mman_lock_acquire(&mman_kernel);
				mapaddr = (byte_t *)mman_findunmapped(&mman_kernel,
				                                      MHINT_GETADDR(KERNEL_MHINT_KERNSTACK),
				                                      KERNEL_STACKSIZE_WITH_GUARD,
				                                      MHINT_GETMODE(KERNEL_MHINT_KERNSTACK));
				if unlikely(mapaddr == (byte_t *)MAP_FAILED)
					goto again_release_kernel_and_cc;
				LOCAL_INITIALIZE_STACKGUARD_BEFORE(result, mapaddr);
				FORTASK(result, this_kernel_stacknode_).mn_minaddr = mapaddr;
				FORTASK(result, this_kernel_stacknode_).mn_maxaddr = mapaddr + KERNEL_STACKSIZE - 1;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
				if unlikely(!pagedir_kernelprepare(mapaddr, KERNEL_STACKSIZE)) {
					mman_lock_release(&mman_kernel);
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
				}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
				LOCAL_INITIALIZE_STACKGUARD_AFTER(result, mapaddr);
				mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
				IF_HAVE_STACK_GUARD(mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stackguard_)));
				mapaddr = (byte_t *)mman_findunmapped(&mman_kernel,
				                                      MHINT_GETADDR(KERNEL_MHINT_TRAMPOLINE), PAGESIZE,
				                                      MHINT_GETMODE(KERNEL_MHINT_TRAMPOLINE));
				if (mapaddr != (byte_t *)MAP_FAILED)
					break;
			}
		}
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		if unlikely(!pagedir_kernelprepareone(mapaddr)) {
			pagedir_kernelunprepare(FORTASK(result, this_kernel_stacknode_).mn_minaddr, KERNEL_STACKSIZE);
			mman_mappings_removenode(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
			IF_HAVE_STACK_GUARD(mman_mappings_removenode(&mman_kernel, &FORTASK(result, this_kernel_stackguard_)));
			mman_lock_release(&mman_kernel);
			THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		FORTASK(result, this_trampoline_node_).mn_minaddr = mapaddr;
		FORTASK(result, this_trampoline_node_).mn_maxaddr = mapaddr + PAGESIZE - 1;
		mman_mappings_insert(&mman_kernel, &FORTASK(result, this_trampoline_node_));

		/* Map the stack into memory */
		mpart_mmap_force(&FORTASK(result, this_kernel_stackpart_),
		                 FORTASK(result, this_kernel_stacknode_).mn_minaddr,
		                 KERNEL_STACKSIZE, 0, PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
		mman_lock_release(&mman_kernel);

		/* Initialize the initial `scpustate' to-be executed by the thread. */
		{
			struct scpustate *child_state;
			KERNEL byte_t *kernel_stack;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			kernel_stack = FORTASK(result, this_kernel_stacknode_).mn_maxaddr + 1;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			kernel_stack = FORTASK(result, this_kernel_stacknode_).mn_minaddr;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */

			/* Construct the initial scheduler CPU state from the caller-given `init_state' */
#ifdef __x86_64__
			child_state = icpustate_to_scpustate_p_ex(init_state,
			                                          kernel_stack,
			                                          x86_child_gsbase,
			                                          x86_child_fsbase,
			                                          __rdgs(),
			                                          __rdfs(),
			                                          __rdes(),
			                                          __rdds());
#else /* __x86_64__ */
			child_state = icpustate_to_scpustate_p(init_state, kernel_stack);
#endif /* !__x86_64__ */

			/* Do additional, arch-specific initialization */
#if defined(__i386__) || defined(__x86_64__)
			/* Assign the given stack pointer for the new thread. */
			scpustate_setuserpsp(child_state, (uintptr_t)x86_child_psp);

			/* Reset iopl() for the child thread/process */
			if ((clone_flags & CLONE_THREAD) ? !x86_iopl_keep_after_clone
			                                 : !x86_iopl_keep_after_fork)
				child_state->scs_irregs.ir_Pflags &= ~EFLAGS_IOPLMASK;
#endif /* __i386__ || __x86_64__ */
#if defined(__i386__) && !defined(__x86_64__)
			FORTASK(result, this_x86_user_gsbase) = x86_child_gsbase;
			FORTASK(result, this_x86_user_fsbase) = x86_child_fsbase;
#endif /* __i386__ && !__x86_64__ */

			/* Have `fork(2)' and `clone(2)' return `0' in the child thread/process */
			scpustate_setreturn(child_state, 0);

			/* Inject  an  RPC  for  saving  the  child's  TID  within  the  given  pointer
			 * This always needs to be done in the context of the child, so that exceptions
			 * during the write are handled in the proper context, as well as in regards to
			 * the child actually existing in a  different VM when `CLONE_VM' isn't  given. */
			if (clone_flags & CLONE_CHILD_SETTID)
				child_state = task_asyncrpc_push(child_state, &clone_set_child_tid, child_tidptr);

			/* Apply some finalizing transformations to `child_state' */
			_task_init_arch_sstate(result, caller, &child_state);

			/* Save the CPU context with which the child will launch */
			FORTASK(result, this_sstate) = child_state;
		}

		if (clone_flags & CLONE_CHILD_CLEARTID)
			FORTASK(result, this_tid_address) = child_tidptr; /* `set_tid_address(child_tidptr)' */

		/************************************************************************/
		/* CLONE THREAD CONTEXT                                                 */
		/************************************************************************/

		/* Clone user-space exception handler. */
		memcpy(&FORTASK(result, this_user_except_handler),
		       &FORTASK(caller, this_user_except_handler),
		       sizeof(struct user_except_handler));

		/* Clone the calling thread's FS context */
		{
			struct fs *result_fs = FORTASK(caller, this_fs);
			if (clone_flags & CLONE_FS) {
				result_fs = incref(result_fs);
			} else {
				result_fs = fs_clone(result_fs, (clone_flags & CLONE_NEWNS) != 0);
			}
			FORTASK(result, this_fs) = result_fs;
		}

		/* Clone credentials */
		{
			struct cred *result_cred = FORTASK(caller, this_cred);
			if (clone_flags & CLONE_CRED) {
				result_cred = incref(result_cred);
			} else {
				result_cred = cred_clone(result_cred);
			}
			FORTASK(result, this_cred) = result_cred; /* Inherit reference */
		}

		/* Clone the calling thread's signal mask */
		task_clone_sigmask(result, caller, clone_flags);

		/* Clone the calling thread's signal handlers */
		task_clone_sighand(result, caller, clone_flags);

		/* Clone the calling thread's open file descriptors */
		{
			struct handle_manager *result_hman;
			result_hman = FORTASK(caller, this_handle_manager);
			if (clone_flags & CLONE_FILES) {
				result_hman = incref(result_hman);
			} else {
				result_hman = handle_manager_clone(result_hman);
			}
			FORTASK(result, this_handle_manager) = result_hman; /* Inherit reference */
		}

		/* On x86, the ioperm() permissions bitmap is always inherited by child
		 * threads! Only the  iopl() level  is not inherited  in certain  cases
		 * (as configurable via `/proc/sys/x86/keepiopl/(clone|exec|fork)') */
#if defined(__i386__) || defined(__x86_64__)
		{
			struct ioperm_bitmap *iob;
			iob = FORTASK(caller, this_x86_ioperm_bitmap);
			/* `unlikely', since this isn't really  something
			 * that modern applications commonly make use of! */
			if unlikely(iob) {
				assert(iob->ib_share >= 1);
				incref(iob);
				/* Unset write-access if this is the first time the IOB is getting shared. */
				if (ATOMIC_FETCHINC(iob->ib_share) == 1)
					x86_ioperm_bitmap_unset_write_access(caller, iob);
				FORTASK(result, this_x86_ioperm_bitmap) = iob;
			}
		}
#endif /* __i386__ || __x86_64__ */

		/************************************************************************/
		/* MAKE NEW THREAD GLOBALLY VISIBLE                                     */
		/************************************************************************/

		/* NOTE: The  act of making a new thread visible must be done in such a
		 *       way that we are holding all  relevant longs at the same  time,
		 *       and while still holding all of them, we check for pending RPCs
		 *       in the calling thread. If there are any, we release all  locks
		 *       and serve them before starting over from scratch.
		 * -> This way of doing things is required to ensure that we'll never
		 *    spawn additional threads while there might be a signal  pending
		 *    with the capacity of killing us.
		 *    The reason why we have to interlock that possibility with holding
		 *    locks  to all  thread lists into  which the new  thread should be
		 *    added, is so someone sending SIGKILL to a process group, can live
		 *    with the knowledge that none of  the processes are able to  spawn
		 *    more  processes that might continue to live even after the signal
		 *    was handled by all existing onces being killed.
		 *    This works because anyone sending such a signal would  necessarily
		 *    have to acquire the same locks we acquire to register a new thread
		 *    globally, meaning that only when  holding all of those locks,  and
		 *    also making sure that there's no chance of us actually being meant
		 *    to die right  now, can we  say for certain  that we're allowed  to
		 *    create  a  new  thread, rather  than  do something  else,  such as
		 *    handling a signal. */

		/* TODO */

	} EXCEPT {
		/* Cleanup on error. */
#if defined(__i386__) || defined(__x86_64__)
		if unlikely(FORTASK(result, this_x86_ioperm_bitmap)) {
			assert(FORTASK(result, this_x86_ioperm_bitmap)->ib_share >= 1);
			ATOMIC_DEC(FORTASK(result, this_x86_ioperm_bitmap)->ib_share);
			decref_likely(FORTASK(result, this_x86_ioperm_bitmap));
		}
#endif /* __i386__ || __x86_64__ */
		xdecref(FORTASK(result, this_handle_manager));
		xdecref(FORTASK(result, this_sighand_ptr));
		if (arref_ptr(&FORTASK(result, this_kernel_sigmask)) != &kernel_sigmask_empty)
			decref(arref_ptr(&FORTASK(result, this_kernel_sigmask)));
		xdecref(FORTASK(result, this_cred));
		xdecref(FORTASK(result, this_fs));
		if (result->t_mman) {
			if likely(LIST_ISBOUND(result, t_mman_tasks)) {
				mman_threadslock_acquire(result->t_mman);
				if likely(LIST_ISBOUND(result, t_mman_tasks))
					LIST_REMOVE(result, t_mman_tasks);
				mman_threadslock_release(result->t_mman);
			}
			decref(result->t_mman);
		}
		if (FORTASK(result, this_kernel_stacknode_).mn_minaddr != (byte_t *)MAP_FAILED) {
			task_unmap_stack_and_free(result);
		} else {
			if (FORTASK(result, this_kernel_stackpart_).mp_state != MPART_ST_VOID)
				mpart_ll_ccfreemem(&FORTASK(result, this_kernel_stackpart_));
			heap_free(&kernel_locked_heap, result, result->t_heapsz, GFP_LOCKED);
		}
		RETHROW();
	}


	/* At this point the new thread is fully initialized and visible.
	 * The  only thing that's still left to do is to start it (and in
	 * the case of vfork(): wait for it to exit(2) or exec(2)). */
	TRY {
#if 1 /* TODO: Remove me */
		/* Allocate the PID descriptor for the new thread. */
		if (clone_flags & CLONE_NEWPID) {
			REF struct pidns *ns;
			ns = pidns_alloc(FORTASK(caller, this_taskpid)->tp_pidns);
			FINALLY_DECREF_UNLIKELY(ns);
			task_setpid(result, ns, 0);
		} else {
			task_setpid(result, THIS_PIDNS, 0);
		}

		/* TODO: Remember `flags & CSIGNAL' as signal to-be send on exit! */
		if (clone_flags & CLONE_THREAD) {
			/* Add to the same process as the caller */
			task_setthread(result, caller);
		} else if (clone_flags & CLONE_PARENT) {
			REF struct task *my_parent;
			my_parent = task_getprocessparent_of(caller);
			FINALLY_XDECREF_UNLIKELY(my_parent);
			/* Inherit parent, group & session of the caller */
			task_setprocess(result, my_parent, caller, caller);
		} else {
			/* Inherit group & session of the caller; set caller as parent */
			task_setprocess(result, caller, caller, caller);
		}

		/* Already pre-detach the thread if instructed to */
		if (clone_flags & CLONE_DETACHED)
			task_detach(result);

		/* Insert the new task into its mman's thread-list */
		mman_threadslock_acquire(result->t_mman);
		LIST_INSERT_HEAD(&result->t_mman->mm_threads, result, t_mman_tasks);
		mman_threadslock_release(result->t_mman);

		/* Write-back the new thread's TID to the caller-given  memory
		 * location within the calling process. TODO: This also has to
		 * happen whilst interlocked with other systems which are able
		 * to  make the thread visible. In the case where the pointed-
		 * to  memory  is  VIO,   the  operation  must  happen   like:
		 * >>    lock_pid_system();
		 * >>again:
		 * >>    ...
		 * >>    pid_t cpid = NEXT_FREE_PID;
		 * >>    unlock_pid_system();
		 * >>    *parent_tidptr = cpid;
		 * >>    lock_pid_system();
		 * >>    if (cpid != NEXT_FREE_PID)
		 * >>        goto again;
		 * >>    ...
		 * >>    unlock_pid_system();
		 */
		if (clone_flags & CLONE_PARENT_SETTID)
			ATOMIC_WRITE(*parent_tidptr, task_gettid_of(result));
#endif

		/* Deal with vfork() */
		if (clone_flags & CLONE_VFORK) {
#ifdef CONFIG_HAVE_USERPROCMASK
			/* Special case for when the parent thread was using USERPROCMASK.
			 * In this case we have to save+restore both the contents of--, as
			 * well  as the pointer to the signal  mask as it was active prior
			 * to the vfork() call being made.
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

				TRY {
					/* Actually start execution of the newly created thread. */
					task_start(result);

					/* Wait for the thread to clear its VFORK flag. */
					waitfor_vfork_completion(result);
				} EXCEPT {
					{
						NESTED_EXCEPTION;
						memcpy(user_sigmask, &saved_user_sigset, sizeof(sigset_t));
						ATOMIC_WRITE(um->pm_sigmask, user_sigmask);
					}
					RETHROW();
				}

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

				/* Wait for the thread to clear its VFORK flag. */
				waitfor_vfork_completion(result);
			}
		} else {
			/* Simply start execution of the newly created thread. */
			task_start(result);
		}
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	return result;
}


/* Per-task relocations */
INTDEF uintptr_t __kernel_pertask_relocations_start[];
INTDEF uintptr_t __kernel_pertask_relocations_end[];

/* Initialize task relocations, as defined by `DEFINE_PERTASK_RELOCATION()' */
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _task_init_relocations)(struct task *__restrict self) {
	uintptr_t *p_offset;
	/* Apply relocations */
	for (p_offset = __kernel_pertask_relocations_start;
	     p_offset < __kernel_pertask_relocations_end; ++p_offset) {
		uintptr_t *reladdr;
		reladdr = (uintptr_t *)((byte_t *)self + *p_offset);
		*reladdr += (uintptr_t)self;
	}

	/* Assert that relocations were applied correctly. */
	assert(self->t_self == self);
	assert(FORTASK(self, this_kernel_stacknode_).mn_part == &FORTASK(self, this_kernel_stackpart_));
	assert(FORTASK(self, this_kernel_stacknode_).mn_link.le_prev == &FORTASK(self, this_kernel_stackpart_).mp_share.lh_first);
	assert(FORTASK(self, this_kernel_stackpart_).mp_share.lh_first == &FORTASK(self, this_kernel_stacknode_));
	assert(FORTASK(self, this_connections) == &FORTASK(self, this_root_connections));
	assert(FORTASK(self, this_root_connections).tcs_thread == self);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_CLONE_C */
