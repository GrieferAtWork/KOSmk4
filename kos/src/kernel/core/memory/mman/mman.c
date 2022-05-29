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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C 1
#define __WANT_MNODE_INIT

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/event.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/paging.h>
#include <sched/arch/userkern.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/userkern.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sync/atomic-lock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/except.h>
#include <kos/kernel/paging.h>

#include <assert.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifdef KERNELSPACE_HIGHMEM
#define KS_MINADDR ((uintptr_t)KERNELSPACE_BASE)
#define KS_MAXADDR ((uintptr_t)-1)
#elif defined(KERNELSPACE_LOWMEM)
#define KS_MINADDR ((uintptr_t)0)
#define KS_MAXADDR ((uintptr_t)(KERNELSPACE_END - 1))
#else /* KERNELSPACE_...MEM */
#define KS_MINADDR ((uintptr_t)KERNELSPACE_BASE)
#define KS_MAXADDR ((uintptr_t)(KERNELSPACE_END - 1))
#endif /* !KERNELSPACE_...MEM */

/* MMan exec() information */
PUBLIC ATTR_PERMMAN ATTR_ALIGN(struct mexecinfo) thismman_execinfo = {
	.mei_file = NULL,
	.mei_dent = NULL,
	.mei_path = NULL,
	.mei_peb  = NULL,
#ifdef __ARCH_HAVE_COMPAT
	.mei_peb_iscompat = false,
#endif /* __ARCH_HAVE_COMPAT */
};



/* A special per-MMAN node that is  used to cover the kernel  core
 * with a reservation within user-space memory manager. Within the
 * kernel mman itself, this field is undefined. */
PUBLIC ATTR_PERMMAN ATTR_ALIGN(struct mnode) thismman_kernel_reservation = {
	MNODE_INIT_mn_mement({}),
	MNODE_INIT_mn_minaddr(KS_MINADDR),
	MNODE_INIT_mn_maxaddr(KS_MAXADDR),
#ifdef CONFIG_NO_USERKERN_SEGMENT
	MNODE_INIT_mn_flags(MNODE_F_NOSPLIT | MNODE_F_NOMERGE |
	                    _MNODE_F_MPREPARED_KERNEL | MNODE_F_KERNPART),
	MNODE_INIT_mn_part(NULL), /* Reserved node */
#else /* CONFIG_NO_USERKERN_SEGMENT */
	MNODE_INIT_mn_flags(MNODE_F_NOSPLIT | MNODE_F_NOMERGE |
	                    MNODE_F_PREAD | MNODE_F_PWRITE | MNODE_F_PEXEC |
	                    _MNODE_F_MPREPARED_KERNEL | MNODE_F_KERNPART),
	MNODE_INIT_mn_part(&userkern_segment_part),
#endif /* !CONFIG_NO_USERKERN_SEGMENT */
	MNODE_INIT_mn_fspath(NULL),
	MNODE_INIT_mn_fsname(NULL),
	MNODE_INIT_mn_mman(NULL), /* Filled in during init */
	MNODE_INIT_mn_partoff(0),
	MNODE_INIT_mn_link(LIST_ENTRY_UNBOUND_INITIALIZER),
	MNODE_INIT_mn_writable(LIST_ENTRY_UNBOUND_INITIALIZER),
};

/* [0..n] Linked chain of pending  operations that should be  executed
 * (via a reap-mechanism) whenever the lock for this mman is released. */
PUBLIC ATTR_PERMMAN ATTR_ALIGN(Toblockop_slist(mman))
thismman_lockops = SLIST_HEAD_INITIALIZER(thismman_lockops);


/* Dynamic per-memory-manager init/fini callbacks.
 * XXX: Maybe get rid of these? (there aren't really ~that~ many of these) */
typedef NONNULL_T((1)) void (KCALL *permman_init_t)(struct mman *__restrict self) /*THROWS(...)*/;
typedef NOBLOCK NONNULL_T((1)) void NOTHROW_T(KCALL *permman_fini_t)(struct mman *__restrict self);
extern permman_init_t __kernel_permman_init_start[];
extern permman_init_t __kernel_permman_init_end[];
extern permman_fini_t __kernel_permman_fini_start[];
extern permman_fini_t __kernel_permman_fini_end[];

/* List of callbacks that should be invoked after mman_exec()
 * These  are called alongside stuff like `handman_cloexec()'
 * NOTE: The passed mman is always `THIS_MMAN', and is never `&mman_kernel' */
PUBLIC CALLBACK_LIST(void KCALL(void)) mman_onexec_callbacks = CALLBACK_LIST_INIT;
/* Mman initialization/finalization callbacks. */
PUBLIC CALLBACK_LIST(void FCALL(struct mman *)) mman_oninit_callbacks = CALLBACK_LIST_INIT;
PUBLIC CALLBACK_LIST(void FCALL(struct mman *)) mman_onfini_callbacks = CALLBACK_LIST_INIT;
PUBLIC CALLBACK_LIST(void FCALL(struct mman * /*newmman*/, struct mman * /*oldmman*/)) mman_onclone_callbacks = CALLBACK_LIST_INIT;

extern byte_t __kernel_permman_start[];
extern byte_t __kernel_permman_size[];


/* Architectures may define additional GFP_* flags used when allocating
 * the  backing memory of  a `struct mman' (and  in turn: its pagedir).
 *
 * This is needed by (e.g.) the i386 paging implementation to restrict
 * physical memory to 32-bit, as  nothing larger would fit into  %cr3. */
#ifndef ARCH_PAGEDIR_ALLOC_GFP
#define ARCH_PAGEDIR_ALLOC_GFP 0
#endif /* !ARCH_PAGEDIR_ALLOC_GFP */

/* Total size of `struct mman' */
#define _sizeof_mman ((size_t)__kernel_permman_size + PAGEDIR_SIZE)

/* Low-level (untraced) alloc/free for `struct mman' */
#define _mman_alloc_untraced()                                                         \
	(struct mman *)mman_map_kram(MHINT_GETADDR(KERNEL_MHINT_MMAN), _sizeof_mman,       \
	                             gfp_from_mapflags(MHINT_GETMODE(KERNEL_MHINT_MMAN)) | \
	                             ARCH_PAGEDIR_ALLOC_GFP | GFP_LOCKED | GFP_PREFLT,     \
	                             MAX_C(PAGEDIR_ALIGN, alignof(struct mman)))
#define _mman_free_untraced(self) \
	mman_unmap_kram(self, _sizeof_mman)

/* Raw alloc/free functions for `struct mman' */
#ifdef CONFIG_TRACE_MALLOC
PRIVATE ATTR_RETNONNULL WUNUSED struct mman *KCALL _mman_alloc(void) {
	void *result;
	result = _mman_alloc_untraced();
	TRY {
		/* Trace memory, excluding the leading page directory. */
		kmalloc_trace((byte_t *)result + PAGEDIR_SIZE,
		              (size_t)__kernel_permman_size,
		              GFP_NORMAL);
	} EXCEPT {
		_mman_free_untraced(result);
		RETHROW();
	}
	return (struct mman *)result;
}
#define _mman_free(self) \
	(kmalloc_untrace((byte_t *)(self) + PAGEDIR_SIZE), _mman_free_untraced(self))
#else /* CONFIG_TRACE_MALLOC */
#define _mman_alloc _mman_alloc_untraced
#define _mman_free  _mman_free_untraced
#endif /* !CONFIG_TRACE_MALLOC */





/* Memory manager reference counting control. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_free)(struct mman *__restrict self) {
	_mman_free(self);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mnode_tree_destroy)(struct mnode *root,
                                  struct mnode *skipme) {
	struct mnode *lhs, *rhs;
again:
	lhs = root->mn_mement.rb_lhs;
	rhs = root->mn_mement.rb_rhs;
	if (root != skipme)
		mnode_destroy(root);
	if (lhs) {
		if (rhs)
			mnode_tree_destroy(rhs, skipme);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mman_destroy)(struct mman *__restrict self) {
	assert(self != THIS_MMAN);
	assert(self != &mman_kernel);
	assert(LIST_EMPTY(&self->mm_threads));

	/* Finalize the underlying page directory. */
	pagedir_fini2(&self->mm_pagedir, self->mm_pagedir_p);

	/* Invoke per-VM finalizer callbacks. */
	mman_onfini_callbacks(self);
	{
		permman_fini_t *iter = __kernel_permman_fini_start;
		for (; iter < __kernel_permman_fini_end; ++iter)
			(**iter)(self);
		assert(iter == __kernel_permman_fini_end);
	}

	/* Finalize `thismman_execinfo' */
	xdecref(FORMMAN(self, thismman_execinfo).mei_file);
	xdecref(FORMMAN(self, thismman_execinfo).mei_dent);
	xdecref(FORMMAN(self, thismman_execinfo).mei_path);

	/* Destroy all of the memory-mappings within the tree. */
	mnode_tree_destroy(self->mm_mappings,
	                   &FORMMAN(self, thismman_kernel_reservation));

	/* Drop a weak reference, which is likely going to free the VM */
	weakdecref_likely(self);
}



/* Memory manager construction functions. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct mman *FCALL
mman_new(void) THROWS(E_BADALLOC) {
	REF struct mman *result;
	result = _mman_alloc();

	/* Copy the PER-VM initialization template. */
	memcpy((byte_t *)result + PAGEDIR_SIZE, __kernel_permman_start,
	       (size_t)__kernel_permman_size);

	/* Fill in mm-specific fields. */
	result->mm_pagedir_p  = (pagedir_phys_t)pagedir_translate(&result->mm_pagedir);
	result->mm_refcnt     = 1;
	result->mm_weakrefcnt = 1;
	_mman_init_wrlockpc_(result)
#ifdef CONFIG_USE_RWLOCK_FOR_MMAN
	atomic_rwlock_init(&result->mm_lock);
#else /* CONFIG_USE_RWLOCK_FOR_MMAN */
	atomic_lock_init(&result->mm_lock);
#endif /* !CONFIG_USE_RWLOCK_FOR_MMAN */
	FORMMAN(result, thismman_kernel_reservation).mn_mman = result;
	result->mm_mappings = &FORMMAN(result, thismman_kernel_reservation);
	/*LIST_INIT(&result->mm_writable);*/ /* Already done by the `memcpy()' */
	/*LIST_INIT(&result->mm_threads);*/  /* Already done by the `memcpy()' */
#ifndef CONFIG_NO_SMP
	/*atomic_lock_init(&result->mm_threadslock);*/ /* Already done by the `memcpy()' */
#endif /* !CONFIG_NO_SMP */

#ifdef ARCH_PAGEDIR_INIT_IS_NOEXCEPT
	/* Initialize the page directory. */
	pagedir_init2(&result->mm_pagedir, result->mm_pagedir_p);
#endif /* ARCH_PAGEDIR_INIT_IS_NOEXCEPT */
	TRY {
#ifndef ARCH_PAGEDIR_INIT_IS_NOEXCEPT
		/* Initialize the page directory. */
		pagedir_init2(&result->mm_pagedir, result->mm_pagedir_p);
#endif /* !ARCH_PAGEDIR_INIT_IS_NOEXCEPT */
		{
			/* Run per-VM initializers. */
			permman_init_t *iter = __kernel_permman_init_start;
			for (; iter < __kernel_permman_init_end; ++iter)
				(**iter)(result);
			assert(iter == __kernel_permman_init_end);
		}
		mman_oninit_callbacks(result);
	} EXCEPT {
		ATOMIC_WRITE(result->mm_refcnt, 0);
		destroy(result);
		RETHROW();
	}
	return result;
}







/* Lock that must be held when accessing the mman of some thread. */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_lock setmman_lock = ATOMIC_LOCK_INIT;
/* Return a pointer to the  mman-change-lock that must be held  when
 * accessing the `t_mman' field of another thread, or changing one's
 * own memory manager. */
#define task_mman_change_lock(thread) (&setmman_lock)
#endif /* !CONFIG_NO_SMP */



/* Set  the mman active within the calling thread, as well as
 * change page directories to make use of the new mman before
 * returning. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_setmman)(struct mman *__restrict newmman) {
	REF struct mman *oldmman;
	newmman = incref(newmman);
	oldmman = task_xchmman_inherit(newmman);
	decref(oldmman);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_setmman_inherit)(/*inherit(always)*/ REF struct mman *__restrict newmman) {
	REF struct mman *oldmman;
	oldmman = task_xchmman_inherit(newmman);
	decref(oldmman);
}

/* Same as `task_setmman()', but return a reference to the old mman. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_xchmman)(struct mman *__restrict newmman) {
	return task_xchmman_inherit(incref(newmman));
}

/* Same as `task_setmman()', but return a reference to the old mman. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_xchmman_inherit)(/*inherit(always)*/ REF struct mman *__restrict newmman) {
	REF struct mman *oldmman;
	struct task *me = THIS_TASK;
	preemption_flag_t was;
#ifndef CONFIG_NO_SMP
again:
#endif /* CONFIG_NO_SMP */
	preemption_pushoff(&was);
	oldmman = me->t_mman; /* Inherit reference */
#ifndef CONFIG_NO_SMP
	if unlikely(oldmman == newmman) {
		/* No-op (but must  check explicitly  to prevent  dead-
		 * lock from acquiring `newmman->mm_threadslock' twice) */
		preemption_pop(&was);
		return newmman;
	}

	/* Acquire all of the necessary locks. */
	if (!atomic_lock_tryacquire(task_mman_change_lock(me))) {
		preemption_pop(&was);
		while (!atomic_lock_available(task_mman_change_lock(me)))
			preemption_tryyield();
		goto again;
	}
	if unlikely(!mman_threadslock_tryacquire_nopr(newmman)) {
		atomic_lock_release(task_mman_change_lock(me));
		preemption_pop(&was);
		while (!mman_threadslock_available(newmman))
			preemption_tryyield();
		goto again;
	}
	if unlikely(!mman_threadslock_tryacquire_nopr(oldmman)) {
		mman_threadslock_release_nopr(newmman);
		/* Keep a reference  in case  we re-enable  interrupts,
		 * and an  RPC  changes  the mman  in  the  mean  time.
		 * Shouldn't happen as far as control flow logic  goes,
		 * but is actually something that's allowed to be done. */
		incref(oldmman);
		atomic_lock_release(task_mman_change_lock(me));
		preemption_pop(&was);
		while (!mman_threadslock_available(oldmman))
			preemption_tryyield();
		decref(oldmman);
		goto again;
	}
#endif /* !CONFIG_NO_SMP */

	/* All of the necessary locks have been acquired.
	 * With this in mind, we can do the actual transition atomically. */
	LIST_REMOVE(me, t_mman_tasks);
	LIST_INSERT_HEAD(&newmman->mm_threads, me, t_mman_tasks);
	me->t_mman = newmman; /* Inherit reference (2x) */

	/* Release locks */
#ifndef CONFIG_NO_SMP
	mman_threadslock_release_nopr(oldmman);
	mman_threadslock_release_nopr(newmman);
	atomic_lock_release(task_mman_change_lock(me));
#endif /* !CONFIG_NO_SMP */

	/* Set the new mman as the active manager for the current CPU.
	 * NOTE: To prevent the CPU from changing, do this before re-
	 *       enabling preemption. */
#if defined(CONFIG_NO_SMP) && !defined(__OPTIMIZE_SIZE__)
	if (oldmman != newmman)
#endif /* CONFIG_NO_SMP && !__OPTIMIZE_SIZE__ */
	{
		cpu_setmman_ex(me->t_cpu, newmman);
	}
	preemption_pop(&was);

	/* Return a reference to the old mman. */
	return oldmman;
}



/* Return the active mman of the given `thread' */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mman *
NOTHROW(FCALL task_getmman)(struct task *__restrict thread) {
	REF struct mman *result;
	atomic_lock_acquire_smp(task_mman_change_lock(thread));
	result = incref(thread->t_mman);
	atomic_lock_release_smp(task_mman_change_lock(thread));
	return result;
}


/* Allocate an set a new mman for /bin/init during booting.
 * This function is used to assign a new mman for the initial user-space process,
 * so-as not to launch that process in the context of the special  `mman_kernel',
 * which shouldn't contain mappings for anything user-space related. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_user_mman)(void) {
	REF struct mman *umm;
	umm = mman_new();
	task_setmman_inherit(umm);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MMAN_C */
