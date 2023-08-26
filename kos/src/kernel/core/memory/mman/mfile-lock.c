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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_LOCK_C 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/ramfs.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <misc/unlockinfo.h>
#include <sched/cred.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>

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

/* release locks and decref() an entire mem-part tree. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_unlock_and_decref_whole_tree)(REF struct mpart *__restrict self) {
	struct mpart *lhs, *rhs;
again:
	lhs = self->mp_filent.rb_lhs;
	rhs = self->mp_filent.rb_rhs;
	mpart_lock_release(self);
	decref_unlikely(self);
	if (lhs) {
		if (rhs)
			mpart_unlock_and_decref_whole_tree(rhs);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}


/* Try to acquire locks and references  to all mem-parts reachable from  `self'.
 * If a mem-part is encountered that has been destroyed, return a pointer to it.
 * If a part  is encountered that  cannot be locked  immediately, also return  a
 * pointer to it. Otherwise, return  `NULL' (references+locks are only  acquired
 * when this function returns `NULL', making that the success-return-value) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL mpart_incref_and_tree_trylock_whole_tree)(struct mpart *__restrict self) {
	struct mpart *result;
	struct mpart *lhs, *rhs;
	lhs = self->mp_filent.rb_lhs;
	rhs = self->mp_filent.rb_rhs;
	if unlikely(!tryincref(self))
		return self; /* Destroyed mem-part. */
	if (!mpart_lock_tryacquire(self)) {
		decref_unlikely(self);
		return self; /* Blocking mem-part. */
	}

	/* Recursion... */
	if (lhs) {
		result = mpart_incref_and_tree_trylock_whole_tree(lhs);
		if unlikely(result != NULL)
			goto err;
	}
	if (rhs) {
		result = mpart_incref_and_tree_trylock_whole_tree(rhs);
		if unlikely(result != NULL)
			goto err;
	}
	return NULL;
err:
	mpart_lock_release(self);
	decref_unlikely(self);
	return result;
}


/* Same  as  `mfile_incref_and_lock_parts_or_unlock()', but  return a
 * reference to the blocking part (if any), and not release any locks
 * other than those to mem-parts that could be locked before the part
 * that is blocking was encountered:
 * - Try to acquire references and locks to an entire part tree. When
 *   there is some part to which no lock can be acquired immediately,
 *   return a reference to said part.
 * - When this function returns `NULL', locks+references have been acquired. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct mpart *
NOTHROW(FCALL mfile_tryincref_and_lock_parts)(struct mfile *__restrict self) {
	REF struct mpart *result;
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
again:
	result = self->mf_parts;
	if (result) {
		result = mpart_incref_and_tree_trylock_whole_tree(result);
		if (result) {
			/* Either remove a  dead mem-part,  or return  a
			 * reference to one which is currently blocking. */
			assert(result->mp_file == self);
			if (tryincref(result)) {
				/* Blocking part. */
			} else {
				/* Dead mem-part. (remove from tree) */
				mpart_tree_removenode(&self->mf_parts, result);
				DBG_memset(&result->mp_filent.rb_lhs, 0xcc, sizeof(result->mp_filent.rb_lhs));
				result->mp_filent.rb_rhs = NULL; /* Indicator for `mpart_trim()' */
				atomic_write(&result->mp_filent.rb_par, (struct mpart *)-1);
				goto again;
			}
		}
	}
	return result;
}

/* Do the inverse of `mfile_incref_and_lock_parts_or_unlock()' and
 * release locks+references to parts of `self'. NOTE: The lock  to
 * `self' is _NOT_ released during this! */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_unlock_and_decref_parts)(struct mfile *__restrict self) {
	assert(mfile_lock_reading(self));
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	if (self->mf_parts)
		mpart_unlock_and_decref_whole_tree(self->mf_parts);
}


/* release locks and decref() an entire mem-part tree. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_unlock_and_decref_whole_tree_except)(REF struct mpart *__restrict self,
                                                         struct mpart *__restrict keepme) {
	struct mpart *lhs, *rhs;
again:
	lhs = self->mp_filent.rb_lhs;
	rhs = self->mp_filent.rb_rhs;
	if (self != keepme) {
		mpart_lock_release(self);
		decref_unlikely(self);
	}
	if (lhs) {
		if (rhs)
			mpart_unlock_and_decref_whole_tree_except(rhs, keepme);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

/* Same as `mfile_unlock_and_decref_parts()', but keep a lock & reference to `part' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_unlock_and_decref_parts_except)(struct mfile *__restrict self,
                                                    struct mpart *__restrict part) {
	assert(self->mf_parts != NULL);
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	mpart_unlock_and_decref_whole_tree_except(self->mf_parts, part);
}



/* Acquire locks to all of the mem-parts associated with a given mfile.
 * - The caller must be holding a write-lock to `self' and must ensure
 *   that `self' isn't anonymous.
 * - Acquire  references to  all parts of  `self'. If any  one of these
 *   cannot be acquired due to some part already having been destroyed,
 *   remove the offending part from the part-tree and mark it as  anon.
 * - Afterwards, try to acquire a lock to each of the parts. If  this
 *   fails, release locks from all  already-locked parts, as well  as
 *   the write-lock to `self' and `unlock'. Then wait for the lock to
 *   the blocking part to become available and return `false'
 * - If all locks could be acquired, return `true'
 * @return: true:  Locks+references acquired.
 * @return: false: All locks were locks; try again. */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
mfile_incref_and_lock_parts_or_unlock(struct mfile *__restrict self,
                                      struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK) {
	REF struct mpart *blocking_part;
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	blocking_part = mfile_tryincref_and_lock_parts(self);
	if unlikely(blocking_part) {
		mfile_lock_endwrite(self);
		unlockinfo_xunlock(unlock);
		FINALLY_DECREF_UNLIKELY(blocking_part);
		mpart_lock_waitfor(blocking_part);
		return false;
	}
	return true;
}



/* Same as `mfile_incref_and_lock_parts_or_unlock()', but
 * assert `mpart_denywrite_or_unlock()'  for  all  parts.
 *
 * Should be used if the caller intends to set `MFILE_F_READONLY' */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
mfile_incref_and_lock_parts_and_denywrite_or_unlock(struct mfile *__restrict self,
                                                    struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY) {

	/* Acquire locks. */
	if (!mfile_incref_and_lock_parts_or_unlock(self, unlock))
		return false;

	/* Deny write access to memory mappings. */
	if (!mfile_parts_denywrite_or_unlock(self, unlock))
		return false;
	return true;
}



struct unlock_whole_tree_except: unlockinfo {
	struct mfile      *uwte_file;   /* [1..1] File to unlock */
	struct mpart      *uwte_except; /* [1..1] Don't unlock this part */
	struct unlockinfo *uwte_inner;  /* [0..1] Inner unlock info */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unlock_whole_tree_except_cb)(struct unlockinfo *__restrict self) {
	struct unlock_whole_tree_except *me;
	me = (struct unlock_whole_tree_except *)self;

	/* Release part locks and references (except those for held for `uwte_except') */
	mfile_unlock_and_decref_parts_except(me->uwte_file, me->uwte_except);

	/* Release our lock to the file. */
	mfile_lock_endwrite(me->uwte_file);

	/* If defined, release more locks possibly held by the caller. */
	unlockinfo_xunlock(me->uwte_inner);
}



PRIVATE WUNUSED NONNULL((1, 2)) bool FCALL
mfile_parts_denywrite_or_unlock_impl(struct mfile *__restrict file,
                                     struct mpart *__restrict self,
                                     struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY) {
	struct unlock_whole_tree_except ul;
again:
	/* Setup a custom unlock controller. */
	ul.ui_unlock   = &unlock_whole_tree_except_cb;
	ul.uwte_except = self;
	ul.uwte_file   = file;
	ul.uwte_inner  = unlock;
	TRY {
		/* Deny write access to mappings of this part. */
		if (!mpart_denywrite_or_unlock(self, &ul)) {
			/* Locks were lost :( */
			assert(ul.uwte_except == self);
			decref_unlikely(ul.uwte_except); /* This ref was skipped by `mfile_unlock_and_decref_parts_except' */
			return false;
		}
	} EXCEPT {
		/* Locks were also lost in this case! */
		assert(ul.uwte_except == self);
		decref_unlikely(ul.uwte_except); /* This ref was skipped by `mfile_unlock_and_decref_parts_except' */
		RETHROW();
	}

	/* Recursion... */
	if (self->mp_filent.rb_lhs) {
		if (self->mp_filent.rb_rhs) {
			if (!mfile_parts_denywrite_or_unlock_impl(file, self->mp_filent.rb_rhs, unlock))
				return false;
		}
		self = self->mp_filent.rb_lhs;
		goto again;
	}
	if (self->mp_filent.rb_rhs) {
		self = self->mp_filent.rb_rhs;
		goto again;
	}
	return true;
}

/* Deny  write  access  to anyone  currently  mapping any  part  of `self'.
 * The caller must be holding a write-lock to `self', as well as individual
 * locks to every part associated with it, as well as be holding references
 * to all of the parts of `self' (`mfile_incref_and_lock_parts_or_unlock').
 *
 * @return: true:  Success: write access has been denied to all parts.
 * @return: false: Locks were lost and you must try again.
 *
 * Locking logic:
 *   - return == true:  No locks are lost, and no locks are gained
 *   - return == false: - mfile_unlock_and_decref_parts(self);
 *                      - mfile_lock_endwrite(unlock);
 *                      - unlockinfo_xunlock(unlock);
 *   - THROW:           like `return == false' */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
mfile_parts_denywrite_or_unlock(struct mfile *__restrict self,
                                struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY) {
	assert(self->mf_parts != MFILE_PARTS_ANONYMOUS);
	if (self->mf_parts == NULL)
		return true; /* Nothing to do here :) */
	return mfile_parts_denywrite_or_unlock_impl(self, self->mf_parts, unlock);
}




/* Alter  flags  of `self'  like `self->mf_flags = (self->mf_flags & mask) | flags'
 * Special care is taken to ensure that the transformation is performed atomically,
 * and that `MFILE_F_READONLY' is only  altered while holding the necessary  locks,
 * including a preceding denywrite when it is set.
 * @param: mask:  Inverted set of flags, as accepted by `flags'
 * @param: flags: Set of `MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOUSRMMAP |
 *                        MFILE_F_NOUSRIO | MFILE_F_NOMTIME | MFILE_FN_ATTRREADONLY |
 *                        MFILE_F_RELATIME | MFILE_F_STRICTATIME |  MFILE_F_LAZYTIME'
 * @param: check_permissions: When true, ensure that the caller is allowed to alter
 *                            flags in the requested manner.
 * @return: * : The old set of file flags.
 * @throw: E_ILLEGAL_OPERATION:E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS: [...] */
PUBLIC NONNULL((1)) uintptr_t FCALL
mfile_chflags(struct mfile *__restrict self, uintptr_t mask,
              uintptr_t flags, bool check_permissions)
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY,
		       E_INSUFFICIENT_RIGHTS, E_ILLEGAL_OPERATION) {
#define MODIFIABLE_FLAGS                                         \
	(MFILE_F_READONLY | MFILE_F_NOATIME | MFILE_F_NOUSRMMAP |    \
	 MFILE_F_NOUSRIO | MFILE_F_NOMTIME | MFILE_FN_ATTRREADONLY | \
	 MFILE_F_RELATIME | MFILE_F_STRICTATIME | MFILE_F_LAZYTIME)
	bool cmpxch_ok;
	uintptr_t old_flags, new_flags;
	/* Ensure that only certain flags will be modified. */
	assert((~mask & ~MODIFIABLE_FLAGS) == 0);
	assert((flags & ~MODIFIABLE_FLAGS) == 0);
again:
	do {
		mfile_lock_write(self);
		old_flags = atomic_read(&self->mf_flags);
		new_flags = (old_flags & mask) | flags;

		/* Make sure that read-only flags aren't altered when ROFLAGS was set. */
		if unlikely((old_flags & MFILE_F_ROFLAGS) &&
		            (old_flags & _MFILE_F_ROFLAGSMASK) != (new_flags & _MFILE_F_ROFLAGSMASK)) {
			mfile_lock_endwrite(self);
			THROW(E_ILLEGAL_OPERATION,
			      E_ILLEGAL_OPERATION_CONTEXT_READONLY_FILE_FLAGS,
			      old_flags, new_flags);
		}

		/* Check if the READONLY flag changed state. */
		if ((new_flags & MFILE_F_READONLY) != (old_flags & MFILE_F_READONLY)) {

			/* Need CAP_SYS_ADMIN to change READONLY for device files. (s.a. `BLKROSET') */
			if (check_permissions && mfile_isdevice(self) && !capable(CAP_SYS_ADMIN)) {
				mfile_lock_endwrite(self);
				THROW(E_INSUFFICIENT_RIGHTS, CAP_SYS_ADMIN);
			}

			/* Need locks to all of the file's mem-parts to change `MFILE_F_READONLY'. */
			if (self->mf_parts != MFILE_PARTS_ANONYMOUS) {
				if (!mfile_incref_and_lock_parts_or_unlock(self, NULL))
					goto again;

				/* When the READONLY flag is set, then we must also deny write access
				 * to  anyone who may currently be holding PROT_WRITE mappings to the
				 * affected address range. */
				if ((new_flags & MFILE_F_READONLY) &&
				    !mfile_parts_denywrite_or_unlock(self, NULL))
					goto again;
			}
		}

		/* As per the specs, in order to change the flags of a file, you must
		 * be that file's owner, or have the `CAP_FOWNER' capability. Because
		 * we allow this operator for mfiles that don't have owners, we  only
		 * do this check if the file _does_ have an owner!
		 *
		 * NOTE: Just so we don't ever run into problems with `BLKROSET',
		 *       we also accept CAP_SYS_ADMIN here if `self' is a device.
		 */
		if (check_permissions && old_flags != new_flags && mfile_isnode(self)) {
			if (fnode_getuid(mfile_asnode(self)) == cred_geteuid() ||
			    capable(CAP_FOWNER) ||
			    (capable(CAP_SYS_ADMIN) && mfile_isdevice(self))) {
				/* Allowed! */
			} else {
				/* Not allowed! */
				if (self->mf_parts != MFILE_PARTS_ANONYMOUS &&
				    (new_flags & MFILE_F_READONLY) != (old_flags & MFILE_F_READONLY))
					mfile_unlock_and_decref_parts(self);
				mfile_lock_endwrite(self);
				THROW(E_INSUFFICIENT_RIGHTS, CAP_FOWNER);
			}
		}

		/* Try to atomically apply the new set of flags. */
		cmpxch_ok = atomic_cmpxch(&self->mf_flags, old_flags, new_flags);

		/* Release locks */
		if (self->mf_parts != MFILE_PARTS_ANONYMOUS &&
		    (new_flags & MFILE_F_READONLY) != (old_flags & MFILE_F_READONLY))
			mfile_unlock_and_decref_parts(self);
		mfile_lock_endwrite(self);
	} while (!cmpxch_ok);
	return old_flags;
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_LOCK_C */
