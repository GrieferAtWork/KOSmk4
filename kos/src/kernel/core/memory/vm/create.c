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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_CREATE_C
#define GUARD_KERNEL_SRC_MEMORY_VM_CREATE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/paging.h>
#include <kernel/driver.h>
#include <kernel/vm.h>
#include <sched/userkern.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

typedef void (KCALL *pervm_init_t)(struct vm *__restrict self) THROWS(...);
typedef NOBLOCK /*ATTR_NOTHROW*/void (KCALL *pervm_fini_t)(struct vm *__restrict self);
INTDEF pervm_init_t __kernel_pervm_init_start[];
INTDEF pervm_init_t __kernel_pervm_init_end[];
INTDEF pervm_fini_t __kernel_pervm_fini_start[];
INTDEF pervm_fini_t __kernel_pervm_fini_end[];

PUBLIC CALLBACK_LIST(void FCALL(struct vm *)) vm_oninit_callbacks = CALLBACK_LIST_INIT;
PUBLIC CALLBACK_LIST(void FCALL(struct vm *)) vm_onfini_callbacks = CALLBACK_LIST_INIT;

INTDEF byte_t __kernel_pervm_start[];
INTDEF byte_t __kernel_pervm_size[];

/* Allocate and initialize a new, empty VM for user-space. */
PUBLIC ATTR_RETNONNULL REF struct vm *KCALL
vm_alloc(void) THROWS(E_BADALLOC) {
	REF struct vm *result;
	struct heapptr resptr;
	/* TODO: On i386 (even with PAE), we mustn't allocate
	 *       physical memory above 4GiB for the VM itself! */
	resptr = heap_align(&kernel_locked_heap,
	                    PAGEDIR_ALIGN,
	                    0,
	                    PAGEDIR_SIZE + (size_t)__kernel_pervm_size,
	                    GFP_LOCKED | GFP_PREFLT);
	result = (REF struct vm *)resptr.hp_ptr;
	assert(IS_ALIGNED((uintptr_t)result, PAGEDIR_ALIGN));
	/* Copy the PER-VM initialization template. */
	memcpy((byte_t *)result + PAGEDIR_SIZE, __kernel_pervm_start,
	       (size_t)__kernel_pervm_size);
	/* Setup and initialize the VM's page directory. */
	result->v_pdir_phys = pagedir_translate((vm_virt_t)result);
	result->v_refcnt    = 1;
	assert(result->v_weakrefcnt == 1);
	result->v_tree      = &result->v_kernreserve;
	result->v_byaddr    = &result->v_kernreserve;
	result->v_heap_size = resptr.hp_siz;
	/*atomic_rwlock_init(&result->v_treelock);*/
	assert(result->v_tasks == NULL);
	/*atomic_rwlock_init(&result->v_tasklock);*/
	assert(result->v_deltasks == NULL);
	/*shared_rwlock_init(&result->v_dma_lock);*/
	result->v_kernreserve.vn_node.a_min = NULL;
	result->v_kernreserve.vn_node.a_max = NULL;
#ifdef HIGH_MEMORY_KERNEL
	result->v_kernreserve.vn_node.a_vmin = (vm_vpage_t)KERNEL_BASE_PAGE;
	result->v_kernreserve.vn_node.a_vmax = (vm_vpage_t)VM_VPAGE_MAX;
#else /* HIGH_MEMORY_KERNEL */
	result->v_kernreserve.vn_node.a_vmin = (vm_vpage_t)0;
	result->v_kernreserve.vn_node.a_vmax = (vm_vpage_t)KERNEL_MAX_PAGE;
#endif /* !HIGH_MEMORY_KERNEL */
	result->v_kernreserve.vn_byaddr.ln_pself = &result->v_byaddr;
	result->v_kernreserve.vn_byaddr.ln_next  = NULL;
	result->v_kernreserve.vn_prot = (VM_PROT_NONE | VM_PROT_PRIVATE
#ifndef CONFIG_NO_USERKERN_SEGMENT
	                                 | VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC
#endif /* !CONFIG_NO_USERKERN_SEGMENT */
	                                 );
	result->v_kernreserve.vn_flags = (VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_KERNPRT);
	result->v_kernreserve.vn_vm    = result;
#ifndef CONFIG_NO_USERKERN_SEGMENT
	/* NOTE: Don't chain the `v_kernreserve' node, or incref() the part/block,
	 *       since doing so is unnecessary.
	 *    -> The node must never be altered by regular functions, and already
	 *       has special handling associated with it during destruction, so
	 *       none of the functions that would normally rely on proper integration
	 *       should ever get to the point they could be bothered by the missing
	 *       integrity. */
	result->v_kernreserve.vn_part  = &userkern_segment_part;
	result->v_kernreserve.vn_block = &userkern_segment_block;
#else /* !CONFIG_NO_USERKERN_SEGMENT */
	result->v_kernreserve.vn_part  = NULL;
	result->v_kernreserve.vn_block = NULL;
#endif /* CONFIG_NO_USERKERN_SEGMENT */
	result->v_kernreserve.vn_guard = 0;

#ifdef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
	/* Initialize the page directory. */
	pagedir_init2(&result->v_pagedir, result->v_pdir_phys);
#endif /* CONFIG_PAGEDIR_INIT_IS_NOEXCEPT */
	TRY {
#ifndef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
		/* Initialize the page directory. */
		pagedir_init2(&result->v_pagedir, result->v_pdir_phys);
#endif /* !CONFIG_PAGEDIR_INIT_IS_NOEXCEPT */
		{
			/* Run per-VM initializers. */
			pervm_init_t *iter = __kernel_pervm_init_start;
			for (; iter < __kernel_pervm_init_end; ++iter)
				(**iter)(result);
			assert(iter == __kernel_pervm_init_end);
		}
		vm_oninit_callbacks(result);
	} EXCEPT {
		ATOMIC_WRITE(result->v_refcnt, 0);
		destroy(result);
		RETHROW();
	}
	return result;
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_free)(struct vm *__restrict self) {
	/* Actually free the VM. */
	assert(self != THIS_VM);
	heap_free(&kernel_heaps[GFP_LOCKED],
	          self,
	          self->v_heap_size,
	          GFP_LOCKED);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_destroy)(struct vm *__restrict self) {
	struct vm_node *iter, *next;
	/* Destroy all remaining nodes. */
	assert(self != THIS_VM);
	assert(self != &vm_kernel);
	assert(!self->v_tasks);
	assert(!self->v_deltasks);
	assert(self->v_kernreserve.vn_vm == self);
	/* Invoke per-VM finalizer callbacks. */
	vm_onfini_callbacks(self);
	{
		pervm_fini_t *iter = __kernel_pervm_fini_start;
		for (; iter < __kernel_pervm_fini_end; ++iter)
			(**iter)(self);
		assert(iter == __kernel_pervm_fini_end);
	}
	iter = self->v_byaddr;
	while (iter) {
		next = iter->vn_byaddr.ln_next;
		assert(next != iter);
		assert(iter->vn_vm == self);
		if (iter != &self->v_kernreserve)
			vm_node_destroy(iter);
		iter = next;
	}
#ifndef CONFIG_NO_USERKERN_SEGMENT
	assert(self->v_kernreserve.vn_part == &userkern_segment_part);
	assert(self->v_kernreserve.vn_block == &userkern_segment_block);
#endif /* !CONFIG_NO_USERKERN_SEGMENT */
	/* Finalize the underlying page directory. */
	pagedir_fini2(&self->v_pagedir, self->v_pdir_phys);
	/* Drop a weak reference, which is likely going to free the VM */
	weakdecref_likely(self);
}



/* Set the VM active within the calling thread, as well as
 * change page directories to make use of the new VM before
 * returning. */
PUBLIC void KCALL task_setvm(struct vm *__restrict newvm)
		THROWS(E_WOULDBLOCK) {
	pflag_t was;
	REF struct vm *oldvm;
	struct task *me = THIS_TASK;
again:
	was   = PREEMPTION_PUSHOFF();
	oldvm = FORTASK(me, _this_vm);
	if likely(oldvm != newvm) {
		if unlikely(!vm_tasklock_trywrite(newvm)) {
			PREEMPTION_POP(was);
			vm_tasklock_write(newvm);
			vm_tasklock_endwrite(newvm);
			goto again;
		}
		if (ATOMIC_READ(me->t_vm_tasks.ln_pself) != NULL) {
			if unlikely(!vm_tasklock_trywrite(oldvm)) {
				incref(oldvm);
				PREEMPTION_POP(was);
				vm_tasklock_endwrite(newvm);
				FINALLY_DECREF_UNLIKELY(oldvm);
				vm_tasklock_write(oldvm);
				vm_tasklock_endwrite(oldvm);
				goto again;
			}
			COMPILER_READ_BARRIER();
			if likely(ATOMIC_READ(me->t_vm_tasks.ln_pself) != NULL)
				LLIST_REMOVE(me, t_vm_tasks);
			vm_tasklock_endwrite(oldvm);
		}
		LLIST_INSERT(newvm->v_tasks, me, t_vm_tasks);
		vm_tasklock_endwrite(newvm);
		FORTASK(me, _this_vm) = incref(newvm);
		pagedir_set(newvm->v_pdir_phys_ptr);
		PREEMPTION_POP(was);
		decref(oldvm);
	} else {
		PREEMPTION_POP(was);
	}
}


/* Allocate an set a new VM for /bin/init during booting.
 * This function is used to assign a new VM for the initial user-space process,
 * so-as not to launch that process in the context of the special `kernel_vm',
 * which shouldn't contain mappings for anything user-space related. */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_user_vm)(void) {
	REF struct vm *uvm;
	uvm = vm_alloc();
	task_setvm(uvm);
	decref(uvm);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_CREATE_C */
