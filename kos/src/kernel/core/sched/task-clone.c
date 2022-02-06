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
#include <kernel/mman/nopf.h>
#include <kernel/mman/phys.h> /* this_trampoline_node */
#include <kernel/mman/unmapped.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sigmask.h>
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
#ifdef CONFIG_USE_NEW_GROUP
		{
			/* Figure out which PID namespace(s) the new thread should appear in. */
			REF struct taskpid *result_pid;
			REF struct taskpid *owner_pid;
			struct procctl *owner_ctl;
			REF struct pidns *result_pidns, *ns_iter;
			struct taskpid *caller_pid;
			struct procctl *result_ctl     = NULL;
			REF struct procgrp *result_grp = NULL;
#ifdef CONFIG_HAVE_USERPROCMASK
			sigset_t caller_sigmask;
			bool have_caller_sigmask = false;
#endif /* CONFIG_HAVE_USERPROCMASK */

			/* Figure out the caller's PID relationship */
			caller_pid   = task_gettaskpid_of(caller);
			result_pidns = caller_pid->tp_ns;

			/* Figure out what will be the new thread's top-level PID namespace. */
again_assign_pid:
			if unlikely(clone_flags & CLONE_NEWPID) {
				result_pidns = pidns_alloc(result_pidns);
			} else {
				result_pidns = incref(result_pidns);
			}

			/* Allocate a PID descriptor for the new thread. */
			TRY {
				result_pid = _taskpid_alloc(result_pidns);
			} EXCEPT {
				decref_unlikely(result_pidns);
				RETHROW();
			}
			result_pid->tp_refcnt = 1;
			awref_init(&result_pid->tp_thread, result);
			sig_init(&result_pid->tp_changed);
			result_pid->tp_status = 0;
			result_pid->tp_SIGCLD = clone_flags & CSIGNAL;
			if (result_pid->tp_SIGCLD == 0)
				result_pid->tp_SIGCLD = SIGCLD;
			result_pid->tp_ns             = result_pidns; /* Inherit reference */
			FORTASK(result, this_taskpid) = result_pid;   /* Inherit reference */

			/* Allocate process information. */
			if (clone_flags & CLONE_THREAD) {
				/* Simply case: create another thread within the calling process. */
				owner_pid = taskpid_getprocpid(caller_pid);
				assert(caller_pid->tp_pctl == owner_pid->tp_pctl);
				result_pid->tp_proc = owner_pid;
				ATOMIC_ADD(owner_pid->tp_refcnt, 2); /* +1: `owner_pid', +1: `result_pid->tp_proc' */
				result_pid->tp_pctl = owner_pid->tp_pctl;
				if (clone_flags & CLONE_DETACHED)
					result->t_flags |= TASK_FDETACHED; /* Auto-reap on exit */
			} else {
				REF struct task *parent_proc;

				/* Allocate a new process controller. */
				TRY {
					result_ctl = _procctl_alloc();
				} EXCEPT {
					decref_unlikely(result_pidns);
					_taskpid_free(result_pid);
					RETHROW();
				}
#ifndef CONFIG_NO_SMP
				atomic_lock_init(&result_ctl->pc_thrds_lock);
#endif /* !CONFIG_NO_SMP */
				LIST_INIT(&result_ctl->pc_thrds_list);
				atomic_rwlock_init(&result_ctl->pc_chlds_lock);
				LIST_INIT(&result_ctl->pc_chlds_list);
				sig_init(&result_ctl->pc_chld_changed);
				/*result_ctl->pc_parent = ...;*/ /* Initialized next */
				atomic_rwlock_init(&result_ctl->pc_sig_lock);
				SLIST_INIT(&result_ctl->pc_sig_list);
				sig_init(&result_ctl->pc_sig_more);
				result_grp = taskpid_getprocgrp(caller_pid);
				arref_init(&result_ctl->pc_grp, result_grp);
				/*result_ctl->pc_grpmember = ...;*/ /* Initialized below */

				/* Select who should be the process's parent. */
				if (clone_flags & CLONE_DETACHED) {
					/* Launch in detached state, meaning /bin/init is parent. */
use_boottask_as_parent:
					parent_proc = incref(&boottask);
				} else if (clone_flags & CLONE_PARENT) {
					/* Re-use parent of calling process as parent of child process */
					parent_proc = taskpid_getparentprocess(caller_pid);
					if unlikely(ATOMIC_READ(parent_proc->t_flags) & (TASK_FTERMINATING |
					                                                 TASK_FTERMINATED)) {
						/* The calling process's parent has already terminated.
						 * -> Simply use `boottask' instead, emulating what would
						 *    have been done  by `parent_proc' in  `task_exit()'. */
						decref_unlikely(parent_proc);
						goto use_boottask_as_parent;
					}
				} else {
					/* Using calling process as parent. */
					parent_proc = taskpid_gettask(taskpid_getprocpid(caller_pid));
					if unlikely(!parent_proc || (ATOMIC_READ(parent_proc->t_flags) & (TASK_FTERMINATING |
					                                                                  TASK_FTERMINATED))) {
						/* Current process has exited. */
						arref_fini(&result_ctl->pc_grp);
						_procctl_free(result_ctl);
						_taskpid_free(result_pid);
						decref_unlikely(result_pidns);
						_task_serve(); /* Serve main thread's exit RPC */
						/* Really shouldn't get here! */
						THROW(E_EXIT_THREAD, taskpid_getprocpid(caller_pid)->tp_status);
					}
				}
				owner_pid = incref(task_gettaskpid_of(parent_proc));
				arref_init(&result_ctl->pc_parent, parent_proc); /* Inherit reference */
				result_pid->tp_proc = result_pid;                /* New process */
				result_pid->tp_pctl = result_ctl;                /* Process controller */
				incref(result_grp);                              /* Keep around a second reference! */
			}

			FINALLY_DECREF_UNLIKELY(owner_pid);
			owner_ctl = taskpid_getprocctl(owner_pid);

			/* Acquire all of the relevant locks in order to make the new thread visible. */
again_acquire_locks:
			TRY {
				ns_iter = pidns_trywriteall(result_pidns);
				if unlikely(ns_iter) {
					pidns_waitwrite(ns_iter);
					goto again_acquire_locks;
				}
				if (result_ctl) {
					if (!procctl_chlds_trywrite(owner_ctl)) {
						pidns_endwriteall(result_pidns);
						procctl_chlds_waitwrite(owner_ctl);
						goto again_acquire_locks;
					}
					if unlikely(!procgrp_memb_trywrite(result_grp)) {
						procctl_chlds_endwrite(owner_ctl);
						pidns_endwriteall(result_pidns);
						procgrp_memb_waitwrite(result_grp);
						goto again_acquire_locks;
					}
				}

				/* Allocate PIDs for `result_pid' within all namespaces it should appear in. */
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
				if (!pidns_allocpids(result_pid)) {
err_pidns_allocpids_failed:
					if (result_ctl != NULL) {
						_procgrp_memb_endwrite(result_grp);
						_procctl_chlds_endwrite(owner_ctl);
						procgrp_memb_reap(result_grp);
						procctl_chlds_reap(owner_ctl);
					}
					pidns_endwriteall(result_pidns);
					THROW(E_BADALLOC); /* XXX: Custom error sub-class */
				}
#else /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
				pidns_allocpids(result_pid);
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */

				if (clone_flags & CLONE_PARENT_SETTID) {
					/* Write-back  the child TID to the parent  process. Because this is a memory
					 * access, we have to be very careful when it comes to writing to VIO memory.
					 * As  such, we have to interlock this write with all of locks above, as well
					 * as the allocation of (at least) the PID within the initial namespace. */
					pid_t ctid;
					ctid = taskpid_getnstid(result_pid, caller_pid->tp_ns);
again_write_ctid_to_parent_tidptr:
					if (!write_nopf(parent_tidptr, ctid)) {
						pid_t new_ctid;
						/* Complicated case: writing to the user-given address faults. - This can
						 * happen for VIO memory,  if the pointer is  actually faulty, or if  the
						 * associated page simply hasn't been allocated, yet.
						 *
						 * Whatever the case be, we have to release locks, repeat the write, then
						 * re-acquire locks and allocate PIDs again. - Afterwards, we check if we
						 * were  able to allocate the `ctid', and if not, we try to write the new
						 * value back to user-space once again.
						 *
						 * This cycle continues until the ctid written in a previous cycle matches
						 * what would have to be written in the next, the calling thread  receives
						 * an interrupt, or the `write_nopf()' above succeeds. */
						if (result_ctl != NULL) {
							_procgrp_memb_endwrite(result_grp);
							_procctl_chlds_endwrite(owner_ctl);
							procgrp_memb_reap(result_grp);
							procctl_chlds_reap(owner_ctl);
						}
						pidns_endwriteall(result_pidns);

						/* Do a proper write, which is allowed to fault or be VIO. */
						ATOMIC_WRITE(*parent_tidptr, ctid);
						task_serve();

						/* Re-acquire locks. */
again_acquire_locks_inner:
						ns_iter = pidns_trywriteall(result_pidns);
						if unlikely(ns_iter) {
							pidns_waitwrite(ns_iter);
							goto again_acquire_locks_inner;
						}
						if (result_ctl) {
							if (!procctl_chlds_trywrite(owner_ctl)) {
								pidns_endwriteall(result_pidns);
								procctl_chlds_waitwrite(owner_ctl);
								goto again_acquire_locks_inner;
							}
							if unlikely(!procgrp_memb_trywrite(result_grp)) {
								procctl_chlds_endwrite(owner_ctl);
								pidns_endwriteall(result_pidns);
								procgrp_memb_waitwrite(result_grp);
								goto again_acquire_locks_inner;
							}
						}

						/* Allocate PIDs for `result_pid' within all namespaces it should appear in. */
#ifdef PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE
						if (!pidns_allocpids(result_pid))
							goto err_pidns_allocpids_failed;
#else /* PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */
						pidns_allocpids(result_pid);
#endif /* !PIDNS_NEXTPID_CAN_RETURN_MINUS_ONE */

						/* Check if we were able  to allocate the same  TID.
						 * If we were, then we also know that the same value
						 * has previously been written to user-space! */
						new_ctid = taskpid_getnstid(result_pid, caller_pid->tp_ns);
						if unlikely(ctid != new_ctid) {
							ctid = new_ctid;
							goto again_write_ctid_to_parent_tidptr;
						}
					}
				}
			} EXCEPT {
				assert((result_grp != NULL) == (result_ctl != NULL));
				if (result_ctl != NULL) {
					arref_fini(&result_ctl->pc_grp);
					arref_fini(&result_ctl->pc_parent);
					_procctl_free(result_ctl);
					decref_unlikely(result_grp);
				} else {
					assert(result_pid->tp_proc == owner_pid);
					decref_nokill(owner_pid);
				}
				_taskpid_free(result_pid);
				decref_unlikely(result_pidns);
				RETHROW();
			}

			/* While interlocked with `parent_ctl->pc_chlds_lock', check if the parent
			 * process (as pointed-to by `owner_pid') has already terminated. - If it
			 * has, then we have to release all  of our locks, and free most  relevant
			 * data,  before looping back  to the point where  the parent process gets
			 * calculated, which is then able to deal with that process having exited. */
			{
				REF struct task *owner_task;
				owner_task = taskpid_gettask(owner_pid);
				if unlikely(!owner_task || (ATOMIC_READ(owner_task->t_flags) & (TASK_FTERMINATED |
				                                                                TASK_FTERMINATING))) {
					pidns_endwriteall(result_pidns);
					if (result_ctl != NULL) {
						_procgrp_memb_endwrite(result_grp);
						_procctl_chlds_endwrite(owner_ctl);
						procgrp_memb_reap(result_grp);
						procctl_chlds_reap(owner_ctl);
						decref_unlikely(result_grp);
						arref_fini(&result_ctl->pc_grp);
						arref_fini(&result_ctl->pc_parent);
						_procctl_free(result_ctl);
						decref_unlikely(result_grp);
					} else {
						assert(result_pid->tp_proc == owner_pid);
						decref_nokill(owner_pid);
					}
					xdecref_unlikely(owner_task);
					_taskpid_free(result_pid);
					decref_unlikely(result_pidns);
					_task_serve();
					if (task_gettaskpid_of(owner_task) == taskpid_getprocpid(caller_pid)) {
						/* Might  get here if the calling process's main thread is currently
						 * in the process of exiting (inside task_exit: already set the flag
						 * `TASK_FTERMINATING', but has yet to propagate its exit status  to
						 * all of the other threads)
						 *
						 * In this case, don't wait for the RPC to arrive, but do the work
						 * ourselves  by  throwing the  relevant  E_EXIT_THREAD exception! */
						THROW(E_EXIT_THREAD, taskpid_getprocpid(caller_pid)->tp_status);
					}
					goto again_assign_pid;
				}
				decref_unlikely(owner_task);
			}

			/* Whilst interlocked with all of the locks needed to make a new thread
			 * globally visible, check if our own  thread might need to serve  some
			 * RPCs  right now. -- If it does,  then we mustn't actually go through
			 * with creation of a  new thread, since there  might be an RPC  that's
			 * meant for us to terminate,  and might originate from something  like
			 * a process-group-wide broadcast of a SIGINT.
			 *
			 * When something like that happens, we mustn't be allowed to add a new
			 * process to the process group, which would then no longer be apart of
			 * the original set of processes that received the SIGINT.
			 *
			 * Furthermore,  this is a special case in  that we can't solely rely on
			 * the presence of `TASK_FRPC' to indicate the presence of pending RPCs,
			 * which  in the case of process-wide RPCs might get set asynchronously,
			 * in which case there can be a process-directed RPC pending right  now,
			 * which is also meant to kill,  even though our `TASK_FRPC' flag  isn't
			 * set right now.
			 *
			 * Because of this, we need a custom way of checking for signal, which
			 * we facilitate by checking for TASK_FRPC, and even if that one's not
			 * set, we also go through signals send to our process in order to see
			 * if there are any that aren't marked by the calling thread.
			 *
			 * FIXME: What about a process-directed RPC with the intend of killing the
			 *        targeted process, but then one of the process's thread took that
			 *        RPC  and began handling it (so we're  no longer able to see it).
			 *        Now handling of the RPCs hasn't  finished yet, but once it  has,
			 *        the receiving thread will cause  our process to terminate,  only
			 *        at that point it's too late because we ended up creating the new
			 *        process...
			 * Solution: until the kernel-side part relating to execution of a
			 *           process-directed RPC has finished, there must be some
			 *           kind of  flag "PROCESS_RPC_HANDLING_IN_PROCESS"  that
			 *           remains set for as long as a process-directed RPC  is
			 *           still being processed by some thread of the  process.
			 *           The flag also comes with a `struct sig' (possibly one
			 *           that is global), and that  we can then wait on  here,
			 *           so-as to ensure  that no  process-directed RPC  could
			 *           possibly exist  that might  stop  creation of  a  new
			 *           thread.
			 */
			if (ATOMIC_READ(caller->t_flags) & TASK_FRPC) {
do_task_serve_and_acquire_locks:
				if (result_ctl != NULL) {
					_procgrp_memb_endwrite(result_grp);
					_procctl_chlds_endwrite(owner_ctl);
					procgrp_memb_reap(result_grp);
					procctl_chlds_reap(owner_ctl);
				}
				pidns_endwriteall(result_pidns);
				_task_serve();
				goto again_acquire_locks;
			}

			/* Check for unmasked process-directed signals.
			 * Note that for this, we need yet another lock, which has to be held
			 * at the same time as all of the other locks in order to ensure that
			 * everything operates interlocked! */
			{
				struct procctl *caller_ctl;
				struct pending_rpc *rpc;
				struct pending_rpc_slist pending;
				caller_ctl = caller_pid->tp_pctl;
				if (!procctl_sig_tryread(caller_ctl)) {
					if (result_ctl != NULL) {
						_procgrp_memb_endwrite(result_grp);
						_procctl_chlds_endwrite(owner_ctl);
						procgrp_memb_reap(result_grp);
						procctl_chlds_reap(owner_ctl);
					}
					pidns_endwriteall(result_pidns);
					procctl_sig_waitread(caller_ctl);
					goto again_acquire_locks;
				}
				pending.slh_first = ATOMIC_READ(caller_ctl->pc_sig_list.slh_first);
				if unlikely(pending.slh_first == THIS_RPCS_TERMINATED) {
sig_endread_and_force_task_serve_and_acquire_locks:
					procctl_sig_endread(caller_ctl);
					/* Set the RPC flag ourselves, so `_task_serve()' actually does its job! */
					ATOMIC_OR(caller->t_flags, TASK_FRPC);
					goto do_task_serve_and_acquire_locks;
				}
				SLIST_FOREACH (rpc, &pending, pr_link) {
					int status;
					status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
					if (status == SIGMASK_ISMASKED_NOPF_NO)
						goto sig_endread_and_force_task_serve_and_acquire_locks; /* Unmasked, pending RPC! */
#ifdef CONFIG_HAVE_USERPROCMASK
					if (status == SIGMASK_ISMASKED_NOPF_FAULT) {
						if (!have_caller_sigmask) {
							/* Copy the calling thread's userprocmask so we can use that one! */
							USER CHECKED struct userprocmask *um;
							USER UNCHECKED sigset_t *current_sigmask;
							_procctl_sig_endread(caller_ctl);
							if (result_ctl != NULL) {
								_procgrp_memb_endwrite(result_grp);
								_procctl_chlds_endwrite(owner_ctl);
								procgrp_memb_reap(result_grp);
								procctl_chlds_reap(owner_ctl);
							}
							pidns_endwriteall(result_pidns);
							procctl_sig_reap(caller_ctl);
							COMPILER_BARRIER();
							um              = PERTASK_GET(this_userprocmask_address);
							current_sigmask = ATOMIC_READ(um->pm_sigmask);
							validate_readable(current_sigmask, sizeof(sigset_t));
							memcpy(&caller_sigmask, current_sigmask, sizeof(sigset_t));
							sigdelset(&caller_sigmask, SIGKILL);
							sigdelset(&caller_sigmask, SIGSTOP);
							have_caller_sigmask = true;
							goto again_acquire_locks;
						}
						if (!sigismember(&caller_sigmask, _RPC_GETSIGNO(rpc->pr_flags)))
							goto sig_endread_and_force_task_serve_and_acquire_locks; /* Unmasked, pending RPC! */
					}
#endif /* CONFIG_HAVE_USERPROCMASK */
				}
				procctl_sig_endread(caller_ctl);
			}

			/* ========== Point of no return: From here on, we'll be making the thread visible! */

			/* Insert `result_pid' into all of the PID namespaces it should appear in. */
			ns_iter = result_pidns;
			do {
				pidns_insertpid(ns_iter, result_pid);
			} while ((ns_iter = ns_iter->pn_par) != NULL);

			/* Insert a new process PID into the calling process's process group. */
			assert((result_grp != NULL) == (result_ctl != NULL));
			assert((result_grp != NULL) == ((clone_flags & CLONE_THREAD) == 0));
			if (result_ctl != NULL) {
				/* Insert the new thread into the relevant process controller's child list. */
				procctl_chlds_insert(owner_ctl, result_pid);
				procgrp_memb_insert(result_grp, result_pid); /* Initializes `pc_grpmember' */
			} else {
				/* Add thread to main process's thread list. */
				procctl_thrds_acquire(owner_ctl); /* SMP-lock, so nesting is allowed! */
				/* FIXME: Must check if the current process terminated _AFTER_ `procctl_thrds_acquire'! */

				procctl_thrds_insert(owner_ctl, result_pid);
				procctl_thrds_release(owner_ctl);
			}

			/* Insert the new task into its mman's thread-list */
			mman_threadslock_acquire(result->t_mman); /* SMP-lock, so nesting is allowed! */
			LIST_INSERT_HEAD(&result->t_mman->mm_threads, result, t_mman_tasks);
			mman_threadslock_release(result->t_mman);

			/* Release locks... */
			if (result_ctl != NULL) {
				procgrp_memb_endwrite(result_grp);
				decref_unlikely(result_grp);
			}
			_procctl_chlds_endwrite(owner_ctl);
			procctl_chlds_reap(owner_ctl);
			pidns_endwriteall(result_pidns);

			/* Indicate to the process controller that its list of children has changed. */
			sig_broadcast(&owner_ctl->pc_chld_changed);
		} /* Scope... */
#endif /* CONFIG_USE_NEW_GROUP */

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
#ifndef CONFIG_USE_NEW_GROUP
		/* Allocate the PID descriptor for the new thread. */
		if (clone_flags & CLONE_NEWPID) {
			REF struct pidns *ns;
			ns = pidns_alloc(FORTASK(caller, this_taskpid)->tp_ns);
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
#endif /* !CONFIG_USE_NEW_GROUP */

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
