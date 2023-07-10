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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_CLONE_C
#define GUARD_KERNEL_SRC_SCHED_TASK_CLONE_C 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/fs.h>
#include <kernel/handman.h>
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
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sig.h>
#include <sched/sigaction.h>
#include <sched/sigmask.h>
#include <sched/task-clone.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/host.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/paging.h>

#include <assert.h>
#include <atomic.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
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

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

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
	atomic_write((USER CHECKED pid_t *)cookie, task_gettid());
}

PRIVATE NONNULL((1)) void FCALL
waitfor_vfork_completion(struct task *__restrict thread)
		THROWS(E_INTERRUPT) {
	/* Wait until the child thread is done vfork()-ing */
	while ((atomic_read(&thread->t_flags) & TASK_FVFORK) != 0) {
		struct taskpid *pid;
		pid = FORTASK(thread, this_taskpid);
		assert(pid);
		task_connect(&pid->tp_changed);
		if unlikely((atomic_read(&thread->t_flags) & TASK_FVFORK) == 0) {
			task_disconnectall();
			break;
		}

		/* Prepare the calling thread  for the fact that  we're
		 * about to use a custom signal mask when service RPCs. */
		sigmask_prepare_sigsuspend();

		/* The specs say that we should ignore (mask) all POSIX
		 * signals until the  child indicate VFORK  completion.
		 *
		 * We do  this by  simply doing  the wait  using  a
		 * custom mask that has all signal bits set to `1'.
		 *
		 * s.a. `__ARCH_HAVE_SIGBLOCK_VFORK' */
		task_waitfor_with_sigmask(&sigmask_full);
	}
}


#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PRIVATE NONNULL((4)) void KCALL
restore_userprocmask_after_vfork(USER CHECKED struct userprocmask *um,
                                 USER CHECKED sigset_t *umask,
                                 size_t umasksize,
                                 sigset_t const *__restrict saved) {
#if 0 /* Don't do this! -- See comment below */
	memcpy(umask, saved, umasksize);
#else
	/* NOTE: Check word-wise for modified sigmask words, and only
	 *       restore those that actually changed. -- In case none
	 *       changed, we mustn't do any writes since the mask may
	 *       reside in read-only memory! */
	while (umasksize >= sizeof(ulongptr_t)) {
		ulongptr_t oword, nword;
		oword = UNALIGNED_GET((USER CHECKED ulongptr_t const *)umask);
		nword = *(ulongptr_t const *)saved;
		if (nword != oword)
			UNALIGNED_SET((USER CHECKED ulongptr_t *)umask, nword);
		umask = (USER CHECKED sigset_t *)((byte_t *)umask + sizeof(ulongptr_t));
		saved = (sigset_t const *)((byte_t const *)saved + sizeof(ulongptr_t));
		umasksize -= sizeof(ulongptr_t);
	}
	while (umasksize) {
		byte_t oword, nword;
		oword = *(byte_t USER CHECKED const *)umask;
		nword = *(byte_t const *)saved;
		if (nword != oword)
			*(byte_t USER CHECKED *)umask = nword;
		umask = (USER CHECKED sigset_t *)((byte_t *)umask + 1);
		saved = (sigset_t const *)((byte_t const *)saved + 1);
		umasksize -= 1;
	}
#endif

	/* Also restore the active userprocmask pointer to what it was
	 * prior  to the vfork(2) (just in case the child modified it,
	 * since we want everything about the parent's signal mask  to
	 * go back to what it was before they called vfork(2)) */
	atomic_write(&um->pm_sigmask, umask);
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */


/* Clone the calling thread's signal mask into `result'. */
PRIVATE NONNULL((1, 2)) void KCALL
task_clone_sigmask(struct task *__restrict result,
                   struct task *__restrict caller,
                   uint64_t clone_flags) {
	/* Clone the current signal mask. */
	(void)clone_flags;
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
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
			USER UNCHECKED sigset_t *parent_umask;
			size_t parent_umasksize;
			parent_umask     = um->pm_sigmask;
			parent_umasksize = um->pm_sigsize;
			COMPILER_READ_BARRIER();
			validate_readable(parent_umask, parent_umasksize);
			if (parent_umasksize > sizeof(sigset_t))
				parent_umasksize = sizeof(sigset_t);
			memset(memcpy(&FORTASK(result, this_kernel_sigmask),
			              parent_umask, parent_umasksize),
			       0xff, sizeof(sigset_t) - parent_umasksize);
		}
	} else
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
	{
		memcpy(&FORTASK(result, this_kernel_sigmask),
		       &FORTASK(caller, this_kernel_sigmask),
		       sizeof(sigset_t));
	}
}



/* Clone the calling thread's signal handlers into `result'. */
PRIVATE NONNULL((1, 2)) void KCALL
task_clone_sighand(struct task *__restrict result,
                   struct task *__restrict caller,
                   uint64_t clone_flags) {
	if (clone_flags & CLONE_SIGHAND) {
		/* Must share signal handlers. */
		REF struct sighand_ptr *myptr;
		if unlikely(!(clone_flags & CLONE_VM)) {
			/* In order for signal handler sharing to make sense, memory must also be shared! */
			THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
			      E_INVALID_ARGUMENT_CONTEXT_CLONE_SIGHAND_WITHOUT_VM,
			      clone_flags, CLONE_SIGHAND | CLONE_VM, CLONE_SIGHAND);
		}
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
				sighand_ptr_read(myptr);
				COMPILER_READ_BARRIER();
				myhand = myptr->sp_hand;
				COMPILER_READ_BARRIER();
				if (!myhand) {
					/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
					sighand_ptr_endread(myptr);
					kfree(newptr);
					newptr = NULL;
				} else {
					if (!sighand_trywrite(myhand)) {
						sighand_ptr_endread(myptr);
						task_yield();
						goto again_lock_myptr;
					}
					sighand_ptr_endread(myptr);
					sighand_incshare(myhand);
					sighand_endwrite(myhand);

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
	preemption_flag_t was;
	struct cpu *mycpu;
	preemption_pushoff(&was);
	mycpu = caller->t_cpu;
	if (FORCPU(mycpu, thiscpu_x86_ioperm_bitmap) == self) {
		/* Re-map, and only include read permissions. */
		pagedir_map(FORCPU(mycpu, thiscpu_x86_iob),
		            2 * PAGESIZE,
		            self->ib_pages,
		            PAGEDIR_PROT_READ);
	}
	preemption_pop(&was);
}
#endif /* __i386__ || __x86_64__ */


#ifdef __INTELLISENSE__
PRIVATE NONNULL((1, 2)) void FCALL
task_clone_thrdpid(struct task *__restrict result,
                   struct task *__restrict caller,
                   uint64_t clone_flags,
                   USER UNCHECKED pid_t *parent_tidptr);
PRIVATE NONNULL((1, 2)) void FCALL
task_clone_procpid(struct task *__restrict result,
                   struct task *__restrict caller,
                   uint64_t clone_flags,
                   USER UNCHECKED pid_t *parent_tidptr);
#else /* __INTELLISENSE__ */
DECL_END

#define DEFINE_task_clone_thrdpid
#include "task-clone-pid.c.inl"
#define DEFINE_task_clone_procpid
#include "task-clone-pid.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */



/* High-level implementation for the `clone(2)' system call.
 * @param: init_state: The CPU state of the thread that called `clone(2)'
 *                     Pass   `NULL'  to  spawn   a  new  kernel  thread.
 * @param: args:       Clone arguments. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((2)) REF struct task *FCALL
task_clone(struct icpustate const *init_state,
           struct task_clone_args *__restrict args)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct task *result;
	struct task *caller = THIS_TASK;
	uint64_t clone_flags = args->tca_flags;

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
			if unlikely(init_state == NULL) {
				/* Since kernel threads are handled as children of /bin/init,
				 * that's exactly who  we act like  being our parent  thread. */
				caller         = &boottask;
				result->t_mman = incref(&mman_kernel);
			} else {
				if (!(clone_flags & CLONE_VM)) {
					THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
					      E_INVALID_ARGUMENT_CONTEXT_CLONE_VFORK_WITHOUT_VM,
					      (syscall_ulong_t)clone_flags,
					      CLONE_VM | CLONE_VFORK, CLONE_VFORK);
				}
				/* The mman is being shared */
				result->t_mman = incref(caller->t_mman);
				/* Set the VFORK flag to cause the thread to execute in VFORK-mode.
				 * This must be done before we  start making the thread visible  to
				 * other kernel components, since this also affects things such  as
				 * the thread's effective signal mask. */
				if (clone_flags & CLONE_VFORK)
					result->t_flags |= TASK_FVFORK;
			}
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
			kernel_stack = (KERNEL byte_t *)mnode_getendaddr(&FORTASK(result, this_kernel_stacknode_));
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			kernel_stack = (KERNEL byte_t *)mnode_getaddr(&FORTASK(result, this_kernel_stacknode_));
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */

			/* Handle special case of spawning a new kernel thread */
			if unlikely(init_state == NULL) {
				child_state = task_clone_setup_kthread(result, kernel_stack, &args->tca_kthread);
				FORTASK(result, this_sstate) = child_state;
				bzero(&FORTASK(result, this_user_except_handler),
				      sizeof(struct user_except_handler));
				FORTASK(result, this_fs)      = incref(&fs_kernel);
				FORTASK(result, this_cred)    = incref(&cred_kernel);
				FORTASK(result, this_handman) = incref(&handman_kernel);
				sigfillset(&FORTASK(result, this_kernel_sigmask));
				assert(FORTASK(result, this_sighand_ptr) == NULL);
#if defined(__i386__) || defined(__x86_64__)
				assert(FORTASK(result, this_x86_ioperm_bitmap) == NULL);
#endif /* __i386__ || __x86_64__ */
				result->t_flags |= TASK_FKERNTHREAD;
				goto do_clone_pid;
			}

			/* Construct the initial scheduler CPU state from the caller-given `init_state' */
#ifdef SCPUSTATE_IS_TRANSITIVE_ICPUSTATE
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			child_state = (struct scpustate *)(kernel_stack - sizeof(struct scpustate));
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			child_state = (struct scpustate *)kernel_stack;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			*child_state = *init_state;
#elif defined(__x86_64__)
			child_state = icpustate_to_scpustate_p_ex(init_state,
			                                          kernel_stack,
			                                          args->tca_arch.atca_x86_gsbase,
			                                          args->tca_arch.atca_x86_fsbase,
			                                          __rdgs(),
			                                          __rdfs(),
			                                          __rdes(),
			                                          __rdds());
#else /* __x86_64__ */
			child_state = icpustate_to_scpustate_p(init_state, kernel_stack);
#endif /* !__x86_64__ */

			/* Assign the given stack pointer for the new thread. */
#ifdef scpustate_setusersp
			scpustate_setusersp(child_state, (void *)args->tca_stack);
#else /* scpustate_setusersp */
			scpustate_setsp(child_state, (void *)args->tca_stack);
#endif /* !scpustate_setusersp */

			/* Do additional, arch-specific initialization */
#if defined(__i386__) || defined(__x86_64__)
			/* Reset iopl() for the child thread/process */
			if ((clone_flags & CLONE_THREAD) ? !x86_iopl_keep_after_clone
			                                 : !x86_iopl_keep_after_fork)
				child_state->scs_irregs.ir_Pflags &= ~EFLAGS_IOPLMASK;
#endif /* __i386__ || __x86_64__ */

#if defined(__i386__) && !defined(__x86_64__)
			FORTASK(result, this_x86_user_fsbase) = args->tca_arch.atca_x86_fsbase;
			FORTASK(result, this_x86_user_gsbase) = args->tca_arch.atca_x86_gsbase;
#endif /* __i386__ && !__x86_64__ */

			/* Have `fork(2)' and `clone(2)' return `0' in the child thread/process */
			scpustate_setreturn(child_state, 0);

			/* Inject  an  RPC  for  saving  the  child's  TID  within  the  given  pointer
			 * This always needs to be done in the context of the child, so that exceptions
			 * during the write are handled in the proper context, as well as in regards to
			 * the child actually existing in a  different VM when `CLONE_VM' isn't  given. */
			if (clone_flags & CLONE_CHILD_SETTID) {
				validate_writable(args->tca_child_tid, sizeof(*args->tca_child_tid));
				child_state = task_asyncrpc_push(child_state, &clone_set_child_tid, args->tca_child_tid);
			}

			/* Apply some finalizing transformations to `child_state' (and `result') */
			_task_init_arch_sstate(result, caller, &child_state);

			/* Save the CPU context with which the child will launch */
			FORTASK(result, this_sstate) = child_state;
		}

		if (clone_flags & CLONE_CHILD_CLEARTID) {
			validate_writable(args->tca_child_tid, sizeof(*args->tca_child_tid));
			FORTASK(result, this_tid_address) = args->tca_child_tid; /* `set_tid_address(child_tidptr)' */
		}

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
				if unlikely(clone_flags & CLONE_NEWNS) {
					THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
					      E_INVALID_ARGUMENT_CONTEXT_CLONE_FS_WITH_NEWNS,
					      (syscall_ulong_t)clone_flags,
					      CLONE_FS | CLONE_NEWNS,
					      CLONE_FS | CLONE_NEWNS);
				}
				result_fs = incref(result_fs);
			} else {
				result_fs = fs_clone(result_fs, (clone_flags & CLONE_NEWNS) != 0);
			}
			FORTASK(result, this_fs) = result_fs; /* Inherit reference */
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
			struct handman *result_handman;
			result_handman = FORTASK(caller, this_handman);
			if (clone_flags & CLONE_FILES) {
				result_handman = incref(result_handman);
			} else {
				/* NOTE: `handman_fork()' automatically closes CLOFORK files. */
				result_handman = handman_fork(result_handman);
			}
			FORTASK(result, this_handman) = result_handman; /* Inherit reference */
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
				if (atomic_fetchinc(&iob->ib_share) == 1)
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
do_clone_pid:
		if unlikely(clone_flags & CLONE_PIDFD) {
			fd_t pidfd;
			struct handle_install_data install;
			/* Support for PIDFDs */
			pidfd = handles_install_begin(&install);
			TRY {
				/* Write the chosen FDNO to user-space. */
				validate_and_write(args->tca_pidfd, pidfd);

				/* Clone the thread/process PID. */
				if (clone_flags & CLONE_THREAD) {
					task_clone_thrdpid(result, caller, clone_flags, args->tca_parent_tid);
				} else {
					task_clone_procpid(result, caller, clone_flags, args->tca_parent_tid);
				}
			} EXCEPT {
				handles_install_rollback(&install);
				RETHROW();
			}
			/* NOTE: From this point forth, normally nothing should be able to throw.
			 *       The  exception to  this is  `CLONE_VFORK', though  even that one
			 *       shouldn't be able  to fail, unless  the caller receives  SIGKILL
			 *       (SIGSTOP would be handled without  unwinding), or has a  corrupt
			 *       userprocmask. The later is userspace's fault, and the for former
			 *       it doesn't matter if  we leak an FD,  since the process dies  no
			 *       matter  what. (Though this might pose problems if the process is
			 *       shared is FD-table  with another process...  -- No; it  doens't,
			 *       because  if the SIGKILL was received after clone returned in the
			 *       parent, then  they would  also die  with the  child pidfd  being
			 *       shared with yet another process) */
			handles_install_commit(&install, FORTASK(result, this_taskpid), IO_RDWR);
		} else if (clone_flags & CLONE_THREAD) {
			task_clone_thrdpid(result, caller, clone_flags, args->tca_parent_tid);
		} else {
			task_clone_procpid(result, caller, clone_flags, args->tca_parent_tid);
		}
	} EXCEPT {
		/* Cleanup on error. */
#if defined(__i386__) || defined(__x86_64__)
		if unlikely(FORTASK(result, this_x86_ioperm_bitmap)) {
			assert(FORTASK(result, this_x86_ioperm_bitmap)->ib_share >= 1);
			atomic_dec(&FORTASK(result, this_x86_ioperm_bitmap)->ib_share);
			decref_likely(FORTASK(result, this_x86_ioperm_bitmap));
		}
#endif /* __i386__ || __x86_64__ */
		xdecref(FORTASK(result, this_handman));
		xdecref(FORTASK(result, this_sighand_ptr));
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

	/* Deal with vfork() */
	if (clone_flags & CLONE_VFORK) {
		TRY {
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
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
				sigset_t saved_umask;
				USER CHECKED struct userprocmask *um;
				USER UNCHECKED sigset_t *umask;
				size_t umasksize;
				um        = PERTASK_GET(this_userprocmask_address);
				umask     = um->pm_sigmask;
				umasksize = um->pm_sigsize;
				COMPILER_READ_BARRIER();
				validate_readwrite(umask, umasksize);
				if (umasksize > sizeof(sigset_t))
					umasksize = sizeof(sigset_t);
				memcpy(&saved_umask, umask, umasksize);

				TRY {
					/* Actually start execution of the newly created thread. */
					task_start(result);

					/* Wait for the thread to clear its VFORK flag. */
					waitfor_vfork_completion(result);
				} EXCEPT {
					{
						NESTED_EXCEPTION;
						restore_userprocmask_after_vfork(um, umask, umasksize, &saved_umask);
					}
					RETHROW();
				}

				/* Restore the old (saved) state of the user-space  signal
				 * mask, as it was prior to the vfork-child being started. */
				restore_userprocmask_after_vfork(um, umask, umasksize, &saved_umask);
			} else
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
			{
				/* Actually start execution of the newly created thread. */
				task_start(result);

				/* Wait for the thread to clear its VFORK flag. */
				waitfor_vfork_completion(result);
			}
		} EXCEPT {
			decref(result);
			RETHROW();
		}
	} else {
		/* Simply start execution of the newly created thread. */
		task_start(result);
	}
	return result;
}


/* Create  and start a new kernel thread.
 * >> static int my_tmain(int a, int b) {
 * >>     printk(KERN_TRACE "my_tmain(%d, %d)\n", a, b);
 * >>     return 0;
 * >> }
 * >> void spawn_thread() {
 * >>     decref(task_clone_kthread((int (*)())(void *)&my_tmain, 2, 10, 20));
 * >> }
 * @param: thread_main: thread entry point (`task_exit(return)' is called upon return)
 * @param: argc:        # of arguments to pass to `thread_main' (via its stack)
 * @param: ...:         Variable arguments for `thread_main' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct task *VCALL
task_clone_kthread(int (*thread_main)(), size_t argc, ...)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct task *result;
	struct task_clone_args cargs;
	cargs.tca_flags            = CLONE_VM | CLONE_THREAD | CLONE_DETACHED;
	cargs.tca_exit_signal      = SIGCHLD;
	cargs.tca_kthread.tck_main = thread_main;
	cargs.tca_kthread.tck_argc = argc;
	va_start(cargs.tca_kthread.tck_args, argc);
	RAII_FINALLY { va_end(cargs.tca_kthread.tck_args); };
	result = task_clone(NULL, &cargs);
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





/************************************************************************/
/* clone3()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CLONE3
INTERN NONNULL((1)) pid_t FCALL
sys_clone3_impl(struct icpustate const *__restrict state,
                USER UNCHECKED struct clone_args *cl_args,
                size_t size) {
	pid_t cpid;
	REF struct task *child;
	struct task_clone_args cargs;
	bzero(&cargs, sizeof(cargs));
	switch (size) {

	case 88:
		cargs.tca_cgroup = cl_args->ca_cgroup;
		ATTR_FALLTHROUGH
	case 80:
		cargs.tca_set_tid     = cl_args->ca_set_tid;
		cargs.tca_set_tid_siz = cl_args->ca_set_tid_size;
		ATTR_FALLTHROUGH
	case 64: {
		size_t stacksize;
		USER UNCHECKED void *stackbase;
		validate_readable(cl_args, size);
		cargs.tca_flags       = cl_args->ca_flags;
		cargs.tca_pidfd       = cl_args->ca_pidfd;
		cargs.tca_child_tid   = cl_args->ca_child_tid;
		cargs.tca_parent_tid  = cl_args->ca_parent_tid;
		cargs.tca_exit_signal = cl_args->ca_exit_signal;

		/* Load the requested stack */
		stacksize = cl_args->ca_stack_size;
		stackbase = cl_args->ca_stack;
		if (stacksize || (cargs.tca_flags & CLONE_VM)) {
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			stackbase = (byte_t *)stackbase + stacksize;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
			cargs.tca_stack = stackbase;
		} else {
#ifdef icpustate_getusersp
			cargs.tca_stack = (USER UNCHECKED void *)icpustate_getusersp(state);
#else /* icpustate_getusersp */
			cargs.tca_stack = (USER UNCHECKED void *)icpustate_getsp(state);
#endif /* !icpustate_getusersp */
		}

		/* Initialize arch-specific TLS data. */
#ifdef ARCH_HAVE_ARCH_TASK_CLONE_ARGS
		arch_task_clone_args_inittls(&cargs.tca_arch, cargs.tca_flags, cl_args->ca_tls);
#endif /* ARCH_HAVE_ARCH_TASK_CLONE_ARGS */
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_CLONE3_INVALID_SIZE,
		      size);
		break;
	}
	COMPILER_READ_BARRIER();

	/* Verify the user-given `flags' argument. */
	if (cargs.tca_flags & ~(UINT64_C(0x00000000ffffff00) | CLONE_CLEAR_SIGHAND |
	                        CLONE_INTO_CGROUP | CLONE_NEWTIME | CLONE_CRED)) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
		      E_INVALID_ARGUMENT_CONTEXT_CLONE3_INVALID_FLAGS, cargs.tca_flags,
		      ~(CLONE_CLEAR_SIGHAND | CLONE_INTO_CGROUP | CLONE_NEWTIME | CLONE_CRED));
	}

	/* Spawn a new child thread/process */
	child = task_clone(state, &cargs);
	cpid  = task_gettid_of(child);
	decref_unlikely(child);
	return cpid;
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_clone3_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	pid_t cpid;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	cpid = sys_clone3_impl(ctx->rc_state,
	                       (USER UNCHECKED struct clone_args *)ctx->rc_scinfo.rsi_regs[0],
	                       (size_t)ctx->rc_scinfo.rsi_regs[1]);
	icpustate_setreturn(ctx->rc_state, cpid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL2(syscall_slong_t, clone3,
                USER UNCHECKED struct clone_args *, cl_args,
                size_t, size) {
	(void)cl_args;
	(void)size;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_clone3_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_CLONE3 */




/************************************************************************/
/* fork()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FORK
INTERN NONNULL((1)) pid_t FCALL
sys_fork_impl(struct icpustate const *__restrict state) {
	pid_t child_tid;
	REF struct task *child_tsk;
	struct task_clone_args cargs;

	/* Set-up clone args. */
	bzero(&cargs, sizeof(cargs));
	cargs.tca_exit_signal = SIGCHLD;
#ifdef icpustate_getusersp
	cargs.tca_stack = icpustate_getusersp(state);
#else /* icpustate_getusersp */
	cargs.tca_stack = icpustate_getsp(state);
#endif /* !icpustate_getusersp */
#ifdef ARCH_HAVE_ARCH_TASK_CLONE_ARGS
	arch_task_clone_args_initfork(&cargs.tca_arch);
#endif /* ARCH_HAVE_ARCH_TASK_CLONE_ARGS */

	/* Do the clone. */
	child_tsk = task_clone(state, &cargs);
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	return child_tid;
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_fork_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	pid_t cpid;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	cpid = sys_fork_impl(ctx->rc_state);
	icpustate_setreturn(ctx->rc_state, cpid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL0(pid_t, fork) {
	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_fork_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_FORK */





/************************************************************************/
/* vfork()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_VFORK
INTERN NONNULL((1)) pid_t FCALL
sys_vfork_impl(struct icpustate const *__restrict state) {
	pid_t child_tid;
	REF struct task *child_tsk;
	struct task_clone_args cargs;

	/* Set-up clone args. */
	bzero(&cargs, sizeof(cargs));
	cargs.tca_flags       = CLONE_VM | CLONE_VFORK;
	cargs.tca_exit_signal = SIGCHLD;
#ifdef icpustate_getusersp
	cargs.tca_stack = icpustate_getusersp(state);
#else /* icpustate_getusersp */
	cargs.tca_stack = icpustate_getsp(state);
#endif /* !icpustate_getusersp */
#ifdef ARCH_HAVE_ARCH_TASK_CLONE_ARGS
	arch_task_clone_args_initvfork(&cargs.tca_arch);
#endif /* ARCH_HAVE_ARCH_TASK_CLONE_ARGS */

	/* Do the clone. */
	child_tsk = task_clone(state, &cargs);
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	return child_tid;
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_vfork_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	pid_t cpid;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	cpid = sys_vfork_impl(ctx->rc_state);
	icpustate_setreturn(ctx->rc_state, cpid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL0(pid_t, vfork) {
	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_vfork_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_VFORK */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_CLONE_C */
