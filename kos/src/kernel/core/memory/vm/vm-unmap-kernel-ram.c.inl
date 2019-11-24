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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_UNMAP_KERNEL_RAM_C_INL
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_UNMAP_KERNEL_RAM_C_INL 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/vm.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <sys/mmio.h>

#include <assert.h>
#include <string.h>

#include "../corebase.h"

#ifdef __INTELLISENSE__
#include "vm.c"
#endif

DECL_BEGIN

struct pending_unmap_ram {
	struct pending_unmap_ram *pur_next; /* [0..1] Next pending unmap. */
	size_t                    pur_size; /* Pending unmap size (in pages) */
	bool                      pur_zero; /* Are bytes of pending unmap pages zero */
};

/* Chain of pending kernel unmap RAM requests. */
PRIVATE ATTR_READMOSTLY WEAK
struct pending_unmap_ram *vm_pending_unmap_kernel_ram = NULL;

/* Chain of tasks that are pending destruction.
 * Linked via `t_sched.s_running.sr_runnxt' */
INTDEF ATTR_READMOSTLY WEAK struct task *vm_pending_destroy_tasks;

INTDEF NOBLOCK void NOTHROW(KCALL task_destroy_raw_impl)(struct task *__restrict self);


#define vm_kernel_treelock_mustservice() \
	(ATOMIC_READ(vm_pending_destroy_tasks) || ATOMIC_READ(vm_pending_unmap_kernel_ram))

PRIVATE NOBLOCK_IF(flags & GFP_ATOMIC) void
NOTHROW(KCALL vm_kernel_treelock_service)(gfp_t flags);


LOCAL NOBLOCK void
NOTHROW(KCALL vm_do_pdir_unmap)(vm_vpage_t page_index, size_t num_pages) {
	/* Unmap the associated memory, sync it, and unprepare it. */
	pagedir_unmap(page_index, num_pages);
	vm_kernel_sync(page_index, num_pages);
#ifdef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	/* NOTE: Only unprepare the range after all CPUs were notified about the unmap.
	 *       If we were to free any descriptor pages before then, the pages may
	 *       be allocated again, and become corrupt while other cores are still
	 *       believing them to contain paging data. */
	pagedir_unprepare_map(page_index, num_pages);
#endif /* CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL pprop_bitset_move_to_front)(uintptr_t *__restrict base,
                                          size_t src_index,
                                          size_t num_pages) {
	size_t dst_index = 0;
	assert(src_index > 0);
	while (num_pages--) {
		uintptr_t bit;
		bit = pprop_getbit(base, src_index);
		pprop_setbit(base, dst_index, bit);
		++src_index;
		++dst_index;
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_truncate_leading)(struct vm_datapart *__restrict self,
                                            size_t num_truncate_pages,
                                            bool is_zero) {
	size_t new_total_pages, old_total_pages;
	assert(self->dp_tree.a_vmin == 0);
	old_total_pages = (size_t)self->dp_tree.a_vmax + 1;
	assert(num_truncate_pages < old_total_pages);
	new_total_pages = old_total_pages - num_truncate_pages;
	/* Update the page-property bitset. */
	if (self->dp_flags & VM_DATAPART_FLAG_HEAPPPP) {
		if (self->dp_pprop_p) {
			pprop_bitset_move_to_front(self->dp_pprop_p,
			                           num_truncate_pages,
			                           new_total_pages);
			if (new_total_pages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
				uintptr_t bitset_word;
				bitset_word = self->dp_pprop_p[0];
				kfree(self->dp_pprop_p);
				self->dp_pprop = bitset_word;
				self->dp_flags &= ~VM_DATAPART_FLAG_HEAPPPP;
			} else {
				size_t new_bitset_size;
				new_bitset_size = CEILDIV(new_total_pages,
				                          BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
				/* Try to trim unused memory from the page property vector. */
				krealloc_in_place_nx(self->dp_pprop_p, new_bitset_size,
				                     GFP_ATOMIC | GFP_LOCKED |
				                     GFP_NOMMAP | GFP_PREFLT);
			}
		}
	} else {
		pprop_bitset_move_to_front(&self->dp_pprop,
		                           num_truncate_pages,
		                           new_total_pages);
	}
	switch (self->dp_state) {

	case VM_DATAPART_STATE_INCORE:
	case VM_DATAPART_STATE_LOCKED:
		if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
			/* Single-block (just truncate it!) */
			assert(self->dp_ramdata.rd_block0.rb_size == old_total_pages);
			page_ffree(self->dp_ramdata.rd_block0.rb_start, num_truncate_pages, is_zero);
			self->dp_ramdata.rd_block0.rb_start += num_truncate_pages;
			self->dp_ramdata.rd_block0.rb_size = new_total_pages;
		} else {
			/* This one's a bit more complicated... */
			size_t i;
			size_t num_missing = num_truncate_pages;
			for (i = 0;; ++i) {
				size_t part_free;
				assert(i < self->dp_ramdata.rd_blockc);
				part_free = self->dp_ramdata.rd_blockv[i].rb_size;
				if (part_free > num_missing)
					part_free = num_missing;
				page_ffree(self->dp_ramdata.rd_blockv[i].rb_start, part_free, is_zero);
				self->dp_ramdata.rd_blockv[i].rb_start += part_free;
				self->dp_ramdata.rd_blockv[i].rb_size -= part_free;
				if (part_free >= num_missing)
					break;
				num_missing -= part_free;
			}
			if (i != 0) {
				/* Remove leading parts. */
				self->dp_ramdata.rd_blockc -= i;
				memmovedown(&self->dp_ramdata.rd_blockv[0],
				            &self->dp_ramdata.rd_blockv[i],
				            self->dp_ramdata.rd_blockc,
				            sizeof(struct vm_ramblock));
				/* Try to trim unused memory from the ram-block vector. */
				krealloc_in_place_nx(self->dp_ramdata.rd_blockv,
				                     self->dp_ramdata.rd_blockc *
				                     sizeof(struct vm_ramblock),
				                     GFP_ATOMIC | GFP_LOCKED |
				                     GFP_NOMMAP | GFP_PREFLT);
			}
		}
		break;

#ifndef CONFIG_NO_SWAP
	case VM_DATAPART_STATE_INSWAP:
		if (self->dp_swpdata.sd_blockv == &self->dp_swpdata.sd_block0) {
			/* Single-block (just truncate it!) */
			assert(self->dp_swpdata.sd_block0.sb_size == old_total_pages);
			swap_free(self->dp_swpdata.sd_block0.sb_start, num_truncate_pages);
			self->dp_swpdata.sd_block0.sb_start += num_truncate_pages;
			self->dp_swpdata.sd_block0.sb_size = new_total_pages;
		} else {
			/* This one's a bit more complicated... */
			size_t i;
			size_t num_missing = num_truncate_pages;
			for (i = 0;; ++i) {
				size_t part_free;
				assert(i < self->dp_swpdata.sd_blockc);
				part_free = self->dp_swpdata.sd_blockv[i].sb_size;
				if (part_free > num_missing)
					part_free = num_missing;
				swap_free(self->dp_swpdata.sd_blockv[i].sb_start, part_free);
				self->dp_swpdata.sd_blockv[i].sb_start += part_free;
				self->dp_swpdata.sd_blockv[i].sb_size -= part_free;
				if (part_free >= num_missing)
					break;
				num_missing -= part_free;
			}
			if (i != 0) {
				/* Remove leading parts. */
				self->dp_swpdata.sd_blockc -= i;
				memmovedown(&self->dp_swpdata.sd_blockv[0],
				            &self->dp_swpdata.sd_blockv[i],
				            self->dp_swpdata.sd_blockc,
				            sizeof(struct vm_swpblock));
				/* Try to trim unused memory from the swp-block vector. */
				krealloc_in_place_nx(self->dp_swpdata.sd_blockv,
				                     self->dp_swpdata.sd_blockc *
				                     sizeof(struct vm_swpblock),
				                     GFP_ATOMIC | GFP_LOCKED |
				                     GFP_NOMMAP | GFP_PREFLT);
			}
		}
		break;
#endif /* !CONFIG_NO_SWAP */

	default: break;
	}
	assert(self->dp_tree.a_vmin == 0);
	self->dp_tree.a_vmax = (vm_dpage_t)(new_total_pages - 1);
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_truncate_trailing_ramblocks)(struct vm_datapart *__restrict self,
                                                       size_t new_total_pages,
                                                       bool is_zero) {
	size_t i, j;
	size_t num_keep = new_total_pages;
	for (i = 0;; ++i) {
		size_t part_free;
		assert(i < self->dp_ramdata.rd_blockc);
		part_free = self->dp_ramdata.rd_blockv[i].rb_size;
		if (num_keep >= part_free) {
			num_keep -= part_free;
			continue;
		}
		/* Free the unused portion from this specific part. */
		page_ffree(self->dp_ramdata.rd_blockv[i].rb_start + num_keep,
		           part_free - num_keep, is_zero);
		self->dp_ramdata.rd_blockc            = i;
		self->dp_ramdata.rd_blockv[i].rb_size = num_keep;

		/* Free all following parts. */
		for (j = i; j < self->dp_ramdata.rd_blockc; ++j) {
			page_ffree(self->dp_ramdata.rd_blockv[j].rb_start,
			           self->dp_ramdata.rd_blockv[j].rb_size,
			           is_zero);
		}
		/* Try to trim unused memory from the ram-block vector. */
		krealloc_in_place_nx(self->dp_ramdata.rd_blockv,
		                     i * sizeof(struct vm_ramblock),
		                     GFP_ATOMIC | GFP_LOCKED |
		                     GFP_NOMMAP | GFP_PREFLT);
		break;
	}
}

#ifndef CONFIG_NO_SWAP
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_truncate_trailing_swpblocks)(struct vm_datapart *__restrict self,
                                                       size_t new_total_pages) {
	size_t i, j;
	size_t num_keep = new_total_pages;
	for (i = 0;; ++i) {
		size_t part_free;
		assert(i < self->dp_swpdata.sd_blockc);
		part_free = self->dp_swpdata.sd_blockv[i].sb_size;
		if (num_keep >= part_free) {
			num_keep -= part_free;
			continue;
		}
		/* Free the unused portion from this specific part. */
		swap_free(self->dp_swpdata.sd_blockv[i].sb_start + num_keep, part_free - num_keep);
		self->dp_swpdata.sd_blockc            = i;
		self->dp_swpdata.sd_blockv[i].sb_size = num_keep;

		/* Free all following parts. */
		for (j = i; j < self->dp_swpdata.sd_blockc; ++j) {
			swap_free(self->dp_swpdata.sd_blockv[j].sb_start,
			          self->dp_swpdata.sd_blockv[j].sb_size);
		}
		/* Try to trim unused memory from the swp-block vector. */
		krealloc_in_place_nx(self->dp_swpdata.sd_blockv,
		                     i * sizeof(struct vm_swpblock),
		                     GFP_ATOMIC | GFP_LOCKED |
		                     GFP_NOMMAP | GFP_PREFLT);
		break;
	}
}
#endif /* !CONFIG_NO_SWAP */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL vm_datapart_truncate_trailing)(struct vm_datapart *__restrict self,
                                             size_t new_total_pages, bool is_zero) {
	size_t num_truncate_pages;
	size_t old_total_pages;
	assert(self->dp_tree.a_vmin == 0);
	old_total_pages = (size_t)self->dp_tree.a_vmax + 1;
	assert(new_total_pages < old_total_pages);
	num_truncate_pages = old_total_pages - new_total_pages;
	if (self->dp_flags & VM_DATAPART_FLAG_HEAPPPP && self->dp_pprop_p != NULL) {
#if 0 /* Can't be done... (would introduce a race condition with hinted page-fault handling) */
		if (new_total_pages <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
			uintptr_t bitset_word;
			bitset_word = self->dp_pprop_p[0];
			kfree(self->dp_pprop_p);
			self->dp_pprop = bitset_word;
			self->dp_flags &= ~VM_DATAPART_FLAG_HEAPPPP;
		} else
#endif
		{
			size_t new_bitset_size;
			new_bitset_size = CEILDIV(new_total_pages,
			                          BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
			/* Try to trim unused memory from the page property vector. */
			krealloc_in_place_nx(self->dp_pprop_p, new_bitset_size,
			                     GFP_ATOMIC | GFP_LOCKED |
			                     GFP_NOMMAP | GFP_PREFLT);
		}
	}
	switch (self->dp_state) {

	case VM_DATAPART_STATE_INCORE:
	case VM_DATAPART_STATE_LOCKED:
		if (self->dp_ramdata.rd_blockv == &self->dp_ramdata.rd_block0) {
			/* Single-block (just truncate it!) */
			assert(self->dp_ramdata.rd_block0.rb_size == old_total_pages);
			page_ffree(self->dp_ramdata.rd_block0.rb_start + new_total_pages, num_truncate_pages, is_zero);
			self->dp_ramdata.rd_block0.rb_size = new_total_pages;
		} else {
			/* This one's a bit more complicated... */
			vm_datapart_truncate_trailing_ramblocks(self, new_total_pages, is_zero);
		}
		break;

#ifndef CONFIG_NO_SWAP
	case VM_DATAPART_STATE_INSWAP:
		if (self->dp_swpdata.sd_blockv == &self->dp_swpdata.sd_block0) {
			/* Single-block (just truncate it!) */
			assert(self->dp_swpdata.sd_block0.sb_size == old_total_pages);
			swap_free(self->dp_swpdata.sd_block0.sb_start + new_total_pages, num_truncate_pages);
			self->dp_swpdata.sd_block0.sb_size = new_total_pages;
		} else {
			/* This one's a bit more complicated... */
			vm_datapart_truncate_trailing_swpblocks(self, new_total_pages);
		}
		break;
#endif /* !CONFIG_NO_SWAP */

	default: break;
	}
	assert(self->dp_tree.a_vmin == 0);
	self->dp_tree.a_vmax = (vm_dpage_t)(new_total_pages - 1);
}



PRIVATE /*NOBLOCK_IF(flags & GFP_ATOMIC)*/ void
NOTHROW(KCALL vm_do_unmap_kernel_ram)(vm_vpage_t page_index, size_t num_pages,
                                      bool is_zero, gfp_t flags) {
	/* In order to unmap a sub-segment of a hinted VM nodes, the following must be done:
	 *  - Because hinted VM nodes cannot be split (only truncated),
	 *    we must first see how many pages reside on the upper end
	 *    of the sub-segment to-be unmapped.
	 *  - We must always chose the upper end because we must eventually
	 *    truncate the associated data part's `dp_pprop_p' vector, though
	 *    we cannot modify its base-pointer, or move around its elements.
	 *    NOTE: The same goes for the `rd_blockv' vector.
	 *    This restriction must be in place, since the page-fault handler
	 *    doesn't acquire any sort of lock before accessing such a component,
	 *    relying purely on the assumption that the kernel won't try to
	 *    unmap its own private memory, whilst still using that memory.
	 *  - We then ensure that all pages above the unmapped segment have been
	 *    initialized in kernel memory (this is guarantied to be NOEXCEPT
	 *    because hinted memory in kernel-space is always pre-allocated,
	 *    and always has initializers that don't throw any exceptions)
	 *    A type of initializer like this would usually only `memset()'
	 *    or `mempat()' new memory for either debugging or `calloc()'
	 *  - Once that is done, we know that everything above the sub-segment
	 *    to-be unmapped has been allocated, and consequently no longer
	 *    represents hinted memory (the page directory contains the actual
	 *    memory mapping, rather than a hint as to how to initialize it).
	 *    Because of this, we can proceed to replace the upper sub-segment
	 *    with a new VM node/data part pair, before moving on to truncate
	 *    the original (and still hinted base node) to end where the
	 *    unmapped sub-segment ends.
	 *
	 *
	 * Before:
	 * /--vm_datapart at 0xc1234567
	 * [HINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTEDHINTED]
	 *              |-- Unmap this part ---|
	 *
	 * After:
	 * /--vm_datapart at 0xc1234567        /--vm_datapart at 0xc7654321
	 * [HINTEDHINTED]                      [USABLEUSABLEUSABLEUSABLEUSABLE]
	 *              |-- Unmap this part ---|
	 *
	 * Note that the upper part is entirely new, and no longer represents
	 * hinted memory, while the lower part still is the same datapart, but
	 * has been truncated!
	 *
	 * HINTED: Allocated, but initialized memory (initialize on first access)
	 * USABLE: Fully initialized memory
	 */
	struct vm_node *node;
	struct vm_datapart *part;
	size_t effective_pages;
	vm_vpage_t unmap_max;
	unmap_max = page_index + num_pages - 1;
again:
	assert(num_pages != 0);
	assert(page_index >= (vm_vpage_t)KERNEL_BASE_PAGE);
	assert(unmap_max >= page_index);
	assert(unmap_max <= VM_VPAGE_MAX);
	/* With the caller having acquired a write-lock to the kernel
	 * VM for us, now it's time to actually perform the unmap! */
	node = vm_node_remove(&vm_kernel, page_index);
	assertf(node, "Nothing mapped at %p...%p\n",
	        VM_PAGE2ADDR(page_index),
	        VM_PAGE2ADDR(page_index + num_pages) - 1);
	assertf(!(node->vn_flags & VM_NODE_FLAG_KERNPRT),
	        "Attempted to unmap node at %p...%p, which is part of the kernel core",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(node->vn_prot & VM_PROT_SHARED,
	        "Attempted to unmap copy-on-write node at %p...%p as RAM (RAM nodes must be shared mappings)",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(node->vn_flags & VM_NODE_FLAG_PREPARED,
	        "Attempted to unmap unprepared node at %p...%p as RAM "
	        "(RAM nodes must remain prepared for the duration of their lifetime)",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(node->vn_vm == &vm_kernel,
	        "Kernel-space node at %p...%p has a corrupt VM pointer (%p != %p)",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node),
	        node->vn_vm, &vm_kernel);
	/* Check if the unmap request was split across multiple nodes. */
	effective_pages = num_pages;
	if (unmap_max > VM_NODE_MAX(node))
		effective_pages = (size_t)((VM_NODE_MAX(node) - page_index) + 1);
	part = node->vn_part;
	assertf(part->dp_crefs == NULL,
	        "Datapart backing anonymous kernel-space node at %p...%p has copy-on-write references",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(part->dp_srefs == node && node->vn_link.ln_next == NULL,
	        "Datapart backing anonymous kernel-space node at %p...%p is shared by other nodes",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(node->vn_link.ln_pself == &part->dp_srefs,
	        "Corrupted datalink self-pointer in anonymous kernel-space node at %p...%p",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(!(part->dp_flags & VM_DATAPART_FLAG_KERNPRT),
	        "Attempted to unmap kernel-space node at %p...%p, backed "
	        "by a data part referring to a part of the kernel core",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));
	assertf(part->dp_block->db_parts == VM_DATABLOCK_ANONPARTS,
	        "Cannot unmap non-anonymous kernel-space node at %p...%p as RAM",
	        VM_NODE_MINADDR(node), VM_NODE_MAXADDR(node));

	if (unmap_max >= VM_NODE_MAX(node)) {
		/* We can either unmap the entire node, or we can just truncate it. */
		if (page_index <= VM_NODE_MIN(node)) {
			/* Simply unmap the entire node. */
			decref_unlikely(part->dp_block);
			decref_unlikely(node->vn_block);
			vm_do_pdir_unmap(page_index, effective_pages);
			part->dp_srefs = NULL;
			vm_datapart_destroy(part, is_zero);
			vm_node_free(node);
		} else {
			/* Must truncate the node at the end. */
			vm_do_pdir_unmap(page_index, effective_pages);
			vm_datapart_truncate_trailing(part, (size_t)(page_index - VM_NODE_MIN(node)), is_zero);
			assert(page_index - 1 < node->vn_node.a_vmax);
			node->vn_node.a_vmax = page_index - 1;
			/* Re-insert the (now truncated) node */
			vm_node_insert(node);
		}
	} else {
		if (node->vn_flags & VM_NODE_FLAG_HINTED) {
			/* The node is being hinted towards, and the unmap will either
			 * only remove a sub-region of the node, or a small piece standing
			 * near its end.
			 * In either case, we must make sure to initialize all trailing
			 * hinted pages such that no trailing pages are still being hinted
			 * to. Otherwise, the page-fault handler may would run into race
			 * conditions arising from the node changing while it is in the
			 * processes of operating with that node (which we subvert by doing
			 * it's work ahead of time for all of the nodes that could possibly
			 * be affected by this) */
			vm_vpage_t tail_start;
			size_t tail_size;
			assert(part->dp_state == VM_DATAPART_STATE_LOCKED);
			/* Simply touch (thus initialize) all affected trailing pages,
			 * thus forcing the page fault handler to initialize them. */
			tail_start = unmap_max + 1;
			tail_size  = (size_t)(VM_NODE_MAX(node) - unmap_max);
			assert(tail_size >= 1);
			do {
#if __SIZEOF_POINTER__ >= 8
				readq((uintptr_t)VM_PAGE2ADDR(tail_start));
#else
				readl((uintptr_t)VM_PAGE2ADDR(tail_start));
#endif
				++tail_start;
			} while (--tail_size);
		}
		if (page_index <= VM_NODE_MIN(node)) {
			size_t num_truncate;
			num_truncate = (size_t)((unmap_max + 1) - VM_NODE_MIN(node));
			assert(num_truncate >= 1);
			/* Unmap all leading memory from the node. */
			node->vn_node.a_vmin = unmap_max + 1;
			vm_do_pdir_unmap(page_index, effective_pages);
			vm_datapart_truncate_leading(part, num_truncate, is_zero);
			/* Re-insert the (now truncated) node */
			vm_node_insert(node);
		} else {
			struct vm_corepair_ptr corepair;
			/* Must split the node (and datapart) in 2 (`X' and `Z'):
			 *    BEFORE: XXXX XXXXXXX XXXX
			 *    AFTER:  XXXX YYYYYYY ZZZZ
			 *            keep -unmap- keep */
			size_t sizeof_leading  = (size_t)(page_index - VM_NODE_MIN(node));      /* SIZEOF(X) */
			size_t sizeof_truncate = effective_pages;                               /* SIZEOF(Y) */
			size_t sizeof_trailing = (size_t)(VM_NODE_MAX(node) - unmap_max);       /* SIZEOF(Z) */
			size_t trailing_offset = (size_t)((unmap_max + 1) - VM_NODE_MIN(node)); /* Offset from the start of `Z' to the start of `X' */
			uintptr_t *part_pprot_bitset;
			assert(page_index > VM_NODE_MIN(node));
			assert(VM_NODE_MAX(node) > unmap_max);
			corepair.cp_node = (struct vm_node *)kmalloc_nx(sizeof(struct vm_node),
			                                                GFP_LOCKED | GFP_CALLOC | GFP_PREFLT |
			                                                (flags & GFP_INHERIT));
			corepair.cp_part = (struct vm_datapart *)kmalloc_nx(sizeof(struct vm_datapart),
			                                                    GFP_LOCKED | GFP_CALLOC | GFP_PREFLT |
			                                                    (flags & GFP_INHERIT));
			if unlikely(!corepair.cp_node || !corepair.cp_part) {
				kffree(corepair.cp_node, GFP_CALLOC);
				kffree(corepair.cp_part, GFP_CALLOC);
				corepair = vm_corepair_alloc(flags, true);
				if unlikely(!corepair.cp_node) {
					struct pending_unmap_ram *pend, *next;
					/* Failed to allocate the necessary secondary node/datapart.
					 * -> Schedule everything as a pending kernel RAM unmap. */
restore_node_after_corepair_failure:
					if (corepair.cp_part) {
						if (corepair.cp_part->dp_flags & VM_DATAPART_FLAG_HEAPPPP)
							kfree(corepair.cp_part->dp_pprop_p);
						vm_datapart_free(corepair.cp_part);
					}
					if (corepair.cp_node)
						vm_node_free(corepair.cp_node);
					vm_node_insert(node);
					pend           = (struct pending_unmap_ram *)VM_PAGE2ADDR(page_index);
					pend->pur_size = effective_pages;
					pend->pur_zero = is_zero;
					do {
						next = ATOMIC_READ(vm_pending_unmap_kernel_ram);
						pend->pur_next = next;
					} while (!ATOMIC_CMPXCH_WEAK(vm_pending_unmap_kernel_ram, next, pend));
					goto continue_with_next;
				}
			}
			/* Initialize the sub-mapping. */
			part_pprot_bitset = &part->dp_pprop;
			if (part->dp_flags & VM_DATAPART_FLAG_HEAPPPP) {
				part_pprot_bitset = part->dp_pprop_p;
				if (!part_pprot_bitset) {
					corepair.cp_part->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
					corepair.cp_part->dp_pprop_p = NULL;
					goto page_properties_updated;
				}
			}
			/* Copy page property bits from high-order pages. */
			if (sizeof_trailing <= BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS) {
				size_t i;
				uintptr_t bit;
				for (i = 0; i < sizeof_trailing; ++i) {
					bit = pprop_getbit(part_pprot_bitset, trailing_offset + i);
					pprop_setbit(&corepair.cp_part->dp_pprop, i, bit);
				}
			} else {
				size_t bitset_size, i;
				uintptr_t bit;
				bitset_size                  = CEILDIV(sizeof_trailing, BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
				corepair.cp_part->dp_pprop_p = (uintptr_t *)kmalloc_nx(bitset_size,
				                                                       GFP_LOCKED | GFP_CALLOC | GFP_PREFLT |
				                                                       (flags & GFP_INHERIT));
				if unlikely(!corepair.cp_part->dp_pprop_p)
					goto restore_node_after_corepair_failure;
				for (i = 0; i < sizeof_trailing; ++i) {
					bit = pprop_getbit(part_pprot_bitset, trailing_offset + i);
					pprop_setbit(corepair.cp_part->dp_pprop_p, i, bit);
				}
				corepair.cp_part->dp_flags |= VM_DATAPART_FLAG_HEAPPPP;
			}
page_properties_updated:

			/* Split the part's actual RAM / SWAP data. */
			switch (part->dp_state) {

			case VM_DATAPART_STATE_INCORE:
			case VM_DATAPART_STATE_LOCKED:
				if (part->dp_ramdata.rd_blockv == &part->dp_ramdata.rd_block0) {
					/* A single ram block is being split (simple case) */
					corepair.cp_part->dp_ramdata.rd_blockv          = &corepair.cp_part->dp_ramdata.rd_block0;
					corepair.cp_part->dp_ramdata.rd_block0.rb_start = part->dp_ramdata.rd_block0.rb_start + trailing_offset;
					corepair.cp_part->dp_ramdata.rd_block0.rb_size  = sizeof_trailing;
					/* Free memory in between */
					vm_do_pdir_unmap(page_index, effective_pages);
					page_ffree(part->dp_ramdata.rd_block0.rb_start + sizeof_leading,
					           sizeof_truncate, is_zero);
					part->dp_ramdata.rd_block0.rb_size = sizeof_leading;
				} else {
					/* Figure out how many ram blocks are required to represent
					 * the last `sizeof_trailing' pages of the part.
					 * If it's more than 1, we must allocate the associated vector
					 * first, so we can safely handle that allocation failing by
					 * jump to `restore_node_after_corepair_failure' */
					size_t i, req_block_trailing = 1;
					size_t covered_pages;
					i             = part->dp_ramdata.rd_blockc - 1;
					covered_pages = part->dp_ramdata.rd_blockv[i].rb_size;
					while (covered_pages < sizeof_trailing) {
						assert(i != 0);
						--i;
						covered_pages += part->dp_ramdata.rd_blockv[i].rb_size;
						++req_block_trailing;
					}
					if (req_block_trailing <= 1) {
						size_t trailing_keep;
						/* Simple case: Only one block is actually required. */
						assert(i == part->dp_ramdata.rd_blockc - 1);
						assert(part->dp_ramdata.rd_blockv[i].rb_size >= sizeof_trailing);
						trailing_keep                                   = part->dp_ramdata.rd_blockv[i].rb_size - sizeof_trailing;
						corepair.cp_part->dp_ramdata.rd_block0.rb_start = part->dp_ramdata.rd_blockv[i].rb_start + trailing_keep;
						corepair.cp_part->dp_ramdata.rd_block0.rb_size  = sizeof_trailing;
						if (trailing_keep == 0) {
							/* The last part simply gets transferred. */
							--part->dp_ramdata.rd_blockc;
						} else {
							/* Keep a portion of the last part. */
							part->dp_ramdata.rd_blockv[i].rb_size = trailing_keep;
						}
					} else {
						/* We need more than 1 RAM block to represent the Z-node,
						 * so we must allocate a vector of them on the heap. */
						struct vm_ramblock *hi_blocks;
						size_t num_pages_from_first;
						hi_blocks = (struct vm_ramblock *)kmalloc_nx(req_block_trailing *
						                                             sizeof(struct vm_ramblock),
						                                             GFP_LOCKED | GFP_CALLOC | GFP_PREFLT |
						                                             (flags & GFP_INHERIT));
						if unlikely(!hi_blocks)
							goto restore_node_after_corepair_failure;
						corepair.cp_part->dp_ramdata.rd_blockc = req_block_trailing;
						corepair.cp_part->dp_ramdata.rd_blockv = hi_blocks;
						num_pages_from_first                   = sizeof_trailing - (covered_pages - part->dp_ramdata.rd_blockv[i].rb_size);
						/* Split the first block. */
						hi_blocks[0].rb_size  = num_pages_from_first;
						hi_blocks[0].rb_start = part->dp_ramdata.rd_blockv[i].rb_start;
						hi_blocks[0].rb_start += part->dp_ramdata.rd_blockv[i].rb_size;
						hi_blocks[0].rb_start -= num_pages_from_first;
						/* Copy additional blocks. */
						assert((req_block_trailing - 1) == (part->dp_ramdata.rd_blockc - (i + 1)));
						memcpy(&hi_blocks[1],
						       &part->dp_ramdata.rd_blockv[i + 1],
						       req_block_trailing - 1, sizeof(struct vm_ramblock));
						part->dp_ramdata.rd_blockc = i;
						part->dp_ramdata.rd_blockv[i].rb_size -= num_pages_from_first;
					}
					vm_do_pdir_unmap(page_index, effective_pages);
					/* Truncate trailing RAM blocks from the new leading block. */
					vm_datapart_truncate_trailing_ramblocks(part, sizeof_leading, is_zero);
				}
				break;

#ifndef CONFIG_NO_SWAP
			case VM_DATAPART_STATE_INSWAP:
				if (part->dp_swpdata.sd_blockv == &part->dp_swpdata.sd_block0) {
					/* A single swp block is being split (simple case) */
					corepair.cp_part->dp_swpdata.sd_blockv          = &corepair.cp_part->dp_swpdata.sd_block0;
					corepair.cp_part->dp_swpdata.sd_block0.sb_start = part->dp_swpdata.sd_block0.sb_start + trailing_offset;
					corepair.cp_part->dp_swpdata.sd_block0.sb_size  = sizeof_trailing;
					/* Free memory in between */
					vm_do_pdir_unmap(page_index, effective_pages);
					swap_free(part->dp_swpdata.sd_block0.sb_start + sizeof_leading,
					          sizeof_truncate);
					part->dp_swpdata.sd_block0.sb_size = sizeof_leading;
				} else {
					/* Figure out how many swp blocks are required to represent
					 * the last `sizeof_trailing' pages of the part.
					 * If it's more than 1, we must allocate the associated vector
					 * first, so we can safely handle that allocation failing by
					 * jump to `restore_node_after_corepair_failure' */
					size_t i, req_block_trailing = 1;
					size_t covered_pages;
					i             = part->dp_swpdata.sd_blockc - 1;
					covered_pages = part->dp_swpdata.sd_blockv[i].sb_size;
					while (covered_pages < sizeof_trailing) {
						assert(i != 0);
						--i;
						covered_pages += part->dp_swpdata.sd_blockv[i].sb_size;
						++req_block_trailing;
					}
					if (req_block_trailing <= 1) {
						size_t trailing_keep;
						/* Simple case: Only one block is actually required. */
						assert(i == part->dp_swpdata.sd_blockc - 1);
						assert(part->dp_swpdata.sd_blockv[i].sb_size >= sizeof_trailing);
						trailing_keep                                   = part->dp_swpdata.sd_blockv[i].sb_size - sizeof_trailing;
						corepair.cp_part->dp_swpdata.sd_block0.sb_start = part->dp_swpdata.sd_blockv[i].sb_start + trailing_keep;
						corepair.cp_part->dp_swpdata.sd_block0.sb_size  = sizeof_trailing;
						if (trailing_keep == 0) {
							/* The last part simply gets transferred. */
							--part->dp_swpdata.sd_blockc;
						} else {
							/* Keep a portion of the last part. */
							part->dp_swpdata.sd_blockv[i].sb_size = trailing_keep;
						}
					} else {
						/* We need more than 1 RAM block to represent the Z-node,
						 * so we must allocate a vector of them on the heap. */
						struct vm_swpblock *hi_blocks;
						size_t num_pages_from_first;
						hi_blocks = (struct vm_swpblock *)kmalloc_nx(req_block_trailing *
						                                             sizeof(struct vm_swpblock),
						                                             GFP_LOCKED | GFP_CALLOC | GFP_PREFLT |
						                                             (flags & GFP_INHERIT));
						if unlikely(!hi_blocks)
							goto restore_node_after_corepair_failure;
						corepair.cp_part->dp_swpdata.sd_blockc = req_block_trailing;
						corepair.cp_part->dp_swpdata.sd_blockv = hi_blocks;
						num_pages_from_first                   = sizeof_trailing - (covered_pages - part->dp_swpdata.sd_blockv[i].sb_size);
						/* Split the first block. */
						hi_blocks[0].sb_size  = num_pages_from_first;
						hi_blocks[0].sb_start = part->dp_swpdata.sd_blockv[i].sb_start;
						hi_blocks[0].sb_start += part->dp_swpdata.sd_blockv[i].sb_size;
						hi_blocks[0].sb_start -= num_pages_from_first;
						/* Copy additional blocks. */
						assert((req_block_trailing - 1) == (part->dp_swpdata.sd_blockc - (i + 1)));
						memcpy(&hi_blocks[1],
						       &part->dp_swpdata.sd_blockv[i + 1],
						       req_block_trailing - 1, sizeof(struct vm_swpblock));
						part->dp_swpdata.sd_blockc = i;
						part->dp_swpdata.sd_blockv[i].sb_size -= num_pages_from_first;
					}
					vm_do_pdir_unmap(page_index, effective_pages);
					/* Truncate trailing RAM blocks from the new leading block. */
					vm_datapart_truncate_trailing_swpblocks(part, sizeof_leading);
				}
				break;
#endif /* !CONFIG_NO_SWAP */

			default:
				vm_do_pdir_unmap(page_index, effective_pages);
				break;
			}

			assert(node->vn_prot & VM_PROT_SHARED);
			corepair.cp_node->vn_node.a_vmin = unmap_max + 1;
			corepair.cp_node->vn_node.a_vmax = node->vn_node.a_vmax;
			corepair.cp_node->vn_flags |= node->vn_flags & ~(VM_NODE_FLAG_COREPRT);
			corepair.cp_node->vn_prot          = node->vn_prot;
			corepair.cp_node->vn_vm            = &vm_kernel;
			corepair.cp_part->dp_block         = incref(part->dp_block);
			corepair.cp_node->vn_part          = corepair.cp_part;
			corepair.cp_node->vn_block         = incref(node->vn_block);
			corepair.cp_node->vn_link.ln_pself = &corepair.cp_part->dp_srefs;
			corepair.cp_part->dp_tree.a_vmin   = part->dp_tree.a_vmin + trailing_offset;
			corepair.cp_part->dp_tree.a_vmax   = corepair.cp_part->dp_tree.a_vmin + sizeof_trailing - 1;
			corepair.cp_part->dp_srefs         = corepair.cp_node;
			corepair.cp_part->dp_flags |= part->dp_flags & ~(VM_DATAPART_FLAG_COREPRT | VM_DATAPART_FLAG_HEAPPPP);
			corepair.cp_part->dp_state = part->dp_state;
			part->dp_tree.a_vmax       = (vm_dpage_t)(sizeof_leading - 1);
			node->vn_node.a_vmax       = page_index - 1;
			if (part->dp_flags & VM_DATAPART_FLAG_HEAPPPP && part->dp_pprop_p != NULL) {
				size_t new_bitset_size;
				new_bitset_size = CEILDIV(sizeof_leading,
				                          BITSOF(uintptr_t) / VM_DATAPART_PPP_BITS);
				/* Try to trim unused memory from the page property vector. */
				krealloc_in_place_nx(part->dp_pprop_p, new_bitset_size,
				                     GFP_ATOMIC | GFP_LOCKED |
				                     GFP_NOMMAP | GFP_PREFLT);
			}

			/* Re-insert both the low-order, as well as the new high-order nodes. */
			vm_node_insert(node);
			vm_node_insert(corepair.cp_node);
		}
	}

continue_with_next:
	/* Check if the unmap request was split across multiple nodes. */
	if (effective_pages < num_pages) {
		page_index += effective_pages;
		num_pages -= effective_pages;
		goto again;
	}
}



PRIVATE NOBLOCK struct pending_unmap_ram *
NOTHROW(KCALL pending_unmap_sort)(struct pending_unmap_ram *__restrict self) {
	struct pending_unmap_ram **piter, *iter, *next;
	bool changed;
again:
	/* Really cheap and bad sorting. - Don't look
	 * -> But in actuality, this sorting function should only ever
	 *    be called with no more than a single element, and even
	 *    that is a very rare case on its own. */
	changed = false;
	piter   = (struct pending_unmap_ram **)&self;
	while ((iter = *piter) != NULL) {
		next = iter->pur_next;
		if ((uintptr_t)next < (uintptr_t)iter) {
			*piter         = next;
			next->pur_next = iter;
			piter          = &next->pur_next;
			changed        = true;
		} else {
			piter = &iter->pur_next;
		}
	}
	if (changed)
		goto again;
	return self;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL pending_unmap_merge)(struct pending_unmap_ram *__restrict self) {
	struct pending_unmap_ram *next;
	for (;;) {
		next = self->pur_next;
		if (!next)
			break;
		if ((self->pur_zero != next->pur_zero) ||
		    ((uintptr_t)self + VM_PAGE2ADDR(self->pur_size) != (uintptr_t)next)) {
			self = next;
			continue;
		}
		/* Merge the 2 pending unmap commands. */
		self->pur_size += next->pur_size;
		self->pur_next = next->pur_next;
		if (self->pur_zero)
			memset(next, 0, sizeof(struct pending_unmap_ram));
	}
}


PRIVATE NOBLOCK_IF(flags & GFP_ATOMIC) void
NOTHROW(KCALL vm_kernel_treelock_service)(gfp_t flags) {
	if (ATOMIC_READ(vm_pending_unmap_kernel_ram) != NULL) {
		/* Serve pending request to unmap kernel RAM. */
		struct pending_unmap_ram *pend, *next;
		pend = ATOMIC_XCH(vm_pending_unmap_kernel_ram, NULL);
		if (pend) {
			/* Search the pending chain and merge adjacent free operations.
			 * That way we can prevent a failure loop that can otherwise
			 * happen when `vm_do_unmap_kernel_ram()' keeps on failing to
			 * split a larger node into 2 smaller ones, when in fact one of
			 * the smaller ones may be about to get freed as well! */
			pend = pending_unmap_sort(pend);
			pending_unmap_merge(pend);
			for (;;) {
				size_t num_pages;
				bool is_zero;
				next      = pend->pur_next;
				num_pages = pend->pur_size;
				is_zero   = pend->pur_zero;
				assert(IS_ALIGNED((uintptr_t)pend, PAGESIZE));
				assert(num_pages != 0);
				/* Ensure a consistent memory state if zero-initialized memory is being unmapped. */
				if (is_zero)
					memset(pend, 0, sizeof(struct pending_unmap_ram));
				vm_do_unmap_kernel_ram(VM_ADDR2PAGE((vm_virt_t)pend),
				                       num_pages, is_zero, flags);
				if (!next)
					break;
				pend = next;
			}
		}
	}
	if (ATOMIC_READ(vm_pending_destroy_tasks) != NULL) {
		struct task *pend, *next;
		pend = ATOMIC_XCH(vm_pending_destroy_tasks, NULL);
		while (pend) {
			next = pend->t_sched.s_running.sr_runnxt;
			cpu_assert_integrity();
			task_destroy_raw_impl(pend);
			cpu_assert_integrity();
			pend = next;
		}
	}
}

/* Without blocking, unmap the given range of kernel RAM. */
PUBLIC NOBLOCK void
NOTHROW(FCALL vm_unmap_kernel_ram)(vm_vpage_t page_index,
                                   size_t num_pages,
                                   bool is_zero) {
	if unlikely(!num_pages)
		return;
	assert(page_index >= (vm_vpage_t)KERNEL_BASE_PAGE);
	assert(page_index + num_pages >= page_index);
	assert(page_index + num_pages - 1 <= VM_VPAGE_MAX);
	printk(KERN_DEBUG "Unmap kernel RAM %p...%p%s\n",
	       VM_PAGE2ADDR(page_index),
	       VM_PAGE2ADDR(page_index + num_pages) - 1,
	       is_zero ? " (zero-initialized)" : "");
	if (vm_kernel_treelock_trywrite()) {
		/* Immediately do the unmap. */
		vm_do_unmap_kernel_ram(page_index,
		                       num_pages,
		                       is_zero,
		                       GFP_ATOMIC);
		vm_kernel_treelock_endwrite();
	} else {
		/* Schedule the unmap as pending. */
		struct pending_unmap_ram *pend, *next;
		pend           = (struct pending_unmap_ram *)VM_PAGE2ADDR(page_index);
		pend->pur_size = num_pages;
		pend->pur_zero = is_zero;
		do {
			next = ATOMIC_READ(vm_pending_unmap_kernel_ram);
			pend->pur_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(vm_pending_unmap_kernel_ram, next, pend));
		vm_kernel_treelock_tryservice();
	}
}


/* Acquire a write-lock to the kernel VM, automatically serving any pending
 * requests for unmapping kernel memory, as scheduled by `vm_unmap_kernel_ram()' */
PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) bool KCALL
vm_kernel_treelock_writef(gfp_t flags) THROWS(E_WOULDBLOCK) {
	if (!sync_trywrite(&vm_kernel.v_treelock)) {
		if (flags & GFP_ATOMIC)
			return false;
		sync_write(&vm_kernel.v_treelock);
	}
	vm_kernel_treelock_service(flags);
	return true;
}

PUBLIC NOBLOCK_IF(flags & GFP_ATOMIC) WUNUSED bool
NOTHROW(KCALL vm_kernel_treelock_writef_nx)(gfp_t flags) {
	if (!sync_trywrite(&vm_kernel.v_treelock)) {
		if (flags & GFP_ATOMIC)
			return false;
		if (!sync_write_nx(&vm_kernel.v_treelock))
			return false;
	}
	vm_kernel_treelock_service(flags);
	return true;
}

PUBLIC WUNUSED bool
NOTHROW(KCALL vm_kernel_treelock_write_nx)(void) {
	if (!sync_write_nx(&vm_kernel.v_treelock))
		return false;
	vm_kernel_treelock_service(GFP_NORMAL);
	return true;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL vm_kernel_treelock_trywrite)(void) {
	if (!sync_trywrite(&vm_kernel.v_treelock))
		return false;
	vm_kernel_treelock_service(GFP_ATOMIC);
	return true;
}

PUBLIC void (KCALL vm_kernel_treelock_write)(void) {
	sync_write(&vm_kernel.v_treelock);
	vm_kernel_treelock_service(GFP_NORMAL);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_kernel_treelock_endwrite)(void) {
again:
	sync_endwrite(&vm_kernel.v_treelock);
	if unlikely(vm_kernel_treelock_mustservice()) {
		if (vm_kernel_treelock_trywrite())
			goto again;
	}
}

PUBLIC NOBLOCK void
NOTHROW(KCALL vm_kernel_treelock_tryservice)(void) {
	if (sync_trywrite(&vm_kernel.v_treelock)) {
		vm_kernel_treelock_service(GFP_ATOMIC);
		sync_endwrite(&vm_kernel.v_treelock);
	}
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL vm_kernel_treelock_tryread)(void) {
	if (!sync_tryread(&vm_kernel.v_treelock))
		return false;
	while unlikely(vm_kernel_treelock_mustservice()) {
		if (!sync_tryupgrade(&vm_kernel.v_treelock))
			break;
		vm_kernel_treelock_service(GFP_ATOMIC);
		vm_kernel_treelock_downgrade();
	}
	return true;
}

PUBLIC WUNUSED bool NOTHROW(KCALL vm_kernel_treelock_read_nx)(void) {
	if (!sync_read_nx(&vm_kernel.v_treelock))
		return false;
	while unlikely(vm_kernel_treelock_mustservice()) {
		if (sync_upgrade_nx(&vm_kernel.v_treelock) == 0)
			return false;
		vm_kernel_treelock_service(GFP_NORMAL);
		vm_kernel_treelock_downgrade();
	}
	return true;
}

PUBLIC void KCALL vm_kernel_treelock_read(void) THROWS(E_WOULDBLOCK) {
	sync_read(&vm_kernel.v_treelock);
	while unlikely(vm_kernel_treelock_mustservice()) {
		sync_upgrade(&vm_kernel.v_treelock);
		vm_kernel_treelock_service(GFP_NORMAL);
		vm_kernel_treelock_downgrade();
	}
}

PUBLIC NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_endread)(void) {
	if unlikely(vm_kernel_treelock_mustservice()) {
		if (sync_tryupgrade(&vm_kernel.v_treelock)) {
again_service:
			vm_kernel_treelock_service(GFP_ATOMIC);
			vm_kernel_treelock_endwrite();
			goto check_service;
		}
	}
	sync_endread(&vm_kernel.v_treelock);
check_service:
	if unlikely(vm_kernel_treelock_mustservice()) {
		if (sync_trywrite(&vm_kernel.v_treelock))
			goto again_service;
	}
}

PUBLIC NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_end)(void) {
	sync_end(&vm_kernel.v_treelock);
check_service:
	if unlikely(vm_kernel_treelock_mustservice()) {
		if (sync_trywrite(&vm_kernel.v_treelock)) {
			vm_kernel_treelock_service(GFP_ATOMIC);
			vm_kernel_treelock_endwrite();
			goto check_service;
		}
	}
}

PUBLIC NOBLOCK void NOTHROW(KCALL vm_kernel_treelock_downgrade)(void) {
	if unlikely(vm_kernel_treelock_mustservice()) {
again_service:
		vm_kernel_treelock_service(GFP_ATOMIC);
	}
	sync_downgrade(&vm_kernel.v_treelock);
	if unlikely(vm_kernel_treelock_mustservice()) {
		if (sync_tryupgrade(&vm_kernel.v_treelock))
			goto again_service;
	}
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL vm_kernel_treelock_tryupgrade)(void) {
	if (!sync_tryupgrade(&vm_kernel.v_treelock))
		return false;
	vm_kernel_treelock_service(GFP_ATOMIC);
	return true;
}

PUBLIC WUNUSED unsigned int
NOTHROW(KCALL vm_kernel_treelock_upgrade_nx)(void) {
	unsigned int result;
	result = sync_upgrade_nx(&vm_kernel.v_treelock);
	if (result != 0)
		vm_kernel_treelock_service(GFP_NORMAL);
	return result;
}

PUBLIC bool KCALL
vm_kernel_treelock_upgrade(void) THROWS(E_WOULDBLOCK) {
	bool result;
	result = sync_upgrade(&vm_kernel.v_treelock);
	if (result)
		vm_kernel_treelock_service(GFP_NORMAL);
	return result;
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_UNMAP_KERNEL_RAM_C_INL */
