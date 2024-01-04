/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILEMETA_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILEMETA_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>

#include <hybrid/sched/atomic-lock.h>

#include <asm/os/fcntl.h>
#include <kos/sched/shared-rwlock.h>

#include <libc/string.h>

/* Shared lock. */
#ifndef LOCK_SH
#define LOCK_SH __LOCK_SH
#endif /* !LOCK_SH */

/* Exclusive lock. */
#ifndef LOCK_EX
#define LOCK_EX __LOCK_EX
#endif /* !LOCK_EX */

/* Or'd with one of the above to prevent blocking. */
#ifndef LOCK_NB
#define LOCK_NB __LOCK_NB
#endif /* !LOCK_NB */

/* Remove lock. */
#ifndef LOCK_UN
#define LOCK_UN __LOCK_UN
#endif /* !LOCK_UN */

#ifdef __CC__
DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
struct inotify_controller;
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */


/************************************************************************/
/* FLOCK(2) SUPPORT                                                     */
/************************************************************************/

/* BRIEF
 *    flock() works such that each `struct filehandle' can hold up to 1
 *    lock  descriptor for its  associated file, that  is then either a
 *    shared or exclusive (or none) flock-style lock for the file (when
 *    the  file descriptor  is closed,  any lock  held is automatically
 *    released). */



/* In order to identify read/write-lock holders, we use pointers
 * to the linked file handles. That way, file handles don't even
 * need to know if they're holding locks (they only need to  try
 * to release a lock linked to their self-pointer on destroy).
 *
 * Note that while holding an flock file lock, the linked mfile
 * must NOT be destroyed! */
struct filehandle;
typedef struct filehandle *mfile_flock_key_t;

/* >> mfile_flock_key_t filehandle_get_flock_key(struct filehandle *self); */
#define filehandle_get_flock_key(self) (self)

/* Calculate the hash of an flock key (as used for locating the
 * key in the mfile's flock hash-vector). */
#define mfile_flock_key_gethash(self) (((uintptr_t)(self)) >> 6)

/* Special mfile flock keys. */
#define MFILE_FLOCK_KEY_SENTINEL ((mfile_flock_key_t)0)   /* Sentinel key (marks end of a hash-chain) */
#define MFILE_FLOCK_KEY_DELETED  ((mfile_flock_key_t)-1)  /* Deleted key (marks ignored slots in a hash-chain) */
#define MFILE_FLOCK_KEY_NONE     MFILE_FLOCK_KEY_SENTINEL /* A special key that can never be used. */

struct mfile_flock_rl_item {
	mfile_flock_key_t mfflri_key; /* Key of this item. */
};

struct mfile_flock {
	struct shared_rwlock        mffl_flock;   /* The actual flock R/W-lock. */
#ifndef CONFIG_NO_SMP
	struct atomic_lock          mffl_klock;   /* SMP-Lock for the state of keys. */
#endif /* !CONFIG_NO_SMP */
	mfile_flock_key_t           mffl_wr_key;  /* [lock(mffl_klock)] Key that owns the write-lock  (or
	                                           * `MFILE_FLOCK_KEY_NONE' when there is no write-lock). */
	/* Everything below may only be used while:
	 * - Holding a read-lock to `mffl_flock'   (when this is not held, everything below must be NULL/0)
	 * - Holding an SMP-lock to `mffl_klock' (i.e. preemption is disabled) */
	size_t                      mffl_rl_mask; /* [lock(mffl_klock)][> mffl_rl_size || mffl_rl_mask == 0] Allocated set size minus 1. */
	size_t                      mffl_rl_size; /* [lock(mffl_klock)][< mffl_rl_mask || mffl_rl_mask == 0] Amount of non-MFILE_FLOCK_KEY_SENTINEL keys. */
	size_t                      mffl_rl_used; /* [lock(mffl_klock)][<= mffl_rl_size] Amount of non-MFILE_FLOCK_KEY_DELETED/MFILE_FLOCK_KEY_SENTINEL keys. */
	struct mfile_flock_rl_item *mffl_rl_elem; /* [lock(mffl_klock)][0..mffl_rl_size|ALLOC(mffl_rl_mask+1)] Hash-vector. */
};

#ifndef CONFIG_NO_SMP
#define _mfile_flock_cinit__mffl_klock_(self) atomic_lock_cinit(&(self)->mffl_klock),
#else /* !CONFIG_NO_SMP */
#define _mfile_flock_cinit__mffl_klock_(self) /* nothing */
#endif /* CONFIG_NO_SMP */
#define mfile_flock_cinit(self)            \
	(_mfile_flock_cinit__mffl_klock_(self) \
	 shared_rwlock_cinit(&(self)->mffl_flock))

#define mfile_flock_klock_acquire(self)    atomic_lock_acquire_smp(&(self)->mffl_klock)
#define mfile_flock_klock_release(self)    atomic_lock_release_smp(&(self)->mffl_klock)
#define mfile_flock_klock_acquire_br(self) atomic_lock_acquire_smp_b(&(self)->mffl_klock)
#define mfile_flock_klock_release_br(self) atomic_lock_release_smp_b(&(self)->mffl_klock)

#define mfile_flock_rl_hashst(self, hash)  ((hash) & (self)->mffl_rl_mask)
#define mfile_flock_rl_hashnx(hs, perturb) (void)((hs) = ((hs) << 2) + (hs) + (perturb) + 1, (perturb) >>= 5) /* This `5' is tunable. */
#define mfile_flock_rl_hashit(self, i)     ((self)->mffl_rl_elem + ((i) & (self)->mffl_rl_mask))


/* Acquire an flock-based lock to `self'. Note that an existing lock for `key'
 * is  always overwritten (when one already exists), and that if a lock of the
 * same type already exists for `key', the call is a no-op.
 * @param: self: The file on which to acquire the lock
 * @param: how:  One of `LOCK_SH', `LOCK_EX', optionally or'd with `LOCK_NB'
 * @param: key:  Lock key (needs to be passed to `mfile_flock_release')
 * @throws: E_WOULDBLOCK: The operation would block, and `LOCK_NB' was given
 * @throws: E_INTERRUPT:  [...]
 * @throws: E_BADALLOC:   [...]
 * @throws: E_INVALID_ARGUMENT_UNKNOWN_COMMAND:E_INVALID_ARGUMENT_CONTEXT_FLOCK_COMMAND: [...] */
FUNDEF BLOCKING_IF(!(how & LOCK_NB)) NONNULL((1)) void FCALL
mfile_flock_acquire(struct mfile *__restrict self,
                    syscall_ulong_t how,
                    mfile_flock_key_t key)
		THROWS(E_WOULDBLOCK, E_INTERRUPT, E_BADALLOC,
		       E_INVALID_ARGUMENT_UNKNOWN_COMMAND);

/* Release an flock-based lock to `self'.
 * @return: true:  Lock was released
 * @return: false: No lock exists for `key' (note that this is a no-op in `LOCK_UN') */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL mfile_flock_release)(struct mfile *__restrict self,
                                   mfile_flock_key_t key);

/* High-level wrapper to facilitate `flock(2)' operations on a given `struct mfile *self'
 * @param: key: The key to which this operation is bound (should be `filehandle_get_flock_key(...)') */
#define mfile_flock(self, operation, key)                          \
	((operation) == LOCK_UN ? (void)mfile_flock_release(self, key) \
	                        : (void)mfile_flock_acquire(self, operation, key))

/* Same  as `mfile_flock_release()',  but do some  inline checks to  optimize for the
 * case where no lock matching `key' exists (meaning that `false' should be returned)
 *
 * This version of the call shold be made from `filehandle_destroy()', as the most
 * common case is  that no  flock-based lock was  being held  by the  file-handle. */
#ifdef __OPTIMIZE_SIZE__
#define mfile_flock_release_expecting_nolock(self, key) mfile_flock_release(self, key)
#else /* __OPTIMIZE_SIZE__ */
#define mfile_flock_release_expecting_nolock(self, key)                                     \
	__XBLOCK({                                                                              \
		struct mfilemeta *_mfflr_meta = __hybrid_atomic_load(&(self)->mf_meta,              \
		                                                     __ATOMIC_ACQUIRE);             \
		__XRETURN(unlikely(_mfflr_meta != __NULLPTR &&                                      \
		                   __hybrid_atomic_load(&_mfflr_meta->mfm_flock.mffl_flock.sl_lock, \
		                                        __ATOMIC_ACQUIRE) != 0) &&                  \
		          mfile_flock_release(self, key));                                          \
	})
#endif /* !__OPTIMIZE_SIZE__ */






/* mfile-metadata controller.
 *
 * Used to store volatile metadata components surrounding `struct mfile' that
 * are too rarely used to justify putting them into the base mfile structure.
 *
 * This includes:
 * - inotify controllers (as used for monitoring files for changes)
 * - user-space file locks (as used by `flock(2)')
 * - ...
 */
struct mfilemeta {
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	struct inotify_controller *mfm_notify; /* [0..1][owned][lock(!PREEMPTION && :notify_lock)] Notify controller. */
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	struct mfile_flock         mfm_flock;  /* Controller for flock(2)-based locks. */
};

#define mfilemeta_alloc()          (struct mfilemeta *)kmalloc(sizeof(struct mfilemeta), GFP_NORMAL)
#define mfilemeta_free(self)       kfree(self)
#define mfilemeta_xfree(self)      kfree(self)
#define mfilemeta_init(self, file)                 \
	(__libc_bzero(self, sizeof(struct mfilemeta)), \
	 mfile_flock_cinit(&(self)->mfm_flock))

/* Destroy the given mfile meta-data `self' that was originally allocated & initialized for `file' */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfilemeta_destroy)(struct mfilemeta *self, struct mfile *file);

/* When this is defined, `mfilemeta_destroy()' can be replaced with `mfilemeta_free()',
 * even after `mfilemeta_init()'  was called,  so-long as the  mfilemeta object  hadn't
 * actually been installed into the associated file. */
#define MFILEMETA_DESTROY_MAYOMIT_AFTER_FRESH_INIT

/* Ensure that `self->mf_meta' has been allocated, which is then returned. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct mfilemeta *FCALL
mfile_getmeta(struct mfile *__restrict self) THROWS(E_BADALLOC);


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MFILEMETA_H */
