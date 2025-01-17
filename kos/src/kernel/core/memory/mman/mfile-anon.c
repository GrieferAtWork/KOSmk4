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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C 1
#define __WANT_MPART__mp_anXplop
#define __WANT_MPART__mp_dead
#define __WANT_MFILE__mf_lop
#define __WANT_MFILE__mf_plop
#define __WANT_MFILE__mf_lopX
#define __WANT_MFILE__mf_mplop
#define __WANT_MFILE__mf_mflop
#define __WANT_MFILE__mf_mfplop
#define __WANT_MFILE__mf_deadparts
#define __WANT_MFILE__mf_compl
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/allnodes.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/super.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <sched/sig-completion.h>
#include <sched/task.h>

#include <hybrid/minmax.h>

#include <kos/lockop.h>

#include <assert.h>
#include <atomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE ATTR_NOINLINE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_decref_after_delete_extusage)(REF struct mfile *__restrict self);


/* Called after referencing elements from `fallsuper_list'
 * were removed for `MFILE_F_EXTUSAGE'-marked file  `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_decref_after_delete_extusage_mounts)(REF struct mfile *__restrict self) {
	/* More file-usages that set `MFILE_F_EXTUSAGE' can be handled here... */
	decref(self);
}



/************************************************************************/
/* ASYNC FILE MOUNT DELETION                                            */
/************************************************************************/

#define _MFILE_EXTUSAGE_FSUPER_OFFSET      MAX_C(sizeof(struct postlockop), sizeof(struct lockop))
#define _mfile_extusage_getfsuper(self)    (*(struct fsuper *const *)((self)->_mf_lopX + _MFILE_EXTUSAGE_FSUPER_OFFSET))
#define _mfile_extusage_setfsuper(self, v) (void)(*(struct fsuper **)((self)->_mf_lopX + _MFILE_EXTUSAGE_FSUPER_OFFSET) = (v))
static_assert(sizeof(((struct mfile *)0)->_mf_lopX) >= (_MFILE_EXTUSAGE_FSUPER_OFFSET + sizeof(struct fsuper *)));

PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct fsuper *
NOTHROW(FCALL fallsuper_try_remove_by_device_locked)(struct mfile *__restrict self) {
	struct fsuper *fs;
	LIST_FOREACH (fs, &fallsuper_list, fs_root.fn_allsuper) {
		if (fs->fs_dev == self && likely(tryincref(fs))) {
			/* Remove from the list of all superblocks. */
			fallsuper_remove(fs);
			LIST_ENTRY_UNBOUND_INIT(&fs->fs_root.fn_allsuper);

			/* Clear  the global flag  (if set) since we
			 * removed the superblock from the all-list. */
			if (atomic_fetchand(&fs->fs_root.mf_flags, ~MFILE_FN_GLOBAL_REF))
				decref_nokill(fs);
			return fs;
		}
	}
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC mfile_decref_after_delete_extusage_allsuper_plop)(struct postlockop *__restrict self) {
	REF struct fsuper *fs;
	REF struct mfile *me;
	me = container_of(self, struct mfile, _mf_plop);
	fs = _mfile_extusage_getfsuper(me);
	if (fs) {
		/* Delete  the  superblock and  drop the  reference we
		 * got from `fallsuper_try_remove_by_device_locked()'. */
		fsuper_delete_and_decref(fs);

		/* Repeat the search for more filesystems (unlikely, but *technically* you're allowed to mount
		 * a file multiple times, so-long as you (somehow) skip the `fsuper') */
		mfile_decref_after_delete_extusage(me);
	} else {
		mfile_decref_after_delete_extusage_mounts(me);
	}
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(LOCKOP_CC mfile_decref_after_delete_extusage_allsuper_lop)(struct lockop *__restrict self) {
	REF struct fsuper *fs;
	REF struct mfile *me;
	me = container_of(self, struct mfile, _mf_lop);
	fs = fallsuper_try_remove_by_device_locked(me);
	_mfile_extusage_setfsuper(me, fs);
	me->_mf_plop.plo_func = &mfile_decref_after_delete_extusage_allsuper_plop;
	return &me->_mf_plop;
}

PRIVATE ATTR_NOINLINE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_decref_after_delete_extusage)(REF struct mfile *__restrict self) {
again:
	if (fallsuper_tryacquire()) {
		REF struct fsuper *super;
		super = fallsuper_try_remove_by_device_locked(self);
		fallsuper_release();
		if (super) {
			fsuper_delete_and_decref(super);
			goto again;
		}
		mfile_decref_after_delete_extusage_mounts(self);
	} else {
		/* Must use a lock-op. */
		self->_mf_lop.lo_func = &mfile_decref_after_delete_extusage_allsuper_lop; /* inherit reference */
		lockop_enqueue(&fallsuper_lockops, &self->_mf_lop);
		_fallsuper_reap();
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_decref_after_delete)(REF struct mfile *__restrict self) {
	/* Generate `IN_IGNORED' */
	mfile_inotify_ignored(self);

	/* If `self' is being used to mount a super-block, force-delete
	 * that superblock (case: you pull out a thumb-drive while it's
	 * mounted,  and we want  those mounts to  disappear as soon as
	 * possible) */
	if unlikely(self->mf_flags & MFILE_F_EXTUSAGE) {
		mfile_decref_after_delete_extusage(self);
		return;
	}

	/* Drop the inherited reference to the original file. */
	decref_unlikely(self);
}





/************************************************************************/
/* ASYNC FILE DELETION                                                  */
/************************************************************************/

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC mpart_delete_postop_cb)(Tobpostlockop(mfile) *__restrict self,
                                          struct mfile *__restrict UNUSED(obj)) {
	struct mpart *chain, *next;
	chain = container_of(self, struct mpart, _mp_anfplop);
	DBG_memset(&chain->_mp_anfplop, 0xcc, sizeof(chain->_mp_anfplop));
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
#define mpart_delete_postop_builder_asfop(self)   (&(self)->mdpb_delme->_mp_anfplop)
#define mpart_delete_postop_builder_aspop(self)   (&(self)->mdpb_delme->_mp_anpplop)

/* Enqueue a given mem-part `delme' on which to call `mpart_destroy()' from  within
 * the post-op that can be constructed with `mpart_delete_postop_builder_as(f|p)op' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_delete_postop_builder_enqueue)(struct mpart_delete_postop_builder *__restrict self,
                                                   struct mpart *__restrict delme) {
	struct mpart *primary = self->mdpb_delme;
	if (primary == NULL) {
		delme->_mp_anfplop.oplo_func = &mpart_delete_postop_cb;
		delme->_mp_dead.sle_next     = NULL;
		self->mdpb_delme             = delme;
	} else {
		delme->_mp_dead.sle_next   = primary->_mp_dead.sle_next;
		primary->_mp_dead.sle_next = delme;
	}
}




/* Try to acquire a reference to all parts reachable from `root'.
 * Parts  that  had  already  been  destroyed  will  be  skipped. */
PRIVATE NOBLOCK NONNULL((1)) void
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
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_tree_decrefall)(struct mpart *__restrict root,
                                    struct mpart_delete_postop_builder *__restrict deadparts) {
	struct mpart *lhs, *rhs;
again:
	lhs = root->mp_filent.rb_lhs;
	rhs = root->mp_filent.rb_rhs;
	if (!wasdestroyed(root)) {
		if (atomic_decfetch(&root->mp_refcnt) == 0)
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
PRIVATE NOBLOCK NONNULL((1)) void
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
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mpart *
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
PRIVATE NOBLOCK NONNULL((1, 3, 4)) void
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
		_mpart_init_asanon(root); /* TODO: Posix wants access to SHARED nodes of `root' after this point to raise SIGBUS */
		assert(root->mp_file == file);
		newfile = incref(&mfile_anon[file->mf_blockshift]);
		atomic_write(&root->mp_file, newfile);
		decref_nokill(file);
		if (atomic_fetchand(&root->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
			decref_nokill(root);

		/* Try to merge mem-parts after changing the pointed-to file.
		 * This  must be done to prevent a race condition relating to
		 * some very rare cases of async mem-part merging, as well as
		 * to ensure consistency,  and to allow  merging of  adjacent
		 * nodes within mman mapping trees. */
		if likely(root != dont_unlock_me) {
			root = mpart_merge_locked(root);
			mpart_lock_release(root);
		} else {
			/* We can't do the merge right now since we're not allowed
			 * to  release/change `dont_unlock_me', but what we can do
			 * is enqueue the merge to be done later. */
			mpart_start_asyncjob(root, MPART_XF_WILLMERGE);
		}

		/* Drop the reference gifted to us by the caller. */
		if (atomic_decfetch(&root->mp_refcnt) == 0) {
			assert(root != dont_unlock_me);
			mpart_delete_postop_builder_enqueue(deadparts, root);
		}
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
NOTHROW(LOCKOP_CC mfile_delete_withfilelock)(Toblockop(mfile) *__restrict self,
                                             REF struct mfile *__restrict file);
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC mfile_decref_and_destroy_deadparts_postop)(Tobpostlockop(mfile) *__restrict self,
                                                             struct mfile *__restrict file);
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC mfile_decref_postop)(Tobpostlockop(mfile) *__restrict self,
                                       struct mfile *__restrict file);


PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mpart) *
NOTHROW(LOCKOP_CC mfile_delete_withpartlock)(Toblockop(mpart) *__restrict self,
                                             struct mpart *__restrict part) {
	REF struct mfile *me;
	me = container_of(self, struct mfile, _mf_mplop);

	/* Also try to acquire a lock to the file. */
	if (mfile_lock_trywrite(me)) {
		Tobpostlockop(mfile) *pop;

		/* Try to delete the file, but remember that we're already holding a lock to `part'! */
		pop = mfile_delete_withfilelock_ex(me, part);
		mfile_lock_endwrite(me);
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
	me->_mf_mflop.olo_func = &mfile_delete_withfilelock;
	oblockop_enqueue(&me->mf_lockops, &me->_mf_mflop);
	_mfile_lockops_reap(me);
	return NULL;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC mfile_decref_and_destroy_deadparts_postop)(Tobpostlockop(mfile) *__restrict self,
                                                             struct mfile *__restrict UNUSED(_file)) {
	REF struct mfile *me;
	struct mpart_slist deadparts;
	me        = container_of(self, struct mfile, _mf_mfplop);
	deadparts = me->_mf_deadparts;
	DBG_memset(me->_mf_lopX, 0xcc, sizeof(me->_mf_lopX));

	/* Destroy all dead parts. */
	while (!SLIST_EMPTY(&deadparts)) {
		struct mpart *part;
		part = SLIST_FIRST(&deadparts);
		SLIST_REMOVE_HEAD(&deadparts, _mp_dead);
		DBG_memset(&part->_mp_dead, 0xcc, sizeof(part->_mp_dead));
		mpart_destroy(part);
	}
	mfile_decref_after_delete(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC mfile_decref_postop)(Tobpostlockop(mfile) *__restrict self,
                                       struct mfile *__restrict UNUSED(_file)) {
	REF struct mfile *me;
	me = container_of(self, struct mfile, _mf_mfplop);
	mfile_decref_after_delete(me);
}

PRIVATE NOBLOCK void
NOTHROW(FCALL mfile_zerotrunc_completion2_cb)(struct sig_completion_context *__restrict UNUSED(context),
                                              void *buf) {
	REF struct mfile *file;
	file = *(REF struct mfile **)buf;

	/* Re-start async file deletion from scratch, since
	 * we're  not actually holding any locks right now! */
	mfile_delete_impl(file);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL mfile_zerotrunc_completion_cb)(struct sig_completion *__restrict self,
                                             struct sig_completion_context *__restrict context,
                                             void *buf, size_t bufsize) {
	REF struct mfile *me;
	me = container_of(self, struct mfile, _mf_compl);

	/* Check if the trunc-lock has been released... */
	if (atomic_read(&me->mf_trunclock) != 0) {
		sig_completion_reprime(self, true);
		return 0;
	}

	/* All right! - Time to do this.
	 * Note however that we must do the actual work in a phase-2 completion
	 * callback,   since   deletion   of   a   file   isn't  SMP-lock-safe! */
	if (bufsize < sizeof(REF struct mfile *))
		return sizeof(REF struct mfile *);
	*(REF struct mfile **)buf = me; /* Inherited by `mfile_zerotrunc_completion2_cb()' */
	context->scc_post = &mfile_zerotrunc_completion2_cb;
	return sizeof(REF struct mfile *);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_do_delete_msalign_files)(struct mfile *__restrict self) {
	assert(mfile_lock_writing(self));
	assert(!LIST_EMPTY(&self->mf_msalign));
	do {
		struct misaligned_mfile *file;
		file = LIST_FIRST(&self->mf_msalign);
		LIST_UNBIND(file, mam_link); /* UNBIND! (s.a. `misaligned_mfile_v_destroy()') */

		/* If the file hasn't been destroyed yet, then try to delete it. */
		if (tryincref(file))
			mfile_delete_and_decref(file);
	} while (!LIST_EMPTY(&self->mf_msalign));
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mfile) *
NOTHROW(FCALL mfile_delete_withfilelock_ex)(REF struct mfile *__restrict file,
                                            struct mpart *already_locked_part) {
	Tobpostlockop(mfile) *result;
	struct mpart_slist changes;
	struct mpart_delete_postop_builder deadparts;

	/* Start out with something easy: recursively delete misaligned files. */
	if unlikely(!LIST_EMPTY(&file->mf_msalign))
		mfile_do_delete_msalign_files(file);

	/* We're currently holding a write-lock to `file'!
	 * We can start out by clearing out the list of changed parts. */
	changes.slh_first = atomic_xch(&file->mf_changed.slh_first,
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
			atomic_and(&part->mp_flags, ~MPART_F_CHANGED);

			/* Drop a reference from `part'. If the part dies, then
			 * enqueue  it for later  destruction via the post-lock
			 * operations mechanism. */
			if (atomic_decfetch(&part->mp_refcnt) == 0)
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
		if unlikely(part != NULL) {
			incref(part);
			mpart_tree_decrefall(tree, &deadparts);

			/* Found a part that's blocking...
			 * Because of  this, we  must enqueue  a locked  operation  within
			 * the context of `part' that'll try to complete the file deletion
			 * once that lock becomes available. */
			file->_mf_mplop.olo_func = &mfile_delete_withpartlock;
			oblockop_enqueue(&part->mp_lockops, &file->_mf_mplop);
			_mpart_lockops_reap(part);
			if (atomic_decfetch(&part->mp_refcnt) == 0)
				mpart_delete_postop_builder_enqueue(&deadparts, part);

			/* The rest  of the  deletion of  `file' will  happen
			 * async from inside of `mfile_delete_withpartlock()' */
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
	if unlikely(atomic_read(&file->mf_trunclock) != 0) {
		/* Use `struct sig_completion' to wait for `mf_trunclock' to
		 * become ZERO before  setting the file  size down to  zero. */
		sig_completion_init(&file->_mf_compl, &mfile_zerotrunc_completion_cb);
		sig_connect_completion_for_poll(&file->mf_initdone, &file->_mf_compl);

		/* Make sure that the completion-callback is always invoked in case
		 * the `mf_trunclock' counter dropped to zero before our completion
		 * callback was connected. */
		if unlikely(atomic_read(&file->mf_trunclock) == 0)
			sig_broadcast(&file->mf_initdone);

		/* Cleanup... */
		result = NULL;
		if (!mpart_delete_postop_builder_isempty(&deadparts))
			result = mpart_delete_postop_builder_asfop(&deadparts);
		return result;
	}

	/* Set the file size to zero. */
	atomic64_write(&file->mf_filesize, 0);

	/* In order to wake up threads which may be doing tail-reads,
	 * we broadcast the `mf_initdone' signal, which is also  used
	 * during mfile_tailread() to  wait for more  data to  become
	 * available. */
	sig_broadcast(&file->mf_initdone);


	/* As post-operations, destroy all dead parts, and drop a reference from `file' */
	if (!mpart_delete_postop_builder_isempty(&deadparts)) {
		DBG_memset(mpart_delete_postop_builder_asfop(&deadparts), 0xcc,
		           sizeof(*mpart_delete_postop_builder_asfop(&deadparts)));
		file->_mf_deadparts.slh_first = deadparts.mdpb_delme;
		file->_mf_mfplop.oplo_func    = &mfile_decref_and_destroy_deadparts_postop;
		return &file->_mf_mfplop;
	}
	result            = &file->_mf_mfplop;
	result->oplo_func = &mfile_decref_postop;
	return result;
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mfile) *
NOTHROW(LOCKOP_CC mfile_delete_withfilelock)(Toblockop(mfile) *__restrict self,
                                             struct mfile *__restrict UNUSED(_file)) {
	REF struct mfile *me;
	me = container_of(self, struct mfile, _mf_mflop);
	return mfile_delete_withfilelock_ex(me, NULL);
}


/* Internal implementation of `mfile_delete()' (don't call this one
 * unless you know that you're doing; otherwise, you may cause race
 * conditions that can result in data corruption) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete_impl)(/*inherit(always)*/ REF struct mfile *__restrict self) {
	if (mfile_lock_trywrite(self)) {
		Tobpostlockop(mfile) *post;
		post = mfile_delete_withfilelock(&self->_mf_mflop, self);
		mfile_lock_endwrite(self);
		if (post != NULL)
			(*post->oplo_func)(post, self);
	} else {
		/* Enqueue a lock operation. */
		self->_mf_mflop.olo_func = &mfile_delete_withfilelock;
		oblockop_enqueue(&self->mf_lockops, &self->_mf_mflop);
		_mfile_lockops_reap(self);
	}
}


/* Make the given file anonymous+deleted. What this means is that (in order):
 *  - The `MFILE_F_DELETED' flag is set for the file.
 *  - The `MFILE_F_PERSISTENT' flag is cleared for the file.
 *  - The file-fields of all mem-parts are altered to point
 *    at  anonymous  memory   files.  (s.a.   `mfile_anon')
 *  - The `MPART_F_GLOBAL_REF' flag is cleared for all parts
 *  - The `mf_parts' and `mf_changed' fields are set to `MFILE_PARTS_ANONYMOUS'
 *  - The `mf_filesize' field is set to `0'.
 *  - The `mf_msalign' list is cleared and after recursively mfile_delete-ing contained files.
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
	 *       the `mf_atime', `mf_mtime' and `mf_btime' fields after this point.  -
	 *       This must be  done since  we intend  on (ab-)using  those fields  for
	 *       storing lock-op descriptors needed to delete the file asynchronously.
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
	old_flags = atomic_fetchor(&self->mf_flags,
	                           MFILE_F_DELETED |
	                           MFILE_F_NOATIME |
	                           MFILE_F_NOMTIME);
	mfile_tslock_release(self);

	/* Also clear the PERSISTENT flag */
	if (old_flags & MFILE_F_PERSISTENT)
		atomic_and(&self->mf_flags, ~MFILE_F_PERSISTENT);

	/* Check if the file has already been marked as deleted. */
	if (old_flags & MFILE_F_DELETED)
		return;

	/* Broadcast that the file was marked as deleted. */
	sig_broadcast(&self->mf_initdone);

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
	mfile_delete_impl(self);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_delete_and_decref)(REF struct mfile *__restrict self) {
	/* Same as `mfile_delete()', but inherit a reference to `self' */
	uintptr_t old_flags;
	mfile_tslock_acquire(self);
	old_flags = atomic_fetchor(&self->mf_flags,
	                           MFILE_F_DELETED |
	                           MFILE_F_NOATIME |
	                           MFILE_F_NOMTIME);
	mfile_tslock_release(self);
	if (old_flags & MFILE_F_PERSISTENT)
		atomic_and(&self->mf_flags, ~MFILE_F_PERSISTENT);
	if (old_flags & MFILE_F_DELETED) {
		decref(self);
		return;
	}
	sig_broadcast(&self->mf_initdone);
	mfile_delete_impl(self);
}



/* Do various things necessary to set `MFILE_F_DELETING' in `self->mf_flags'.
 *
 * NOTES:
 * - The caller must have already asserted that there are no trunc-lock (`self->mf_trunclock == 0')
 * - The caller must have already asserted that `MFILE_F_DELETING' isn't already set.
 * - The caller must be holding a write-lock to `self'
 * - This function will *NEVER* set `MFILE_F_DELETED' itself (it only checks if it is/gets set)
 * - The given in-file address range is used to determine which MAP_PRIVATE parts to load
 * - The caller of this function still has to decide how to deal with misaligned sub-files of `self'
 *
 * @param: delete_minaddr: The lowest in-file address where you intend to delete data
 * @param: delete_maxaddr: The greatest in-file address where you intend to delete data
 * @return: true:  Success (`MFILE_F_DELETING' is now set)
 * @return: false: Locks were released -> try again */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mfile_deleting_begin_locked_or_unlock(struct mfile *__restrict self,
                                      pos_t delete_minaddr,
                                      pos_t delete_maxaddr,
                                      struct unlockinfo *unlock)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...) {
#define LOCAL_unlock_all()        \
	(mfile_lock_endwrite_f(self), \
	 unlockinfo_xunlock(unlock),  \
	 mfile_lockops_reap(self))
	assert(mfile_lock_writing(self));
	assert(self->mf_trunclock == 0);
	assert(!(self->mf_flags & MFILE_F_DELETING));

	if likely(self->mf_parts != MFILE_PARTS_ANONYMOUS) {
		if (delete_minaddr == 0 && delete_maxaddr == (pos_t)-1) {
			/* Special-case optimization for when the entire file is being deleted
			 * This is the case when we get here from `ftruncate(0)' or `unlink()' */
			if (!mfile_incref_and_lock_parts_or_unlock(self, unlock))
				return false;
			if (!mfile_parts_denywrite_or_unlock(self, unlock))
				return false;
			if (!mfile_parts_loadprivate_or_unlock(self, unlock))
				return false;
		} else {
			/* Acquire references and locks to all parts of `self' */
			if (!mfile_incref_and_lock_parts_r_or_unlock(self, delete_minaddr, delete_maxaddr, unlock))
				return false;

			/* Deny write access to memory mappings. */
			if (!mfile_parts_denywrite_r_or_unlock(self, delete_minaddr, delete_maxaddr, unlock))
				return false;

			/* Load parts linked to MAP_PRIVATE nodes. */
			if (!mfile_parts_loadprivate_r_or_unlock(self, delete_minaddr, delete_maxaddr, unlock))
				return false;
		}

		/* Actually set the DELETING flag. */
		atomic_or(&self->mf_flags, MFILE_F_DELETING);

		/* Release locks to parts of `self' */
		mfile_unlock_and_decref_parts(self);
	} else {
		/* Without any parts, we can set the DELETING flag without any extra work. */
		atomic_or(&self->mf_flags, MFILE_F_DELETING);
	}
	return true;
#undef LOCAL_unlock_all
}


struct misaligned_mfile_unlink_prepare_unlockinfo: unlockinfo {
	struct misaligned_mfile *msmupui_msfile; /* [1..1] The misaligned file currently being prepared. */
	struct unlockinfo       *msmupui_inner;  /* [0..1] Inner unlock-info */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL misaligned_mfile_unlink_prepare_unlockinfo_cb)(struct unlockinfo *__restrict self) {
	struct mfile *file;
	struct misaligned_mfile *ms;
	struct misaligned_mfile_unlink_prepare_unlockinfo *me;
	me   = (struct misaligned_mfile_unlink_prepare_unlockinfo *)self;
	ms   = me->msmupui_msfile;
	file = ms->mam_base;
	while (ms != LIST_FIRST(&file->mf_msalign)) {
		ms = LIST_PREV_UNSAFE(ms, mam_link);
		decref_unlikely(ms);
		mfile_deleting_rollback(ms);
	}
	assert(file->mf_flags & MFILE_F_DELETING);
	mfile_lock_endwrite(file);
	mfile_deleting_rollback(file);
	unlockinfo_xunlock(me->msmupui_inner);
}


/* Prepare `self' for being unlinked.
 *
 * This function uses `mfile_deleting_begin_locked_or_unlock()' to set `MFILE_F_DELETING'
 * for `self' and all associated misaligned sub-files, as well as forces all  MAP_PRIVATE
 * file mappings into memory (which obviously includes mmapread mappings).
 *
 * This function should be called in order to prepare a file for unlinking. */
PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) bool FCALL
mfile_unlink_prepare_locked_or_unlock(struct mfile *__restrict self,
                                      struct mfile_unlink_info *__restrict info,
                                      struct unlockinfo *unlock)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...) {
#define LOCAL_unlock_all() (mfile_lock_endwrite(self), unlockinfo_xunlock(unlock))
	assert(mfile_lock_writing(self));

	/* Wait for trunc locks (if present) */
	if unlikely(atomic_read(&self->mf_trunclock) != 0) {
		LOCAL_unlock_all();
		mfile_trunclock_waitfor(self);
		return false;
	}

	/* Wait for the DELETING flag to not be set */
	{
		uintptr_t file_flags;
		file_flags = atomic_read(&self->mf_flags);
		if unlikely(file_flags & (MFILE_F_DELETING | MFILE_F_DELETED)) {
			if unlikely(file_flags & MFILE_F_DELETED) {
				info->mfui_deleted = true;
				return true; /* File was already deleted */
			}
			LOCAL_unlock_all();
			mfile_deleting_waitfor(self);
			return false;
		}
	}

	/* Do all the rest. */
	if (!mfile_deleting_begin_locked_or_unlock(self, 0, (pos_t)-1, unlock))
		return false;

	/* If there are misaligned sub-files, recursively mark those as deleted.
	 * Note that the  presence of the  `MFILE_F_DELETING' flag prevents  new
	 * misaligned files from being added,  and since we acquire a  reference
	 * to all of them, this also prevents parts from being removed  (meaning
	 * that in the  end, we have  the guaranty that  the list of  misaligned
	 * files will *not* change until we're done) */
	if unlikely(!LIST_EMPTY(&self->mf_msalign)) {
		struct misaligned_mfile *ms, *next;
		assert(!mfile_ismisaligned(self));
		for (ms = LIST_FIRST(&self->mf_msalign); ms; ms = next) {
			struct misaligned_mfile_unlink_prepare_unlockinfo ui;
			struct mfile_unlink_info ms_info;
			next = LIST_NEXT(ms, mam_link);
			if unlikely(!tryincref(ms)) {
				/* Disabled dead files. */
				LIST_UNBIND(ms, mam_link);
				continue;
			}
			ui.ui_unlock      = &misaligned_mfile_unlink_prepare_unlockinfo_cb;
			ui.msmupui_msfile = ms;
			ui.msmupui_inner  = unlock;
			if (!mfile_unlink_prepare_or_unlock(ms, &ms_info, &ui)) {
				decref_unlikely(ms);
				return false;
			}
			if (ms_info.mfui_deleted) {
				/* Misaligned file was already marked as DELETED
				 * -> just get rid of it... */
				assert(ms->mf_flags & MFILE_F_DELETED);
				LIST_UNBIND(ms, mam_link);
			}
		}
	}

	info->mfui_deleted = false;
	return true;
#undef LOCAL_unlock_all
}

PUBLIC BLOCKING WUNUSED NONNULL((1, 2)) bool FCALL
mfile_unlink_prepare_or_unlock(struct mfile *__restrict self,
                               struct mfile_unlink_info *__restrict info,
                               struct unlockinfo *unlock)
		THROWS(E_INTERRUPT_USER_RPC, E_WOULDBLOCK, ...) {
#define LOCAL_unlock_all() (unlockinfo_xunlock(unlock))
	bool result;
	if (!mfile_lock_trywrite(self)) {
		LOCAL_unlock_all();
		mfile_lock_waitwrite(self);
		return false;
	}
	result = mfile_unlink_prepare_locked_or_unlock(self, info, unlock);
	if (result)
		mfile_lock_endwrite(self);
	return result;
#undef LOCAL_unlock_all
}

/* Roll-back the actions of `mfile_unlink_prepare_or_unlock()' */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfile_unlink_rollback)(struct mfile *__restrict self,
                                     struct mfile_unlink_info const *__restrict info) {
	struct misaligned_mfile *ms;
	if (info->mfui_deleted)
		return;
	assert(self->mf_flags & MFILE_F_DELETING);
	LIST_FOREACH_SAFE (ms, &self->mf_msalign, mam_link) {
		assert(!wasdestroyed(ms));
		mfile_deleting_rollback(ms);
		decref_unlikely(ms);
	}
	mfile_deleting_rollback(self);
}

/* Must be called prior to `mfile_delete(self)' or whatever other
 * function has to  be used to  asynchronously anonymize  `self'. */
PUBLIC NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _mfile_unlink_commit_prehook)(struct mfile *__restrict self,
                                            struct mfile_unlink_info const *__restrict info) {
	struct misaligned_mfile *ms;
	if (info->mfui_deleted)
		return;
	assert(self->mf_flags & MFILE_F_DELETING);
	/* Drop references to misaligned files created above. */
	LIST_FOREACH_SAFE (ms, &self->mf_msalign, mam_link) {
		assert(!wasdestroyed(ms));
		assert(ms->mf_flags & MFILE_F_DELETING);
#if 0 /* Don't  need to delete right now; once  the base file gets deleted, the
       * misaligned sub-files will, too. s.a. `mfile_do_delete_msalign_files()' */
		mfile_delete_and_decref(ms);
#else
		decref_unlikely(ms);
#endif
	}
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_C */
