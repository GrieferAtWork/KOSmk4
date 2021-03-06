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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C 1
#define __WANT_MPART__mp_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <sched/lockop.h>
#include <sched/signal-completion.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef NDEBUG
#define DBG_memset(dst, byte, num_bytes) memset(dst, byte, num_bytes)
#else /* !NDEBUG */
#define DBG_memset(dst, byte, num_bytes) (void)0
#endif /* NDEBUG */


#ifdef CONFIG_USE_NEW_FS

union mpart_delete_postop {
	/* NOTE: The list of more parts that must be destroyed is chained via `_mp_dead' */
	Tobpostlockop(mfile) mdp_fop;
	Tobpostlockop(mpart) mdp_pop;
};
STATIC_ASSERT(sizeof(union mpart_delete_postop) <=
              (offsetafter(struct mpart, mp_share) -
               offsetof(struct mpart, mp_copy)));
STATIC_ASSERT(offsetof(Tobpostlockop(mfile), oplo_func) ==
              offsetof(Tobpostlockop(mpart), oplo_func));
#define mpart_as_mpart_delete_postop(self)   ((union mpart_delete_postop *)&(self)->mp_copy)
#define mpart_from_mpart_delete_postop(self) ((struct mpart *)((byte_t *)&(self)->mdp_fop - offsetof(struct mpart, mp_copy)))

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_delete_postop_cb)(union mpart_delete_postop *__restrict self,
                                      void *__restrict UNUSED(unused)) {
	struct mpart *chain, *next;
	DBG_memset(self, 0xcc, sizeof(*self));
	chain = mpart_from_mpart_delete_postop(self);
	do {
		next = chain->_mp_dead.sle_next;
		DBG_memset(&chain->_mp_dead, 0xcc, sizeof(chain->_mp_dead));
		mpart_destroy(chain);
		chain = next;
	} while (chain);
}


struct mpart_delete_postop_builder {
	struct mpart *mdpb_delme; /* [0..1] First part that should be deleted. */
};
#define mpart_delete_postop_builder_init(self)    ((self)->mdpb_delme = NULL)
#define mpart_delete_postop_builder_isempty(self) ((self)->mdpb_delme == NULL)
#define mpart_delete_postop_builder_asfop(self)   (&mpart_as_mpart_delete_postop((self)->mdpb_delme)->mdp_fop)
#define mpart_delete_postop_builder_aspop(self)   (&mpart_as_mpart_delete_postop((self)->mdpb_delme)->mdp_pop)

/* Enqueue a given mem-part `delme' on which to call `mpart_destroy()' from  within
 * the post-op that can be constructed with `mpart_delete_postop_builder_as(f|p)op' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_delete_postop_builder_enqueue)(struct mpart_delete_postop_builder *__restrict self,
                                                   struct mpart *__restrict delme) {
	struct mpart *primary = self->mdpb_delme;
	if (primary == NULL) {
		union mpart_delete_postop *pop;
		pop = mpart_as_mpart_delete_postop(delme);
		pop->mdp_fop.oplo_func  = (Tobpostlockop_callback_t(mfile))&mpart_delete_postop_cb;
		delme->_mp_dead.sle_next = NULL;
		self->mdpb_delme         = delme;
	} else {
		delme->_mp_dead.sle_next   = primary->_mp_dead.sle_next;
		primary->_mp_dead.sle_next = delme;
	}
}




/* These are the offsets and  total size of the lockop-workspace  area
 * within a `struct mfile' after the DELETED and NOATIME|NOMTIME flags
 * have all been set. */
#define MFILE_LOCKOPS_SPACE_OFFS offsetof(struct mfile, mf_atime)
#define MFILE_LOCKOPS_SPACE_SIZE (offsetafter(struct mfile, mf_ctime) - MFILE_LOCKOPS_SPACE_OFFS)

union mflops {
	Toblockop(mfile)         mfl_flop;      /* mem-file lock operation */
	Toblockop(mpart)             mfl_plop;      /* mem-part lock operation */
	struct {
		Tobpostlockop(mfile) mfl_fplop;     /* mem-file post-lock operation */
		struct mpart_slist          mfl_deadparts; /* Only used by `mfile_decref_and_destroy_deadparts_postop' */
	};
	Tobpostlockop(mpart)         mfl_pplop;     /* mem-part post-lock operation */
	struct sig_completion           mfl_compl;     /* Signal completion callback. (used for waiting on `mf_trunclock') */
};

STATIC_ASSERT(sizeof(union mflops) <= MFILE_LOCKOPS_SPACE_SIZE);

/* Helper macros to convert an mfile to/from various different types of lockop descriptors. */
#ifdef __INTELLISENSE__
#define mfile_as_mflops(self)   ((union mflops *)((byte_t *)&(self)->mf_refcnt + MFILE_LOCKOPS_SPACE_OFFS))
#define mfile_from_mflops(self) ((struct mfile *)((byte_t *)&(self)->mfl_flop - MFILE_LOCKOPS_SPACE_OFFS))
#else /* __INTELLISENSE__ */
#define mfile_as_mflops(self)   ((union mflops *)((byte_t *)(self) + MFILE_LOCKOPS_SPACE_OFFS))
#define mfile_from_mflops(self) ((struct mfile *)((byte_t *)(self) - MFILE_LOCKOPS_SPACE_OFFS))
#endif /* !__INTELLISENSE__ */

/* Try to acquire a reference to all parts reachable from `root'.
 * Parts  that  had  already  been  destroyed  will  be  skipped. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL mpart_tree_increfall)(struct mpart *__restrict root) {
again:
	COMPILER_UNUSED(tryincref(root));
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_increfall(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

/* Drop a reference from all parts reachable from `root'. If a
 * part  ends up dying because of this, add it to `deadparts'.
 * Parts that had already been destroyed will be skipped. */
PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL mpart_tree_decrefall)(struct mpart *__restrict root,
                                    struct mpart_delete_postop_builder *__restrict deadparts) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if (!wasdestroyed(root)) {
		if (ATOMIC_DECFETCH(root->mp_refcnt) == 0)
			mpart_delete_postop_builder_enqueue(deadparts, root);
	}
	if (lhs) {
		if (rhs)
			mpart_tree_increfall(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Release locks to all parts reachable from `root', with the exception
 * of `skipme'  (if non-NULL),  from which  no lock  will be  released.
 * Parts that had already been destroyed will be skipped. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL mpart_tree_unlockall)(struct mpart *root,
                                    struct mpart *skipme) {
again:
	if (root != skipme && !wasdestroyed(root))
		mpart_lock_release(root);
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_increfall(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

/* Try  to  acquire locks  to all  parts reachable  from `root',  with the
 * exception of `skipme' (if non-NULL), to which no lock will be acquired.
 * It  at least  one part can't  be locked immediately,  release all locks
 * already  acquired,  and  return  a   pointer  to  the  blocking   part.
 * Parts that had already been destroyed will be skipped. */
PRIVATE WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL mpart_tree_trylockall)(struct mpart *root,
                                     struct mpart *skipme) {
	struct mpart *error;
	if (root != skipme && !wasdestroyed(root)) {
		if (!mpart_lock_tryacquire(root))
			return root;
	}
	if (root->mp_filent.rb_lhs) {
		error = mpart_tree_trylockall(root->mp_filent.rb_lhs, skipme);
		if unlikely(error != NULL)
			goto err_root;
	}
	if (root->mp_filent.rb_rhs) {
		error = mpart_tree_trylockall(root->mp_filent.rb_rhs, skipme);
		if unlikely(error != NULL)
			goto err_root_lhs;
	}
	return NULL;
err_root_lhs:
	if (root->mp_filent.rb_lhs)
		mpart_tree_unlockall(root->mp_filent.rb_lhs, skipme);
err_root:
	if (root != skipme && !wasdestroyed(root))
		mpart_lock_release(root);
	return error;
}


/* For all non-destroyed parts reachable from `root', mark then as anon,
 * change their file field from  `file' to `mfile_anon[*]', clear  their
 * `MPART_F_GLOBAL_REF'  flag, and (if different from `dont_unlock_me'),
 * release a lock to them. */
PRIVATE NONNULL((1, 3)) void
NOTHROW(FCALL mpart_tree_forall_makeanon_and_unlock_decref)(struct mpart *root,
                                                            struct mpart *dont_unlock_me,
                                                            struct mfile *__restrict file,
                                                            struct mpart_delete_postop_builder *__restrict deadparts) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if (!wasdestroyed(root)) {
		REF struct mfile *newfile;
		_mpart_init_asanon(root);
		assert(root->mp_file == file);
		newfile = incref(&mfile_anon[file->mf_blockshift]);
		ATOMIC_WRITE(root->mp_file, newfile);
		decref_nokill(file);
		if (ATOMIC_FETCHAND(root->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
			decref_nokill(root);
		/* Try to merge mem-parts after changing the pointed-to file.
		 * This  must be done to prevent a race condition relating to
		 * some very rare cases of async mem-part merging, as well as
		 * to ensure consistency,  and to allow  merging of  adjacent
		 * nodes within mman mapping trees. */
		root = mpart_merge_locked(root);
		mpart_lock_release(root);
		if (ATOMIC_DECFETCH(root->mp_refcnt) == 0)
			mpart_delete_postop_builder_enqueue(deadparts, root);

	}
	if (lhs != NULL) {
		if (rhs != NULL)
			mpart_tree_forall_makeanon_and_unlock_decref(rhs, dont_unlock_me, file, deadparts);
		root = lhs;
		goto again;
	}
	if (rhs != NULL) {
		root = rhs;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mfile) *
NOTHROW(FCALL mfile_delete_withfilelock_ex)(REF struct mfile *__restrict file,
                                            struct mpart *already_locked_part);
PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mfile) *
NOTHROW(FCALL mfile_delete_withfilelock)(Toblockop(mfile) *__restrict self,
                                         REF struct mfile *__restrict file);

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(FCALL mfile_delete_withpartlock)(Toblockop(mpart) *__restrict self,
                                         struct mpart *__restrict part) {
	union mflops *mfl;
	REF struct mfile *file;
	mfl  = container_of(self, union mflops, mfl_plop);
	file = mfile_from_mflops(mfl);
	/* Also try to acquire a lock to the file. */
	if (mfile_lock_trywrite(file)) {
		Tobpostlockop(mfile) *pop;
		/* Try to delete the file, but remember that we're already holding a lock to `part'! */
		pop = mfile_delete_withfilelock_ex(file, part);
		mfile_lock_endwrite(file);
		if (pop == NULL)
			return NULL;
		assert(pop->oplo_func == (Tobpostlockop_callback_t(mfile))&mpart_delete_postop_cb ||
		       pop->oplo_func == &mfile_decref_and_destroy_deadparts_postop ||
		       pop->oplo_func == &mfile_decref_postop);
		/* NOTE: None of the possible callback ever make use of the `file' argument  of
		 *       the post-operation callback, meaning that we can simply cast the mfile
		 *       post-operation into an mpart post-operation! */
		return (Tobpostlockop(mpart) *)pop;
	}
	/* Bounce back a lock-operation for `file'
	 * Use `mfile_delete_withfilelock' for this purpose! */
	mfl->mfl_flop.olo_func = &mfile_delete_withfilelock;
	SLIST_ATOMIC_INSERT(&file->mf_lockops, &mfl->mfl_flop, olo_link);
	_mfile_lockops_reap(file);
	return NULL;
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_decref_and_destroy_deadparts_postop)(Tobpostlockop(mfile) *__restrict self,
                                                         struct mfile *__restrict UNUSED(_file)) {
	union mflops *mfl;
	REF struct mfile *file;
	struct mpart_slist deadparts;
	mfl       = container_of(self, union mflops, mfl_fplop);
	file      = mfile_from_mflops(mfl);
	deadparts = mfl->mfl_deadparts;
	DBG_memset(mfl, 0xcc, sizeof(*mfl));

	/* Destroy all dead parts. */
	while (!SLIST_EMPTY(&deadparts)) {
		struct mpart *part;
		part = SLIST_FIRST(&deadparts);
		SLIST_REMOVE_HEAD(&deadparts, _mp_dead);
		mpart_destroy(part);
	}

	/* Drop the inherited reference to the original file. */
	decref_unlikely(file);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_decref_postop)(Tobpostlockop(mfile) *__restrict self,
                                   struct mfile *__restrict UNUSED(_file)) {
	union mflops *mfl;
	REF struct mfile *file;
	mfl  = container_of(self, union mflops, mfl_fplop);
	file = mfile_from_mflops(mfl);
	decref_unlikely(file);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_begin_async_delete)(/*inherit(always)*/ REF struct mfile *__restrict self);

PRIVATE NOBLOCK void
NOTHROW(FCALL mfile_zerotrunc_completion2_cb)(struct sig_completion_context *__restrict UNUSED(context),
                                              void *buf) {
	REF struct mfile *file;
	file = *(REF struct mfile **)buf;
	/* Re-start async file deletion from scratch, since
	 * we're  not actually holding any locks right now! */
	mfile_begin_async_delete(file);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL mfile_zerotrunc_completion_cb)(struct sig_completion *__restrict self,
                                             struct sig_completion_context *__restrict context,
                                             void *buf, size_t bufsize) {
	union mflops *mfl;
	REF struct mfile *file;
	mfl  = container_of(self, union mflops, mfl_compl);
	file = mfile_from_mflops(mfl);

	/* Check if the trunc-lock has been released... */
	if (ATOMIC_READ(file->mf_trunclock) != 0) {
		sig_completion_reprime(self, true);
		return 0;
	}

	/* All right! - Time to do this.
	 * Note however that we must do the actual work in a phase-2 completion
	 * callback,   since   deletion   of   a   file   isn't  SMP-lock-safe! */
	if (bufsize < sizeof(REF struct mfile *))
		return sizeof(REF struct mfile *);
	*(REF struct mfile **)buf = file; /* Inherited by `mfile_zerotrunc_completion2_cb()' */
	context->scc_post         = &mfile_zerotrunc_completion2_cb;
	return sizeof(REF struct mfile *);
}


PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mfile) *
NOTHROW(FCALL mfile_delete_withfilelock_ex)(REF struct mfile *__restrict file,
                                            struct mpart *already_locked_part) {
	Tobpostlockop(mfile) *result;
	struct mpart_slist changes;
	struct mpart_delete_postop_builder deadparts;
	/* We're currently holding a write-lock to `file'!
	 * We can start out by clearing out the list of changed parts. */
	changes.slh_first = ATOMIC_XCH(file->mf_changed.slh_first,
	                               MFILE_PARTS_ANONYMOUS);
	mpart_delete_postop_builder_init(&deadparts);
	if (changes.slh_first != NULL &&
	    changes.slh_first != MFILE_PARTS_ANONYMOUS) {
		/* Clear  the  `MPART_F_CHANGED' flags  for all  changed parts,
		 * and  drop  references to  each of  them.  Note that  if this
		 * results in  any of  the parts  being destroyed,  then  we'll
		 * try to enqueue them for deletion _after_ `file' is unlocked. */
		do {
			REF struct mpart *part;
			part = SLIST_FIRST(&changes);
			SLIST_REMOVE_HEAD(&changes, mp_changed);
			DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
			ATOMIC_AND(part->mp_flags, ~MPART_F_CHANGED);

			/* Drop a reference from `part'. If the part dies, then
			 * enqueue  it for later  destruction via the post-lock
			 * operations mechanism. */
			if (ATOMIC_DECFETCH(part->mp_refcnt) == 0)
				mpart_delete_postop_builder_enqueue(&deadparts, part);
		} while (!SLIST_EMPTY(&changes));
	}

	/* Try  to acquire a lock to _all_ of the file's parts.
	 * If this fails, then enqueue a lock-operation on  the
	 * part that is blocking,  and only pass the  deadparts
	 * list to our caller in terms of post-lock operations. */
	if (file->mf_parts == NULL) {
		file->mf_parts = MFILE_PARTS_ANONYMOUS;
	} else if (file->mf_parts != MFILE_PARTS_ANONYMOUS) {
		struct mpart *part, *tree;
		tree = file->mf_parts;
		mpart_tree_increfall(tree);
		part = mpart_tree_trylockall(tree, already_locked_part);
		if unlikely(!part) {
			union mflops *mfl;
			mpart_tree_decrefall(tree, &deadparts);

			/* Found a part that's blocking...
			 * Because of  this, we  must enqueue  a locked  operation  within
			 * the context of `part' that'll try to complete the file deletion
			 * once that lock becomes available. */
			mfl                      = mfile_as_mflops(file);
			mfl->mfl_plop.olo_func = &mfile_delete_withpartlock;

			/* TODO */

			result = NULL;
			if (!mpart_delete_postop_builder_isempty(&deadparts))
				result = mpart_delete_postop_builder_asfop(&deadparts);
			return result;
		}

		/* Mark the part-tree as anonymous. */
		file->mf_parts = MFILE_PARTS_ANONYMOUS;

		/* Release  all of the part-locks, whilst simultaneously marking
		 * all of them as anonymous, altering their file-fields to point
		 * at  mfile_anon[*],  clearing their  MPART_F_GLOBAL_REF flags,
		 * changing the parts themself  to be considered anonymous,  and
		 * finally release a lock to each of them. */
		mpart_tree_forall_makeanon_and_unlock_decref(tree, already_locked_part,
		                                             file, &deadparts);
	}

	/* Success! - All that's left now is to set the file's size to zero! */
	if unlikely(ATOMIC_READ(file->mf_trunclock) != 0) {
		/* Use `struct sig_completion' to wait for `mf_trunclock' to
		 * become ZERO before  setting the file  size down to  zero. */
		struct sig_completion *sc;
		sc = &mfile_as_mflops(file)->mfl_compl;
		sig_completion_init(sc, &mfile_zerotrunc_completion_cb);
		sig_connect_completion_for_poll(&file->mf_initdone, sc);

		/* Make sure that the completion-callback  is always invoked in  case
		 * the `mf_trunclock' countered dropped to zero before our completion
		 * callback was connected. */
		if unlikely(ATOMIC_READ(file->mf_trunclock) == 0)
			sig_broadcast(&file->mf_initdone);

		/* Cleanup... */
		result = NULL;
		if (!mpart_delete_postop_builder_isempty(&deadparts))
			result = mpart_delete_postop_builder_asfop(&deadparts);
		return result;
	}

	/* Set the file size to zero. */
	atomic64_write(&file->mf_filesize, 0);

	/* As post-operations, destroy all dead parts, and drop a reference from `file' */
	if (!mpart_delete_postop_builder_isempty(&deadparts)) {
		union mflops *mfl;
		DBG_memset(mpart_as_mpart_delete_postop(deadparts.mdpb_delme), 0xcc,
		           sizeof(*mpart_as_mpart_delete_postop(deadparts.mdpb_delme)));
		mfl                          = mfile_as_mflops(file);
		mfl->mfl_deadparts.slh_first = deadparts.mdpb_delme;
		mfl->mfl_fplop.oplo_func    = &mfile_decref_and_destroy_deadparts_postop;
		return &mfl->mfl_fplop;
	}
	result             = &mfile_as_mflops(file)->mfl_fplop;
	result->oplo_func = &mfile_decref_postop;
	return result;
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mfile) *
NOTHROW(FCALL mfile_delete_withfilelock)(Toblockop(mfile) *__restrict self,
                                         struct mfile *__restrict UNUSED(_file)) {
	union mflops *mfl;
	REF struct mfile *file;
	mfl  = container_of(self, union mflops, mfl_flop);
	file = mfile_from_mflops(mfl);
	return mfile_delete_withfilelock_ex(file, NULL);
}

/* Initiate async file deletion. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_begin_async_delete)(/*inherit(always)*/ REF struct mfile *__restrict self) {
	if (mfile_lock_trywrite(self)) {
		Tobpostlockop(mfile) *post;
		post = mfile_delete_withfilelock(&mfile_as_mflops(self)->mfl_flop, self);
		mfile_lock_endwrite(self);
		if (post != NULL)
			(*post->oplo_func)(post, self);
	} else {
		Toblockop(mfile) *lop;
		/* Enqueue a lock operation. */
		lop = &mfile_as_mflops(self)->mfl_flop;
		lop->olo_func = &mfile_delete_withfilelock;
		SLIST_ATOMIC_INSERT(&self->mf_lockops, lop, olo_link);
		_mfile_lockops_reap(self);
	}
}


/* Make the given file anonymous+deleted. What this means is that (in order):
 *  - The `MFILE_F_DELETED' flag is set for the file.
 *  - The file-fields of all mem-parts are altered to point
 *    at  anonymous  memory   files.  (s.a.   `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' fields are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_filesize' field is set to `0'.
 * The result of all of this is that it is no longer possible to
 * trace  back  mappings  of  parts  of  `self'  to  that  file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become  unavailable for  some other reason  (e.g. the  backing
 * filesystem has been unmounted)
 *
 * Note that  (with the  exception of  `MFILE_F_DELETED' being  set, which  is
 * always done synchronously), this function operates entirely asynchronously,
 * meaning  that it uses lockops in order to wait for any locks it may need to
 * become available. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete)(struct mfile *__restrict self) {
	/* Start by setting  the DELETED  flag. -  If it  was already  set, then  we
	 * mustn't do anything since the file has either already been fully deleted,
	 * or another async-delete operation is already in progress!
	 *
	 * NOTE: We also set the NOATIME+NOMTIME flags to prevent anyone from changing
	 *       the `mf_atime' and `mf_mtime' fields after this point. - This must be
	 *       done since we intend on  (ab-)using those fields for storing  lock-op
	 *       descriptors needed do delete the file asynchronously.
	 *
	 * For simplicity, we set all of these flags at the same time, thus allowing
	 * someone who wishes to write to the atime or mtime fields to be able to do
	 * so via:
	 * >> mfile_tslock_acquire(self);
	 * >> if (!(self->mf_flags & MFILE_F_NOATIME))
	 * >>     self->mf_atime = ...;
	 * >> mfile_tslock_release(self);
	 *
	 * And anyone wishing to read those fields:
	 * >> struct timespec ts;
	 * >> mfile_tslock_acquire(self);
	 * >> ts = self->mf_atime;
	 * >> mfile_tslock_release(self);
	 * >> if (self->mf_flags & MFILE_F_DELETED) {
	 * >>     ... // Invalid data was read
	 * >> } else {
	 * >>     ... // Valid data was read
	 * >> }
	 */
	uintptr_t old_flags;
	mfile_tslock_acquire(self);
	old_flags = ATOMIC_FETCHOR(self->mf_flags,
	                           MFILE_F_DELETED |
	                           MFILE_F_NOATIME |
	                           MFILE_F_NOMTIME);
	mfile_tslock_release(self);

	/* Check if the file has already been marked as deleted. */
	if (old_flags & MFILE_F_DELETED)
		return;

	/* Looks  like the burden of deleting the file falls on us...
	 * Note  that by we've got quite a  bit of space to work with
	 * now, since we can (re-)use the file atime and mtime fields
	 * for storing lockop descriptors!
	 *
	 * Note that in  order to do  what we have  to, we somehow  have
	 * to  manage  to acquire  a lock  to `self',  and _all_  of the
	 * parts still found in its part-tree, _at_ _the_ _same_ _time_! */


	/* Inherited by `mfile_delete_withfilelock()' */
	incref(self);

	/* Do the thing! */
	mfile_begin_async_delete(self);
}

#else /* CONFIG_USE_NEW_FS */


/* Try to incref all parts of the given tree.
 * Parts that have already been destroyed are simply ignored. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_tree_tryincref)(struct mpart *__restrict root) {
again:
	COMPILER_UNUSED(tryincref(root));
	/* Recursive over the entire tree. */
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_tryincref(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

/* Drop references from all parts (that haven't already
 * been destroyed)  that  are  reachable  from  `root'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_tree_decref)(struct mpart *__restrict root) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if likely(!wasdestroyed(root))
		decref(root);
	/* Recursive over the entire tree. */
	if (lhs) {
		if (rhs)
			mpart_tree_decref(rhs);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}

/* Release locks to all parts reachable from `root'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_tree_unlock)(struct mpart *__restrict root) {
again:
	if likely(!wasdestroyed(root))
		mpart_lock_release(root);
	/* Recursive over the entire tree. */
	if (root->mp_filent.rb_lhs) {
		if (root->mp_filent.rb_rhs)
			mpart_tree_tryincref(root->mp_filent.rb_rhs);
		root = root->mp_filent.rb_lhs;
		goto again;
	}
	if (root->mp_filent.rb_rhs) {
		root = root->mp_filent.rb_rhs;
		goto again;
	}
}

/* Try  to acquire a lock to all parts reachable from `root'.
 * If one of these locks cannot be acquired without blocking,
 * release all locks already acquired and return that part. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mpart *
NOTHROW(FCALL mpart_tree_trylock)(struct mpart *__restrict root) {
	struct mpart *result;
	/* Try to lock the root-part. (but skip destroyed parts) */
	if likely(!wasdestroyed(root)) {
		if (!mpart_lock_tryacquire(root))
			return root;
	}
	/* Recursively lock the  entire tree (but  keep track of  our
	 * current path so we're always able to release exaclty those
	 * locks which we've already acquired previously). */
	if (root->mp_filent.rb_lhs) {
		result = mpart_tree_trylock(root->mp_filent.rb_lhs);
		if (result != NULL)
			goto err_lock_root;
	}
	if (root->mp_filent.rb_rhs) {
		result = mpart_tree_trylock(root->mp_filent.rb_rhs);
		if (result != NULL)
			goto err_lock_lhs;
	}
	return NULL;
err_lock_lhs:
	if (root->mp_filent.rb_lhs)
		mpart_tree_unlock(root->mp_filent.rb_lhs);
err_lock_root:
	if likely(!wasdestroyed(root))
		mpart_lock_release(root);
	return result;
}

/* Acquire  a lock  to all  parts within  the parts-tree of
 * `self', or decref all parts and release a lock to `self'
 * before waiting for the blocking part to become available
 * and returning `false' */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
mfile_lockparts_or_decref_and_unlock(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct mpart *blocking;
	/* Try to lock all parts. */
	blocking = mpart_tree_trylock(self->mf_parts);
	if (blocking) {
		/* Found a blocking part :( */
		incref(blocking); /* Keep around a reference to this part. */
		mpart_tree_decref(self->mf_parts);
		mfile_lock_endwrite(self);
		FINALLY_DECREF_UNLIKELY(blocking);
		/* Wait for the lock to become available. */
		while (!mpart_lock_available(blocking))
			task_yield();
		return false;
	}
	return true;
}


/* Make all parts reachable from  `root' anonymous, as well as  override
 * their `mp_file' field  with `mfile_anon[...]',  before releasing  the
 * lock  held to said part and dropping  a reference. If this results in
 * the part being destroyed, don't destroy it immediately, but add it to
 * the given `dead' list instead (linked via `_mp_dead')
 *
 * This is done for all parts reachable from `root'. */
PRIVATE NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL mpart_tree_makeanon_and_unlock_and_decref)(struct mpart *__restrict root,
                                                         struct mfile *__restrict file,
                                                         struct mpart_slist *__restrict dead) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if (!wasdestroyed(root)) {
		REF struct mfile *newfile;
		/* Set the NO_GLOBAL_REF bit, thus essentially unloading the part from the
		 * global part cache (should this mem-part  still be apart of said  cache) */
		if (ATOMIC_FETCHAND(root->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
			decref_nokill(root); /* The global reference... */
		_mpart_init_asanon(root);
		assert(root->mp_file == file);
		newfile = incref(&mfile_anon[file->mf_blockshift]);
		ATOMIC_WRITE(root->mp_file, newfile);
		/* Try to merge mem-parts after changing the pointed-to file.
		 * This  must be done to prevent a race condition relating to
		 * some very rare cases of async mem-part merging, as well as
		 * to ensure consistency,  and to allow  merging of  adjacent
		 * nodes within mman mapping trees. */
		root = mpart_merge_locked(root);
		mpart_lock_release(root);
		decref_nokill(file); /* The reference previously stored  in `root->mp_file' */
		if (ATOMIC_DECFETCH(root->mp_refcnt) == 0)
			SLIST_INSERT(dead, root, _mp_dead); /* Destroy this one later... */
	} else {
		DBG_memset(&root->mp_filent, 0xcc, sizeof(root->mp_filent));
	}
	/* Recursive over the entire tree. */
	if (lhs) {
		if (rhs)
			mpart_tree_makeanon_and_unlock_and_decref(rhs, file, dead);
		root = lhs;
		goto again;
	}
	if (rhs) {
		root = rhs;
		goto again;
	}
}


/* Make the given file anonymous+deleted. What this means is that:
 *  - Existing mappings of all  mem-parts are altered to  point
 *    at anonymous memory files. For this purpose, the nodes of
 *    all existing mappings are altered. (s.a. `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' are set to `MFILE_PARTS_ANONYMOUS'
 * The result of all of this is that it is no longer possible to
 * trace  back  mappings  of  parts  of  `self'  to  that  file.
 *
 * This function is called when the given file `self' should be deleted,
 * or has become  unavailable for  some other reason  (e.g. the  backing
 * filesystem has been unmounted) */
PUBLIC NONNULL((1)) void FCALL
mfile_delete(struct mfile *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct mpart_slist dead;

	/* Quick check: is the file already anonymous? */
	if (ATOMIC_READ(self->mf_parts) == MFILE_PARTS_ANONYMOUS)
		return; /* Nothing to do here! */
	SLIST_INIT(&dead);
again_lock:
	mfile_lock_write(self);
	COMPILER_READ_BARRIER();
	if (self->mf_parts == MFILE_PARTS_ANONYMOUS)
		goto done; /* Nothing to do here! */
	if (self->mf_parts == NULL) {
		self->mf_parts = MFILE_PARTS_ANONYMOUS;
		goto do_clear_changed_parts;
	}
	/* Try to incref all of the parts from `self' */
	mpart_tree_tryincref(self->mf_parts);

	/* Acquire locks to all parts. */
	if (!mfile_lockparts_or_decref_and_unlock(self))
		goto again_lock;

	/* For every node within the tree, do the following:
	 * >> if (!wasdestroyed(part)) {
	 * >>     if (ATOMIC_FETCHAND(part->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
	 * >>         decref_nokill(part);
	 * >>     _mpart_init_asanon(part);
	 * >>     assert(part->mp_file == self);
	 * >>     part->mp_file = incref(&mfile_anon[...]);
	 * >>     decref_nokill(self);
	 * >>     if (ATOMIC_DECFETCH(part->mp_refcnt) == 0)
	 * >>         SLIST_INSERT(&dead, part, _mp_dead);
	 * >> } */
	mpart_tree_makeanon_and_unlock_and_decref(self->mf_parts, self, &dead);
	self->mf_parts = MFILE_PARTS_ANONYMOUS;
do_clear_changed_parts:

	/* Clear the list of changed mem-parts. Anything non-synced changes that
	 * still exist at this point will be lost, but we must still drop all of
	 * the references stored in the changed-part list! */
	{
		struct mpart_slist changed;
		changed.slh_first = ATOMIC_XCH(self->mf_changed.slh_first, MFILE_PARTS_ANONYMOUS);
		assert(changed.slh_first != MFILE_PARTS_ANONYMOUS);
		while (!SLIST_EMPTY(&changed)) {
			struct mpart *part;
			part = SLIST_FIRST(&changed);
			SLIST_REMOVE_HEAD(&changed, mp_changed);
			assert(part->mp_file == &mfile_anon[self->mf_blockshift]);
			DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));

			/* Also clear the CHANGED bit for all of the parts.
			 * We're allowed to do  this because we've set  the changed list of  ANON,
			 * giving us special permissions to clear this bit (s.a. the documentation
			 * of the `MPART_F_CHANGED' flag) */
			ATOMIC_AND(part->mp_flags, ~MPART_F_CHANGED);

			/* Drop  a reference from the changed mem-part. This is the reference
			 * that was originally created when the part was added to the changed
			 * list. */
			if (ATOMIC_DECFETCH(part->mp_refcnt) == 0)
				SLIST_INSERT(&dead, part, _mp_dead);
		}
	} /* Scope... */

done:
	mfile_lock_endwrite_f(self);

	/* Destroy all mem-parts apart of the dead-list. */
	while (!SLIST_EMPTY(&dead)) {
		struct mpart *part;
		part = SLIST_FIRST(&dead);
		SLIST_REMOVE_HEAD(&dead, _mp_dead);
		mpart_destroy(part);
	}

	/* Reap  lockops _after_  having destroyed  all of  the old parts
	 * have been destroyed, thus raising the interlocked-ness between
	 * those 2 operations, which may potentially increase efficiency. */
	mfile_lockops_reap(self);

	/* Wake-up possibly waiting threads.
	 * Since we've altered the backing files of a lot of parts, we
	 * have to ensure that threads waiting for init to be done are
	 * connected to the relevant signal. */
	sig_broadcast(&self->mf_initdone);
}
#endif /* !CONFIG_USE_NEW_FS */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C */
