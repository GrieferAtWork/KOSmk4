/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef GUARD_KERNEL_SRC_MEMORY_COREBASE_C
#define GUARD_KERNEL_SRC_MEMORY_COREBASE_C 1
#define _KOS_SOURCE 1

#include "corebase.h"

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/printk.h>
#include <kernel/vm.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

struct pending_free_part {
	struct pending_free_part *next;
};


PRIVATE ATTR_BSS ATTR_ALIGNED(PAGESIZE)
struct vm_corepage vm_corepage_start;


/* Core page controller globals. */
INTERN DEFINE_ATOMIC_RWLOCK(vm_corepage_lock);
INTERN struct vm_corepage *vm_corepage_head = &vm_corepage_start;
INTERN size_t vm_corepage_free = VM_COREPAIRS_PER_PAGE;
PRIVATE ATTR_READMOSTLY struct pending_free_part *pending_free = NULL;


/* The mask of the last word of the is-used bitset that must be
 * matched for that word to be considered to only represent FREE parts. */
#define LAST_ALL_USED_MASK                                                                \
	(((uintptr_t)1 << (BITSOF(uintptr_t) -                                                \
	                   ((COMPILER_LENOF(((struct vm_corepage_controller *)0)->cpc_used) * \
	                     BITSOF(uintptr_t)) -                                             \
	                    VM_COREPAIRS_PER_PAGE))) -                                        \
	 1)


PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL corepage_hasfree)(struct vm_corepage const *__restrict self) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(self->cp_ctrl.cpc_used) - 1; ++i) {
		if (self->cp_ctrl.cpc_used[i] != (uintptr_t)-1)
			return true;
	}
	return self->cp_ctrl.cpc_used[COMPILER_LENOF(self->cp_ctrl.cpc_used) - 1] != LAST_ALL_USED_MASK;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(KCALL corepage_hasused)(struct vm_corepage const *__restrict self) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(self->cp_ctrl.cpc_used); ++i) {
		if (self->cp_ctrl.cpc_used[i] != 0)
			return true;
	}
	return false;
}


PRIVATE NONNULL((1)) void
NOTHROW(KCALL do_free_part)(void *__restrict part) {
	struct vm_corepage *page;
	unsigned int index, i;
	uintptr_t mask;
	page  = VM_COREPAGE_OF(part);
	index = (union vm_corepart *)part - page->cp_parts;
	assertf(&page->cp_parts[index] == (union vm_corepart *)part,
	        "Invalid COREPART pointer: %p", part);
	i    = index / BITSOF(uintptr_t);
	mask = (uintptr_t)1 << (index % BITSOF(uintptr_t));
	assertf(page->cp_ctrl.cpc_used[i] & mask,
	        "COREPART %p (page %p, index %u) is not marked as used",
	        part, page, index);
	page->cp_ctrl.cpc_used[i] &= ~mask;
	++vm_corepage_free;
	if (vm_corepage_free >= (VM_COREPAIRS_PER_PAGE + 4)) {
		/* Check if the associated page has become fully
		 * unused, in which case we're able to unload it.
		 * Also: Never unmap the initial start-page! */
		if (page != &vm_corepage_start && !corepage_hasused(page)) {
			/* Get rid of this page! */
			struct vm_corepage **ppage;
			ppage = &vm_corepage_head;
			while (*ppage != page) {
				assertf(*ppage,
				        "Page %p (containing part at %p) couldn't "
				        "be found as part of the COREPAGE chain",
				        page, part);
				ppage = &(*ppage)->cp_ctrl.cpc_prev;
			}
			/* Unlink the page. */
			*ppage = page->cp_ctrl.cpc_prev;
			vm_corepage_free -= VM_COREPAIRS_PER_PAGE;
			/* Atomically unmap the containing page. */
			vm_unmap_kernel_ram(page, PAGESIZE, false);
		}
	}
}

PRIVATE void NOTHROW(KCALL free_pending_parts)(void) {
	if (ATOMIC_READ(pending_free) != NULL) {
		struct pending_free_part *part, *next;
		part = ATOMIC_XCH(pending_free, NULL);
		while (part) {
			next = part->next;
			do_free_part(part);
			part = next;
		}
	}
}

PRIVATE void *
NOTHROW(KCALL corepage_alloc_part)(struct vm_corepage *__restrict self) {
	unsigned int i, j;
	for (i = 0;; ++i) {
		uintptr_t word, mask;
		assert(i < COMPILER_LENOF(self->cp_ctrl.cpc_used));
		word = self->cp_ctrl.cpc_used[i];
		if (word == (uintptr_t)-1)
			continue;
		/* This word describes an unused part. */
		j = 0, mask = 1;
		while (word & mask)
			++j, mask <<= 1;
		/* Allocate this part. */
		self->cp_ctrl.cpc_used[i] |= mask;
		return &self->cp_parts[i * BITSOF(uintptr_t) + j];
	}
}


PRIVATE struct vm_corepair_ptr
NOTHROW(KCALL vm_corepair_alloc_impl)(void) {
	struct vm_corepair_ptr result;
	assert(vm_corepage_free >= 2);
	result.cp_part = (struct vm_datapart *)corepage_alloc_part(vm_corepage_head);
	memset(result.cp_part, 0, sizeof(*result.cp_part));
	result.cp_part->dp_flags |= VM_DATAPART_FLAG_COREPRT;
	if (!corepage_hasfree(vm_corepage_head)) {
		vm_corepage_head = vm_corepage_head->cp_ctrl.cpc_prev;
		assert(vm_corepage_head);
	}
	result.cp_node = (struct vm_node *)corepage_alloc_part(vm_corepage_head);
	memset(result.cp_node, 0, sizeof(*result.cp_node));
	result.cp_node->vn_flags |= VM_NODE_FLAG_COREPRT;
	if (!corepage_hasfree(vm_corepage_head)) {
		vm_corepage_head = vm_corepage_head->cp_ctrl.cpc_prev;
		assert((vm_corepage_head != NULL) ==
		       (vm_corepage_free > 2));
	}
	vm_corepage_free -= 2;
	assert(result.cp_part->dp_flags == VM_DATAPART_FLAG_COREPRT);
	assert(result.cp_node->vn_flags == VM_NODE_FLAG_COREPRT);
	return result;
}


#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


/* Allocate a new core pair.
 * NOTE: When the nx-variant fails, the returned corepair contains NULL-pointers.
 * @param: flags: Set of `GFP_*' (Uses `GFP_ATOMIC') */
INTERN struct vm_corepair_ptr KCALL
vm_corepair_alloc(gfp_t flags, bool nothrow) {
	struct vm_corepair_ptr result;
again:
	if (!sync_trywrite(&vm_corepage_lock)) {
		if (flags & GFP_ATOMIC) {
atomic_failure:
			if (!nothrow)
				THROW(E_WOULDBLOCK_PREEMPTED);
atomic_failure_nx:
			result.cp_node = NULL;
			result.cp_part = NULL;
			goto done;
		}
		if (nothrow) {
			if (!sync_write_nx(&vm_corepage_lock))
				goto atomic_failure_nx;
		} else {
			sync_write(&vm_corepage_lock);
		}
	}
	free_pending_parts();
	assert(vm_corepage_free >= 2);
	if (vm_corepage_free >= 4) {
allocate_from_corepage:
		result = vm_corepair_alloc_impl();
	} else {
		/* It's our responsibility to allocate a new corepage. */
		void *mapping_target;
		pageptr_t mapping_backend;
		struct vm_corepage *new_page;
		/* Safely acquire the VM-lock, while also keeping the COREPAGE lock. */
		while (!vm_kernel_treelock_trywrite()) {
			sync_endwrite(&vm_corepage_lock);
			if (nothrow) {
				if (!vm_kernel_treelock_writef_nx(flags))
					goto atomic_failure_nx;
			} else {
				if (!vm_kernel_treelock_writef(flags))
					goto atomic_failure;
			}
			if (sync_trywrite(&vm_corepage_lock)) {
				free_pending_parts();
				break;
			}
			vm_kernel_treelock_endwrite();
			if (nothrow) {
				if (!sync_write_nx(&vm_corepage_lock))
					goto atomic_failure_nx;
			} else {
				sync_write(&vm_corepage_lock);
			}
			free_pending_parts();
		}
		COMPILER_READ_BARRIER();
		/* Check if sufficient parts have become available in the mean time. */
		assert(vm_corepage_free >= 2);
		if (vm_corepage_free >= 4) {
			vm_kernel_treelock_endwrite();
			goto allocate_from_corepage;
		}
		/* XXX: Check if we can simply extend an existing core page? */
		mapping_target = vm_getfree(&vm_kernel,
		                            HINT_GETADDR(KERNEL_VMHINT_COREPAGE),
		                            PAGESIZE, PAGESIZE,
		                            HINT_GETMODE(KERNEL_VMHINT_COREPAGE));
		if unlikely(mapping_target == VM_GETFREE_ERROR) {
			uintptr_t version;
			vm_kernel_treelock_endwrite();
			sync_endwrite(&vm_corepage_lock);
#ifndef __OPTIMIZE_SIZE__
			if (system_clearcaches())
				goto again;
#endif /* !__OPTIMIZE_SIZE__ */
			version = 0;
again_tryhard_mapping_target:
			vm_kernel_treelock_read();
			mapping_target = vm_getfree(&vm_kernel,
			                             HINT_GETADDR(KERNEL_VMHINT_COREPAGE),
			                             PAGESIZE, PAGESIZE,
			                             HINT_GETMODE(KERNEL_VMHINT_COREPAGE));
			vm_kernel_treelock_endread();
			if (mapping_target != VM_GETFREE_ERROR)
				goto again;
			if (system_clearcaches_s(&version))
				goto again_tryhard_mapping_target;
			if (!nothrow)
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, PAGESIZE);
			result.cp_node = NULL;
			result.cp_part = NULL;
			goto done;
		}
		/* All right! We've got a virtual memory location, where we can map our new
		 * data block. Now all that we still need is 1 page of physical memory which
		 * we can then use to map at that location! */
		mapping_backend = page_mallocone();
		if (mapping_backend == PAGEPTR_INVALID) {
			vm_kernel_treelock_endwrite();
			sync_endwrite(&vm_corepage_lock);
			if (!nothrow)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			result.cp_node = NULL;
			result.cp_part = NULL;
			goto done;
		}
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		/* Map the page into our current page directory. */
		if (!pagedir_prepare_mapone(mapping_target)) {
			vm_kernel_treelock_endwrite();
			sync_endwrite(&vm_corepage_lock);
			page_ccfree(mapping_backend, 1);
			if (!nothrow)
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
			result.cp_node = NULL;
			result.cp_part = NULL;
			goto done;
		}
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		pagedir_mapone(mapping_target,
		               page2addr(mapping_backend),
		               PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);

		/* Allocate (reserve) 2 of the remaining corebase components,
		 * which will then be used to describe the new corebase page
		 * within the kernel VM. */
		result = vm_corepair_alloc_impl();

		/* With everything now allocated, fill in node data
		 * and register the node in the kernel VM. */
		result.cp_node->vn_node.a_vmin = PAGEID_ENCODE(mapping_target);
		result.cp_node->vn_node.a_vmax = result.cp_node->vn_node.a_vmin;
		result.cp_part->dp_block       = incref(&vm_datablock_anonymous);
		result.cp_node->vn_block       = incref(&vm_datablock_anonymous);
		result.cp_node->vn_prot        = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_SHARED;
		result.cp_node->vn_vm          = &vm_kernel;
		result.cp_node->vn_flags |= VM_NODE_FLAG_PREPARED;
		result.cp_node->vn_part                       = result.cp_part;
		result.cp_node->vn_link.ln_pself              = &LLIST_HEAD(result.cp_part->dp_srefs);
		result.cp_part->dp_srefs                      = result.cp_node;
		result.cp_part->dp_state                      = VM_DATAPART_STATE_LOCKED;
		result.cp_part->dp_pprop                      = (uintptr_t)-1;
		result.cp_part->dp_ramdata.rd_blockc          = 1;
		result.cp_part->dp_ramdata.rd_blockv          = &result.cp_part->dp_ramdata.rd_block0;
		result.cp_part->dp_ramdata.rd_block0.rb_start = mapping_backend;
		vm_node_insert(result.cp_node);
		COMPILER_BARRIER();

		/* Now initialize the new CORE page, and link it. */
		new_page = (struct vm_corepage *)mapping_target;
		if (!page_iszero(mapping_backend))
			memset(&new_page->cp_ctrl, 0, sizeof(new_page->cp_ctrl));
		new_page->cp_ctrl.cpc_prev = vm_corepage_head;
		vm_corepage_head           = new_page;

		/* Keep track of all of the new parts that we've just allocated. */
		vm_corepage_free += VM_COREPAIRS_PER_PAGE;
		vm_kernel_treelock_endwrite();
		goto allocate_from_corepage;
	}
	sync_endwrite(&vm_corepage_lock);
	assert(result.cp_part->dp_flags == VM_DATAPART_FLAG_COREPRT);
	assert(result.cp_node->vn_flags == VM_NODE_FLAG_COREPRT);
done:
	return result;
}


/* Free a `struct vm_datapart' or `struct vm_node', previously
 * allocated using the core pair allocator functions below. */
INTERN NOBLOCK void
NOTHROW(KCALL vm_corepage_freepart)(void *__restrict part) {
	if (!sync_trywrite(&vm_corepage_lock)) {
		struct pending_free_part *pend, *next;
		/* Remember the given `part' as a pending free-part,
		 * thus ensuring that this function can't block, as
		 * `sync_write()' could potentially do a call
		 * to `SCHED_YIELD()', which may be illegal if preemption
		 * is currently disabled. */
		pend = (struct pending_free_part *)part;
		do {
			next = ATOMIC_READ(pending_free);
			pend->next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(pending_free, next, pend));
		COMPILER_BARRIER();
		if (sync_trywrite(&vm_corepage_lock)) {
			free_pending_parts();
			sync_endwrite(&vm_corepage_lock);
		}
		return;
	}
	free_pending_parts();
	do_free_part(part);
	sync_endwrite(&vm_corepage_lock);
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_COREBASE_C */
