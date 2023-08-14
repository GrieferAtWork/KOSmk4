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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_C
#define GUARD_KERNEL_SRC_SCHED_TASK_C 1
#define __WANT_MNODE_INIT
#define __WANT_MPART_INIT
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <kernel/except.h>
#include <kernel/fs/fs.h>
#include <kernel/handman.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h> /* this_trampoline_node */
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/panic.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <sched/async.h>
#include <sched/comm.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/scheduler.h>
#include <sched/task-clone.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>

#include <asm/defsym.h>
#include <asm/farptr.h>
#include <sys/wait.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

DECL_BEGIN

INTDEF byte_t __kernel_pertask_start[];
INTDEF byte_t __kernel_pertask_size[];

/* Assert that static task-offsets are correct */
static_assert(offsetof(struct task, t_self) == OFFSET_TASK_SELF);
static_assert(offsetof(struct task, t_refcnt) == OFFSET_TASK_REFCNT);
static_assert(offsetof(struct task, t_flags) == OFFSET_TASK_FLAGS);
static_assert(offsetof(struct task, t_cpu) == OFFSET_TASK_CPU);
static_assert(offsetof(struct task, t_mman) == OFFSET_TASK_MMAN);
static_assert(offsetof(struct task, t_mman_tasks.le_next) == OFFSET_TASK_MMAN_TASKS_NEXT);
static_assert(offsetof(struct task, t_mman_tasks.le_prev) == OFFSET_TASK_MMAN_TASKS_PREV);
static_assert(offsetof(struct task, t_heapsz) == OFFSET_TASK_HEAPSZ);
static_assert(offsetof(struct task, t_state) == OFFSET_TASK_STATE);
static_assert(offsetof(struct task, _t_next) == OFFSET_TASK__NEXT);
static_assert(sizeof(struct task) == SIZEOF_STRUCT_TASK);
static_assert(offsetof(struct cpu, c_id) == OFFSET_CPU_ID);
static_assert(offsetof(struct cpu, c_state) == OFFSET_CPU_STATE);
#ifdef OFFSET_CPU__PAD
static_assert(offsetof(struct cpu, _c_pad) == OFFSET_CPU__PAD);
#endif /* OFFSET_CPU__PAD */
#ifdef OFFSET_CPU_PDIR
static_assert(offsetof(struct cpu, c_pdir) == OFFSET_CPU_PDIR);
#endif /* OFFSET_CPU_PDIR */


PRIVATE ATTR_USED ATTR_SECTION(".data.pertask.head")
ATTR_ALIGN(struct task) task_header = {
	.t_self       = NULL, /* Filled in by the initializer. */
	.t_refcnt     = 1,
	.t_flags      = TASK_FNORMAL,
	.t_cpu        = &bootcpu,
	.t_mman       = &mman_kernel, /* NOTE: Initialize changed to `NULL' in `kernel_initialize_scheduler_after_smp()' */
	.t_mman_tasks = LIST_ENTRY_UNBOUND_INITIALIZER,
	.t_heapsz     = (size_t)__kernel_pertask_size,
	{ .t_state = NULL }
};

DATDEF ATTR_PERTASK struct mnode this_trampoline_node_ ASMNAME("this_trampoline_node");
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
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct mpart) this_kernel_stackpart_ = {
	MPART_INIT_mp_refcnt(1),
	MPART_INIT_mp_flags(MPART_F_NOSPLIT | MPART_F_NOMERGE |
	                    MPART_F_MLOCK_FROZEN | MPART_F_MLOCK),
	MPART_INIT_mp_state(MPART_ST_MEM), /* NOTE: Initialize changed to `MPART_ST_VOID' in `kernel_initialize_scheduler_after_smp()' */
	MPART_INIT_mp_file(&mfile_zero),
	MPART_INIT_mp_copy(LIST_HEAD_INITIALIZER(this_kernel_stackpart_.mp_copy)),
	MPART_INIT_mp_share({ &this_kernel_stacknode_ }),
	MPART_INIT_mp_lockops(SLIST_HEAD_INITIALIZER(this_kernel_stackpart_.mp_lockops)),
	MPART_INIT_mp_allparts(LIST_ENTRY_UNBOUND_INITIALIZER),
	MPART_INIT_mp_changed({}),
	MPART_INIT_mp_minaddr(0),
	MPART_INIT_mp_maxaddr(KERNEL_STACKSIZE - 1),
	MPART_INIT_mp_filent({ {} }),
	MPART_INIT_mp_blkst_ptr(NULL),
	MPART_INIT_mp_mem(0 /* Filled later */, CEILDIV(KERNEL_STACKSIZE, PAGESIZE)),
	MPART_INIT_mp_meta(NULL)
};

PUBLIC ATTR_PERTASK ATTR_ALIGN(struct mnode) this_kernel_stacknode_ = {
	MNODE_INIT_mn_mement({ {} }),
	MNODE_INIT_mn_minaddr(MAP_FAILED),
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
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct mnode) this_kernel_stackguard_ = {
	MNODE_INIT_mn_mement({}),
	MNODE_INIT_mn_minaddr(MAP_FAILED),
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






INTDEF FREE void NOTHROW(KCALL kernel_initialize_scheduler_arch)(void);

LOCAL ATTR_FREETEXT void
NOTHROW(KCALL initialize_predefined_trampoline)(struct task *__restrict self,
                                                   PAGEDIR_PAGEALIGNED void *addr) {
	FORTASK(self, this_trampoline_node_).mn_minaddr = (byte_t *)addr;
	FORTASK(self, this_trampoline_node_).mn_maxaddr = (byte_t *)addr + PAGESIZE - 1;
	/* Load the trampoline node into the kernel VM. */
	assert(FORTASK(self, this_trampoline_node_).mn_mman == &mman_kernel);
	mman_mappings_insert(&mman_kernel, &FORTASK(self, this_trampoline_node_));
}

#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
/* Prepare 2 consecutive (and 2-page aligned) pages of  virtual
 * memory for the purpose of doing the initial prepare required
 * for `THIS_TRAMPOLINE_PAGE' of `boottask' and also `bootidle' */
INTDEF NOBLOCK FREE WUNUSED void *
NOTHROW(FCALL kernel_initialize_boot_trampolines)(void);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

PUBLIC ATTR_PERTASK ATTR_ALIGN(struct exception_info) this_exception_info = {};


/* Define relocations */
DEFINE_PERTASK_RELOCATION(this_task + OFFSET_TASK_SELF);
DEFINE_PERTASK_RELOCATION(this_kernel_stacknode + OFFSET_MNODE_PART);
DEFINE_PERTASK_RELOCATION(this_kernel_stacknode + OFFSET_MNODE_LINK_PREV);
DEFINE_PERTASK_RELOCATION(this_kernel_stackpart + OFFSET_MPART_SHARE_FIRST);

/* Define PERTASK alias symbols */
DEFINE_PUBLIC_SYMBOL(this_task, 0, SIZEOF_STRUCT_TASK);
#define DEFINE_FIELD_SYMBOL(name, BASE, OFFSET, SIZEOF, T, field) \
	static_assert(offsetof(T, field) == (OFFSET));                \
	static_assert(sizeoffield(T, field) == (SIZEOF));             \
	DEFINE_PUBLIC_SYMBOL(name, (BASE) + (OFFSET), SIZEOF)

DEFINE_FIELD_SYMBOL(this_cpu, 0, OFFSET_TASK_CPU, SIZEOF_POINTER, struct task, t_cpu);
DEFINE_FIELD_SYMBOL(this_mman, 0, OFFSET_TASK_MMAN, SIZEOF_POINTER, struct task, t_mman);
DEFINE_FIELD_SYMBOL(this_sstate, 0, OFFSET_TASK_STATE, SIZEOF_POINTER, struct task, t_state);
DEFINE_FIELD_SYMBOL(this_exception_code, this_exception_info, OFFSET_EXCEPTION_INFO_CODE, __SIZEOF_EXCEPT_CODE_T__, struct exception_info, ei_code);
DEFINE_FIELD_SYMBOL(this_exception_data, this_exception_info, OFFSET_EXCEPTION_INFO_DATA, __SIZEOF_EXCEPTION_DATA, struct exception_info, ei_data);
DEFINE_FIELD_SYMBOL(this_exception_state, this_exception_info, OFFSET_EXCEPTION_INFO_STATE, __SIZEOF_EXCEPT_REGISTER_STATE, struct exception_info, ei_state);
DEFINE_FIELD_SYMBOL(this_exception_class, this_exception_info, OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_CLASS, __SIZEOF_EXCEPT_CLASS_T__, struct exception_info, ei_class);
DEFINE_FIELD_SYMBOL(this_exception_subclass, this_exception_info, OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_SUBCLASS, __SIZEOF_EXCEPT_SUBCLASS_T__, struct exception_info, ei_subclass);
DEFINE_FIELD_SYMBOL(this_exception_args, this_exception_info, OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_ARGS, EXCEPTION_DATA_POINTERS * SIZEOF_POINTER, struct exception_info, ei_data.e_args);
DEFINE_FIELD_SYMBOL(this_exception_flags, this_exception_info, OFFSET_EXCEPTION_INFO_FLAGS, 1, struct exception_info, ei_flags);
DEFINE_FIELD_SYMBOL(this_exception_faultaddr, this_exception_info, OFFSET_EXCEPTION_INFO_DATA + __OFFSET_EXCEPTION_DATA_FAULTADDR, SIZEOF_POINTER, struct exception_info, ei_data.e_faultaddr);
#ifdef OFFSET_EXCEPTION_INFO_TRACE
DEFINE_FIELD_SYMBOL(this_exception_trace, this_exception_info, OFFSET_EXCEPTION_INFO_TRACE, EXCEPT_BACKTRACE_SIZE * SIZEOF_POINTER, struct exception_info, ei_trace);
#else /* OFFSET_EXCEPTION_INFO_TRACE */
DEFINE_PUBLIC_SYMBOL(this_exception_trace, 0, 0);
#endif /* !OFFSET_EXCEPTION_INFO_TRACE */
DEFINE_FIELD_SYMBOL(thiscpu_id, 0, OFFSET_CPU_ID, __SIZEOF_INT__, struct cpu, c_id);
#ifndef CONFIG_NO_SMP
DEFINE_FIELD_SYMBOL(thiscpu_pdir, 0, OFFSET_CPU_PDIR, __SIZEOF_PAGEDIR_PHYS_T__, struct cpu, c_pdir);
#else /* !CONFIG_NO_SMP */
DEFINE_PUBLIC_SYMBOL(thiscpu_pdir, 0, 0);
#endif /* CONFIG_NO_SMP */
DEFINE_FIELD_SYMBOL(thiscpu_state, 0, OFFSET_CPU_STATE, 2, struct cpu, c_state);
DEFINE_FIELD_SYMBOL(thismman_pagedir_p, 0, OFFSET_MMAN_PAGEDIR_P, __SIZEOF_PAGEDIR_PHYS_T__, struct mman, mm_pagedir_p);
#undef DEFINE_FIELD_SYMBOL


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

INTDEF struct taskpid boottask_pid;
INTDEF struct taskpid bootcpu_idle_pid;
INTDEF struct taskpid asyncwork_pid;



INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler_after_smp)(void) {
	/* This  right here is needed for `clone(2)', but until this point, we had the
	 * task template's mman  field point  at the kernel  mman, thus  automatically
	 * initializing it correctly for all of the statically allocated threads, such
	 * as CPU IDLE threads, as well as boottask/bootidle and asyncwork. */
	struct task *task_template;
	task_template = (struct task *)__kernel_pertask_start;
	assert(task_template->t_mman == &mman_kernel);
	assert(FORTASK(task_template, this_kernel_stackpart_).mp_state == MPART_ST_MEM);
	assert(FORTASK(task_template, this_fs) == &fs_kernel);
	assert(FORTASK(task_template, this_handman) == &handman_kernel);

	/* All of the following are set by task_clone(), which also expects
	 * these pre-initializations (which matter when it comes to cleanup
	 * of partially constructed tasks during errors) */
	task_template->t_mman                                   = NULL;
	FORTASK(task_template, this_kernel_stackpart_).mp_state = MPART_ST_VOID;
	FORTASK(task_template, this_fs)                         = NULL;
	FORTASK(task_template, this_handman)                    = NULL;
#ifndef CONFIG_KERNEL_EVERYONE_IS_ROOT
	assert(FORTASK(task_template, this_cred) == &cred_kernel);
	FORTASK(task_template, this_cred) = NULL;
#endif /* !CONFIG_KERNEL_EVERYONE_IS_ROOT */
}

/* Defined in "mman/driver.c" -- dirent with the string "/os/kernel.bin" */
extern struct fdirent kernel_driver_fsname;

INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_scheduler)(void) {
	void *boot_trampoline_pages;

	/* Apply relocations to static threads. */
	_task_init_relocations(&boottask);
	_task_init_relocations(&bootidle);
	_task_init_relocations(&asyncwork);

	/* Fill in task PID pointers. */
	FORTASK(&boottask, this_taskpid)  = &boottask_pid;
	FORTASK(&bootidle, this_taskpid)  = &bootcpu_idle_pid;
	FORTASK(&asyncwork, this_taskpid) = &asyncwork_pid;

	/* Assign task command names. */
#ifdef CONFIG_HAVE_KERNEL_TASK_COMM
#define SET_TASK_NAME(thread, name)                         \
	memcpy(FORTASK(thread, this_comm), name,                \
	       MIN_C(COMPILER_STRLEN(name), TASK_COMM_LEN - 1), \
	       sizeof(char))
	SET_TASK_NAME(&boottask, "boot");
	SET_TASK_NAME(&bootidle, "idle0");
	SET_TASK_NAME(&asyncwork, "async0");
#undef SET_TASK_NAME
#endif /* CONFIG_HAVE_KERNEL_TASK_COMM */

	/* Assign exec information to `mman_kernel'.
	 * This might not be the perfect place to do so, but since I don't want to  add
	 * a initializer just to do this one thing, we might as well fill in that field
	 * here! */
	FORMMAN(&mman_kernel, thismman_execinfo.mei_dent) = &kernel_driver_fsname;

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
	STN(boottask).mn_minaddr      = __kernel_boottask_stack;
	STN(boottask).mn_maxaddr      = __kernel_boottask_stack + KERNEL_STACKSIZE - 1;
	STP(boottask).mp_mem.mc_start = (physpage_t)loadfarptr(__kernel_boottask_stack_page_p);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	FORTASK(&boottask, this_kernel_stackguard_).mn_minaddr = __kernel_boottask_stack_guard;
	FORTASK(&boottask, this_kernel_stackguard_).mn_maxaddr = __kernel_boottask_stack_guard + PAGESIZE - 1;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

	/* asyncwork */
	STN(asyncwork).mn_minaddr      = __kernel_asyncwork_stack;
	STN(asyncwork).mn_maxaddr      = __kernel_asyncwork_stack + KERNEL_STACKSIZE - 1;
	STP(asyncwork).mp_mem.mc_start = (physpage_t)loadfarptr(__kernel_asyncwork_stack_page_p);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	FORTASK(&asyncwork, this_kernel_stackguard_).mn_minaddr = __kernel_asyncwork_stack_guard;
	FORTASK(&asyncwork, this_kernel_stackguard_).mn_maxaddr = __kernel_asyncwork_stack_guard + PAGESIZE - 1;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

	/* bootidle */
	STN(bootidle).mn_minaddr      = __kernel_bootidle_stack;
	STN(bootidle).mn_maxaddr      = __kernel_bootidle_stack + KERNEL_IDLE_STACKSIZE - 1;
	STP(bootidle).mp_maxaddr      = (pos_t)(KERNEL_IDLE_STACKSIZE - 1);
	STP(bootidle).mp_mem.mc_start = (physpage_t)loadfarptr(__kernel_bootidle_stack_page_p);
	STP(bootidle).mp_mem.mc_size  = CEILDIV(KERNEL_IDLE_STACKSIZE, PAGESIZE);
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	FORTASK(&bootidle, this_kernel_stackguard_).mn_minaddr = __kernel_bootidle_stack_guard;
	FORTASK(&bootidle, this_kernel_stackguard_).mn_maxaddr = __kernel_bootidle_stack_guard + PAGESIZE - 1;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

#undef STP
#undef STN

	/* The stack of IDLE threads is executable in order to allow for hacking around .free restrictions. */
	FORTASK(&bootidle, this_kernel_stacknode_).mn_flags = (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD |
	                                                       MNODE_F_SHARED | MNODE_F_NOSPLIT | MNODE_F_NOMERGE |
	                                                       _MNODE_F_MPREPARED_KERNEL);

	mman_kernel.mm_threads.lh_first = &boottask;
	boottask.t_mman_tasks.le_prev   = &mman_kernel.mm_threads.lh_first;
	boottask.t_mman_tasks.le_next   = &asyncwork;
	asyncwork.t_mman_tasks.le_prev  = &boottask.t_mman_tasks.le_next;
	asyncwork.t_mman_tasks.le_next  = &bootidle;
	bootidle.t_mman_tasks.le_prev   = &asyncwork.t_mman_tasks.le_next;
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

	FORCPU(&bootcpu, thiscpu_sched_current) = &boottask;

	kernel_initialize_scheduler_arch();
}










PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL task_destroy_raw_impl_post)(Tobpostlockop(mman) *__restrict _lop,
                                          struct mman *__restrict UNUSED(mm)) {
	struct task *self;
	self = (struct task *)_lop;

	/* Deallocate physical memory once used by the kernel stack. */
	mpart_ll_freemem(&FORTASK(self, this_kernel_stackpart_));

	/* Free the backing memory of the task structure itself. */
	heap_free(&kernel_locked_heap, self, self->t_heapsz, GFP_LOCKED);
}

/* Called while a lock to the kernel mman is held. */
PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(FCALL task_destroy_raw_impl)(Toblockop(mman) *__restrict _lop,
                                     struct mman *__restrict UNUSED(mm)) {
	void *addr;
	size_t size;
	struct task *self;
	self = (struct task *)_lop;

	/* Unlink + unmap the trampoline node. */
	mman_mappings_removenode(&mman_kernel, &FORTASK(self, this_trampoline_node_));

	/* The  `mn_writable' field is only valid when  a part is set, which must
	 * not be the case for the trampoline node (which is a reserved mapping!) */
	assert(FORTASK(self, this_trampoline_node_).mn_part == NULL);
	addr = mnode_getaddr(&FORTASK(self, this_trampoline_node_));
	pagedir_unmapone(addr);
	mman_supersyncone(addr);
	pagedir_kernelunprepareone(addr);

#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
	/* The  `mn_writable' field is only valid when  a part is set, which must
	 * not be the case for the stackguard node (which is a reserved mapping!) */
	assert(FORTASK(self, this_kernel_stackguard_).mn_part == NULL);
	mman_mappings_removenode(&mman_kernel, &FORTASK(self, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

	assert(FORTASK(self, this_kernel_stacknode_).mn_part == &FORTASK(self, this_kernel_stackpart_));
	if unlikely(LIST_ISBOUND(&FORTASK(self, this_kernel_stacknode_), mn_writable))
		LIST_REMOVE(&FORTASK(self, this_kernel_stacknode_), mn_writable);
	mman_mappings_removenode(&mman_kernel, &FORTASK(self, this_kernel_stacknode_));
	addr = mnode_getaddr(&FORTASK(self, this_kernel_stacknode_));
	size = mnode_getsize(&FORTASK(self, this_kernel_stacknode_));
	pagedir_unmap(addr, size);
	mman_supersync(addr, size);
	pagedir_kernelunprepare(addr, size);

	/* Use 2-step cleanup and free the task structure _after_ releasing
	 * the  lock  to  the kernel  mman  (through use  of  a postlockop) */
	((Tobpostlockop(mman) *)_lop)->oplo_func = &task_destroy_raw_impl_post;
	return (Tobpostlockop(mman) *)_lop;
}


typedef void (KCALL *pertask_fini_t)(struct task *__restrict self);
INTDEF pertask_fini_t __kernel_pertask_fini_start[];
INTDEF pertask_fini_t __kernel_pertask_fini_end[];

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_unmap_stack_and_free)(struct task *__restrict self) {
	/* Destroy  the  task  structure,  and  unload  memory segments
	 * occupied by the thread, including its stack, and trampoline. */
	if (mman_lock_tryacquire(&mman_kernel)) {
		Tobpostlockop(mman) *post;
		post = task_destroy_raw_impl((Toblockop(mman) *)self, &mman_kernel);
		mman_lock_release(&mman_kernel);
		assert(post);
		(*post->oplo_func)(post, &mman_kernel);
	} else {
		Toblockop(mman) *lop;

		/* Schedule the task to-be destroyed later. */
		lop           = (Toblockop(mman) *)self;
		lop->olo_func = &task_destroy_raw_impl;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops, lop, olo_link);
		_mman_lockops_reap(&mman_kernel);
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_destroy)(struct task *__restrict self) {
	REF struct mman *mm;
	pertask_fini_t *iter;
	assertf(self != &boottask && self != &bootidle && self != &asyncwork,
	        "Cannot destroy the BOOT or IDLE task of CPU0\n"
	        "self       = %p\n"
	        "&boottask  = %p\n"
	        "&bootidle  = %p\n"
	        "&asyncwork = %p\n",
	        self, &boottask, &bootidle, &asyncwork);
	assert(self->t_refcnt == 0);
	assert(self->t_self == self);
	assert((self->t_flags & TASK_FTERMINATED) || !(self->t_flags & TASK_FSTARTED));

	/* Run task finalizers. */
	iter = __kernel_pertask_fini_start;
	for (; iter < __kernel_pertask_fini_end; ++iter)
		(**iter)(self);

	/* Remove from the mman's task list. */
	mm = self->t_mman;
	if likely(LIST_ISBOUND(self, t_mman_tasks)) {
		mman_threadslock_acquire(mm);
		if likely(LIST_ISBOUND(self, t_mman_tasks))
			LIST_REMOVE(self, t_mman_tasks);
		mman_threadslock_release(mm);
	}
	decref(mm);

	/* Destroy  the  task  structure,  and  unload  memory segments
	 * occupied by the thread, including its stack, and trampoline. */
	task_unmap_stack_and_free(self);
}

PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct task *
(KCALL task_alloc)(struct mman *__restrict task_mman) THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct task *result;
	heapptr_t resptr;

	/* Allocate a new task structure. */
	resptr = heap_alloc(&kernel_locked_heap,
	                    (size_t)__kernel_pertask_size,
	                    GFP_LOCKED | GFP_PREFLT);
	result = (REF struct task *)heapptr_getptr(resptr);

	/* Copy the per-task initialization template. */
	memcpy(result, __kernel_pertask_start, (size_t)__kernel_pertask_size);
	result->t_heapsz = heapptr_getsiz(resptr);
	_task_init_relocations(result);
	TRY {
		mpart_ll_allocmem(&FORTASK(result, this_kernel_stackpart_),
		                  CEILDIV(KERNEL_STACKSIZE, PAGESIZE));

		/* In order to make it possible to (safely) allocate small O_DIRECT buffers
		 * on kernel stacks, we have to manually clear the `page_iszero()' bits for
		 * backing memory of kernel stacks.
		 *
		 * Because mfile_ops::mo_(load|save)blocks is allowed to make use of  said
		 * bit in order to speed up initialization in those cases where the target
		 * buffer needs to be filled with all zeroes. As such, physical pages  for
		 * which `page_iszero()' returns true will  be skipped in this  situation.
		 * However, for kernel stacks that is most probably no longer the case  at
		 * the time the operator is invoked, so to work around this issue, we must
		 * enforce a consistent state of the  iszero bit for kernel stacks,  which
		 * is done by clearing them here. */
		mpart_ll_resetzero(&FORTASK(result, this_kernel_stackpart_));

		TRY {
			void *stack_addr;
			void *trampoline_addr;
			ccstate_t version = CCSTATE_INIT;
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
				if (system_cc_s(&version))
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
				if (system_cc_s(&version))
					goto again_lock_kernel_mman;
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, PAGESIZE);
			}
			FORTASK(result, this_trampoline_node_).mn_minaddr = (byte_t *)trampoline_addr;
			FORTASK(result, this_trampoline_node_).mn_maxaddr = (byte_t *)trampoline_addr + PAGESIZE - 1;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
			if unlikely(!pagedir_prepareone(trampoline_addr))
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
			/* Load nodes into the kernel VM. */
			mman_mappings_insert(&mman_kernel, &FORTASK(result, this_trampoline_node_));
			mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stacknode_));
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
			mman_mappings_insert(&mman_kernel, &FORTASK(result, this_kernel_stackguard_));
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

			/* Map the stack into memory */
			mpart_mmap_force(&FORTASK(result, this_kernel_stackpart_), stack_addr,
			                 KERNEL_STACKSIZE, 0, PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
			mman_lock_release(&mman_kernel);
		} EXCEPT {
			mpart_ll_ccfreemem(&FORTASK(result, this_kernel_stackpart_));
			RETHROW();
		}
	} EXCEPT {
		heap_free(&kernel_locked_heap,
		          heapptr_getptr(resptr),
		          heapptr_getsiz(resptr),
		          GFP_LOCKED);
		RETHROW();
	}
	result->t_mman = task_mman;
	incref(task_mman);
	assert(!LIST_ISBOUND(result, t_mman_tasks));

	/* Insert the new task into the VM */
	mman_threadslock_acquire(task_mman);
	LIST_INSERT_HEAD(&task_mman->mm_threads, result, t_mman_tasks);
	mman_threadslock_release(task_mman);
	return result;
}



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
