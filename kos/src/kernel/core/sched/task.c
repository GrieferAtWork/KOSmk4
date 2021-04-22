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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_C
#define GUARD_KERNEL_SRC_SCHED_TASK_C 1
#define __WANT_MNODE_INIT
#define __WANT_MPART_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/cache.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h> /* this_trampoline_node */
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/async.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <asm/farptr.h>
#include <sys/wait.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];


PRIVATE ATTR_USED ATTR_SECTION(".data.pertask.head")
struct task task_header = {
	/* .t_self       = */ NULL, /* Filled in by the initializer. */
	/* .t_refcnt     = */ 1,
	/* .t_flags      = */ TASK_FNORMAL,
	/* .t_cpu        = */ &bootcpu,
	/* .t_mman       = */ &mman_kernel,
	/* .t_mman_tasks = */ LIST_ENTRY_UNBOUND_INITIALIZER,
	/* .t_heapsz     = */ (size_t)__kernel_pertask_size,
	{
		/* .t_state  = */ NULL
	}
};

DATDEF ATTR_PERTASK struct mpart this_kernel_stackpart_ ASMNAME("this_kernel_stackpart");
DATDEF ATTR_PERTASK struct mnode this_kernel_stacknode_ ASMNAME("this_kernel_stacknode");
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
DATDEF ATTR_PERTASK struct mnode this_kernel_stackguard_ ASMNAME("this_kernel_stackguard");
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

/* [const] MMan node referring to the kernel stack of the current thread.
 * WARNING: These structures for `boottask' and `bootidle' are not actually part of the kernel MMan!
 * WARNING: You cannot assume that your stack-pointer is always located within `THIS_KERNEL_STACK',
 *          as KOS may use special, arch-specific stacks  to deal with certain CPU exceptions  that
 *          require execution on  a separate stack  (such as  the #DF-stack on  x86). To  determine
 *          available/used stack memory, use the function below. */
PUBLIC ATTR_PERTASK struct mpart this_kernel_stackpart_ = {
	MPART_INIT_mp_refcnt(1),
	MPART_INIT_mp_flags(MPART_F_NOSPLIT | MPART_F_NOMERGE |
	                    MPART_F_MLOCK_FROZEN | MPART_F_MLOCK),
	MPART_INIT_mp_state(MPART_ST_MEM),
	MPART_INIT_mp_file(&mfile_zero),
	MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(this_kernel_stackpart_.mp_copy)),
	MPART_INIT_mp_share({ &this_kernel_stacknode_ }),
	MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(this_kernel_stackpart_.mp_lockops)),
	MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),
	MPART_INIT_mp_minaddr(0),
	MPART_INIT_mp_maxaddr(KERNEL_STACKSIZE - 1),
	MPART_INIT_mp_changed({}),
	MPART_INIT_mp_filent({ {} }),
	MPART_INIT_mp_blkst_ptr({ NULL }),
	MPART_INIT_mp_mem(0 /* Filled later */, CEILDIV(KERNEL_STACKSIZE, PAGESIZE)),
	MPART_INIT_mp_meta(NULL)
};

PUBLIC ATTR_PERTASK struct mnode this_kernel_stacknode_ = {
	MNODE_INIT_mn_mement({ {} }),
	MNODE_INIT_mn_minaddr(0),
	MNODE_INIT_mn_maxaddr(KERNEL_STACKSIZE - 1),
	MNODE_INIT_mn_flags(MNODE_F_PWRITE | MNODE_F_PREAD |
	                    MNODE_F_SHARED | MNODE_F_NOSPLIT |
	                    MNODE_F_NOMERGE | MNODE_F_KERNPART |
	                    MNODE_F_MLOCK | MNODE_F_MPREPARED),
	MNODE_INIT_mn_part(&this_kernel_stackpart_),
	MNODE_INIT_mn_fspath(NULL),
	MNODE_INIT_mn_fsname(NULL),
	MNODE_INIT_mn_mman(&mman_kernel),
	MNODE_INIT_mn_partoff(0),
	MNODE_INIT_mn_link({ NULL, &this_kernel_stackpart_.mp_share.lh_first }),
	MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT_mn_module(NULL)
};

#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
PUBLIC ATTR_PERTASK struct mnode this_kernel_stackguard_ = {
	MNODE_INIT_mn_mement({}),
	MNODE_INIT_mn_minaddr(0),
	MNODE_INIT_mn_maxaddr(PAGESIZE - 1),
	MNODE_INIT_mn_flags(MNODE_F_NOSPLIT | MNODE_F_NOMERGE |
	                    MNODE_F_KERNPART | MNODE_F_MLOCK |
	                    _MNODE_F_MPREPARED_KERNEL),
	MNODE_INIT_mn_part(NULL), /* Reserved node! */
	MNODE_INIT_mn_fspath(NULL),
	MNODE_INIT_mn_fsname(NULL),
	MNODE_INIT_mn_mman(&mman_kernel),
	MNODE_INIT_mn_partoff(0),
	MNODE_INIT_mn_link(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT_mn_module(NULL)
};
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */






typedef void (KCALL *pertask_init_t)(struct task *__restrict self);
INTDEF pertask_init_t __kernel_pertask_init_start[];
INTDEF pertask_init_t __kernel_pertask_init_end[];
INTDEF FREE void NOTHROW(KCALL kernel_initialize_scheduler_arch)(void);

LOCAL ATTR_FREETEXT void
NOTHROW(KCALL initialize_predefined_trampoline)(struct task *__restrict self,
                                                   PAGEDIR_PAGEALIGNED void *addr) {
	FORTASK(self, this_trampoline_node).mn_minaddr = (byte_t *)addr;
	FORTASK(self, this_trampoline_node).mn_maxaddr = (byte_t *)addr + PAGESIZE - 1;
	/* Load the trampoline node into the kernel VM. */
	assert(FORTASK(self, this_trampoline_node).mn_mman == &mman_kernel);
	mman_mappings_insert(&mman_kernel, &FORTASK(self, this_trampoline_node));
}

#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
/* Prepare 2 consecutive (and 2-page aligned) pages of  virtual
 * memory for the purpose of doing the initial prepare required
 * for `THIS_TRAMPOLINE_PAGE' of `boottask' and also `bootidle' */
INTDEF NOBLOCK FREE void *
NOTHROW(FCALL kernel_initialize_boot_trampolines)(void);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

PUBLIC ATTR_PERTASK struct exception_info this_exception_info = {};


INTDEF byte_t __kernel_boottask_stack[];
INTDEF byte_t __kernel_boottask_stack_page_p[];
INTDEF byte_t __kernel_bootidle_stack[];
INTDEF byte_t __kernel_bootidle_stack_page_p[];
INTDEF byte_t __kernel_asyncwork_stack[];
INTDEF byte_t __kernel_asyncwork_stack_page_p[];
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
INTDEF byte_t __kernel_boottask_stack_guard[];
INTDEF byte_t __kernel_asyncwork_stack_guard[];
INTDEF byte_t __kernel_bootidle_stack_guard[];
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */


INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler)(void) {
	void *boot_trampoline_pages;
	DEFINE_PUBLIC_SYMBOL(this_task, offsetof(struct task, t_self), sizeof(struct task));
	DEFINE_PUBLIC_SYMBOL(this_cpu, offsetof(struct task, t_cpu), sizeof(struct cpu *));
	DEFINE_PUBLIC_SYMBOL(this_mman, offsetof(struct task, t_mman), sizeof(struct mman *));
	DEFINE_PUBLIC_SYMBOL(this_sstate, offsetof(struct task, t_state), sizeof(struct scpustate *));
	DEFINE_PUBLIC_SYMBOL(this_exception_code, &this_exception_info.ei_code, sizeof(this_exception_info.ei_code));
	DEFINE_PUBLIC_SYMBOL(this_exception_data, &this_exception_info.ei_data, sizeof(this_exception_info.ei_data));
	DEFINE_PUBLIC_SYMBOL(this_exception_state, &this_exception_info.ei_state, sizeof(this_exception_info.ei_state));
	DEFINE_PUBLIC_SYMBOL(this_exception_class, &this_exception_info.ei_class, sizeof(this_exception_info.ei_class));
	DEFINE_PUBLIC_SYMBOL(this_exception_subclass, &this_exception_info.ei_subclass, sizeof(this_exception_info.ei_subclass));
	DEFINE_PUBLIC_SYMBOL(this_exception_args, &this_exception_info.ei_data.e_args, sizeof(this_exception_info.ei_data.e_args));
	DEFINE_PUBLIC_SYMBOL(this_exception_flags, &this_exception_info.ei_flags, sizeof(this_exception_info.ei_flags));
	DEFINE_PUBLIC_SYMBOL(this_exception_faultaddr, &this_exception_info.ei_data.e_faultaddr, sizeof(this_exception_info.ei_data.e_faultaddr));
#if EXCEPT_BACKTRACE_SIZE != 0
	DEFINE_PUBLIC_SYMBOL(this_exception_trace, &this_exception_info.ei_trace[0], sizeof(this_exception_info.ei_trace));
#else /* EXCEPT_BACKTRACE_SIZE != 0 */
	DEFINE_PUBLIC_SYMBOL(this_exception_trace, 0, 0);
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */
	DEFINE_PUBLIC_SYMBOL(thiscpu_id, offsetof(struct cpu, c_id), sizeof(unsigned int));
#ifndef CONFIG_NO_SMP
	DEFINE_PUBLIC_SYMBOL(thiscpu_pdir, offsetof(struct cpu, c_pdir), sizeof(pagedir_phys_t));
#else /* !CONFIG_NO_SMP */
	DEFINE_PUBLIC_SYMBOL(thiscpu_pdir, 0, 0);
#endif /* CONFIG_NO_SMP */
	DEFINE_PUBLIC_SYMBOL(thiscpu_state, offsetof(struct cpu, c_state), sizeof(u16));
	DEFINE_PUBLIC_SYMBOL(thismman_pagedir_p, offsetof(struct mman, mm_pagedir_p), sizeof(physaddr_t));

	assert(boottask.t_refcnt == 1);
	assert(bootidle.t_refcnt == 1);
	assert(asyncwork.t_refcnt == 1);

	/* Figure out where to put the initial trampolines for boottask and bootidle */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	boot_trampoline_pages = kernel_initialize_boot_trampolines();
#else /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	boot_trampoline_pages = mman_findunmapped(&mman_kernel,
	                                          MHINT_GETADDR(KERNEL_MHINT_TRAMPOLINE),
	                                          2 * PAGESIZE,
	                                          MHINT_GETMODE(KERNEL_MHINT_TRAMPOLINE));
#endif /* !ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Construct the trampoline node for the predefined tasks. */
	initialize_predefined_trampoline(&boottask, (byte_t *)boot_trampoline_pages + 0 * PAGESIZE);
	initialize_predefined_trampoline(&bootidle, (byte_t *)boot_trampoline_pages + 1 * PAGESIZE);
	initialize_predefined_trampoline(&asyncwork, (byte_t *)boot_trampoline_pages + 2 * PAGESIZE);

#define STN(thread) FORTASK(&thread, this_kernel_stacknode_)
#define STP(thread) FORTASK(&thread, this_kernel_stackpart_)

	/* boottask */
	STN(boottask).mn_part           = &STP(boottask);
	STN(boottask).mn_link.le_prev   = &STP(boottask).mp_share.lh_first;
	STP(boottask).mp_share.lh_first = &STN(boottask);
	STN(boottask).mn_minaddr        = __kernel_boottask_stack;
	STN(boottask).mn_maxaddr        = __kernel_boottask_stack + KERNEL_STACKSIZE - 1;
	STP(boottask).mp_mem.mc_start   = (physpage_t)loadfarptr(__kernel_boottask_stack_page_p);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	FORTASK(&boottask, this_kernel_stackguard_).mn_minaddr = __kernel_boottask_stack_guard;
	FORTASK(&boottask, this_kernel_stackguard_).mn_maxaddr = __kernel_boottask_stack_guard + PAGESIZE - 1;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

	/* asyncwork */
	STN(asyncwork).mn_part           = &STP(asyncwork);
	STN(asyncwork).mn_link.le_prev   = &STP(asyncwork).mp_share.lh_first;
	STP(asyncwork).mp_share.lh_first = &STN(asyncwork);
	STN(asyncwork).mn_minaddr        = __kernel_asyncwork_stack;
	STN(asyncwork).mn_maxaddr        = __kernel_asyncwork_stack + KERNEL_STACKSIZE - 1;
	STP(asyncwork).mp_mem.mc_start   = (physpage_t)loadfarptr(__kernel_asyncwork_stack_page_p);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	FORTASK(&asyncwork, this_kernel_stackguard_).mn_minaddr = __kernel_asyncwork_stack_guard;
	FORTASK(&asyncwork, this_kernel_stackguard_).mn_maxaddr = __kernel_asyncwork_stack_guard + PAGESIZE - 1;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

	/* bootidle */
	STN(bootidle).mn_part           = &STP(bootidle);
	STN(bootidle).mn_link.le_prev   = &STP(bootidle).mp_share.lh_first;
	STP(bootidle).mp_share.lh_first = &STN(bootidle);
	STN(bootidle).mn_minaddr        = __kernel_bootidle_stack;
	STN(bootidle).mn_maxaddr        = __kernel_bootidle_stack + KERNEL_IDLE_STACKSIZE - 1;
	STP(bootidle).mp_maxaddr        = (pos_t)(KERNEL_IDLE_STACKSIZE - 1);
	STP(bootidle).mp_mem.mc_start   = (physpage_t)loadfarptr(__kernel_bootidle_stack_page_p);
	STP(bootidle).mp_mem.mc_size    = CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	FORTASK(&bootidle, this_kernel_stackguard_).mn_minaddr = __kernel_bootidle_stack_guard;
	FORTASK(&bootidle, this_kernel_stackguard_).mn_maxaddr = __kernel_bootidle_stack_guard + PAGESIZE - 1;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

#undef STP
#undef STN

	FORTASK(&boottask, this_fs) = &fs_kernel;
	FORTASK(&bootidle, this_fs) = &fs_kernel;
#ifndef CONFIG_EVERYONE_IS_ROOT
	FORTASK(&boottask, this_cred) = &cred_kernel;
	FORTASK(&bootidle, this_cred) = &cred_kernel;
#endif /* !CONFIG_EVERYONE_IS_ROOT */
	FORTASK(&boottask, this_handle_manager) = &handle_manager_kernel;
	FORTASK(&bootidle, this_handle_manager) = &handle_manager_kernel;

	/* The stack of IDLE threads is executable in order to allow for hacking around .free restrictions. */
	FORTASK(&bootidle, this_kernel_stacknode_).mn_flags = (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD |
	                                                        MNODE_F_SHARED | MNODE_F_NOSPLIT | MNODE_F_NOMERGE |
	                                                        _MNODE_F_MPREPARED_KERNEL);

	mman_kernel.mm_threads.lh_first = &boottask;
	boottask.t_mman_tasks.le_prev  = &mman_kernel.mm_threads.lh_first;
	boottask.t_mman_tasks.le_next  = &asyncwork;
	asyncwork.t_mman_tasks.le_prev = &boottask.t_mman_tasks.le_next;
	asyncwork.t_mman_tasks.le_next = &bootidle;
	bootidle.t_mman_tasks.le_prev  = &asyncwork.t_mman_tasks.le_next;
	assert(bootidle.t_mman_tasks.le_next == NULL);

	boottask.t_refcnt  = 2; /* +1: scheduler chain, +1: public symbol `boottask' */
	asyncwork.t_refcnt = 2; /* +1: scheduler chain, +1: intern symbol `asyncwork' */
	bootidle.t_refcnt  = 2; /* +1: scheduler chain, +1: public symbol `bootidle' */

	boottask.t_flags  = TASK_FCRITICAL | TASK_FSTARTED | TASK_FRUNNING;
	asyncwork.t_flags = TASK_FCRITICAL | TASK_FSTARTED | TASK_FRUNNING | TASK_FKERNTHREAD;
	bootidle.t_flags  = TASK_FCRITICAL | TASK_FSTARTED | TASK_FKEEPCORE | TASK_FKERNTHREAD;

	/* Initialize the boot CPU's scheduler. */
	FORTASK(&boottask, this_sched_link).le_prev  = &FORCPU(&bootcpu, thiscpu_scheduler).s_running.lh_first;
	FORTASK(&boottask, this_sched_link).le_next  = &asyncwork;
	FORTASK(&asyncwork, this_sched_link).le_prev = &FORTASK(&boottask, this_sched_link).le_next;
	/*FORTASK(&asyncwork, this_sched_link).le_next = NULL;*/
	FORCPU(&bootcpu, thiscpu_scheduler).s_running.lh_first = &boottask;
	FORCPU(&bootcpu, thiscpu_scheduler).s_running_last     = &asyncwork;
	FORCPU(&bootcpu, thiscpu_scheduler).s_runcount         = 2;

	boottask.t_self  = &boottask;
	bootidle.t_self  = &bootidle;
	asyncwork.t_self = &asyncwork;

	FORCPU(&bootcpu, thiscpu_sched_current) = &boottask;

	kernel_initialize_scheduler_arch();
}

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler_callbacks)(void) {
	/* Execute initializers for the boot & idle thread. */
	pertask_init_t *iter;
	iter = __kernel_pertask_init_start;
	for (; iter < __kernel_pertask_init_end; ++iter) {
		(**iter)(&boottask);
		(**iter)(&bootidle);
		(**iter)(&asyncwork);
	}
}











/* Called with a lock to the kernel VM's treelock held. */
PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(FCALL task_destroy_raw_impl)(Toblockop(mman) *__restrict _lop,
                                     struct mman *__restrict UNUSED(mm)) {
	void *addr;
	size_t size;
	struct task *self;
	self = (struct task *)_lop;
	assertf(self != &boottask && self != &bootidle && self != &asyncwork,
	        "Cannot destroy the BOOT or IDLE task of CPU0\n"
	        "self       = %p\n"
	        "&boottask  = %p\n"
	        "&bootidle  = %p\n"
	        "&asyncwork = %p\n",
	        self, &boottask, &bootidle, &asyncwork);
	assert(mman_lock_writing(&mman_kernel));
	assert((self->t_flags & TASK_FTERMINATED) || !(self->t_flags & TASK_FSTARTED));

	/* Unlink + unmap the trampoline node. */
	mman_mappings_removenode(&mman_kernel, &FORTASK(self, this_trampoline_node));
	addr = mnode_getaddr(&FORTASK(self, this_trampoline_node));
	pagedir_unmapone(addr);
	mman_supersyncone(addr);
	pagedir_kernelunprepareone(addr);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	mman_mappings_removenode(&mman_kernel, &FORTASK(self, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
	mman_mappings_removenode(&mman_kernel, &FORTASK(self, this_kernel_stacknode_));
	addr = mnode_getaddr(&FORTASK(self, this_kernel_stacknode_));
	size = mnode_getsize(&FORTASK(self, this_kernel_stacknode_));
	pagedir_unmap(addr, size);
	mman_supersync(addr, size);
	pagedir_kernelunprepare(addr, size);

	/* Deallocate the kernel stack. */
	mpart_ll_freemem(&FORTASK(self, this_kernel_stackpart_));

	/* TODO: Use 2-step cleanup and free the task structure _after_ releasing
	 *       the  lock  to  the kernel  mman  (through use  of  a postlockop) */
	{
		REF struct mman *mm;
		mm = self->t_mman;
		if likely(LIST_ISBOUND(self, t_mman_tasks)) {
			mman_threadslock_acquire(mm);
			if likely(LIST_ISBOUND(self, t_mman_tasks))
				LIST_REMOVE(self, t_mman_tasks);
			mman_threadslock_release(mm);
		}
		heap_free(&kernel_locked_heap, self, self->t_heapsz, GFP_NORMAL);
		decref(mm);
	}
	return NULL;
}


typedef void (KCALL *pertask_fini_t)(struct task *__restrict self);
INTDEF pertask_fini_t __kernel_pertask_fini_start[];
INTDEF pertask_fini_t __kernel_pertask_fini_end[];

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_destroy)(struct task *__restrict self) {
	pertask_fini_t *iter;
	assert(self->t_refcnt == 0);
	assert(self->t_self == self);
	assert((self->t_flags & TASK_FTERMINATED) || !(self->t_flags & TASK_FSTARTED));

	/* Run task finalizers. */
	iter = __kernel_pertask_fini_start;
	for (; iter < __kernel_pertask_fini_end; ++iter)
		(**iter)(self);

	/* Destroy  the  task  structure,  and  unload  memory segments
	 * occupied by the thread, including its stack, and trampoline. */
	if (mman_lock_tryacquire(&mman_kernel)) {
		task_destroy_raw_impl((Toblockop(mman) *)self, &mman_kernel);
		mman_lock_release(&mman_kernel);
	} else {
		Toblockop(mman) *lop;
		/* Schedule the task to-be destroyed later. */
		lop           = (Toblockop(mman) *)self;
		lop->olo_func = &task_destroy_raw_impl;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops, lop, olo_link);
		_mman_lockops_reap(&mman_kernel);
	}
}

PUBLIC ATTR_MALLOC WUNUSED ATTR_RETNONNULL REF struct task *
(KCALL task_alloc)(struct mman *__restrict task_mman) THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct task *result;
	struct heapptr resptr;
	/* Allocate a new task structure. */
	resptr = heap_alloc(&kernel_locked_heap,
	                    (size_t)__kernel_pertask_size,
	                    GFP_LOCKED | GFP_PREFLT);
	result = (REF struct task *)resptr.hp_ptr;
	/* Copy the per-task initialization template. */
	memcpy(result, __kernel_pertask_start, (size_t)__kernel_pertask_size);
	result->t_heapsz = resptr.hp_siz;
	result->t_self   = result;
	incref(&mfile_ndef); /* FORTASK(result, this_kernel_stackpart_).mp_file */
#define STN(thread) FORTASK(&thread, this_kernel_stacknode_)
#define STP(thread) FORTASK(&thread, this_kernel_stackpart_)
	STN(*result).mn_part           = &STP(*result);
	STN(*result).mn_link.le_prev   = &STP(*result).mp_share.lh_first;
	STP(*result).mp_share.lh_first = &STN(*result);
	TRY {
		mpart_ll_allocmem(&FORTASK(result, this_kernel_stackpart_),
		                  CEILDIV(KERNEL_STACKSIZE, PAGESIZE));
		TRY {
			void *stack_addr;
			void *trampoline_addr;
			syscache_version_t version = SYSCACHE_VERSION_INIT;
again_lock_kernel_mman:
			mman_lock_acquire(&mman_kernel);
			stack_addr = mman_findunmapped(&mman_kernel,
			                               MHINT_GETADDR(KERNEL_MHINT_KERNSTACK),
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			                               CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE) + PAGESIZE,
#else /* CONFIG_HAVE_KERNEL_STACK_GUARD */
			                               CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE),
#endif /* !CONFIG_HAVE_KERNEL_STACK_GUARD */
			                               MHINT_GETMODE(KERNEL_MHINT_KERNSTACK));
			if unlikely(stack_addr == MAP_FAILED) {
				mman_lock_release(&mman_kernel);
				if (syscache_clear_s(&version))
					goto again_lock_kernel_mman;
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
				      CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE));
			}
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			FORTASK(result, this_kernel_stackguard_).mn_minaddr = (byte_t *)stack_addr;
			FORTASK(result, this_kernel_stackguard_).mn_maxaddr = (byte_t *)stack_addr + PAGESIZE - 1;
			stack_addr = (byte_t *)stack_addr + PAGESIZE;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */
			FORTASK(result, this_kernel_stacknode_).mn_minaddr = (byte_t *)stack_addr;
			FORTASK(result, this_kernel_stacknode_).mn_maxaddr = (byte_t *)stack_addr + KERNEL_STACKSIZE - 1;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepare(stack_addr, CEIL_ALIGN(KERNEL_STACKSIZE, PAGESIZE))) {
				mman_lock_release(&mman_kernel);
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

			/* Map the trampoline node. */
			trampoline_addr = mman_findunmapped(&mman_kernel,
			                                    MHINT_GETADDR(KERNEL_MHINT_TRAMPOLINE), PAGESIZE,
			                                    MHINT_GETMODE(KERNEL_MHINT_TRAMPOLINE));
			if unlikely(trampoline_addr == MAP_FAILED) {
				mman_lock_release(&mman_kernel);
				if (syscache_clear_s(&version))
					goto again_lock_kernel_mman;
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, PAGESIZE);
			}
			FORTASK(result, this_trampoline_node).mn_minaddr = (byte_t *)trampoline_addr;
			FORTASK(result, this_trampoline_node).mn_maxaddr = (byte_t *)trampoline_addr + PAGESIZE - 1;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepareone(trampoline_addr))
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			/* Load nodes into the kernel VM. */
			mman_mappings_insert(&mman_kernel, &FORTASK(result, this_trampoline_node));
			mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

			/* Map the stack into memory */
			mpart_mmap_force(&FORTASK(result, this_kernel_stackpart_), stack_addr,
			                 KERNEL_STACKSIZE, 0, PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			mman_lock_release(&mman_kernel);
		} EXCEPT {
			mpart_ll_ccfreemem(&FORTASK(result, this_kernel_stackpart_));
			RETHROW();
		}
	} EXCEPT {
		decref_nokill(&mfile_ndef); /* FORTASK(result, this_kernel_stackpart_).mp_file */
		heap_free(&kernel_locked_heap,
		          resptr.hp_ptr,
		          resptr.hp_siz,
		          GFP_NORMAL);
		RETHROW();
	}

	result->t_mman = task_mman;
	incref(task_mman);

	/* Run custom initializers. */
	TRY {
		pertask_init_t *iter;
		assert(!LIST_ISBOUND(result, t_mman_tasks));

		/* Insert the new task into the VM */
		mman_threadslock_acquire(task_mman);
		LIST_INSERT_HEAD(&task_mman->mm_threads, result, t_mman_tasks);
		mman_threadslock_release(task_mman);

		iter = __kernel_pertask_init_start;
		for (; iter < __kernel_pertask_init_end; ++iter)
			(**iter)(result);
	} EXCEPT {
		ATOMIC_WRITE(result->t_refcnt, 0);
		/* Destroy the task if an initializer threw another exception. */
		task_destroy(result);
		RETHROW();
	}
	return result;
}


#if 0
typedef void (KCALL *pertask_clone_t)(struct task *__restrict new_thread, uintptr_t flags);
INTDEF pertask_clone_t __kernel_pertask_clone_start[];
INTDEF pertask_clone_t __kernel_pertask_clone_end[];


/* High-level kernel interface for the clone(2) system call.
 * @param: clone_flags: Set of `TASK_CLONE_*' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct task *
(KCALL task_clone)(uintptr_t clone_flags)
		THROWS(E_BADALLOC, E_WOULDBLOCK) {
	REF struct task *result;
	if (clone_flags & TASK_CLONE_VM) {
		result = task_alloc(THIS_MMAN);
	} else {
		REF struct mman *result_mman = mman_fork();
		FINALLY_DECREF_UNLIKELY(result_mman);
		result = task_alloc(result_mman);
	}
	TRY {
		/* Invoke additional callbacks. */
		{
			pertask_clone_t *iter;
			for (iter = __kernel_pertask_clone_start;
			     iter < __kernel_pertask_clone_end; ++iter)
				(**iter)(result, clone_flags);
		}
	} EXCEPT {
		decref_likely(result);
		RETHROW();
	}
	return result;
}
#endif



/************************************************************************/
/* exit(), exit_group()                                                 */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_EXIT
DEFINE_SYSCALL1(void, exit, syscall_ulong_t, exit_code) {
	COMPILER_IMPURE();
	THROW(E_EXIT_THREAD, W_EXITCODE(exit_code & 0xff, 0));
}
#endif /* __ARCH_WANT_SYSCALL_EXIT */

#ifdef __ARCH_WANT_SYSCALL_EXIT_GROUP
DEFINE_SYSCALL1(void, exit_group, syscall_ulong_t, exit_code) {
	COMPILER_IMPURE();
	THROW(E_EXIT_PROCESS, W_EXITCODE(exit_code & 0xff, 0));
}
#endif /* __ARCH_WANT_SYSCALL_EXIT_GROUP */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_C */
