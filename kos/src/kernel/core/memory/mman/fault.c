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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_FAULT_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_FAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/module.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Threshold (in bytes) that specifies the upper limit on how many bytes
 * of physical memory  are (technically useless)  allocated in calls  to
 * `mpart_setcore_or_unlock()',  even  when only  parts of  the mem-part
 * actually  need to be allocated as a result of `mfault_or_unlock()' or
 * some other operation that requires parts to loaded into memory.
 *
 * Note that this "overallocation" never poses a problem for available
 * system memory, as such memory  (if truly unused) is always  trimmed
 * in calls to `system_cc()' (as invoked during OOM), so this hint  is
 * only meaningful to  differentiate between  fragmentation of  memory
 * (which  happens more frequently  the lower this  value is), and the
 * allocation of "unused" memory (which happens more often the  higher
 * this value is)
 *
 * NOTES:
 * - This value is ignored for parts with the `MPART_F_NOSPLIT' flag
 * - The default value for this option is "64 * PAGESIZE"
 *
 * The value of this variable is exposed in `/proc/kos/mm/part-autosplit-threshold' */
PUBLIC ATTR_READMOSTLY size_t mfault_autosplit_threshold = 64 * PAGESIZE;


/* Try to pre-fault access to the given addres range, such that `memcpy_nopf()'
 * may succeed when re-attempted.
 * @return: * : The # of leading bytes that this function managed to fault.  For
 *              this purpose, any  non-zero value  means that  `*(byte_t *)addr'
 *              was made accessible for at least one moment before this function
 *              returns. Note though that memory may have already been  unloaded
 *              by the time this function returns (unlikely), so the caller must
 *              still be ready to deal with the possibility that another attempt
 *              at doing nopf access at `*(byte_t *)addr' might immediately fail
 *              again.
 *              Also note that for any memory  that had already been faulted  within
 *              the  given address range,  this function acts as  though it had been
 *              the one to fault that range,  meaning that the return value  doesn't
 *              actually represent how much memory had just been faulted, but rather
 *              how much continuous  memory (starting  at `addr' and  limited by  at
 *              most `num_bytes') was  faulted simultaneously at  some point  before
 *              this function returns.
 * @return: 0 : Nothing could be faulted. This  might be because `addr'  doesn't
 *              point into mapped memory, or the memory that is pointed-to by it
 *              is backed by VIO storage.
 *              The caller should handle this  case by attempting direct  memory
 *              access to the affected region  (i.e. using `memcpy' rather  than
 *              `memcpy_nopf'), and dealing with any potential E_SEGFAULT error.
 * @param: flags: Set of `MMAN_FAULT_F_*' */
PUBLIC BLOCKING size_t FCALL
mman_prefault(NCX void const *addr,
              size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct mfault mf;
	size_t result = 0;
	while (num_bytes) {
		PAGEDIR_PAGEALIGNED void *pagealigned_addr;
		PAGEDIR_PAGEALIGNED size_t pagealigned_size;
		size_t addend;
		pagealigned_addr = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
		pagealigned_size = CEIL_ALIGN(num_bytes + ((uintptr_t)addr - (uintptr_t)pagealigned_addr), PAGESIZE);
		mfault_init(&mf, ADDR_ISKERN(addr) ? &mman_kernel : THIS_MMAN,
		            pagealigned_addr, pagealigned_size, flags);
		TRY {
again:
			mman_lock_acquire(mf.mfl_mman);
			mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings, addr);
			if unlikely(!mf.mfl_node)
				goto unlock_and_done;
			mf.mfl_part = mf.mfl_node->mn_part;
			if unlikely(!mf.mfl_part)
				goto unlock_and_done;

#ifdef LIBVIO_CONFIG_ENABLED
			/* Skip VIO parts. */
			if unlikely(mf.mfl_part->mp_state == MPART_ST_VIO)
				goto unlock_and_done;
#endif /* LIBVIO_CONFIG_ENABLED */

			/* Try to fault the backing mem-parts. */
			if (!mfault_lockpart_or_unlock(&mf))
				goto again;

			/* `mfault_or_unlock()' would normally throw E_FSERROR_READONLY when
			 * trying to write-fault a SHARED mapping of a READONLY file, but we
			 * don't want that here.
			 *
			 * Instead, we want to handle that case by `goto unlock_and_done'!
			 * NOTE: Because `MFILE_F_DELETED' negates the effects of READONLY
			 *       and is WRITE_ONCE, and `MFILE_F_READONLY' can only be set
			 *       while  holding a lock to all parts (which no other thread
			 *       can  do right now since we're currently holding a lock to
			 *       at least one of those parts), we know that the file won't
			 *       randomly become READONLY by the time `mfault_or_unlock()'
			 *       repeats this check! */
			if ((mf.mfl_flags & MMAN_FAULT_F_WRITE) &&
			    (mf.mfl_node->mn_flags & MNODE_F_SHARED) &&
			    (mf.mfl_part->mp_file->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY)) == MFILE_F_READONLY) {
				mpart_lock_release(mf.mfl_part);
				goto unlock_and_done;
			}

			if (!mfault_or_unlock(&mf))
				goto again;

			/* Prepare our page directory of mapping memory. */
			if (!pagedir_prepare(mf.mfl_addr, mf.mfl_size)) {
				mpart_lock_release(mf.mfl_part);
				mman_lock_release(mf.mfl_mman);
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
			}
		} EXCEPT {
			mfault_fini(&mf);
			RETHROW();
		}

		/* (re-)map the faulted address range. */
		{
			pagedir_prot_t prot;
			prot = mpart_mmap_node(mf.mfl_part, mf.mfl_addr,
			                       mf.mfl_size, mf.mfl_offs,
			                       mf.mfl_node);
			pagedir_unprepare(mf.mfl_addr, mf.mfl_size);
			pagedir_sync(mf.mfl_addr, mf.mfl_size);
			mpart_lock_release(mf.mfl_part);
			if ((prot & PAGEDIR_PROT_WRITE) && !LIST_ISBOUND(mf.mfl_node, mn_writable))
				LIST_INSERT_HEAD(&mf.mfl_mman->mm_writable, mf.mfl_node, mn_writable);
		}
		mman_lock_release(mf.mfl_mman);

		addend = (size_t)(((byte_t *)pagealigned_addr + mf.mfl_size) - (byte_t *)addr);
		/*mfault_fini(&mf);*/ /* Don't finalize here (s.a. the documentation of `mfault_or_unlock()') */
		/* Account for how much was actually faulted. */
		assert(addend != 0);
		if (addend >= num_bytes) {
			result += num_bytes; /* Limit by the max request. */
			break;
		}
		/* Continue faulting more memory... */
		result += addend;
		addr = (byte_t *)addr + addend;
		num_bytes -= addend;
	}
done:
	return result;
unlock_and_done:
	mman_lock_release(mf.mfl_mman);
	mfault_fini(&mf);
	goto done;
}



/* Enumerate segments from `buffer', and prefault up to `num_bytes' of pointed-to
 * memory,  after skipping the first `offset' bytes.  The return value is the sum
 * of successfully faulted  segments, however  faulting also stops  on the  first
 * segment that cannot be fully faulted.
 * @param: flags: Set of `MMAN_FAULT_F_*' */
PUBLIC BLOCKING NONNULL((1)) size_t FCALL
mman_prefaultv(struct iov_buffer const *__restrict buffer,
               size_t offset, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct iov_entry ent;
	size_t temp, result = 0;
	IOV_BUFFER_FOREACH(ent, buffer) {
		if (offset != 0) {
			if (offset >= ent.ive_size) {
				offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += offset;
			ent.ive_size -= offset;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		/* Prefault this part. */
		temp = mman_prefault(ent.ive_base, ent.ive_size, flags);
		result += temp;
		/* Stop upon the first partial error (iow: once reaching
		 * the   first   byte   that  could   not   be  faulted) */
		if (temp < ent.ive_size)
			break;
		if (ent.ive_size >= num_bytes)
			break;
		num_bytes -= ent.ive_size;
	}
	return result;
}



/* Force  all  bytes within  the given  address range  to be  faulted for  either reading
 * or writing. If any page within the  specified range isn't mapped, throw an  E_SEGFAULT
 * exception. Otherwise, ensure that copy-on-write is performed when `MMAN_FAULT_F_WRITE'
 * is  set, and that  irregardless of `MMAN_FAULT_F_WRITE',  physical memory is allocated
 * for any mapping that can be made to be backed by RAM.
 *
 * NOTES:
 *  - When `MMAN_FAULT_F_WRITE' is set, this function also verifies that the mem-nodes
 *    associated with the given address range all have the `MNODE_F_PWRITE' flag  set.
 *  - Any VIO mappings within the specified range are simply ignored (and will not
 *    count towards the  returned value), unless  `MMAN_FAULT_F_NOVIO' is set,  in
 *    which case such mappings will cause an exception to be thrown.
 *  - This function will automatically wide the given range to encompass whole pages.
 *  - This function will also update the page directory mappings for any  mem-parts
 *    that get faulted during its  invocation, meaning that use of  `memcpy_nopf()'
 *    within the indicated address range (whilst  still checking it for errors  for
 *    the even of the mapping changing, or the mapping being a VIO mapping) becomes
 *    possible immediately, without having to  force any sort of additional  memory
 *    access  (note though that this only applies  to the page directory of `self',
 *    though also note that if some mem-part within the range was already  faulted,
 *    its  page directory mapping in `self' will still be updated if need be, as it
 *    may have been faulted as a lazy memory mapping).
 * @param: E_FSERROR_READONLY: Attempted to write-fault a SHARED mapping of a READONLY file. */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mman_forcefault(struct mman *__restrict self,
                NCX void const *addr,
                size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_FSERROR_READONLY, ...) {
	struct mfault mf;
	while (num_bytes) {
		PAGEDIR_PAGEALIGNED void *pagealigned_addr;
		PAGEDIR_PAGEALIGNED size_t pagealigned_size;
		size_t addend;
again_mfault_init:
		pagealigned_addr = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
		pagealigned_size = CEIL_ALIGN(num_bytes + ((uintptr_t)addr - (uintptr_t)pagealigned_addr), PAGESIZE);
		mfault_init(&mf, self, pagealigned_addr, pagealigned_size, flags);
		TRY {
again:
			mman_lock_acquire(mf.mfl_mman);

			/* Load the associated node. */
			mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings, addr);
			if unlikely(!mf.mfl_node)
				goto err_unmapped;

			/* Load the associated part. */
			mf.mfl_part = mf.mfl_node->mn_part;
			if unlikely(!mf.mfl_part)
				goto err_unmapped;

			/* Verify write-access if requested. */
			if unlikely((flags & MMAN_FAULT_F_WRITE) &&
			            !(mf.mfl_node->mn_flags & MNODE_F_PWRITE)) {
				mman_lock_release(mf.mfl_mman);
				THROW(E_SEGFAULT_READONLY, addr,
				      E_SEGFAULT_CONTEXT_WRITING);
			}

#ifdef LIBVIO_CONFIG_ENABLED
			/* Skip VIO parts, or throw an exception. */
			if unlikely(mf.mfl_part->mp_state == MPART_ST_VIO) {
				void *old_end_addr, *new_end_addr;
				mman_lock_release(mf.mfl_mman);
				mfault_fini(&mf);
				if (flags & MMAN_FAULT_F_NOVIO)
					goto err_unmapped_now;
				old_end_addr = (byte_t *)addr + num_bytes;
				new_end_addr = mnode_getendaddr(mf.mfl_node);
				if (new_end_addr >= old_end_addr)
					goto done;
				num_bytes = (size_t)((byte_t *)old_end_addr - (byte_t *)new_end_addr);
				addr      = new_end_addr;
				goto again_mfault_init;
			}
#endif /* LIBVIO_CONFIG_ENABLED */

			/* Try to fault the backing mem-parts. */
			if (!mfault_lockpart_or_unlock(&mf))
				goto again;
			if (!mfault_or_unlock(&mf))
				goto again;

			/* Prepare our page directory of mapping memory. */
			if (!pagedir_prepare(mf.mfl_addr, mf.mfl_size)) {
				mpart_lock_release(mf.mfl_part);
				mman_lock_release(mf.mfl_mman);
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
			}
		} EXCEPT {
			mfault_fini(&mf);
			RETHROW();
		}

		/* (re-)map the faulted address range. */
		{
			pagedir_prot_t prot;
			prot = mpart_mmap_node(mf.mfl_part, mf.mfl_addr,
			                       mf.mfl_size, mf.mfl_offs,
			                       mf.mfl_node);
			pagedir_unprepare(mf.mfl_addr, mf.mfl_size);
			pagedir_sync(mf.mfl_addr, mf.mfl_size);
			mpart_lock_release(mf.mfl_part);
			if ((prot & PAGEDIR_PROT_WRITE) && !LIST_ISBOUND(mf.mfl_node, mn_writable))
				LIST_INSERT_HEAD(&mf.mfl_mman->mm_writable, mf.mfl_node, mn_writable);
		}
		mman_lock_release(mf.mfl_mman);

		addend = (size_t)(((byte_t *)pagealigned_addr + mf.mfl_size) - (byte_t *)addr);
		/*mfault_fini(&mf);*/ /* Don't finalize here (s.a. the documentation of `mfault_or_unlock()') */
		if (addend >= num_bytes)
			break;
		/* Continue force-faulting more memory... */
		addr = (byte_t *)addr + addend;
		num_bytes -= addend;
	}
done:
	return;
/*
unlock_and_done:
	mman_lock_release(mf.mfl_mman);
	mfault_fini(&mf);
	goto done;*/
err_unmapped:
	mman_lock_release(mf.mfl_mman);
	mfault_fini(&mf);
err_unmapped_now:
	THROW(E_SEGFAULT_UNMAPPED, addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      ((flags & MMAN_FAULT_F_WRITE) ? E_SEGFAULT_CONTEXT_WRITING : 0));
}



/* Same as `mman_forcefault()', but fault all memory pointed-to by the given buffer. */
PUBLIC BLOCKING NONNULL((1, 2)) void FCALL
mman_forcefaultv(struct mman *__restrict self,
                 struct iov_buffer const *__restrict buffer,
                 size_t offset, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, buffer) {
		if (offset != 0) {
			if (offset >= ent.ive_size) {
				offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += offset;
			ent.ive_size -= offset;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		/* Force-fault this part. */
		mman_forcefault(self, ent.ive_base, ent.ive_size, flags);
		if (ent.ive_size >= num_bytes)
			break;
		num_bytes -= ent.ive_size;
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unlock_mman_cb)(struct unlockinfo *__restrict self) {
	struct mfault *mf;
	mf = container_of(self, struct mfault, mfl_unlck);
	mman_lock_release(mf->mfl_mman);
}



/************************************************************************/
/* Functions from "mpart-lock.c"                                        */
INTDEF NONNULL((1, 3)) bool FCALL
unsharecow_makecopy_or_unlock(struct mpart *__restrict self,
                              struct unlockinfo *unlock,
                              struct mpart_unsharecow_data *__restrict data);
INTDEF NONNULL((1, 3)) bool FCALL
unsharecow_makeblkext_or_unlock(struct mpart *__restrict self,
                                struct unlockinfo *unlock,
                                struct mpart_unsharecow_data *__restrict data,
                                PAGEDIR_PAGEALIGNED size_t num_bytes);
INTDEF NONNULL((1, 3)) bool FCALL
unsharecow_makememdat_or_unlock(struct mpart *__restrict self,
                                struct unlockinfo *unlock,
                                struct mpart_unsharecow_data *__restrict data,
                                PAGEDIR_PAGEALIGNED size_t num_bytes);
INTDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_copyram)(struct mpart *__restrict dst,
                             struct mpart *__restrict src,
                             PAGEDIR_PAGEALIGNED mpart_reladdr_t src_offset,
                             size_t num_pages);
/************************************************************************/



/* Allocate `self->mfl_ucdat.ucd_copy' */
PRIVATE NONNULL((1)) bool FCALL
mfault_pcopy_makecopy_or_unlock(struct mfault *__restrict self) {
	return unsharecow_makecopy_or_unlock(self->mfl_part,
	                                     &self->mfl_unlck,
	                                     &self->mfl_ucdat);
}

/* Allocate `self->mfl_ucdat.ucd_ucmem.scd_bitset' if necessary */
PRIVATE NONNULL((1)) bool FCALL
mfault_pcopy_makeblkext_or_unlock(struct mfault *__restrict self) {
	return unsharecow_makeblkext_or_unlock(self->mfl_part,
	                                       &self->mfl_unlck,
	                                       &self->mfl_ucdat,
	                                       self->mfl_size);
}

/* Allocate `self->mfl_ucdat.ucd_ucmem.ucd_copy_state' (and `ucd_copy_mem' / `ucd_copy_mem_sc') */
PRIVATE NONNULL((1)) bool FCALL
mfault_pcopy_makememdat_or_unlock(struct mfault *__restrict self) {
	return unsharecow_makememdat_or_unlock(self->mfl_part,
	                                       &self->mfl_unlck,
	                                       &self->mfl_ucdat,
	                                       self->mfl_size);
}

#define unlockall(self)                     \
	(_mpart_lock_release((self)->mfl_part), \
	 mman_lock_release((self)->mfl_mman),   \
	 mpart_lockops_reap((self)->mfl_part))

/* Allocate `self->mfl_pcopy[0]' (and possibly `self->mfl_pcopy[1]') if necessary */
PRIVATE NONNULL((1)) bool FCALL
mfault_pcopy_makenodes_or_unlock(struct mfault *__restrict self) {
	size_t reqcnt = 0;
	struct mnode *node;
	void *endaddr;
	/* Figure out how many additional nodes we need. */
	node    = self->mfl_node;
	endaddr = (byte_t *)self->mfl_addr + self->mfl_size;
	assert((uintptr_t)self->mfl_addr >= (uintptr_t)mnode_getaddr(node));
	assert((uintptr_t)endaddr <= (uintptr_t)mnode_getendaddr(node));
	if ((uintptr_t)self->mfl_addr > (uintptr_t)mnode_getaddr(node))
		++reqcnt;
	if ((uintptr_t)endaddr < (uintptr_t)mnode_getendaddr(node))
		++reqcnt;
	if (reqcnt == 0)
		return true; /* Simple case: Don't need any additional nodes! */
	if likely(!self->mfl_pcopy[0]) {
		self->mfl_pcopy[1] = NULL;
		/* Try to allocate a missing node. */
		node = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
		                                  GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if unlikely(!node) {
			unlockall(self);
			node = (struct mnode *)kmalloc(sizeof(struct mnode),
			                               GFP_LOCKED | GFP_PREFLT);
			self->mfl_pcopy[0] = node;
			if (reqcnt == 1)
				return false; /* Got everything we need! */
			/* Must also allocate the second node. */
			node = (struct mnode *)kmalloc(sizeof(struct mnode),
			                               GFP_LOCKED | GFP_PREFLT);
			self->mfl_pcopy[1] = node;
			return false;
		}
		self->mfl_pcopy[0] = node;
	}
	if (reqcnt == 1)
		return true; /* Got everything we need! */
	if likely(!self->mfl_pcopy[1]) {
		/* Must also allocate the second node. */
		node = (struct mnode *)kmalloc_nx(sizeof(struct mnode),
		                                  GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if unlikely(!node) {
			unlockall(self);
			node = (struct mnode *)kmalloc(sizeof(struct mnode),
			                               GFP_LOCKED | GFP_PREFLT);
			self->mfl_pcopy[1] = node;
			assert(self->mfl_pcopy[0] != NULL);
			return false;
		}
		self->mfl_pcopy[1] = node;
	}
	return true;
}


PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL bitmovedown)(mpart_blkst_word_t *dst_bitset, size_t dst_index,
                           mpart_blkst_word_t const *src_bitset, size_t src_index,
                           size_t num_bits) {
#define BITSET_INDEX(index) ((index) / BITSOF(mpart_blkst_word_t))
#define BITSET_SHIFT(index) ((index) % BITSOF(mpart_blkst_word_t))
#define GETBIT(index)       ((src_bitset[BITSET_INDEX(index)] >> BITSET_SHIFT(index)) & 1)
#define SETBIT_OFF(index)   ((dst_bitset[BITSET_INDEX(index)] &= ~((mpart_blkst_word_t)1 << BITSET_SHIFT(index))))
#define SETBIT_ON(index)    ((dst_bitset[BITSET_INDEX(index)] |= ((mpart_blkst_word_t)1 << BITSET_SHIFT(index))))
	while (num_bits) {
		--num_bits;
		if (GETBIT(src_index)) {
			SETBIT_ON(dst_index);
		} else {
			SETBIT_OFF(dst_index);
		}
		++dst_index;
		++src_index;
	}
#undef SETBIT_ON
#undef SETBIT_OFF
#undef GETBIT
#undef BITSET_SHIFT
#undef BITSET_INDEX
}




/* Acquire a lock to `self->mfl_part', or release a lock to `self->mfl_mman'
 * Locking logic:
 *   - return == true:   mpart_lock_acquire(self->mfl_part);
 *   - return == false:  _mman_lock_release(self->mfl_mman);
 *   - EXCEPT:           mman_lock_release(self->mfl_mman); */
PUBLIC NONNULL((1)) void FCALL
_mfault_unlock_and_waitfor_part(struct mfault *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct mpart *part = self->mfl_part;
	incref(part);
	mman_lock_release(self->mfl_mman);
	FINALLY_DECREF_UNLIKELY(part);
	/* Wait for the part's lock to become available. */
	mpart_lock_waitfor(part);
}



/* (Try to) acquire locks, and load/split/unshare/... backing memory,
 * as  well as mem-parts and mem-nodes in order to prepare everything
 * needed in order to map a given sub-address-range of a given mpart,
 * as accessed through a given mnode into memory.
 * The caller must already be holding a lock to `self->mfl_part'!
 *
 * Usage:
 * >> void pf_handler(void *addr, bool is_write) {
 * >>     struct mfault mf;
 * >>     // Missing: Handling for `MNODE_F_MHINT'
 * >>     // Missing: Call to `task_pushconnections()'
 * >>     mfault_init(&mf, ADDR_ISKERN(addr) ? &mman_kernel : THIS_MMAN,
 * >>                 FLOOR_ALIGN(addr, PAGESIZE), PAGESIZE,
 * >>                 is_write ? MMAN_FAULT_F_WRITE : 0);
 * >>     TRY {
 * >> again:
 * >>         mman_lock_acquire(mf.mfl_mman);
 * >>         mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings, mf.mfl_addr);
 * >>         mf.mfl_part = mf.mfl_node->mn_part;
 * >>         // Missing: NULL- and safety-checks; VIO support
 * >>         // Missing: Is-access-even-allowed-checks
 * >>         if (!mfault_lockpart_or_unlock(&mf))
 * >>             goto again;
 * >>         if (!mfault_or_unlock(&mf))
 * >>             goto again;
 * >>     } EXCEPT {
 * >>         mfault_fini(&mf);
 * >>         RETHROW();
 * >>     }
 * >>     if (!pagedir_prepare(mf.mfl_addr, mf.mfl_size)) { ... }
 * >>     perm = mpart_mmap_node(mf.mfl_part, mf.mfl_addr,
 * >>                            mf.mfl_size, mf.mfl_offs,
 * >>                            mf.mfl_node);
 * >>     pagedir_unprepare(mf.mfl_addr, mf.mfl_size);
 * >>     pagedir_sync(mf.mfl_addr, mf.mfl_size);
 * >>     mpart_lock_release(mf.mfl_part);
 * >>     if ((perm & PAGEDIR_PROT_WRITE) && !LIST_ISBOUND(mf.mfl_node, mn_writable))
 * >>         LIST_INSERT_HEAD(&mf.mfl_mman->mm_writable, mf.mfl_node, mn_writable);
 * >>     mman_lock_release(mf.mfl_mman);
 * >>     // NOTE: Don't call `mfault_fini(&mf)' here!
 * >>     //       Internal data of `mf' is left in an undefined state
 * >>     //       following a successful call to `mfault_or_unlock()'!
 * >> }
 *
 * Locking logic:
 *   - return == true:   undefined(out(INTERNAL_DATA(self)))
 *   - return == false:  mpart_lock_releases(self->mfl_part);
 *                       _mman_lock_release(self->mfl_mman);
 *   - EXCEPT:           mpart_lock_releases(self->mfl_part);
 *                       mman_lock_release(self->mfl_mman);
 *
 * @param: self:   mem-lock control descriptor.
 * @return: true:  Successfully faulted memory.
 * @return: false: The lock to `self->mfl_mman' was lost, but the  goal
 *                 of faulting memory has gotten closer, and the caller
 *                 should re-attempt the call after re-acquiring locks.
 * @return: false: The accessed address range lies outside the bounds
 *                 of the associated mem-part.
 *                 Resolve  this  issue  by simply  trying  again (this
 *                 inconsistency can result from someone else splitting
 *                 the associated mem-part)
 * @throw: E_FSERROR_READONLY:
 *         Attempted to fault write for `MNODE_F_SHARED' mapping of `MFILE_F_READONLY'-file:
 *         >> (self->mfl_flags & MMAN_FAULT_F_WRITE) &&
 *         >> (self->mfl_node->mn_flags & MNODE_F_SHARED) &&
 *         >> ((self->mfl_part->mp_file->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY)) == MFILE_F_READONLY)
 */
PUBLIC BLOCKING NONNULL((1)) bool FCALL
mfault_or_unlock(struct mfault *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...) {
	struct mnode *node;
	struct mpart *part;
	mpart_reladdr_t acc_offs;
	size_t acc_size, max_size;
	size_t noderel_offset;

	/* Validate input arguments. */
	assert(self->mfl_node);
	assert(self->mfl_part);
	assert(self->mfl_mman == self->mfl_node->mn_mman);
	assert(self->mfl_part == self->mfl_node->mn_part);
	assert(mman_lock_acquired(self->mfl_mman));
	assert(mpart_lock_acquired(self->mfl_part));
	assert(IS_ALIGNED((uintptr_t)self->mfl_addr, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)self->mfl_size, PAGESIZE));
	assert(self->mfl_size != 0);
	assert(!wasdestroyed(self->mfl_part));
	assert(!wasdestroyed(self->mfl_mman));
	node = self->mfl_node;
	part = self->mfl_part;
	mpart_assert_integrity(part);

	/* Set-up our extended unlock controller. */
	self->mfl_unlck.ui_unlock = &unlock_mman_cb;

	/* Calculate the part-relative accessed address range. */
	noderel_offset = (size_t)((uintptr_t)self->mfl_addr -
	                          (uintptr_t)mnode_getminaddr(node));
	acc_offs       = noderel_offset + node->mn_partoff;
	acc_size       = self->mfl_size;
	self->mfl_offs = acc_offs;
	/* NOTE: No  need to check that `acc_offs' is still in-bounds of `part'!
	 *       Our  caller originally acquiring a lock to their mman has since
	 *       guarantied that any mem-part mapped by any of its mem-nodes (of
	 *       which the one we're supposed to fault is one of) can't have its
	 *       min/max address be altered until said mman-lock is released! */

	/* Limit the accessed address range so that it ends with the containing node. */
	max_size = (size_t)((uintptr_t)mnode_getendaddr(node) -
	                    (uintptr_t)self->mfl_addr);
	if (acc_size > max_size) {
		acc_size       = max_size;
		self->mfl_size = acc_size;
	}

	/* Assert that the node doesn't exceed bounds set by the mem-part. */
	assert(IS_ALIGNED(acc_offs, PAGESIZE));
	assert(IS_ALIGNED(acc_size, PAGESIZE));
	assert(acc_offs + acc_size > acc_offs);
	assert(acc_offs + acc_size <= mpart_getsize(part));

	/* If the part hasn't been loaded into the core, and the area  we're
	 * going to access isn't very large, then try to split the part into
	 * a couple of  smaller parts, so  that the range  that needs to  be
	 * loaded into the core (read: allocated) becomes smaller. */
	if (!mpart_maybesplit_or_unlock(part, &self->mfl_unlck, acc_offs, acc_size))
		goto nope;

	/* Whatever happens, we always need the part to be re-locked into the core. */
	if (!mpart_setcore_or_unlock(part, &self->mfl_unlck, &self->mfl_scdat))
		goto nope;

	TRY {

		/* Simple case: When reading, only need to lock+load the accessed address range. */
		if (!(self->mfl_flags & MMAN_FAULT_F_WRITE)) {
			if (!mpart_load_or_unlock(part, &self->mfl_unlck, acc_offs, acc_size))
				goto nope_reinit_scmem;

			/* Make  sure  that   unshare-cow  data   was  never   allocated.
			 * Because the  `mfl_flags'  field  is [const],  we  should  have
			 * never reached any of the paths that would have allocated this! */
			assert(self->mfl_ucdat.ucd_copy == NULL);
			assert(self->mfl_ucdat.ucd_ucmem.scd_bitset == NULL);
			assert(self->mfl_ucdat.ucd_ucmem.scd_copy_state == MPART_ST_VOID);
			assert(self->mfl_pcopy[0] == NULL);
			goto done;
		}

		/* Deal with writes to shared memory mappings. */
		if (node->mn_flags & MNODE_F_SHARED) {

			/* Ensure that the backing file isn't marked as READONLY
			 *
			 * This can happen if the memory mapping was created before the READONLY
			 * flag  was set (but note that setting  the flag causes denywrite to be
			 * called for all parts, meaning that we may very well have gotten  here
			 * because somebody revoked write access)
			 *
			 * This check is synonymous to the IS_WRITESHARE_MAPPING_OF_READONLY_FILE
			 * check done when trying to create  file mappings, only that this  check
			 * is necessary to deal with the case  where a thread already has a  pre-
			 * existing MAP_SHARED+PROT_WRITE mapping of a file that has later become
			 * READONLY, at which point pagedir-level  write access was revoked,  but
			 * the mapping itself wasn't deleted. */
			if unlikely((part->mp_file->mf_flags & (MFILE_F_DELETED |
			                                        MFILE_F_READONLY)) ==
			            MFILE_F_READONLY) {
				mpart_lock_release(part);
				unlockinfo_unlock(&self->mfl_unlck);
				THROW(E_FSERROR_READONLY);
			}

			if (!mpart_msalign_makeanon_or_unlock(part, &self->mfl_unlck, acc_offs, acc_size))
				goto nope;
			if (LIST_EMPTY(&part->mp_copy)) {
				if (!mpart_load_or_unlock(part, &self->mfl_unlck, acc_offs, acc_size))
					goto nope_reinit_scmem;
				/* Free data which may have been allocated for a previous unshare-cow attempt. */
				mpart_unsharecow_data_fini(&self->mfl_ucdat);
			} else {
				/* Load the part into the core, and unshare copy-on-write if necessary. */
				if (!mpart_unsharecow_or_unlock(part, &self->mfl_unlck, &self->mfl_ucdat, acc_offs, acc_size))
					goto nope;
			}

			/* Free data which may have been allocated for a previous pcopy attempt. */
			if unlikely(self->mfl_pcopy[0]) {
				kfree(self->mfl_pcopy[0]);
				kfree(self->mfl_pcopy[1]);
			}
done_mark_changed:
			/* Mark the accessed address range as changed */
			mpart_changed(part, acc_offs, acc_size);
			goto done;
		}

		/* Make sure that the accessed part is loaded. */
		if (!mpart_load_or_unlock(part, &self->mfl_unlck, acc_offs, acc_size))
			goto nope_reinit_scmem;

		/* Deal with writes to copy-on-write mappings that aren't reachable from the
		 * outside word. This is the  normal case for mmap(MAN_ANON) memory,  unless
		 * the associated process has called fork(2), at which point there would  be
		 * more than 1 mapping for the mem-part, and this part would fail! */
		if (mpart_iscopywritable(part, acc_offs, acc_size, node)) {
			/* Backing file is anonymous, there are no SHARED-mappings,
			 * and  we're the only  copy-on-write mapping in existence.
			 *
			 * -> We essentially _own_ this mem-part. */

			/* Free data which may have been allocated for a previous unshare-cow attempt. */
			mpart_unsharecow_data_fini(&self->mfl_ucdat);

			/* Free data which may have been allocated for a previous pcopy attempt. */
			if unlikely(self->mfl_pcopy[0]) {
				kfree(self->mfl_pcopy[0]);
				kfree(self->mfl_pcopy[1]);
			}
			goto done_mark_changed;
		}

		/* Copy-on-write mapping that is being shared with someone else.
		 *
		 * In this case, we must must essentially unshare ourselves from
		 * the mem-part's copy-on-write list. For this purpose, we must:
		 *
		 *   - Split  the mem-node  accessed by  the caller  such that it
		 *     represents the smallest possible address range which still
		 *     contains the accessed address range.
		 *   - The new node that now  contains only the accessed  address
		 *     range must now have it's pointed-to part altered such that
		 *     it points to a new, private copy of the original part.
		 *
		 * Further optimizations are performed to prevent this mechanism
		 * from creating _way_ too  many small node+anon-part pairs,  by
		 * simply trying to merge nodes after they've been created.
		 *
		 * This optimization is performed by a trailing call to `mnode_merge()' */

		if unlikely(node->mn_flags & MNODE_F_NOSPLIT) {
			/* Must unshare the mem-node as  a whole (that is: fault  the
			 * entirety of the address range that is described by `node')
			 *
			 * Note that we don't have to check the part for `MPART_F_NOSPLIT',
			 * since we don't actually have  to split the part anywhere  below! */
			if (self->mfl_addr != mnode_getaddr(node) ||
			    self->mfl_size != mnode_getsize(node)) {
				bool result;
				PAGEDIR_PAGEALIGNED void *orig_addr;
				PAGEDIR_PAGEALIGNED size_t orig_size;
				assert((uintptr_t)self->mfl_addr >=
				       (uintptr_t)mnode_getaddr(node));
				assert((uintptr_t)self->mfl_addr + self->mfl_size <=
				       (uintptr_t)mnode_getendaddr(node));
				/* Because this is a rather rare scenario, implement support via
				 * a recursive call, so we don't have to add special handling in
				 * the regular code path down below. */
				orig_addr      = self->mfl_addr;
				orig_size      = self->mfl_size;
				self->mfl_addr = mnode_getaddr(node);
				self->mfl_size = mnode_getsize(node);
				result         = mfault_or_unlock(self);
				/* NOTE: Technically, `mfl_offs' only need to be adjusted on success. */
				self->mfl_offs += (size_t)((byte_t *)self->mfl_addr - (byte_t *)orig_addr);
				self->mfl_addr = orig_addr;
				self->mfl_size = orig_size;
				return result;
			}
		}

		/* Allocate everything we need to create the anon copy of the accessed range. */
		if (!mfault_pcopy_makecopy_or_unlock(self))
			goto nope_reinit_scmem;
		if (!mfault_pcopy_makeblkext_or_unlock(self))
			goto nope_reinit_scmem;
		if (!mfault_pcopy_makememdat_or_unlock(self))
			goto nope_reinit_scmem;
		if (!mfault_pcopy_makenodes_or_unlock(self))
			goto nope_reinit_scmem;

		/* ======== Point of no return */

		/* Split the given `node' within the caller's memory manager,  and
		 * make it so that `node' fits the accessed address range exactly. */
		{
			void *endaddr;
			/* Figure out how many additional nodes we need. */
			node    = self->mfl_node;
			endaddr = (byte_t *)self->mfl_addr + self->mfl_size;
			assert((uintptr_t)self->mfl_addr >= (uintptr_t)mnode_getaddr(node));
			assert((uintptr_t)endaddr <= (uintptr_t)mnode_getendaddr(node));

			if ((uintptr_t)self->mfl_addr > (uintptr_t)mnode_getaddr(node)) {
				struct mnode *lonode;
				mman_mappings_removenode(self->mfl_mman, node);
				lonode = self->mfl_pcopy[0];
				assert(lonode);

				/* Initialize the node below the accessed range. */
				lonode->mn_flags   = node->mn_flags;
				lonode->mn_minaddr = node->mn_minaddr;
				lonode->mn_maxaddr = (byte_t *)self->mfl_addr - 1;
				lonode->mn_mman    = self->mfl_mman;
				lonode->mn_part    = incref(part);
				lonode->mn_partoff = node->mn_partoff;
				assert(!(lonode->mn_flags & MNODE_F_SHARED));
				LIST_INSERT_HEAD(&part->mp_copy, lonode, mn_link);
				lonode->mn_fspath  = xincref(node->mn_fspath);
				lonode->mn_fsname  = xincref(node->mn_fsname);
				lonode->mn_module  = node->mn_module;
				if (lonode->mn_module)
					module_inc_nodecount(lonode->mn_module);

				node->mn_minaddr = (byte_t *)self->mfl_addr;
				node->mn_partoff += mnode_getsize(lonode); /* Potentially needed for `hinode->mn_partoff' */

				/* Consume the first p-copy node. */
				self->mfl_pcopy[0] = self->mfl_pcopy[1];
				self->mfl_pcopy[1] = NULL;

				/* Re-insert both nodes into the mman's mapping tree. */
				mman_mappings_insert(self->mfl_mman, lonode);
				mman_mappings_insert(self->mfl_mman, node);

				/* If the original node had been marked as containing writable
				 * mappings, then  we must  also mark  the new  node as  such! */
				LIST_ENTRY_UNBOUND_INIT(&lonode->mn_writable);
				if (LIST_ISBOUND(node, mn_writable))
					LIST_INSERT_HEAD(&self->mfl_mman->mm_writable, lonode, mn_writable);
				mnode_assert_integrity(lonode);
				mnode_assert_integrity(node);
			}

			if ((uintptr_t)endaddr < (uintptr_t)mnode_getendaddr(node)) {
				struct mnode *hinode;
				mman_mappings_removenode(self->mfl_mman, node);
				hinode = self->mfl_pcopy[0];
				assert(hinode);

				/* Initialize the node above the accessed range. */
				hinode->mn_flags   = node->mn_flags;
				hinode->mn_minaddr = (byte_t *)endaddr;
				hinode->mn_maxaddr = node->mn_maxaddr;
				hinode->mn_mman    = self->mfl_mman;
				hinode->mn_part    = incref(part);
				hinode->mn_partoff = node->mn_partoff + ((uintptr_t)endaddr - (uintptr_t)node->mn_minaddr);
				assert(!(hinode->mn_flags & MNODE_F_SHARED));
				LIST_INSERT_HEAD(&part->mp_copy, hinode, mn_link);
				hinode->mn_fspath  = xincref(node->mn_fspath);
				hinode->mn_fsname  = xincref(node->mn_fsname);
				hinode->mn_module  = node->mn_module;
				if (hinode->mn_module)
					module_inc_nodecount(hinode->mn_module);
				node->mn_maxaddr = (byte_t *)endaddr - 1;

				/* Consume the first p-copy node. */
				self->mfl_pcopy[0] = self->mfl_pcopy[1];
				self->mfl_pcopy[1] = NULL;

				/* Re-insert both nodes into the mman's mapping tree. */
				mman_mappings_insert(self->mfl_mman, node);
				mman_mappings_insert(self->mfl_mman, hinode);

				/* If the original node had been marked as containing writable
				 * mappings, then  we must  also mark  the new  node as  such! */
				LIST_ENTRY_UNBOUND_INIT(&hinode->mn_writable);
				if (LIST_ISBOUND(node, mn_writable))
					LIST_INSERT_HEAD(&self->mfl_mman->mm_writable, hinode, mn_writable);
				mnode_assert_integrity(node);
				mnode_assert_integrity(hinode);
			}

			/* Free allocated, but unused data. */
			if unlikely(self->mfl_pcopy[0] != NULL) {
				kfree(self->mfl_pcopy[1]);
				kfree(self->mfl_pcopy[0]);
			}
			DBG_memset(&self->mfl_pcopy, 0xcc, sizeof(self->mfl_pcopy));
		} /* Scope... */


		/* Construct the new mem-part. */
		{
			struct mpart *copy;
			size_t block_offset;
			size_t block_count;
			copy = self->mfl_ucdat.ucd_copy;
			assert(copy);
			copy->mp_refcnt = 1; /* This reference will be inherited by the node we create below */
			copy->mp_flags  = MPART_F_LOCKBIT;
			copy->mp_xflags = MPART_XF_NORMAL;
#if MNODE_F_MLOCK == MPART_F_MLOCK
			copy->mp_flags |= node->mn_flags & MNODE_F_MLOCK;
#else /* MNODE_F_MLOCK == MPART_F_MLOCK */
			if (node->mn_flags & MNODE_F_MLOCK)
				copy->mp_flags |= MPART_F_MLOCK;
#endif /* MNODE_F_MLOCK != MPART_F_MLOCK */
			copy->mp_file = incref(&mfile_anon[part->mp_file->mf_blockshift]);
			LIST_INIT(&copy->mp_share);
			SLIST_INIT(&copy->mp_lockops);
			DBG_memset(&copy->mp_changed, 0xcc, sizeof(copy->mp_changed));
			copy->mp_minaddr = part->mp_minaddr + acc_offs;
			copy->mp_maxaddr = copy->mp_minaddr + acc_size - 1;
			_mpart_init_asanon(copy);

			/* We need to copy the block-status bitset. */
			block_offset = acc_offs >> copy->mp_file->mf_blockshift;
			block_count  = acc_size >> copy->mp_file->mf_blockshift;
			if (block_count <= MPART_BLKST_BLOCKS_PER_WORD) {
				/* A single word is enough! */
				mpart_blkst_word_t word;
				if (part->mp_flags & MPART_F_BLKST_INL) {
					word = part->mp_blkst_inl >> (block_offset * MPART_BLOCK_STBITS);
				} else if (part->mp_blkst_ptr == NULL) {
					word = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
				} else {
					word = 0;
					bitmovedown(&word, 0, part->mp_blkst_ptr,
					            block_offset * MPART_BLOCK_STBITS,
					            block_count * MPART_BLOCK_STBITS);
				}
				copy->mp_blkst_inl = word;
				copy->mp_flags |= MPART_F_BLKST_INL;
pcopy_free_unused_block_status:
				if unlikely(self->mfl_ucdat.ucd_ucmem.scd_bitset)
					kfree(self->mfl_ucdat.ucd_ucmem.scd_bitset);
				DBG_memset(&self->mfl_ucdat.ucd_ucmem.scd_bitset, 0xcc,
				           sizeof(self->mfl_ucdat.ucd_ucmem.scd_bitset));
			} else if (part->mp_blkst_ptr == NULL) {
				copy->mp_blkst_ptr = NULL;
				goto pcopy_free_unused_block_status;
			} else {
				/* This is the case where we need the dynamically allocated block-status bitset. */
				assert(self->mfl_ucdat.ucd_ucmem.scd_bitset != NULL);
				assert((kmalloc_usable_size(self->mfl_ucdat.ucd_ucmem.scd_bitset) *
				        MPART_BLKST_BLOCKS_PER_WORD) >= block_count);
				assert(block_count <= mpart_getblockcount(part, part->mp_file));
				/* Copy over block-status bitset data. */
				copy->mp_blkst_ptr = self->mfl_ucdat.ucd_ucmem.scd_bitset;
				DBG_memset(&self->mfl_ucdat.ucd_ucmem.scd_bitset, 0xcc,
				           sizeof(self->mfl_ucdat.ucd_ucmem.scd_bitset));
				bitmovedown(copy->mp_blkst_ptr, 0, part->mp_blkst_ptr,
				            block_offset * MPART_BLOCK_STBITS,
				            block_count * MPART_BLOCK_STBITS);
			}

			/* Fill in information on the backing storage. */
			copy->mp_state = self->mfl_ucdat.ucd_ucmem.scd_copy_state;
			DBG_memset(&self->mfl_ucdat.ucd_ucmem.scd_bitset, 0xcc,
			           sizeof(self->mfl_ucdat.ucd_ucmem.scd_bitset));
			memcpy(&copy->mp_mem,
			       &self->mfl_ucdat.ucd_ucmem.scd_copy_mem,
			       MAX_C(sizeof(struct mchunk),
			             sizeof(struct mchunkvec)));
			DBG_memset(&self->mfl_ucdat.ucd_ucmem.scd_copy_mem, 0xcc,
			           MAX_C(sizeof(struct mchunk),
			                 sizeof(struct mchunkvec)));

			/* We don't copy mem-part meta-data, since doing so
			 * wouldn't really make too much sense, and since I
			 * have  no  idea   how  that   would  even   work.
			 * >> meta-data can't really be copied */
			copy->mp_meta = NULL;

			/* With that, the new mem-part has been initialized, however we must
			 * still copy over the  contents of the old  part into the new  one! */
			mpart_copyram(copy, part, acc_offs, acc_size / PAGESIZE);

			/* Remove `node' from the link-list of the original mem-part. */
			LIST_REMOVE(node, mn_link);

			/* With  memory copied, we  no longer need  our lock to `part'
			 * But note that we've set  `copy->mp_flags & MPART_F_LOCKBIT'
			 * above, and it is _that_ lock which we'll eventually let our
			 * caller inherit! */
			mpart_lock_release(part);

			/* Set-up the copy <--> node link */
			node->mn_part          = copy; /* A reference to the original `part' is inherited here.
			                                * That   reference   is   destroyed   further    below! */
			node->mn_partoff       = 0;    /* The newly created node is a perfect fit for the accessed range! */
			self->mfl_offs         = 0;    /* *ditto* */
			copy->mp_copy.lh_first = node;
			node->mn_link.le_prev  = &copy->mp_copy.lh_first;
			node->mn_link.le_next  = NULL;
			/*noderel_offset = 0;*/ /* Would be unused... */
			/*acc_offs       = 0;*/ /* Would be unused... */

			/* Insert the new (copy)-part into the global list of all parts. */
			COMPILER_WRITE_BARRIER();
			mpart_all_list_insert(copy);
			/*self->mfl_part = copy;*/ /* Already done by the `self->mfl_part = node->mn_part;' below! */
		} /* Scope... */

		decref_unlikely(part); /* Originally inherited from `node->mn_part' */

		/* Try to merge the newly updated node with its successor/predecessor. */
		{
			node           = mnode_merge_with_partlock(node);
			self->mfl_node = node;
			self->mfl_part = node->mn_part;
			assert(self->mfl_addr >= node->mn_minaddr);
			assert(self->mfl_addr <= node->mn_maxaddr);
			/* Re-calculate the part-offset which should be mapped.
			 *
			 * This is needed because merging the mem-node might have  altered
			 * the node's base address and/or its mn_partoff! The former being
			 * changed when the node itself is merged, and the later when  the
			 * pointed-to mem-part is merged. */
			self->mfl_offs = (size_t)((byte_t *)self->mfl_addr - node->mn_minaddr) +
			                 node->mn_partoff;
		} /* Scope... */
	} EXCEPT {
		/* Must re-initialize `mfl_scdat' on error (it was originally finalized by
		 * our  successful call to  `mpart_setcore_or_unlock()' further up above).
		 *
		 * This is required to ensure that `self' is in a consistent state,  should
		 * our caller decide to use `mfault_fini()' to destroy the fault-controller
		 * before propagating the exception that brought us here (which is the most
		 * likely thing to happen after we re-throw the exception here) */
		mpart_setcore_data_init(&self->mfl_scdat);
		RETHROW();
	}
done:
	DBG_memset(&self->mfl_scdat, 0xcc, sizeof(self->mfl_scdat));
	DBG_memset(&self->mfl_ucdat, 0xcc, sizeof(self->mfl_ucdat));
	DBG_memset(self->mfl_pcopy, 0xcc, sizeof(self->mfl_pcopy));
	assert(self->mfl_size != 0);
	return true;
nope_reinit_scmem:
	mpart_setcore_data_init(&self->mfl_scdat);
nope:
	return false;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_FAULT_C */
