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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_ENUM_C
#define GUARD_KERNEL_SRC_MEMORY_VM_ENUM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/vm.h>

#include <hybrid/align.h>

#include <assert.h>
#include <string.h>

#include "vm-nodeapi.h"

DECL_BEGIN

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL vm_mapinfo_fini)(struct vm_mapinfo *__restrict self) {
	xdecref_unlikely(self->vmi_block);
	xdecref_unlikely(self->vmi_fspath);
	xdecref_unlikely(self->vmi_fsname);
}

/* Find the first mapped node that overlaps with `minaddr ... maxaddr' */
PRIVATE WUNUSED NONNULL((1)) struct vm_node *
NOTHROW(FCALL vm_find_first_node_between)(struct vm *__restrict self,
                                          UNCHECKED void *minaddr,
                                          UNCHECKED void *maxaddr,
                                          pageid_t *__restrict pmaxpage) {
	pageid_t minpage, maxpage;
	size_t num_pages;
	vm_nodetree_minmax_t minmax;
	num_pages = CEILDIV(((byte_t *)maxaddr - (byte_t *)minaddr) + 1,
	                    PAGESIZE);
	minpage   = PAGEID_ENCODE(minaddr);
	maxpage   = minpage + num_pages - 1;
	*pmaxpage = maxpage;
	if unlikely(maxpage < minpage)
		return NULL; /* Overflow */
	/* Search for the first node within the given page-range */
	minmax.mm_min = minmax.mm_max = NULL;
	vm_nodetree_minmaxlocate(self->v_tree,
	                         minpage,
	                         maxpage,
	                         &minmax);
	assert((minmax.mm_min != NULL) == (minmax.mm_max != NULL));
	return minmax.mm_min;
}


/* Enumerate all mappings contained within the given `enum_minaddr...enum_maxaddr'
 * address range within the given VM `self'. This function will automatically re-
 * assemble memory mappings that had previously been split into multiple nodes,
 * such that adjacent `struct vm_node's that describe a contiguous memory mapping
 * do not appear as individual, separate nodes.
 * @param: cb:           A callback that should be invoked for every mapped memory region
 *                       contained with the given address range `enum_minaddr' ... `enum_maxaddr'
 *                       The sum of return values returned by this callback will eventually be
 *                       returned by this function, unless `cb()' returns a negative value, which
 *                       will cause enumeration to halt immediately, and that same value to be
 *                       propagated to the caller.
 *                       Note that mappings are enumerated in strictly ascending order, and that
 *                       this function guaranties that even in the modifications being made to the
 *                       given `self' while enumeration takes place, the `vmi_min' of all future
 *                       mappings will always be `> vmi_max' of every already/currently enumerated
 *                       mapping.
 * @param: arg:          An argument (cookie) to-be passed to `cb()'
 * @param: enum_minaddr: The starting address of mappings to-be enumerated, such that any mapping
 *                       that overlap with `enum_minaddr ... enum_maxaddr' will be enumerated.
 * @param: enum_maxaddr: Same as `enum_minaddr', but specifies the max address of any enumerated
 *                       mapping. */
PUBLIC ssize_t KCALL
vm_enum(struct vm *__restrict self,
        vm_enum_callback_t cb, void *arg,
        UNCHECKED void *enum_minaddr,
        UNCHECKED void *enum_maxaddr) {
#define PENDING_BUFLEN 64
	struct vm_mapinfo pending[PENDING_BUFLEN];
	size_t i = 0, num_pending = 0;
	ssize_t result = 0, temp;
	size_t index = 0;
	TRY {
		struct vm_node *node;
		pageid_t maxpage;
again_lock_tree_and_search_for_first_node:
		vm_treelock_read(self);
		node = vm_find_first_node_between(self,
		                                  enum_minaddr,
		                                  enum_maxaddr,
		                                  &maxpage);
		while (node) {
			struct vm_mapinfo *ent;
			/* Gather information about this node. */
			ent = &pending[num_pending];
			ent->vmi_min = vm_node_getmin(node);
			if (num_pending) {
				struct vm_mapinfo *prev;
				prev = ent - 1;
				/* Check if `node' might be an extension of `prev' */
				if (prev->vmi_max != (byte_t *)ent->vmi_min - 1)
					goto node_is_not_an_extension;
				if (prev->vmi_prot != node->vn_prot)
					goto node_is_not_an_extension;
				if (!node->vn_part)
					goto node_is_not_an_extension;
				if (prev->vmi_block != node->vn_block)
					goto node_is_not_an_extension;
				if (prev->vmi_offset + vm_mapinfo_size(prev) != vm_datapart_minbyte(node->vn_part))
					goto node_is_not_an_extension;
				if (prev->vmi_fspath != node->vn_fspath)
					goto node_is_not_an_extension;
				if (prev->vmi_fsname != node->vn_fsname)
					goto node_is_not_an_extension;
				/* This _is_ an extension to the previous node! */
				prev->vmi_max = vm_node_getmax(node);
				goto continue_with_next_node;
			}
node_is_not_an_extension:
			ent->vmi_max    = vm_node_getmax(node);
			ent->vmi_prot   = node->vn_prot;
			ent->vmi_block  = xincref(node->vn_block);
			ent->vmi_offset = node->vn_part ? vm_datapart_minbyte(node->vn_part) : 0;
			ent->vmi_fspath = xincref(node->vn_fspath);
			ent->vmi_fsname = xincref(node->vn_fsname);
			ent->vmi_index  = index;
			++num_pending;
			if (num_pending >= PENDING_BUFLEN) {
				/* Buffer is full. (enumerate everything except for the
				 * last entry, such that we cna extend its area of affect
				 * in the event that `node' would still continue) */
				vm_treelock_endread(self);
				/* Enumerate all mappings up until (but _not_ including) the very last. */
				assert(i == 0);
				for (; i < PENDING_BUFLEN - 1; ++i) {
					temp = (*cb)(arg, &pending[i]);
					if unlikely(temp < 0)
						goto err;
					result += temp;
					vm_mapinfo_fini(&pending[i]);
				}
				/* Update enumeration specs to continue extending the last entry. */
				i            = 0;
				num_pending  = 1;
				enum_minaddr = (byte_t *)pending[PENDING_BUFLEN - 1].vmi_max + 1;
				memcpy(&pending[0], &pending[PENDING_BUFLEN - 1], sizeof(struct vm_mapinfo));
				goto again_lock_tree_and_search_for_first_node;
			}
continue_with_next_node:
			node = node->vn_byaddr.ln_next;
			if (!node)
				break;
			if (node->vn_node.a_vmin > maxpage)
				break; /* Don't enumerate this one */
			++index;
		}
		vm_treelock_endread(self);
		/* Enumerate all of the (still) pending entires. */
		for (; i < num_pending; ++i) {
			temp = (*cb)(arg, &pending[i]);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			vm_mapinfo_fini(&pending[i]);
		}
	} EXCEPT {
		for (; i < num_pending; ++i)
			vm_mapinfo_fini(&pending[i]);
		RETHROW();
	}
	return result;
err:
	for (; i < num_pending; ++i)
		vm_mapinfo_fini(&pending[i]);
	return temp;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_ENUM_C */
