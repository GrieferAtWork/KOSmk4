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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MM_FAULT_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MM_FAULT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mm-fault.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifdef NDEBUG
#define DBG_memset(ptr, byte, num_bytes) (void)0
#else /* NDEBUG */
#define DBG_memset(ptr, byte, num_bytes) memset(ptr, byte, num_bytes)
#endif /* !NDEBUG */
#define DBG_inval(obj) DBG_memset(&(obj), 0xcc, sizeof(obj))



/* Try to pre-fault access to the given addres range, such that `memcpy_nopf()'
 * may succeed when re-attempted.
 * @return: * : The # of leading bytes that this function managed to fault. For
 *              this purpose, any non-zero value means that `*(byte_t *)addr'
 *              was made accessible for at least one moment before this function
 *              returns. Note though that memory may have already been unloaded
 *              by the time this function returns (unlikely), so the caller must
 *              still be ready to deal with the possibility that another attempt
 *              at doing nopf access at `*(byte_t *)addr' might immediatly fail
 *              again.
 *              Also note that for any memory that had already been faulted within
 *              the given address range, this function acts as though it had been
 *              the one to fault that range, meaning that the return value doesn't
 *              actually represent how much memory had just been faulted, but rather
 *              how much continuous memory (starting at `addr' and limited by at
 *              most `num_bytes') was faulted simultaneously at some point before
 *              this function returns.
 * @return: 0 : Nothing could be faulted. This might be because `addr' doesn't
 *              point into mapped memory, or the memory that is pointed-to by it
 *              is backed by VIO storage.
 *              The caller should handle this case by attempting direct memory
 *              access to the affected region (i.e. using `memcpy' rather than 
 *              `memcpy_nopf'), and dealing with any potential E_SEGFAULT error.
 * @param: flags: Set of `MMAN_FAULT_F_*' */
PUBLIC size_t FCALL
mman_prefault(USER CHECKED void const *addr,
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
		            pagealigned_addr, pagealigned_size);
		TRY {
again:
			mman_lock_acquire(mf.mfl_mman);
			mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings, addr);
			if unlikely(!mf.mfl_node)
				goto unlock_and_done;
			mf.mfl_part = mf.mfl_node->mn_part;
			if unlikely(!mf.mfl_part)
				goto unlock_and_done;

			/* Skip VIO parts. */
			if unlikely(mf.mfl_part->mp_state == MPART_ST_VIO)
				goto unlock_and_done;

			/* Try to fault the backing mem-parts. */
			if (!mfault_or_unlock(&mf, flags))
				goto again;

			/* Prepare our page directory of mapping memory. */
			if (!pagedir_prepare_map(mf.mfl_addr, mf.mfl_size)) {
				mpart_lock_release(mf.mfl_part);
				mman_lock_release(mf.mfl_mman);
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
			}
		} EXCEPT {
			mfault_fini(&mf);
			RETHROW();
		}
		/* (re-)map the faulted address range. */
		mpart_mmap(mf.mfl_part, mf.mfl_addr, mf.mfl_size,
		           mf.mfl_offs, mnode_getperm(mf.mfl_node));
		pagedir_unprepare_map(mf.mfl_addr, mf.mfl_size);
		pagedir_sync(mf.mfl_addr, mf.mfl_size);
		mpart_lock_release(mf.mfl_part);
		mman_lock_release(mf.mfl_mman);

		addend = (size_t)(((byte_t *)pagealigned_addr + mf.mfl_size) - (byte_t *)addr);
		mfault_fini(&mf);
		/* Account for how much was actually faulted. */
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
 * memory, after skipping the first `offset' bytes. The return value is the sum
 * of successfully faulted segments, however faulting also stops on the first
 * segment that cannot be fully faulted.
 * @param: flags: Set of `MMAN_FAULT_F_*' */
PUBLIC size_t FCALL
mman_prefaultv(struct aio_buffer const *__restrict buffer,
               size_t offset, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	AIO_BUFFER_FOREACH(ent, buffer) {
		if (offset != 0) {
			if (offset >= ent.ab_size) {
				offset -= ent.ab_size;
				continue;
			}
			ent.ab_base += offset;
			ent.ab_size -= offset;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		/* Prefault this part. */
		temp = mman_prefault(ent.ab_base, ent.ab_size, flags);
		result += temp;
		/* Stop upon the first partial error (iow: once reaching
		 * the first byte that could not be faulted) */
		if (temp < ent.ab_size)
			break;
		if (ent.ab_size >= num_bytes)
			break;
		num_bytes -= ent.ab_size;
	}
	return result;
}



/* Force all bytes within the given address range to be faulted for either reading
 * or writing. If any page within the specified range isn't mapped, throw an E_SEGFAULT
 * exception. Otherwise, ensure that copy-on-write is performed when `MMAN_FAULT_F_WRITE'
 * is set, and that irregardless of `MMAN_FAULT_F_WRITE', physical memory is allocated
 * for any mapping that can be made to be backed by RAM.
 *
 * NOTES:
 *  - When `MMAN_FAULT_F_WRITE' is set, this function also verifies that the mem-nodes
 *    associated with the given address range all have the `MNODE_F_PWRITE' flag set.
 *  - Any VIO mappings within the specified range are simply ignored (and will not
 *    count towards the returned value), unless `MMAN_FAULT_F_NOVIO' is set, in
 *    which case such mappings will cause an exception to be thrown.
 *  - This function will automatically wide the given range to encompass whole pages.
 *  - This function will also update the page directory mappings for any mem-parts
 *    that get faulted during its invocation, meaning that use of `memcpy_nopf()'
 *    within the indicated address range (whilst still checking it for errors for
 *    the even of the mapping changing, or the mapping being a VIO mapping) becomes
 *    possible immediately, without having to force any sort of additional memory
 *    access (note though that this only applies to the page directory of `self',
 *    though also note that if some mem-part within the range was already faulted,
 *    its page directory mapping in `self' will still be updated if need be, as it
 *    may have been faulted as a lazy memory mapping).
 */
PUBLIC NONNULL((1)) void FCALL
mman_forcefault(struct mman *__restrict self,
                USER CHECKED void const *addr,
                size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	struct mfault mf;
	while (num_bytes) {
		PAGEDIR_PAGEALIGNED void *pagealigned_addr;
		PAGEDIR_PAGEALIGNED size_t pagealigned_size;
		size_t addend;
again_mfault_init:
		pagealigned_addr = (void *)FLOOR_ALIGN((uintptr_t)addr, PAGESIZE);
		pagealigned_size = CEIL_ALIGN(num_bytes + ((uintptr_t)addr - (uintptr_t)pagealigned_addr), PAGESIZE);
		mfault_init(&mf, ADDR_ISKERN(addr) ? &mman_kernel : THIS_MMAN,
		            pagealigned_addr, pagealigned_size);
		TRY {
again:
			mman_lock_acquire(mf.mfl_mman);
			mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings, addr);
			if unlikely(!mf.mfl_node)
				goto err_unmapped;
			mf.mfl_part = mf.mfl_node->mn_part;
			if unlikely(!mf.mfl_part)
				goto err_unmapped;

			/* Skip VIO parts, or throw an exception. */
			if unlikely(mf.mfl_part->mp_state == MPART_ST_VIO) {
				void *old_end_addr, *new_end_addr;
				mman_lock_release(mf.mfl_mman);
				mfault_fini(&mf);
				if (flags & MMAN_FAULT_F_NOVIO)
					goto err_unmapped_now;
				old_end_addr = (void *)addr + num_bytes;
				new_end_addr = mnode_getendaddr(mf.mfl_node);
				if (new_end_addr >= old_end_addr)
					goto done;
				num_bytes = (size_t)((byte_t *)old_end_addr - (byte_t *)new_end_addr);
				addr      = new_end_addr;
				goto again_mfault_init;
			}

			/* Try to fault the backing mem-parts. */
			if (!mfault_or_unlock(&mf, flags))
				goto again;

			/* Prepare our page directory of mapping memory. */
			if (!pagedir_prepare_map(mf.mfl_addr, mf.mfl_size)) {
				mpart_lock_release(mf.mfl_part);
				mman_lock_release(mf.mfl_mman);
				THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
			}
		} EXCEPT {
			mfault_fini(&mf);
			RETHROW();
		}

		/* (re-)map the faulted address range. */
		mpart_mmap(mf.mfl_part, mf.mfl_addr, mf.mfl_size,
		           mf.mfl_offs, mnode_getperm(mf.mfl_node));
		pagedir_unprepare_map(mf.mfl_addr, mf.mfl_size);
		pagedir_sync(mf.mfl_addr, mf.mfl_size);
		mpart_lock_release(mf.mfl_part);
		mman_lock_release(mf.mfl_mman);

		addend = (size_t)(((byte_t *)pagealigned_addr + mf.mfl_size) - (byte_t *)addr);
		mfault_fini(&mf);
		if (addend >= num_bytes)
			break;
		/* Continue force-faulting more memory... */
		addr = (byte_t *)addr + addend;
		num_bytes -= addend;
	}
done:
	return;
unlock_and_done:
	mman_lock_release(mf.mfl_mman);
	mfault_fini(&mf);
	goto done;
err_unmapped:
	mman_lock_release(mf.mfl_mman);
	mfault_fini(&mf);
err_unmapped_now:
	THROW(E_SEGFAULT_UNMAPPED, addr,
	      E_SEGFAULT_CONTEXT_FAULT |
	      ((flags & MMAN_FAULT_F_WRITE) ? E_SEGFAULT_CONTEXT_WRITING : 0));
}



/* Same as `mman_forcefault()', but fault all memory pointed-to by the given buffer. */
PUBLIC NONNULL((1, 2)) void FCALL
mman_forcefaultv(struct mman *__restrict self,
                 struct aio_buffer const *__restrict buffer,
                 size_t offset, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT) {
	struct aio_buffer_entry ent;
	AIO_BUFFER_FOREACH(ent, buffer) {
		if (offset != 0) {
			if (offset >= ent.ab_size) {
				offset -= ent.ab_size;
				continue;
			}
			ent.ab_base += offset;
			ent.ab_size -= offset;
		}
		if (ent.ab_size > num_bytes)
			ent.ab_size = num_bytes;
		/* Force-fault this part. */
		mman_forcefault(self, ent.ab_base, ent.ab_size, flags);
		if (ent.ab_size >= num_bytes)
			break;
		num_bytes -= ent.ab_size;
	}
}


struct unlock_mman_info {
	struct mpart_unlockinfo umi_unlock; /* Unlock info */
	struct mman            *umi_mman;   /* [1..1][const] The mman that should be unlocked. */
};

NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unlock_mman_cb)(struct mpart_unlockinfo *__restrict self) {
	struct unlock_mman_info *me;
	me = container_of(self, struct unlock_mman_info, umi_unlock);
	mman_lock_release(me->umi_mman);
}


/* (Try to) acquire locks, and load/split/unshare/... backing memory,
 * as well as mem-parts and mem-nodes in order to prepare everything
 * needed in order to map a given sub-address-range of a given mpart,
 * as accessed through a given mnode into memory.
 *
 * Usage:
 * >> void pf_handler(void *addr, bool is_write) {
 * >>     struct mfault mf;
 * >>     mfault_init(&mf, ADDR_ISKERN(addr) ? &mman_kernel : THIS_MMAN,
 * >>                 FLOOR_ALIGN(addr, PAGESIZE), PAGESIZE);
 * >>     TRY {
 * >> again:
 * >>         mman_lock_acquire(mf.mfl_mman);
 * >>         mf.mfl_node = mnode_tree_locate(mf.mfl_mman->mm_mappings);
 * >>         mf.mfl_part = mf.mfl_node->mn_part;
 * >>         // Missing: NULL- and safety-checks; VIO support
 * >>         if (!mfault_or_unlock(&mf, is_write ? MMAN_FAULT_F_WRITE : 0))
 * >>             goto again;
 * >>     } EXCEPT {
 * >>         mfault_fini(&mf);
 * >>         RETHROW();
 * >>     }
 * >>     if (!pagedir_prepare_map(mf.mfl_addr, mf.mfl_size)) { ... }
 * >>     mpart_mmap(mf.mfl_part, mf.mfl_addr, mf.mfl_size,
 * >>                mf.mfl_offs, mnode_getperm(mf.mfl_node));
 * >>     pagedir_unprepare_map(mf.mfl_addr, mf.mfl_size);
 * >>     pagedir_sync(mf.mfl_addr, mf.mfl_size);
 * >>     mpart_lock_release(mf.mfl_part);
 * >>     mman_lock_release(mf.mfl_mman);
 * >>     // NOTE: Don't call `mfault_fini(&mf)' here!
 * >>     //       Internal data of `mf' is left in an undefined state
 * >>     //       following a successful call to `mfault_or_unlock()'!
 * >> }
 *
 * Locking logic:
 *   - return == true:   mpart_lock_acquire(self->mfl_part);
 *                       undefined(out(INTERNAL_DATA(self)))
 *   - return == false:  mman_lock_release(self->mfl_mman);
 *   - EXCEPT:           mman_lock_release(self->mfl_mman);
 *
 * @param: self:   mem-lock control descriptor.
 * @param: flags:  Set of `MMAN_FAULT_F_NORMAL | MMAN_FAULT_F_WRITE'
 * @return: true:  Successfully faulted memory.
 * @return: false: The lock to `self->mfl_mman' was lost, but the goal
 *                 of faulting memory has gotten closer, and the caller
 *                 should re-attempt the call after re-acquiring locks.
 * @return: false: `mpart_lock_acquire_and_setcore_loadsome()' would have
 *                 had to be called, but the accessed address range lies
 *                 outside the bounds of the associated mem-part.
 *                 Resolve this issue by simply trying again (this
 *                 inconsistency can result from someone else splitting
 *                 the associated mem-part) */
PUBLIC NONNULL((1)) bool FCALL
mfault_or_unlock(struct mfault *__restrict self,
                 unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct unlock_mman_info unlock;

	/* Validate input arguments. */
	assert(self->mfl_node);
	assert(self->mfl_part);
	assert(self->mfl_mman == self->mfl_node->mn_mman);
	assert(self->mfl_part == self->mfl_node->mn_part);
	assert(mman_lock_acquired(self->mfl_mman));
	assert(IS_ALIGNED((uintptr_t)self->mfl_addr, PAGESIZE));
	assert(IS_ALIGNED((uintptr_t)self->mfl_size, PAGESIZE));
	assert(self->mfl_size != 0);
	assert(!wasdestroyed(self->mfl_part));
	assert(!wasdestroyed(self->mfl_mman));

	/* First off: Try to acquire a lock to the associated data-part.
	 * XXX: Maybe change the ABI so this is also done by other caller?
	 * After all: Our function name doesn't really suggest that we
	 *            do this; only the function doc tell about this... */
	if unlikely(!mpart_lock_tryacquire(self->mfl_part)) {
		incref(self->mfl_part);
		mman_lock_release(self->mfl_mman);
		FINALLY_DECREF_UNLIKELY(self->mfl_part);
		/* Wait for the part's lock to become available. */
		while (!mpart_lock_available(self->mfl_part))
			task_yield();
		goto nope;
	}

	/* Set-up our extended unlock controller. */
	/* TODO: Make the unlock controller be apart of `struct mfault'.
	 *       That way, we wouldn't have to initialize it here, and
	 *       `unlock_mman_cb()' could still gain access to the mman
	 *       it's supposed to unlock by using `container_of()' */
	unlock.umi_unlock.ui_unlock = &unlock_mman_cb;
	unlock.umi_mman             = self->mfl_mman;

	if (!(flags & MMAN_FAULT_F_WRITE)) {
		mpart_reladdr_t partrel_offset;
		size_t num_bytes;
		/* Simple case: Only need to lock+load the accessed address range. */
		if (!mpart_setcore_or_unlock(self->mfl_part,
		                             &unlock.umi_unlock,
		                             &self->mfl_ucdat.ucd_scmem))
			goto nope;
		partrel_offset = 42; /* TODO */
		num_bytes      = 42; /* TODO */
		if (!mpart_loadsome_or_unlock(self->mfl_part,
		                              &unlock.umi_unlock,
		                              partrel_offset,
		                              num_bytes))
			goto nope;
		self->mfl_offs = partrel_offset;
		self->mfl_size = num_bytes;
		DBG_inval(self->mfl_ucdat);
		return true;
	}

	/* TODO: As many of those `mpart_lock_acquire_and_...' functions as
	 *       possible need to have their internal dothing_or_unlock()
	 *       variants exposed, so we can make calls to them from in here!
	 * Specifically, we must be able to call:
	 *   - setcore
	 *   - loadsome
	 *   - loadall
	 *   - unsharecow
	 *
	 * As well as make our own allocations of up to 2 additional mem-nodes that
	 * are needed when doing the local cow-unshare (~ala `mfl_node = ALLOC_NODE();')
	 */

	/* TODO */

	return true;
nope:
	return false;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MM_FAULT_C */
