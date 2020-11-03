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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_UNMAP_KERNEL_MAP_C
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_UNMAP_KERNEL_MAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/panic.h>
#include <kernel/vm.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>

#include "vm-nodeapi.h"

DECL_BEGIN

/* Unmap a kernel-space memory mapping (that was created using `VM_NODE_FLAG_NOMERGE | VM_NODE_FLAG_PREPARED')
 * from kernel-space, where the caller must be holding a lock to `vm_kernel_treelock_write()'
 * HINT: In order to do this entirely non-blocking, you should make use
 *       of `vm_kernel_pending_operations'! */
PUBLIC NOBLOCK void
NOTHROW(FCALL vm_unmap_kernel_mapping_locked)(PAGEDIR_PAGEALIGNED UNCHECKED void *addr,
                                              PAGEDIR_PAGEALIGNED size_t num_bytes) {
	struct vm_node *node;
	vm_nodetree_minmax_t minmax;
	pageid_t minpageid;
	pageid_t maxpageid;
	assertf(((uintptr_t)addr & PAGEMASK) == 0,
	        "Badly aligned addr:%p", addr);
	assertf((num_bytes & PAGEMASK) == 0,
	        "Badly aligned num_bytes:%#" PRIxSIZ,
	        num_bytes);
	if unlikely(!num_bytes)
		return;
	assertf(ADDRRANGE_ISKERN(addr, (byte_t *)addr + num_bytes - 1),
	        "Not a kernel address range: %p...%p",
	        addr, (byte_t *)addr + num_bytes - 1);
	assert(sync_writing(&vm_kernel));
	minpageid = PAGEID_ENCODE((byte_t *)addr);
	maxpageid = PAGEID_ENCODE((byte_t *)addr + num_bytes - 1);
	assertf(maxpageid >= minpageid,
	        "Address range overflows: %p...%p",
	        addr, (byte_t *)addr + num_bytes - 1);
	minmax.mm_min = minmax.mm_max = NULL;
	vm_nodetree_minmaxlocate(vm_kernel.v_tree,
	                         minpageid,
	                         maxpageid,
	                         &minmax);
	assert(minpageid == minmax.mm_min_min);
	assert(maxpageid == minmax.mm_max_max);
	assert(minmax.mm_min);
	assert(minmax.mm_max);
	/* Assert that all memory mappings within the given range have been prepared! */
	node = minmax.mm_min;
	for (;;) {
		struct vm_node *next;
		assert(node);
		assert(node->vn_vm == &vm_kernel);
		assertf((node->vn_flags & (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE)) ==
		        /*             */ (VM_NODE_FLAG_PREPARED | VM_NODE_FLAG_NOMERGE),
		        "node: %p...%p\n"
		        "node->vn_flags = %#" PRIxSIZ,
		        vm_node_getmin(node),
		        vm_node_getmax(node),
		        node->vn_flags);
		next = VM_NODE_NEXT(node);
		assert(vm_node_getminpageid(node) >= minpageid);
		assert(vm_node_getmaxpageid(node) <= maxpageid);
		if unlikely(node->vn_flags & VM_NODE_FLAG_KERNPRT) {
			kernel_panic("Attempted to munmap() a kernel part at %p...%p",
			             vm_node_getmin(node), vm_node_getmax(node));
		}
		pagedir_unmap(vm_node_getstart(node),
		              vm_node_getsize(node));
		/* Remove the node from the VM. */
		vm_nodetree_remove(&vm_kernel.v_tree, vm_node_getstartpageid(node));
		LLIST_REMOVE(node, vn_byaddr);
		/* Destroy the old node. */
		vm_node_destroy(node);
		if (node == minmax.mm_max)
			break;
		node = next;
	}
	vm_supersync(addr, num_bytes);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_UNMAP_KERNEL_MAP_C */
