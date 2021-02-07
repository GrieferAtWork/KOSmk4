/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MMETA_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MMETA_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_VM
#include <kernel/vm.h>
#else /* !CONFIG_USE_NEW_VM */
#include <kernel/arch/mman/rtm.h>
#include <kernel/mman/mpart.h>
#include <kernel/types.h>
#include <sched/signal.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/aref.h>

/* NOTE: Unlike `mpart' and its other fields, `mpartmeta', as well
 *       `mfutex' objects may be allocated without `GFP_LOCKED'!
 *       This is because these components don't add anything that
 *       might be needed within the context of loading data from
 *       swap. */

#ifdef __CC__
DECL_BEGIN

/* Rarely used memory meta-data (for use with the `struct mpart::mp_exdat') */

struct mfile;     /* Memory file. */
struct mpart;     /* Memory file part. */
struct mpartmeta; /* Memory file part meta-data. */
struct mfutex;    /* Memory-Fast-Userspace-mUTEX */

#ifndef __mfutex_slist_defined
#define __mfutex_slist_defined
SLIST_HEAD(mfutex_slist, mfutex);
#endif /* !__mfutex_slist_defined */

#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */

#define MFUTEX_ADDR_ALIGNMENT 2 /* Minimum alignment for mem-futex addresses. */

#ifndef __mpart_awref_defined
#define __mpart_awref_defined
AWREF(mpart_awref, mpart);
#endif /* !__mpart_awref_defined */

struct mfutex {
	/* Memory-Fast-Userspace-mUTEX */
	WEAK refcnt_t                    mfu_refcnt; /* Reference counter. */
	struct mpart_awref               mfu_part;   /* [1..1] The (currently) associated mem-part.
	                                              * Note that this part may change arbitrarily as the result of calls to
	                                              * `mpart_split()'. To prevent this, read out this field, acquire a lock
	                                              * to the mem-part, or the futex-tree-lock, then read out this field again
	                                              * until the mem-part no longer changes. At this point, the mem-part you'll
	                                              * end up with will be consistent.
	                                              * end up with will be consistent. */
	mpart_reladdr_t                  mfu_addr;   /* [lock(mfu_part->mp_meta->mpm_ftx)] Address of this mem-futex
	                                              * (relative to mfu_part; within the R/B-tree)
	                                              * NOTE: The least-significant bit is used as R/B-bit, meaning
	                                              *       that part addresses must be aligned by at least 2 bytes. */
	union {
		LLRBTREE_NODE(struct mfutex) mfu_mtaent; /* [lock(mfu_part->mp_meta->mpm_ftx)] MeTA-data ENTry. */
		SLIST_ENTRY(mfutex)         _mfu_dead2;  /* Used internally */
	};
	union {
		struct sig                   mfu_signal; /* [valid_if(mfu_refcnt != 0)] The signal used to implement the mem-futex. */
		SLIST_ENTRY(mfutex)         _mfu_dead;   /* [valid_if(mfu_refcnt == 0)][lock(ATOMIC)]
		                                          * Entry within the list of dead mem-futex objects. */
	};
};

#define mfutex_init(self, part, addr)     \
	((self)->mfu_refcnt = 1,              \
	 awref_init(&(self)->mfu_part, part), \
	 (self)->mfu_addr = (addr),           \
	 sig_init(&(self)->mfu_signal))
#define mfutex_cinit(self, part, addr)     \
	((self)->mfu_refcnt = 1,               \
	 awref_cinit(&(self)->mfu_part, part), \
	 (self)->mfu_addr = (addr),            \
	 sig_cinit(&(self)->mfu_signal))
#define mfutex_addr(self) ((self)->mfu_addr & ~1)


/* Destroy the given mem-futex. */
#define mfutex_free(self) kfree(self)
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL mfutex_destroy)(struct mfutex *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mfutex, mfu_refcnt, mfutex_destroy)


/* Mem-futex tree API. All of these functions require that the caller
 * be holding a lock to the associated `struct mpartmeta::mpm_ftxlock'. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mfutex *NOTHROW(FCALL mfutex_tree_locate)(/*nullable*/ struct mfutex *root, mpart_reladdr_t key);
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mfutex *NOTHROW(FCALL mfutex_tree_rlocate)(/*nullable*/ struct mfutex *root, mpart_reladdr_t minkey, mpart_reladdr_t maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mfutex_tree_insert)(struct mfutex **__restrict proot, struct mfutex *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL mfutex_tree_tryinsert)(struct mfutex **__restrict proot, struct mfutex *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mfutex *NOTHROW(FCALL mfutex_tree_remove)(struct mfutex **__restrict proot, mpart_reladdr_t key);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mfutex *NOTHROW(FCALL mfutex_tree_rremove)(struct mfutex **__restrict proot, mpart_reladdr_t minkey, mpart_reladdr_t maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mfutex_tree_removenode)(struct mfutex **__restrict proot, struct mfutex *__restrict node);



struct mpartmeta {
	struct atomic_rwlock              mpm_ftxlock;  /* Lock for `mpm_ftx' */
	LLRBTREE_ROOT(WEAK struct mfutex) mpm_ftx;      /* [0..n][lock(mpm_ftx)] Futex tree.
	                                                 * NOTE: May contain dead futex objects! */
	struct WEAK mfutex_slist          mpm_ftx_dead; /* [0..n][lock(ATOMIC)] Chain of dead futex objects. */
	WEAK refcnt_t                     mpm_dmalocks; /* [lock(INC(:MPART_F_LOCKBIT), DEC(ATOMIC))]
	                                                 * # of DMA locks referencing the associated part. */
	struct sig                        mpm_dma_done; /* Broadcast when `mpm_dmalocks' drops to `0' */
#ifdef ARCH_HAVE_RTM
	/* We keep the RTM version and field in the futex controller, such that
	 * they don't take up space in the base `mpart' structure, but only exist
	 * conditionally, and upon first access. */
	uintptr_t                         mpm_rtm_vers; /* [lock(:dp_lock)]
	                                                 * RTM version (incremented for every RTM-driven
	                                                 * modifications made to memory). */
#endif /* ARCH_HAVE_RTM */
};

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpartmeta_destroy)(struct mpartmeta *__restrict self);

#ifdef ARCH_HAVE_RTM
#define __mpartmeta_init_rtm(self)  , (self)->mpm_rtm_vers = 0
#define __mpartmeta_cinit_rtm(self) , __hybrid_assert((self)->mpm_rtm_vers == 0)
#else /* ARCH_HAVE_RTM */
#define __mpartmeta_init_rtm(self)
#define __mpartmeta_cinit_rtm(self)
#endif /* !ARCH_HAVE_RTM */
#define mpartmeta_init(self)                   \
	(atomic_rwlock_init(&(self)->mpm_ftxlock), \
	 (self)->mpm_ftx = __NULLPTR,              \
	 SLIST_INIT(&(self)->mpm_ftx_dead),        \
	 sig_init(&(self)->mpm_dma_done)           \
	 __mpartmeta_init_rtm(self))
#define mpartmeta_cinit(self)                             \
	(atomic_rwlock_cinit(&(self)->mpm_ftxlock),           \
	 __hybrid_assert((self)->mpm_ftx == __NULLPTR),       \
	 __hybrid_assert(SLIST_EMPTY(&(self)->mpm_ftx_dead)), \
	 sig_cinit(&(self)->mpm_dma_done)                     \
	 __mpartmeta_cinit_rtm(self))


/* Reap dead futex objects of `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpartmeta_deadftx_reap)(struct mpartmeta *__restrict self);
#define mpartmeta_deadftx_mustreap(self) \
	(__hybrid_atomic_load((self)->mpm_ftx_dead.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#ifdef __OPTIMIZE_SIZE__
#define mpartmeta_deadftx_reap(self) _mpartmeta_deadftx_reap(self)
#else /* __OPTIMIZE_SIZE__ */
#define mpartmeta_deadftx_reap(self) (void)(!mpartmeta_deadftx_mustreap(self) || (_mpartmeta_deadftx_reap(self), 0))
#endif /* !__OPTIMIZE_SIZE__ */


/* Lock accessor helpers for the futex tree of `struct mpartmeta' */
#define mpartmeta_ftxlock_write(self)      atomic_rwlock_write(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_write_nx(self)   atomic_rwlock_write_nx(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_trywrite(self)   atomic_rwlock_trywrite(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_endwrite(self)   (atomic_rwlock_endwrite(&(self)->mpm_ftxlock), mpartmeta_deadftx_reap(self))
#define mpartmeta_ftxlock_endwrite_f(self) atomic_rwlock_endwrite(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_read(self)       atomic_rwlock_read(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_read_nx(self)    atomic_rwlock_read_nx(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_tryread(self)    atomic_rwlock_tryread(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_endread(self)    (void)(atomic_rwlock_endread(&(self)->mpm_ftxlock) && (mpartmeta_deadftx_reap(self), 0))
#define mpartmeta_ftxlock_end(self)        (void)(atomic_rwlock_end(&(self)->mpm_ftxlock) && (mpartmeta_deadftx_reap(self), 0))
#define mpartmeta_ftxlock_upgrade(self)    atomic_rwlock_upgrade(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_upgrade_nx(self) atomic_rwlock_upgrade_nx(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_downgrade(self)  atomic_rwlock_downgrade(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_reading(self)    atomic_rwlock_reading(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_writing(self)    atomic_rwlock_writing(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_canread(self)    atomic_rwlock_canread(&(self)->mpm_ftxlock)
#define mpartmeta_ftxlock_canwrite(self)   atomic_rwlock_canwrite(&(self)->mpm_ftxlock)




/************************************************************************/
/* Helper functions to creating/destroying DMA locks.                   */
/************************************************************************/
FORCELOCAL NOBLOCK NONNULL((1)) void
NOTHROW(mpart_dma_addlock)(struct mpart *__restrict self) {
	__hybrid_assert(mpart_lock_acquired(self));
	struct mpartmeta *meta = self->mp_meta;
	__hybrid_assert(meta != __NULLPTR);
	__hybrid_atomic_inc(meta->mpm_dmalocks, __ATOMIC_SEQ_CST);
}

FORCELOCAL NOBLOCK NONNULL((1)) void
NOTHROW(mpart_dma_dellock)(struct mpart *__restrict self) {
	refcnt_t old_count;
	struct mpartmeta *meta = self->mp_meta;
	__hybrid_assert(meta != __NULLPTR);
	old_count = __hybrid_atomic_fetchdec(meta->mpm_dmalocks, __ATOMIC_SEQ_CST);
	__hybrid_assert(old_count >= 1);
	if (old_count == 1)
		sig_broadcast(&meta->mpm_dma_done);
}





/************************************************************************/
/* Futex access/creation API                                            */
/************************************************************************/

/* Return a pointer to the meta-data controller of `self', allocating it
 * if not already allocated in the past. This function should not be called
 * when already holding a lock to `self'. - Use `mpart_hasmeta_or_unlock()'
 * for that purpose instead! */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mpartmeta *FCALL
mpart_getmeta(struct mpart *__restrict self) THROWS(E_BADALLOC);

/* Special value returned by the functions below for when `partrel_offset' lies
 * beyond the bounds of the given mem-part. This can happen arbitrarily for any
 * `partrel_offset >= PAGESIZE' as the result of the accessed part being split. */
#define MPART_FUTEX_OOB ((struct mfutex *)-1)

/* Return a reference to the futex associated with `file_position' within the given part.
 * If no such futex already exists, use this chance to allocate it, as well as a potentially
 * missing `mfutex_controller' when `self->mp_meta' was `NULL' when this function was called.
 * @param: file_position:    The absolute in-file address of the futex (will be floor-aligned
 *                           by `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :              A reference to the futex associated with `file_position'
 * @return: MPART_FUTEX_OOB: The given `file_position' isn't mapped by `self'. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mpart_createfutex(struct mpart *__restrict self, pos_t file_position)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Same as `mpart_createfutex()', but don't allocate a new futex object if none already
 * exists for the given `file_position'
 * @param: file_position:    The absolute in-file address of the futex (will be floor-aligned
 *                           by `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :              A reference to the futex bound to the given `partrel_offset'
 * @return: NULL:            No futex exists for the given `partrel_offset'.
 * @return: MPART_FUTEX_OOB: The given `file_position' isn't mapped by `self'. */
FUNDEF WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mpart_lookupfutex(struct mpart *__restrict self, pos_t file_position)
		THROWS(E_WOULDBLOCK);

/* Lookup a futex at a given address that is offset from the start of a given
 * mem-file. Note though the possibly unintended behavior which applies when
 * the given `mfile' is anonymous at the time of the call being made.
 * @param: addr: Absolute file-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally)
 * WARNING: Using this function when `self' has been, or always was anonymous, will
 *          cause the mem-part associated with the returned futex to also be anonymous,
 *          meaning that the part would get freshly allocated, and repeated calls with
 *          the same arguments would not yield the same futex object!
 *       -> As such, in the most common case of a futex lookup where you wish to find
 *          the futex associated with some given `uintptr_t', the process would be to
 *          to determine the `mnode' of the address, and using that node then determine
 *          the associated mpart, and relative offset into that mem-part. If a lookup
 *          of the futex then returns `MPART_FUTEX_OOB', loop back around
 *          and once again lookup the `mnode'.
 *       -> In the end, there exists no API also found on linux that would make use of this
 *          function, however on KOS it is possible to access this function through use of
 *          the HANDLE_TYPE_DATABLOCK-specific hop() function `HOP_DATABLOCK_OPEN_FUTEX[_EXISTING]'
 * @return: * : The futex associated with the given `addr' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mfile_createfutex(struct mfile *__restrict self, pos_t addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Same as `mfile_createfutex()', but don't allocate a new
 * futex object if none already exists for the given `addr'
 * @param: addr:  Absolute file-address of the futex (will be floor-aligned by
 *                `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :   The futex associated with the given `addr'
 * @return: NULL: No futex exists for the given address. */
FUNDEF WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mfile_lookupfutex(struct mfile *__restrict self, pos_t addr)
		THROWS(E_WOULDBLOCK);

/* Return the futex object that is associated with the given virtual memory address.
 * In the event that `addr' isn't mapped to anything (or is mapped to a reserved
 * node), then throw an `E_SEGFAULT' exception.
 * @param: addr: Absolute memory-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally) */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mman_createfutex(struct mman *__restrict self, UNCHECKED void *addr)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT);

/* Same as `mman_createfutex()', but don't allocate a new futex object if none already
 * exists for the given `addr'. If the given address isn't mapped, also return `NULL'.
 * @param: addr:  Absolute memory-address of the futex (will be floor-aligned by
 *                `MFUTEX_ADDR_ALIGNMENT' internally)
 * @return: * :   The futex associated with the given `addr'
 * @return: NULL: No futex exists for the given address. */
FUNDEF WUNUSED NONNULL((1)) REF struct mfutex *FCALL
mman_lookupfutex(struct mman *__restrict self, UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK);

/* Broadcast to all thread waiting for a futex at `addr' within the current mman.
 * If `addr' isn't mapped, or no pre-existing node is bound to that address,
 * simply do nothing and return immediately.
 * @param: addr: Absolute memory-address of the futex (will be floor-aligned by
 *               `MFUTEX_ADDR_ALIGNMENT' internally) */
FUNDEF void FCALL
mman_broadcastfutex(UNCHECKED void *addr)
		THROWS(E_WOULDBLOCK);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MMETA_H */
