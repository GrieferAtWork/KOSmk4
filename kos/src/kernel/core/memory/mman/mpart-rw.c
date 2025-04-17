/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_RW_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_RW_C 1
#define __WANT_MNODE__mn_dead
#define __WANT_MNODE__mn_alloc
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/flags.h>
#include <kernel/mman/mfile-map.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hybrid/align.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

/*[[[config CONFIG_HAVE_AUTO_MMAP = true]]]*/
#ifdef CONFIG_NO_AUTO_MMAP
#undef CONFIG_HAVE_AUTO_MMAP
#elif !defined(CONFIG_HAVE_AUTO_MMAP)
#define CONFIG_HAVE_AUTO_MMAP
#elif (-CONFIG_HAVE_AUTO_MMAP - 1) == -1
#undef CONFIG_HAVE_AUTO_MMAP
#define CONFIG_NO_AUTO_MMAP
#endif /* ... */
/*[[[end]]]*/


#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* I/O size threshold that must be met or exceeded in order for `mpart_read()'
 * to try and make use of `mpart_mmapread()' in order to do the I/O operation.
 *
 * Notes:
 * - Must *NOT* be set to a value that is less than PAGESIZE. If you were to
 *   set to a value lower  than this, `mpart_read()' and  `mpart_mmapread()'
 *   might call each other and cause a stack overflow.
 * - Set this value to `(size_t)-1' to soft-disable the auto-mmap feature.
 * - When set to `0', the kernel was configured to have this feature be
 *   hard-disabled (s.a. `CONFIG_HAVE_AUTO_MMAP').
 *
 * The value of this variable is exposed in `/proc/kos/mm/part-automap-threshold' */
#ifdef CONFIG_HAVE_AUTO_MMAP
PUBLIC ATTR_READMOSTLY size_t mpart_mmapread_threshold = 6 * PAGESIZE;
#else /* CONFIG_HAVE_AUTO_MMAP */
DATDEF size_t const _mpart_mmapread_threshold ASMNAME("mpart_mmapread_threshold");
PUBLIC size_t const _mpart_mmapread_threshold = 0;
#endif /* !CONFIG_HAVE_AUTO_MMAP */

#ifdef CONFIG_HAVE_AUTO_MMAP
/* Load and verify the nodes within the given address range.
 * @return: true:  Verification success -> proceed
 * @return: false: Verification failed -> can't do mmapread */
PRIVATE NONNULL((1, 4)) bool
NOTHROW(KCALL mpart_mmapread_loadnodes)(struct mman *__restrict mm,
                                        PAGEDIR_PAGEALIGNED byte_t *mmap_minaddr,
                                        PAGEDIR_PAGEALIGNED byte_t *mmap_endaddr,
                                        struct mnode_tree_minmax *__restrict mima) {
	struct mnode *node;
	mman_mappings_minmaxlocate(mm, mmap_minaddr, mmap_endaddr - 1, mima);
	assert((mima->mm_min != NULL) == (mima->mm_max != NULL));
	if unlikely(!mima->mm_min)
		goto nope; /* Buffer isn't mapped? */
	if unlikely(mnode_getminaddr(mima->mm_min) > mmap_minaddr)
		goto nope; /* (Part of) buffer isn't mapped? */
	if unlikely(mnode_getendaddr(mima->mm_max) < mmap_endaddr)
		goto nope; /* (Part of) buffer isn't mapped? */

	for (node = mima->mm_min;;) {
		struct mnode *next;
		struct mpart *part;
		/* XXX: It would be possible to support inheritance of `MNODE_F_MLOCK' and `MNODE_F_NOCORE'... */
		if unlikely((node->mn_flags & (MNODE_F_PMASK | MNODE_F_SHARED | MNODE_F_UNMAPPED |
		                               MNODE_F_KERNPART | MNODE_F_MHINT | MNODE_F_MLOCK |
		                               MNODE_F_NOSPLIT | MNODE_F_NOCORE)) !=
		            /*             */ (MNODE_F_PREAD | MNODE_F_PWRITE))
			goto nope; /* Unsupported memory protection flags */
		if unlikely(node->mn_module) {
			/* Buffer  is part of a cached module? (*might* be able to happen for userelf modules,
			 * but that's a can of worms to complicated to handle, so just don't support and fail) */
			goto nope;
		}
		part = node->mn_part;
		if unlikely(!part)
			goto nope; /* Buffer is reserved memory? */
		if unlikely(!mpart_isanon_atomic(part))
			goto nope; /* Buffer isn't backed by anonymous memory. */
		if (node == mima->mm_max)
			break;
		next = mnode_tree_nextnode(node);
		assert(next);

		/* Assert continuous-ness of the caller-given buffer area. */
		if unlikely(mnode_getendaddr(node) != mnode_getminaddr(node))
			goto nope;
		node = next;
	}

	return true;
nope:
	return false;
}

PRIVATE NONNULL((1, 2, 3, 4)) void
NOTHROW(KCALL mnode_range_remove_and_unmap)(struct mman *mm,
                                            struct mnode *minnode,
                                            struct mnode *endnode,
                                            struct mnode_slist *__restrict deleted_nodes) {
	struct mnode *node, *next;
	for (node = minnode; node != endnode; node = next) {
		next = mnode_tree_nextnode(node);
		assert(node->mn_mman == mm);

		/* Unmap the node (s.a. implementation of `mman_unmap()') */
		mman_mappings_removenode(mm, node);
		atomic_or(&node->mn_flags, MNODE_F_UNMAPPED);
		if (LIST_ISBOUND(node, mn_writable))
			LIST_REMOVE(node, mn_writable);
		if (node->mn_module)
			module_dec_nodecount(node->mn_module);
		DBG_memset(&node->mn_module, 0xcc, sizeof(node->mn_module));
		SLIST_INSERT(deleted_nodes, node, _mn_dead);

		/* NOTE: The actual unmapping in the page directory is done by the caller. */
	}
}

/* Special mpart functions that *try* to implement large reads from `self' by
 * creating MAP_PRIVATE memory mappings of `self' in `THIS_MMAN' over-top the
 * given target buffer, which (when  accessed) will lazily load the  contents
 * of the file that is backing `self' into memory.
 *
 * These functions should never need to  be called explicitly, as they  are
 * called automatically from `mpart_read()' and `mpart_readv()', which will
 * invoke  this functions for "large" (s.a. `mpart_mmapread_threshold') I/O
 * operations.
 *
 * @assume(num_bytes >= PAGESIZE);
 * @return: * : The number of bytes that were "read" by this function.
 * @return: 0 : Unable to replace target  buffer with an automatic  memory
 *              mapping. Reasons include the  buffer not being mapped,  or
 *              being backed by VIO memory. In any case: the caller should
 *              just do a normal read  operation, behaving as though  this
 *              function didn't exist. */
PUBLIC NONNULL((1)) size_t KCALL
mpart_mmapread(struct mpart *__restrict self, NCX void *dst,
               size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct mnode_slist deleted_nodes;
	struct mnode_tree_minmax mima;
	struct mfile *orig_map_file;
	pos_t orig_filepos;
	REF struct mfile *map_file;
	struct mfile_map_with_unlockinfo fmap;
	REF struct mpart *lobuf_part, *hibuf_part;
	size_t result = 0;
	struct mman *mm;
	byte_t *bufend;
	PAGEDIR_PAGEALIGNED byte_t *mmap_minaddr;
	PAGEDIR_PAGEALIGNED byte_t *mmap_endaddr;
	size_t unaligned_headbytes;
	size_t unaligned_tailbytes;
	size_t map_size;

	/* Do some quick checks to see if mmap is allowed. */
	if unlikely(ADDRRANGE_ISKERN_PARTIAL(dst, (byte_t *)dst + num_bytes))
		goto done; /* Not allowed for kernel-space address ranges. */
	mm = THIS_MMAN;
	if unlikely(mm == &mman_kernel)
		goto done; /* Not allowed for the kernel mman. */

	/* Figure out where we want to place the mnode, and so on... */
	bufend       = (byte_t *)dst + num_bytes;
	mmap_minaddr = (PAGEDIR_PAGEALIGNED byte_t *)CEIL_ALIGN((uintptr_t)dst, PAGESIZE);
	mmap_endaddr = (PAGEDIR_PAGEALIGNED byte_t *)FLOOR_ALIGN((uintptr_t)bufend, PAGESIZE);
	if unlikely(mmap_minaddr >= mmap_endaddr)
		goto done; /* The effective, mmap'd area would be empty */
	map_size = (size_t)(mmap_endaddr - mmap_minaddr);

	/* Figure out how much memory we need to read the old fashioned way at the head/tail */
	unaligned_headbytes = (size_t)(mmap_minaddr - (byte_t *)dst);
	unaligned_tailbytes = (size_t)(bufend - mmap_endaddr);
	assert(unaligned_headbytes < PAGESIZE);
	assert(unaligned_tailbytes < PAGESIZE);

	/* Read head memory the old fashioned way. */
	if likely(unaligned_headbytes) {
		result = mpart_read_nommap(self, dst, unaligned_headbytes, filepos);
		assert(result <= unaligned_headbytes);
		if unlikely(result != unaligned_headbytes)
			goto done;
		filepos += result;
	}
	DBG_memset(&dst, 0xcc, sizeof(dst));
	DBG_memset(&unaligned_headbytes, 0xcc, sizeof(unaligned_headbytes));

	/* Do an initial verification to check that the buffer can be remapped. */
#ifndef __OPTIMIZE_SIZE__
	{
		bool ok;
		mman_lock_acquire(mm);
		ok = mpart_mmapread_loadnodes(mm, mmap_minaddr, mmap_endaddr, &mima);
		mman_lock_release(mm);
		if unlikely(!ok)
			goto done;
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Extract the file from the caller-given mem-part. */
	mpart_lock_acquire(self);
	map_file = incref(self->mp_file);
	mpart_lock_release(self);

	/* Assert that the file supports "raw" I/O (iow: can be mmap'd normally) */
	if unlikely(!mfile_hasrawio(map_file))
		goto done_map_file;

	/* Check if the file is unaligned.
	 * -> If so, then we have to create a misaligned wrapper file
	 *
	 * This case is highly likely since it's only not the case when
	 * user-space  `malloc(3)' happens to match the sub-page offset
	 * of the file position where the user wants to read from. */
	orig_map_file = map_file;
	orig_filepos  = filepos;
	if likely((filepos & map_file->mf_part_amask) != 0) {
		FINALLY_DECREF_UNLIKELY(map_file);
		map_file = mfile_create_misaligned_wrapper(map_file, &filepos);
		assert((filepos & map_file->mf_part_amask) == 0);
	}

	/* Create a file mapping */
	TRY {
		mfile_map_init_and_acquire(&fmap.mmwu_map, map_file,
		                           filepos, map_size,
		                           PROT_READ | PROT_WRITE, 0);
	} EXCEPT {
		decref_likely(map_file);
		RETHROW();
	}
	fmap.ui_unlock = &mfile_map_with_unlockinfo_unlock;
again_lock_mm:
	TRY {
		if (!mman_lock_tryacquire(mm)) {
			mfile_map_release(&fmap.mmwu_map);
			mman_lock_waitfor(mm);
again_lock_fmap_and_mm:
			mfile_map_acquire(&fmap.mmwu_map);
			goto again_lock_mm;
		}

		/* Lookup + verify the target buffer */
#ifdef __OPTIMIZE_SIZE__
		if (!mpart_mmapread_loadnodes(mm, mmap_minaddr, mmap_endaddr, &mima))
#else /* __OPTIMIZE_SIZE__ */
		if unlikely(!mpart_mmapread_loadnodes(mm, mmap_minaddr, mmap_endaddr, &mima))
#endif /* !__OPTIMIZE_SIZE__ */
		{
			goto done_fini_fmap_unlock_mm;
		}

		/* Split memory at the lower address boundary. */
		if (mnode_getminaddr(mima.mm_min) != mmap_minaddr) {
			struct mnode *old_min;
			if unlikely(mnode_getminaddr(mima.mm_min) > mmap_minaddr)
				goto done_fini_fmap; /* Buffer isn't mapped? */
			if (!mnode_split_or_unlock(mm, mima.mm_min, mmap_minaddr, &fmap))
				goto again_lock_fmap_and_mm;
			old_min     = mima.mm_min;
			mima.mm_min = mnode_tree_nextnode(old_min);
			if (mima.mm_max == old_min)
				mima.mm_max = mima.mm_min;
		}
		assert(mnode_getminaddr(mima.mm_min) == mmap_minaddr);
	} EXCEPT {
		mfile_map_fini(&fmap.mmwu_map);
		decref_likely(map_file);
		RETHROW();
	}

	/* ===== Point of no return ===== */
	printk(KERN_TRACE "[mmapread] Replace buffer at %p-%p with MAP_PRIVATE "
	                  /**/ "mapping of mfile %p@%" PRIu64,
	       mmap_minaddr, mmap_endaddr, map_file, (uint64_t)filepos);
	if likely(map_file != orig_map_file) {
		printk(KERN_TRACE " [alias: %p@%" PRIu64 "]",
		       orig_map_file, (uint64_t)orig_filepos);
	}
	printk(KERN_TRACE "\n");

	/* Load the mem-parts of the lower-  and upper node-bounds, so we  can
	 * try and trim them below. This must be done in order to free backing
	 * memory of the file-mapped buffer  region, in case it was  allocated
	 * as one continuous part across the entire caller-given buffer  area. */
	lobuf_part = mima.mm_min->mn_part;
	hibuf_part = mima.mm_max->mn_part;
	incref(lobuf_part);
	incref(hibuf_part);

	/* Trim the start of the last node such that it
	 * doesn't  conflict with the new file mapping. */
	assertf(mmap_endaddr <= mnode_getendaddr(mima.mm_max),
	        "mmap_endaddr:                  %p\n"
	        "mnode_getendaddr(mima.mm_max): %p",
	        mmap_endaddr, mnode_getendaddr(mima.mm_max));
	if unlikely(mmap_endaddr >= mnode_getendaddr(mima.mm_max)) {
		/* The end node is entirely contained within the file-map area.
		 * -> Update the max-node pointer to reflect the fact that it will be replaced in its entirety.
		 *
		 * This is actually a rather unlikely case since it relies on the chance
		 * that  the user is reading into a buffer up to that buffer's page end.
		 *
		 * This isn't usually the case when reading into memory from `malloc(3)' */
		mima.mm_max = mnode_tree_nextnode(mima.mm_max);
	} else {
		size_t ltrim_bytes;
		ltrim_bytes = mmap_endaddr - (byte_t *)mnode_getminaddr(mima.mm_max);
		mnode_tree_removenode(&mm->mm_mappings, mima.mm_max);
		mima.mm_max->mn_minaddr += ltrim_bytes;
		mima.mm_max->mn_partoff += ltrim_bytes;
		mnode_tree_insert(&mm->mm_mappings, mima.mm_max);
	}

	/* Remove existing nodes in the range of [mima.mm_min,mima.mm_max) */
	SLIST_INIT(&deleted_nodes);
	mnode_range_remove_and_unmap(mm, mima.mm_min, mima.mm_max, &deleted_nodes);

	/* Delete page directory mappings within the buffer area such
	 * that these mappings will  get re-loaded as file  mappings.
	 *
	 * This can be done before we insert the new nodes, since we're
	 * still  holding a lock  to the mman,  meaning that if another
	 * thread  were to fault  before we inserted  the new nodes, it
	 * would  simply block until  it could lock  the mman (at which
	 * point the new nodes will be present). */
	if likely(pagedir_prepare(mmap_minaddr, map_size)) {
		pagedir_unmap(mmap_minaddr, map_size);
		pagedir_unprepare(mmap_minaddr, map_size);
		pagedir_sync_smp(mmap_minaddr, map_size);
	} else {
		pagedir_unmap_userspace();
		pagedir_syncall_smp();
	}

	/* Insert the new file nodes into the mman. */
	assert(!mnode_tree_rlocate(mm->mm_mappings, mmap_minaddr, mmap_endaddr - 1));
	while (!SLIST_EMPTY(&fmap.mmwu_map.mfm_nodes)) {
		struct mnode *node;
		node = SLIST_FIRST(&fmap.mmwu_map.mfm_nodes);
		SLIST_REMOVE_HEAD(&fmap.mmwu_map.mfm_nodes, _mn_alloc);
		/* NOTE: We asserted that the original buffer had flags that semantically matched these! */
		node->mn_flags = MNODE_F_PREAD | MNODE_F_PWRITE;
		node->mn_mman  = mm;
		LIST_INSERT_HEAD(&node->mn_part->mp_copy, node, mn_link);
		LIST_ENTRY_UNBOUND_INIT(&node->mn_writable);
		node->mn_fspath = NULL;
		node->mn_fsname = NULL;
		node->mn_module = NULL;
		node->mn_minaddr += (uintptr_t)mmap_minaddr;
		node->mn_maxaddr += (uintptr_t)mmap_minaddr;

		/* Insert into the mman. */
		mman_mappings_insert(mm, node);

		/* While we're here, try to merge the node with its neighbors.
		 * This  is unlikely to  succeed, but we  might as well try... */
#ifndef __OPTIMIZE_SIZE__
		if unlikely(!unaligned_headbytes || !unaligned_tailbytes)
#endif /* !__OPTIMIZE_SIZE__ */
		{
			node = mnode_merge_with_partlock(node);
		}
		mpart_lock_release(node->mn_part);
	}

	/* Cleanup... */
	mman_lock_release(mm);
	mfile_map_fini(&fmap.mmwu_map);
	decref_unlikely(map_file);
	while (!SLIST_EMPTY(&deleted_nodes)) {
		struct mnode *node;
		node = SLIST_FIRST(&deleted_nodes);
		SLIST_REMOVE_HEAD(&deleted_nodes, _mn_dead);
		mnode_destroy(node);
	}

	/* Trim unused memory from the user-supplied buffer, since we essentially unmapped
	 * part of it (only to  then replace that part  with a MAP_PRIVATE file  mapping). */
	if (lobuf_part == hibuf_part) {
		decref_nokill(lobuf_part);
	} else {
		mpart_trim(lobuf_part);
	}
	mpart_trim(hibuf_part);

	/* Include the size of the read-mapped area in the resulting total. */
	result += map_size;

	/* If we were able to map the entirety of the user-requested area, then also
	 * try  to do one last direct read  for any remaining, unaligned tail bytes. */
	if likely(unaligned_tailbytes)
		result += mpart_read_nommap(self, mmap_endaddr, unaligned_tailbytes, orig_filepos + map_size);
	return result;
done_fini_fmap_unlock_mm:
	mman_lock_release(mm);
done_fini_fmap:
	mfile_map_fini(&fmap.mmwu_map);
done_map_file:
	decref_likely(map_file);
done:
	return result;
}


PUBLIC NONNULL((1, 2)) size_t KCALL
mpart_mmapreadv(struct mpart *__restrict self,
                struct iov_buffer const *__restrict buf,
                size_t buf_offset, size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result    = 0;
	size_t threshold = atomic_read(&mpart_mmapread_threshold);
	size_t cur_offset = 0;
	size_t smallparts_off = 0;
	size_t smallparts_siz = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, buf) {
		size_t temp;
		if (buf_offset) {
			if (buf_offset >= ent.ive_size) {
				cur_offset += ent.ive_size;
				buf_offset -= ent.ive_size;
				continue;
			}
			cur_offset += buf_offset;
			ent.ive_base += buf_offset;
			ent.ive_size -= buf_offset;
			buf_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;

		/* Check if this IOV entry is large enough to qualify for mmap-reading. */
		if (ent.ive_size >= threshold) {
			/* Must read populate small, preceding parts first! */
			if (smallparts_siz != 0) {
				temp = mpart_readv_nommap(self, buf, smallparts_off, smallparts_siz,
				                          filepos - smallparts_siz);
				assert(temp <= smallparts_siz);
				result += temp;
				if (temp < smallparts_siz)
					break;
				smallparts_siz = 0;
			}

			/* Try to read large, continuous buffer locations via mmap-read. */
			temp = mpart_mmapread(self, ent.ive_base, ent.ive_size, filepos);
			assert(temp <= ent.ive_size);
#ifndef __OPTIMIZE_SIZE__
			if (temp)
#endif /* !__OPTIMIZE_SIZE__ */
			{
				result += temp;
				num_bytes -= temp;
				if (!num_bytes)
					break;
				cur_offset += temp;
				ent.ive_base += temp;
				ent.ive_size -= temp;
				filepos += temp;
				if (!ent.ive_size)
					continue;
			}
		}
		if (smallparts_siz == 0)
			smallparts_off = cur_offset; /* Start of a small-parts area. */
		smallparts_siz += ent.ive_size;
		result += ent.ive_size;
		num_bytes -= ent.ive_size;
		if (!num_bytes)
			break;
		filepos += ent.ive_size;
	}

	/* Check if we still need to (try to) read a trailing small-parts chunk. */
	if (smallparts_siz) {
		size_t temp;
		temp = mpart_readv_nommap(self, buf, smallparts_off, smallparts_siz,
		                          filepos - smallparts_siz);
		assert(temp <= smallparts_siz);
		result += temp;
	}

	return result;
}
#endif /* CONFIG_HAVE_AUTO_MMAP */


/* Substitute functions when auto-mmap has been hard-disabled. */
#ifndef CONFIG_HAVE_AUTO_MMAP
DEFINE_PUBLIC_ALIAS(mpart_read_nommap, mpart_read);
DEFINE_PUBLIC_ALIAS(mpart_readv_nommap, mpart_readv);

PUBLIC NONNULL((1)) size_t KCALL
mpart_mmapread(struct mpart *__restrict self,
               NCX void *dst, size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	(void)self;
	(void)dst;
	(void)num_bytes;
	(void)filepos;
	COMPILER_IMPURE();
	return 0;
}

PUBLIC NONNULL((1, 2)) size_t KCALL
mpart_mmapreadv(struct mpart *__restrict self,
                struct iov_buffer const *__restrict buf,
                size_t buf_offset, size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	(void)self;
	(void)buf;
	(void)buf_offset;
	(void)num_bytes;
	(void)filepos;
	COMPILER_IMPURE();
	return 0;
}
#endif /* !CONFIG_HAVE_AUTO_MMAP */


DECL_END

#ifndef __INTELLISENSE__
#define DEFINE_mpart_read
#include "mpart-rw.c.inl"
#ifdef CONFIG_HAVE_AUTO_MMAP
#define DEFINE_mpart_read_nommap
#include "mpart-rw.c.inl"
#endif /* CONFIG_HAVE_AUTO_MMAP */
#define DEFINE_mpart_write
#include "mpart-rw.c.inl"
#define DEFINE_mpart_read_p
#include "mpart-rw.c.inl"
#define DEFINE_mpart_write_p
#include "mpart-rw.c.inl"
#define DEFINE_mpart_readv
#include "mpart-rw.c.inl"
#ifdef CONFIG_HAVE_AUTO_MMAP
#define DEFINE_mpart_readv_nommap
#include "mpart-rw.c.inl"
#endif /* CONFIG_HAVE_AUTO_MMAP */
#define DEFINE_mpart_writev
#include "mpart-rw.c.inl"
#define DEFINE_mpart_readv_p
#include "mpart-rw.c.inl"
#define DEFINE_mpart_writev_p
#include "mpart-rw.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_RW_C */
