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
#ifdef __INTELLISENSE__
#include "mman-unmap.c"
//#define   DEFINE_mman_unmap
//#define DEFINE_mman_protect
#define DEFINE_mman_madvise
#endif /* __INTELLISENSE__ */

#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/sync.h>
#include <kernel/panic.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <sys/mman.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <string.h>

DECL_BEGIN

#ifndef DBG_memset
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */
#endif /* !DBG_memset */

#ifdef DEFINE_mman_unmap
/* Unmap all memory mappings within the given address range.
 * The actual range is widened to include all whole pages that overlap the given range.
 * @param: addr:      The base address at which to start unmapping memory.
 * @param: num_bytes: The # of continuous bytes of memory to unmap, starting at `addr'
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of unmapped bytes of memory. */
PUBLIC NONNULL((1)) size_t KCALL
mman_unmap(struct mman *__restrict self,
           UNCHECKED void *addr, size_t num_bytes,
           unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT)
#define LOCAL_FUNCTION_NAME "mman_unmap"
#elif defined(DEFINE_mman_protect)
/* Update access protection flags within the given address range.
 * @param: addr:      The base address at which to start changing protection.
 * @param: num_bytes: The number of continuous bytes of memory to change, starting at `addr'
 * @param: prot_mask: Mask of protection bits that should be kept (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 *                    Other bits are silently ignored.
 * @param: prot_more: Set of protection bits that should be added (Set of `PROT_EXEC | PROT_WRITE | PROT_READ').
 *                    Other bits are silently ignored.
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of (possibly) altered bytes of memory. */
PUBLIC NONNULL((1)) size_t KCALL
mman_protect(struct mman *__restrict self,
             UNCHECKED void *addr, size_t num_bytes,
             unsigned int prot_mask, unsigned int prot_more,
             unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT)
#define LOCAL_FUNCTION_NAME "mman_protect"
#elif defined(DEFINE_mman_madvise)
/* Kernel-level implementation of `madvise(2)'
 * @param: addr:      The base address at which to start changing protection.
 * @param: num_bytes: The number of continuous bytes of memory to change, starting at `addr'
 * @param: advice:    The advice to apply (one of `MADV_*', except `MADV_POPULATE_*')
 * @param: flags:     Set of `MMAN_UNMAP_*'
 * @return: * :       The actual # of (possibly) altered bytes of memory. */
PUBLIC NONNULL((1)) size_t KCALL
mman_madvise(struct mman *__restrict self,
             UNCHECKED void *addr, size_t num_bytes,
             unsigned int advice, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT)
#define LOCAL_FUNCTION_NAME "mman_madvise"
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
#ifdef DEFINE_mman_unmap
#define LOCAL_must_modify_node(node) 1
#elif defined(DEFINE_mman_protect)
#define LOCAL_must_modify_node(node) \
	((node)->mn_flags != (((node)->mn_flags & mnode_flags_mask) | mnode_flags_more))
#elif defined(DEFINE_mman_madvise)
#define LOCAL_must_modify_node(node) 1
#endif /* ... */
	struct mnode_tree_minmax mima;
	struct mnode *node;
#ifdef DEFINE_mman_unmap
	struct mnode_slist deleted_nodes;
#endif /* DEFINE_mman_unmap */
	size_t result = 0;
#ifdef DEFINE_mman_madvise
	struct ccinfo info;
	struct mpart_trim_data trim_data;
#endif /* DEFINE_mman_madvise */

#ifdef DEFINE_mman_protect
	uintptr_t mnode_flags_mask, mnode_flags_more;
	mnode_flags_mask = mnodeflags_from_prot_noshared(prot_mask) |
	                   ~(uintptr_t)(MNODE_F_PREAD | MNODE_F_PWRITE |
	                                MNODE_F_PEXEC);
	mnode_flags_more = mnodeflags_from_prot_noshared(prot_more);
#endif /* DEFINE_mman_protect */

	/* Deal with the special case of the request size being zero */
	if unlikely(!num_bytes)
		return 0;

#ifdef DEFINE_mman_madvise
	ccinfo_init(&info, GFP_NORMAL, (size_t)-1);
	mpart_trim_data_init(&trim_data, &info, NULL, self, 0); /* The mode-argument is overwritten as needed */
	RAII_FINALLY { mpart_trim_data_fini(&trim_data); };
#endif /* DEFINE_mman_madvise */
	TRY {
		/* Lock the memory manager. */
again_acquire_lock:
		mman_lock_acquire(self);

		/* Deal with `MMAN_UNMAP_FAULTIFUNUSED' */
		if (flags & MMAN_UNMAP_FAULTIFUNUSED) {
			/* Make sure that the entirety of the given address range is mapped.
			 * If it isn't, then don't do anything at all, and immediately  fail
			 * with an exception. */
			byte_t *addr_iter, *endaddr;
			addr_iter = (byte_t *)addr;
			endaddr   = (byte_t *)addr + num_bytes;
			for (;;) {
				node = mnode_tree_locate(self->mm_mappings, addr_iter);
				if unlikely(!node) {
					mman_lock_release(self);
					THROW(E_SEGFAULT_UNMAPPED, addr_iter,
					      E_SEGFAULT_CONTEXT_FAULT |
					      E_SEGFAULT_CONTEXT_UNMAP);
				}
				addr_iter = (byte_t *)mnode_getendaddr(node);
				if (addr_iter >= endaddr)
					break;
			}
		}

		if (!(flags & MMAN_UNMAP_NOSPLIT)) {
			byte_t *maxaddr;

			/* Ensure that we're working on a properly page-aligned address range. */
			if unlikely(!IS_ALIGNED((uintptr_t)addr, PAGESIZE)) {
				num_bytes += (uintptr_t)addr & (PAGESIZE - 1);
				addr = (byte_t *)((uintptr_t)addr & ~(PAGESIZE - 1));
			}
			if unlikely(!IS_ALIGNED(num_bytes, PAGESIZE))
				num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);

			/* Unless  `MMAN_UNMAP_NOSPLIT'  has  been given,  or  in the  case  of mprotect,
			 * nothing would change about border-nodes, make use of `mnode_split_or_unlock()'
			 * to split nodes not fully contained within the given address range. */
			node = mnode_tree_locate(self->mm_mappings, addr);
			if (node && mnode_getminaddr(node) != addr &&
			    !(node->mn_flags & MNODE_F_NOSPLIT) && LOCAL_must_modify_node(node)) {
				if (!mnode_split_or_unlock(self, node, addr, NULL))
					goto again_acquire_lock;
			}
			maxaddr = (byte_t *)addr + num_bytes - 1;
			node = mnode_tree_locate(self->mm_mappings, maxaddr);
			if (node && mnode_getmaxaddr(node) != maxaddr &&
			    !(node->mn_flags & MNODE_F_NOSPLIT) && LOCAL_must_modify_node(node)) {
				if (!mnode_split_or_unlock(self, node, maxaddr + 1, NULL))
					goto again_acquire_lock;
			}
		}

#ifdef DEFINE_mman_unmap
		SLIST_INIT(&deleted_nodes);
#endif /* DEFINE_mman_unmap */

		/* Load the range of affected memory-nodes. */
#ifdef DEFINE_mman_madvise
again_minmaxlocate:
#endif /* DEFINE_mman_madvise */
		mnode_tree_minmaxlocate(self->mm_mappings, addr,
		                        (byte_t *)addr + num_bytes - 1,
		                        &mima);
		if unlikely(mima.mm_min == NULL)
			goto unlock_and_done;

		/* Make sure that all of the affected nodes have been prepared. */
#ifdef DEFINE_mman_madvise
		{
			VIRT byte_t *node_minaddr;
			VIRT byte_t *node_endaddr;
			size_t node_offset;
			assert(node);
			node_minaddr = (byte_t *)mnode_getminaddr(node);
			node_endaddr = (byte_t *)mnode_getendaddr(node);
			assert(node_endaddr > (byte_t *)addr);
			if (node_minaddr > (byte_t *)addr) {
				node_offset = node_minaddr - (byte_t *)addr;
				addr = (void *)((uintptr_t)addr + node_offset);
				assertf(num_bytes > node_offset,
				        "Why did this node get enumerated? It's beyond "
				        "the end of the caller-given address range!\n"
				        "given: %p-%p\n"
				        "node:  %p-%p",
				        addr, (byte_t *)addr + num_bytes - 1,
				        mnode_getminaddr(node),
				        mnode_getmaxaddr(node));
				num_bytes -= node_offset;
			}

			/* Apply an advice on how this node should behave. */
			if (!mnode_advise_or_unlock(node, &trim_data, advice))
				goto again_acquire_lock;

			/* Skip  at  least  until  the  original  end  of  the   node.
			 * Above already asserted that `node_endaddr > (byte_t *)addr' */
			node_offset = node_endaddr - (byte_t *)addr;
			addr        = node_endaddr;
			if (OVERFLOW_USUB(num_bytes, node_offset, &num_bytes))
				num_bytes = 0;

			/* Search for more nodes which may be located after `node'
			 * Note  that we have to re-search for nodes every step of
			 * the way here,  since `mnode_advise_or_unlock' may  have
			 * split/merged nodes */
			if (num_bytes <= 0)
				goto unlock_and_done;

			/* Skip more memory in case `mnode_advise_or_unlock()' made the node grow upwards. */
			node_endaddr = (byte_t *)mnode_getendaddr(node);
			if (node_endaddr > (byte_t *)addr) {
				node_offset = node_endaddr - (byte_t *)addr;
				addr        = node_endaddr;
				if (OVERFLOW_USUB(num_bytes, node_offset, &num_bytes))
					num_bytes = 0;
				if (num_bytes <= 0)
					goto unlock_and_done;
			}
			goto again_minmaxlocate;
		}
#else /* !DEFINE_mman_madvise */
		for (node = mima.mm_min;;) {
			assert(node);
#ifdef DEFINE_mman_protect
#define LOCAL_must_prepare_node(node)                              \
			(likely(!(node->mn_flags & MNODE_F_MPREPARED)) &&      \
			 LOCAL_must_modify_node(node) &&                       \
			 mnodeflags_prot_more_restrictive(node->mn_flags,      \
			                                  (node->mn_flags &    \
			                                   mnode_flags_mask) | \
			                                  mnode_flags_more))
#else /* DEFINE_mman_protect */
#define LOCAL_must_prepare_node(node)                         \
			(likely(!(node->mn_flags & MNODE_F_MPREPARED)) && \
			 LOCAL_must_modify_node(node))
#endif /* !DEFINE_mman_protect */

			/* Don't allow `PROT_WRITE' to be set when `MNODE_F_PDENYWRITE' was set. */
#ifdef DEFINE_mman_protect
			if unlikely((mnode_flags_more & MNODE_F_PWRITE) &&
			            (node->mn_flags & MNODE_F_PDENYWRITE)) {
				struct mnode *iter;
				/* Undo everything... */
				for (iter = mima.mm_min; iter != node;
				     iter = mnode_tree_nextnode(iter)) {
					assert(iter);
					if (LOCAL_must_prepare_node(iter)) {
						pagedir_unprepare_p(self->mm_pagedir_p,
						                    mnode_getaddr(iter),
						                    mnode_getsize(iter));
					}
				}
				mman_lock_release(self);
				THROW(E_INVALID_HANDLE_OPERATION, -1, /* We no longer know the FD... */
				      E_INVALID_HANDLE_OPERATION_MMAP,
				      IO_RDONLY);
			}
#endif /* DEFINE_mman_protect */

			/* If necessary, prepare the mem-node for remapping. */
			if (LOCAL_must_prepare_node(node)) {
				if unlikely(!pagedir_prepare_p(self->mm_pagedir_p,
				                                mnode_getaddr(node),
				                                mnode_getsize(node))) {
					struct mnode *iter;
					/* Undo everything... */
					for (iter = mima.mm_min; iter != node;
					     iter = mnode_tree_nextnode(iter)) {
						assert(iter);
						if (LOCAL_must_prepare_node(iter)) {
							pagedir_unprepare_p(self->mm_pagedir_p,
							                    mnode_getaddr(iter),
							                    mnode_getsize(iter));
						}
					}
					mman_lock_release(self);

					/* Throw the relevant exception. */
					THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, PAGESIZE);
				}
			}
			if (node == mima.mm_max)
				break;
			node = mnode_tree_nextnode(node);
		}
#endif /* !DEFINE_mman_madvise */
#undef LOCAL_must_prepare_node
	} EXCEPT {
		/* If we split them earlier, re-merge nodes if something went wrong! */
		if (!(flags & MMAN_UNMAP_NOSPLIT))
			mman_mergenodes(self);
		RETHROW();
	}

#ifndef DEFINE_mman_madvise
	/* ==== Point of no return */

	for (node = mima.mm_min;;) {
		struct mnode *next = NULL;
		if (node != mima.mm_max)
			next = mnode_tree_nextnode(node);

		/* Check if we have to modify this node. */
		if (!LOCAL_must_modify_node(node))
			goto next_node;

		/* Deal with the case where `node' is a kernel part. */
		if unlikely(node->mn_flags & MNODE_F_KERNPART) {
			if (flags & MMAN_UNMAP_NOKERNPART)
				goto next_node;
			kernel_panic(LOCAL_FUNCTION_NAME ": Attempted to manipulate kern-part node at %p-%p",
			             mnode_getminaddr(node),
			             mnode_getmaxaddr(node));
		}

#ifdef DEFINE_mman_unmap
		/* Remove the node from the mappings tree. */
		mman_mappings_removenode(self, node);

		/* Make  sure to set  the UNMAPPED bit,  so that other kernel
		 * components can identify this node as having been unmapped!
		 * This mainly effects `mpart_split()' */
		atomic_or(&node->mn_flags, MNODE_F_UNMAPPED);

		/* Remove the node from the writable-list in case it was apart of it. */
		if (LIST_ISBOUND(node, mn_writable))
			LIST_REMOVE(node, mn_writable);

		/* Keep track of how many nodes are mapping a particular module. */
		if (node->mn_module)
			module_dec_nodecount(node->mn_module);
		DBG_memset(&node->mn_module, 0xcc, sizeof(node->mn_module));

		/* Enqueue the node to-be deleted once we've released our lock to `self' */
		SLIST_INSERT(&deleted_nodes, node, _mn_dead);

		/* Actually do the unmap, and sync the address range. */
		{
			void *node_addr;
			size_t node_size;
			node_addr = mnode_getaddr(node);
			node_size = mnode_getsize(node);
			pagedir_unmap_p(self->mm_pagedir_p, node_addr, node_size);
			pagedir_unprepare_p(self->mm_pagedir_p, node_addr, node_size);
			mman_sync_p(self, node_addr, node_size);
		}
#elif defined(DEFINE_mman_protect)
		{
			uintptr_t old_flags, new_flags;
			old_flags = node->mn_flags;
			new_flags = (old_flags & mnode_flags_mask) | mnode_flags_more;
			if (mnodeflags_prot_more_restrictive(old_flags, new_flags)) {
				struct mpart *part = node->mn_part;
				if likely(part != NULL) {
					pagedir_prot_t newperm;
					void *node_addr;
					size_t node_size;
					node_addr = mnode_getaddr(node);
					node_size = mnode_getsize(node);
					if (mpart_lock_tryacquire(part)) {
						/* Re-create the page directory mapping for the part. */
						newperm = mpart_mmap_node_p(part, self->mm_pagedir_p,
						                            node_addr, node_size,
						                            node->mn_partoff,
						                            node);
						mpart_lock_release(part);
					} else {
						/* Just delete the mapping, and let the #PF-handler figure it out lazily. */
						pagedir_unmap_p(self->mm_pagedir_p,
						                node_addr, node_size);
						newperm = 0;
					}

					/* Undo the prepare that was originally done above. */
					if (!(node->mn_flags & MNODE_F_MPREPARED)) {
						pagedir_unprepare_p(self->mm_pagedir_p,
						                    node_addr, node_size);
					}

					/* Sync the affected address range within the given mman. */
					mman_sync_p(self, node_addr, node_size);

					/* If write-permissions went away, remove the node from  the
					 * list of writable nodes stored within the associated mman. */
					if (LIST_ISBOUND(node, mn_writable) && !(newperm & PAGEDIR_PROT_WRITE))
						LIST_UNBIND(node, mn_writable);
				}
			}
			node->mn_flags = new_flags;
		}
#endif /* ... */

next_node:
		if (next == NULL)
			break;
		node = next;
	}
#endif /* !DEFINE_mman_madvise */

#if defined(DEFINE_mman_protect) || defined(DEFINE_mman_madvise)
	/* Try to re-merge nodes within the min/max bounds, since the change
	 * in node permissions  may not allow  previously separate nodes  to
	 * become one. */
	mman_mergenodes_inrange(self,
	                        (byte_t const *)addr,
	                        (byte_t const *)addr + num_bytes - 1);
#endif /* DEFINE_mman_protect || DEFINE_mman_madvise */

unlock_and_done:
	mman_lock_release(self);
#ifdef DEFINE_mman_unmap
	while (!SLIST_EMPTY(&deleted_nodes)) {
		node = SLIST_FIRST(&deleted_nodes);
		SLIST_REMOVE_HEAD(&deleted_nodes, _mn_dead);
		mnode_destroy(node);
	}
#endif /* DEFINE_mman_unmap */
	return result;
#undef LOCAL_must_modify_node
}

#undef LOCAL_FUNCTION_NAME

DECL_END

#undef DEFINE_mman_unmap
#undef DEFINE_mman_protect
#undef DEFINE_mman_madvise
