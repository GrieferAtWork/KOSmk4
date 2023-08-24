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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FAULT_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FAULT_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mpart.h> /* struct mpart_unsharecow_data */
#include <kernel/paging.h>
#include <kernel/types.h>

/* Helper functions for faulting address ranges over a given mman */


/* Flags for prefaulting functions below. */
#define MMAN_FAULT_F_NORMAL 0x0000 /* Normal flags */
#define MMAN_FAULT_F_WRITE  0x0001 /* Fault for writing */
#ifdef LIBVIO_CONFIG_ENABLED
#define MMAN_FAULT_F_NOVIO  0x0002 /* (for `mman_forcefault'): Throw `E_SEGFAULT' if encountering VIO. */
#else /* LIBVIO_CONFIG_ENABLED */
#define MMAN_FAULT_F_NOVIO  0x0000 /* Ignored */
#endif /* !LIBVIO_CONFIG_ENABLED */

#ifdef __CC__
DECL_BEGIN

struct mman;
struct iov_buffer;

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
FUNDEF BLOCKING size_t FCALL
mman_prefault(NCX void const *addr,
              size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

/* Enumerate segments from `buffer', and prefault up to `num_bytes' of pointed-to
 * memory,  after skipping the first `offset' bytes.  The return value is the sum
 * of successfully faulted  segments, however  faulting also stops  on the  first
 * segment that cannot be fully faulted.
 * @param: flags: Set of `MMAN_FAULT_F_*' */
FUNDEF BLOCKING NONNULL((1)) size_t FCALL
mman_prefaultv(struct iov_buffer const *__restrict buffer,
               size_t offset, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


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
FUNDEF BLOCKING NONNULL((1)) void FCALL
mman_forcefault(struct mman *__restrict self,
                NCX void const *addr,
                size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, E_FSERROR_READONLY, ...);

/* Same as `mman_forcefault()', but fault all memory pointed-to by the given buffer. */
FUNDEF BLOCKING NONNULL((1, 2)) void FCALL
mman_forcefaultv(struct mman *__restrict self,
                 struct iov_buffer const *__restrict buffer,
                 size_t offset, size_t num_bytes, unsigned int flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...);






/************************************************************************/
/* Low-level memory faulting control (used to implement the above)      */
/************************************************************************/


#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */

struct mfault {
	/* mfault: Controller for faulting memory in the context of a memory manager.
	 *
	 * Control flow mockup of `mfault_or_unlock()'. (Oversimplified!)
	 *
	 * >> size_t noderel_addr = mfl_addr - mnode_getaddr(mfl_node);
	 * >> size_t partrel_addr = mfl_node->mn_partoff + noderel_addr;
	 * >> mfl_part            = mfl_node->mn_part;
	 * >>
	 * >> if (READ_ONLY) {
	 * >>     mpart_lock_acquire_and_setcore_load(mfl_part, partrel_addr, mfl_size);
	 * >> } else {
	 * >>     if (mfl_node->mn_flags & MNODE_F_SHARED) {
	 * >>         mpart_lock_acquire_and_setcore_unsharecow_load(mfl_part, partrel_addr, mfl_size);
	 * >>     } else if (mpart_iscopywritable(mfl_part, ...)) {
	 * >>         // Accessed mfl_node is the only copy-on-write mfl_node in existence
	 * >>         mpart_split(mfl_part, FLOOR_ALIGN(partrel_addr));
	 * >>         mpart_split(mfl_part, CEIL_ALIGN(partrel_addr + mfl_size));
	 * >>         mpart_lock_acquire_and_setcore_load(mfl_part, partrel_addr, mfl_size);
	 * >>     } else {
	 * >>         // XXX: This part I've not fully thought through; There may be design flaws...
	 * >>         //
	 * >>         // Create an anonymous copy of the given mfl_part within the accessed
	 * >>         // address range. Then, create a new mnode to map that anonymous
	 * >>         // copy within the accessed address range.
	 * >>         // Also: Both here, and in `mpart_lock_acquire_and_setcore_unsharecow()'
	 * >>         //       there should be checks that will attempt to merge these anonymous
	 * >>         //       mnode+mpart pairs with neighboring ones that do the same.
	 * >>         mfl_node = ALLOC_NODE();
	 * >>         mfl_part = mpart_anoncopy(mfl_part, partrel_addr, mfl_size);
	 * >>         mfl_node->mn_minaddr += noderel_addr;
	 * >>         mfl_node->mn_maxaddr = mfl_node->mn_minaddr + mfl_size - 1;
	 * >>         mfl_node->mn_part    = mfl_part;
	 * >>         MMAN_DELETE_NODE_SUBRANGE(mfl_mman, mfl_node->mn_minaddr, mfl_node->mn_maxaddr);
	 * >>         mman_mappings_insert(mfl_mman, mfl_node);
	 * >>     }
	 * >>     mpart_changed(mfl_part);
	 * >> } */

	/* NOTE: All of the [out] fields below are only modified when `mfault_or_unlock()'
	 *       returns while indicating success! */
	struct mman                        *mfl_mman;  /* [1..1][const][== mfl_node->mn_mman] */
	PAGEDIR_PAGEALIGNED void           *mfl_addr;  /* [const] address where faulting starts */
	PAGEDIR_PAGEALIGNED size_t          mfl_size;  /* [in|out][!0] The # of bytes that should be/were faulted. */
	unsigned int                        mfl_flags; /* [const] Access flags (set of `MMAN_FAULT_F_NORMAL | MMAN_FAULT_F_WRITE') */
	struct mnode                       *mfl_node;  /* [1..1][in|out] The node  being accessed.  Depending
	                                                * on how the access is made, this node may be altered */
	struct mpart                       *mfl_part;  /* [1..1][in|out][== mfl_node->mn_part] The locked part (on success). */
	PAGEDIR_PAGEALIGNED mpart_reladdr_t mfl_offs;  /* [out] Mapping offset into `mfl_part'. */

	/* All of the  below fields  should not  be touched,  and are  [in|out],
	 * though may also be modified when `mfault_or_unlock()' returns `false'
	 * Leave them  alone.  -  They're needed  to  make  `mfault_or_unlock()'
	 * fully re-entrant following a lock re-acquisition. */
	struct unlockinfo                   mfl_unlck;    /* Unlock controller. */
	struct mpart_setcore_data           mfl_scdat;    /* Load-data for setcore. */
	struct mpart_unsharecow_data        mfl_ucdat;    /* Load-data for unshare. */
	struct mnode                       *mfl_pcopy[2]; /* [0..1][*] Up to 2 additional mem-nodes used for private unsharing. */
};

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */

#define mfault_init(self, mm, addr, size, flags) \
	(void)((self)->mfl_mman  = (mm),             \
	       (self)->mfl_addr  = (addr),           \
	       (self)->mfl_size  = (size),           \
	       (self)->mfl_flags = (flags),          \
	       __mfault_init(self))
#define __mfault_init(self)                                \
	(void)(mpart_setcore_data_init(&(self)->mfl_scdat),    \
	       mpart_unsharecow_data_init(&(self)->mfl_ucdat), \
	       (self)->mfl_pcopy[0] = __NULLPTR)
#define mfault_fini(self)                                     \
	(mpart_setcore_data_fini(&(self)->mfl_scdat),             \
	 mpart_unsharecow_data_fini(&(self)->mfl_ucdat),          \
	 (self)->mfl_pcopy[0] ? (__os_free((self)->mfl_pcopy[0]), \
	                         __os_free((self)->mfl_pcopy[1])) \
	                      : (void)0)


/* Acquire a lock to `self->mfl_part', or release a lock to `self->mfl_mman'
 * Locking logic:
 *   - return == true:   mpart_lock_acquire(self->mfl_part);
 *   - return == false:  _mman_lock_release(self->mfl_mman);
 *   - EXCEPT:           mman_lock_release(self->mfl_mman); */
#ifdef __INTELLISENSE__
BLOCKING NONNULL((1)) __BOOL
mfault_lockpart_or_unlock(struct mfault *__restrict self)
		THROWS(E_WOULDBLOCK);
#else /* __INTELLISENSE__ */
#define mfault_lockpart_or_unlock(self) \
	(mpart_lock_tryacquire((self)->mfl_part) || (_mfault_unlock_and_waitfor_part(self), 0))
#endif /* !__INTELLISENSE__ */
FUNDEF NONNULL((1)) void FCALL
_mfault_unlock_and_waitfor_part(struct mfault *__restrict self)
		THROWS(E_WOULDBLOCK);


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
 *         >> (self->mfl_part->mp_file->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY)) == MFILE_F_READONLY
 */
FUNDEF BLOCKING NONNULL((1)) __BOOL FCALL
mfault_or_unlock(struct mfault *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_FSERROR_READONLY, ...);


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
DATDEF size_t mfault_autosplit_threshold;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FAULT_H */
