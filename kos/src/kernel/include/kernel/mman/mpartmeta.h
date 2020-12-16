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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MMETA_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MMETA_H 1

#include <kernel/compiler.h>

#include <kernel/arch/vm-rtm.h>
#include <kernel/mman/mpart.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/signal.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sequence/rbtree.h>
#include <hybrid/sync/atomic-rwlock.h>

#ifdef __CC__
DECL_BEGIN

/* Rarely used memory meta-data (for use with the `struct mpart::mp_exdat') */

struct mpart;     /* Memory file part. */
struct mpartmeta; /* Memory file part meta-data. */
struct mfutex;    /* Memory-Fast-Userspace-mUTEX */

SLIST_HEAD(mfutex_slist, mfutex);

#ifndef __mpart_reladdr_t_defined
#define __mpart_reladdr_t_defined 1
typedef size_t mpart_reladdr_t;
#endif /* !__mpart_reladdr_t_defined */


struct mfutex {
	/* Memory-Fast-Userspace-mUTEX */
	WEAK refcnt_t                    mfu_refcnt; /* Reference counter. */
	ATOMIC_REF(struct mpart)         mfu_part;   /* [1..1] The (currently) associated mem-part.
	                                              * Note that this part may change arbitrarily as the result of calls to `mpart_split()'
	                                              * To prevent this, read out this field, acquire a lock to the mem-part,
	                                              * then read out this field again until the mem-part no longer changes.
	                                              * At this point, the mem-part you'll end up with will be consistent. */
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

#define mfutex_addr(self) ((self)->mfu_addr & ~1)


/* Destroy the given mem-futex. */
#define mfutex_free(self) kfree(self)
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL mfutex_destroy)(struct mfutex *__restrict self);
/* Same as `mfutex_destroy()', but _always_ enqueue the futex to-be reaped
 * lazily once `mpartmeta_deadftx_reap()' is called with the associated controller. */
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL mfutex_destroy_later)(struct mfutex *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct mfutex, mfu_refcnt, mfutex_destroy)


/* Mem-futex tree API. All of these functions require that the caller
 * be holding a lock to the associated `struct mpartmeta::mpm_ftxlock'. */
struct mfutex_tree_minmax {
	struct mfutex *mm_min; /* [0..1] Lowest branch. */
	struct mfutex *mm_max; /* [0..1] Greatest branch. */
};
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mfutex *NOTHROW(FCALL mfutex_tree_locate)(/*nullable*/ struct mfutex *root, mpart_reladdr_t key);
FUNDEF NOBLOCK ATTR_PURE WUNUSED struct mfutex *NOTHROW(FCALL mfutex_tree_rlocate)(/*nullable*/ struct mfutex *root, mpart_reladdr_t minkey, mpart_reladdr_t maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mfutex_tree_insert)(struct mfutex **__restrict proot, struct mfutex *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL NOTHROW(FCALL mfutex_tree_tryinsert)(struct mfutex **__restrict proot, struct mfutex *__restrict node);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mfutex *NOTHROW(FCALL mfutex_tree_remove)(struct mfutex **__restrict proot, mpart_reladdr_t key);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) struct mfutex *NOTHROW(FCALL mfutex_tree_rremove)(struct mfutex **__restrict proot, mpart_reladdr_t minkey, mpart_reladdr_t maxkey);
FUNDEF NOBLOCK NONNULL((1, 2)) void NOTHROW(FCALL mfutex_tree_removenode)(struct mfutex **__restrict proot, struct mfutex *__restrict node);
FUNDEF NOBLOCK NONNULL((4)) void NOTHROW(FCALL mfutex_tree_minmaxlocate)(struct mfutex *root, mpart_reladdr_t minkey, mpart_reladdr_t maxkey, struct mfutex_tree_minmax *__restrict result);



struct mpartmeta {
	struct atomic_rwlock              mpm_ftxlock;  /* Lock for `mpm_ftx' */
	LLRBTREE_ROOT(WEAK struct mfutex) mpm_ftx;      /* [0..n][lock(mpm_ftx)] Futex tree.
	                                                 * NOTE: May contain dead futex objects! */
	struct WEAK mfutex_slist          mpm_ftx_dead; /* [0..n][lock(ATOMIC)] Chain of dead futex objects. */
#ifdef ARCH_VM_HAVE_RTM
	/* We keep the RTM version and field in the futex controller, such that
	 * they don't take up space in the base `mpart' structure, but only exist
	 * conditionally, and upon first access. */
	uintptr_t                         mpm_rtm_vers; /* [lock(:dp_lock)]
	                                                 * RTM version (incremented for every RTM-driven
	                                                 * modifications made to memory). */
#endif /* ARCH_VM_HAVE_RTM */
};

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpartmeta_destroy)(struct mpartmeta *__restrict self);


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


/* Lock accessor helpers for `struct mfile' */
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




DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MMETA_H */
